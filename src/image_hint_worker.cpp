#include <image_hint_worker/image_hint_worker.h>
#include <lms/datamanager.h>
#include <lms/imaging/find/line.h>
#include <lms/imaging/draw_debug.h>
#include <lms/imaging/image_factory.h>
#include <lms/imaging/find/image_hint.h>
bool ImageHintWorker::cycle(){
    if(gaussBuffer->width() < target->width() || gaussBuffer->height() < target->height()){
        gaussBuffer->resize(target->width(),target->height(),lms::imaging::Format::GREY);
    }
    gaussBuffer->fill(255);
    debug->resize(target->width(),target->height(),lms::imaging::Format::BGRA);
    debug->fill(0);


    for(lms::imaging::find::ImageHintBase *base: hintContainer->hints){
        base->find(*debugGraphics);
    }

    return true;
}

bool ImageHintWorker::initialize(){

    gaussBuffer = new lms::imaging::Image();
    //just for testing
    target = datamanager()->readChannel<lms::imaging::Image>(this,"GREY_IMAGE");
    debug = datamanager()->writeChannel<lms::imaging::Image>(this,"DEBUG_IMAGE");
    hintContainer = datamanager()->writeChannel<lms::imaging::find::HintContainer>(this,"HINTS");
    debugGraphics = new lms::imaging::BGRAImageGraphics(*debug);

    lms::imaging::find::ImageHint<lms::imaging::find::Line> *hint = new lms::imaging::find::ImageHint<lms::imaging::find::Line>();
    hint->name = "RIGHT_LANE";
    hint->parameter.target = target;
    hint->parameter.approxEdge = false;
    hint->parameter.lineWidthMax = 10;
    hint->parameter.lineWidthMin = 2;
    hint->parameter.maxLength = 100;
    hint->parameter.searchAngle = 0;
    hint->parameter.searchLength = 100;
    hint->parameter.gaussBuffer = gaussBuffer;
    hint->parameter.x = 240;
    hint->parameter.y = 150;
    hint->parameter.sobelThreshold = 250;
    hint->parameter.stepLengthMin = 2;
    hint->parameter.stepLengthMax = 20;
    hint->parameter.lineWidthTransMultiplier = 1;
    hint->parameter.edge = false;
    //add it
    hintContainer->add(hint);

    hint = new lms::imaging::find::ImageHint<lms::imaging::find::Line>(*hint);
    hint->name = "LEFT_LANE";
    hint->parameter.x = 80;
    hint->parameter.searchAngle = -M_PI;
    hintContainer->add(hint);

    hint = new lms::imaging::find::ImageHint<lms::imaging::find::Line>(*hint);
    hint->name = "BOX";
    hint->parameter.x = 120;
    hint->parameter.y = 100;
    hint->parameter.searchAngle = -M_PI_2l*1.5;
    hint->parameter.stepLengthMax = 5;
    hint->parameter.lineWidthMax = 5;
    hint->parameter.maxLength = 20;
    hint->parameter.edge = true;
    hintContainer->add(hint);

    return true;
}

bool ImageHintWorker::deinitialize(){
    return false;
}
