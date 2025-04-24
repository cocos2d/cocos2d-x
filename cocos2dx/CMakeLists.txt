
if(OHOS)
	cmake_minimum_required(VERSION 3.4.1)
	project(cocos2dx_static)

	set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

	set(COCOS2DX_HEADER_PUBLIC
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/kazmath/include
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/platform/ohos/napi/modules
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/platform/ohos
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/platform/ohos/napi/common
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/platform/ohos/napi
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/platform/ohos/napi/render
	    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../
	)

	set(COCOS2DX_SRC
	    CCConfiguration.cpp
	    CCScheduler.cpp
	    CCCamera.cpp
	    ccFPSImages.c
	    actions/CCAction.cpp
	    actions/CCActionCamera.cpp
	    actions/CCActionCatmullRom.cpp
	    actions/CCActionEase.cpp
	    actions/CCActionGrid.cpp
	    actions/CCActionGrid3D.cpp
	    actions/CCActionInstant.cpp
	    actions/CCActionInterval.cpp
	    actions/CCActionManager.cpp
	    actions/CCActionPageTurn3D.cpp
	    actions/CCActionProgressTimer.cpp
	    actions/CCActionTiledGrid.cpp
	    actions/CCActionTween.cpp
	    base_nodes/CCAtlasNode.cpp
	    base_nodes/CCNode.cpp
	    cocoa/CCAffineTransform.cpp
	    cocoa/CCGeometry.cpp
	    cocoa/CCAutoreleasePool.cpp
	    cocoa/CCDictionary.cpp
	    cocoa/CCNS.cpp
	    cocoa/CCObject.cpp
	    cocoa/CCSet.cpp
	    cocoa/CCString.cpp
	    cocoa/CCZone.cpp
	    cocoa/CCArray.cpp
	    cocoa/CCDataVisitor.cpp
	    cocos2d.cpp
	    CCDirector.cpp
	    draw_nodes/CCDrawingPrimitives.cpp
	    draw_nodes/CCDrawNode.cpp
	    effects/CCGrabber.cpp
	    effects/CCGrid.cpp
	    kazmath/src/aabb.c
	    kazmath/src/mat3.c
	    kazmath/src/mat4.c
	    kazmath/src/neon_matrix_impl.c
	    kazmath/src/plane.c
	    kazmath/src/quaternion.c
	    kazmath/src/ray2.c
	    kazmath/src/utility.c
	    kazmath/src/vec2.c
	    kazmath/src/vec3.c
	    kazmath/src/vec4.c
	    kazmath/src/GL/mat4stack.c
	    kazmath/src/GL/matrix.c
	    keypad_dispatcher/CCKeypadDelegate.cpp
	    keypad_dispatcher/CCKeypadDispatcher.cpp
	    label_nodes/CCLabelAtlas.cpp
	    label_nodes/CCLabelBMFont.cpp
	    label_nodes/CCLabelTTF.cpp
	    layers_scenes_transitions_nodes/CCLayer.cpp
	    layers_scenes_transitions_nodes/CCScene.cpp
	    layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp
	    layers_scenes_transitions_nodes/CCTransition.cpp
	    layers_scenes_transitions_nodes/CCTransitionProgress.cpp
	    menu_nodes/CCMenu.cpp
	    menu_nodes/CCMenuItem.cpp
	    misc_nodes/CCClippingNode.cpp
	    misc_nodes/CCMotionStreak.cpp
	    misc_nodes/CCProgressTimer.cpp
	    misc_nodes/CCRenderTexture.cpp
	    particle_nodes/CCParticleExamples.cpp
	    particle_nodes/CCParticleSystem.cpp
	    particle_nodes/CCParticleBatchNode.cpp
	    particle_nodes/CCParticleSystemQuad.cpp
	    platform/CCImageCommonWebp.cpp
	    platform/CCSAXParser.cpp
	    platform/CCThread.cpp
	    platform/CCFileUtils.cpp
	    platform/platform.cpp
	    platform/CCEGLViewProtocol.cpp
	    platform/ohos/CCDevice.cpp
	    platform/ohos/CCEGLView.cpp
	    platform/ohos/CCAccelerometer.cpp
	    platform/ohos/CCApplication.cpp
	    platform/ohos/CCCommon.cpp
	    platform/ohos/CCData.cpp
	    platform/ohos/CCFileUtilsOhos.cpp
	    platform/ohos/CCTextBitmap.cpp
        
	    platform/CCImageCommon_cpp.h
	    platform/CCImage.h
	    platform/ohos/CCImage.cpp
	    platform/ohos/CCLogOhos.h
	    platform/ohos/CCData.h
	    platform/ohos/CCApplication.cpp
	    platform/ohos/CCTextBitmap.cpp
	    platform/ohos/napi/modules/RawFileUtils.cpp
	    platform/ohos/napi/modules/TouchesNapi.cpp
	    platform/ohos/napi/modules/InputNapi.cpp
	    platform/ohos/napi/modules/WebViewNapi.cpp
	    platform/ohos/napi/modules/SensorNapi.cpp
	    platform/ohos/napi/modules/VideoPlayerNapi.cpp
	    platform/ohos/napi/helper/NapiValueConverter.cpp
	    platform/ohos/napi/helper/Js_Cocos2dxHelper.cpp
	    platform/ohos/napi/helper/NapiHelper.cpp
	    platform/ohos/napi/render/egl_core.cpp
	    platform/ohos/napi/render/plugin_render.cpp
	    platform/ohos/napi/plugin_manager.cpp
	    platform/ohos/napi/WorkerMessageQueue.cpp

	    script_support/CCScriptSupport.cpp
	    shaders/ccShaders.cpp
	    shaders/CCGLProgram.cpp
	    shaders/ccGLStateCache.cpp
	    shaders/CCShaderCache.cpp
	    sprite_nodes/CCAnimation.cpp
	    sprite_nodes/CCAnimationCache.cpp
	    sprite_nodes/CCSprite.cpp
	    sprite_nodes/CCSpriteBatchNode.cpp
	    sprite_nodes/CCSpriteFrame.cpp
	    sprite_nodes/CCSpriteFrameCache.cpp
	    support/ccUTF8.cpp
	    support/CCNotificationCenter.cpp
	    support/CCProfiling.cpp
	    support/CCPointExtension.cpp
	    support/TransformUtils.cpp
	    support/user_default/CCUserDefault.cpp
	    support/base64.cpp
	    support/ccUtils.cpp
	    support/CCVertex.cpp
	    support/data_support/ccCArray.cpp
	    support/image_support/TGAlib.cpp
	    support/tinyxml2/tinyxml2.cpp
	    support/zip_support/ZipUtils.cpp
	    support/zip_support/ioapi.cpp
	    support/zip_support/unzip.cpp
	    support/component/CCComponent.cpp
	    support/component/CCComponentContainer.cpp
	    text_input_node/CCIMEDispatcher.cpp
	    text_input_node/CCTextFieldTTF.cpp
	    textures/CCTexture2D.cpp
	    textures/CCTextureAtlas.cpp
	    textures/CCTextureCache.cpp
	    textures/CCTextureETC.cpp
	    textures/CCTexturePVR.cpp
	    tilemap_parallax_nodes/CCParallaxNode.cpp
	    tilemap_parallax_nodes/CCTMXLayer.cpp
	    tilemap_parallax_nodes/CCTMXObjectGroup.cpp
	    tilemap_parallax_nodes/CCTMXTiledMap.cpp
	    tilemap_parallax_nodes/CCTMXXMLParser.cpp
	    tilemap_parallax_nodes/CCTileMapAtlas.cpp
	    touch_dispatcher/CCTouchDispatcher.cpp
	    touch_dispatcher/CCTouchHandler.cpp
	    touch_dispatcher/CCTouch.cpp
	)

	include_directories(${COCOS2DX_HEADER}
	    ../external/png/include/ohos
	    ../external/jpeg/include/ohos
	    ../external/zlib/include
	    ../external/libxml2
	    ../external/libwebp-0.4.2/src/webp
	)


	add_compile_options(-DUSE_FILE32API
	    -Wno-absolute-value
	    -Wno-extra
	    -Wno-implicit-int-float-conversion
	    -Wno-overloaded-virtual
	    -Wno-unused-function
	    -Wno-unused-private-field
	    -Wno-reorder-ctor
	    -Wno-unsequenced
	    -Wno-extra
	    -Wno-c++11-narrowing
	    -DHARMONYOS_NEXT
	    )

	add_library(${PROJECT_NAME} STATIC ${COCOS2DX_SRC})

	add_subdirectory(../external/png ext_png)
	add_subdirectory(../external/jpeg ext_jpeg)
	add_subdirectory(../external/zlib ext_zlib)

	target_link_libraries(${PROJECT_NAME} PUBLIC ext_png ext_zlib libtiff ext_jpeg)
	target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_HEADER_PUBLIC})
	target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_FILE32API -DHARMONYOS_NEXT)
	target_compile_options(${PROJECT_NAME} PUBLIC -Wno-psabi)

	find_library( # Sets the name of the path variable.
	              EGL-lib
	              # Specifies the name of the NDK library that
	              # you want CMake to locate.
	              EGL )
	find_library( # Sets the name of the path variable.
	              GLES-lib
	              # Specifies the name of the NDK library that
	              # you want CMake to locate.
	              GLESv3 )
	find_library( # Sets the name of the path variable.
	              hilog-lib
	              # Specifies the name of the NDK library that
	              # you want CMake to locate.
	              hilog_ndk.z )
	find_library( # Sets the name of the path variable.
	              libace-lib
	              # Specifies the name of the NDK library that
	              # you want CMake to locate.
	              ace_ndk.z )
	find_library( # Sets the name of the path variable.
	              libnapi-lib
	              # Specifies the name of the NDK library that
	              # you want CMake to locate.
	              ace_napi.z )
	find_library( # Sets the name of the path variable.
	              libuv-lib
	              # Specifies the name of the NDK library that
	              # you want CMake to locate.
	              uv )

	find_library( # Sets the name of the path variable.
	              rawfile-lib
	              # Specifies the name of the NDK library that
	              # you want CMake to locate.
	              rawfile.z )

	target_link_libraries(${PROJECT_NAME} PUBLIC  ${EGL-lib} ${GLES-lib} ${hilog-lib} ${libace-lib} ${libnapi-lib} ${libuv-lib} ${rawfile-lib}  libc++.a)
	if(OHOS)
	    target_link_libraries(${PROJECT_NAME} PUBLIC  libnative_window.so libnative_buffer.so)
	endif()
	target_link_libraries(${PROJECT_NAME} PUBLIC libnative_drawing.so)

	add_subdirectory(../external/tiff_4_0_3 libtiff)
endif()
