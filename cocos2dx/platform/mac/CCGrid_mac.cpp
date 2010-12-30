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
#include "ccMacros.h"
#include "effects/CCGrid.h"
#include "CCDirector.h"
#include "effects/CCGrabber.h"
#include "support/ccUtils.h"

#include "CCGL.h"
#include "CGPointExtension.h"

namespace cocos2d
{
	// implementation of CCGridBase

	CCGridBase* CCGridBase::gridWithSize(cocos2d::ccGridSize gridSize)
	{
        CCGridBase *pGridBase = new CCGridBase();

		if (pGridBase)
		{
            if (pGridBase->initWithSize(gridSize))
			{
				pGridBase->autorelease();
			}
			else
			{
				CCX_SAFE_RELEASE_NULL(pGridBase);
			}
		}

		return pGridBase;
	}

	CCGridBase* CCGridBase::gridWithSize(ccGridSize gridSize, CCTexture2D *texture, bool flipped)
	{
		CCGridBase *pGridBase = new CCGridBase();

		if (pGridBase)
		{
			if (pGridBase->initWithSize(gridSize, texture, flipped))
			{
				pGridBase->autorelease();
			}
			else
			{
				CCX_SAFE_RELEASE_NULL(pGridBase);
			}
		}

		return pGridBase;
	}

	bool CCGridBase::initWithSize(ccGridSize gridSize, CCTexture2D *pTexture, bool bFlipped)
	{
		bool bRet = true;

		m_bActive = false;
		m_nReuseGrid = 0;
		m_sGridSize = gridSize;

		m_pTexture = pTexture;
		CCX_SAFE_RETAIN(m_pTexture);
		m_bIsTextureFlipped = bFlipped;

		CGSize texSize = m_pTexture->getContentSizeInPixels();
		m_obStep.x = texSize.width / m_sGridSize.x;
		m_obStep.y = texSize.height / m_sGridSize.y;

		m_pGrabber = new CCGrabber();
		if (m_pGrabber)
		{
			m_pGrabber->grab(m_pTexture);
		}
		else
		{
            bRet = false;
		}
		

		calculateVertexPoints();

		return bRet;
	}

	bool CCGridBase::initWithSize(ccGridSize gridSize)
	{
    	CCDirector *pDirector = CCDirector::sharedDirector();
		CGSize s = pDirector->getWinSizeInPixels();
		
		unsigned int POTWide = ccNextPOT((unsigned int)s.width);
		unsigned int POTHigh = ccNextPOT((unsigned int)s.height);

		// on mac, it use kCCTexture2DPixelFormat_RGBA8888
		CCTexture2DPixelFormat format = kCCTexture2DPixelFormat_RGBA8888;

		void *data = calloc((int)(POTWide * POTHigh * 4), 1);
		if (! data)
		{
			CCLOG("cocos2d: CCGrid: not enough memory.");
			this->release();
			return false;
		}

		CCTexture2D *pTexture = new CCTexture2D();
		pTexture->initWithData(data, format, POTWide, POTHigh, s);

		free(data);

		if (! pTexture)
		{
			CCLOG("cocos2d: CCGrid: error creating texture");
			delete this;
			return false;
		}

		initWithSize(gridSize, pTexture, false);

		pTexture->release();

		return true;
	}

	CCGridBase::~CCGridBase(void)
	{
		CCLOGINFO("cocos2d: deallocing %p", this);

		setActive(false);
		CCX_SAFE_RELEASE(m_pTexture);
		CCX_SAFE_RELEASE(m_pGrabber);
	}

	// properties
	void CCGridBase::setActive(bool bActive)
	{
		m_bActive = bActive;
		if (! bActive)
		{
			CCDirector *pDirector = CCDirector::sharedDirector();
			ccDirectorProjection proj = pDirector->getProjection();
			pDirector->setProjection(proj);
		}
	}

	void CCGridBase::setIsTextureFlipped(bool bFlipped)
	{
		if (m_bIsTextureFlipped != bFlipped)
		{
			m_bIsTextureFlipped = bFlipped;
			calculateVertexPoints();
		}
	}

	// mac can not applay land space
	void CCGridBase::applyLandscape(void)
	{	
		CCLOG("unsupported");
	}

