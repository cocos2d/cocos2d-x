

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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "UIWebViewTest/UIWebViewTest.h"
#endif
#include "UIScale9SpriteTest.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include "UIEditBoxTest.h"
#endif


USING_NS_CC;

static const char* s_testArray[] =
{
    "UIButtonTest",
    "UIButtonTest_Scale9",
    "UIButtonTest_PressedAction",
    "UIButtonTest_Title",
    "UIButtonTest_RemoveSelf",
    "UIButtonTestSwitchScale9",
    "UIButtonTestZoomScale",
    "UIButtonTextOnly",
    "UIButtonIgnoreContentSizeTest",
    "UIButtonTitleEffectTest",
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    "UIEditBoxTest",
#endif
    "UICheckBoxTest",
    "UISliderTest",
    "UISliderTest_Scale9",
  
    "UIImageViewTest",
    "UIImageViewTest_Scale9",
    "UIImageViewTest_ContentSize",
    
    "UILoadingBarTest_Left",
    "UILoadingBarTest_Right",
    "UILoadingBarTest_Left_Scale9",
    "UILoadingBarTest_Right_Scale9",
  
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
    "UITextFieldTest_TrueTypeFont",
    "UITextFieldTest_PlaceHolderColor",
    
    "UILayoutTest",
    "UILayoutTest_Color",
    "UILayoutTest_Gradient",
    "UILayoutTest_BackGroundImage",
    "UILayoutTest_BackGroundImage_Scale9",
    "UILayoutTest_Layout_Linear_Vertical",
    "UILayoutTest_Layout_Linear_Horizontal",
    "UILayoutTest_Layout_Relative_Align_Parent",
    "UILayoutTest_Layout_Relative_Location",
   
    "UIScrollViewTest_Vertical",
    "UIScrollViewTest_Horizontal",
    "UIScrollViewTest_Both",
    "UIScrollViewTest_ScrollToPercentBothDirection",
    "UIScrollViewTest_ScrollToPercentBothDirection_Bounce",
    "UIScrollViewNestTest",
    "UIScrollViewRotated",
    
    "UIPageViewTest",
    "UIPageViewButtonTest",
    "UIPageViewCustomScrollThreshold",
    "UIPageViewTouchPropagationTest",
    "UIPageViewDynamicAddAndRemoveTest",
    
    "UIListViewTest_Vertical",
    "UIListViewTest_Horizontal",
   
    "UIWidgetAddNodeTest",
    
    "UIRichTextTest",
    
    "UIFocusTest-HBox",
    "UIFocusTest-VBox",
    "UIFocusTest-NestedLayout1",
    "UIFocusTest-NestedLayout2",
    "UIFocusTest-NestedLayout3",
    "UIFocusTest-ListView",
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    "UIVideoPlayerTest",
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    "UIWebViewTest",
#endif
    "UIScale9SpriteTest",
    "UIScale9SpriteHierarchialTest",
    "UIScale9SpriteTouchTest",
    "UIS9BatchNodeBasic",
    "UIS9FrameNameSpriteSheet",
    "UIS9FrameNameSpriteSheetRotated",
    "UIS9FrameNameSpriteSheetCropped",
    "UIS9FrameNameSpriteSheetCroppedRotated",
    "UIS9BatchNodeScaledNoInsets",
    "UIS9FrameNameSpriteSheetScaledNoInsets",
    "UIS9FrameNameSpriteSheetRotatedScaledNoInsets",
    "UIS9BatchNodeScaleWithCapInsets",
    "UIS9FrameNameSpriteSheetInsets",
    "UIS9FrameNameSpriteSheetInsetsScaled",
    "UIS9FrameNameSpriteSheetRotatedInsets",
    "UIS9_TexturePacker",
    "UIS9FrameNameSpriteSheetRotatedInsetsScaled",
    "UIS9FrameNameSpriteSheetRotatedSetCapInsetLater",
    "UIS9CascadeOpacityAndColor",
    "UIS9ZOrder",
    "UIS9Flip",
    "UIS9ChangeAnchorPoint",
};

static UISceneManager *sharedInstance = nullptr;


UISceneManager::UISceneManager()
{
    _currentUISceneId = kUIButtonTest;
}

UISceneManager::~UISceneManager()
{
    
}

UISceneManager * UISceneManager::sharedUISceneManager()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new (std::nothrow) UISceneManager();
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
    
    return currentUIScene();
}

