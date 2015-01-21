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

#include "FlatBuffersSerialize.h"

#include "base/ObjectFactory.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CSParseBinary_generated.h"

#include "WidgetReader/NodeReaderProtocol.h"
#include "WidgetReader/NodeReaderDefine.h"

#include "WidgetReader/NodeReader/NodeReader.h"
#include "WidgetReader/SingleNodeReader/SingleNodeReader.h"
#include "WidgetReader/SpriteReader/SpriteReader.h"
#include "WidgetReader/ParticleReader/ParticleReader.h"
#include "WidgetReader/GameMapReader/GameMapReader.h"
#include "WidgetReader/ComAudioReader/ComAudioReader.h"
#include "WidgetReader/ProjectNodeReader/ProjectNodeReader.h"

#include "WidgetReader/ButtonReader/ButtonReader.h"
#include "WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "WidgetReader/ImageViewReader/ImageViewReader.h"
#include "WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "WidgetReader/TextReader/TextReader.h"
#include "WidgetReader/TextFieldReader/TextFieldReader.h"
#include "WidgetReader/TextAtlasReader/TextAtlasReader.h"
#include "WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "WidgetReader/SliderReader/SliderReader.h"
#include "WidgetReader/LayoutReader/LayoutReader.h"
#include "WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "WidgetReader/PageViewReader/PageViewReader.h"
#include "WidgetReader/ListViewReader/ListViewReader.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/util.h"



USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
using namespace flatbuffers;

