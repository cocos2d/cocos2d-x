/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "sprite_nodes/CCSprite.h"
#include "textures/CCTextureCache.h"
#include "shaders/CCShaderCache.h"
#include "shaders/CCGLProgram.h"
#include "support/CCPointExtension.h"
#include "support/data_support/ccCArray.h"
#include "CCDirector.h"

NS_CC_BEGIN


// CCTMXLayer - init & alloc & dealloc

CCTMXLayer * CCTMXLayer::create(CCTMXTilesetInfo *tilesetInfo, CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo)
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
    CCSize size = layerInfo->_layerSize;
    float totalNumberOfTiles = size.width * size.height;
    float capacity = totalNumberOfTiles * 0.35f + 1; // 35 percent is occupied ?

    CCTexture2D *texture = NULL;
    if( tilesetInfo )
    {
        texture = CCTextureCache::sharedTextureCache()->addImage(tilesetInfo->_sourceImage.c_str());
    }

    if (CCSpriteBatchNode::initWithTexture(texture, (unsigned int)capacity))
    {
        // layerInfo
        _layerName = layerInfo->_name;
        _layerSize = size;
        _tiles = layerInfo->_tiles;
        _minGID = layerInfo->_minGID;
        _maxGID = layerInfo->_maxGID;
        _opacity = layerInfo->_opacity;
        setProperties(CCDictionary::createWithDictionary(layerInfo->getProperties()));
        _contentScaleFactor = CCDirector::sharedDirector()->getContentScaleFactor(); 

        // tilesetInfo
        _tileSet = tilesetInfo;
        CC_SAFE_RETAIN(_tileSet);

        // mapInfo
        _mapTileSize = mapInfo->getTileSize();
        _layerOrientation = mapInfo->getOrientation();

        // offset (after layer orientation is set);
        CCPoint offset = this->calculateLayerOffset(layerInfo->_offset);
        this->setPosition(CC_POINT_PIXELS_TO_POINTS(offset));

        _atlasIndexArray = ccCArrayNew((unsigned int)totalNumberOfTiles);

        this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(CCSizeMake(_layerSize.width * _mapTileSize.width, _layerSize.height * _mapTileSize.height)));

        _useAutomaticVertexZ = false;
        _vertexZvalue = 0;
        
        return true;
    }
    return false;
}

CCTMXLayer::CCTMXLayer()
:_layerSize(CCSizeZero)
,_mapTileSize(CCSizeZero)
,_tiles(NULL)
,_tileSet(NULL)
,_properties(NULL)
,_layerName("")
,_reusedTile(NULL)
,_atlasIndexArray(NULL)    
{}

CCTMXLayer::~CCTMXLayer()
{
    CC_SAFE_RELEASE(_tileSet);
    CC_SAFE_RELEASE(_reusedTile);
    CC_SAFE_RELEASE(_properties);

    if (_atlasIndexArray)
    {
        ccCArrayFree(_atlasIndexArray);
        _atlasIndexArray = NULL;
    }

    CC_SAFE_DELETE_ARRAY(_tiles);
}

CCTMXTilesetInfo * CCTMXLayer::getTileSet()
{
    return _tileSet;
}

void CCTMXLayer::setTileSet(CCTMXTilesetInfo* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_tileSet);
    _tileSet = var;
}

void CCTMXLayer::releaseMap()
{
    if (_tiles)
    {
        delete [] _tiles;
        _tiles = NULL;
    }

    if (_atlasIndexArray)
    {
        ccCArrayFree(_atlasIndexArray);
        _atlasIndexArray = NULL;
    }
}

