set(COCOS_UI_SRC
  CocosGUI.cpp
  UIButton.cpp
  UICheckBox.cpp
  UIHBox.cpp
  UIHelper.cpp
  UIImageView.cpp
  UILayout.cpp
  UILayoutParameter.cpp
  UILayoutManager.cpp
  UIListView.cpp
  UILoadingBar.cpp
  UIPageView.cpp
  UIRelativeBox.cpp
  UIRichText.cpp
  UIScrollView.cpp
  UISlider.cpp
  UITextAtlas.cpp
  UITextBMFont.cpp
  UIText.cpp
  UITextField.cpp
  UIVBox.cpp
  UIWidget.cpp
  UIDeprecated.cpp
  UIScale9Sprite.cpp
)

include_directories(
  ui
  ../../base
)


add_library(ui STATIC
  ${COCOS_UI_SRC}
)

target_link_libraries(ui
  cocos2d
)

set_target_properties(ui
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
