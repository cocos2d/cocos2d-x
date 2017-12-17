/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2017 Chukong Technologies Inc.

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
#ifndef __CC_FAST_TMX_LAYER_H__
#define __CC_FAST_TMX_LAYER_H__

#include <map>
#include <unordered_map>
#include "2d/CCNode.h"
#include "2d/CCTMXXMLParser.h"
#include "renderer/CCPrimitiveCommand.h"
#include "base/CCMap.h"

NS_CC_BEGIN

class TMXMapInfo;
class TMXLayerInfo;
class TMXTilesetInfo;
class Texture2D;
class Sprite;
struct _ccCArray;

namespace experimental{

/**
 * @addtogroup _2d
 * @{
 */

/** @brief FastTMXLayer represents the TMX layer.

 * It is a subclass of SpriteBatchNode. By default the tiles are rendered using a TextureAtlas.
 * If you modify a tile on runtime, then, that tile will become a Sprite, otherwise no Sprite objects are created.
 * The benefits of using Sprite objects as tiles are:
 * - tiles (Sprite) can be rotated/scaled/moved with a nice API.

 * If the layer contains a property named "cc_vertexz" with an integer (in can be positive or negative),
 * then all the tiles belonging to the layer will use that value as their OpenGL vertex Z for depth.

 * On the other hand, if the "cc_vertexz" property has the "automatic" value, then the tiles will use an automatic vertex Z value.
 * Also before drawing the tiles, GL_ALPHA_TEST will be enabled, and disabled after drawing them. The used alpha func will be:

 * glAlphaFunc( GL_GREATER, value ).

 * "value" by default is 0, but you can change it from Tiled by adding the "cc_alpha_func" property to the layer.
 * The value 0 should work for most cases, but if you have tiles that are semi-transparent, then you might want to use a different
 * value, like 0.5.
 
 * For further information, please see the programming guide:
 * http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:tiled_maps
 
 * @since v3.2
 * @js NA
 */

class CC_DLL TMXLayer : public Node
{
public:
    /** Creates a FastTMXLayer with an tileset info, a layer info and a map info.
     *
     * @param tilesetInfo An tileset info.
     * @param layerInfo A layer info.
     * @param mapInfo A map info.
     * @return Return an autorelease object.
     */
    static TMXLayer * create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    /**
     * @js ctor
     */
    TMXLayer();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXLayer();

    /** Returns the tile gid at a given tile coordinate. It also returns the tile flags.
     * 
     * @param tileCoordinate The tile coordinate.
     * @param flags A TMXTileFlags.
     * @return The tile gid at a given tile coordinate. It also returns the tile flags.
     */
    int getTileGIDAt(const Vec2& tileCoordinate, TMXTileFlags* flags = nullptr);

    /** Sets the tile gid (gid = tile global id) at a given tile coordinate.
     * The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
     * If a tile is already placed at that position, then it will be removed.
     * @param gid The gid value.
     * @param tileCoordinate The tile coordinate.
     */
    void setTileGID(int gid, const Vec2& tileCoordinate);

    /** Sets the tile gid (gid = tile global id) at a given tile coordinate.
     * The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
     * If a tile is already placed at that position, then it will be removed.
     * Use withFlags if the tile flags need to be changed as well.
     *
     * @param gid A integer value,it will be sets the tile gid.
     * @param tileCoordinate The tile coordinate.
     * @param flags A TMXTileFlags.
     */
    void setTileGID(int gid, const Vec2& tileCoordinate, TMXTileFlags flags);

    /** Removes a tile at given tile coordinate.
     *
     * @param tileCoordinate The tile Coordinate.
     */
    void removeTileAt(const Vec2& tileCoordinate);

    /** Returns the position in points of a given tile coordinate.
     *
     * @param tileCoordinate The tile Coordinate.
     * @return The position in points of a given tile coordinate.
     */
    Vec2 getPositionAt(const Vec2& tileCoordinate);

    /** Return the value for the specific property name.
     *
     * @param propertyName The value for the specific property name.
     * @return The value for the specific property name.
     */
    Value getProperty(const std::string& propertyName) const;

    /** Creates the tiles. */
    void setupTiles();
    
    /** Get the tile layer name.
     *
     * @return The tile layer name.
     */
    const std::string& getLayerName() { return _layerName; }
    
    /** Set the tile layer name.
     *
     * @param layerName The new layer name.
     */
    void setLayerName(const std::string& layerName) { _layerName = layerName; }

    /** Size of the layer in tiles.
     *
     * @return Size of the layer in tiles.
     */
    const Size& getLayerSize() const { return _layerSize; }
    
    /** Set the size of the layer in tiles. 
     *
     * @param size The new size of the layer in tiles.
     */
    void setLayerSize(const Size& size) { _layerSize = size; }
    
    /** Size of the map's tile (could be different from the tile's size).
     *
     * @return Size of the map's tile (could be different from the tile's size).
     */
    const Size& getMapTileSize() const { return _mapTileSize; }
    
    /** Set the size of the map's tile. 
     *
     * @param size The new size of the map's tile.
     */
    void setMapTileSize(const Size& size) { _mapTileSize = size; }
    
    /** Pointer to the map of tiles.
     * @js NA
     * @lua NA
     * @return The pointer to the map of tiles.
     */
    const uint32_t* getTiles() const { return _tiles; };
    
    /** Set the pointer to the map of tiles.
     *
     * @param tiles The pointer to the map of tiles.
     */
    void setTiles(uint32_t* tiles) { _tiles = tiles; _quadsDirty = true;};
    
