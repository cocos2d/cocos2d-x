set(SOURCE CCModuleTIFF.cpp)

add_library(cocostiff STATIC ${SOURCE})

target_link_libraries(cocostiff tiff cocos2d)

set_target_properties(cocostiff
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

