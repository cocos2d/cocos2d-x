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

#include "ui/UILayout.h"
#include "cocostudio/DictionaryHelper.h"
#include "WidgetReader/WidgetReaderProtocol.h"
#include "base/ObjectFactory.h"
#include "cocostudio/CocosStudioExport.h"

namespace protocolbuffers
{
    class NodeTree;
}

namespace tinyxml2
{
    class XMLElement;
}

namespace cocostudio {
    
    class CocoLoader;
    struct stExpCocoNode;

    
#define kCCSVersion 1.0
    
    typedef void (cocos2d::Ref::*SEL_ParseEvent)(const std::string&, cocos2d::Ref*, const rapidjson::Value&);
#define parseselector(_SELECTOR) (SEL_ParseEvent)(&_SELECTOR)

class CC_STUDIO_DLL GUIReader : public cocos2d::Ref
{
public:
    CC_DEPRECATED_ATTRIBUTE static GUIReader* shareReader() { return GUIReader::getInstance(); };
    CC_DEPRECATED_ATTRIBUTE static void purgeGUIReader() { GUIReader::destroyInstance(); };

    /**
    * @~english Gets the static instance of GUIReader.
    * @~chinese 获取GUIReader的静态实例.
    */
    static GUIReader* getInstance();

    /**
    * @~english Destroy GUIReader static instance.
    * @~chinese 释放GUIReader的静态实例.
    */
    static void destroyInstance();

    /**
    * @~english Create a UI widget from file contain Json description data.
    * @~chinese 根据json描述文件的数据创建UI组件.
    *
    * @parame fileName   @~english full path of Json description file @~chinese Json描述文件全路径
    *
    * @return @~english UI widget node @~chinese UI组件节点
    */
    cocos2d::ui::Widget* widgetFromJsonFile(const char* fileName);

    /**
    * @~english Create a UI widget from file contain binary description data.
    * @~chinese 根据二进制描述文件的数据创建UI组件.
    *
    * @parame fileName   @~english full path of binary description file @~chinese 二进制描述文件全路径
    *
    * @return @~english UI widget node @~chinese UI组件节点
    */
    cocos2d::ui::Widget* widgetFromBinaryFile(const char* fileName);

    /**
    * @~english Get int value of a version string
    * @~chinese 获取版本字符串的整型值
    *
    * @parame str   @~english string value of version @~chinese 版本字符串
    *
    * @return @~english integer value of version @~chinese 版本整型值
    */
    int getVersionInteger(const char* str);

    /**
     * @~english Store design screen size
     * @~chinese 保存屏幕设计尺寸
     * @js NA
     */
    void storeFileDesignSize(const char* fileName, const cocos2d::Size &size);
    /**
     * @~english Get design screen size
     * @~chinese 获取设计屏幕尺寸
     * @js NA
     */
    const cocos2d::Size getFileDesignSize(const char* fileName) const;
    
    void setFilePath(const std::string& strFilePath) { m_strFilePath = strFilePath; }
    const std::string& getFilePath() const { return m_strFilePath; }

    /**
    * @~english Register type to ObjectFactory
    * @~chinese 向ObjectFactory注册类型
    *
    * @parame classType @~english type of class @~chinese 类型
    *
    * @parame ins       @~english Object instance of classType @~chinese 指定类型实例对象
    *
    * @parame object    @~english Reader instance @~chinese 指定类型数据读取类实例
    *
    * @parame callBack  @~english Notify call back function @~chinese 回调通知函数
    */
    void registerTypeAndCallBack(const std::string& classType,
                                 cocos2d::ObjectFactory::Instance ins,
                                 Ref* object,
                                 SEL_ParseEvent callBack);

