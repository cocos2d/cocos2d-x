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

#include "NodeReader.h"

#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"

#include "tinyxml2/tinyxml2.h"
#include "flatbuffers/flatbuffers.h"


USING_NS_CC;
using namespace flatbuffers;

namespace cocostudio
{
    IMPLEMENT_CLASS_NODE_READER_INFO(NodeReader)
    
    NodeReader::NodeReader()
    {
        
    }
    
    NodeReader::~NodeReader()
    {
        
    }
    
    static NodeReader* _instanceNodeReader = nullptr;
    
    NodeReader* NodeReader::getInstance()
    {
        if (!_instanceNodeReader)
        {
            _instanceNodeReader = new NodeReader();
        }
        
        return _instanceNodeReader;
    }
    
    void NodeReader::purge()
    {
        CC_SAFE_DELETE(_instanceNodeReader);
    }
    
    Offset<Table> NodeReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
                                                           flatbuffers::FlatBufferBuilder *builder)
    {
        std::string name = "";
        long actionTag = 0;
        Vec2 rotationSkew = Vec2::ZERO;
        int zOrder = 0;
        bool visible = true;
        GLubyte alpha = 255;
        int tag = 0;
        Vec2 position = Vec2::ZERO;
        Vec2 scale = Vec2(1.0f, 1.0f);
        Vec2 anchorPoint = Vec2::ZERO;
        Color4B color(255, 255, 255, 255);

        Vec2 size = Vec2::ZERO;
        bool flipX = false;
        bool flipY = false;
        bool ignoreSize = false;
        bool touchEnabled = false;
        std::string frameEvent = "";
        std::string customProperty = "";
        
        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string attriname = attribute->Name();
            std::string value = attribute->Value();
            
            if (attriname == "Name")
            {
                name = value;
            }
            else if (attriname == "ActionTag")
            {
                actionTag = atol(value.c_str());
            }
            else if (attriname == "RotationSkewX")
            {
                rotationSkew.x = atof(value.c_str());
            }
            else if (attriname == "RotationSkewY")
            {
                rotationSkew.y = atof(value.c_str());
            }
            else if (attriname == "Rotation")
            {
                //            rotation = atoi(value.c_str());
            }
            else if (attriname == "FlipX")
            {
                flipX = (value == "True") ? true : false;
            }
            else if (attriname == "FlipY")
            {
                flipY = (value == "True") ? true : false;
            }
            else if (attriname == "ZOrder")
            {
                zOrder = atoi(value.c_str());
            }
            else if (attriname == "Visible")
            {
                //            visible = (value == "True") ? true : false;
            }
            else if (attriname == "VisibleForFrame")
            {
                visible = (value == "True") ? true : false;
            }
            else if (attriname == "Alpha")
            {
                alpha = atoi(value.c_str());
            }
            else if (attriname == "Tag")
            {
                tag = atoi(value.c_str());
            }
            else if (attriname == "TouchEnable")
            {
                touchEnabled = (value == "True") ? true : false;
            }
            else if (attriname == "FrameEvent")
            {
                frameEvent = value;
            }
            
            attribute = attribute->Next();
        }
        
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string attriname = child->Name();
            if (attriname == "Children")
            {
                break;
            }
            else if (attriname == "Position")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "X")
                    {
                        position.x = atof(value.c_str());
                    }
                    else if (attriname == "Y")
                    {
                        position.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "Scale")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "ScaleX")
                    {
                        scale.x = atof(value.c_str());
                    }
                    else if (attriname == "ScaleY")
                    {
                        scale.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "AnchorPoint")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "ScaleX")
                    {
                        anchorPoint.x = atof(value.c_str());
                    }
                    else if (attriname == "ScaleY")
                    {
                        anchorPoint.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "CColor")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "A")
                    {
                        color.a = atoi(value.c_str());
                    }
                    else if (attriname == "R")
                    {
                        color.r = atoi(value.c_str());
                    }
                    else if (attriname == "G")
                    {
                        color.g = atoi(value.c_str());
                    }
                    else if (attriname == "B")
                    {
                        color.b = atoi(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            else if (attriname == "Size")
            {
                attribute = child->FirstAttribute();
                
                while (attribute)
                {
                    attriname = attribute->Name();
                    std::string value = attribute->Value();
                    
                    if (attriname == "X")
                    {
                        size.x = atof(value.c_str());
                    }
                    else if (attriname == "Y")
                    {
                        size.y = atof(value.c_str());
                    }
                    
                    attribute = attribute->Next();
                }
            }
            
            child = child->NextSiblingElement();
        }
        
        RotationSkew f_rotationskew(rotationSkew.x, rotationSkew.y);
        Position f_position(position.x, position.y);
        Scale f_scale(scale.x, scale.y);
        AnchorPoint f_anchortpoint(anchorPoint.x, anchorPoint.y);
        Color f_color(color.a, color.r, color.g, color.b);
        FlatSize f_size(size.x, size.y);
        
        
        auto options = CreateWidgetOptions(*builder,
                                           builder->CreateString(name),
                                           (int)actionTag,
                                           &f_rotationskew,
                                           zOrder,
                                           visible,
                                           alpha,
                                           tag,
                                           &f_position,
                                           &f_scale,
                                           &f_anchortpoint,
                                           &f_color,
                                           &f_size,
                                           flipX,
                                           flipY,
                                           ignoreSize,
                                           touchEnabled,
                                           builder->CreateString(frameEvent),
                                           builder->CreateString(customProperty)
                                           );
        
        return *(Offset<Table>*)(&options);
    }
    
    void NodeReader::setPropsWithFlatBuffers(cocos2d::Node *node,
                                             const flatbuffers::Table* nodeOptions)
    {
        auto options = (WidgetOptions*)(nodeOptions);
        
        std::string name = options->name()->c_str();
        float x             = options->position()->x();
        float y             = options->position()->y();
        float scalex        = options->scale()->scaleX();
        float scaley        = options->scale()->scaleY();
        //    float rotation      = options.rotation();
        float rotationSkewX      = options->rotationSkew()->rotationSkewX();
        float rotationSkewY      = options->rotationSkew()->rotationSkewY();
        float anchorx       = options->anchorPoint()->scaleX();
        float anchory       = options->anchorPoint()->scaleY();
        int zorder		    = options->zOrder();
        int tag             = options->tag();
        int actionTag       = options->actionTag();
        bool visible        = options->visible();
        float w             = options->size()->width();
        float h             = options->size()->height();
        int alpha           = options->alpha();
        Color3B color(options->color()->r(), options->color()->g(), options->color()->b());
        
        node->setName(name);
        
//        if(x != 0 || y != 0)
            node->setPosition(Point(x, y));
        if(scalex != 1)
            node->setScaleX(scalex);
        if(scaley != 1)
            node->setScaleY(scaley);
        //    if (rotation != 0)
        //        node->setRotation(rotation);
        if (rotationSkewX != 0)
            node->setRotationSkewX(rotationSkewX);
        if (rotationSkewY != 0)
            node->setRotationSkewY(rotationSkewY);
        if(anchorx != 0.5f || anchory != 0.5f)
            node->setAnchorPoint(Point(anchorx, anchory));
        if(zorder != 0)
            node->setLocalZOrder(zorder);
        if(visible != true)
            node->setVisible(visible);
//        if (w != 0 || h != 0)
            node->setContentSize(Size(w, h));
        if (alpha != 255)
            node->setOpacity(alpha);
        
        node->setColor(color);
        
        node->setTag(tag);
        node->setUserObject(timeline::ActionTimelineData::create(actionTag));
        
        node->setCascadeColorEnabled(true);
        node->setCascadeOpacityEnabled(true);
    }
    
    Node* NodeReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
    {
        Node* node = Node::create();
        
        setPropsWithFlatBuffers(node, nodeOptions);
        
        return node;
    }
}


