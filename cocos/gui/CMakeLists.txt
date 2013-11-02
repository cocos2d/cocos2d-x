set(GUI_SRC
  UIRootWidget.cpp
  UIWidget.cpp
  Layout.cpp
  LayoutParameter.cpp
  UILayoutDefine.cpp
  CocosGUI.cpp
  UIHelper.cpp
  UIInputManager.cpp
  UILayer.cpp
  UIDragPanel.cpp
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

