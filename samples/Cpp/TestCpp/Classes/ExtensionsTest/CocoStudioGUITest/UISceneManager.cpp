

#include "UISceneManager.h"
#include "UIScene.h"
#include "UIButtonTest/UIButtonTest.h"
#include "UICheckBoxTest/UICheckBoxTest.h"
#include "UISliderTest/UISliderTest.h"
#include "UIImageViewTest/UIImageViewTest.h"
#include "UILoadingBarTest/UILoadingBarTest.h"
#include "UILabelAtlasTest/UILabelAtlasTest.h"
#include "UILabelTest/UILabelTest.h"
#include "UILabelBMFontTest/UILabelBMFontTest.h"
#include "UITextFieldTest/UITextFieldTest.h"
#include "UILayoutTest/UILayoutTest.h"
#include "UIScrollViewTest/UIScrollViewTest.h"
#include "UIPageViewTest/UIPageViewTest.h"
#include "UIListViewTest/UIListViewTest.h"
#include "UIWidgetAddNodeTest/UIWidgetAddNodeTest.h"
#include "UIRichTextTest/UIRichTextTest.h"
/*===*/
/*
#include "UISwitchTest/UISwitchTest.h"
#include "UIProgressTimerTest/UIProgressTimerTest.h"
#include "UIPotentiometerTest/UIPotentiometerTest.h"
 */
/*
#include "UIGridViewTest/UIGridViewTest.h"
#include "UIPickerViewTest/UIPickerViewTest.h"
 */
/*=*/

USING_NS_CC;


static const char* s_testArray[] =
{
    "UIButtonTest",
    "UIButtonTest_Scale9",
    "UIButtonTest_PressedAction",
    /*===*/
    "UIButtonTest_Title",
    /*=*/
    "UICheckBoxTest",
    "UISliderTest",
    "UISliderTest_Scale9",
    /*===*/
    /*
    "UIPotentiometerTest",
    "UISwitchTest_Horizontal",
    "UISwitchTest_Vertical",
    "UISwitchTest_VerticalAndTitleVertical",
     */
    /*=*/
    "UIImageViewTest",
    "UIImageViewTest_Scale9",
    "UILoadingBarTest_Left",
    "UILoadingBarTest_Right",
    "UILoadingBarTest_Left_Scale9",
    "UILoadingBarTest_Right_Scale9",
    /*===*/
    /*
    "UIProgressTimerTest_Radial",
    "UIProgressTimerTest_Horizontal",
    "UIProgressTimerTest_Vertical",
    "UIProgressTimerTest_RadialMidpointChanged",
    "UIProgressTimerTest_BarVarious",
    "UIProgressTimerTest_BarTintAndFade",
    "UIProgressTimerTest_WithSpriteFrame",
     */
    /*=*/
    "UILabelAtlasTest",
    "UILabelTest",
    /*===*/
    "UILabelTest_LineWrap",
    /*
    "UILabelTest_Effect",
     */
    "UILabelTest_TTF",
    /*=*/
    "UILabelBMFontTest",
    "UITextFieldTest",
    "UITextFieldTest_MaxLength",
    "UITextFieldTest_Password",
    "UITextFieldTest_LineWrap",
    /*===*/
    "UITextFieldTest_LineWrap",
    /**/
    "UILayoutTest",
    "UILayoutTest_Color",
    "UILayoutTest_Gradient",
    "UILayoutTest_BackGroundImage",
    "UILayoutTest_BackGroundImage_Scale9",
    "UILayoutTest_Layout_Linear_Vertical",
    "UILayoutTest_Layout_Linear_Horizontal",
    /*===*/
    "UILayoutTest_Layout_Relative_Align_Parent",
    "UILayoutTest_Layout_Relative_Location",
    /*
    "UILayoutTest_Layout_Grid",
     */
    /*=*/
    "UIScrollViewTest_Vertical",
    "UIScrollViewTest_Horizontal",
    /*===*/
    "UIScrollViewTest_Both",
    "UIScrollViewTest_ScrollToPercentBothDirection",
    "UIScrollViewTest_ScrollToPercentBothDirection_Bounce",
    /*=*/
    "UIPageViewTest,",
    /*===*/
    "UIListViewTest_Vertical",
    "UIListViewTest_Horizontal",
    /*
    "UIGridViewTest_Mode_Column",
    "UIGridViewTest_Mode_Row",
    "UIPickerViewTest_Vertical",
    "UIPickerViewTest_Horizontal",
     */
    /*=*/
    /*===*/
    "UIWidgetAddNodeTest",
    "UIRichTextTest",
    /*=*/
};

static UISceneManager *sharedInstance = NULL;


