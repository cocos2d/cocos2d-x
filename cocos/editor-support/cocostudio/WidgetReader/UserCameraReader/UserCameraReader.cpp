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

#include "UserCameraReader.h"

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
    IMPLEMENT_CLASS_NODE_READER_INFO(UserCameraReader)
    
    UserCameraReader::UserCameraReader()
    {
        
    }
    
    UserCameraReader::~UserCameraReader()
    {
        
    }
    
    static UserCameraReader* _instanceUserCameraReader = nullptr;
    
    UserCameraReader* UserCameraReader::getInstance()
    {
        if (!_instanceUserCameraReader)
        {
            _instanceUserCameraReader = new UserCameraReader();
        }
        
        return _instanceUserCameraReader;
    }
    
    void UserCameraReader::purge()
    {
        CC_SAFE_DELETE(_instanceUserCameraReader);
    }
    
    Vec2 UserCameraReader::getVec2Attribute(const tinyxml2::XMLAttribute* attribute) const
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
    
    Offset<Table> UserCameraReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                             flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = Node3DReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto node3DOptions = *(Offset<Node3DOption>*)(&temp);
        
        float fov = 60.f;
        unsigned int cameraFlag = 0;
        
        std::string attriname;
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while(attribute)
        {
            attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if(attriname == "Fov")
            {
                fov = atof(value.c_str());
            }
            else if(attriname == "UserCameraFlagMode")
            {
                if(value == "DEFAULT")  cameraFlag = 1;
                else if(value == "USER1") cameraFlag = 1 << 1;
                else if(value == "USER2") cameraFlag = 1 << 2;
                else if(value == "USER3") cameraFlag = 1 << 3;
            }
            
            attribute = attribute->Next();
        }

        Vec2 clipPlane(1, 1000);
        
        // FileData
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "ClipPlane")
            {
                attribute = child->FirstAttribute();
                clipPlane = getVec2Attribute(attribute);
                break;
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateUserCameraOptions(*builder,
                                             node3DOptions,
                                             fov,
                                             clipPlane.x,
                                             clipPlane.y,
                                             cameraFlag
                                             );
        
        return *(Offset<Table>*)(&options);
    }
    
    void UserCameraReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                                   const flatbuffers::Table* userCameraDOptions)
    {
        auto options = (UserCameraOptions*)userCameraDOptions;
        
        Camera* camera = static_cast<Camera*>(node);
        int cameraFlag = options->cameraFlag();
        camera->setCameraFlag((CameraFlag)cameraFlag);

        auto node3DReader = Node3DReader::getInstance();
        node3DReader->setPropsWithFlatBuffers(node, (Table*)(options->node3DOption()));
    }
    
    Node* UserCameraReader::createNodeWithFlatBuffers(const flatbuffers::Table *userCameraDOptions)
    {
        auto options = (UserCameraOptions*)userCameraDOptions;
        
        float fov = options->fov();
        float nearClip = options->nearClip();
        float farClip = options->farClip();
        
        auto size = Director::getInstance()->getWinSize();
        Camera* camera = Camera::createPerspective(fov, size.width / size.height, nearClip, farClip);
        
        setPropsWithFlatBuffers(camera, userCameraDOptions);
        
        return camera;
    }
}
