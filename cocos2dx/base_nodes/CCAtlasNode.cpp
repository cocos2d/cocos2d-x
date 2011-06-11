/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
 
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
: m_nItemsPerRow(0)
, m_nItemsPerColumn(0)
, m_nItemWidth(0)
, m_nItemHeight(0)
, m_pTextureAtlas(NULL)
, m_bIsOpacityModifyRGB(false)
, m_cOpacity(0)
{
}

CCAtlasNode::~CCAtlasNode()
{
	CC_SAFE_RELEASE(m_pTextureAtlas);
}

CCAtlasNode * CCAtlasNode::atlasWithTileFile(const char *tile, int tileWidth, int tileHeight, int itemsToRender)
{
	CCAtlasNode * pRet = new CCAtlasNode();
	if (pRet->initWithTileFile(tile, tileWidth, tileHeight, itemsToRender))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCAtlasNode::initWithTileFile(const char *tile, int tileWidth, int tileHeight, int itemsToRender)
{
	assert(tile != NULL);
	m_nItemWidth  = (int) (tileWidth * CC_CONTENT_SCALE_FACTOR());
	m_nItemHeight = (int) (tileHeight * CC_CONTENT_SCALE_FACTOR());

	m_cOpacity = 255;
	m_tColor = m_tColorUnmodified = ccWHITE;
	m_bIsOpacityModifyRGB = true;

	m_tBlendFunc.src = CC_BLEND_SRC;
	m_tBlendFunc.dst = CC_BLEND_DST;

	// double retain to avoid the autorelease pool
	// also, using: self.textureAtlas supports re-initialization without leaking
	this->m_pTextureAtlas = new CCTextureAtlas();
	m_pTextureAtlas->initWithFile(tile, itemsToRender);
    
	if (! m_pTextureAtlas)
	{
		CCLOG("cocos2d: Could not initialize CCAtlasNode. Invalid Texture.");
		delete this;
		return false;
	}

	this->updateBlendFunc();
	this->updateOpacityModifyRGB();

	this->calculateMaxItems();

	return true;
}


// CCAtlasNode - Atlas generation

void CCAtlasNode::calculateMaxItems()
{
	CCSize s = m_pTextureAtlas->getTexture()->getContentSizeInPixels();
	m_nItemsPerColumn = (int)(s.height / m_nItemHeight);
	m_nItemsPerRow = (int)(s.width / m_nItemWidth);
}

void CCAtlasNode::updateAtlasValues()
{
	CCAssert(false, "CCAtlasNode:Abstract updateAtlasValue not overriden");
	//[NSException raise:@"CCAtlasNode:Abstract" format:@"updateAtlasValue not overriden"];
}

// CCAtlasNode - draw
void CCAtlasNode::draw()
{
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Unneeded states: GL_COLOR_ARRAY
	glDisableClientState(GL_COLOR_ARRAY);

    // glColor4ub isn't implement on some android devices
	// glColor4ub( m_tColor.r, m_tColor.g, m_tColor.b, m_cOpacity); 
    glColor4f(((GLfloat)m_tColor.r) / 255, ((GLfloat)m_tColor.g) / 255, ((GLfloat)m_tColor.b) / 255, ((GLfloat)m_cOpacity) / 255);
	bool newBlend = m_tBlendFunc.src != CC_BLEND_SRC || m_tBlendFunc.dst != CC_BLEND_DST;
	if(newBlend) 
	{
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
		this->setColor(m_tColorUnmodified);
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
	CC_SAFE_RETAIN(var);
	CC_SAFE_RELEASE(m_pTextureAtlas);
	m_pTextureAtlas = var;
}
CCTextureAtlas * CCAtlasNode::getTextureAtlas()
{
	return m_pTextureAtlas;
}

} // namespace   cocos2d
