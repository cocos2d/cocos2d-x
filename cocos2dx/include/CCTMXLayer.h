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
#ifndef __CCTMX_LAYER_H__
#define __CCTMX_LAYER_H__
#include "CCTMXObjectGroup.h"
#include "CCAtlasNode.h"
#include "CCSpriteBatchNode.h"
namespace cocos2d {

	class CCTMXMapInfo;
	class CCTMXLayerInfo;
	class CCTMXTilesetInfo;
	struct _ccCArray;

	/** @brief CCTMXLayer represents the TMX layer.

	It is a subclass of CCSpriteBatchNode. By default the tiles are rendered using a CCTextureAtlas.
	If you modify a tile on runtime, then, that tile will become a CCSprite, otherwise no CCSprite objects are created.
	The benefits of using CCSprite objects as tiles are:
	- tiles (CCSprite) can be rotated/scaled/moved with a nice API

	If the layer contains a property named "cc_vertexz" with an integer (in can be positive or negative),
	then all the tiles belonging to the layer will use that value as their OpenGL vertex Z for depth.

	On the other hand, if the "cc_vertexz" property has the "automatic" value, then the tiles will use an automatic vertex Z value.
	Also before drawing the tiles, GL_ALPHA_TEST will be enabled, and disabled after drawin them. The used alpha func will be:

	glAlphaFunc( GL_GREATER, value )

	"value" by default is 0, but you can change it from Tiled by adding the "cc_alpha_func" property to the layer.
	The value 0 should work for most cases, but if you have tiles that are semi-transparent, then you might want to use a differnt
	value, like 0.5.

	For further information, please see the programming guide:

	http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:tiled_maps

	@since v0.8.1
	*/
	class CC_DLL CCTMXLayer : public CCSpriteBatchNode
	{
		/** size of the layer in tiles */
		CC_SYNTHESIZE(CCSize, m_tLayerSize, LayerSize);
		/** size of the map's tile (could be differnt from the tile's size) */
		CC_SYNTHESIZE(CCSize, m_tMapTileSize, MapTileSize);
		/** pointer to the map of tiles */
		CC_SYNTHESIZE(unsigned int*, m_pTiles, Tiles);
		/** Tilset information for the layer */
		CC_PROPERTY(CCTMXTilesetInfo*, m_pTileSet, TileSet);
		/** Layer orientation, which is the same as the map orientation */
		CC_SYNTHESIZE(unsigned int, m_uLayerOrientation, LayerOrientation);
		/** properties from the layer. They can be added using Tiled */
		CC_PROPERTY(CCStringToStringDictionary*, m_pProperties, Properties);
	public:
		CCTMXLayer();
		virtual ~CCTMXLayer();
		/** creates a CCTMXLayer with an tileset info, a layer info and a map info */
		static CCTMXLayer * layerWithTilesetInfo(CCTMXTilesetInfo *tilesetInfo, CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo);
		/** initializes a CCTMXLayer with a tileset info, a layer info and a map info */
		bool initWithTilesetInfo(CCTMXTilesetInfo *tilesetInfo, CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo);

		/** dealloc the map that contains the tile position from memory.
		Unless you want to know at runtime the tiles positions, you can safely call this method.
		If you are going to call layer->tileGIDAt() then, don't release the map
		*/
		void releaseMap();

		/** returns the tile (CCSprite) at a given a tile coordinate.
		The returned CCSprite will be already added to the CCTMXLayer. Don't add it again.
		The CCSprite can be treated like any other CCSprite: rotated, scaled, translated, opacity, color, etc.
		You can remove either by calling:
		- layer->removeChild(sprite, cleanup);
		- or layer->removeTileAt(ccp(x,y));
		*/
		CCSprite* tileAt(CCPoint tileCoordinate);

		/** returns the tile gid at a given tile coordinate.
		if it returns 0, it means that the tile is empty.
		This method requires the the tile map has not been previously released (eg. don't call layer->releaseMap())
		*/
		unsigned int  tileGIDAt(CCPoint tileCoordinate);

		/** sets the tile gid (gid = tile global id) at a given tile coordinate.
		The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
		If a tile is already placed at that position, then it will be removed.
		*/
		void setTileGID(unsigned int gid, CCPoint tileCoordinate);

		/** removes a tile at given tile coordinate */
		void removeTileAt(CCPoint tileCoordinate);

		/** returns the position in pixels of a given tile coordinate */
		CCPoint positionAt(CCPoint tileCoordinate);

		/** return the value for the specific property name */
		CCString *propertyNamed(const char *propertyName);

		/** Creates the tiles */
		void setupTiles();

		/** CCTMXLayer doesn't support adding a CCSprite manually.
		@warning addchild(z, tag); is not supported on CCTMXLayer. Instead of setTileGID.
		*/
		virtual void addChild(CCNode * child, int zOrder, int tag);
		// super method
		void removeChild(CCNode* child, bool cleanup);
		void draw();

		inline const char* getLayerName(){ return m_sLayerName.c_str(); }
		inline void setLayerName(const char *layerName){ m_sLayerName = layerName; }
	private:
		CCPoint positionForIsoAt(CCPoint pos);
		CCPoint positionForOrthoAt(CCPoint pos);
		CCPoint positionForHexAt(CCPoint pos);

		CCPoint calculateLayerOffset(CCPoint offset);
	
		/* optimization methos */
		CCSprite* appendTileForGID(unsigned int gid, CCPoint pos);
		CCSprite* insertTileForGID(unsigned int gid, CCPoint pos);
		CCSprite* updateTileForGID(unsigned int gid, CCPoint pos);

		/* The layer recognizes some special properties, like cc_vertez */
		void parseInternalProperties();
		int vertexZForPos(CCPoint pos);

		// index
		unsigned int atlasIndexForExistantZ(unsigned int z);
		unsigned int atlasIndexForNewZ(int z);
	protected:
		//! name of the layer
		std::string m_sLayerName;
		//! TMX Layer supports opacity
		unsigned char		m_cOpacity;

		unsigned int		m_uMinGID;
		unsigned int		m_uMaxGID;

		//! Only used when vertexZ is used
		int					m_nVertexZvalue;
		bool				m_bUseAutomaticVertexZ;
		float				m_fAlphaFuncValue;

		//! used for optimization
		CCSprite			*m_pReusedTile;
		_ccCArray			*m_pAtlasIndexArray;
        
        // used for retina display
        float               m_fContentScaleFactor;
	};

}// namespace cocos2d
#endif //__CCTMX_LAYER_H__

