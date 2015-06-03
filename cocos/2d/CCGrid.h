/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (C) 2013-2014 Chukong Technologies Inc.
 
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
#ifndef __EFFECTS_CCGRID_H__
#define __EFFECTS_CCGRID_H__

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

class Texture2D;
class Grabber;
class GLProgram;
class Node;

/**
 * @addtogroup _2d
 * @{
 */

/** @~english Base class for Other grid.
 * @~chinese 其他网格类的基类。
*/
class CC_DLL GridBase : public Ref
{
public:
    /** @~english create one Grid  @~chinese 创建一个网格*/
    static GridBase* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** @~english create one Grid  @~chinese 创建一个网格*/
    static GridBase* create(const Size& gridSize);
    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     * @js NA
     * @lua NA
     */
    virtual ~GridBase(void);

    /**@{@~english
     *Init the Grid base.
     * @~chinese 
     * 初始化网格基类。
     @param gridSize @~english the size of the grid.
     * @~chinese 网格的大小。
     @param texture @~english The texture used for grab.
     * @~chinese 待抓取的纹理。
     @param flipped @~english whether or not the grab texture should be flip by Y or not.
     * @~chinese 是否应该在Y轴方向翻转待抓取的纹理。
     * @return @~english True if initailize success, false otherwise. @~chinese 如果初始化成功，则返回真，否则返回假。
     */
    bool initWithSize(const Size& gridSize, Texture2D *texture, bool flipped);

    /**
     * @~english Init the Grid base.
     * @~chinese 初始化网格基类
     *
     * @param gridSize @~english the size of grid. @~chinese 网格的大小
     *
     * @return @~english True if initailize success, false otherwise. @~chinese 如果初始化成功，则返回真，否则返回假。
     */
    bool initWithSize(const Size& gridSize);
    /**@}*/
    /** @{@~english
     * Get the active state of grid.
     * @~chinese 
     * 获取网格的活动状态。
    */
    inline bool isActive(void) const { return _active; }
    /**
     * @~english Set the active state of grid.
     * @~chinese 设置网格的活动状态
     *
     * @param active @~english true if the grid is active, false otherwise @~chinese 如果网格处于活动状态，则返回真，否则返回假。
     */
    void setActive(bool active);
    /**@}*/

    /** @~english Get number of times that the grid will be reused.  @~chinese 获取网格将被重用的次数。*/
    inline int getReuseGrid(void) const { return _reuseGrid; }
    /** @~english Set number of times that the grid will be reused.  @~chinese 设置网格将被重用的次数。*/
    inline void setReuseGrid(int reuseGrid) { _reuseGrid = reuseGrid; }

    /** @~english Get the size of the grid.  @~chinese 获取网格的大小。*/
    inline const Size& getGridSize(void) const { return _gridSize; }
    /**@~english Set the size of the grid. @~chinese 设置网格的大小*/
    inline void setGridSize(const Size& gridSize) { _gridSize = gridSize; }

    /** @~english Pixels between the grids.  @~chinese 获取网格之间的像素。*/
    inline const Vec2& getStep(void) const { return _step; }
    /**@~english Get the pixels between the grids. @~chinese 设置网格之间的像素。*/
    inline void setStep(const Vec2& step) { _step = step; }

    /** @~english is texture flipped.  @~chinese 纹理是否翻转。*/
    inline bool isTextureFlipped(void) const { return _isTextureFlipped; }
    /**@~english Set the texture flipped or not. @~chinese 设置纹理是否翻转。*/
    void setTextureFlipped(bool flipped);
    
    /**@{@~english
     * Init and reset the status when render effects by using the grid.
     * @~chinese 
     * 在绘制前后，用来初始化和重置渲染网格的状态。
     */
    void beforeDraw(void);
    void afterDraw(Node *target);
    /**@}*/
    
    /**@{@~english
     * Interface for custom action when before or after draw.
     * @~chinese 
     * 在绘制前后，用来定制动作。
     @js NA
     */
    virtual void beforeBlit() {}
    virtual void afterBlit() {}
    /**@}*/
    
    /**@~english Used to blit the texture with grid to screen. @~chinese 用于拷贝网格纹理贴图到屏幕。*/
    virtual void blit(void);
    /**@~english Reuse the grid vertices. @~chinese 重用网格顶点。*/
    virtual void reuse(void);
    /**@~english Calculate the vertices used for the blit. @~chinese 计算用于位块传输的顶点。*/
    virtual void calculateVertexPoints(void);
    
    /**@~english Change projection to 2D for grabbing. @~chinese 改变投影为抓住2 d。*/
    void set2DProjection(void);

protected:
    bool _active;
    int  _reuseGrid;
    Size _gridSize;
    Texture2D *_texture;
    Vec2 _step;
    Grabber *_grabber;
    bool _isTextureFlipped;
    GLProgram* _shaderProgram;
    Director::Projection _directorProjection;
};

/**@~english
 * Grid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 * @~chinese 
 * Grid3D是一个3D网格实现。每个顶点都有三个维度:x,y,z
 */