    /** Tileset information for the layer.
     *
     * @return Tileset information for the layer.
     */
    TMXTilesetInfo* getTileSet() const { return _tileSet; }
    
    /** Set the tileset information for the layer. 
     *
     * @param info The new tileset information for the layer.
     */
    void setTileSet(TMXTilesetInfo* info) {
        CC_SAFE_RETAIN(info);
        CC_SAFE_RELEASE(_tileSet);
        _tileSet = info;
    }
    
    /** Layer orientation, which is the same as the map orientation.
     *
     * @return Layer orientation, which is the same as the map orientation.
     */
    int getLayerOrientation() const { return _layerOrientation; }
    
    /** Set Layer orientation, which is the same as the map orientation. 
     *
     * @param orientation Layer orientation, which is the same as the map orientation.
     */
    void setLayerOrientation(int orientation) { _layerOrientation = orientation; }
    
    /** Properties from the layer. They can be added using Tiled. 
     *
     * @return Properties from the layer. They can be added using Tiled.
     */
    const ValueMap& getProperties() const { return _properties; }
    
    /** Properties from the layer. They can be added using Tiled.
     *
     * @return Properties from the layer. They can be added using Tiled.
     */
    ValueMap& getProperties() { return _properties; }
    
    /** Set the properties to the layer.
     *
     * @param properties The properties to the layer.
     */
    void setProperties(const ValueMap& properties)
    {
        _properties = properties;
    }

    /** Returns the tile (Sprite) at a given a tile coordinate.
     * The returned Sprite will be already added to the TMXLayer. Don't add it again.
     * The Sprite can be treated like any other Sprite: rotated, scaled, translated, opacity, color, etc.
     * You can remove either by calling:
     * - layer->removeChild(sprite, cleanup);
     *
     * @return Returns the tile (Sprite) at a given a tile coordinate.
     */
    Sprite* getTileAt(const Vec2& tileCoordinate);
    
    /** Set an sprite to the tile,with the tile coordinate and gid.
     *
     * @param sprite A Sprite.
     * @param pos The tile coordinate.
     * @param gid The tile gid.
     */
    void setupTileSprite(Sprite* sprite, const Vec2& pos, uint32_t gid);

    //
    // Override
    //
    virtual std::string getDescription() const override;
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
    void removeChild(Node* child, bool cleanup = true) override;

protected:

    bool initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    void updateTiles(const Rect& culledRect);
    Vec2 calculateLayerOffset(const Vec2& offset);

    /* The layer recognizes some special properties, like cc_vertexz */
    void parseInternalProperties();
    
    Mat4 tileToNodeTransform();
    Rect tileBoundsForClipTransform(const Mat4 &tileToClip);
    
    int getVertexZForPos(const Vec2& pos);
    
    //Flip flags is packed into gid
    void setFlaggedTileGIDByIndex(int index, uint32_t gid);
    
    //
    void updateTotalQuads();
    
    void onDraw(Primitive* primitive);
    int getTileIndexByPos(int x, int y) const { return x + y * (int) _layerSize.width; }
    
    void updateVertexBuffer();
    void updateIndexBuffer();
    void updatePrimitives();
protected:
    
    //! name of the layer
    std::string _layerName;

    /** size of the layer in tiles */
    Size _layerSize;
    /** size of the map's tile (could be different from the tile's size) */
    Size _mapTileSize;
    /** pointer to the map of tiles */
    uint32_t* _tiles;
    /** Tileset information for the layer */
    TMXTilesetInfo* _tileSet;
    /** Layer orientation, which is the same as the map orientation */
    int _layerOrientation;
    /** properties from the layer. They can be added using Tiled */
    ValueMap _properties;

    Texture2D *_texture;
    
    /** container for sprite children. map<index, pair<sprite, gid> > */
    std::map<int, std::pair<Sprite*, int> > _spriteContainer;

    //GLuint _buffersVBO; //0: vertex, 1: indices

    Size _screenGridSize;
    Rect _screenGridRect;
    int _screenTileCount;
    
    int _vertexZvalue;
    bool _useAutomaticVertexZ;
    
    /** tile coordinate to node coordinate transform */
    Mat4 _tileToNodeTransform;
    /** data for rendering */
    bool _quadsDirty;
    std::vector<int> _tileToQuadIndex;
    std::vector<V3F_C4B_T2F_Quad> _totalQuads;
#ifdef CC_FAST_TILEMAP_32_BIT_INDICES
    std::vector<GLuint> _indices;
#else
    std::vector<GLushort> _indices;
#endif
    std::map<int/*vertexZ*/, int/*offset to _indices by quads*/> _indicesVertexZOffsets;
    std::unordered_map<int/*vertexZ*/, int/*number to quads*/> _indicesVertexZNumber;
    std::vector<PrimitiveCommand> _renderCommands;
    bool _dirty;
    
    VertexBuffer* _vertexBuffer;
    
    VertexData* _vData;
    
    IndexBuffer* _indexBuffer;
    
    Map<int , Primitive*> _primitives;
    
public:
    /** Possible orientations of the TMX map */
    static const int FAST_TMX_ORIENTATION_ORTHO;
    static const int FAST_TMX_ORIENTATION_HEX;
    static const int FAST_TMX_ORIENTATION_ISO;
};

// end of tilemap_parallax_nodes group
/// @}
} //end of namespace experimental
NS_CC_END

#endif //__CCTMX_LAYER2_H__
