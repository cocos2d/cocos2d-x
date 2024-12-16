set(APP_NAME lua-tests)

set(SAMPLE_SRC
    Classes/AppDelegate.cpp
    Classes/lua_assetsmanager_test_sample.cpp
    Classes/lua_test_bindings.cpp
)

if(LINUX)
    set(SAMPLE_SRC ${SAMPLE_SRC} proj.linux/main.cpp)
    set(RES_PREFIX "/Resources")
elseif(OHOS)
    list(APPEND SAMPLE_SRC proj.ohos/entry/src/main/cpp/main.cpp)
elseif(WINDOWS)
    list(APPEND SAMPLE_SRC proj.win32/main.cpp)
    set(RES_PREFIX "")
elseif(MACOSX)
    set(SAMPLE_SRC ${SAMPLE_SRC} proj.ios_mac/mac/main.cpp)

    file(GLOB_RECURSE APP_RESOURCES ../res/*)
    cocos_mark_resources(FILES ${APP_RESOURCES} BASEDIR ../res RESOURCEBASE Resources/res)
    file(GLOB_RECURSE APP_SCRIPTS ../src/*)
    cocos_mark_resources(FILES ${APP_SCRIPTS} BASEDIR ../src RESOURCEBASE Resources/src)
    file(GLOB_RECURSE COCOS_SCRIPTS ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/*)
    cocos_mark_resources(FILES ${COCOS_SCRIPTS} BASEDIR ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script RESOURCEBASE Resources/src/cocos)
    file(GLOB_RECURSE TEST_RESOURCES ${CMAKE_SOURCE_DIR}/tests/cpp-tests/Resources/*)
    cocos_mark_resources(FILES ${TEST_RESOURCES} BASEDIR ${CMAKE_SOURCE_DIR}/tests/cpp-tests/Resources RESOURCEBASE Resources/res)

    list(APPEND SAMPLE_SRC ${APP_RESOURCES} ${APP_SCRIPTS} ${COCOS_SCRIPTS} ${TEST_RESOURCES})
endif()

if(OHOS)
include_directories(
  Classes
  ../../../cocos/scripting/lua-bindings/manual
  ../../../cocos/scripting/lua-bindings/auto
  ../../../external/lua/luajit/include
  ../../../external/lua/tolua
)
else()
include_directories(
  Classes
  ../../../cocos/scripting/lua-bindings/manual
  ../../../cocos/scripting/lua-bindings/auto
  ../../../external/lua/lua
  ../../../external/lua/tolua
)
endif()

if(OHOS)
    set(res_raw_folders "${CMAKE_CURRENT_LIST_DIR}/proj.ohos/entry/src/main/resources/rawfile")
    file(GLOB resFiles "${CMAKE_CURRENT_LIST_DIR}/../res/*")
    file(COPY ${resFiles} DESTINATION  ${res_raw_folders})
    file(GLOB srcFiles "${CMAKE_CURRENT_LIST_DIR}/../src/*")
    file(COPY ${srcFiles} DESTINATION  ${res_raw_folders})
    file(GLOB cppTestresFiles "${COCOS2DX_ROOT_PATH}/tests/cpp-tests/Resources/*")
    file(COPY ${cppTestresFiles} DESTINATION  ${res_raw_folders})

    if(NOT EXISTS  ${res_raw_folders}/cocos)
        file(GLOB cocosFiles "${COCOS2DX_ROOT_PATH}/cocos/scripting/lua-bindings/script/*")
        file(COPY ${cocosFiles} DESTINATION  ${res_raw_folders}/cocos)
    endif()

    include_directories(${COCOS2DX_ROOT_PATH}/external/opengles/api ${COCOS2DX_ROOT_PATH}/cocos ${COCOS2DX_ROOT_PATH} ${COCOS2DX_ROOT_PATH}/external)
    add_library(${APP_NAME} SHARED ${SAMPLE_SRC})

    find_library( # Sets the name of the path variable.
                  hilog-lib
                  # Specifies the name of the NDK library that
                  # you want CMake to locate.
                  hilog_ndk.z )
    target_link_libraries(${APP_NAME} PRIVATE ${hilog-lib})
else()
    # add the executable
    add_executable(${APP_NAME} ${SAMPLE_SRC})
endif()

target_link_libraries(${APP_NAME} luacocos2d cocos2d)

if(MACOSX OR APPLE)
  set_target_properties(${APP_NAME} PROPERTIES
      MACOSX_BUNDLE 1
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )

elseif(!OHOS)

    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}")

    set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")

    pre_build(${APP_NAME}
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../res ${APP_BIN_DIR}${RES_PREFIX}/res
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../src ${APP_BIN_DIR}${RES_PREFIX}/src
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cocos/scripting/lua-bindings/script/ ${APP_BIN_DIR}/Resources/src/cocos
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/tests/cpp-tests/Resources ${APP_BIN_DIR}${RES_PREFIX}/res
      )

endif()

