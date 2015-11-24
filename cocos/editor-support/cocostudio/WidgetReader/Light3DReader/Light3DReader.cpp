/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
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

#include "Light3DReader.h"

#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/CSParse3DBinary_generated.h"

#include "cocostudio/FlatBuffersSerialize.h"
#include "cocostudio/WidgetReader/Node3DReader/Node3DReader.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace flatbuffers;

namespace cocostudio
{
    IMPLEMENT_CLASS_NODE_READER_INFO(Light3DReader)
    
    Light3DReader::Light3DReader()
    {
        
    }
    
    Light3DReader::~Light3DReader()
    {
        
    }
    
    static Light3DReader* _instanceLight3DReader = nullptr;
    
    Light3DReader* Light3DReader::getInstance()
    {
        if (!_instanceLight3DReader)
        {
            _instanceLight3DReader = new Light3DReader();
        }
        
        return _instanceLight3DReader;
    }
    
    void Light3DReader::purge()
    {
        CC_SAFE_DELETE(_instanceLight3DReader);
    }
    
    void Light3DReader::destroyInstance()
    {
        CC_SAFE_DELETE(_instanceLight3DReader);
    }
    
    Offset<Table> Light3DReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                             flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = Node3DReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto node3DOptions = *(Offset<Node3DOption>*)(&temp);
        
        bool enabled = true;
        int type = 0;
        int flag = 0;
        float intensity = 1.0f;
        float range = 5.0f;
        float outerAngle = 30.0f;

        std::string attriname;
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while(attribute)
        {
            attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if (attriname == "Type")
            {
                if (value == "DIRECTIONAL")  type = (int)LightType::DIRECTIONAL;
                else if (value == "POINT") type = (int)LightType::POINT;
                else if (value == "SPOT") type = (int)LightType::SPOT;
                else if (value == "AMBIENT") type = (int)LightType::AMBIENT;
            }
            else if (attriname == "Flag")
            {
                if (value == "LIGHT0")  flag = (int)LightFlag::LIGHT0;
                else if (value == "LIGHT1") flag = (int)LightFlag::LIGHT1;
                else if (value == "LIGHT2") flag = (int)LightFlag::LIGHT2;
                else if (value == "LIGHT3") flag = (int)LightFlag::LIGHT3;
                else if (value == "LIGHT4") flag = (int)LightFlag::LIGHT4;
                else if (value == "LIGHT5") flag = (int)LightFlag::LIGHT5;
                else if (value == "LIGHT6") flag = (int)LightFlag::LIGHT6;
                else if (value == "LIGHT7") flag = (int)LightFlag::LIGHT7;
                else if (value == "LIGHT8") flag = (int)LightFlag::LIGHT8;
                else if (value == "LIGHT9") flag = (int)LightFlag::LIGHT9;
                else if (value == "LIGHT10") flag = (int)LightFlag::LIGHT10;
                else if (value == "LIGHT11") flag = (int)LightFlag::LIGHT11;
                else if (value == "LIGHT12") flag = (int)LightFlag::LIGHT12;
            }
            else if (attriname == "Intensity")
            {
                intensity = atof(value.c_str());
            }
            else if (attriname == "Range")
            {
                range = atof(value.c_str());
            }
            else if (attriname == "OuterAngle")
            {
                outerAngle = atof(value.c_str());
            }
            else if (attriname == "Enable")
            {
                enabled = (value == "True") ? true : false;
            }
            
            attribute = attribute->Next();
        }
        
        auto options = CreateLight3DOption(*builder,node3DOptions,enabled,type,flag,intensity,range,outerAngle);
        
        return *(Offset<Table>*)(&options);
    }
    
    void Light3DReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                                   const flatbuffers::Table* light3DOptions)
    {
        auto options = (Sprite3DOptions*)light3DOptions;
        auto node3DReader = Node3DReader::getInstance();
        node3DReader->setPropsWithFlatBuffers(node, (Table*)(options->node3DOption()));
    }
    
    Node* Light3DReader::createNodeWithFlatBuffers(const flatbuffers::Table* light3DOptions)
    {
        Node* lightNode = Node::create();

        auto options = (Light3DOption*)light3DOptions;

        BaseLight* light = nullptr;
        LightType type = (LightType)options->type();
        LightFlag flag = (LightFlag)options->flag();
        float intensity = options->intensity();
        float range = options->range();
        float outerAngle = options->outerAngle()*0.5f;
        bool enabled = options->enabled();
        switch (type)
        {
        case cocos2d::LightType::DIRECTIONAL:
            light = DirectionLight::create(Vec3::UNIT_Z , Color3B::WHITE);
            break;
        case cocos2d::LightType::POINT:
            light = PointLight::create(Vec3::ZERO, Color3B::WHITE, range);
            break;
        case cocos2d::LightType::SPOT:
            light = SpotLight::create(Vec3::UNIT_Z, Vec3::ZERO, Color3B::WHITE, 0, CC_DEGREES_TO_RADIANS(outerAngle), range);
            break;
        case cocos2d::LightType::AMBIENT:
            light = AmbientLight::create(Color3B::WHITE);
            break;
        default:
            break;
        }
        if (light != nullptr)
        {
            light->setIntensity(intensity);
            light->setEnabled(enabled);
            light->setLightFlag(flag);
        }
        lightNode->addChild(light);

        setPropsWithFlatBuffers(lightNode, light3DOptions);

        return lightNode;
    }
}
