#include <image_hint_worker/image_hint_worker.h>
#include <lms/datamanager.h>
#include <lms/imaging_detection/line.h>
#include <lms/imaging/draw_debug.h>
#include <lms/imaging/image_factory.h>
#include <lms/imaging_detection/image_hint.h>
#include "lms/imaging/draw_debug.h"
bool ImageHintWorker::cycle(){
#if IMAGING_DRAW_DEBUG == 1
        //clear the debug image
        debug->fill(0);
#endif
    for(lms::imaging::find::ImageHintBase *base: hintContainer->hints){
        if(base->getTarget() == nullptr){
            logger.error("target is null!!!");
            return true;
        }
#if IMAGING_DRAW_DEBUG == 1
        //TODO: shitty code, but as it's just for debugging it's ok
        debug->resize(base->getTarget()->width(),base->getTarget()->height(),lms::imaging::Format::BGRA);
        base->find(*debugGraphics);
#else
        base->find();
#endif
    }

    return true;
}

bool ImageHintWorker::initialize(){
    hintContainer = datamanager()->writeChannel<lms::imaging::find::HintContainer>(this,"HINTS");

#ifdef DRAWDEBUG
    debug = datamanager()->writeChannel<lms::imaging::Image>(this,"DEBUG_IMAGE");
    debugGraphics = new lms::imaging::BGRAImageGraphics(*debug);
#endif
    return true;
}

bool ImageHintWorker::deinitialize(){
    return false;
}
