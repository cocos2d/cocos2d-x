

#include "UISceneManager_Editor.h"
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


USING_NS_CC;

static const char* s_testArray[] =
{
    "UIButtonTest_Editor",
    "UICheckBoxTest_Editor",
    "UIImageViewTest_Editor",
    "UITextAtlasTest_Editor",
    "UITextBMFontTest_Editor",
    "UITextTest_Editor",
    "UILoadingBarTest_Editor",
    "UISliderTest_Editor",
    "UITextFieldTest_Editor",
    "UIWidgetAddNodeTest_Editor",
    "UILayoutTest_Editor",
    "UILayoutTest_Color_Editor",
    "UILayoutTest_Gradient_Editor",
    "UILayoutTest_BackGroundImage_Editor",
    "UILayoutTest_BackGroundImage_Scale9_Editor",
    "UILayoutTest_Layout_Linear_Vertical_Editor",
    "UILayoutTest_Layout_Linear_Horizontal_Editor",
    "UILayoutTest_Layout_Relative_Align_Parent_Editor",
    "UILayoutTest_Layout_Relative_Location_Editor",
    "UIListViewTest_Vertical_Editor",
    "UIListViewTest_Horizontal_Editor",
    "UIPageViewTest_Editor",
    "UIScrollViewTest_Vertical_Editor",
    "UIScrollViewTest_Horizontal_Editor",
    "UIScrollViewTest_Both_Editor",    
};

static UISceneManager_Editor* sharedInstance = NULL;

UISceneManager_Editor::UISceneManager_Editor()
{
    _currentUISceneId = kUIButtonTest_Editor;
}

UISceneManager_Editor::~UISceneManager_Editor()
{
    
}

UISceneManager_Editor* UISceneManager_Editor::sharedUISceneManager_Editor()
{
    if (sharedInstance == NULL)
    {
        sharedInstance = new UISceneManager_Editor();
    }
    return sharedInstance;
}

void UISceneManager_Editor::purge()
{
    CC_SAFE_DELETE(sharedInstance);
}

Scene* UISceneManager_Editor::nextUIScene()
{
    _currentUISceneId = _currentUISceneId + 1;
    if (_currentUISceneId > _maxUISceneId)
    {
        _currentUISceneId = _minUISceneId;
    }
    
    return currentUIScene();
}

Scene* UISceneManager_Editor::previousUIScene()
{
    _currentUISceneId = _currentUISceneId - 1;
    if (_currentUISceneId < _minUISceneId)
    {
        _currentUISceneId = _maxUISceneId;
    }
    
    return currentUIScene();
}

Scene* UISceneManager_Editor::currentUIScene()
{
    switch (_currentUISceneId)
    {
        case kUIButtonTest_Editor:
            return UIButtonTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            break;
            
        case kUICheckBoxTest_Editor:
            return UICheckBoxTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            break;
            
        case kUIImageViewTest_Editor:
            return UIImageViewTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextAtlasTest_Editor:
            return UITextAtlasTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextBMFontTest_Editor:
            return UITextBMFontTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextTest_Editor:
            return UITextTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILoadingBarTest_Editor:
            return UILoadingBarTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUISliderTest_Editor:
            return UISliderTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUITextFieldTest_Editor:
            return UITextFieldTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIWidgetAddNodeTest_Editor:
            return UIWidgetAddNodeTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Editor:
            return UILayoutTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Color_Editor:
            return UILayoutTest_Color_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Gradient_Editor:
            return UILayoutTest_Gradient_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_BackGroundImage_Editor:
            return UILayoutTest_BackGroundImage_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_BackGroundImage_Scale9_Editor:
            return UILayoutTest_BackGroundImage_Scale9_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Layout_Linear_Vertical_Editor:
            return UILayoutTest_Layout_Linear_Vertical_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Layout_Linear_Horizontal_Editor:
            return UILayoutTest_Layout_Linear_Horizontal_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Layout_Relative_Align_Parent_Editor:
            return UILayoutTest_Layout_Relative_Align_Parent_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUILayoutTest_Layout_Relative_Location_Editor:
            return UILayoutTest_Layout_Relative_Location_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIListViewTest_Vertical_Editor:
            return UIListViewTest_Vertical_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIListViewTest_Horizontal_Editor:
            return UIListViewTest_Horizontal_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIPageViewTest_Editor:
            return UIPageViewTest_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIScrollViewTest_Vertical_Editor:
            return UIScrollViewTest_Vertical_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIScrollViewTest_Horizontal_Editor:
            return UIScrollViewTest_Horizontal_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        case kUIScrollViewTest_Both_Editor:
            return UIScrollViewTest_Both_Editor::sceneWithTitle(s_testArray[_currentUISceneId]);
            
        default:
            break;
    }
    
    return NULL;
}