class CC_DLL Grid3D : public GridBase
{
public:
    /** @~english create one Grid.  @~chinese 创建一个网格。*/
    static Grid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** @~english create one Grid.  @~chinese 创建一个网格。*/
    static Grid3D* create(const Size& gridSize);
    /**@~english
     * Constructor.
     * @~chinese 
     * 构造函数。
     * @js ctor
     */
    Grid3D();
    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     * @js NA
     * @lua NA
     */
    ~Grid3D(void);

    /** @~english Returns the vertex at a given position.
     * @~chinese 返回一个给定的位置的顶点。
     * @js NA
     * @lua NA
     */
    Vec3 getVertex(const Vec2& pos) const;
    /** @deprecated Use getVertex() instead 
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 vertex(const Vec2& pos) const { return getVertex(pos); }
    /** @~english Returns the original (non-transformed) vertex at a given position.
     * @~chinese 返回一个给定的位置的原始的(没有经过坐标变换的)顶点。
     * @js NA
     * @lua NA
     */
    Vec3 getOriginalVertex(const Vec2& pos) const;
    /** @deprecated Use getOriginalVertex() instead 
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 originalVertex(const Vec2& pos) const { return getOriginalVertex(pos); }

    /** @~english Sets a new vertex at a given position.
     * @~chinese 在一个给定的位置上设置一个新的顶点。
     * @lua NA
     */
    void setVertex(const Vec2& pos, const Vec3& vertex);
    /**@{@~english
     * Implementations for interfaces in base calss.
     * @~chinese 
     * 实现Grid基类的一些接口
     */
    virtual void beforeBlit() override;
    virtual void afterBlit() override;
    virtual void blit() override;
    virtual void reuse() override;
    virtual void calculateVertexPoints() override;
    /**@}*/
    
    /**@{@~english
     * Set the depth test state when blit.
     * @~chinese 
     * 设置位块传送时的深度测试状态。
     @js NA
     */
    void setNeedDepthTestForBlit( bool neededDepthTest) { _needDepthTestForBlit = neededDepthTest; }
    /**
     * @~english Get the depth test state when blit.
     * @~chinese 获取位块传送时的深度测试状态
     *
     * @return @~english Return true if depth test is enabled, false otherwise. @~chinese 如果深度测试是开启的，则返回真，否则返回假。
     */
    bool getNeedDepthTestForBlit() const { return _needDepthTestForBlit; }
    /**@}*/
protected:
    GLvoid *_texCoordinates;
    GLvoid *_vertices;
    GLvoid *_originalVertices;
    GLushort *_indices;
    bool _needDepthTestForBlit;
    bool _oldDepthTestValue;
    bool _oldDepthWriteValue;
};

/**@~english
 * TiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 * the tiles can be separated from the grid.
 * @~chinese 
 * TiledGrid3D是一个3D网格实现。它不同于Grid3D,
 * 每一个瓦片(tile)可以独立于网格。
*/
class CC_DLL TiledGrid3D : public GridBase
{
public:
    /** @~english Create one Grid.  @~chinese 创建一个网格。*/
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** @~english Create one Grid.  @~chinese 创建一个网格。*/
    static TiledGrid3D* create(const Size& gridSize);
    /**@~english
     * Constructor.
     * @~chinese 
     * 构造函数。
     * @js ctor
     */
    TiledGrid3D();
    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     * @js NA
     * @lua NA
     */
    ~TiledGrid3D();

    /** @~english Returns the tile at the given position.
     * @~chinese 返回给定位置的瓦片。
     * @js NA
     * @lua NA
     */
    Quad3 getTile(const Vec2& pos) const;
    /** @~english returns the tile at the given position 
     * @~chinese 返回给定位置的瓦片.
     * @deprecated Use getTile instead.
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Vec2& pos) const { return getTile(pos); }
    /** @~english Returns the original tile (untransformed) at the given position.
     * @~chinese 返回给定位置的没有经过坐标变换的瓦片。
     * @js NA
     * @lua NA
     */
    Quad3 getOriginalTile(const Vec2& pos) const;
    /** @~english returns the original tile (untransformed) at the given position 
     * @~chinese 返回给定位置的没有经过坐标变换的瓦片。
     * @deprecated use getOriginalTile instead.
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Vec2& pos) const { return getOriginalTile(pos); }

    /** @~english Sets a new tile.
     * @~chinese 设置一个新的瓦片。
     * @lua NA
     */
    void setTile(const Vec2& pos, const Quad3& coords);

    /**@{@~english
     * Implementations for interfaces in base calss.
     * @~chinese 
     * 实现Grid基类的一些接口。
     */
    virtual void blit() override;
    virtual void reuse() override;
    virtual void calculateVertexPoints() override;
    /**@}*/
protected:
    GLvoid *_texCoordinates;
    GLvoid *_vertices;
    GLvoid *_originalVertices;
    GLushort *_indices;
};

// end of effects group
/// @}

NS_CC_END

#endif // __EFFECTS_CCGRID_H__
