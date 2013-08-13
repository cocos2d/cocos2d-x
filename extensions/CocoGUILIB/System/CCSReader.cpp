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

#include "CocosGUI.h"
#include "../../CocostudioReader/DictionaryHelper.h"
#include "../Action/UIActionManager.h"
#include <fstream>
#include <iostream>


NS_CC_EXT_BEGIN
    
static CCSReader* sharedReader = NULL;

CCSReader::CCSReader():
m_strFilePath(""),
m_bOlderVersion(false)
{
    
}

CCSReader::~CCSReader()
{
    
}

CCSReader* CCSReader::shareReader()
{
    if (!sharedReader)
    {
        sharedReader = new CCSReader();
    }
    return sharedReader;
}

void CCSReader::purgeCCSReader()
{
	CC_SAFE_DELETE(sharedReader);
}

int CCSReader::getVersionInteger(const char *str)
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

UIWidget* CCSReader::widgetFromJsonDictionary(cs::CSJsonDictionary* data)
{
    UIWidget* widget = NULL;
    const char* classname = DICTOOL->getStringValue_json(data, "classname");
    cs::CSJsonDictionary* uiOptions = DICTOOL->getSubDictionary_json(data, "options");
    if (classname && strcmp(classname, "Button") == 0)
    {
        widget = UIButton::create();
        setPropsForButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "CheckBox") == 0)
    {
        widget = UICheckBox::create();
        setPropsForCheckBoxFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Label") == 0)
    {
        widget = UILabel::create();
        setPropsForLabelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelAtlas") == 0)
    {
        widget = UILabelAtlas::create();
        setPropsForLabelAtlasFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LoadingBar") == 0)
    {
        widget = UILoadingBar::create();
        setPropsForLoadingBarFromJsonDictionary(widget, uiOptions);
    }else if (classname && strcmp(classname, "ScrollView") == 0){
        widget = UIScrollView::create();
        setPropsForScrollViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextArea") == 0)
    {
        widget = UITextArea::create();
        setPropsForTextAreaFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextButton") == 0)
    {
        widget = UITextButton::create();
        setPropsForTextButtonFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "TextField") == 0)
    {
        widget = UITextField::create();
        setPropsForTextFieldFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "ImageView") == 0)
    {
        widget = UIImageView::create();
        setPropsForImageViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Panel") == 0)
    {
        widget = UIPanel::create();
        setPropsForPanelFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "Slider") == 0)
    {
        widget = UISlider::create();
        setPropsForSliderFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "ListView") == 0)
    {
//        widget = UIListView::create();
//        setPropsForListViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "PageView") == 0)
    {
        widget = UIPageView::create();
        setPropsForPageViewFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "LabelBMFont") == 0)
    {
        widget = UILabelBMFont::create();
        setPropsForLabelBMFontFromJsonDictionary(widget, uiOptions);
    }
    else if (classname && strcmp(classname, "DragPanel") == 0)
    {
        widget = UIDragPanel::create();
        setPropsForDragPanelFromJsonDictionary(widget, uiOptions);
    }

    int childrenCount = DICTOOL->getArrayCount_json(data, "children");
    for (int i=0;i<childrenCount;i++)
    {
        cs::CSJsonDictionary* subData = DICTOOL->getDictionaryFromArray_json(data, "children", i);
        UIWidget* child = widgetFromJsonDictionary(subData);
        if (child)
        {
            widget->addChild(child);
        }
		CC_SAFE_DELETE(subData);
    }

	CC_SAFE_DELETE(uiOptions);
    return widget;
}



UIWidget* CCSReader::widgetFromJsonFile(const char *fileName)
{
    m_bOlderVersion = false;
    const char *des = NULL;
    std::string jsonpath;
    cs::CSJsonDictionary *jsonDict = NULL;
    jsonpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    
    unsigned long size = 0;
    des = (char*)(CCFileUtils::sharedFileUtils()->getFileData(jsonpath.c_str(),"r" , &size));
	if(NULL == des || strcmp(des, "") == 0)
	{
		printf("read json file[%s] error!\n", fileName);
		return NULL;
	}
	std::string strDes(des);
    jsonDict = new cs::CSJsonDictionary();
    jsonDict->initWithDescription(strDes.c_str());

    const char* fileVersion = DICTOOL->getStringValue_json(jsonDict, "version");
    if (!fileVersion || getVersionInteger(fileVersion) < 250)
    {
        m_bOlderVersion = true;
    }
    
    int texturesCount = DICTOOL->getArrayCount_json(jsonDict, "textures");
    int pos = jsonpath.find_last_of('/');
	m_strFilePath = jsonpath.substr(0,pos+1);
    for (int i=0; i<texturesCount; i++)
    {
        const char* file = DICTOOL->getStringValueFromArray_json(jsonDict, "textures", i);
        std::string tp = m_strFilePath;
        tp.append(file);
        CCUIHELPER->addSpriteFrame(tp.c_str());
    }
    float fileDesignWidth = DICTOOL->getFloatValue_json(jsonDict, "designWidth");
    float fileDesignHeight = DICTOOL->getFloatValue_json(jsonDict, "designHeight");
    if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
        printf("Read design size error!\n");
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCUIHELPER->setFileDesignWidth(winSize.width);
        CCUIHELPER->setFileDesignHeight(winSize.height);
    }
    else
    {
        CCUIHELPER->setFileDesignWidth(fileDesignWidth);
        CCUIHELPER->setFileDesignHeight(fileDesignHeight);
    }
    cs::CSJsonDictionary* widgetTree = DICTOOL->getSubDictionary_json(jsonDict, "widgetTree");
    UIWidget* widget = widgetFromJsonDictionary(widgetTree);
    
    /* *********temp********* */
    if (widget->getContentSize().equals(CCSizeZero))
    {
        UIContainerWidget* rootWidget = dynamic_cast<UIContainerWidget*>(widget);
        rootWidget->setSize(CCSizeMake(fileDesignWidth, fileDesignHeight));
    }
    /* ********************** */
    
    widget->setFileDesignSize(CCSizeMake(fileDesignWidth, fileDesignHeight));
    cs::CSJsonDictionary* actions = DICTOOL->getSubDictionary_json(jsonDict, "animation");
    /* *********temp********* */
//    UIActionManager::shareManager()->releaseActions();
    /* ********************** */
    CCLOG("file name == [%s]",fileName);
    UIActionManager::shareManager()->initWithDictionary(fileName,actions,widget);

	CC_SAFE_DELETE(widgetTree);
	CC_SAFE_DELETE(actions);
	CC_SAFE_DELETE(jsonDict);
    CC_SAFE_DELETE_ARRAY(des);
    return widget;
}

