set(COCOS_MATH_SRC
  MathUtil.cpp
  Matrix.cpp
  Quaternion.cpp
  Vector2.cpp
  Vector3.cpp
  Vector4.cpp
)

add_library(cocosmath STATIC
  ${COCOS_MATH_SRC}
)


set_target_properties(cocosmath
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