// CCTMXLayer - setup Tiles
void CCTMXLayer::setupTiles()
{    
    // Optimization: quick hack that sets the image size on the tileset
    _tileSet->_imageSize = _textureAtlas->getTexture()->getContentSizeInPixels();

    // By default all the tiles are aliased
    // pros:
    //  - easier to render
    // cons:
    //  - difficult to scale / rotate / etc.
    _textureAtlas->getTexture()->setAliasTexParameters();

    //CFByteOrder o = CFByteOrderGetCurrent();

    // Parse cocos2d properties
    this->parseInternalProperties();

    for (unsigned int y=0; y < _layerSize.height; y++) 
    {
        for (unsigned int x=0; x < _layerSize.width; x++) 
        {
            unsigned int pos = (unsigned int)(x + _layerSize.width * y);
            unsigned int gid = _tiles[ pos ];

            // gid are stored in little endian.
            // if host is big endian, then swap
            //if( o == CFByteOrderBigEndian )
            //    gid = CFSwapInt32( gid );
            /* We support little endian.*/

            // XXX: gid == 0 --> empty tile
            if (gid != 0) 
            {
                this->appendTileForGID(gid, ccp(x, y));

                // Optimization: update min and max GID rendered by the layer
                _minGID = MIN(gid, _minGID);
                _maxGID = MAX(gid, _maxGID);
            }
        }
    }

    CCAssert( _maxGID >= _tileSet->_firstGid &&
        _minGID >= _tileSet->_firstGid, "TMX: Only 1 tileset per layer is supported");    
}

// CCTMXLayer - Properties
CCString* CCTMXLayer::propertyNamed(const char *propertyName)
{
    return (CCString*)_properties->objectForKey(propertyName);
}

void CCTMXLayer::parseInternalProperties()
{
    // if cc_vertex=automatic, then tiles will be rendered using vertexz

    CCString *vertexz = propertyNamed("cc_vertexz");
    if (vertexz) 
    {
        // If "automatic" is on, then parse the "cc_alpha_func" too
        if (vertexz->_string == "automatic")
        {
            _useAutomaticVertexZ = true;
            CCString *alphaFuncVal = propertyNamed("cc_alpha_func");
            float alphaFuncValue = 0.0f;
            if (alphaFuncVal != NULL)
            {
                alphaFuncValue = alphaFuncVal->floatValue();
            }
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest));

            GLint alphaValueLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kCCUniformAlphaTestValue);

            // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
            getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, alphaFuncValue);
        }
        else
        {
            _vertexZvalue = vertexz->intValue();
        }
    }
}

void CCTMXLayer::setupTileSprite(CCSprite* sprite, CCPoint pos, unsigned int gid)
{
    sprite->setPosition(positionAt(pos));
    sprite->setVertexZ((float)vertexZForPos(pos));
    sprite->setAnchorPoint(CCPointZero);
    sprite->setOpacity(_opacity);

    //issue 1264, flip can be undone as well
    sprite->setFlipX(false);
    sprite->setFlipY(false);
    sprite->setRotation(0.0f);
    sprite->setAnchorPoint(ccp(0,0));

    // Rotation in tiled is achieved using 3 flipped states, flipping across the horizontal, vertical, and diagonal axes of the tiles.
    if (gid & kCCTMXTileDiagonalFlag)
    {
        // put the anchor in the middle for ease of rotation.
        sprite->setAnchorPoint(ccp(0.5f,0.5f));
        sprite->setPosition(ccp(positionAt(pos).x + sprite->getContentSize().height/2,
           positionAt(pos).y + sprite->getContentSize().width/2 ) );

        unsigned int flag = gid & (kCCTMXTileHorizontalFlag | kCCTMXTileVerticalFlag );

        // handle the 4 diagonally flipped states.
        if (flag == kCCTMXTileHorizontalFlag)
        {
            sprite->setRotation(90.0f);
        }
        else if (flag == kCCTMXTileVerticalFlag)
        {
            sprite->setRotation(270.0f);
        }
        else if (flag == (kCCTMXTileVerticalFlag | kCCTMXTileHorizontalFlag) )
        {
            sprite->setRotation(90.0f);
            sprite->setFlipX(true);
        }
        else
        {
            sprite->setRotation(270.0f);
            sprite->setFlipX(true);
        }
    }
    else
    {
        if (gid & kCCTMXTileHorizontalFlag)
        {
            sprite->setFlipX(true);
        }

        if (gid & kCCTMXTileVerticalFlag)
        {
            sprite->setFlipY(true);
        }
    }
}

