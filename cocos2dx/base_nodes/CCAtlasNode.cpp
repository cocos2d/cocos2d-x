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

#include "CCAtlasNode.h"
#include "CCTextureAtlas.h"

namespace   cocos2d {

// implementation CCAtlasNode

// CCAtlasNode - Creation & Init

CCAtlasNode::CCAtlasNode()
{
}

CCAtlasNode::~CCAtlasNode()
{
	m_pTextureAtlas->release();
}

CCAtlasNode * CCAtlasNode::atlasWithTileFile(const char *tile, int tileWidth, int tileHeight, int itemsToRender)
{
	CCAtlasNode * pRet = new CCAtlasNode();
	if (pRet->initWithTileFile(tile, tileWidth, tileHeight, itemsToRender))
	{
		pRet->autorelease();
		return pRet;
	}
	CCX_SAFE_DELETE(pRet);
	return NULL;
}

bool CCAtlasNode::initWithTileFile(const char *tile, int tileWidth, int tileHeight, int itemsToRender)
{
	assert(tile != NULL);
	m_nItemWidth = tileWidth;
	m_nItemHeight = tileHeight;

	m_cOpacity = 255;
	m_tColor = m_tColorUnmodified = ccWHITE;
	m_bIsOpacityModifyRGB = true;

	m_tBlendFunc.src = CC_BLEND_SRC;
	m_tBlendFunc.dst = CC_BLEND_DST;

	// double retain to avoid the autorelease pool
	// also, using: self.textureAtlas supports re-initialization without leaking
	this->m_pTextureAtlas = new CCTextureAtlas();
	m_pTextureAtlas->initWithFile(tile, itemsToRender);
//	m_pTextureAtlas->release();

	this->updateBlendFunc();
	this->updateOpacityModifyRGB();

	this->calculateMaxItems();
	this->calculateTexCoordsSteps();

	return true;
}


// CCAtlasNode - Atlas generation

void CCAtlasNode::calculateMaxItems()
{
	CGSize s = m_pTextureAtlas->getTexture()->getContentSize();
	m_nItemsPerColumn = (int)(s.height / m_nItemHeight);
	m_nItemsPerRow = (int)(s.width / m_nItemWidth);
}

void CCAtlasNode:: calculateTexCoordsSteps()
{
	CCTexture2D *texture = m_pTextureAtlas->getTexture();
	m_fTexStepX = m_nItemWidth / (float)(texture->getPixelsWide());
	m_fTexStepY = m_nItemHeight / (float)(texture->getPixelsHigh());
}

void CCAtlasNode::updateAtlasValues()
{
	NSAssert(false, "CCAtlasNode:Abstract updateAtlasValue not overriden");
	//[NSException raise:@"CCAtlasNode:Abstract" format:@"updateAtlasValue not overriden"];
}

// CCAtlasNode - draw
void CCAtlasNode::draw()
{
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Unneeded states: GL_COLOR_ARRAY
	glDisableClientState(GL_COLOR_ARRAY);

	glColor4ub( m_tColor.r, m_tColor.g, m_tColor.b, m_cOpacity);

	bool newBlend = false;
	if( m_tBlendFunc.src != CC_BLEND_SRC || m_tBlendFunc.dst != CC_BLEND_DST ) 
	{
		newBlend = true;
		glBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );
	}

	m_pTextureAtlas->drawQuads();

	if( newBlend )
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);

	// is this chepear than saving/restoring color state ?
	// XXX: There is no need to restore the color to (255,255,255,255). Objects should use the color
	// XXX: that they need
	//	glColor4ub( 255, 255, 255, 255);

	// restore default GL state
	glEnableClientState(GL_COLOR_ARRAY);

}

// CCAtlasNode - RGBA protocol

ccColor3B CCAtlasNode:: getColor()
{
	if(m_bIsOpacityModifyRGB)
	{
		return m_tColorUnmodified;
	}
	return m_tColor;
}

void CCAtlasNode::setColor(ccColor3B color3)
{
	m_tColor = m_tColorUnmodified = color3;

	if( m_bIsOpacityModifyRGB )
	{
		m_tColor.r = color3.r * m_cOpacity/255;
		m_tColor.g = color3.g * m_cOpacity/255;
		m_tColor.b = color3.b * m_cOpacity/255;
	}	
}

GLubyte CCAtlasNode::getOpacity()
{
	return m_cOpacity;
}

void CCAtlasNode::setOpacity(GLubyte opacity)
{
	m_cOpacity = opacity;

	// special opacity for premultiplied textures
	if( m_bIsOpacityModifyRGB )
		this->setColor(m_bIsOpacityModifyRGB ? m_tColorUnmodified : m_tColor);
}

void CCAtlasNode::setIsOpacityModifyRGB(bool bValue)
{
	ccColor3B oldColor	= this->m_tColor;
	m_bIsOpacityModifyRGB = bValue;
	this->m_tColor		= oldColor;
}

bool CCAtlasNode::getIsOpacityModifyRGB()
{
	return m_bIsOpacityModifyRGB;
}

void CCAtlasNode::updateOpacityModifyRGB()
{
	m_bIsOpacityModifyRGB = m_pTextureAtlas->getTexture()->getHasPremultipliedAlpha();
}

// CCAtlasNode - CocosNodeTexture protocol

ccBlendFunc CCAtlasNode::getBlendFunc()
{
	return m_tBlendFunc;
}

void CCAtlasNode::setBlendFunc(ccBlendFunc blendFunc)
{
	m_tBlendFunc = blendFunc;
}

void CCAtlasNode::updateBlendFunc()
{
	if( ! m_pTextureAtlas->getTexture()->getHasPremultipliedAlpha() ) {
		m_tBlendFunc.src = GL_SRC_ALPHA;
		m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
	}
}

void CCAtlasNode::setTexture(CCTexture2D *texture)
{
	m_pTextureAtlas->setTexture(texture);
	this->updateBlendFunc();
	this->updateOpacityModifyRGB();
}

CCTexture2D * CCAtlasNode::getTexture()
{
	return m_pTextureAtlas->getTexture();
}

void CCAtlasNode::setTextureAtlas(CCTextureAtlas* var)
{
	CCX_SAFE_RELEASE(m_pTextureAtlas);
	m_pTextureAtlas = var;
	CCX_SAFE_RETAIN(m_pTextureAtlas);
}
CCTextureAtlas * CCAtlasNode::getTextureAtlas()
{
	return m_pTextureAtlas;
}

} // namespace   cocos2d
