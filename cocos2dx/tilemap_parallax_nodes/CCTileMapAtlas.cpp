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
#include "CCTileMapAtlas.h"
#include "platform/CCFileUtils.h"
#include "textures/CCTextureAtlas.h"
#include "support/image_support/TGAlib.h"
#include "ccConfig.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCInteger.h"
#include "CCDirector.h"
#include "support/CCPointExtension.h"

NS_CC_BEGIN

// implementation CCTileMapAtlas

CCTileMapAtlas * CCTileMapAtlas::create(const char *tile, const char *mapFile, int tileWidth, int tileHeight)
{
    CCTileMapAtlas *pRet = new CCTileMapAtlas();
    if (pRet->initWithTileFile(tile, mapFile, tileWidth, tileHeight))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCTileMapAtlas::initWithTileFile(const char *tile, const char *mapFile, int tileWidth, int tileHeight)
{
    this->loadTGAfile(mapFile);
    this->calculateItemsToRender();

    if( CCAtlasNode::initWithTileFile(tile, tileWidth, tileHeight, m_nItemsToRender) )
    {
        m_pPosToAtlasIndex = new CCDictionary();
        this->updateAtlasValues();
        this->setContentSize(CCSizeMake((float)(m_pTGAInfo->width*m_uItemWidth),
                                        (float)(m_pTGAInfo->height*m_uItemHeight)));
        return true;
    }
    return false;
}

CCTileMapAtlas::CCTileMapAtlas()
    :m_pTGAInfo(NULL)
    ,m_pPosToAtlasIndex(NULL)
    ,m_nItemsToRender(0)
{
}

CCTileMapAtlas::~CCTileMapAtlas()
{
    if (m_pTGAInfo)
    {
        tgaDestroy(m_pTGAInfo);
    }
    CC_SAFE_RELEASE(m_pPosToAtlasIndex);
}

void CCTileMapAtlas::releaseMap()
{
    if (m_pTGAInfo)
    {
        tgaDestroy(m_pTGAInfo);
    }
    m_pTGAInfo = NULL;

    CC_SAFE_RELEASE_NULL(m_pPosToAtlasIndex);
}

void CCTileMapAtlas::calculateItemsToRender()
{
    CCAssert( m_pTGAInfo != NULL, "tgaInfo must be non-nil");

    m_nItemsToRender = 0;
    for(int x=0;x < m_pTGAInfo->width; x++ ) 
    {
        for( int y=0; y < m_pTGAInfo->height; y++ ) 
        {
            ccColor3B *ptr = (ccColor3B*) m_pTGAInfo->imageData;
            ccColor3B value = ptr[x + y * m_pTGAInfo->width];
            if( value.r )
            {
                ++m_nItemsToRender;
            }
        }
    }
}

void CCTileMapAtlas::loadTGAfile(const char *file)
{
    CCAssert( file != NULL, "file must be non-nil");

    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(file);

    //    //Find the path of the file
    //    NSBundle *mainBndl = [CCDirector sharedDirector].loadingBundle;
    //    CCString *resourcePath = [mainBndl resourcePath];
    //    CCString * path = [resourcePath stringByAppendingPathComponent:file];

    m_pTGAInfo = tgaLoad( fullPath.c_str() );
#if 1
    if( m_pTGAInfo->status != TGA_OK ) 
    {
        CCAssert(0, "TileMapAtlasLoadTGA : TileMapAtlas cannot load TGA file");
    }
#endif
}

// CCTileMapAtlas - Atlas generation / updates
void CCTileMapAtlas::setTile(const ccColor3B& tile, const CCPoint& position)
{
    CCAssert(m_pTGAInfo != NULL, "tgaInfo must not be nil");
    CCAssert(m_pPosToAtlasIndex != NULL, "posToAtlasIndex must not be nil");
    CCAssert(position.x < m_pTGAInfo->width, "Invalid position.x");
    CCAssert(position.y < m_pTGAInfo->height, "Invalid position.x");
    CCAssert(tile.r != 0, "R component must be non 0");

    ccColor3B *ptr = (ccColor3B*)m_pTGAInfo->imageData;
    ccColor3B value = ptr[(unsigned int)(position.x + position.y * m_pTGAInfo->width)];
    if( value.r == 0 )
    {
        CCLOG("cocos2d: Value.r must be non 0.");
    } 
    else
    {
        ptr[(unsigned int)(position.x + position.y * m_pTGAInfo->width)] = tile;

        // XXX: this method consumes a lot of memory
        // XXX: a tree of something like that shall be implemented
        CCInteger *num = (CCInteger*)m_pPosToAtlasIndex->objectForKey(CCString::createWithFormat("%ld,%ld", 
                                                                                                 (long)position.x, 
                                                                                                 (long)position.y)->getCString());
        this->updateAtlasValueAt(position, tile, num->getValue());
    }    
}

ccColor3B CCTileMapAtlas::tileAt(const CCPoint& position)
{
    CCAssert( m_pTGAInfo != NULL, "tgaInfo must not be nil");
    CCAssert( position.x < m_pTGAInfo->width, "Invalid position.x");
    CCAssert( position.y < m_pTGAInfo->height, "Invalid position.y");

    ccColor3B *ptr = (ccColor3B*)m_pTGAInfo->imageData;
    ccColor3B value = ptr[(unsigned int)(position.x + position.y * m_pTGAInfo->width)];

    return value;    
}

void CCTileMapAtlas::updateAtlasValueAt(const CCPoint& pos, const ccColor3B& value, unsigned int index)
{
    CCAssert( index >= 0 && index < m_pTextureAtlas->getCapacity(), "updateAtlasValueAt: Invalid index");

    ccV3F_C4B_T2F_Quad* quad = &((m_pTextureAtlas->getQuads())[index]);

    int x = pos.x;
    int y = pos.y;
    float row = (float) (value.r % m_uItemsPerRow);
    float col = (float) (value.r / m_uItemsPerRow);

    float textureWide = (float) (m_pTextureAtlas->getTexture()->getPixelsWide());
    float textureHigh = (float) (m_pTextureAtlas->getTexture()->getPixelsHigh());

    float itemWidthInPixels = m_uItemWidth * CC_CONTENT_SCALE_FACTOR();
    float itemHeightInPixels = m_uItemHeight * CC_CONTENT_SCALE_FACTOR();

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

    quad->bl.vertices.x = (float) (x * m_uItemWidth);
    quad->bl.vertices.y = (float) (y * m_uItemHeight);
    quad->bl.vertices.z = 0.0f;
    quad->br.vertices.x = (float)(x * m_uItemWidth + m_uItemWidth);
    quad->br.vertices.y = (float)(y * m_uItemHeight);
    quad->br.vertices.z = 0.0f;
    quad->tl.vertices.x = (float)(x * m_uItemWidth);
    quad->tl.vertices.y = (float)(y * m_uItemHeight + m_uItemHeight);
    quad->tl.vertices.z = 0.0f;
    quad->tr.vertices.x = (float)(x * m_uItemWidth + m_uItemWidth);
    quad->tr.vertices.y = (float)(y * m_uItemHeight + m_uItemHeight);
    quad->tr.vertices.z = 0.0f;

    ccColor4B color = { _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity };
    quad->tr.colors = color;
    quad->tl.colors = color;
    quad->br.colors = color;
    quad->bl.colors = color;

    m_pTextureAtlas->setDirty(true);
    unsigned int totalQuads = m_pTextureAtlas->getTotalQuads();
    if (index + 1 > totalQuads) {
        m_pTextureAtlas->increaseTotalQuadsWith(index + 1 - totalQuads);
    }
}

void CCTileMapAtlas::updateAtlasValues()
{
    CCAssert( m_pTGAInfo != NULL, "tgaInfo must be non-nil");

    int total = 0;

    for(int x=0;x < m_pTGAInfo->width; x++ ) 
    {
        for( int y=0; y < m_pTGAInfo->height; y++ ) 
        {
            if( total < m_nItemsToRender ) 
            {
                ccColor3B *ptr = (ccColor3B*) m_pTGAInfo->imageData;
                ccColor3B value = ptr[x + y * m_pTGAInfo->width];

                if( value.r != 0 )
                {
                    this->updateAtlasValueAt(ccp(x,y), value, total);

                    CCString *key = CCString::createWithFormat("%d,%d", x,y);
                    CCInteger *num = CCInteger::create(total);
                    m_pPosToAtlasIndex->setObject(num, key->getCString());

                    total++;
                }
            }
        }
    }
}

void CCTileMapAtlas::setTGAInfo(struct sImageTGA* var)
{
    m_pTGAInfo = var;
}

struct sImageTGA * CCTileMapAtlas::getTGAInfo()
{
    return m_pTGAInfo;
}

NS_CC_END
