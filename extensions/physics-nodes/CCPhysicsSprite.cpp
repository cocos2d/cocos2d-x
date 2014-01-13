/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#if (CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION)

#include "CCPhysicsSprite.h"

#if (CC_ENABLE_CHIPMUNK_INTEGRATION && CC_ENABLE_BOX2D_INTEGRATION)
#error "Either Chipmunk or Box2d should be enabled, but not both at the same time"
#endif

#if CC_ENABLE_CHIPMUNK_INTEGRATION
#include "chipmunk.h"
#elif CC_ENABLE_BOX2D_INTEGRATION
#include "Box2D/Box2D.h"
#endif

NS_CC_EXT_BEGIN

PhysicsSprite::PhysicsSprite()
: _ignoreBodyRotation(false)
, _CPBody(NULL)
, _pB2Body(NULL)
, _PTMRatio(0.0f)
{}

PhysicsSprite* PhysicsSprite::create()
{
    PhysicsSprite* pRet = new PhysicsSprite();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

PhysicsSprite* PhysicsSprite::createWithTexture(Texture2D *pTexture)
{
    PhysicsSprite* pRet = new PhysicsSprite();
    if (pRet && pRet->initWithTexture(pTexture))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

PhysicsSprite* PhysicsSprite::createWithTexture(Texture2D *pTexture, const Rect& rect)
{
    PhysicsSprite* pRet = new PhysicsSprite();
    if (pRet && pRet->initWithTexture(pTexture, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

PhysicsSprite* PhysicsSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    PhysicsSprite* pRet = new PhysicsSprite();
    if (pRet && pRet->initWithSpriteFrame(pSpriteFrame))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

PhysicsSprite* PhysicsSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    PhysicsSprite* pRet = new PhysicsSprite();
    if (pRet && pRet->initWithSpriteFrameName(pszSpriteFrameName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

PhysicsSprite* PhysicsSprite::create(const char *pszFileName)
{
    PhysicsSprite* pRet = new PhysicsSprite();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

PhysicsSprite* PhysicsSprite::create(const char *pszFileName, const Rect& rect)
{
    PhysicsSprite* pRet = new PhysicsSprite();
    if (pRet && pRet->initWithFile(pszFileName, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

// this method will only get called if the sprite is batched.
// return YES if the physic's values (angles, position ) changed.
// If you return NO, then getNodeToParentTransform won't be called.
bool PhysicsSprite::isDirty() const
{
    return true;
}

bool PhysicsSprite::isIgnoreBodyRotation() const
{
    return _ignoreBodyRotation;
}

void PhysicsSprite::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
    _ignoreBodyRotation = bIgnoreBodyRotation;
}

// Override the setters and getters to always reflect the body's properties.
const Point& PhysicsSprite::getPosition() const
{
    return getPosFromPhysics();
}

void PhysicsSprite::getPosition(float* x, float* y) const
{
    if (x == NULL || y == NULL) {
        return;
    }
    const Point& pos = getPosFromPhysics();
    *x = pos.x;
    *y = pos.y;
}

float PhysicsSprite::getPositionX() const
{
    return getPosFromPhysics().x;
}

float PhysicsSprite::getPositionY() const
{
    return getPosFromPhysics().y;
}

//
// Chipmunk only
//

#if CC_ENABLE_CHIPMUNK_INTEGRATION

cpBody* PhysicsSprite::getCPBody() const
{
    return _CPBody;
}

void PhysicsSprite::setCPBody(cpBody *pBody)
{
    _CPBody = pBody;
}

b2Body* PhysicsSprite::getB2Body() const
{
    CCASSERT(false, "Can't call box2d methods when Chipmunk is enabled");
    return NULL;
}

void PhysicsSprite::setB2Body(b2Body *pBody)
{
    CCASSERT(false, "Can't call box2d methods when Chipmunk is enabled");
}

float PhysicsSprite::getPTMRatio() const
{
    CCASSERT(false, "Can't call box2d methods when Chipmunk is enabled");
    return 0;
}

void PhysicsSprite::setPTMRatio(float fRatio)
{
    CCASSERT(false, "Can't call box2d methods when Chipmunk is enabled");
}

//
// Box2d only
//
#elif CC_ENABLE_BOX2D_INTEGRATION

b2Body* PhysicsSprite::getB2Body() const
{
    return _pB2Body;
}

void PhysicsSprite::setB2Body(b2Body *pBody)
{
    _pB2Body = pBody;
}

float PhysicsSprite::getPTMRatio() const
{
    return _PTMRatio;
}

void PhysicsSprite::setPTMRatio(float fRatio)
{
    _PTMRatio = fRatio;
}

cpBody* PhysicsSprite::getCPBody() const
{
    CCASSERT(false, "Can't call Chipmunk methods when Box2d is enabled");
    return NULL;
}

void PhysicsSprite::setCPBody(cpBody *pBody)
{
    CCASSERT(false, "Can't call Chipmunk methods when Box2d is enabled");
}

#endif

//
// Common to Box2d and Chipmunk
//

const Point& PhysicsSprite::getPosFromPhysics() const
{
    static Point s_physicPosion;
#if CC_ENABLE_CHIPMUNK_INTEGRATION

    cpVect cpPos = cpBodyGetPos(_CPBody);
    s_physicPosion = Point(cpPos.x, cpPos.y);

#elif CC_ENABLE_BOX2D_INTEGRATION

    b2Vec2 pos = _pB2Body->GetPosition();
    float x = pos.x * _PTMRatio;
    float y = pos.y * _PTMRatio;
    s_physicPosion = Point(x,y);
#endif
    return s_physicPosion;
}

void PhysicsSprite::setPosition(const Point &pos)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION

    cpVect cpPos = cpv(pos.x, pos.y);
    cpBodySetPos(_CPBody, cpPos);

#elif CC_ENABLE_BOX2D_INTEGRATION

    float angle = _pB2Body->GetAngle();
    _pB2Body->SetTransform(b2Vec2(pos.x / _PTMRatio, pos.y / _PTMRatio), angle);
#endif

}

float PhysicsSprite::getRotation() const
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION

    return (_ignoreBodyRotation ? Sprite::getRotation() : -CC_RADIANS_TO_DEGREES(cpBodyGetAngle(_CPBody)));

#elif CC_ENABLE_BOX2D_INTEGRATION
    
    return (_ignoreBodyRotation ? Sprite::getRotation() :
            CC_RADIANS_TO_DEGREES(_pB2Body->GetAngle()));
#endif

}

void PhysicsSprite::setRotation(float fRotation)
{
    if (_ignoreBodyRotation)
    {
        Sprite::setRotation(fRotation);
    }

#if CC_ENABLE_CHIPMUNK_INTEGRATION
    else
    {
        cpBodySetAngle(_CPBody, -CC_DEGREES_TO_RADIANS(fRotation));
    }

#elif CC_ENABLE_BOX2D_INTEGRATION
    else
    {
        b2Vec2 p = _pB2Body->GetPosition();
        float radians = CC_DEGREES_TO_RADIANS(fRotation);
        _pB2Body->SetTransform(p, radians);
    }
#endif

}

// returns the transform matrix according the Chipmunk Body values
const kmMat4& PhysicsSprite::getNodeToParentTransform() const
{
    // Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990

#if CC_ENABLE_CHIPMUNK_INTEGRATION

	cpVect rot = (_ignoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(_rotationX)) : _CPBody->rot);
	float x = _CPBody->p.x + rot.x * -_anchorPointInPoints.x * _scaleX - rot.y * -_anchorPointInPoints.y * _scaleY;
	float y = _CPBody->p.y + rot.y * -_anchorPointInPoints.x * _scaleX + rot.x * -_anchorPointInPoints.y * _scaleY;

	if (_ignoreAnchorPointForPosition)
    {
		x += _anchorPointInPoints.x;
		y += _anchorPointInPoints.y;
	}

    
    kmScalar mat[] = {  (kmScalar)rot.x * _scaleX, (kmScalar)rot.y * _scaleX, 0,  0,
                        (kmScalar)-rot.y * _scaleY, (kmScalar)rot.x * _scaleY,  0,  0,
                        0,  0,  1,  0,
                        x,	y,  0,  1};


    kmMat4Fill(&_transform, mat);
    
    return _transform;


#elif CC_ENABLE_BOX2D_INTEGRATION

    b2Vec2 pos  = _pB2Body->GetPosition();

	float x = pos.x * _PTMRatio;
	float y = pos.y * _PTMRatio;

	if (_ignoreAnchorPointForPosition)
    {
		x += _anchorPointInPoints.x;
		y += _anchorPointInPoints.y;
	}

	// Make matrix
	float radians = _pB2Body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);

	if (!_anchorPointInPoints.equals(Point::ZERO))
    {
		x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
		y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
	}

	// Rot, Translate Matrix
	_transform = AffineTransformMake( c * _scaleX,	s * _scaleX,
                                     -s * _scaleY,	c * _scaleY,
                                     x,	y );

	return _transform;
#endif
}

NS_CC_EXT_END
#endif //(CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION)
