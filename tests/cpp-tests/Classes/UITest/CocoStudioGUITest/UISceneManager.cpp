

#include "UISceneManager.h"
#include "UIScene.h"
#include "UIButtonTest/UIButtonTest.h"
#include "UICheckBoxTest/UICheckBoxTest.h"
#include "UISliderTest/UISliderTest.h"
#include "UIImageViewTest/UIImageViewTest.h"
#include "UILoadingBarTest/UILoadingBarTest.h"
#include "UITextAtlasTest/UITextAtlasTest.h"
#include "UITextTest/UITextTest.h"
#include "UITextBMFontTest/UITextBMFontTest.h"
#include "UITextFieldTest/UITextFieldTest.h"
#include "UILayoutTest/UILayoutTest.h"
#include "UIScrollViewTest/UIScrollViewTest.h"
#include "UIPageViewTest/UIPageViewTest.h"
#include "UIListViewTest/UIListViewTest.h"
#include "UIWidgetAddNodeTest/UIWidgetAddNodeTest.h"
#include "UIRichTextTest/UIRichTextTest.h"
#include "UIFocusTest/UIFocusTest.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "UIVideoPlayerTest/UIVideoPlayerTest.h"
#endif
/*
#include "UISwitchTest/UISwitchTest.h"
 */
 /*
#include "UIProgressTimerTest/UIProgressTimerTest.h"
 */
/*
#include "UIPotentiometerTest/UIPotentiometerTest.h"
 */
/*
#include "UIGridViewTest/UIGridViewTest.h"
 */
/*
#include "UIPickerViewTest/UIPickerViewTest.h"
 */

USING_NS_CC;

static const char* s_testArray[] =
{
    "UIButtonTest",
    "UIButtonTest_Scale9",
    "UIButtonTest_PressedAction",
    "UIButtonTest_Title",
    "UICheckBoxTest",
    "UISliderTest",
    "UISliderTest_Scale9",
    /*
    "UIPotentiometerTest",
     */
    /*
    "UISwitchTest_Horizontal",
    "UISwitchTest_Vertical",
    "UISwitchTest_VerticalAndTitleVertical",
     */
    "UIImageViewTest",
    "UIImageViewTest_Scale9",
    "UILoadingBarTest_Left",
    "UILoadingBarTest_Right",
    "UILoadingBarTest_Left_Scale9",
    "UILoadingBarTest_Right_Scale9",
    /*
    "UIProgressTimerTest_Radial",
    "UIProgressTimerTest_Horizontal",
    "UIProgressTimerTest_Vertical",
    "UIProgressTimerTest_RadialMidpointChanged",
    "UIProgressTimerTest_BarVarious",
    "UIProgressTimerTest_BarTintAndFade",
    "UIProgressTimerTest_WithSpriteFrame",
     */
    "UITextAtlasTest",
    "UITextTest",
    "UITextTest_LineWrap",
    
    "UILabelTest_Effect",
    
    "UITextTest_TTF",
    "UITextBMFontTest",
    "UITextFieldTest",
    "UITextFieldTest_MaxLength",
    "UITextFieldTest_Password",
    "UITextFieldTest_LineWrap",
    "UILayoutTest",
    "UILayoutTest_Color",
    "UILayoutTest_Gradient",
    "UILayoutTest_BackGroundImage",
    "UILayoutTest_BackGroundImage_Scale9",
    "UILayoutTest_Layout_Linear_Vertical",
    "UILayoutTest_Layout_Linear_Horizontal",
    "UILayoutTest_Layout_Relative_Align_Parent",
    "UILayoutTest_Layout_Relative_Location",
    /*
    "UILayoutTest_Layout_Grid",
     */
    "UIScrollViewTest_Vertical",
    "UIScrollViewTest_Horizontal",
    "UIScrollViewTest_Both",
    "UIScrollViewTest_ScrollToPercentBothDirection",
    "UIScrollViewTest_ScrollToPercentBothDirection_Bounce",    
    "UIPageViewTest,",
    "UIListViewTest_Vertical",
    "UIListViewTest_Horizontal",
    /*
    "UIGridViewTest_Mode_Column",
    "UIGridViewTest_Mode_Row",
     */
    /*
    "UIPickerViewTest_Vertical",
    "UIPickerViewTest_Horizontal",
     */
    "UIWidgetAddNodeTest",
    "UIRichTextTest",
    "UIFocusTest-HBox",
    "UIFocusTest-VBox",
    "UIFocusTest-NestedLayout1",
    "UIFocusTest-NestedLayout2",
    "UIFocusTest-NestedLayout3",
    "UIFocusTest-ListView",
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    "UIVideoPlayerTest"
#endif
};

