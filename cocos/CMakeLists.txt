if(WINDOWS)
  ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
endif()

set(COCOS_SRC cocos2d.cpp)

include(2d/CMakeLists.txt)
include(3d/CMakeLists.txt)
include(platform/CMakeLists.txt)
include(physics/CMakeLists.txt)
include(math/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(base/CMakeLists.txt)
include(deprecated/CMakeLists.txt)

add_library(cocos2d STATIC
  ${COCOS_SRC}
  ${COCOS_2D_SRC}
  ${COCOS_3D_SRC}
  ${COCOS_PLATFORM_SRC}
  ${COCOS_BASE_SRC}
  ${COCOS_RENDERER_SRC}
  ${COCOS_MATH_SRC}
  ${COCOS_PHYSICS_SRC}
  ${COCOS_DEPRECATED_SRC}
)

if(MINGW)
  set(COCOS_LINK z jpeg png webp tiff glfw3 glew32 opengl32 iconv freetype bz2)
elseif(WINDOWS)
  set(COCOS_LINK libjpeg libpng libwebp libtiff freetype250 glfw3 glew32 opengl32 libiconv libzlib)
elseif(LINUX)
  set(COCOS_LINK jpeg webp tiff freetype fontconfig png pthread glfw GLEW GL X11 rt z)
endif()

target_link_libraries(cocos2d
  chipmunk_static
  tinyxml2
  unzip
  xxhash
  ${COCOS_LINK}
)

set_target_properties(cocos2d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
