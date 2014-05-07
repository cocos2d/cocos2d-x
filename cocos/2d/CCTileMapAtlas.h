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
#ifndef __CCTILE_MAP_ATLAS__
#define __CCTILE_MAP_ATLAS__

#include "CCAtlasNode.h"
#include "base/CCValue.h"

NS_CC_BEGIN

struct sImageTGA;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief TileMapAtlas is a subclass of AtlasNode.

It knows how to render a map based of tiles.
The tiles must be in a .PNG format while the map must be a .TGA file.

For more information regarding the format, please see this post:
http://www.cocos2d-iphone.org/archives/27

All features from AtlasNode are valid in TileMapAtlas

IMPORTANT:
This class is deprecated. It is maintained for compatibility reasons only.
You SHOULD not use this class.
Instead, use the newer TMX file format: TMXTiledMap
*/
class CC_DLL TileMapAtlas : public AtlasNode 
{
public:
    /** creates a TileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
     The tile file will be loaded using the TextureMgr.
     */
    static TileMapAtlas * create(const std::string& tile, const std::string& mapFile, int tileWidth, int tileHeight);
    /**
     * @js ctor
     */
    TileMapAtlas();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TileMapAtlas();
    
    /** initializes a TileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
    The file will be loaded using the TextureMgr.
    */
    bool initWithTileFile(const std::string& tile, const std::string& mapFile, int tileWidth, int tileHeight);
    /** returns a tile from position x,y.
    For the moment only channel R is used
    */
    Color3B getTileAt(const Vector2& position) const;
    CC_DEPRECATED_ATTRIBUTE Color3B tileAt(const Vector2& position) const { return getTileAt(position); };
    /** sets a tile at position x,y.
    For the moment only channel R is used
    */
    void setTile(const Color3B& tile, const Vector2& position);
    /** dealloc the map from memory */
    void releaseMap();
    
    inline struct sImageTGA* getTGAInfo() const { return _TGAInfo; };
    inline void setTGAInfo(struct sImageTGA* TGAInfo) { _TGAInfo = TGAInfo; };

protected:
    void loadTGAfile(const std::string& file);
    void calculateItemsToRender();
    void updateAtlasValueAt(const Vector2& pos, const Color3B& value, int index);
    void updateAtlasValues();


    //! x,y to atlas dictionary
    ValueMap _posToAtlasIndex;
    //! numbers of tiles to render
    int _itemsToRender;
    /** TileMap info */
    struct sImageTGA* _TGAInfo;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTILE_MAP_ATLAS__

