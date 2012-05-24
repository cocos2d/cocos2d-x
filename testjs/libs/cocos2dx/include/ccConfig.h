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

#ifndef __CCCONFIG_H__
#define __CCCONFIG_H__

#include "CCPlatformConfig.h"

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

/** @def CC_FONT_LABEL_SUPPORT
 If enabled, FontLabel will be used to render .ttf files.
 If the .ttf file is not found, then it will use the standard UIFont class
 If disabled, the standard UIFont class will be used.
 
 To disable set it to 0. Enabled by default.

 Only valid for cocos2d-ios. Not supported on cocos2d-mac
 */
#ifndef CC_FONT_LABEL_SUPPORT
#define CC_FONT_LABEL_SUPPORT	1
#endif

/** @def CC_DIRECTOR_FAST_FPS
 If enabled, then the FPS will be drawn using CCLabelAtlas (fast rendering).
 You will need to add the fps_images.png to your project.
 If disabled, the FPS will be rendered using CCLabel (slow rendering)
 
 To enable set it to a value different than 0. Enabled by default.
 */
#ifndef CC_DIRECTOR_FAST_FPS
#define CC_DIRECTOR_FAST_FPS	1
#endif

/** @def CC_DIRECTOR_FPS_INTERVAL
 Senconds between FPS updates.
 0.5 seconds, means that the FPS number will be updated every 0.5 seconds.
 Having a bigger number means a more reliable FPS
 
 Default value: 0.1f
 */
#ifndef CC_DIRECTOR_FPS_INTERVAL
#define CC_DIRECTOR_FPS_INTERVAL (0.5f)
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

/** @def CC_COCOSNODE_RENDER_SUBPIXEL
 If enabled, the CCNode objects (CCSprite, CCLabel,etc) will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to 1. Enabled by default.
 */
#ifndef CC_COCOSNODE_RENDER_SUBPIXEL
#define CC_COCOSNODE_RENDER_SUBPIXEL 1
#endif

/** @def CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
 If enabled, the CCSprite objects rendered with CCSpriteBatchNode will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to 1. Enabled by default.
 */
#ifndef CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define CC_SPRITEBATCHNODE_RENDER_SUBPIXEL	1
#endif

/** @def CC_USES_VBO
If enabled, batch nodes (texture atlas and particle system) will use VBO instead of vertex list (VBO is recommended by Apple)

To enable set it to 1.
Enabled by default on iPhone with ARMv7 processors, iPhone Simulator and Mac
Disabled by default on iPhone with ARMv6 processors.

@since v0.99.5
*/
#ifndef CC_USES_VBO
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
#define CC_USES_VBO 0
#else
#define CC_USES_VBO 1
#endif
#endif

/** @def CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
 If enabled, CCNode will transform the nodes using a cached Affine matrix.
 If disabled, the node will be transformed using glTranslate,glRotate,glScale.
 Using the affine matrix only requires 2 GL calls.
 Using the translate/rotate/scale requires 5 GL calls.
 But computing the Affine matrix is relative expensive.
 But according to performance tests, Affine matrix performs better.
 This parameter doesn't affect CCSpriteBatchNode nodes.
 
 To enable set it to a value different than 0. Enabled by default.

 */
#ifndef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
#define CC_NODE_TRANSFORM_USING_AFFINE_MATRIX 1
#endif

/** @def CC_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA
If most of your imamges have pre-multiplied alpha, set it to 1 (if you are going to use .PNG/.JPG file images).
Only set to 0 if ALL your images by-pass Apple UIImage loading system (eg: if you use libpng or PVR images)

To enable set it to a value different than 0. Enabled by default.

@since v0.99.5
*/
#ifndef CC_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA
#define CC_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA 1
#endif

/** @def CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
 Use GL_TRIANGLE_STRIP instead of GL_TRIANGLES when rendering the texture atlas.
 It seems it is the recommend way, but it is much slower, so, enable it at your own risk
 
 To enable set it to a value different than 0. Disabled by default.

 */
#ifndef CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
#define CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP 0
#endif

/** @def CC_TEXTURE_NPOT_SUPPORT
 If enabled, NPOT textures will be used where available. Only 3rd gen (and newer) devices support NPOT textures.
 NPOT textures have the following limitations:
	- They can't have mipmaps
	- They only accept GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}
 
 To enable set it to a value different than 0. Disabled by default.

 This value governs only the PNG, GIF, BMP, images.
 This value DOES NOT govern the PVR (PVR.GZ, PVR.CCZ) files. If NPOT PVR is loaded, then it will create an NPOT texture ignoring this value.

 @deprecated This value will be removed in 1.1 and NPOT textures will be loaded by default if the device supports it.

 @since v0.99.2
 */
#ifndef CC_TEXTURE_NPOT_SUPPORT
#define CC_TEXTURE_NPOT_SUPPORT 0
#endif


/** @def CC_USE_LA88_LABELS_ON_NEON_ARCH
If enabled, it will use LA88 (16-bit textures) on Neon devices for CCLabelTTF objects.
If it is disabled, or if it is used on another architecture it will use A8 (8-bit textures).
On Neon devices, LA88 textures are 6% faster than A8 textures, but then will consume 2x memory.

This feature is disabled by default.

Platforms: Only used on ARM Neon architectures like iPhone 3GS or newer and iPad.

@since v0.99.5
*/
#ifndef CC_USE_LA88_LABELS_ON_NEON_ARCH
#define CC_USE_LA88_LABELS_ON_NEON_ARCH 0
#endif

/** @def CC_SPRITE_DEBUG_DRAW
 If enabled, all subclasses of CCSprite will draw a bounding box
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
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
Useful for debugging purposes only. It is recommened to leave it disabled.

To enable set it to a value different than 0. Disabled by default.
*/
#ifndef CC_SPRITEBATCHNODE_DEBUG_DRAW
#define CC_SPRITEBATCHNODE_DEBUG_DRAW 0
#endif

/** @def CC_LABELBMFONT_DEBUG_DRAW
If enabled, all subclasses of CCLabelBMFont will draw a bounding box
Useful for debugging purposes only. It is recommened to leave it disabled.

To enable set it to a value different than 0. Disabled by default.
*/
#ifndef CC_LABELBMFONT_DEBUG_DRAW
#define CC_LABELBMFONT_DEBUG_DRAW 0
#endif

/** @def CC_LABELATLAS_DEBUG_DRAW
 If enabled, all subclasses of LabeltAtlas will draw a bounding box
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#ifndef CC_LABELATLAS_DEBUG_DRAW
#define CC_LABELATLAS_DEBUG_DRAW 0
#endif

/** @def CC_ENABLE_PROFILERS
 If enabled, will activate various profilers withing cocos2d. This statistical data will be output to the console
 once per second showing average time (in milliseconds) required to execute the specific routine(s).
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
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
