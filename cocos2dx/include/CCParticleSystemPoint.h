/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada 
Copyright (c) 2011      Zynga Inc.

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
#ifndef __CC_PARTICLE_SYSTEM_POINT_MOBILE_H__
#define __CC_PARTICLE_SYSTEM_POINT_MOBILE_H__

/*#include "Availability.h"*/
#include "CCParticleSystem.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_QNX)
#include "CCParticleSystemQuad.h"
#endif

namespace cocos2d {

#define CC_MAX_PARTICLE_SIZE 64

/** @brief CCParticleSystemPoint is a subclass of CCParticleSystem
Attributes of a Particle System:
* All the attributes of Particle System

Features:
* consumes small memory: uses 1 vertex (x,y) per particle, no need to assign tex coordinates
* size can't be bigger than 64
* the system can't be scaled since the particles are rendered using GL_POINT_SPRITE

Limitations:
* On 3rd gen iPhone devices and iPads, this node performs MUCH slower than CCParticleSystemQuad.
*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_QNX)
class CC_DLL CCParticleSystemPoint : public CCParticleSystemQuad{
	//nothing to do
};
#else
class CC_DLL CCParticleSystemPoint : public CCParticleSystem
{	
public:
	CCParticleSystemPoint()
		:m_pVertices(NULL)	
	{}
	virtual ~CCParticleSystemPoint();

    /** creates an initializes a CCParticleSystemPoint from a plist file.
    This plist files can be creted manually or with Particle Designer:  
    */
    static CCParticleSystemPoint * particleWithFile(const char *plistFile);

	// super methods
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	virtual void updateQuadWithParticle(tCCParticle* particle, const CCPoint& newPosition);
	virtual void postStep();
	virtual void draw();
	virtual void setStartSpin(float var);
	virtual void setStartSpinVar(float var);
	virtual void setEndSpin(float var);
	virtual void setEndSpinVar(float var);
	virtual void setStartSize(float var);
	virtual void setEndSize(float var);
protected:
	//! Array of (x,y,size) 
	ccPointSprite *m_pVertices;
	//! vertices buffer id
# if CC_USES_VBO
	GLuint	m_uVerticesID;	
#endif
};
#endif

}// namespace cocos2d

#endif //__CC_PARTICLE_SYSTEM_POINT_MOBILE_H__
