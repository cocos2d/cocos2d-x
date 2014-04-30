set(COCOS_RENDERER_SRC
  CCBatchCommand.cpp
  CCCustomCommand.cpp
  CCGroupCommand.cpp
  CCQuadCommand.cpp
  CCRenderCommand.cpp
  CCRenderer.cpp
)

add_library(cocosrenderer STATIC
  ${COCOS_RENDERER_SRC}
)

set_target_properties(cocosrenderer
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

