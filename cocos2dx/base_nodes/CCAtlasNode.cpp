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
#include "textures/CCTextureCache.h"
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
: _itemsPerRow(0)
, _itemsPerColumn(0)
, _itemWidth(0)
, _itemHeight(0)
, _textureAtlas(NULL)
, _isOpacityModifyRGB(false)
, _quadsToDraw(0)
, _uniformColor(0)
, _ignoreContentScaleFactor(false)
{
}

CCAtlasNode::~CCAtlasNode()
{
    CC_SAFE_RELEASE(_textureAtlas);
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

bool CCAtlasNode::initWithTileFile(const char *tile, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender)
{
    CCAssert(tile != NULL, "title should not be null");
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(tile);
	return initWithTexture(texture, tileWidth, tileHeight, itemsToRender);
}

bool CCAtlasNode::initWithTexture(CCTexture2D* texture, unsigned int tileWidth, unsigned int tileHeight, 
                                   unsigned int itemsToRender)
{
    _itemWidth  = tileWidth;
    _itemHeight = tileHeight;

    _colorUnmodified = ccWHITE;
    _isOpacityModifyRGB = true;

    _blendFunc.src = CC_BLEND_SRC;
    _blendFunc.dst = CC_BLEND_DST;

    _textureAtlas = new CCTextureAtlas();
    _textureAtlas->initWithTexture(texture, itemsToRender);

    if (! _textureAtlas)
    {
        CCLOG("cocos2d: Could not initialize CCAtlasNode. Invalid Texture.");
        return false;
    }

    this->updateBlendFunc();
    this->updateOpacityModifyRGB();

    this->calculateMaxItems();

    _quadsToDraw = itemsToRender;

    // shader stuff
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture_uColor));
    _uniformColor = glGetUniformLocation( getShaderProgram()->getProgram(), "u_color");

    return true;
}


// CCAtlasNode - Atlas generation

void CCAtlasNode::calculateMaxItems()
{
    CCSize s = _textureAtlas->getTexture()->getContentSize();
    
    if (_ignoreContentScaleFactor)
    {
        s = _textureAtlas->getTexture()->getContentSizeInPixels();
    }
    
    _itemsPerColumn = (int)(s.height / _itemHeight);
    _itemsPerRow = (int)(s.width / _itemWidth);
}

void CCAtlasNode::updateAtlasValues()
{
    CCAssert(false, "CCAtlasNode:Abstract updateAtlasValue not overridden");
}

// CCAtlasNode - draw
void CCAtlasNode::draw(void)
{
    CC_NODE_DRAW_SETUP();

    ccGLBlendFunc( _blendFunc.src, _blendFunc.dst );

    GLfloat colors[4] = {_displayedColor.r / 255.0f, _displayedColor.g / 255.0f, _displayedColor.b / 255.0f, _displayedOpacity / 255.0f};
    getShaderProgram()->setUniformLocationWith4fv(_uniformColor, colors, 1);

    _textureAtlas->drawNumberOfQuads(_quadsToDraw, 0);
}

// CCAtlasNode - RGBA protocol

const ccColor3B& CCAtlasNode::getColor()
{
    if(_isOpacityModifyRGB)
    {
        return _colorUnmodified;
    }
    return CCNodeRGBA::getColor();
}

void CCAtlasNode::setColor(const ccColor3B& color3)
{
    ccColor3B tmp = color3;
    _colorUnmodified = color3;

    if( _isOpacityModifyRGB )
    {
        tmp.r = tmp.r * _displayedOpacity/255;
        tmp.g = tmp.g * _displayedOpacity/255;
        tmp.b = tmp.b * _displayedOpacity/255;
    }
    CCNodeRGBA::setColor(tmp);
}

void CCAtlasNode::setOpacity(GLubyte opacity)
{
    CCNodeRGBA::setOpacity(opacity);

    // special opacity for premultiplied textures
    if( _isOpacityModifyRGB )
        this->setColor(_colorUnmodified);
}

void CCAtlasNode::setOpacityModifyRGB(bool bValue)
{
    ccColor3B oldColor = this->getColor();
    _isOpacityModifyRGB = bValue;
    this->setColor(oldColor);
}

bool CCAtlasNode::isOpacityModifyRGB()
{
    return _isOpacityModifyRGB;
}

void CCAtlasNode::updateOpacityModifyRGB()
{
    _isOpacityModifyRGB = _textureAtlas->getTexture()->hasPremultipliedAlpha();
}

void CCAtlasNode::setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor)
{
    _ignoreContentScaleFactor = bIgnoreContentScaleFactor;
}

// CCAtlasNode - CocosNodeTexture protocol

ccBlendFunc CCAtlasNode::getBlendFunc()
{
    return _blendFunc;
}

void CCAtlasNode::setBlendFunc(ccBlendFunc blendFunc)
{
    _blendFunc = blendFunc;
}

void CCAtlasNode::updateBlendFunc()
{
    if( ! _textureAtlas->getTexture()->hasPremultipliedAlpha() ) {
        _blendFunc.src = GL_SRC_ALPHA;
        _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    }
}

void CCAtlasNode::setTexture(CCTexture2D *texture)
{
    _textureAtlas->setTexture(texture);
    this->updateBlendFunc();
    this->updateOpacityModifyRGB();
}

CCTexture2D * CCAtlasNode::getTexture()
{
    return _textureAtlas->getTexture();
}

void CCAtlasNode::setTextureAtlas(CCTextureAtlas* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_textureAtlas);
    _textureAtlas = var;
}

CCTextureAtlas * CCAtlasNode::getTextureAtlas()
{
    return _textureAtlas;
}

unsigned int CCAtlasNode::getQuadsToDraw()
{
    return _quadsToDraw;
}

void CCAtlasNode::setQuadsToDraw(unsigned int uQuadsToDraw)
{
    _quadsToDraw = uQuadsToDraw;
}

NS_CC_END
