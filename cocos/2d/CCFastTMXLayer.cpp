/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

Copyright (c) 2011 HKASoftware

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

/*
 Original rewrite of TMXLayer was based on HKTMXTiledMap by HKASoftware http://hkasoftware.com
 Further info: http://www.cocos2d-iphone.org/forums/topic/hktmxtiledmap/

 It was rewritten again, and only a small part of the original HK ideas/code remains in this implementation

 */
#include "CCFastTMXLayer.h"
#include "CCTMXXMLParser.h"
#include "CCFastTMXTiledMap.h"
#include "2d/CCSprite.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgram.h"
#include "base/CCDirector.h"
#include "base/CCConfiguration.h"
#include "renderer/CCRenderer.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN

namespace
{
    static const int MAX_QUADS_COUNT = 65536 / 6;
}

// FastTMXLayer - init & alloc & dealloc

FastTMXLayer * FastTMXLayer::create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{
    FastTMXLayer *ret = new FastTMXLayer();
    if (ret->initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo))
    {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}
bool FastTMXLayer::initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{    

    if( tilesetInfo )
    {
        _texture = Director::getInstance()->getTextureCache()->addImage(tilesetInfo->_sourceImage);
        _texture->retain();
    }

    // layerInfo
    _layerName = layerInfo->_name;
    _layerSize = layerInfo->_layerSize;
    _tiles = layerInfo->_tiles;
    setOpacity( layerInfo->_opacity );
    setProperties(layerInfo->getProperties());

    // tilesetInfo
    _tileSet = tilesetInfo;
    CC_SAFE_RETAIN(_tileSet);

    // mapInfo
    _mapTileSize = mapInfo->getTileSize();
    _layerOrientation = mapInfo->getOrientation();

    // offset (after layer orientation is set);
    Vec2 offset = this->calculateLayerOffset(layerInfo->_offset);
    this->setPosition(CC_POINT_PIXELS_TO_POINTS(offset));

    this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(Size(_layerSize.width * _mapTileSize.width, _layerSize.height * _mapTileSize.height)));
    
    this->tileToNodeTransform();

    // shader, and other stuff
    setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    
    _useAutomaticVertexZ = false;
    _vertexZvalue = 0;

    return true;
}

FastTMXLayer::FastTMXLayer()
:_layerName("")
,_layerSize(Size::ZERO)
,_mapTileSize(Size::ZERO)
,_tiles(nullptr)
,_tileSet(nullptr)
,_layerOrientation(FastTMXOrientationOrtho)
,_texture(nullptr)
,_verticesToDraw(0)
,_vertexZvalue(0)
,_useAutomaticVertexZ(false)
,_dirty(false)
{}

FastTMXLayer::~FastTMXLayer()
{
    CC_SAFE_RELEASE(_tileSet);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_DELETE_ARRAY(_tiles);
}

void FastTMXLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(FastTMXLayer::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void FastTMXLayer::onDraw(const Mat4 &transform, bool transformUpdated)
{
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
    GL::bindTexture2D( _texture->getName() );


    // tex coords + indices
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);


    if( transformUpdated || _dirty )
    {
    
        Size s = Director::getInstance()->getWinSize();
        auto rect = Rect(0, 0, s.width, s.height);

        Mat4 inv = transform;
        inv.inverse();
        rect = RectApplyTransform(rect, inv);
        
        _verticesToDraw = updateTiles(rect);
        
        if (_quads.size() > 0 && _indices.size() > 0 && _verticesToDraw > 0)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _quads.size() , &_quads[0], GL_DYNAMIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _quads.size() * 6 , &_indices[0], GL_STATIC_DRAW);
        }

        // don't draw more than 65535 vertices since we are using GL_UNSIGNED_SHORT for indices
        _verticesToDraw = std::min(_verticesToDraw, 65535);
        
        _dirty = false;
    }

    if(_verticesToDraw > 0) {

        getGLProgram()->use();
        getGLProgram()->setUniformsForBuiltins(_modelViewTransform);

        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_T2F), (GLvoid*) offsetof(V3F_T2F, vertices));

        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_T2F), (GLvoid*) offsetof(V3F_T2F, texCoords));

        // color
        glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, _displayedColor.r/255.0f, _displayedColor.g/255.0f, _displayedColor.b/255.0f, _displayedOpacity/255.0f);
        
        glDrawElements(GL_TRIANGLES, _verticesToDraw, GL_UNSIGNED_SHORT, nullptr);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_verticesToDraw);
    }

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int FastTMXLayer::updateTiles(const Rect& culledRect)
{
    int tilesUsed = 0;

    Rect visibleTiles = culledRect;
    Size mapTileSize = CC_SIZE_PIXELS_TO_POINTS(_mapTileSize);
    Size tileSize = CC_SIZE_PIXELS_TO_POINTS(_tileSet->_tileSize);
    Mat4 nodeToTileTransform = _tileToNodeTransform.getInversed();
    //transform to tile
    visibleTiles = RectApplyTransform(visibleTiles, nodeToTileTransform);
    // tile coordinate is upside-down, so we need to make the tile coordinate use top-left for the start point.
    visibleTiles.origin.y += 1;
    
    // if x=0.7, width=9.5, we need to draw number 0~10 of tiles, and so is height.
    visibleTiles.size.width = ceil(visibleTiles.origin.x + visibleTiles.size.width)  - floor(visibleTiles.origin.x);
    visibleTiles.size.height = ceil(visibleTiles.origin.y + visibleTiles.size.height) - floor(visibleTiles.origin.y);
    visibleTiles.origin.x = floor(visibleTiles.origin.x);
    visibleTiles.origin.y = floor(visibleTiles.origin.y);

    
    // for the bigger tiles.
    int tilesOverX = 0;
    int tilesOverY = 0;
    // for diagonal oriention tiles
    float tileSizeMax = std::max(tileSize.width, tileSize.height);
    if (_layerOrientation == FastTMXOrientationOrtho)
    {
        tilesOverX = ceil(tileSizeMax / mapTileSize.width) - 1;
        tilesOverY = ceil(tileSizeMax / mapTileSize.height) - 1;
        
        if (tilesOverX < 0) tilesOverX = 0;
        if (tilesOverY < 0) tilesOverY = 0;
    }
    else if(_layerOrientation == FastTMXOrientationIso)
    {
        Rect overTileRect(0, 0, tileSizeMax - mapTileSize.width, tileSizeMax - mapTileSize.height);
        if (overTileRect.size.width < 0) overTileRect.size.width = 0;
        if (overTileRect.size.height < 0) overTileRect.size.height = 0;
        overTileRect = RectApplyTransform(overTileRect, nodeToTileTransform);
        
        tilesOverX = ceil(overTileRect.origin.x + overTileRect.size.width) - floor(overTileRect.origin.x);
        tilesOverY = ceil(overTileRect.origin.y + overTileRect.size.height) - floor(overTileRect.origin.y);
    }
    
    // doesn't support VBO
    int quadsNeed = std::min(static_cast<int>((visibleTiles.size.width + tilesOverX) * (visibleTiles.size.height + tilesOverY)), MAX_QUADS_COUNT);
    if (_quads.size() < quadsNeed)
    {
        _quads.resize(quadsNeed);
        _indices.resize(quadsNeed * 6);
    }
    
    V3F_T2F_Quad* quadsTmp = &_quads[0];
    GLushort* indicesTmp = &_indices[0];

    Size texSize = _tileSet->_imageSize;
    for (int y =  visibleTiles.origin.y - tilesOverY; y < visibleTiles.origin.y + visibleTiles.size.height + tilesOverY; ++y)
    {
        if(y<0 || y >= _layerSize.height)
            continue;
        for (int x = visibleTiles.origin.x - tilesOverX; x < visibleTiles.origin.x + visibleTiles.size.width + tilesOverX; ++x)
        {
            if(x<0 || x >= _layerSize.width)
                continue;

            int tileGID = _tiles[x + y * (int)_layerSize.width];

            // GID==0 empty tile
            if(tileGID!=0)
            {

                V3F_T2F_Quad *quad = &quadsTmp[tilesUsed];
                
                Vec3 nodePos(static_cast<float>(x), static_cast<float>(y), 0);
                _tileToNodeTransform.transformPoint(&nodePos);

                float left, right, top, bottom, z;
                
                z = getVertexZForPos(Vec2(x, y));

                // vertices
                if (tileGID & kTMXTileDiagonalFlag)
                {
                    left = nodePos.x;
                    right = nodePos.x + tileSize.height;
                    bottom = nodePos.y + tileSize.width;
                    top = nodePos.y;
                }
                else
                {
                    left = nodePos.x;
                    right = nodePos.x + tileSize.width;
                    bottom = nodePos.y + tileSize.height;
                    top = nodePos.y;
                }

                if(tileGID & kTMXTileVerticalFlag)
                    std::swap(top, bottom);
                if(tileGID & kTMXTileHorizontalFlag)
                    std::swap(left, right);

                if(tileGID & kTMXTileDiagonalFlag)
                {
                    // XXX: not working correcly
                    quad->bl.vertices.x = left;
                    quad->bl.vertices.y = bottom;
                    quad->bl.vertices.z = z;
                    quad->br.vertices.x = left;
                    quad->br.vertices.y = top;
                    quad->br.vertices.z = z;
                    quad->tl.vertices.x = right;
                    quad->tl.vertices.y = bottom;
                    quad->tl.vertices.z = z;
                    quad->tr.vertices.x = right;
                    quad->tr.vertices.y = top;
                    quad->tr.vertices.z = z;
                }
                else
                {
                    quad->bl.vertices.x = left;
                    quad->bl.vertices.y = bottom;
                    quad->bl.vertices.z = z;
                    quad->br.vertices.x = right;
                    quad->br.vertices.y = bottom;
                    quad->br.vertices.z = z;
                    quad->tl.vertices.x = left;
                    quad->tl.vertices.y = top;
                    quad->tl.vertices.z = z;
                    quad->tr.vertices.x = right;
                    quad->tr.vertices.y = top;
                    quad->tr.vertices.z = z;
                }

                // texcoords
                Rect tileTexture = _tileSet->getRectForGID(tileGID);
                left   = (tileTexture.origin.x / texSize.width);
                right  = left + (tileTexture.size.width / texSize.width);
                bottom = (tileTexture.origin.y / texSize.height);
                top    = bottom + (tileTexture.size.height / texSize.height);

                quad->bl.texCoords.u = left;
                quad->bl.texCoords.v = bottom;
                quad->br.texCoords.u = right;
                quad->br.texCoords.v = bottom;
                quad->tl.texCoords.u = left;
                quad->tl.texCoords.v = top;
                quad->tr.texCoords.u = right;
                quad->tr.texCoords.v = top;


                GLushort *idxbase = indicesTmp + tilesUsed * 6;
                int vertexbase = tilesUsed * 4;

                idxbase[0] = vertexbase;
                idxbase[1] = vertexbase + 1;
                idxbase[2] = vertexbase + 2;
                idxbase[3] = vertexbase + 3;
                idxbase[4] = vertexbase + 2;
                idxbase[5] = vertexbase + 1;

                tilesUsed++;
            }
            
            if (tilesUsed >= MAX_QUADS_COUNT)
            {
                break;
            }
        } // for x
        
        if (tilesUsed >= MAX_QUADS_COUNT)
        {
            break;
        }
    } // for y

    return tilesUsed * 6;
}

