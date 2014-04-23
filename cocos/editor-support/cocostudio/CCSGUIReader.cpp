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

using namespace cocos2d::ui;
using namespace cocos2d;


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
        sharedReader = new GUIReader();
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
    CCLOG("iversion %d",iVersion);
    return iVersion;
    /************************/
}

void GUIReader::storeFileDesignSize(const char *fileName, const cocos2d::Size &size)
{
    std::string keyWidth = fileName;
    keyWidth.append("width");
    std::string keyHeight = fileName;
    keyHeight.append("height");
    _fileDesignSizes[keyWidth] = Value(size.width);
    _fileDesignSizes[keyHeight] = Value(size.height);
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


Widget* GUIReader::widgetFromJsonFile(const char *fileName)
{
	std::string jsonpath;
	rapidjson::Document jsonDict;
    jsonpath = CCFileUtils::getInstance()->fullPathForFilename(fileName);
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
            pReader = new WidgetPropertiesReader0250();
            widget = pReader->createWidget(jsonDict, m_strFilePath.c_str(), fileName);
        }
        else
        {
            pReader = new WidgetPropertiesReader0300();
            widget = pReader->createWidget(jsonDict, m_strFilePath.c_str(), fileName);
        }
    }
    else
    {
        pReader = new WidgetPropertiesReader0250();
        widget = pReader->createWidget(jsonDict, m_strFilePath.c_str(), fileName);
    }
    
    CC_SAFE_DELETE(pReader);
    return widget;
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
        rootWidget->setSize(Size(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    //    widget->setFileDesignSize(Size(fileDesignWidth, fileDesignHeight));
    const rapidjson::Value& actions = DICTOOL->getSubDictionary_json(data, "animation");
    /* *********temp********* */
    //    ActionManager::getInstance()->releaseActions();
    /* ********************** */
    CCLOG("file name == [%s]",fileName);
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
    widget->setSize(Size(w, h));
    
    widget->setTag(DICTOOL->getIntValue_json(options, "tag"));
	widget->setActionTag(DICTOOL->getIntValue_json(options, "actiontag"));
    widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, "touchAble"));
    const char* name = DICTOOL->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = DICTOOL->getFloatValue_json(options, "x");
    float y = DICTOOL->getFloatValue_json(options, "y");
    widget->setPosition(Point(x,y));
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
    bool apx = DICTOOL->checkObjectExist_json(options, "anchorPointX");
    float apxf = apx ? DICTOOL->getFloatValue_json(options, "anchorPointX") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    bool apy = DICTOOL->checkObjectExist_json(options, "anchorPointY");
    float apyf = apy ? DICTOOL->getFloatValue_json(options, "anchorPointY") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    widget->setAnchorPoint(Point(apxf, apyf));
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
            button->loadTextures(normalFileName, pressedFileName, disabledFileName,UI_TEX_TYPE_PLIST);
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
            button->setSize(Size(swf, shf));
        }
    }
    else
    {
        if (useMergedTexture)
        {
            button->loadTextures(normalFileName, pressedFileName, disabledFileName,UI_TEX_TYPE_PLIST);
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
        checkBox->loadTextures(backGroundFileName, backGroundSelectedFileName, frontCrossFileName,backGroundDisabledFileName,frontCrossDisabledFileName,UI_TEX_TYPE_PLIST);
    }
    else
    {
        checkBox->loadTextures(backGroundFileName_tp, backGroundSelectedFileName_tp, frontCrossFileName_tp,backGroundDisabledFileName_tp,frontCrossDisabledFileName_tp);
    }
    checkBox->setSelectedState(DICTOOL->getBooleanValue_json(options, "selectedState"));
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
            imageView->loadTexture(imageFileName,UI_TEX_TYPE_PLIST);
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
            imageView->setSize(Size(swf, shf));
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
            imageView->loadTexture(imageFileName,UI_TEX_TYPE_PLIST);
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
    label->setText(text);
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
    panel->setBackGroundColorVector(Point(bgcv1, bgcv2));
    
    int co = DICTOOL->getIntValue_json(options, "bgColorOpacity");
    
    int colorType = DICTOOL->getIntValue_json(options, "colorType");
    panel->setBackGroundColorType(LayoutBackGroundColorType(colorType));
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
            panel->setBackGroundImage(imageFileName,UI_TEX_TYPE_PLIST);
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
            panel->setBackGroundImage(imageFileName,UI_TEX_TYPE_PLIST);
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
    scrollView->setDirection((SCROLLVIEW_DIR)direction);
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
                slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
            }
            else
            {
                slider->loadBarTexture(imageFileName_tp);
            }
            slider->setSize(Size(barLength, slider->getContentSize().height));
        }
        else
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(options, "barFileName");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
            if (useMergedTexture)
            {
                slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
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
        slider->loadSlidBallTextures(normalFileName,pressedFileName,disabledFileName,UI_TEX_TYPE_PLIST);
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
        slider->loadProgressBarTexture(imageFileName, UI_TEX_TYPE_PLIST);
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
    textField->setText(DICTOOL->getStringValue_json(options, "text"));
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
        loadingBar->loadTexture(imageFileName,UI_TEX_TYPE_PLIST);
    }
    else
    {
        loadingBar->loadTexture(imageFileName_tp);
    }
    loadingBar->setDirection(LoadingBarType(DICTOOL->getIntValue_json(options, "direction")));
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
    labelBMFont->setText(text);
    
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
        rootWidget->setSize(Size(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    //    widget->setFileDesignSize(Size(fileDesignWidth, fileDesignHeight));
    const rapidjson::Value& actions = DICTOOL->getSubDictionary_json(data, "animation");
    /* *********temp********* */
    //    ActionManager::getInstance()->releaseActions();
    /* ********************** */
    CCLOG("file name == [%s]",fileName);
    Ref* rootWidget = (Ref*) widget;
    ActionManagerEx::getInstance()->initWithDictionary(fileName,actions,rootWidget);
    return widget;
}
    
Widget* WidgetPropertiesReader0300::widgetFromJsonDictionary(const rapidjson::Value& data)
{
    const char* classname = DICTOOL->getStringValue_json(data, "classname");
    const rapidjson::Value& uiOptions = DICTOOL->getSubDictionary_json(data, "options");
    Widget* widget = ObjectFactory::getInstance()->createGUI(classname);
    
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
    WidgetReaderProtocol* reader = ObjectFactory::getInstance()->createWidgetReaderProtocol(readerName);
    
    if (reader)
    {
        // widget parse with widget reader
        setPropsForAllWidgetFromJsonDictionary(reader, widget, uiOptions);
    }
    else
    {
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
        else if (dynamic_cast<Layout*>(widget))
        {
            readerName = "LayoutReader";
        }
        else if (dynamic_cast<ScrollView*>(widget))
        {
            readerName = "ScrollViewReader";
        }
        else if (dynamic_cast<ListView*>(widget))
        {
            readerName = "ListViewReader";
        }
        else if (dynamic_cast<PageView*>(widget))
        {
            readerName = "PageViewReader";
        }
        else if (dynamic_cast<Widget*>(widget))
        {
            readerName = "WidgetReader";
        }
        reader = ObjectFactory::getInstance()->createWidgetReaderProtocol(readerName);
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
                    if (!dynamic_cast<Layout*>(widget))
                    {
                        if (child->getPositionType() == cocos2d::ui::POSITION_PERCENT)
                        {
                            child->setPositionPercent(Point(child->getPositionPercent().x + 0.5f, child->getPositionPercent().y + 0.5f));
                        }
                        child->setPosition(Point(child->getPositionX() + widget->getSize().width / 2.0f, child->getPositionY() + widget->getSize().height / 2.0f));
                    }
                    widget->addChild(child);
                }
            }
        }
    }
    return widget;
}

