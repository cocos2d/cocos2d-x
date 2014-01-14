/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "CCTextureCache.h"
#include "CCDrawingPrimitives.h"
#include "ccConfig.h"
#include "CCShaderCache.h"
#include "CCGLProgram.h"
#include "ccGLStateCache.h"
#include "CCDirector.h"
#include "TransformUtils.h"
#include "CCInteger.h"
#include "platform/CCFileUtils.h"
// external
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

//CCLabelAtlas - Creation & Init

LabelAtlas* LabelAtlas::create()
{
    LabelAtlas* ret = new LabelAtlas();
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
    LabelAtlas* ret = new LabelAtlas();
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
    LabelAtlas *ret = new LabelAtlas();
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
    std::string relPathStr = pathStr.substr(0, pathStr.find_last_of("/"))+"/";
    
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(pathStr.c_str());

    CCASSERT(dict["version"].asInt() == 1, "Unsupported version. Upgrade cocos2d version");

    std::string textureFilename = relPathStr + dict["textureFilename"].asString();

    unsigned int width = dict["itemWidth"].asInt() / CC_CONTENT_SCALE_FACTOR();
    unsigned int height = dict["itemHeight"].asInt() / CC_CONTENT_SCALE_FACTOR();
    unsigned int startChar = dict["firstChar"].asInt();


    this->initWithString(theString, textureFilename.c_str(), width, height, startChar);

    return true;
}

//CCLabelAtlas - Atlas generation
void LabelAtlas::updateAtlasValues()
{
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

const std::string& LabelAtlas::getString(void) const
{
    return _string;
}

//CCLabelAtlas - draw

#if CC_LABELATLAS_DEBUG_DRAW    
void LabelAtlas::draw()
{
    AtlasNode::draw();

    const Size& s = this->getContentSize();
    Point vertices[4]={
        Point(0,0),Point(s.width,0),
        Point(s.width,s.height),Point(0,s.height),
    };
    ccDrawPoly(vertices, 4, true);
}
#endif

std::string LabelAtlas::getDescription() const
{
    return StringUtils::format("<LabelAtlas | Tag = %d, Label = '%s'>", _tag, _string.c_str());
}

NS_CC_END
