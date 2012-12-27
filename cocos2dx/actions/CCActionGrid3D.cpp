/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      On-Core
 
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
#include "CCActionGrid3D.h"
#include "support/CCPointExtension.h"
#include "CCDirector.h"
#include "cocoa/CCZone.h"
#include <stdlib.h>

NS_CC_BEGIN
// implementation of CCWaves3D

CCWaves3D* CCWaves3D::create(float duration, const CCSize& gridSize, unsigned int waves, float amplitude)
{
    CCWaves3D *pAction = new CCWaves3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, waves, amplitude))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;    
}

bool CCWaves3D::initWithDuration(float duration, const CCSize& gridSize, unsigned int waves, float amplitude)
{
    if (CCGrid3DAction::initWithDuration(duration, gridSize))
    {
        m_nWaves = waves;
        m_fAmplitude = amplitude;
        m_fAmplitudeRate = 1.0f;

        return true;
    }

    return false;
}

CCObject* CCWaves3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCWaves3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCWaves3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCWaves3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCGrid3DAction::copyWithZone(pZone);


    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nWaves, m_fAmplitude);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCWaves3D::update(float time)
{
    int i, j;
    for (i = 0; i < m_sGridSize.width + 1; ++i)
    {
        for (j = 0; j < m_sGridSize.height + 1; ++j)
        {
            ccVertex3F v = originalVertex(ccp(i ,j));
            v.z += (sinf((float)M_PI * time * m_nWaves * 2 + (v.y+v.x) * 0.01f) * m_fAmplitude * m_fAmplitudeRate);
            //CCLOG("v.z offset is %f\n", (sinf((float)M_PI * time * m_nWaves * 2 + (v.y+v.x) * .01f) * m_fAmplitude * m_fAmplitudeRate));
            setVertex(ccp(i, j), v);
        }
    }
}

// implementation of CCFlipX3D

