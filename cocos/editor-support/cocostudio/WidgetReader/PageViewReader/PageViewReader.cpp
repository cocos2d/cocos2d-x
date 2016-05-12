

#include "editor-support/cocostudio/WidgetReader/PageViewReader/PageViewReader.h"

#include "ui/UIPageView.h"
#include "ui/UILayout.h"
#include "editor-support/cocostudio/CocoLoader.h"
#include "editor-support/cocostudio/CSParseBinary_generated.h"
#include "editor-support/cocostudio/FlatBuffersSerialize.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"
#include "platform/CCFileUtils.h"
#include "2d/CCSpriteFrameCache.h"

USING_NS_CC;
using namespace ui;
using namespace flatbuffers;

namespace cocostudio
{
    static PageViewReader* instancePageViewReader = nullptr;
    
    IMPLEMENT_CLASS_NODE_READER_INFO(PageViewReader)
    
    PageViewReader::PageViewReader()
    {
        
    }
    
    PageViewReader::~PageViewReader()
    {
        
    }
    
    PageViewReader* PageViewReader::getInstance()
    {
        if (!instancePageViewReader)
        {
            instancePageViewReader = new (std::nothrow) PageViewReader();
        }
        return instancePageViewReader;
    }
    
    void PageViewReader::destroyInstance()
    {
        CC_SAFE_DELETE(instancePageViewReader);
    }
    
    void PageViewReader::setPropsFromBinary(cocos2d::ui::Widget *widget, CocoLoader *cocoLoader, stExpCocoNode *cocoNode)
	{
		LayoutReader::setPropsFromBinary(widget, cocoLoader, cocoNode);
    }
    
    void PageViewReader::setPropsFromJsonDictionary(Widget *widget, const rapidjson::Value &options)
    {
        LayoutReader::setPropsFromJsonDictionary(widget, options);
    }        
    
    Offset<Table> PageViewReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                               flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto widgetOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string path = "";
        std::string plistFile = "";
        int resourceType = 0;
        