void CCSReader::setPropsForWidgetFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary *options)
{
    widget->setWidgetTag(DICTOOL->getIntValue_json(options, "tag"));
	widget->setActionTag(DICTOOL->getIntValue_json(options, "actiontag"));
    widget->setTouchEnable(DICTOOL->getBooleanValue_json(options, "touchAble"));
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
//    widget->setUseMergedTexture(DICTOOL->getBooleanValue_json(options, "useMergedTexture"));
    int z = DICTOOL->getIntValue_json(options, "ZOrder");
    widget->setWidgetZOrder(z);
}

void CCSReader::setColorPropsForWidgetFromJsonDictionary(UIWidget *widget, cs::CSJsonDictionary *options)
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
    float apxf = apx ? DICTOOL->getFloatValue_json(options, "anchorPointX") : 0.5f;
    bool apy = DICTOOL->checkObjectExist_json(options, "anchorPointY");
    float apyf = apy ? DICTOOL->getFloatValue_json(options, "anchorPointY") : 0.5f;
    widget->setAnchorPoint(ccp(apxf, apyf));
    bool flipX = DICTOOL->getBooleanValue_json(options, "flipX");
    bool flipY = DICTOOL->getBooleanValue_json(options, "flipY");
    widget->setFlipX(flipX);
    widget->setFlipY(flipY);
}

