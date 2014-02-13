set(APP_NAME testjavascript)

set(SAMPLE_SRC
  proj.linux/main.cpp
  Classes/AppDelegate.cpp
)

include_directories(
  Classes
  ../../cocos/scripting/javascript/bindings
  ../../cocos/scripting/auto-generated/js-bindings
  ../../external/spidermonkey/include/linux/${ARCH_DIR}
)

# add the executable
add_executable(${APP_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${APP_NAME}
  jsbinding
  storage
  gui
  network
  cocostudio
  cocosbuilder
  extensions
  audio
  cocos2d
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/javascript/script ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/tests/test-cpp/Resources ${APP_BIN_DIR}/Resources
  )

