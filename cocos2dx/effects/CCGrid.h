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
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCGridBase(void);

    /** whether or not the grid is active 
     *  @lua NA
     */
    inline bool isActive(void) { return m_bActive; }
    /**
     *  @lua NA
     */
    void setActive(bool bActive);

    /** number of times that the grid will be reused 
     *  @lua NA
     */
    inline int getReuseGrid(void) { return m_nReuseGrid; }
    /**
     *  @lua NA
     */
    inline void setReuseGrid(int nReuseGrid) { m_nReuseGrid = nReuseGrid; }

    /** size of the grid 
     *  @lua NA
     */
    inline const CCSize& getGridSize(void) { return m_sGridSize; }
    /**
     *  @lua NA
     */
    inline void setGridSize(const CCSize& gridSize) { m_sGridSize = gridSize; }

    /** pixels between the grids 
     *  @lua NA
     */
    inline const CCPoint& getStep(void) { return m_obStep; }
    /**
     *  @lua NA
     */
    inline void setStep(const CCPoint& step) { m_obStep = step; }

    /** is texture flipped 
     * @lua NA
     */
    inline bool isTextureFlipped(void) { return m_bIsTextureFlipped; }
    /**
     *  @lua NA
     */
    void setTextureFlipped(bool bFlipped);
    /**
     *  @lua NA
     */
    bool initWithSize(const CCSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
    /**
     *  @lua NA
     */
    bool initWithSize(const CCSize& gridSize);
    /**
     *  @lua NA
     */
    void beforeDraw(void);
    /**
     *  @lua NA
     */
    void afterDraw(CCNode *pTarget);
    /**
     *  @lua NA
     */
    virtual void blit(void);
    /**
     *  @lua NA
     */
    virtual void reuse(void);
    /**
     *  @lua NA
     */
    virtual void calculateVertexPoints(void);

public:

    /** create one Grid 
     * @lua NA
     */
    static CCGridBase* create(const CCSize& gridSize, CCTexture2D *texture, bool flipped);
    /** create one Grid 
     * @lua NA
     */
    static CCGridBase* create(const CCSize& gridSize);
    /**
     *  @lua NA
     */
    void set2DProjection(void);

protected:
    bool m_bActive;
    int  m_nReuseGrid;
    CCSize m_sGridSize;
    CCTexture2D *m_pTexture;
    CCPoint m_obStep;
    CCGrabber *m_pGrabber;
    bool m_bIsTextureFlipped;
    CCGLProgram* m_pShaderProgram;
    ccDirectorProjection m_directorProjection;
};

/**
 CCGrid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 @js NA
 @lua NA
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
    GLvoid *m_pTexCoordinates;
    GLvoid *m_pVertices;
    GLvoid *m_pOriginalVertices;
    GLushort *m_pIndices;
};

/**
 CCTiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 the tiles can be separated from the grid.
 @js NA
 @lua NA
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
    GLvoid *m_pTexCoordinates;
    GLvoid *m_pVertices;
    GLvoid *m_pOriginalVertices;
    GLushort *m_pIndices;
};

// end of effects group
/// @}

NS_CC_END

#endif // __EFFECTS_CCGRID_H__