namespace cocostudio {

static const char* Property_VisibleForFrame = "VisibleForFrame";
static const char* Property_Position        = "Position";
static const char* Property_Scale           = "Scale";
static const char* Property_RotationSkew    = "RotationSkew";
static const char* Property_CColor          = "CColor";
static const char* Property_FileData        = "FileData";
static const char* Property_FrameEvent      = "FrameEvent";
static const char* Property_Alpha           = "Alpha";
static const char* Property_ZOrder          = "ZOrder";
static const char* Property_ActionValue     = "ActionValue";

static FlatBuffersSerialize* _instanceFlatBuffersSerialize = nullptr;
    
FlatBuffersSerialize::FlatBuffersSerialize()
: _isSimulator(false)
, _builder(nullptr)
, _csparsebinary(nullptr)
{
    CREATE_CLASS_NODE_READER_INFO(NodeReader);
    CREATE_CLASS_NODE_READER_INFO(SingleNodeReader);
    CREATE_CLASS_NODE_READER_INFO(SpriteReader);
    CREATE_CLASS_NODE_READER_INFO(ParticleReader);
    CREATE_CLASS_NODE_READER_INFO(GameMapReader);
    
    CREATE_CLASS_NODE_READER_INFO(ButtonReader);
    CREATE_CLASS_NODE_READER_INFO(CheckBoxReader);
    CREATE_CLASS_NODE_READER_INFO(ImageViewReader);
    CREATE_CLASS_NODE_READER_INFO(TextBMFontReader);
    CREATE_CLASS_NODE_READER_INFO(TextReader);
    CREATE_CLASS_NODE_READER_INFO(TextFieldReader);
    CREATE_CLASS_NODE_READER_INFO(TextAtlasReader);
    CREATE_CLASS_NODE_READER_INFO(LoadingBarReader);
    CREATE_CLASS_NODE_READER_INFO(SliderReader);
    CREATE_CLASS_NODE_READER_INFO(LayoutReader);
    CREATE_CLASS_NODE_READER_INFO(ScrollViewReader);
    CREATE_CLASS_NODE_READER_INFO(PageViewReader);
    CREATE_CLASS_NODE_READER_INFO(ListViewReader);
    
}

FlatBuffersSerialize::~FlatBuffersSerialize()
{
    purge();
}

FlatBuffersSerialize* FlatBuffersSerialize::getInstance()
{
    if (!_instanceFlatBuffersSerialize)
    {
        _instanceFlatBuffersSerialize = new FlatBuffersSerialize();
    }
    
    return _instanceFlatBuffersSerialize;
}

void FlatBuffersSerialize::purge()
{
    CC_SAFE_DELETE(_instanceFlatBuffersSerialize);
	
}

void FlatBuffersSerialize::deleteFlatBufferBuilder()
{
    if (_builder != nullptr)
    {
        _builder->Clear();
        CC_SAFE_DELETE(_builder);
    }
}

std::string FlatBuffersSerialize::serializeFlatBuffersWithXMLFile(const std::string &xmlFileName,
                                                                  const std::string &flatbuffersFileName)
{
    
    std::string inFullpath = FileUtils::getInstance()->fullPathForFilename(xmlFileName).c_str();
    
    // xml read
    if (!FileUtils::getInstance()->isFileExist(inFullpath))
    {
        return ".csd file doesn not exists ";
    }
    
    std::string content = FileUtils::getInstance()->getStringFromFile(inFullpath);
    
    // xml parse
    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
    document->Parse(content.c_str());
    
    const tinyxml2::XMLElement* rootElement = document->RootElement();// Root
//    CCLOG("rootElement name = %s", rootElement->Name());
    
    const tinyxml2::XMLElement* element = rootElement->FirstChildElement();
    
    bool serializeEnabled = false;
    std::string rootType = "";
    
    while (element)
    {
//        CCLOG("entity name = %s", element->Name());
        if (strcmp("PropertyGroup", element->Name()) == 0)
        {
            const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
            while (attribute && strcmp("Version", attribute->Name()) != 0)
                attribute = attribute->Next();
            if (attribute)
                _csdVersion = attribute->Value();
        }

        if (strcmp("Content", element->Name()) == 0)
        {
            const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
            
            //
            if (!attribute)
            {
                serializeEnabled = true;
                rootType = "NodeObjectData";
            }
            //
            
            //
            //            while (attribute)
            //            {
            //                std::string name = attribute->Name();
            //                std::string value = attribute->Value();
            //                CCLOG("attribute name = %s, value = %s", name, value);
            //                if (name == "")
            //                {
            //                    serializeEnabled = true;
            //                    rootType = (strcmp("", value) == 0) ? "Node" : value;
            //                }
            //
            //                if (serializeEnabled)
            //                {
            //                    break;
            //                }
            //
            //                attribute = attribute->Next();
            //            }
            //
        }
        
        if (serializeEnabled)
        {
            break;
        }
        
        const tinyxml2::XMLElement* child = element->FirstChildElement();
        if (child)
        {
            element = child;
        }
        else
        {
            element = element->NextSiblingElement();
        }
    }
    
    if (serializeEnabled)
    {
        _builder = new FlatBufferBuilder();
        
        Offset<NodeTree> nodeTree;
        Offset<NodeAction> aciton;
        std::vector<Offset<flatbuffers::AnimationInfo>> animationInfos;
        
        const tinyxml2::XMLElement* child = element->FirstChildElement();
        
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Animation") // action
            {
                const tinyxml2::XMLElement* animation = child;
                aciton = createNodeAction(animation);
            }
            else if (name == "ObjectData") // nodeTree
            {
                const tinyxml2::XMLElement* objectData = child;
                nodeTree = createNodeTree(objectData, rootType);
            }
            else if (name == "AnimationList") // animation list
            {
                const tinyxml2::XMLElement* animationinfoElement = child->FirstChildElement();
                while (animationinfoElement)
                {
                    auto animationinfo = createAnimationInfo(animationinfoElement);
                    animationInfos.push_back(animationinfo);
                    animationinfoElement = animationinfoElement->NextSiblingElement();
                }
            }
            child = child->NextSiblingElement();
        }

        
        auto csparsebinary = CreateCSParseBinary(*_builder,
                                                 _builder->CreateString(_csdVersion),
                                                 _builder->CreateVector(_textures),
                                                 _builder->CreateVector(_texturePngs),
                                                 nodeTree,
                                                 aciton,
                                                 _builder->CreateVector(animationInfos));
        _builder->Finish(csparsebinary);
        
        _textures.clear();
        _texturePngs.clear();
        
        
        std::string outFullPath = FileUtils::getInstance()->fullPathForFilename(flatbuffersFileName);
        size_t pos = outFullPath.find_last_of('.');
        std::string convert = outFullPath.substr(0, pos).append(".csb");
        auto save = flatbuffers::SaveFile(convert.c_str(),
										  reinterpret_cast<const char *>(_builder->GetBufferPointer()),
										  _builder->GetSize(),
                                          true);
        if (!save)
        {
            return "couldn't save files!";
        }
        
        deleteFlatBufferBuilder();
    }
    
