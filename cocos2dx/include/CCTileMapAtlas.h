/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#ifndef __CCTILE_MAP_ATLAS__
#define __CCTILE_MAP_ATLAS__
#include <string>
#include <map>
#include "CCAtlasNode.h"
namespace cocos2d {

	typedef std::map<std::string, int> StringToIntegerDictionary;
	typedef std::pair<std::string, int> StringToIntegerPair;
	struct sImageTGA;
	/** @brief CCTileMapAtlas is a subclass of CCAtlasNode.

	It knows how to render a map based of tiles.
	The tiles must be in a .PNG format while the map must be a .TGA file.

	For more information regarding the format, please see this post:
	http://www.cocos2d-iphone.org/archives/27

	All features from CCAtlasNode are valid in CCTileMapAtlas

	IMPORTANT:
	This class is deprecated. It is maintained for compatibility reasons only.
	You SHOULD not use this class.
	Instead, use the newer TMX file format: CCTMXTiledMap
	*/
	class CC_DLL CCTileMapAtlas : public CCAtlasNode 
	{
		/** TileMap info */
		CC_PROPERTY(struct sImageTGA*, m_pTGAInfo, TGAInfo);
	public:
		CCTileMapAtlas();
		virtual ~CCTileMapAtlas();
		/** creates a CCTileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
		The tile file will be loaded using the TextureMgr.
		*/
		static CCTileMapAtlas * tileMapAtlasWithTileFile(const char *tile, const char *mapFile, int tileWidth, int tileHeight);
		/** initializes a CCTileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
		The file will be loaded using the TextureMgr.
		*/
		bool initWithTileFile(const char *tile, const char *mapFile, int tileWidth, int tileHeight);
		/** returns a tile from position x,y.
		For the moment only channel R is used
		*/
		ccColor3B tileAt(ccGridSize position);
		/** sets a tile at position x,y.
		For the moment only channel R is used
		*/
		void setTile(ccColor3B tile, ccGridSize position);
		/** dealloc the map from memory */
		void releaseMap();
	private:
		void loadTGAfile(const char *file);
		void calculateItemsToRender();
		void updateAtlasValueAt(ccGridSize pos, ccColor3B value, int index);
		void updateAtlasValues();

	protected:
		//! x,y to altas dicctionary
		StringToIntegerDictionary *m_pPosToAtlasIndex;
		//! numbers of tiles to render
		int				m_nItemsToRender;
	};

}// namespace cocos2d
#endif //__CCTILE_MAP_ATLAS__

