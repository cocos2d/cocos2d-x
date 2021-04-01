/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "editor-support/cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.h"

#include "editor-support/cocostudio/CSParseBinary_generated.h"
#include "editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace flatbuffers;

namespace cocostudio
{
    ProjectNodeReader::ProjectNodeReader()
    {
        
    }
    
    ProjectNodeReader::~ProjectNodeReader()
    {
        
    }
    
    static ProjectNodeReader* _instanceProjectNodeReader = nullptr;
    
    ProjectNodeReader* ProjectNodeReader::getInstance()
    {
        if (!_instanceProjectNodeReader)
        {
            _instanceProjectNodeReader = new (std::nothrow) ProjectNodeReader();
        }
        
        return _instanceProjectNodeReader;
    }
    
    void ProjectNodeReader::purge()
    {
        CC_SAFE_DELETE(_instanceProjectNodeReader);
    }
    
    void ProjectNodeReader::destroyInstance()
    {
        CC_SAFE_DELETE(_instanceProjectNodeReader);
    }
    
    Offset<Table> ProjectNodeReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                                  flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);
        
        std::string filename = "";
        float innerspeed = 1.0f;

        const tinyxml2::XMLAttribute* objattri = objectData->FirstAttribute();
        // inneraction speed
        while (objattri)
        {
            std::string name = objattri->Name();
            std::string value = objattri->Value();
            if (name == "InnerActionSpeed")
            {
                    innerspeed = atof(objattri->Value());
                    break;
            }
            objattri = objattri->Next();
        }

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
                        size_t pos = value.find_last_of('.');
                        std::string convert = value.substr(0, pos).append(".csb");
                        filename = convert;
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateProjectNodeOptions(*builder,
                                                nodeOptions,
                                                builder->CreateString(filename),
                                                innerspeed);
        
        return *(Offset<Table>*)(&options);
    }
    
    void ProjectNodeReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                                    const flatbuffers::Table* projectNodeOptions)
    {
        auto options = (ProjectNodeOptions*)projectNodeOptions;
        
        auto nodeReader = NodeReader::getInstance();
        
        nodeReader->setPropsWithFlatBuffers(node, (Table*)options->nodeOptions());
    }
    
    Node* ProjectNodeReader::createNodeWithFlatBuffers(const flatbuffers::Table* /*nodeOptions*/)
    {
        return nullptr;
    }
}