	void CCGridBase::set2DProjection()
	{
		CGSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();

		glLoadIdentity();
		glViewport((GLsizei)0, (GLsizei)0, (GLsizei)winSize.width, (GLsizei)winSize.height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		ccglOrtho(0, winSize.width, 0, winSize.height, -1024, 1024);
		glMatrixMode(GL_MODELVIEW);
	}

	// This routine can be merged with Director
	void CCGridBase::set3DProjection()
	{
		CGSize	winSize = CCDirector::sharedDirector()->getDisplaySizeInPixels();

		glViewport(0, 0, (GLsizei)winSize.width, (GLsizei)winSize.height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (GLfloat)winSize.width/winSize.height, 0.5f, 1500.0f);

		glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity();
		gluLookAt( winSize.width/2, winSize.height/2, CCDirector::sharedDirector()->getZEye(),
			winSize.width/2, winSize.height/2, 0,
			0.0f, 1.0f, 0.0f
			);
	}

	void CCGridBase::beforeDraw(void)
	{
		set2DProjection();
		m_pGrabber->beforeRender(m_pTexture);
	}

	void CCGridBase::afterDraw(cocos2d::CCNode *pTarget)
	{
		m_pGrabber->afterRender(m_pTexture);

		set3DProjection();
		// mac can not applay land space
		//applyLandscape();

		if (pTarget->getCamera()->getDirty())
		{
			CGPoint offset = pTarget->getAnchorPointInPixels();

			//
			// XXX: Camera should be applied in the AnchorPoint
			//
			ccglTranslate(offset.x, offset.y, 0);
			pTarget->getCamera()->locate();
			ccglTranslate(-offset.x, -offset.y, 0);
		}

		glBindTexture(GL_TEXTURE_2D, m_pTexture->getName());

		blit();
	}

	void CCGridBase::blit(void)
	{
		assert(0);
	}

	void CCGridBase::reuse(void)
	{
		assert(0);
	}

	void CCGridBase::calculateVertexPoints(void)
	{
		assert(0);
	}

	// implementation of CCGrid3D

	CCGrid3D* CCGrid3D::gridWithSize(ccGridSize gridSize, CCTexture2D *pTexture, bool bFlipped)
	{
		CCGrid3D *pRet= new CCGrid3D();

		if (pRet)
		{
			if (pRet->initWithSize(gridSize, pTexture, bFlipped))
			{
			    pRet->autorelease();
			}
			else
			{
				delete pRet;
				pRet = NULL;
			}
		}

		return pRet;
	}

	CCGrid3D* CCGrid3D::gridWithSize(ccGridSize gridSize)
	{
		CCGrid3D *pRet= new CCGrid3D();

		if (pRet)
		{
			if (pRet->initWithSize(gridSize))
			{
			    pRet->autorelease();
			}
			else
			{
				delete pRet;
				pRet = NULL;
			}
		}

		return pRet;
	}

	CCGrid3D::~CCGrid3D(void)
	{
		free(m_pTexCoordinates);
		free(m_pVertices);
		free(m_pIndices);
		free(m_pOriginalVertices);
	}

	void CCGrid3D::blit(void)
	{
		int n = m_sGridSize.x * m_sGridSize.y;

		// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Unneeded states: GL_COLOR_ARRAY
		glDisableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_pVertices);
		glTexCoordPointer(2, GL_FLOAT, 0, m_pTexCoordinates);
		glDrawElements(GL_TRIANGLES, n * 6, GL_UNSIGNED_SHORT, m_pIndices);

		// restore GL default state
		glEnableClientState(GL_COLOR_ARRAY);
	}

