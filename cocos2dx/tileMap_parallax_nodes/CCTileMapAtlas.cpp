/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCXFileUtils.h"
#include "CCTextureAtlas.h"

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
		CCX_SAFE_DELETE(pRet);
		return NULL;
	}
	bool CCTileMapAtlas::initWithTileFile(const char *tile, const char *mapFile, int tileWidth, int tileHeight)
	{
		this->loadTGAfile(mapFile);
		this->calculateItemsToRender();
		if( __super::initWithTileFile(tile, tileWidth, tileHeight, m_nItemsToRender) )
		{
			m_pPosToAtlasIndex = new StringToIntegerDictionary();
			this->updateAtlasValues();
			this->setContentSize(CGSizeMake((float)(m_pTGAInfo->width*m_nItemWidth),
											(float)(m_pTGAInfo->height*m_nItemHeight)));
			return true;
		}
		return false;
	}
	CCTileMapAtlas::CCTileMapAtlas()
		:m_pPosToAtlasIndex(NULL)
		,m_pTGAInfo(NULL)
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
		NSAssert( m_pTGAInfo != NULL, "tgaInfo must be non-nil");

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
		NSAssert( file != NULL, "file must be non-nil");

		//	//Find the path of the file
		//	NSBundle *mainBndl = [CCDirector sharedDirector].loadingBundle;
		//	NSString *resourcePath = [mainBndl resourcePath];
		//	NSString * path = [resourcePath stringByAppendingPathComponent:file];

		m_pTGAInfo = tgaLoad( CCFileUtils::fullPathFromRelativePath(file) );
	#if 1
		if( m_pTGAInfo->status != TGA_OK ) 
		{
			NSAssert(0, "TileMapAtlasLoadTGA : TileMapAtas cannot load TGA file");
		}
	#endif
	}

	// CCTileMapAtlas - Atlas generation / updates
	void CCTileMapAtlas::setTile(ccColor3B tile, ccGridSize position)
	{
		NSAssert( m_pTGAInfo != NULL, "tgaInfo must not be nil");
		NSAssert( m_pPosToAtlasIndex != NULL, "posToAtlasIndex must not be nil");
		NSAssert( position.x < m_pTGAInfo->width, "Invalid position.x");
		NSAssert( position.y < m_pTGAInfo->height, "Invalid position.x");
		NSAssert( tile.r != 0, "R component must be non 0");

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
			std::string key = itoa(position.x, buffer, 10);
			key += ",";
			key += itoa(position.y, buffer, 10);
			int num = m_pPosToAtlasIndex->find(key)->second;
			this->updateAtlasValueAt(position, tile, num);
		}	
	}
	ccColor3B CCTileMapAtlas::tileAt(ccGridSize position)
	{
		NSAssert( m_pTGAInfo != NULL, "tgaInfo must not be nil");
		NSAssert( position.x < m_pTGAInfo->width, "Invalid position.x");
		NSAssert( position.y < m_pTGAInfo->height, "Invalid position.y");

		ccColor3B *ptr = (ccColor3B*)m_pTGAInfo->imageData;
		ccColor3B value = ptr[position.x + position.y * m_pTGAInfo->width];

		return value;	
	}
	void CCTileMapAtlas::updateAtlasValueAt(ccGridSize pos, ccColor3B value, int index)
	{
		ccV3F_C4B_T2F_Quad quad;

		int x = pos.x;
		int y = pos.y;
		float row = (value.r % m_nItemsPerRow) * m_fTexStepX;
		float col = (value.r / m_nItemsPerRow) * m_fTexStepY;

		quad.tl.texCoords.u = row;
		quad.tl.texCoords.v = col;
		quad.tr.texCoords.u = row + m_fTexStepX;
		quad.tr.texCoords.v = col;
		quad.bl.texCoords.u = row;
		quad.bl.texCoords.v = col + m_fTexStepY;
		quad.br.texCoords.u = row + m_fTexStepX;
		quad.br.texCoords.v = col + m_fTexStepY;

		quad.bl.vertices.x = (float) (x * m_nItemWidth);
		quad.bl.vertices.y = (float) (y * m_nItemHeight);
		quad.bl.vertices.z = 0.0f;
		quad.br.vertices.x = (float)(x * m_nItemWidth + m_nItemWidth);
		quad.br.vertices.y = (float)(y * m_nItemHeight);
		quad.br.vertices.z = 0.0f;
		quad.tl.vertices.x = (float)(x * m_nItemWidth);
		quad.tl.vertices.y = (float)(y * m_nItemHeight + m_nItemHeight);
		quad.tl.vertices.z = 0.0f;
		quad.tr.vertices.x = (float)(x * m_nItemWidth + m_nItemWidth);
		quad.tr.vertices.y = (float)(y * m_nItemHeight + m_nItemHeight);
		quad.tr.vertices.z = 0.0f;

		m_pTextureAtlas->updateQuad(&quad, index);
	}
	void CCTileMapAtlas::updateAtlasValues()
	{
		NSAssert( m_pTGAInfo != NULL, "tgaInfo must be non-nil");

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
						std::string key = itoa(x, buffer, 10);
						key += ",";
						key += itoa(y, buffer, 10);
						m_pPosToAtlasIndex->insert(StringToIntegerPair(key, total));

						total++;
					}
				}
			}
		}
	}
	void CCTileMapAtlas::setTGAInfo(tImageTGA* var)
	{
		m_pTGAInfo = var;
	}
	tImageTGA * CCTileMapAtlas::getTGAInfo()
	{
		return m_pTGAInfo;
	}

} // namespace cocos2d