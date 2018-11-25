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
#include "2d/CCTileMapAtlas.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTextureAtlas.h"
#include "base/TGAlib.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"

NS_CC_BEGIN

// implementation TileMapAtlas

TileMapAtlas * TileMapAtlas::create(const std::string& tile, const std::string& mapFile, int tileWidth, int tileHeight)
{
    TileMapAtlas *ret = new (std::nothrow) TileMapAtlas();
    if (ret->initWithTileFile(tile, mapFile, tileWidth, tileHeight))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool TileMapAtlas::initWithTileFile(const std::string& tile, const std::string& mapFile, int tileWidth, int tileHeight)
{
    this->loadTGAfile(mapFile);
    this->calculateItemsToRender();

    if( AtlasNode::initWithTileFile(tile, tileWidth, tileHeight, _itemsToRender) )
    {
        this->updateAtlasValues();
        this->setContentSize(Size((float)(_TGAInfo->width*_itemWidth),
                                        (float)(_TGAInfo->height*_itemHeight)));
        return true;
    }
    return false;
}

TileMapAtlas::TileMapAtlas()
 : _itemsToRender(0)
 , _TGAInfo(nullptr)
{
}

TileMapAtlas::~TileMapAtlas()
{
    if (_TGAInfo)
    {
        tgaDestroy(_TGAInfo);
    }
}

void TileMapAtlas::releaseMap()
{
    if (_TGAInfo)
    {
        tgaDestroy(_TGAInfo);
    }
    _TGAInfo = nullptr;
}

void TileMapAtlas::calculateItemsToRender()
{
    CCASSERT( _TGAInfo != nullptr, "tgaInfo must be non-nil");

    _itemsToRender = 0;
    for(int x=0;x < _TGAInfo->width; x++ ) 
    {
        for( int y=0; y < _TGAInfo->height; y++ ) 
        {
            Color3B *ptr = (Color3B*) _TGAInfo->imageData;
            Color3B value = ptr[x + y * _TGAInfo->width];
            if( value.r )
            {
                ++_itemsToRender;
            }
        }
    }
}

void TileMapAtlas::loadTGAfile(const std::string& file)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(file);

    //    //Find the path of the file
    //    NSBundle *mainBndl = [Director sharedDirector].loadingBundle;
    //    String *resourcePath = [mainBndl resourcePath];
    //    String * path = [resourcePath stringByAppendingPathComponent:file];

    _TGAInfo = tgaLoad( fullPath.c_str() );
#if 1
    if( _TGAInfo->status != TGA_OK ) 
    {
        CCASSERT(0, "TileMapAtlasLoadTGA : TileMapAtlas cannot load TGA file");
    }
#endif
}

// TileMapAtlas - Atlas generation / updates
void TileMapAtlas::setTile(const Color3B& tile, const Vec2& position)
{
    CCASSERT(_TGAInfo != nullptr, "tgaInfo must not be nil");
    CCASSERT(position.x < _TGAInfo->width, "Invalid position.x");
    CCASSERT(position.y < _TGAInfo->height, "Invalid position.x");
    CCASSERT(tile.r != 0, "R component must be non 0");

    Color3B *ptr = (Color3B*)_TGAInfo->imageData;
    Color3B value = ptr[(unsigned int)(position.x + position.y * _TGAInfo->width)];
    if( value.r == 0 )
    {
        CCLOG("cocos2d: Value.r must be non 0.");
    } 
    else
    {
        ptr[(unsigned int)(position.x + position.y * _TGAInfo->width)] = tile;

        // FIXME:: this method consumes a lot of memory
        // FIXME:: a tree of something like that shall be implemented
        std::string key = StringUtils::toString(position.x) + "," + StringUtils::toString(position.y);
        int num = _posToAtlasIndex[key].asInt();

        this->updateAtlasValueAt(position, tile, num);
    }    
}

Color3B TileMapAtlas::getTileAt(const Vec2& position) const
{
    CCASSERT( _TGAInfo != nullptr, "tgaInfo must not be nil");
    CCASSERT( position.x < _TGAInfo->width, "Invalid position.x");
    CCASSERT( position.y < _TGAInfo->height, "Invalid position.y");

    Color3B *ptr = (Color3B*)_TGAInfo->imageData;
    Color3B value = ptr[(unsigned int)(position.x + position.y * _TGAInfo->width)];

    return value;    
}

