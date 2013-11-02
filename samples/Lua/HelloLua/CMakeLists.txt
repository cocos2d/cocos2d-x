set(SAMPLE_NAME hellolua)

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
add_executable(${SAMPLE_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${SAMPLE_NAME}
  luabinding
  gui
  network
  cocostudio
  cocosbuilder
  extensions
  ${COCOS_LIBRARIES}
  jsoncpp
  curl
  tolua
  lua
  rt
)

set(SAMPLE_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${SAMPLE_NAME}")

SET_TARGET_PROPERTIES(${SAMPLE_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${SAMPLE_BIN_DIR}")

COPY_RES( ${SAMPLE_NAME} "Resources/*" "${SAMPLE_BIN_DIR}")

