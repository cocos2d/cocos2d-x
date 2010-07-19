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

#ifndef __CCMACROS_H__
#define __CCMACROS_H__

#define _USE_MATH_DEFINES
#include <math.h>

/**
 @file
 cocos2d helper macros
 */
 /*
 * if COCOS2D_DEBUG is not defined, or if it is 0 then
 *	all CCLOGXXX macros will be disabled
 *
 * if COCOS2D_DEBUG==1 then:
 *		CCLOG() will be enabled
 *		CCLOGERROR() will be enabled
 *		CCLOGINFO()	will be disabled
 *
 * if COCOS2D_DEBUG==2 or higher then:
 *		CCLOG() will be enabled
 *		CCLOGERROR() will be enabled
 *		CCLOGINFO()	will be enabled 
 */

#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
#define CCLOG(...) do {} while (0)
#define CCLOGINFO(...) do {} while (0)
#define CCLOGERROR(...) do {} while (0)

#elif COCOS2D_DEBUG == 1
#define CCLOG(...) printf(__VA_ARGS__)
#define CCLOGERROR(...) printf(__VA_ARGS__)
#define CCLOGINFO(...) do {} while (0)

#elif COCOS2D_DEBUG > 1
#define CCLOG(...) printf(__VA_ARGS__)
#define CCLOGERROR(...) printf(__VA_ARGS__)
#define CCLOGINFO(...) printf(__VA_ARGS__)
#endif // COCOS2D_DEBUG

/** @def CC_SWAP
simple macro that swaps 2 variables
*/
//#define CC_SWAP(x, y)			\
//{ typename(x) temp  = (x);		\
//		x = y; y = temp;		\
//}


/** @def CCRANDOM_MINUS1_1
 returns a random float between -1 and 1
 */
#define CCRANDOM_MINUS1_1() ((random() / (float)0x3fffffff )-1.0f)

/** @def CCRANDOM_0_1
 returns a random float between 0 and 1
 */
#define CCRANDOM_0_1() ((random() / (float)0x7fffffff ))

/** @def CC_DEGREES_TO_RADIANS
 converts degrees to radians
 */
#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) / 180.0f * (float)M_PI)

/** @def CC_RADIANS_TO_DEGREES
 converts radians to degrees
 */
#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) / (float)M_PI * 180.0f)

/** @def CC_BLEND_SRC
default gl blend src function. Compatible with premultiplied alpha images.
*/
#define CC_BLEND_SRC GL_ONE

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

/** @def CC_DIRECTOR_INIT
	- Initializes an EAGLView with 0-bit depth format, and RGB565 render buffer.
	- The EAGLView view will have multiple touches disabled.
	- It will create a UIWindow and it will assign it the 'window' variable. 'window' must be declared before calling this marcro.
	- It will parent the EAGLView to the created window
	- If the firmware >= 3.1 it will create a Display Link Director. Else it will create an NSTimer director.
	- It will try to run at 60 FPS.
	- The FPS won't be displayed.
	- The orientation will be portrait.
	- It will connect the director with the EAGLView.

 IMPORTANT: If you want to use another type of render buffer (eg: RGBA8)
 or if you want to use a 16-bit or 24-bit depth buffer, you should NOT
 use this macro. Instead, you should create the EAGLView manually.
 
 @since v0.99.4
 */

//---- todo: replace with uphone window

/*
#define CC_DIRECTOR_INIT()																		\
do	{																							\
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];					\
	if( ! [CCDirector setDirectorType:kCCDirectorTypeDisplayLink] )								\
		[CCDirector setDirectorType:kCCDirectorTypeNSTimer];									\
	CCDirector *__director = [CCDirector sharedDirector];										\
	[__director setDeviceOrientation:kCCDeviceOrientationPortrait];								\
	[__director setDisplayFPS:NO];																\
	[__director setAnimationInterval:1.0/60];													\
	EAGLView *__glView = [EAGLView viewWithFrame:[window bounds]								\
									pixelFormat:kEAGLColorFormatRGB565							\
									depthFormat:0 /* GL_DEPTH_COMPONENT24_OES   				\
							 preserveBackbuffer:NO];											\
	[__director setOpenGLView:__glView];														\
	[window addSubview:__glView];																\
	[window makeKeyAndVisible];																	\
} while(0)
*/
 
 /** @def CC_DIRECTOR_END
  Stops and removes the director from memory.
  Removes the EAGLView from its parent
  
  @since v0.99.4
  */

//---- todo: replace with uphone window

 /*
#define CC_DIRECTOR_END()										\
do {															\
	CCDirector *__director = [CCDirector sharedDirector];		\
	EAGLView *__view = [__director openGLView];					\
	[__view removeFromSuperview];								\
	[__director end];											\
} while(0)
*/

#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	        TypeName(const TypeName&);\
			void operator=(const TypeName&)


#endif // __CCMACROS_H__
