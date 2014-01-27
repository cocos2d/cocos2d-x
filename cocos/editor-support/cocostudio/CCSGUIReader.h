/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "cocostudio/DictionaryHelper.h"

namespace cocostudio {

#define kCCSVersion 1.0

class GUIReader : public cocos2d::Object
{
public:
    CC_DEPRECATED_ATTRIBUTE static GUIReader* shareReader() { return GUIReader::getInstance(); };
    CC_DEPRECATED_ATTRIBUTE static void purgeGUIReader() { GUIReader::destroyInstance(); };
    
    static GUIReader* getInstance();
    static void destroyInstance();
    
    cocos2d::gui::Widget* widgetFromJsonFile(const char* fileName);
    int getVersionInteger(const char* str);
    /**
     *  @js NA
     */
    void storeFileDesignSize(const char* fileName, const cocos2d::Size &size);
    /**
     *  @js NA
     */
    const cocos2d::Size getFileDesignSize(const char* fileName) const;
    
protected:
    GUIReader();
    ~GUIReader();
    
    std::string m_strFilePath;
    cocos2d::ValueMap _fileDesignSizes;
    
};

class WidgetPropertiesReader : public cocos2d::Object
{
public:
    virtual cocos2d::gui::Widget* createWidget(const rapidjson::Value& dic, const char* fullPath, const char* fileName)=0;
    virtual cocos2d::gui::Widget* widgetFromJsonDictionary(const rapidjson::Value& data) = 0;
protected:
    std::string m_strFilePath;
};


class WidgetPropertiesReader0250 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0250(){};
    virtual ~WidgetPropertiesReader0250(){};
    
    virtual cocos2d::gui::Widget* createWidget(const rapidjson::Value& dic, const char* fullPath, const char* fileName);
    virtual cocos2d::gui::Widget* widgetFromJsonDictionary(const rapidjson::Value& dic);
    virtual void setPropsForWidgetFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForButtonFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForCheckBoxFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForImageViewFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLoadingBarFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForSliderFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForTextFieldFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    
    virtual void setPropsForLayoutFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForScrollViewFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
};

class WidgetPropertiesReader0300 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0300(){};
    virtual ~WidgetPropertiesReader0300(){};
    
    virtual cocos2d::gui::Widget* createWidget(const rapidjson::Value& dic, const char* fullPath, const char* fileName);
    virtual cocos2d::gui::Widget* widgetFromJsonDictionary(const rapidjson::Value& dic);
    virtual void setPropsForWidgetFromJsonDictionary(cocos2d::gui::Widget*,const rapidjson::Value& options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForButtonFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForCheckBoxFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForImageViewFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLoadingBarFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForSliderFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForTextFieldFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    
    virtual void setPropsForLayoutFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForPageViewFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForScrollViewFromJsonDictionary(cocos2d::gui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForListViewFromJsonDictionary(cocos2d::gui::Widget* widget, const rapidjson::Value& options);
};


}


#endif /* defined(__CCSGUIReader__) */
