/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
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
#ifndef __CCTILE_MAP_ATLAS__
#define __CCTILE_MAP_ATLAS__


#include "base_nodes/CCAtlasNode.h"

NS_CC_BEGIN

struct sImageTGA;
class CCDictionary;

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

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
    /**
     * @js ctor
     */
    CCTileMapAtlas();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CCTileMapAtlas();
    
    /** creates a CCTileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
    The tile file will be loaded using the TextureMgr.
    */
    static CCTileMapAtlas * create(const char *tile, const char *mapFile, int tileWidth, int tileHeight);
   
    /** initializes a CCTileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
    The file will be loaded using the TextureMgr.
    */
    bool initWithTileFile(const char *tile, const char *mapFile, int tileWidth, int tileHeight);
    /** returns a tile from position x,y.
     For the moment only channel R is used
     @js getTileAt
     */
    ccColor3B tileAt(const CCPoint& position);
    /** sets a tile at position x,y.
    For the moment only channel R is used
    */
    void setTile(const ccColor3B& tile, const CCPoint& position);
    /** dealloc the map from memory */
    void releaseMap();
private:
    void loadTGAfile(const char *file);
    void calculateItemsToRender();
    void updateAtlasValueAt(const CCPoint& pos, const ccColor3B& value, unsigned int index);
    void updateAtlasValues();

protected:
    //! x,y to atlas dictionary
    CCDictionary* m_pPosToAtlasIndex;
    //! numbers of tiles to render
    int m_nItemsToRender;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTILE_MAP_ATLAS__

