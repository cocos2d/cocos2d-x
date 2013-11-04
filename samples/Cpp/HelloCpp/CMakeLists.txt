set(APP_NAME hellocpp)

set(SAMPLE_SRC
  proj.linux/main.cpp
  Classes/AppDelegate.cpp
  Classes/HelloWorldScene.cpp
)

# add the executable
add_executable(${APP_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${APP_NAME} audio cocos2d)

set(APP_BIN_DIR "${CMAKE_SOURCE_DIR}/bin/${APP_NAME}")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

COPY_RES( ${APP_NAME} )

