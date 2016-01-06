/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

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

#include "tinyxml2/tinyxml2.h"
#include "flatbuffers/flatbuffers.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/WidgetReader/SkeletonReader/CSBoneBinary_generated.h"
#include "cocostudio/WidgetReader/SkeletonReader/BoneNodeReader.h"
#include "cocostudio/ActionTimeline/CCBoneNode.h"


USING_NS_CC;
USING_NS_TIMELINE;
using namespace cocostudio;
using namespace flatbuffers;

IMPLEMENT_CLASS_NODE_READER_INFO(BoneNodeReader)

BoneNodeReader::BoneNodeReader()
{

}

BoneNodeReader::~BoneNodeReader()
{

}

static BoneNodeReader* _instanceBoneNodeReader = nullptr;

BoneNodeReader* BoneNodeReader::getInstance()
{
    if (_instanceBoneNodeReader == nullptr)
    {
        _instanceBoneNodeReader = new (std::nothrow) BoneNodeReader();
    }
    return _instanceBoneNodeReader;
}

void BoneNodeReader::destroyInstance()
{
    CC_SAFE_DELETE(_instanceBoneNodeReader);
}

Offset<Table> BoneNodeReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
    flatbuffers::FlatBufferBuilder *builder)
{

    auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
    auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);

    float length = 0;
    cocos2d::BlendFunc blendFunc = cocos2d::BlendFunc::ALPHA_PREMULTIPLIED;

    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string name = attribute->Name();
        std::string value = attribute->Value();

        if (name == "Length")
        {
            length = atof(value.c_str());
        }
        attribute = attribute->Next();
    }

    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    while (child)
    {
        std::string name = child->Name();
        if (name == "BlendFunc")
        {
            const tinyxml2::XMLAttribute* battribute = child->FirstAttribute();

            while (battribute)
            {
                name = battribute->Name();
                std::string value = battribute->Value();

                if (name == "Src")
                {
                    blendFunc.src = atoi(value.c_str());
                }
                else if (name == "Dst")
                {
                    blendFunc.dst = atoi(value.c_str());
                }

                battribute = battribute->Next();
            }
        }

        child = child->NextSiblingElement();
    }
    flatbuffers::BlendFunc f_blendFunc(blendFunc.src, blendFunc.dst);

    auto options = CreateBoneOptions(*builder,
        nodeOptions,
        length,
        &f_blendFunc);

    return *(Offset<Table>*)(&options);
}

void BoneNodeReader::setPropsWithFlatBuffers(cocos2d::Node *node,
    const flatbuffers::Table *nodeOptions)
{

    auto* bone = static_cast<BoneNode*>(node);
    auto options = (flatbuffers::BoneOptions*)nodeOptions;

    float length = options->length();
    bone->setDebugDrawLength(length);

    auto f_blendFunc = options->blendFunc();
    if (f_blendFunc)
    {
        cocos2d::BlendFunc blendFunc = cocos2d::BlendFunc::ALPHA_PREMULTIPLIED;
        blendFunc.src = f_blendFunc->src();
        blendFunc.dst = f_blendFunc->dst();
        bone->setBlendFunc(blendFunc);
    }
}

cocos2d::Node*  BoneNodeReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    auto bone = BoneNode::create();

    // self options
    auto options = (flatbuffers::BoneOptions*)nodeOptions;
    setPropsWithFlatBuffers(bone, (Table*)options);

    // super options (node)
    auto nodeReader = NodeReader::getInstance();
    nodeReader->setPropsWithFlatBuffers(bone, (Table*)options->nodeOptions());

    return bone;
}