        bool clipEnabled = false;
        Color3B bgColor;
        Color3B bgStartColor;
        Color3B bgEndColor;
        int colorType = 0;
        GLubyte bgColorOpacity = 255;
        Vec2 colorVector(0.0f, -0.5f);
        Rect capInsets;
        Size scale9Size;
        bool backGroundScale9Enabled = false;
        
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "ClipAble")
            {
                clipEnabled = (value == "True") ? true : false;
            }
            else if (name == "ComboBoxIndex")
            {
                colorType = atoi(value.c_str());
            }
            else if (name == "BackColorAlpha")
            {
                bgColorOpacity = atoi(value.c_str());
            }
            else if (name == "Scale9Enable")
            {
                if (value == "True")
                {
                    backGroundScale9Enabled = true;
                }
            }
            else if (name == "Scale9OriginX")
            {
                capInsets.origin.x = atof(value.c_str());
            }
            else if (name == "Scale9OriginY")
            {
                capInsets.origin.y = atof(value.c_str());
            }
            else if (name == "Scale9Width")
            {
                capInsets.size.width = atof(value.c_str());
            }
            else if (name == "Scale9Height")
            {
                capInsets.size.height = atof(value.c_str());
            }
            
            attribute = attribute->Next();
        }
        
        // child elements
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Size" && backGroundScale9Enabled)
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "X")
                    {
                        scale9Size.width = atof(value.c_str());
                    }
                    else if (name == "Y")
                    {
                        scale9Size.height = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "SingleColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        bgColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        bgColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        bgColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "EndColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        bgEndColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        bgEndColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        bgEndColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "FirstColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "R")
                    {
                        bgStartColor.r = atoi(value.c_str());
                    }
                    else if (name == "G")
                    {
                        bgStartColor.g = atoi(value.c_str());
                    }
                    else if (name == "B")
                    {
                        bgStartColor.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "ColorVector")
            {
                attribute = child->FirstAttribute();
                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (name == "ScaleX")
                    {
                        colorVector.x = atof(value.c_str());
                    }
                    else if (name == "ScaleY")
                    {
                        colorVector.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (name == "FileData")
            {
                std::string texture = "";
                std::string texturePng = "";
                
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
                        resourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                        texture = value;
                    }
                    
                    attribute = attribute->Next();
                }
                
                if (resourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));                    
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        Color f_bgColor(255, bgColor.r, bgColor.g, bgColor.b);
        Color f_bgStartColor(255, bgStartColor.r, bgStartColor.g, bgStartColor.b);
        Color f_bgEndColor(255, bgEndColor.r, bgEndColor.g, bgEndColor.b);
        ColorVector f_colorVector(colorVector.x, colorVector.y);
        CapInsets f_capInsets(capInsets.origin.x, capInsets.origin.y, capInsets.size.width, capInsets.size.height);
        FlatSize f_scale9Size(scale9Size.width, scale9Size.height);
        
        auto options = CreatePageViewOptions(*builder,
                                             widgetOptions,
                                             CreateResourceData(*builder,
                                                                builder->CreateString(path),
                                                                builder->CreateString(plistFile),
                                                                resourceType),
                                             clipEnabled,
                                             &f_bgColor,
                                             &f_bgStartColor,
                                             &f_bgEndColor,
                                             colorType,
                                             bgColorOpacity,
                                             &f_colorVector,
                                             &f_capInsets,
                                             &f_scale9Size,
                                             backGroundScale9Enabled);
        
        return *(Offset<Table>*)(&options);
    }
    
    void PageViewReader::setPropsWithFlatBuffers(cocos2d::Node *node, const flatbuffers::Table *pageViewOptions)
    {
        PageView* pageView = static_cast<PageView*>(node);
        auto options = (PageViewOptions*)pageViewOptions;
        
        bool clipEnabled = options->clipEnabled() != 0;
        pageView->setClippingEnabled(clipEnabled);
        
        bool backGroundScale9Enabled = options->backGroundScale9Enabled() != 0;
        pageView->setBackGroundImageScale9Enabled(backGroundScale9Enabled);
        
        
        auto f_bgColor = options->bgColor();
        Color3B bgColor(f_bgColor->r(), f_bgColor->g(), f_bgColor->b());
        auto f_bgStartColor = options->bgStartColor();
        Color3B bgStartColor(f_bgStartColor->r(), f_bgStartColor->g(), f_bgStartColor->b());
        auto f_bgEndColor = options->bgEndColor();
        Color3B bgEndColor(f_bgEndColor->r(), f_bgEndColor->g(), f_bgEndColor->b());
        
        auto f_colorVecor = options->colorVector();
        Vec2 colorVector(f_colorVecor->vectorX(), f_colorVecor->vectorY());
        pageView->setBackGroundColorVector(colorVector);
        
        int bgColorOpacity = options->bgColorOpacity();
        
        int colorType = options->colorType();
        pageView->setBackGroundColorType(Layout::BackGroundColorType(colorType));
        
        pageView->setBackGroundColor(bgStartColor, bgEndColor);
        pageView->setBackGroundColor(bgColor);
        pageView->setBackGroundColorOpacity(bgColorOpacity);
        
        
        bool fileExist = false;
        std::string errorFilePath = "";
        auto imageFileNameDic = options->backGroundImageData();
        int imageFileNameType = imageFileNameDic->resourceType();
        std::string imageFileName = imageFileNameDic->path()->c_str();
        if (imageFileName != "")
        {
            switch (imageFileNameType)
            {
                case 0:
                {
                    if (FileUtils::getInstance()->isFileExist(imageFileName))
                    {
                        fileExist = true;
                    }
                    else
                    {
                        errorFilePath = imageFileName;
                        fileExist = false;
                    }
                    break;
                }
                    
                case 1:
                {
                    std::string plist = imageFileNameDic->plistFile()->c_str();
                    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imageFileName);
                    if (spriteFrame)
                    {
                        fileExist = true;
                    }
                    else
                    {
                        if (FileUtils::getInstance()->isFileExist(plist))
                        {
                            ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                            ValueMap metadata = value["metadata"].asValueMap();
                            std::string textureFileName = metadata["textureFileName"].asString();
                            if (!FileUtils::getInstance()->isFileExist(textureFileName))
                            {
                                errorFilePath = textureFileName;
                            }
                        }
                        else
                        {
                            errorFilePath = plist;
                        }
                        fileExist = false;
                    }
                    break;
                }
                    
                default:
                    break;
            }
            if (fileExist)
            {
                pageView->setBackGroundImage(imageFileName, (Widget::TextureResType)imageFileNameType);
            }
        }
        
        auto widgetOptions = options->widgetOptions();
        auto f_color = widgetOptions->color();
        Color3B color(f_color->r(), f_color->g(), f_color->b());
        pageView->setColor(color);
        
        int opacity = widgetOptions->alpha();
        pageView->setOpacity(opacity);
        
        
        auto widgetReader = WidgetReader::getInstance();
        widgetReader->setPropsWithFlatBuffers(node, (Table*)options->widgetOptions());
        
        if (backGroundScale9Enabled)
        {
            auto f_capInsets = options->capInsets();
            Rect capInsets(f_capInsets->x(), f_capInsets->y(), f_capInsets->width(), f_capInsets->height());
            pageView->setBackGroundImageCapInsets(capInsets);
            
            auto f_scale9Size = options->scale9Size();
            Size scale9Size(f_scale9Size->width(), f_scale9Size->height());
            pageView->setContentSize(scale9Size);
        }
        else
        {
            if (!pageView->isIgnoreContentAdaptWithSize())
            {
                Size contentSize(widgetOptions->size()->width(), widgetOptions->size()->height());
                pageView->setContentSize(contentSize);
            }
        }
    }
    
    Node* PageViewReader::createNodeWithFlatBuffers(const flatbuffers::Table *pageViewOptions)
    {
        PageView* pageView = PageView::create();
        
        setPropsWithFlatBuffers(pageView, (Table*)pageViewOptions);
        
        return pageView;
    }
    
    int PageViewReader::getResourceType(std::string key)
    {
        if(key == "Normal" || key == "Default")
        {
            return 	0;
        }
        
        FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
        if(fbs->_isSimulator)
        {
            if(key == "MarkedSubImage")
            {
                return 0;
            }
        }
        return 1;
    }
    
}