void WidgetPropertiesReader0300::setPropsForWidgetFromJsonDictionary(Widget*widget,const rapidjson::Value&options)
{
    bool ignoreSizeExsit = DICTOOL->checkObjectExist_json(options, "ignoreSize");
    if (ignoreSizeExsit)
    {
        widget->ignoreContentAdaptWithSize(DICTOOL->getBooleanValue_json(options, "ignoreSize"));
    }
    
    widget->setSizeType((SizeType)DICTOOL->getIntValue_json(options, "sizeType"));
    widget->setPositionType((PositionType)DICTOOL->getIntValue_json(options, "positionType"));
    
    widget->setSizePercent(Point(DICTOOL->getFloatValue_json(options, "sizePercentX"), DICTOOL->getFloatValue_json(options, "sizePercentY")));
    widget->setPositionPercent(Point(DICTOOL->getFloatValue_json(options, "positionPercentX"), DICTOOL->getFloatValue_json(options, "positionPercentY")));
    
    float w = DICTOOL->getFloatValue_json(options, "width");
    float h = DICTOOL->getFloatValue_json(options, "height");
    widget->setSize(Size(w, h));
    
    widget->setTag(DICTOOL->getIntValue_json(options, "tag"));
	widget->setActionTag(DICTOOL->getIntValue_json(options, "actiontag"));
    widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, "touchAble"));
    const char* name = DICTOOL->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = DICTOOL->getFloatValue_json(options, "x");
    float y = DICTOOL->getFloatValue_json(options, "y");
    widget->setPosition(Point(x,y));
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

	bool layout = DICTOOL->checkObjectExist_json(options, "layoutParameter");
	if (layout)
	{
		const rapidjson::Value& layoutParameterDic = DICTOOL->getSubDictionary_json(options, "layoutParameter");
		int paramType = DICTOOL->getIntValue_json(layoutParameterDic, "type");
        LayoutParameter* parameter = nullptr;
        switch (paramType)
        {
            case 0:
                break;
            case 1:
            {
                parameter = LinearLayoutParameter::create();
				int gravity = DICTOOL->getIntValue_json(layoutParameterDic, "gravity");
                ((LinearLayoutParameter*)parameter)->setGravity((LinearGravity)gravity);
                break;
            }
            case 2:
            {
                parameter = RelativeLayoutParameter::create();
                RelativeLayoutParameter* rParameter = (RelativeLayoutParameter*)parameter;
				const char* relativeName = DICTOOL->getStringValue_json(layoutParameterDic, "relativeName");
                rParameter->setRelativeName(relativeName);
				const char* relativeToName = DICTOOL->getStringValue_json(layoutParameterDic, "relativeToName");
                rParameter->setRelativeToWidgetName(relativeToName);
				int align = DICTOOL->getIntValue_json(layoutParameterDic, "align");
                rParameter->setAlign((RelativeAlign)align);
                break;
            }
            default:
                break;
        }
        if (parameter)
        {
			float mgl = DICTOOL->getFloatValue_json(layoutParameterDic, "marginLeft");
			float mgt = DICTOOL->getFloatValue_json(layoutParameterDic, "marginTop");
			float mgr = DICTOOL->getFloatValue_json(layoutParameterDic, "marginRight");
			float mgb = DICTOOL->getFloatValue_json(layoutParameterDic, "marginDown");
            parameter->setMargin(Margin(mgl, mgt, mgr, mgb));
            widget->setLayoutParameter(parameter);
        }
    }
}