void FastTMXLayer::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);

    // 10922 = 65536/6
    int total = std::min(static_cast<int>(_layerSize.width * _layerSize.height), MAX_QUADS_COUNT);

    // Vertex + Tex Coords
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, total * sizeof(V3F_T2F_Quad), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, total * 6 * sizeof(GLushort), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

// FastTMXLayer - setup Tiles
void FastTMXLayer::setupTiles()
{    
    // Optimization: quick hack that sets the image size on the tileset
    _tileSet->_imageSize = _texture->getContentSizeInPixels();

    // By default all the tiles are aliased
    // pros: easier to render
    // cons: difficult to scale / rotate / etc.
    _texture->setAliasTexParameters();

    //CFByteOrder o = CFByteOrderGetCurrent();

    // Parse cocos2d properties
    this->parseInternalProperties();

    Size screenSize = Director::getInstance()->getWinSize();

    switch (_layerOrientation)
    {
        case FastTMXOrientationOrtho:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 1;
            _screenGridSize.height = ceil(screenSize.height / _mapTileSize.height) + 1;

            // tiles could be bigger than the grid, add additional rows if needed
            _screenGridSize.height += _tileSet->_tileSize.height / _mapTileSize.height;
            break;
        case FastTMXOrientationIso:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 2;
            _screenGridSize.height = ceil(screenSize.height / (_mapTileSize.height/2)) + 4;
            break;
        case FastTMXOrientationHex:
            break;
    }

    _screenTileCount = _screenGridSize.width * _screenGridSize.height;

    setupVBO();
}

