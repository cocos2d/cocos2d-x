#include "GUIEditorTest.h"

#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "CocoStudioGUITest.h"

#include "UIButtonTest/UIButtonTest_Editor.h"
#include "UICheckBoxTest/UICheckBoxTest_Editor.h"
#include "UIImageViewTest/UIImageViewTest_Editor.h"
#include "UITextAtlasTest/UITextAtlasTest_Editor.h"
#include "UITextBMFontTest/UITextBMFontTest_Editor.h"
#include "UITextTest/UITextTest_Editor.h"
#include "UILoadingBarTest/UILoadingBarTest_Editor.h"
#include "UISliderTest/UISliderTest_Editor.h"
#include "UITextFieldTest/UITextFieldTest_Editor.h"
#include "UIWidgetAddNodeTest/UIWidgetAddNodeTest_Editor.h"
#include "UILayoutTest/UILayoutTest_Editor.h"
#include "UIListViewTest/UIListViewTest_Editor.h"
#include "UIPageViewTest/UIPageViewTest_Editor.h"
#include "UIScrollViewTest/UIScrollViewTest_Editor.h"

GUIEditorTests::GUIEditorTests()
{
    addTest("GUI Button Editor Test", [](){ return new (std::nothrow) UIButtonEditorTests; });
    addTest("GUI CheckBox Editor Test", [](){ return new (std::nothrow) UICheckBoxEditorTests; });
    addTest("GUI Slider Editor Test", [](){ return new (std::nothrow) UISliderEditorTests; });
    addTest("GUI ImageView Editor Test", [](){ return new (std::nothrow) UIImageViewEditorTests; });
    addTest("GUI LoadingBar Editor Test", [](){ return new (std::nothrow) UILoadingBarEditorTests; });
    addTest("GUI Text Editor Test", [](){ return new (std::nothrow) UITextEditorTests; });
    addTest("GUI TextBMFont Editor Test", [](){ return new (std::nothrow) UITextBMFontEditorTest; });
    addTest("GUI TextField Editor Test", [](){ return new (std::nothrow) UITextFieldEditorTests; });
    addTest("GUI Layout Editor Test", [](){ return new (std::nothrow) UILayoutEditorTests; });
    addTest("GUI ScrollView Editor Test", [](){ return new (std::nothrow) UIScrollViewEditorTests; });
    addTest("GUI PageView Editor Test", [](){ return new (std::nothrow) UIPageViewEditorTests; });
    addTest("GUI ListView Editor Test", [](){ return new (std::nothrow) UIListViewEditorTests; });
    addTest("GUI WidgetAddNode Editor Test", [](){ return new (std::nothrow) UIWidgetAddNodeEditorTests; });
};
