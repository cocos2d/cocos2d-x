/****************************************************************************
Copyright (c) 2009-2010 Ricardo Quesada
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
#ifndef __CCTMX_TILE_MAP_H__
#define __CCTMX_TILE_MAP_H__

#include "2d/CCNode.h"
#include "2d/CCTMXObjectGroup.h"
#include "base/CCValue.h"

NS_CC_BEGIN

class TMXLayer;
class TMXLayerInfo;
class TMXTilesetInfo;
class TMXMapInfo;

/**
 * @addtogroup _2d
 * @{
 */


/** @~english Possible orientations of the TMX map.  @~chinese TMXmap的方位。*/
enum
{
    /** @~english Orthogonal orientation.  @~chinese 直角鸟瞰定向(orientation)。 */
    TMXOrientationOrtho,

    /** @~english Hexagonal orientation.  @~chinese  六边形定向(orientation)。 */
    TMXOrientationHex,

    /** @~english Isometric orientation.  @~chinese 持等距斜视定向(orientation)。*/
    TMXOrientationIso,
    
    /** @~english Isometric staggered orientation.  @~chinese 等距交错定向。*/
    TMXOrientationStaggered,
};

/** @brief @~english TMXTiledMap knows how to parse and render a TMX map.

 * It adds support for the TMX tiled map format used by http://www.mapeditor.org
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
 * Each layer is created using an TMXLayer (subclass of SpriteBatchNode). If you have 5 layers, then 5 TMXLayer will be created,
 * unless the layer visibility is off. In that case, the layer won't be created at all.
 * You can obtain the layers (TMXLayer objects) at runtime by:
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

 * @~chinese TMXTiledMap知道如何解析和渲染TMX地图。
 * 
 * http://www.mapeditor.org官网将其加入支持TMX tiled地图格式
 * 其支持等距斜视(isometric),六边形(hexagonal),直角鸟瞰(orthogonal)tiles
 * 也支持对象组,多对象以及多属性
 * 
 * 特点:
 * - 每个TMXTiledMap都被当作一个精灵
 * - 这些精灵需要时被创建而且仅当调用layer->tileAt(position)时才会被创建
 * - 每个tile继承了精灵的特点，可以旋转/移动/缩放/着色/透明化
 * - Tiles可以在运行时添加或删除
 * - Tiles的z-order亦可在运行时修改
 * - 每个tile的锚点是(0,0)
 * - TMXTileMap的锚点是(0,0)
 * - TMX layers可以当作子节点添加
 * - TXM layers默认会设置一个别名
 * - Tileset图片可以在使用TextureCache时加入
 * - 每个tile都有一个唯一的tag
 * - 每个tile都有一个唯一的z值.左上(top-left): z=1, 右下(bottom-right): z=max z
 * - 每个对象组(object group)可以用作可变数组(MutaleArray)
 * - 对象类包含的属性都存储在一个字典(dictionary)中
 * - 属性可以赋值给地图(Map),层(Layer),对象属性(Object Group)以及对象(Object)
 * 
 * 限制:
 * - 每个layer只支持一个tileset
 * - 不支持嵌入式图片(Embedded images)
 * - 只支持XML格式(不支持JSON格式)。
 * 
 * 技术描述:
 * 每个layer被创建成TMXLayer(继承自SpriteBatchNode)。
 * 如果layer是可视的,那么如果你有5个layer,则5个TMXLayer被创建.
 * 如果不可视,则layer根本不会被创建。
 * 在运行时,可通过如下获取layers(TMXLayer objects):
 * - map->getChildByTag(tag_number);  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
 * - map->getLayer(name_of_the_layer);
 * 
 * 每个对象组被创建成一个继承自MutableArray的TMXObjectGroup
 * 运行时,可通过如下获取该对象组:
 * - map->getObjectGroup(name_of_the_object_group);//name_of_the_object_group 对象组名
 * 每个object都是一个TMXObject
 * 每个属性都通过key-value对存储在一个MutableDictionary里
 * 运行时,可通过如下获取属性:
 * 
 * map->getProperty(name_of_the_property);
 * layer->getProperty(name_of_the_property);
 * objectGroup->getProperty(name_of_the_property);
 * object->getProperty(name_of_the_property);
 * 
 * @since v0.8.1
 */
