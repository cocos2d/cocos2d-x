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
#include "CCTMXLayer2.h"
#include "CCTMXXMLParser.h"
#include "CCTMXTiledMap.h"
#include "CCSprite.h"
#include "CCTextureCache.h"
#include "CCGLProgramCache.h"
#include "CCGLProgram.h"
#include "ccCArray.h"
#include "CCDirector.h"
#include "CCConfiguration.h"
#include "renderer/CCRenderer.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN

namespace
{
    static const int MAX_QUADS_COUNT = 65536 / 6;
}

// TMXLayer2 - init & alloc & dealloc

TMXLayer2 * TMXLayer2::create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{
    TMXLayer2 *ret = new TMXLayer2();
    if (ret->initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo))
    {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}
bool TMXLayer2::initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
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
    Point offset = this->calculateLayerOffset(layerInfo->_offset);
    this->setPosition(CC_POINT_PIXELS_TO_POINTS(offset));

    this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(Size(_layerSize.width * _mapTileSize.width, _layerSize.height * _mapTileSize.height)));
    
    this->tileToNodeTransform();

    // shader, and other stuff
    setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    
    _useAutomaticVertexZ = false;
    _vertexZvalue = 0;

    return true;
}

TMXLayer2::TMXLayer2()
:_layerName("")
,_layerSize(Size::ZERO)
,_mapTileSize(Size::ZERO)
,_tiles(nullptr)
,_tileSet(nullptr)
,_layerOrientation(TMXOrientationOrtho)
,_texture(nullptr)
,_reusedTile(nullptr)
,_verticesToDraw(0)
,_vertexZvalue(0)
,_useAutomaticVertexZ(false)
,_quads(nullptr)
,_indices(nullptr)
,_numQuads(0)
,_dirty(false)
{}

TMXLayer2::~TMXLayer2()
{
    CC_SAFE_RELEASE(_tileSet);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_DELETE_ARRAY(_tiles);
    CC_SAFE_FREE(_quads);
    CC_SAFE_FREE(_indices);
}

