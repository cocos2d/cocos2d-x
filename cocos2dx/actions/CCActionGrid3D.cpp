/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
#include "CCPointExtension.h"
#include "CCDirector.h"

#include <stdlib.h>

namespace cocos2d
{
	// implementation of CCWaves3D

	CCWaves3D* CCWaves3D::actionWithWaves(int wav, float amp, const ccGridSize& gridSize, ccTime duration)
	{
		CCWaves3D *pAction = new CCWaves3D();

		if (pAction)
		{
			if (pAction->initWithWaves(wav, amp, gridSize, duration))
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

	bool CCWaves3D::initWithWaves(int wav, float amp, const ccGridSize& gridSize, ccTime duration)
	{
		if (CCGrid3DAction::initWithSize(gridSize, duration))
		{
			m_nWaves = wav;
			m_fAmplitude = amp;
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


		pCopy->initWithWaves(m_nWaves, m_fAmplitude, m_sGridSize, m_fDuration);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCWaves3D::update(ccTime time)
	{
		int i, j;
		for (i = 0; i < m_sGridSize.x + 1; ++i)
		{
			for (j = 0; j < m_sGridSize.y + 1; ++j)
			{
				ccVertex3F v = originalVertex(ccg(i ,j));
				v.z += (sinf((CGFloat)M_PI * time * m_nWaves * 2 + (v.y+v.x) * .01f) * m_fAmplitude * m_fAmplitudeRate);
				CCLog("v.z offset is %f\n", (sinf((CGFloat)M_PI * time * m_nWaves * 2 + (v.y+v.x) * .01f) * m_fAmplitude * m_fAmplitudeRate));
				setVertex(ccg(i, j), v);
			}
		}
	}

	// implementation of CCFlipX3D

	CCFlipX3D* CCFlipX3D::actionWithDuration(ccTime duration)
	{
		CCFlipX3D *pAction = new CCFlipX3D();

		if (pAction)
		{
			if (pAction->initWithSize(ccg(1, 1), duration))
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

	bool CCFlipX3D::initWithDuration(ccTime duration)
	{
		return CCGrid3DAction::initWithSize(ccg(1, 1), duration);
	}

	bool CCFlipX3D::initWithSize(const ccGridSize& gridSize, ccTime duration)
	{
		if (gridSize.x != 1 || gridSize.y != 1)
		{
			// Grid size must be (1,1)
			CCAssert(0, "");

			return false;
		}

		return CCGrid3DAction::initWithSize(gridSize, duration);
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

	void CCFlipX3D::update(ccTime time)
	{
		CGFloat angle = (CGFloat)M_PI * time; // 180 degrees
		CGFloat mz = sinf(angle);
		angle = angle / 2.0f; // x calculates degrees from 0 to 90
		CGFloat mx = cosf(angle);

		ccVertex3F v0, v1, v, diff;

		v0 = originalVertex(ccg(1, 1));
		v1 = originalVertex(ccg(0, 0));

		CGFloat	x0 = v0.x;
		CGFloat	x1 = v1.x;
		CGFloat x;
		ccGridSize	a, b, c, d;

		if ( x0 > x1 )
		{
			// Normal Grid
			a = ccg(0,0);
			b = ccg(0,1);
			c = ccg(1,0);
			d = ccg(1,1);
			x = x0;
		}
		else
		{
			// Reversed Grid
			c = ccg(0,0);
			d = ccg(0,1);
			a = ccg(1,0);
			b = ccg(1,1);
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

	CCFlipY3D* CCFlipY3D::actionWithDuration(ccTime duration)
	{
		CCFlipY3D *pAction = new CCFlipY3D();

		if (pAction)
		{
			if (pAction->initWithSize(ccg(1, 1), duration))
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

	void CCFlipY3D::update(ccTime time)
	{
		CGFloat angle = (CGFloat)M_PI * time; // 180 degrees
		CGFloat mz = sinf( angle );
		angle = angle / 2.0f;     // x calculates degrees from 0 to 90
		CGFloat my = cosf(angle);
		
		ccVertex3F	v0, v1, v, diff;
		
		v0 = originalVertex(ccg(1, 1));
		v1 = originalVertex(ccg(0, 0));
		
		CGFloat	y0 = v0.y;
		CGFloat	y1 = v1.y;
		CGFloat y;
		ccGridSize	a, b, c, d;
		
		if (y0 > y1)
		{
			// Normal Grid
			a = ccg(0,0);
			b = ccg(0,1);
			c = ccg(1,0);
			d = ccg(1,1);
			y = y0;
		}
		else
		{
			// Reversed Grid
			b = ccg(0,0);
			a = ccg(0,1);
			d = ccg(1,0);
			c = ccg(1,1);
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

	CCLens3D* CCLens3D::actionWithPosition(const CCPoint& pos, float r, const ccGridSize& gridSize, ccTime duration)
	{
		CCLens3D *pAction = new CCLens3D();

		if (pAction)
		{
			if (pAction->initWithPosition(pos, r, gridSize, duration))
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

	bool CCLens3D::initWithPosition(const CCPoint& pos, float r, const ccGridSize& gridSize, ccTime duration)
	{
		if (CCGrid3DAction::initWithSize(gridSize, duration))
		{
			m_position = ccp(-1, -1);
            setPosition(pos);
			m_fRadius = r;
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

		pCopy->initWithPosition(m_position, m_fRadius, m_sGridSize, m_fDuration);
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

    void CCLens3D::setPosition(const CCPoint& pos)
    {
        if( ! CCPoint::CCPointEqualToPoint(pos, m_position) ) {
            m_position = pos;
            m_positionInPixels.x = pos.x * CC_CONTENT_SCALE_FACTOR();
            m_positionInPixels.y = pos.y * CC_CONTENT_SCALE_FACTOR();

            m_bDirty = true;
        }
    }

	void CCLens3D::update(ccTime time)
	{
        CC_UNUSED_PARAM(time);
		if (m_bDirty)
		{
			int i, j;
			
			for (i = 0; i < m_sGridSize.x + 1; ++i)
			{
				for (j = 0; j < m_sGridSize.y + 1; ++j)
				{
					ccVertex3F v = originalVertex(ccg(i, j));
					CCPoint vect = ccpSub(m_positionInPixels, ccp(v.x, v.y));
					CGFloat r = ccpLength(vect);
					
					if (r < m_fRadius)
					{
						r = m_fRadius - r;
						CGFloat pre_log = r / m_fRadius;
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
					
					setVertex(ccg(i, j), v);
				}
			}
			
			m_bDirty = false;
		}
	}

	// implementation of Ripple3D

	CCRipple3D* CCRipple3D::actionWithPosition(const CCPoint& pos, float r, int wav, float amp, const ccGridSize& gridSize, ccTime duration)
	{
		CCRipple3D *pAction = new CCRipple3D();

		if (pAction)
		{
			if (pAction->initWithPosition(pos, r, wav, amp, gridSize, duration))
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

	bool CCRipple3D::initWithPosition(const CCPoint& pos, float r, int wav, float amp, const ccGridSize& gridSize, ccTime duration)
	{
		if (CCGrid3DAction::initWithSize(gridSize, duration))
		{
			setPosition(pos);
			m_fRadius = r;
			m_nWaves = wav;
			m_fAmplitude = amp;
			m_fAmplitudeRate = 1.0f;

			return true;
		}

		return false;
	}

    void CCRipple3D::setPosition(const CCPoint& position)
    {
        m_position = position;
        m_positionInPixels.x = position.x * CC_CONTENT_SCALE_FACTOR();
        m_positionInPixels.y = position.y * CC_CONTENT_SCALE_FACTOR();
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

		pCopy->initWithPosition(m_position, m_fRadius, m_nWaves, m_fAmplitude, m_sGridSize, m_fDuration);
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCRipple3D::update(ccTime time)
	{
		int i, j;
	
		for (i = 0; i < (m_sGridSize.x+1); ++i)
		{
			for (j = 0; j < (m_sGridSize.y+1); ++j)
			{
				ccVertex3F v = originalVertex(ccg(i, j));
				CCPoint vect = ccpSub(m_positionInPixels, ccp(v.x,v.y));
				CGFloat r = ccpLength(vect);
				
				if (r < m_fRadius)
				{
					r = m_fRadius - r;
					CGFloat rate = powf(r / m_fRadius, 2);
					v.z += (sinf( time*(CGFloat)M_PI * m_nWaves * 2 + r * 0.1f) * m_fAmplitude * m_fAmplitudeRate * rate);
				}
				
				setVertex(ccg(i, j), v);
			}
		}
	}

	// implementation of Shaky3D

	CCShaky3D* CCShaky3D::actionWithRange(int range, bool shakeZ, const ccGridSize& gridSize, ccTime duration)
	{
		CCShaky3D *pAction = new CCShaky3D();

		if (pAction)
		{
			if (pAction->initWithRange(range, shakeZ, gridSize, duration))
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

	bool CCShaky3D::initWithRange(int range, bool shakeZ, const ccGridSize& gridSize, ccTime duration)
	{
		if (CCGrid3DAction::initWithSize(gridSize, duration))
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

		pCopy->initWithRange(m_nRandrange, m_bShakeZ, m_sGridSize, m_fDuration);
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCShaky3D::update(ccTime time)
	{
        CC_UNUSED_PARAM(time);
		int i, j;
	
		for (i = 0; i < (m_sGridSize.x+1); ++i)
		{
			for (j = 0; j < (m_sGridSize.y+1); ++j)
			{
				ccVertex3F v = originalVertex(ccg(i ,j));
				v.x += (rand() % (m_nRandrange*2)) - m_nRandrange;
				v.y += (rand() % (m_nRandrange*2)) - m_nRandrange;
				if (m_bShakeZ)
				{
					v.z += (rand() % (m_nRandrange*2)) - m_nRandrange;
				}
				
				setVertex(ccg(i, j), v);
			}
		}
	}

	// implementation of Liquid

	CCLiquid* CCLiquid::actionWithWaves(int wav, float amp, const ccGridSize& gridSize, ccTime duration)
	{
		CCLiquid *pAction = new CCLiquid();

		if (pAction)
		{
			if (pAction->initWithWaves(wav, amp, gridSize, duration))
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

	bool CCLiquid::initWithWaves(int wav, float amp, const ccGridSize& gridSize, ccTime duration)
	{
		if (CCGrid3DAction::initWithSize(gridSize, duration))
		{
			m_nWaves = wav;
			m_fAmplitude = amp;
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

		pCopy->initWithWaves(m_nWaves, m_fAmplitude, m_sGridSize, m_fDuration);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCLiquid::update(ccTime time)
	{
		int i, j;

		for (i = 1; i < m_sGridSize.x; ++i)
		{
			for (j = 1; j < m_sGridSize.y; ++j)
			{
				ccVertex3F v = originalVertex(ccg(i, j));
				v.x = (v.x + (sinf(time * (CGFloat)M_PI * m_nWaves * 2 + v.x * .01f) * m_fAmplitude * m_fAmplitudeRate));
				v.y = (v.y + (sinf(time * (CGFloat)M_PI * m_nWaves * 2 + v.y * .01f) * m_fAmplitude * m_fAmplitudeRate));
				setVertex(ccg(i, j), v);
			}
		}
	}

	// implementation of Waves

	CCWaves* CCWaves::actionWithWaves(int wav, float amp, bool h, bool v, const ccGridSize& gridSize, ccTime duration)
	{
		CCWaves *pAction = new CCWaves();

		if (pAction)
		{
			if (pAction->initWithWaves(wav, amp, h, v, gridSize, duration))
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

	bool CCWaves::initWithWaves(int wav, float amp, bool h, bool v, const ccGridSize& gridSize, ccTime duration)
	{
		if (CCGrid3DAction::initWithSize(gridSize, duration))
		{
			m_nWaves = wav;
			m_fAmplitude = amp;
			m_fAmplitudeRate = 1.0f;
			m_bHorizontal = h;
			m_bVertical = v;

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

		pCopy->initWithWaves(m_nWaves, m_fAmplitude, m_bHorizontal, m_bVertical, m_sGridSize, m_fDuration);
		
		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCWaves::update(ccTime time)
	{
		int i, j;

		for (i = 0; i < m_sGridSize.x + 1; ++i)
		{
			for (j = 0; j < m_sGridSize.y + 1; ++j)
			{
				ccVertex3F v = originalVertex(ccg(i, j));

				if (m_bVertical)
				{
					v.x = (v.x + (sinf(time * (CGFloat)M_PI * m_nWaves * 2 + v.y * .01f) * m_fAmplitude * m_fAmplitudeRate));
				}

				if (m_bHorizontal)
				{
                    v.y = (v.y + (sinf(time * (CGFloat)M_PI * m_nWaves * 2 + v.x * .01f) * m_fAmplitude * m_fAmplitudeRate));
				}

				setVertex(ccg(i, j), v);
			}
		}
	}

	// implementation of Twirl

	CCTwirl* CCTwirl::actionWithPosition(CCPoint pos, int t, float amp, const ccGridSize& gridSize, ccTime duration)
	{
		CCTwirl *pAction = new CCTwirl();

		if (pAction)
		{
			if (pAction->initWithPosition(pos, t, amp, gridSize, duration))
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

	bool CCTwirl::initWithPosition(const CCPoint& pos, int t, float amp, const ccGridSize& gridSize, ccTime duration)
	{
		if (CCGrid3DAction::initWithSize(gridSize, duration))
		{
			setPosition(pos);
			m_nTwirls = t;
			m_fAmplitude = amp;
			m_fAmplitudeRate = 1.0f;

			return true;
		}

		return false;
	}

    void CCTwirl::setPosition(const CCPoint& position)
    {
        m_position = position;
        m_positionInPixels.x = position.x * CC_CONTENT_SCALE_FACTOR();
        m_positionInPixels.y = position.y * CC_CONTENT_SCALE_FACTOR();
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


		pCopy->initWithPosition(m_position, m_nTwirls, m_fAmplitude, m_sGridSize, m_fDuration);

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCTwirl::update(ccTime time)
	{
		int i, j;
		CCPoint	c = m_positionInPixels;
		
		for (i = 0; i < (m_sGridSize.x+1); ++i)
		{
			for (j = 0; j < (m_sGridSize.y+1); ++j)
			{
				ccVertex3F v = originalVertex(ccg(i ,j));
				
				CCPoint	avg = ccp(i-(m_sGridSize.x/2.0f), j-(m_sGridSize.y/2.0f));
				CGFloat r = ccpLength(avg);
				
				CGFloat amp = 0.1f * m_fAmplitude * m_fAmplitudeRate;
				CGFloat a = r * cosf( (CGFloat)M_PI/2.0f + time * (CGFloat)M_PI * m_nTwirls * 2 ) * amp;
				
				CCPoint	d;
				
				d.x = sinf(a) * (v.y-c.y) + cosf(a) * (v.x-c.x);
				d.y = cosf(a) * (v.y-c.y) - sinf(a) * (v.x-c.x);
				
				v.x = c.x + d.x;
				v.y = c.y + d.y;

				setVertex(ccg(i ,j), v);
			}
		}
	}

} // end of namespace cocos2d
