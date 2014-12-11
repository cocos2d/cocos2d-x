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
#include "2d/CCFastTMXLayer.h"
#include "2d/CCFastTMXTiledMap.h"
#include "2d/CCSprite.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "base/CCDirector.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN
namespace experimental {

const int TMXLayer::FAST_TMX_ORIENTATION_ORTHO = 0;
const int TMXLayer::FAST_TMX_ORIENTATION_HEX = 1;
const int TMXLayer::FAST_TMX_ORIENTATION_ISO = 2;

// FastTMXLayer - init & alloc & dealloc
TMXLayer * TMXLayer::create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{
    TMXLayer *ret = new (std::nothrow) TMXLayer();
    if (ret->initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo))
    {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}

bool TMXLayer::initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
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
    _quadsDirty = true;
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

TMXLayer::TMXLayer()
: _layerName("")
, _layerSize(Size::ZERO)
, _mapTileSize(Size::ZERO)
, _tiles(nullptr)
, _tileSet(nullptr)
, _layerOrientation(FAST_TMX_ORIENTATION_ORTHO)
, _texture(nullptr)
, _vertexZvalue(0)
, _useAutomaticVertexZ(false)
, _quadsDirty(true)
, _dirty(true)
, _vertexBuffer(nullptr)
, _vData(nullptr)
, _indexBuffer(nullptr)
{
}

TMXLayer::~TMXLayer()
{
    CC_SAFE_RELEASE(_tileSet);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_DELETE_ARRAY(_tiles);
    CC_SAFE_RELEASE(_vData);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
    
}

void TMXLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    updateTotalQuads();
    
    if( flags != 0 || _dirty || _quadsDirty )
    {
        Size s = Director::getInstance()->getWinSize();
        auto rect = Rect(0, 0, s.width, s.height);
        
        Mat4 inv = transform;
        inv.inverse();
        rect = RectApplyTransform(rect, inv);
        
        updateTiles(rect);
        updateIndexBuffer();
        updatePrimitives();
        _dirty = false;
    }
    
    if(_renderCommands.size() < _primitives.size())
    {
        _renderCommands.resize(_primitives.size());
    }
    
    int index = 0;
    for(const auto& iter : _primitives)
    {
        if(iter.second->getCount() > 0)
        {
            auto& cmd = _renderCommands[index++];
            cmd.init(iter.first, _texture->getName(), getGLProgramState(), BlendFunc::ALPHA_NON_PREMULTIPLIED, iter.second, _modelViewTransform);
            renderer->addCommand(&cmd);
        }
    }
}

void TMXLayer::onDraw(Primitive *primitive)
{
    GL::bindTexture2D(_texture->getName());
    getGLProgramState()->apply(_modelViewTransform);
    
    GL::bindVAO(0);
    primitive->draw();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, primitive->getCount() * 4);
}

void TMXLayer::updateTiles(const Rect& culledRect)
{
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
    if (_layerOrientation == FAST_TMX_ORIENTATION_ORTHO)
    {
        tilesOverX = ceil(tileSizeMax / mapTileSize.width) - 1;
        tilesOverY = ceil(tileSizeMax / mapTileSize.height) - 1;
        
        if (tilesOverX < 0) tilesOverX = 0;
        if (tilesOverY < 0) tilesOverY = 0;
    }
    else if(_layerOrientation == FAST_TMX_ORIENTATION_ISO)
    {
        Rect overTileRect(0, 0, tileSizeMax - mapTileSize.width, tileSizeMax - mapTileSize.height);
        if (overTileRect.size.width < 0) overTileRect.size.width = 0;
        if (overTileRect.size.height < 0) overTileRect.size.height = 0;
        overTileRect = RectApplyTransform(overTileRect, nodeToTileTransform);
        
        tilesOverX = ceil(overTileRect.origin.x + overTileRect.size.width) - floor(overTileRect.origin.x);
        tilesOverY = ceil(overTileRect.origin.y + overTileRect.size.height) - floor(overTileRect.origin.y);
    }
    else
    {
        //do nothing, do not support
        //CCASSERT(0, "TMX invalid value");
    }
    
    _indicesVertexZNumber.clear();
    
    for(const auto& iter : _indicesVertexZOffsets)
    {
        _indicesVertexZNumber[iter.first] = iter.second;
    }
    
    int yBegin = std::max(0.f,visibleTiles.origin.y - tilesOverY);
    int yEnd = std::min(_layerSize.height,visibleTiles.origin.y + visibleTiles.size.height + tilesOverY);
    int xBegin = std::max(0.f,visibleTiles.origin.x - tilesOverX);
    int xEnd = std::min(_layerSize.width,visibleTiles.origin.x + visibleTiles.size.width + tilesOverX);
    
    for (int y =  yBegin; y < yEnd; ++y)
    {
        for (int x = xBegin; x < xEnd; ++x)
        {
            int tileIndex = getTileIndexByPos(x, y);
            if(_tiles[tileIndex] == 0) continue;
            
            int vertexZ = getVertexZForPos(Vec2(x,y));
            auto iter = _indicesVertexZNumber.find(vertexZ);
            int offset = iter->second;
            iter->second++;
            
            int quadIndex = _tileToQuadIndex[tileIndex];
            CC_ASSERT(-1 != quadIndex);
            _indices[6 * offset + 0] = quadIndex * 4 + 0;
            _indices[6 * offset + 1] = quadIndex * 4 + 1;
            _indices[6 * offset + 2] = quadIndex * 4 + 2;
            _indices[6 * offset + 3] = quadIndex * 4 + 3;
            _indices[6 * offset + 4] = quadIndex * 4 + 2;
            _indices[6 * offset + 5] = quadIndex * 4 + 1;
            
        } // for x
    } // for y
    
    for(const auto& iter : _indicesVertexZOffsets)
    {
        _indicesVertexZNumber[iter.first] -= iter.second;
        if(_indicesVertexZNumber[iter.first] == 0)
        {
            _indicesVertexZNumber.erase(iter.first);
        }
    }
    
}