	void CCGrid3D::calculateVertexPoints(void)
	{
		float width = (float)m_pTexture->getPixelsWide();
		float height = (float)m_pTexture->getPixelsHigh();
		float imageH = m_pTexture->getContentSizeInPixels().height;

		int x, y, i;

		m_pVertices = malloc((m_sGridSize.x+1) * (m_sGridSize.y+1) * sizeof(ccVertex3F));
		m_pOriginalVertices = malloc((m_sGridSize.x+1) * (m_sGridSize.y+1) * sizeof(ccVertex3F));
		m_pTexCoordinates = malloc((m_sGridSize.x+1) * (m_sGridSize.y+1) * sizeof(CGPoint));
		m_pIndices = (GLushort*)malloc(m_sGridSize.x * m_sGridSize.y * sizeof(GLushort) * 6);

		float *vertArray = (float*)m_pVertices;
		float *texArray = (float*)m_pTexCoordinates;
		GLushort *idxArray = m_pIndices;

		for (x = 0; x < m_sGridSize.x; ++x)
		{
			for (y = 0; y < m_sGridSize.y; ++y)
			{
				int idx = (y * m_sGridSize.x) + x;

				float x1 = x * m_obStep.x;
				float x2 = x1 + m_obStep.x;
				float y1 = y * m_obStep.y;
				float y2= y1 + m_obStep.y;

				GLushort a = x * (m_sGridSize.y + 1) + y;
				GLushort b = (x + 1) * (m_sGridSize.y + 1) + y;
				GLushort c = (x + 1) * (m_sGridSize.y + 1) + (y + 1);
				GLushort d = x * (m_sGridSize.y + 1) + (y + 1);

				GLushort tempidx[6] = {a, b, d, b, c, d};

				memcpy(&idxArray[6*idx], tempidx, 6*sizeof(GLushort));

				int l1[4] = {a*3, b*3, c*3, d*3};
				ccVertex3F e = {x1, y1, 0};
				ccVertex3F f = {x2, y1, 0};
				ccVertex3F g = {x2, y2, 0};
				ccVertex3F h = {x1, y2, 0};

				ccVertex3F l2[4] = {e, f, g, h};

				int tex1[4] = {a*2, b*2, c*2, d*2};
				CGPoint tex2[4] = {ccp(x1, y1), ccp(x2, y1), ccp(x2, y2), ccp(x1, y2)};

				for (i = 0; i < 4; ++i)
				{
					vertArray[l1[i]] = l2[i].x;
					vertArray[l1[i] + 1] = l2[i].y;
					vertArray[l1[i] + 2] = l2[i].z;

					texArray[tex1[i]] = tex2[i].x / width;
					if (m_bIsTextureFlipped)
					{
						texArray[tex1[i] + 1] = (imageH - tex2[i].y) / height;
					}
					else
					{
						texArray[tex1[i] + 1] = tex2[i].y / height;
					}
				}
			}
		}

		memcpy(m_pOriginalVertices, m_pVertices, (m_sGridSize.x+1) * (m_sGridSize.y+1) * sizeof(ccVertex3F));
	}

	ccVertex3F CCGrid3D::vertex(ccGridSize pos)
	{
		int index = (pos.x * (m_sGridSize.y+1) + pos.y) * 3;
		float *vertArray = (float*)m_pVertices;

		ccVertex3F vert = {vertArray[index], vertArray[index+1], vertArray[index+2]};

		return vert;
	}

	ccVertex3F CCGrid3D::originalVertex(cocos2d::ccGridSize pos)
	{
		int index = (pos.x * (m_sGridSize.y+1) + pos.y) * 3;
		float *vertArray = (float*)m_pOriginalVertices;

		ccVertex3F vert = {vertArray[index], vertArray[index+1], vertArray[index+2]};

		return vert;
	}

	void CCGrid3D::setVertex(ccGridSize pos, ccVertex3F vertex)
	{
		int index = (pos.x * (m_sGridSize.y + 1) + pos.y) * 3;
		float *vertArray = (float*)m_pVertices;
		vertArray[index] = vertex.x;
		vertArray[index+1] = vertex.y;
		vertArray[index+2] = vertex.z;
	}

	void CCGrid3D::reuse(void)
	{
		if (m_nReuseGrid > 0)
		{
			memcpy(m_pOriginalVertices, m_pVertices, (m_sGridSize.x+1) * (m_sGridSize.y+1) * sizeof(ccVertex3F));
			--m_nReuseGrid;
		}
	}

	// implementation of CCTiledGrid3D

	CCTiledGrid3D::~CCTiledGrid3D(void)
	{
		free(m_pTexCoordinates);
		free(m_pVertices);
		free(m_pOriginalVertices);
		free(m_pIndices);
	}

	CCTiledGrid3D* CCTiledGrid3D::gridWithSize(cocos2d::ccGridSize gridSize, cocos2d::CCTexture2D *pTexture, bool bFlipped)
	{
		CCTiledGrid3D *pRet= new CCTiledGrid3D();

		if (pRet)
		{
			if (pRet->initWithSize(gridSize, pTexture, bFlipped))
			{
			    pRet->autorelease();
			}
			else
			{
				delete pRet;
				pRet = NULL;
			}
		}

		return pRet;
	}

	CCTiledGrid3D* CCTiledGrid3D::gridWithSize(cocos2d::ccGridSize gridSize)
	{
		CCTiledGrid3D *pRet= new CCTiledGrid3D();

		if (pRet)
		{
			if (pRet->initWithSize(gridSize))
			{
			    pRet->autorelease();
			}
			else
			{
				delete pRet;
				pRet = NULL;
			}
		}

		return pRet;
	}

