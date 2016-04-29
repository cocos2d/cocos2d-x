/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "editor-support/cocostudio/CCDatas.h"
#include "editor-support/cocostudio/CCUtilMath.h"
#include "editor-support/cocostudio/CCTransformHelp.h"

using namespace cocos2d;

namespace cocostudio {


BaseData::BaseData()
    : x(0.0f)
    , y(0.0f)
    , zOrder(0)

    , skewX(0.0f)
    , skewY(0.0f)
    , scaleX(1.0f)
    , scaleY(1.0f)

    , tweenRotate(0.0f)

    , isUseColorInfo(false)
    , a(255)
    , r(255)
    , g(255)
    , b(255)
{
}

BaseData::~BaseData()
{
}

void BaseData::copy(const BaseData *node )
{
    x = node->x;
    y = node->y;
    zOrder = node->zOrder;

    scaleX = node->scaleX;
    scaleY = node->scaleY;
    skewX = node->skewX;
    skewY = node->skewY;

    tweenRotate = node->tweenRotate;

    isUseColorInfo = node->isUseColorInfo;
    r = node->r;
    g = node->g;
    b = node->b;
    a = node->a;
}


void BaseData::subtract(BaseData *from, BaseData *to, bool limit)
{
    x = to->x - from->x;
    y = to->y - from->y;
    scaleX = to->scaleX - from->scaleX;
    scaleY = to->scaleY - from->scaleY;
    skewX = to->skewX - from->skewX;
    skewY = to->skewY - from->skewY;

    if(isUseColorInfo || from->isUseColorInfo || to->isUseColorInfo)
    {
        a = to->a - from->a;
        r = to->r - from->r;
        g = to->g - from->g;
        b = to->b - from->b;

        isUseColorInfo = true;
    }
    else
    {
        a = r = g = b = 0;
        isUseColorInfo = false;
    }

	if (limit)
	{
        if (skewX > M_PI)
        {
            skewX -= (float)CC_DOUBLE_PI;
        }
        if (skewX < -M_PI)
        {
            skewX += (float)CC_DOUBLE_PI;
        }

        if (skewY > M_PI)
        {
            skewY -= (float)CC_DOUBLE_PI;
        }
        if (skewY < -M_PI)
        {
            skewY += (float)CC_DOUBLE_PI;
        }
    }

    if (to->tweenRotate)
    {
        skewX += to->tweenRotate * M_PI * 2;
        skewY -= to->tweenRotate * M_PI * 2;
    }
	
}

void BaseData::setColor(const Color4B &color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

Color4B BaseData::getColor()
{
    return Color4B(r, g, b, a);
}

std::string DisplayData::changeDisplayToTexture(const std::string& displayName)
{
    // remove .xxx
    std::string textureName = displayName;
    size_t startPos = textureName.find_last_of(".");

    if(startPos != std::string::npos)
    {
        textureName = textureName.erase(startPos);
    }

    return textureName;
}

DisplayData::DisplayData(void)
    : displayType(CS_DISPLAY_MAX)
    , displayName("")
{
}

void DisplayData::copy(DisplayData *displayData)
{
    displayName = displayData->displayName;
    displayType = displayData->displayType;
}

SpriteDisplayData::SpriteDisplayData(void)
{
    displayType = CS_DISPLAY_SPRITE;
}


void SpriteDisplayData::copy(DisplayData *displayData)
{
    DisplayData::copy(displayData);

    if (SpriteDisplayData *sdd = dynamic_cast<SpriteDisplayData*>(displayData))
    {
        skinData = sdd->skinData;
    }
}

ArmatureDisplayData::ArmatureDisplayData(void)
{
    displayType = CS_DISPLAY_ARMATURE;
}

ParticleDisplayData::ParticleDisplayData(void)
{
    displayType = CS_DISPLAY_PARTICLE;
}



BoneData::BoneData(void)
    : name("")
    , parentName("")
{
}

BoneData::~BoneData(void)
{
}

bool BoneData::init()
{
    return true;
}

void BoneData::addDisplayData(DisplayData *displayData)
{
    displayDataList.pushBack(displayData);
}

DisplayData *BoneData::getDisplayData(int index)
{
    return displayDataList.at(index);
}


ArmatureData::ArmatureData()
    : dataVersion(0.1f)
{
}

ArmatureData::~ArmatureData()
{
}

bool ArmatureData::init()
{
    return true;
}

void ArmatureData::addBoneData(BoneData *boneData)
{
    boneDataDic.insert(boneData->name, boneData);
}

BoneData *ArmatureData::getBoneData(const std::string& boneName)
{
    return static_cast<BoneData*>(boneDataDic.at(boneName));
}

FrameData::FrameData(void)
    : frameID(0)
    , duration(1)
    , tweenEasing(cocos2d::tweenfunc::Linear)
    , easingParamNumber(0)
    , easingParams(nullptr)
    , isTween(true)
    , displayIndex(0)
    , blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)

