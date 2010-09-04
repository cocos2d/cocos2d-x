file(GLOB chipmunk_source_files "*.c" "constraints/*.c")
file(GLOB chipmunk_public_header "${chipmunk_SOURCE_DIR}/include/chipmunk/*.h")
file(GLOB chipmunk_constraint_header "${chipmunk_SOURCE_DIR}/include/chipmunk/constraints/*.h")

include_directories(${chipmunk_SOURCE_DIR}/include/chipmunk)

if(BUILD_SHARED)
  add_library(chipmunk SHARED
    ${chipmunk_source_files}
  )
  # set the lib's version number
  set_target_properties(chipmunk PROPERTIES VERSION 5.1)
  install(TARGETS chipmunk RUNTIME DESTINATION lib LIBRARY DESTINATION lib)
endif(BUILD_SHARED)

if(BUILD_STATIC)
  add_library(chipmunk_static STATIC
    ${chipmunk_source_files}
  )
  # Sets chipmunk_static to output "libchipmunk.a" not "libchipmunk_static.a"
  set_target_properties(chipmunk_static PROPERTIES OUTPUT_NAME chipmunk)
  if(INSTALL_STATIC)
    install(TARGETS chipmunk_static ARCHIVE DESTINATION lib)
  endif(INSTALL_STATIC)
endif(BUILD_STATIC)

if(BUILD_SHARED OR INSTALL_STATIC)
  # FIXME: change to PUBLIC_HEADER to allow building frameworks
  install(FILES ${chipmunk_public_header} DESTINATION include/chipmunk)
  install(FILES ${chipmunk_constraint_header} DESTINATION include/chipmunk/constraints)
endif(BUILD_SHARED OR INSTALL_STATIC)