CCSprite* CCTMXLayer::reusedTileWithRect(CCRect rect)
{
    if (! _reusedTile) 
    {
        _reusedTile = new CCSprite();
        _reusedTile->initWithTexture(_textureAtlas->getTexture(), rect, false);
        _reusedTile->setBatchNode(this);
    }
    else
    {
        // XXX HACK: Needed because if "batch node" is nil,
		// then the Sprite'squad will be reset
        _reusedTile->setBatchNode(NULL);
        
		// Re-init the sprite
        _reusedTile->setTextureRect(rect, false, rect.size);
        
		// restore the batch node
        _reusedTile->setBatchNode(this);
    }

    return _reusedTile;
}

// CCTMXLayer - obtaining tiles/gids
CCSprite * CCTMXLayer::tileAt(const CCPoint& pos)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");

    CCSprite *tile = NULL;
    unsigned int gid = this->tileGIDAt(pos);

    // if GID == 0, then no tile is present
    if (gid) 
    {
        int z = (int)(pos.x + pos.y * _layerSize.width);
        tile = (CCSprite*) this->getChildByTag(z);

        // tile not created yet. create it
        if (! tile) 
        {
            CCRect rect = _tileSet->rectForGID(gid);
            rect = CC_RECT_PIXELS_TO_POINTS(rect);

            tile = new CCSprite();
            tile->initWithTexture(this->getTexture(), rect);
            tile->setBatchNode(this);
            tile->setPosition(positionAt(pos));
            tile->setVertexZ((float)vertexZForPos(pos));
            tile->setAnchorPoint(CCPointZero);
            tile->setOpacity(_opacity);

            unsigned int indexForZ = atlasIndexForExistantZ(z);
            this->addSpriteWithoutQuad(tile, indexForZ, z);
            tile->release();
        }
    }
    
    return tile;
}

unsigned int CCTMXLayer::tileGIDAt(const CCPoint& pos)
{
    return tileGIDAt(pos, NULL);
}

unsigned int CCTMXLayer::tileGIDAt(const CCPoint& pos, ccTMXTileFlags* flags)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");

    int idx = (int)(pos.x + pos.y * _layerSize.width);
    // Bits on the far end of the 32-bit global tile ID are used for tile flags
    unsigned int tile = _tiles[idx];

    // issue1264, flipped tiles can be changed dynamically
    if (flags) 
    {
        *flags = (ccTMXTileFlags)(tile & kCCFlipedAll);
    }
    
    return (tile & kCCFlippedMask);
}

// CCTMXLayer - adding helper methods
CCSprite * CCTMXLayer::insertTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCRect rect = _tileSet->rectForGID(gid);
    rect = CC_RECT_PIXELS_TO_POINTS(rect);

    intptr_t z = (intptr_t)(pos.x + pos.y * _layerSize.width);

    CCSprite *tile = reusedTileWithRect(rect);

    setupTileSprite(tile, pos, gid);

    // get atlas index
    unsigned int indexForZ = atlasIndexForNewZ(z);

    // Optimization: add the quad without adding a child
    this->insertQuadFromSprite(tile, indexForZ);

    // insert it into the local atlasindex array
    ccCArrayInsertValueAtIndex(_atlasIndexArray, (void*)z, indexForZ);

    // update possible children
    if (_children && _children->count()>0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
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
    _tiles[z] = gid;
    return tile;
}
CCSprite * CCTMXLayer::updateTileForGID(unsigned int gid, const CCPoint& pos)    
{
    CCRect rect = _tileSet->rectForGID(gid);
    rect = CCRectMake(rect.origin.x / _contentScaleFactor, rect.origin.y / _contentScaleFactor, rect.size.width/ _contentScaleFactor, rect.size.height/ _contentScaleFactor);
    int z = (int)(pos.x + pos.y * _layerSize.width);

    CCSprite *tile = reusedTileWithRect(rect);

    setupTileSprite(tile ,pos ,gid);

    // get atlas index
    unsigned int indexForZ = atlasIndexForExistantZ(z);
    tile->setAtlasIndex(indexForZ);
    tile->setDirty(true);
    tile->updateTransform();
    _tiles[z] = gid;

    return tile;
}

