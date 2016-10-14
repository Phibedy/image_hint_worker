set ( SOURCES
	"src/image_hint_worker.cpp"
	"src/interface.cpp"
)

set (HEADERS
	"include/image_hint_worker/image_hint_worker.h"
)

include_directories("include")

add_library (image_hint_worker MODULE ${SOURCES} ${HEADERS})
target_link_libraries(image_hint_worker PRIVATE lmscore imaging lms_imaging_detection)
