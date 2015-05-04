set ( SOURCES 
	"src/image_hint_worker.cpp"
	"src/interface.cpp"
)

set (HEADERS
	"include/image_hint_worker/image_hint_worker.h"
)

include_directories("include")

add_library ( image_detection_test MODULE ${SOURCES} ${HEADERS})
target_link_libraries(image_detection_test PRIVATE lms imaging)
