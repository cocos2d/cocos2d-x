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
#include "../Json/rapidjson/document.h"
#include "cocos-ext.h"
#include "WidgetReader/WidgetReaderProtocol.h"
#include "../Trigger/ObjectFactory.h"
#include "../Json/CocoLoader.h"

NS_CC_EXT_BEGIN

typedef void (CCObject::*SEL_ParseEvent)(const std::string&, CCObject*, const rapidjson::Value&);
#define parseselector(_SELECTOR) (SEL_ParseEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_ParseEventBinary)(const std::string&, CCObject*, CocoLoader* pCocoLoader,
                                               stExpCocoNode*	pCocoNode);
#define parsebinaryselector(_SELECTOR) (SEL_ParseEventBinary)(&_SELECTOR)


#define kCCSVersion 1.0
/**
 *   @js NA
 *   @lua NA
 */
class CC_EX_DLL GUIReader : public CCObject
{
public:
	/**
     *  @js ctor
     */
    GUIReader();
	/**
     *  @js NA
     */
    ~GUIReader();
	/**
     *  @js getInstance
     */
    static GUIReader* shareReader();
    /**
     *  @js pure
     */
	static void purge();
    
    cocos2d::ui::Widget* widgetFromJsonFile(const char* fileName);
    cocos2d::ui::Widget* widgetFromBinaryFile(const char* fileName);

    int getVersionInteger(const char* str);
    void storeFileDesignSize(const char* fileName, const cocos2d::CCSize &size);
    const cocos2d::CCSize getFileDesignSize(const char* fileName) const;
    
    void setFilePath(const std::string& strFilePath) { m_strFilePath = strFilePath; }
    const std::string& getFilePath() const { return m_strFilePath; };
    
    void registerTypeAndCallBack(const std::string& classType,
                                 ObjectFactory::Instance ins,
                                 CCObject* object,
                                 SEL_ParseEvent callBack);
protected:
    std::string m_strFilePath;
    CCDictionary* _fileDesignSizes;
    
    typedef std::map<std::string, SEL_ParseEvent>  ParseCallBackMap;
    ParseCallBackMap _mapParseSelector;
    typedef std::map<std::string, CCObject*> ParseObjectMap;
    ParseObjectMap _mapObject;
    
public:
    ParseCallBackMap getParseCallBackMap() { return _mapParseSelector; };
    ParseObjectMap getParseObjectMap() { return _mapObject; };
};

class WidgetPropertiesReader : public CCObject
{
public:
    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic,
                                              const char* fullPath,
                                              const char* fileName)=0;
    
    
    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& data) = 0;
    
    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader,
                                                        cocos2d::ui::Widget* widget,
                                                        const rapidjson::Value& options) = 0;
    
    virtual void setPropsForAllCustomWidgetFromJsonDictionary(const std::string& classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions) = 0;
    
    //add binary parsing
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* pCocoLoader,
                                                        stExpCocoNode*	pCocoNode,
                                                        const char* fileName)=0;
    
    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* pCocoLoader,
                                                  stExpCocoNode*	pCocoNode) = 0;
    
    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* pCocoLoader,
                                                stExpCocoNode*	pCocoNode) = 0;
    
//    virtual void setPropsForAllCustomWidgetFromBinary(const std::string& classType,
//                                                      cocos2d::ui::Widget* widget,
//                                                      CocoLoader* pCocoLoader,
//                                                      stExpCocoNode*	pCocoNode) = 0;
    
protected:
    std::string  getWidgetReaderClassName(const std::string& classname);
    std::string  getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
    std::string getGUIClassName(const std::string& name);
    cocos2d::ui::Widget *createGUI(const std::string& classname);
    WidgetReaderProtocol* createWidgetReaderProtocol(const std::string& classname);
    
    std::string m_strFilePath;
};



/**
 *  @js NA
 *  @lua NA
 */
class WidgetPropertiesReader0250 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0250(){};
    virtual ~WidgetPropertiesReader0250(){};
    
    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic, const char* fullPath, const char* fileName);
    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& dic);
    virtual void setPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForButtonFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForCheckBoxFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForImageViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForLabelFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForLoadingBarFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForSliderFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForTextFieldFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    
    virtual void setPropsForLayoutFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForScrollViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    
    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader, cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    
    virtual void setPropsForAllCustomWidgetFromJsonDictionary(const std::string& classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions);
    
    //added for binary parsing
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* pCocoLoader,
                                                        stExpCocoNode*	pCocoNode,
                                                        const char* fileName){return NULL;}
    
    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* pCocoLoader,
                                                  stExpCocoNode*	pCocoNode){return NULL;}
    
    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* pCocoLoader,
                                                stExpCocoNode*	pCocoNode) {}
    
};

/**
 *  @js NA
 *  @lua NA
 */
class WidgetPropertiesReader0300 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0300(){};
    virtual ~WidgetPropertiesReader0300(){};
    
    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic, const char* fullPath, const char* fileName);
    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& dic);
    virtual void setPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForButtonFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForCheckBoxFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForImageViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForLabelFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForLoadingBarFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForSliderFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForTextFieldFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    
    virtual void setPropsForLayoutFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForPageViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForScrollViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options);
    virtual void setPropsForListViewFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    
    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader, cocos2d::ui::Widget* widget, const rapidjson::Value& options);
    
    virtual void setPropsForAllCustomWidgetFromJsonDictionary(const std::string& classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions);
    
    
    //added for binary parsing
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* pCocoLoader,
                                                        stExpCocoNode*	pCocoNode,
                                                        const char* fileName);
    
    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* pCocoLoader,
                                                  stExpCocoNode*	pCocoNode);
    
    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* pCocoLoader,
                                                stExpCocoNode*	pCocoNode);
    
};

NS_CC_EXT_END


#endif /* defined(__CCSGUIReader__) */
