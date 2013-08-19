

#include "UISceneManager.h"
#include "UIScene.h"
#include "UIButtonTest/UIButtonTest.h"
#include "UITextButtonTest/UITextButtonTest.h"
#include "UIZoomButtonTest/UIZoomButtonTest.h"
#include "UICheckBoxTest/UICheckBoxTest.h"
#include "UISliderTest/UISliderTest.h"
#include "UIImageViewTest/UIImageViewTest.h"
#include "UILoadingBarTest/UILoadingBarTest.h"
#include "UILabelAtlasTest/UILabelAtlasTest.h"
#include "UILabelTest/UILabelTest.h"
#include "UITextAreaTest/UITextAreaTest.h"
#include "UILabelBMFontTest/UILabelBMFontTest.h"
#include "UITextFieldTest/UITextFieldTest.h"
#include "UIPanelTest/UIPanelTest.h"
#include "UIScrollViewTest/UIScrollViewTest.h"
#include "UIPageViewTest/UIPageViewTest.h"
#include "UIListViewTest/UIListViewTest.h"
#include "UIDragPanelTest/UIDragPanelTest.h"
#include "UINodeContainerTest/UINodeContainerTest.h"

USING_NS_CC;

enum
{
    kUIButtonTest = 0,
    kUIButtonTest_Scale9,
    kUITextButtonTest,
    kUITextButtonTest_Scale9,
    kUIZoomButtonTest,
    kUICheckBoxTest,
    kUISliderTest,
    kUISliderTest_Scale9,
    kUIImageViewTest,
    kUIImageViewTest_Scale9,
    kUILoadingBarTest_Left,
    kUILoadingBarTest_Right,
    kUILoadingBarTest_Left_Scale9,
    kUILoadingBarTest_Right_Scale9,
    kUILabelAtlasTest,
    kUILabelTest,
    kUITextAreaTest,
    kUILabelBMFontTest,
    kUITextFieldTest,
    kUITextFieldTest_MaxLength,
    kUITextFieldTest_Password,
    kUIPanelTest,
    kUIPanelTest_Color,
    kUIPanelTest_Gradient,
    kUIPanelTest_BackGroundImage,
    kUIPanelTest_BackGroundImage_Scale9,
    kUIPanelTest_Layout_Linear_Vertical,
    kUIPanelTest_Layout_Linear_Horizontal,
    kUIPanelTest_Layout_Relative,
    kUIScrollViewTest_Vertical,
    kUIScrollViewTest_Horizontal,
    kUIPageViewTest,
    kUIListViewTest_Vertical,
    kUIListViewTest_Horizontal,
    kUIDragPanelTest,
    kUIDragPanelTest_Bounce,
    kUINodeContainerTest,    
    kUITestMax
};

static const char* s_testArray[] =
{
    "UIButtonTest",
    "UIButtonTest_Scale9",
    "UITextButtonTest",
    "UITextButtonTest_Scale9",
    "UIZoomButtonTest",
    "UICheckBoxTest",
    "UISliderTest",
    "UISliderTest_Scale9",
    "UIImageViewTest",
    "UIImageViewTest_Scale9",
    "UILoadingBarTest_Left",
    "UILoadingBarTest_Right"
    "UILoadingBarTest_Left_Scale9",
    "UILoadingBarTest_Right_Scale9",
    "UILabelAtlasTest",
    "UILabelTest",
    "UITextAreaTest",    
    "UILabelBMFontTest",
    "UITextFieldTest",
    "UITextFieldTest_MaxLength",
    "UITextFieldTest_Password",
    "UIPanelTest",
    "UIPanelTest_Color",
    "UIPanelTest_Gradient",
    "UIPanelTest_BackGroundImage",
    "UIPanelTest_BackGroundImage_Scale9",
    "UIPanelTest_Layout_Linear_Vertical",
    "UIPanelTest_Layout_Linear_Horizontal",
    "UIPanelTest_Layout_Relative",
    "UIScrollViewTest_Vertical",
    "UIScrollViewTest_Horizontal",
    "UIPageViewTest,",
    "UIListViewTest_Vertical",
    "UIListViewTest_Horizontal",
    "UIDragPanelTest",
    "UIDragPanelTest_Bounce",
    "UINodeContainerTest",
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
    m_nCurrentUISceneId = (m_nCurrentUISceneId + 1) % kUITestMax;
    
    return currentUIScene();
}

CCScene *UISceneManager::previousUIScene()
{
    m_nCurrentUISceneId = m_nCurrentUISceneId - 1;
    if (m_nCurrentUISceneId < 0)
    {
        m_nCurrentUISceneId = kUITestMax - 1;
    }
    
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
            
        case kUITextButtonTest:
            return UITextButtonTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUITextButtonTest_Scale9:
            return UITextButtonTest_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIZoomButtonTest:
            return UIZoomButtonTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUICheckBoxTest:
            return UICheckBoxTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUISliderTest:
            return UISliderTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUISliderTest_Scale9:
            return UISliderTest_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
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
            
        case kUILabelAtlasTest:
            return UILabelAtlasTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILabelBMFontTest:
            return UILabelBMFontTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUILabelTest:
            return UILabelTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUITextAreaTest:
            return UITextAreaTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUITextFieldTest:
            return UITextFieldTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUITextFieldTest_MaxLength:
            return UITextFieldTest_MaxLength::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUITextFieldTest_Password:
            return UITextFieldTest_Password::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPanelTest:
            return UIPanelTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPanelTest_Color:
            return UIPanelTest_Color::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPanelTest_Gradient:
            return UIPanelTest_Gradient::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPanelTest_BackGroundImage:
            return UIPanelTest_BackGroundImage::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPanelTest_BackGroundImage_Scale9:
            return UIPanelTest_BackGroundImage_Scale9::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPanelTest_Layout_Linear_Vertical:
            return UIPanelTest_Layout_Linear_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPanelTest_Layout_Linear_Horizontal:
            return UIPanelTest_Layout_Linear_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPanelTest_Layout_Relative:
            return UIPanelTest_Layout_Relative::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIScrollViewTest_Vertical:
            return UIScrollViewTest_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIScrollViewTest_Horizontal:
            return UIScrollViewTest_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIPageViewTest:
            return UIPageViewTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIListViewTest_Vertical:
            return UIListViewTest_Vertical::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIListViewTest_Horizontal:
            return UIListViewTest_Horizontal::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIDragPanelTest:
            return UIDragPanelTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUIDragPanelTest_Bounce:
            return UIDragPanelTest_Bounce::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
            
        case kUINodeContainerTest:
            return UINodeContainerTest::sceneWithTitle(s_testArray[m_nCurrentUISceneId]);
    }
    return NULL;
}