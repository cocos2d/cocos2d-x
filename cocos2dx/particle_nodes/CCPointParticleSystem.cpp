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
#include "CCPointParticleSystem.h"

namespace cocos2d {

	//implementation CCPointParticleSystem
	bool CCPointParticleSystem::initWithTotalParticles(int numberOfParticles)
	{
		if( CCParticleSystem::initWithTotalParticles(numberOfParticles) )
		{
			m_pVertices = new ccPointSprite[m_nTotalParticles];

			if( ! m_pVertices )
			{
				CCLOG("cocos2d: Particle system: not enough memory");
				this->release();
				return false;
			}

			glGenBuffers(1, &m_uVerticesID);

			// initial binding
			glBindBuffer(GL_ARRAY_BUFFER, m_uVerticesID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(ccPointSprite)*m_nTotalParticles, m_pVertices, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);		
			return true;
		}
		return false;
	}
	CCPointParticleSystem::~CCPointParticleSystem()
	{
		delete [] m_pVertices;
		glDeleteBuffers(1, &m_uVerticesID);
	}
	void CCPointParticleSystem::updateQuadWithParticle(tCCParticle* particle, CGPoint newPosition)
	{
		// place vertices and colos in array
		m_pVertices[m_nParticleIdx].pos = newPosition;
		m_pVertices[m_nParticleIdx].size = particle->size;
		m_pVertices[m_nParticleIdx].colors = particle->color;
	}
	void CCPointParticleSystem::postStep()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_uVerticesID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ccPointSprite)*m_nParticleCount, m_pVertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void CCPointParticleSystem::draw()
	{
		if (m_nParticleIdx==0)
		{
			return;
		}

		// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY
		// Unneeded states: GL_TEXTURE_COORD_ARRAY
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, m_pTexture->getName());

		glEnable(GL_POINT_SPRITE_OES);
		glTexEnvi( GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE );	

		glBindBuffer(GL_ARRAY_BUFFER, m_uVerticesID);

		glVertexPointer(2,GL_FLOAT,sizeof(m_pVertices[0]),0);

		glColorPointer(4, GL_FLOAT, sizeof(m_pVertices[0]),(GLvoid*) offsetof(ccPointSprite,colors) );

		glEnableClientState(GL_POINT_SIZE_ARRAY_OES);
		glPointSizePointerOES(GL_FLOAT,sizeof(m_pVertices[0]),(GLvoid*) offsetof(ccPointSprite,size) );


		bool newBlend = false;
		if( m_tBlendFunc.src != CC_BLEND_SRC || m_tBlendFunc.dst != CC_BLEND_DST ) 
		{
			newBlend = true;
			glBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );
		}

		// save color mode
#if 0
		glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &colorMode);
		if( colorModulate )
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		else
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
#endif

		glDrawArrays(GL_POINTS, 0, m_nParticleIdx);

		// restore blend state
		if( newBlend )
			glBlendFunc( CC_BLEND_SRC, CC_BLEND_DST);

#if 0
		// restore color mode
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, colorMode);
#endif

		// unbind VBO buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisableClientState(GL_POINT_SIZE_ARRAY_OES);
		glDisable(GL_POINT_SPRITE_OES);

		// restore GL default state
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	// Non supported properties

	//
	// SPIN IS NOT SUPPORTED
	//
	void CCPointParticleSystem::setStartSpin(float var)
	{
		NSAssert(var == 0, "PointParticleSystem doesn't support spinning");
		CCParticleSystem::setStartSpin(var);
	}
	void CCPointParticleSystem::setStartSpinVar(float var)
	{
		NSAssert(var == 0, "PointParticleSystem doesn't support spinning");
		CCParticleSystem::setStartSpinVar(var);
	}
	void CCPointParticleSystem::setEndSpin(float var)
	{
		NSAssert(var == 0, "PointParticleSystem doesn't support spinning");
		CCParticleSystem::setEndSpin(var);
	}
	void CCPointParticleSystem::setEndSpinVar(float var)
	{
		NSAssert(var == 0, "PointParticleSystem doesn't support spinning");
		CCParticleSystem::setEndSpinVar(var);
	}
	//
	// SIZE > 64 IS NOT SUPPORTED
	//
	void CCPointParticleSystem::setStartSize(float size)
	{
		NSAssert(size >= 0 && size <= CC_MAX_PARTICLE_SIZE, "PointParticleSystem only supports 0 <= size <= 64");
		CCParticleSystem::setStartSize(size);
	}
	void CCPointParticleSystem::setEndSize(float size)
	{
		NSAssert( (size == kCCParticleStartSizeEqualToEndSize) ||
			( size >= 0 && size <= CC_MAX_PARTICLE_SIZE), "PointParticleSystem only supports 0 <= size <= 64");
		CCParticleSystem::setEndSize(size);
	}

}// namespace cocos2d

