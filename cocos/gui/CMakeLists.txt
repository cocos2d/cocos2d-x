set(GUI_SRC
  UIRootWidget.cpp
  UIWidget.cpp
  UILayout.cpp
  UILayoutParameter.cpp
  UILayoutDefine.cpp
  CocosGUI.cpp
  UIHelper.cpp
  UIInputManager.cpp
  UILayer.cpp
  UIListView.cpp
  UIPageView.cpp
  UIScrollView.cpp
  UIButton.cpp
  UICheckBox.cpp
  UIImageView.cpp
  UILabel.cpp
  UILabelAtlas.cpp
  UILabelBMFont.cpp
  UILoadingBar.cpp
  UISlider.cpp
  UITextField.cpp
)

add_library(gui STATIC
  ${GUI_SRC}
)

set_target_properties(gui
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)
