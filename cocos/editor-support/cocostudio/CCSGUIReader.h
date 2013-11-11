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

#ifndef __CCSGUIREADER_H__
#define __CCSGUIREADER_H__

#include "gui/UIWidget.h"
#include "cocostudio/CSContentJsonDictionary.h"

namespace cocostudio {

#define kCCSVersion 1.0
class CCSGUIReader : public cocos2d::Object
{
public:
    CCSGUIReader();
    virtual ~CCSGUIReader();
    static CCSGUIReader* shareReader();
	static void purgeCCSGUIReader();
    
    gui::UIWidget* widgetFromJsonFile(const char* fileName);
    gui::UIWidget* widgetFromJsonDictionary(JsonDictionary* data);
    
    int getVersionInteger(const char* str);
    
    void setPropsForWidgetFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setColorPropsForWidgetFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForButtonFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForCheckBoxFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForImageViewFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForLabelFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForLabelAtlasFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForContainerWidgetFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForPanelFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForScrollViewFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForSliderFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForTextAreaFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForTextButtonFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForTextFieldFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForLoadingBarFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForImageButtonFromJsonDictionary(gui::UIWidget* widget, JsonDictionary* options);
    void setPropsForListViewFromJsonDictionary(gui::UIWidget* widget, JsonDictionary* options);
    void setPropsForPageViewFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForLabelBMFontFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    void setPropsForDragPanelFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    
    void storeFileDesignSize(const char* fileName, const cocos2d::Size &size);
    
    const cocos2d::Size getFileDesignSize(const char* fileName) const;
protected:
    std::string m_strFilePath;
    bool m_bOlderVersion;
    cocos2d::Dictionary* _fileDesignSizes;
};

}


#endif /* defined(__CCSGUIReader__) */
