
cocos_target_sources(${COCOS2D_TARGET} GROUP "base" FILES
    ${CMAKE_CURRENT_LIST_FILE}
    "base/allocator/CCAllocatorDiagnostics.cpp"
    "base/allocator/CCAllocatorGlobal.cpp"
    "base/allocator/CCAllocatorGlobalNewDelete.cpp"
    "base/ccFPSImages.c"
    "base/CCAsyncTaskPool.cpp"
    "base/CCAutoreleasePool.cpp"
    "base/CCConfiguration.cpp"
    "base/CCConsole.cpp"
    "base/CCController.cpp"
    "base/CCData.cpp"
    "base/CCDataVisitor.cpp"
    "base/CCDirector.cpp"
    "base/CCEvent.cpp"
    "base/CCEventAcceleration.cpp"
    "base/CCEventController.cpp"
    "base/CCEventCustom.cpp"
    "base/CCEventDispatcher.cpp"
    "base/CCEventFocus.cpp"
    "base/CCEventKeyboard.cpp"
    "base/CCEventListener.cpp"
    "base/CCEventListenerAcceleration.cpp"
    "base/CCEventListenerController.cpp"
    "base/CCEventListenerCustom.cpp"
    "base/CCEventListenerFocus.cpp"
    "base/CCEventListenerKeyboard.cpp"
    "base/CCEventListenerMouse.cpp"
    "base/CCEventListenerTouch.cpp"
    "base/CCEventMouse.cpp"
    "base/CCEventTouch.cpp"
    "base/CCIMEDispatcher.cpp"
    "base/CCNS.cpp"
    "base/CCProfiling.cpp"
    "base/CCRef.cpp"
    "base/CCScheduler.cpp"
    "base/CCScriptSupport.cpp"
    "base/CCTouch.cpp"
    "base/CCUserDefault.cpp"
    "base/CCValue.cpp"
    "base/ObjectFactory.cpp"
    "base/TGAlib.cpp"
    "base/ZipUtils.cpp"
    "base/atitc.cpp"
    "base/base64.cpp"
    "base/ccCArray.cpp"
    "base/ccRandom.cpp"
    "base/ccTypes.cpp"
    "base/ccUTF8.cpp"
    "base/ccUtils.cpp"
    "base/etc1.cpp"
    "base/pvr.cpp"
    "base/s3tc.cpp"
)

if(APPLE) # Darwin and iOS
    list(APPEND base_src "base/CCUserDefault-apple.mm")
endif()

if(COCOS_TARGET_SYSTEM_IOS)
    list(APPEND base_src "base/CCController-iOS.mm")
    # CCController-iOS.mm include CCLabel.h,
    #   need modify sometime.
    target_include_directories(${COCOS2D_TARGET} PRIVATE "2d")
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    list(APPEND base_src
        "base/CCController-android.cpp"
        "base/CCUserDefault-android.cpp"
        )
endif()

if(base_src)
    cocos_target_sources(${COCOS2D_TARGET} GROUP "base" FILES ${base_src})
endif()

