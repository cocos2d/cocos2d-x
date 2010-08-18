/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCGrid3DAction.h"
#include "support/CGPointExtension.h"

namespace cocos2d
{
	// implementation of CCWaves3D

	CCWaves3D* CCWaves3D::actionWithWaves(int wav, float amp, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
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
				CCX_SAFE_RELEASE(pAction);
			}
		}

		return pAction;	
	}

	bool CCWaves3D::initWithWaves(int wav, float amp, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		if (__super::initWithSize(gridSize, duration))
		{
			m_nWaves = wav;
			m_fAmplitude = amp;
			m_fAmplitudeRate = 1.0f;

			return true;
		}

		return false;
	}

	NSObject* CCWaves3D::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCWaves3D* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCWaves3D*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCWaves3D();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);


		pCopy->initWithWaves(m_nWaves, m_fAmplitude, m_sGridSize, m_fDuration);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCWaves3D::update(cocos2d::ccTime time)
	{
		int i, j;

		for (i = 0; i < m_sGridSize.x + 1; ++i)
		{
			for (j = 0; j < m_sGridSize.y + 1; ++j)
			{
				ccVertex3F v = originalVertex(ccg(i ,j));
				v.z += (sinf((CGFloat)M_PI * time * m_nWaves * 2 + (v.y+v.x) * .01f) * m_fAmplitude * m_fAmplitudeRate);
				setVertex(ccg(i, j), v);
			}
		}
	}

	// implementation of CCFlipX3D

	CCFlipX3D* CCFlipX3D::actionWithDuration(cocos2d::ccTime duration)
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
				CCX_SAFE_RELEASE(pAction);
			}
		}

		return pAction;
	}

	bool CCFlipX3D::initWithDuration(cocos2d::ccTime duration)
	{
		return __super::initWithSize(ccg(1, 1), duration);
	}

	bool CCFlipX3D::initWithSize(cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		if (gridSize.x != 1 || gridSize.y != 1)
		{
			// Grid size must be (1,1)
			assert(0);

			return false;
		}

		return __super::initWithSize(gridSize, duration);
	}

	NSObject* CCFlipX3D::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCFlipX3D* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCFlipX3D*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCFlipX3D();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);

		pCopy->initWithSize(m_sGridSize, m_fDuration);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCFlipX3D::update(cocos2d::ccTime time)
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
				CCX_SAFE_RELEASE(pAction);
			}
		}

		return pAction;
	}

	NSObject* CCFlipY3D::copyWithZone(NSZone* pZone)
	{
		NSZone* pNewZone = NULL;
		CCFlipY3D* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCFlipY3D*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCFlipY3D();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);

		pCopy->initWithSize(m_sGridSize, m_fDuration);

		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCFlipY3D::update(cocos2d::ccTime time)
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

	CCLens3D* CCLens3D::actionWithPosition(cocos2d::CGPoint pos, float r, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
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
				CCX_SAFE_RELEASE(pAction);
			}
		}

		return pAction;
	}

	bool CCLens3D::initWithPosition(cocos2d::CGPoint pos, float r, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		if (__super::initWithSize(gridSize, duration))
		{
			m_position = pos;
			m_fRadius = r;
			m_fLensEffect = 0.7f;
			m_lastPosition = ccp(-1, -1);

			return true;
		}

		return false;
	}

	NSObject* CCLens3D::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCLens3D* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCLens3D*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCLens3D();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);


		pCopy->initWithPosition(m_position, m_fRadius, m_sGridSize, m_fDuration);
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCLens3D::update(cocos2d::ccTime time)
	{
		if (m_position.x != m_lastPosition.x || m_position.y != m_lastPosition.y )
		{
			int i, j;
			
			for (i = 0; i < m_sGridSize.x + 1; ++i)
			{
				for (j = 0; j < m_sGridSize.y + 1; ++j)
				{
					ccVertex3F v = originalVertex(ccg(i, j));
					CGPoint vect = ccpSub(m_position, ccp(v.x, v.y));
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
							CGPoint new_vect = ccpMult(vect, new_r);
							v.z += ccpLength(new_vect) * m_fLensEffect;
						}
					}
					
					setVertex(ccg(i, j), v);
				}
			}
			
			m_lastPosition = m_position;
		}
	}

	// implementation of Ripple3D

	CCRipple3D* CCRipple3D::actionWithPosition(cocos2d::CGPoint pos, float r, int wav, float amp, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
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
				CCX_SAFE_RELEASE(pAction);
			}
		}

		return pAction;
	}

	bool CCRipple3D::initWithPosition(cocos2d::CGPoint pos, float r, int wav, float amp, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		if (__super::initWithSize(gridSize, duration))
		{
			m_position = pos;
			m_fRadius = r;
			m_nWaves = wav;
			m_fAmplitude = amp;
			m_fAmplitudeRate = 1.0f;

			return true;
		}

		return false;
	}

	NSObject* CCRipple3D::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCRipple3D* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject)
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCRipple3D*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCRipple3D();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);


		pCopy->initWithPosition(m_position, m_fRadius, m_nWaves, m_fAmplitude, m_sGridSize, m_fDuration);
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCRipple3D::update(cocos2d::ccTime time)
	{
		int i, j;
	
		for (i = 0; i < (m_sGridSize.x+1); ++i)
		{
			for (j = 0; j < (m_sGridSize.y+1); ++j)
			{
				ccVertex3F v = originalVertex(ccg(i, j));
				CGPoint vect = ccpSub(m_position, ccp(v.x,v.y));
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

	CCShaky3D* CCShaky3D::actionWithRange(int range, bool shakeZ, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
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
				CCX_SAFE_RELEASE(pAction);
			}
		}

		return pAction;
	}

	bool CCShaky3D::initWithRange(int range, bool shakeZ, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		if (__super::initWithSize(gridSize, duration))
		{
			m_nRandrange = range;
			m_bShakeZ = shakeZ;

			return true;
		}

		return false;
	}

	NSObject* CCShaky3D::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCShaky3D* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject)
		{
			//in case of being called at sub class
			pCopy = dynamic_cast<CCShaky3D*>(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new CCShaky3D();
			pZone = pNewZone = new NSZone(pCopy);
		}

		__super::copyWithZone(pZone);

		pCopy->initWithRange(m_nRandrange, m_bShakeZ, m_sGridSize, m_fDuration);
		
		CCX_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void CCShaky3D::update(cocos2d::ccTime time)
	{
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

	CCLiquid* CCLiquid::actionWithWaves(int wav, float amp, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
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
				CCX_SAFE_RELEASE(pAction);
			}
		}

		return pAction;
	}

	bool CCLiquid::initWithWaves(int wav, float amp, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		if (__super::initWithSize(gridSize, duration))
		{
			m_nWaves = wav;
			m_fAmplitude = amp;
			m_fAmplitudeRate = 1.0f;

			return true;
		}

		return false;
	}

	NSObject* CCLiquid::copyWithZone(cocos2d::NSZone *pZone)
	{
		return NULL;
	}

	void CCLiquid::update(cocos2d::ccTime time)
	{
	}

	// implementation of Waves

	CCWaves* CCWaves::actionWithWaves(int wav, float amp, bool h, bool v, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		return NULL;
	}

	bool CCWaves::initWithWaves(int wav, float amp, bool h, bool v, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		return false;
	}

	NSObject* CCWaves::copyWithZone(cocos2d::NSZone *pZone)
	{
		return NULL;
	}

	void CCWaves::update(cocos2d::ccTime time)
	{
	}

	// implementation of Twirl

	CCTwirl* CCTwirl::actionWithPosition(cocos2d::CGPoint pos, int t, float amp, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		return NULL;
	}

	bool CCTwirl::initWithPosition(cocos2d::CGPoint pos, int t, float amp, cocos2d::ccGridSize gridSize, cocos2d::ccTime duration)
	{
		return false;
	}

	NSObject* CCTwirl::copyWithZone(cocos2d::NSZone *pZone)
	{
		return NULL;
	}

	void CCTwirl::update(cocos2d::ccTime time)
	{
	}

} // end of namespace cocos2d