CCFlipX3D* CCFlipX3D::create(float duration)
{
    CCFlipX3D *pAction = new CCFlipX3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool CCFlipX3D::initWithDuration(float duration)
{
    return CCGrid3DAction::initWithDuration(duration, CCSizeMake(1, 1));
}

bool CCFlipX3D::initWithSize(const CCSize& gridSize, float duration)
{
    if (gridSize.width != 1 || gridSize.height != 1)
    {
        // Grid size must be (1,1)
        CCAssert(0, "Grid size must be (1,1)");

        return false;
    }

    return CCGrid3DAction::initWithDuration(duration, gridSize);
}

CCObject* CCFlipX3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCFlipX3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCFlipX3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCFlipX3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCGrid3DAction::copyWithZone(pZone);

    pCopy->initWithSize(m_sGridSize, m_fDuration);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCFlipX3D::update(float time)
{
    float angle = (float)M_PI * time; // 180 degrees
    float mz = sinf(angle);
    angle = angle / 2.0f; // x calculates degrees from 0 to 90
    float mx = cosf(angle);

    ccVertex3F v0, v1, v, diff;

    v0 = originalVertex(ccp(1, 1));
    v1 = originalVertex(ccp(0, 0));

    float    x0 = v0.x;
    float    x1 = v1.x;
    float x;
    CCPoint    a, b, c, d;

    if ( x0 > x1 )
    {
        // Normal Grid
        a = ccp(0,0);
        b = ccp(0,1);
        c = ccp(1,0);
        d = ccp(1,1);
        x = x0;
    }
    else
    {
        // Reversed Grid
        c = ccp(0,0);
        d = ccp(0,1);
        a = ccp(1,0);
        b = ccp(1,1);
        x = x1;
    }
    
    diff.x = ( x - x * mx );
    diff.z = fabsf( floorf( (x * mz) / 4.0f ) );

    // bottom-left
    v = originalVertex(a);
    v.x = diff.x;
    v.z += diff.z;
    setVertex(a, v);
    
    // upper-left
    v = originalVertex(b);
    v.x = diff.x;
    v.z += diff.z;
    setVertex(b, v);
    
    // bottom-right
    v = originalVertex(c);
    v.x -= diff.x;
    v.z -= diff.z;
    setVertex(c, v);
    
    // upper-right
    v = originalVertex(d);
    v.x -= diff.x;
    v.z -= diff.z;
    setVertex(d, v);
}

// implementation of FlipY3D

CCFlipY3D* CCFlipY3D::create(float duration)
{
    CCFlipY3D *pAction = new CCFlipY3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

CCObject* CCFlipY3D::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCFlipY3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCFlipY3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCFlipY3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCFlipX3D::copyWithZone(pZone);

    pCopy->initWithSize(m_sGridSize, m_fDuration);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCFlipY3D::update(float time)
{
    float angle = (float)M_PI * time; // 180 degrees
    float mz = sinf( angle );
    angle = angle / 2.0f;     // x calculates degrees from 0 to 90
    float my = cosf(angle);
    
    ccVertex3F    v0, v1, v, diff;
    
    v0 = originalVertex(ccp(1, 1));
    v1 = originalVertex(ccp(0, 0));
    
    float    y0 = v0.y;
    float    y1 = v1.y;
    float y;
    CCPoint    a, b, c, d;
    
    if (y0 > y1)
    {
        // Normal Grid
        a = ccp(0,0);
        b = ccp(0,1);
        c = ccp(1,0);
        d = ccp(1,1);
        y = y0;
    }
    else
    {
        // Reversed Grid
        b = ccp(0,0);
        a = ccp(0,1);
        d = ccp(1,0);
        c = ccp(1,1);
        y = y1;
    }
    
    diff.y = y - y * my;
    diff.z = fabsf(floorf((y * mz) / 4.0f));
    
    // bottom-left
    v = originalVertex(a);
    v.y = diff.y;
    v.z += diff.z;
    setVertex(a, v);
    
    // upper-left
    v = originalVertex(b);
    v.y -= diff.y;
    v.z -= diff.z;
    setVertex(b, v);
    
    // bottom-right
    v = originalVertex(c);
    v.y = diff.y;
    v.z += diff.z;
    setVertex(c, v);
    
    // upper-right
    v = originalVertex(d);
    v.y -= diff.y;
    v.z -= diff.z;
    setVertex(d, v);
}


// implementation of Lens3D

CCLens3D* CCLens3D::create(float duration, const CCSize& gridSize, const CCPoint& position, float radius)
{
    CCLens3D *pAction = new CCLens3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, position, radius))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool CCLens3D::initWithDuration(float duration, const CCSize& gridSize, const CCPoint& position, float radius)
{
    if (CCGrid3DAction::initWithDuration(duration, gridSize))
    {
        m_position = ccp(-1, -1);
        setPosition(position);
        m_fRadius = radius;
        m_fLensEffect = 0.7f;
        m_bDirty = true;

        return true;
    }

    return false;
}

CCObject* CCLens3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCLens3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCLens3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCLens3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_position, m_fRadius);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCLens3D::setPosition(const CCPoint& pos)
{
    if( !pos.equals(m_position))
    {
        m_position = pos;
        m_bDirty = true;
    }
}

void CCLens3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    if (m_bDirty)
    {
        int i, j;
        
        for (i = 0; i < m_sGridSize.width + 1; ++i)
        {
            for (j = 0; j < m_sGridSize.height + 1; ++j)
            {
                ccVertex3F v = originalVertex(ccp(i, j));
                CCPoint vect = ccpSub(m_position, ccp(v.x, v.y));
                float r = ccpLength(vect);
                
                if (r < m_fRadius)
                {
                    r = m_fRadius - r;
                    float pre_log = r / m_fRadius;
                    if ( pre_log == 0 ) 
                    {
                        pre_log = 0.001f;
                    }

                    float l = logf(pre_log) * m_fLensEffect;
                    float new_r = expf( l ) * m_fRadius;
                    
                    if (ccpLength(vect) > 0)
                    {
                        vect = ccpNormalize(vect);
                        CCPoint new_vect = ccpMult(vect, new_r);
                        v.z += ccpLength(new_vect) * m_fLensEffect;
                    }
                }
                
                setVertex(ccp(i, j), v);
            }
        }
        
        m_bDirty = false;
    }
}

