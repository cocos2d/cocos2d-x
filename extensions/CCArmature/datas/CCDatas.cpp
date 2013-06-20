/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCDatas.h"
#include "CCArmature/utils/CCUtilMath.h"

namespace cocos2d { namespace extension { namespace armature {


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


void BaseData::subtract(BaseData *from, BaseData *to)
{
	x = to->x - from->x;
	y = to->y - from->y;
	scaleX = to->scaleX - from->scaleX;
	scaleY = to->scaleY - from->scaleY;
	skewX = to->skewX - from->skewX;
	skewY = to->skewY - from->skewY;

	if(from->isUseColorInfo || to->isUseColorInfo)
	{
		a = to->a - from->a;
		r = to->r - from->r;
		g = to->g - from->g;
		b = to->b - from->b;

		isUseColorInfo = true;
	}


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

	if (to->tweenRotate)
	{
		skewX += to->tweenRotate;
		skewY -= to->tweenRotate;
	}
}


const char *DisplayData::changeDisplayToTexture(const char *displayName)
{
    // remove .xxx
    std::string textureName = displayName;
    size_t startPos = textureName.find_last_of(".");

    if(startPos != std::string::npos)
    {
        textureName = textureName.erase(startPos);
    }

    return textureName.c_str();
}

DisplayData::DisplayData(void)
    : displayType(CS_DISPLAY_SPRITE)
{
}

DisplayData::~DisplayData(void)
{
}

SpriteDisplayData::SpriteDisplayData(void)
    : displayName("")
{
    displayType = CS_DISPLAY_SPRITE;
}

SpriteDisplayData::~SpriteDisplayData()
{
}

void SpriteDisplayData::copy(SpriteDisplayData *displayData)
{
    displayName = displayData->displayName;
    displayType = displayData->displayType;
}

ArmatureDisplayData::ArmatureDisplayData(void)
    : displayName("")
{
    displayType = CS_DISPLAY_ARMATURE;
}

ArmatureDisplayData::~ArmatureDisplayData()
{
}

void ArmatureDisplayData::copy(ArmatureDisplayData *displayData)
{
    displayName = displayData->displayName;
    displayType = displayData->displayType;
}

ParticleDisplayData::ParticleDisplayData(void)
    : plist("")
{
    displayType = CS_DISPLAY_PARTICLE;
}

void ParticleDisplayData::copy(ParticleDisplayData *displayData)
{
    plist = displayData->plist;
    displayType = displayData->displayType;
}

ShaderDisplayData::ShaderDisplayData(void)
    : vert("")
    , frag("")
{
    displayType = CS_DISPLAY_SHADER;
}

void ShaderDisplayData::copy(ShaderDisplayData *displayData)
{
    vert = displayData->vert;
    frag = displayData->frag;
    displayType = displayData->displayType;
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
    displayDataList.init();
    return true;
}

void BoneData::addDisplayData(DisplayData *displayData)
{
    displayDataList.addObject(displayData);
}

DisplayData *BoneData::getDisplayData(int index)
{
    return (DisplayData *)displayDataList.objectAtIndex(index);
}

ArmatureData::ArmatureData()
{
}

ArmatureData::~ArmatureData()
{
}

bool ArmatureData::init()
{
    return boneList.init();
}

void ArmatureData::addBoneData(BoneData *boneData)
{
    boneDataDic.setObject(boneData, boneData->name);
    boneList.addObject(boneData);
}

BoneData *ArmatureData::getBoneData(const char *boneName)
{
    return (BoneData *)boneDataDic.objectForKey(boneName);
}

FrameData::FrameData(void)
    : duration(1)
    , tweenEasing(Linear)
    , displayIndex(0)

    , _movement("")
    , _event("")
    , _sound("")
    , _soundEffect("")
{
}

FrameData::~FrameData(void)
{
}

void FrameData::copy(FrameData *frameData)
{
    BaseData::copy(frameData);

    duration = frameData->duration;
    displayIndex = frameData->displayIndex;
    tweenEasing = frameData->tweenEasing;
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
    return frameList.init();
}

void MovementBoneData::addFrameData(FrameData *frameData)
{
    frameList.addObject(frameData);
    duration += frameData->duration;
}

FrameData *MovementBoneData::getFrameData(int index)
{
    return (FrameData *)frameList.objectAtIndex(index);
}



MovementData::MovementData(void)
    : name("")
    , duration(0)
    , durationTo(0)
    , durationTween(0)
    , loop(true)
    , tweenEasing(Linear)
{
}

MovementData::~MovementData(void)
{
}

void MovementData::addMovementBoneData(MovementBoneData *movBoneData)
{
    movBoneDataDic.setObject(movBoneData, movBoneData->name);
}

MovementBoneData *MovementData::getMovementBoneData(const char *boneName)
{
    return (MovementBoneData *)movBoneDataDic.objectForKey(boneName);
}



AnimationData::AnimationData(void)
{
}

AnimationData::~AnimationData(void)
{
}

void AnimationData::release()
{
    Object::release();
}

void AnimationData::retain()
{
    Object::retain();
}

void AnimationData::addMovement(MovementData *movData)
{
    movementDataDic.setObject(movData, movData->name);
    movementNames.push_back(movData->name);
}

MovementData *AnimationData::getMovement(const char *movementName)
{
    return (MovementData *)movementDataDic.objectForKey(movementName);
}

int AnimationData::getMovementCount()
{
    return movementDataDic.count();
}



ContourData::ContourData()
{
}

ContourData::~ContourData()
{
}

bool ContourData::init()
{
    return vertexList.init();
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
    return contourDataList.init();
}

void TextureData::addContourData(ContourData *contourData)
{
    contourDataList.addObject(contourData);
}

ContourData *TextureData::getContourData(int index)
{
    return (ContourData *)contourDataList.objectAtIndex(index);
}


}}} // namespace cocos2d { namespace extension { namespace armature {
