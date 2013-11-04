set(APP_NAME hellolua)

set(SAMPLE_SRC
  proj.linux/main.cpp
  Classes/AppDelegate.cpp
)

include_directories(
  Classes
  ../../../cocos/scripting/lua/bindings
  ../../../external/lua/lua
  ../../../external/lua/tolua
)

# add the executable
add_executable(${APP_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${APP_NAME}
  luabinding
  gui
  network
  cocostudio
  cocosbuilder
  extensions
  audio
  cocos2d
)

set(APP_BIN_DIR "${CMAKE_SOURCE_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

COPY_RES( ${APP_NAME} )

COPY_RES_EXTRA(${APP_NAME} copy_core_scripts ${CMAKE_SOURCE_DIR}/cocos/scripting/lua
  script/*
  )
