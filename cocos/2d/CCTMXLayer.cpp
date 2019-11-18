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

#include "2d/CCTMXLayer.h"
#include "2d/CCTMXTiledMap.h"
#include "2d/CCSprite.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgram.h"

NS_CC_BEGIN


// TMXLayer - init & alloc & dealloc

TMXLayer * TMXLayer::create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{
    TMXLayer *ret = new (std::nothrow) TMXLayer();
    if (ret->initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
bool TMXLayer::initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{
    // FIXME:: is 35% a good estimate ?
    Size size = layerInfo->_layerSize;
    float totalNumberOfTiles = size.width * size.height;
    float capacity = totalNumberOfTiles * 0.35f + 1; // 35 percent is occupied ?

    Texture2D *texture = nullptr;
    if( tilesetInfo )
    {
        texture = Director::getInstance()->getTextureCache()->addImage(tilesetInfo->_sourceImage);
    }

    if (nullptr == texture)
        return false;

    if (SpriteBatchNode::initWithTexture(texture, static_cast<ssize_t>(capacity)))
    {
        // layerInfo
        _layerName = layerInfo->_name;
        _layerSize = size;
        _tiles = layerInfo->_tiles;
        _opacity = layerInfo->_opacity;
        setProperties(layerInfo->getProperties());
        _contentScaleFactor = Director::getInstance()->getContentScaleFactor();

        // tilesetInfo
        _tileSet = tilesetInfo;
        CC_SAFE_RETAIN(_tileSet);

        // mapInfo
        _mapTileSize = mapInfo->getTileSize();
        _layerOrientation = mapInfo->getOrientation();
        _staggerAxis = mapInfo->getStaggerAxis();
        _staggerIndex = mapInfo->getStaggerIndex();
        _hexSideLength = mapInfo->getHexSideLength();

        // offset (after layer orientation is set);
        Vec2 offset = this->calculateLayerOffset(layerInfo->_offset);
        this->setPosition(CC_POINT_PIXELS_TO_POINTS(offset));

        _atlasIndexArray = ccCArrayNew(totalNumberOfTiles);

        float width = 0;
        float height = 0;
        if (_layerOrientation == TMXOrientationHex) {
            if (_staggerAxis == TMXStaggerAxis_X) {
                height = _mapTileSize.height * (_layerSize.height + 0.5);
                width = (_mapTileSize.width + _hexSideLength) * ((int)(_layerSize.width / 2)) + _mapTileSize.width * ((int)_layerSize.width % 2);
            } else {
                width = _mapTileSize.width * (_layerSize.width + 0.5);
                height = (_mapTileSize.height + _hexSideLength) * ((int)(_layerSize.height / 2)) + _mapTileSize.height * ((int)_layerSize.height % 2);
            }
        } else {
            width = _layerSize.width * _mapTileSize.width;
            height = _layerSize.height * _mapTileSize.height;
        }
        this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(Size(width, height)));

        _useAutomaticVertexZ = false;
        _vertexZvalue = 0;

        return true;
    }
    return false;
}

TMXLayer::TMXLayer()
:_layerName("")
,_opacity(0)
,_vertexZvalue(0)
,_useAutomaticVertexZ(false)
,_reusedTile(nullptr)
,_atlasIndexArray(nullptr)
,_contentScaleFactor(1.0f)
,_layerSize(Size::ZERO)
,_mapTileSize(Size::ZERO)
,_tiles(nullptr)
,_tileSet(nullptr)
,_layerOrientation(TMXOrientationOrtho)
,_staggerAxis(TMXStaggerAxis_Y)
,_staggerIndex(TMXStaggerIndex_Even)
,_hexSideLength(0)
{}

TMXLayer::~TMXLayer()
{
    CC_SAFE_RELEASE(_tileSet);
    CC_SAFE_RELEASE(_reusedTile);

    if (_atlasIndexArray)
    {
        ccCArrayFree(_atlasIndexArray);
        _atlasIndexArray = nullptr;
    }

    CC_SAFE_FREE(_tiles);
}

void TMXLayer::releaseMap()
{
    if (_tiles)
    {
        free(_tiles);
        _tiles = nullptr;
    }

    if (_atlasIndexArray)
    {
        ccCArrayFree(_atlasIndexArray);
        _atlasIndexArray = nullptr;
    }
}

// TMXLayer - setup Tiles
void TMXLayer::setupTiles()
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

    for (int y=0; y < _layerSize.height; y++)
    {
        for (int x=0; x < _layerSize.width; x++)
        {
            int newX = x;
            // fix correct render ordering in Hexagonal maps when stagger axis == x
            if (_staggerAxis == TMXStaggerAxis_X && _layerOrientation == TMXOrientationHex)
            {
                if (_staggerIndex == TMXStaggerIndex_Odd)
                {
                    if (x >= _layerSize.width/2)
                        newX = (x - std::ceil(_layerSize.width/2)) * 2 + 1;
                    else
                        newX = x * 2;
                } else {
                    // TMXStaggerIndex_Even
                    if (x >= static_cast<int>(_layerSize.width/2))
                        newX = (x - static_cast<int>(_layerSize.width/2)) * 2;
                    else
                        newX = x * 2 + 1;
                }
            }

            int pos = static_cast<int>(newX + _layerSize.width * y);
            int gid = _tiles[ pos ];

            // gid are stored in little endian.
            // if host is big endian, then swap
            //if( o == CFByteOrderBigEndian )
            //    gid = CFSwapInt32( gid );
            /* We support little endian.*/

            // FIXME:: gid == 0 --> empty tile
            if (gid != 0)
            {
                this->appendTileForGID(gid, Vec2(newX, y));
                if(_tileSet->_animationInfo.at(gid))
                {
                    _animTileCoord[gid].push_back(Vec2(newX, y));
                }
            }
        }
    }
    if(hasTileAnimation())
    {
        _tileAnimManager = TMXTileAnimManager::create(this);
        CC_SAFE_RETAIN(_tileAnimManager);
    }
}

