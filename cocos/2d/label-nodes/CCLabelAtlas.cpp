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
#include "CCLabelAtlas.h"
#include "textures/CCTextureAtlas.h"
#include "textures/CCTextureCache.h"
#include "draw_nodes/CCDrawingPrimitives.h"
#include "ccConfig.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "CCDirector.h"
#include "support/TransformUtils.h"
#include "cocoa/CCInteger.h"
#include "platform/CCFileUtils.h"
// external
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

//CCLabelAtlas - Creation & Init

LabelAtlas* LabelAtlas::create(const char *string, const char *charMapFile, unsigned int itemWidth, int unsigned itemHeight, unsigned int startCharMap)
{
    LabelAtlas *pRet = new LabelAtlas();
    if(pRet && pRet->initWithString(string, charMapFile, itemWidth, itemHeight, startCharMap))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool LabelAtlas::initWithString(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    Texture2D *texture = TextureCache::getInstance()->addImage(charMapFile);
	return initWithString(string, texture, itemWidth, itemHeight, startCharMap);
}

bool LabelAtlas::initWithString(const char *string, Texture2D* texture, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    CCASSERT(string != NULL, "");
    if (AtlasNode::initWithTexture(texture, itemWidth, itemHeight, strlen(string)))
    {
        _mapStartChar = startCharMap;
        this->setString(string);
        return true;
    }
    return false;
}

LabelAtlas* LabelAtlas::create(const char *string, const char *fntFile)
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

bool LabelAtlas::initWithString(const char *theString, const char *fntFile)
{
  std::string pathStr = FileUtils::getInstance()->fullPathForFilename(fntFile);
  std::string relPathStr = pathStr.substr(0, pathStr.find_last_of("/"))+"/";
  Dictionary *dict = Dictionary::createWithContentsOfFile(pathStr.c_str());
  
  CCASSERT(((String*)dict->objectForKey("version"))->intValue() == 1, "Unsupported version. Upgrade cocos2d version");
    
  std::string texturePathStr = relPathStr + ((String*)dict->objectForKey("textureFilename"))->getCString();
  String *textureFilename = String::create(texturePathStr);
  unsigned int width = ((String*)dict->objectForKey("itemWidth"))->intValue() / CC_CONTENT_SCALE_FACTOR();
  unsigned int height = ((String*)dict->objectForKey("itemHeight"))->intValue() / CC_CONTENT_SCALE_FACTOR();
  unsigned int startChar = ((String*)dict->objectForKey("firstChar"))->intValue();
  

  this->initWithString(theString, textureFilename->getCString(), width, height, startChar);
    
  return true;
}

//CCLabelAtlas - Atlas generation
void LabelAtlas::updateAtlasValues()
{
    int n = _string.length();

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

    CCASSERT( n <= _textureAtlas->getCapacity(), "updateAtlasValues: Invalid String length");
    V3F_C4B_T2F_Quad* quads = _textureAtlas->getQuads();
    for(int i = 0; i < n; i++) {

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
        int totalQuads = _textureAtlas->getTotalQuads();
        if (n > totalQuads) {
            _textureAtlas->increaseTotalQuadsWith(n - totalQuads);
        }
    }
}

//CCLabelAtlas - LabelProtocol
void LabelAtlas::setString(const char *label)
{
    int len = strlen(label);
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

const char* LabelAtlas::getString(void) const
{
    return _string.c_str();
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

NS_CC_END