	void CCTiledGrid3D::blit(void)
	{
		int n = m_sGridSize.x * m_sGridSize.y;

		// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Unneeded states: GL_COLOR_ARRAY
		glDisableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_pVertices);
		glTexCoordPointer(2, GL_FLOAT, 0, m_pTexCoordinates);
		glDrawElements(GL_TRIANGLES, n*6, GL_UNSIGNED_SHORT, m_pIndices);

		// restore default GL state
		glEnableClientState(GL_COLOR_ARRAY);
	}

	void CCTiledGrid3D::calculateVertexPoints(void)
	{
 		float width = (float)m_pTexture->getPixelsWide();
 		float height = (float)m_pTexture->getPixelsHigh();
		float imageH = m_pTexture->getContentSizeInPixels().height;
		
		int numQuads = m_sGridSize.x * m_sGridSize.y;
		
		m_pVertices = malloc(numQuads * 12 * sizeof(GLfloat));
		m_pOriginalVertices = malloc(numQuads * 12 * sizeof(GLfloat));
		m_pTexCoordinates = malloc(numQuads * 8 * sizeof(GLfloat));
		m_pIndices = (GLushort *)malloc(numQuads * 6 * sizeof(GLushort));
		
		float *vertArray = (float*)m_pVertices;
		float *texArray = (float*)m_pTexCoordinates;
		GLushort *idxArray = m_pIndices;
		
		int x, y;
		
		for( x = 0; x < m_sGridSize.x; x++ )
		{
			for( y = 0; y < m_sGridSize.y; y++ )
			{
				float x1 = x * m_obStep.x;
				float x2 = x1 + m_obStep.x;
				float y1 = y * m_obStep.y;
				float y2 = y1 + m_obStep.y;
				
				*vertArray++ = x1;
				*vertArray++ = y1;
				*vertArray++ = 0;
				*vertArray++ = x2;
				*vertArray++ = y1;
				*vertArray++ = 0;
				*vertArray++ = x1;
				*vertArray++ = y2;
				*vertArray++ = 0;
				*vertArray++ = x2;
				*vertArray++ = y2;
				*vertArray++ = 0;
				
				float newY1 = y1;
				float newY2 = y2;
				
				if (m_bIsTextureFlipped) 
				{
					newY1 = imageH - y1;
					newY2 = imageH - y2;
				}

				*texArray++ = x1 / width;
				*texArray++ = newY1 / height;
				*texArray++ = x2 / width;
				*texArray++ = newY1 / height;
				*texArray++ = x1 / width;
				*texArray++ = newY2 / height;
				*texArray++ = x2 / width;
				*texArray++ = newY2 / height;
			}
		}
		
		for (x = 0; x < numQuads; x++)
		{
			idxArray[x*6+0] = x * 4 + 0;
			idxArray[x*6+1] = x * 4 + 1;
			idxArray[x*6+2] = x * 4 + 2;
			
			idxArray[x*6+3] = x * 4 + 1;
			idxArray[x*6+4] = x * 4 + 2;
			idxArray[x*6+5] = x * 4 + 3;
		}
		
		memcpy(m_pOriginalVertices, m_pVertices, numQuads * 12 * sizeof(GLfloat));
	}

	void CCTiledGrid3D::setTile(cocos2d::ccGridSize pos, cocos2d::ccQuad3 coords)
	{
		int idx = (m_sGridSize.y * pos.x + pos.y) * 4 * 3;
		float *vertArray = (float*)m_pVertices;
		memcpy(&vertArray[idx], &coords, sizeof(ccQuad3));
	}

	ccQuad3 CCTiledGrid3D::originalTile(ccGridSize pos)
	{
		int idx = (m_sGridSize.y * pos.x + pos.y) * 4 * 3;
		float *vertArray = (float*)m_pOriginalVertices;

		ccQuad3 ret;
		memcpy(&ret, &vertArray[idx], sizeof(ccQuad3));

		return ret;
	}

	ccQuad3 CCTiledGrid3D::tile(cocos2d::ccGridSize pos)
	{
		int idx = (m_sGridSize.y * pos.x + pos.y) * 4 * 3;
		float *vertArray = (float*)m_pVertices;

		ccQuad3 ret;
		memcpy(&ret, &vertArray[idx], sizeof(ccQuad3));

		return ret;
	}

	void CCTiledGrid3D::reuse(void)
	{
		if (m_nReuseGrid > 0)
		{
			int numQuads = m_sGridSize.x * m_sGridSize.y;

			memcpy(m_pOriginalVertices, m_pVertices, numQuads * 12 * sizeof(GLfloat));
			--m_nReuseGrid;
		}
	}
} // end of namespace cocos2d
