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

#ifndef __TestCpp__UISceneManager_Editor__
#define __TestCpp__UISceneManager_Editor__

#include "cocos2d.h"

USING_NS_CC;

enum
{
    kUIButtonTest_Editor = 0,
    kUICheckBoxTest_Editor,
    kUIImageViewTest_Editor,
    kUILabelAtlasTest_Editor,
    kUILabelBMFontTest_Editor,
    kUILabelTest_Editor,
    kUILoadingBarTest_Editor,
    kUISliderTest_Editor,
    kUITextFieldTest_Editor,
    kUIWidgetAddNodeTest_Editor,
    kUILayoutTest_Editor,
    kUILayoutTest_Color_Editor,
    kUILayoutTest_Gradient_Editor,
    kUILayoutTest_BackGroundImage_Editor,
    kUILayoutTest_BackGroundImage_Scale9_Editor,
    kUILayoutTest_Layout_Linear_Vertical_Editor,
    kUILayoutTest_Layout_Linear_Horizontal_Editor,
    kUILayoutTest_Layout_Relative_Align_Parent_Editor,
    kUILayoutTest_Layout_Relative_Location_Editor,
    kUIListViewTest_Vertical_Editor,
    kUIListViewTest_Horizontal_Editor,
    kUIPageViewTest_Editor,
    kUIScrollViewTest_Vertical_Editor,
    kUIScrollViewTest_Horizontal_Editor,
    kUIScrollViewTest_Both_Editor,
    kUITestMax_Editor,
};

class UISceneManager_Editor : public CCObject
{
public:
    UISceneManager_Editor();
    ~UISceneManager_Editor();
    
    /** Returns the singleton of the ui scene manager. */
    static UISceneManager_Editor* sharedUISceneManager_Editor();
	static void purge();
    
    /** Returns the next ui scene. */
    virtual CCScene* nextUIScene();
    
    /** Returns the previous ui scene. */
    virtual CCScene* previousUIScene();
    
    /** Returns the current control scene. */
    virtual CCScene* currentUIScene();
    
    /** UI scene id. */
    CC_SYNTHESIZE(int, _currentUISceneId, CurrentUISceneId)
    
    CC_SYNTHESIZE(int, _minUISceneId, MinUISceneId)
    CC_SYNTHESIZE(int, _maxUISceneId, MaxUISceneId)
};

#endif /* defined(__TestCpp__UISceneManager_Editor__) */