void TMXLayer::updateVertexBuffer()
{
    GL::bindVAO(0);
    if(nullptr == _vData)
    {
        _vertexBuffer = VertexBuffer::create(sizeof(V3F_C4B_T2F), (int)_totalQuads.size() * 4);
        _vData = VertexData::create();
        _vData->setStream(_vertexBuffer, VertexStreamAttribute(0, GLProgram::VERTEX_ATTRIB_POSITION, GL_FLOAT, 3));
        _vData->setStream(_vertexBuffer, VertexStreamAttribute(offsetof(V3F_C4B_T2F, colors), GLProgram::VERTEX_ATTRIB_COLOR, GL_UNSIGNED_BYTE, 4, true));
        _vData->setStream(_vertexBuffer, VertexStreamAttribute(offsetof(V3F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, GL_FLOAT, 2));
        CC_SAFE_RETAIN(_vData);
        CC_SAFE_RETAIN(_vertexBuffer);
    }
    if(_vertexBuffer)
    {
        _vertexBuffer->updateVertices((void*)&_totalQuads[0], (int)_totalQuads.size() * 4, 0);
    }
    
}

void TMXLayer::updateIndexBuffer()
{
    if(nullptr == _indexBuffer)
    {
        _indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, (int)_indices.size());
        CC_SAFE_RETAIN(_indexBuffer);
    }
    _indexBuffer->updateIndices(&_indices[0], (int)_indices.size(), 0);
    
}

// FastTMXLayer - setup Tiles
void TMXLayer::setupTiles()
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
        case FAST_TMX_ORIENTATION_ORTHO:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 1;
            _screenGridSize.height = ceil(screenSize.height / _mapTileSize.height) + 1;

            // tiles could be bigger than the grid, add additional rows if needed
            _screenGridSize.height += _tileSet->_tileSize.height / _mapTileSize.height;
            break;
        case FAST_TMX_ORIENTATION_ISO:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 2;
            _screenGridSize.height = ceil(screenSize.height / (_mapTileSize.height/2)) + 4;
            break;
        case FAST_TMX_ORIENTATION_HEX:
        default:
            CCLOGERROR("FastTMX does not support type %d", _layerOrientation);
            break;
    }

    _screenTileCount = _screenGridSize.width * _screenGridSize.height;

}

Mat4 TMXLayer::tileToNodeTransform()
{
    float w = _mapTileSize.width / CC_CONTENT_SCALE_FACTOR();
    float h = _mapTileSize.height / CC_CONTENT_SCALE_FACTOR();
    float offY = (_layerSize.height - 1) * h;
    
    switch(_layerOrientation)
    {
        case FAST_TMX_ORIENTATION_ORTHO:
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
        case FAST_TMX_ORIENTATION_ISO:
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
        case FAST_TMX_ORIENTATION_HEX:
        {
            _tileToNodeTransform = Mat4
            (
                h * sqrtf(0.75),    0,   0, 0,
                -h/2,      -h,      0,   offY,
                0,               0,     1,  0,
                0,               0,     0,  1
            );
            return _tileToNodeTransform;
        }
        default:
        {
            _tileToNodeTransform = Mat4::IDENTITY;
            return _tileToNodeTransform;
        }
    }
    
}

