/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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
#ifndef __CCTMX_TILE_MAP_H__
#define __CCTMX_TILE_MAP_H__
#include "CCNode.h"
#include "CCTMXObjectGroup.h"

namespace cocos2d {

	class CCTMXObjectGroup;
	class CCTMXLayer;
	class CCTMXLayerInfo;
	class CCTMXTilesetInfo;
	class CCTMXMapInfo;

	/** Possible oritentations of the TMX map */
	enum
	{
		/** Orthogonal orientation */
		CCTMXOrientationOrtho,

		/** Hexagonal orientation */
		CCTMXOrientationHex,

		/** Isometric orientation */
		CCTMXOrientationIso,
	};

	/** @brief CCTMXTiledMap knows how to parse and render a TMX map.

	It adds support for the TMX tiled map format used by http://www.mapeditor.org
	It supports isometric, hexagonal and orthogonal tiles.
	It also supports object groups, objects, and properties.

	Features:
	- Each tile will be treated as an CCSprite
	- The sprites are created on demand. They will be created only when you call "layer->tileAt(position)"
	- Each tile can be rotated / moved / scaled / tinted / "opacitied", since each tile is a CCSprite
	- Tiles can be added/removed in runtime
	- The z-order of the tiles can be modified in runtime
	- Each tile has an anchorPoint of (0,0)
	- The anchorPoint of the TMXTileMap is (0,0)
	- The TMX layers will be added as a child
	- The TMX layers will be aliased by default
	- The tileset image will be loaded using the CCTextureCache
	- Each tile will have a unique tag
	- Each tile will have a unique z value. top-left: z=1, bottom-right: z=max z
	- Each object group will be treated as an CCMutableArray
	- Object class which will contain all the properties in a dictionary
	- Properties can be assigned to the Map, Layer, Object Group, and Object

	Limitations:
	- It only supports one tileset per layer.
	- Embeded images are not supported
	- It only supports the XML format (the JSON format is not supported)

	Technical description:
	Each layer is created using an CCTMXLayer (subclass of CCSpriteBatchNode). If you have 5 layers, then 5 CCTMXLayer will be created,
	unless the layer visibility is off. In that case, the layer won't be created at all.
	You can obtain the layers (CCTMXLayer objects) at runtime by:
	- map->getChildByTag(tag_number);  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
	- map->layerNamed(name_of_the_layer);

	Each object group is created using a CCTMXObjectGroup which is a subclass of CCMutableArray.
	You can obtain the object groups at runtime by:
	- map->objectGroupNamed(name_of_the_object_group);

	Each object is a CCTMXObject.

	Each property is stored as a key-value pair in an CCMutableDictionary.
	You can obtain the properties at runtime by:

	map->propertyNamed(name_of_the_property);
	layer->propertyNamed(name_of_the_property);
	objectGroup->propertyNamed(name_of_the_property);
	object->propertyNamed(name_of_the_property);

	@since v0.8.1
	*/
	class CC_DLL CCTMXTiledMap : public CCNode
	{
		/** the map's size property measured in tiles */
		CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tMapSize, MapSize);
		/** the tiles's size property measured in pixels */
		CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tTileSize, TileSize);
		/** map orientation */
		CC_SYNTHESIZE(int, m_nMapOrientation, MapOrientation);
		/** object groups */
		CC_PROPERTY(CCMutableArray<CCTMXObjectGroup*>*, m_pObjectGroups, ObjectGroups);
		/** properties */
		CC_PROPERTY(CCStringToStringDictionary*, m_pProperties, Properties);
	public:
		CCTMXTiledMap();
		virtual ~CCTMXTiledMap();

		/** creates a TMX Tiled Map with a TMX file.*/
		static CCTMXTiledMap * tiledMapWithTMXFile(const char *tmxFile);

		/** initializes a TMX Tiled Map with a TMX file */
		bool initWithTMXFile(const char *tmxFile);

		/** return the TMXLayer for the specific layer */
		CCTMXLayer* layerNamed(const char *layerName);

		/** return the TMXObjectGroup for the secific group */
		CCTMXObjectGroup* objectGroupNamed(const char *groupName);

		/** return the value for the specific property name */
		CCString *propertyNamed(const char *propertyName);

		/** return properties dictionary for tile GID */
		CCDictionary<std::string, CCString*> *propertiesForGID(int GID);

	private:
 		CCTMXLayer * parseLayer(CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo);
 		CCTMXTilesetInfo * tilesetForLayer(CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo);

	protected:
		//! tile properties
        CCDictionary<int, CCStringToStringDictionary*> *m_pTileProperties;
        CCDictionary<std::string, CCTMXLayer*> *m_pTMXLayers;

	};

}// namespace cocos2d
#endif //__CCTMX_TILE_MAP_H__


