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
#include "cocostudio/CCSGUIReader.h"
#include "gui/CocosGUI.h"
#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CCActionManagerEx.h"
#include <fstream>
#include <iostream>

using namespace cocos2d::gui;
using namespace cocos2d;


namespace cocostudio {
    
static GUIReader* sharedReader = nullptr;

GUIReader::GUIReader():
m_strFilePath("")
{
}

GUIReader::~GUIReader()
{
}

GUIReader* GUIReader::shareReader()
{
    if (!sharedReader)
    {
        sharedReader = new GUIReader();
    }
    return sharedReader;
}

void GUIReader::purgeGUIReader()
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


Widget* GUIReader::widgetFromJsonFile(const char *fileName)
{
    DictionaryHelper* dicHelper = DICTOOL;

    std::string jsonpath;
    JsonDictionary *jsonDict = nullptr;
    jsonpath = CCFileUtils::getInstance()->fullPathForFilename(fileName);
    int pos = jsonpath.find_last_of('/');
    m_strFilePath = jsonpath.substr(0,pos+1);

    std::string des = FileUtils::getInstance()->getStringFromFile(jsonpath);
    if (des.empty())
    {
        CCLOG("read json file[%s] error!\n", fileName);
        return nullptr;
    }

    jsonDict = new JsonDictionary();
    jsonDict->initWithDescription(des.c_str());
    
    Widget* widget = nullptr;
    const char* fileVersion = dicHelper->getStringValue_json(jsonDict, "version");
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
    CC_SAFE_DELETE(jsonDict);
    return widget;
}



Widget* WidgetPropertiesReader0250::createWidget(JsonDictionary* data, const char* fullPath, const char* fileName)
{
    m_strFilePath = fullPath;
    DictionaryHelper* dicHelper = DICTOOL;
    int texturesCount = dicHelper->getArrayCount_json(data, "textures");
    
    for (int i=0; i<texturesCount; i++)
    {
        const char* file = dicHelper->getStringValueFromArray_json(data, "textures", i);
        std::string tp = fullPath;
        tp.append(file);
        CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile(tp.c_str());
    }
    float fileDesignWidth = dicHelper->getFloatValue_json(data, "designWidth");
    float fileDesignHeight = dicHelper->getFloatValue_json(data, "designHeight");
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
        printf("Read design size error!\n");
        Size winSize = Director::getInstance()->getWinSize();
        GUIReader::shareReader()->storeFileDesignSize(fileName, winSize);
    }
    else
    {
        GUIReader::shareReader()->storeFileDesignSize(fileName, Size(fileDesignWidth, fileDesignHeight));
    }
    JsonDictionary* widgetTree = dicHelper->getSubDictionary_json(data, "widgetTree");
    Widget* widget = widgetFromJsonDictionary(widgetTree);
    
