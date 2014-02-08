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
 Code based on HKTMXTiledMap by HKASoftware http://hkasoftware.com
 
 Further info:
 http://www.cocos2d-iphone.org/forums/topic/hktmxtiledmap/

 */
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

    // shader, and other stuff
    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    return true;
}

TMXLayer2::TMXLayer2()
:_layerName("")
,_layerSize(Size::ZERO)
,_mapTileSize(Size::ZERO)
,_tiles(nullptr)
,_tileSet(nullptr)
,_layerOrientation(TMXOrientationOrtho)
,_lastPosition(Point(-1000,-1000))
{}

TMXLayer2::~TMXLayer2()
{
    CC_SAFE_RELEASE(_tileSet);
    CC_SAFE_RELEASE(_texture);
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


    Point trans = convertToWorldSpace(Point::ZERO);
    Point baseTile = Point( floor(-trans.x / (_mapTileSize.width)), floor(-trans.y / (_mapTileSize.height)));

    if( !baseTile.equals(_lastPosition) ) {

        GLfloat *texcoords = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        updateTexCoords(baseTile, texcoords);
        _lastPosition = baseTile;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    getShaderProgram()->use();

    // Draws in "world" coordinates, since the vertices are always displayed.
    _modelViewTransform.mat[12] += (baseTile.x * _mapTileSize.width);
    _modelViewTransform.mat[13] += (baseTile.y * _mapTileSize.height);
    getShaderProgram()->setUniformsForBuiltins(_modelViewTransform);

    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, _displayedColor.r/255.0f, _displayedColor.g/255.0f, _displayedColor.b/255.0f, _displayedOpacity/255.0f);

    // indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[2]);
    glDrawElements(GL_TRIANGLES, _screenTileCount * 6, GL_UNSIGNED_SHORT, NULL);

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CC_INCREMENT_GL_DRAWS(1);
}

ssize_t TMXLayer2::getTileIndex(int x, int y, cocos2d::Point baseTile) const
{
    int tileidx = -1;
    switch (_layerOrientation)
    {
        case TMXOrientationOrtho:
        {
            x += baseTile.x;
            y += baseTile.y;

            if( x < 0 || x >= _layerSize.width
               || y < 0 || y >= _layerSize.height)
                tileidx = -1;
            else
                tileidx = (_layerSize.height - y - 1) * _layerSize.width + x;
            break;
        }

        case TMXOrientationIso:
        {
            x += baseTile.x;
            y -= baseTile.y*2;

            int xx = x + y/2;
            int yy = (y+1)/2 - x;

            if( xx < 0 || xx >= _layerSize.width
               || yy < 0 || yy >= _layerSize.height )
                tileidx = -1;
            else
                tileidx = xx + _layerSize.width * yy;
            break;
        }

        default:
        {
            log("unsupported orientation format");
            CCASSERT(false, "ouch");
            break;
        }
    }


    return tileidx;
}

