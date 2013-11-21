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
/**
*   @js NA
*   @lua NA
*/
class GUIReader : public CCObject
{
public:
    GUIReader();
    ~GUIReader();
    static GUIReader* shareReader();
	static void purgeGUIReader();
    
    UIWidget* widgetFromJsonFile(const char* fileName);
    int getVersionInteger(const char* str);
    void storeFileDesignSize(const char* fileName, const cocos2d::CCSize &size);
    const cocos2d::CCSize getFileDesignSize(const char* fileName) const;
protected:
    std::string m_strFilePath;
    CCDictionary* _fileDesignSizes;
};

class WidgetPropertiesReader : public CCObject
{
public:
    virtual UIWidget* createWidget(cs::CSJsonDictionary* dic, const char* fullPath, const char* fileName)=0;
    virtual UIWidget* widgetFromJsonDictionary(cs::CSJsonDictionary* dic) = 0;
protected:
    std::string m_strFilePath;
};


class WidgetPropertiesReader0250 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0250(){};
    virtual ~WidgetPropertiesReader0250(){};
    
    virtual UIWidget* createWidget(cs::CSJsonDictionary* dic, const char* fullPath, const char* fileName);
    virtual UIWidget* widgetFromJsonDictionary(cs::CSJsonDictionary* dic);
    virtual void setPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForButtonFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForCheckBoxFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForImageViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForLabelFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForLoadingBarFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForSliderFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForTextFieldFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    
    virtual void setPropsForLayoutFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForScrollViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
};

class WidgetPropertiesReader0300 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0300(){};
    virtual ~WidgetPropertiesReader0300(){};
    
    virtual UIWidget* createWidget(cs::CSJsonDictionary* dic, const char* fullPath, const char* fileName);
    virtual UIWidget* widgetFromJsonDictionary(cs::CSJsonDictionary* dic);
    virtual void setPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForButtonFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForCheckBoxFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForImageViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForLabelFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForLoadingBarFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForSliderFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForTextFieldFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    
    virtual void setPropsForLayoutFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForPageViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForScrollViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options);
    virtual void setPropsForListViewFromJsonDictionary(UIWidget* widget, cs::CSJsonDictionary* options);
};

NS_CC_EXT_END


#endif /* defined(__CCSGUIReader__) */
