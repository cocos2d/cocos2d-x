
set(ui_src
    ${CMAKE_CURRENT_LIST_FILE}
    "ui/CocosGUI.cpp"
    "ui/UIButton.cpp"
    "ui/UICheckBox.cpp"
    "ui/UIDeprecated.cpp"
    "ui/UIHBox.cpp"
    "ui/UIHelper.cpp"
    "ui/UIImageView.cpp"
    "ui/UILayout.cpp"
    "ui/UILayoutManager.cpp"
    "ui/UILayoutParameter.cpp"
    "ui/UIListView.cpp"
    "ui/UILoadingBar.cpp"
    "ui/UIPageView.cpp"
    "ui/UIRelativeBox.cpp"
    "ui/UIRichText.cpp"
    "ui/UIScale9Sprite.cpp"
    "ui/UIScrollView.cpp"
    "ui/UISlider.cpp"
    "ui/UIText.cpp"
    "ui/UITextAtlas.cpp"
    "ui/UITextBMFont.cpp"
    "ui/UITextField.cpp"
    "ui/UIVBox.cpp"
    "ui/UIWebView.cpp"
    "ui/UIWidget.cpp"
    "ui/UIEditBox/UIEditBox.cpp"
    "ui/UILayoutComponent.cpp"
    "ui/shaders/UIShaders.cpp"
)

if(COCOS_TARGET_SYSTEM_MACOSX)
    list(APPEND ui_src
        "ui/UIEditBox/UIEditBoxImpl-mac.mm"
        )
elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    list(APPEND ui_src
        "ui/UIEditBox/UIEditBoxImpl-win32.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_LINUX)
    list(APPEND ui_src
        "ui/UIWebView.cpp"
        "ui/UIEditBox/UIEditBoxImpl-stub.cpp"
        )
elseif(COCOS_TARGET_SYSTEM_IOS)
    list(APPEND ui_src
        "ui/UIWebView.mm"
        "ui/UIWebViewImpl-ios.mm"
        "ui/UIVideoPlayer-ios.mm"
        "ui/UIEditBox/UIEditBox.cpp"
        "ui/UIEditBox/UIEditBoxImpl-ios.mm"
        "ui/UIEditBox/UIEditBoxImpl-stub.cpp"
        )
    # "ui/UIWebView.cpp" can't pass the ios compile.
    list(REMOVE_ITEM ui_src "ui/UIWebView.cpp")
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    list(APPEND ui_src
        "ui/UIEditBox/UIEditBoxImpl-android.cpp"
        "ui/UIVideoPlayer-android.cpp"
        "ui/UIWebView.cpp"
        "ui/UIWebViewImpl-android.cpp"
        )
else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} build for unsupported OS.")
endif()

cocos_target_sources(${COCOS2D_TARGET} GROUP "ui" FILES ${ui_src})

if(COCOS_TARGET_SYSTEM_WINDOWS AND BUILD_SHARED_LIBS)
    target_compile_definitions(${COCOS2D_TARGET} PRIVATE _USEGUIDLL)
endif()

