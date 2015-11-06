#ifndef IMAGE_HINT_WORKER
#define IMAGE_HINT_WORKER

#include <lms/module.h>
#include <lms/imaging/image.h>
#include <lms/imaging/graphics.h>
#include "lms/imaging_detection/image_hint.h"
class ImageHintWorker:public lms::Module{
    const lms::imaging::Image *target;
    lms::WriteDataChannel<lms::imaging::Image> debug;
    lms::imaging::BGRAImageGraphics *debugGraphics;
    lms::ReadDataChannel<lms::imaging::detection::HintContainer> hintContainer;
public:
    bool initialize();
    bool deinitialize();
    bool cycle();
};

#endif /* IMAGE_HINT_WORKER */
