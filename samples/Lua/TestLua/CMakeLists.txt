set(SAMPLE_NAME testlua)

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
  audio
  cocos2d
)

set(SAMPLE_BIN_DIR "${CMAKE_SOURCE_DIR}/bin/${SAMPLE_NAME}")

set_target_properties(${SAMPLE_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${SAMPLE_BIN_DIR}")

COPY_RES(${SAMPLE_NAME} "Resources/*" "${SAMPLE_BIN_DIR}")
COPY_RES_EXTRA(${SAMPLE_NAME} "${CMAKE_SOURCE_DIR}/samples/TestCpp/Resources/*")
# "${SAMPLE_BIN_DIR}")