    return "";
}

// NodeTree
Offset<NodeTree> FlatBuffersSerialize::createNodeTree(const tinyxml2::XMLElement *objectData,
                                                      std::string classType)
{
    std::string classname = classType.substr(0, classType.find("ObjectData"));
//    CCLOG("classname = %s", classname.c_str());
    
    std::string name = "";
    
    Offset<Options> options;
    std::vector<Offset<NodeTree>> children;
    
    if (classname == "ProjectNode")
    {
        auto reader = ProjectNodeReader::getInstance();
        options = CreateOptions(*_builder, reader->createOptionsWithFlatBuffers(objectData, _builder));
    }
    else if (classname == "SimpleAudio")
    {
        auto reader = ComAudioReader::getInstance();
        options = CreateOptions(*_builder, reader->createOptionsWithFlatBuffers(objectData, _builder));
    }
    else
    {
        std::string readername = getGUIClassName(classname);
        readername.append("Reader");
        
        NodeReaderProtocol* reader = dynamic_cast<NodeReaderProtocol*>(ObjectFactory::getInstance()->createObject(readername));
        options = CreateOptions(*_builder, reader->createOptionsWithFlatBuffers(objectData, _builder));
    }
    
    
    // children
    bool containChildrenElement = false;
    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    
    while (child)
    {
//        CCLOG("child name = %s", child->Name());
        
        if (strcmp("Children", child->Name()) == 0)
        {
            containChildrenElement = true;
            break;
        }
        
        child = child->NextSiblingElement();
    }
    
    if (containChildrenElement)
    {
        child = child->FirstChildElement();
//        CCLOG("element name = %s", child->Name());
        
        while (child)
        {
            const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
            bool bHasType = false;
            while (attribute)
            {
                std::string attriname = attribute->Name();
                std::string value = attribute->Value();
                
                if (attriname == "ctype")
                {
                    children.push_back(createNodeTree(child, value));
                    
                    bHasType = true;
                    break;
                }
                
                attribute = attribute->Next();
            }
            
            if(!bHasType)
            {
                children.push_back(createNodeTree(child, "NodeObjectData"));
            }
            
            child = child->NextSiblingElement();
        }
    }
    //
    
    std::string customClassName = "";
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string attriname = attribute->Name();
        std::string value = attribute->Value();
        
        if (attriname == "CustomClassName")
        {
            customClassName = value;
            break;
        }
        
        attribute = attribute->Next();
    }
    
    return CreateNodeTree(*_builder,
                          _builder->CreateString(classname),
                          _builder->CreateVector(children),
                          options,
                          _builder->CreateString(customClassName));
    
}

int FlatBuffersSerialize::getResourceType(std::string key)
{
    if(key == "Normal" || key == "Default")
    {
        return 	0;
    }
    
    if(_isSimulator)
    {
        if(key == "MarkedSubImage")
        {
            return 0;
        }
    }
    return 1;
}

std::string FlatBuffersSerialize::getGUIClassName(const std::string &name)
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

