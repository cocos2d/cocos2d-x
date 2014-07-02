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

#include "../GUI/System/CocosGUI.h"
#include "../Json/DictionaryHelper.h"
#include "../Action/CCActionManager.h"
#include <fstream>
#include <iostream>

#include "WidgetReader/ButtonReader/ButtonReader.h"
#include "WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "WidgetReader/SliderReader/SliderReader.h"
#include "WidgetReader/ImageViewReader/ImageViewReader.h"
#include "WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "WidgetReader/LabelAtlasReader/LabelAtlasReader.h"
#include "WidgetReader/LabelReader/LabelReader.h"
#include "WidgetReader/LabelBMFontReader/LabelBMFontReader.h"
#include "WidgetReader/TextFieldReader/TextFieldReader.h"
#include "WidgetReader/LayoutReader/LayoutReader.h"
#include "WidgetReader/PageViewReader/PageViewReader.h"
#include "WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "WidgetReader/ListViewReader/ListViewReader.h"

NS_CC_EXT_BEGIN

using namespace cocos2d::ui;

static GUIReader* sharedReader = NULL;

GUIReader::GUIReader()
: m_strFilePath("")
{
    _fileDesignSizes = CCDictionary::create();
    CC_SAFE_RETAIN(_fileDesignSizes);
    
    ObjectFactory* factoryCreate = ObjectFactory::getInstance();
    
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(ButtonReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(CheckBoxReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(SliderReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(ImageViewReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(LoadingBarReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(LabelAtlasReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(LabelReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(LabelBMFontReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(TextFieldReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(LayoutReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(PageViewReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(ScrollViewReader));
    factoryCreate->registerType(CREATE_CLASS_WIDGET_READER_INFO(ListViewReader));
    
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(Button));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(CheckBox));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(ImageView));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(Label));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(LabelAtlas));
    factoryCreate->registerType(CREATE_CLASS_GUI_INFO(LabelBMFont));
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
    _fileDesignSizes->removeAllObjects();
    CC_SAFE_RELEASE(_fileDesignSizes);
}

GUIReader* GUIReader::shareReader()
{
    if (!sharedReader)
    {
        sharedReader = new GUIReader();
    }
    return sharedReader;
}

void GUIReader::purge()
{
	CC_SAFE_DELETE(sharedReader);
}

int GUIReader::getVersionInteger(const char *str)
{
    /*********temp***********/
    std::string strVersion = str;
    int length = strVersion.length();
    if (length < 7)
    {
        return 0;
    }
    int pos = strVersion.find_first_of(".");
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

void GUIReader::storeFileDesignSize(const char *fileName, const cocos2d::CCSize &size)
{
    if (!_fileDesignSizes)
    {
        return;
    }
    cocos2d::CCString* strSize = cocos2d::CCString::createWithFormat("{%f,%f}", size.width, size.height);
    _fileDesignSizes->setObject(strSize, fileName);
}

const cocos2d::CCSize GUIReader::getFileDesignSize(const char* fileName) const
{
    if (!_fileDesignSizes)
    {
        return cocos2d::CCSizeZero;
    }
    cocos2d::CCSize designSize = cocos2d::CCSizeFromString(((cocos2d::CCString*)_fileDesignSizes->objectForKey(fileName))->m_sString.c_str());
    return designSize;
}

void GUIReader::registerTypeAndCallBack(const std::string& classType,
                                        ObjectFactory::Instance ins,
                                        CCObject *object,
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

cocos2d::ui::Widget* GUIReader::widgetFromBinaryFile(const char *fileName)
{
    std::string jsonpath;
    rapidjson::Document jsonDict;
    jsonpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    size_t pos = jsonpath.find_last_of('/');
    m_strFilePath = jsonpath.substr(0,pos+1);
    unsigned long nSize = 0;
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "rb", &nSize);
    
    const char* fileVersion = "";
    ui::Widget* widget = NULL;
    
    if (pBuffer != NULL && nSize > 0)
    {
        CocoLoader	tCocoLoader;
        if(true == tCocoLoader.ReadCocoBinBuff((char*)pBuffer))
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
                
                WidgetPropertiesReader * pReader = NULL;
                if (fileVersion)
                {
                    int versionInteger = getVersionInteger(fileVersion);
                    if (versionInteger < 250)
                    {
                        CCAssert(0, "You current studio doesn't support binary format, please upgrade to the latest version!");
                        pReader = new WidgetPropertiesReader0250();
                        widget = pReader->createWidgetFromBinary(&tCocoLoader, tpRootCocoNode, fileName);
                    }
                    else
                    {
                        pReader = new WidgetPropertiesReader0300();
                        widget = pReader->createWidgetFromBinary(&tCocoLoader, tpRootCocoNode, fileName);
                    }
                }
                else
                {
                    pReader = new WidgetPropertiesReader0250();
                    widget = pReader->createWidgetFromBinary(&tCocoLoader, tpRootCocoNode, fileName);
                }
                
                CC_SAFE_DELETE(pReader);
                
            }
        }
    }
    
    CC_SAFE_DELETE_ARRAY(pBuffer);
    
    return widget;
}

cocos2d::ui::Widget* GUIReader::widgetFromJsonFile(const char *fileName)
{
	unsigned char *pBytes = NULL;
	std::string jsonpath;
	rapidjson::Document jsonDict;
    jsonpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    int pos = jsonpath.find_last_of('/');
	m_strFilePath = jsonpath.substr(0,pos+1);
    unsigned long size = 0;
    pBytes = CCFileUtils::sharedFileUtils()->getFileData(jsonpath.c_str(),"r" , &size);
	if(NULL == pBytes || strcmp((const char*)pBytes, "") == 0)
	{
		printf("read json file[%s] error!\n", fileName);
		return NULL;
	}
	CCData *data = new CCData(pBytes, size);
	std::string load_str = std::string((const char *)data->getBytes(), data->getSize() );
	CC_SAFE_DELETE(data);
	jsonDict.Parse<0>(load_str.c_str());
    if (jsonDict.HasParseError())
    {
        CCLOG("GetParseError %s\n",jsonDict.GetParseError());
    }
    cocos2d::ui::Widget* widget = NULL;
    const char* fileVersion = DICTOOL->getStringValue_json(jsonDict, "version");
    WidgetPropertiesReader * pReader = NULL;
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
    CC_SAFE_DELETE_ARRAY(pBytes);
    return widget;
}

cocos2d::ui::Widget* WidgetPropertiesReader::createGUI(const std::string &classname)
{
    std::string name = this->getGUIClassName(classname);
    
    CCObject* object = ObjectFactory::getInstance()->createObject(name);
    
    return dynamic_cast<ui::Widget*>(object);
}

WidgetReaderProtocol* WidgetPropertiesReader::createWidgetReaderProtocol(const std::string &classname)
{
    CCObject* object = ObjectFactory::getInstance()->createObject(classname);
    
    return dynamic_cast<WidgetReaderProtocol*>(object);
}


std::string  WidgetPropertiesReader::getWidgetReaderClassName(const std::string& classname)
{
    // create widget reader to parse properties of widget
    std::string readerName = classname;
    if (readerName == "Panel")
    {
        readerName = "Layout";
    }
    else if (readerName == "LabelArea")
    {
        readerName = "Label";
    }
    else if (readerName == "TextButton")
    {
        readerName = "Button";
    }
    readerName.append("Reader");
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
        convertedClassName = "Label";
    }
    else if (name == "TextButton")
    {
        convertedClassName = "Button";
    }
    
    
    return convertedClassName;
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
    else if (dynamic_cast<LabelAtlas*>(widget))
    {
        readerName = "LabelAtlasReader";
    }
    else if (dynamic_cast<LabelBMFont*>(widget))
    {
        readerName = "LabelBMFontReader";
    }
    else if (dynamic_cast<Label*>(widget))
    {
        readerName = "LabelReader";
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
    
    return readerName;
}




cocos2d::ui::Widget* WidgetPropertiesReader0250::createWidget(const rapidjson::Value& data, const char* fullPath, const char* fileName)
{
    m_strFilePath = fullPath;
    int texturesCount = DICTOOL->getArrayCount_json(data, "textures");
    
    for (int i=0; i<texturesCount; i++)
    {
        const char* file = DICTOOL->getStringValueFromArray_json(data, "textures", i);
        std::string tp = fullPath;
        tp.append(file);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(tp.c_str());
    }
    float fileDesignWidth = DICTOOL->getFloatValue_json(data, "designWidth");
    float fileDesignHeight = DICTOOL->getFloatValue_json(data, "designHeight");
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
        printf("Read design size error!\n");
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        GUIReader::shareReader()->storeFileDesignSize(fileName, winSize);
    }
    else
    {
        GUIReader::shareReader()->storeFileDesignSize(fileName, CCSizeMake(fileDesignWidth, fileDesignHeight));
    }
    const rapidjson::Value& widgetTree = DICTOOL->getSubDictionary_json(data, "widgetTree");
    cocos2d::ui::Widget* widget = widgetFromJsonDictionary(widgetTree);
    
    /* *********temp********* */
    if (widget->getContentSize().equals(CCSizeZero))
    {
        widget->setSize(CCSizeMake(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    //    widget->setFileDesignSize(CCSizeMake(fileDesignWidth, fileDesignHeight));
    const rapidjson::Value& actions = DICTOOL->getSubDictionary_json(data, "animation");
    /* *********temp********* */
    //    ActionManager::shareManager()->releaseActions();
    /* ********************** */
    // CCLOG("file name == [%s]",fileName);
	CCObject* rootWidget = (CCObject*) widget;
    ActionManager::shareManager()->initWithDictionary(fileName,actions,rootWidget);
    return widget;
}

cocos2d::ui::Widget* WidgetPropertiesReader0250::widgetFromJsonDictionary(const rapidjson::Value& data)
{
    cocos2d::ui::Widget* widget = NULL;
    const char* classname = DICTOOL->getStringValue_json(data, "classname");
    const rapidjson::Value& uiOptions = DICTOOL->getSubDictionary_json(data, "options");
    if (classname && strcmp(classname, "Button") == 0)
    {
        widget = cocos2d::ui::Button::create();
        setPropsForButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "CheckBox") == 0)
    {
        widget = cocos2d::ui::CheckBox::create();
        setPropsForCheckBoxFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Label") == 0)
    {
        widget = cocos2d::ui::Label::create();
        setPropsForLabelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelAtlas") == 0)
    {
        widget = cocos2d::ui::LabelAtlas::create();
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
        widget = cocos2d::ui::Label::create();
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
        widget = cocos2d::ui::Layout::create();
        setPropsForLayoutFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Slider") == 0)
    {
        widget = cocos2d::ui::Slider::create();
        setPropsForSliderFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelBMFont") == 0)
    {
        widget = cocos2d::ui::LabelBMFont::create();
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
        cocos2d::ui::Widget* child = widgetFromJsonDictionary(subData);
        if (child)
        {
            widget->addChild(child);
        }
    }
    return widget;
}

void WidgetPropertiesReader0250::setPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    bool ignoreSizeExsit = DICTOOL->checkObjectExist_json(options, "ignoreSize");
    if (ignoreSizeExsit)
    {
        widget->ignoreContentAdaptWithSize(DICTOOL->getBooleanValue_json(options, "ignoreSize"));
    }
    
    float w = DICTOOL->getFloatValue_json(options, "width");
    float h = DICTOOL->getFloatValue_json(options, "height");
    widget->setSize(CCSizeMake(w, h));
    
    widget->setTag(DICTOOL->getIntValue_json(options, "tag"));
	widget->setActionTag(DICTOOL->getIntValue_json(options, "actiontag"));
    widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, "touchAble"));
    const char* name = DICTOOL->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = DICTOOL->getFloatValue_json(options, "x");
    float y = DICTOOL->getFloatValue_json(options, "y");
    widget->setPosition(ccp(x,y));
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
    widget->setZOrder(z);
}

void WidgetPropertiesReader0250::setColorPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget *widget, const rapidjson::Value& options)
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
    widget->setColor(ccc3(colorR, colorG, colorB));
    bool apx = DICTOOL->checkObjectExist_json(options, "anchorPointX");
    float apxf = apx ? DICTOOL->getFloatValue_json(options, "anchorPointX") : ((widget->getWidgetType() == ui::WidgetTypeWidget) ? 0.5f : 0.0f);
    bool apy = DICTOOL->checkObjectExist_json(options, "anchorPointY");
    float apyf = apy ? DICTOOL->getFloatValue_json(options, "anchorPointY") : ((widget->getWidgetType() == ui::WidgetTypeWidget) ? 0.5f : 0.0f);
    widget->setAnchorPoint(ccp(apxf, apyf));
    bool flipX = DICTOOL->getBooleanValue_json(options, "flipX");
    bool flipY = DICTOOL->getBooleanValue_json(options, "flipY");
    widget->setFlipX(flipX);
    widget->setFlipY(flipY);
}

void WidgetPropertiesReader0250::setPropsForButtonFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Button* button = (cocos2d::ui::Button*)widget;
    bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
    button->setScale9Enabled(scale9Enable);
    
    std::string tp_n = m_strFilePath;
    std::string tp_p = m_strFilePath;
    std::string tp_d = m_strFilePath;
    
    const char* normalFileName = DICTOOL->getStringValue_json(options, "normal");
    const char* pressedFileName = DICTOOL->getStringValue_json(options, "pressed");
    const char* disabledFileName = DICTOOL->getStringValue_json(options, "disabled");
    
    const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():NULL;
    const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
    const char* disabledFileName_tp =  (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    if (scale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        
        if (useMergedTexture)
        {
            button->loadTextures(normalFileName, pressedFileName, disabledFileName,ui::UI_TEX_TYPE_PLIST);
        }
        else
        {
            button->loadTextures(normalFileName_tp, pressedFileName_tp, disabledFileName_tp);
        }
        button->setCapInsets(CCRectMake(cx, cy, cw, ch));
        bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
        bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
            float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
            button->setSize(CCSizeMake(swf, shf));
        }
    }
    else
    {
        if (useMergedTexture)
        {
            button->loadTextures(normalFileName, pressedFileName, disabledFileName,ui::UI_TEX_TYPE_PLIST);
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
    button->setTitleColor(ccc3(cri,cgi,cbi));
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

void WidgetPropertiesReader0250::setPropsForCheckBoxFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::CheckBox* checkBox = (cocos2d::ui::CheckBox*)widget;
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
    
    const char* backGroundFileName_tp = (backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():NULL;
    const char* backGroundSelectedFileName_tp = (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():NULL;
    const char* frontCrossFileName_tp = (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():NULL;
    const char* backGroundDisabledFileName_tp = (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():NULL;
    const char* frontCrossDisabledFileName_tp = (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():NULL;
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    
    if (useMergedTexture)
    {
        checkBox->loadTextures(backGroundFileName, backGroundSelectedFileName, frontCrossFileName,backGroundDisabledFileName,frontCrossDisabledFileName,UI_TEX_TYPE_PLIST);
    }
    else
    {
        checkBox->loadTextures(backGroundFileName_tp, backGroundSelectedFileName_tp, frontCrossFileName_tp,backGroundDisabledFileName_tp,frontCrossDisabledFileName_tp);
    }
    
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForImageViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::ui::ImageView* imageView = (cocos2d::ui::ImageView*)widget;
    const char* imageFileName = DICTOOL->getStringValue_json(options, "fileName");
    bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, "scale9Enable");
    bool scale9Enable = false;
    if (scale9EnableExist)
    {
        scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
    }
    imageView->setScale9Enabled(scale9Enable);
    
    std::string tp_i = m_strFilePath;
    const char* imageFileName_tp = NULL;
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
            imageView->setSize(CCSizeMake(swf, shf));
        }
        
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        imageView->setCapInsets(CCRectMake(cx, cy, cw, ch));
        
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

void WidgetPropertiesReader0250::setPropsForLabelFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Label* label = (cocos2d::ui::Label*)widget;
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
        CCSize size = CCSize(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
        label->setTextAreaSize(size);
    }
    bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        label->setTextHorizontalAlignment((CCTextAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
    }
    bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        label->setTextVerticalAlignment((CCVerticalTextAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLabelAtlasFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::LabelAtlas* labelAtlas = (cocos2d::ui::LabelAtlas*)widget;
    bool sv = DICTOOL->checkObjectExist_json(options, "stringValue");
    bool cmf = DICTOOL->checkObjectExist_json(options, "charMapFile");
    bool iw = DICTOOL->checkObjectExist_json(options, "itemWidth");
    bool ih = DICTOOL->checkObjectExist_json(options, "itemHeight");
    bool scm = DICTOOL->checkObjectExist_json(options, "startCharMap");
    if (sv && cmf && iw && ih && scm && (strcmp(DICTOOL->getStringValue_json(options, "charMapFile"), "") != 0))
    {
        std::string tp_c = m_strFilePath;
        const char* cmf_tp = NULL;
        const char* cmft = DICTOOL->getStringValue_json(options, "charMapFile");
        cmf_tp = tp_c.append(cmft).c_str();
        
        labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth") / CC_CONTENT_SCALE_FACTOR(),DICTOOL->getIntValue_json(options,"itemHeight") / CC_CONTENT_SCALE_FACTOR(), DICTOOL->getStringValue_json(options, "startCharMap"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLayoutFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    Layout* containerWidget = (Layout*)widget;
    if (!dynamic_cast<cocos2d::ui::ScrollView*>(containerWidget)
        && !dynamic_cast<ListView*>(containerWidget))
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
    panel->setBackGroundColorVector(ccp(bgcv1, bgcv2));
    
    int co = DICTOOL->getIntValue_json(options, "bgColorOpacity");
    
    int colorType = DICTOOL->getIntValue_json(options, "colorType");
    panel->setBackGroundColorType(LayoutBackGroundColorType(colorType));
    panel->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
    panel->setBackGroundColor(ccc3(cr, cg, cb));
    panel->setBackGroundColorOpacity(co);
    
    std::string tp_b = m_strFilePath;
    const char* imageFileName = DICTOOL->getStringValue_json(options, "backGroundImage");
    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
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
        panel->setBackGroundImageCapInsets(CCRectMake(cx, cy, cw, ch));
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

void WidgetPropertiesReader0250::setPropsForScrollViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForLayoutFromJsonDictionary(widget, options);
    cocos2d::ui::ScrollView* scrollView = (cocos2d::ui::ScrollView*)widget;
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
	int direction = DICTOOL->getFloatValue_json(options, "direction");
	scrollView->setDirection((SCROLLVIEW_DIR)direction);
    scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForSliderFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Slider* slider = (cocos2d::ui::Slider*)widget;
    
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
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
            if (useMergedTexture)
            {
                slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
            }
            else
            {
                slider->loadBarTexture(imageFileName_tp);
            }
            slider->setSize(CCSizeMake(barLength, slider->getContentSize().height));
        }
        else
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(options, "barFileName");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
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
    
    const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():NULL;
    const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
    const char* disabledFileName_tp =  (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
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
    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
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

void WidgetPropertiesReader0250::setPropsForTextFieldFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::TextField* textField = (cocos2d::ui::TextField*)widget;
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
        textField->setTouchSize(CCSizeMake(DICTOOL->getFloatValue_json(options, "touchSizeWidth"), DICTOOL->getFloatValue_json(options,"touchSizeHeight")));
    }
    
    float dw = DICTOOL->getFloatValue_json(options, "width");
    float dh = DICTOOL->getFloatValue_json(options, "height");
    if (dw > 0.0f || dh > 0.0f)
    {
        //textField->setSize(CCSizeMake(dw, dh));
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

void WidgetPropertiesReader0250::setPropsForLoadingBarFromJsonDictionary(cocos2d::ui::Widget *widget, const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::LoadingBar* loadingBar = (cocos2d::ui::LoadingBar*)widget;
    bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
    std::string tp_b = m_strFilePath;
    const char*imageFileName =  DICTOOL->getStringValue_json(options, "texture");
    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
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

void WidgetPropertiesReader0250::setPropsForLabelBMFontFromJsonDictionary(cocos2d::ui::Widget *widget, const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::ui::LabelBMFont* labelBMFont = (cocos2d::ui::LabelBMFont*)widget;
    
    std::string tp_c = m_strFilePath;
    const char* cmf_tp = NULL;
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
cocos2d::ui::Widget* WidgetPropertiesReader0300::createWidget(const rapidjson::Value& data, const char* fullPath, const char* fileName)
{
    m_strFilePath = fullPath;
    
    int texturesCount = DICTOOL->getArrayCount_json(data, "textures");
    
    for (int i=0; i<texturesCount; i++)
    {
        const char* file = DICTOOL->getStringValueFromArray_json(data, "textures", i);
        std::string tp = fullPath;
        tp.append(file);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(tp.c_str());
    }
    float fileDesignWidth = DICTOOL->getFloatValue_json(data, "designWidth");
    float fileDesignHeight = DICTOOL->getFloatValue_json(data, "designHeight");
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
        printf("Read design size error!\n");
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        GUIReader::shareReader()->storeFileDesignSize(fileName, winSize);
    }
    else
    {
        GUIReader::shareReader()->storeFileDesignSize(fileName, CCSizeMake(fileDesignWidth, fileDesignHeight));
    }
    const rapidjson::Value& widgetTree = DICTOOL->getSubDictionary_json(data, "widgetTree");
    cocos2d::ui::Widget* widget = widgetFromJsonDictionary(widgetTree);
    
    /* *********temp********* */
    if (widget->getContentSize().equals(CCSizeZero))
    {
        widget->setSize(CCSizeMake(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    //    widget->setFileDesignSize(CCSizeMake(fileDesignWidth, fileDesignHeight));
    const rapidjson::Value& actions = DICTOOL->getSubDictionary_json(data, "animation");
    /* *********temp********* */
    //    ActionManager::shareManager()->releaseActions();
    /* ********************** */
    CCLOG("file name == [%s]",fileName);
	CCObject* rootWidget = (CCObject*) widget;
    ActionManager::shareManager()->initWithDictionary(fileName,actions,rootWidget);
    return widget;
}

cocos2d::ui::Widget* WidgetPropertiesReader0300::widgetFromJsonDictionary(const rapidjson::Value& data)
{
    const char* classname = DICTOOL->getStringValue_json(data, "classname");
    const rapidjson::Value& uiOptions = DICTOOL->getSubDictionary_json(data, "options");
    cocos2d::ui::Widget* widget = ObjectFactory::getInstance()->createGUI(classname);
    
    // create widget reader to parse properties of widget
    std::string readerName = getWidgetReaderClassName(classname);
    
    WidgetReaderProtocol* reader = this->createWidgetReaderProtocol(readerName);
    
    if (reader)
    {
        // widget parse with widget reader
        setPropsForAllWidgetFromJsonDictionary(reader, widget, uiOptions);
    }
    else
    {
        // 1st., custom widget parse properties of parent widget with parent widget reader
        readerName = this->getWidgetReaderClassName(widget);
        reader =  this->createWidgetReaderProtocol(readerName);
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
                    widget->addChild(child);
                }
            }
        }
    }
    return widget;
}

void WidgetPropertiesReader0300::setPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    bool ignoreSizeExsit = DICTOOL->checkObjectExist_json(options, "ignoreSize");
    if (ignoreSizeExsit)
    {
        widget->ignoreContentAdaptWithSize(DICTOOL->getBooleanValue_json(options, "ignoreSize"));
    }
    
    widget->setSizeType((SizeType)DICTOOL->getIntValue_json(options, "sizeType"));
    widget->setPositionType((PositionType)DICTOOL->getIntValue_json(options, "positionType"));
    
    widget->setSizePercent(ccp(DICTOOL->getFloatValue_json(options, "sizePercentX"), DICTOOL->getFloatValue_json(options, "sizePercentY")));
    widget->setPositionPercent(ccp(DICTOOL->getFloatValue_json(options, "positionPercentX"), DICTOOL->getFloatValue_json(options, "positionPercentY")));        
    
    widget->setTag(DICTOOL->getIntValue_json(options, "tag"));
	widget->setActionTag(DICTOOL->getIntValue_json(options, "actiontag"));
    widget->setTouchEnabled(DICTOOL->getBooleanValue_json(options, "touchAble"));
    const char* name = DICTOOL->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = DICTOOL->getFloatValue_json(options, "x");
    float y = DICTOOL->getFloatValue_json(options, "y");
    widget->setPosition(ccp(x,y));
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
    widget->setZOrder(z);
    
	bool layout = DICTOOL->checkObjectExist_json(options, "layoutParameter");
	if (layout)
	{
		const rapidjson::Value& layoutParameterDic = DICTOOL->getSubDictionary_json(options, "layoutParameter");
		int paramType = DICTOOL->getIntValue_json(layoutParameterDic, "type");
		cocos2d::ui::LayoutParameter* parameter = NULL;
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

void WidgetPropertiesReader0300::setColorPropsForWidgetFromJsonDictionary(cocos2d::ui::Widget *widget, const rapidjson::Value& options)
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
    widget->setColor(ccc3(colorR, colorG, colorB));
    bool apx = DICTOOL->checkObjectExist_json(options, "anchorPointX");
    float apxf = apx ? DICTOOL->getFloatValue_json(options, "anchorPointX") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    bool apy = DICTOOL->checkObjectExist_json(options, "anchorPointY");
    float apyf = apy ? DICTOOL->getFloatValue_json(options, "anchorPointY") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    widget->setAnchorPoint(ccp(apxf, apyf));
    bool flipX = DICTOOL->getBooleanValue_json(options, "flipX");
    bool flipY = DICTOOL->getBooleanValue_json(options, "flipY");
    widget->setFlipX(flipX);
    widget->setFlipY(flipY);
}

void WidgetPropertiesReader0300::setPropsForButtonFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Button* button = (cocos2d::ui::Button*)widget;
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
            const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():NULL;
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
            const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
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
            const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
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
        
        button->setCapInsets(CCRectMake(cx, cy, cw, ch));
        bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
        bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
            float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
            button->setSize(CCSizeMake(swf, shf));
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
    button->setTitleColor(ccc3(cri,cgi,cbi));
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

void WidgetPropertiesReader0300::setPropsForCheckBoxFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::CheckBox* checkBox = (cocos2d::ui::CheckBox*)widget;
    
    const rapidjson::Value& backGroundDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxData");
    int backGroundType = DICTOOL->getIntValue_json(backGroundDic, "resourceType");
    switch (backGroundType)
    {
        case 0:
        {
            std::string tp_b = m_strFilePath;
            const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
            const char* backGroundFileName_tp = (backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():NULL;
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
            const char* backGroundSelectedFileName_tp = (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():NULL;
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
            const char* frontCrossFileName_tp = (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():NULL;
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
            const char* backGroundDisabledFileName_tp = (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():NULL;
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
            const char* frontCrossDisabledFileName_tp = (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():NULL;
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
    
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForImageViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::ui::ImageView* imageView = (cocos2d::ui::ImageView*)widget;
    
    const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "fileNameData");
    int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_i = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            const char* imageFileName_tp = NULL;
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
            imageView->setSize(CCSizeMake(swf, shf));
        }
        
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        
        imageView->setCapInsets(CCRectMake(cx, cy, cw, ch));
        
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLabelFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Label* label = (cocos2d::ui::Label*)widget;
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
        CCSize size = CCSize(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
        label->setTextAreaSize(size);
    }
    bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        label->setTextHorizontalAlignment((CCTextAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
    }
    bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        label->setTextVerticalAlignment((CCVerticalTextAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLabelAtlasFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::LabelAtlas* labelAtlas = (cocos2d::ui::LabelAtlas*)widget;
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
                labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth"), DICTOOL->getIntValue_json(options,"itemHeight"), DICTOOL->getStringValue_json(options, "startCharMap"));
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

void WidgetPropertiesReader0300::setPropsForLayoutFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    Layout* panel = (Layout*)widget;
    
    float w = 0, h = 0;
    bool adaptScrenn = DICTOOL->getBooleanValue_json(options, "adaptScreen");
    if (adaptScrenn)
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        w = screenSize.width;
        h = screenSize.height;
    }
    else
    {
        w = DICTOOL->getFloatValue_json(options, "width");
        h = DICTOOL->getFloatValue_json(options, "height");
    }
    panel->setSize(CCSizeMake(w, h));    
    
    if (!dynamic_cast<cocos2d::ui::ScrollView*>(widget)
        && !dynamic_cast<ListView*>(widget))
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
    panel->setBackGroundColorVector(ccp(bgcv1, bgcv2));
    
    int co = DICTOOL->getIntValue_json(options, "bgColorOpacity");
    
    int colorType = DICTOOL->getIntValue_json(options, "colorType");
    panel->setBackGroundColorType(LayoutBackGroundColorType(colorType));
    panel->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
    panel->setBackGroundColor(ccc3(cr, cg, cb));
    panel->setBackGroundColorOpacity(co);
    
    
    const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "backGroundImageData");
    int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
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
        panel->setBackGroundImageCapInsets(CCRectMake(cx, cy, cw, ch));
    }
    panel->setLayoutType((LayoutType)DICTOOL->getIntValue_json(options, "layoutType"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForScrollViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForLayoutFromJsonDictionary(widget, options);
    cocos2d::ui::ScrollView* scrollView = (cocos2d::ui::ScrollView*)widget;
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
	int direction = DICTOOL->getFloatValue_json(options, "direction");
	scrollView->setDirection((SCROLLVIEW_DIR)direction);
    scrollView->setBounceEnabled(DICTOOL->getBooleanValue_json(options, "bounceEnable"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForSliderFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::Slider* slider = (cocos2d::ui::Slider*)widget;
    
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
                    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
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
            
            slider->setSize(CCSizeMake(barLength, slider->getContentSize().height));
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
                    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
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
            const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():NULL;
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
            const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
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
            const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
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
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
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

void WidgetPropertiesReader0300::setPropsForTextFieldFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::TextField* textField = (cocos2d::ui::TextField*)widget;
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
        textField->setTouchSize(CCSizeMake(DICTOOL->getFloatValue_json(options, "touchSizeWidth"), DICTOOL->getFloatValue_json(options,"touchSizeHeight")));
    }
    
    float dw = DICTOOL->getFloatValue_json(options, "width");
    float dh = DICTOOL->getFloatValue_json(options, "height");
    if (dw > 0.0f || dh > 0.0f)
    {
        //textField->setSize(CCSizeMake(dw, dh));
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

void WidgetPropertiesReader0300::setPropsForLoadingBarFromJsonDictionary(cocos2d::ui::Widget *widget, const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::ui::LoadingBar* loadingBar = (cocos2d::ui::LoadingBar*)widget;
    
    const rapidjson::Value& imageFileNameDic = DICTOOL->getSubDictionary_json(options, "textureData");
    int imageFileNameType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_i = m_strFilePath;
            const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
            const char* imageFileName_tp = NULL;
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
    
    /* gui mark add load bar scale9 parse */
    bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
    loadingBar->setScale9Enabled(scale9Enable);
    
    if (scale9Enable)
    {
        float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
        float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
        float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
        float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
        
        loadingBar->setCapInsets(CCRectMake(cx, cy, cw, ch));
        
        float width = DICTOOL->getFloatValue_json(options, "width");
        float height = DICTOOL->getFloatValue_json(options, "height");
        loadingBar->setSize(CCSizeMake(width, height));
    }
    /**/
    
    loadingBar->setDirection(LoadingBarType(DICTOOL->getIntValue_json(options, "direction")));
    loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLabelBMFontFromJsonDictionary(cocos2d::ui::Widget *widget, const rapidjson::Value& options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::ui::LabelBMFont* labelBMFont = (cocos2d::ui::LabelBMFont*)widget;
    
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

void WidgetPropertiesReader0300::setPropsForPageViewFromJsonDictionary(cocos2d::ui::Widget*widget,const rapidjson::Value& options)
{
    setPropsForLayoutFromJsonDictionary(widget, options);
}

void WidgetPropertiesReader0300::setPropsForListViewFromJsonDictionary(cocos2d::ui::Widget* widget, const rapidjson::Value& options)
{
    setPropsForLayoutFromJsonDictionary(widget, options);
    
    ListView* listView = (ListView*)widget;
    
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    listView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
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
    GUIReader* guiReader = GUIReader::shareReader();
    
    std::map<std::string, CCObject*> object_map = GUIReader::shareReader()->getParseObjectMap();
    CCObject* object = object_map[classType];
    
    std::map<std::string, SEL_ParseEvent> selector_map = guiReader->getParseCallBackMap();
    SEL_ParseEvent selector = selector_map[classType];
    
    if (object && selector)
    {
        (object->*selector)(classType, widget, customOptions);
    }    
}

Widget* WidgetPropertiesReader0300::createWidgetFromBinary(cocos2d::extension::CocoLoader *pCocoLoader,
                                                           cocos2d::extension::stExpCocoNode *pCocoNode,
                                                           const char *fileName)
{
    
    std::string jsonpath;
	rapidjson::Document jsonDict;
    jsonpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    int pos = jsonpath.find_last_of('/');
	m_strFilePath = jsonpath.substr(0,pos+1);
    
    stExpCocoNode *tpChildArray = pCocoNode->GetChildArray(pCocoLoader);
    float fileDesignWidth;
    float fileDesignHeight;
    
    Widget* widget =  NULL;
    
    for (int i = 0; i < pCocoNode->GetChildNum(); ++i) {
        std::string key = tpChildArray[i].GetName(pCocoLoader);
        
        if (key == "textures") {
            int texturesCount = tpChildArray[i].GetChildNum();
            for (int j=0; j<texturesCount; j++)
            {
                std::string file;
                stExpCocoNode *textureCountsArray = tpChildArray[i].GetChildArray(pCocoLoader);
                file = textureCountsArray[j].GetValue(pCocoLoader);
                std::string tp = m_strFilePath;
                tp.append(file);
                CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(tp.c_str());
            }
        }else if (key == "designWidth"){
            fileDesignWidth =  atof(tpChildArray[i].GetValue(pCocoLoader));
        }else if (key == "designHeight"){
            fileDesignHeight = atof(tpChildArray[i].GetValue(pCocoLoader));
        }else if (key == "widgetTree"){
            
            if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
                CCLOGERROR("Read design size error!\n");
                CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                GUIReader::shareReader()->storeFileDesignSize(fileName, winSize);
            }
            else
            {
                GUIReader::shareReader()->storeFileDesignSize(fileName, CCSize(fileDesignWidth, fileDesignHeight));
            }
            
            
            stExpCocoNode *widgetTreeNode = &tpChildArray[i];
            rapidjson::Type tType  = tpChildArray[i].GetType(pCocoLoader);
            
            if (rapidjson::kObjectType == tType)
            {
                widget = widgetFromBinary(pCocoLoader, widgetTreeNode);
            }
            
            if (widget->getContentSize().equals(CCSize(0,0)))
            {
                Layout* rootWidget = dynamic_cast<Layout*>(widget);
                rootWidget->setSize(CCSize(fileDesignWidth, fileDesignHeight));
            }
        }
    }
    
    /* ********************** */
    stExpCocoNode *optionChildNode = pCocoNode->GetChildArray(pCocoLoader);
    for (int k = 0; k < pCocoNode->GetChildNum(); ++k) {
        std::string key = optionChildNode[k].GetName(pCocoLoader);
        if (key == "animation") {
            CCObject* rootWidget = (CCObject*) widget;
            ActionManager::shareManager()->initWithBinary(fileName,rootWidget,pCocoLoader, &optionChildNode[k]);
            break;
        }
    }
    
   
	
    return widget;
}

cocos2d::ui::Widget* WidgetPropertiesReader0300::widgetFromBinary(CocoLoader* pCocoLoader,
                                              stExpCocoNode*	pCocoNode)
{
    Widget* widget = NULL;
    stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
    
    stExpCocoNode *optionsNode = NULL;
    stExpCocoNode *childrenNode = NULL;
    int elementCount = pCocoNode->GetChildNum();
    std::string classname;
    for (int i = 0; i < elementCount; ++i)
    {
        std::string key = stChildArray[i].GetName(pCocoLoader);
        std::string value = stChildArray[i].GetValue(pCocoLoader);
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
    
//    CCLOG("classname = %s", classname.c_str());
    std::string readerName = this->getWidgetReaderClassName(classname);
    
    WidgetReaderProtocol* reader = this->createWidgetReaderProtocol(readerName);
    
    if (reader)
    {
        // widget parse with widget reader
        setPropsForAllWidgetFromBinary(reader, widget, pCocoLoader, optionsNode);
    }
    else
    {
        // 1st., custom widget parse properties of parent widget with parent widget reader
        readerName = this->getWidgetReaderClassName(widget);
        reader = this->createWidgetReaderProtocol(readerName);
        
        if (reader && widget) {
            setPropsForAllWidgetFromBinary(reader, widget, pCocoLoader, optionsNode);
            
            //2nd. parse custom property
            const char* customProperty = NULL;
            stExpCocoNode *optionChildNode = optionsNode->GetChildArray(pCocoLoader);
            for (int k = 0; k < optionsNode->GetChildNum(); ++k) {
                std::string key = optionChildNode[k].GetName(pCocoLoader);
                if (key == "customProperty") {
                    customProperty = optionChildNode[k].GetValue(pCocoLoader);
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
    if (NULL != childrenNode)
    {
        rapidjson::Type tType22  = childrenNode->GetType(pCocoLoader);
        if (tType22 == rapidjson::kArrayType)
        {
            
            int childrenCount = childrenNode->GetChildNum();
            stExpCocoNode* innerChildArray = childrenNode->GetChildArray(pCocoLoader);
            for (int i=0; i < childrenCount; ++i)
            {
                rapidjson::Type tType  = innerChildArray[i].GetType(pCocoLoader);
                
                if (tType == rapidjson::kObjectType)
                {
                    
                    Widget *child = widgetFromBinary(pCocoLoader, &innerChildArray[i]);
                    
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
                                            CocoLoader* pCocoLoader,
                                            stExpCocoNode*	pCocoNode)
{
    reader->setPropsFromBinary(widget, pCocoLoader, pCocoNode);
}

NS_CC_EXT_END