class CC_DLL TMXTiledMap : public Node
{
public:
    /** @~english Creates a TMX Tiled Map with a TMX file.
     *
     * @~chinese 通过指定TMX文件创建一个TMX Tiled地图。
     * 
     * @param tmxFile @~english A TMX file.
     * @~chinese TMX文件。
     * @return @~english An autorelease object.
     * @~chinese 一个autorelease对象。
     */
    static TMXTiledMap* create(const std::string& tmxFile);

    /** @~english Initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources. 
     *
     * @~chinese通过一个指定的TMX格式的XML和TMX资源路径创建一个TMX Tiled地图。
     * 
     * @param tmxString @~english A TMX formatted XML string.
     * @~chinese TMX格式的XML字符串。
     * @param resourcePath @~english The path to TMX resources.
     * @~chinese TMX的资源路径。
     * @return @~english An autorelease object.
     * @~chinese 一个autorelease对象。
     * @js NA
     */
    static TMXTiledMap* createWithXML(const std::string& tmxString, const std::string& resourcePath);

    /** @~english Return the TMXLayer for the specific layer. 
     *
     * @~chinese 通过layerName获取对应的TMXLayer。
     * 
     * @param layerName @~english A specific layer.
     * @~chinese 一个指定的层名称。
     * @return @~english The TMXLayer for the specific layer.
     * @~chinese 指定层名称的TMXLayer层。
     */
    TMXLayer* getLayer(const std::string& layerName) const;

    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE TMXLayer* layerNamed(const std::string& layerName) const { return getLayer(layerName); };

    /** @~english Return the TMXObjectGroup for the specific group. 
     *
     * @~chinese 通过groupName获取对应的TMXObjectGroup。
     * 
     * @param groupName @~english The group Name.
     * @~chinese 组名称。
     * @return @~english A Type of TMXObjectGroup.
     * @~chinese TMXObjectGroup。
     */
    TMXObjectGroup* getObjectGroup(const std::string& groupName) const;

    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE TMXObjectGroup* objectGroupNamed(const std::string& groupName) const { return getObjectGroup(groupName); };

    /** @~english Return the value for the specific property name. 
     *
     * @~chinese  通过propertyName获取对应的Property。
     * 
     * @param propertyName @~english The specific property name.
     * @~chinese 指定的属性名。
     * @return @~english Return the value for the specific property name.
     * @~chinese 返回指定属性名的值。
     */
    Value getProperty(const std::string& propertyName) const;

    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Value propertyNamed(const char *propertyName) const { return getProperty(propertyName); };

    /** @~english Return properties dictionary for tile GID. 
     *
     * @~chinese 通过GID获取对应的属性字典(properties dictionary)。
     * 
     * @param GID @~english The tile GID.
     * @~chinese 瓦片GID。
     * @return @~english Return properties dictionary for tile GID.
     * @~chinese 返回属性字典。
     */
    Value getPropertiesForGID(int GID) const;

    CC_DEPRECATED_ATTRIBUTE Value propertiesForGID(int GID) const { return getPropertiesForGID(GID); };

    /** @~english Assings properties to argument value, returns true if it did found properties 
     * for that GID and did assinged a value, else it returns false.
     *
     * @~chinese 通过指定GID查找其对应的属性变量,并赋予属性值value,
     * 如成功查找到并赋值成功,则返回true,反之则为false。
     * 
     * @param GID @~english The tile GID.
     * @~chinese 瓦片GID。
     * @param value @~english Argument value.
     * @~chinese 参数值。
     * @return @~english Return true if it did found properties for that GID and did assinged a value, else it returns false.
     * @~chinese 如成功查找到并赋值成功,则返回true,反之则为falsee。
     */
    bool getPropertiesForGID(int GID, Value** value);

    /** @~english The map's size property measured in tiles. 
     *
     * @~chinese 获取以tiles数量为基准的地图尺寸
     * 
     * @return @~english The map's size property measured in tiles.
     * @~chinese 以tiles数量为基准的地图尺寸。
     */
    inline const Size& getMapSize() const { return _mapSize; };
    
