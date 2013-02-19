/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#include "CCAtlasNode.h"
#include "textures/CCTextureAtlas.h"
#include "CCDirector.h"
#include "shaders/CCGLProgram.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccGLStateCache.h"
#include "CCDirector.h"
#include "support/TransformUtils.h"

// external
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

// implementation CCAtlasNode

// CCAtlasNode - Creation & Init

CCAtlasNode::CCAtlasNode()
: m_uItemsPerRow(0)
, m_uItemsPerColumn(0)
, m_uItemWidth(0)
, m_uItemHeight(0)
, m_pTextureAtlas(NULL)
, m_bIsOpacityModifyRGB(false)
, m_cOpacity(0)
, m_uQuadsToDraw(0)
, m_nUniformColor(0)
{
}

CCAtlasNode::~CCAtlasNode()
{
    CC_SAFE_RELEASE(m_pTextureAtlas);
}

CCAtlasNode * CCAtlasNode::create(const char *tile, unsigned int tileWidth, unsigned int tileHeight, 
											 unsigned int itemsToRender)
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

bool CCAtlasNode::initWithTileFile(const char *tile, unsigned int tileWidth, unsigned int tileHeight, 
                                   unsigned int itemsToRender)
{
    CCAssert(tile != NULL, "title should not be null");
    m_uItemWidth  = tileWidth;
    m_uItemHeight = tileHeight;

    m_cOpacity = 255;
    m_tColor = m_tColorUnmodified = ccWHITE;
    m_bIsOpacityModifyRGB = true;

    m_tBlendFunc.src = CC_BLEND_SRC;
    m_tBlendFunc.dst = CC_BLEND_DST;

    CCTextureAtlas* pNewAtlas= new CCTextureAtlas();
    pNewAtlas->initWithFile(tile, itemsToRender);
    setTextureAtlas(pNewAtlas);
    pNewAtlas->release();

    if (! m_pTextureAtlas)
    {
        CCLOG("cocos2d: Could not initialize CCAtlasNode. Invalid Texture.");
        return false;
    }

    this->updateBlendFunc();
    this->updateOpacityModifyRGB();

    this->calculateMaxItems();

    m_uQuadsToDraw = itemsToRender;

    // shader stuff
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture_uColor));
    m_nUniformColor = glGetUniformLocation( getShaderProgram()->getProgram(), "u_color");

    return true;
}


// CCAtlasNode - Atlas generation

void CCAtlasNode::calculateMaxItems()
{
    const CCSize& s = m_pTextureAtlas->getTexture()->getContentSize();
    m_uItemsPerColumn = (int)(s.height / m_uItemHeight);
    m_uItemsPerRow = (int)(s.width / m_uItemWidth);
}

void CCAtlasNode::updateAtlasValues()
{
    CCAssert(false, "CCAtlasNode:Abstract updateAtlasValue not overridden");
}

// CCAtlasNode - draw
void CCAtlasNode::draw(void)
{
    CC_NODE_DRAW_SETUP();

    ccGLBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );

    GLfloat colors[4] = {m_tColor.r / 255.0f, m_tColor.g / 255.0f, m_tColor.b / 255.0f, m_cOpacity / 255.0f};
    getShaderProgram()->setUniformLocationWith4fv(m_nUniformColor, colors, 1);

    m_pTextureAtlas->drawNumberOfQuads(m_uQuadsToDraw, 0);
}

// CCAtlasNode - RGBA protocol

const ccColor3B& CCAtlasNode:: getColor()
{
    if(m_bIsOpacityModifyRGB)
    {
        return m_tColorUnmodified;
    }
    return m_tColor;
}

void CCAtlasNode::setColor(const ccColor3B& color3)
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

void CCAtlasNode::setOpacityModifyRGB(bool bValue)
{
    ccColor3B oldColor = this->getColor();
    m_bIsOpacityModifyRGB = bValue;
    this->setColor(oldColor);
}

bool CCAtlasNode::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}

void CCAtlasNode::updateOpacityModifyRGB()
{
    m_bIsOpacityModifyRGB = m_pTextureAtlas->getTexture()->hasPremultipliedAlpha();
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
    if( ! m_pTextureAtlas->getTexture()->hasPremultipliedAlpha() ) {
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

unsigned int CCAtlasNode::getQuadsToDraw()
{
    return m_uQuadsToDraw;
}

void CCAtlasNode::setQuadsToDraw(unsigned int uQuadsToDraw)
{
    m_uQuadsToDraw = uQuadsToDraw;
}

NS_CC_END
