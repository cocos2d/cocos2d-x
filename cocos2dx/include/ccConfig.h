/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCCONFIG_H__
#define __CCCONFIG_H__

#include "platform/CCPlatformConfig.h"

/**
 @file
 cocos2d (cc) configuration file
*/

/** @def CC_ENABLE_GL_STATE_CACHE
 If enabled, cocos2d will maintain an OpenGL state cache internally to avoid unnecessary switches.
 In order to use them, you have to use the following functions, instead of the the GL ones:
    - ccGLUseProgram() instead of glUseProgram()
    - ccGLDeleteProgram() instead of glDeleteProgram()
    - ccGLBlendFunc() instead of glBlendFunc()

 If this functionality is disabled, then ccGLUseProgram(), ccGLDeleteProgram(), ccGLBlendFunc() will call the GL ones, without using the cache.

 It is recommended to enable whenever possible to improve speed.
 If you are migrating your code from GL ES 1.1, then keep it disabled. Once all your code works as expected, turn it on.

 @since v2.0.0
 */
#ifndef CC_ENABLE_GL_STATE_CACHE
#define CC_ENABLE_GL_STATE_CACHE 1
#endif

/** @def CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
If enabled, the texture coordinates will be calculated by using this formula:
- texCoord.left = (rect.origin.x*2+1) / (texture.wide*2);
- texCoord.right = texCoord.left + (rect.size.width*2-2)/(texture.wide*2);

The same for bottom and top.

This formula prevents artifacts by using 99% of the texture.
The "correct" way to prevent artifacts is by using the spritesheet-artifact-fixer.py or a similar tool.

Affected nodes:
- CCSprite / CCSpriteBatchNode and subclasses: CCLabelBMFont, CCTMXTiledMap
- CCLabelAtlas
- CCQuadParticleSystem
- CCTileMap

To enabled set it to 1. Disabled by default.

@since v0.99.5
*/
#ifndef CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0
#endif

/** @def CC_DIRECTOR_FPS_INTERVAL
 Seconds between FPS updates.
 0.5 seconds, means that the FPS number will be updated every 0.5 seconds.
 Having a bigger number means a more reliable FPS
 
 Default value: 0.1f
 */
#ifndef CC_DIRECTOR_STATS_INTERVAL
#define CC_DIRECTOR_STATS_INTERVAL (0.5f)
#endif

/** @def CC_DIRECTOR_FPS_POSITION
 Position of the FPS

 Default: 0,0 (bottom-left corner)
 */
#ifndef CC_DIRECTOR_FPS_POSITION
#define CC_DIRECTOR_FPS_POSITION ccp(0,0)
#endif

/** @def CC_DIRECTOR_DISPATCH_FAST_EVENTS
 If enabled, and only when it is used with CCFastDirector, the main loop will wait 0.04 seconds to
 dispatch all the events, even if there are not events to dispatch.
 If your game uses lot's of events (eg: touches) it might be a good idea to enable this feature.
 Otherwise, it is safe to leave it disabled.
 
 To enable set it to 1. Disabled by default.
 
 @warning This feature is experimental
 */
#ifndef CC_DIRECTOR_DISPATCH_FAST_EVENTS
 #define CC_DIRECTOR_DISPATCH_FAST_EVENTS 0
#endif

/** @def CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
If enabled, cocos2d-mac will run on the Display Link thread. If disabled cocos2d-mac will run in its own thread.

If enabled, the images will be drawn at the "correct" time, but the events might not be very responsive.
If disabled, some frames might be skipped, but the events will be dispatched as they arrived.

To enable set it to a 1, to disable it set to 0. Enabled by default.

Only valid for cocos2d-mac. Not supported on cocos2d-ios.

*/
#ifndef CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
#define CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD 1
#endif

/** @def CC_NODE_RENDER_SUBPIXEL
 If enabled, the CCNode objects (CCSprite, CCLabel,etc) will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to 1. Enabled by default.
 */
#ifndef CC_NODE_RENDER_SUBPIXEL
#define CC_NODE_RENDER_SUBPIXEL 1
#endif

