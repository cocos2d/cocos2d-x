# 基于Cocos引擎的游戏移植方案
## Cocos2d-x引擎移植OpenHarmony总体框架图
![Cocos2d-x引擎移植OpenHarmony总体框架图](Cocos2d-x%E5%BC%95%E6%93%8E%E7%A7%BB%E6%A4%8DOpenHarmony%E6%80%BB%E4%BD%93%E6%A1%86%E6%9E%B6%E5%9B%BE.png)
针对cocos2d-x引擎移植新增内容，以cocos2d-x 3.17.2 cpp-empty-test工程的鸿蒙化为例，需要在cocos2dx/tests/cpp-empty-test路径下，用DevEco Studio基于Stage模型新建OpenHarmony Native C++工程proj.ohos，并基于该工程，在C++侧完成cocos2d-x引擎主体、三方库、OpenHarmony NDK接口以及游戏逻辑的适配，在ets侧完成应用前端的适配。工程结构如下：
```
entry/src/main
          ├── cpp                             // C++代码区，cpp-empty-test对接cocos2d-x引擎实现部分								
          │   ├── CmakeList.txt               // Cmake打包配置文件
          │   ├── main.cpp                    // C++源代码
          │   └── napi_init.cpp               // napi注册模块
          └── ets                             // ets代码区，前端界面实现部分
              ├── common
              │   └── Constants.ts            // 上下文类型
              ├── MainAbility
              │   └── MainAbility.ts          // Ability生命周期管理
              ├── pages
              │   └── index.ets               // 页面生命周期管理
              └── workers
                  ├── CocosWorker.ts          // Worker线程，通过napi使用C++侧渲染功能
                  └── WorkerManager.ets       // Worker线程管理
 ```

## C++侧适配
首先在main.cpp中实现初始化函数Cocos2dxRenderer_nativeInit，然后参考Android工程的proj.android/app/jni/Android.mk文件，编写CMakeLists.txt将C++源代码编译成动态链接库文件，添加cpp-empty-test对cocos2d-x引擎主体、三方库、OpenHarmony系统接口等依赖。
```
// 指定当前工程所需的cmake最小版本
cmake_minimum_required(VERSION 3.4.1)
// 设置工程名
project(nativerender)

// 设置相对路径
set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../..)
set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

// 通过宏定义选择OpenHarmony平台
set(platform_name "ohos")

// 调用OpenHarmony提供的NDK库
find_library(EGL-lib EGL)
find_library(GLES-lib GLESv3)
find_library(hilog-lib hilog_ndk.z)
find_library(libace-lib ace_ndk.z)
find_library(libnapi-lib ace_napi.z)
find_library(libuv-lib uv)
find_library(rawfile-lib rawfile.z)

// 设置rawfile资源路径
if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../tests/cpp-empty-tests/Resources/*")
    file(COPY ${ALL_RESOURCES_FILES}
        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()

// 设置三方库头文件路径
include_directories(${COCOS2DX_ROOT_PATH}/external/opengles/api)

// 为当前工程添加C++源文件
add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp
                                    ${CLASSES_PATH}/AppDelegate.cpp
                                    ${CLASSES_PATH}/HelloWorldScene.cpp)

// 为当前工程添加需要的头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH})
target_include_directories(${PROJECT_NAME}  ${COCOS2DX_ROOT_PATH}
                                            ${COCOS2DX_ROOT_PATH}/cocos
                                            ${COCOS2DX_ROOT_PATH}/cocos/editor-support
                                            ${COCOS2DX_ROOT_PATH}/extensions
                                            ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/common
                                            ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/modules
                                            ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi
                                            ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos)
target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_ROOT_PATH}/external/chipmunk/include)

// 添加中间二进制的路径，该路径下必须包含CMakeLists.txt文件
add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/cpp-empty-test cpp_empty_test)

// 将当前工程关联库文件
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d cpp_empty_test ${libnapi-lib} ${GLES-lib})
```

## ets侧适配
- MainAbility.ts
    负责应用的生命周期管理。
- index.ets
    负责页面的生命周期管理以及Worker线程通信，创建Worker线程对象，增加XComponent组件，调用onLoad()方法执行上下文环境，通过postMessage接口向Worker线程发送消息。
- CocosWorker.ts
    Worker线程在接收到宿主线程发送的消息后调用事件处理程序。