    , strEvent("")
    , strMovement("")
    , strSound("")
    , strSoundEffect("")
{
}

FrameData::~FrameData(void)
{
    CC_SAFE_DELETE(easingParams);
}

void FrameData::copy(const BaseData *baseData)
{
    BaseData::copy(baseData);
    
    if (const FrameData *frameData = dynamic_cast<const FrameData*>(baseData))
    {
        duration = frameData->duration;
        displayIndex = frameData->displayIndex;
        
        tweenEasing = frameData->tweenEasing;
        easingParamNumber = frameData->easingParamNumber;
        
        CC_SAFE_DELETE(easingParams);
        if (easingParamNumber != 0)
        {
            easingParams = new (std::nothrow) float[easingParamNumber];
            for (int i = 0; i<easingParamNumber; i++)
            {
                easingParams[i] = frameData->easingParams[i];
            }
        }

        blendFunc = frameData->blendFunc;
        isTween = frameData->isTween;
    }
}

MovementBoneData::MovementBoneData()
    : delay(0.0f)
    , scale(1.0f)
    , duration(0)
    , name("")
{
}

MovementBoneData::~MovementBoneData(void)
{
}

bool MovementBoneData::init()
{
    return true;
}

void MovementBoneData::addFrameData(FrameData *frameData)
{
    frameList.pushBack(frameData);
}

FrameData *MovementBoneData::getFrameData(int index)
{
    return frameList.at(index);
}



MovementData::MovementData(void)
    : name("")
    , duration(0)
    , scale(1.0f)
    , durationTo(0)
    , durationTween(0)
    , loop(true)
    , tweenEasing(cocos2d::tweenfunc::Linear)
{
}

MovementData::~MovementData(void)
{
}

void MovementData::addMovementBoneData(MovementBoneData *movBoneData)
{
    movBoneDataDic.insert(movBoneData->name, movBoneData);
}

MovementBoneData *MovementData::getMovementBoneData(const std::string& boneName)
{
    return movBoneDataDic.at(boneName);
}



AnimationData::AnimationData(void)
{
}

AnimationData::~AnimationData(void)
{
}

void AnimationData::addMovement(MovementData *movData)
{
    movementDataDic.insert(movData->name, movData);
    movementNames.push_back(movData->name);
}

MovementData *AnimationData::getMovement(const std::string& movementName)
{
    return movementDataDic.at(movementName);
}

ssize_t AnimationData::getMovementCount()
{
    return movementDataDic.size();
}



ContourData::ContourData()
{
}

ContourData::~ContourData()
{
}

bool ContourData::init()
{
    return true;
}

void ContourData::addVertex(Vec2 &vertex)
{
    vertexList.push_back(vertex);
}

TextureData::TextureData()
    : height(0.0f)
    , width(0.0f)
    , pivotX(0.5f)
    , pivotY(0.5f)
    , name("")
{
}

TextureData::~TextureData()
{
}

bool TextureData::init()
{
    return true;
}

void TextureData::addContourData(ContourData *contourData)
{
    contourDataList.pushBack(contourData);
}

ContourData *TextureData::getContourData(int index)
{
    return contourDataList.at(index);
}


}
