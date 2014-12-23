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
 * @addtogroup effects
 * @{
 */

/** Base class for other
*/
class CC_DLL GridBase : public Ref
{
public:
    /** create one Grid */
    static GridBase* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** create one Grid */
    static GridBase* create(const Size& gridSize);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GridBase(void);

    bool initWithSize(const Size& gridSize, Texture2D *texture, bool flipped);
    bool initWithSize(const Size& gridSize);

    /** whether or not the grid is active */
    inline bool isActive(void) const { return _active; }
    void setActive(bool active);

    /** number of times that the grid will be reused */
    inline int getReuseGrid(void) const { return _reuseGrid; }
    inline void setReuseGrid(int reuseGrid) { _reuseGrid = reuseGrid; }

    /** size of the grid */
    inline const Size& getGridSize(void) const { return _gridSize; }
    inline void setGridSize(const Size& gridSize) { _gridSize = gridSize; }

    /** pixels between the grids */
    inline const Vec2& getStep(void) const { return _step; }
    inline void setStep(const Vec2& step) { _step = step; }

    /** is texture flipped */
    inline bool isTextureFlipped(void) const { return _isTextureFlipped; }
    void setTextureFlipped(bool flipped);

    void beforeDraw(void);
    void afterDraw(Node *target);
    virtual void beforeBlit() {}
    virtual void afterBlit() {}
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
 Grid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 */
class CC_DLL Grid3D : public GridBase
{
public:
    /** create one Grid */
    static Grid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** create one Grid */
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

    /** returns the vertex at a given position 
     * @js NA
     * @lua NA
     */
    Vec3 getVertex(const Vec2& pos) const;
    /** @deprecated Use getVertex() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 vertex(const Vec2& pos) const { return getVertex(pos); }
    /** returns the original (non-transformed) vertex at a given position
     * @js NA
     * @lua NA
     */
    Vec3 getOriginalVertex(const Vec2& pos) const;
    /** @deprecated Use getOriginalVertex() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 originalVertex(const Vec2& pos) const { return getOriginalVertex(pos); }

    /** sets a new vertex at a given position 
     * @js NA
     * @lua NA
     */
    void setVertex(const Vec2& pos, const Vec3& vertex);
    
    virtual void beforeBlit() override;
    virtual void afterBlit() override;
    // Overrides
    virtual void blit() override;
    virtual void reuse() override;
    virtual void calculateVertexPoints() override;
    
    void setNeedDepthTestForBlit( bool neededDepthTest) { _needDepthTestForBlit = neededDepthTest; }
    bool getNeedDepthTestForBlit() const { return _needDepthTestForBlit; }
protected:
    GLvoid *_texCoordinates;
    GLvoid *_vertices;
    GLvoid *_originalVertices;
    GLushort *_indices;
    bool _needDepthTestForBlit;
    bool _oldDepthTestValue;
};

/**
 TiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 the tiles can be separated from the grid.
*/
class CC_DLL TiledGrid3D : public GridBase
{
public:
    /** create one Grid */
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** create one Grid */
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

    /** returns the tile at the given position 
     * @js NA
     * @lua NA
     */
    Quad3 getTile(const Vec2& pos) const;
    /** returns the tile at the given position 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Vec2& pos) const { return getTile(pos); }
    /** returns the original tile (untransformed) at the given position 
     * @js NA
     * @lua NA
     */
    Quad3 getOriginalTile(const Vec2& pos) const;
    /** returns the original tile (untransformed) at the given position 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Vec2& pos) const { return getOriginalTile(pos); }

    /** sets a new tile 
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
