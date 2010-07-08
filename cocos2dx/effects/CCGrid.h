/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "ccTypes.h"
#include "CCCamera.h"
#include "../cocoa/NSObject.h"

class CCTexture2D;
class CCGrabber;
class CCNode;

// Base class for other
class CCGridBase : public NSObject
{
public:
	CCGridBase(ccGridSize obGridSize);
	CCGridBase(ccGridSize obGridSize, CCTexture2D *pobTexture, bool bFlipped);

	void beforeDraw(void);
	void afterDraw(CCNode *pobTarget);
	void blit(void);
	void reuse(void);

public:
	static CCGridBase* gridWithSize(ccGridSize obGridSize, CCTexture2D *pobTexture, bool bFlipped);
	static CCGridBase* gridWithSize(ccGridSize obGridSize);

protected:
	bool		m_bActive;
	INT32		m_nReuseGrid;
	ccGridSize  m_obGridSize;
	CCTexture2D *m_pobTexture;
    CGPoint		m_obStep;
	CCGrabber   *p_obGrabber;
	bool        m_bIsTextureFlipped;
};

////////////////////////////////////////////////////////////

/**
 CCGrid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
 */

class CCGrid3D : public CCGridBase
{
public:
	// returns the vertex at a given position
	ccVertex3F getVertexAtPosition(ccGridSize pos);

	// returns the original (non-transformed) vertex at a given position
	ccVertex3F getOriginalVertexAtPosition(ccGridSize pos);

	// sets a new vertex at a given position
	void setVertexAtPosition(ccGridSize pos, ccVertex3F vertex);
protected:
	GLvoid		*pTexCoordinates;
    GLvoid		*pVertices;
	GLvoid		*pOriginalVertices;
	GLushort	*pIndices;
};

////////////////////////////////////////////////////////////

/**
 CCTiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 the tiles can be separated from the grid.
*/

class CCTiledGrid3D : public CCGridBase
{
public:
	// returns the tile at the given position
	ccQuad3 getTileAtPosition(ccGridSize pos);

	// returns the original tile (untransformed) at the given position
	ccQuad3 getOriginalTileAtPosition(ccGridSize pos);

	// sets a new tile
	void setTileAtPosition(ccGridSize pos, ccQuad3 coords);
protected:
	GLvoid		*pTexCoordinates;
	GLvoid		*pVertices;
	GLvoid		*pOriginalVertices;
	GLushort	*pIndices;
};

#endif // __EFFECTS_CCGRID_H__