std::string FlatBuffersSerialize::getWidgetReaderClassName(Widget* widget)
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
//


// NodeAction
Offset<NodeAction> FlatBuffersSerialize::createNodeAction(const tinyxml2::XMLElement *objectData)
{
    int duration = 0;
    float speed = 0.0f;
    std::string currentAnimationName = "";
    
//    CCLOG("animation name = %s", objectData->Name());
    
    // ActionTimeline
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    
    // attibutes
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string value = attribute->Value();
        
        if (name == "Duration")
        {
            duration = atoi(value.c_str());
        }
        else if (name == "Speed")
        {
            speed = atof(value.c_str());
        }
        else if (name == "ActivedAnimationName")
        {
            currentAnimationName = value.c_str();
        }
        
        attribute = attribute->Next();
    }
    
    // all Timeline
    std::vector<Offset<TimeLine>> timelines;
    const tinyxml2::XMLElement* timelineElement = objectData->FirstChildElement();
    while (timelineElement)
    {
        auto timeLine = createTimeLine(timelineElement);
        timelines.push_back(timeLine);
        
        timelineElement = timelineElement->NextSiblingElement();
    }
    
    return CreateNodeAction(*_builder,
                            duration,
                            speed,
                            _builder->CreateVector(timelines),
                            _builder->CreateString(currentAnimationName));
}


Offset<flatbuffers::AnimationInfo> FlatBuffersSerialize::createAnimationInfo(const tinyxml2::XMLElement *objectData)
 {
     std::string infoName = "";
     int startIndex = 0;
     int endIndex = 0;
 
     const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
     while (attribute)
     {
         std::string attriname = attribute->Name();
         std::string attrivalue = attribute->Value();
         if (attriname == "Name")
         {
             infoName = attrivalue;
         }
         else if (attriname == "StartIndex")
         {
             startIndex = atoi(attrivalue.c_str());
         }
         else if (attriname == "EndIndex")
         {
             endIndex = atoi(attrivalue.c_str());
         }
         attribute = attribute->Next();
     }
     return CreateAnimationInfo(*_builder, _builder->CreateString(infoName), startIndex, endIndex);
 }

Offset<TimeLine> FlatBuffersSerialize::createTimeLine(const tinyxml2::XMLElement *objectData)
{
    int actionTag = 0;
    std::string property = "";
    
    // TimelineData attrsibutes
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string value = attribute->Value();
        
        if (name == "ActionTag")
        {
            actionTag = atoi(value.c_str());
        }
        else if (name == "Property")
        {
            property = value;
        }
        
        attribute = attribute->Next();
    }
    
    // all Frame
    std::vector<Offset<flatbuffers::Frame>> frames;
    
    const tinyxml2::XMLElement* frameElement = objectData->FirstChildElement();
    while (frameElement)
    {
        Offset<flatbuffers::Frame> frame;
        
        if (property == Property_VisibleForFrame)
        {
            auto boolFrame = createBoolFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                0, // ScaleFrame
                                0, // ColorFrame
                                0, // TextureFrame
                                0, // EventFrame
                                0, // IntFrame
                                boolFrame);
        }
        else if (property == Property_Position)
        {
            auto pointFrame = createPointFrame(frameElement);
            frame = CreateFrame(*_builder,
                                pointFrame);
        }
        else if (property == Property_Scale)
        {
            auto scaleFrame = createScaleFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                scaleFrame);
        }
        else if (property == Property_RotationSkew)
        {
            auto scaleFrame = createScaleFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                scaleFrame);
        }
        else if (property == Property_CColor)
        {
            auto colorFrame = createColorFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                0, // ScaleFrame
                                colorFrame);
        }
        else if (property == Property_FileData)
        {
            auto textureFrame = createTextureFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                0, // ScaleFrame
                                0, // ColorFrame
                                textureFrame);
        }
        else if (property == Property_FrameEvent)
        {
            auto eventFrame = createEventFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                0, // ScaleFrame
                                0, // ColorFrame
                                0, // TextureFrame
                                eventFrame);
        }
        else if (property == Property_Alpha)
        {
            auto intFrame = createIntFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                0, // ScaleFrame
                                0, // ColorFrame
                                0, // TextureFrame
                                0, // EventFrame
                                intFrame);
        }
        else if (property == Property_ZOrder)
        {
            auto intFrame = createIntFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                0, // ScaleFrame
                                0, // ColorFrame
                                0, // TextureFrame
                                0, // EventFrame
                                intFrame);
        }
        else if (property == Property_ActionValue)
        {
            auto innerActionFrame = createInnerActionFrame(frameElement);
            frame = CreateFrame(*_builder,
                                0, // PointFrame
                                0, // ScaleFrame
                                0, // ColorFrame
                                0, // TextureFrame
                                0, // EventFrame
                                0, // IntFrame
                                0, // BoolFrame
                                innerActionFrame);
        }
        
        frames.push_back(frame);
                
        frameElement = frameElement->NextSiblingElement();
    }
    
    return CreateTimeLine(*_builder,
                          _builder->CreateString(property),
                          actionTag,
                          _builder->CreateVector(frames));
}
    