void TMXLayer2::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(TMXLayer2::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void TMXLayer2::onDraw(const Mat4 &transform, bool transformUpdated)
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

        if (Configuration::getInstance()->supportsShareableVAO())
        {
            V2F_T2F_Quad* quads = (V2F_T2F_Quad*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            GLushort* indices = (GLushort *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
            _verticesToDraw = updateTiles(rect, quads, indices);
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        }
        else
        {
            _verticesToDraw = updateTiles(rect, nullptr, nullptr);
            
            if (_quads != nullptr && _indices != nullptr && _verticesToDraw > 0)
            {
                glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _numQuads , _quads, GL_DYNAMIC_DRAW);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _numQuads * 6 , _indices, GL_STATIC_DRAW);
            }
        }

        // don't draw more than 65535 vertices since we are using GL_UNSIGNED_SHORT for indices
        _verticesToDraw = std::min(_verticesToDraw, 65535);
        
        _dirty = false;
    }

    if(_verticesToDraw > 0) {

        getGLProgram()->use();
        getGLProgram()->setUniformsForBuiltins(_modelViewTransform);

        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_T2F), (GLvoid*) offsetof(V2F_T2F, vertices));

        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_T2F), (GLvoid*) offsetof(V2F_T2F, texCoords));

        // color
        glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, _displayedColor.r/255.0f, _displayedColor.g/255.0f, _displayedColor.b/255.0f, _displayedOpacity/255.0f);
        
        glDrawElements(GL_TRIANGLES, _verticesToDraw, GL_UNSIGNED_SHORT, nullptr);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_verticesToDraw);
    }

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int TMXLayer2::updateTiles(const Rect& culledRect, V2F_T2F_Quad *quads, GLushort *indices)
{
    int tilesUsed = 0;

    Rect visibleTiles = culledRect;
    Size mapTileSize = CC_SIZE_PIXELS_TO_POINTS(_mapTileSize);
    Size tileSize = CC_SIZE_PIXELS_TO_POINTS(_tileSet->_tileSize);
    Mat4 nodeToTileTransform = _tileToNodeTransform;
    nodeToTileTransform.inverse();
    //transform to tile
    visibleTiles = RectApplyTransform(visibleTiles, nodeToTileTransform);
    
    // if x=0.7, width=9.5, we need to draw number 0~10 of tiles, and so is height.
    visibleTiles.size.width = ceil(visibleTiles.origin.x + visibleTiles.size.width)  - floor(visibleTiles.origin.x);
    visibleTiles.size.height = ceil(visibleTiles.origin.y + visibleTiles.size.height) - floor(visibleTiles.origin.y);
    visibleTiles.origin.x = floor(visibleTiles.origin.x);
    visibleTiles.origin.y = floor(visibleTiles.origin.y);
    
    V2F_T2F_Quad* quadsTmp = quads;
    GLushort* indicesTmp = indices;
    
    // for the bigger tiles.
    int tilesOverX = 0;
    int tilesOverY = 0;
    // for diagonal oriention tiles
    float tileSizeMax = std::max(tileSize.width, tileSize.height);
    if (_layerOrientation == TMXOrientationOrtho)
    {
        tilesOverX = ceil(tileSizeMax / mapTileSize.width) - 1;
        tilesOverY = ceil(tileSizeMax / mapTileSize.height) - 1;
        
        if (tilesOverX < 0) tilesOverX = 0;
        if (tilesOverY < 0) tilesOverY = 0;
    }
    else if(_layerOrientation == TMXOrientationIso)
    {
        Rect overTileRect(0, 0, tileSizeMax - mapTileSize.width, tileSizeMax - mapTileSize.height);
        if (overTileRect.size.width < 0) overTileRect.size.width = 0;
        if (overTileRect.size.height < 0) overTileRect.size.height = 0;
        overTileRect = RectApplyTransform(overTileRect, nodeToTileTransform);
        
        tilesOverX = ceil(overTileRect.origin.x + overTileRect.size.width) - floor(overTileRect.origin.x);
        tilesOverY = ceil(overTileRect.origin.y + overTileRect.size.height) - floor(overTileRect.origin.y);
    }
    
    // doesn't support VBO
    if (quadsTmp == nullptr)
    {
        int quadsNeed = std::min(static_cast<int>((visibleTiles.size.width + tilesOverX) * (visibleTiles.size.height + tilesOverY)), MAX_QUADS_COUNT);
        if (_numQuads < quadsNeed)
        {
            _numQuads = quadsNeed;
            _quads = (V2F_T2F_Quad*)realloc(_quads, _numQuads * sizeof(V2F_T2F_Quad));
            _indices = (GLushort*)realloc(_indices, _numQuads * 6 * sizeof(GLushort));
        }
        
        quadsTmp = _quads;
        indicesTmp = _indices;
    }


    Size texSize = _tileSet->_imageSize;
    for (int y =  visibleTiles.origin.y; y < visibleTiles.origin.y + visibleTiles.size.height + tilesOverY; ++y)
    {
        if(y<0 || y >= _layerSize.height)
            continue;
        for (int x = visibleTiles.origin.x - tilesOverX; x < visibleTiles.origin.x + visibleTiles.size.width; ++x)
        {
            if(x<0 || x >= _layerSize.width)
                continue;

            int tileGID = _tiles[x + y * (int)_layerSize.width];

            // GID==0 empty tile
            if(tileGID!=0)
            {

                V2F_T2F_Quad *quad = &quadsTmp[tilesUsed];
                
                Vec3 nodePos(static_cast<float>(x), static_cast<float>(y), 0);
                _tileToNodeTransform.transformPoint(&nodePos);

                float left, right, top, bottom;

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
                    quad->br.vertices.x = left;
                    quad->br.vertices.y = top;
                    quad->tl.vertices.x = right;
                    quad->tl.vertices.y = bottom;
                    quad->tr.vertices.x = right;
                    quad->tr.vertices.y = top;
                }
                else
                {
                    quad->bl.vertices.x = left;
                    quad->bl.vertices.y = bottom;
                    quad->br.vertices.x = right;
                    quad->br.vertices.y = bottom;
                    quad->tl.vertices.x = left;
                    quad->tl.vertices.y = top;
                    quad->tr.vertices.x = right;
                    quad->tr.vertices.y = top;
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

void TMXLayer2::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);

    // 10922 = 65536/6
    int total = std::min(static_cast<int>(_layerSize.width * _layerSize.height), MAX_QUADS_COUNT);

    // Vertex + Tex Coords
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, total * sizeof(V2F_T2F_Quad), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, total * 6 * sizeof(GLushort), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

// TMXLayer2 - setup Tiles
void TMXLayer2::setupTiles()
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
        case TMXOrientationOrtho:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 1;
            _screenGridSize.height = ceil(screenSize.height / _mapTileSize.height) + 1;

            // tiles could be bigger than the grid, add additional rows if needed
            _screenGridSize.height += _tileSet->_tileSize.height / _mapTileSize.height;
            break;
        case TMXOrientationIso:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 2;
            _screenGridSize.height = ceil(screenSize.height / (_mapTileSize.height/2)) + 4;
            break;
        case TMXOrientationHex:
            break;
    }

    _screenTileCount = _screenGridSize.width * _screenGridSize.height;

    setupVBO();
}

Mat4 TMXLayer2::tileToNodeTransform()
{
	float w = _mapTileSize.width / CC_CONTENT_SCALE_FACTOR();
	float h = _mapTileSize.height / CC_CONTENT_SCALE_FACTOR();
	float offY = (_layerSize.height - 1) * h;
    
	switch(_layerOrientation)
    {
		case TMXOrientationOrtho:
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
		case TMXOrientationIso:
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
        case TMXOrientationHex:
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
Sprite* TMXLayer2::getTileAt(const Point& tileCoordinate)
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
            
            Point p = this->getPositionAt(tileCoordinate);
            tile->setAnchorPoint(Point::ZERO);
            tile->setPosition(p);
            tile->setPositionZ((float)getVertexZForPos(tileCoordinate));
            tile->setOpacity(this->getOpacity());
            tile->setTag(index);
            this->addChild(tile, -index);
            _spriteContainer.insert(std::pair<int, std::pair<Sprite*, int> >(index, std::pair<Sprite*, int>(tile, gid)));
            
            // tile is converted to sprite.
            setTileForGID(index, 0);
        }
	}
	return tile;
}