// used only when parsing the map. useless after the map was parsed
// since lot's of assumptions are no longer true
CCSprite * CCTMXLayer::appendTileForGID(unsigned int gid, const CCPoint& pos)
{
    CCRect rect = _tileSet->rectForGID(gid);
    rect = CC_RECT_PIXELS_TO_POINTS(rect);

    intptr_t z = (intptr_t)(pos.x + pos.y * _layerSize.width);

    CCSprite *tile = reusedTileWithRect(rect);

    setupTileSprite(tile ,pos ,gid);

    // optimization:
    // The difference between appendTileForGID and insertTileforGID is that append is faster, since
    // it appends the tile at the end of the texture atlas
    unsigned int indexForZ = _atlasIndexArray->num;

    // don't add it using the "standard" way.
    insertQuadFromSprite(tile, indexForZ);

    // append should be after addQuadFromSprite since it modifies the quantity values
    ccCArrayInsertValueAtIndex(_atlasIndexArray, (void*)z, indexForZ);

    return tile;
}

// CCTMXLayer - atlasIndex and Z
static inline int compareInts(const void * a, const void * b)
{
    return ((*(int*)a) - (*(int*)b));
}
unsigned int CCTMXLayer::atlasIndexForExistantZ(unsigned int z)
{
    int key=z;
    int *item = (int*)bsearch((void*)&key, (void*)&_atlasIndexArray->arr[0], _atlasIndexArray->num, sizeof(void*), compareInts);

    CCAssert(item, "TMX atlas index not found. Shall not happen");

    int index = ((size_t)item - (size_t)_atlasIndexArray->arr) / sizeof(void*);
    return index;
}
unsigned int CCTMXLayer::atlasIndexForNewZ(int z)
{
    // XXX: This can be improved with a sort of binary search
    unsigned int i=0;
    for (i=0; i< _atlasIndexArray->num ; i++) 
    {
        int val = (size_t) _atlasIndexArray->arr[i];
        if (z < val)
        {
            break;
        }
    } 
    
    return i;
}

// CCTMXLayer - adding / remove tiles
void CCTMXLayer::setTileGID(unsigned int gid, const CCPoint& pos)
{
    setTileGID(gid, pos, (ccTMXTileFlags)0);
}

