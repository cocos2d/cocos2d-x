/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "CCTMXLayer2.h"
#include "CCTMXXMLParser.h"
#include "CCTMXTiledMap.h"
#include "CCSprite.h"
#include "CCTextureCache.h"
#include "CCShaderCache.h"
#include "CCGLProgram.h"
#include "ccCArray.h"
#include "CCDirector.h"
#include "renderer/CCRenderer.h"

#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN


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
    // XXX: is 35% a good estimate ?
    Size size = layerInfo->_layerSize;
    int totalNumberOfTiles = size.width * size.height;

    Texture2D *texture = nullptr;
    if( tilesetInfo )
    {
        texture = Director::getInstance()->getTextureCache()->addImage(tilesetInfo->_sourceImage.c_str());
        texture->retain();
    }

    _texture = texture;

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

    // offset (after layer orientation is set);
    Point offset = this->calculateLayerOffset(layerInfo->_offset);
    this->setPosition(CC_POINT_PIXELS_TO_POINTS(offset));

    _atlasIndexArray = ccCArrayNew(totalNumberOfTiles);

    this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(Size(_layerSize.width * _mapTileSize.width, _layerSize.height * _mapTileSize.height)));

    _useAutomaticVertexZ = false;
    _vertexZvalue = 0;

    // shader, and other stuff
    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));


    return true;
}

TMXLayer2::TMXLayer2()
:_layerName("")
,_opacity(0)
,_vertexZvalue(0)
,_useAutomaticVertexZ(false)
,_atlasIndexArray(nullptr)
,_contentScaleFactor(1.0f)
,_layerSize(Size::ZERO)
,_mapTileSize(Size::ZERO)
,_tiles(nullptr)
,_tileSet(nullptr)
,_layerOrientation(TMXOrientationOrtho)
,_reusedTile(nullptr)
{}

TMXLayer2::~TMXLayer2()
{
    CC_SAFE_RELEASE(_tileSet);
    CC_SAFE_RELEASE(_texture);

    if (_atlasIndexArray)
    {
        ccCArrayFree(_atlasIndexArray);
        _atlasIndexArray = nullptr;
    }

    CC_SAFE_DELETE_ARRAY(_tiles);
}

void TMXLayer2::draw()
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(TMXLayer2::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void TMXLayer2::onDraw()
{
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORDS);
    GL::bindTexture2D( _texture->getName() );

    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    // tex coords
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[1]);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    GLfloat *texcoords = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    Point trans = convertToWorldSpace(Point::ZERO);
    Point baseTile = Point(floor(trans.x / (_mapTileSize.width)),
                                       floor(trans.y / (_mapTileSize.height)));

    log("base (%.1f,%.1f)", baseTile.x, baseTile.y);

    Size texSize = _tileSet->_imageSize;
	for (int y=0; y < _screenGridSize.height; y++)
	{
//		if (baseTile.y + y < 0 || baseTile.y + y >= _layerSize.height)
//			continue;
		for (int x=0; x < _screenGridSize.width; x++)
		{
//			if (baseTile.x + x < 0 || baseTile.x + x >= _layerSize.width)
//				continue;

			int tileidx = (_layerSize.height - (baseTile.y + y) - 1) * _layerSize.width + baseTile.x + x;
//			int tileidx = (_layerSize.height - y - 1) * _layerSize.width + x;
			unsigned int tile = _tiles[tileidx];

			int screenidx = (y * (_screenGridSize.width)) + x;
			Rect tileTexture = _tileSet->rectForGID(tile & kFlippedMask);

			GLfloat *texbase = texcoords + screenidx * 4 * 2;

            float left, right, top, bottom;

            if(true || !tile
               || baseTile.x + x < 0 || baseTile.x + x >= _layerSize.width
               || baseTile.y + y < 0 || baseTile.y + y >= _layerSize.height
               )
            {
                left = bottom = 0;
                top = right = 1;
            }
            else
            {
                left   = (tileTexture.origin.x / texSize.width);
                right  = left + (tileTexture.size.width / texSize.width);
                bottom = (tileTexture.origin.y / texSize.height);
                top    = bottom + (tileTexture.size.height / texSize.height);
            }

            texbase[0] = left;
            texbase[1] = top;
            texbase[2] = right;
            texbase[3] = top;
            texbase[4] = left;
            texbase[5] = bottom;
            texbase[6] = right;
            texbase[7] = bottom;
		}
	}

    glUnmapBuffer(GL_ARRAY_BUFFER);

    kmMat4 tempMV = _modelViewTransform;

    tempMV.mat[12] += (baseTile.x * _mapTileSize.width);
    tempMV.mat[13] += (baseTile.y * _mapTileSize.height);

    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins(tempMV);

    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, 1, 1, 1, 1);

    // indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[2]);

    glDrawElements(GL_TRIANGLES, _screenTileCount * 6, GL_UNSIGNED_SHORT, NULL);

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CC_INCREMENT_GL_DRAWS(1);
}

