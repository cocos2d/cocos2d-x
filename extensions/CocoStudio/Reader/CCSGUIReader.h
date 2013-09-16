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

#include "../GUI/BaseClasses/UIWidget.h"
#include "../Json/CSContentJsonDictionary.h"

NS_CC_EXT_BEGIN

#define kCCSVersion 1.0
class CCSGUIReader : Object
{
public:
    CCSGUIReader();
    ~CCSGUIReader();
    static CCSGUIReader* shareReader();
	static void purgeCCSGUIReader();
    
    UIWidget* widgetFromJsonFile(const char* fileName);
    UIWidget* widgetFromJsonDictionary(cs::JsonDictionary* data);
    
    int getVersionInteger(const char* str);
    
    void setPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setColorPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForButtonFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForCheckBoxFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForImageViewFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForLabelFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForLabelAtlasFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForContainerWidgetFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForPanelFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForScrollViewFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForSliderFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForTextAreaFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForTextButtonFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForTextFieldFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForLoadingBarFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForImageButtonFromJsonDictionary(UIWidget* widget, cs::JsonDictionary* options);
    void setPropsForListViewFromJsonDictionary(UIWidget* widget, cs::JsonDictionary* options);
    void setPropsForPageViewFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForLabelBMFontFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    void setPropsForDragPanelFromJsonDictionary(UIWidget*widget,cs::JsonDictionary* options);
    
protected:
    std::string m_strFilePath;
    bool m_bOlderVersion;
};

NS_CC_EXT_END


#endif /* defined(__CCSGUIReader__) */