Mat4 FastTMXLayer::tileToNodeTransform()
{
    float w = _mapTileSize.width / CC_CONTENT_SCALE_FACTOR();
    float h = _mapTileSize.height / CC_CONTENT_SCALE_FACTOR();
    float offY = (_layerSize.height - 1) * h;
    
    switch(_layerOrientation)
    {
		case FastTMXOrientationOrtho:
        {
            _tileToNodeTransform = Mat4
            (
                w, 0.0f, 0.0f, 0.0f,
                0.0f, -h, 0.0f, offY,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0, 0.0f, 1.0f
            );
            
            return _tileToNodeTransform;
        }
		case FastTMXOrientationIso:
        {
            float offX = (_layerSize.width - 1) * w / 2;
            _tileToNodeTransform = Mat4
            (
                w/2, -w/2, 0.0f, offX,
                -h/2, -h/2, 0.0f, offY,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            );
			return _tileToNodeTransform;
		}
        case FastTMXOrientationHex:
        {
            _tileToNodeTransform = Mat4::IDENTITY;
            return _tileToNodeTransform;
        }
        default:
        {
            _tileToNodeTransform = Mat4::IDENTITY;
            return _tileToNodeTransform;
        }
    }
    
}

// removing / getting tiles
Sprite* FastTMXLayer::getTileAt(const Vec2& tileCoordinate)
{
    CCASSERT( tileCoordinate.x < _layerSize.width && tileCoordinate.y < _layerSize.height && tileCoordinate.x >=0 && tileCoordinate.y >=0, "TMXLayer: invalid position");
    CCASSERT( _tiles, "TMXLayer: the tiles map has been released");
    
    Sprite *tile = nullptr;
    int gid = this->getTileGIDAt(tileCoordinate);
    
    // if GID == 0, then no tile is present
    if( gid ) {
        int index = tileCoordinate.x + tileCoordinate.y * _layerSize.width;
        
        auto it = _spriteContainer.find(index);
        if (it != _spriteContainer.end())
        {
            tile = it->second.first;
        }
        else
        {
            // tile not created yet. create it
            Rect rect = _tileSet->getRectForGID(gid);
            rect = CC_RECT_PIXELS_TO_POINTS(rect);
            tile = Sprite::createWithTexture(_texture, rect);
            
            Vec2 p = this->getPositionAt(tileCoordinate);
            tile->setAnchorPoint(Vec2::ZERO);
            tile->setPosition(p);
            tile->setPositionZ((float)getVertexZForPos(tileCoordinate));
            tile->setOpacity(this->getOpacity());
            tile->setTag(index);
            this->addChild(tile, index);
            _spriteContainer.insert(std::pair<int, std::pair<Sprite*, int> >(index, std::pair<Sprite*, int>(tile, gid)));
            
            // tile is converted to sprite.
            setTileForGID(index, 0);
        }
    }
    return tile;
}