    /**
    * @~english Register type to ObjectFactory
    * @~chinese 向ObjectFactory注册类型
    *
    * @parame classType @~english type of class @~chinese 类型
    *
    * @parame ins       @~english Object instance getter function @~chinese 指定类型实例对象获取函数
    *
    * @parame object    @~english Reader instance @~chinese 指定类型数据读取类实例
    *
    * @parame callBack  @~english Notify call back function @~chinese 回调通知函数
    */
    void registerTypeAndCallBack(const std::string& classType,
                                 cocos2d::ObjectFactory::InstanceFunc ins,
                                 Ref* object,
                                 SEL_ParseEvent callBack);
protected:
    GUIReader();
    ~GUIReader();
    
    std::string m_strFilePath;
    cocos2d::ValueMap _fileDesignSizes;
    
    typedef std::map<std::string, SEL_ParseEvent>  ParseCallBackMap;
    ParseCallBackMap _mapParseSelector;
    typedef std::map<std::string, Ref*> ParseObjectMap;
    ParseObjectMap _mapObject;
    
public:
    ParseCallBackMap* getParseCallBackMap() { return &_mapParseSelector; };
    ParseObjectMap* getParseObjectMap() { return &_mapObject; };
    
};

class CC_STUDIO_DLL WidgetPropertiesReader : public cocos2d::Ref
{
public:
    /**
    * @~english Create UI widget with json dictionary
    * @~chinese 根据json数据创建UI组件
    *
    * @parame dic       @~english Widget description data in json dictionary @~chinese json类型组件描述数据
    *
    * @parame fullPath  @~english Full path of resource forder @~chinese 资源目录全路径
    *
    * @parame fileName  @~english Full path of Json description file @~chinese Json描述文件全路径
    *
    * @return @~english UI widget node @~chinese UI组件节点
    */
    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic, const char* fullPath, const char* fileName) = 0;

    /**
    * @~english Create UI widget with json dictionary
    * @~chinese 根据json数据创建UI组件
    *
    * @parame data      @~english Widget description data in json dictionary @~chinese json类型组件描述数据
    *
    * @return @~english UI widget node @~chinese UI组件节点
    */
    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& data) = 0;

    /**
    * @~english Set widget properties from json dictionary
    * @~chinese 根据json数据设定UI组件属性
    *
    * @parame reader    @~english Custom property reader @~chinese 用户自定义属性读取类
    *
    * @parame widget    @~english UI widget to be set @~chinese 需要设置的UI组件
    *
    * @parame options   @~english Json dictionary that contain property data @~chinese 包含属性数据的json对象
    */
    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader, cocos2d::ui::Widget* widget, const rapidjson::Value& options) = 0;

    /**
    * @~english Set custom widget properties from json dictionary
    * @~chinese 根据json数据设定用户自定义UI组件属性
    *
    * @parame classType @~english Custorm class type @~chinese 自定义UI组件类型
    *
    * @parame widget    @~english Custom UI widget to be set @~chinese 需要设置的用户自定义UI组件
    *
    * @parame customOptions   @~english Json dictionary that contain custom property data @~chinese 包含用户自定义属性数据的json对象
    */
    virtual void setPropsForAllCustomWidgetFromJsonDictionary(const std::string& classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions) = 0;

    /**
    * @~english Set widget properties from binary data file
    * @~chinese 根据二进制属性描述数据设定UI组件属性
    *
    * @parame cocoLoader    @~english Property reader @~chinese 属性读取类
    *
    * @parame pCocoNode     @~english UI node to be set @~chinese 需要设置的UI节点
    *
    * @parame fileName      @~english Full path of binary file @~chinese 二进制描述文件全路径
    *
    * @return @~english UI widget node @~chinese UI组件节点
    */
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* cocoLoader, stExpCocoNode* pCocoNode, const char* fileName) = 0;
    /**
    * @~english Set widget properties from binary data file
    * @~chinese 根据二进制属性描述数据设定UI组件属性
    *
    * @parame cocoLoader    @~english Property reader @~chinese 属性读取类
    *
    * @parame pCocoNode     @~english UI node to be set @~chinese 需要设置的UI节点
    *
    * @return @~english UI widget node @~chinese UI组件节点
    */
    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* cocoLoader, stExpCocoNode*	pCocoNode) = 0;
    /**
    * @~english Set widget properties from binary data
    * @~chinese 根据二进制数据设定UI组件属性
    *
    * @parame reader    @~english Custom property reader @~chinese 用户自定义属性读取类
    *
    * @parame widget    @~english UI widget to be set @~chinese 需要设置的UI组件
    *
    * @parame cocoLoader   @~english Binary data reader @~chinese 二进制数据读取类
    *
    * @parame pCocoNode    @~english Custom expand node @~chinese 用户自定义扩展节点
    */
    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* cocoLoader,
                                                stExpCocoNode* pCocoNode) = 0;
    