Offset<flatbuffers::PointFrame> FlatBuffersSerialize::createPointFrame(const tinyxml2::XMLElement *objectData)
{
    int frameIndex = 0;
    bool tween = true;
    Vec2 position;
    
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string value = attribute->Value();
        
        if (name == "X")
        {
            position.x = atof(value.c_str());
        }
        else if (name == "Y")
        {
            position.y = atof(value.c_str());
        }
        else if (name == "FrameIndex")
        {
            frameIndex = atoi(value.c_str());
        }
        else if (name == "Tween")
        {
            tween = (value == "True") ? true : false;
        }
        
        attribute = attribute->Next();
    }
    
    Position f_position(position.x, position.y);
    
    return CreatePointFrame(*_builder,
                            frameIndex,
                            tween,
                            &f_position);
}

Offset<flatbuffers::ScaleFrame> FlatBuffersSerialize::createScaleFrame(const tinyxml2::XMLElement *objectData)
{
    int frameIndex = 0;
    bool tween = true;
    Vec2 scale;
    
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string value = attribute->Value();
        
        if (name == "X")
        {
            scale.x = atof(value.c_str());
        }
        else if (name == "Y")
        {
            scale.y = atof(value.c_str());
        }
        else if (name == "FrameIndex")
        {
            frameIndex = atoi(value.c_str());
        }
        else if (name == "Tween")
        {
            tween = (value == "True") ? true : false;
        }
        
        attribute = attribute->Next();
    }
    
    Scale f_scale(scale.x, scale.y);
    
    return CreateScaleFrame(*_builder,
                            frameIndex,
                            tween,
                            &f_scale);
}

Offset<flatbuffers::ColorFrame> FlatBuffersSerialize::createColorFrame(const tinyxml2::XMLElement *objectData)
{
    int frameIndex = 0;
    bool tween = true;
    Color3B color;
    
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string value = attribute->Value();
        
        if (name == "FrameIndex")
        {
            frameIndex = atoi(value.c_str());
        }
        else if (name == "Tween")
        {
            tween = (value == "True") ? true : false;
        }
        
        attribute = attribute->Next();
    }
    
    // color
    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    while (child)
    {
        attribute = child->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();
            
            if (name == "R")
            {
                color.r = atoi(value.c_str());
            }
            else if (name == "G")
            {
                color.g = atoi(value.c_str());
            }
            else if (name == "B")
            {
                color.b = atoi(value.c_str());
            }
            
            attribute = attribute->Next();
        }
        
        child = child->NextSiblingElement();
    }
    
    Color f_color(255, color.r, color.g, color.b);
    
    return CreateColorFrame(*_builder,
                            frameIndex,
                            tween,
                            &f_color);
}

