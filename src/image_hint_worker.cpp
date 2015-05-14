#include <image_hint_worker/image_hint_worker.h>
#include <lms/datamanager.h>
#include <lms/imaging/find/line.h>
#include <lms/imaging/draw_debug.h>
#include <lms/imaging/image_factory.h>
#include <lms/imaging/find/image_hint.h>
bool ImageHintWorker::cycle(){
    debug->fill(0);
    for(lms::imaging::find::ImageHintBase *base: hintContainer->hints){
        debug->resize(base->getTarget()->width(),base->getTarget()->height(),lms::imaging::Format::BGRA);
        base->find(*debugGraphics);
    }

    return true;
}

bool ImageHintWorker::initialize(){
    //just for testing
    debug = datamanager()->writeChannel<lms::imaging::Image>(this,"DEBUG_IMAGE");
    hintContainer = datamanager()->writeChannel<lms::imaging::find::HintContainer>(this,"HINTS");
    debugGraphics = new lms::imaging::BGRAImageGraphics(*debug);
    return true;
}

bool ImageHintWorker::deinitialize(){
    return false;
}
