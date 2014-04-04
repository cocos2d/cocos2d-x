
SET(KAZMATH_SOURCES
  mat4.c
  mat3.c
  plane.c
  vec4.c
  quaternion.c
  vec2.c
  vec3.c
  utility.c
  aabb.c
  ray2.c
  ray3.c
  GL/mat4stack.c
  GL/matrix.c
  )

ADD_SUBDIRECTORY(kazmath)

set_target_properties(kazmath
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
