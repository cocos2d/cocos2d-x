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

#include "base/CCDirector.h"
#include "2d/CCCamera.h"
#include "platform/CCFileUtils.h"
#include "editor-support/cocostudio/WidgetReader/UserCameraReader/UserCameraReader.h"

#include "editor-support/cocostudio/CSParseBinary_generated.h"
#include "editor-support/cocostudio/CSParse3DBinary_generated.h"
#include "editor-support/cocostudio/FlatBuffersSerialize.h"
#include "editor-support/cocostudio/WidgetReader/Node3DReader/Node3DReader.h"
#include "editor-support/cocostudio/WidgetReader/GameNode3DReader/GameNode3DReader.h"

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
            _instanceUserCameraReader = new (std::nothrow) UserCameraReader();
        }
        
        return _instanceUserCameraReader;
    }
    
    void UserCameraReader::purge()
    {
        CC_SAFE_DELETE(_instanceUserCameraReader);
    }
    
    void UserCameraReader::destroyInstance()
    {
        CC_SAFE_DELETE(_instanceUserCameraReader);
    }
    
    Vec2 UserCameraReader::getVec2Attribute(const tinyxml2::XMLAttribute* attribute) const
    {
        if(!attribute)
            return Vec2::ZERO;
        
        Vec2 ret;
        std::string attriname;
        
        while (attribute)
        {
            attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if (attriname == "X")
            {
                ret.x = atof(value.c_str());
            }
            else if (attriname == "Y")
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
        bool skyBoxEnabled = false;
        bool skyBoxValid = true;

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
                if (cameraFlag == 0)
                {
                    if (value == "DEFAULT")  cameraFlag = 1;
                    else if (value == "USER1") cameraFlag = 1 << 1;
                    else if (value == "USER2") cameraFlag = 1 << 2;
                    else if (value == "USER3") cameraFlag = 1 << 3;
                    else if (value == "USER4") cameraFlag = 1 << 4;
                }
            }
            else if (attriname == "CameraFlagData")
            {
                int flag = atoi(value.c_str());
                if (flag != 0)
                    cameraFlag = flag;
            }
            else if (attriname == "SkyBoxEnabled")
            {
                skyBoxEnabled = (value == "True") ? true : false;
            }
            else if (attriname == "SkyBoxValid")
            {
                skyBoxValid = (value == "True") ? true : false;
            }
            
            attribute = attribute->Next();
        }

        if (!skyBoxValid)
            skyBoxEnabled = false;

        Vec2 clipPlane(1, 1000);

        std::string leftPath = "";
        std::string leftPlistFile = "";
        int leftResourceType = 0;

        std::string rightPath = "";
        std::string rightPlistFile = "";
        int rightResourceType = 0;

        std::string upPath = "";
        std::string upPlistFile = "";
        int upResourceType = 0;

        std::string downPath = "";
        std::string downPlistFile = "";
        int downResourceType = 0;

        std::string forwardPath = "";
        std::string forwardPlistFile = "";
        int forwardResourceType = 0;

        std::string backPath = "";
        std::string backPlistFile = "";
        int backResourceType = 0;
        
        // FileData
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();
            
            if (name == "ClipPlane")
            {
                attribute = child->FirstAttribute();
                clipPlane = getVec2Attribute(attribute);
            }
            else if (name == "LeftImage")
            {
                attribute = child->FirstAttribute();

                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();

                    if (name == "Path")
                    {
                        leftPath = value;
                    }
                    else if (name == "Type")
                    {
                        leftResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        leftPlistFile = value;
                    }

                    attribute = attribute->Next();
                }

                if (leftResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(leftPlistFile));
                }
            }
            else if (name == "RightImage")
            {
                attribute = child->FirstAttribute();

                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();

                    if (name == "Path")
                    {
                        rightPath = value;
                    }
                    else if (name == "Type")
                    {
                        rightResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        rightPlistFile = value;
                    }

                    attribute = attribute->Next();
                }

                if (rightResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(rightPlistFile));
                }
            }
            else if (name == "UpImage")
            {
                attribute = child->FirstAttribute();

                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();

                    if (name == "Path")
                    {
                        upPath = value;
                    }
                    else if (name == "Type")
                    {
                        upResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        upPlistFile = value;
                    }

                    attribute = attribute->Next();
                }

                if (upResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(upPlistFile));
                }
            }
            else if (name == "DownImage")
            {
                attribute = child->FirstAttribute();

                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();

                    if (name == "Path")
                    {
                        downPath = value;
                    }
                    else if (name == "Type")
                    {
                        downResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        downPlistFile = value;
                    }

                    attribute = attribute->Next();
                }

                if (downResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(downPlistFile));
                }
            }
            else if (name == "ForwardImage")
            {
                attribute = child->FirstAttribute();

                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();

                    if (name == "Path")
                    {
                        forwardPath = value;
                    }
                    else if (name == "Type")
                    {
                        forwardResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        forwardPlistFile = value;
                    }

                    attribute = attribute->Next();
                }

                if (forwardResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(forwardPlistFile));
                }
            }
            else if (name == "BackImage")
            {
                attribute = child->FirstAttribute();

                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();

                    if (name == "Path")
                    {
                        backPath = value;
                    }
                    else if (name == "Type")
                    {
                        backResourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        backPlistFile = value;
                    }

                    attribute = attribute->Next();
                }

                if (backResourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(backPlistFile));
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        auto options = CreateUserCameraOptions(*builder,
                                             node3DOptions,
                                             fov,
                                             clipPlane.x,
                                             clipPlane.y,
                                             cameraFlag,
                                             skyBoxEnabled,
                                             CreateResourceData(*builder,
                                                         builder->CreateString(leftPath),
                                                         builder->CreateString(leftPlistFile),
                                                         leftResourceType),
                                             CreateResourceData(*builder,
                                                         builder->CreateString(rightPath),
                                                         builder->CreateString(rightPlistFile),
                                                         rightResourceType),
                                             CreateResourceData(*builder,
                                                         builder->CreateString(upPath),
                                                         builder->CreateString(upPlistFile),
                                                         upResourceType),
                                             CreateResourceData(*builder,
                                                         builder->CreateString(downPath),
                                                         builder->CreateString(downPlistFile),
                                                         downResourceType),
                                             CreateResourceData(*builder,
                                                         builder->CreateString(forwardPath),
                                                         builder->CreateString(forwardPlistFile),
                                                         forwardResourceType),
                                             CreateResourceData(*builder,
                                                         builder->CreateString(backPath),
                                                         builder->CreateString(backPlistFile),
                                                         backResourceType)
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

        bool skyBoxEnabled = options->skyBoxEnabled() != 0;
        if (skyBoxEnabled)
        {
            std::string leftFileData = options->leftFileData()->path()->c_str();
            std::string rightFileData = options->rightFileData()->path()->c_str();
            std::string upFileData = options->upFileData()->path()->c_str();
            std::string downFileData = options->downFileData()->path()->c_str();
            std::string forwardFileData = options->forwardFileData()->path()->c_str();
            std::string backFileData = options->backFileData()->path()->c_str();
            FileUtils *fileUtils = FileUtils::getInstance();

            if (fileUtils->isFileExist(leftFileData)
                && fileUtils->isFileExist(rightFileData)
                && fileUtils->isFileExist(upFileData)
                && fileUtils->isFileExist(downFileData)
                && fileUtils->isFileExist(forwardFileData)
                && fileUtils->isFileExist(backFileData))
            {
                CameraBackgroundSkyBoxBrush* brush = CameraBackgroundSkyBoxBrush::create(leftFileData, rightFileData, upFileData, downFileData, forwardFileData, backFileData);
                camera->setBackgroundBrush(brush);
            }
            else
            {
                if (GameNode3DReader::getSceneBrushInstance() != nullptr)
                    camera->setBackgroundBrush(GameNode3DReader::getSceneBrushInstance());
            }
        }
        else
        {
            if (GameNode3DReader::getSceneBrushInstance() != nullptr)
                camera->setBackgroundBrush(GameNode3DReader::getSceneBrushInstance());
        }
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

    int UserCameraReader::getResourceType(std::string key)
    {
        if (key == "Normal" || key == "Default")
        {
            return 	0;
        }

        FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
        if (fbs->_isSimulator)
        {
            if (key == "MarkedSubImage")
            {
                return 0;
            }
        }
        return 1;
    }
}
