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

#include "2d/CCTMXXMLParser.h"

#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

#include "tinyxml2.h"
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
    
    void GameMapReader::destroyInstance()
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
        
        bool fileExist = false;
        std::string errorFilePath = "";
        std::string path = fileNameData->path()->c_str();
        int resourceType = fileNameData->resourceType();
        switch (resourceType)
        {
            case 0:
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
                break;
            }
                
            default:
                break;
        }
        if (fileExist)
        {
            /* Whether tileset is valid. */
            auto mapInfo = TMXMapInfo::create(path);
            auto& layers = mapInfo->getLayers();
            bool valid = false;
            std::string layerName = "";
            for (const auto &layerInfo : layers)
            {
                valid = false;
                
                if (layerInfo->_visible)
                {
                    Size size = layerInfo->_layerSize;
                    auto& tilesets = mapInfo->getTilesets();
                    if (tilesets.size()>0)
                    {
                        TMXTilesetInfo* tileset = nullptr;
                        for (auto iter = tilesets.crbegin(); iter != tilesets.crend(); ++iter)
                        {
                            tileset = *iter;
                            if (tileset)
                            {
                                for( int y=0; y < size.height; y++ )
                                {
                                    for( int x=0; x < size.width; x++ )
                                    {
                                        int pos = static_cast<int>(x + size.width * y);
                                        int gid = layerInfo->_tiles[ pos ];
                                        
                                        if( gid != 0 )
                                        {
                                            if( (gid & kTMXFlippedMask) >= tileset->_firstGid )
                                            {
                                                valid = true;
                                                break;
                                            }
                                        }
                                    }
                                    
                                    if (valid)
                                    {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    
                    if (!valid)
                    {
                        layerName = layerInfo->_name;
                        break;
                    }
                }
                else
                {
                    valid = true;
                }
            }
            
            if (!valid)
            {
                Node* node = Node::create();
                setPropsWithFlatBuffers(node, (Table*)gameMapOptions);
                auto label = Label::create();
                label->setString(__String::createWithFormat("Some error of gid are in TMX Layer '%s'", layerName.c_str())->getCString());
                node->setScale(1.0f);
                node->addChild(label);
                return node;
            }
            /**/
            
            tmx = TMXTiledMap::create(path);
            if (tmx)
            {
                //prevent that editor's data does not match in size and resources
                Size fileSize = tmx->getContentSize();
                setPropsWithFlatBuffers(tmx, (Table*)gameMapOptions);
                tmx->setContentSize(fileSize);
            }
        }
        else
        {
            Node* node = Node::create();
            setPropsWithFlatBuffers(node, (Table*)gameMapOptions);
            return node;
        }
        
        return tmx;
    }
    
}
