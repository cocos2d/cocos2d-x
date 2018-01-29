/****************************************************************************
Copyright (c) 2009-2010 Ricardo Quesada
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
#ifndef __CC_FAST_TMX_TILEMAP_H__
#define __CC_FAST_TMX_TILEMAP_H__

#include "2d/CCNode.h"
#include "2d/CCTMXObjectGroup.h"

NS_CC_BEGIN

class TMXLayerInfo;
class TMXTilesetInfo;
class TMXMapInfo;

namespace experimental {
    
class TMXLayer;
/**
 * @addtogroup _2d
 * @{
 */
    
/** @brief FastTMXTiledMap knows how to parse and render a TMX map.

 * It adds support for the TMX tiled map format used by http://www.mapeditor.org.
 * It supports isometric, hexagonal and orthogonal tiles.
 * It also supports object groups, objects, and properties.

 * Features:
 * - Each tile will be treated as an Sprite.
 * - The sprites are created on demand. They will be created only when you call "layer->tileAt(position)".
 * - Each tile can be rotated / moved / scaled / tinted / "opaqued", since each tile is a Sprite.
 * - Tiles can be added/removed in runtime.
 * - The z-order of the tiles can be modified in runtime.
 * - Each tile has an anchorPoint of (0,0).
 * - The anchorPoint of the TMXTileMap is (0,0).
 * - The TMX layers will be added as a child.
 * - The TMX layers will be aliased by default.
 * - The tileset image will be loaded using the TextureCache.
 * - Each tile will have a unique tag.
 * - Each tile will have a unique z value. top-left: z=1, bottom-right: z=max z.
 * - Each object group will be treated as an MutableArray.
 * - Object class which will contain all the properties in a dictionary.
 * - Properties can be assigned to the Map, Layer, Object Group, and Object.

 * Limitations:
 * - It only supports one tileset per layer.
 * - Embedded images are not supported.
 * - It only supports the XML format (the JSON format is not supported).

 * Technical description:
 * Each layer is created using an FastTMXLayer (subclass of SpriteBatchNode). If you have 5 layers, then 5 FastTMXLayer will be created,
 * unless the layer visibility is off. In that case, the layer won't be created at all.
 * You can obtain the layers (FastTMXLayer objects) at runtime by:
 * - map->getChildByTag(tag_number);  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
 * - map->getLayer(name_of_the_layer);

 * Each object group is created using a TMXObjectGroup which is a subclass of MutableArray.
 * You can obtain the object groups at runtime by:
 * - map->getObjectGroup(name_of_the_object_group);

 * Each object is a TMXObject.

 * Each property is stored as a key-value pair in an MutableDictionary.
 * You can obtain the properties at runtime by:

 * map->getProperty(name_of_the_property);
 * layer->getProperty(name_of_the_property);
 * objectGroup->getProperty(name_of_the_property);
 * object->getProperty(name_of_the_property);

 * @since v3.2
 * @js NA
 */
class CC_DLL TMXTiledMap : public Node
{
public:
    /** Creates a TMX Tiled Map with a TMX file.
     *
     * @return An autorelease object.
     */
    static TMXTiledMap* create(const std::string& tmxFile);

    /** Initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources. 
     *
     * @param tmxString A TMX formatted XML string.
     * @param resourcePath A path to TMX resources.
     * @return An autorelease object.
     */
    static TMXTiledMap* createWithXML(const std::string& tmxString, const std::string& resourcePath);

    /** Return the FastTMXLayer for the specific layer. 
     * 
     * @return Return the FastTMXLayer for the specific layer.
     */
    TMXLayer* getLayer(const std::string& layerName) const;

    /** Return the TMXObjectGroup for the specific group. 
     * 
     * @return Return the TMXObjectGroup for the specific group.
     */
    TMXObjectGroup* getObjectGroup(const std::string& groupName) const;

    /** Return the value for the specific property name.
     *
     * @return Return the value for the specific property name.
     */
    Value getProperty(const std::string& propertyName) const;

    /** Return properties dictionary for tile GID.
     *
     * @return Return properties dictionary for tile GID.
     */
    Value getPropertiesForGID(int GID) const;

    /** The map's size property measured in tiles. 
     *
     * @return The map's size property measured in tiles.
     */
    const Size& getMapSize() const { return _mapSize; }
    
    /** Set the map's size property measured in tiles.
     *
     * @param mapSize The map's size property measured in tiles.
     */
    void setMapSize(const Size& mapSize) { _mapSize = mapSize; }

    /** The tiles's size property measured in pixels.
     *
     * @return The tiles's size property measured in pixels.
     */
    const Size& getTileSize() const { return _tileSize; }
    
    /** Set the tiles's size property measured in pixels. 
     *
     * @param tileSize The tiles's size property measured in pixels.
     */
    void setTileSize(const Size& tileSize) { _tileSize = tileSize; }

    /** Get map orientation. 
     *
     * @return The map orientation.
     */
    int getMapOrientation() const { return _mapOrientation; }
    
    /** Set map orientation. 
     *
     * @param mapOrientation The map orientation.
     */
    void setMapOrientation(int mapOrientation) { _mapOrientation = mapOrientation; }

    /** Get object groups. 
     *
     * @return Object groups.
     */
    const Vector<TMXObjectGroup*>& getObjectGroups() const { return _objectGroups; }
    Vector<TMXObjectGroup*>& getObjectGroups() { return _objectGroups; }
    
    /** Set object groups. 
     *
     * @param groups An object groups.
     */
    void setObjectGroups(const Vector<TMXObjectGroup*>& groups) {
        _objectGroups = groups;
    }
    
    /** Get properties.
     *
     * @return Properties.
     */
    const ValueMap& getProperties() const { return _properties; }
    
    /** Set properties. 
     *
     * @param properties An ValueMap Properties.
     */
    void setProperties(const ValueMap& properties) {
        _properties = properties;
    }

    virtual std::string getDescription() const override;

protected:
    /**
     * @js ctor
     */
    TMXTiledMap();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXTiledMap();

    /** initializes a TMX Tiled Map with a TMX file */
    bool initWithTMXFile(const std::string& tmxFile);

    /** initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources */
    bool initWithXML(const std::string& tmxString, const std::string& resourcePath);
    
    TMXLayer * parseLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    TMXTilesetInfo * tilesetForLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    void buildWithMapInfo(TMXMapInfo* mapInfo);

    /** the map's size property measured in tiles */
    Size _mapSize;
    /** the tiles's size property measured in pixels */
    Size _tileSize;
    /** map orientation */
    int _mapOrientation;
    /** object groups */
    Vector<TMXObjectGroup*> _objectGroups;
    /** properties */
    ValueMap _properties;
    
    //! tile properties
    ValueMapIntKey _tileProperties;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TMXTiledMap);

};

// end of tilemap_parallax_nodes group
/** @} */
    
} //end of namespace experimental

NS_CC_END

#endif //__CCTMX_TILE_MAP2_H__


