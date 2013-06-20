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

#include "CCPhysicsSprite.h"
#include "support/CCPointExtension.h"

#if CC_ENABLE_CHIPMUNK_INTEGRATION
#include "chipmunk.h"
#elif CC_ENABLE_BOX2D_INTEGRATION
#include "Box2D/Box2D.h"
#endif

NS_CC_EXT_BEGIN

PhysicsSprite::PhysicsSprite()
: _ignoreBodyRotation(false)
#if CC_ENABLE_CHIPMUNK_INTEGRATION
, _CPBody(NULL)
#elif CC_ENABLE_BOX2D_INTEGRATION
, _pB2Body(NULL)
, _PTMRatio(0.0f)
#endif
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
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty()
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
const Point& PhysicsSprite::getPosition()
{
    updatePosFromPhysics();
    return Node::getPosition();
}

void PhysicsSprite::getPosition(float* x, float* y)
{
    updatePosFromPhysics();
    return Node::getPosition(x, y);
}

float PhysicsSprite::getPositionX()
{
    updatePosFromPhysics();
    return _position.x;
}

float PhysicsSprite::getPositionY()
{
    updatePosFromPhysics();
    return _position.y;
}

#if CC_ENABLE_CHIPMUNK_INTEGRATION

cpBody* PhysicsSprite::getCPBody() const
{
    return _CPBody;
}

void PhysicsSprite::setCPBody(cpBody *pBody)
{
    _CPBody = pBody;
}

void PhysicsSprite::updatePosFromPhysics()
{
    cpVect cpPos = cpBodyGetPos(_CPBody);
    _position = ccp(cpPos.x, cpPos.y);
}

void PhysicsSprite::setPosition(const Point &pos)
{
    cpVect cpPos = cpv(pos.x, pos.y);
    cpBodySetPos(_CPBody, cpPos);
}

float PhysicsSprite::getRotation()
{
    return (_ignoreBodyRotation ? Sprite::getRotation() : -CC_RADIANS_TO_DEGREES(cpBodyGetAngle(_CPBody)));
}

void PhysicsSprite::setRotation(float fRotation)
{
    if (_ignoreBodyRotation)
    {
        Sprite::setRotation(fRotation);
    }
    else
    {
        cpBodySetAngle(_CPBody, -CC_DEGREES_TO_RADIANS(fRotation));
    }
}

// returns the transform matrix according the Chipmunk Body values
AffineTransform PhysicsSprite::nodeToParentTransform()
{
    // Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
	cpVect rot = (_ignoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(_rotationX)) : _CPBody->rot);
	float x = _CPBody->p.x + rot.x * -_anchorPointInPoints.x * _scaleX - rot.y * -_anchorPointInPoints.y * _scaleY;
	float y = _CPBody->p.y + rot.y * -_anchorPointInPoints.x * _scaleX + rot.x * -_anchorPointInPoints.y * _scaleY;
	
	if (_ignoreAnchorPointForPosition)
    {
		x += _anchorPointInPoints.x;
		y += _anchorPointInPoints.y;
	}
	
	return (_transform = AffineTransformMake(rot.x * _scaleX, rot.y * _scaleX,
                                                 -rot.y * _scaleY, rot.x * _scaleY,
                                                 x,	y));
}

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

// Override the setters and getters to always reflect the body's properties.
void PhysicsSprite::updatePosFromPhysics()
{
    b2Vec2 pos = _pB2Body->GetPosition();
    float x = pos.x * _PTMRatio;
    float y = pos.y * _PTMRatio;
    _position = ccp(x,y);
}

void PhysicsSprite::setPosition(const Point &pos)
{
    float angle = _pB2Body->GetAngle();
    _pB2Body->SetTransform(b2Vec2(pos.x / _PTMRatio, pos.y / _PTMRatio), angle);
}

float PhysicsSprite::getRotation()
{
    return (_ignoreBodyRotation ? Sprite::getRotation() :
            CC_RADIANS_TO_DEGREES(_pB2Body->GetAngle()));
}

void PhysicsSprite::setRotation(float fRotation)
{
    if (_ignoreBodyRotation)
    {
        Sprite::setRotation(fRotation);
    }
    else
    {
        b2Vec2 p = _pB2Body->GetPosition();
        float radians = CC_DEGREES_TO_RADIANS(fRotation);
        _pB2Body->SetTransform(p, radians);
    }
}

// returns the transform matrix according the Box2D Body values
AffineTransform PhysicsSprite::nodeToParentTransform()
{
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
	
	// Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
	if (!_anchorPointInPoints.equals(PointZero))
    {
		x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
		y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
	}
    
	// Rot, Translate Matrix
	_transform = AffineTransformMake( c * _scaleX,	s * _scaleX,
									     -s * _scaleY,	c * _scaleY,
									     x,	y );
	
	return _transform;
}

#endif

NS_CC_EXT_END