// TMXLayer - Properties
Value TMXLayer::getProperty(const std::string& propertyName) const
{
    if (_properties.find(propertyName) != _properties.end())
        return _properties.at(propertyName);

    return Value();
}

void TMXLayer::parseInternalProperties()
{
    // if cc_vertex=automatic, then tiles will be rendered using vertexz

    auto vertexz = getProperty("cc_vertexz");
    if (!vertexz.isNull())
    {
        std::string vertexZStr = vertexz.asString();
        // If "automatic" is on, then parse the "cc_alpha_func" too
        if (vertexZStr == "automatic")
        {
            _useAutomaticVertexZ = true;
            auto alphaFuncVal = getProperty("cc_alpha_func");
            float alphaFuncValue = alphaFuncVal.asFloat();
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST));

            GLint alphaValueLocation = glGetUniformLocation(getGLProgram()->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);

            // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison

            // use shader program to set uniform
            getGLProgram()->use();
            getGLProgram()->setUniformLocationWith1f(alphaValueLocation, alphaFuncValue);
            CHECK_GL_ERROR_DEBUG();
        }
        else
        {
            _vertexZvalue = vertexz.asInt();
        }
    }
}

void TMXLayer::setupTileSprite(Sprite* sprite, const Vec2& pos, uint32_t gid)
{
    sprite->setPosition(getPositionAt(pos));
    sprite->setPositionZ((float)getVertexZForPos(pos));
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setOpacity(_opacity);

    //issue 1264, flip can be undone as well
    sprite->setFlippedX(false);
    sprite->setFlippedY(false);
    sprite->setRotation(0.0f);
    sprite->setAnchorPoint(Vec2(0,0));

    // Rotation in tiled is achieved using 3 flipped states, flipping across the horizontal, vertical, and diagonal axes of the tiles.
    if (gid & kTMXTileDiagonalFlag)
    {
        // put the anchor in the middle for ease of rotation.
        sprite->setAnchorPoint(Vec2(0.5f,0.5f));
        sprite->setPosition(getPositionAt(pos).x + sprite->getContentSize().height/2,
           getPositionAt(pos).y + sprite->getContentSize().width/2 );

        auto flag = gid & (kTMXTileHorizontalFlag | kTMXTileVerticalFlag );

        // handle the 4 diagonally flipped states.
        if (flag == kTMXTileHorizontalFlag)
        {
            sprite->setRotation(90.0f);
        }
        else if (flag == kTMXTileVerticalFlag)
        {
            sprite->setRotation(270.0f);
        }
        else if (flag == (kTMXTileVerticalFlag | kTMXTileHorizontalFlag) )
        {
            sprite->setRotation(90.0f);
            sprite->setFlippedX(true);
        }
        else
        {
            sprite->setRotation(270.0f);
            sprite->setFlippedX(true);
        }
    }
    else
    {
        if (gid & kTMXTileHorizontalFlag)
        {
            sprite->setFlippedX(true);
        }

        if (gid & kTMXTileVerticalFlag)
        {
            sprite->setFlippedY(true);
        }
    }
}