// implementation of Ripple3D

CCRipple3D* CCRipple3D::create(float duration, const CCSize& gridSize, const CCPoint& position, float radius, unsigned int waves, float amplitude)
{
    CCRipple3D *pAction = new CCRipple3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, position, radius, waves, amplitude))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool CCRipple3D::initWithDuration(float duration, const CCSize& gridSize, const CCPoint& position, float radius, unsigned int waves, float amplitude)
{
    if (CCGrid3DAction::initWithDuration(duration, gridSize))
    {
        setPosition(position);
        m_fRadius = radius;
        m_nWaves = waves;
        m_fAmplitude = amplitude;
        m_fAmplitudeRate = 1.0f;

        return true;
    }

    return false;
}

void CCRipple3D::setPosition(const CCPoint& position)
{
    m_position = position;
}

CCObject* CCRipple3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCRipple3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCRipple3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCRipple3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_position, m_fRadius, m_nWaves, m_fAmplitude);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCRipple3D::update(float time)
{
    int i, j;

    for (i = 0; i < (m_sGridSize.width+1); ++i)
    {
        for (j = 0; j < (m_sGridSize.height+1); ++j)
        {
            ccVertex3F v = originalVertex(ccp(i, j));
            CCPoint vect = ccpSub(m_position, ccp(v.x,v.y));
            float r = ccpLength(vect);
            
            if (r < m_fRadius)
            {
                r = m_fRadius - r;
                float rate = powf(r / m_fRadius, 2);
                v.z += (sinf( time*(float)M_PI * m_nWaves * 2 + r * 0.1f) * m_fAmplitude * m_fAmplitudeRate * rate);
            }
            
            setVertex(ccp(i, j), v);
        }
    }
}

// implementation of Shaky3D

CCShaky3D* CCShaky3D::create(float duration, const CCSize& gridSize, int range, bool shakeZ)
{
    CCShaky3D *pAction = new CCShaky3D();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, range, shakeZ))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool CCShaky3D::initWithDuration(float duration, const CCSize& gridSize, int range, bool shakeZ)
{
    if (CCGrid3DAction::initWithDuration(duration, gridSize))
    {
        m_nRandrange = range;
        m_bShakeZ = shakeZ;

        return true;
    }

    return false;
}

CCObject* CCShaky3D::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCShaky3D* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCShaky3D*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCShaky3D();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nRandrange, m_bShakeZ);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCShaky3D::update(float time)
{
    CC_UNUSED_PARAM(time);
    int i, j;

    for (i = 0; i < (m_sGridSize.width+1); ++i)
    {
        for (j = 0; j < (m_sGridSize.height+1); ++j)
        {
            ccVertex3F v = originalVertex(ccp(i ,j));
            v.x += (rand() % (m_nRandrange*2)) - m_nRandrange;
            v.y += (rand() % (m_nRandrange*2)) - m_nRandrange;
            if (m_bShakeZ)
            {
                v.z += (rand() % (m_nRandrange*2)) - m_nRandrange;
            }
            
            setVertex(ccp(i, j), v);
        }
    }
}

// implementation of Liquid

CCLiquid* CCLiquid::create(float duration, const CCSize& gridSize, unsigned int waves, float amplitude)
{
    CCLiquid *pAction = new CCLiquid();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, waves, amplitude))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool CCLiquid::initWithDuration(float duration, const CCSize& gridSize, unsigned int waves, float amplitude)
{
    if (CCGrid3DAction::initWithDuration(duration, gridSize))
    {
        m_nWaves = waves;
        m_fAmplitude = amplitude;
        m_fAmplitudeRate = 1.0f;

        return true;
    }

    return false;
}

CCObject* CCLiquid::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCLiquid* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCLiquid*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCLiquid();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nWaves, m_fAmplitude);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCLiquid::update(float time)
{
    int i, j;

    for (i = 1; i < m_sGridSize.width; ++i)
    {
        for (j = 1; j < m_sGridSize.height; ++j)
        {
            ccVertex3F v = originalVertex(ccp(i, j));
            v.x = (v.x + (sinf(time * (float)M_PI * m_nWaves * 2 + v.x * .01f) * m_fAmplitude * m_fAmplitudeRate));
            v.y = (v.y + (sinf(time * (float)M_PI * m_nWaves * 2 + v.y * .01f) * m_fAmplitude * m_fAmplitudeRate));
            setVertex(ccp(i, j), v);
        }
    }
}

