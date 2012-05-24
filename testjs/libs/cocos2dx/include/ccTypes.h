/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#ifndef __CCTYPES_H__
#define __CCTYPES_H__

#include "CCGeometry.h"

#include "CCGL.h"

namespace   cocos2d {

/** RGB color composed of bytes 3 bytes
@since v0.8
 */
typedef struct _ccColor3B
{
	GLubyte	r;
	GLubyte	g;
	GLubyte b;
} ccColor3B;

//! helper macro that creates an ccColor3B type
static inline ccColor3B
ccc3(const GLubyte r, const GLubyte g, const GLubyte b)
{
	ccColor3B c = {r, g, b};
	return c;
}
//ccColor3B predefined colors
//! White color (255,255,255)
static const ccColor3B ccWHITE={255,255,255};
//! Yellow color (255,255,0)
static const ccColor3B ccYELLOW={255,255,0};
//! Blue color (0,0,255)
static const ccColor3B ccBLUE={0,0,255};
//! Green Color (0,255,0)
static const ccColor3B ccGREEN={0,255,0};
//! Red Color (255,0,0,)
static const ccColor3B ccRED={255,0,0};
//! Magenta Color (255,0,255)
static const ccColor3B ccMAGENTA={255,0,255};
//! Black Color (0,0,0)
static const ccColor3B ccBLACK={0,0,0};
//! Orange Color (255,127,0)
static const ccColor3B ccORANGE={255,127,0};
//! Gray Color (166,166,166)
static const ccColor3B ccGRAY={166,166,166};

/** RGBA color composed of 4 bytes
@since v0.8
*/
typedef struct _ccColor4B
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
} ccColor4B;
//! helper macro that creates an ccColor4B type
static inline ccColor4B
ccc4f(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte o)
{
	ccColor4B c = {r, g, b, o};
	return c;
}


/** RGBA color composed of 4 floats
@since v0.8
*/
typedef struct _ccColor4F {
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
} ccColor4F;

/** Returns a ccColor4F from a ccColor3B. Alpha will be 1.
 @since v0.99.1
 */
static inline ccColor4F ccc4FFromccc3B(ccColor3B c)
{
	ccColor4F c4 = {c.r/255.f, c.g/255.f, c.b/255.f, 1.f};
	return c4;
}

/** Returns a ccColor4F from a ccColor4B.
 @since v0.99.1
 */
static inline ccColor4F ccc4FFromccc4B(ccColor4B c)
{
	ccColor4F c4 = {c.r/255.f, c.g/255.f, c.b/255.f, c.a/255.f};
	return c4;
}

/** returns YES if both ccColor4F are equal. Otherwise it returns NO.
 @since v0.99.1
 */
static inline bool ccc4FEqual(ccColor4F a, ccColor4F b)
{
	return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

/** A vertex composed of 2 floats: x, y
 @since v0.8
 */
typedef struct _ccVertex2F
{
	GLfloat x;
	GLfloat y;
} ccVertex2F;

static inline ccVertex2F vertex2(const float x, const float y)
{
	ccVertex2F c = {x, y};
	return c;
}


/** A vertex composed of 2 floats: x, y
 @since v0.8
 */
typedef struct _ccVertex3F
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} ccVertex3F;

static inline ccVertex3F vertex3(const float x, const float y, const float z)
{
	ccVertex3F c = {x, y, z};
	return c;
}
		
/** A texcoord composed of 2 floats: u, y
 @since v0.8
 */
typedef struct _ccTex2F {
	 GLfloat u;
	 GLfloat v;
} ccTex2F;

static inline ccTex2F tex2(const float u, const float v)
{
	ccTex2F t = {u , v};
	return t;
}

 
//! Point Sprite component
typedef struct _ccPointSprite
{
	ccVertex2F	pos;		// 8 bytes
	ccColor4B	color;		// 4 bytes
	GLfloat		size;		// 4 bytes
} ccPointSprite;

//!	A 2D Quad. 4 * 2 floats
typedef struct _ccQuad2 {
	ccVertex2F		tl;
	ccVertex2F		tr;
	ccVertex2F		bl;
	ccVertex2F		br;
} ccQuad2;


//!	A 3D Quad. 4 * 3 floats
typedef struct _ccQuad3 {
	ccVertex3F		bl;
	ccVertex3F		br;
	ccVertex3F		tl;
	ccVertex3F		tr;
} ccQuad3;