void TMXLayer2::updateTexCoords(const Point& baseTile, GLfloat *texcoords) const
{
    Size texSize = _tileSet->_imageSize;
    for (int y=0; y < _screenGridSize.height; y++)
    {
        for (int x=0; x < _screenGridSize.width; x++)
        {
            ssize_t tileidx = getTileIndex(x, y, baseTile);

            uint32_t tile = 0;
            if(tileidx >=0)
                tile = _tiles[tileidx];

            // vertices are sorted from top to bottom to support overlapping, so we need to convert 'y' to the new index
            int screenidx = ((y+1) * (_screenGridSize.width)) + x;
            GLfloat *texbase = texcoords + screenidx * 4 * 2;

            float left, right, top, bottom;

            if(!tile)
            {
                left = bottom = 0;
                top = right = 0;
            }
            else
            {
                Rect tileTexture = _tileSet->rectForGID(tile);

                left   = (tileTexture.origin.x / texSize.width);
                right  = left + (tileTexture.size.width / texSize.width);
                bottom = (tileTexture.origin.y / texSize.height);
                top    = bottom + (tileTexture.size.height / texSize.height);
            }

            if (tile & kTMXTileVerticalFlag)
                std::swap(top,bottom);

            if (tile & kTMXTileHorizontalFlag)
                std::swap(left,right);

            if (tile & kTMXTileDiagonalFlag)
            {
                texbase[0] = left;
                texbase[1] = top;
                texbase[2] = left;
                texbase[3] = bottom;
                texbase[4] = right;
                texbase[5] = top;
                texbase[6] = right;
                texbase[7] = bottom;
            }
            else
            {
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
    }
}

void TMXLayer2::setupIndices()
{
    GLushort *indices = (GLushort *)malloc( _screenTileCount * 6 * sizeof(GLushort) );

    for( int i=0; i < _screenTileCount; i++)
    {
        indices[i*6+0] = i*4+0;
        indices[i*6+1] = i*4+1;
        indices[i*6+2] = i*4+2;

        indices[i*6+3] = i*4+3;
        indices[i*6+4] = i*4+2;
        indices[i*6+5] = i*4+1;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * _screenTileCount * 6, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    free(indices);
}

void TMXLayer2::setupVertices()
{
    GLfloat *vertices = (GLfloat *)malloc( _screenTileCount * 4 * 2 * sizeof(GLfloat) );

    GLfloat *tilePtr = vertices;

    // top to bottom sorting to support overlapping
    for (int y=_screenGridSize.height-1; y >=0; y--)
    {
        for (int x=0; x < _screenGridSize.width; x++, tilePtr += 4 * 2)
        {
            GLfloat xpos0, xpos1, ypos0, ypos1;

            setVerticesForPos(x, y, &xpos0, &xpos1, &ypos0, &ypos1);

            // define the points of a quad here; we'll use the index buffer to make them triangles
            tilePtr[0] = xpos0;
            tilePtr[1] = ypos0;
            tilePtr[2] = xpos1;
            tilePtr[3] = ypos0;
            tilePtr[4] = xpos0;
            tilePtr[5] = ypos1;
            tilePtr[6] = xpos1;
            tilePtr[7] = ypos1;
        }
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices[0]) * _screenTileCount * 4 * 2, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    free(vertices);
}

void TMXLayer2::setVerticesForPos(int x, int y, GLfloat *xpos0, GLfloat *xpos1, GLfloat *ypos0, GLfloat *ypos1)
{
    switch (_layerOrientation)
    {
        case TMXOrientationOrtho:
            *xpos0 = _mapTileSize.width * x;
            *xpos1 = *xpos0 + _tileSet->_tileSize.width;
            *ypos0 = _mapTileSize.height * y;
            *ypos1 = *ypos0 + _tileSet->_tileSize.height;
            break;
        case TMXOrientationIso:
            *xpos0 = _mapTileSize.width * x - _mapTileSize.width/2 * (y%2);
            *xpos1 = *xpos0 + _tileSet->_tileSize.width;
            *ypos0 = _mapTileSize.height * (y-1) / 2;
            *ypos1 = *ypos0 + _tileSet->_tileSize.height;
            break;
        case TMXOrientationHex:
            break;
    }
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
//    this->parseInternalProperties();

    Size screenSize = Director::getInstance()->getWinSize();

    switch (_layerOrientation)
    {
        case TMXOrientationOrtho:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 1;
            _screenGridSize.height = ceil(screenSize.height / _mapTileSize.height) + 1;
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
        log("cc_vertexz is not supported in TMXLayer2. Use TMXLayer instead");
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


std::string TMXLayer2::getDescription() const
{
    return StringUtils::format("<TMXLayer2 | tag = %d, size = %d,%d>", _tag, (int)_mapTileSize.width, (int)_mapTileSize.height);
}


NS_CC_END

