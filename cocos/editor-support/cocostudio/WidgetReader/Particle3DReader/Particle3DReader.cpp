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

#include "Particle3DReader.h"

#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/CSParse3DBinary_generated.h"
#include "cocostudio/FlatBuffersSerialize.h"
#include "cocostudio/WidgetReader/Node3DReader/Node3DReader.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

#include "Particle3D/PU/CCPUParticleSystem3D.h"

USING_NS_CC;
using namespace flatbuffers;

namespace cocostudio
{
    IMPLEMENT_CLASS_NODE_READER_INFO(Particle3DReader)
    
    Particle3DReader::Particle3DReader()
    {
        
    }
    
    Particle3DReader::~Particle3DReader()
    {
        
    }
    
    static Particle3DReader* _instanceParticle3DReader = nullptr;
    
    Particle3DReader* Particle3DReader::getInstance()
    {
        if (!_instanceParticle3DReader)
        {
            _instanceParticle3DReader = new Particle3DReader();
        }
        
        return _instanceParticle3DReader;
    }
    
    void Particle3DReader::purge()
    {
        CC_SAFE_DELETE(_instanceParticle3DReader);
    }
    
    void Particle3DReader::destroyInstance()
    {
        CC_SAFE_DELETE(_instanceParticle3DReader);
    }
    
    Offset<Table> Particle3DReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                             flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = Node3DReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto node3DOptions = *(Offset<Node3DOption>*)(&temp);
        
        std::string path;
        int resourceType = 0;

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
        
        auto options = CreateParticle3DOptions(*builder,
                                             node3DOptions,
                                             CreateResourceData(*builder,
                                                                builder->CreateString(path),
                                                                builder->CreateString(""),
                                                                resourceType)
                                             );
        
        return *(Offset<Table>*)(&options);
    }
    
    void Particle3DReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                                   const flatbuffers::Table* particle3DOptions)
    {
        auto options = (Particle3DOptions*)particle3DOptions;
        
        auto node3DReader = Node3DReader::getInstance();
        node3DReader->setPropsWithFlatBuffers(node, (Table*)(options->node3DOption()));
    }
    
    Node* Particle3DReader::createNodeWithFlatBuffers(const flatbuffers::Table *particle3DOptions)
    {
        auto options = (Particle3DOptions*)particle3DOptions;
        
        auto fileData = options->fileData();
        std::string path = fileData->path()->c_str();
        
        PUParticleSystem3D* ret = PUParticleSystem3D::create();
        if (FileUtils::getInstance()->isFileExist(path))
        {
            ret->initWithFilePath(path);
        }
        
        setPropsWithFlatBuffers(ret, particle3DOptions);
        
        if(ret)
        {
            ret->startParticleSystem();
        }
        
        return ret;
    }
}