Sprite* TMXLayer::reusedTileWithRect(const Rect& rect)
{
    if (! _reusedTile)
    {
        _reusedTile = Sprite::createWithTexture(_textureAtlas->getTexture(), rect);
        _reusedTile->setBatchNode(this);
        _reusedTile->retain();
    }
    else
    {
        // FIXME: HACK: Needed because if "batch node" is nil,
        // then the Sprite'squad will be reset
        _reusedTile->setBatchNode(nullptr);

        // Re-init the sprite
        _reusedTile->setTextureRect(rect, false, rect.size);

        // restore the batch node
        _reusedTile->setBatchNode(this);
    }

    return _reusedTile;
}

// TMXLayer - obtaining tiles/gids
Sprite * TMXLayer::getTileAt(const Vec2& pos)
{
    CCASSERT(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCASSERT(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");

    Sprite *tile = nullptr;
    int gid = this->getTileGIDAt(pos);

    // if GID == 0, then no tile is present
    if (gid)
    {
        int z = (int)(pos.x + pos.y * _layerSize.width);
        tile = static_cast<Sprite*>(this->getChildByTag(z));

        // tile not created yet. create it
        if (! tile)
        {
            Rect rect = _tileSet->getRectForGID(gid);
            rect = CC_RECT_PIXELS_TO_POINTS(rect);

            tile = Sprite::createWithTexture(this->getTexture(), rect);
            tile->setBatchNode(this);
            tile->setPosition(getPositionAt(pos));
            tile->setPositionZ((float)getVertexZForPos(pos));
            tile->setAnchorPoint(Vec2::ZERO);
            tile->setOpacity(_opacity);

            ssize_t indexForZ = atlasIndexForExistantZ(z);
            this->addSpriteWithoutQuad(tile, static_cast<int>(indexForZ), z);
        }
    }

    return tile;
}

uint32_t TMXLayer::getTileGIDAt(const Vec2& pos, TMXTileFlags* flags/* = nullptr*/)
{
    CCASSERT(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCASSERT(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");

    ssize_t idx = static_cast<int>(((int) pos.x + (int) pos.y * _layerSize.width));
    // Bits on the far end of the 32-bit global tile ID are used for tile flags
    uint32_t tile = _tiles[idx];

    // issue1264, flipped tiles can be changed dynamically
    if (flags)
    {
        *flags = (TMXTileFlags)(tile & kTMXFlipedAll);
    }

    return (tile & kTMXFlippedMask);
}

// TMXLayer - adding helper methods
Sprite * TMXLayer::insertTileForGID(uint32_t gid, const Vec2& pos)
{
    if (gid != 0 && (static_cast<int>((gid & kTMXFlippedMask)) - _tileSet->_firstGid) >= 0)
    {
        Rect rect = _tileSet->getRectForGID(gid);
        rect = CC_RECT_PIXELS_TO_POINTS(rect);

        intptr_t z = (intptr_t)((int) pos.x + (int) pos.y * _layerSize.width);

        Sprite *tile = reusedTileWithRect(rect);

        setupTileSprite(tile, pos, gid);

        // get atlas index
        ssize_t indexForZ = atlasIndexForNewZ(static_cast<int>(z));

        // Optimization: add the quad without adding a child
        this->insertQuadFromSprite(tile, indexForZ);

        // insert it into the local atlasindex array
        ccCArrayInsertValueAtIndex(_atlasIndexArray, (void*)z, indexForZ);

        // update possible children

        for(const auto &child : _children) {
            Sprite* sp = static_cast<Sprite*>(child);
            ssize_t ai = sp->getAtlasIndex();
            if ( ai >= indexForZ )
            {
                sp->setAtlasIndex(ai+1);
            }
        }

        _tiles[z] = gid;
        return tile;
    }

    return nullptr;
}

Sprite * TMXLayer::updateTileForGID(uint32_t gid, const Vec2& pos)
{
    Rect rect = _tileSet->getRectForGID(gid);
    rect = Rect(rect.origin.x / _contentScaleFactor, rect.origin.y / _contentScaleFactor, rect.size.width/ _contentScaleFactor, rect.size.height/ _contentScaleFactor);
    int z = (int)((int) pos.x + (int) pos.y * _layerSize.width);

    Sprite *tile = reusedTileWithRect(rect);

    setupTileSprite(tile ,pos ,gid);

    // get atlas index
    ssize_t indexForZ = atlasIndexForExistantZ(z);
    tile->setAtlasIndex(indexForZ);
    tile->setDirty(true);
    tile->updateTransform();
    _tiles[z] = gid;

    return tile;
}

intptr_t TMXLayer::getZForPos(const Vec2& pos) const
{
    intptr_t z = -1;
    // fix correct render ordering in Hexagonal maps when stagger axis == x
    if (_staggerAxis == TMXStaggerAxis_X && _layerOrientation == TMXOrientationHex)
    {
        if (_staggerIndex == TMXStaggerIndex_Odd)
        {
            if (((int)pos.x % 2) == 0)
                z = pos.x / 2 + pos.y * _layerSize.width;
            else
                z = pos.x / 2 + std::ceil(_layerSize.width / 2) + pos.y * _layerSize.width;
        } else {
            // TMXStaggerIndex_Even
            if (((int)pos.x % 2) == 1)
                z = pos.x / 2 + pos.y * _layerSize.width;
            else
                z = pos.x / 2 + std::floor(_layerSize.width / 2) + pos.y * _layerSize.width;
        }
    }
    else
    {
        z = (pos.x + pos.y * _layerSize.width);
    }

    CCASSERT(z != -1, "Invalid Z");
    return z;
}

// used only when parsing the map. useless after the map was parsed
// since lot's of assumptions are no longer true
Sprite * TMXLayer::appendTileForGID(uint32_t gid, const Vec2& pos)
{
    if (gid != 0 && (static_cast<int>((gid & kTMXFlippedMask)) - _tileSet->_firstGid) >= 0)
    {
        Rect rect = _tileSet->getRectForGID(gid);
        rect = CC_RECT_PIXELS_TO_POINTS(rect);

        // Z could be just an integer that gets incremented each time it is called.
        // but that wouldn't work on layers with empty tiles.
        // and it is IMPORTANT that Z returns an unique and bigger number than the previous one.
        // since _atlasIndexArray must be ordered because `bsearch` is used to find the GID for
        // a given Z. (github issue #16512)
        intptr_t z = getZForPos(pos);

        Sprite *tile = reusedTileWithRect(rect);

        setupTileSprite(tile ,pos ,gid);

        // optimization:
        // The difference between appendTileForGID and insertTileforGID is that append is faster, since
        // it appends the tile at the end of the texture atlas
        ssize_t indexForZ = _atlasIndexArray->num;

        // don't add it using the "standard" way.
        insertQuadFromSprite(tile, indexForZ);

        // append should be after addQuadFromSprite since it modifies the quantity values
        ccCArrayInsertValueAtIndex(_atlasIndexArray, (void*)z, indexForZ);

        // Validation for issue #16512
        CCASSERT(_atlasIndexArray->num == 1 ||
                 _atlasIndexArray->arr[_atlasIndexArray->num-1] > _atlasIndexArray->arr[_atlasIndexArray->num-2], "Invalid z for _atlasIndexArray");

        return tile;
    }

    return nullptr;
}

// TMXLayer - atlasIndex and Z
static inline int compareInts(const void * a, const void * b)
{
    const int ia = *(int*)a;
    const int ib = *(int*)b;
    return (ia-ib);
}

ssize_t TMXLayer::atlasIndexForExistantZ(int z)
{
    int key=z;
    int *item = (int*)bsearch((void*)&key, (void*)&_atlasIndexArray->arr[0], _atlasIndexArray->num, sizeof(void*), compareInts);

    CCASSERT(item, "TMX atlas index not found. Shall not happen");

    ssize_t index = ((size_t)item - (size_t)_atlasIndexArray->arr) / sizeof(void*);
    return index;
}

ssize_t TMXLayer::atlasIndexForNewZ(int z)
{
    // FIXME:: This can be improved with a sort of binary search
    ssize_t i=0;
    for (i=0; i< _atlasIndexArray->num ; i++)
    {
        ssize_t val = (size_t) _atlasIndexArray->arr[i];
        if (z < val)
        {
            break;
        }
    }

    return i;
}

// TMXLayer - adding / remove tiles
void TMXLayer::setTileGID(uint32_t gid, const Vec2& pos)
{
    setTileGID(gid, pos, (TMXTileFlags)0);
}

void TMXLayer::setTileGID(uint32_t gid, const Vec2& pos, TMXTileFlags flags)
{
    CCASSERT(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCASSERT(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");
    CCASSERT(gid == 0 || (int)gid >= _tileSet->_firstGid, "TMXLayer: invalid gid" );

    TMXTileFlags currentFlags;
    uint32_t currentGID = getTileGIDAt(pos, &currentFlags);

    if (currentGID != gid || currentFlags != flags)
    {
        uint32_t gidAndFlags = gid | flags;

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
            int z = (int) pos.x + (int) pos.y * _layerSize.width;
            Sprite *sprite = static_cast<Sprite*>(getChildByTag(z));
            if (sprite)
            {
                Rect rect = _tileSet->getRectForGID(gid);
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

void TMXLayer::addChild(Node* /*child*/, int /*zOrder*/, int /*tag*/)
{
    CCASSERT(0, "addChild: is not supported on TMXLayer. Instead use setTileGID:at:/tileAt:");
}

void TMXLayer::removeChild(Node* node, bool cleanup)
{
    Sprite *sprite = (Sprite*)node;
    // allows removing nil objects
    if (! sprite)
    {
        return;
    }

    CCASSERT(_children.contains(sprite), "Tile does not belong to TMXLayer");

    ssize_t atlasIndex = sprite->getAtlasIndex();
    ssize_t zz = (ssize_t)_atlasIndexArray->arr[atlasIndex];
    _tiles[zz] = 0;
    ccCArrayRemoveValueAtIndex(_atlasIndexArray, atlasIndex);
    SpriteBatchNode::removeChild(sprite, cleanup);
}

void TMXLayer::removeTileAt(const Vec2& pos)
{
    CCASSERT(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer: invalid position");
    CCASSERT(_tiles && _atlasIndexArray, "TMXLayer: the tiles map has been released");

    int gid = getTileGIDAt(pos);

    if (gid)
    {
        int z = pos.x + pos.y * _layerSize.width;
        ssize_t atlasIndex = atlasIndexForExistantZ(z);

        // remove tile from GID map
        _tiles[z] = 0;

        // remove tile from atlas position array
        ccCArrayRemoveValueAtIndex(_atlasIndexArray, atlasIndex);

        // remove it from sprites and/or texture atlas
        Sprite *sprite = (Sprite*)getChildByTag(z);
        if (sprite)
        {
            SpriteBatchNode::removeChild(sprite, true);
        }
        else
        {
            _textureAtlas->removeQuadAtIndex(atlasIndex);

            // update possible children
            for(const auto &obj : _children) {
                Sprite* child = static_cast<Sprite*>(obj);
                ssize_t ai = child->getAtlasIndex();
                if ( ai >= atlasIndex )
                {
                    child->setAtlasIndex(ai-1);
                }
            }
        }
    }
}

//CCTMXLayer - obtaining positions, offset
Vec2 TMXLayer::calculateLayerOffset(const Vec2& pos)
{
    Vec2 ret;
    switch (_layerOrientation)
    {
        case TMXOrientationOrtho:
            ret.set( pos.x * _mapTileSize.width, -pos.y *_mapTileSize.height);
            break;
        case TMXOrientationIso:
            ret.set((_mapTileSize.width /2) * (pos.x - pos.y),
                  (_mapTileSize.height /2 ) * (-pos.x - pos.y));
            break;
        case TMXOrientationHex:
        {
            if(_staggerAxis == TMXStaggerAxis_Y)
            {
                int diffX = (_staggerIndex == TMXStaggerIndex_Even) ? _mapTileSize.width/2 : 0;
                ret.set(pos.x * _mapTileSize.width + diffX, -pos.y * (_mapTileSize.height - (_mapTileSize.width - _hexSideLength) / 2));
            }
            else if(_staggerAxis == TMXStaggerAxis_X)
            {
                int diffY = (_staggerIndex == TMXStaggerIndex_Odd) ? _mapTileSize.height/2 : 0;
                ret.set(pos.x * (_mapTileSize.width - (_mapTileSize.width - _hexSideLength) / 2), -pos.y * _mapTileSize.height + diffY);
            }
            break;
        }
        case TMXOrientationStaggered:
        {
            float diffX = 0;
            if ((int)std::abs(pos.y) % 2 == 1)
            {
                diffX = _mapTileSize.width/2;
            }
            ret.set(pos.x * _mapTileSize.width + diffX,
                         (-pos.y) * _mapTileSize.height/2);
        }
        break;
    }
    return ret;
}

Vec2 TMXLayer::getPositionAt(const Vec2& pos)
{
    Vec2 ret;
    switch (_layerOrientation)
    {
    case TMXOrientationOrtho:
        ret = getPositionForOrthoAt(pos);
        break;
    case TMXOrientationIso:
        ret = getPositionForIsoAt(pos);
        break;
    case TMXOrientationHex:
        ret = getPositionForHexAt(pos);
        break;
    case TMXOrientationStaggered:
        ret = getPositionForStaggeredAt(pos);
        break;
    }
    ret = CC_POINT_PIXELS_TO_POINTS( ret );
    return ret;
}

Vec2 TMXLayer::getPositionForOrthoAt(const Vec2& pos)
{
    return Vec2(pos.x * _mapTileSize.width,
                            (_layerSize.height - pos.y - 1) * _mapTileSize.height);
}

Vec2 TMXLayer::getPositionForIsoAt(const Vec2& pos)
{
    return Vec2(_mapTileSize.width /2 * (_layerSize.width + pos.x - pos.y - 1),
                             _mapTileSize.height /2 * ((_layerSize.height * 2 - pos.x - pos.y) - 2));
}

Vec2 TMXLayer::getPositionForHexAt(const Vec2& pos)
{
    Vec2 xy;
    Vec2 offset = _tileSet->_tileOffset;

    int odd_even = (_staggerIndex == TMXStaggerIndex_Odd) ? 1 : -1;
    switch (_staggerAxis)
    {
        case TMXStaggerAxis_Y:
        {
            float diffX = 0;
            if ((int)pos.y % 2 == 1)
            {
                diffX = _mapTileSize.width/2 * odd_even;
            }
            xy = Vec2(pos.x * _mapTileSize.width+diffX+offset.x,
                      (_layerSize.height - pos.y - 1) * (_mapTileSize.height-(_mapTileSize.height-_hexSideLength)/2)-offset.y);
            break;
        }

        case TMXStaggerAxis_X:
        {
            float diffY = 0;
            if ((int)pos.x % 2 == 1)
            {
                diffY = _mapTileSize.height/2 * -odd_even;
            }

            xy = Vec2(pos.x * (_mapTileSize.width-(_mapTileSize.width-_hexSideLength)/2)+offset.x,
                      (_layerSize.height - pos.y - 1) * _mapTileSize.height + diffY-offset.y);
            break;
        }
    }
    return xy;
}

Vec2 TMXLayer::getPositionForStaggeredAt(const Vec2 &pos)
{
    float diffX = 0;
    if ((int)pos.y % 2 == 1)
    {
        diffX = _mapTileSize.width/2;
    }
    return Vec2(pos.x * _mapTileSize.width + diffX,
                (_layerSize.height - pos.y - 1) * _mapTileSize.height/2);
}

int TMXLayer::getVertexZForPos(const Vec2& pos)
{
    int ret = 0;
    int maxVal = 0;
    if (_useAutomaticVertexZ)
    {
        switch (_layerOrientation)
        {
        case TMXOrientationIso:
            maxVal = static_cast<int>(_layerSize.width + _layerSize.height);
            ret = static_cast<int>(-(maxVal - (pos.x + pos.y)));
            break;
        case TMXOrientationOrtho:
            ret = static_cast<int>(-(_layerSize.height-pos.y));
            break;
        case TMXOrientationStaggered:
            ret = static_cast<int>(-(_layerSize.height-pos.y));
            break;
        case TMXOrientationHex:
            ret = static_cast<int>(-(_layerSize.height-pos.y));
            break;
        default:
            CCASSERT(0, "TMX invalid value");
            break;
        }
    }
    else
    {
        ret = _vertexZvalue;
    }

    return ret;
}

std::string TMXLayer::getDescription() const
{
    return StringUtils::format("<TMXLayer | tag = %d, size = %d,%d>", _tag, (int)_mapTileSize.width, (int)_mapTileSize.height);
}

TMXTileAnimManager::TMXTileAnimManager(TMXLayer *layer)
{
    _layer = layer;
    for(const auto &p : *_layer->getAnimTileCoord())
    {
        for(auto tilePos : p.second)
        {
            _tasks.pushBack(TMXTileAnimTask::create(_layer, _layer->getTileSet()->_animationInfo.at(p.first), tilePos));
        }
    }
}

TMXTileAnimManager *TMXTileAnimManager::create(TMXLayer *layer)
{
    TMXTileAnimManager *ret = new (std::nothrow) TMXTileAnimManager(layer);
    if (ret)
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void TMXTileAnimManager::startAll()
{
    if(_started || _tasks.empty())
    return;
    _started = true;
    for(auto &task : _tasks)
    {
        task->start();
    }
}

void TMXTileAnimManager::stopAll()
{
    if(!_started)
        return;
    _started = false;
    for(auto &task : _tasks)
    {
        task->stop();
    }
}

TMXTileAnimTask::TMXTileAnimTask(TMXLayer *layer, TMXTileAnimInfo *animation, const Vec2 &tilePos)
{
    _layer = layer;
    _animation = animation;
    _frameCount = static_cast<uint32_t>(_animation->_frames.size());
    _tilePosition = tilePos;
    std::stringstream ss;
    ss << "TickAnimOnTilePos(" << _tilePosition.x << "," << _tilePosition.y << ")";
    _key = ss.str();
}

void TMXTileAnimTask::tickAndScheduleNext(float dt)
{
    setCurrFrame();
    _layer->getParent()->scheduleOnce(CC_CALLBACK_1(TMXTileAnimTask::tickAndScheduleNext, this), _animation->_frames[_currentFrame]._duration/1000.0f, _key);
}

void TMXTileAnimTask::start()
{
    _isRunning = true;
    tickAndScheduleNext(0.0f);
}

void TMXTileAnimTask::stop()
{
    _isRunning = false;
    _layer->getParent()->unschedule(_key);
}

void TMXTileAnimTask::setCurrFrame()
{
    _layer->setTileGID(_animation->_frames[_currentFrame]._tileID, _tilePosition);
    _currentFrame = (_currentFrame + 1) % _frameCount;
}

TMXTileAnimTask *TMXTileAnimTask::create(TMXLayer *layer, TMXTileAnimInfo *animation, const Vec2 &tilePos)
{
    TMXTileAnimTask *ret = new (std::nothrow) TMXTileAnimTask(layer, animation, tilePos);
    if (ret)
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

NS_CC_END
