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

#include "ComAudioReader.h"

#include "cocostudio/CCComAudio.h"
#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace flatbuffers;

namespace cocostudio
{
    ComAudioReader::ComAudioReader()
    {
        
    }
    
    ComAudioReader::~ComAudioReader()
    {
        
    }
    
    static ComAudioReader* _instanceComAudioReader = nullptr;
    
    ComAudioReader* ComAudioReader::getInstance()
    {
        if (!_instanceComAudioReader)
        {
            _instanceComAudioReader = new ComAudioReader();
        }
        
        return _instanceComAudioReader;
    }
    
    void ComAudioReader::purge()
    {
        CC_SAFE_DELETE(_instanceComAudioReader);
    }
    
    Offset<Table> ComAudioReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                               flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string name = "";
        bool enabled = false;
        bool loop = false;
        float volume = 0;
        
        std::string path = "";
        std::string plist = "";
        int resourceType = 0;
        
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if (attriname == "Loop")
            {
                loop = (value == "True") ? true : false;
            }
            else if (attriname == "Volume")
            {
                volume = atof(value.c_str());
            }
            else if (attriname == "Name")
            {
                name = value;
            }
            
            attribute = attribute->Next();
        }
        
        // FileData
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string attriname = child->Name();
            
            if (attriname == "FileData")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "Path")
                    {
                        path = value;
                    }
                    else if (attriname == "Type")
                    {
                        resourceType = 0;
                    }
                    else if (attriname == "Plist")
                    {
                        plist = value;
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateComAudioOptions(*builder,
                                             nodeOptions,
                                             builder->CreateString(name),
                                             enabled,
                                             loop,
                                             volume,
                                             CreateResourceData(*builder,
                                                                builder->CreateString(path),
                                                                builder->CreateString(plist),
                                                                resourceType));
        
        return *(Offset<Table>*)(&options);
    }
    
    void ComAudioReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                                 const flatbuffers::Table *comAudioOptions)
    {
        auto options = (ComAudioOptions*)comAudioOptions;
        
        auto nodeReader = NodeReader::getInstance();
        nodeReader->setPropsWithFlatBuffers(node, (Table*)(options->nodeOptions()));
    }
    
    Component* ComAudioReader::createComAudioWithFlatBuffers(const flatbuffers::Table *comAudioOptions)
    {
        auto options = (ComAudioOptions*)comAudioOptions;
        
        Component* component = ComAudio::create();
        ComAudio* audio = static_cast<ComAudio*>(component);
        
        auto fileNameData = options->fileNameData();
        
        int resourceType = fileNameData->resourceType();
        switch (resourceType)
        {
            case 0:
            {
                std::string path = fileNameData->path()->c_str();
                audio->setFile(path.c_str());
                break;
            }
                
            default:
                break;
        }
        
        bool loop = options->loop();
        audio->setLoop(loop);
        
        audio->setName(options->name()->c_str());
        audio->setLoop(options->loop());
        
        return component;
    }
    
}
