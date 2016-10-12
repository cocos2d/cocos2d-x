/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
 
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

/** Base class for Other grid.
*/
class CC_DLL GridBase : public Ref
{
public:
    /** create one Grid */
    static GridBase* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** create one Grid */
    static GridBase* create(const Size& gridSize);
    /**
    Destructor.
     * @js NA
     * @lua NA
     */
    virtual ~GridBase(void);

    /**@{
     Init the Grid base.
     @param gridSize the size of the grid.
     @param texture The texture used for grab.
     @param flipped whether or not the grab texture should be flip by Y or not.
     @param rect The effective grid rect.
    */
    bool initWithSize(const Size& gridSize);
    bool initWithSize(const Size& gridSize, const Rect& rect);
    bool initWithSize(const Size& gridSize, Texture2D *texture, bool flipped);
    bool initWithSize(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect);

    /**@}*/
    /** @{
    Getter and setter of the active state of the grid.
    */
    bool isActive() const { return _active; }
    void setActive(bool active);
    /**@}*/

    /** Get number of times that the grid will be reused. */
    int getReuseGrid() const { return _reuseGrid; }
    /** Set number of times that the grid will be reused. */
    void setReuseGrid(int reuseGrid) { _reuseGrid = reuseGrid; }

    /** Size of the grid. */
    const Size& getGridSize() const { return _gridSize; }
    /**Set the size of the grid.*/
    void setGridSize(const Size& gridSize) { _gridSize = gridSize; }

    /** Pixels between the grids. */
    const Vec2& getStep() const { return _step; }
    /**Get the pixels between the grids.*/
    void setStep(const Vec2& step) { _step = step; }

    /** is texture flipped. */
    bool isTextureFlipped() const { return _isTextureFlipped; }
    /**Set the texture flipped or not.*/
    void setTextureFlipped(bool flipped);
    
    /**@{
     Init and reset the status when render effects by using the grid.
     */
    void beforeDraw(void);
    void afterDraw(Node *target);
    /**@}*/
    
    /**@{
     Interface for custom action when before or after draw.
     @js NA
     */
    virtual void beforeBlit() {}
    virtual void afterBlit() {}
    /**@}*/
    
    /**Interface used to blit the texture with grid to screen.*/
    virtual void blit(void);
    /**Interface, Reuse the grid vertices.*/
    virtual void reuse(void);
    /**Interface, Calculate the vertices used for the blit.*/
    virtual void calculateVertexPoints(void);
    
    /**Change projection to 2D for grabbing.*/
    void set2DProjection(void);
    
    /**
     * @brief Set the effect grid rect.
     * @param rect The effect grid rect.
     */
    void setGridRect(const Rect& rect);
    /**
     * @brief Get the effect grid rect.
     * @return Return the effect grid rect.
     */
    const Rect& getGridRect() const { return _gridRect; }

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
    Rect _gridRect;
};

/**
 Grid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 */
class CC_DLL Grid3D : public GridBase
{
public:
    /** create one Grid. */
    static Grid3D* create(const Size& gridSize);
    /** create one Grid. */
    static Grid3D* create(const Size& gridSize, const Rect& rect);
    /** create one Grid. */
    static Grid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** create one Grid. */
    static Grid3D* create(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect);
    /**
     Constructor.
     * @js ctor
     */
    Grid3D();
    /**
     Destructor.
     * @js NA
     * @lua NA
     */
    ~Grid3D(void);

    /** Returns the vertex at a given position.
     * @js NA
     * @lua NA
     */
    Vec3 getVertex(const Vec2& pos) const;
    /** @deprecated Use getVertex() instead 
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 vertex(const Vec2& pos) const { return getVertex(pos); }
    /** Returns the original (non-transformed) vertex at a given position.
     * @js NA
     * @lua NA
     */
    Vec3 getOriginalVertex(const Vec2& pos) const;
    /** @deprecated Use getOriginalVertex() instead 
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Vec3 originalVertex(const Vec2& pos) const { return getOriginalVertex(pos); }

    /** Sets a new vertex at a given position.
     * @lua NA
     */
    void setVertex(const Vec2& pos, const Vec3& vertex);
    /**@{
     Implementations for interfaces in base class.
     */
    virtual void beforeBlit() override;
    virtual void afterBlit() override;
    virtual void blit() override;
    virtual void reuse() override;
    virtual void calculateVertexPoints() override;
    /**@}*/
    
    /**@{
     Getter and Setter for depth test state when blit.
     @js NA
     */
    void setNeedDepthTestForBlit( bool neededDepthTest) { _needDepthTestForBlit = neededDepthTest; }
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

/**
 TiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 the tiles can be separated from the grid.
*/
class CC_DLL TiledGrid3D : public GridBase
{
public:
    /** Create one Grid. */
    static TiledGrid3D* create(const Size& gridSize);
    /** Create one Grid. */
    static TiledGrid3D* create(const Size& gridSize, const Rect& rect);
    /** Create one Grid. */
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped);
    /** Create one Grid. */
    static TiledGrid3D* create(const Size& gridSize, Texture2D *texture, bool flipped, const Rect& rect);
    /**
     Constructor.
     * @js ctor
     */
    TiledGrid3D();
    /**
     Destructor.
     * @js NA
     * @lua NA
     */
    ~TiledGrid3D();

    /** Returns the tile at the given position.
     * @js NA
     * @lua NA
     */
    Quad3 getTile(const Vec2& pos) const;
    /** returns the tile at the given position 
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 tile(const Vec2& pos) const { return getTile(pos); }
    /** Returns the original tile (untransformed) at the given position.
     * @js NA
     * @lua NA
     */
    Quad3 getOriginalTile(const Vec2& pos) const;
    /** returns the original tile (untransformed) at the given position 
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Quad3 originalTile(const Vec2& pos) const { return getOriginalTile(pos); }

    /** Sets a new tile.
     * @lua NA
     */
    void setTile(const Vec2& pos, const Quad3& coords);

    /**@{
     Implementations for interfaces in base class.
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