void TMXLayer2::setupIndices()
{
    _indices = (GLushort *)malloc( _screenTileCount * 6 * sizeof(GLushort) );

    for( int i=0; i < _screenTileCount; i++)
    {
        _indices[i*6+0] = i*4+0;
        _indices[i*6+1] = i*4+1;
        _indices[i*6+2] = i*4+2;

        // inverted index. issue #179
        _indices[i*6+3] = i*4+3;
        _indices[i*6+4] = i*4+2;
        _indices[i*6+5] = i*4+1;        
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _screenTileCount * 6, _indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TMXLayer2::setupVertices()
{
    _vertices = (GLfloat *)malloc( _screenTileCount * 4 * 2 * sizeof(GLfloat) );

    GLfloat *tilePtr = _vertices;
    for (int y=0; y < _screenGridSize.height; y++)
    {
        GLfloat ypos_0 = _mapTileSize.height * y;
        GLfloat ypos_1 = _mapTileSize.height * (y+1);
        for (int x=0; x < _screenGridSize.width; x++, tilePtr += 4 * 2)
        {
            GLfloat xpos_0 = _mapTileSize.width * x;
            GLfloat xpos_1 = _mapTileSize.width * (x+1);
            // define the points of a quad here; we'll use the index buffer to make them triangles
            tilePtr[0] = xpos_0;
            tilePtr[1] = ypos_0;
            tilePtr[2] = xpos_1;
            tilePtr[3] = ypos_0;
            tilePtr[4] = xpos_0;
            tilePtr[5] = ypos_1;
            tilePtr[6] = xpos_1;
            tilePtr[7] = ypos_1;
        }
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_vertices[0]) * _screenTileCount * 4 * 2, _vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TMXLayer2::setupVBO()
{
    glGenBuffers(3, &_buffersVBO[0]);

    // Vertex
    setupVertices();

    // Tex Coords
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, _screenTileCount * 4 * 2 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Indices
    setupIndices();

    CHECK_GL_ERROR_DEBUG();
}

void TMXLayer2::releaseMap()
{
    if (_tiles)
    {
        delete [] _tiles;
        _tiles = nullptr;
    }

    if (_atlasIndexArray)
    {
        ccCArrayFree(_atlasIndexArray);
        _atlasIndexArray = nullptr;
    }
}

// TMXLayer2 - setup Tiles
void TMXLayer2::setupTiles()
{    
    // Optimization: quick hack that sets the image size on the tileset
    _tileSet->_imageSize = _texture->getContentSizeInPixels();

    // By default all the tiles are aliased
    // pros:
    //  - easier to render
    // cons:
    //  - difficult to scale / rotate / etc.
    _texture->setAliasTexParameters();

    //CFByteOrder o = CFByteOrderGetCurrent();

    // Parse cocos2d properties
    this->parseInternalProperties();

    Size screenSize = Director::getInstance()->getWinSize();

    _screenGridSize.width = (ceil(screenSize.width / (_mapTileSize.width)) + 1);
    _screenGridSize.height = (ceil(screenSize.height / (_mapTileSize.height)) + 1);
    _screenTileCount = _screenGridSize.width * _screenGridSize.height;

    setupVBO();
}

// used only when parsing the map. useless after the map was parsed
// since lot's of assumptions are no longer true
void TMXLayer2::appendTileForGID(int gid, const Point& pos)
{
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

void TMXLayer2::setupTileSprite(Sprite* sprite, Point pos, int gid)
{
    sprite->setPosition(getPositionAt(pos));
    sprite->setVertexZ((float)getVertexZForPos(pos));
    sprite->setAnchorPoint(Point::ZERO);
    sprite->setOpacity(_opacity);

    //issue 1264, flip can be undone as well
    sprite->setFlippedX(false);
    sprite->setFlippedY(false);
    sprite->setRotation(0.0f);
    sprite->setAnchorPoint(Point(0,0));

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

// TMXLayer2 - Properties
Value TMXLayer2::getProperty(const std::string& propertyName) const
{
    if (_properties.find(propertyName) != _properties.end())
        return _properties.at(propertyName);
    
    return Value();
}

void TMXLayer2::parseInternalProperties()
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
            setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST));

            GLint alphaValueLocation = glGetUniformLocation(getShaderProgram()->getProgram(), GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE);

            // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
            
            // use shader program to set uniform
            getShaderProgram()->use();
            getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, alphaFuncValue);
            CHECK_GL_ERROR_DEBUG();
        }
        else
        {
            _vertexZvalue = vertexz.asInt();
        }
    }
}