void TMXLayer::updatePrimitives()
{
    for(const auto& iter : _indicesVertexZNumber)
    {
        int start = _indicesVertexZOffsets.at(iter.first);
        
        auto primitiveIter= _primitives.find(iter.first);
        if(primitiveIter == _primitives.end())
        {
            auto primitive = Primitive::create(_vData, _indexBuffer, GL_TRIANGLES);
            primitive->setCount(iter.second * 6);
            primitive->setStart(start * 6);
            
            _primitives.insert(iter.first, primitive);
        }
        else
        {
            primitiveIter->second->setCount(iter.second * 6);
            primitiveIter->second->setStart(start * 6);
        }
    }
}

void TMXLayer::updateTotalQuads()
{
    if(_quadsDirty)
    {
        Size tileSize = CC_SIZE_PIXELS_TO_POINTS(_tileSet->_tileSize);
        Size texSize = _tileSet->_imageSize;
        _tileToQuadIndex.clear();
        _totalQuads.resize(int(_layerSize.width * _layerSize.height));
        _indices.resize(6 * int(_layerSize.width * _layerSize.height));
        _tileToQuadIndex.resize(int(_layerSize.width * _layerSize.height),-1);
        _indicesVertexZOffsets.clear();
        
        int quadIndex = 0;
        for(int y = 0; y < _layerSize.height; ++y)
        {
            for(int x =0; x < _layerSize.width; ++x)
            {
                int tileIndex = getTileIndexByPos(x, y);
                int tileGID = _tiles[tileIndex];
                
                if(tileGID == 0) continue;
                
                _tileToQuadIndex[tileIndex] = quadIndex;
                
                auto& quad = _totalQuads[quadIndex];
                
                Vec3 nodePos(float(x), float(y), 0);
                _tileToNodeTransform.transformPoint(&nodePos);
                
                float left, right, top, bottom, z;
                
                z = getVertexZForPos(Vec2(x, y));
                auto iter = _indicesVertexZOffsets.find(z);
                if(iter == _indicesVertexZOffsets.end())
                {
                    _indicesVertexZOffsets[z] = 1;
                }
                else
                {
                    iter->second++;
                }
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
                    // FIXME: not working correcly
                    quad.bl.vertices.x = left;
                    quad.bl.vertices.y = bottom;
                    quad.bl.vertices.z = z;
                    quad.br.vertices.x = left;
                    quad.br.vertices.y = top;
                    quad.br.vertices.z = z;
                    quad.tl.vertices.x = right;
                    quad.tl.vertices.y = bottom;
                    quad.tl.vertices.z = z;
                    quad.tr.vertices.x = right;
                    quad.tr.vertices.y = top;
                    quad.tr.vertices.z = z;
                }
                else
                {
                    quad.bl.vertices.x = left;
                    quad.bl.vertices.y = bottom;
                    quad.bl.vertices.z = z;
                    quad.br.vertices.x = right;
                    quad.br.vertices.y = bottom;
                    quad.br.vertices.z = z;
                    quad.tl.vertices.x = left;
                    quad.tl.vertices.y = top;
                    quad.tl.vertices.z = z;
                    quad.tr.vertices.x = right;
                    quad.tr.vertices.y = top;
                    quad.tr.vertices.z = z;
                }
                
                // texcoords
                Rect tileTexture = _tileSet->getRectForGID(tileGID);
                left   = (tileTexture.origin.x / texSize.width);
                right  = left + (tileTexture.size.width / texSize.width);
                bottom = (tileTexture.origin.y / texSize.height);
                top    = bottom + (tileTexture.size.height / texSize.height);
                
                quad.bl.texCoords.u = left;
                quad.bl.texCoords.v = bottom;
                quad.br.texCoords.u = right;
                quad.br.texCoords.v = bottom;
                quad.tl.texCoords.u = left;
                quad.tl.texCoords.v = top;
                quad.tr.texCoords.u = right;
                quad.tr.texCoords.v = top;
                
                quad.bl.colors = Color4B::WHITE;
                quad.br.colors = Color4B::WHITE;
                quad.tl.colors = Color4B::WHITE;
                quad.tr.colors = Color4B::WHITE;
                
                ++quadIndex;
            }
        }
        
        int offset = 0;
        for(auto iter = _indicesVertexZOffsets.begin(); iter != _indicesVertexZOffsets.end(); ++iter)
        {
            std::swap(offset, iter->second);
            offset += iter->second;
        }
        updateVertexBuffer();
        
        _quadsDirty = false;
    }
}

// removing / getting tiles
Sprite* TMXLayer::getTileAt(const Vec2& tileCoordinate)
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
            setFlaggedTileGIDByIndex(index, 0);
        }
    }
    return tile;
}

int TMXLayer::getTileGIDAt(const Vec2& tileCoordinate, TMXTileFlags* flags/* = nullptr*/)
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