Scene *UISceneManager::previousUIScene()
{
    _currentUISceneId = _currentUISceneId - 1;
    if (_currentUISceneId < _minUISceneId)
    {
        _currentUISceneId = _maxUISceneId;
    }
    
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
        case kUIButtonTest_RemoveSelf:
            return UIButtonTestRemoveSelf::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIButtonTestSwitchScale9:
            return UIButtonTestSwitchScale9::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIButtonTestZoomScale:
            return UIButtonTestZoomScale::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIButtonTextOnly:
            return UIButtonTextOnly::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIButtonIgnoreContentSizeTest:
            return UIButtonIgnoreContentSizeTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIButtonTitleEffectTest:
            return UIButtonTitleEffectTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUICheckBoxTest:
            return UICheckBoxTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUISliderTest:
            return UISliderTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUISliderTest_Scale9:
            return UISliderTest_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIImageViewTest:
            return UIImageViewTest::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIImageViewTest_Scale9:
            return UIImageViewTest_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIImageViewTest_ContentSize:
            return UIImageViewTest_ContentSize::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUILoadingBarTest_Left:
            return UILoadingBarTest_Left::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILoadingBarTest_Right:
            return UILoadingBarTest_Right::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILoadingBarTest_Left_Scale9:
            return UILoadingBarTest_Left_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILoadingBarTest_Right_Scale9:
            return UILoadingBarTest_Right_Scale9::sceneWithTitle(s_testArray[_currentUISceneId]);
            
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
        case kUITextFieldTest_TrueTypeFont:
            return UITextFieldTest_TrueTypeFont::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUITextFieldTest_PlaceHolderColor:
            return UITextFieldTest_PlaceHolderColor::sceneWithTitle(s_testArray[_currentUISceneId]);
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
        case kUIScrollViewNestTest:
            return UIScrollViewNestTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIScrollViewRotated:
            return UIScrollViewRotated::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIPageViewTest:
            return UIPageViewTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIPageViewButtonTest:
            return UIPageViewButtonTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIPageViewCustomScrollThreshold:
            return UIPageViewCustomScrollThreshold::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIPageViewTouchPropagationTest:
            return UIPageViewTouchPropagationTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIPageViewDynamicAddAndRemoveTest:
            return UIPageViewDynamicAddAndRemoveTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIListViewTest_Vertical:
            return UIListViewTest_Vertical::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIListViewTest_Horizontal:
            return UIListViewTest_Horizontal::sceneWithTitle(s_testArray[_currentUISceneId]);
            
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case KWebViewTest:
            return WebViewTest::sceneWithTitle(s_testArray[_currentUISceneId]);
#endif
        case kUIScale9SpriteTest:
            return UIScale9SpriteTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIScale9SpriteHierarchialTest:
            return UIScale9SpriteHierarchialTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIScale9SpriteTouchTest:
            return UIScale9SpriteTouchTest::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9BatchNodeBasic:
            return UIS9BatchNodeBasic::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheet:
            return UIS9FrameNameSpriteSheet::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetRotated:
            return UIS9FrameNameSpriteSheetRotated::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetCropped:
            return UIS9FrameNameSpriteSheetCropped::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetCroppedRotated:
            return UIS9FrameNameSpriteSheetCroppedRotated::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9BatchNodeScaledNoInsets:
            return UIS9BatchNodeScaledNoInsets::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetScaledNoInsets:
            return UIS9FrameNameSpriteSheetScaledNoInsets::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetRotatedScaledNoInsets:
            return UIS9FrameNameSpriteSheetRotatedScaledNoInsets::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9BatchNodeScaleWithCapInsets:
            return UIS9BatchNodeScaleWithCapInsets::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetInsets:
            return UIS9FrameNameSpriteSheetInsets::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetInsetsScaled:
            return UIS9FrameNameSpriteSheetInsetsScaled::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetRotatedInsets:
            return UIS9FrameNameSpriteSheetRotatedInsets::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9_TexturePacker:
            return UIS9_TexturePacker::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetRotatedInsetsScaled:
            return UIS9FrameNameSpriteSheetRotatedInsetsScaled::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9FrameNameSpriteSheetRotatedSetCapInsetLater:
            return UIS9FrameNameSpriteSheetRotatedSetCapInsetLater::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9CascadeOpacityAndColor:
            return UIS9CascadeOpacityAndColor::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9ZOrder:
            return UIS9ZOrder::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9Flip:
            return UIS9Flip::sceneWithTitle(s_testArray[_currentUISceneId]);
        case kUIS9ChangeAnchorPoint:
            return UIS9ChangeAnchorPoint::sceneWithTitle(s_testArray[_currentUISceneId]);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        case kUIEditBoxTest:
            return UIEditBoxTest::sceneWithTitle(s_testArray[_currentUISceneId]);
#endif
       
    }
    return nullptr;
}