void WidgetPropertiesReader0300::setColorPropsForWidgetFromJsonDictionary(Widget *widget, const rapidjson::Value&options)
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
    bool apx = DICTOOL->checkObjectExist_json(options, "anchorPointX");
    float apxf = apx ? DICTOOL->getFloatValue_json(options, "anchorPointX") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    bool apy = DICTOOL->checkObjectExist_json(options, "anchorPointY");
    float apyf = apy ? DICTOOL->getFloatValue_json(options, "anchorPointY") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    widget->setAnchorPoint(Point(apxf, apyf));
    bool flipX = DICTOOL->getBooleanValue_json(options, "flipX");
    bool flipY = DICTOOL->getBooleanValue_json(options, "flipY");
    widget->setFlippedX(flipX);
    widget->setFlippedY(flipY);
}

void WidgetPropertiesReader0300::setPropsForButtonFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Button* button = static_cast<cocos2d::ui::Button*>(widget);
    bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
    button->setScale9Enabled(scale9Enable);
    
    const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, "normalData");
    int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
    switch (normalType)
    {
        case 0:
        {
            std::string tp_n = m_strFilePath;
            const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
            const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
            button->loadTextureNormal(normalFileName_tp);
            break;
        }
        case 1:
        {
            const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
            button->loadTextureNormal(normalFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, "pressedData");
    int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
    switch (pressedType)
    {
        case 0:
        {
            std::string tp_p = m_strFilePath;
            const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
            const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
            button->loadTexturePressed(pressedFileName_tp);
            break;
        }
        case 1:
        {
            const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
            button->loadTexturePressed(pressedFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, "disabledData");
    int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
    switch (disabledType)
    {
        case 0:
        {
            std::string tp_d = m_strFilePath;
            const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
            const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
            button->loadTextureDisabled(disabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
            button->loadTextureDisabled(disabledFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    if (scale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        
        button->setCapInsets(Rect(cx, cy, cw, ch));
        bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
        bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
            float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
            button->setSize(Size(swf, shf));
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

void WidgetPropertiesReader0300::setPropsForCheckBoxFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    CheckBox* checkBox = static_cast<cocos2d::ui::CheckBox*>(widget);
    
    const rapidjson::Value& backGroundDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxData");
    int backGroundType = DICTOOL->getIntValue_json(backGroundDic, "resourceType");
    switch (backGroundType)
    {
        case 0:
        {
            std::string tp_b = m_strFilePath;
            const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
            const char* backGroundFileName_tp = (backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():nullptr;
            checkBox->loadTextureBackGround(backGroundFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
            checkBox->loadTextureBackGround(backGroundFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& backGroundSelectedDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxSelectedData");
    int backGroundSelectedType = DICTOOL->getIntValue_json(backGroundSelectedDic, "resourceType");
    switch (backGroundSelectedType)
    {
        case 0:
        {
            std::string tp_bs = m_strFilePath;
            const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
            const char* backGroundSelectedFileName_tp = (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():nullptr;
            checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
            checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& frontCrossDic = DICTOOL->getSubDictionary_json(options, "frontCrossData");
    int frontCrossType = DICTOOL->getIntValue_json(frontCrossDic, "resourceType");
    switch (frontCrossType)
    {
        case 0:
        {
            std::string tp_c = m_strFilePath;
            const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
            const char* frontCrossFileName_tp = (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():nullptr;
            checkBox->loadTextureFrontCross(frontCrossFileName_tp);
            break;
        }
        case 1:
        {
            const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
            checkBox->loadTextureFrontCross(frontCrossFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& backGroundDisabledDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxDisabledData");
    int backGroundDisabledType = DICTOOL->getIntValue_json(backGroundDisabledDic, "resourceType");
    switch (backGroundDisabledType)
    {
        case 0:
        {
            std::string tp_bd = m_strFilePath;
            const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
            const char* backGroundDisabledFileName_tp = (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():nullptr;
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& frontCrossDisabledDic = DICTOOL->getSubDictionary_json(options, "frontCrossDisabledData");
    int frontCrossDisabledType = DICTOOL->getIntValue_json(frontCrossDisabledDic, "resourceType");
    switch (frontCrossDisabledType)
    {
        case 0:
        {
            std::string tp_cd = m_strFilePath;
            const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
            const char* frontCrossDisabledFileName_tp = (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():nullptr;
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    checkBox->setSelectedState(DICTOOL->getBooleanValue_json(options, "selectedState"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForImageViewFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::ui::ImageView* imageView = static_cast<cocos2d::ui::ImageView*>(widget);
    
    const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "fileNameData");
    int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_i = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            const char* imageFileName_tp = nullptr;
            if (imageFileName && (strcmp(imageFileName, "") != 0))
            {
                imageFileName_tp = tp_i.append(imageFileName).c_str();
                imageView->loadTexture(imageFileName_tp);
            }
            break;
        }
        case 1:
        {
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            imageView->loadTexture(imageFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, "scale9Enable");
    bool scale9Enable = false;
    if (scale9EnableExist)
    {
        scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
    }
    imageView->setScale9Enabled(scale9Enable);
    
    
    if (scale9Enable)
    {
        bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
        bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
            float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
            imageView->setSize(Size(swf, shf));
        }
        
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        
        imageView->setCapInsets(Rect(cx, cy, cw, ch));
        
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLabelFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Text* label = static_cast<cocos2d::ui::Text*>(widget);
    bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, "touchScaleEnable");
    label->setTouchScaleChangeEnabled(touchScaleChangeAble);
    const char* text = DICTOOL->getStringValue_json(options, "text");
    label->setText(text);
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

void WidgetPropertiesReader0300::setPropsForLabelAtlasFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::TextAtlas* labelAtlas = static_cast<cocos2d::ui::TextAtlas*>(widget);
    bool sv = DICTOOL->checkObjectExist_json(options, "stringValue");
    bool cmf = DICTOOL->checkObjectExist_json(options, "charMapFile");
    bool iw = DICTOOL->checkObjectExist_json(options, "itemWidth");
    bool ih = DICTOOL->checkObjectExist_json(options, "itemHeight");
    bool scm = DICTOOL->checkObjectExist_json(options, "startCharMap");
    if (sv && cmf && iw && ih && scm)
    {
        const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, "charMapFileData");
        int cmfType = DICTOOL->getIntValue_json(cmftDic, "resourceType");
        switch (cmfType)
        {
            case 0:
            {
                std::string tp_c = m_strFilePath;
                const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, "path");
                const char* cmf_tp = tp_c.append(cmfPath).c_str();
                labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth"),DICTOOL->getIntValue_json(options,"itemHeight"), DICTOOL->getStringValue_json(options, "startCharMap"));
                break;
            }
            case 1:
                CCLOG("Wrong res type of LabelAtlas!");
                break;
            default:
                break;
        }
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLayoutFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    float w = 0, h = 0;
    bool adaptScrenn = DICTOOL->getBooleanValue_json(options, "adaptScreen");
    if (adaptScrenn)
    {
        Size screenSize = CCDirector::getInstance()->getWinSize();
        w = screenSize.width;
        h = screenSize.height;
    }
    else
    {
        w = DICTOOL->getFloatValue_json(options, "width");
        h = DICTOOL->getFloatValue_json(options, "height");
    }
    
    Layout* panel = static_cast<cocos2d::ui::Layout*>(widget);
    if (!dynamic_cast<cocos2d::ui::ScrollView*>(widget)
        && !dynamic_cast<cocos2d::ui::ListView*>(widget))
    {
        panel->setClippingEnabled(DICTOOL->getBooleanValue_json(options, "clipAble"));
    }
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
    panel->setBackGroundColorVector(Point(bgcv1, bgcv2));
    
    int co = DICTOOL->getIntValue_json(options, "bgColorOpacity");
    
    int colorType = DICTOOL->getIntValue_json(options, "colorType");
    panel->setBackGroundColorType(LayoutBackGroundColorType(colorType));
    panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
    panel->setBackGroundColor(Color3B(cr, cg, cb));
    panel->setBackGroundColorOpacity(co);
    
    
    const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "backGroundImageData");
    int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
            panel->setBackGroundImage(imageFileName_tp);
            break;
        }
        case 1:
        {
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            panel->setBackGroundImage(imageFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    if (backGroundScale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
    }
    panel->setLayoutType((LayoutType)DICTOOL->getIntValue_json(options, "layoutType"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForScrollViewFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForLayoutFromJsonDictionary(widget, options);
    cocos2d::ui::ScrollView* scrollView = static_cast<cocos2d::ui::ScrollView*>(widget);
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
	int direction = DICTOOL->getFloatValue_json(options, "direction");
    scrollView->setDirection((SCROLLVIEW_DIR)direction);
    scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForSliderFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Slider* slider = static_cast<cocos2d::ui::Slider*>(widget);
    
    bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, "barTextureScale9Enable");
    slider->setScale9Enabled(barTextureScale9Enable);
    bool bt = DICTOOL->checkObjectExist_json(options, "barFileName");
    float barLength = DICTOOL->getFloatValue_json(options, "length");
    if (bt)
    {
        if (barTextureScale9Enable)
        {
            
            const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "barFileNameData");
            int imageFileType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
            switch (imageFileType)
            {
                case 0:
                {
                    std::string tp_b = m_strFilePath;
                    const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
                    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
                    slider->loadBarTexture(imageFileName_tp);
                    break;
                }
                case 1:
                {
                    const char* imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                    slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
                    break;
                }
                default:
                    break;
            }
            
            slider->setSize(Size(barLength, slider->getContentSize().height));
        }
        else
        {
            const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "barFileNameData");
            int imageFileType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
            switch (imageFileType)
            {
                case 0:
                {
                    std::string tp_b = m_strFilePath;
                    const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
                    slider->loadBarTexture(imageFileName_tp);
                    break;
                }
                case 1:
                {
                    const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                    slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
                    break;
                }
                default:
                    break;
            }
        }
    }
    
    const rapidjson::Value& normalDic = DICTOOL->getSubDictionary_json(options, "ballNormalData");
    int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
    switch (normalType)
    {
        case 0:
        {
            std::string tp_n = m_strFilePath;
            const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
            const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
            slider->loadSlidBallTextureNormal(normalFileName_tp);
            break;
        }
        case 1:
        {
            const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
            slider->loadSlidBallTextureNormal(normalFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& pressedDic = DICTOOL->getSubDictionary_json(options, "ballPressedData");
    int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
    switch (pressedType)
    {
        case 0:
        {
            std::string tp_p = m_strFilePath;
            const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
            const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
            slider->loadSlidBallTexturePressed(pressedFileName_tp);
            break;
        }
        case 1:
        {
            const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
            slider->loadSlidBallTexturePressed(pressedFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    const rapidjson::Value& disabledDic = DICTOOL->getSubDictionary_json(options, "ballDisabledData");
    int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
    switch (disabledType)
    {
        case 0:
        {
            std::string tp_d = m_strFilePath;
            const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
            const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
            slider->loadSlidBallTextureDisabled(disabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
            slider->loadSlidBallTextureDisabled(disabledFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    slider->setPercent(DICTOOL->getIntValue_json(options, "percent"));
    
    const rapidjson::Value& progressBarDic = DICTOOL->getSubDictionary_json(options, "progressBarData");
    int progressBarType = DICTOOL->getIntValue_json(progressBarDic, "resourceType");
    switch (progressBarType)
    {
        case 0:
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(progressBarDic, "path");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
            slider->loadProgressBarTexture(imageFileName_tp);
            break;
        }
        case 1:
        {
            const char* imageFileName = DICTOOL->getStringValue_json(progressBarDic, "path");
            slider->loadProgressBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForTextFieldFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::TextField* textField = static_cast<cocos2d::ui::TextField*>(widget);
    bool ph = DICTOOL->checkObjectExist_json(options, "placeHolder");
    if (ph)
    {
        textField->setPlaceHolder(DICTOOL->getStringValue_json(options, "placeHolder"));
    }
    textField->setText(DICTOOL->getStringValue_json(options, "text"));
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

void WidgetPropertiesReader0300::setPropsForLoadingBarFromJsonDictionary(Widget *widget, const rapidjson::Value&options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::LoadingBar* loadingBar = static_cast<cocos2d::ui::LoadingBar*>(widget);
    
    const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "textureData");
    int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_i = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            const char* imageFileName_tp = nullptr;
            if (imageFileName && (strcmp(imageFileName, "") != 0))
            {
                imageFileName_tp = tp_i.append(imageFileName).c_str();
                loadingBar->loadTexture(imageFileName_tp);
            }
            break;
        }
        case 1:
        {
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            loadingBar->loadTexture(imageFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    
    /* ui mark add load bar scale9 parse */
    bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
    loadingBar->setScale9Enabled(scale9Enable);
    
    if (scale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        
        loadingBar->setCapInsets(Rect(cx, cy, cw, ch));
        
        float width = DICTOOL->getFloatValue_json(options, "width");
        float height = DICTOOL->getFloatValue_json(options, "height");
        loadingBar->setSize(Size(width, height));
    }
    /**/
    
    loadingBar->setDirection(LoadingBarType(DICTOOL->getIntValue_json(options, "direction")));
    loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLabelBMFontFromJsonDictionary(Widget *widget, const rapidjson::Value&options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::ui::TextBMFont* labelBMFont = static_cast<cocos2d::ui::TextBMFont*>(widget);
    
    const rapidjson::Value& cmftDic = DICTOOL->getSubDictionary_json(options, "fileNameData");
    int cmfType = DICTOOL->getIntValue_json(cmftDic, "resourceType");
    switch (cmfType)
    {
        case 0:
        {
            std::string tp_c = m_strFilePath;
            const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, "path");
            const char* cmf_tp = tp_c.append(cmfPath).c_str();
            labelBMFont->setFntFile(cmf_tp);
            break;
        }
        case 1:
            CCLOG("Wrong res type of LabelAtlas!");
            break;
        default:
            break;
    }
    
    const char* text = DICTOOL->getStringValue_json(options, "text");
    labelBMFont->setText(text);
    
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForPageViewFromJsonDictionary(Widget*widget,const rapidjson::Value& options)
{
     setPropsForLayoutFromJsonDictionary(widget, options);
}

void WidgetPropertiesReader0300::setPropsForListViewFromJsonDictionary(Widget* widget, const rapidjson::Value& options)
{
    setPropsForLayoutFromJsonDictionary(widget, options);
    
    ListView* listView = static_cast<ListView*>(widget);
    
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    listView->setInnerContainerSize(Size(innerWidth, innerHeight));
	int direction = DICTOOL->getFloatValue_json(options, "direction");
	listView->setDirection((SCROLLVIEW_DIR)direction);
    
    ListViewGravity gravity = (ListViewGravity)DICTOOL->getIntValue_json(options, "gravity");
    listView->setGravity(gravity);
    
    float itemMargin = DICTOOL->getFloatValue_json(options, "itemMargin");
    listView->setItemsMargin(itemMargin);
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
    
    std::map<std::string, Ref*> object_map = GUIReader::getInstance()->getParseObjectMap();
    Ref* object = object_map[classType];
    
    std::map<std::string, SEL_ParseEvent> selector_map = guiReader->getParseCallBackMap();
    SEL_ParseEvent selector = selector_map[classType];
    
    if (object && selector)
    {
        (object->*selector)(classType, widget, customOptions);
    }    
}
    
}