static UISceneManager *sharedInstance = NULL;


UISceneManager::UISceneManager()
{
    _currentUISceneId = kUIButtonTest;
}

UISceneManager::~UISceneManager()
{
    
}

UISceneManager * UISceneManager::sharedUISceneManager()
{
    if (sharedInstance == NULL)
    {
        sharedInstance = new UISceneManager();
    }
    return sharedInstance;
}

void UISceneManager::purgeUISceneManager()
{
	CC_SAFE_DELETE(sharedInstance);
}

Scene *UISceneManager::nextUIScene()
{
    _currentUISceneId = _currentUISceneId + 1;
    if (_currentUISceneId > _maxUISceneId)
    {
        _currentUISceneId = _minUISceneId;
    }
//    _currentUISceneId = (_currentUISceneId + 1) % kUITestMax;
    
    return currentUIScene();
}

Scene *UISceneManager::previousUIScene()
{
    _currentUISceneId = _currentUISceneId - 1;
    if (_currentUISceneId < _minUISceneId)
    {
        _currentUISceneId = _maxUISceneId;
    }
    /*
    _currentUISceneId = _currentUISceneId - 1;
    if (_currentUISceneId < 0)
    {
        _currentUISceneId = kUITestMax - 1;
    }
     */
    
    return currentUIScene();
}

