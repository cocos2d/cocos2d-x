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
#include "CCQuadParticleSystem.h"
#include "CCSpriteFrame.h"
namespace cocos2d {

	//implementation CCQuadParticleSystem

	// overriding the init method
	bool CCQuadParticleSystem::initWithTotalParticles(int numberOfParticles)
	{
		// base initialization
		if( CCParticleSystem::initWithTotalParticles(numberOfParticles) ) 
		{
			// allocating data space
			m_pQuads = new ccV2F_C4F_T2F_Quad[m_nTotalParticles];
			m_pIndices = new GLushort[m_nTotalParticles * 6];

			if( !m_pQuads || !m_pIndices) 
			{
				CCLOG("cocos2d: Particle system: not enough memory");
				if( m_pQuads )
					delete [] m_pQuads;
				if(m_pIndices)
					delete [] m_pIndices;
				this->release();
				return NULL;
			}

			// initialize only once the texCoords and the indices
			this->initTexCoordsWithRect(CGRectMake(0, 0, 1, 1));
			this->initIndices();

			// create the VBO buffer
			glGenBuffers(1, &m_uQuadsID);

			// initial binding
			glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(m_pQuads[0])*m_nTotalParticles, m_pQuads, GL_DYNAMIC_DRAW);	
			glBindBuffer(GL_ARRAY_BUFFER, 0);	
			return true;
		}
		return false;
	}
	CCQuadParticleSystem::~CCQuadParticleSystem()
	{
		delete [] m_pQuads;
		delete [] m_pIndices;
		glDeleteBuffers(1, &m_uQuadsID);
	}

	// rect should be in Texture coordinates, not pixel coordinates
	void CCQuadParticleSystem::initTexCoordsWithRect(CGRect rect)
	{
		float bottomLeftX = rect.origin.x;
		float bottomLeftY = rect.origin.y;

		float bottomRightX = bottomLeftX + rect.size.width;
		float bottomRightY = bottomLeftY;

		float topLeftX = bottomLeftX;
		float topLeftY = bottomLeftY + rect.size.height;

		float topRightX = bottomRightX;
		float topRightY = topLeftY;

		// Important. Texture in cocos2d are inverted, so the Y component should be inverted
		CC_SWAP( topRightY, bottomRightY, float);
		CC_SWAP( topLeftY, bottomLeftY, float);

		for(int i=0; i<m_nTotalParticles; i++) 
		{
			// bottom-left vertex:
			m_pQuads[i].bl.texCoords.u = bottomLeftX;
			m_pQuads[i].bl.texCoords.v = bottomLeftY;
			// bottom-right vertex:
			m_pQuads[i].br.texCoords.u = bottomRightX;
			m_pQuads[i].br.texCoords.v = bottomRightY;
			// top-left vertex:
			m_pQuads[i].tl.texCoords.u = topLeftX;
			m_pQuads[i].tl.texCoords.v = topLeftY;
			// top-right vertex:
			m_pQuads[i].tr.texCoords.u = topRightX;
			m_pQuads[i].tr.texCoords.v = topRightY;
		}
	}
	void CCQuadParticleSystem::setTextureWithRect(CCTexture2D *texture, CGRect rect)
	{
		// Only update the texture if is different from the current one
		if( !m_pTexture || texture->getName() != m_pTexture->getName() )
		{
			CCParticleSystem::setTexture(texture);
		}

		// convert to Tex coords
		float wide = (float)texture->getPixelsWide();
		float high = (float)texture->getPixelsHigh();
		rect.origin.x = rect.origin.x / wide;
		rect.origin.y = rect.origin.y / high;
		rect.size.width = rect.size.width / wide;
		rect.size.height = rect.size.height / high;
		this->initTexCoordsWithRect(rect);
	}
	void CCQuadParticleSystem::setTexture(CCTexture2D* var)
	{
		this->setTextureWithRect(var, CGRectMake(0, 0, (float)var->getPixelsWide(), (float)var->getPixelsHigh()));
	}
	void CCQuadParticleSystem::setDisplayFrame(CCSpriteFrame *spriteFrame)
	{
		NSAssert( CGPoint::CGPointEqualToPoint( spriteFrame->getOffset() , CGPointZero ), "QuadParticle only supports SpriteFrames with no offsets");

		// update texture before updating texture rect
		if ( !m_pTexture || spriteFrame->getTexture()->getName() != m_pTexture->getName())
		{
			this->setTexture(spriteFrame->getTexture());
		}
	}
	void CCQuadParticleSystem::initIndices()
	{
		for( int i = 0; i < m_nTotalParticles; ++i)
		{
			m_pIndices[i*6+0] = i*4+0;
			m_pIndices[i*6+1] = i*4+1;
			m_pIndices[i*6+2] = i*4+2;

			m_pIndices[i*6+5] = i*4+1;
			m_pIndices[i*6+4] = i*4+2;
			m_pIndices[i*6+3] = i*4+3;
		}
	}
	void CCQuadParticleSystem::updateQuadWithParticle(tCCParticle* particle, CGPoint newPosition)
	{
		// colors
		m_pQuads[m_nParticleIdx].bl.colors = particle->color;
		m_pQuads[m_nParticleIdx].br.colors = particle->color;
		m_pQuads[m_nParticleIdx].tl.colors = particle->color;
		m_pQuads[m_nParticleIdx].tr.colors = particle->color;

		// vertices
		float size_2 = particle->size/2;
		if( particle->rotation ) 
		{
			float x1 = -size_2;
			float y1 = -size_2;

			float x2 = size_2;
			float y2 = size_2;
			float x = newPosition.x;
			float y = newPosition.y;

			float r = (float)-CC_DEGREES_TO_RADIANS(particle->rotation);
			float cr = cosf(r);
			float sr = sinf(r);
			float ax = x1 * cr - y1 * sr + x;
			float ay = x1 * sr + y1 * cr + y;
			float bx = x2 * cr - y1 * sr + x;
			float by = x2 * sr + y1 * cr + y;
			float cx = x2 * cr - y2 * sr + x;
			float cy = x2 * sr + y2 * cr + y;
			float dx = x1 * cr - y2 * sr + x;
			float dy = x1 * sr + y2 * cr + y;

			// bottom-left
			m_pQuads[m_nParticleIdx].bl.vertices.x = ax;
			m_pQuads[m_nParticleIdx].bl.vertices.y = ay;

			// bottom-right vertex:
			m_pQuads[m_nParticleIdx].br.vertices.x = bx;
			m_pQuads[m_nParticleIdx].br.vertices.y = by;

			// top-left vertex:
			m_pQuads[m_nParticleIdx].tl.vertices.x = dx;
			m_pQuads[m_nParticleIdx].tl.vertices.y = dy;

			// top-right vertex:
			m_pQuads[m_nParticleIdx].tr.vertices.x = cx;
			m_pQuads[m_nParticleIdx].tr.vertices.y = cy;
		} else {
			// bottom-left vertex:
			m_pQuads[m_nParticleIdx].bl.vertices.x = newPosition.x - size_2;
			m_pQuads[m_nParticleIdx].bl.vertices.y = newPosition.y - size_2;

			// bottom-right vertex:
			m_pQuads[m_nParticleIdx].br.vertices.x = newPosition.x + size_2;
			m_pQuads[m_nParticleIdx].br.vertices.y = newPosition.y - size_2;

			// top-left vertex:
			m_pQuads[m_nParticleIdx].tl.vertices.x = newPosition.x - size_2;
			m_pQuads[m_nParticleIdx].tl.vertices.y = newPosition.y + size_2;

			// top-right vertex:
			m_pQuads[m_nParticleIdx].tr.vertices.x = newPosition.x + size_2;
			m_pQuads[m_nParticleIdx].tr.vertices.y = newPosition.y + size_2;				
		}
	}
	void CCQuadParticleSystem::postStep()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_pQuads[0])*m_nParticleCount, m_pQuads);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	// overriding draw method
	void CCQuadParticleSystem::draw()
	{	
		// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Unneeded states: -
		glBindTexture(GL_TEXTURE_2D, m_pTexture->getName());

		glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsID);

#define kPointSize sizeof(m_pQuads[0].bl)
		glVertexPointer(2,GL_FLOAT, kPointSize, 0);

		glColorPointer(4, GL_FLOAT, kPointSize, (GLvoid*) offsetof(ccV2F_C4F_T2F,colors) );

		glTexCoordPointer(2, GL_FLOAT, kPointSize, (GLvoid*) offsetof(ccV2F_C4F_T2F,texCoords) );


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

		if( m_nParticleIdx != m_nParticleCount ) 
		{
			CCLOG("pd:%d, pc:%d", m_nParticleIdx, m_nParticleCount);
		}
		glDrawElements(GL_TRIANGLES, m_nParticleIdx*6, GL_UNSIGNED_SHORT, m_pIndices);	

		// restore blend state
		if( newBlend )
			glBlendFunc( CC_BLEND_SRC, CC_BLEND_DST );

#if 0
		// restore color mode
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, colorMode);
#endif

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// restore GL default state
		// -
	}

}// namespace cocos2d

