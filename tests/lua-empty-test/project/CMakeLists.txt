set(APP_NAME lua-empty-test)

set(SAMPLE_SRC
  proj.linux/main.cpp
  Classes/AppDelegate.cpp
)

include_directories(
  Classes
  ../../../cocos/scripting/lua-bindings
  ../../../external/lua/lua
  ../../../external/lua/tolua
)

# add the executable
add_executable(${APP_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${APP_NAME}
  luacocos2d
  luacocosdenshion
  luanetwork
  audio
  cocos2d
  network
)

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}/Resources/res
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}/Resources/src
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/AudioEngine.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/bitExtend.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/Cocos2d.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/Cocos2dConstants.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedCocos2dClass.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedCocos2dEnum.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedCocos2dFunc.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedCocosDenshionClass.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedCocosDenshionFunc.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedNetworkClass.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedNetworkEnum.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedNetworkFunc.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DeprecatedOpenglEnum.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/DrawPrimitives.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/extern.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/json.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/NetworkConstants.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/Opengl.lua ${APP_BIN_DIR}/Resources
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/OpenglConstants.lua ${APP_BIN_DIR}/Resources
  )
