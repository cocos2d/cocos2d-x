cmake_minimum_required(VERSION 3.4.1)

project(cocosdenshion)

file(GLOB_RECURSE COCOSDENSHION_SRC "./*.cpp")

include_directories(./audio_utils/include/audio_utils ../include)

add_library(${PROJECT_NAME} STATIC ${COCOSDENSHION_SRC})

#set(CMAKE_C_FLAGS -Wno-psabi -Wno-absolute-value -Wno-extra)
#set(CMAKE_CXX_FLAGS -Wno-overloaded-virtual -Wno-unused-function -Wno-unused-private-field -Wno-reorder-ctor -Wno-unsequenced -Wno-extra)
target_compile_options(${PROJECT_NAME} PUBLIC -Wno-psabi -Wno-absolute-value -Wno-extra -Wno-overloaded-virtual -Wno-unused-function -Wno-unused-private-field -Wno-reorder-ctor -Wno-unsequenced -Wno-extra -Wno-unused-command-line-argument -Wno-ignored-qualifiers)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
                                           PUBLIC       ${CMAKE_CURRENT_SOURCE_DIR}/../../cocos2dx
                                           PUBLIC       ${CMAKE_CURRENT_SOURCE_DIR}/../../cocos2dx/include
                                           PUBLIC       ${CMAKE_CURRENT_SOURCE_DIR}/../../cocos2dx/kazmath/include
                                           PUBLIC       ${CMAKE_CURRENT_SOURCE_DIR}/../../cocos2dx/platform/ohos
                                                  )
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2dx_static OPENSLES pvmp3dec vorbisidec)
