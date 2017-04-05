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
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

#if (CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION)

#if (CC_ENABLE_CHIPMUNK_INTEGRATION && CC_ENABLE_BOX2D_INTEGRATION)
#error "Either Chipmunk or Box2d should be enabled, but not both at the same time"
#endif

#if CC_ENABLE_CHIPMUNK_INTEGRATION
#include "chipmunk/chipmunk.h"
#elif CC_ENABLE_BOX2D_INTEGRATION
#include "Box2D/Box2D.h"
#endif

NS_CC_EXT_BEGIN

PhysicsSprite::PhysicsSprite()
: _ignoreBodyRotation(false)
, _CPBody(nullptr)
, _pB2Body(nullptr)
, _PTMRatio(0.0f)
, _syncTransform(nullptr)
{}

PhysicsSprite* PhysicsSprite::create()
{
    PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
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
    PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
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
    PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
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
    PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
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
    PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
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
    PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
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
    PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
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
const Vec2& PhysicsSprite::getPosition() const
{
    return getPosFromPhysics();
}

void PhysicsSprite::getPosition(float* x, float* y) const
{
    if (x == nullptr || y == nullptr) {
        return;
    }
    const Vec2& pos = getPosFromPhysics();
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

Vec3 PhysicsSprite::getPosition3D() const
{
    Vec2 pos = getPosFromPhysics();
    return Vec3(pos.x, pos.y, 0);
}

//
// Chipmunk only
//



cpBody* PhysicsSprite::getCPBody() const
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    return _CPBody;
#else
    CCASSERT(false, "Can't call chipmunk methods when Chipmunk is disabled");
    return nullptr;
#endif
}

void PhysicsSprite::setCPBody(cpBody *pBody)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    _CPBody = pBody;
#else
    CCASSERT(false, "Can't call chipmunk methods when Chipmunk is disabled");
#endif
}

b2Body* PhysicsSprite::getB2Body() const
{
#if CC_ENABLE_BOX2D_INTEGRATION
    return _pB2Body;
#else
    CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
    return nullptr;
#endif
}

void PhysicsSprite::setB2Body(b2Body *pBody)
{
#if CC_ENABLE_BOX2D_INTEGRATION
    _pB2Body = pBody;
#else
    CC_UNUSED_PARAM(pBody);
    CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
#endif
}

float PhysicsSprite::getPTMRatio() const
{
#if CC_ENABLE_BOX2D_INTEGRATION
    return _PTMRatio;
#else
    CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
    return 0;
#endif
}

void PhysicsSprite::setPTMRatio(float fRatio)
{
#if CC_ENABLE_BOX2D_INTEGRATION
     _PTMRatio = fRatio;
#else
    CC_UNUSED_PARAM(fRatio);
    CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
#endif
}

//
// Common to Box2d and Chipmunk
//

const Vec2& PhysicsSprite::getPosFromPhysics() const
{
    static Vec2 s_physicPosion;
#if CC_ENABLE_CHIPMUNK_INTEGRATION

    cpVect cpPos = cpBodyGetPosition(_CPBody);
    s_physicPosion = Vec2(cpPos.x, cpPos.y);

#elif CC_ENABLE_BOX2D_INTEGRATION

    b2Vec2 pos = _pB2Body->GetPosition();
    float x = pos.x * _PTMRatio;
    float y = pos.y * _PTMRatio;
    s_physicPosion.set(x,y);
#endif
    return s_physicPosion;
}

void PhysicsSprite::setPosition(float x, float y)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION

    cpVect cpPos = cpv(x, y);
    cpBodySetPosition(_CPBody, cpPos);

#elif CC_ENABLE_BOX2D_INTEGRATION
    
    float angle = _pB2Body->GetAngle();
    _pB2Body->SetTransform(b2Vec2(x / _PTMRatio, y / _PTMRatio), angle);
#endif
}

void PhysicsSprite::setPosition(const Vec2 &pos)
{
    setPosition(pos.x, pos.y);
}

void PhysicsSprite::setPositionX(float x)
{
    setPosition(x, getPositionY());
}

void PhysicsSprite::setPositionY(float y)
{
    setPosition(getPositionX(), y);
}

void PhysicsSprite::setPosition3D(const Vec3& position)
{
    setPosition(position.x, position.y);
}

float PhysicsSprite::getRotation() const
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION

    return (_ignoreBodyRotation ? Sprite::getRotation() : -CC_RADIANS_TO_DEGREES(cpBodyGetAngle(_CPBody)));

#elif CC_ENABLE_BOX2D_INTEGRATION
    
    return (_ignoreBodyRotation ? Sprite::getRotation() :
            CC_RADIANS_TO_DEGREES(_pB2Body->GetAngle()));
#else
    return 0.0f;
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

void PhysicsSprite::syncPhysicsTransform() const
{
    // Although scale is not used by physics engines, it is calculated just in case
    // the sprite is animated (scaled up/down) using actions.
    // For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
    
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    
    cpVect rot = (_ignoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(_rotationX)) : cpBodyGetRotation(_CPBody));
    float x = cpBodyGetPosition(_CPBody).x + rot.x * -_anchorPointInPoints.x * _scaleX - rot.y * -_anchorPointInPoints.y * _scaleY;
    float y = cpBodyGetPosition(_CPBody).y + rot.y * -_anchorPointInPoints.x * _scaleX + rot.x * -_anchorPointInPoints.y * _scaleY;
    
    if (_ignoreAnchorPointForPosition)
    {
        x += _anchorPointInPoints.x;
        y += _anchorPointInPoints.y;
    }
    
    float mat[] = {  (float)rot.x * _scaleX, (float)rot.y * _scaleX, 0,  0,
        (float)-rot.y * _scaleY, (float)rot.x * _scaleY,  0,  0,
        0,  0,  1,  0,
        x,    y,  0,  1};
    
    
    _transform.set(mat);
    
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
    
    if (!_anchorPointInPoints.isZero())
    {
        x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
        y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
    }
    
    // Rot, Translate Matrix
    
    float mat[] = {  (float)c * _scaleX, (float)s * _scaleX, 0,  0,
        (float)-s * _scaleY, (float)c * _scaleY,  0,  0,
        0,  0,  1,  0,
        x,    y,  0,  1};
    
    _transform.set(mat);
#endif
}

void PhysicsSprite::onEnter()
{
    Node::onEnter();
    _syncTransform = Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_AFTER_UPDATE, std::bind(&PhysicsSprite::afterUpdate, this, std::placeholders::_1));
    _syncTransform->retain();
}

void PhysicsSprite::onExit()
{
    if (_syncTransform != nullptr)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_syncTransform);
        _syncTransform->release();
    }
    Node::onExit();
}

void PhysicsSprite::afterUpdate(EventCustom* /*event*/)
{
    syncPhysicsTransform();
    
    _transformDirty = false;
    _transformUpdated = true;
    setDirtyRecursively(true);
}

NS_CC_EXT_END

#endif // CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION
