set(APP_NAME hellocpp)

if(WIN32)
set(SAMPLE_SRC
  proj.win32/main.cpp
  Classes/AppDelegate.cpp
  Classes/HelloWorldScene.cpp
)

else()
set(SAMPLE_SRC
  proj.linux/main.cpp
  Classes/AppDelegate.cpp
  Classes/HelloWorldScene.cpp
)

endif()

# add the executable
add_executable(${APP_NAME}
  ${SAMPLE_SRC}
)

if(WIN32)
set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
endif(WIN32)

target_link_libraries(${APP_NAME} audio cocos2d)

set(APP_BIN_DIR "${CMAKE_SOURCE_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
  )