    /** @~english Set the map's size property measured in tiles. 
     *
     * @~chinese 设置以tiles数量为基准的地图尺寸。
     * 
     * @param mapSize @~english The map's size property measured in tiles.
     * @~chinese 以tiles数量为基准的地图尺寸。
     */
    inline void setMapSize(const Size& mapSize) { _mapSize = mapSize; };

    /** @~english The tiles's size property measured in pixels. 
     *
     * @~chinese 获取以像素点为基准的tile尺寸属性。
     * 
     * @return @~english The tiles's size property measured in pixels.
     * @~chinese 以像素点为基准的tile尺寸属性。
     */
    inline const Size& getTileSize() const { return _tileSize; };
    
    /** @~english Set the tiles's size property measured in pixels. 
     *
     * @~chinese 设置以像素点为基准的tile尺寸属性。
     * 
     * @param tileSize @~english The tiles's size property measured in pixels.
     * @~chinese 以像素点为基准的tile尺寸属性。
     */
    inline void setTileSize(const Size& tileSize) { _tileSize = tileSize; };

    /** @~english Map orientation. 
     *
     * @~chinese 获取地图定向(orientation)
     * 
     * @return @~english Map orientation.
     * @~chinese 地图定向(orientation)
     */
    inline int getMapOrientation() const { return _mapOrientation; };
    
    /** @~english Set map orientation. 
     *
     * @~chinese 设置地图定向(orientation)
     * 
     * @param mapOrientation @~english The map orientation.
     * @~chinese 地图定向(orientation)
     */
    inline void setMapOrientation(int mapOrientation) { _mapOrientation = mapOrientation; };

    /** @~english Get the Object groups. 
     *
     * @~chinese 获取对象组。
     * 
     * @return @~english The object groups.
     * @~chinese 对象组。
     */
    inline const Vector<TMXObjectGroup*>& getObjectGroups() const { return _objectGroups; };
    inline Vector<TMXObjectGroup*>& getObjectGroups() { return _objectGroups; };
    
    /** @~english Set the object groups. 
     *
     * @~chinese 设置对象组。
     * 
     * @param groups @~english The object groups.
     * @~chinese 对象组。
     */
    inline void setObjectGroups(const Vector<TMXObjectGroup*>& groups) {
        _objectGroups = groups;
    };
    
    /** @~english Properties. 
     *
     * @~chinese 获取属性。
     * 
     * @return @~english Properties.
     * @~chinese ValueMap属性。
     */
    inline ValueMap& getProperties() { return _properties; };
    
    /** @~english Set the properties.
     *
     * @~chinese 设置属性。
     * 
     * @param properties @~english A  Type of ValueMap to set the properties.
     * @~chinese ValueMap属性。
     */
    inline void setProperties(const ValueMap& properties) {
        _properties = properties;
    };
    
    /** @~english Get the description.
     * @~chinese 得到了描述。
     * @js NA
     */
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    TMXTiledMap();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXTiledMap();
    
    /** @~english initializes a TMX Tiled Map with a TMX file  @~chinese 通过指定的TMX文件初始化TMXTiledMap*/
    bool initWithTMXFile(const std::string& tmxFile);
    
    /** @~english initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources  @~chinese 通过指定的TMX格式XML字符串来初始化TMXTiledMap */
    bool initWithXML(const std::string& tmxString, const std::string& resourcePath);

protected:
    TMXLayer * parseLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    TMXTilesetInfo * tilesetForLayer(TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo);
    void buildWithMapInfo(TMXMapInfo* mapInfo);

    /** @~english the map's size property measured in tiles  @~chinese 地图的大小属性用瓦片*/
    Size _mapSize;
    /** @~english the tiles's size property measured in pixels  @~chinese 瓦片的大小属性以像素*/
    Size _tileSize;
    /** @~english map orientation  @~chinese 地图定位*/
    int _mapOrientation;
    /** @~english object groups  @~chinese 对象组*/
    Vector<TMXObjectGroup*> _objectGroups;
    /** @~english properties  @~chinese 属性*/
    ValueMap _properties;
    
    //! tile properties
    ValueMapIntKey _tileProperties;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(TMXTiledMap);

};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_TILE_MAP_H__


