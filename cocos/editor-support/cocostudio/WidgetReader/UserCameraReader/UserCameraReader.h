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

#ifndef __cocos2d_libs__UserCameraReader__
#define __cocos2d_libs__UserCameraReader__

#include "math/Vec2.h"
#include "editor-support/cocostudio/CocosStudioExport.h"
#include "editor-support/cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "editor-support/cocostudio/WidgetReader/NodeReaderDefine.h"

namespace tinyxml2
{
    class XMLAttribute;
}

namespace cocostudio
{
    class CC_STUDIO_DLL UserCameraReader : public cocos2d::Ref, public NodeReaderProtocol
    {
        DECLARE_CLASS_NODE_READER_INFO
        
    public:
        UserCameraReader();
        ~UserCameraReader();
        
        static UserCameraReader* getInstance();
        /** @deprecated Use method destroyInstance() instead */
        CC_DEPRECATED_ATTRIBUTE static void purge();
        static void destroyInstance();
        
        flatbuffers::Offset<flatbuffers::Table> createOptionsWithFlatBuffers(const tinyxml2::XMLElement* objectData,
                                                                             flatbuffers::FlatBufferBuilder* builder);
        void setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* userCameraOptions);
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* userCameraOptions);
        
    protected:
        int getResourceType(const std::string& key);
        cocos2d::Vec2 getVec2Attribute(const tinyxml2::XMLAttribute* attribute) const;
    };
}

#endif /* defined(__cocos2d_libs__UserCameraReader__) */