// implementation of Waves

CCWaves* CCWaves::create(float duration, const CCSize& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical)
{
    CCWaves *pAction = new CCWaves();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, waves, amplitude, horizontal, vertical))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool CCWaves::initWithDuration(float duration, const CCSize& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical)
{
    if (CCGrid3DAction::initWithDuration(duration, gridSize))
    {
        m_nWaves = waves;
        m_fAmplitude = amplitude;
        m_fAmplitudeRate = 1.0f;
        m_bHorizontal = horizontal;
        m_bVertical = vertical;

        return true;
    }

    return false;
}

CCObject* CCWaves::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCWaves* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCWaves*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCWaves();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCGrid3DAction::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_nWaves, m_fAmplitude, m_bHorizontal, m_bVertical);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCWaves::update(float time)
{
    int i, j;

    for (i = 0; i < m_sGridSize.width + 1; ++i)
    {
        for (j = 0; j < m_sGridSize.height + 1; ++j)
        {
            ccVertex3F v = originalVertex(ccp(i, j));

            if (m_bVertical)
            {
                v.x = (v.x + (sinf(time * (float)M_PI * m_nWaves * 2 + v.y * .01f) * m_fAmplitude * m_fAmplitudeRate));
            }

            if (m_bHorizontal)
            {
                v.y = (v.y + (sinf(time * (float)M_PI * m_nWaves * 2 + v.x * .01f) * m_fAmplitude * m_fAmplitudeRate));
            }

            setVertex(ccp(i, j), v);
        }
    }
}

// implementation of Twirl

CCTwirl* CCTwirl::create(float duration, const CCSize& gridSize, CCPoint position, unsigned int twirls, float amplitude)
{
    CCTwirl *pAction = new CCTwirl();

    if (pAction)
    {
        if (pAction->initWithDuration(duration, gridSize, position, twirls, amplitude))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }

    return pAction;
}

bool CCTwirl::initWithDuration(float duration, const CCSize& gridSize, CCPoint position, unsigned int twirls, float amplitude)
{
    if (CCGrid3DAction::initWithDuration(duration, gridSize))
    {
        setPosition(position);
        m_nTwirls = twirls;
        m_fAmplitude = amplitude;
        m_fAmplitudeRate = 1.0f;

        return true;
    }

    return false;
}

void CCTwirl::setPosition(const CCPoint& position)
{
    m_position = position;
}

CCObject* CCTwirl::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCTwirl* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCTwirl*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCTwirl();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCGrid3DAction::copyWithZone(pZone);


    pCopy->initWithDuration(m_fDuration, m_sGridSize, m_position, m_nTwirls, m_fAmplitude);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCTwirl::update(float time)
{
    int i, j;
    CCPoint    c = m_position;
    
    for (i = 0; i < (m_sGridSize.width+1); ++i)
    {
        for (j = 0; j < (m_sGridSize.height+1); ++j)
        {
            ccVertex3F v = originalVertex(ccp(i ,j));
            
            CCPoint    avg = ccp(i-(m_sGridSize.width/2.0f), j-(m_sGridSize.height/2.0f));
            float r = ccpLength(avg);
            
            float amp = 0.1f * m_fAmplitude * m_fAmplitudeRate;
            float a = r * cosf( (float)M_PI/2.0f + time * (float)M_PI * m_nTwirls * 2 ) * amp;
            
            CCPoint d = ccp(
                sinf(a) * (v.y-c.y) + cosf(a) * (v.x-c.x),
                cosf(a) * (v.y-c.y) - sinf(a) * (v.x-c.x));
            
            v.x = c.x + d.x;
            v.y = c.y + d.y;

            setVertex(ccp(i ,j), v);
        }
    }
}

NS_CC_END

