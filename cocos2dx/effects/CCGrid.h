/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      On-Core
 
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

#include "cocoa/CCObject.h"
#include "base_nodes/CCNode.h"
#include "CCCamera.h"
#include "ccTypes.h"
#include "textures/CCTexture2D.h"
#include "CCDirector.h"
#include "kazmath/mat4.h"
#ifdef EMSCRIPTEN
#include "base_nodes/CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

class CCTexture2D;
class CCGrabber;
class CCGLProgram;

/**
 * @addtogroup effects
 * @{
 */

/** Base class for other
*/
class CC_DLL CCGridBase : public CCObject
{
public:
    virtual ~CCGridBase(void);

    /** whether or not the grid is active */
    inline bool isActive(void) { return _active; }
    void setActive(bool bActive);

    /** number of times that the grid will be reused */
    inline int getReuseGrid(void) { return _reuseGrid; }
    inline void setReuseGrid(int nReuseGrid) { _reuseGrid = nReuseGrid; }

    /** size of the grid */
    inline const CCSize& getGridSize(void) { return _gridSize; }
    inline void setGridSize(const CCSize& gridSize) { _gridSize = gridSize; }

    /** pixels between the grids */
    inline const CCPoint& getStep(void) { return _step; }
    inline void setStep(const CCPoint& step) { _step = step; }

    /** is texture flipped */
    inline bool isTextureFlipped(void) { return _isTextureFlipped; }
    void setTextureFlipped(bool bFlipped);

    bool initWithSize(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
    bool initWithSize(const CCSize& gridSize);

    void beforeDraw(void);
    void afterDraw(CCNode *pTarget);
    virtual void blit(void);
    virtual void reuse(void);
    virtual void calculateVertexPoints(void);

public:

    /** create one Grid */
    static CCGridBase* create(const CCSize& gridSize, CCTexture2D *texture, bool flipped);
    /** create one Grid */
    static CCGridBase* create(const CCSize& gridSize);

    void set2DProjection(void);

protected:
    bool _active;
    int  _reuseGrid;
    CCSize _gridSize;
    CCTexture2D *_texture;
    CCPoint _step;
    CCGrabber *_grabber;
    bool _isTextureFlipped;
    CCGLProgram* _shaderProgram;
    ccDirectorProjection _directorProjection;
};

/**
 CCGrid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 */
class CC_DLL CCGrid3D : public CCGridBase
#ifdef EMSCRIPTEN
, public CCGLBufferedNode
#endif // EMSCRIPTEN
{
public:
    CCGrid3D();
    ~CCGrid3D(void);

    /** returns the vertex at a given position */
    ccVertex3F vertex(const CCPoint& pos);
    /** returns the original (non-transformed) vertex at a given position */
    ccVertex3F originalVertex(const CCPoint& pos);
    /** sets a new vertex at a given position */
    void setVertex(const CCPoint& pos, const ccVertex3F& vertex);

    virtual void blit(void);
    virtual void reuse(void);
    virtual void calculateVertexPoints(void);

public:
    /** create one Grid */
    static CCGrid3D* create(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
    /** create one Grid */
    static CCGrid3D* create(const CCSize& gridSize);
    
protected:
    GLvoid *_texCoordinates;
    GLvoid *_vertices;
    GLvoid *_originalVertices;
    GLushort *_indices;
};

/**
 CCTiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 the tiles can be separated from the grid.
*/
class CC_DLL CCTiledGrid3D : public CCGridBase
#ifdef EMSCRIPTEN
, public CCGLBufferedNode
#endif // EMSCRIPTEN
{
public:
    CCTiledGrid3D();
    ~CCTiledGrid3D(void);

    /** returns the tile at the given position */
    ccQuad3 tile(const CCPoint& pos);
    /** returns the original tile (untransformed) at the given position */
    ccQuad3 originalTile(const CCPoint& pos);
    /** sets a new tile */
    void setTile(const CCPoint& pos, const ccQuad3& coords);

    virtual void blit(void);
    virtual void reuse(void);
    virtual void calculateVertexPoints(void);

public:

    /** create one Grid */
    static CCTiledGrid3D* create(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
    /** create one Grid */
    static CCTiledGrid3D* create(const CCSize& gridSize);
    
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
