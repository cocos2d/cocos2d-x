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

#ifndef __CCMACROS_H__
#define __CCMACROS_H__

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "CCCommon.h"
#include "CCStdC.h"

#ifndef CCAssert
#define CCAssert(cond, msg)         CC_ASSERT(cond)
#endif  // CCAssert

#include "ccConfig.h"

/** @def CC_SWAP
simple macro that swaps 2 variables
*/
#define CC_SWAP(x, y, type)	\
{	type temp = (x);		\
	x = y; y = temp;		\
}


/** @def CCRANDOM_MINUS1_1
 returns a random float between -1 and 1
 */
#define CCRANDOM_MINUS1_1() ((2.0f*((float)rand()/RAND_MAX))-1.0f)

/** @def CCRANDOM_0_1
 returns a random float between 0 and 1
 */
#define CCRANDOM_0_1() ((float)rand()/RAND_MAX)

/** @def CC_DEGREES_TO_RADIANS
 converts degrees to radians
 */
#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

/** @def CC_RADIANS_TO_DEGREES
 converts radians to degrees
 */
#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

/** @def CC_BLEND_SRC
default gl blend src function. Compatible with premultiplied alpha images.
*/
#if CC_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA
    #define CC_BLEND_SRC GL_ONE
    #define CC_BLEND_DST GL_ONE_MINUS_SRC_ALPHA
#else
    #define CC_BLEND_SRC GL_SRC_ALPHA
    #define CC_BLEND_DST GL_ONE_MINUS_SRC_ALPHA
#endif // ! CC_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA

/** @def CC_BLEND_DST
 default gl blend dst function. Compatible with premultiplied alpha images.
 */
#define CC_BLEND_DST GL_ONE_MINUS_SRC_ALPHA

/** @def CC_ENABLE_DEFAULT_GL_STATES
 GL states that are enabled:
	- GL_TEXTURE_2D
	- GL_VERTEX_ARRAY
	- GL_TEXTURE_COORD_ARRAY
	- GL_COLOR_ARRAY
 */
#define CC_ENABLE_DEFAULT_GL_STATES() {				\
	glEnableClientState(GL_VERTEX_ARRAY);			\
	glEnableClientState(GL_COLOR_ARRAY);			\
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	\
	glEnable(GL_TEXTURE_2D);						\
}

/** @def CC_DISABLE_DEFAULT_GL_STATES 
 Disable default GL states:
	- GL_TEXTURE_2D
	- GL_VERTEX_ARRAY
	- GL_TEXTURE_COORD_ARRAY
	- GL_COLOR_ARRAY
 */
#define CC_DISABLE_DEFAULT_GL_STATES() {			\
	glDisable(GL_TEXTURE_2D);						\
	glDisableClientState(GL_COLOR_ARRAY);			\
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	\
	glDisableClientState(GL_VERTEX_ARRAY);			\
}

#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	        TypeName(const TypeName&);\
			void operator=(const TypeName&)

/****************************/
/** RETINA DISPLAY ENABLED **/
/****************************/

/** @def CC_CONTENT_SCALE_FACTOR
On Mac it returns 1;
On iPhone it returns 2 if RetinaDisplay is On. Otherwise it returns 1
*/
#define CC_CONTENT_SCALE_FACTOR() CCDirector::sharedDirector()->getContentScaleFactor()


/** @def CC_RECT_PIXELS_TO_POINTS
Converts a rect in pixels to points
*/
#define CC_RECT_PIXELS_TO_POINTS(__pixels__)																		\
    CCRectMake( (__pixels__).origin.x / CC_CONTENT_SCALE_FACTOR(), (__pixels__).origin.y / CC_CONTENT_SCALE_FACTOR(),	\
    (__pixels__).size.width / CC_CONTENT_SCALE_FACTOR(), (__pixels__).size.height / CC_CONTENT_SCALE_FACTOR() )

/** @def CC_RECT_POINTS_TO_PIXELS
Converts a rect in points to pixels
*/
#define CC_RECT_POINTS_TO_PIXELS(__points__)																		\
    CCRectMake( (__points__).origin.x * CC_CONTENT_SCALE_FACTOR(), (__points__).origin.y * CC_CONTENT_SCALE_FACTOR(),	\
    (__points__).size.width * CC_CONTENT_SCALE_FACTOR(), (__points__).size.height * CC_CONTENT_SCALE_FACTOR() )

/**
Helper marcos which converts 4-byte little/big endian 
integral number to the machine native number representation
 
It should work same as apples CFSwapInt32LittleToHost(..)
*/

/// when define returns true it means that our architecture uses big endian
#define CC_HOST_IS_BIG_ENDIAN (bool)(*(unsigned short *)"\0\xff" < 0x100) 
#define CC_SWAP32(i)  ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define CC_SWAP16(i)  ((i & 0x00ff) << 8 | (i &0xff00) >> 8)   
#define CC_SWAP_INT32_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true)? CC_SWAP32(i) : (i) )
#define CC_SWAP_INT16_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true)? CC_SWAP16(i) : (i) )
#define CC_SWAP_INT32_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true)? (i) : CC_SWAP32(i) )
#define CC_SWAP_INT16_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true)? (i):  CC_SWAP16(i) )

#endif // __CCMACROS_H__