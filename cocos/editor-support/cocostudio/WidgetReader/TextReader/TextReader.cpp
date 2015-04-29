

#include "TextReader.h"

#include "ui/UIText.h"
#include "cocostudio/CocoLoader.h"
#include "cocostudio/CSParseBinary_generated.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{
    static const char* P_TouchScaleEnable = "touchScaleEnable";
    static const char* P_Text = "text";
    static const char* P_FontSize = "fontSize";
    static const char* P_FontName = "fontName";
    static const char* P_AreaWidth = "areaWidth";
    static const char* P_AreaHeight = "areaHeight";
    static const char* P_HAlignment = "hAlignment";
    static const char* P_VAlignment = "vAlignment";
    
    static TextReader* instanceTextReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(TextReader)
    
    TextReader::TextReader()
    {
        
    }
    
    TextReader::~TextReader()
    {
        
    }
    
    TextReader* TextReader::getInstance()
    {
        if (!instanceTextReader)
        {
            instanceTextReader = new (std::nothrow) TextReader();
        }
        return instanceTextReader;
    }
    
    void TextReader::destroyInstance()
    {
        CC_SAFE_DELETE(instanceTextReader);
    }
    
    void TextReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
    {
        this->beginSetBasicProperties(widget);
        
        stExpCocoNode *stChildArray = cocoNode->GetChildArray(cocoLoader);
        
        Text* label = static_cast<Text*>(widget);
        
        std::string binaryFilePath = GUIReader::getInstance()->getFilePath();

        
        for (int i = 0; i < cocoNode->GetChildNum(); ++i) {
            std::string key = stChildArray[i].GetName(cocoLoader);
            std::string value = stChildArray[i].GetValue(cocoLoader);
            //read all basic properties of widget
            CC_BASIC_PROPERTY_BINARY_READER
            //read all color related properties of widget
            CC_COLOR_PROPERTY_BINARY_READER

            else if (key == P_TouchScaleEnable) {
                label->setTouchScaleChangeEnabled(valueToBool(value));
            }
            
            else if(key == P_Text){
                label->setString(value);
            }else if(key == P_FontSize){
                label->setFontSize(valueToInt(value));
            }else if(key == P_FontName){
                std::string fontFilePath;
                fontFilePath = binaryFilePath.append(value);
                if (FileUtils::getInstance()->isFileExist(fontFilePath)) {
                    label->setFontName(fontFilePath);
                }else{
                    label->setFontName(value);
                }
            }else if(key == P_AreaWidth){
                label->setTextAreaSize(Size(valueToFloat(value), label->getTextAreaSize().height));
            }else if(key == P_AreaHeight){
                label->setTextAreaSize(Size(label->getTextAreaSize().width, valueToFloat(value)));
            }else if(key == P_HAlignment){
                label->setTextHorizontalAlignment((TextHAlignment)valueToInt(value));
            }else if(key == P_VAlignment){
                label->setTextVerticalAlignment((TextVAlignment)valueToInt(value));
            }
            
        } //end of for loop
        this->endSetBasicProperties(widget);
    }
    
    void TextReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        WidgetReader::setPropsFromJsonDictionary(widget, options);
        
        
        std::string jsonPath = GUIReader::getInstance()->getFilePath();
        
        Text* label = static_cast<Text*>(widget);
        bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, P_TouchScaleEnable);
        label->setTouchScaleChangeEnabled(touchScaleChangeAble);
        const char* text = DICTOOL->getStringValue_json(options, P_Text,"Text Label");
        label->setString(text);
      
        label->setFontSize(DICTOOL->getIntValue_json(options, P_FontSize,20));
       
        std::string fontName = DICTOOL->getStringValue_json(options, P_FontName, "");
        
        std::string fontFilePath = jsonPath.append(fontName);
		if (FileUtils::getInstance()->isFileExist(fontFilePath))
		{
			label->setFontName(fontFilePath);
		}
		else{
			label->setFontName(fontName);
		}
        
        bool aw = DICTOOL->checkObjectExist_json(options, P_AreaWidth);
        bool ah = DICTOOL->checkObjectExist_json(options, P_AreaHeight);
        if (aw && ah)
        {
            Size size = Size(DICTOOL->getFloatValue_json(options, P_AreaWidth),DICTOOL->getFloatValue_json(options,P_AreaHeight));
            label->setTextAreaSize(size);
        }
        bool ha = DICTOOL->checkObjectExist_json(options, P_HAlignment);
        if (ha)
        {
            label->setTextHorizontalAlignment((TextHAlignment)DICTOOL->getIntValue_json(options, P_HAlignment));
        }
        bool va = DICTOOL->checkObjectExist_json(options, P_VAlignment);
        if (va)
        {
            label->setTextVerticalAlignment((TextVAlignment)DICTOOL->getIntValue_json(options, P_VAlignment));
        }
        
        
        WidgetReader::setColorPropsFromJsonDictionary(widget, options);
    }        
    
    Offset<Table> TextReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                           flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        bool touchScaleEnabled = false;
        bool isCustomSize = false;
        std::string fontName = "";
        int fontSize = 20;
        std::string text = "Text Label";
        int areaWidth = 0;
        int areaHeight = 0;
        int h_alignment = 0;
        int v_alignment = 0;
        bool outlineEnabled = false;
        Color4B outlineColor = Color4B::BLACK;
        int outlineSize = 1;
        bool shadowEnabled = false;
        Color4B shadowColor = Color4B::BLACK;
        Size shadowOffset = Size(2, -2);
        int shadowBlurRadius = 0;
        
        std::string path = "";
        std::string plistFile = "";
        int resourceType = 0;
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "TouchScaleChangeAble")
            {
                touchScaleEnabled = (value == "True") ? true : false;
            }
            else if (name == "LabelText")
            {
                text = value;
            }
            else if (name == "FontSize")
            {
                fontSize = atoi(value.c_str());
            }
            else if (name == "FontName")
            {
                fontName = value;
            }
            else if (name == "AreaWidth")
            {
                areaWidth = atoi(value.c_str());
            }
            else if (name == "AreaHeight")
            {
                areaHeight = atoi(value.c_str());
            }
            else if (name == "HorizontalAlignmentType")
            {
                if (value == "HT_Left")
                {
                    h_alignment = 0;
                }
                else if (value == "HT_Center")
                {
                    h_alignment = 1;
                }
                else if (value == "HT_Right")
                {
                    h_alignment = 2;
                }
            }
            else if (name == "VerticalAlignmentType")
            {
                if (value == "VT_Top")
                {
                    v_alignment = 0;
                }
                else if (value == "VT_Center")
                {
                    v_alignment = 1;
                }
                else if (value == "VT_Bottom")
                {
                    v_alignment = 2;
                }
            }
            else if (name == "IsCustomSize")
            {
                isCustomSize = (value == "True") ? true : false;
            }
            else if (name == "OutlineEnabled")
            {
                outlineEnabled = (value == "True") ? true : false;
            }
            else if (name == "OutlineSize")
            {
                outlineSize = atoi(value.c_str());
            }
            else if (name == "ShadowEnabled")
            {
                shadowEnabled = (value == "True") ? true : false;
            }
            else if (name == "ShadowOffsetX")
            {
                shadowOffset.width = atof(value.c_str());
            }
            else if (name == "ShadowOffsetY")
            {
                shadowOffset.height = atof(value.c_str());
            }
            else if (name == "ShadowBlurRadius")
            {
                shadowBlurRadius = atoi(value.c_str());
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "FontResource")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "Path")
                    {
                        path = value;
                    }
                    else if (name == "Type")
                    {
                        resourceType = 0;
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "OutlineColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "A")
                    {
                        outlineColor.a = atoi(value.c_str());
                    }
                    else if (name == "R")
                    {
                        outlineColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        outlineColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        outlineColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "ShadowColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "A")
                    {
                        shadowColor.a = atoi(value.c_str());
                    }
                    else if (name == "R")
                    {
                        shadowColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        shadowColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        shadowColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        flatbuffers::Color f_outlineColor(outlineColor.a, outlineColor.r, outlineColor.g, outlineColor.b);
        flatbuffers::Color f_shadowColor(shadowColor.a, shadowColor.r, shadowColor.g, shadowColor.b);
        
        auto options = CreateTextOptions(*builder,
                                         widgetOptions,
                                         CreateResourceData(*builder,
                                                            builder->CreateString(path),
                                                            builder->CreateString(plistFile),
                                                            resourceType),
                                         builder->CreateString(fontName),
                                         fontSize,
                                         builder->CreateString(text),
                                         areaWidth,
                                         areaHeight,
                                         h_alignment,
                                         v_alignment,
                                         touchScaleEnabled,
                                         isCustomSize,
                                         outlineEnabled,
                                         &f_outlineColor,
                                         outlineSize,
                                         shadowEnabled,
                                         &f_shadowColor,
                                         shadowOffset.width,
                                         shadowOffset.height,
                                         shadowBlurRadius);
        
        return *(Offset<Table>*)(&options);
    }
    
    void TextReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *textOptions)
    {
        Text* label = static_cast<Text*>(node);
        auto options = (TextOptions*)textOptions;
        
        bool touchScaleEnabled = options->touchScaleEnable() != 0;
        label->setTouchScaleChangeEnabled(touchScaleEnabled);
        
        std::string text = options->text()->c_str();
        label->setString(text);
        
        int fontSize = options->fontSize();
        label->setFontSize(fontSize);
        
        std::string fontName = options->fontName()->c_str();
        label->setFontName(fontName);
        
        Size areaSize = Size(options->areaWidth(), options->areaHeight());
        if (!areaSize.equals(Size::ZERO))
        {
            label->setTextAreaSize(areaSize);
        }
        
        TextHAlignment h_alignment = (TextHAlignment)options->hAlignment();
        label->setTextHorizontalAlignment(h_alignment);
        
        TextVAlignment v_alignment = (TextVAlignment)options->vAlignment();
        label->setTextVerticalAlignment((TextVAlignment)v_alignment);
        
        bool fileExist = false;
        std::string errorFilePath = "";
        auto resourceData = options->fontResource();
        std::string path = resourceData->path()->c_str();
        if (path != "")
        {
            if (FileUtils::getInstance()->isFileExist(path))
            {
                fileExist = true;
            }
            else
            {
                errorFilePath = path;
                fileExist = false;
            }
            if (fileExist)
            {
                label->setFontName(path);
            }
            else
            {
                auto alert = Label::create();
                alert->setString(__String::createWithFormat("%s missed", errorFilePath.c_str())->getCString());
                label->addChild(alert);
            }
        }
        
        bool outlineEnabled = options->outlineEnabled();
        if (outlineEnabled)
        {
            auto f_outlineColor = options->outlineColor();
            if (f_outlineColor)
            {
                Color4B outlineColor(f_outlineColor->r(), f_outlineColor->g(), f_outlineColor->b(), f_outlineColor->a());
                label->enableOutline(outlineColor, options->outlineSize());
            }
        }
        
        bool shadowEnabled = options->shadowEnabled();
        if (shadowEnabled)
        {
            auto f_shadowColor = options->shadowColor();
            if (f_shadowColor)
            {
                Color4B shadowColor(f_shadowColor->r(), f_shadowColor->g(), f_shadowColor->b(), f_shadowColor->a());
                label->enableShadow(shadowColor, Size(options->shadowOffsetX(), options->shadowOffsetY()), options->shadowBlurRadius());
            }
        }

        // Save node color before set widget properties
        auto oldColor = node->getColor();

        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());

        // restore node color and set color to text to fix shadow & outline color won't show correct bug
        node->setColor(oldColor);
        auto optionsWidget = (WidgetOptions*)options->widgetOptions();
        auto f_color = optionsWidget->color();
        Color4B color(f_color->r(), f_color->g(), f_color->b(), f_color->a());
        ((Text *)node)->setTextColor(color);

        label->setUnifySizeEnabled(false);
        
        bool IsCustomSize = options->isCustomSize() != 0;
        label->ignoreContentAdaptWithSize(!IsCustomSize);
        
        auto widgetOptions = options->widgetOptions();
        if (!label->isIgnoreContentAdaptWithSize())
        {
            Size contentSize(widgetOptions->size()->width(), widgetOptions->size()->height());
            label->setContentSize(contentSize);
        }
        
    }
    
    Node* TextReader::createNodeWithFlatBuffers(const flatbuffers::Table *textOptions)
    {
        Text* text = Text::create();
        
        setPropsWithFlatBuffers(text, (Table*)textOptions);
        
        return text;
    }
    
}