Vec2 TMXLayer::getPositionAt(const Vec2& pos)
{
    return PointApplyTransform(pos, _tileToNodeTransform);
}

int TMXLayer::getVertexZForPos(const Vec2& pos)
{
    int ret = 0;
    int maxVal = 0;
    if (_useAutomaticVertexZ)
    {
        switch (_layerOrientation)
        {
            case FAST_TMX_ORIENTATION_ISO:
                maxVal = static_cast<int>(_layerSize.width + _layerSize.height);
                ret = static_cast<int>(-(maxVal - (pos.x + pos.y)));
                break;
            case FAST_TMX_ORIENTATION_ORTHO:
                ret = static_cast<int>(-(_layerSize.height-pos.y));
                break;
            case FAST_TMX_ORIENTATION_HEX:
                CCASSERT(0, "TMX Hexa vertexZ not supported");
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

void TMXLayer::removeTileAt(const Vec2& tileCoordinate)
{
    
    CCASSERT( tileCoordinate.x < _layerSize.width && tileCoordinate.y < _layerSize.height && tileCoordinate.x >=0 && tileCoordinate.y >=0, "TMXLayer: invalid position");
    
    int gid = this->getTileGIDAt(tileCoordinate);
    
    if( gid ) {
        
        int z = tileCoordinate.x + tileCoordinate.y * _layerSize.width;
        
        // remove tile from GID map
        setFlaggedTileGIDByIndex(z, 0);
        
        // remove it from sprites
        auto it = _spriteContainer.find(z);
        if (it != _spriteContainer.end())
        {
            this->removeChild(it->second.first);
        }
    }
}

void TMXLayer::setFlaggedTileGIDByIndex(int index, int gid)
{
    if(gid == _tiles[index]) return;
    _tiles[index] = gid;
    _quadsDirty = true;
    _dirty = true;
}

void TMXLayer::removeChild(Node* node, bool cleanup)
{
    int tag = node->getTag();
    auto it = _spriteContainer.find(tag);
    if (it != _spriteContainer.end() && it->second.first == node)
    {
        _spriteContainer.erase(it);
    }
    Node::removeChild(node, cleanup);
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
    auto vertexz = getProperty("cc_vertexz");
    if (vertexz.isNull()) return;
    
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

//CCTMXLayer2 - obtaining positions, offset
Vec2 TMXLayer::calculateLayerOffset(const Vec2& pos)
{
    Vec2 ret = Vec2::ZERO;
    switch (_layerOrientation) 
    {
    case FAST_TMX_ORIENTATION_ORTHO:
        ret = Vec2( pos.x * _mapTileSize.width, -pos.y *_mapTileSize.height);
        break;
    case FAST_TMX_ORIENTATION_ISO:
        ret = Vec2((_mapTileSize.width /2) * (pos.x - pos.y),
                  (_mapTileSize.height /2 ) * (-pos.x - pos.y));
        break;
    case FAST_TMX_ORIENTATION_HEX:
    default:
        CCASSERT(pos.equals(Vec2::ZERO), "offset for this map not implemented yet");
        break;
    }
    return ret;    
}

// TMXLayer - adding / remove tiles
void TMXLayer::setTileGID(int gid, const Vec2& tileCoordinate)
{
    setTileGID(gid, tileCoordinate, (TMXTileFlags)0);
}

void TMXLayer::setTileGID(int gid, const Vec2& tileCoordinate, TMXTileFlags flags)
{
    CCASSERT(tileCoordinate.x < _layerSize.width && tileCoordinate.y < _layerSize.height && tileCoordinate.x >=0 && tileCoordinate.y >=0, "TMXLayer: invalid position");
    CCASSERT(_tiles, "TMXLayer: the tiles map has been released");
    CCASSERT(gid == 0 || gid >= _tileSet->_firstGid, "TMXLayer: invalid gid" );
    
    TMXTileFlags currentFlags;
    int currentGID = getTileGIDAt(tileCoordinate, &currentFlags);
    
    if (currentGID == gid && currentFlags == flags) return;
    
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
        setFlaggedTileGIDByIndex(z, gidAndFlags);
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
            setFlaggedTileGIDByIndex(z, gidAndFlags);
        }
    }
}

void TMXLayer::setupTileSprite(Sprite* sprite, Vec2 pos, int gid)
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
        sprite->setPosition(getPositionAt(pos).x + sprite->getContentSize().height/2,
                                  getPositionAt(pos).y + sprite->getContentSize().width/2 );
        
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

std::string TMXLayer::getDescription() const
{
    return StringUtils::format("<FastTMXLayer | tag = %d, size = %d,%d>", _tag, (int)_mapTileSize.width, (int)_mapTileSize.height);
}

} //end of namespace experimental

NS_CC_END
