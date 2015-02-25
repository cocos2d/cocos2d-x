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

#include "Node3DReader.h"

#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/CSParse3DBinary_generated.h"

#include "cocostudio/FlatBuffersSerialize.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace flatbuffers;

namespace cocostudio
{
    IMPLEMENT_CLASS_NODE_READER_INFO(Node3DReader)
    
    Node3DReader::Node3DReader()
    {
        
    }
    
    Node3DReader::~Node3DReader()
    {
        
    }
    
    static Node3DReader* _instanceNode3DReader = nullptr;
    
    Node3DReader* Node3DReader::getInstance()
    {
        if (!_instanceNode3DReader)
        {
            _instanceNode3DReader = new Node3DReader();
        }
        
        return _instanceNode3DReader;
    }
    
    void Node3DReader::purge()
    {
        CC_SAFE_DELETE(_instanceNode3DReader);
    }
    
    Vec3 Node3DReader::getVec3Attribute(const tinyxml2::XMLAttribute* attribute) const
    {
        if(!attribute)
            return Vec3::ZERO;
        
        Vec3 ret(Vec3::ZERO);
        std::string attriname;
        
        while (attribute)
        {
            attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if (attriname == "ValueX")
            {
                ret.x = atof(value.c_str());
            }
            else if (attriname == "ValueY")
            {
                ret.y = atof(value.c_str());
            }
            else if(attriname == "ValueZ")
            {
                ret.z = atof(value.c_str());
            }
            
            attribute = attribute->Next();
        }

        return ret;
    }
    
    Offset<Table> Node3DReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                             flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);
        
        Vec3 position(Vec3::ZERO);
        Vec3 rotation(Vec3::ZERO);
        Vec3 scale(Vec3::ZERO);
        int cameraMask = 0;

        std::string attriname;
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while(attribute)
        {
            attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if(attriname == "CameraFlagMode")
            {
                cameraMask = atoi(value.c_str());
            }
            
            attribute = attribute->Next();
        }
        
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();

        while (child)
        {
            std::string name = child->Name();
            
            if (name == "Position3D")
            {
                position = getVec3Attribute(child->FirstAttribute());
            }
            else if(name == "Rotation3D")
            {
                rotation = getVec3Attribute(child->FirstAttribute());
            }
            else if(name == "Scale3D")
            {
                scale = getVec3Attribute(child->FirstAttribute());
            }
            
            child = child->NextSiblingElement();
        }
        
        Vector3 postion3D(position.x, position.y, position.z);
        Vector3 rotation3D(rotation.x, rotation.y, rotation.z);
        Vector3 scale3D(scale.x, scale.y, scale.z);

        auto options = CreateNode3DOption(*builder,
                                           nodeOptions,
                                           &postion3D,
                                           &rotation3D,
                                           &scale3D,
                                           cameraMask
                                           );
        
        return *(Offset<Table>*)(&options);
    }
    
    void Node3DReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                                   const flatbuffers::Table* node3DOptions)
    {
        auto options = (Node3DOption*)node3DOptions;
        
        const Vector3* position = options->position3D();
        const Vector3* rotation = options->rotation3D();
        const Vector3* scale = options->scale3D();
        int cameraMask = options->cameramask();
        
        if(position)
        {
            node->setPosition3D(Vec3(position->x(), position->y(), position->z()));
        }
        
        if(rotation)
        {
            node->setRotation3D(Vec3(rotation->x(), rotation->y(), rotation->z()));
        }
        
        if(scale)
        {
            node->setScaleX(scale->x());
            node->setScaleY(scale->y());
            node->setScaleZ(scale->z());
        }
        
        node->setCameraMask(cameraMask, true);
        
        auto nodeReader = NodeReader::getInstance();
        nodeReader->setPropsWithFlatBuffers(node, (Table*)(options->nodeOptions()));
    }
    
    Node* Node3DReader::createNodeWithFlatBuffers(const flatbuffers::Table *node3DOptions)
    {
        Node* node = Node::create();
        
        setPropsWithFlatBuffers(node, (Table*)node3DOptions);
        
        return node;
    }
}
