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
class GUIReader : public cocos2d::Object
{
public:
    GUIReader();
    ~GUIReader();
    static GUIReader* shareReader();
    static void purgeGUIReader();
    
    gui::UIWidget* widgetFromJsonFile(const char* fileName);
    int getVersionInteger(const char* str);
    void storeFileDesignSize(const char* fileName, const cocos2d::Size &size);
    const cocos2d::Size getFileDesignSize(const char* fileName) const;
protected:
    std::string m_strFilePath;
    cocos2d::Dictionary* _fileDesignSizes;
};

class WidgetPropertiesReader : public cocos2d::Object
{
public:
    virtual gui::UIWidget* createWidget(JsonDictionary* dic, const char* fullPath, const char* fileName)=0;
    virtual gui::UIWidget* widgetFromJsonDictionary(JsonDictionary* dic) = 0;
protected:
    std::string m_strFilePath;
};


class WidgetPropertiesReader0250 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0250(){};
    virtual ~WidgetPropertiesReader0250(){};
    
    virtual gui::UIWidget* createWidget(JsonDictionary* dic, const char* fullPath, const char* fileName);
    virtual gui::UIWidget* widgetFromJsonDictionary(JsonDictionary* dic);
    virtual void setPropsForWidgetFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForButtonFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForCheckBoxFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForImageViewFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForLabelFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForLoadingBarFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForSliderFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForTextFieldFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    
    virtual void setPropsForLayoutFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForScrollViewFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
};

class WidgetPropertiesReader0300 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0300(){};
    virtual ~WidgetPropertiesReader0300(){};
    
    virtual gui::UIWidget* createWidget(JsonDictionary* dic, const char* fullPath, const char* fileName);
    virtual gui::UIWidget* widgetFromJsonDictionary(JsonDictionary* dic);
    virtual void setPropsForWidgetFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForButtonFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForCheckBoxFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForImageViewFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForLabelFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForLoadingBarFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForSliderFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForTextFieldFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    
    virtual void setPropsForLayoutFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForPageViewFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForScrollViewFromJsonDictionary(gui::UIWidget*widget,JsonDictionary* options);
    virtual void setPropsForListViewFromJsonDictionary(gui::UIWidget* widget, JsonDictionary* options);
};


}


#endif /* defined(__CCSGUIReader__) */