int TMXLayer2::getTileGIDAt(const Point& tileCoordinate, TMXTileFlags* flags/* = nullptr*/)
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

Point TMXLayer2::getPositionAt(const Point& pos)
{
    return PointApplyTransform(pos, _tileToNodeTransform);
}

int TMXLayer2::getVertexZForPos(const Point& pos)
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
            case TMXOrientationHex:
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

void TMXLayer2::removeTileAt(const Point& tileCoordinate)
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

void TMXLayer2::setTileForGID(int index, int gid)
{
    _tiles[index] = gid;
    _dirty = true;
}



void TMXLayer2::removeChild(Node* node, bool cleanup)
{
    int tag = node->getTag();
    auto it = _spriteContainer.find(tag);
    if (it != _spriteContainer.end() && it->second.first == node)
    {
        _spriteContainer.erase(it);
    }
    Node::removeChild(node, cleanup);
}

// TMXLayer2 - Properties
Value TMXLayer2::getProperty(const std::string& propertyName) const
{
    if (_properties.find(propertyName) != _properties.end())
        return _properties.at(propertyName);
    
    return Value();
}

void TMXLayer2::parseInternalProperties()
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
Point TMXLayer2::calculateLayerOffset(const Point& pos)
{
    Point ret = Point::ZERO;
    switch (_layerOrientation) 
    {
    case TMXOrientationOrtho:
        ret = Point( pos.x * _mapTileSize.width, -pos.y *_mapTileSize.height);
        break;
    case TMXOrientationIso:
        ret = Point((_mapTileSize.width /2) * (pos.x - pos.y),
                  (_mapTileSize.height /2 ) * (-pos.x - pos.y));
        break;
    case TMXOrientationHex:
        CCASSERT(pos.equals(Point::ZERO), "offset for hexagonal map not implemented yet");
        break;
    }
    return ret;    
}

// TMXLayer - adding / remove tiles
void TMXLayer2::setTileGID(int gid, const Point& tileCoordinate)
{
    setTileGID(gid, tileCoordinate, (TMXTileFlags)0);
}

void TMXLayer2::setTileGID(int gid, const Point& tileCoordinate, TMXTileFlags flags)
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

void TMXLayer2::setupTileSprite(Sprite* sprite, Point pos, int gid)
{
    sprite->setPosition(getPositionAt(pos));
    sprite->setPositionZ((float)getVertexZForPos(pos));
    sprite->setAnchorPoint(Point::ZERO);
    sprite->setOpacity(this->getOpacity());
    
    //issue 1264, flip can be undone as well
    sprite->setFlippedX(false);
    sprite->setFlippedY(false);
    sprite->setRotation(0.0f);
    
    // Rotation in tiled is achieved using 3 flipped states, flipping across the horizontal, vertical, and diagonal axes of the tiles.
    if (gid & kTMXTileDiagonalFlag)
    {
        // put the anchor in the middle for ease of rotation.
        sprite->setAnchorPoint(Point(0.5f,0.5f));
        sprite->setPosition(Point(getPositionAt(pos).x + sprite->getContentSize().height/2,
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

Sprite* TMXLayer2::reusedTileWithRect(Rect rect)
{
    if (! _reusedTile)
    {
        _reusedTile = Sprite::createWithTexture(_texture, rect);
        _reusedTile->retain();
    }
    else
    {
		// Re-init the sprite
        _reusedTile->setTextureRect(rect, false, rect.size);
    }
    
    return _reusedTile;
}

std::string TMXLayer2::getDescription() const
{
    return StringUtils::format("<TMXLayer2 | tag = %d, size = %d,%d>", _tag, (int)_mapTileSize.width, (int)_mapTileSize.height);
}

NS_CC_END

