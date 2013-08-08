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

#ifndef __UIHELPER_H__
#define __UIHELPER_H__

#include "UIInputManager.h"
#include "../../CCArmature/external_tool/Json/CSContentJsonDictionary.h"


#define CCUIHELPER cocos2d::extension::UIHelper::instance()

NS_CC_EXT_BEGIN

class UIHelper
{
public:
    UIHelper();
    ~UIHelper();
    void init();
    
    UIWidget* createWidgetFromJsonFile(const char* fileName);
    static UIHelper* instance();
	static void purgeUIHelper();
    void addSpriteFrame(const char* fileName);
    void removeSpriteFrame(const char* fileName);
    void removeAllSpriteFrame();
    UIWidget* seekWidgetByTag(UIWidget* root, int tag);
    UIWidget* seekWidgetByName(UIWidget* root, const char* name);
	UIWidget* seekActionWidgetByActionTag(UIWidget* root, int tag);
    UIWidget* seekWidgetByRelativeName(UIWidget* root, const char* name);
    void setFileDesignWidth(float width);
    float getFileDesignWidth();
    void setFileDesignHeight(float height);
    float getFileDesignHeight();
protected:
    
    float m_fFileDesignWidth;
    float m_fFileDesignHeight;
    //texture
    CCArray* m_textureFiles;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UISystem__) */
