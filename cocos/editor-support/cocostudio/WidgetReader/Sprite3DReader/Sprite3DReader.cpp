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

#include "Sprite3DReader.h"

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
    IMPLEMENT_CLASS_NODE_READER_INFO(Sprite3DReader)
    
    Sprite3DReader::Sprite3DReader()
    {
        
    }
    
    Sprite3DReader::~Sprite3DReader()
    {
        
    }
    
    static Sprite3DReader* _instanceSprite3DReader = nullptr;
    
    Sprite3DReader* Sprite3DReader::getInstance()
    {
        if (!_instanceSprite3DReader)
        {
            _instanceSprite3DReader = new Sprite3DReader();
        }
        
        return _instanceSprite3DReader;
    }
    
    void Sprite3DReader::purge()
    {
        CC_SAFE_DELETE(_instanceSprite3DReader);
    }
    
    Vec2 Sprite3DReader::getVec2Attribute(const tinyxml2::XMLAttribute* attribute) const
    {
        if(!attribute)
            return Vec2::ZERO;
        
        Vec2 ret(Vec2::ZERO);
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
            
            attribute = attribute->Next();
        }

        return ret;
    }
    
    Offset<Table> Sprite3DReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                             flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = Node3DReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto node3DOptions = *(Offset<Node3DOption>*)(&temp);
        
        bool runAction = false;
        std::string path;
        int resourceType = 0;
        
        std::string attriname;
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while(attribute)
        {
            attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if(attriname == "RunAction3D")
            {
                runAction = value == "True" ? true : false;
                break;
            }
            
            attribute = attribute->Next();
        }

        // FileData
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "FileData")
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
                        if(value == "Normal")
                        {
                            resourceType = 1;
                        }
                        else if(value == "Default")
                        {
                            resourceType = 0;
                        }
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateSprite3DOptions(*builder,
                                             node3DOptions,
                                             CreateResourceData(*builder,
                                                                builder->CreateString(path),
                                                                builder->CreateString(""),
                                                                resourceType),
                                             runAction
                                             );
        
        return *(Offset<Table>*)(&options);
    }
    
    void Sprite3DReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                                   const flatbuffers::Table* sprite3DOptions)
    {
        Sprite3D* sprite3D = static_cast<Sprite3D*>(node);
        
        auto options = (Sprite3DOptions*)sprite3DOptions;
        
        bool runAction = options->runAction() != 0;
        auto fileData = options->fileData();
        std::string path = fileData->path()->c_str();

        if(runAction && FileUtils::getInstance()->isFileExist(path))
        {
            Animation3D* animation = Animation3D::create(path);
            if(animation)
            {
                Animate3D* animate = Animate3D::create(animation);
                Action* action = RepeatForever::create(animate);
                sprite3D->runAction(action);
            }
        }
        
        auto nodeOptions = options->node3DOption()->nodeOptions();
        
        GLubyte alpha       = (GLubyte)nodeOptions->color()->a();
        GLubyte red         = (GLubyte)nodeOptions->color()->r();
        GLubyte green       = (GLubyte)nodeOptions->color()->g();
        GLubyte blue        = (GLubyte)nodeOptions->color()->b();
        
        if (alpha != 255)
        {
            sprite3D->setOpacity(alpha);
        }
        if (red != 255 || green != 255 || blue != 255)
        {
            sprite3D->setColor(Color3B(red, green, blue));
        }
        
        auto node3DReader = Node3DReader::getInstance();
        node3DReader->setPropsWithFlatBuffers(sprite3D, (Table*)(options->node3DOption()));
    }
    
    Node* Sprite3DReader::createNodeWithFlatBuffers(const flatbuffers::Table *sprite3DOptions)
    {
        auto options = (Sprite3DOptions*)sprite3DOptions;
        
        auto fileData = options->fileData();
        std::string path = fileData->path()->c_str();
        
        Sprite3D* ret = NULL;
        if(!FileUtils::getInstance()->isFileExist(path))
        {
            ret = Sprite3D::create();
        }
        else
        {
            ret = Sprite3D::create(path);
        }
        
        setPropsWithFlatBuffers(ret, sprite3DOptions);
        
        return ret;
    }
}