UISceneManager::UISceneManager()
{
    m_nCurrentUISceneId = kUIButtonTest;
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

CCScene *UISceneManager::nextUIScene()
{
    m_nCurrentUISceneId = m_nCurrentUISceneId + 1;
    if (m_nCurrentUISceneId > m_nMaxUISceneId)
    {
        m_nCurrentUISceneId = m_nMinUISceneId;
    }
//    m_nCurrentUISceneId = (m_nCurrentUISceneId + 1) % kUITestMax;
    
    return currentUIScene();
}

CCScene *UISceneManager::previousUIScene()
{
    m_nCurrentUISceneId = m_nCurrentUISceneId - 1;
    if (m_nCurrentUISceneId < m_nMinUISceneId)
    {
        m_nCurrentUISceneId = m_nMaxUISceneId;
    }
    /*
    if (m_nCurrentUISceneId < 0)
    {
        m_nCurrentUISceneId = m_nMaxUISceneId - 1;
    }
     */
    
    return currentUIScene();
}

CCScene *UISceneManager::currentUIScene()
{    
    switch (m_nCurrentUISceneId)
    {
        case kUIButtonTest:
            return UIButtonTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIButtonTest_Scale9:
            return UIButtonTest_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIButtonTest_PressedAction:
            return UIButtonTest_PressedAction::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*===*/
        case kUIButtonTest_Title:
            return UIButtonTest_Title::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            /*=*/
            
        case kUICheckBoxTest:
            return UICheckBoxTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUISliderTest:
            return UISliderTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUISliderTest_Scale9:
            return UISliderTest_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*===*/
            /*
        case kUIPotentiometerTest:
            return UIPotentiometerTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUISwitchTest_Horizontal:
            return UISwitchTest_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUISwitchTest_Vertical:
            return UISwitchTest_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUISwitchTest_VerticalAndTitleVertical:
            return UISwitchTest_VerticalAndTitleVertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
             */
            /*=*/
            
        case kUIImageViewTest:
            return UIImageViewTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIImageViewTest_Scale9:
            return UIImageViewTest_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILoadingBarTest_Left:
            return UILoadingBarTest_Left::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILoadingBarTest_Right:
            return UILoadingBarTest_Right::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILoadingBarTest_Left_Scale9:
            return UILoadingBarTest_Left_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILoadingBarTest_Right_Scale9:
            return UILoadingBarTest_Right_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*===*/
            /*
        case kUIProgressTimerTest_Radial:
            return UIProgressTimerTest_Radial::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIProgressTimerTest_Horizontal:
            return UIProgressTimerTest_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIProgressTimerTest_Vertical:
            return UIProgressTimerTest_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIProgressTimerTest_RadialMidpointChanged:
            return UIProgressTimerTest_RadialMidpointChanged::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIProgressTimerTest_BarVarious:
            return UIProgressTimerTest_BarVarious::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIProgressTimerTest_BarTintAndFade:
            return UIProgressTimerTest_BarTintAndFade::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIProgressTimerTest_WithSpriteFrame:
            return UIProgressTimerTest_WithSpriteFrame::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
             */
            /*=*/
            
        case kUILabelAtlasTest:
            return UILabelAtlasTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILabelBMFontTest:
            return UILabelBMFontTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILabelTest:
            return UILabelTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*===*/
        case kUILabelTest_LineWrap:
            return UILabelTest_LineWrap::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*
        case kUILabelTest_Effect:
            return UILabelTest_Effect::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
             */
            
        case kUILabelTest_TTF:
            return UILabelTest_TTF::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            /*=*/
            
        case kUITextFieldTest:
            return UITextFieldTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUITextFieldTest_MaxLength:
            return UITextFieldTest_MaxLength::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUITextFieldTest_Password:
            return UITextFieldTest_Password::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUITextFieldTest_LineWrap:
            return UITextFieldTest_LineWrap::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILayoutTest:
            return UILayoutTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILayoutTest_Color:
            return UILayoutTest_Color::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILayoutTest_Gradient:
            return UILayoutTest_Gradient::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILayoutTest_BackGroundImage:
            return UILayoutTest_BackGroundImage::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILayoutTest_BackGroundImage_Scale9:
            return UILayoutTest_BackGroundImage_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILayoutTest_Layout_Linear_Vertical:
            return UILayoutTest_Layout_Linear_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILayoutTest_Layout_Linear_Horizontal:
            return UILayoutTest_Layout_Linear_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*===*/
        case kUILayoutTest_Layout_Relative_Align_Parent:
            return UILayoutTest_Layout_Relative_Align_Parent::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILayoutTest_Layout_Relative_Location:
            return UILayoutTest_Layout_Relative_Location::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*
        case kUILayoutTest_Layout_Grid:
            return UILayoutTest_Layout_Grid::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
             */
            /*=*/
            
        case kUIScrollViewTest_Vertical:
            return UIScrollViewTest_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIScrollViewTest_Horizontal:
            return UIScrollViewTest_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*===*/
        case kUIScrollViewTest_Both:
            return UIScrollViewTest_Both::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIScrollViewTest_ScrollToPercentBothDirection:
            return UIScrollViewTest_ScrollToPercentBothDirection::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIScrollViewTest_ScrollToPercentBothDirection_Bounce:
            return UIScrollViewTest_ScrollToPercentBothDirection_Bounce::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);                    
            /*=*/
            
        case kUIPageViewTest:
            return UIPageViewTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*===*/
        case kUIListViewTest_Vertical:
            return UIListViewExTest_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIListViewTest_Horizontal:
            return UIListViewExTest_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
            /*
        case kUIGridViewTest_Mode_Column:
            return UIGridViewTest_Mode_Column::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIGridViewTest_Mode_Row:
            return UIGridViewTest_Mode_Row::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPickerViewTest_Vertical:
            return UIPickerViewTest_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPickerViewTest_Horizontal:
            return UIPickerViewTest_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
             */
            /*=*/
            
            /*===*/
        case kUIWidgetAddNodeTest:
            return UIWidgetAddNodeTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIRichTextTest:
            return UIRichTextTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            /*=*/
    }
    return NULL;
}
