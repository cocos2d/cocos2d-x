/****************************************************************************
Copyright (c) 2010-2011  cocos2d-x.org
Copyright (c) 2008, 2009 Jason Booth

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
#ifndef __CCRIBBON_H__
#define __CCRIBBON_H__

/*#include <GLES/egl.h>*/
#include "CCNode.h"
#include "CCProtocols.h"
#include "CCMutableArray.h"

namespace cocos2d {

class CCRibbonSegment;
/**
* @brief A CCRibbon is a dynamically generated list of polygons drawn as a single or series
* of triangle strips. The primary use of CCRibbon is as the drawing class of Motion Streak,
* but it is quite useful on it's own. When manually drawing a ribbon, you can call addPointAt
* and pass in the parameters for the next location in the ribbon. The system will automatically
* generate new polygons, texture them accourding to your texture width, etc, etc.
*
* CCRibbon data is stored in a CCRibbonSegment class. This class statically allocates enough verticies and
* texture coordinates for 50 locations (100 verts or 48 triangles). The ribbon class will allocate
* new segments when they are needed, and reuse old ones if available. The idea is to avoid constantly
* allocating new memory and prefer a more static method. However, since there is no way to determine
* the maximum size of some ribbons (motion streaks), a truely static allocation is not possible.
*
* @since v0.8.1
*/
class CC_DLL CCRibbon : public CCNode, public CCTextureProtocol
{
	/** Texture used by the ribbon. Conforms to CCTextureProtocol protocol */
	CC_PROPERTY(CCTexture2D*, m_pTexture, Texture)
	/** Texture lengths in pixels */
	CC_PROPERTY(float, m_fTextureLength, TextureLength)
	/** GL blendind function */
	CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)
	/** color used by the Ribbon (RGBA) */
	CC_PROPERTY_PASS_BY_REF(ccColor4B, m_tColor, Color)

public:
    CCRibbon() : m_pTexture(0), m_pSegments(0), m_pDeletedSegments(0){}
	virtual ~CCRibbon();

	/** creates the ribbon */
	static CCRibbon * ribbonWithWidth(float w, const char *path, float length, const ccColor4B& color, float fade);
	/** init the ribbon */
	bool initWithWidth(float w, const char *path, float length, const ccColor4B& color, float fade);
	/** add a point to the ribbon */
	void addPointAt(CCPoint location, float width);
	/** polling function */
	void update(ccTime delta);
	/** determine side of line */
	float sideOfLine(const CCPoint& p, const CCPoint& l1, const CCPoint& l2);
	// super method
	virtual void draw();
private:
	/** rotates a point around 0, 0 */
	CCPoint rotatePoint(const CCPoint& vec, float rotation);
protected:
	CCMutableArray<CCRibbonSegment*> *m_pSegments;
	CCMutableArray<CCRibbonSegment*> *m_pDeletedSegments;

	CCPoint	m_tLastPoint1;
	CCPoint	m_tLastPoint2;
	CCPoint	m_tLastLocation;
// 	int		m_nVertCount_;
	float	m_fTexVPos;
	float	m_fCurTime;
	float	m_fFadeTime;
	float	m_fDelta;
	float	m_fLastWidth;
	float	m_fLastSign;
	bool	m_bPastFirstPoint;
};

/** @brief object to hold ribbon segment data */
class CC_DLL CCRibbonSegment : public CCObject
{
public:
	GLfloat	m_pVerts[50*6];
	GLfloat	m_pCoords[50*4];
	GLubyte	m_pColors[50*8];
	float	m_pCreationTime[50];
	bool	m_bFinished;
	unsigned int	m_uEnd;
	unsigned int	m_uBegin;
public:
	CCRibbonSegment()
		: m_bFinished(false)
        , m_uEnd(0)
		, m_uBegin(0)		
	{}
	virtual ~CCRibbonSegment();
	char * description();
	bool init();
	void reset();
	void draw(float curTime, float fadeTime, const ccColor4B& color);
};

} // namespace cocos2d

#endif //__CCRIBBON_H__