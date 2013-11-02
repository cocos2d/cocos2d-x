
SET(KAZMATH_SOURCES
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/mat4.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/mat3.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/plane.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/vec4.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/quaternion.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/vec2.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/vec3.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/utility.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/aabb.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/ray2.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/GL/mat4stack.c
  ${CMAKE_SOURCE_DIR}/cocos/math/kazmath/src/GL/matrix.c
  )

ADD_SUBDIRECTORY(src)