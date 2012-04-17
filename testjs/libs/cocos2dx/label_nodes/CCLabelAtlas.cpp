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
#include "CCLabelAtlas.h"
#include "CCTextureAtlas.h"
#include "CCPointExtension.h"
#include "CCDrawingPrimitives.h"
#include "ccConfig.h"

namespace cocos2d{

	//CCLabelAtlas - Creation & Init
	CCLabelAtlas * CCLabelAtlas::labelWithString(const char *label, const char *charMapFile, unsigned int itemWidth, int unsigned itemHeight, unsigned char startCharMap)
	{
		CCLabelAtlas *pRet = new CCLabelAtlas();
		if(pRet && pRet->initWithString(label, charMapFile, itemWidth, itemHeight, startCharMap))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_DELETE(pRet)
		return NULL;
	}

	bool CCLabelAtlas::initWithString(const char *label, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned char startCharMap)
	{
		CCAssert(label != NULL, "");
		if (CCAtlasNode::initWithTileFile(charMapFile, itemWidth, itemHeight, strlen(label)))
		{
			m_cMapStartChar = startCharMap;
			this->setString(label);
			return true;
		}
		return false;
	}

	//CCLabelAtlas - Atlas generation
	void CCLabelAtlas::updateAtlasValues()
	{
		unsigned int n = m_sString.length();

		ccV3F_C4B_T2F_Quad quad;

		const unsigned char *s = (unsigned char*)m_sString.c_str();

        CCTexture2D *texture = m_pTextureAtlas->getTexture();
        float textureWide = (float) texture->getPixelsWide();
        float textureHigh = (float) texture->getPixelsHigh();

		for(unsigned int i = 0; i < n; i++) {
			unsigned char a = s[i] - m_cMapStartChar;
			float row = (float) (a % m_uItemsPerRow);
			float col = (float) (a / m_uItemsPerRow);

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
            // Issue #938. Don't use texStepX & texStepY
            float left		= (2 * row * m_uItemWidth + 1) / (2 * textureWide);
            float right		= left + (m_uItemWidth * 2 - 2) / (2 * textureWide);
            float top		= (2 * col * m_uItemHeight + 1) / (2 * textureHigh);
            float bottom	= top + (m_uItemHeight * 2 - 2) / (2 * textureHigh);
#else
            float left		= row * m_uItemWidth / textureWide;
            float right		= left + m_uItemWidth / textureWide;
            float top		= col * m_uItemHeight / textureHigh;
            float bottom	= top + m_uItemHeight / textureHigh;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

            quad.tl.texCoords.u = left;
            quad.tl.texCoords.v = top;
            quad.tr.texCoords.u = right;
            quad.tr.texCoords.v = top;
            quad.bl.texCoords.u = left;
            quad.bl.texCoords.v = bottom;
            quad.br.texCoords.u = right;
            quad.br.texCoords.v = bottom;

			quad.bl.vertices.x = (float) (i * m_uItemWidth);
			quad.bl.vertices.y = 0;
			quad.bl.vertices.z = 0.0f;
			quad.br.vertices.x = (float)(i * m_uItemWidth + m_uItemWidth);
			quad.br.vertices.y = 0;
			quad.br.vertices.z = 0.0f;
			quad.tl.vertices.x = (float)(i * m_uItemWidth);
			quad.tl.vertices.y = (float)(m_uItemHeight);
			quad.tl.vertices.z = 0.0f;
			quad.tr.vertices.x = (float)(i * m_uItemWidth + m_uItemWidth);
			quad.tr.vertices.y = (float)(m_uItemHeight);
			quad.tr.vertices.z = 0.0f;

			m_pTextureAtlas->updateQuad(&quad, i);
		}
	}
	
	//CCLabelAtlas - CCLabelProtocol
	void CCLabelAtlas::setString(const char *label)
	{
		unsigned int len = strlen(label);
		if (len > m_pTextureAtlas->getTotalQuads())
		{
			m_pTextureAtlas->resizeCapacity(len);
		}
		m_sString.clear();
		m_sString = label;
		this->updateAtlasValues();

		CCSize s;
		s.width = (float)(len * m_uItemWidth);
		s.height = (float)(m_uItemHeight);
		this->setContentSizeInPixels(s);

		m_uQuadsToDraw = len;
	}

	const char* CCLabelAtlas::getString(void)
	{
		return m_sString.c_str();
	}

	//CCLabelAtlas - draw

#if CC_LABELATLAS_DEBUG_DRAW	
	void CCLabelAtlas::draw()
	{
		CCAtlasNode::draw();

		const CCSize& s = this->getContentSize();
		CCPoint vertices[4]={
			ccp(0,0),ccp(s.width,0),
			ccp(s.width,s.height),ccp(0,s.height),
		};
		ccDrawPoly(vertices, 4, true);
	}
#endif
} // namespace cocos2d