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
#include "CCLabelAtlas.h"
#include "CCTextureAtlas.h"
namespace cocos2d{

	//CCLabelAtlas - Creation & Init
	CCLabelAtlas * CCLabelAtlas::labelAtlasWithString(const char *label, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap)
	{
		CCLabelAtlas *pRet = new CCLabelAtlas();
		if(pRet && pRet->initWithString(label, charMapFile, itemWidth, itemHeight, startCharMap))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}
	bool CCLabelAtlas::initWithString(const char *label, const char *charMapFile, int itemWidth, int itemHeight, char startCharMap)
	{
		assert(label != NULL);
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
		int n = m_sString.length();

		ccV3F_C4B_T2F_Quad quad;

		const char *s = m_sString.c_str();

		for( int i=0; i<n; i++) {
			unsigned char a = s[i] - m_cMapStartChar;
			float row = (a % m_nItemsPerRow) * m_fTexStepX;
			float col = (a / m_nItemsPerRow) * m_fTexStepY;

			quad.tl.texCoords.u = row;
			quad.tl.texCoords.v = col;
			quad.tr.texCoords.u = row + m_fTexStepX;
			quad.tr.texCoords.v = col;
			quad.bl.texCoords.u = row;
			quad.bl.texCoords.v = col + m_fTexStepY;
			quad.br.texCoords.u = row + m_fTexStepX;
			quad.br.texCoords.v = col + m_fTexStepY;

			quad.bl.vertices.x = (float) (i * m_nItemWidth);
			quad.bl.vertices.y = 0;
			quad.bl.vertices.z = 0.0f;
			quad.br.vertices.x = (float)(i * m_nItemWidth + m_nItemWidth);
			quad.br.vertices.y = 0;
			quad.br.vertices.z = 0.0f;
			quad.tl.vertices.x = (float)(i * m_nItemWidth);
			quad.tl.vertices.y = (float)(m_nItemHeight);
			quad.tl.vertices.z = 0.0f;
			quad.tr.vertices.x = (float)(i * m_nItemWidth + m_nItemWidth);
			quad.tr.vertices.y = (float)(m_nItemHeight);
			quad.tr.vertices.z = 0.0f;

			m_pTextureAtlas->updateQuad(&quad, i);
		}
	}
	
	//CCLabelAtlas - CCLabelProtocol
	void CCLabelAtlas::setString(const char *label)
	{
		if (strlen(label) > m_pTextureAtlas->getTotalQuads())
		{
			m_pTextureAtlas->resizeCapacity(strlen(label));
		}
		m_sString.clear();
		m_sString = label;
		this->updateAtlasValues();

		CGSize s;
		s.width = (float)(m_sString.length() * m_nItemWidth);
		s.height = (float)(m_nItemHeight);
		this->setContentSize(s);
	}

	//CCLabelAtlas - draw

	// XXX: overriding draw from AtlasNode
	void CCLabelAtlas::draw()
	{
		// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_TEXTURE_COORD_ARRAY
		// Unneeded states: GL_COLOR_ARRAY
		glDisableClientState(GL_COLOR_ARRAY);

		glColor4ub( m_tColor.r, m_tColor.g, m_tColor.b, m_cOpacity);

		bool newBlend = false;
		if( m_tBlendFunc.src != CC_BLEND_SRC || m_tBlendFunc.dst != CC_BLEND_DST ) {
			newBlend = false;
			glBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );
		}

		m_pTextureAtlas->drawNumberOfQuads(m_sString.length());

		if( newBlend )
			glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);

		// is this chepear than saving/restoring color state ?
		// XXX: There is no need to restore the color to (255,255,255,255). Objects should use the color
		// XXX: that they need
		//	glColor4ub( 255, 255, 255, 255);

		// Restore Default GL state. Enable GL_COLOR_ARRAY
		glEnableClientState(GL_COLOR_ARRAY);


#if CC_LABELATLAS_DEBUG_DRAW
		CGSize s = this->getContentSize();
		CGPoint vertices[4]={
			ccp(0,0),ccp(s.width,0),
			ccp(s.width,s.height),ccp(0,s.height),
		};
		ccDrawPoly(vertices, 4, true);
#endif // CC_LABELATLAS_DEBUG_DRAW

	}
} // namespace cocos2d