#include <image_hint_worker/image_hint_worker.h>
#include <lms/datamanager.h>
#include <lms/imaging/find/line.h>
#include <lms/imaging/draw_debug.h>
bool ImageHintWorker::cycle(){
    lms::imaging::Image *gaussBuffer = new lms::imaging::Image();
    gaussBuffer->resize(target->width(),target->height(),lms::imaging::Format::GREY);
    gaussBuffer->fill(255);
    debug->resize(target->width(),target->height(),lms::imaging::Format::BGRA);
    debug->fill(0);
    //try to find one line
    lms::imaging::find::Line line;
    lms::imaging::find::Line::LineParam param;
    param.target = target;
    param.approxEdge = false;
    param.gaussBuffer = gaussBuffer;
    param.lineWidthMax = 10;
    param.lineWidthMin = 2;
    param.maxLength = INFINITY;
    param.searchAngle = 0;
    param.x = 240;
    param.y = 180;
    param.sobelThreshold = 500;
    line.find(param,*debugGraphics);

    return true;
}

bool ImageHintWorker::initialize(){
    //just for testing
    target = datamanager()->readChannel<lms::imaging::Image>(this,"GREY_IMAGE");
    debug = datamanager()->writeChannel<lms::imaging::Image>(this,"DEBUG_IMAGE");
    debugGraphics = new lms::imaging::BGRAImageGraphics(*debug);
    return true;
}

bool ImageHintWorker::deinitialize(){
    return false;
}
