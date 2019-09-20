/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "2d/CCLabelAtlas.h"
#include "renderer/CCTextureAtlas.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "renderer/CCTextureCache.h"

#if CC_LABELATLAS_DEBUG_DRAW
#include "renderer/CCRenderer.h"
#endif

NS_CC_BEGIN

//CCLabelAtlas - Creation & Init

LabelAtlas* LabelAtlas::create()
{
    LabelAtlas* ret = new (std::nothrow) LabelAtlas();
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL(ret);
    }
    
    return ret;
}

LabelAtlas* LabelAtlas::create(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    LabelAtlas* ret = new (std::nothrow) LabelAtlas();
    if(ret && ret->initWithString(string, charMapFile, itemWidth, itemHeight, startCharMap))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LabelAtlas::initWithString(const std::string& string, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(charMapFile);
    return initWithString(string, texture, itemWidth, itemHeight, startCharMap);
}

bool LabelAtlas::initWithString(const std::string& string, Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    if (AtlasNode::initWithTexture(texture, itemWidth, itemHeight, static_cast<int>(string.size())))
    {
        _mapStartChar = startCharMap;
        this->setString(string);
        return true;
    }
    return false;
}

LabelAtlas* LabelAtlas::create(const std::string& string, const std::string& fntFile)
{    
    LabelAtlas *ret = new (std::nothrow) LabelAtlas();
    if (ret)
    {
        if (ret->initWithString(string, fntFile))
        {
            ret->autorelease();
        }
        else 
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }
    
    return ret;
}

bool LabelAtlas::initWithString(const std::string& theString, const std::string& fntFile)
{
    std::string pathStr = FileUtils::getInstance()->fullPathForFilename(fntFile);
    std::string relPathStr = pathStr.substr(0, pathStr.find_last_of('/'))+"/";
    
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(pathStr);

    CCASSERT(dict["version"].asInt() == 1, "Unsupported version. Upgrade cocos2d version");

    std::string textureFilename = relPathStr + dict["textureFilename"].asString();

    unsigned int width = dict["itemWidth"].asInt() / CC_CONTENT_SCALE_FACTOR();
    unsigned int height = dict["itemHeight"].asInt() / CC_CONTENT_SCALE_FACTOR();
    unsigned int startChar = dict["firstChar"].asInt();


    this->initWithString(theString, textureFilename, width, height, startChar);

    return true;
}

//CCLabelAtlas - Atlas generation
void LabelAtlas::updateAtlasValues()
{
    if(_itemsPerRow == 0)
    {
        return;
    }

    ssize_t n = _string.length();

    const unsigned char *s = (unsigned char*)_string.c_str();

    Texture2D *texture = _textureAtlas->getTexture();
    float textureWide = (float) texture->getPixelsWide();
    float textureHigh = (float) texture->getPixelsHigh();
    float itemWidthInPixels = _itemWidth * CC_CONTENT_SCALE_FACTOR();
    float itemHeightInPixels = _itemHeight * CC_CONTENT_SCALE_FACTOR();
    if (_ignoreContentScaleFactor)
    {
        itemWidthInPixels = _itemWidth;
        itemHeightInPixels = _itemHeight;
    }

    CCASSERT(n <= _textureAtlas->getCapacity(), "updateAtlasValues: Invalid String length");
    V3F_C4B_T2F_Quad* quads = _textureAtlas->getQuads();
    for(ssize_t i = 0; i < n; i++) {

        unsigned char a = s[i] - _mapStartChar;
        float row = (float) (a % _itemsPerRow);
        float col = (float) (a / _itemsPerRow);

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        // Issue #938. Don't use texStepX & texStepY
        float left        = (2 * row * itemWidthInPixels + 1) / (2 * textureWide);
        float right        = left + (itemWidthInPixels * 2 - 2) / (2 * textureWide);
        float top        = (2 * col * itemHeightInPixels + 1) / (2 * textureHigh);
        float bottom    = top + (itemHeightInPixels * 2 - 2) / (2 * textureHigh);
#else
        float left        = row * itemWidthInPixels / textureWide;
        float right        = left + itemWidthInPixels / textureWide;
        float top        = col * itemHeightInPixels / textureHigh;
        float bottom    = top + itemHeightInPixels / textureHigh;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

        quads[i].tl.texCoords.u = left;
        quads[i].tl.texCoords.v = top;
        quads[i].tr.texCoords.u = right;
        quads[i].tr.texCoords.v = top;
        quads[i].bl.texCoords.u = left;
        quads[i].bl.texCoords.v = bottom;
        quads[i].br.texCoords.u = right;
        quads[i].br.texCoords.v = bottom;

        quads[i].bl.vertices.x = (float) (i * _itemWidth);
        quads[i].bl.vertices.y = 0;
        quads[i].bl.vertices.z = 0.0f;
        quads[i].br.vertices.x = (float)(i * _itemWidth + _itemWidth);
        quads[i].br.vertices.y = 0;
        quads[i].br.vertices.z = 0.0f;
        quads[i].tl.vertices.x = (float)(i * _itemWidth);
        quads[i].tl.vertices.y = (float)(_itemHeight);
        quads[i].tl.vertices.z = 0.0f;
        quads[i].tr.vertices.x = (float)(i * _itemWidth + _itemWidth);
        quads[i].tr.vertices.y = (float)(_itemHeight);
        quads[i].tr.vertices.z = 0.0f;
        Color4B c(_displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity);
        quads[i].tl.colors = c;
        quads[i].tr.colors = c;
        quads[i].bl.colors = c;
        quads[i].br.colors = c;
    }
    if (n > 0 ){
        _textureAtlas->setDirty(true);
        ssize_t totalQuads = _textureAtlas->getTotalQuads();
        if (n > totalQuads) {
            _textureAtlas->increaseTotalQuadsWith(static_cast<int>(n - totalQuads));
        }
    }
}

//CCLabelAtlas - LabelProtocol
void LabelAtlas::setString(const std::string &label)
{
    ssize_t len = label.size();
    if (len > _textureAtlas->getTotalQuads())
    {
        _textureAtlas->resizeCapacity(len);
    }
    _string.clear();
    _string = label;
    this->updateAtlasValues();

    Size s = Size(len * _itemWidth, _itemHeight);

    this->setContentSize(s);

    _quadsToDraw = len;
}

const std::string& LabelAtlas::getString() const
{
    return _string;
}

void LabelAtlas::updateColor()
{
    if (_textureAtlas)
    {
        Color4B color4( _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity );
        if (_isOpacityModifyRGB)
        {
            color4.r *= _displayedOpacity/255.0f;
            color4.g *= _displayedOpacity/255.0f;
            color4.b *= _displayedOpacity/255.0f;
        }
        auto quads = _textureAtlas->getQuads();
        ssize_t length = _string.length();
        for (int index = 0; index < length; index++)
        {
            quads[index].bl.colors = color4;
            quads[index].br.colors = color4;
            quads[index].tl.colors = color4;
            quads[index].tr.colors = color4;
            _textureAtlas->updateQuad(&quads[index], index);
        }
    }
}

//CCLabelAtlas - draw
#if CC_LABELATLAS_DEBUG_DRAW
void LabelAtlas::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    AtlasNode::draw(renderer, transform, _transformUpdated);

    _debugDrawNode->clear();
    auto size = getContentSize();
    Vec2 vertices[4]=
    {
        Vec2::ZERO,
        Vec2(size.width, 0),
        Vec2(size.width, size.height),
        Vec2(0.0f, size.height)
    };
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
}
#endif

std::string LabelAtlas::getDescription() const
{
    return StringUtils::format("<LabelAtlas | Tag = %d, Label = '%s'>", _tag, _string.c_str());
}

NS_CC_END
