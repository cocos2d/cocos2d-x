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
#ifndef __CCRIBBON_H__
#define __CCRIBBON_H__
#include <gles/egl.h>
#include "CCNode.h"
#include "CCProtocols.h"
namespace cocos2d {
	class CCRibbonSegment;
	/**
	* A CCRibbon is a dynamically generated list of polygons drawn as a single or series
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
	class CCX_DLL CCRibbon : public CCNode, public CCTextureProtocol
	{
		/** Texture used by the ribbon. Conforms to CCTextureProtocol protocol */
		CCX_PROPERTY(CCTexture2D*, m_pTexture, Texture)
		/** Texture lenghts in pixels */
		CCX_PROPERTY(float, m_fTextureLength, TextureLength)
		/** GL blendind function */
		CCX_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)
		/** color used by the Ribbon (RGBA) */
		CCX_PROPERTY(ccColor4B, m_tColor, Color)
	public:
		CCRibbon(){}
		virtual ~CCRibbon();
		/** creates the ribbon */
		static CCRibbon * ribbonWithWidth(float w, const char *path, float length, ccColor4B color, float fade);
		/** init the ribbon */
		bool initWithWidth(float w, const char *path, float length, ccColor4B color, float fade);
		/** add a point to the ribbon */
		void addPointAt(CGPoint location, float width);
		/** polling function */
		void update(ccTime delta);
		/** determine side of line */
		float sideOfLine(CGPoint p, CGPoint l1, CGPoint l2);
		// super method
		virtual void draw();
	private:
		/** rotates a point around 0, 0 */
		CGPoint rotatePoint(CGPoint vec, float rotation);
	protected:
		NSMutableArray<CCRibbonSegment*> *m_pSegments;
		NSMutableArray<CCRibbonSegment*> *m_pDeletedSegments;

		CGPoint	m_tLastPoint1;
		CGPoint	m_tLastPoint2;
		CGPoint	m_tLastLocation;
		int		m_nVertCount_;
		float	m_fTexVPos;
		float	m_fCurTime;
		float	m_fFadeTime;
		float	m_fDelta;
		float	m_fLastWidth;
		float	m_fLastSign;
		bool	m_bPastFirstPoint;
	};

	/** object to hold ribbon segment data */
	class CCX_DLL CCRibbonSegment : public NSObject
	{
	public:
		GLfloat	m_pVerts[50*6];
		GLfloat	m_pCoords[50*4];
		GLubyte	m_pColors[50*8];
		float	m_pCreationTime[50];
		bool	m_bFinished;
		UINT	m_uEnd;
		UINT	m_uBegin;
	public:
		CCRibbonSegment(){}
		virtual ~CCRibbonSegment();
		char * description();
		CCRibbonSegment * init();
		void reset();
		void draw(float curTime, float fadeTime, ccColor4B color);
	};
} // namespace cocos2d
#endif //__CCRIBBON_H__