Offset<flatbuffers::TextureFrame> FlatBuffersSerialize::createTextureFrame(const tinyxml2::XMLElement *objectData)
{
    int frameIndex = 0;
    bool tween = true;
    
    std::string path = "";
    std::string plistFile = "";
    int resourceType = 0;
    
    std::string texture = "";
    std::string texturePng = "";
    
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string attriname = attribute->Name();
        std::string value = attribute->Value();
        
        if (attriname == "FrameIndex")
        {
            frameIndex = atoi(value.c_str());
        }
        else if (attriname == "Tween")
        {
            tween = (value == "True") ? true : false;
        }
        
        attribute = attribute->Next();
    }
    
    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    while (child)
    {
        attribute = child->FirstAttribute();
        while (attribute)
        {
            std::string attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if (attriname == "Path")
            {
                path = value;
            }
            else if (attriname == "Type")
            {
                resourceType = getResourceType(value);
            }
            else if (attriname == "Plist")
            {
                plistFile = value;
                texture = value;
            }
            
            attribute = attribute->Next();
        }
        
        if (resourceType == 1)
        {
            _textures.push_back(_builder->CreateString(texture));
        }
        
        child = child->NextSiblingElement();
    }
    
    return CreateTextureFrame(*_builder,
                              frameIndex,
                              tween,
                              CreateResourceData(*_builder,
                                                 _builder->CreateString(path),
                                                 _builder->CreateString(plistFile),
                                                 resourceType));
}

Offset<flatbuffers::EventFrame> FlatBuffersSerialize::createEventFrame(const tinyxml2::XMLElement *objectData)
{
    int frameIndex = 0;
    bool tween = true;
    std::string value = "";
    
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string attrivalue = attribute->Value();
        
        if (name == "Value") // to be gonna modify
        {
            value = attrivalue;
        }
        else if (name == "FrameIndex")
        {
            frameIndex = atoi(attrivalue.c_str());
        }
        else if (name == "Tween")
        {
            tween = (attrivalue == "True") ? true : false;
        }
        
        attribute = attribute->Next();
    }
    
    return CreateEventFrame(*_builder,
                            frameIndex,
                            tween,
                            _builder->CreateString(value));
}

Offset<flatbuffers::IntFrame> FlatBuffersSerialize::createIntFrame(const tinyxml2::XMLElement *objectData)
{
    int frameIndex = 0;
    bool tween = true;
    int value = 0;
    
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string attrivalue = attribute->Value();
        
        if (name == "Value") // to be gonna modify
        {
            value = atoi(attrivalue.c_str());
        }
        else if (name == "FrameIndex")
        {
            frameIndex = atoi(attrivalue.c_str());
        }
        else if (name == "Tween")
        {
            tween = (attrivalue == "True") ? true : false;
        }
        
        attribute = attribute->Next();
    }
    
    return CreateIntFrame(*_builder,
                          frameIndex,
                          tween,
                          value);
}
    
