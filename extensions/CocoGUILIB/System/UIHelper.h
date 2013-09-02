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
    /**
     * Default constructor
     */
    UIHelper();
    
    /**
     * Default destructor
     */
    ~UIHelper();
    
    //initializes state of UIHelper.
    void init();
    
    /**
     * Load a widget with json file.
     *
     * @return a widget created with json file.
     */
    UIWidget* createWidgetFromJsonFile(const char* fileName);
    
    //get instance
    static UIHelper* instance();
    
    //release instance
	static void purgeUIHelper();
    
    //add a plist file for loading widget's texture.
    void addSpriteFrame(const char* fileName);
    
    //remove a plist file for loading widget's texture.
    void removeSpriteFrame(const char* fileName);
    
    //remove all plist files for loading widget's texture.
    void removeAllSpriteFrame();
    
    /**
     * Finds a widget whose tag equals to param tag from root widget.
     *
     * @param root      widget which will be seeked.
     *
     * @tag             tag value.
     *
     * @return finded result.
     */
    UIWidget* seekWidgetByTag(UIWidget* root, int tag);
    
    /**
     * Finds a widget whose name equals to param name from root widget.
     *
     * @param root      widget which will be seeked.
     *
     * @name             name value.
     *
     * @return finded result.
     */
    UIWidget* seekWidgetByName(UIWidget* root, const char* name);
    
    /**
     * Finds a widget whose name equals to param name from root widget.
     *
     * RelativeLayout will call this method to find the widget witch is needed.
     *
     * @param root      widget which will be seeked.
     *
     * @name             name value.
     *
     * @return finded result.
     */
    UIWidget* seekWidgetByRelativeName(UIWidget* root, const char* name);
    void setFileDesignWidth(float width);
    float getFileDesignWidth();
    void setFileDesignHeight(float height);
    float getFileDesignHeight();
    /*temp action*/
    UIWidget* seekActionWidgetByActionTag(UIWidget* root, int tag);
protected:
    
    float m_fFileDesignWidth;
    float m_fFileDesignHeight;
    //texture
    CCArray* m_textureFiles;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UISystem__) */