int FastTMXLayer::getTileGIDAt(const Vec2& tileCoordinate, TMXTileFlags* flags/* = nullptr*/)
{
    CCASSERT(tileCoordinate.x < _layerSize.width && tileCoordinate.y < _layerSize.height && tileCoordinate.x >=0 && tileCoordinate.y >=0, "TMXLayer: invalid position");
    CCASSERT(_tiles, "TMXLayer: the tiles map has been released");
    
    int idx = static_cast<int>((tileCoordinate.x + tileCoordinate.y * _layerSize.width));
    
    // Bits on the far end of the 32-bit global tile ID are used for tile flags
    int tile = _tiles[idx];
    auto it = _spriteContainer.find(idx);
    
    // converted to sprite.
    if (tile == 0 && it != _spriteContainer.end())
    {
        tile = it->second.second;
    }
    
    // issue1264, flipped tiles can be changed dynamically
    if (flags)
    {
        *flags = (TMXTileFlags)(tile & kTMXFlipedAll);
    }
    
    return (tile & kTMXFlippedMask);
}

Vec2 FastTMXLayer::getPositionAt(const Vec2& pos)
{
    return PointApplyTransform(pos, _tileToNodeTransform);
}

int FastTMXLayer::getVertexZForPos(const Vec2& pos)
{
    int ret = 0;
    int maxVal = 0;
    if (_useAutomaticVertexZ)
    {
        switch (_layerOrientation)
        {
            case FastTMXOrientationIso:
                maxVal = static_cast<int>(_layerSize.width + _layerSize.height);
                ret = static_cast<int>(-(maxVal - (pos.x + pos.y)));
                break;
            case FastTMXOrientationOrtho:
                ret = static_cast<int>(-(_layerSize.height-pos.y));
                break;
            case FastTMXOrientationHex:
                CCASSERT(0, "TMX Hexa zOrder not supported");
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

void FastTMXLayer::removeTileAt(const Vec2& tileCoordinate)
{
    
    CCASSERT( tileCoordinate.x < _layerSize.width && tileCoordinate.y < _layerSize.height && tileCoordinate.x >=0 && tileCoordinate.y >=0, "TMXLayer: invalid position");
    
    int gid = this->getTileGIDAt(tileCoordinate);
    
    if( gid ) {
        
        int z = tileCoordinate.x + tileCoordinate.y * _layerSize.width;
        
        // remove tile from GID map
        setTileForGID(z, 0);
        
        // remove it from sprites
        auto it = _spriteContainer.find(z);
        if (it != _spriteContainer.end())
        {
            this->removeChild(it->second.first);
        }
    }
}

void FastTMXLayer::setTileForGID(int index, int gid)
{
    _tiles[index] = gid;
    _dirty = true;
}



void FastTMXLayer::removeChild(Node* node, bool cleanup)
{
    int tag = node->getTag();
    auto it = _spriteContainer.find(tag);
    if (it != _spriteContainer.end() && it->second.first == node)
    {
        _spriteContainer.erase(it);
    }
    Node::removeChild(node, cleanup);
}

// FastTMXLayer - Properties
Value FastTMXLayer::getProperty(const std::string& propertyName) const
{
    if (_properties.find(propertyName) != _properties.end())
        return _properties.at(propertyName);
    
    return Value();
}

void FastTMXLayer::parseInternalProperties()
{
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
            setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST));
            
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


//CCTMXLayer2 - obtaining positions, offset
Vec2 FastTMXLayer::calculateLayerOffset(const Vec2& pos)
{
    Vec2 ret = Vec2::ZERO;
    switch (_layerOrientation) 
    {
    case FastTMXOrientationOrtho:
        ret = Vec2( pos.x * _mapTileSize.width, -pos.y *_mapTileSize.height);
        break;
    case FastTMXOrientationIso:
        ret = Vec2((_mapTileSize.width /2) * (pos.x - pos.y),
                  (_mapTileSize.height /2 ) * (-pos.x - pos.y));
        break;
    case FastTMXOrientationHex:
        CCASSERT(pos.equals(Vec2::ZERO), "offset for hexagonal map not implemented yet");
        break;
    }
    return ret;    
}

// TMXLayer - adding / remove tiles
void FastTMXLayer::setTileGID(int gid, const Vec2& tileCoordinate)
{
    setTileGID(gid, tileCoordinate, (TMXTileFlags)0);
}

void FastTMXLayer::setTileGID(int gid, const Vec2& tileCoordinate, TMXTileFlags flags)
{
    CCASSERT(tileCoordinate.x < _layerSize.width && tileCoordinate.y < _layerSize.height && tileCoordinate.x >=0 && tileCoordinate.y >=0, "TMXLayer: invalid position");
    CCASSERT(_tiles, "TMXLayer: the tiles map has been released");
    CCASSERT(gid == 0 || gid >= _tileSet->_firstGid, "TMXLayer: invalid gid" );
    
    TMXTileFlags currentFlags;
    int currentGID = getTileGIDAt(tileCoordinate, &currentFlags);
    
    if (currentGID != gid || currentFlags != flags)
    {
        int gidAndFlags = gid | flags;
        
        // setting gid=0 is equal to remove the tile
        if (gid == 0)
        {
            removeTileAt(tileCoordinate);
        }
        // empty tile. create a new one
        else if (currentGID == 0)
        {
            int z = tileCoordinate.x + tileCoordinate.y * _layerSize.width;
            setTileForGID(z, gidAndFlags);
        }
        // modifying an existing tile with a non-empty tile
        else
        {
            int z = tileCoordinate.x + tileCoordinate.y * _layerSize.width;
            auto it = _spriteContainer.find(z);
            if (it != _spriteContainer.end())
            {
                Sprite *sprite = it->second.first;
                Rect rect = _tileSet->getRectForGID(gid);
                rect = CC_RECT_PIXELS_TO_POINTS(rect);
                
                sprite->setTextureRect(rect, false, rect.size);
                this->reorderChild(sprite, z);
                if (flags)
                {
                    setupTileSprite(sprite, sprite->getPosition(), gidAndFlags);
                }
                
                it->second.second = gidAndFlags;
            }
            else
            {
                setTileForGID(z, gidAndFlags);
            }
        }
    }
}

void FastTMXLayer::setupTileSprite(Sprite* sprite, Vec2 pos, int gid)
{
    sprite->setPosition(getPositionAt(pos));
    sprite->setPositionZ((float)getVertexZForPos(pos));
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setOpacity(this->getOpacity());
    
    //issue 1264, flip can be undone as well
    sprite->setFlippedX(false);
    sprite->setFlippedY(false);
    sprite->setRotation(0.0f);
    
    // Rotation in tiled is achieved using 3 flipped states, flipping across the horizontal, vertical, and diagonal axes of the tiles.
    if (gid & kTMXTileDiagonalFlag)
    {
        // put the anchor in the middle for ease of rotation.
        sprite->setAnchorPoint(Vec2(0.5f,0.5f));
        sprite->setPosition(Vec2(getPositionAt(pos).x + sprite->getContentSize().height/2,
                                  getPositionAt(pos).y + sprite->getContentSize().width/2 ) );
        
        int flag = gid & (kTMXTileHorizontalFlag | kTMXTileVerticalFlag );
        
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

std::string FastTMXLayer::getDescription() const
{
    return StringUtils::format("<FastTMXLayer | tag = %d, size = %d,%d>", _tag, (int)_mapTileSize.width, (int)_mapTileSize.height);
}

NS_CC_END