int TMXLayer2::getTileGIDAt(const Point& pos, ccTMXTileFlags* flags/* = nullptr*/)
{
    CCASSERT(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "TMXLayer2: invalid position");
    CCASSERT(_tiles && _atlasIndexArray, "TMXLayer2: the tiles map has been released");

    int idx = static_cast<int>((pos.x + pos.y * _layerSize.width));
    // Bits on the far end of the 32-bit global tile ID are used for tile flags
    int tile = _tiles[idx];

    // issue1264, flipped tiles can be changed dynamically
    if (flags) 
    {
        *flags = (ccTMXTileFlags)(tile & kFlipedAll);
    }
    
    return (tile & kFlippedMask);
}

// TMXLayer2 - atlasIndex and Z
static inline int compareInts(const void * a, const void * b)
{
    return ((*(int*)a) - (*(int*)b));
}

ssize_t TMXLayer2::atlasIndexForExistantZ(int z)
{
    int key=z;
    int *item = (int*)bsearch((void*)&key, (void*)&_atlasIndexArray->arr[0], _atlasIndexArray->num, sizeof(void*), compareInts);

    CCASSERT(item, "TMX atlas index not found. Shall not happen");

    ssize_t index = ((size_t)item - (size_t)_atlasIndexArray->arr) / sizeof(void*);
    return index;
}

ssize_t TMXLayer2::atlasIndexForNewZ(int z)
{
    // XXX: This can be improved with a sort of binary search
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

// TMXLayer2 - adding / remove tiles
void TMXLayer2::setTileGID(int gid, const Point& pos)
{
    setTileGID(gid, pos, (ccTMXTileFlags)0);
}

void TMXLayer2::setTileGID(int gid, const Point& pos, ccTMXTileFlags flags)
{
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

Point TMXLayer2::getPositionAt(const Point& pos)
{
    Point ret = Point::ZERO;
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
    }
    ret = CC_POINT_PIXELS_TO_POINTS( ret );
    return ret;
}

Point TMXLayer2::getPositionForOrthoAt(const Point& pos)
{
    return Point(pos.x * _mapTileSize.width,
                            (_layerSize.height - pos.y - 1) * _mapTileSize.height);
}

Point TMXLayer2::getPositionForIsoAt(const Point& pos)
{
    return Point(_mapTileSize.width /2 * (_layerSize.width + pos.x - pos.y - 1),
                             _mapTileSize.height /2 * ((_layerSize.height * 2 - pos.x - pos.y) - 2));
}

Point TMXLayer2::getPositionForHexAt(const Point& pos)
{
    float diffY = 0;
    if ((int)pos.x % 2 == 1)
    {
        diffY = -_mapTileSize.height/2 ;
    }

    Point xy = Point(pos.x * _mapTileSize.width*3/4,
                            (_layerSize.height - pos.y - 1) * _mapTileSize.height + diffY);
    return xy;
}

float TMXLayer2::getVertexZForPos(const Point& pos)
{
    float ret = 0;
    float maxVal = 0;
    if (_useAutomaticVertexZ)
    {
        switch (_layerOrientation) 
        {
        case TMXOrientationIso:
            maxVal = _layerSize.width + _layerSize.height;
            ret = -(maxVal - (pos.x + pos.y));
            break;
        case TMXOrientationOrtho:
            ret = -(_layerSize.height-pos.y);
            break;
        case TMXOrientationHex:
            CCASSERT(false, "TMX Hexa zOrder not supported");
            break;
        default:
            CCASSERT(false, "TMX invalid value");
            break;
        }
    } 
    else
    {
        ret = _vertexZvalue;
    }
    
    return ret;
}

std::string TMXLayer2::getDescription() const
{
    return StringUtils::format("<TMXLayer2 | tag = %d, size = %d,%d>", _tag, (int)_mapTileSize.width, (int)_mapTileSize.height);
}


NS_CC_END