Offset<flatbuffers::BoolFrame> FlatBuffersSerialize::createBoolFrame(const tinyxml2::XMLElement *objectData)
{
    int frameIndex = 0;
    bool tween = true;
    bool value = true;
    
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string attrivalue = attribute->Value();
        
        if (name == "Value")
        {
            value = (attrivalue == "True") ? true : false;
        }
        else if (name == "FrameIndex")
        {
            frameIndex = atoi(attrivalue.c_str());
        }
        else if (name == "Tween")
        {
            tween = (attrivalue == "True") ? true : false;
        }
        
        attribute = attribute->Next();
    }
    
    return CreateBoolFrame(*_builder,
                          frameIndex,
                          tween,
                          value);
}
    
    Offset<flatbuffers::InnerActionFrame> FlatBuffersSerialize::createInnerActionFrame(const tinyxml2::XMLElement *objectData)
    {
        int frameIndex = 0;
        bool tween = true;
        int innerActionType = 0;
        std::string currentAniamtionName = "";
        int singleFrameIndex = 0;
        
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string attrivalue = attribute->Value();
            
            if (name == "InnerActionType")
            {
                if (attrivalue == "LoopAction")
                {
                    innerActionType = 0;
                }
                else if (attrivalue == "NoLoopAction")
                {
                    innerActionType = 1;
                }
                else if (attrivalue == "SingleFrame")
                {
                    innerActionType = 2;
                }
            }
            else if (name == "CurrentAniamtionName")
            {
                currentAniamtionName = attrivalue;
            }
            else if (name == "SingleFrameIndex")
            {
                singleFrameIndex = atoi(attrivalue.c_str());
            }
            else if (name == "FrameIndex")
            {
                frameIndex = atoi(attrivalue.c_str());
            }
            else if (name == "Tween")
            {
                tween = (attrivalue == "True") ? true : false;
            }
            
            attribute = attribute->Next();
        }
        
        return CreateInnerActionFrame(*_builder,
                                      frameIndex,
                                      tween,
                                      innerActionType,
                                      _builder->CreateString(currentAniamtionName),
                                      singleFrameIndex);
    }

