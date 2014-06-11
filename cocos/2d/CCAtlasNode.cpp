/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
CopyRight (c) 2013-2014 Chukong Technologies Inc.
 
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
#include "renderer/CCTextureAtlas.h"
#include "base/CCDirector.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/ccGLStateCache.h"
#include "math/TransformUtils.h"

NS_CC_BEGIN

// implementation AtlasNode

// AtlasNode - Creation & Init

AtlasNode::AtlasNode()
: _itemsPerRow(0)
, _itemsPerColumn(0)
, _itemWidth(0)
, _itemHeight(0)
, _textureAtlas(nullptr)
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

AtlasNode * AtlasNode::create(const std::string& tile, int tileWidth, int tileHeight, int itemsToRender)
{
	AtlasNode * ret = new AtlasNode();
	if (ret->initWithTileFile(tile, tileWidth, tileHeight, itemsToRender))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool AtlasNode::initWithTileFile(const std::string& tile, int tileWidth, int tileHeight, int itemsToRender)
{
    CCASSERT(tile.size() > 0, "file size should not be empty");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(tile);
	return initWithTexture(texture, tileWidth, tileHeight, itemsToRender);
}

bool AtlasNode::initWithTexture(Texture2D* texture, int tileWidth, int tileHeight, int itemsToRender)
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
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));

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
void AtlasNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _quadCommand.init(
              _globalZOrder,
              _textureAtlas->getTexture()->getName(),
              getGLProgramState(),
              _blendFunc,
              _textureAtlas->getQuads(),
              _quadsToDraw,
              transform);

    renderer->addCommand(&_quadCommand);

}

// AtlasNode - RGBA protocol

const Color3B& AtlasNode::getColor() const
{
    if(_isOpacityModifyRGB)
    {
        return _colorUnmodified;
    }
    return Node::getColor();
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
    Node::setColor(tmp);
}

void AtlasNode::setOpacity(GLubyte opacity)
{
    Node::setOpacity(opacity);

    // special opacity for premultiplied textures
    if( _isOpacityModifyRGB )
        this->setColor(_colorUnmodified);
}

void AtlasNode::setOpacityModifyRGB(bool value)
{
    Color3B oldColor = this->getColor();
    _isOpacityModifyRGB = value;
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

void AtlasNode::setIgnoreContentScaleFactor(bool ignoreContentScaleFactor)
{
    _ignoreContentScaleFactor = ignoreContentScaleFactor;
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

ssize_t AtlasNode::getQuadsToDraw() const
{
    return _quadsToDraw;
}

void AtlasNode::setQuadsToDraw(ssize_t quadsToDraw)
{
    _quadsToDraw = quadsToDraw;
}

NS_CC_END
