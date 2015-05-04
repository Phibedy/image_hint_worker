#include <image_hint_worker/image_hint_worker.h>

extern "C" {
void* getInstance () {
    return new ImageHintWorker();
}
}
