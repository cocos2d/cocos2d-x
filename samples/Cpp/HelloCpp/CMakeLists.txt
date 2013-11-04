set(SAMPLE_NAME hellocpp)

set(SAMPLE_SRC
  proj.linux/main.cpp
  Classes/AppDelegate.cpp
  Classes/HelloWorldScene.cpp
)

# add the executable
add_executable(${SAMPLE_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${SAMPLE_NAME} audio cocos2d)

set(SAMPLE_BIN_DIR "${CMAKE_SOURCE_DIR}/bin/${SAMPLE_NAME}")

set_target_properties(${SAMPLE_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${SAMPLE_BIN_DIR}")

COPY_RES( ${SAMPLE_NAME} "Resources/*" "${SAMPLE_BIN_DIR}")

