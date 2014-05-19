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
#include "2d/CCNode.h"
#include "2d/CCTexture2D.h"
#ifdef EMSCRIPTEN
#include "CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

class Texture2D;
class Grabber;
class GLProgram;

/**
 * @addtogroup effects
 * @{
 */

/** 其它类的基类
*/
class CC_DLL GridBase : public Ref
{
public:
    /** 创建一个网格（grid） */
    static GridBase* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** 创建一个网格（grid） */
    static GridBase* create(const Size& gridSize);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GridBase(void);

    bool initWithSize(const Size& gridSize, Texture2D *texture, bool flipped);
    bool initWithSize(const Size& gridSize);

    /** 判断网格（grid）状态是否活动的*/
    inline bool isActive(void) const { return _active; }
    void setActive(bool active);

    /** 获取网格（grid）的重用次数 */
    inline int getReuseGrid(void) const { return _reuseGrid; }
    inline void setReuseGrid(int reuseGrid) { _reuseGrid = reuseGrid; }

    /** 获取网格（grid）的大小 */
    inline const Size& getGridSize(void) const { return _gridSize; }
    inline void setGridSize(const Size& gridSize) { _gridSize = gridSize; }

    /** 获取网格（grid）之间的像素大小 */
    inline const Vec2& getStep(void) const { return _step; }
    inline void setStep(const Vec2& step) { _step = step; }

    /** 纹理是否翻转 */
    inline bool isTextureFlipped(void) const { return _isTextureFlipped; }
    void setTextureFlipped(bool flipped);

    void beforeDraw(void);
    void afterDraw(Node *target);
    virtual void blit(void);
    virtual void reuse(void);
    virtual void calculateVertexPoints(void);

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

/** 
 Grid3D类是3D网格（3D grid）的一个实现类。每个顶点都有三个维度:x,y,z 
 */
class CC_DLL Grid3D : public GridBase
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** 创建一个网格（grid） */
    static Grid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** 创建一个网格（grid） */
    static Grid3D* create(const Size& gridSize);
    /**
     * @js ctor
     */
    Grid3D();
    /**
     * @js NA
     * @lua NA
     */
    ~Grid3D(void);

    /** 返回指定位置的顶点
     * @js NA
     * @lua NA
     */
    Vec3 getVertex(const Vec2& pos) const;
    /** @deprecated 使用方法getVertex()替代
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 vertex(const Vec2& pos) const { return getVertex(pos); }
    /** 返回指定位置的原始顶点(非转换)
     * @js NA
     * @lua NA
     */
    Vec3 getOriginalVertex(const Vec2& pos) const;
    /** @deprecated 使用方法getOriginalVertex()替代
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 originalVertex(const Vec2& pos) const { return getOriginalVertex(pos); }

   /** 在指定的位置设置一个新的顶点
     * @js NA
     * @lua NA
     */
    void setVertex(const Vec2& pos, const Vec3& vertex);

    // Overrides
    virtual void blit() override;
    virtual void reuse() override;
    virtual void calculateVertexPoints() override;

protected:
    GLvoid *_texCoordinates;
    GLvoid *_vertices;
    GLvoid *_originalVertices;
    GLushort *_indices;
};

/**
 TiledGrid3D类是3D网格（3D grid）的一个实现类，和Grid3D类相比，不同的是TiledGrid3D类的格子是可以从网格（grid）中分离出来
*/
class CC_DLL TiledGrid3D : public GridBase
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** 创建一个网格（grid） */
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** 创建一个网格（grid） */
    static TiledGrid3D* create(const Size& gridSize);
    /**
     * @js ctor
     */
    TiledGrid3D();
    /**
     * @js NA
     * @lua NA
     */
    ~TiledGrid3D();

    /** 返回指定位置的瓦片（tile）
     * @js NA
     * @lua NA
     */
    Quad3 getTile(const Vec2& pos) const;
    /** 返回指定位置的瓦片（tile）
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Vec2& pos) const { return getTile(pos); }
    /** 返回指定位置的原始瓦片（tile）（非转换)
     * @js NA
     * @lua NA
     */
    Quad3 getOriginalTile(const Vec2& pos) const;
    /** 返回指定位置的原始瓦片（tile）（非转换)
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Vec2& pos) const { return getOriginalTile(pos); }

    /** 设置一个新的瓦片（tile）
     * @js NA
     * @lua NA
     */
    void setTile(const Vec2& pos, const Quad3& coords);

    // Overrides
    virtual void blit() override;
    virtual void reuse() override;
    virtual void calculateVertexPoints() override;

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
