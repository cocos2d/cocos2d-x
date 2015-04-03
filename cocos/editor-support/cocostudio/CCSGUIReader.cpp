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
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CCActionManagerEx.h"
#include <fstream>
#include <iostream>
#include "WidgetReader/ButtonReader/ButtonReader.h"
#include "WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "WidgetReader/SliderReader/SliderReader.h"
#include "WidgetReader/ImageViewReader/ImageViewReader.h"
#include "WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "WidgetReader/TextAtlasReader/TextAtlasReader.h"
#include "WidgetReader/TextReader/TextReader.h"
#include "WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "WidgetReader/TextFieldReader/TextFieldReader.h"
#include "WidgetReader/LayoutReader/LayoutReader.h"
#include "WidgetReader/PageViewReader/PageViewReader.h"
#include "WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "WidgetReader/ListViewReader/ListViewReader.h"
#include "cocostudio/CocoLoader.h"
#include "ui/CocosGUI.h"
#include "tinyxml2.h"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace cocostudio {
    
static GUIReader* sharedReader = nullptr;

GUIReader::GUIReader():
m_strFilePath("")
{
    ObjectFactory* factoryCreate = ObjectFactory::getInstance();
    
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(ButtonReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(CheckBoxReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(SliderReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(ImageViewReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(LoadingBarReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(TextAtlasReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(TextReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(TextBMFontReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(TextFieldReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(LayoutReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(PageViewReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(ScrollViewReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(ListViewReader));
    
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(Button));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(CheckBox));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(ImageView));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(Text));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(TextAtlas));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(TextBMFont));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(LoadingBar));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(Slider));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(TextField));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(Layout));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(ListView));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(PageView));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(ScrollView));
}

GUIReader::~GUIReader()
{
}

GUIReader* GUIReader::getInstance()
{
    if (!sharedReader)
    {
        sharedReader = new (std::nothrow) GUIReader();
    }
    return sharedReader;
}

void GUIReader::destroyInstance()
{
    CC_SAFE_DELETE(sharedReader);
}

int GUIReader::getVersionInteger(const char *str)
{
    std::string strVersion = str;
    size_t length = strVersion.length();
    if (length < 7)
    {
        return 0;
    }
    size_t pos = strVersion.find_first_of(".");
    std::string t = strVersion.substr(0,pos);
    strVersion = strVersion.substr(pos+1,strVersion.length()-1);
    
    pos = strVersion.find_first_of(".");
    std::string h = strVersion.substr(0,pos);
    strVersion = strVersion.substr(pos+1,strVersion.length()-1);
    
    pos = strVersion.find_first_of(".");
    std::string te = strVersion.substr(0,pos);
    strVersion = strVersion.substr(pos+1,strVersion.length()-1);
    
    pos = strVersion.find_first_of(".");
    std::string s = strVersion.substr(0,pos);
    
    int it = atoi(t.c_str());
    int ih = atoi(h.c_str());
    int ite = atoi(te.c_str());
    int is = atoi(s.c_str());
    
    int iVersion = it*1000+ih*100+ite*10+is;
//    CCLOG("iversion %d",iVersion);
    return iVersion;
    /************************/
}

void GUIReader::storeFileDesignSize(const char *fileName, const cocos2d::Size &size)
{
    std::string keyWidth = fileName;
    keyWidth.append("width");
    std::string keyHeight = fileName;
    keyHeight.append("height");
    _fileDesignSizes[keyWidth] = cocos2d::Value(size.width);
    _fileDesignSizes[keyHeight] = cocos2d::Value(size.height);
}

const cocos2d::Size GUIReader::getFileDesignSize(const char* fileName) const
{
    std::string keyWidth = fileName;
    keyWidth.append("width");
    std::string keyHeight = fileName;
    keyHeight.append("height");
    float w = _fileDesignSizes.at(keyWidth).asFloat();
    float h = _fileDesignSizes.at(keyHeight).asFloat();
    return Size(w, h);
}
    
void GUIReader::registerTypeAndCallBack(const std::string& classType,
                                        ObjectFactory::Instance ins,
                                        Ref *object,
                                        SEL_ParseEvent callBack)
{
    ObjectFactory* factoryCreate = ObjectFactory::getInstance();
    
    ObjectFactory::TInfo t(classType, ins);
    factoryCreate->registerType(t);
    
    if (object)
    {
        _mapObject.insert(ParseObjectMap::value_type(classType, object));
    }
    
    if (callBack)
    {
        _mapParseSelector.insert(ParseCallBackMap::value_type(classType, callBack));
    }
}

void GUIReader::registerTypeAndCallBack(const std::string& classType,
                                        ObjectFactory::InstanceFunc ins,
                                        Ref *object,
                                        SEL_ParseEvent callBack)
{
    ObjectFactory* factoryCreate = ObjectFactory::getInstance();

    ObjectFactory::TInfo t(classType, ins);
    factoryCreate->registerType(t);

    if (object)
    {
        _mapObject.insert(ParseObjectMap::value_type(classType, object));
    }

    if (callBack)
    {
        _mapParseSelector.insert(ParseCallBackMap::value_type(classType, callBack));
    }
}


Widget* GUIReader::widgetFromJsonFile(const char *fileName)
{
	std::string jsonpath;
	rapidjson::Document jsonDict;
    jsonpath = fileName;
//    jsonpath = CCFileUtils::getInstance()->fullPathForFilename(fileName);
    size_t pos = jsonpath.find_last_of('/');
	m_strFilePath = jsonpath.substr(0,pos+1);
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
	jsonDict.Parse<0>(contentStr.c_str());
    if (jsonDict.HasParseError())
    {
        CCLOG("GetParseError %s\n",jsonDict.GetParseError());
    }
    Widget* widget = nullptr;
    const char* fileVersion = DICTOOL->getStringValue_json(jsonDict, "version");
    WidgetPropertiesReader * pReader = nullptr;
    if (fileVersion)
    {
        int versionInteger = getVersionInteger(fileVersion);
        if (versionInteger < 250)
        {
            pReader = new (std::nothrow) WidgetPropertiesReader0250();
            widget = pReader->createWidget(jsonDict, m_strFilePath.c_str(), fileName);
        }
        else
        {
            pReader = new (std::nothrow) WidgetPropertiesReader0300();
            widget = pReader->createWidget(jsonDict, m_strFilePath.c_str(), fileName);
        }
    }
    else
    {
        pReader = new (std::nothrow) WidgetPropertiesReader0250();
        widget = pReader->createWidget(jsonDict, m_strFilePath.c_str(), fileName);
    }
    
    CC_SAFE_DELETE(pReader);
    return widget;
}
    
