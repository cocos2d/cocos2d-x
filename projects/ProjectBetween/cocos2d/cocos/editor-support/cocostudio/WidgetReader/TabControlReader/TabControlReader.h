/****************************************************************************
 Copyright (c) 2016 cocos2d-x.org
 
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

#ifndef __TABCONTROLREADER_H_
#define __TABCONTROLREADER_H_

#include "editor-support/cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "editor-support/cocostudio/WidgetReader/NodeReaderDefine.h"
#include "editor-support/cocostudio/WidgetReader/TabControlReader/CSTabControl_generated.h"


class TabControlReader : public cocos2d::Ref, public cocostudio::NodeReaderProtocol
{
    DECLARE_CLASS_NODE_READER_INFO
    
public:
    TabControlReader();
    ~TabControlReader();
    
    static TabControlReader* getInstance();
    static void destroyInstance();
    
    flatbuffers::Offset<flatbuffers::Table> createOptionsWithFlatBuffers(const tinyxml2::XMLElement* objectData,
                                                                         flatbuffers::FlatBufferBuilder* builder) override;
    
    void setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* nodeOption) override;
    
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions) override;
private:
    static TabControlReader* _tabReaderInstance;
};

class TabHeaderReader : public cocos2d::Ref, public cocostudio::NodeReaderProtocol
{
    DECLARE_CLASS_NODE_READER_INFO
    
public:
    TabHeaderReader();
    ~TabHeaderReader();
    
    static TabHeaderReader* getInstance();
    static void destroyInstance();
    
    flatbuffers::Offset<flatbuffers::Table> createOptionsWithFlatBuffers(const tinyxml2::XMLElement* objectData,
                                                                         flatbuffers::FlatBufferBuilder* builder) override;
    
    void setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* nodeOption) override;
    
    //CSArmatureNode
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions) override;
private:
    static TabHeaderReader* _tabheaderReaderInstance;
    int    getResourceType(std::string key);
};

class TabItemReader : public cocos2d::Ref, public cocostudio::NodeReaderProtocol
{
    DECLARE_CLASS_NODE_READER_INFO
    
public:
    TabItemReader();
    ~TabItemReader();
    
    static TabItemReader* getInstance();
    static void destroyInstance();
    
    flatbuffers::Offset<flatbuffers::TabItemOption> createTabItemOptionWithFlatBuffers(
                                                                                       const tinyxml2::XMLElement* objectData,
                                                                                       flatbuffers::FlatBufferBuilder* builder);
    
    void setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* nodeOption) override;
    
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions) override;
    
    virtual flatbuffers::Offset<flatbuffers::Table> createOptionsWithFlatBuffers(
                                                                                 const tinyxml2::XMLElement* objectData, flatbuffers::FlatBufferBuilder* builder) override;
    
private:
    static TabItemReader* _tabItemReaderInstance;
};

#endif //__TABCONTROLREADER_H_