void CCSReader::setPropsForButtonFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    if (m_bOlderVersion)
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UIButton* button = (UIButton*)widget;
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        button->setScale9Enable(scale9Enable);
        
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
                button->setTextures(normalFileName, pressedFileName, disabledFileName,UI_TEX_TYPE_PLIST);
            }
            else
            {
                button->setTextures(normalFileName_tp, pressedFileName_tp, disabledFileName_tp);
            }
            button->setCapInsets(CCRectMake(cx, cy, cw, ch));
            bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                button->setScale9Size(CCSizeMake(swf, shf));
            }
        }
        else
        {
            if (useMergedTexture)
            {
                button->setTextures(normalFileName, pressedFileName, disabledFileName,UI_TEX_TYPE_PLIST);
            }
            else
            {
                button->setTextures(normalFileName_tp, pressedFileName_tp, disabledFileName_tp);
            }
        }
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    else
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UIButton* button = (UIButton*)widget;
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        button->setScale9Enable(scale9Enable);
        
        cs::CSJsonDictionary* normalDic = DICTOOL->getSubDictionary_json(options, "normalData");
        int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
        switch (normalType)
        {
            case 0:
            {
                std::string tp_n = m_strFilePath;
                const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
                const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():NULL;
                button->setNormalTexture(normalFileName_tp);
                break;
            }
            case 1:
            {
                const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
                button->setNormalTexture(normalFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        CC_SAFE_DELETE(normalDic);
        cs::CSJsonDictionary* pressedDic = DICTOOL->getSubDictionary_json(options, "pressedData");
        int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
        switch (pressedType)
        {
            case 0:
            {
                std::string tp_p = m_strFilePath;
                const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
                const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
                button->setPressedTexture(pressedFileName_tp);
                break;
            }
            case 1:
            {
                const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
                button->setPressedTexture(pressedFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        CC_SAFE_DELETE(pressedDic);
        cs::CSJsonDictionary* disabledDic = DICTOOL->getSubDictionary_json(options, "disabledData");
        int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
        switch (disabledType)
        {
            case 0:
            {
                std::string tp_d = m_strFilePath;
                const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
                const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
                button->setDisabledTexture(disabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
                button->setDisabledTexture(disabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        CC_SAFE_DELETE(disabledDic);
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
                button->setScale9Size(CCSizeMake(swf, shf));
            }
        }
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
}

void CCSReader::setPropsForCheckBoxFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    if (m_bOlderVersion)
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UICheckBox* checkBox = (UICheckBox*)widget;
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
            checkBox->setTextures(backGroundFileName, backGroundSelectedFileName, frontCrossFileName,backGroundDisabledFileName,frontCrossDisabledFileName,UI_TEX_TYPE_PLIST);
        }
        else
        {
            checkBox->setTextures(backGroundFileName_tp, backGroundSelectedFileName_tp, frontCrossFileName_tp,backGroundDisabledFileName_tp,frontCrossDisabledFileName_tp);
        }
        
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    else
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UICheckBox* checkBox = (UICheckBox*)widget;
        
        cs::CSJsonDictionary* backGroundDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxData");
        int backGroundType = DICTOOL->getIntValue_json(backGroundDic, "resourceType");
        switch (backGroundType)
        {
            case 0:
            {
                std::string tp_b = m_strFilePath;
                const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
                const char* backGroundFileName_tp = (backGroundFileName && (strcmp(backGroundFileName, "") != 0))?tp_b.append(backGroundFileName).c_str():NULL;
                checkBox->setBackGroundTexture(backGroundFileName_tp);
                break;
            }
            case 1:
            {
                const char* backGroundFileName = DICTOOL->getStringValue_json(backGroundDic, "path");
                checkBox->setBackGroundTexture(backGroundFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        CC_SAFE_DELETE(backGroundDic);

        cs::CSJsonDictionary* backGroundSelectedDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxSelectedData");
        int backGroundSelectedType = DICTOOL->getIntValue_json(backGroundSelectedDic, "resourceType");
        switch (backGroundSelectedType)
        {
            case 0:
            {
                std::string tp_bs = m_strFilePath;
                const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
                const char* backGroundSelectedFileName_tp = (backGroundSelectedFileName && (strcmp(backGroundSelectedFileName, "") != 0))?tp_bs.append(backGroundSelectedFileName).c_str():NULL;
                checkBox->setBackGroundSelectedTexture(backGroundSelectedFileName_tp);
                break;
            }
            case 1:
            {
                const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(backGroundSelectedDic, "path");
                checkBox->setBackGroundSelectedTexture(backGroundSelectedFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        CC_SAFE_DELETE(backGroundSelectedDic);

        cs::CSJsonDictionary* frontCrossDic = DICTOOL->getSubDictionary_json(options, "frontCrossData");
        int frontCrossType = DICTOOL->getIntValue_json(frontCrossDic, "resourceType");
        switch (frontCrossType)
        {
            case 0:
            {
                std::string tp_c = m_strFilePath;
                const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
                const char* frontCrossFileName_tp = (frontCrossFileName && (strcmp(frontCrossFileName, "") != 0))?tp_c.append(frontCrossFileName).c_str():NULL;
                checkBox->setFrontCrossTexture(frontCrossFileName_tp);
                break;
            }
            case 1:
            {
                const char* frontCrossFileName = DICTOOL->getStringValue_json(frontCrossDic, "path");
                checkBox->setFrontCrossTexture(frontCrossFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
		CC_SAFE_DELETE(frontCrossDic);
        
        cs::CSJsonDictionary* backGroundDisabledDic = DICTOOL->getSubDictionary_json(options, "backGroundBoxDisabledData");
        int backGroundDisabledType = DICTOOL->getIntValue_json(backGroundDisabledDic, "resourceType");
        switch (backGroundDisabledType)
        {
            case 0:
            {
                std::string tp_bd = m_strFilePath;
                const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
                const char* backGroundDisabledFileName_tp = (backGroundDisabledFileName && (strcmp(backGroundDisabledFileName, "") != 0))?tp_bd.append(backGroundDisabledFileName).c_str():NULL;
                checkBox->setBackGroundDisabledTexture(backGroundDisabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(backGroundDisabledDic, "path");
                checkBox->setBackGroundDisabledTexture(backGroundDisabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
		CC_SAFE_DELETE(backGroundDisabledDic);
        
        cs::CSJsonDictionary* frontCrossDisabledDic = DICTOOL->getSubDictionary_json(options, "frontCrossDisabledData");
        int frontCrossDisabledType = DICTOOL->getIntValue_json(frontCrossDisabledDic, "resourceType");
        switch (frontCrossDisabledType)
        {
            case 0:
            {
                std::string tp_cd = m_strFilePath;
                const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
                const char* frontCrossDisabledFileName_tp = (frontCrossDisabledFileName && (strcmp(frontCrossDisabledFileName, "") != 0))?tp_cd.append(frontCrossDisabledFileName).c_str():NULL;
                checkBox->setFrontCrossDisabledTexture(frontCrossDisabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "path");
                checkBox->setFrontCrossDisabledTexture(frontCrossDisabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
		CC_SAFE_DELETE(frontCrossDisabledDic);

        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
}

void CCSReader::setPropsForImageViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    if (m_bOlderVersion)
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        
        UIImageView* imageView = (UIImageView*)widget;
        const char* imageFileName = DICTOOL->getStringValue_json(options, "fileName");
        bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, "scale9Enable");
        bool scale9Enable = false;
        if (scale9EnableExist)
        {
            scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        }
        imageView->setScale9Enable(scale9Enable);
        
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
                imageView->setTexture(imageFileName,UI_TEX_TYPE_PLIST);
            }
            else
            {
                imageView->setTexture(imageFileName_tp);
            }
            
            bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                imageView->setScale9Size(CCSizeMake(swf, shf));
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
                imageView->setTexture(imageFileName,UI_TEX_TYPE_PLIST);
            }
            else
            {
                imageView->setTexture(imageFileName_tp);
            }
        }
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    else
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        
        UIImageView* imageView = (UIImageView*)widget;
        
        cs::CSJsonDictionary* imageFileNameDic = DICTOOL->getSubDictionary_json(options, "fileNameData");
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
                    imageView->setTexture(imageFileName_tp);
                }
                break;
            }
            case 1:
            {
                const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
                imageView->setTexture(imageFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        CC_SAFE_DELETE(imageFileNameDic);

        bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, "scale9Enable");
        bool scale9Enable = false;
        if (scale9EnableExist)
        {
            scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        }
        imageView->setScale9Enable(scale9Enable);
        
        
        if (scale9Enable)
        {            
            bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                imageView->setScale9Size(CCSizeMake(swf, shf));
            }
            
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            imageView->setCapInsets(CCRectMake(cx, cy, cw, ch));
            
        }
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
}

void CCSReader::setPropsForLabelFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    UILabel* label = (UILabel*)widget;
    bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, "touchSacleEnable");
    label->setTouchScaleChangeAble(touchScaleChangeAble);
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
    bool cro = DICTOOL->checkObjectExist_json(options, "colorR");
    bool cgo = DICTOOL->checkObjectExist_json(options, "colorG");
    bool cbo = DICTOOL->checkObjectExist_json(options, "colorB");
    int cr = cro?DICTOOL->getIntValue_json(options, "colorR"):255;
    int cg = cgo?DICTOOL->getIntValue_json(options, "colorG"):255;
    int cb = cbo?DICTOOL->getIntValue_json(options, "colorB"):255;
    ccColor3B tc = ccc3(cr, cg, cb);
    label->setColor(tc);
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void CCSReader::setPropsForLabelAtlasFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    if (m_bOlderVersion)
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UILabelAtlas* labelAtlas = (UILabelAtlas*)widget;
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
            
            labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth"),DICTOOL->getIntValue_json(options,"itemHeight"),DICTOOL->getStringValue_json(options, "startCharMap"));
        }
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    else
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UILabelAtlas* labelAtlas = (UILabelAtlas*)widget;
        bool sv = DICTOOL->checkObjectExist_json(options, "stringValue");
        bool cmf = DICTOOL->checkObjectExist_json(options, "charMapFile");
        bool iw = DICTOOL->checkObjectExist_json(options, "itemWidth");
        bool ih = DICTOOL->checkObjectExist_json(options, "itemHeight");
        bool scm = DICTOOL->checkObjectExist_json(options, "startCharMap");
        if (sv && cmf && iw && ih && scm)
        {
            
            cs::CSJsonDictionary* cmftDic = DICTOOL->getSubDictionary_json(options, "charMapFileData");
            int cmfType = DICTOOL->getIntValue_json(cmftDic, "resourceType");
            switch (cmfType)
            {
                case 0:
                {
                    std::string tp_c = m_strFilePath;
                    const char* cmfPath = DICTOOL->getStringValue_json(cmftDic, "path");
                    const char* cmf_tp = tp_c.append(cmfPath).c_str();
                    labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),cmf_tp,DICTOOL->getIntValue_json(options, "itemWidth"),DICTOOL->getIntValue_json(options,"itemHeight"),DICTOOL->getStringValue_json(options, "startCharMap"));       
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
}

void CCSReader::setPropsForContainerWidgetFromJsonDictionary(UIWidget *widget, cs::CSJsonDictionary *options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    UIContainerWidget* containerWidget = (UIContainerWidget*)widget;
    containerWidget->setClippingEnable(DICTOOL->getBooleanValue_json(options, "clipAble"));
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void CCSReader::setPropsForPanelFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    if (m_bOlderVersion)
    {
        setPropsForContainerWidgetFromJsonDictionary(widget, options);
        UIPanel* panel = (UIPanel*)widget;
        bool backGroundScale9Enable = DICTOOL->getBooleanValue_json(options, "backGroundScale9Enable");
        panel->setBackGroundImageScale9Enable(backGroundScale9Enable);
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
        panel->setBackGroundColorType(PanelColorType(colorType));
        float w = DICTOOL->getFloatValue_json(options, "width");
        float h = DICTOOL->getFloatValue_json(options, "height");
        panel->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
        panel->setBackGroundColor(ccc3(cr, cg, cb));
        panel->setBackGroundColorOpacity(co);
        panel->setSize(CCSizeMake(w, h));
        
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
    else
    {
        setPropsForContainerWidgetFromJsonDictionary(widget, options);
        UIPanel* panel = (UIPanel*)widget;
        bool backGroundScale9Enable = DICTOOL->getBooleanValue_json(options, "backGroundScale9Enable");
        panel->setBackGroundImageScale9Enable(backGroundScale9Enable);
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
        panel->setBackGroundColorType(PanelColorType(colorType));
        float w = DICTOOL->getFloatValue_json(options, "width");
        float h = DICTOOL->getFloatValue_json(options, "height");
        panel->setBackGroundColor(ccc3(scr, scg, scb),ccc3(ecr, ecg, ecb));
        panel->setBackGroundColor(ccc3(cr, cg, cb));
        panel->setBackGroundColorOpacity(co);
        panel->setSize(CCSizeMake(w, h));
        
        
        cs::CSJsonDictionary* imageFileNameDic = DICTOOL->getSubDictionary_json(options, "backGroundImageData");
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
		CC_SAFE_DELETE(imageFileNameDic);

        if (backGroundScale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            panel->setBackGroundImageCapInsets(CCRectMake(cx, cy, cw, ch));
        }
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
}

void CCSReader::setPropsForScrollViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    setPropsForPanelFromJsonDictionary(widget, options);
    UIScrollView* scrollView = (UIScrollView*)widget;
    float innerWidth = DICTOOL->getFloatValue_json(options, "innerWidth");
    float innerHeight = DICTOOL->getFloatValue_json(options, "innerHeight");
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
    
    int direction = DICTOOL->getIntValue_json(options, "direction");
    scrollView->setDirection((SCROLLVIEW_DIR)direction);
    
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void CCSReader::setPropsForSliderFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    if (m_bOlderVersion)
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UISlider* slider = (UISlider*)widget;
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, "barTextureScale9Enable");
        slider->setScale9Enable(barTextureScale9Enable);
        bool bt = DICTOOL->checkObjectExist_json(options, "barFileName");

        bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
        if (bt)
        {
            if (barTextureScale9Enable)
            {                
                std::string tp_b = m_strFilePath;
                const char*imageFileName =  DICTOOL->getStringValue_json(options, "barFileName");
                const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
                if (useMergedTexture)
                {
                    slider->setBarTexture(imageFileName, UI_TEX_TYPE_PLIST);
                }
                else
                {
                    slider->setBarTexture(imageFileName_tp);
                }
                
                float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
                float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
                float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
                float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
                
                slider->setCapInsets(CCRectMake(cx, cy, cw, ch));
                
                bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
                bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
                if (sw && sh)
                {
                    float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                    float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                    slider->setScale9Size(CCSizeMake(swf, shf));
                }
            }
            else
            {
                std::string tp_b = m_strFilePath;
                const char*imageFileName =  DICTOOL->getStringValue_json(options, "barFileName");
                const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
                if (useMergedTexture)
                {
                    slider->setBarTexture(imageFileName,UI_TEX_TYPE_PLIST);
                }
                else
                {
                    slider->setBarTexture(imageFileName_tp);
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
            slider->setSlidBallTextures(normalFileName,pressedFileName,disabledFileName,UI_TEX_TYPE_PLIST);
        }
        else
        {
            slider->setSlidBallTextures(normalFileName_tp,pressedFileName_tp,disabledFileName_tp);
        }
        slider->setSlidBallPercent(DICTOOL->getIntValue_json(options, "percent"));
        bool progressBarVisibleExist = DICTOOL->checkObjectExist_json(options, "progressBarVisible");
        bool progressBarVisible = false;
        if (progressBarVisibleExist)
        {
            progressBarVisible = DICTOOL->getBooleanValue_json(options, "progressBarVisible");
        }
        if (progressBarVisible)
        {
            slider->setProgressBarVisible(progressBarVisible);
            std::string tp_b = m_strFilePath;
            const char*imageFileName =  DICTOOL->getStringValue_json(options, "progressBarFileName");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
            if (useMergedTexture)
            {
                slider->setProgressBarTexture(imageFileName, UI_TEX_TYPE_PLIST);
            }
            else
            {
                slider->setProgressBarTexture(imageFileName_tp);
            }
            slider->setProgressBarScale();
        }
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    else
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UISlider* slider = (UISlider*)widget;
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, "barTextureScale9Enable");
        slider->setScale9Enable(barTextureScale9Enable);
        bool bt = DICTOOL->checkObjectExist_json(options, "barFileName");
        float barLength = DICTOOL->getFloatValue_json(options, "length");
        bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
        if (bt)
        {
            if (barTextureScale9Enable)
            {
//                slider->setBarLength(barLength);
                
                cs::CSJsonDictionary* imageFileNameDic = DICTOOL->getSubDictionary_json(options, "barFileNameData");
                int imageFileType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
                switch (imageFileType)
                {
                    case 0:
                    {
                        std::string tp_b = m_strFilePath;
                        const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                        const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
                        slider->setBarTexture(imageFileName_tp);
                        break;
                    }
                    case 1:
                    {
                        const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                        slider->setBarTexture(imageFileName, UI_TEX_TYPE_PLIST);
                        break;
                    }
                    default:
                        break;
                }
                
                bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
                bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
                if (sw && sh)
                {
                    float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                    float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                    slider->setScale9Size(CCSizeMake(swf, shf));
                }
                
                float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
                float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
                float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
                float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
                
                slider->setCapInsets(CCRectMake(cx, cy, cw, ch));
                
				CC_SAFE_DELETE(imageFileNameDic);
            }
            else
            {
                cs::CSJsonDictionary* imageFileNameDic = DICTOOL->getSubDictionary_json(options, "barFileNameData");
                int imageFileType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
                switch (imageFileType)
                {
                    case 0:
                    {
                        std::string tp_b = m_strFilePath;
                        const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                        const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
                        slider->setBarTexture(imageFileName_tp);
                        break;
                    }
                    case 1:
                    {
                        const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                        slider->setBarTexture(imageFileName, UI_TEX_TYPE_PLIST);
                        break;
                    }
                    default:
                        break;
                }
				CC_SAFE_DELETE(imageFileNameDic);
            }
        }
//        std::string tp_n = m_strFilePath;
//        std::string tp_p = m_strFilePath;
//        std::string tp_d = m_strFilePath;
//        
//        const char* normalFileName = DICTOOL->getStringValue_json(options, "ballNormal");
//        const char* pressedFileName = DICTOOL->getStringValue_json(options, "ballPressed");
//        const char* disabledFileName = DICTOOL->getStringValue_json(options, "ballDisabled");
//        
//        const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():NULL;
//        const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
//        const char* disabledFileName_tp =  (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
//        if (useMergedTexture)
//        {
//            slider->setSlidBallTextures(normalFileName,pressedFileName,disabledFileName,UI_TEX_TYPE_PLIST);
//        }
//        else
//        {
//            slider->setSlidBallTextures(normalFileName_tp,pressedFileName_tp,disabledFileName_tp);
//        }
        
        cs::CSJsonDictionary* normalDic = DICTOOL->getSubDictionary_json(options, "ballNormalData");
        int normalType = DICTOOL->getIntValue_json(normalDic, "resourceType");
        switch (normalType)
        {
            case 0:
            {
                std::string tp_n = m_strFilePath;
                const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
                const char* normalFileName_tp = (normalFileName && (strcmp(normalFileName, "") != 0))?tp_n.append(normalFileName).c_str():NULL;
                slider->setSlidBallNormalTexture(normalFileName_tp);
                break;
            }
            case 1:
            {
                const char* normalFileName = DICTOOL->getStringValue_json(normalDic, "path");
                slider->setSlidBallNormalTexture(normalFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
        CC_SAFE_DELETE(normalDic);

        cs::CSJsonDictionary* pressedDic = DICTOOL->getSubDictionary_json(options, "ballPressedData");
        int pressedType = DICTOOL->getIntValue_json(pressedDic, "resourceType");
        switch (pressedType)
        {
            case 0:
            {
                std::string tp_p = m_strFilePath;
                const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
                const char* pressedFileName_tp = (pressedFileName && (strcmp(pressedFileName, "") != 0))?tp_p.append(pressedFileName).c_str():NULL;
                slider->setSlidBallPressedTexture(pressedFileName_tp);
                break;
            }
            case 1:
            {
                const char* pressedFileName = DICTOOL->getStringValue_json(pressedDic, "path");
                slider->setSlidBallPressedTexture(pressedFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
		CC_SAFE_DELETE(pressedDic);
        
        cs::CSJsonDictionary* disabledDic = DICTOOL->getSubDictionary_json(options, "ballDisableddData");
        int disabledType = DICTOOL->getIntValue_json(disabledDic, "resourceType");
        switch (disabledType)
        {
            case 0:
            {
                std::string tp_d = m_strFilePath;
                const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
                const char* disabledFileName_tp = (disabledFileName && (strcmp(disabledFileName, "") != 0))?tp_d.append(disabledFileName).c_str():NULL;
                slider->setSlidBallDisabledTexture(disabledFileName_tp);
                break;
            }
            case 1:
            {
                const char* disabledFileName = DICTOOL->getStringValue_json(disabledDic, "path");
                slider->setSlidBallDisabledTexture(disabledFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
		CC_SAFE_DELETE(disabledDic);
        
        slider->setSlidBallPercent(DICTOOL->getIntValue_json(options, "percent"));
//        bool progressBarVisibleExist = DICTOOL->checkObjectExist_json(options, "progressBarVisible");
        bool progressBarVisible = false;
//        if (progressBarVisibleExist)
//        {
            progressBarVisible = DICTOOL->getBooleanValue_json(options, "progressBarVisible");
            slider->setProgressBarVisible(progressBarVisible);
//        }
        if (progressBarVisible)
        {
            cs::CSJsonDictionary* imageFileNameDic = DICTOOL->getSubDictionary_json(options, "progressBarData");
            int imageFileType = DICTOOL->getIntValue_json(imageFileNameDic, "resourceType");
            switch (imageFileType)
            {
                case 0:
                {
                    std::string tp_b = m_strFilePath;
                    const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                    const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
                    slider->setProgressBarTexture(imageFileName_tp);
                    break;
                }
                case 1:
                {
                    const char*imageFileName =  DICTOOL->getStringValue_json(imageFileNameDic, "path");
                    slider->setProgressBarTexture(imageFileName, UI_TEX_TYPE_PLIST);
                    break;
                }
                default:
                    break;
            }
            CC_SAFE_DELETE(imageFileNameDic);
            
            
            /*
            slider->setProgressBarVisible(progressBarVisible);
            std::string tp_b = m_strFilePath;
            const char*imageFileName =  DICTOOL->getStringValue_json(options, "progressBarFileName");
            const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
            if (useMergedTexture)
            {
                slider->setProgressBarTexture(imageFileName, UI_TEX_TYPE_PLIST);
            }
            else
            {
                slider->setProgressBarTexture(imageFileName_tp);
            }
            slider->setProgressBarScale();
             */
        }
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
}

void CCSReader::setPropsForTextAreaFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    UITextArea* textArea = (UITextArea*)widget;
    textArea->setText(DICTOOL->getStringValue_json(options, "text"));
    bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        textArea->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
    }
    int cr = DICTOOL->getIntValue_json(options, "colorR");
    int cg = DICTOOL->getIntValue_json(options, "colorG");
    int cb = DICTOOL->getIntValue_json(options, "colorB");
    textArea->setTextColor(cr, cg, cb);
    textArea->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
    bool aw = DICTOOL->checkObjectExist_json(options, "areaWidth");
    bool ah = DICTOOL->checkObjectExist_json(options, "areaHeight");
    if (aw && ah)
    {
        CCSize size = CCSize(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
        textArea->setTextAreaSize(size);
    }
    bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
    if (ha)
    {
        textArea->setTextHorizontalAlignment((CCTextAlignment)DICTOOL->getIntValue_json(options, "hAlignment"));
    }
    bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
    if (va)
    {
        textArea->setTextVerticalAlignment((CCVerticalTextAlignment)DICTOOL->getIntValue_json(options, "vAlignment"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void CCSReader::setPropsForTextButtonFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    setPropsForButtonFromJsonDictionary(widget, options);
    UITextButton* textButton = (UITextButton*)widget;
    textButton->setText(DICTOOL->getStringValue_json(options, "text"));
    bool cr = DICTOOL->checkObjectExist_json(options, "textColorR");
    bool cg = DICTOOL->checkObjectExist_json(options, "textColorG");
    bool cb = DICTOOL->checkObjectExist_json(options, "textColorB");
    int cri = cr ? DICTOOL->getIntValue_json(options, "textColorR") : 255;
    int cgi = cg ? DICTOOL->getIntValue_json(options, "textColorG") : 255;
    int cbi = cb ? DICTOOL->getIntValue_json(options, "textColorB") : 255;
    textButton->setTextColor(cri,cgi,cbi);
    bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
    if (fs)
    {
        textButton->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
    }
    bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
    if (fn)
    {
        textButton->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void CCSReader::setPropsForTextFieldFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    setPropsForWidgetFromJsonDictionary(widget, options);
    UITextField* textField = (UITextField*)widget;
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
    
    bool maxLengthEnable = DICTOOL->getBooleanValue_json(options, "maxLengthEnable");
    textField->setMaxLengthEnable(maxLengthEnable);
    if (maxLengthEnable)
    {
        int maxLength = DICTOOL->getIntValue_json(options, "maxLength");
        textField->setMaxLength(maxLength);
    }
    
    bool passwordEnable = DICTOOL->getBooleanValue_json(options, "passwordEnable");
    textField->setPasswordEnable(passwordEnable);
    if (passwordEnable)
    {
        textField->setPasswordStyleText(DICTOOL->getStringValue_json(options, "passwordStyleText"));
    }
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void CCSReader::setPropsForLoadingBarFromJsonDictionary(UIWidget *widget, cs::CSJsonDictionary *options)
{
    if (m_bOlderVersion)
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UILoadingBar* loadingBar = (UILoadingBar*)widget;
        bool useMergedTexture = DICTOOL->getBooleanValue_json(options, "useMergedTexture");
        std::string tp_b = m_strFilePath;
        const char*imageFileName =  DICTOOL->getStringValue_json(options, "texture");
        const char* imageFileName_tp = (imageFileName && (strcmp(imageFileName, "") != 0))?tp_b.append(imageFileName).c_str():NULL;
        if (useMergedTexture)
        {
            loadingBar->setTexture(imageFileName,UI_TEX_TYPE_PLIST);
        }
        else
        {
            loadingBar->setTexture(imageFileName_tp);
        }
        loadingBar->setDirection(LoadingBarType(DICTOOL->getIntValue_json(options, "direction")));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    else
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        UILoadingBar* loadingBar = (UILoadingBar*)widget;
        
        cs::CSJsonDictionary* imageFileNameDic = DICTOOL->getSubDictionary_json(options, "textureData");
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
                    loadingBar->setTexture(imageFileName_tp);
                }
                break;
            }
            case 1:
            {
                const char* imageFileName = DICTOOL->getStringValue_json(imageFileNameDic, "path");
                loadingBar->setTexture(imageFileName,UI_TEX_TYPE_PLIST);
                break;
            }
            default:
                break;
        }
		CC_SAFE_DELETE(imageFileNameDic);

        loadingBar->setDirection(LoadingBarType(DICTOOL->getIntValue_json(options, "direction")));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
}

void CCSReader::setPropsForListViewFromJsonDictionary(UIWidget *widget, cs::CSJsonDictionary *options)
{
    setPropsForScrollViewFromJsonDictionary(widget, options);
}

void CCSReader::setPropsForPageViewFromJsonDictionary(UIWidget*widget,cs::CSJsonDictionary* options)
{
    setPropsForPanelFromJsonDictionary(widget, options);
    setColorPropsForWidgetFromJsonDictionary(widget,options);
}

void CCSReader::setPropsForLabelBMFontFromJsonDictionary(UIWidget *widget, cs::CSJsonDictionary *options)
{
    if (m_bOlderVersion)
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        
        UILabelBMFont* labelBMFont = (UILabelBMFont*)widget;
        
        std::string tp_c = m_strFilePath;
        const char* cmf_tp = NULL;
        const char* cmft = DICTOOL->getStringValue_json(options, "fileName");
        cmf_tp = tp_c.append(cmft).c_str();
        
        labelBMFont->setFntFile(cmf_tp);
        
        const char* text = DICTOOL->getStringValue_json(options, "text");
        labelBMFont->setText(text);
        
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    else
    {
        setPropsForWidgetFromJsonDictionary(widget, options);
        
        UILabelBMFont* labelBMFont = (UILabelBMFont*)widget;
        
        cs::CSJsonDictionary* cmftDic = DICTOOL->getSubDictionary_json(options, "fileNameData");
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
        CC_SAFE_DELETE(cmftDic);

        const char* text = DICTOOL->getStringValue_json(options, "text");
        labelBMFont->setText(text);
        
        setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
}

void CCSReader::setPropsForDragPanelFromJsonDictionary(UIWidget *widget, cs::CSJsonDictionary *options)
{
    setPropsForPanelFromJsonDictionary(widget, options);
    
    UIDragPanel* dragPanel = (UIDragPanel*)widget;
    
    bool bounceEnable = DICTOOL->getBooleanValue_json(options, "bounceEnable");
    dragPanel->setBounceEnable(bounceEnable);
    
    setColorPropsForWidgetFromJsonDictionary(widget, options);
}

NS_CC_EXT_END