std::string WidgetPropertiesReader::getWidgetReaderClassName(Widget* widget)
{
    std::string readerName;
    
    // 1st., custom widget parse properties of parent widget with parent widget reader
    if (dynamic_cast<Button*>(widget))
    {
        readerName = "ButtonReader";
    }
    else if (dynamic_cast<CheckBox*>(widget))
    {
        readerName = "CheckBoxReader";
    }
    else if (dynamic_cast<ImageView*>(widget))
    {
        readerName = "ImageViewReader";
    }
    else if (dynamic_cast<TextAtlas*>(widget))
    {
        readerName = "TextAtlasReader";
    }
    else if (dynamic_cast<TextBMFont*>(widget))
    {
        readerName = "TextBMFontReader";
    }
    else if (dynamic_cast<Text*>(widget))
    {
        readerName = "TextReader";
    }
    else if (dynamic_cast<LoadingBar*>(widget))
    {
        readerName = "LoadingBarReader";
    }
    else if (dynamic_cast<Slider*>(widget))
    {
        readerName = "SliderReader";
    }
    else if (dynamic_cast<TextField*>(widget))
    {
        readerName = "TextFieldReader";
    }
    else if (dynamic_cast<ListView*>(widget))
    {
        readerName = "ListViewReader";
    }
    else if (dynamic_cast<PageView*>(widget))
    {
        readerName = "PageViewReader";
    }
    else if (dynamic_cast<ScrollView*>(widget))
    {
        readerName = "ScrollViewReader";
    }
  
    else if (dynamic_cast<Layout*>(widget))
    {
        readerName = "LayoutReader";
    }
    else if (dynamic_cast<Widget*>(widget))
    {
        readerName = "WidgetReader";
    }
    
    return readerName;
}


std::string WidgetPropertiesReader::getGUIClassName(const std::string &name)
{
    std::string convertedClassName = name;
    if (name == "Panel")
    {
        convertedClassName = "Layout";
    }
    else if (name == "TextArea")
    {
        convertedClassName = "Text";
    }
    else if (name == "TextButton")
    {
        convertedClassName = "Button";
    }
    else if (name == "Label")
    {
        convertedClassName = "Text";
    }
    else if (name == "LabelAtlas")
    {
        convertedClassName = "TextAtlas";
    }
    else if (name == "LabelBMFont")
    {
        convertedClassName = "TextBMFont";
    }
   
    
    return convertedClassName;
}
    
cocos2d::ui::Widget* WidgetPropertiesReader::createGUI(const std::string &classname)
{
    std::string name = this->getGUIClassName(classname);

    Ref* object = ObjectFactory::getInstance()->createObject(name);
    
    return dynamic_cast<ui::Widget*>(object);
}

WidgetReaderProtocol* WidgetPropertiesReader::createWidgetReaderProtocol(const std::string &classname)
{
    Ref* object = ObjectFactory::getInstance()->createObject(classname);
    
    return dynamic_cast<WidgetReaderProtocol*>(object);
}

Widget* GUIReader::widgetFromBinaryFile(const char *fileName)
{
    std::string jsonpath;
    rapidjson::Document jsonDict;
    jsonpath = fileName;
//    jsonpath = CCFileUtils::getInstance()->fullPathForFilename(fileName);
    size_t pos = jsonpath.find_last_of('/');
    m_strFilePath = jsonpath.substr(0,pos+1);
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto fileData = FileUtils::getInstance()->getDataFromFile(fullPath);
    auto fileDataBytes = fileData.getBytes();
    auto fileDataSize = fileData.getSize();
    
    const char* fileVersion = "";
    ui::Widget* widget = nullptr;

    if (fileDataBytes != nullptr && fileDataSize > 0)
    {
        CocoLoader	tCocoLoader;
        if(true == tCocoLoader.ReadCocoBinBuff((char*)fileDataBytes))
        {
            stExpCocoNode*	tpRootCocoNode = tCocoLoader.GetRootCocoNode();
            
            rapidjson::Type tType = tpRootCocoNode->GetType(&tCocoLoader);
            if (rapidjson::kObjectType == tType || rapidjson::kArrayType == tType)
            {
                stExpCocoNode *tpChildArray = tpRootCocoNode->GetChildArray(&tCocoLoader);
                
                
                for (int i = 0; i < tpRootCocoNode->GetChildNum(); ++i) {
                    std::string key = tpChildArray[i].GetName(&tCocoLoader);
                    if (key == "version") {
                        fileVersion = tpChildArray[i].GetValue(&tCocoLoader);
                        break;
                    }
                }
                
                WidgetPropertiesReader * pReader = nullptr;
                if (fileVersion)
                {
                    int versionInteger = getVersionInteger(fileVersion);
                    if (versionInteger < 250)
                    {
                        CCASSERT(0, "You current studio doesn't support binary format, please upgrade to the latest version!");
                        pReader = new (std::nothrow) WidgetPropertiesReader0250();
                        widget = pReader->createWidgetFromBinary(&tCocoLoader, tpRootCocoNode, fileName);
                    }
                    else
                    {
                        pReader = new (std::nothrow) WidgetPropertiesReader0300();
                        widget = pReader->createWidgetFromBinary(&tCocoLoader, tpRootCocoNode, fileName);
                    }
                }
                else
                {
                    pReader = new (std::nothrow) WidgetPropertiesReader0250();
                    widget = pReader->createWidgetFromBinary(&tCocoLoader, tpRootCocoNode, fileName);
                }
                
                CC_SAFE_DELETE(pReader);

            }
        }
    }
    
    return widget;
   
}