//! A 2D grid size
typedef struct _ccGridSize
{
	int	x;
	int	y;
} ccGridSize;

//! helper function to create a ccGridSize
static inline ccGridSize
ccg(const int x, const int y)
{
	ccGridSize v = {x, y};
	return v;
}

//! a Point with a vertex point, a tex coord point and a color 4B
typedef struct _ccV2F_C4B_T2F
{
	//! vertices (2F)
	ccVertex2F		vertices;
	//! colors (4B)
	ccColor4B		colors;
	//! tex coords (2F)
	ccTex2F			texCoords;
} ccV2F_C4B_T2F;

//! a Point with a vertex point, a tex coord point and a color 4F
typedef struct _ccV2F_C4F_T2F
{
	//! vertices (2F)
	ccVertex2F		vertices;
	//! colors (4F)
	ccColor4F		colors;
	//! tex coords (2F)
	ccTex2F			texCoords;
} ccV2F_C4F_T2F;

//! a Point with a vertex point, a tex coord point and a color 4B
typedef struct _ccV3F_C4B_T2F
{
	//! vertices (3F)
	ccVertex3F		vertices;			// 12 bytes
//	char __padding__[4];

	//! colors (4B)
	ccColor4B		colors;				// 4 bytes
//	char __padding2__[4];

	// tex coords (2F)
	ccTex2F			texCoords;			// 8 byts
} ccV3F_C4B_T2F;

//! 4 ccVertex2FTex2FColor4B Quad
typedef struct _ccV2F_C4B_T2F_Quad
{
	//! bottom left
	ccV2F_C4B_T2F	bl;
	//! bottom right
	ccV2F_C4B_T2F	br;
	//! top left
	ccV2F_C4B_T2F	tl;
	//! top right
	ccV2F_C4B_T2F	tr;
} ccV2F_C4B_T2F_Quad;

//! 4 ccVertex3FTex2FColor4B
typedef struct _ccV3F_C4B_T2F_Quad
{
	//! top left
	ccV3F_C4B_T2F	tl;
	//! bottom left
	ccV3F_C4B_T2F	bl;
	//! top right
	ccV3F_C4B_T2F	tr;
	//! bottom right
	ccV3F_C4B_T2F	br;
} ccV3F_C4B_T2F_Quad;

//! 4 ccVertex2FTex2FColor4F Quad
typedef struct _ccV2F_C4F_T2F_Quad
{
	//! bottom left
	ccV2F_C4F_T2F	bl;
	//! bottom right
	ccV2F_C4F_T2F	br;
	//! top left
	ccV2F_C4F_T2F	tl;
	//! top right
	ccV2F_C4F_T2F	tr;
} ccV2F_C4F_T2F_Quad;

//! Blend Function used for textures
typedef struct _ccBlendFunc
{
	//! source blend function
	GLenum src;
	//! destination blend function
	GLenum dst;
} ccBlendFunc;

//! ccResolutionType
typedef enum
{
    //! Unknonw resolution type
    kCCResolutionUnknown,
    //! iPhone resolution type
    kCCResolutioniPhone,
    //! RetinaDisplay resolution type
    kCCResolutioniPhoneRetinaDisplay,
    //! iPad resolution type
    kCCResolutioniPad,
    //! iPad Retina Display resolution type
    kCCResolutioniPadRetinaDisplay,
    
} ccResolutionType;

//! delta time type
//! if you want more resolution redefine it as a double
typedef float ccTime;
//typedef double ccTime;

typedef enum 
{
	CCTextAlignmentLeft,
	CCTextAlignmentCenter,
	CCTextAlignmentRight,
} CCTextAlignment;

// types for animation in particle systems

// texture coordinates for a quad
typedef struct _ccT2F_Quad
{
	//! bottom left
	ccTex2F	bl;
	//! bottom right
	ccTex2F	br;
	//! top left
	ccTex2F	tl;
	//! top right
	ccTex2F	tr;
} ccT2F_Quad;

// struct that holds the size in pixels, texture coordinates and delays for animated CCParticleSystemQuad
typedef struct
{
	ccT2F_Quad texCoords;
	ccTime delay;
	CCSize size; 
} ccAnimationFrameData;

}//namespace   cocos2d 

#endif //__CCTYPES_H__
