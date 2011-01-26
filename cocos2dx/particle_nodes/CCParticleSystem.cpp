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
#include "CCParticleSystem.h"
#include "ccTypes.h"
#include "CCTextureCache.h"
#include "support/base64.h"
#include "CGPointExtension.h"
#include "CCXFileUtils.h"
#include "CCXUIImage.h"
#include "platform/platform.h"
#include "support/zip_support/ZipUtils.h"

// opengl
#include "platform/CCGL.h"

#if CC_ENABLE_PROFILERS
#include "Support/CCProfiling.h"
#endif

namespace cocos2d {

// ideas taken from:
//	 . The ocean spray in your face [Jeff Lander]
//		http://www.double.co.nz/dust/col0798.pdf
//	 . Building an Advanced Particle System [John van der Burg]
//		http://www.gamasutra.com/features/20000623/vanderburg_01.htm
//   . LOVE game engine
//		http://love2d.org/
//
//
// Radius mode support, from 71 squared
//		http://particledesigner.71squared.com/
//
// IMPORTANT: Particle Designer is supported by cocos2d, but
// 'Radius Mode' in Particle Designer uses a fixed emit rate of 30 hz. Since that can't be guarateed in cocos2d,
//  cocos2d uses a another approach, but the results are almost identical. 
//

CCParticleSystem::CCParticleSystem()
	:m_sPlistFile("")
	,m_fElapsed(0)
	,m_pParticles(NULL)
	,m_fEmitCounter(0)
	,m_nParticleIdx(0)
#if CC_ENABLE_PROFILERS
	,m_pProfilingTimer(NULL)
#endif
	,m_bIsActive(true)
	,m_nParticleCount(0)
	,m_fDuration(0)
	,m_tSourcePosition(CGPointZero)
	,m_tPosVar(CGPointZero)
	,m_fLife(0)
	,m_fLifeVar(0)
	,m_fAngle(0)
	,m_fAngleVar(0)
	,m_fStartSize(0)
	,m_fStartSizeVar(0)
	,m_fEndSize(0)
	,m_fEndSizeVar(0)
	,m_fStartSpin(0)
	,m_fStartSpinVar(0)
	,m_fEndSpin(0)
	,m_fEndSpinVar(0)
	,m_fEmissionRate(0)
	,m_nTotalParticles(0)
	,m_pTexture(NULL)
	,m_bIsBlendAdditive(false)
	,m_ePositionType(kCCPositionTypeFree)
	,m_bIsAutoRemoveOnFinish(false)
	,m_nEmitterMode(kCCParticleModeGravity)
{
	modeA.gravity = CGPointZero;
	modeA.speed = 0;
	modeA.speedVar = 0;
	modeA.tangentialAccel = 0;
	modeA.tangentialAccelVar = 0;
	modeA.radialAccel = 0;
	modeA.radialAccelVar = 0;
	modeB.startRadius = 0;
	modeB.startRadiusVar = 0;
	modeB.endRadius = 0;
	modeB.endRadiusVar = 0;			
	modeB.rotatePerSecond = 0;
	modeB.rotatePerSecondVar = 0;
	m_tBlendFunc.src = CC_BLEND_SRC;
	m_tBlendFunc.dst = CC_BLEND_DST;
}
// implementation CCParticleSystem
CCParticleSystem * CCParticleSystem::particleWithFile(const char *plistFile)
{
	CCParticleSystem *pRet = new CCParticleSystem();
	if (pRet && pRet->initWithFile(plistFile))
	{
		pRet->autorelease();
		return pRet;
	}
	CCX_SAFE_DELETE(pRet)
	return pRet;
}
bool CCParticleSystem::initWithFile(const char *plistFile)
{
	m_sPlistFile = CCFileUtils::fullPathFromRelativePath(plistFile);
	NSDictionary<std::string, NSObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(m_sPlistFile.c_str());

	NSAssert( dict != NULL, "Particles: file not found");
	return this->initWithDictionary(dict);
}

bool CCParticleSystem::initWithDictionary(NSDictionary<std::string, NSObject*> *dictionary)
{
	bool bRet = false;
	unsigned char *buffer = NULL;
	unsigned char *deflated = NULL;
	UIImage *image = NULL;
	do 
	{
		int maxParticles = atoi(valueForKey("maxParticles", dictionary));
		// self, not super
		if(this->initWithTotalParticles(maxParticles))
		{
			// angle
			m_fAngle = (float)atof(valueForKey("angle", dictionary));
			m_fAngleVar = (float)atof(valueForKey("angleVariance", dictionary));

			// duration
			m_fDuration = (float)atof(valueForKey("duration", dictionary));

			// blend function 
			m_tBlendFunc.src = atoi(valueForKey("blendFuncSource", dictionary));
			m_tBlendFunc.dst = atoi(valueForKey("blendFuncDestination", dictionary));

			// color
			m_tStartColor.r = (float)atof(valueForKey("startColorRed", dictionary));
			m_tStartColor.g = (float)atof(valueForKey("startColorGreen", dictionary));
			m_tStartColor.b = (float)atof(valueForKey("startColorBlue", dictionary));
			m_tStartColor.a = (float)atof(valueForKey("startColorAlpha", dictionary));

			m_tStartColorVar.r = (float)atof(valueForKey("startColorVarianceRed", dictionary));
			m_tStartColorVar.g = (float)atof(valueForKey("startColorVarianceGreen", dictionary));
			m_tStartColorVar.b = (float)atof(valueForKey("startColorVarianceBlue", dictionary));
			m_tStartColorVar.a = (float)atof(valueForKey("startColorVarianceAlpha", dictionary));

			m_tEndColor.r = (float)atof(valueForKey("finishColorRed", dictionary));
			m_tEndColor.g = (float)atof(valueForKey("finishColorGreen", dictionary));
			m_tEndColor.b = (float)atof(valueForKey("finishColorBlue", dictionary));
			m_tEndColor.a = (float)atof(valueForKey("finishColorAlpha", dictionary));

			m_tEndColorVar.r = (float)atof(valueForKey("finishColorVarianceRed", dictionary));
			m_tEndColorVar.g = (float)atof(valueForKey("finishColorVarianceGreen", dictionary));
			m_tEndColorVar.b = (float)atof(valueForKey("finishColorVarianceBlue", dictionary));
			m_tEndColorVar.a = (float)atof(valueForKey("finishColorVarianceAlpha", dictionary));

			// particle size
			m_fStartSize = (float)atof(valueForKey("startParticleSize", dictionary));
			m_fStartSizeVar = (float)atof(valueForKey("startParticleSizeVariance", dictionary));
			m_fEndSize = (float)atof(valueForKey("finishParticleSize", dictionary));
			m_fEndSizeVar = (float)atof(valueForKey("finishParticleSizeVariance", dictionary));

			// position
			m_tPosition.x = (float)atof(valueForKey("sourcePositionx", dictionary));
			m_tPosition.y = (float)atof(valueForKey("sourcePositiony", dictionary));
			m_tPosVar.x = (float)atof(valueForKey("sourcePositionVariancex", dictionary));
			m_tPosVar.y = (float)atof(valueForKey("sourcePositionVariancey", dictionary));

			m_nEmitterMode = atoi(valueForKey("emitterType", dictionary));

			// Mode A: Gravity + tangential accel + radial accel
			if( m_nEmitterMode == kCCParticleModeGravity ) 
			{
				// gravity
				modeA.gravity.x = (float)atof(valueForKey("gravityx", dictionary));
				modeA.gravity.y = (float)atof(valueForKey("gravityy", dictionary));

				// speed
				modeA.speed = (float)atof(valueForKey("speed", dictionary));
				modeA.speedVar = (float)atof(valueForKey("speedVariance", dictionary));

                const char * pszTmp = NULL;
				// radial acceleration
                pszTmp = valueForKey("radialAcceleration", dictionary);
                modeA.radialAccel = (pszTmp) ? (float)atof(pszTmp) : 0;

                pszTmp = valueForKey("radialAccelVariance", dictionary);
				modeA.radialAccelVar = (pszTmp) ? (float)atof(pszTmp) : 0;

				// tangential acceleration
                pszTmp = valueForKey("tangentialAcceleration", dictionary);
				modeA.tangentialAccel = (pszTmp) ? (float)atof(pszTmp) : 0;

                pszTmp = valueForKey("tangentialAccelVariance", dictionary);
				modeA.tangentialAccelVar = (pszTmp) ? (float)atof(pszTmp) : 0;
			}

			// or Mode B: radius movement
			else if( m_nEmitterMode == kCCParticleModeRadius ) 
			{
				modeB.startRadius = (float)atof(valueForKey("maxRadius", dictionary));
				modeB.startRadiusVar = (float)atof(valueForKey("maxRadiusVariance", dictionary));
				modeB.endRadius = (float)atof(valueForKey("minRadius", dictionary));
				modeB.endRadiusVar = 0;
				modeB.rotatePerSecond = (float)atof(valueForKey("rotatePerSecond", dictionary));
				modeB.rotatePerSecondVar = (float)atof(valueForKey("rotatePerSecondVariance", dictionary));

			} else {
				NSAssert( false, "Invalid emitterType in config file");
				CCX_BREAK_IF(true);
			}

			// life span
			m_fLife = (float)atof(valueForKey("particleLifespan", dictionary));
			m_fLifeVar = (float)atof(valueForKey("particleLifespanVariance", dictionary));

			// emission Rate
			m_fEmissionRate = m_nTotalParticles / m_fLife;

			// texture		
			// Try to get the texture from the cache
			char *textureName = (char *)valueForKey("textureFileName", dictionary);
            std::string fullpath = CCFileUtils::fullPathFromRelativeFile(textureName, m_sPlistFile.c_str());

            if (strlen(textureName) > 0)
            {
                // set not pop-up message box when load image failed
                bool bNotify = UIImage::getIsPopupNotify();
                UIImage::setIsPopupNotify(false);
                this->m_pTexture = CCTextureCache::sharedTextureCache()->addImage(fullpath.c_str());

                // reset the value of UIImage notify
                UIImage::setIsPopupNotify(bNotify);
            }

			// if it fails, try to get it from the base64-gzipped data			
            char *textureData = NULL;
			if ( ! m_pTexture && 
                (textureData = (char *)valueForKey("textureImageData", dictionary)))
			{
				int dataLen = strlen(textureData);
				if(dataLen != 0)
				{
					int decodeLen = base64Decode((unsigned char*)textureData, dataLen, &buffer);
					NSAssert( buffer != NULL, "CCParticleSystem: error decoding textureImageData");
					CCX_BREAK_IF(!buffer);

						int deflatedLen = ZipUtils::ccInflateMemory(buffer, decodeLen, &deflated);
						NSAssert( deflated != NULL, "CCParticleSystem: error ungzipping textureImageData");
						CCX_BREAK_IF(!deflated);
						
						image = new UIImage();
						bool isOK = image->initWithData(deflated, deflatedLen);
						NSAssert(isOK, "CCParticleSystem: error init image with Data");
						CCX_BREAK_IF(!isOK);
						
						m_pTexture = CCTextureCache::sharedTextureCache()->addUIImage(image, fullpath.c_str());
				}
			}
			NSAssert( this->m_pTexture != NULL, "CCParticleSystem: error loading the texture");
			
			CCX_BREAK_IF(!m_pTexture);
			this->m_pTexture->retain();
			bRet = true;
		}
	} while (0);
	CCX_SAFE_DELETE_ARRAY(buffer);
    CCX_SAFE_DELETE_ARRAY(deflated);
	CCX_SAFE_DELETE(image);
	return bRet;
}
bool CCParticleSystem::initWithTotalParticles(int numberOfParticles)
{
	m_nTotalParticles = numberOfParticles;

    CCX_SAFE_DELETE_ARRAY(m_pParticles);
	
	m_pParticles = new tCCParticle[m_nTotalParticles];

	if( ! m_pParticles )
	{
		CCLOG("Particle system: not enough memory");
		this->release();
		return false;
	}

	// default, active
	m_bIsActive = true;

	// default blend function
	m_tBlendFunc.src = CC_BLEND_SRC;
	m_tBlendFunc.dst = CC_BLEND_DST;

	// default movement type;
	m_ePositionType = kCCPositionTypeFree;

	// by default be in mode A:
	m_nEmitterMode = kCCParticleModeGravity;

	// default: modulate
	// XXX: not used
	//	colorModulate = YES;

	m_bIsAutoRemoveOnFinish = false;

	// profiling
#if CC_ENABLE_PROFILERS
	/// @todo _profilingTimer = [[CCProfiler timerWithName:@"particle system" andInstance:self] retain];
#endif

	// Optimization: compile udpateParticle method
	//updateParticleSel = @selector(updateQuadWithParticle:newPosition:);
	//updateParticleImp = (CC_UPDATE_PARTICLE_IMP) [self methodForSelector:updateParticleSel];

	// udpate after action in run!
	this->scheduleUpdateWithPriority(1);

	return true;
}

CCParticleSystem::~CCParticleSystem()
{
    CCX_SAFE_DELETE_ARRAY(m_pParticles);
	CCX_SAFE_RELEASE(m_pTexture)
	// profiling
#if CC_ENABLE_PROFILERS
	/// @todo [CCProfiler releaseTimer:_profilingTimer];
#endif
}
bool CCParticleSystem::addParticle()
{
	if (this->isFull())
	{
		return false;
	}

	tCCParticle * particle = &m_pParticles[ m_nParticleCount ];
	this->initParticle(particle);
	++m_nParticleCount;

	return true;
}
void CCParticleSystem::initParticle(tCCParticle* particle)
{
	// timeToLive
	// no negative life. prevent division by 0
	particle->timeToLive = MAX(0, m_fLife + m_fLifeVar * CCRANDOM_MINUS1_1() );

	// position
	particle->pos.x = m_tSourcePosition.x + m_tPosVar.x * CCRANDOM_MINUS1_1();
    particle->pos.x *= CC_CONTENT_SCALE_FACTOR();
	particle->pos.y = m_tSourcePosition.y + m_tPosVar.y * CCRANDOM_MINUS1_1();
    particle->pos.y *= CC_CONTENT_SCALE_FACTOR();

	// Color
	ccColor4F start;
	start.r = MIN(1, MAX(0, m_tStartColor.r + m_tStartColorVar.r * CCRANDOM_MINUS1_1() ) );
	start.g = MIN(1, MAX(0, m_tStartColor.g + m_tStartColorVar.g * CCRANDOM_MINUS1_1() ) );
	start.b = MIN(1, MAX(0, m_tStartColor.b + m_tStartColorVar.b * CCRANDOM_MINUS1_1() ) );
	start.a = MIN(1, MAX(0, m_tStartColor.a + m_tStartColorVar.a * CCRANDOM_MINUS1_1() ) );

	ccColor4F end;
	end.r = MIN(1, MAX(0, m_tEndColor.r + m_tEndColorVar.r * CCRANDOM_MINUS1_1() ) );
	end.g = MIN(1, MAX(0, m_tEndColor.g + m_tEndColorVar.g * CCRANDOM_MINUS1_1() ) );
	end.b = MIN(1, MAX(0, m_tEndColor.b + m_tEndColorVar.b * CCRANDOM_MINUS1_1() ) );
	end.a = MIN(1, MAX(0, m_tEndColor.a + m_tEndColorVar.a * CCRANDOM_MINUS1_1() ) );

	particle->color = start;
	particle->deltaColor.r = (end.r - start.r) / particle->timeToLive;
	particle->deltaColor.g = (end.g - start.g) / particle->timeToLive;
	particle->deltaColor.b = (end.b - start.b) / particle->timeToLive;
	particle->deltaColor.a = (end.a - start.a) / particle->timeToLive;

	// size
	float startS = MAX(0, m_fStartSize + m_fStartSizeVar * CCRANDOM_MINUS1_1() ); // no negative size
    startS *= CC_CONTENT_SCALE_FACTOR();

	particle->size = startS;

	if( m_fEndSize == kCCParticleStartSizeEqualToEndSize )
	{
		particle->deltaSize = 0;
	}
	else
	{
		float endS = m_fEndSize + m_fEndSizeVar * CCRANDOM_MINUS1_1();
		endS = MAX(0, endS);
        endS *= CC_CONTENT_SCALE_FACTOR();
		particle->deltaSize = (endS - startS) / particle->timeToLive;
	}

	// rotation
	float startA = m_fStartSpin + m_fStartSpinVar * CCRANDOM_MINUS1_1();
	float endA = m_fEndSpin + m_fEndSpinVar * CCRANDOM_MINUS1_1();
	particle->rotation = startA;
	particle->deltaRotation = (endA - startA) / particle->timeToLive;

	// position
	if( m_ePositionType == kCCPositionTypeFree )
	{
        CGPoint p = this->convertToWorldSpace(CGPointZero);
		particle->startPos = ccpMult( p, CC_CONTENT_SCALE_FACTOR() );
	}
    else if ( m_ePositionType == kCCPositionTypeRelative )
    {
        particle->startPos = ccpMult( m_tPosition, CC_CONTENT_SCALE_FACTOR() );
    }

	// direction
	float a = CC_DEGREES_TO_RADIANS( m_fAngle + m_fAngleVar * CCRANDOM_MINUS1_1() );	

	// Mode Gravity: A
	if( m_nEmitterMode == kCCParticleModeGravity ) 
	{
		CGPoint v(cosf( a ), sinf( a ));
		float s = modeA.speed + modeA.speedVar * CCRANDOM_MINUS1_1();
        s *= CC_CONTENT_SCALE_FACTOR();

		// direction
		particle->modeA.dir = ccpMult( v, s );

		// radial accel
		particle->modeA.radialAccel = modeA.radialAccel + modeA.radialAccelVar * CCRANDOM_MINUS1_1();
        particle->modeA.radialAccel *= CC_CONTENT_SCALE_FACTOR();

		// tangential accel
		particle->modeA.tangentialAccel = modeA.tangentialAccel + modeA.tangentialAccelVar * CCRANDOM_MINUS1_1();
        particle->modeA.tangentialAccel *= CC_CONTENT_SCALE_FACTOR();
    }

	// Mode Radius: B
	else {
		// Set the default diameter of the particle from the source position
		float startRadius = modeB.startRadius + modeB.startRadiusVar * CCRANDOM_MINUS1_1();
		float endRadius = modeB.endRadius + modeB.endRadiusVar * CCRANDOM_MINUS1_1();
        startRadius *= CC_CONTENT_SCALE_FACTOR();
        endRadius *= CC_CONTENT_SCALE_FACTOR();

		particle->modeB.radius = startRadius;

		if( modeB.endRadius == kCCParticleStartRadiusEqualToEndRadius )
			particle->modeB.deltaRadius = 0;
		else
			particle->modeB.deltaRadius = (endRadius - startRadius) / particle->timeToLive;

		particle->modeB.angle = a;
		particle->modeB.degreesPerSecond = CC_DEGREES_TO_RADIANS(modeB.rotatePerSecond + modeB.rotatePerSecondVar * CCRANDOM_MINUS1_1());
	}	
}
void CCParticleSystem::stopSystem()
{
	m_bIsActive = false;
	m_fElapsed = m_fDuration;
	m_fEmitCounter = 0;
}
void CCParticleSystem::resetSystem()
{
	m_bIsActive = true;
	m_fElapsed = 0;
	for (m_nParticleIdx = 0; m_nParticleIdx < m_nParticleCount; ++m_nParticleIdx)
	{
		tCCParticle *p = &m_pParticles[m_nParticleIdx];
		p->timeToLive = 0;
	}
}
bool CCParticleSystem::isFull()
{
	return (m_nParticleCount == m_nTotalParticles);
}

// ParticleSystem - MainLoop
void CCParticleSystem::update(ccTime dt)
{
	if( m_bIsActive && m_fEmissionRate )
	{
		float rate = 1.0f / m_fEmissionRate;
		m_fEmitCounter += dt;
		while( m_nParticleCount < m_nTotalParticles && m_fEmitCounter > rate ) 
		{
			this->addParticle();
			m_fEmitCounter -= rate;
		}

		m_fElapsed += dt;
		if(m_fDuration != -1 && m_fDuration < m_fElapsed)
		{
			this->stopSystem();
		}
	}

	m_nParticleIdx = 0;


#if CC_ENABLE_PROFILERS
	/// @todo CCProfilingBeginTimingBlock(_profilingTimer);
#endif


	CGPoint currentPosition = CGPointZero;
	if( m_ePositionType == kCCPositionTypeFree )
	{
		currentPosition = this->convertToWorldSpace(CGPointZero);
        currentPosition.x *= CC_CONTENT_SCALE_FACTOR();
        currentPosition.y *= CC_CONTENT_SCALE_FACTOR();
	}
    else if ( m_ePositionType == kCCPositionTypeRelative )
    {
        currentPosition = m_tPosition;
        currentPosition.x *= CC_CONTENT_SCALE_FACTOR();
        currentPosition.y *= CC_CONTENT_SCALE_FACTOR();
    }

	while( m_nParticleIdx < m_nParticleCount )
	{
		tCCParticle *p = &m_pParticles[m_nParticleIdx];

		// life
		p->timeToLive -= dt;

		if( p->timeToLive > 0 ) 
		{
			// Mode A: gravity, direction, tangential accel & radial accel
			if( m_nEmitterMode == kCCParticleModeGravity ) 
			{
				CGPoint tmp, radial, tangential;

				radial = CGPointZero;
				// radial acceleration
				if(p->pos.x || p->pos.y)
					radial = ccpNormalize(p->pos);
				tangential = radial;
				radial = ccpMult(radial, p->modeA.radialAccel);

				// tangential acceleration
				float newy = tangential.x;
				tangential.x = -tangential.y;
				tangential.y = newy;
				tangential = ccpMult(tangential, p->modeA.tangentialAccel);

				// (gravity + radial + tangential) * dt
				tmp = ccpAdd( ccpAdd( radial, tangential), modeA.gravity);
				tmp = ccpMult( tmp, dt);
				p->modeA.dir = ccpAdd( p->modeA.dir, tmp);
				tmp = ccpMult(p->modeA.dir, dt);
				p->pos = ccpAdd( p->pos, tmp );
			}

			// Mode B: radius movement
			else {				
				// Update the angle and radius of the particle.
				p->modeB.angle += p->modeB.degreesPerSecond * dt;
				p->modeB.radius += p->modeB.deltaRadius * dt;

				p->pos.x = - cosf(p->modeB.angle) * p->modeB.radius;
				p->pos.y = - sinf(p->modeB.angle) * p->modeB.radius;
			}

			// color
			p->color.r += (p->deltaColor.r * dt);
			p->color.g += (p->deltaColor.g * dt);
			p->color.b += (p->deltaColor.b * dt);
			p->color.a += (p->deltaColor.a * dt);

			// size
			p->size += (p->deltaSize * dt);
			p->size = MAX( 0, p->size );

			// angle
			p->rotation += (p->deltaRotation * dt);

			//
			// update values in quad
			//

			CGPoint	newPos;

			if( m_ePositionType == kCCPositionTypeFree || m_ePositionType == kCCPositionTypeRelative ) 
			{
				CGPoint diff = ccpSub( currentPosition, p->startPos );
				newPos = ccpSub(p->pos, diff);
			} 
			else
			{
				newPos = p->pos;
			}

			updateQuadWithParticle(p, newPos);
			//updateParticleImp(self, updateParticleSel, p, newPos);

			// update particle counter
			++m_nParticleIdx;

		} 
		else 
		{
			// life < 0
			if( m_nParticleIdx != m_nParticleCount-1 )
			{
				m_pParticles[m_nParticleIdx] = m_pParticles[m_nParticleCount-1];
			}
			--m_nParticleCount;

			if( m_nParticleCount == 0 && m_bIsAutoRemoveOnFinish )
			{
				this->unscheduleUpdate();
				m_pParent->removeChild(this, true);
				return;
			}
		}
	}

#if CC_ENABLE_PROFILERS
	/// @todo CCProfilingEndTimingBlock(_profilingTimer);
#endif

//#ifdef CC_USES_VBO
	this->postStep();
//#endif
}
void CCParticleSystem::updateQuadWithParticle(tCCParticle* particle, CGPoint newPosition)
{
	// should be overriden
}
void CCParticleSystem::postStep()
{
	// should be overriden
}

// ParticleSystem - CCTexture protocol
void CCParticleSystem::setTexture(CCTexture2D* var)
{
	CCX_SAFE_RETAIN(var);
	CCX_SAFE_RELEASE(m_pTexture)
	m_pTexture = var;

	// If the new texture has No premultiplied alpha, AND the blendFunc hasn't been changed, then update it
	if( m_pTexture && ! m_pTexture->getHasPremultipliedAlpha() &&		
		( m_tBlendFunc.src == CC_BLEND_SRC && m_tBlendFunc.dst == CC_BLEND_DST ) ) 
	{
		m_tBlendFunc.src = GL_SRC_ALPHA;
		m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
	}
}
CCTexture2D * CCParticleSystem::getTexture()
{
	return m_pTexture;
}

// ParticleSystem - Additive Blending
void CCParticleSystem::setIsBlendAdditive(bool additive)
{
	if( additive )
	{
		m_tBlendFunc.src = GL_SRC_ALPHA;
		m_tBlendFunc.dst = GL_ONE;
	}
	else
	{
		if( m_pTexture && ! m_pTexture->getHasPremultipliedAlpha() )
		{
			m_tBlendFunc.src = GL_SRC_ALPHA;
			m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
		} 
		else 
		{
			m_tBlendFunc.src = CC_BLEND_SRC;
			m_tBlendFunc.dst = CC_BLEND_DST;
		}
	}
}
bool CCParticleSystem::getIsBlendAdditive()
{
	return( m_tBlendFunc.src == GL_SRC_ALPHA && m_tBlendFunc.dst == GL_ONE);
}

// ParticleSystem - Properties of Gravity Mode 
void CCParticleSystem::setTangentialAccel(float t)
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	modeA.tangentialAccel = t;
}
float CCParticleSystem::getTangentialAccel()
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	return modeA.tangentialAccel;
}
void CCParticleSystem::setTangentialAccelVar(float t)
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	modeA.tangentialAccelVar = t;
}
float CCParticleSystem::getTangentialAccelVar()
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	return modeA.tangentialAccelVar;
}	
void CCParticleSystem::setRadialAccel(float t)
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	modeA.radialAccel = t;
}
float CCParticleSystem::getRadialAccel()
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	return modeA.radialAccel;
}
void CCParticleSystem::setRadialAccelVar(float t)
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	modeA.radialAccelVar = t;
}
float CCParticleSystem::getRadialAccelVar()
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	return modeA.radialAccelVar;
}
void CCParticleSystem::setGravity(CGPoint g)
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	modeA.gravity = g;
}
CGPoint CCParticleSystem::getGravity()
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	return modeA.gravity;
}
void CCParticleSystem::setSpeed(float speed)
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	modeA.speed = speed;
}
float CCParticleSystem::getSpeed()
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	return modeA.speed;
}
void CCParticleSystem::setSpeedVar(float speedVar)
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	modeA.speedVar = speedVar;
}
float CCParticleSystem::getSpeedVar()
{
	NSAssert( m_nEmitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
	return modeA.speedVar;
}

// ParticleSystem - Properties of Radius Mode
void CCParticleSystem::setStartRadius(float startRadius)
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	modeB.startRadius = startRadius;
}
float CCParticleSystem::getStartRadius()
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	return modeB.startRadius;
}
void CCParticleSystem::setStartRadiusVar(float startRadiusVar)
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	modeB.startRadiusVar = startRadiusVar;
}
float CCParticleSystem::getStartRadiusVar()
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	return modeB.startRadiusVar;
}
void CCParticleSystem::setEndRadius(float endRadius)
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	modeB.endRadius = endRadius;
}
float CCParticleSystem::getEndRadius()
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	return modeB.endRadius;
}
void CCParticleSystem::setEndRadiusVar(float endRadiusVar)
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	modeB.endRadiusVar = endRadiusVar;
}
float CCParticleSystem::getEndRadiusVar()
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	return modeB.endRadiusVar;
}
void CCParticleSystem::setRotatePerSecond(float degrees)
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	modeB.rotatePerSecond = degrees;
}
float CCParticleSystem::getRotatePerSecond()
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	return modeB.rotatePerSecond;
}
void CCParticleSystem::setRotatePerSecondVar(float degrees)
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	modeB.rotatePerSecondVar = degrees;
}
float CCParticleSystem::getRotatePerSecondVar()
{
	NSAssert( m_nEmitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
	return modeB.rotatePerSecondVar;
}
bool CCParticleSystem::getIsActive()
{
	return m_bIsActive;
}
int CCParticleSystem::getParticleCount()
{
	return m_nParticleCount;
}
float CCParticleSystem::getDuration()
{
	return m_fDuration;
}
void CCParticleSystem::setDuration(float var)
{
	m_fDuration = var;
}
CGPoint CCParticleSystem::getSourcePosition()
{
	return m_tSourcePosition;
}
void CCParticleSystem::setSourcePosition(CGPoint var)
{
	m_tSourcePosition = var;
}
CGPoint CCParticleSystem::getPosVar()
{
	return m_tPosVar;
}
void CCParticleSystem::setPosVar(CGPoint var)
{
	m_tPosVar = var;
}
float CCParticleSystem::getLife()
{
	return m_fLife;
}
void CCParticleSystem::setLife(float var)
{
	m_fLife = var;
}
float CCParticleSystem::getLifeVar()
{
	return m_fLifeVar;
}
void CCParticleSystem::setLifeVar(float var)
{
	m_fLifeVar = var;
}
float CCParticleSystem::getAngle()
{
	return m_fAngle;
}
void CCParticleSystem::setAngle(float var)
{
	m_fAngle = var;
}
float CCParticleSystem::getAngleVar()
{
	return m_fAngleVar;
}
void CCParticleSystem::setAngleVar(float var)
{
	m_fAngleVar = var;
}
float CCParticleSystem::getStartSize()
{
	return m_fStartSize;
}
void CCParticleSystem::setStartSize(float var)
{
	m_fStartSize = var;
}
float CCParticleSystem::getStartSizeVar()
{
	return m_fStartSizeVar;
}
void CCParticleSystem::setStartSizeVar(float var)
{
	m_fStartSizeVar = var;
}
float CCParticleSystem::getEndSize()
{
	return m_fEndSize;
}
void CCParticleSystem::setEndSize(float var)
{
	m_fEndSize = var;
}
float CCParticleSystem::getEndSizeVar()
{
	return m_fEndSizeVar;
}
void CCParticleSystem::setEndSizeVar(float var)
{
	m_fEndSizeVar = var;
}
ccColor4F CCParticleSystem::getStartColor()
{
	return m_tStartColor;
}
void CCParticleSystem::setStartColor(ccColor4F var)
{
	m_tStartColor = var;
}
ccColor4F CCParticleSystem::getStartColorVar()
{
	return m_tStartColorVar;
}
void CCParticleSystem::setStartColorVar(ccColor4F var)
{
	m_tStartColorVar = var;
}
ccColor4F CCParticleSystem::getEndColor()
{
	return m_tEndColor;
}
void CCParticleSystem::setEndColor(ccColor4F var)
{
	m_tEndColor = var;
}
ccColor4F CCParticleSystem::getEndColorVar()
{
	return m_tEndColorVar;
}
void CCParticleSystem::setEndColorVar(ccColor4F var)
{
	m_tEndColorVar = var;
}
float CCParticleSystem::getStartSpin()
{
	return m_fStartSpin;
}
void CCParticleSystem::setStartSpin(float var)
{
	m_fStartSpin = var;
}
float CCParticleSystem::getStartSpinVar()
{
	return m_fStartSpinVar;
}
void CCParticleSystem::setStartSpinVar(float var)
{
	m_fStartSpinVar = var;
}
float CCParticleSystem::getEndSpin()
{
	return m_fEndSpin;
}
void CCParticleSystem::setEndSpin(float var)
{
	m_fEndSpin = var;
}
float CCParticleSystem::getEndSpinVar()
{
	return m_fEndSpinVar;
}
void CCParticleSystem::setEndSpinVar(float var)
{
	m_fEndSpinVar = var;
}
float CCParticleSystem::getEmissionRate()
{
	return m_fEmissionRate;
}
void CCParticleSystem::setEmissionRate(float var)
{
	m_fEmissionRate = var;
}
int CCParticleSystem::getTotalParticles()
{
	return m_nTotalParticles;
}
void CCParticleSystem::setTotalParticles(int var)
{
	m_nTotalParticles = var;
}
ccBlendFunc CCParticleSystem::getBlendFunc()
{
	return m_tBlendFunc;
}
void CCParticleSystem::setBlendFunc(ccBlendFunc var)
{
	m_tBlendFunc = var;
}
tCCPositionType CCParticleSystem::getPositionType()
{
	return m_ePositionType;
}
void CCParticleSystem::setPositionType(tCCPositionType var)
{
	m_ePositionType = var;
}
bool CCParticleSystem::getIsAutoRemoveOnFinish()
{
	return m_bIsAutoRemoveOnFinish;
}
void CCParticleSystem::setIsAutoRemoveOnFinish(bool var)
{
	m_bIsAutoRemoveOnFinish = var;
}
int CCParticleSystem::getEmitterMode()
{
	return m_nEmitterMode;
}
void CCParticleSystem::setEmitterMode(int var)
{
	m_nEmitterMode = var;
}

}// namespace cocos2d

