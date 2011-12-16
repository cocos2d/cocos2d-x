/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009-2010 Ricardo Quesada
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
#include "CCTMXLayer.h"
#include "CCTMXXMLParser.h"
#include "CCTMXTiledMap.h"
#include "CCSprite.h"
#include "CCTextureCache.h"
#include "CCPointExtension.h"
#include "support/data_support/ccCArray.h"
#include "CCDirector.h"

namespace cocos2d {


	// CCTMXLayer - init & alloc & dealloc
	CCTMXLayer * CCTMXLayer::layerWithTilesetInfo(CCTMXTilesetInfo *tilesetInfo, CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo)
	{
		CCTMXLayer *pRet = new CCTMXLayer();
		if (pRet->initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo))
		{
			pRet->autorelease();
			return pRet;
		}
		return NULL;
	}
	bool CCTMXLayer::initWithTilesetInfo(CCTMXTilesetInfo *tilesetInfo, CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo)
	{	
		// XXX: is 35% a good estimate ?
		CCSize size = layerInfo->m_tLayerSize;
		float totalNumberOfTiles = size.width * size.height;
		float capacity = totalNumberOfTiles * 0.35f + 1; // 35 percent is occupied ?

		CCTexture2D *texture = NULL;
		if( tilesetInfo )
		{
			texture = CCTextureCache::sharedTextureCache()->addImage(tilesetInfo->m_sSourceImage.c_str());
		}

		if (CCSpriteBatchNode::initWithTexture(texture, (unsigned int)capacity))
		{
			// layerInfo
			m_sLayerName = layerInfo->m_sName;
			m_tLayerSize = layerInfo->m_tLayerSize;
			m_pTiles = layerInfo->m_pTiles;
			m_uMinGID = layerInfo->m_uMinGID;
			m_uMaxGID = layerInfo->m_uMaxGID;
			m_cOpacity = layerInfo->m_cOpacity;
			m_pProperties = CCStringToStringDictionary::dictionaryWithDictionary(layerInfo->getProperties());
			m_fContentScaleFactor = CCDirector::sharedDirector()->getContentScaleFactor(); 

			// tilesetInfo
			m_pTileSet = tilesetInfo;
			CC_SAFE_RETAIN(m_pTileSet);

			// mapInfo
			m_tMapTileSize = mapInfo->getTileSize();
			m_uLayerOrientation = mapInfo->getOrientation();

			// offset (after layer orientation is set);
			CCPoint offset = this->calculateLayerOffset(layerInfo->m_tOffset);
			this->setPosition(offset);

			m_pAtlasIndexArray = ccCArrayNew((unsigned int)totalNumberOfTiles);

			this->setContentSizeInPixels(CCSizeMake(m_tLayerSize.width * m_tMapTileSize.width, m_tLayerSize.height * m_tMapTileSize.height));
                        m_tMapTileSize.width /= m_fContentScaleFactor;
                        m_tMapTileSize.height /= m_fContentScaleFactor;

			m_bUseAutomaticVertexZ = false;
			m_nVertexZvalue = 0;
			m_fAlphaFuncValue = 0;
			return true;
		}
		return false;
	}
	CCTMXLayer::CCTMXLayer()
        :m_tLayerSize(CCSizeZero)
        ,m_tMapTileSize(CCSizeZero)
        ,m_pTiles(NULL)
		,m_pTileSet(NULL)
		,m_pProperties(NULL)
        ,m_sLayerName("")
		,m_pReusedTile(NULL)
		,m_pAtlasIndexArray(NULL)	
	{}
	CCTMXLayer::~CCTMXLayer()
	{
		CC_SAFE_RELEASE(m_pTileSet);
		CC_SAFE_RELEASE(m_pReusedTile);
		CC_SAFE_RELEASE(m_pProperties);

		if( m_pAtlasIndexArray )
		{
			ccCArrayFree(m_pAtlasIndexArray);
			m_pAtlasIndexArray = NULL;
		}

		CC_SAFE_DELETE_ARRAY(m_pTiles);
	}
	CCTMXTilesetInfo * CCTMXLayer::getTileSet()
	{
		return m_pTileSet;
	}
	void CCTMXLayer::setTileSet(CCTMXTilesetInfo* var)
	{
		CC_SAFE_RETAIN(var);
		CC_SAFE_RELEASE(m_pTileSet);
		m_pTileSet = var;
	}
	void CCTMXLayer::releaseMap()
	{
		if( m_pTiles )
		{
			delete [] m_pTiles;
			m_pTiles = NULL;
		}

		if( m_pAtlasIndexArray )
		{
			ccCArrayFree(m_pAtlasIndexArray);
			m_pAtlasIndexArray = NULL;
		}
	}

	// CCTMXLayer - setup Tiles
	void CCTMXLayer::setupTiles()
	{	
		// Optimization: quick hack that sets the image size on the tileset
		m_pTileSet->m_tImageSize = m_pobTextureAtlas->getTexture()->getContentSizeInPixels();

		// By default all the tiles are aliased
		// pros:
		//  - easier to render
		// cons:
		//  - difficult to scale / rotate / etc.
		m_pobTextureAtlas->getTexture()->setAliasTexParameters();

		//CFByteOrder o = CFByteOrderGetCurrent();

		// Parse cocos2d properties
		this->parseInternalProperties();

		for( unsigned int y=0; y < m_tLayerSize.height; y++ ) 
		{
			for( unsigned int x=0; x < m_tLayerSize.width; x++ ) 
			{
				unsigned int pos = (unsigned int)(x + m_tLayerSize.width * y);
				unsigned int gid = m_pTiles[ pos ];

				// gid are stored in little endian.
				// if host is big endian, then swap
				//if( o == CFByteOrderBigEndian )
				//	gid = CFSwapInt32( gid );
				/* We support little endian.*/

				// XXX: gid == 0 --> empty tile
				if( gid != 0 ) 
				{
					this->appendTileForGID(gid, ccp((float)x, (float)y));

					// Optimization: update min and max GID rendered by the layer
					m_uMinGID = MIN(gid, m_uMinGID);
					m_uMaxGID = MAX(gid, m_uMaxGID);
				}
			}
		}

		CCAssert( m_uMaxGID >= m_pTileSet->m_uFirstGid &&
			m_uMinGID >= m_pTileSet->m_uFirstGid, "TMX: Only 1 tilset per layer is supported");	
	}

	// CCTMXLayer - Properties
	CCString *CCTMXLayer::propertyNamed(const char *propertyName)
	{
		return m_pProperties->objectForKey(std::string(propertyName));
	}
	void CCTMXLayer::parseInternalProperties()
	{
		// if cc_vertex=automatic, then tiles will be rendered using vertexz

		CCString *vertexz = propertyNamed("cc_vertexz");
		if( vertexz ) 
		{
			if( vertexz->m_sString == "automatic" )
			{
				m_bUseAutomaticVertexZ = true;
			}
			else
			{
				m_nVertexZvalue = vertexz->toInt();
			}
		}

		CCString *alphaFuncVal = propertyNamed("cc_alpha_func");
		if (alphaFuncVal)
		{
			m_fAlphaFuncValue = alphaFuncVal->toFloat();
		}
	}

	// CCTMXLayer - obtaining tiles/gids
	CCSprite * CCTMXLayer::tileAt(const CCPoint& pos)
	{
		CCAssert( pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
		CCAssert( m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");

		CCSprite *tile = NULL;
		unsigned int gid = this->tileGIDAt(pos);

		// if GID == 0, then no tile is present
		if( gid ) 
		{
			int z = (int)(pos.x + pos.y * m_tLayerSize.width);
			tile = (CCSprite*) this->getChildByTag(z);

			// tile not created yet. create it
			if( ! tile ) 
			{
				CCRect rect = m_pTileSet->rectForGID(gid);
                                rect = CCRectMake(rect.origin.x / m_fContentScaleFactor, rect.origin.y / m_fContentScaleFactor, rect.size.width/ m_fContentScaleFactor, rect.size.height/ m_fContentScaleFactor);

				tile = new CCSprite();
				tile->initWithBatchNode(this, rect);
				tile->setPosition(positionAt(pos));
				tile->setVertexZ((float)vertexZForPos(pos));
				tile->setAnchorPoint(CCPointZero);
				tile->setOpacity(m_cOpacity);

				unsigned int indexForZ = atlasIndexForExistantZ(z);
				this->addSpriteWithoutQuad(tile, indexForZ, z);
				tile->release();
			}
		}
		return tile;
	}
	unsigned int CCTMXLayer::tileGIDAt(const CCPoint& pos)
	{
		CCAssert( pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
		CCAssert( m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");

		int idx = (int)(pos.x + pos.y * m_tLayerSize.width);
		return m_pTiles[ idx ];
	}

	// CCTMXLayer - adding helper methods
	CCSprite * CCTMXLayer::insertTileForGID(unsigned int gid, const CCPoint& pos)
	{
		CCRect rect = m_pTileSet->rectForGID(gid);
                rect = CCRectMake(rect.origin.x / m_fContentScaleFactor, rect.origin.y / m_fContentScaleFactor, rect.size.width/ m_fContentScaleFactor, rect.size.height/ m_fContentScaleFactor);

		int z = (int)(pos.x + pos.y * m_tLayerSize.width);

		if( ! m_pReusedTile )
		{
			m_pReusedTile = new CCSprite();
			m_pReusedTile->initWithBatchNode(this, rect);
		}
		else
		{
			m_pReusedTile->initWithBatchNode(this, rect);
		}
		m_pReusedTile->setPositionInPixels(positionAt(pos));
		m_pReusedTile->setVertexZ((float)vertexZForPos(pos));
		m_pReusedTile->setAnchorPoint(CCPointZero);
		m_pReusedTile->setOpacity(m_cOpacity);

		// get atlas index
		unsigned int indexForZ = atlasIndexForNewZ(z);

		// Optimization: add the quad without adding a child
		this->addQuadFromSprite(m_pReusedTile, indexForZ);

		// insert it into the local atlasindex array
		ccCArrayInsertValueAtIndex(m_pAtlasIndexArray, (void*)z, indexForZ);

		// update possible children
		if (m_pChildren && m_pChildren->count()>0)
		{
            CCObject* pObject = NULL;
            CCARRAY_FOREACH(m_pChildren, pObject)
            {
                CCSprite* pChild = (CCSprite*) pObject;
                if (pChild)
                {
                    unsigned int ai = pChild->getAtlasIndex();
                    if ( ai >= indexForZ )
                    {
                        pChild->setAtlasIndex(ai+1);
                    }
                }
            }
		}
		m_pTiles[z] = gid;
		return m_pReusedTile;
	}
	CCSprite * CCTMXLayer::updateTileForGID(unsigned int gid, const CCPoint& pos)	
	{
		CCRect rect = m_pTileSet->rectForGID(gid);
                rect = CCRectMake(rect.origin.x / m_fContentScaleFactor, rect.origin.y / m_fContentScaleFactor, rect.size.width/ m_fContentScaleFactor, rect.size.height/ m_fContentScaleFactor);
		int z = (int)(pos.x + pos.y * m_tLayerSize.width);

		if( ! m_pReusedTile )
		{
			m_pReusedTile = new CCSprite();
			m_pReusedTile->initWithBatchNode(this, rect);
		}
		else
		{
			m_pReusedTile->initWithBatchNode(this, rect);
		}
		
		m_pReusedTile->setPositionInPixels(positionAt(pos));
		m_pReusedTile->setVertexZ((float)vertexZForPos(pos));
		m_pReusedTile->setAnchorPoint(CCPointZero);
		m_pReusedTile->setOpacity(m_cOpacity);

		// get atlas index
		unsigned int indexForZ = atlasIndexForExistantZ(z);
		m_pReusedTile->setAtlasIndex(indexForZ);
        m_pReusedTile->setDirty(true);
		m_pReusedTile->updateTransform();
		m_pTiles[z] = gid;

		return m_pReusedTile;
	}

	// used only when parsing the map. useless after the map was parsed
	// since lot's of assumptions are no longer true
	CCSprite * CCTMXLayer::appendTileForGID(unsigned int gid, const CCPoint& pos)
	{
		CCRect rect = m_pTileSet->rectForGID(gid);
                rect = CCRectMake(rect.origin.x / m_fContentScaleFactor, rect.origin.y / m_fContentScaleFactor, rect.size.width/ m_fContentScaleFactor, rect.size.height/ m_fContentScaleFactor);

		int z = (int)(pos.x + pos.y * m_tLayerSize.width);

		if( ! m_pReusedTile )
		{
			m_pReusedTile = new CCSprite();
			m_pReusedTile->initWithBatchNode(this, rect);
		}
		else
		{
			m_pReusedTile->initWithBatchNode(this, rect);
		}
		
		m_pReusedTile->setPosition(positionAt(pos));
		m_pReusedTile->setVertexZ((float)vertexZForPos(pos));
		m_pReusedTile->setAnchorPoint(CCPointZero);
		m_pReusedTile->setOpacity(m_cOpacity);

		// optimization:
		// The difference between appendTileForGID and insertTileforGID is that append is faster, since
		// it appends the tile at the end of the texture atlas
		unsigned int indexForZ = m_pAtlasIndexArray->num;

		// don't add it using the "standard" way.
		addQuadFromSprite(m_pReusedTile, indexForZ);

		// append should be after addQuadFromSprite since it modifies the quantity values
		ccCArrayInsertValueAtIndex(m_pAtlasIndexArray, (void*)z, indexForZ);

		return m_pReusedTile;
	}

	// CCTMXLayer - atlasIndex and Z
	static inline int compareInts(const void * a, const void * b)
	{
		return ( *(int*)a - *(int*)b );
	}
	unsigned int CCTMXLayer::atlasIndexForExistantZ(unsigned int z)
	{
		int key=z;
		int *item = (int*)bsearch((void*)&key, (void*)&m_pAtlasIndexArray->arr[0], m_pAtlasIndexArray->num, sizeof(void*), compareInts);

		CCAssert( item, "TMX atlas index not found. Shall not happen");

        int index = ((size_t)item - (size_t)m_pAtlasIndexArray->arr) / sizeof(void*);
		return index;
	}
	unsigned int CCTMXLayer::atlasIndexForNewZ(int z)
	{
		// XXX: This can be improved with a sort of binary search
		unsigned int i=0;
		for( i=0; i< m_pAtlasIndexArray->num ; i++) 
		{
            int val = (size_t) m_pAtlasIndexArray->arr[i];
			if( z < val )
				break;
		}	
		return i;
	}

	// CCTMXLayer - adding / remove tiles
	void CCTMXLayer::setTileGID(unsigned int gid, const CCPoint& pos)
	{
		CCAssert( pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
		CCAssert( m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");
        CCAssert( gid == 0 || gid >= m_pTileSet->m_uFirstGid, "TMXLayer: invalid gid" );

		unsigned int currentGID = tileGIDAt(pos);

		if( currentGID != gid ) 
		{
			// setting gid=0 is equal to remove the tile
			if( gid == 0 )
			{
				removeTileAt(pos);
			}

			// empty tile. create a new one
			else if( currentGID == 0 )
			{
				insertTileForGID(gid, pos);
			}

			// modifying an existing tile with a non-empty tile
			else 
			{
				unsigned int z = (unsigned int)(pos.x + pos.y * m_tLayerSize.width);
				CCSprite *sprite = (CCSprite*)getChildByTag(z);
				if( sprite )
				{
					CCRect rect = m_pTileSet->rectForGID(gid);
                                        rect = CCRectMake(rect.origin.x / m_fContentScaleFactor, rect.origin.y / m_fContentScaleFactor, rect.size.width/ m_fContentScaleFactor, rect.size.height/ m_fContentScaleFactor);

					sprite->setTextureRectInPixels(rect, false, rect.size);
					m_pTiles[z] = gid;
				} 
				else 
				{
					updateTileForGID(gid, pos);
				}
			}
		}
	}
	void CCTMXLayer::addChild(CCNode * child, int zOrder, int tag)
	{
        CC_UNUSED_PARAM(child);
        CC_UNUSED_PARAM(zOrder);
        CC_UNUSED_PARAM(tag);
		CCAssert(0, "addChild: is not supported on CCTMXLayer. Instead use setTileGID:at:/tileAt:");
	}
	void CCTMXLayer::removeChild(CCNode* node, bool cleanup)
	{
		CCSprite *sprite = (CCSprite*)node;
		// allows removing nil objects
		if( ! sprite )
			return;

		CCAssert( m_pChildren->containsObject(sprite), "Tile does not belong to TMXLayer");

		unsigned int atlasIndex = sprite->getAtlasIndex();
        unsigned int zz = (size_t) m_pAtlasIndexArray->arr[atlasIndex];
		m_pTiles[zz] = 0;
		ccCArrayRemoveValueAtIndex(m_pAtlasIndexArray, atlasIndex);
		CCSpriteBatchNode::removeChild(sprite, cleanup);
	}
	void CCTMXLayer::removeTileAt(const CCPoint& pos)
	{
		CCAssert( pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
		CCAssert( m_pTiles && m_pAtlasIndexArray, "TMXLayer: the tiles map has been released");

		unsigned int gid = tileGIDAt(pos);

		if( gid ) 
		{
			unsigned int z = (unsigned int)(pos.x + pos.y * m_tLayerSize.width);
			unsigned int atlasIndex = atlasIndexForExistantZ(z);

			// remove tile from GID map
			m_pTiles[z] = 0;

			// remove tile from atlas position array
			ccCArrayRemoveValueAtIndex(m_pAtlasIndexArray, atlasIndex);

			// remove it from sprites and/or texture atlas
			CCSprite *sprite = (CCSprite*)getChildByTag(z);
			if( sprite )
			{
				CCSpriteBatchNode::removeChild(sprite, true);
			}
			else 
			{
				m_pobTextureAtlas->removeQuadAtIndex(atlasIndex);

				// update possible children
				if (m_pChildren && m_pChildren->count()>0)
				{
                    CCObject* pObject = NULL;
                    CCARRAY_FOREACH(m_pChildren, pObject)
                    {
                        CCSprite* pChild = (CCSprite*) pObject;
                        if (pChild)
                        {
                            unsigned int ai = pChild->getAtlasIndex();
                            if ( ai >= atlasIndex )
                            {
                                pChild->setAtlasIndex(ai-1);
                            }
                        }
                    }
				}
			}
		}
	}

	//CCTMXLayer - obtaining positions, offset
	CCPoint CCTMXLayer::calculateLayerOffset(const CCPoint& pos)
	{
		CCPoint ret = CCPointZero;
		switch( m_uLayerOrientation ) 
		{
		case CCTMXOrientationOrtho:
			ret = ccp( pos.x * m_tMapTileSize.width, -pos.y *m_tMapTileSize.height);
			break;
		case CCTMXOrientationIso:
			ret = ccp( (m_tMapTileSize.width /2) * (pos.x - pos.y),
				(m_tMapTileSize.height /2 ) * (-pos.x - pos.y) );
			break;
		case CCTMXOrientationHex:
			CCAssert(CCPoint::CCPointEqualToPoint(pos, CCPointZero), "offset for hexagonal map not implemented yet");
			break;
		}
		return ret;	
	}
	CCPoint CCTMXLayer::positionAt(const CCPoint& pos)
	{
		CCPoint ret = CCPointZero;
		switch( m_uLayerOrientation )
		{
		case CCTMXOrientationOrtho:
			ret = positionForOrthoAt(pos);
			break;
		case CCTMXOrientationIso:
			ret = positionForIsoAt(pos);
			break;
		case CCTMXOrientationHex:
			ret = positionForHexAt(pos);
			break;
		}
		return ret;
	}
	CCPoint CCTMXLayer::positionForOrthoAt(const CCPoint& pos)
	{
        CCPoint xy = CCPointMake(pos.x * m_tMapTileSize.width,
                                (m_tLayerSize.height - pos.y - 1) * m_tMapTileSize.height);
        return xy;
	}
	CCPoint CCTMXLayer::positionForIsoAt(const CCPoint& pos)
	{
        CCPoint xy = CCPointMake(m_tMapTileSize.width /2 * ( m_tLayerSize.width + pos.x - pos.y - 1),
                                 m_tMapTileSize.height /2 * (( m_tLayerSize.height * 2 - pos.x - pos.y) - 2));
        return xy;
	}
	CCPoint CCTMXLayer::positionForHexAt(const CCPoint& pos)
	{
		float diffY = 0;
		if( (int)pos.x % 2 == 1 )
		{
			diffY = -m_tMapTileSize.height/2 ;
		}

        CCPoint xy = CCPointMake(pos.x * m_tMapTileSize.width*3/4,
                                (m_tLayerSize.height - pos.y - 1) * m_tMapTileSize.height + diffY);
        return xy;
	}
	int CCTMXLayer::vertexZForPos(const CCPoint& pos)
	{
		int ret = 0;
		unsigned int maxVal = 0;
		if( m_bUseAutomaticVertexZ )
		{
			switch( m_uLayerOrientation ) 
			{
			case CCTMXOrientationIso:
				maxVal = (unsigned int)(m_tLayerSize.width + m_tLayerSize.height);
				ret = (int)(-(maxVal - (pos.x + pos.y)));
				break;
			case CCTMXOrientationOrtho:
				ret = (int)(-(m_tLayerSize.height-pos.y));
				break;
			case CCTMXOrientationHex:
				CCAssert(0, "TMX Hexa zOrder not supported");
				break;
			default:
				CCAssert(0, "TMX invalid value");
				break;
			}
		} 
		else
		{
			ret = m_nVertexZvalue;
		}
		return ret;
	}

	// CCTMXLayer - draw
	void CCTMXLayer::draw()
	{
		if( m_bUseAutomaticVertexZ )
		{
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, m_fAlphaFuncValue);
		}

		CCSpriteBatchNode::draw();

		if( m_bUseAutomaticVertexZ )
		{
			glDisable(GL_ALPHA_TEST);
		}
	}

	CCStringToStringDictionary * CCTMXLayer::getProperties()
	{
		return m_pProperties;
	}
	void CCTMXLayer::setProperties(CCStringToStringDictionary* var)
	{
		CC_SAFE_RETAIN(var);
		CC_SAFE_RELEASE(m_pProperties);
		m_pProperties = var;
	}

}// namespace cocos2d