void CCTMXLayer::setTileGID(unsigned int gid, const CCPoint& pos, ccTMXTileFlags flags)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");
    CCAssert(gid == 0 || gid >= _tileSet->_firstGid, "TMXLayer: invalid gid" );

    ccTMXTileFlags currentFlags;
    unsigned int currentGID = tileGIDAt(pos, &currentFlags);

    if (currentGID != gid || currentFlags != flags) 
    {
        unsigned gidAndFlags = gid | flags;

        // setting gid=0 is equal to remove the tile
        if (gid == 0)
        {
            removeTileAt(pos);
        }
        // empty tile. create a new one
        else if (currentGID == 0)
        {
            insertTileForGID(gidAndFlags, pos);
        }
        // modifying an existing tile with a non-empty tile
        else 
        {
            unsigned int z = (unsigned int)(pos.x + pos.y * _layerSize.width);
            CCSprite *sprite = (CCSprite*)getChildByTag(z);
            if (sprite)
            {
                CCRect rect = _tileSet->rectForGID(gid);
                rect = CC_RECT_PIXELS_TO_POINTS(rect);

                sprite->setTextureRect(rect, false, rect.size);
                if (flags) 
                {
                    setupTileSprite(sprite, sprite->getPosition(), gidAndFlags);
                }
                _tiles[z] = gidAndFlags;
            } 
            else 
            {
                updateTileForGID(gidAndFlags, pos);
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
    if (! sprite)
    {
        return;
    }

    CCAssert(_children->containsObject(sprite), "Tile does not belong to TMXLayer");

    unsigned int atlasIndex = sprite->getAtlasIndex();
    unsigned int zz = (size_t)_atlasIndexArray->arr[atlasIndex];
    _tiles[zz] = 0;
    ccCArrayRemoveValueAtIndex(_atlasIndexArray, atlasIndex);
    CCSpriteBatchNode::removeChild(sprite, cleanup);
}
void CCTMXLayer::removeTileAt(const CCPoint& pos)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCAssert(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");

    unsigned int gid = tileGIDAt(pos);

    if (gid) 
    {
        unsigned int z = (unsigned int)(pos.x + pos.y * _layerSize.width);
        unsigned int atlasIndex = atlasIndexForExistantZ(z);

        // remove tile from GID map
        _tiles[z] = 0;

        // remove tile from atlas position array
        ccCArrayRemoveValueAtIndex(_atlasIndexArray, atlasIndex);

        // remove it from sprites and/or texture atlas
        CCSprite *sprite = (CCSprite*)getChildByTag(z);
        if (sprite)
        {
            CCSpriteBatchNode::removeChild(sprite, true);
        }
        else 
        {
            _textureAtlas->removeQuadAtIndex(atlasIndex);

            // update possible children
            if (_children && _children->count()>0)
            {
                CCObject* pObject = NULL;
                CCARRAY_FOREACH(_children, pObject)
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
    switch (_layerOrientation) 
    {
    case CCTMXOrientationOrtho:
        ret = ccp( pos.x * _mapTileSize.width, -pos.y *_mapTileSize.height);
        break;
    case CCTMXOrientationIso:
        ret = ccp((_mapTileSize.width /2) * (pos.x - pos.y),
                  (_mapTileSize.height /2 ) * (-pos.x - pos.y));
        break;
    case CCTMXOrientationHex:
        CCAssert(pos.equals(CCPointZero), "offset for hexagonal map not implemented yet");
        break;
    }
    return ret;    
}
CCPoint CCTMXLayer::positionAt(const CCPoint& pos)
{
    CCPoint ret = CCPointZero;
    switch (_layerOrientation)
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
    ret = CC_POINT_PIXELS_TO_POINTS( ret );
    return ret;
}
CCPoint CCTMXLayer::positionForOrthoAt(const CCPoint& pos)
{
    CCPoint xy = CCPointMake(pos.x * _mapTileSize.width,
                            (_layerSize.height - pos.y - 1) * _mapTileSize.height);
    return xy;
}
CCPoint CCTMXLayer::positionForIsoAt(const CCPoint& pos)
{
    CCPoint xy = CCPointMake(_mapTileSize.width /2 * (_layerSize.width + pos.x - pos.y - 1),
                             _mapTileSize.height /2 * ((_layerSize.height * 2 - pos.x - pos.y) - 2));
    return xy;
}
CCPoint CCTMXLayer::positionForHexAt(const CCPoint& pos)
{
    float diffY = 0;
    if ((int)pos.x % 2 == 1)
    {
        diffY = -_mapTileSize.height/2 ;
    }

    CCPoint xy = CCPointMake(pos.x * _mapTileSize.width*3/4,
                            (_layerSize.height - pos.y - 1) * _mapTileSize.height + diffY);
    return xy;
}
int CCTMXLayer::vertexZForPos(const CCPoint& pos)
{
    int ret = 0;
    unsigned int maxVal = 0;
    if (_useAutomaticVertexZ)
    {
        switch (_layerOrientation) 
        {
        case CCTMXOrientationIso:
            maxVal = (unsigned int)(_layerSize.width + _layerSize.height);
            ret = (int)(-(maxVal - (pos.x + pos.y)));
            break;
        case CCTMXOrientationOrtho:
            ret = (int)(-(_layerSize.height-pos.y));
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
        ret = _vertexZvalue;
    }
    
    return ret;
}

CCDictionary * CCTMXLayer::getProperties()
{
    return _properties;
}
void CCTMXLayer::setProperties(CCDictionary* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(_properties);
    _properties = var;
}

NS_CC_END

