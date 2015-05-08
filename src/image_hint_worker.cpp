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
    lms::imaging::find::Pixel pixel(240,180);
    pixel.setImage(const_cast<lms::imaging::Image*>(target));
    line.find(pixel,100,0,2,10,500,*gaussBuffer,*debugGraphics);

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
