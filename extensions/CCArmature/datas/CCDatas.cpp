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
#include "../utils/CCUtilMath.h"
#include "../utils/CCTransformHelp.h"

NS_CC_EXT_BEGIN


CCBaseData::CCBaseData()
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

CCBaseData::~CCBaseData()
{
}

void CCBaseData::copy(const CCBaseData *node )
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


void CCBaseData::subtract(CCBaseData *from, CCBaseData *to)
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

void CCBaseData::setColor(ccColor4B &color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}

ccColor4B CCBaseData::getColor()
{
	return ccc4(r, g, b, a);
}

const char *CCDisplayData::changeDisplayToTexture(const char *displayName)
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

CCDisplayData::CCDisplayData(void)
    : displayType(CS_DISPLAY_SPRITE)
{
}

CCDisplayData::~CCDisplayData(void)
{
}

CCSpriteDisplayData::CCSpriteDisplayData(void)
    : displayName("")
{
    displayType = CS_DISPLAY_SPRITE;
}

CCSpriteDisplayData::~CCSpriteDisplayData()
{
}

void CCSpriteDisplayData::copy(CCSpriteDisplayData *displayData)
{
    displayName = displayData->displayName;
    displayType = displayData->displayType;

	skinData = displayData->skinData;
}

CCArmatureDisplayData::CCArmatureDisplayData(void)
    : displayName("")
{
    displayType = CS_DISPLAY_ARMATURE;
}

CCArmatureDisplayData::~CCArmatureDisplayData()
{
}

void CCArmatureDisplayData::copy(CCArmatureDisplayData *displayData)
{
    displayName = displayData->displayName;
    displayType = displayData->displayType;
}

CCParticleDisplayData::CCParticleDisplayData(void)
    : plist("")
{
    displayType = CS_DISPLAY_PARTICLE;
}

void CCParticleDisplayData::copy(CCParticleDisplayData *displayData)
{
    plist = displayData->plist;
    displayType = displayData->displayType;
}

CCShaderDisplayData::CCShaderDisplayData(void)
    : vert("")
    , frag("")
{
    displayType = CS_DISPLAY_SHADER;
}

void CCShaderDisplayData::copy(CCShaderDisplayData *displayData)
{
    vert = displayData->vert;
    frag = displayData->frag;
    displayType = displayData->displayType;
}


CCBoneData::CCBoneData(void)
    : name("")
    , parentName("")
{
}

CCBoneData::~CCBoneData(void)
{
}

bool CCBoneData::init()
{
    displayDataList.init();
    return true;
}

void CCBoneData::addDisplayData(CCDisplayData *displayData)
{
    displayDataList.addObject(displayData);
}

CCDisplayData *CCBoneData::getDisplayData(int index)
{
    return (CCDisplayData *)displayDataList.objectAtIndex(index);
}


CCArmatureData::CCArmatureData()
	:dataVersion(0.1f)
{
}

CCArmatureData::~CCArmatureData()
{
}

bool CCArmatureData::init()
{
    return true;
}

void CCArmatureData::addBoneData(CCBoneData *boneData)
{
    boneDataDic.setObject(boneData, boneData->name);
}

CCBoneData *CCArmatureData::getBoneData(const char *boneName)
{
    return (CCBoneData *)boneDataDic.objectForKey(boneName);
}

CCFrameData::CCFrameData(void)
    : frameID(0)
	, duration(1)
    , tweenEasing(Linear)
    , displayIndex(0)

    , strMovement("")
    , strEvent("")
    , strSound("")
    , strSoundEffect("")
{
}

CCFrameData::~CCFrameData(void)
{
}

void CCFrameData::copy(CCFrameData *frameData)
{
    CCBaseData::copy(frameData);

    duration = frameData->duration;
    displayIndex = frameData->displayIndex;
    tweenEasing = frameData->tweenEasing;
}

CCMovementBoneData::CCMovementBoneData()
    : delay(0.0f)
	, scale(1.0f)
    , duration(0)
    , name("")
{
}

CCMovementBoneData::~CCMovementBoneData(void)
{
}

bool CCMovementBoneData::init()
{
    return frameList.init();
}

void CCMovementBoneData::addFrameData(CCFrameData *frameData)
{
    frameList.addObject(frameData);
}

CCFrameData *CCMovementBoneData::getFrameData(int index)
{
    return (CCFrameData *)frameList.objectAtIndex(index);
}



CCMovementData::CCMovementData(void)
    : name("")
    , duration(0)
	, scale(1.0f)
    , durationTo(0)
    , durationTween(0)
    , loop(true)
    , tweenEasing(Linear)
{
}

CCMovementData::~CCMovementData(void)
{
}

void CCMovementData::addMovementBoneData(CCMovementBoneData *movBoneData)
{
    movBoneDataDic.setObject(movBoneData, movBoneData->name);
}

CCMovementBoneData *CCMovementData::getMovementBoneData(const char *boneName)
{
    return (CCMovementBoneData *)movBoneDataDic.objectForKey(boneName);
}



CCAnimationData::CCAnimationData(void)
{
}

CCAnimationData::~CCAnimationData(void)
{
}

void CCAnimationData::release()
{
    CCObject::release();
}

void CCAnimationData::retain()
{
    CCObject::retain();
}

void CCAnimationData::addMovement(CCMovementData *movData)
{
    movementDataDic.setObject(movData, movData->name);
    movementNames.push_back(movData->name);
}

CCMovementData *CCAnimationData::getMovement(const char *movementName)
{
    return (CCMovementData *)movementDataDic.objectForKey(movementName);
}

int CCAnimationData::getMovementCount()
{
    return movementDataDic.count();
}



CCContourData::CCContourData()
{
}

CCContourData::~CCContourData()
{
}

bool CCContourData::init()
{
    return vertexList.init();
}

void CCContourData::addVertex(CCPoint *vertex)
{
	CCContourVertex2 *vertex2 = new CCContourVertex2(vertex->x, vertex->y);
	vertex2->autorelease();

	vertexList.addObject(vertex2);
}

CCTextureData::CCTextureData()
    : height(0.0f)
    , width(0.0f)
    , pivotX(0.5f)
    , pivotY(0.5f)
    , name("")
{
}

CCTextureData::~CCTextureData()
{
}

bool CCTextureData::init()
{
    return contourDataList.init();
}

void CCTextureData::addContourData(CCContourData *contourData)
{
    contourDataList.addObject(contourData);
}

CCContourData *CCTextureData::getContourData(int index)
{
    return (CCContourData *)contourDataList.objectAtIndex(index);
}


NS_CC_EXT_END