std::string  WidgetPropertiesReader::getWidgetReaderClassName(const std::string& classname)
{
    // create widget reader to parse properties of widget
    std::string readerName = classname;
    if (readerName == "Panel")
    {
        readerName = "Layout";
    }
    else if (readerName == "TextArea")
    {
        readerName = "Text";
    }
    else if (readerName == "TextButton")
    {
        readerName = "Button";
    }
    else if (readerName == "Label")
    {
        readerName = "Text";
    }
    else if (readerName == "LabelAtlas")
    {
        readerName = "TextAtlas";
    }
    else if (readerName == "LabelBMFont")
    {
        readerName = "TextBMFont";
    }
    readerName.append("Reader");
    return readerName;
}

void WidgetPropertiesReader::setAnchorPointForWidget(cocos2d::ui::Widget *widget, const rapidjson::Value &options)
{
    bool isAnchorPointXExists = DICTOOL->checkObjectExist_json(options, "anchorPointX");
    float anchorPointXInFile;
    if (isAnchorPointXExists) {
        anchorPointXInFile = DICTOOL->getFloatValue_json(options, "anchorPointX");
    }else{
        anchorPointXInFile = widget->getAnchorPoint().x;
    }
    
    bool isAnchorPointYExists = DICTOOL->checkObjectExist_json(options, "anchorPointY");
    float anchorPointYInFile;
    if (isAnchorPointYExists) {
        anchorPointYInFile = DICTOOL->getFloatValue_json(options, "anchorPointY");
    }
    else{
        anchorPointYInFile = widget->getAnchorPoint().y;
    }
    
    if (isAnchorPointXExists || isAnchorPointYExists) {
        widget->setAnchorPoint(Vec2(anchorPointXInFile, anchorPointYInFile));
    }
}

     

