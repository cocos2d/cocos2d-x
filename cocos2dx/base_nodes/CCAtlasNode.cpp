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

// implementation AtlasNode

// AtlasNode - Creation & Init

AtlasNode::AtlasNode()
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

AtlasNode::~AtlasNode()
{
    CC_SAFE_RELEASE(_textureAtlas);
}

AtlasNode * AtlasNode::create(const char *tile, unsigned int tileWidth, unsigned int tileHeight, 
											 unsigned int itemsToRender)
{
	AtlasNode * pRet = new AtlasNode();
	if (pRet->initWithTileFile(tile, tileWidth, tileHeight, itemsToRender))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool AtlasNode::initWithTileFile(const char *tile, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender)
{
    CCASSERT(tile != NULL, "title should not be null");
    Texture2D *texture = TextureCache::getInstance()->addImage(tile);
	return initWithTexture(texture, tileWidth, tileHeight, itemsToRender);
}

bool AtlasNode::initWithTexture(Texture2D* texture, unsigned int tileWidth, unsigned int tileHeight, 
                                   unsigned int itemsToRender)
{
    _itemWidth  = tileWidth;
    _itemHeight = tileHeight;

    _colorUnmodified = Color3B::WHITE;
    _isOpacityModifyRGB = true;

    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;

    _textureAtlas = new TextureAtlas();
    _textureAtlas->initWithTexture(texture, itemsToRender);

    if (! _textureAtlas)
    {
        CCLOG("cocos2d: Could not initialize AtlasNode. Invalid Texture.");
        return false;
    }

    this->updateBlendFunc();
    this->updateOpacityModifyRGB();

    this->calculateMaxItems();

    _quadsToDraw = itemsToRender;

    // shader stuff
    setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR));
    _uniformColor = glGetUniformLocation( getShaderProgram()->getProgram(), "u_color");

    return true;
}


// AtlasNode - Atlas generation

void AtlasNode::calculateMaxItems()
{
    Size s = _textureAtlas->getTexture()->getContentSize();
    
    if (_ignoreContentScaleFactor)
    {
        s = _textureAtlas->getTexture()->getContentSizeInPixels();
    }
    
    _itemsPerColumn = (int)(s.height / _itemHeight);
    _itemsPerRow = (int)(s.width / _itemWidth);
}

void AtlasNode::updateAtlasValues()
{
    CCASSERT(false, "CCAtlasNode:Abstract updateAtlasValue not overridden");
}

// AtlasNode - draw
void AtlasNode::draw(void)
{
    CC_NODE_DRAW_SETUP();

    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    GLfloat colors[4] = {_displayedColor.r / 255.0f, _displayedColor.g / 255.0f, _displayedColor.b / 255.0f, _displayedOpacity / 255.0f};
    getShaderProgram()->setUniformLocationWith4fv(_uniformColor, colors, 1);

    _textureAtlas->drawNumberOfQuads(_quadsToDraw, 0);
}

// AtlasNode - RGBA protocol

const Color3B& AtlasNode::getColor() const
{
    if(_isOpacityModifyRGB)
    {
        return _colorUnmodified;
    }
    return NodeRGBA::getColor();
}

void AtlasNode::setColor(const Color3B& color3)
{
    Color3B tmp = color3;
    _colorUnmodified = color3;

    if( _isOpacityModifyRGB )
    {
        tmp.r = tmp.r * _displayedOpacity/255;
        tmp.g = tmp.g * _displayedOpacity/255;
        tmp.b = tmp.b * _displayedOpacity/255;
    }
    NodeRGBA::setColor(tmp);
}

void AtlasNode::setOpacity(GLubyte opacity)
{
    NodeRGBA::setOpacity(opacity);

    // special opacity for premultiplied textures
    if( _isOpacityModifyRGB )
        this->setColor(_colorUnmodified);
}

void AtlasNode::setOpacityModifyRGB(bool bValue)
{
    Color3B oldColor = this->getColor();
    _isOpacityModifyRGB = bValue;
    this->setColor(oldColor);
}

bool AtlasNode::isOpacityModifyRGB() const
{
    return _isOpacityModifyRGB;
}

void AtlasNode::updateOpacityModifyRGB()
{
    _isOpacityModifyRGB = _textureAtlas->getTexture()->hasPremultipliedAlpha();
}

void AtlasNode::setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor)
{
    _ignoreContentScaleFactor = bIgnoreContentScaleFactor;
}

// AtlasNode - CocosNodeTexture protocol

const BlendFunc& AtlasNode::getBlendFunc() const
{
    return _blendFunc;
}

void AtlasNode::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}

void AtlasNode::updateBlendFunc()
{
    if( ! _textureAtlas->getTexture()->hasPremultipliedAlpha() )
        _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
}

void AtlasNode::setTexture(Texture2D *texture)
{
    _textureAtlas->setTexture(texture);
    this->updateBlendFunc();
    this->updateOpacityModifyRGB();
}

Texture2D * AtlasNode::getTexture() const
{
    return _textureAtlas->getTexture();
}

void AtlasNode::setTextureAtlas(TextureAtlas* textureAtlas)
{
    CC_SAFE_RETAIN(textureAtlas);
    CC_SAFE_RELEASE(_textureAtlas);
    _textureAtlas = textureAtlas;
}

TextureAtlas * AtlasNode::getTextureAtlas() const
{
    return _textureAtlas;
}

unsigned int AtlasNode::getQuadsToDraw() const
{
    return _quadsToDraw;
}

void AtlasNode::setQuadsToDraw(unsigned int uQuadsToDraw)
{
    _quadsToDraw = uQuadsToDraw;
}

NS_CC_END
