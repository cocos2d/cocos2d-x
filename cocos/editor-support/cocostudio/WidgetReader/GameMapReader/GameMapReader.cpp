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

#include "GameMapReader.h"

#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

#include "tinyxml2/tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace flatbuffers;

namespace cocostudio
{
    IMPLEMENT_CLASS_NODE_READER_INFO(GameMapReader)
    
    GameMapReader::GameMapReader()
    {
        
    }
    
    GameMapReader::~GameMapReader()
    {
        
    }
    
    static GameMapReader* _instanceTMXTiledMapReader = nullptr;
    
    GameMapReader* GameMapReader::getInstance()
    {
        if (!_instanceTMXTiledMapReader)
        {
            _instanceTMXTiledMapReader = new GameMapReader();
        }
        
        return _instanceTMXTiledMapReader;
    }
    
    void GameMapReader::purge()
    {
        CC_SAFE_DELETE(_instanceTMXTiledMapReader);
    }
    
    Offset<Table> GameMapReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                              flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string path = "";
        std::string plistFile = "";
        int resourceType = 0;
        
        // child elements
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
                        resourceType = 0;
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateGameMapOptions(*builder,
                                            nodeOptions,
                                            CreateResourceData(*builder,
                                                               builder->CreateString(path),
                                                               builder->CreateString(plistFile),
                                                               resourceType));
        
        return *(Offset<Table>*)(&options);
    }
    
    void GameMapReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                                const flatbuffers::Table *gameMapOptions)
    {
        auto options = (GameMapOptions*)gameMapOptions;
        auto nodeReader = NodeReader::getInstance();
        nodeReader->setPropsWithFlatBuffers(node, (Table*)options->nodeOptions());
    }
    
    Node* GameMapReader::createNodeWithFlatBuffers(const flatbuffers::Table *gameMapOptions)
    {
        TMXTiledMap* tmx = nullptr;
        
        auto options = (GameMapOptions*)gameMapOptions;
        auto fileNameData = options->fileNameData();
        
        int resourceType = fileNameData->resourceType();
        switch (resourceType)
        {
            case 0:
            {
                std::string path = fileNameData->path()->c_str();
                const char* tmxFile = path.c_str();
                
                if (tmxFile && strcmp("", tmxFile) != 0)
                {
                    tmx = TMXTiledMap::create(tmxFile);
                }
                break;
            }
                
            default:
                break;
        }
        
        if (tmx)
        {
            setPropsWithFlatBuffers(tmx, (Table*)gameMapOptions);
        }
        
        return tmx;
    }
    
}
