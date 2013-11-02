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
