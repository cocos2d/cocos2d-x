set(APP_NAME lua-tests)

set(SAMPLE_SRC
    Classes/AppDelegate.cpp
    Classes/lua_assetsmanager_test_sample.cpp
)

if(LINUX)
  set(SAMPLE_SRC
     ${SAMPLE_SRC}
     proj.linux/main.cpp
     )
elseif(MACOSX)
  set(SAMPLE_SRC
     ${SAMPLE_SRC}
     proj.ios_mac/mac/main.cpp
     )
endif()

include_directories(
  Classes
  ../../../cocos/scripting/lua-bindings/manual
  ../../../cocos/scripting/lua-bindings/auto
  ../../../external/lua/lua
  ../../../external/lua/tolua
)

# add the executable
add_executable(${APP_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${APP_NAME}
  luacocos2d
  cocos2d
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}/Resources/res
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}/Resources/src
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/cocos2d ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/cocosdenshion ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/network ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/cocosbuilder ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/cocostudio ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/extension ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/ui ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/tests/cpp-tests/Resources ${APP_BIN_DIR}/Resources/res
  )

