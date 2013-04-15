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
, m_pCPBody(NULL)
#elif CC_ENABLE_BOX2D_INTEGRATION
, m_pB2Body(NULL)
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

// Override the setters and getters to always reflect the body's properties.
const CCPoint& CCPhysicsSprite::getPosition()
{
    updatePosFromPhysics();
    return CCNode::getPosition();
}

void CCPhysicsSprite::getPosition(float* x, float* y)
{
    updatePosFromPhysics();
    return CCNode::getPosition(x, y);
}

float CCPhysicsSprite::getPositionX()
{
    updatePosFromPhysics();
    return m_obPosition.x;
}

float CCPhysicsSprite::getPositionY()
{
    updatePosFromPhysics();
    return m_obPosition.y;
}

#if CC_ENABLE_CHIPMUNK_INTEGRATION

cpBody* CCPhysicsSprite::getCPBody() const
{
    return m_pCPBody;
}

void CCPhysicsSprite::setCPBody(cpBody *pBody)
{
    m_pCPBody = pBody;
}

void CCPhysicsSprite::updatePosFromPhysics()
{
    cpVect cpPos = cpBodyGetPos(m_pCPBody);
    m_obPosition = ccp(cpPos.x, cpPos.y);
}

void CCPhysicsSprite::setPosition(const CCPoint &pos)
{
    cpVect cpPos = cpv(pos.x, pos.y);
    cpBodySetPos(m_pCPBody, cpPos);
}

float CCPhysicsSprite::getRotation()
{
    return (m_bIgnoreBodyRotation ? CCSprite::getRotation() : -CC_RADIANS_TO_DEGREES(cpBodyGetAngle(m_pCPBody)));
}

void CCPhysicsSprite::setRotation(float fRotation)
{
    if (m_bIgnoreBodyRotation)
    {
        CCSprite::setRotation(fRotation);
    }
    else
    {
        cpBodySetAngle(m_pCPBody, -CC_DEGREES_TO_RADIANS(fRotation));
    }
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform CCPhysicsSprite::nodeToParentTransform()
{
    // Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
	cpVect rot = (m_bIgnoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(m_fRotationX)) : m_pCPBody->rot);
	float x = m_pCPBody->p.x + rot.x * -m_obAnchorPointInPoints.x * m_fScaleX - rot.y * -m_obAnchorPointInPoints.y * m_fScaleY;
	float y = m_pCPBody->p.y + rot.y * -m_obAnchorPointInPoints.x * m_fScaleX + rot.x * -m_obAnchorPointInPoints.y * m_fScaleY;
	
	if (m_bIgnoreAnchorPointForPosition)
    {
		x += m_obAnchorPointInPoints.x;
		y += m_obAnchorPointInPoints.y;
	}
	
	return (m_sTransform = CCAffineTransformMake(rot.x * m_fScaleX, rot.y * m_fScaleX,
                                                 -rot.y * m_fScaleY, rot.x * m_fScaleY,
                                                 x,	y));
}

#elif CC_ENABLE_BOX2D_INTEGRATION

b2Body* CCPhysicsSprite::getB2Body() const
{
    return m_pB2Body;
}

void CCPhysicsSprite::setB2Body(b2Body *pBody)
{
    m_pB2Body = pBody;
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
void CCPhysicsSprite::updatePosFromPhysics()
{
    b2Vec2 pos = m_pB2Body->GetPosition();
    float x = pos.x * m_fPTMRatio;
    float y = pos.y * m_fPTMRatio;
    m_obPosition = ccp(x,y);
}

void CCPhysicsSprite::setPosition(const CCPoint &pos)
{
    float angle = m_pB2Body->GetAngle();
    m_pB2Body->SetTransform(b2Vec2(pos.x / m_fPTMRatio, pos.y / m_fPTMRatio), angle);
}

float CCPhysicsSprite::getRotation()
{
    return (m_bIgnoreBodyRotation ? CCSprite::getRotation() :
            CC_RADIANS_TO_DEGREES(m_pB2Body->GetAngle()));
}

void CCPhysicsSprite::setRotation(float fRotation)
{
    if (m_bIgnoreBodyRotation)
    {
        CCSprite::setRotation(fRotation);
    }
    else
    {
        b2Vec2 p = m_pB2Body->GetPosition();
        float radians = CC_DEGREES_TO_RADIANS(fRotation);
        m_pB2Body->SetTransform(p, radians);
    }
}

// returns the transform matrix according the Box2D Body values
CCAffineTransform CCPhysicsSprite::nodeToParentTransform()
{
    b2Vec2 pos  = m_pB2Body->GetPosition();
	
	float x = pos.x * m_fPTMRatio;
	float y = pos.y * m_fPTMRatio;
	
	if (m_bIgnoreAnchorPointForPosition)
    {
		x += m_obAnchorPointInPoints.x;
		y += m_obAnchorPointInPoints.y;
	}
	
	// Make matrix
	float radians = m_pB2Body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);
	
	// Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
	if (!m_obAnchorPointInPoints.equals(CCPointZero))
    {
		x += ((c * -m_obAnchorPointInPoints.x * m_fScaleX) + (-s * -m_obAnchorPointInPoints.y * m_fScaleY));
		y += ((s * -m_obAnchorPointInPoints.x * m_fScaleX) + (c * -m_obAnchorPointInPoints.y * m_fScaleY));
	}
    
	// Rot, Translate Matrix
	m_sTransform = CCAffineTransformMake( c * m_fScaleX,	s * m_fScaleX,
									     -s * m_fScaleY,	c * m_fScaleY,
									     x,	y );
	
	return m_sTransform;
}

#endif

NS_CC_EXT_END