/** @def CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
 If enabled, the CCSprite objects rendered with CCSpriteBatchNode will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to 1. Enabled by default.
 */
#ifndef CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define CC_SPRITEBATCHNODE_RENDER_SUBPIXEL    1
#endif

/** @def CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
 Use GL_TRIANGLE_STRIP instead of GL_TRIANGLES when rendering the texture atlas.
 It seems it is the recommend way, but it is much slower, so, enable it at your own risk
 
 To enable set it to a value different than 0. Disabled by default.

 */
#ifndef CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
#define CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP 0
#endif

/** @def CC_TEXTURE_ATLAS_USE_VAO
 By default, CCTextureAtlas (used by many cocos2d classes) will use VAO (Vertex Array Objects).
 Apple recommends its usage but they might consume a lot of memory, specially if you use many of them.
 So for certain cases, where you might need hundreds of VAO objects, it might be a good idea to disable it.
 
 To disable it set it to 0. Enabled by default.
 
 */
#ifndef CC_TEXTURE_ATLAS_USE_VAO
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        #define CC_TEXTURE_ATLAS_USE_VAO 1
    #else
        /* Some Windows display adapter driver cannot support VAO. */
        /* Some android devices cannot support VAO very well, so we disable it by default for android platform. */
        /* Blackberry also doesn't support this feature. */
		#define CC_TEXTURE_ATLAS_USE_VAO 0
    #endif
#endif


/** @def CC_USE_LA88_LABELS
 If enabled, it will use LA88 (Luminance Alpha 16-bit textures) for CCLabelTTF objects.
 If it is disabled, it will use A8 (Alpha 8-bit textures).
 LA88 textures are 6% faster than A8 textures, but they will consume 2x memory.

 This feature is enabled by default.

 @since v0.99.5
 */
#ifndef CC_USE_LA88_LABELS
#define CC_USE_LA88_LABELS 1
#endif

/** @def CC_SPRITE_DEBUG_DRAW
 If enabled, all subclasses of CCSprite will draw a bounding box
 Useful for debugging purposes only. It is recommended to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default:
 0 -- disabled
 1 -- draw bounding box
 2 -- draw texture box
 0 -- disabled
 1 -- draw bounding box
 2 -- draw texture box
*/
#ifndef CC_SPRITE_DEBUG_DRAW
#define CC_SPRITE_DEBUG_DRAW 0
#endif

/** @def CC_SPRITEBATCHNODE_DEBUG_DRAW
If enabled, all subclasses of CCSprite that are rendered using an CCSpriteBatchNode draw a bounding box.
Useful for debugging purposes only. It is recommended to leave it disabled.

To enable set it to a value different than 0. Disabled by default.
*/
#ifndef CC_SPRITEBATCHNODE_DEBUG_DRAW
#define CC_SPRITEBATCHNODE_DEBUG_DRAW 0
#endif

/** @def CC_LABELBMFONT_DEBUG_DRAW
If enabled, all subclasses of CCLabelBMFont will draw a bounding box
Useful for debugging purposes only. It is recommended to leave it disabled.

To enable set it to a value different than 0. Disabled by default.
*/
#ifndef CC_LABELBMFONT_DEBUG_DRAW
#define CC_LABELBMFONT_DEBUG_DRAW 0
#endif

/** @def CC_LABELATLAS_DEBUG_DRAW
 If enabled, all subclasses of LabeltAtlas will draw a bounding box
 Useful for debugging purposes only. It is recommended to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#ifndef CC_LABELATLAS_DEBUG_DRAW
#define CC_LABELATLAS_DEBUG_DRAW 0
#endif

/** @def CC_ENABLE_PROFILERS
 If enabled, will activate various profilers within cocos2d. This statistical data will be output to the console
 once per second showing average time (in milliseconds) required to execute the specific routine(s).
 Useful for debugging purposes only. It is recommended to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#ifndef CC_ENABLE_PROFILERS
#define CC_ENABLE_PROFILERS 0
#endif

/** Enable Lua engine debug log */
#ifndef CC_LUA_ENGINE_DEBUG
#define CC_LUA_ENGINE_DEBUG 0
#endif

#endif // __CCCONFIG_H__