void TileMapAtlas::updateAtlasValueAt(const Vec2& pos, const Color3B& value, int index)
{
    CCASSERT( index >= 0 && index < _textureAtlas->getCapacity(), "updateAtlasValueAt: Invalid index");

    V3F_C4B_T2F_Quad* quad = &((_textureAtlas->getQuads())[index]);

    int x = pos.x;
    int y = pos.y;
    float row = (float) (value.r % _itemsPerRow);
    float col = (float) (value.r / _itemsPerRow);

    float textureWide = (float) (_textureAtlas->getTexture()->getPixelsWide());
    float textureHigh = (float) (_textureAtlas->getTexture()->getPixelsHigh());

    float itemWidthInPixels = _itemWidth * CC_CONTENT_SCALE_FACTOR();
    float itemHeightInPixels = _itemHeight * CC_CONTENT_SCALE_FACTOR();

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
    float left        = (2 * row * itemWidthInPixels + 1) / (2 * textureWide);
    float right       = left + (itemWidthInPixels * 2 - 2) / (2 * textureWide);
    float top         = (2 * col * itemHeightInPixels + 1) / (2 * textureHigh);
    float bottom      = top + (itemHeightInPixels * 2 - 2) / (2 * textureHigh);
#else
    float left        = (row * itemWidthInPixels) / textureWide;
    float right       = left + itemWidthInPixels / textureWide;
    float top         = (col * itemHeightInPixels) / textureHigh;
    float bottom      = top + itemHeightInPixels / textureHigh;
#endif

    quad->tl.texCoords.u = left;
    quad->tl.texCoords.v = top;
    quad->tr.texCoords.u = right;
    quad->tr.texCoords.v = top;
    quad->bl.texCoords.u = left;
    quad->bl.texCoords.v = bottom;
    quad->br.texCoords.u = right;
    quad->br.texCoords.v = bottom;

    quad->bl.vertices.x = (float) (x * _itemWidth);
    quad->bl.vertices.y = (float) (y * _itemHeight);
    quad->bl.vertices.z = 0.0f;
    quad->br.vertices.x = (float)(x * _itemWidth + _itemWidth);
    quad->br.vertices.y = (float)(y * _itemHeight);
    quad->br.vertices.z = 0.0f;
    quad->tl.vertices.x = (float)(x * _itemWidth);
    quad->tl.vertices.y = (float)(y * _itemHeight + _itemHeight);
    quad->tl.vertices.z = 0.0f;
    quad->tr.vertices.x = (float)(x * _itemWidth + _itemWidth);
    quad->tr.vertices.y = (float)(y * _itemHeight + _itemHeight);
    quad->tr.vertices.z = 0.0f;

    Color4B color(_displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity);
    quad->tr.colors = color;
    quad->tl.colors = color;
    quad->br.colors = color;
    quad->bl.colors = color;

    _textureAtlas->setDirty(true);
    ssize_t totalQuads = _textureAtlas->getTotalQuads();
    if (index + 1 > totalQuads) {
        _textureAtlas->increaseTotalQuadsWith(index + 1 - totalQuads);
    }
}

void TileMapAtlas::updateAtlasValues()
{
    CCASSERT( _TGAInfo != nullptr, "tgaInfo must be non-nil");

    int total = 0;

    for(int x=0;x < _TGAInfo->width; x++ ) 
    {
        for( int y=0; y < _TGAInfo->height; y++ ) 
        {
            if( total < _itemsToRender ) 
            {
                Color3B *ptr = (Color3B*) _TGAInfo->imageData;
                Color3B value = ptr[x + y * _TGAInfo->width];

                if( value.r != 0 )
                {
                    this->updateAtlasValueAt(Vec2(x,y), value, total);

                    std::string key = StringUtils::toString(x) + "," + StringUtils::toString(y);
                    _posToAtlasIndex[key] = total;

                    total++;
                }
            }
        }
    }
}


NS_CC_END
