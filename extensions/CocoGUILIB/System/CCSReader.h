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

#ifndef __CCSREADER_H__
#define __CCSREADER_H__

#include "../BaseClasses/UIWidget.h"
#include "../../CCArmature/external_tool/Json/CSContentJsonDictionary.h"

NS_CC_EXT_BEGIN

#define kCCSVersion 1.0
class CCSReader : CCObject
{
public:
    CCSReader();
    ~CCSReader();
    static CCSReader* shareReader();
	static void purgeCCSReader();
    
    UIWidget* widgetFromJsonFile(const char* fileName);
    UIWidget* widgetFromJsonDictionary(cs::CSJsonDictionary* data);
    
    int getVersionInteger(const char* str);
    
    void setPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setColorPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForButtonFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForCheckBoxFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForImageViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForLabelFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForLabelAtlasFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForContainerWidgetFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForPanelFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForScrollViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForSliderFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForTextAreaFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForTextButtonFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForTextFieldFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForLoadingBarFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForImageButtonFromJsonDictionary(UIWidget* widget, cs::CSJsonDictionary* options);
    void setPropsForListViewFromJsonDictionary(UIWidget* widget, cs::CSJsonDictionary* options);
    void setPropsForPageViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForLabelBMFontFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    void setPropsForDragPanelFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    
protected:
    std::string m_strFilePath;
    bool m_bOlderVersion;
};

NS_CC_EXT_END


#endif /* defined(__CocosGUITest__CCSReader__) */
