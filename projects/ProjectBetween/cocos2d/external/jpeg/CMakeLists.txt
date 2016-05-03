set(SOURCE CCModuleJPEG.cpp)

add_library(cocosjpeg STATIC ${SOURCE})

target_link_libraries(cocosjpeg jpeg cocos2d)

set_target_properties(cocosjpeg
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