Widget* WidgetPropertiesReader0250::createWidget(const rapidjson::Value& data, const char* fullPath, const char* fileName)
{
    m_strFilePath = fullPath;
    int texturesCount = DICTOOL->getArrayCount_json(data, "textures");
    
    for (int i=0; i<texturesCount; i++)
    {
        const char* file = DICTOOL->getStringValueFromArray_json(data, "textures", i);
        std::string tp = fullPath;
        tp.append(file);
        CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile(tp.c_str());
    }
    float fileDesignWidth = DICTOOL->getFloatValue_json(data, "designWidth");
    float fileDesignHeight = DICTOOL->getFloatValue_json(data, "designHeight");
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
        CCLOGERROR("Read design size error!\n");
        Size winSize = Director::getInstance()->getWinSize();
        GUIReader::getInstance()->storeFileDesignSize(fileName, winSize);
    }
    else
    {
        GUIReader::getInstance()->storeFileDesignSize(fileName, Size(fileDesignWidth, fileDesignHeight));
    }
    const rapidjson::Value& widgetTree = DICTOOL->getSubDictionary_json(data, "widgetTree");
    Widget* widget = widgetFromJsonDictionary(widgetTree);
    
    /* *********temp********* */
    if (widget->getContentSize().equals(Size::ZERO))
    {
        Layout* rootWidget = dynamic_cast<Layout*>(widget);
        rootWidget->setContentSize(Size(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    //    widget->setFileDesignSize(Size(fileDesignWidth, fileDesignHeight));
    const rapidjson::Value& actions = DICTOOL->getSubDictionary_json(data, "animation");
    /* *********temp********* */
    //    ActionManager::getInstance()->releaseActions();
    /* ********************** */
//    CCLOG("file name == [%s]",fileName);
    Ref* rootWidget = (Ref*) widget;
    ActionManagerEx::getInstance()->initWithDictionary(fileName,actions,rootWidget);
    return widget;
}


Widget* WidgetPropertiesReader0250::widgetFromJsonDictionary(const rapidjson::Value&data)
{
    Widget* widget = nullptr;
    const char* classname = DICTOOL->getStringValue_json(data, "classname");
    const rapidjson::Value& uiOptions = DICTOOL->getSubDictionary_json(data, "options");
    if (classname && strcmp(classname, "Button") == 0)
    {
        widget = cocos2d::ui::Button::create();
        setPropsForButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "CheckBox") == 0)
    {
        widget = CheckBox::create();
        setPropsForCheckBoxFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Label") == 0)
    {
        widget = cocos2d::ui::Text::create();
        setPropsForLabelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelAtlas") == 0)
    {
        widget = cocos2d::ui::TextAtlas::create();
        setPropsForLabelAtlasFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LoadingBar") == 0)
    {
        widget = cocos2d::ui::LoadingBar::create();
        setPropsForLoadingBarFromJsonDictionary(widget, uiOptions);
    }else if (classname && strcmp(classname, "ScrollView") == 0){
        widget = cocos2d::ui::ScrollView::create();
        setPropsForScrollViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextArea") == 0)
    {
        widget = cocos2d::ui::Text::create();
        setPropsForLabelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextButton") == 0)
    {
        widget = cocos2d::ui::Button::create();
        setPropsForButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextField") == 0)
    {
        widget = cocos2d::ui::TextField::create();
        setPropsForTextFieldFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "ImageView") == 0)
    {
        widget = cocos2d::ui::ImageView::create();
        setPropsForImageViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Panel") == 0)
    {
        widget = Layout::create();
        setPropsForLayoutFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Slider") == 0)
    {
        widget = cocos2d::ui::Slider::create();
        setPropsForSliderFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelBMFont") == 0)
    {
        widget = cocos2d::ui::TextBMFont::create();
        setPropsForLabelBMFontFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "DragPanel") == 0)
    {
        widget = cocos2d::ui::ScrollView::create();
        setPropsForScrollViewFromJsonDictionary(widget, uiOptions);
    }
    
    int childrenCount = DICTOOL->getArrayCount_json(data, "children");
    for (int i=0;i<childrenCount;i++)
    {
        const rapidjson::Value& subData = DICTOOL->getDictionaryFromArray_json(data, "children", i);
        Widget* child = widgetFromJsonDictionary(subData);
        if (child)
        {
            widget->addChild(child);
        }
    }
    
    return widget;
}

void WidgetPropertiesReader0250::setPropsForWidgetFromJsonDictionary(Widget*widget,const rapidjson::Value&options)
{
    bool ignoreSizeExsit = DICTOOL->checkObjectExist_json(options, "ignoreSize");
    if (ignoreSizeExsit)
    {
        widget->ignoreContentAdaptWithSize(DICTOOL->getBooleanValue_json(options, "ignoreSize"));
    }
    
    float w = DICTOOL->getFloatValue_json(options, "width");
    float h = DICTOOL->getFloatValue_json(options, "height");
    widget->setContentSize(Size(w, h));
    
    widget->setTag(DICTOOL->getIntValue_json(options, "tag"));
	widget->setActionTag(DICTOOL->getIntValue_json(options, "actiontag"));
    widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, "touchAble"));
    const char* name = DICTOOL->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = DICTOOL->getFloatValue_json(options, "x");
    float y = DICTOOL->getFloatValue_json(options, "y");
    widget->setPosition(Vec2(x,y));
    bool sx = DICTOOL->checkObjectExist_json(options, "scaleX");
    if (sx)
    {
        widget->setScaleX(DICTOOL->getFloatValue_json(options, "scaleX"));
    }
    bool sy = DICTOOL->checkObjectExist_json(options, "scaleY");
    if (sy)
    {
        widget->setScaleY(DICTOOL->getFloatValue_json(options, "scaleY"));
    }
    bool rt = DICTOOL->checkObjectExist_json(options, "rotation");
    if (rt)
    {
        widget->setRotation(DICTOOL->getFloatValue_json(options, "rotation"));
    }
    bool vb = DICTOOL->checkObjectExist_json(options, "visible");
    if (vb)
    {
        widget->setVisible(DICTOOL->getBooleanValue_json(options, "visible"));
    }
    int z = DICTOOL->getIntValue_json(options, "ZOrder");
    widget->setLocalZOrder(z);
}

void WidgetPropertiesReader0250::setColorPropsForWidgetFromJsonDictionary(Widget *widget, const rapidjson::Value&options)
{
    bool op = DICTOOL->checkObjectExist_json(options, "opacity");
    if (op)
    {
        widget->setOpacity(DICTOOL->getIntValue_json(options, "opacity"));
    }
    bool cr = DICTOOL->checkObjectExist_json(options, "colorR");
    bool cg = DICTOOL->checkObjectExist_json(options, "colorG");
    bool cb = DICTOOL->checkObjectExist_json(options, "colorB");
    int colorR = cr ? DICTOOL->getIntValue_json(options, "colorR") : 255;
    int colorG = cg ? DICTOOL->getIntValue_json(options, "colorG") : 255;
    int colorB = cb ? DICTOOL->getIntValue_json(options, "colorB") : 255;
    widget->setColor(Color3B(colorR, colorG, colorB));
    
    this->setAnchorPointForWidget(widget, options);
    
    bool flipX = DICTOOL->getBooleanValue_json(options, "flipX");
    bool flipY = DICTOOL->getBooleanValue_json(options, "flipY");
    widget->setFlippedX(flipX);
    widget->setFlippedY(flipY);
}

void WidgetPropertiesReader0250::setPropsForButtonFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Button* button = static_cast<Button*>(widget);
    bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
    button->setScale9Enabled(scale9Enable);
    
    std::string tp_n = m_strFilePath;
    std::string tp_p = m_strFilePath;
    std::string tp_d = m_strFilePath;
    
    const char* normalFileName = DICTOOL->getStringValue_json(options, "normal");
    const char* pressedFileName = DICTOOL->getStringValue_json(options, "pressed");
    const char* disabledFileName = DICTOOL->getStringValue_json(options, "disabled");
    
    const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
    const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
    const char* disabledFileName_tp =  (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    if (scale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        
        if (useMergedTexture)
        {
            button->loadTextures(normalFileName, pressedFileName, disabledFileName,TextureResType::PLIST);
        }
        else
        {
            button->loadTextures(normalFileName_tp, pressedFileName_tp, disabledFileName_tp);
        }
        button->setCapInsets(Rect(cx, cy, cw, ch));
        bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
        bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
            float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
            button->setContentSize(Size(swf, shf));
        }
    }
    else
    {
        if (useMergedTexture)
        {
            button->loadTextures(normalFileName, pressedFileName, disabledFileName,TextureResType::PLIST);
        }
        else
        {
            button->loadTextures(normalFileName_tp, pressedFileName_tp, disabledFileName_tp);
        }
    }
    bool tt = DICTOOL->checkObjectExist_json(options, "text");
    if (tt)
    {
        const char* text = DICTOOL->getStringValue_json(options, "text");
        if (text)
        {
            button->setTitleText(text);
        }
    }
    bool cr = DICTOOL->checkObjectExist_json(options, "textColorR");
    bool cg = DICTOOL->checkObjectExist_json(options, "textColorG");
    bool cb = DICTOOL->checkObjectExist_json(options, "textColorB");
    int cri = cr?DICTOOL->getIntValue_json(options, "textColorR"):255;
    int cgi = cg?DICTOOL->getIntValue_json(options, "textColorG"):255;
    int cbi = cb?DICTOOL->getIntValue_json(options, "textColorB"):255;
    button->setTitleColor(Color3B(cri,cgi,cbi));
    bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        button->setTitleFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
    }
    bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        button->setTitleFontName(DICTOOL->getStringValue_json(options, "fontName"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForCheckBoxFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    CheckBox* checkBox = static_cast<CheckBox*>(widget);
    const char* backGroundFileName = DICTOOL->getStringValue_json(options, "backGroundBox");
    const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(options, "backGroundBoxSelected");
    const char* frontCrossFileName = DICTOOL->getStringValue_json(options, "frontCross");
    const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(options, "backGroundBoxDisabled");
    const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "frontCrossDisabled");
    
    std::string tp_b = m_strFilePath;
    std::string tp_bs = m_strFilePath;
    std::string tp_c = m_strFilePath;
    std::string tp_bd = m_strFilePath;
    std::string tp_cd = m_strFilePath;
    
    const char* backGroundFileName_tp = (backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():nullptr;
    const char* backGroundSelectedFileName_tp = (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():nullptr;
    const char* frontCrossFileName_tp = (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():nullptr;
    const char* backGroundDisabledFileName_tp = (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():nullptr;
    const char* frontCrossDisabledFileName_tp = (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():nullptr;
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    
    if (useMergedTexture)
    {
        checkBox->loadTextures(backGroundFileName, backGroundSelectedFileName, frontCrossFileName,backGroundDisabledFileName,frontCrossDisabledFileName,TextureResType::PLIST);
    }
    else
    {
        checkBox->loadTextures(backGroundFileName_tp, backGroundSelectedFileName_tp, frontCrossFileName_tp,backGroundDisabledFileName_tp,frontCrossDisabledFileName_tp);
    }
    checkBox->setSelected(DICTOOL->getBooleanValue_json(options, "selectedState"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForImageViewFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::ImageView* imageView = static_cast<ImageView*>(widget);
    const char* imageFileName = DICTOOL->getStringValue_json(options, "fileName");
    bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, "scale9Enable");
    bool scale9Enable = false;
    if (scale9EnableExist)
    {
        scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
    }
    imageView->setScale9Enabled(scale9Enable);
    
    std::string tp_i = m_strFilePath;
    const char* imageFileName_tp = nullptr;
    if (imageFileName && (strcmp(imageFileName, "") != 0))
    {
        imageFileName_tp = tp_i.append(imageFileName).c_str();
    }
    
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    if (scale9Enable)
    {
        if (useMergedTexture)
        {
            imageView->loadTexture(imageFileName,TextureResType::PLIST);
        }
        else
        {
            imageView->loadTexture(imageFileName_tp);
        }
        
        bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
        bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
            float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
            imageView->setContentSize(Size(swf, shf));
        }
        
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        imageView->setCapInsets(Rect(cx, cy, cw, ch));
        
    }
    else
    {
        if (useMergedTexture)
        {
            imageView->loadTexture(imageFileName,TextureResType::PLIST);
        }
        else
        {
            imageView->loadTexture(imageFileName_tp);
        }
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLabelFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Text* label = static_cast<cocos2d::ui::Text*>(widget);
    bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, "touchScaleEnable");
    label->setTouchScaleChangeEnabled(touchScaleChangeAble);
    const char* text = DICTOOL->getStringValue_json(options, "text");
    label->setString(text);
    bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        label->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
    }
    bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        label->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
    }
    bool aw = DICTOOL->checkObjectExist_json(options, "areaWidth");
    bool ah = DICTOOL->checkObjectExist_json(options, "areaHeight");
    if (aw && ah)
    {
        Size size = Size(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
        label->setTextAreaSize(size);
    }
    bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        label->setTextHorizontalAlignment((TextHAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
    }
    bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        label->setTextVerticalAlignment((TextVAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLabelAtlasFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::TextAtlas* labelAtlas = static_cast<cocos2d::ui::TextAtlas*>(widget);
    bool sv = DICTOOL->checkObjectExist_json(options, "stringValue");
    bool cmf = DICTOOL->checkObjectExist_json(options, "charMapFile");
    bool iw = DICTOOL->checkObjectExist_json(options, "itemWidth");
    bool ih = DICTOOL->checkObjectExist_json(options, "itemHeight");
    bool scm = DICTOOL->checkObjectExist_json(options, "startCharMap");
    if (sv && cmf && iw && ih && scm && (strcmp(DICTOOL->getStringValue_json(options, "charMapFile"), "") != 0))
    {
        std::string tp_c = m_strFilePath;
        const char* cmf_tp = nullptr;
        const char* cmft = DICTOOL->getStringValue_json(options, "charMapFile");
        cmf_tp = tp_c.append(cmft).c_str();
        
        labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth"),DICTOOL->getIntValue_json(options,"itemHeight"),DICTOOL->getStringValue_json(options, "startCharMap"));
        labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth") / CC_CONTENT_SCALE_FACTOR() ,DICTOOL->getIntValue_json(options,"itemHeight") / CC_CONTENT_SCALE_FACTOR(), DICTOOL->getStringValue_json(options, "startCharMap"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLayoutFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    Layout* containerWidget = static_cast<Layout*>(widget);
    if (!dynamic_cast<cocos2d::ui::ScrollView*>(containerWidget)
        && !dynamic_cast<cocos2d::ui::ListView*>(containerWidget))
    {
        containerWidget->setClippingEnabled(DICTOOL->getBooleanValue_json(options, "clipAble"));
    }
    Layout* panel = (Layout*)widget;
    bool backGroundScale9Enable = DICTOOL->getBooleanValue_json(options, "backGroundScale9Enable");
    panel->setBackGroundImageScale9Enabled(backGroundScale9Enable);
    int cr = DICTOOL->getIntValue_json(options, "bgColorR");
    int cg = DICTOOL->getIntValue_json(options, "bgColorG");
    int cb = DICTOOL->getIntValue_json(options, "bgColorB");
    
    int scr = DICTOOL->getIntValue_json(options, "bgStartColorR");
    int scg = DICTOOL->getIntValue_json(options, "bgStartColorG");
    int scb = DICTOOL->getIntValue_json(options, "bgStartColorB");
    
    int ecr = DICTOOL->getIntValue_json(options, "bgEndColorR");
    int ecg = DICTOOL->getIntValue_json(options, "bgEndColorG");
    int ecb = DICTOOL->getIntValue_json(options, "bgEndColorB");
    
    float bgcv1 = DICTOOL->getFloatValue_json(options, "vectorX");
    float bgcv2 = DICTOOL->getFloatValue_json(options, "vectorY");
    panel->setBackGroundColorVector(Vec2(bgcv1, bgcv2));
    
    int co = DICTOOL->getIntValue_json(options, "bgColorOpacity");
    
    int colorType = DICTOOL->getIntValue_json(options, "colorType");
    panel->setBackGroundColorType(Layout::BackGroundColorType(colorType));
    panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
    panel->setBackGroundColor(Color3B(cr, cg, cb));
    panel->setBackGroundColorOpacity(co);
    
    std::string tp_b = m_strFilePath;
    const char* imageFileName = DICTOOL->getStringValue_json(options, "backGroundImage");
    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    if (backGroundScale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        if (useMergedTexture)
        {
            panel->setBackGroundImage(imageFileName,TextureResType::PLIST);
        }
        else
        {
            panel->setBackGroundImage(imageFileName_tp);
        }
        panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
    }
    else
    {
        
        if (useMergedTexture)
        {
            panel->setBackGroundImage(imageFileName,TextureResType::PLIST);
        }
        else
        {
            panel->setBackGroundImage(imageFileName_tp);
        }
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForScrollViewFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForLayoutFromJsonDictionary(widget, options);
    cocos2d::ui::ScrollView* scrollView = static_cast<cocos2d::ui::ScrollView*>(widget);
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
	int direction = DICTOOL->getFloatValue_json(options, "direction");
    scrollView->setDirection((ScrollView::Direction)direction);
    scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForSliderFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Slider* slider = static_cast<cocos2d::ui::Slider*>(widget);
    
    bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, "barTextureScale9Enable");
    slider->setScale9Enabled(barTextureScale9Enable);
    bool bt = DICTOOL->checkObjectExist_json(options, "barFileName");
    float barLength = DICTOOL->getFloatValue_json(options, "length");
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    if (bt)
    {
        if (barTextureScale9Enable)
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(options, "barFileName");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
            if (useMergedTexture)
            {
                slider->loadBarTexture(imageFileName,TextureResType::PLIST);
            }
            else
            {
                slider->loadBarTexture(imageFileName_tp);
            }
            slider->setContentSize(Size(barLength, slider->getContentSize().height));
        }
        else
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(options, "barFileName");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
            if (useMergedTexture)
            {
                slider->loadBarTexture(imageFileName,TextureResType::PLIST);
            }
            else
            {
                slider->loadBarTexture(imageFileName_tp);
            }
        }
    }
    std::string tp_n = m_strFilePath;
    std::string tp_p = m_strFilePath;
    std::string tp_d = m_strFilePath;
    
    const char* normalFileName = DICTOOL->getStringValue_json(options, "ballNormal");
    const char* pressedFileName = DICTOOL->getStringValue_json(options, "ballPressed");
    const char* disabledFileName = DICTOOL->getStringValue_json(options, "ballDisabled");
    
    const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
    const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
    const char* disabledFileName_tp =  (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
    if (useMergedTexture)
    {
        slider->loadSlidBallTextures(normalFileName,pressedFileName,disabledFileName,TextureResType::PLIST);
    }
    else
    {
        slider->loadSlidBallTextures(normalFileName_tp,pressedFileName_tp,disabledFileName_tp);
    }
    slider->setPercent(DICTOOL->getIntValue_json(options, "percent"));
    
    std::string tp_b = m_strFilePath;
    const char* imageFileName = DICTOOL->getStringValue_json(options, "progressBarFileName");
    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
    if (useMergedTexture)
    {
        slider->loadProgressBarTexture(imageFileName, TextureResType::PLIST);
    }
    else
    {
        slider->loadProgressBarTexture(imageFileName_tp);
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForTextFieldFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::TextField* textField = static_cast<cocos2d::ui::TextField*>(widget);
    bool ph = DICTOOL->checkObjectExist_json(options, "placeHolder");
    if (ph)
    {
        textField->setPlaceHolder(DICTOOL->getStringValue_json(options, "placeHolder"));
    }
    textField->setString(DICTOOL->getStringValue_json(options, "text"));
    bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        textField->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
    }
    bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        textField->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
    }
    bool tsw = DICTOOL->checkObjectExist_json(options, "touchSizeWidth");
    bool tsh = DICTOOL->checkObjectExist_json(options, "touchSizeHeight");
    if (tsw && tsh)
    {
        textField->setTouchSize(Size(DICTOOL->getFloatValue_json(options, "touchSizeWidth"), DICTOOL->getFloatValue_json(options,"touchSizeHeight")));
    }
    
    float dw = DICTOOL->getFloatValue_json(options, "width");
    float dh = DICTOOL->getFloatValue_json(options, "height");
    if (dw > 0.0f || dh > 0.0f)
    {
        //textField->setSize(Size(dw, dh));
    }
    bool maxLengthEnable = DICTOOL->getBooleanValue_json(options, "maxLengthEnable");
    textField->setMaxLengthEnabled(maxLengthEnable);
    
    if (maxLengthEnable)
    {
        int maxLength = DICTOOL->getIntValue_json(options, "maxLength");
        textField->setMaxLength(maxLength);
    }
    bool passwordEnable = DICTOOL->getBooleanValue_json(options, "passwordEnable");
    textField->setPasswordEnabled(passwordEnable);
    if (passwordEnable)
    {
        textField->setPasswordStyleText(DICTOOL->getStringValue_json(options, "passwordStyleText"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLoadingBarFromJsonDictionary(Widget *widget, const rapidjson::Value&options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::LoadingBar* loadingBar = static_cast<cocos2d::ui::LoadingBar*>(widget);
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    std::string tp_b = m_strFilePath;
    const char*imageFileName =  DICTOOL->getStringValue_json(options, "texture");
    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
    if (useMergedTexture)
    {
        loadingBar->loadTexture(imageFileName,TextureResType::PLIST);
    }
    else
    {
        loadingBar->loadTexture(imageFileName_tp);
    }
    loadingBar->setDirection(LoadingBar::Direction(DICTOOL->getIntValue_json(options, "direction")));
    loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLabelBMFontFromJsonDictionary(Widget *widget, const rapidjson::Value&options)
{
    
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::ui::TextBMFont* labelBMFont = static_cast<cocos2d::ui::TextBMFont*>(widget);
    
    std::string tp_c = m_strFilePath;
    const char* cmf_tp = nullptr;
    const char* cmft = DICTOOL->getStringValue_json(options, "fileName");
    cmf_tp = tp_c.append(cmft).c_str();
    
    labelBMFont->setFntFile(cmf_tp);
    
    const char* text = DICTOOL->getStringValue_json(options, "text");
    labelBMFont->setString(text);
    
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}
    
void WidgetPropertiesReader0250::setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol *reader, Widget *widget, const rapidjson::Value &options)
{
    
}

void WidgetPropertiesReader0250::setPropsForAllCustomWidgetFromJsonDictionary(const std::string &classType,
                                                                              cocos2d::ui::Widget *widget,
                                                                              const rapidjson::Value &customOptions)
{
    
}


/*0.3.0.0~1.0.0.0*/
Widget* WidgetPropertiesReader0300::createWidget(const rapidjson::Value& data, const char* fullPath, const char* fileName)
{
    m_strFilePath = fullPath;

    int texturesCount = DICTOOL->getArrayCount_json(data, "textures");
    
    for (int i=0; i<texturesCount; i++)
    {
        const char* file = DICTOOL->getStringValueFromArray_json(data, "textures", i);
        std::string tp = fullPath;
        tp.append(file);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(tp.c_str());
    }
    float fileDesignWidth = DICTOOL->getFloatValue_json(data, "designWidth");
    float fileDesignHeight = DICTOOL->getFloatValue_json(data, "designHeight");
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
        CCLOGERROR("Read design size error!\n");
        Size winSize = Director::getInstance()->getWinSize();
        GUIReader::getInstance()->storeFileDesignSize(fileName, winSize);
    }
    else
    {
        GUIReader::getInstance()->storeFileDesignSize(fileName, Size(fileDesignWidth, fileDesignHeight));
    }
    const rapidjson::Value& widgetTree = DICTOOL->getSubDictionary_json(data, "widgetTree");
    Widget* widget = widgetFromJsonDictionary(widgetTree);
    
    /* *********temp********* */
    if (widget->getContentSize().equals(Size::ZERO))
    {
        Layout* rootWidget = dynamic_cast<Layout*>(widget);
        rootWidget->setContentSize(Size(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    //    widget->setFileDesignSize(Size(fileDesignWidth, fileDesignHeight));
    const rapidjson::Value& actions = DICTOOL->getSubDictionary_json(data, "animation");
    /* *********temp********* */
    //    ActionManager::getInstance()->releaseActions();
    /* ********************** */
//    CCLOG("file name == [%s]",fileName);
    Ref* rootWidget = (Ref*) widget;
    ActionManagerEx::getInstance()->initWithDictionary(fileName,actions,rootWidget);
    return widget;
}
    
 cocos2d::ui::Widget* WidgetPropertiesReader0300::createWidgetFromBinary(CocoLoader* cocoLoader,stExpCocoNode*	cocoNode, const char* fileName)
{
    
    stExpCocoNode *tpChildArray = cocoNode->GetChildArray(cocoLoader);
    float fileDesignWidth;
    float fileDesignHeight;
    
    Widget* widget =  nullptr;

    for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
        std::string key = tpChildArray[i].GetName(cocoLoader);
       
        if (key == "textures") {
            int texturesCount = tpChildArray[i].GetChildNum();
            for (int j=0; j<texturesCount; j++)
            {
                std::string file;
                stExpCocoNode *textureCountsArray = tpChildArray[i].GetChildArray(cocoLoader);
                file = textureCountsArray[j].GetValue(cocoLoader);
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(file);
            }
        }else if (key == "designWidth"){
            fileDesignWidth =  utils::atof(tpChildArray[i].GetValue(cocoLoader));
        }else if (key == "designHeight"){
            fileDesignHeight = utils::atof(tpChildArray[i].GetValue(cocoLoader));
        }else if (key == "widgetTree"){
            
            if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
                CCLOGERROR("Read design size error!\n");
                Size winSize = Director::getInstance()->getWinSize();
                GUIReader::getInstance()->storeFileDesignSize(fileName, winSize);
            }
            else
            {
                GUIReader::getInstance()->storeFileDesignSize(fileName, Size(fileDesignWidth, fileDesignHeight));
            }
            
            
            stExpCocoNode *widgetTreeNode = &tpChildArray[i];
            rapidjson::Type tType  = tpChildArray[i].GetType(cocoLoader);
            
            if (rapidjson::kObjectType == tType)
            {
                widget = widgetFromBinary(cocoLoader, widgetTreeNode);
            }
            
            if (widget->getContentSize().equals(Size::ZERO))
            {
                Layout* rootWidget = dynamic_cast<Layout*>(widget);
                rootWidget->setContentSize(Size(fileDesignWidth, fileDesignHeight));
            }
        }
    }
    
    /* ********************** */
    /* ********************** */
    stExpCocoNode *optionChildNode = cocoNode->GetChildArray(cocoLoader);
    for (int k = 0; k < cocoNode->GetChildNum(); ++k) {
        std::string key = optionChildNode[k].GetName(cocoLoader);
        if (key == "animation") {
            Ref* rootWidget = (Ref*) widget;
            ActionManagerEx::getInstance()->initWithBinary(fileName,rootWidget,cocoLoader, &optionChildNode[k]);
            break;
        }
    }

    return widget;
}

Widget* WidgetPropertiesReader0300::widgetFromBinary(CocoLoader* cocoLoader,  stExpCocoNode*	cocoNode)
{
    Widget* widget = nullptr;
    stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
    stExpCocoNode *optionsNode = nullptr;
    stExpCocoNode *childrenNode = nullptr;
    int elementCount = cocoNode->GetChildNum();
    std::string classname;
    
    for (int i = 0; i < elementCount; ++i) {
        std::string key = stChildArray[i].GetName(cocoLoader);
        std::string value = stChildArray[i].GetValue(cocoLoader);
        
        if (key == "classname" )
        {
            if (!value.empty())
            {
                classname = value;
                widget = this->createGUI(classname);
            }
            else
            {
                CCLOG("Warning!!! classname not found!");
            }
        }else if(key == "children"){
            childrenNode = &stChildArray[i];
        }else if(key == "options"){
            optionsNode = &stChildArray[i];
        }

    }
    
    std::string readerName = this->getWidgetReaderClassName(classname);
    
    WidgetReaderProtocol* reader = this->createWidgetReaderProtocol(readerName);
    
    if (reader)
    {
        // widget parse with widget reader
        setPropsForAllWidgetFromBinary(reader, widget, cocoLoader,optionsNode);
    }
    else
    {
        // 1st., custom widget parse properties of parent widget with parent widget reader
        readerName = this->getWidgetReaderClassName(widget);
        reader = this->createWidgetReaderProtocol(readerName);
        
        
        if (reader && widget) {
            setPropsForAllWidgetFromBinary(reader, widget, cocoLoader, optionsNode);
            // 2nd., custom widget parse with custom reader
            //2nd. parse custom property
            const char* customProperty = nullptr;
            stExpCocoNode *optionChildNode = optionsNode->GetChildArray(cocoLoader);
            for (int k = 0; k < optionsNode->GetChildNum(); ++k) {
                std::string key = optionChildNode[k].GetName(cocoLoader);
                if (key == "customProperty") {
                    customProperty = optionChildNode[k].GetValue(cocoLoader);
                    break;
                }
            }
            
            rapidjson::Document customJsonDict;
            customJsonDict.Parse<0>(customProperty);
            if (customJsonDict.HasParseError())
            {
                CCLOG("GetParseError %s\n", customJsonDict.GetParseError());
            }
            setPropsForAllCustomWidgetFromJsonDictionary(classname, widget, customJsonDict);
        }else{
            CCLOG("Widget or WidgetReader doesn't exists!!!  Please check your csb file.");
        }
      
    }
    
    //parse children
    if (nullptr != childrenNode) {
        rapidjson::Type tType22  = childrenNode->GetType(cocoLoader);
        if (tType22 == rapidjson::kArrayType) {
            
            int childrenCount = childrenNode->GetChildNum();
            stExpCocoNode* innerChildArray = childrenNode->GetChildArray(cocoLoader);
            for (int i=0; i < childrenCount; ++i) {
                rapidjson::Type tType  = innerChildArray[i].GetType(cocoLoader);
                
                if (tType == rapidjson::kObjectType) {
                    
                    Widget *child = widgetFromBinary(cocoLoader, &innerChildArray[i]);
                    
                    if (child)
                    {
                        PageView* pageView = dynamic_cast<PageView*>(widget);
                        if (pageView)
                        {
                            pageView->addPage(static_cast<Layout*>(child));
                        }
                        else
                        {
                            ListView* listView = dynamic_cast<ListView*>(widget);
                            if (listView)
                            {
                                listView->pushBackCustomItem(child);
                            }
                            else
                            {
                                if (dynamic_cast<Layout*>(widget))
                                {
                                    if (child->getPositionType() == ui::Widget::PositionType::PERCENT)
                                    {
                                        child->setPositionPercent(Vec2(child->getPositionPercent().x + widget->getAnchorPoint().x,
                                                                       child->getPositionPercent().y + widget->getAnchorPoint().y));
                                    }
                                    child->setPosition(Vec2(child->getPositionX() + widget->getAnchorPointInPoints().x,
                                                            child->getPositionY() + widget->getAnchorPointInPoints().y));
                                }
                                widget->addChild(child);
                            }
                        }
                    }
                    
                }
            }
        }
    }
    
    return widget;
}
    
void WidgetPropertiesReader0300::setPropsForAllWidgetFromBinary(WidgetReaderProtocol* reader,
                                                                cocos2d::ui::Widget* widget,
                                                                CocoLoader* cocoLoader,
                                                                stExpCocoNode*	cocoNode)
{
    reader->setPropsFromBinary(widget, cocoLoader, cocoNode);
}

    
Widget* WidgetPropertiesReader0300::widgetFromJsonDictionary(const rapidjson::Value& data)
{
    const char* classname = DICTOOL->getStringValue_json(data, "classname");
    const rapidjson::Value& uiOptions = DICTOOL->getSubDictionary_json(data, "options");
    Widget* widget = this->createGUI(classname);
//    CCLOG("classname = %s", classname);
    std::string readerName = this->getWidgetReaderClassName(classname);
    
    WidgetReaderProtocol* reader = this->createWidgetReaderProtocol(readerName);
    
    if (reader)
    {
        // widget parse with widget reader
        setPropsForAllWidgetFromJsonDictionary(reader, widget, uiOptions);
    }
    else
    {
        readerName = this->getWidgetReaderClassName(widget);
        
        reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        
        if (reader && widget) {
            setPropsForAllWidgetFromJsonDictionary(reader, widget, uiOptions);
            
            // 2nd., custom widget parse with custom reader
            const char* customProperty = DICTOOL->getStringValue_json(uiOptions, "customProperty");
            rapidjson::Document customJsonDict;
            customJsonDict.Parse<0>(customProperty);
            if (customJsonDict.HasParseError())
            {
                CCLOG("GetParseError %s\n", customJsonDict.GetParseError());
            }
            setPropsForAllCustomWidgetFromJsonDictionary(classname, widget, customJsonDict);
        }else{
            CCLOG("Widget or WidgetReader doesn't exists!!!  Please check your json file.");
        }
       
    }
    
    int childrenCount = DICTOOL->getArrayCount_json(data, "children");
    for (int i = 0; i < childrenCount; i++)
    {
        const rapidjson::Value& subData = DICTOOL->getDictionaryFromArray_json(data, "children", i);
        cocos2d::ui::Widget* child = widgetFromJsonDictionary(subData);
        if (child)
        {
            PageView* pageView = dynamic_cast<PageView*>(widget);
            if (pageView)
            {
                pageView->addPage(static_cast<Layout*>(child));
            }
            else
            {
                ListView* listView = dynamic_cast<ListView*>(widget);
                if (listView)
                {
                    listView->pushBackCustomItem(child);
                }
                else
                {
                    if (dynamic_cast<Layout*>(widget))
                    {
                        if (child->getPositionType() == ui::Widget::PositionType::PERCENT)
                        {
                            child->setPositionPercent(Vec2(child->getPositionPercent().x + widget->getAnchorPoint().x, child->getPositionPercent().y + widget->getAnchorPoint().y));
                        }
                        child->setPosition(Vec2(child->getPositionX() + widget->getAnchorPointInPoints().x, child->getPositionY() + widget->getAnchorPointInPoints().y));
                    }
                    widget->addChild(child);
                }
            }
        }
    }
    return widget;
}
    
void WidgetPropertiesReader0300::setPropsForAllWidgetFromJsonDictionary(WidgetReaderProtocol *reader, Widget *widget, const rapidjson::Value &options)
{
    reader->setPropsFromJsonDictionary(widget, options);
}
    
void WidgetPropertiesReader0300::setPropsForAllCustomWidgetFromJsonDictionary(const std::string &classType,
                                                                              cocos2d::ui::Widget *widget,
                                                                              const rapidjson::Value &customOptions)
{
    GUIReader* guiReader = GUIReader::getInstance();
    
    std::map<std::string, Ref*> *object_map = guiReader->getParseObjectMap();
    Ref* object = (*object_map)[classType];
    
    std::map<std::string, SEL_ParseEvent> *selector_map = guiReader->getParseCallBackMap();
    SEL_ParseEvent selector = (*selector_map)[classType];
    
    if (object && selector)
    {
        (object->*selector)(classType, widget, customOptions);
    }    
}
    
}
