set(TOLUA_SRC
  tolua_event.c
  tolua_is.c
  tolua_map.c
  tolua_push.c
  tolua_to.c
)

include_directories(
  ../lua
)


add_library(tolua STATIC
  ${TOLUA_SRC}
)

set_target_properties(tolua
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