    /* *********temp********* */
    if (widget->getContentSize().equals(Size::ZERO))
    {
        Layout* rootWidget = dynamic_cast<Layout*>(widget);
        rootWidget->setSize(Size(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    //    widget->setFileDesignSize(Size(fileDesignWidth, fileDesignHeight));
    JsonDictionary* actions = dicHelper->getSubDictionary_json(data, "animation");
    /* *********temp********* */
    //    ActionManager::shareManager()->releaseActions();
    /* ********************** */
    CCLOG("file name == [%s]",fileName);
    Object* rootWidget = (Object*) widget;
    ActionManagerEx::shareManager()->initWithDictionary(fileName,actions,rootWidget);
    CC_SAFE_DELETE(widgetTree);
    CC_SAFE_DELETE(actions);
    return widget;
}

Widget* WidgetPropertiesReader0250::widgetFromJsonDictionary(JsonDictionary *data)
{
    DictionaryHelper* dicHelper = DICTOOL;
    Widget* widget = nullptr;
    const char* classname = dicHelper->getStringValue_json(data, "classname");
    JsonDictionary* uiOptions = dicHelper->getSubDictionary_json(data, "options");
    if (classname && strcmp(classname, "Button") == 0)
    {
        widget = cocos2d::gui::Button::create();
        setPropsForButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "CheckBox") == 0)
    {
        widget = CheckBox::create();
        setPropsForCheckBoxFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Label") == 0)
    {
        widget = cocos2d::gui::Label::create();
        setPropsForLabelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelAtlas") == 0)
    {
        widget = cocos2d::gui::LabelAtlas::create();
        setPropsForLabelAtlasFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LoadingBar") == 0)
    {
        widget = cocos2d::gui::LoadingBar::create();
        setPropsForLoadingBarFromJsonDictionary(widget, uiOptions);
    }else if (classname && strcmp(classname, "ScrollView") == 0){
        widget = cocos2d::gui::ScrollView::create();
        setPropsForScrollViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextArea") == 0)
    {
        widget = cocos2d::gui::Label::create();
        setPropsForLabelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextButton") == 0)
    {
        widget = cocos2d::gui::Button::create();
        setPropsForButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextField") == 0)
    {
        widget = cocos2d::gui::TextField::create();
        setPropsForTextFieldFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "ImageView") == 0)
    {
        widget = cocos2d::gui::ImageView::create();
        setPropsForImageViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Panel") == 0)
    {
        widget = Layout::create();
        setPropsForLayoutFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Slider") == 0)
    {
        widget = cocos2d::gui::Slider::create();
        setPropsForSliderFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelBMFont") == 0)
    {
        widget = cocos2d::gui::LabelBMFont::create();
        setPropsForLabelBMFontFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "DragPanel") == 0)
    {
        widget = cocos2d::gui::ScrollView::create();
        setPropsForScrollViewFromJsonDictionary(widget, uiOptions);
    }
    
    int childrenCount = dicHelper->getArrayCount_json(data, "children");
    for (int i=0;i<childrenCount;i++)
    {
        JsonDictionary* subData = dicHelper->getDictionaryFromArray_json(data, "children", i);
        Widget* child = widgetFromJsonDictionary(subData);
        if (child)
        {
            widget->addChild(child);
        }
        CC_SAFE_DELETE(subData);
    }
    
    CC_SAFE_DELETE(uiOptions);
    return widget;
}

void WidgetPropertiesReader0250::setPropsForWidgetFromJsonDictionary(Widget*widget,JsonDictionary *options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    bool ignoreSizeExsit = dicHelper->checkObjectExist_json(options, "ignoreSize");
    if (ignoreSizeExsit)
    {
        widget->ignoreContentAdaptWithSize(dicHelper->getBooleanValue_json(options, "ignoreSize"));
    }
    
    float w = dicHelper->getFloatValue_json(options, "width");
    float h = dicHelper->getFloatValue_json(options, "height");
    widget->setSize(Size(w, h));
    
    widget->setTag(dicHelper->getIntValue_json(options, "tag"));
    widget->setActionTag(dicHelper->getIntValue_json(options, "actiontag"));
    widget->setTouchEnabled(dicHelper->getBooleanValue_json(options, "touchAble"));
    const char* name = dicHelper->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = dicHelper->getFloatValue_json(options, "x");
    float y = dicHelper->getFloatValue_json(options, "y");
    widget->setPosition(Point(x,y));
    bool sx = dicHelper->checkObjectExist_json(options, "scaleX");
    if (sx)
    {
        widget->setScaleX(dicHelper->getFloatValue_json(options, "scaleX"));
    }
    bool sy = dicHelper->checkObjectExist_json(options, "scaleY");
    if (sy)
    {
        widget->setScaleY(dicHelper->getFloatValue_json(options, "scaleY"));
    }
    bool rt = dicHelper->checkObjectExist_json(options, "rotation");
    if (rt)
    {
        widget->setRotation(dicHelper->getFloatValue_json(options, "rotation"));
    }
    bool vb = dicHelper->checkObjectExist_json(options, "visible");
    if (vb)
    {
        widget->setVisible(dicHelper->getBooleanValue_json(options, "visible"));
    }
    int z = dicHelper->getIntValue_json(options, "ZOrder");
    widget->setZOrder(z);
}

void WidgetPropertiesReader0250::setColorPropsForWidgetFromJsonDictionary(Widget *widget, JsonDictionary *options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    bool op = dicHelper->checkObjectExist_json(options, "opacity");
    if (op)
    {
        widget->setOpacity(dicHelper->getIntValue_json(options, "opacity"));
    }
    bool cr = dicHelper->checkObjectExist_json(options, "colorR");
    bool cg = dicHelper->checkObjectExist_json(options, "colorG");
    bool cb = dicHelper->checkObjectExist_json(options, "colorB");
    int colorR = cr ? dicHelper->getIntValue_json(options, "colorR") : 255;
    int colorG = cg ? dicHelper->getIntValue_json(options, "colorG") : 255;
    int colorB = cb ? dicHelper->getIntValue_json(options, "colorB") : 255;
    widget->setColor(Color3B(colorR, colorG, colorB));
    bool apx = dicHelper->checkObjectExist_json(options, "anchorPointX");
    float apxf = apx ? dicHelper->getFloatValue_json(options, "anchorPointX") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    bool apy = dicHelper->checkObjectExist_json(options, "anchorPointY");
    float apyf = apy ? dicHelper->getFloatValue_json(options, "anchorPointY") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    widget->setAnchorPoint(Point(apxf, apyf));
    bool flipX = dicHelper->getBooleanValue_json(options, "flipX");
    bool flipY = dicHelper->getBooleanValue_json(options, "flipY");
    widget->setFlipX(flipX);
    widget->setFlipY(flipY);
}

void WidgetPropertiesReader0250::setPropsForButtonFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::Button* button = static_cast<Button*>(widget);
    bool scale9Enable = dicHelper->getBooleanValue_json(options, "scale9Enable");
    button->setScale9Enabled(scale9Enable);
    
    std::string tp_n = m_strFilePath;
    std::string tp_p = m_strFilePath;
    std::string tp_d = m_strFilePath;
    
    const char* normalFileName = dicHelper->getStringValue_json(options, "normal");
    const char* pressedFileName = dicHelper->getStringValue_json(options, "pressed");
    const char* disabledFileName = dicHelper->getStringValue_json(options, "disabled");
    
    const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
    const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
    const char* disabledFileName_tp =  (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
    bool useMergedTexture = dicHelper->getBooleanValue_json(options, "useMergedTexture");
    if (scale9Enable)
    {
        float cx = dicHelper->getFloatValue_json(options, "capInsetsX");
        float cy = dicHelper->getFloatValue_json(options, "capInsetsY");
        float cw = dicHelper->getFloatValue_json(options, "capInsetsWidth");
        float ch = dicHelper->getFloatValue_json(options, "capInsetsHeight");
        
        if (useMergedTexture)
        {
            button->loadTextures(normalFileName, pressedFileName, disabledFileName,UI_TEX_TYPE_PLIST);
        }
        else
        {
            button->loadTextures(normalFileName_tp, pressedFileName_tp, disabledFileName_tp);
        }
        button->setCapInsets(Rect(cx, cy, cw, ch));
        bool sw = dicHelper->checkObjectExist_json(options, "scale9Width");
        bool sh = dicHelper->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = dicHelper->getFloatValue_json(options, "scale9Width");
            float shf = dicHelper->getFloatValue_json(options, "scale9Height");
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
    bool tt = dicHelper->checkObjectExist_json(options, "text");
    if (tt)
    {
        const char* text = dicHelper->getStringValue_json(options, "text");
        if (text)
        {
            button->setTitleText(text);
        }
    }
    bool cr = dicHelper->checkObjectExist_json(options, "textColorR");
    bool cg = dicHelper->checkObjectExist_json(options, "textColorG");
    bool cb = dicHelper->checkObjectExist_json(options, "textColorB");
    int cri = cr?dicHelper->getIntValue_json(options, "textColorR"):255;
    int cgi = cg?dicHelper->getIntValue_json(options, "textColorG"):255;
    int cbi = cb?dicHelper->getIntValue_json(options, "textColorB"):255;
    button->setTitleColor(Color3B(cri,cgi,cbi));
    bool fs = dicHelper->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        button->setTitleFontSize(dicHelper->getIntValue_json(options, "fontSize"));
    }
    bool fn = dicHelper->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        button->setTitleFontName(dicHelper->getStringValue_json(options, "fontName"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForCheckBoxFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    CheckBox* checkBox = static_cast<CheckBox*>(widget);
    const char* backGroundFileName = dicHelper->getStringValue_json(options, "backGroundBox");
    const char* backGroundSelectedFileName = dicHelper->getStringValue_json(options, "backGroundBoxSelected");
    const char* frontCrossFileName = dicHelper->getStringValue_json(options, "frontCross");
    const char* backGroundDisabledFileName = dicHelper->getStringValue_json(options, "backGroundBoxDisabled");
    const char* frontCrossDisabledFileName = dicHelper->getStringValue_json(options, "frontCrossDisabled");
    
    
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
    bool useMergedTexture = dicHelper->getBooleanValue_json(options, "useMergedTexture");
    
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

void WidgetPropertiesReader0250::setPropsForImageViewFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::gui::ImageView* imageView = static_cast<ImageView*>(widget);
    const char* imageFileName = dicHelper->getStringValue_json(options, "fileName");
    bool scale9EnableExist = dicHelper->checkObjectExist_json(options, "scale9Enable");
    bool scale9Enable = false;
    if (scale9EnableExist)
    {
        scale9Enable = dicHelper->getBooleanValue_json(options, "scale9Enable");
    }
    imageView->setScale9Enabled(scale9Enable);
    
    std::string tp_i = m_strFilePath;
    const char* imageFileName_tp = nullptr;
    if (imageFileName && (strcmp(imageFileName, "") != 0))
    {
        imageFileName_tp = tp_i.append(imageFileName).c_str();
    }
    
    bool useMergedTexture = dicHelper->getBooleanValue_json(options, "useMergedTexture");
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
        
        bool sw = dicHelper->checkObjectExist_json(options, "scale9Width");
        bool sh = dicHelper->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = dicHelper->getFloatValue_json(options, "scale9Width");
            float shf = dicHelper->getFloatValue_json(options, "scale9Height");
            imageView->setSize(Size(swf, shf));
        }
        
        float cx = dicHelper->getFloatValue_json(options, "capInsetsX");
        float cy = dicHelper->getFloatValue_json(options, "capInsetsY");
        float cw = dicHelper->getFloatValue_json(options, "capInsetsWidth");
        float ch = dicHelper->getFloatValue_json(options, "capInsetsHeight");
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

void WidgetPropertiesReader0250::setPropsForLabelFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::Label* label = static_cast<cocos2d::gui::Label*>(widget);
    bool touchScaleChangeAble = dicHelper->getBooleanValue_json(options, "touchScaleEnable");
    label->setTouchScaleChangeEnabled(touchScaleChangeAble);
    const char* text = dicHelper->getStringValue_json(options, "text");
    label->setText(text);
    bool fs = dicHelper->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        label->setFontSize(dicHelper->getIntValue_json(options, "fontSize"));
    }
    bool fn = dicHelper->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        label->setFontName(dicHelper->getStringValue_json(options, "fontName"));
    }
    bool aw = dicHelper->checkObjectExist_json(options, "areaWidth");
    bool ah = dicHelper->checkObjectExist_json(options, "areaHeight");
    if (aw && ah)
    {
        Size size = Size(dicHelper->getFloatValue_json(options, "areaWidth"),dicHelper->getFloatValue_json(options,"areaHeight"));
        label->setTextAreaSize(size);
    }
    bool ha = dicHelper->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        label->setTextHorizontalAlignment((TextHAlignment)dicHelper->getIntValue_json(options, "hAlignment"));
    }
    bool va = dicHelper->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        label->setTextVerticalAlignment((TextVAlignment)dicHelper->getIntValue_json(options, "vAlignment"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLabelAtlasFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::LabelAtlas* labelAtlas = static_cast<cocos2d::gui::LabelAtlas*>(widget);
    bool sv = dicHelper->checkObjectExist_json(options, "stringValue");
    bool cmf = dicHelper->checkObjectExist_json(options, "charMapFile");
    bool iw = dicHelper->checkObjectExist_json(options, "itemWidth");
    bool ih = dicHelper->checkObjectExist_json(options, "itemHeight");
    bool scm = dicHelper->checkObjectExist_json(options, "startCharMap");
    if (sv && cmf && iw && ih && scm && (strcmp(dicHelper->getStringValue_json(options, "charMapFile"), "") != 0))
    {
        std::string tp_c = m_strFilePath;
        const char* cmf_tp = nullptr;
        const char* cmft = dicHelper->getStringValue_json(options, "charMapFile");
        cmf_tp = tp_c.append(cmft).c_str();
        
        labelAtlas->setProperty(dicHelper->getStringValue_json(options, "stringValue"),cmf_tp,dicHelper->getIntValue_json(options, "itemWidth"),dicHelper->getIntValue_json(options,"itemHeight"),dicHelper->getStringValue_json(options, "startCharMap"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLayoutFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    
    setPropsForWidgetFromJsonDictionary(widget, options);
    Layout* containerWidget = static_cast<Layout*>(widget);
    if (!dynamic_cast<cocos2d::gui::ScrollView*>(containerWidget)
        && !dynamic_cast<cocos2d::gui::ListView*>(containerWidget))
    {
        containerWidget->setClippingEnabled(dicHelper->getBooleanValue_json(options, "clipAble"));
    }
    Layout* panel = (Layout*)widget;
    bool backGroundScale9Enable = dicHelper->getBooleanValue_json(options, "backGroundScale9Enable");
    panel->setBackGroundImageScale9Enabled(backGroundScale9Enable);
    int cr = dicHelper->getIntValue_json(options, "bgColorR");
    int cg = dicHelper->getIntValue_json(options, "bgColorG");
    int cb = dicHelper->getIntValue_json(options, "bgColorB");
    
    int scr = dicHelper->getIntValue_json(options, "bgStartColorR");
    int scg = dicHelper->getIntValue_json(options, "bgStartColorG");
    int scb = dicHelper->getIntValue_json(options, "bgStartColorB");
    
    int ecr = dicHelper->getIntValue_json(options, "bgEndColorR");
    int ecg = dicHelper->getIntValue_json(options, "bgEndColorG");
    int ecb = dicHelper->getIntValue_json(options, "bgEndColorB");
    
    float bgcv1 = dicHelper->getFloatValue_json(options, "vectorX");
    float bgcv2 = dicHelper->getFloatValue_json(options, "vectorY");
    panel->setBackGroundColorVector(Point(bgcv1, bgcv2));
    
    int co = dicHelper->getIntValue_json(options, "bgColorOpacity");
    
    int colorType = dicHelper->getIntValue_json(options, "colorType");
    panel->setBackGroundColorType(LayoutBackGroundColorType(colorType));
    panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
    panel->setBackGroundColor(Color3B(cr, cg, cb));
    panel->setBackGroundColorOpacity(co);
    
    std::string tp_b = m_strFilePath;
    const char* imageFileName = dicHelper->getStringValue_json(options, "backGroundImage");
    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
    bool useMergedTexture = dicHelper->getBooleanValue_json(options, "useMergedTexture");
    if (backGroundScale9Enable)
    {
        float cx = dicHelper->getFloatValue_json(options, "capInsetsX");
        float cy = dicHelper->getFloatValue_json(options, "capInsetsY");
        float cw = dicHelper->getFloatValue_json(options, "capInsetsWidth");
        float ch = dicHelper->getFloatValue_json(options, "capInsetsHeight");
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

void WidgetPropertiesReader0250::setPropsForScrollViewFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForLayoutFromJsonDictionary(widget, options);
    cocos2d::gui::ScrollView* scrollView = static_cast<cocos2d::gui::ScrollView*>(widget);
    float innerWidth = dicHelper->getFloatValue_json(options, "innerWidth");
    float innerHeight = dicHelper->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
    int direction = dicHelper->getFloatValue_json(options, "direction");
    scrollView->setDirection((SCROLLVIEW_DIR)direction);
    scrollView->setBounceEnabled(dicHelper->getBooleanValue_json(options, "bounceEnable"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForSliderFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::Slider* slider = static_cast<cocos2d::gui::Slider*>(widget);
    
    bool barTextureScale9Enable = dicHelper->getBooleanValue_json(options, "barTextureScale9Enable");
    slider->setScale9Enabled(barTextureScale9Enable);
    bool bt = dicHelper->checkObjectExist_json(options, "barFileName");
    float barLength = dicHelper->getFloatValue_json(options, "length");
    bool useMergedTexture = dicHelper->getBooleanValue_json(options, "useMergedTexture");
    if (bt)
    {
        if (barTextureScale9Enable)
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = dicHelper->getStringValue_json(options, "barFileName");
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
            const char* imageFileName = dicHelper->getStringValue_json(options, "barFileName");
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
    
    const char* normalFileName = dicHelper->getStringValue_json(options, "ballNormal");
    const char* pressedFileName = dicHelper->getStringValue_json(options, "ballPressed");
    const char* disabledFileName = dicHelper->getStringValue_json(options, "ballDisabled");
    
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
    slider->setPercent(dicHelper->getIntValue_json(options, "percent"));
    
    std::string tp_b = m_strFilePath;
    const char* imageFileName = dicHelper->getStringValue_json(options, "progressBarFileName");
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

void WidgetPropertiesReader0250::setPropsForTextFieldFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::TextField* textField = static_cast<cocos2d::gui::TextField*>(widget);
    bool ph = dicHelper->checkObjectExist_json(options, "placeHolder");
    if (ph)
    {
        textField->setPlaceHolder(dicHelper->getStringValue_json(options, "placeHolder"));
    }
    textField->setText(dicHelper->getStringValue_json(options, "text"));
    bool fs = dicHelper->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        textField->setFontSize(dicHelper->getIntValue_json(options, "fontSize"));
    }
    bool fn = dicHelper->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        textField->setFontName(dicHelper->getStringValue_json(options, "fontName"));
    }
    bool tsw = dicHelper->checkObjectExist_json(options, "touchSizeWidth");
    bool tsh = dicHelper->checkObjectExist_json(options, "touchSizeHeight");
    if (tsw && tsh)
    {
        textField->setTouchSize(Size(dicHelper->getFloatValue_json(options, "touchSizeWidth"), dicHelper->getFloatValue_json(options,"touchSizeHeight")));
    }
    
    float dw = dicHelper->getFloatValue_json(options, "width");
    float dh = dicHelper->getFloatValue_json(options, "height");
    if (dw > 0.0f || dh > 0.0f)
    {
        //textField->setSize(Size(dw, dh));
    }
    bool maxLengthEnable = dicHelper->getBooleanValue_json(options, "maxLengthEnable");
    textField->setMaxLengthEnabled(maxLengthEnable);
    
    if (maxLengthEnable)
    {
        int maxLength = dicHelper->getIntValue_json(options, "maxLength");
        textField->setMaxLength(maxLength);
    }
    bool passwordEnable = dicHelper->getBooleanValue_json(options, "passwordEnable");
    textField->setPasswordEnabled(passwordEnable);
    if (passwordEnable)
    {
        textField->setPasswordStyleText(dicHelper->getStringValue_json(options, "passwordStyleText"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLoadingBarFromJsonDictionary(Widget *widget, JsonDictionary *options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::LoadingBar* loadingBar = static_cast<cocos2d::gui::LoadingBar*>(widget);
    bool useMergedTexture = dicHelper->getBooleanValue_json(options, "useMergedTexture");
    std::string tp_b = m_strFilePath;
    const char*imageFileName =  dicHelper->getStringValue_json(options, "texture");
    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
    if (useMergedTexture)
    {
        loadingBar->loadTexture(imageFileName,UI_TEX_TYPE_PLIST);
    }
    else
    {
        loadingBar->loadTexture(imageFileName_tp);
    }
    loadingBar->setDirection(LoadingBarType(dicHelper->getIntValue_json(options, "direction")));
    loadingBar->setPercent(dicHelper->getIntValue_json(options, "percent"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0250::setPropsForLabelBMFontFromJsonDictionary(Widget *widget, JsonDictionary *options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::gui::LabelBMFont* labelBMFont = static_cast<cocos2d::gui::LabelBMFont*>(widget);
    
    std::string tp_c = m_strFilePath;
    const char* cmf_tp = nullptr;
    const char* cmft = dicHelper->getStringValue_json(options, "fileName");
    cmf_tp = tp_c.append(cmft).c_str();
    
    labelBMFont->setFntFile(cmf_tp);
    
    const char* text = dicHelper->getStringValue_json(options, "text");
    labelBMFont->setText(text);
    
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}


/*0.3.0.0~1.0.0.0*/
Widget* WidgetPropertiesReader0300::createWidget(JsonDictionary* data, const char* fullPath, const char* fileName)
{
    m_strFilePath = fullPath;
    DictionaryHelper* dicHelper = DICTOOL;
    int texturesCount = dicHelper->getArrayCount_json(data, "textures");
    
    for (int i=0; i<texturesCount; i++)
    {
        const char* file = dicHelper->getStringValueFromArray_json(data, "textures", i);
        std::string tp = fullPath;
        tp.append(file);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(tp.c_str());
    }
    float fileDesignWidth = dicHelper->getFloatValue_json(data, "designWidth");
    float fileDesignHeight = dicHelper->getFloatValue_json(data, "designHeight");
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
        printf("Read design size error!\n");
        Size winSize = Director::getInstance()->getWinSize();
        GUIReader::shareReader()->storeFileDesignSize(fileName, winSize);
    }
    else
    {
        GUIReader::shareReader()->storeFileDesignSize(fileName, Size(fileDesignWidth, fileDesignHeight));
    }
    JsonDictionary* widgetTree = dicHelper->getSubDictionary_json(data, "widgetTree");
    Widget* widget = widgetFromJsonDictionary(widgetTree);
    
    /* *********temp********* */
    if (widget->getContentSize().equals(Size::ZERO))
    {
        Layout* rootWidget = dynamic_cast<Layout*>(widget);
        rootWidget->setSize(Size(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    //    widget->setFileDesignSize(Size(fileDesignWidth, fileDesignHeight));
    JsonDictionary* actions = dicHelper->getSubDictionary_json(data, "animation");
    /* *********temp********* */
    //    ActionManager::shareManager()->releaseActions();
    /* ********************** */
    CCLOG("file name == [%s]",fileName);
    Object* rootWidget = (Object*) widget;
    ActionManagerEx::shareManager()->initWithDictionary(fileName,actions,rootWidget);
    CC_SAFE_DELETE(widgetTree);
    CC_SAFE_DELETE(actions);
    return widget;
}

Widget* WidgetPropertiesReader0300::widgetFromJsonDictionary(JsonDictionary *data)
{
    DictionaryHelper* dicHelper = DICTOOL;
    Widget* widget = nullptr;
    const char* classname = dicHelper->getStringValue_json(data, "classname");
    JsonDictionary* uiOptions = dicHelper->getSubDictionary_json(data, "options");
    if (classname && strcmp(classname, "Button") == 0)
    {
        widget = cocos2d::gui::Button::create();
        setPropsForButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "CheckBox") == 0)
    {
        widget = CheckBox::create();
        setPropsForCheckBoxFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Label") == 0)
    {
        widget = cocos2d::gui::Label::create();
        setPropsForLabelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelAtlas") == 0)
    {
        widget = cocos2d::gui::LabelAtlas::create();
        setPropsForLabelAtlasFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LoadingBar") == 0)
    {
        widget = cocos2d::gui::LoadingBar::create();
        setPropsForLoadingBarFromJsonDictionary(widget, uiOptions);
    }else if (classname && strcmp(classname, "ScrollView") == 0){
        widget = cocos2d::gui::ScrollView::create();
        setPropsForScrollViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextArea") == 0)
    {
        widget = cocos2d::gui::Label::create();
        setPropsForLabelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextButton") == 0)
    {
        widget = cocos2d::gui::Button::create();
        setPropsForButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextField") == 0)
    {
        widget = cocos2d::gui::TextField::create();
        setPropsForTextFieldFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "ImageView") == 0)
    {
        widget = cocos2d::gui::ImageView::create();
        setPropsForImageViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Panel") == 0)
    {
        widget = Layout::create();
        setPropsForLayoutFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Slider") == 0)
    {
        widget = cocos2d::gui::Slider::create();
        setPropsForSliderFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelBMFont") == 0)
    {
        widget = cocos2d::gui::LabelBMFont::create();
        setPropsForLabelBMFontFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "DragPanel") == 0)
    {
        widget = cocos2d::gui::ScrollView::create();
        setPropsForScrollViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "ListView") == 0)
    {
        widget = cocos2d::gui::ListView::create();
        setPropsForListViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "PageView") == 0)
    {
        widget = cocos2d::gui::PageView::create();
        setPropsForPageViewFromJsonDictionary(widget, uiOptions);
    }
    
    int childrenCount = dicHelper->getArrayCount_json(data, "children");
    for (int i=0;i<childrenCount;i++)
    {
        JsonDictionary* subData = dicHelper->getDictionaryFromArray_json(data, "children", i);
        Widget* child = widgetFromJsonDictionary(subData);
        if (child)
        {
            widget->addChild(child);
        }
        CC_SAFE_DELETE(subData);
    }
    
    CC_SAFE_DELETE(uiOptions);
    return widget;
}

void WidgetPropertiesReader0300::setPropsForWidgetFromJsonDictionary(Widget*widget,JsonDictionary *options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    bool ignoreSizeExsit = dicHelper->checkObjectExist_json(options, "ignoreSize");
    if (ignoreSizeExsit)
    {
        widget->ignoreContentAdaptWithSize(dicHelper->getBooleanValue_json(options, "ignoreSize"));
    }
    
    widget->setSizeType((SizeType)dicHelper->getIntValue_json(options, "sizeType"));
    widget->setPositionType((PositionType)dicHelper->getIntValue_json(options, "positionType"));
    
    widget->setSizePercent(Point(dicHelper->getFloatValue_json(options, "sizePercentX"), dicHelper->getFloatValue_json(options, "sizePercentY")));
    widget->setPositionPercent(Point(dicHelper->getFloatValue_json(options, "positionPercentX"), dicHelper->getFloatValue_json(options, "positionPercentY")));
    
    float w = dicHelper->getFloatValue_json(options, "width");
    float h = dicHelper->getFloatValue_json(options, "height");
    widget->setSize(Size(w, h));
    
    widget->setTag(dicHelper->getIntValue_json(options, "tag"));
    widget->setActionTag(dicHelper->getIntValue_json(options, "actiontag"));
    widget->setTouchEnabled(dicHelper->getBooleanValue_json(options, "touchAble"));
    const char* name = dicHelper->getStringValue_json(options, "name");
    const char* widgetName = name?name:"default";
    widget->setName(widgetName);
    float x = dicHelper->getFloatValue_json(options, "x");
    float y = dicHelper->getFloatValue_json(options, "y");
    widget->setPosition(Point(x,y));
    bool sx = dicHelper->checkObjectExist_json(options, "scaleX");
    if (sx)
    {
        widget->setScaleX(dicHelper->getFloatValue_json(options, "scaleX"));
    }
    bool sy = dicHelper->checkObjectExist_json(options, "scaleY");
    if (sy)
    {
        widget->setScaleY(dicHelper->getFloatValue_json(options, "scaleY"));
    }
    bool rt = dicHelper->checkObjectExist_json(options, "rotation");
    if (rt)
    {
        widget->setRotation(dicHelper->getFloatValue_json(options, "rotation"));
    }
    bool vb = dicHelper->checkObjectExist_json(options, "visible");
    if (vb)
    {
        widget->setVisible(dicHelper->getBooleanValue_json(options, "visible"));
    }
    int z = dicHelper->getIntValue_json(options, "ZOrder");
    widget->setZOrder(z);

    JsonDictionary* layoutParameterDic = dicHelper->getSubDictionary_json(options, "layoutParameter");
    if (layoutParameterDic)
    {
        int paramType = dicHelper->getIntValue_json(layoutParameterDic, "type");
        LayoutParameter* parameter = nullptr;
        switch (paramType)
        {
            case 0:
                break;
            case 1:
            {
                parameter = LinearLayoutParameter::create();
                int gravity = dicHelper->getIntValue_json(layoutParameterDic, "gravity");
                ((LinearLayoutParameter*)parameter)->setGravity((LinearGravity)gravity);
                break;
            }
            case 2:
            {
                parameter = RelativeLayoutParameter::create();
                RelativeLayoutParameter* rParameter = (RelativeLayoutParameter*)parameter;
                const char* relativeName = dicHelper->getStringValue_json(layoutParameterDic, "relativeName");
                rParameter->setRelativeName(relativeName);
                const char* relativeToName = dicHelper->getStringValue_json(layoutParameterDic, "relativeToName");
                rParameter->setRelativeToWidgetName(relativeToName);
                int align = dicHelper->getIntValue_json(layoutParameterDic, "align");
                rParameter->setAlign((RelativeAlign)align);
                break;
            }
            default:
                break;
        }
        if (parameter)
        {
            float mgl = dicHelper->getFloatValue_json(layoutParameterDic, "marginLeft");
            float mgt = dicHelper->getFloatValue_json(layoutParameterDic, "marginTop");
            float mgr = dicHelper->getFloatValue_json(layoutParameterDic, "marginRight");
            float mgb = dicHelper->getFloatValue_json(layoutParameterDic, "marginDown");
            parameter->setMargin(Margin(mgl, mgt, mgr, mgb));
            widget->setLayoutParameter(parameter);
        }
    }
    CC_SAFE_DELETE(layoutParameterDic);
}

void WidgetPropertiesReader0300::setColorPropsForWidgetFromJsonDictionary(Widget *widget, JsonDictionary *options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    bool op = dicHelper->checkObjectExist_json(options, "opacity");
    if (op)
    {
        widget->setOpacity(dicHelper->getIntValue_json(options, "opacity"));
    }
    bool cr = dicHelper->checkObjectExist_json(options, "colorR");
    bool cg = dicHelper->checkObjectExist_json(options, "colorG");
    bool cb = dicHelper->checkObjectExist_json(options, "colorB");
    int colorR = cr ? dicHelper->getIntValue_json(options, "colorR") : 255;
    int colorG = cg ? dicHelper->getIntValue_json(options, "colorG") : 255;
    int colorB = cb ? dicHelper->getIntValue_json(options, "colorB") : 255;
    widget->setColor(Color3B(colorR, colorG, colorB));
    bool apx = dicHelper->checkObjectExist_json(options, "anchorPointX");
    float apxf = apx ? dicHelper->getFloatValue_json(options, "anchorPointX") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    bool apy = dicHelper->checkObjectExist_json(options, "anchorPointY");
    float apyf = apy ? dicHelper->getFloatValue_json(options, "anchorPointY") : ((widget->getWidgetType() == WidgetTypeWidget) ? 0.5f : 0.0f);
    widget->setAnchorPoint(Point(apxf, apyf));
    bool flipX = dicHelper->getBooleanValue_json(options, "flipX");
    bool flipY = dicHelper->getBooleanValue_json(options, "flipY");
    widget->setFlipX(flipX);
    widget->setFlipY(flipY);
}

void WidgetPropertiesReader0300::setPropsForButtonFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::Button* button = static_cast<cocos2d::gui::Button*>(widget);
    bool scale9Enable = dicHelper->getBooleanValue_json(options, "scale9Enable");
    button->setScale9Enabled(scale9Enable);
    
    JsonDictionary* normalDic = dicHelper->getSubDictionary_json(options, "normalData");
    int normalType = dicHelper->getIntValue_json(normalDic, "resourceType");
    switch (normalType)
    {
        case 0:
        {
            std::string tp_n = m_strFilePath;
            const char* normalFileName = dicHelper->getStringValue_json(normalDic, "path");
            const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
            button->loadTextureNormal(normalFileName_tp);
            break;
        }
        case 1:
        {
            const char* normalFileName = dicHelper->getStringValue_json(normalDic, "path");
            button->loadTextureNormal(normalFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(normalDic);
    JsonDictionary* pressedDic = dicHelper->getSubDictionary_json(options, "pressedData");
    int pressedType = dicHelper->getIntValue_json(pressedDic, "resourceType");
    switch (pressedType)
    {
        case 0:
        {
            std::string tp_p = m_strFilePath;
            const char* pressedFileName = dicHelper->getStringValue_json(pressedDic, "path");
            const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
            button->loadTexturePressed(pressedFileName_tp);
            break;
        }
        case 1:
        {
            const char* pressedFileName = dicHelper->getStringValue_json(pressedDic, "path");
            button->loadTexturePressed(pressedFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(pressedDic);
    JsonDictionary* disabledDic = dicHelper->getSubDictionary_json(options, "disabledData");
    int disabledType = dicHelper->getIntValue_json(disabledDic, "resourceType");
    switch (disabledType)
    {
        case 0:
        {
            std::string tp_d = m_strFilePath;
            const char* disabledFileName = dicHelper->getStringValue_json(disabledDic, "path");
            const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
            button->loadTextureDisabled(disabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* disabledFileName = dicHelper->getStringValue_json(disabledDic, "path");
            button->loadTextureDisabled(disabledFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(disabledDic);
    if (scale9Enable)
    {
        float cx = dicHelper->getFloatValue_json(options, "capInsetsX");
        float cy = dicHelper->getFloatValue_json(options, "capInsetsY");
        float cw = dicHelper->getFloatValue_json(options, "capInsetsWidth");
        float ch = dicHelper->getFloatValue_json(options, "capInsetsHeight");
        
        button->setCapInsets(Rect(cx, cy, cw, ch));
        bool sw = dicHelper->checkObjectExist_json(options, "scale9Width");
        bool sh = dicHelper->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = dicHelper->getFloatValue_json(options, "scale9Width");
            float shf = dicHelper->getFloatValue_json(options, "scale9Height");
            button->setSize(Size(swf, shf));
        }
    }
    bool tt = dicHelper->checkObjectExist_json(options, "text");
    if (tt)
    {
        const char* text = dicHelper->getStringValue_json(options, "text");
        if (text)
        {
            button->setTitleText(text);
        }
    }
    
    bool cr = dicHelper->checkObjectExist_json(options, "textColorR");
    bool cg = dicHelper->checkObjectExist_json(options, "textColorG");
    bool cb = dicHelper->checkObjectExist_json(options, "textColorB");
    int cri = cr?dicHelper->getIntValue_json(options, "textColorR"):255;
    int cgi = cg?dicHelper->getIntValue_json(options, "textColorG"):255;
    int cbi = cb?dicHelper->getIntValue_json(options, "textColorB"):255;
    button->setTitleColor(Color3B(cri,cgi,cbi));
    bool fs = dicHelper->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        button->setTitleFontSize(dicHelper->getIntValue_json(options, "fontSize"));
    }
    bool fn = dicHelper->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        button->setTitleFontName(dicHelper->getStringValue_json(options, "fontName"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForCheckBoxFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    CheckBox* checkBox = static_cast<cocos2d::gui::CheckBox*>(widget);
    
    JsonDictionary* backGroundDic = dicHelper->getSubDictionary_json(options, "backGroundBoxData");
    int backGroundType = dicHelper->getIntValue_json(backGroundDic, "resourceType");
    switch (backGroundType)
    {
        case 0:
        {
            std::string tp_b = m_strFilePath;
            const char* backGroundFileName = dicHelper->getStringValue_json(backGroundDic, "path");
            const char* backGroundFileName_tp = (backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():nullptr;
            checkBox->loadTextureBackGround(backGroundFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundFileName = dicHelper->getStringValue_json(backGroundDic, "path");
            checkBox->loadTextureBackGround(backGroundFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(backGroundDic);
    
    JsonDictionary* backGroundSelectedDic = dicHelper->getSubDictionary_json(options, "backGroundBoxSelectedData");
    int backGroundSelectedType = dicHelper->getIntValue_json(backGroundSelectedDic, "resourceType");
    switch (backGroundSelectedType)
    {
        case 0:
        {
            std::string tp_bs = m_strFilePath;
            const char* backGroundSelectedFileName = dicHelper->getStringValue_json(backGroundSelectedDic, "path");
            const char* backGroundSelectedFileName_tp = (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():nullptr;
            checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundSelectedFileName = dicHelper->getStringValue_json(backGroundSelectedDic, "path");
            checkBox->loadTextureBackGroundSelected(backGroundSelectedFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(backGroundSelectedDic);
    
    JsonDictionary* frontCrossDic = dicHelper->getSubDictionary_json(options, "frontCrossData");
    int frontCrossType = dicHelper->getIntValue_json(frontCrossDic, "resourceType");
    switch (frontCrossType)
    {
        case 0:
        {
            std::string tp_c = m_strFilePath;
            const char* frontCrossFileName = dicHelper->getStringValue_json(frontCrossDic, "path");
            const char* frontCrossFileName_tp = (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():nullptr;
            checkBox->loadTextureFrontCross(frontCrossFileName_tp);
            break;
        }
        case 1:
        {
            const char* frontCrossFileName = dicHelper->getStringValue_json(frontCrossDic, "path");
            checkBox->loadTextureFrontCross(frontCrossFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(frontCrossDic);
    
    JsonDictionary* backGroundDisabledDic = dicHelper->getSubDictionary_json(options, "backGroundBoxDisabledData");
    int backGroundDisabledType = dicHelper->getIntValue_json(backGroundDisabledDic, "resourceType");
    switch (backGroundDisabledType)
    {
        case 0:
        {
            std::string tp_bd = m_strFilePath;
            const char* backGroundDisabledFileName = dicHelper->getStringValue_json(backGroundDisabledDic, "path");
            const char* backGroundDisabledFileName_tp = (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():nullptr;
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* backGroundDisabledFileName = dicHelper->getStringValue_json(backGroundDisabledDic, "path");
            checkBox->loadTextureBackGroundDisabled(backGroundDisabledFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(backGroundDisabledDic);
    
    JsonDictionary* frontCrossDisabledDic = dicHelper->getSubDictionary_json(options, "frontCrossDisabledData");
    int frontCrossDisabledType = dicHelper->getIntValue_json(frontCrossDisabledDic, "resourceType");
    switch (frontCrossDisabledType)
    {
        case 0:
        {
            std::string tp_cd = m_strFilePath;
            const char* frontCrossDisabledFileName = dicHelper->getStringValue_json(options, "path");
            const char* frontCrossDisabledFileName_tp = (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():nullptr;
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* frontCrossDisabledFileName = dicHelper->getStringValue_json(options, "path");
            checkBox->loadTextureFrontCrossDisabled(frontCrossDisabledFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(frontCrossDisabledDic);
    
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForImageViewFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::gui::ImageView* imageView = static_cast<cocos2d::gui::ImageView*>(widget);
    
    JsonDictionary* imageFileNameDic = dicHelper->getSubDictionary_json(options, "fileNameData");
    int imageFileNameType = dicHelper->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_i = m_strFilePath;
            const char* imageFileName = dicHelper->getStringValue_json(imageFileNameDic, "path");
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
            const char* imageFileName = dicHelper->getStringValue_json(imageFileNameDic, "path");
            imageView->loadTexture(imageFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(imageFileNameDic);
    
    bool scale9EnableExist = dicHelper->checkObjectExist_json(options, "scale9Enable");
    bool scale9Enable = false;
    if (scale9EnableExist)
    {
        scale9Enable = dicHelper->getBooleanValue_json(options, "scale9Enable");
    }
    imageView->setScale9Enabled(scale9Enable);
    
    
    if (scale9Enable)
    {
        bool sw = dicHelper->checkObjectExist_json(options, "scale9Width");
        bool sh = dicHelper->checkObjectExist_json(options, "scale9Height");
        if (sw && sh)
        {
            float swf = dicHelper->getFloatValue_json(options, "scale9Width");
            float shf = dicHelper->getFloatValue_json(options, "scale9Height");
            imageView->setSize(Size(swf, shf));
        }
        
        float cx = dicHelper->getFloatValue_json(options, "capInsetsX");
        float cy = dicHelper->getFloatValue_json(options, "capInsetsY");
        float cw = dicHelper->getFloatValue_json(options, "capInsetsWidth");
        float ch = dicHelper->getFloatValue_json(options, "capInsetsHeight");
        
        imageView->setCapInsets(Rect(cx, cy, cw, ch));
        
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLabelFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::Label* label = static_cast<cocos2d::gui::Label*>(widget);
    bool touchScaleChangeAble = dicHelper->getBooleanValue_json(options, "touchScaleEnable");
    label->setTouchScaleChangeEnabled(touchScaleChangeAble);
    const char* text = dicHelper->getStringValue_json(options, "text");
    label->setText(text);
    bool fs = dicHelper->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        label->setFontSize(dicHelper->getIntValue_json(options, "fontSize"));
    }
    bool fn = dicHelper->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        label->setFontName(dicHelper->getStringValue_json(options, "fontName"));
    }
    bool aw = dicHelper->checkObjectExist_json(options, "areaWidth");
    bool ah = dicHelper->checkObjectExist_json(options, "areaHeight");
    if (aw && ah)
    {
        Size size = Size(dicHelper->getFloatValue_json(options, "areaWidth"),dicHelper->getFloatValue_json(options,"areaHeight"));
        label->setTextAreaSize(size);
    }
    bool ha = dicHelper->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        label->setTextHorizontalAlignment((TextHAlignment)dicHelper->getIntValue_json(options, "hAlignment"));
    }
    bool va = dicHelper->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        label->setTextVerticalAlignment((TextVAlignment)dicHelper->getIntValue_json(options, "vAlignment"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLabelAtlasFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::LabelAtlas* labelAtlas = static_cast<cocos2d::gui::LabelAtlas*>(widget);
    bool sv = dicHelper->checkObjectExist_json(options, "stringValue");
    bool cmf = dicHelper->checkObjectExist_json(options, "charMapFile");
    bool iw = dicHelper->checkObjectExist_json(options, "itemWidth");
    bool ih = dicHelper->checkObjectExist_json(options, "itemHeight");
    bool scm = dicHelper->checkObjectExist_json(options, "startCharMap");
    if (sv && cmf && iw && ih && scm)
    {
        JsonDictionary* cmftDic = dicHelper->getSubDictionary_json(options, "charMapFileData");
        int cmfType = dicHelper->getIntValue_json(cmftDic, "resourceType");
        switch (cmfType)
        {
            case 0:
            {
                std::string tp_c = m_strFilePath;
                const char* cmfPath = dicHelper->getStringValue_json(cmftDic, "path");
                const char* cmf_tp = tp_c.append(cmfPath).c_str();
                labelAtlas->setProperty(dicHelper->getStringValue_json(options, "stringValue"),cmf_tp,dicHelper->getIntValue_json(options, "itemWidth"),dicHelper->getIntValue_json(options,"itemHeight"),dicHelper->getStringValue_json(options, "startCharMap"));
                break;
            }
            case 1:
                CCLOG("Wrong res type of LabelAtlas!");
                break;
            default:
                break;
        }
        CC_SAFE_DELETE(cmftDic);
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLayoutFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    
    setPropsForWidgetFromJsonDictionary(widget, options);
    Layout* panel = static_cast<cocos2d::gui::Layout*>(widget);
    if (!dynamic_cast<cocos2d::gui::ScrollView*>(widget)
        && !dynamic_cast<cocos2d::gui::ListView*>(widget))
    {
        panel->setClippingEnabled(dicHelper->getBooleanValue_json(options, "clipAble"));
    }
    bool backGroundScale9Enable = dicHelper->getBooleanValue_json(options, "backGroundScale9Enable");
    panel->setBackGroundImageScale9Enabled(backGroundScale9Enable);
    int cr = dicHelper->getIntValue_json(options, "bgColorR");
    int cg = dicHelper->getIntValue_json(options, "bgColorG");
    int cb = dicHelper->getIntValue_json(options, "bgColorB");
    
    int scr = dicHelper->getIntValue_json(options, "bgStartColorR");
    int scg = dicHelper->getIntValue_json(options, "bgStartColorG");
    int scb = dicHelper->getIntValue_json(options, "bgStartColorB");
    
    int ecr = dicHelper->getIntValue_json(options, "bgEndColorR");
    int ecg = dicHelper->getIntValue_json(options, "bgEndColorG");
    int ecb = dicHelper->getIntValue_json(options, "bgEndColorB");
    
    float bgcv1 = dicHelper->getFloatValue_json(options, "vectorX");
    float bgcv2 = dicHelper->getFloatValue_json(options, "vectorY");
    panel->setBackGroundColorVector(Point(bgcv1, bgcv2));
    
    int co = dicHelper->getIntValue_json(options, "bgColorOpacity");
    
    int colorType = dicHelper->getIntValue_json(options, "colorType");
    panel->setBackGroundColorType(LayoutBackGroundColorType(colorType));
    panel->setBackGroundColor(Color3B(scr, scg, scb),Color3B(ecr, ecg, ecb));
    panel->setBackGroundColor(Color3B(cr, cg, cb));
    panel->setBackGroundColorOpacity(co);
    
    
    JsonDictionary* imageFileNameDic = dicHelper->getSubDictionary_json(options, "backGroundImageData");
    int imageFileNameType = dicHelper->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = dicHelper->getStringValue_json(imageFileNameDic, "path");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
            panel->setBackGroundImage(imageFileName_tp);
            break;
        }
        case 1:
        {
            const char* imageFileName = dicHelper->getStringValue_json(imageFileNameDic, "path");
            panel->setBackGroundImage(imageFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(imageFileNameDic);
    
    if (backGroundScale9Enable)
    {
        float cx = dicHelper->getFloatValue_json(options, "capInsetsX");
        float cy = dicHelper->getFloatValue_json(options, "capInsetsY");
        float cw = dicHelper->getFloatValue_json(options, "capInsetsWidth");
        float ch = dicHelper->getFloatValue_json(options, "capInsetsHeight");
        panel->setBackGroundImageCapInsets(Rect(cx, cy, cw, ch));
    }
    panel->setLayoutType((LayoutType)dicHelper->getIntValue_json(options, "layoutType"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForScrollViewFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForLayoutFromJsonDictionary(widget, options);
    cocos2d::gui::ScrollView* scrollView = static_cast<cocos2d::gui::ScrollView*>(widget);
    float innerWidth = dicHelper->getFloatValue_json(options, "innerWidth");
    float innerHeight = dicHelper->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
    int direction = dicHelper->getFloatValue_json(options, "direction");
    scrollView->setDirection((SCROLLVIEW_DIR)direction);
    scrollView->setBounceEnabled(dicHelper->getBooleanValue_json(options, "bounceEnable"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForSliderFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::Slider* slider = static_cast<cocos2d::gui::Slider*>(widget);
    
    bool barTextureScale9Enable = dicHelper->getBooleanValue_json(options, "barTextureScale9Enable");
    slider->setScale9Enabled(barTextureScale9Enable);
    bool bt = dicHelper->checkObjectExist_json(options, "barFileName");
    float barLength = dicHelper->getFloatValue_json(options, "length");
    if (bt)
    {
        if (barTextureScale9Enable)
        {
            
            JsonDictionary* imageFileNameDic = dicHelper->getSubDictionary_json(options, "barFileNameData");
            int imageFileType = dicHelper->getIntValue_json(imageFileNameDic, "resourceType");
            switch (imageFileType)
            {
                case 0:
                {
                    std::string tp_b = m_strFilePath;
                    const char* imageFileName = dicHelper->getStringValue_json(imageFileNameDic, "path");
                    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
                    slider->loadBarTexture(imageFileName_tp);
                    break;
                }
                case 1:
                {
                    const char* imageFileName =  dicHelper->getStringValue_json(imageFileNameDic, "path");
                    slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
                    break;
                }
                default:
                    break;
            }
            
            slider->setSize(Size(barLength, slider->getContentSize().height));
            CC_SAFE_DELETE(imageFileNameDic);
        }
        else
        {
            JsonDictionary* imageFileNameDic = dicHelper->getSubDictionary_json(options, "barFileNameData");
            int imageFileType = dicHelper->getIntValue_json(imageFileNameDic, "resourceType");
            switch (imageFileType)
            {
                case 0:
                {
                    std::string tp_b = m_strFilePath;
                    const char*imageFileName =  dicHelper->getStringValue_json(imageFileNameDic, "path");
                    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
                    slider->loadBarTexture(imageFileName_tp);
                    break;
                }
                case 1:
                {
                    const char*imageFileName =  dicHelper->getStringValue_json(imageFileNameDic, "path");
                    slider->loadBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
                    break;
                }
                default:
                    break;
            }
            CC_SAFE_DELETE(imageFileNameDic);
        }
    }
    
    JsonDictionary* normalDic = dicHelper->getSubDictionary_json(options, "ballNormalData");
    int normalType = dicHelper->getIntValue_json(normalDic, "resourceType");
    switch (normalType)
    {
        case 0:
        {
            std::string tp_n = m_strFilePath;
            const char* normalFileName = dicHelper->getStringValue_json(normalDic, "path");
            const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():nullptr;
            slider->loadSlidBallTextureNormal(normalFileName_tp);
            break;
        }
        case 1:
        {
            const char* normalFileName = dicHelper->getStringValue_json(normalDic, "path");
            slider->loadSlidBallTextureNormal(normalFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(normalDic);
    
    JsonDictionary* pressedDic = dicHelper->getSubDictionary_json(options, "ballPressedData");
    int pressedType = dicHelper->getIntValue_json(pressedDic, "resourceType");
    switch (pressedType)
    {
        case 0:
        {
            std::string tp_p = m_strFilePath;
            const char* pressedFileName = dicHelper->getStringValue_json(pressedDic, "path");
            const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():nullptr;
            slider->loadSlidBallTexturePressed(pressedFileName_tp);
            break;
        }
        case 1:
        {
            const char* pressedFileName = dicHelper->getStringValue_json(pressedDic, "path");
            slider->loadSlidBallTexturePressed(pressedFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(pressedDic);
    
    JsonDictionary* disabledDic = dicHelper->getSubDictionary_json(options, "ballDisabledData");
    int disabledType = dicHelper->getIntValue_json(disabledDic, "resourceType");
    switch (disabledType)
    {
        case 0:
        {
            std::string tp_d = m_strFilePath;
            const char* disabledFileName = dicHelper->getStringValue_json(disabledDic, "path");
            const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():nullptr;
            slider->loadSlidBallTextureDisabled(disabledFileName_tp);
            break;
        }
        case 1:
        {
            const char* disabledFileName = dicHelper->getStringValue_json(disabledDic, "path");
            slider->loadSlidBallTextureDisabled(disabledFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(disabledDic);
    
    slider->setPercent(dicHelper->getIntValue_json(options, "percent"));
    
    JsonDictionary* progressBarDic = dicHelper->getSubDictionary_json(options, "progressBarData");
    int progressBarType = dicHelper->getIntValue_json(progressBarDic, "resourceType");
    switch (progressBarType)
    {
        case 0:
        {
            std::string tp_b = m_strFilePath;
            const char* imageFileName = dicHelper->getStringValue_json(progressBarDic, "path");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():nullptr;
            slider->loadProgressBarTexture(imageFileName_tp);
            break;
        }
        case 1:
        {
            const char* imageFileName = dicHelper->getStringValue_json(progressBarDic, "path");
            slider->loadProgressBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForTextFieldFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::TextField* textField = static_cast<cocos2d::gui::TextField*>(widget);
    bool ph = dicHelper->checkObjectExist_json(options, "placeHolder");
    if (ph)
    {
        textField->setPlaceHolder(dicHelper->getStringValue_json(options, "placeHolder"));
    }
    textField->setText(dicHelper->getStringValue_json(options, "text"));
    bool fs = dicHelper->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        textField->setFontSize(dicHelper->getIntValue_json(options, "fontSize"));
    }
    bool fn = dicHelper->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        textField->setFontName(dicHelper->getStringValue_json(options, "fontName"));
    }
    bool tsw = dicHelper->checkObjectExist_json(options, "touchSizeWidth");
    bool tsh = dicHelper->checkObjectExist_json(options, "touchSizeHeight");
    if (tsw && tsh)
    {
        textField->setTouchSize(Size(dicHelper->getFloatValue_json(options, "touchSizeWidth"), dicHelper->getFloatValue_json(options,"touchSizeHeight")));
    }
    
    float dw = dicHelper->getFloatValue_json(options, "width");
    float dh = dicHelper->getFloatValue_json(options, "height");
    if (dw > 0.0f || dh > 0.0f)
    {
        //textField->setSize(Size(dw, dh));
    }
    bool maxLengthEnable = dicHelper->getBooleanValue_json(options, "maxLengthEnable");
    textField->setMaxLengthEnabled(maxLengthEnable);
    
    if (maxLengthEnable)
    {
        int maxLength = dicHelper->getIntValue_json(options, "maxLength");
        textField->setMaxLength(maxLength);
    }
    bool passwordEnable = dicHelper->getBooleanValue_json(options, "passwordEnable");
    textField->setPasswordEnabled(passwordEnable);
    if (passwordEnable)
    {
        textField->setPasswordStyleText(dicHelper->getStringValue_json(options, "passwordStyleText"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLoadingBarFromJsonDictionary(Widget *widget, JsonDictionary *options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    cocos2d::gui::LoadingBar* loadingBar = static_cast<cocos2d::gui::LoadingBar*>(widget);
    
    JsonDictionary* imageFileNameDic = dicHelper->getSubDictionary_json(options, "textureData");
    int imageFileNameType = dicHelper->getIntValue_json(imageFileNameDic, "resourceType");
    switch (imageFileNameType)
    {
        case 0:
        {
            std::string tp_i = m_strFilePath;
            const char* imageFileName = dicHelper->getStringValue_json(imageFileNameDic, "path");
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
            const char* imageFileName = dicHelper->getStringValue_json(imageFileNameDic, "path");
            loadingBar->loadTexture(imageFileName,UI_TEX_TYPE_PLIST);
            break;
        }
        default:
            break;
    }
    CC_SAFE_DELETE(imageFileNameDic);
    
    /* gui mark add load bar scale9 parse */
    bool scale9Enable = dicHelper->getBooleanValue_json(options, "scale9Enable");
    loadingBar->setScale9Enabled(scale9Enable);
    
    if (scale9Enable)
    {
        float cx = dicHelper->getFloatValue_json(options, "capInsetsX");
        float cy = dicHelper->getFloatValue_json(options, "capInsetsY");
        float cw = dicHelper->getFloatValue_json(options, "capInsetsWidth");
        float ch = dicHelper->getFloatValue_json(options, "capInsetsHeight");
        
        loadingBar->setCapInsets(Rect(cx, cy, cw, ch));
        
        float width = dicHelper->getFloatValue_json(options, "width");
        float height = dicHelper->getFloatValue_json(options, "height");
        loadingBar->setSize(Size(width, height));
    }
    /**/
    
    loadingBar->setDirection(LoadingBarType(dicHelper->getIntValue_json(options, "direction")));
    loadingBar->setPercent(dicHelper->getIntValue_json(options, "percent"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForLabelBMFontFromJsonDictionary(Widget *widget, JsonDictionary *options)
{
    DictionaryHelper* dicHelper = DICTOOL;
    setPropsForWidgetFromJsonDictionary(widget, options);
    
    cocos2d::gui::LabelBMFont* labelBMFont = static_cast<cocos2d::gui::LabelBMFont*>(widget);
    
    JsonDictionary* cmftDic = dicHelper->getSubDictionary_json(options, "fileNameData");
    int cmfType = dicHelper->getIntValue_json(cmftDic, "resourceType");
    switch (cmfType)
    {
        case 0:
        {
            std::string tp_c = m_strFilePath;
            const char* cmfPath = dicHelper->getStringValue_json(cmftDic, "path");
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
    CC_SAFE_DELETE(cmftDic);
    
    const char* text = dicHelper->getStringValue_json(options, "text");
    labelBMFont->setText(text);
    
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void WidgetPropertiesReader0300::setPropsForPageViewFromJsonDictionary(Widget*widget,JsonDictionary* options)
{
    
}

void WidgetPropertiesReader0300::setPropsForListViewFromJsonDictionary(Widget* widget, JsonDictionary* options)
{
    
}
}