/* create flat buffers with XML */
FlatBufferBuilder* FlatBuffersSerialize::createFlatBuffersWithXMLFileForSimulator(const std::string &xmlFileName)
{    
    std::string inFullpath = FileUtils::getInstance()->fullPathForFilename(xmlFileName).c_str();
    
    // xml read
    if (!FileUtils::getInstance()->isFileExist(inFullpath))
    {
//        CCLOG(".csd file doesn not exists ");
    }
    
    std::string content = FileUtils::getInstance()->getStringFromFile(inFullpath);
    
    // xml parse
    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
    document->Parse(content.c_str());
    
    const tinyxml2::XMLElement* rootElement = document->RootElement();// Root
//    CCLOG("rootElement name = %s", rootElement->Name());
    
    const tinyxml2::XMLElement* element = rootElement->FirstChildElement();
    
    bool serializeEnabled = false;
    std::string rootType = "";
    
    while (element)
    {
//        CCLOG("entity name = %s", element->Name());
        if (strcmp("PropertyGroup", element->Name()) == 0)
        {
            const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
            while (attribute && strcmp("Version", attribute->Name()) != 0)
                attribute = attribute->Next();
            if (attribute)
                _csdVersion = attribute->Value();
        }
        
        if (strcmp("Content", element->Name()) == 0)
        {
            const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
            
            //
            if (!attribute)
            {
                serializeEnabled = true;
                rootType = "NodeObjectData";
            }
        }
        
        if (serializeEnabled)
        {
            break;
        }
        
        const tinyxml2::XMLElement* child = element->FirstChildElement();
        if (child)
        {
            element = child;
        }
        else
        {
            element = element->NextSiblingElement();
        }
    }
    
    if (serializeEnabled)
    {
        _builder = new FlatBufferBuilder();

        Offset<NodeTree> nodeTree;
        Offset<NodeAction> aciton;
        std::vector<Offset<flatbuffers::AnimationInfo> > animationInfos;
        
        const tinyxml2::XMLElement* child = element->FirstChildElement();
        
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Animation") // action
            {
                const tinyxml2::XMLElement* animation = child;
                aciton = createNodeAction(animation);
            }
            else if (name == "ObjectData") // nodeTree
            {
                const tinyxml2::XMLElement* objectData = child;
                nodeTree = createNodeTreeForSimulator(objectData, rootType);
            }
            else if (name == "AnimationList") // animation list
            {
                const tinyxml2::XMLElement* animationinfoElement = child->FirstChildElement();
                while (animationinfoElement)
                {
                    auto animationinfo = createAnimationInfo(animationinfoElement);
                    animationInfos.push_back(animationinfo);
                    animationinfoElement = animationinfoElement->NextSiblingElement();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
		auto csparsebinary = CreateCSParseBinary(*_builder,
                                                 _builder->CreateString(_csdVersion),
                                                 _builder->CreateVector(_textures),
                                                 _builder->CreateVector(_texturePngs),
                                                 nodeTree,
                                                 aciton,
                                                 _builder->CreateVector(animationInfos));
        _builder->Finish(csparsebinary);
        
        _textures.clear();
        _texturePngs.clear();
    }
    return _builder;
}

Offset<NodeTree> FlatBuffersSerialize::createNodeTreeForSimulator(const tinyxml2::XMLElement *objectData,
                                                                  std::string classType)
{
    std::string classname = classType.substr(0, classType.find("ObjectData"));
//    CCLOG("classname = %s", classname.c_str());
    
    std::string name = "";
    
    Offset<Options> options;
    std::vector<Offset<NodeTree>> children;
    
    if (classname == "ProjectNode")
    {
        auto projectNodeOptions = createProjectNodeOptionsForSimulator(objectData);
        options = CreateOptions(*_builder, *(Offset<Table>*)(&projectNodeOptions));
    }
    else if (classname == "SimpleAudio")
    {
        auto reader = ComAudioReader::getInstance();
        options = CreateOptions(*_builder, reader->createOptionsWithFlatBuffers(objectData, _builder));
    }
    else
    {
        std::string readername = getGUIClassName(classname);
        readername.append("Reader");
        
        NodeReaderProtocol* reader = dynamic_cast<NodeReaderProtocol*>(ObjectFactory::getInstance()->createObject(readername));
        options = CreateOptions(*_builder, reader->createOptionsWithFlatBuffers(objectData, _builder));
    }
    
    
    // children
    bool containChildrenElement = false;
    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    
    while (child)
    {
//        CCLOG("child name = %s", child->Name());
        
        if (strcmp("Children", child->Name()) == 0)
        {
            containChildrenElement = true;
            break;
        }
        
        child = child->NextSiblingElement();
    }
    
    if (containChildrenElement)
    {
        child = child->FirstChildElement();
//        CCLOG("element name = %s", child->Name());
        
        while (child)
        {
            const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
            bool bHasType = false;
            while (attribute)
            {
                std::string attriname = attribute->Name();
                std::string value = attribute->Value();
                
                if (attriname == "ctype")
                {
                    children.push_back(createNodeTreeForSimulator(child, value));
                    
                    bHasType = true;
                    break;
                }
                
                attribute = attribute->Next();
            }
            
            if(!bHasType)
            {
                children.push_back(createNodeTreeForSimulator(child, "NodeObjectData"));
            }
            
            child = child->NextSiblingElement();
        }
    }
    //
    
    
    std::string customClassName = "";
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string attriname = attribute->Name();
        std::string value = attribute->Value();
        
        if (attriname == "CustomClassName")
        {
            customClassName = value;
            break;
        }
        
        attribute = attribute->Next();
    }
    
    return CreateNodeTree(*_builder,
                          _builder->CreateString(classname),
                          _builder->CreateVector(children),
                          options,
                          _builder->CreateString(customClassName));
}

Offset<ProjectNodeOptions> FlatBuffersSerialize::createProjectNodeOptionsForSimulator(const tinyxml2::XMLElement *objectData)
{
    auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, _builder);
    auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);

    std::string filename = "";

    // FileData
    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    while (child)
    {
        std::string name = child->Name();
        
        if (name == "FileData")
        {
            const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
            
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();
                
                if (name == "Path")
                {
                    filename = value;
                }
                
                attribute = attribute->Next();
            }
        }
        
        child = child->NextSiblingElement();
    }
    
    return CreateProjectNodeOptions(*_builder,
                                    nodeOptions,
                                    _builder->CreateString(filename));
}
    
}
/**/
