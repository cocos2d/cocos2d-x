/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __TestCpp__UISceneManager__
#define __TestCpp__UISceneManager__

#include "cocos2d.h"

USING_NS_CC;

enum
{
    kUIButtonTest = 0,
    kUIButtonTest_Scale9,
    kUIButtonTest_PressedAction,
    kUIButtonTest_Title,
    kUICheckBoxTest,
    kUISliderTest,
    kUISliderTest_Scale9,
    /*
    kUIPotentiometerTest,
     */
    /*
    kUISwitchTest_Horizontal,
    kUISwitchTest_Vertical,
    kUISwitchTest_VerticalAndTitleVertical,
     */
    kUIImageViewTest,
    kUIImageViewTest_Scale9,
    kUILoadingBarTest_Left,
    kUILoadingBarTest_Right,
    kUILoadingBarTest_Left_Scale9,
    kUILoadingBarTest_Right_Scale9,
    /*
    kUIProgressTimerTest_Radial,
    kUIProgressTimerTest_Horizontal,
    kUIProgressTimerTest_Vertical,
    kUIProgressTimerTest_RadialMidpointChanged,
    kUIProgressTimerTest_BarVarious,
    kUIProgressTimerTest_BarTintAndFade,
    kUIProgressTimerTest_WithSpriteFrame,
     */
    kUITextAtlasTest,
    kUITextTest,
    kUITextTest_LineWrap,
    
    kUILabelTest_Effect,
    kUITextTest_TTF,
    kUITextBMFontTest,
    kUITextFieldTest,
    kUITextFieldTest_MaxLength,
    kUITextFieldTest_Password,
    kUITextFieldTest_LineWrap,
    kUILayoutTest,
    kUILayoutTest_Color,
    kUILayoutTest_Gradient,
    kUILayoutTest_BackGroundImage,
    kUILayoutTest_BackGroundImage_Scale9,
    kUILayoutTest_Layout_Linear_Vertical,
    kUILayoutTest_Layout_Linear_Horizontal,
    kUILayoutTest_Layout_Relative_Align_Parent,
    kUILayoutTest_Layout_Relative_Location,
    /*
    kUILayoutTest_Layout_Grid,
     */
    kUIScrollViewTest_Vertical,
    kUIScrollViewTest_Horizontal,
    kUIScrollViewTest_Both,
    kUIScrollViewTest_ScrollToPercentBothDirection,
    kUIScrollViewTest_ScrollToPercentBothDirection_Bounce,    
    kUIPageViewTest,
    kUIListViewTest_Vertical,
    kUIListViewTest_Horizontal,
    /*
    kUIGridViewTest_Mode_Column,
    kUIGridViewTest_Mode_Row,
    kUIPickerViewTest_Vertical,
    kUIPickerViewTest_Horizontal,
     */
    kUIWidgetAddNodeTest,
    kUIRichTextTest,
    KUIFocusTest_HBox,
    KUIFocusTest_VBox,
    KUIFocusTest_NestedLayout1,
    KUIFocusTest_NestedLayout2,
    KUIFocusTest_NestedLayout3,
    kUIFocusTest_ListView,
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    kUIVideoPlayerTest,
#endif
    kUITestMax
};

class UISceneManager : public Ref
{
public:
    UISceneManager();
    ~UISceneManager();
    /** Returns the singleton of the ui scene manager. */
    static UISceneManager * sharedUISceneManager();
	static void purgeUISceneManager();
    
    /** Returns the next ui scene. */
    cocos2d::Scene *nextUIScene();
    
    /** Returns the previous ui scene. */
    cocos2d::Scene *previousUIScene();
    
    /** Returns the current control scene. */
    cocos2d::Scene *currentUIScene();
    
    /** UI scene id. */
    CC_SYNTHESIZE(int, _currentUISceneId, CurrentUISceneId)
    
    CC_SYNTHESIZE(int, _minUISceneId, MinUISceneId)
    CC_SYNTHESIZE(int, _maxUISceneId, MaxUISceneId)
};

#endif /* defined(__TestCpp__UISceneManager__) */
