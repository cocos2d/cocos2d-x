set(APP_NAME cpp-empty-test)

if(ANDROID)
  set(PLATFORM_SRC proj.android/jni/hellocpp/main.cpp)
  set(RES_PREFIX "/Resources")
elseif(WINDOWS)
  set(PLATFORM_SRC proj.win32/main.cpp)
  set(RES_PREFIX "")
elseif(IOS)
  set(PLATFORM_SRC
    proj.ios/main.m
    proj.ios/AppController.mm
    proj.ios/RootViewController.mm
  )

elseif(MACOSX OR APPLE)
  set(PLATFORM_SRC proj.mac/main.cpp)

  file(GLOB_RECURSE RES_FILES Resources/*)
  cocos_mark_resources(FILES ${RES_FILES} BASEDIR Resources)
  list(APPEND PLATFORM_SRC ${RES_FILES})

elseif(LINUX)
  set(PLATFORM_SRC proj.linux/main.cpp)
  set(RES_PREFIX "/Resources")
else()
  message( FATAL_ERROR "Unsupported platform, CMake will exit" )

endif()

set(SAMPLE_SRC
  ${PLATFORM_SRC}
  Classes/AppDelegate.cpp
  Classes/HelloWorldScene.cpp
)

# add the executable
add_executable(${APP_NAME}
  ${SAMPLE_SRC}
)

target_link_libraries(${APP_NAME} cocos2d)

if(MSVC)

  #get our resources
  add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_directory
                         ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR})
  #get our dlls
  add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy
                     ${CMAKE_CURRENT_SOURCE_DIR}/../../external/win32-specific/gles/prebuilt/glew32.dll 
					 ${CMAKE_CURRENT_BINARY_DIR})

  add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy
                     ${CMAKE_CURRENT_SOURCE_DIR}/../../external/win32-specific/zlib/prebuilt/zlib1.dll 
					 ${CMAKE_CURRENT_BINARY_DIR}/Debug)

  #Visual Studio Defaults to wrong type
  set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
  set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")

elseif(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )

else()

  set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

  set_target_properties(${APP_NAME} PROPERTIES
       RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")
  add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${APP_NAME}>${RES_PREFIX}
    )

endif()

