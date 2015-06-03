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

#include "2d/CCAtlasNode.h"
#include "base/CCValue.h"

NS_CC_BEGIN

/// @cond DO_NOT_SHOW

struct sImageTGA;

/** @brief @~english TileMapAtlas is a subclass of AtlasNode.
 * 
 * It knows how to render a map based of tiles.
 * The tiles must be in a .PNG format while the map must be a .TGA file.
 * 
 * For more information regarding the format, please see this post:
 * http://www.cocos2d-iphone.org/archives/27
 * 
 * All features from AtlasNode are valid in TileMapAtlas
 * 
 * IMPORTANT:
 * This class is deprecated. It is maintained for compatibility reasons only.
 * You SHOULD not use this class.
 * Instead, use the newer TMX file format: TMXTiledMap
 *
 * @~chinese TileMapAtlas 是 AtlasNode的一个子类。
 * 
 * 用于绘制 TileMap。
 * TileMap 所使用的图片资源必须在同一个 .png 格式的文件中，而且 TileMap 的配置文件必须为 .tga 格式。
 * 
 * 关于格式的更多信息，请参阅这篇文章:
 * http://www.cocos2d-iphone.org/archives/27
 * 
 * AtlasNode 的所有功能在 TileMapAtlas 里面都是可用的。
 * 
 * **注意**:
 * 这个类是弃用的。只是为保持兼容性才保留了这个类。
 * 不推荐继续使用这个类。请使用更新的 TMX 文件格式：TMXTiledMap
 * @js NA
 */
class CC_DLL TileMapAtlas : public AtlasNode 
{
public:
    /** @~english creates a TileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
     * The tile file will be loaded using the TextureMgr.
     * @~chinese 使用指定的图片文件，tga 配置文件，格子宽度和格子高度创建一个 TileMapAtlas 实例。
     * 图片文件将被 TextureMgr 加载。
     * @param tile @~english The texture file for the TileMap.
     * @~chinese TileMap 使用的图片文件路径。
     * @param mapFile @~english The .tga file of the TileMap.
     * @~chinese TileMap tga 格式配置文件的路径。
     * @param tileWidth @~english The width of a tile.
     * @~chinese TileMap 一个格子的宽度。
     * @param tileHeight @~english The height of a tile.
     * @~chinese TileMap 一个格子的高度。
     * @return @~english A TileMapAtlas object.
     * @~chinese 返回 TileMapAtlas 的实例。
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
    
    /** @~english creates a TileMap with a tile file (atlas) with a map file and the width and height of each tile in points.
     * The tile file will be loaded using the TextureMgr.
     * @~chinese 使用指定的图片文件，tga 配置文件，格子宽度和格子高度初始化一个 TileMapAtlas 实例。
     * 图片文件将被 TextureMgr 加载。
     * @param tile @~english The texture file for the TileMap.
     * @~chinese TileMap 使用的图片文件路径。
     * @param mapFile @~english The .tga file of the TileMap.
     * @~chinese TileMap tga 格式配置文件的路径。
     * @param tileWidth @~english The width of a tile.
     * @~chinese TileMap 一个格子的宽度。
     * @param tileHeight @~english The height of a tile.
     * @~chinese TileMap 一个格子的高度。
     * @return @~english If the initialization success, return true; else return false.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    bool initWithTileFile(const std::string& tile, const std::string& mapFile, int tileWidth, int tileHeight);
    /**@~english
     * Returns a tile from position x,y.
     * For the moment only channel R is used
     * @~chinese 
     * 返回 x,y 位置的格子。
     * 目前只使用 R 通道
     */
    Color3B getTileAt(const Vec2& position) const;
    /**@~english
     * Returns a tile from position x,y.
     * For the moment only channel R is used
     * @~chinese 
     * 返回 x,y 位置的格子。
     * 目前只使用 R 通道
     */
    CC_DEPRECATED_ATTRIBUTE Color3B tileAt(const Vec2& position) const { return getTileAt(position); };
    /** @~english sets a tile at position x,y.
    For the moment only channel R is used
     * @~chinese 设置 x,y 位置的格子。
     * 目前只使用 R 通道
    */
    void setTile(const Color3B& tile, const Vec2& position);
    /** @~english dealloc the map from memory  @~chinese 释放地图的内存。*/
    void releaseMap();
    
    /**@~english
     * Query TGA image info.
     * @~chinese 
     * 获取 tga 的图像信息。
     *@return @~english The TGA image info.
     * @~chinese tga 的图像信息。
     */
    inline struct sImageTGA* getTGAInfo() const { return _TGAInfo; };

    /**@~english
     * Set the TGA image info for TileMapAtlas
     * @~chinese 
     * 设置 TileMapAtlas 的 tga 图像信息
     *@param TGAInfo @~english The TGA info in sImageTGA.
     * @~chinese tga 图像信息。
     */
    inline void setTGAInfo(struct sImageTGA* TGAInfo) { _TGAInfo = TGAInfo; };

protected:
    void loadTGAfile(const std::string& file);
    void calculateItemsToRender();
    void updateAtlasValueAt(const Vec2& pos, const Color3B& value, int index);
    void updateAtlasValues();


    //! x,y to atlas dictionary
    ValueMap _posToAtlasIndex;
    //! numbers of tiles to render
    int _itemsToRender;
    /** @~english TileMap info  @~chinese TileMap信息*/
    struct sImageTGA* _TGAInfo;
};

/// @endcond

NS_CC_END

#endif //__CCTILE_MAP_ATLAS__

