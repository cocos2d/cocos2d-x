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

CCPhysicsSprite::CCPhysicsSprite()
: m_bIgnoreBodyRotation(false)
#if CC_ENABLE_CHIPMUNK_INTEGRATION
, m_pBody(NULL)
#elif CC_ENABLE_BOX2D_INTEGRATION
, m_pBody(NULL)
, m_fPTMRatio(0.0f)
#endif
{}

CCPhysicsSprite* CCPhysicsSprite::create()
{
    CCPhysicsSprite* pRet = new CCPhysicsSprite();
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

CCPhysicsSprite* CCPhysicsSprite::createWithTexture(CCTexture2D *pTexture)
{
    CCPhysicsSprite* pRet = new CCPhysicsSprite();
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

CCPhysicsSprite* CCPhysicsSprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    CCPhysicsSprite* pRet = new CCPhysicsSprite();
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

CCPhysicsSprite* CCPhysicsSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    CCPhysicsSprite* pRet = new CCPhysicsSprite();
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

CCPhysicsSprite* CCPhysicsSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCPhysicsSprite* pRet = new CCPhysicsSprite();
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

CCPhysicsSprite* CCPhysicsSprite::create(const char *pszFileName)
{
    CCPhysicsSprite* pRet = new CCPhysicsSprite();
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

CCPhysicsSprite* CCPhysicsSprite::create(const char *pszFileName, const CCRect& rect)
{
    CCPhysicsSprite* pRet = new CCPhysicsSprite();
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
bool CCPhysicsSprite::isDirty()
{
    return true;
}

bool CCPhysicsSprite::isIgnoreBodyRotation() const
{
    return m_bIgnoreBodyRotation;
}

void CCPhysicsSprite::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
    m_bIgnoreBodyRotation = bIgnoreBodyRotation;
}

#if CC_ENABLE_CHIPMUNK_INTEGRATION

cpBody* CCPhysicsSprite::getBody() const
{
    return m_pBody;
}

void CCPhysicsSprite::setBody(cpBody *pBody)
{
    m_pBody = pBody;
}

// Override the setters and getters to always reflect the body's properties.
CCPoint CCPhysicsSprite::getPosition()
{
    cpVect cpPos = cpBodyGetPos(m_pBody);
    return ccp(cpPos.x, cpPos.y);
}

void CCPhysicsSprite::setPosition(const CCPoint &pos)
{
    cpVect cpPos = cpv(pos.x, pos.y);
    cpBodySetPos(m_pBody, cpPos);
}

float CCPhysicsSprite::getRotation()
{
    return (m_bIgnoreBodyRotation ? CCSprite::getRotation() : -CC_RADIANS_TO_DEGREES(cpBodyGetAngle(m_pBody)));
}

void CCPhysicsSprite::setRotation(float fRotation)
{
    if (m_bIgnoreBodyRotation)
    {
        CCSprite::setRotation(fRotation);
    }
    else
    {
        cpBodySetAngle(m_pBody, -CC_DEGREES_TO_RADIANS(fRotation));
    }
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform CCPhysicsSprite::nodeToParentTransform()
{
    cpVect rot = (m_bIgnoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(m_fRotationX)) : m_pBody->rot);
    float x = m_pBody->p.x + rot.x*(-m_obAnchorPointInPoints.x) - rot.y*(-m_obAnchorPointInPoints.y);
    float y = m_pBody->p.y + rot.y*(-m_obAnchorPointInPoints.x) + rot.x*(-m_obAnchorPointInPoints.y);
    
    if (m_bIgnoreAnchorPointForPosition)
    {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }
    
    return (m_sTransform = CCAffineTransformMake(rot.x, rot.y, -rot.y, rot.x, x, y));
}

#elif CC_ENABLE_BOX2D_INTEGRATION

b2Body* CCPhysicsSprite::getBody() const
{
    return m_pBody;
}

void CCPhysicsSprite::setBody(b2Body *pBody)
{
    m_pBody = pBody;
}

float CCPhysicsSprite::getPTMRatio() const
{
    return m_fPTMRatio;
}

void CCPhysicsSprite::setPTMRatio(float fRatio)
{
    m_fPTMRatio = fRatio;
}

// Override the setters and getters to always reflect the body's properties.
CCPoint CCPhysicsSprite::getPosition()
{
    b2Vec2 pos = m_pBody->GetPosition();
    
    float x = pos.x * m_fPTMRatio;
    float y = pos.y * m_fPTMRatio;
    return ccp(x,y);
}

void CCPhysicsSprite::setPosition(const CCPoint &pos)
{
    float angle = m_pBody->GetAngle();
    m_pBody->SetTransform(b2Vec2(pos.x / m_fPTMRatio, pos.y / m_fPTMRatio), angle);
}

float CCPhysicsSprite::getRotation()
{
    return (m_bIgnoreBodyRotation ? CCSprite::getRotation() :
            CC_RADIANS_TO_DEGREES(m_pBody->GetAngle()));
}

void CCPhysicsSprite::setRotation(float fRotation)
{
    if (m_bIgnoreBodyRotation)
    {
        CCSprite::setRotation(fRotation);
    }
    else
    {
        b2Vec2 p = m_pBody->GetPosition();
        float radians = CC_DEGREES_TO_RADIANS(fRotation);
        m_pBody->SetTransform(p, radians);
    }
}

// returns the transform matrix according the Box2D Body values
CCAffineTransform CCPhysicsSprite::nodeToParentTransform()
{
    b2Vec2 pos = m_pBody->GetPosition();
    
    float x = pos.x * m_fPTMRatio;
    float y = pos.y * m_fPTMRatio;
    
    if (m_bIgnoreAnchorPointForPosition)
    {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }
    
    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);
    
    if (! m_obAnchorPointInPoints.equals(CCPointZero))
    {
        x += c*(-m_obAnchorPointInPoints.x) + -s*(-m_obAnchorPointInPoints.y);
        y += s*(-m_obAnchorPointInPoints.x) + c*(-m_obAnchorPointInPoints.y);
    }
    
    // Rot, Transition Matrix
    m_sTransform = CCAffineTransformMake(c, s,
                                         -s, c,
                                         x, y);
    
    return m_sTransform;
}

#endif

NS_CC_EXT_END
