/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
#include "CCFileUtils.h"
#include "CCTextureAtlas.h"
#include "support/image_support/TGAlib.h"
#include "ccConfig.h"

namespace cocos2d {


	// implementation CCTileMapAtlas

	CCTileMapAtlas * CCTileMapAtlas::tileMapAtlasWithTileFile(const char *tile, const char *mapFile, int tileWidth, int tileHeight)
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
			m_pPosToAtlasIndex = new StringToIntegerDictionary();
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
		if (m_pPosToAtlasIndex)
		{
			m_pPosToAtlasIndex->clear();
			delete m_pPosToAtlasIndex;
			m_pPosToAtlasIndex = NULL;
		}
	}
	void CCTileMapAtlas::releaseMap()
	{
		if (m_pTGAInfo)
		{
			tgaDestroy(m_pTGAInfo);
		}
		m_pTGAInfo = NULL;

		if (m_pPosToAtlasIndex)
		{
			m_pPosToAtlasIndex->clear();
			delete m_pPosToAtlasIndex;
			m_pPosToAtlasIndex = NULL;
		}
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

		//	//Find the path of the file
		//	NSBundle *mainBndl = [CCDirector sharedDirector].loadingBundle;
		//	CCString *resourcePath = [mainBndl resourcePath];
		//	CCString * path = [resourcePath stringByAppendingPathComponent:file];

		m_pTGAInfo = tgaLoad( CCFileUtils::fullPathFromRelativePath(file) );
	#if 1
		if( m_pTGAInfo->status != TGA_OK ) 
		{
			CCAssert(0, "TileMapAtlasLoadTGA : TileMapAtas cannot load TGA file");
		}
	#endif
	}

	// CCTileMapAtlas - Atlas generation / updates
	void CCTileMapAtlas::setTile(const ccColor3B& tile, const ccGridSize& position)
	{
		CCAssert( m_pTGAInfo != NULL, "tgaInfo must not be nil");
		CCAssert( m_pPosToAtlasIndex != NULL, "posToAtlasIndex must not be nil");
		CCAssert( position.x < m_pTGAInfo->width, "Invalid position.x");
		CCAssert( position.y < m_pTGAInfo->height, "Invalid position.x");
		CCAssert( tile.r != 0, "R component must be non 0");

		ccColor3B *ptr = (ccColor3B*)m_pTGAInfo->imageData;
		ccColor3B value = ptr[position.x + position.y * m_pTGAInfo->width];
		if( value.r == 0 )
		{
			CCLOG("cocos2d: Value.r must be non 0.");
		} 
		else
		{
			ptr[position.x + position.y * m_pTGAInfo->width] = tile;

			// XXX: this method consumes a lot of memory
			// XXX: a tree of something like that shall be impolemented
			char buffer[32];
			/*std::string key = itoa(position.x, buffer, 10);*/
			sprintf(buffer, "%d", position.x);
			std::string key = buffer;
			
			key += ",";
			/*key += itoa(position.y, buffer, 10);*/
			sprintf(buffer, "%d", position.y);
			key += buffer;

			int num = m_pPosToAtlasIndex->find(key)->second;
			this->updateAtlasValueAt(position, tile, num);
		}	
	}
	ccColor3B CCTileMapAtlas::tileAt(const ccGridSize& position)
	{
		CCAssert( m_pTGAInfo != NULL, "tgaInfo must not be nil");
		CCAssert( position.x < m_pTGAInfo->width, "Invalid position.x");
		CCAssert( position.y < m_pTGAInfo->height, "Invalid position.y");

		ccColor3B *ptr = (ccColor3B*)m_pTGAInfo->imageData;
		ccColor3B value = ptr[position.x + position.y * m_pTGAInfo->width];

		return value;	
	}
	void CCTileMapAtlas::updateAtlasValueAt(const ccGridSize& pos, const ccColor3B& value, unsigned int index)
	{
		ccV3F_C4B_T2F_Quad quad;

		int x = pos.x;
		int y = pos.y;
        float row = (float) (value.r % m_uItemsPerRow);
        float col = (float) (value.r / m_uItemsPerRow);

        float textureWide = (float) (m_pTextureAtlas->getTexture()->getPixelsWide());
        float textureHigh = (float) (m_pTextureAtlas->getTexture()->getPixelsHigh());

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        float left		= (2 * row * m_uItemWidth + 1) / (2 * textureWide);
        float right		= left + (m_uItemWidth * 2 - 2) / (2 * textureWide);
        float top		= (2 * col * m_uItemHeight + 1) / (2 * textureHigh);
        float bottom	= top + (m_uItemHeight * 2 - 2) / (2 * textureHigh);
#else
        float left		= (row * m_uItemWidth) / textureWide;
        float right		= left + m_uItemWidth / textureWide;
        float top		= (col * m_uItemHeight) / textureHigh;
        float bottom	= top + m_uItemHeight / textureHigh;
#endif

        quad.tl.texCoords.u = left;
        quad.tl.texCoords.v = top;
        quad.tr.texCoords.u = right;
        quad.tr.texCoords.v = top;
        quad.bl.texCoords.u = left;
        quad.bl.texCoords.v = bottom;
        quad.br.texCoords.u = right;
        quad.br.texCoords.v = bottom;

		quad.bl.vertices.x = (float) (x * m_uItemWidth);
		quad.bl.vertices.y = (float) (y * m_uItemHeight);
		quad.bl.vertices.z = 0.0f;
		quad.br.vertices.x = (float)(x * m_uItemWidth + m_uItemWidth);
		quad.br.vertices.y = (float)(y * m_uItemHeight);
		quad.br.vertices.z = 0.0f;
		quad.tl.vertices.x = (float)(x * m_uItemWidth);
		quad.tl.vertices.y = (float)(y * m_uItemHeight + m_uItemHeight);
		quad.tl.vertices.z = 0.0f;
		quad.tr.vertices.x = (float)(x * m_uItemWidth + m_uItemWidth);
		quad.tr.vertices.y = (float)(y * m_uItemHeight + m_uItemHeight);
		quad.tr.vertices.z = 0.0f;

		m_pTextureAtlas->updateQuad(&quad, index);
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
						this->updateAtlasValueAt(ccg(x,y), value, total);

						char buffer[32];
						/*std::string key = itoa(x, buffer, 10);*/
						sprintf(buffer, "%d", x);
						std::string key = buffer;

						key += ",";
						/*key += itoa(y, buffer, 10);*/
						sprintf(buffer, "%d", y);
						key += buffer;

						m_pPosToAtlasIndex->insert(StringToIntegerPair(key, total));

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

} // namespace cocos2d