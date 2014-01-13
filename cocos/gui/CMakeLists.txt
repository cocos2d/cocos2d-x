set(GUI_SRC
  UIWidget.cpp
  UILayout.cpp
  UILayoutParameter.cpp
  UILayoutDefine.cpp
  CocosGUI.cpp
  UIHelper.cpp
  UIListView.cpp
  UIPageView.cpp
  UIScrollView.cpp
  UIButton.cpp
  UICheckBox.cpp
  UIImageView.cpp
  UIText.cpp
  UITextAtlas.cpp
  UITextBMFont.cpp
  UILoadingBar.cpp
  UISlider.cpp
  UITextField.cpp
)

add_library(gui STATIC
  ${GUI_SRC}
)

set_target_properties(gui
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