protected:
    void setAnchorPointForWidget(cocos2d::ui::Widget* widget, const rapidjson::Value&options);
    std::string  getWidgetReaderClassName(const std::string& classname);
    std::string  getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
    std::string getGUIClassName(const std::string& name);
    cocos2d::ui::Widget *createGUI(const std::string& classname);
    WidgetReaderProtocol* createWidgetReaderProtocol(const std::string& classname);
    
protected:
    std::string m_strFilePath;
};


class CC_STUDIO_DLL WidgetPropertiesReader0250 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0250(){};
    virtual ~WidgetPropertiesReader0250(){};
    
    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic, const char* fullPath, const char* fileName) override;

    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& dic) override;
    
    //added for binary parsing
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* cocoLoader,
                                                        stExpCocoNode*	pCocoNode,
                                                        const char* fileName)override{return nullptr;}
    
    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* cocoLoader,
                                                  stExpCocoNode*	pCocoNode) override {return nullptr;}
    
    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* cocoLoader,
                                                stExpCocoNode*	pCocoNode) override {}

    virtual void setPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    
    virtual void setColorPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForButtonFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForCheckBoxFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForImageViewFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelAtlasFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLabelBMFontFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForLoadingBarFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForSliderFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForTextFieldFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    
    virtual void setPropsForLayoutFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    virtual void setPropsForScrollViewFromJsonDictionary(cocos2d::ui::Widget* widget,const rapidjson::Value& options);
    
    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader, cocos2d::ui::Widget* widget, const rapidjson::Value& options) override;
    virtual void setPropsForAllCustomWidgetFromJsonDictionary(const std::string& classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions) override;
};
   
class CC_STUDIO_DLL WidgetPropertiesReader0300 : public WidgetPropertiesReader
{
    
    
public:
    WidgetPropertiesReader0300(){};
    virtual ~WidgetPropertiesReader0300(){};
    
    virtual cocos2d::ui::Widget* createWidget(const rapidjson::Value& dic,
                                              const char* fullPath,
                                              const char* fileName) override;
    
    
    //add bin parse support
    virtual cocos2d::ui::Widget* createWidgetFromBinary(CocoLoader* cocoLoader,
                                                        stExpCocoNode*	pCocoNode,
                                                        const char* fileName)override;
    
    virtual cocos2d::ui::Widget* widgetFromBinary(CocoLoader* cocoLoader,
                                                  stExpCocoNode*	pCocoNode) override;
    
    virtual void setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                cocos2d::ui::Widget* widget,
                                                CocoLoader* cocoLoader,
                                                stExpCocoNode*	pCocoNode) override;
    
    virtual void setPropsForAllCustomWidgetFromBinary(const std::string& classType,
                                                      cocos2d::ui::Widget* widget,
                                                      CocoLoader* cocoLoader,
                                                      stExpCocoNode*	pCocoNode) {
        //TODO: custom property
    }
    
    virtual cocos2d::ui::Widget* widgetFromJsonDictionary(const rapidjson::Value& dic) override;
    
    virtual void setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol* reader,
                                                        cocos2d::ui::Widget* widget,
                                                        const rapidjson::Value& options) override;
    
    virtual void setPropsForAllCustomWidgetFromJsonDictionary(const std::string& classType,
                                                              cocos2d::ui::Widget* widget,
                                                              const rapidjson::Value& customOptions) override;        
};


}


#endif /* defined(__CCSGUIReader__) */
