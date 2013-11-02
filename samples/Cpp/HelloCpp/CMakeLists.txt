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

target_link_libraries(${SAMPLE_NAME} ${COCOS_LIBRARIES})

set(SAMPLE_BIN_DIR ${CMAKE_BINARY_DIR}/bin)

SET_TARGET_PROPERTIES(${SAMPLE_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${SAMPLE_BIN_DIR}/HelloCpp")

message(STATUS "Hello.........." ${CMAKE_BINARY_DIR})

COPY_RES( ${SAMPLE_NAME} "Resources/*" "${SAMPLE_BIN_DIR}/HelloCpp")