Scene *UISceneManager::currentUIScene()
{    
    switch (_currentUISceneId)
    {
        case kUIButtonTest:
            return UIButtonTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIButtonTest_Scale9:
            return UIButtonTest_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIButtonTest_PressedAction:
            return UIButtonTest_PressedAction::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIButtonTest_Title:
            return UIButtonTest_Title::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUICheckBoxTest:
            return UICheckBoxTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUISliderTest:
            return UISliderTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUISliderTest_Scale9:
            return UISliderTest_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
            /*
        case kUIPotentiometerTest:
            return UIPotentiometerTest::sceneWithTitle(s_testArray[_currentUISceneId]);
             */
            
            /*
        case kUISwitchTest_Horizontal:
            return UISwitchTest_Horizontal::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUISwitchTest_Vertical:
            return UISwitchTest_Vertical::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUISwitchTest_VerticalAndTitleVertical:
            return UISwitchTest_VerticalAndTitleVertical::sceneWithTitle(s_testArray[_currentUISceneId]);
             */
            
        case kUIImageViewTest:
            return UIImageViewTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIImageViewTest_Scale9:
            return UIImageViewTest_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILoadingBarTest_Left:
            return UILoadingBarTest_Left::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILoadingBarTest_Right:
            return UILoadingBarTest_Right::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILoadingBarTest_Left_Scale9:
            return UILoadingBarTest_Left_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILoadingBarTest_Right_Scale9:
            return UILoadingBarTest_Right_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
            /*
        case kUIProgressTimerTest_Radial:
            return UIProgressTimerTest_Radial::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIProgressTimerTest_Horizontal:
            return UIProgressTimerTest_Horizontal::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIProgressTimerTest_Vertical:
            return UIProgressTimerTest_Vertical::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIProgressTimerTest_RadialMidpointChanged:
            return UIProgressTimerTest_RadialMidpointChanged::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIProgressTimerTest_BarVarious:
            return UIProgressTimerTest_BarVarious::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIProgressTimerTest_BarTintAndFade:
            return UIProgressTimerTest_BarTintAndFade::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIProgressTimerTest_WithSpriteFrame:
            return UIProgressTimerTest_WithSpriteFrame::sceneWithTitle(s_testArray[_currentUISceneId]);
             */
            
        case kUITextAtlasTest:
            return UITextAtlasTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextBMFontTest:
            return UITextBMFontTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextTest:
            return UITextTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextTest_LineWrap:
            return UITextTest_LineWrap::sceneWithTitle(s_testArray[_currentUISceneId]);
            
            
        case kUILabelTest_Effect:
            return UILabelTest_Effect::sceneWithTitle(s_testArray[_currentUISceneId]);
            
            
        case kUITextTest_TTF:
            return UITextTest_TTF::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextFieldTest:
            return UITextFieldTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextFieldTest_MaxLength:
            return UITextFieldTest_MaxLength::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextFieldTest_Password:
            return UITextFieldTest_Password::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextFieldTest_LineWrap:
            return UITextFieldTest_LineWrap::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest:
            return UILayoutTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Color:
            return UILayoutTest_Color::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Gradient:
            return UILayoutTest_Gradient::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_BackGroundImage:
            return UILayoutTest_BackGroundImage::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_BackGroundImage_Scale9:
            return UILayoutTest_BackGroundImage_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Layout_Linear_Vertical:
            return UILayoutTest_Layout_Linear_Vertical::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Layout_Linear_Horizontal:
            return UILayoutTest_Layout_Linear_Horizontal::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Layout_Relative_Align_Parent:
            return UILayoutTest_Layout_Relative_Align_Parent::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Layout_Relative_Location:
            return UILayoutTest_Layout_Relative_Location::sceneWithTitle(s_testArray[_currentUISceneId]);
            
            /*
        case kUILayoutTest_Layout_Grid:
            return UILayoutTest_Layout_Grid::sceneWithTitle(s_testArray[_currentUISceneId]);
             */
            
        case kUIScrollViewTest_Vertical:
            return UIScrollViewTest_Vertical::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIScrollViewTest_Horizontal:
            return UIScrollViewTest_Horizontal::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIScrollViewTest_Both:
            return UIScrollViewTest_Both::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIScrollViewTest_ScrollToPercentBothDirection:
            return UIScrollViewTest_ScrollToPercentBothDirection::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIScrollViewTest_ScrollToPercentBothDirection_Bounce:
            return UIScrollViewTest_ScrollToPercentBothDirection_Bounce::sceneWithTitle(s_testArray[_currentUISceneId]);                    
            
        case kUIPageViewTest:
            return UIPageViewTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIListViewTest_Vertical:
            return UIListViewTest_Vertical::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIListViewTest_Horizontal:
            return UIListViewTest_Horizontal::sceneWithTitle(s_testArray[_currentUISceneId]);
            
            /*
        case kUIGridViewTest_Mode_Column:
            return UIGridViewTest_Mode_Column::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIGridViewTest_Mode_Row:
            return UIGridViewTest_Mode_Row::sceneWithTitle(s_testArray[_currentUISceneId]);
             */
            
            /*
        case kUIPickerViewTest_Vertical:
            return UIPickerViewTest_Vertical::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIPickerViewTest_Horizontal:
            return UIPickerViewTest_Horizontal::sceneWithTitle(s_testArray[_currentUISceneId]);
            */
            
        case kUIWidgetAddNodeTest:
            return UIWidgetAddNodeTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIRichTextTest:
            return UIRichTextTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case KUIFocusTest_HBox:
            return UIFocusTestHorizontal::sceneWithTitle(s_testArray[_currentUISceneId]);
        case KUIFocusTest_VBox:
            return UIFocusTestVertical::sceneWithTitle(s_testArray[_currentUISceneId]);
        case KUIFocusTest_NestedLayout1:
            return UIFocusTestNestedLayout1::sceneWithTitle(s_testArray[_currentUISceneId]);
        case KUIFocusTest_NestedLayout2:
            return UIFocusTestNestedLayout2::sceneWithTitle(s_testArray[_currentUISceneId]);
        case KUIFocusTest_NestedLayout3:
            return UIFocusTestNestedLayout3::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIFocusTest_ListView:
            return UIFocusTestListView::sceneWithTitle(s_testArray[_currentUISceneId]);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case kUIVideoPlayerTest:
            return VideoPlayerTest::sceneWithTitle(s_testArray[_currentUISceneId]);
#endif
    }
    return NULL;
}
