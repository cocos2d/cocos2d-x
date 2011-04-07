/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
- CCSprite / CCSpriteBatchNode and subclasses: CCBitmapFontAtlas, CCTMXTiledMap
- CCLabelAtlas
- CCQuadParticleSystem
- CCTileMap

To enabled set it to 1. Disabled by default.

@since v0.99.5
*/
#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0

/** @def CC_FONT_LABEL_SUPPORT
 If enabled, FontLabel will be used to render .ttf files.
 If the .ttf file is not found, then it will use the standard UIFont class
 If disabled, the standard UIFont class will be used.
 
 To disable set it to 0. Enabled by default.

 Only valid for cocos2d-ios. Not supported on cocos2d-mac
 */
#define CC_FONT_LABEL_SUPPORT	1

/** @def CC_DIRECTOR_FAST_FPS
 If enabled, then the FPS will be drawn using CCLabelAtlas (fast rendering).
 You will need to add the fps_images.png to your project.
 If disabled, the FPS will be rendered using CCLabel (slow rendering)
 
 To enable set it to a value different than 0. Enabled by default.
 */
#define CC_DIRECTOR_FAST_FPS	1

/** @def CC_DIRECTOR_FPS_INTERVAL
 Senconds between FPS updates.
 0.5 seconds, means that the FPS number will be updated every 0.5 seconds.
 Having a bigger number means a more reliable FPS
 
 Default value: 0.1f
 */
#define CC_DIRECTOR_FPS_INTERVAL (0.5f)

/** @def CC_DIRECTOR_DISPATCH_FAST_EVENTS
 If enabled, and only when it is used with CCFastDirector, the main loop will wait 0.04 seconds to
 dispatch all the events, even if there are not events to dispatch.
 If your game uses lot's of events (eg: touches) it might be a good idea to enable this feature.
 Otherwise, it is safe to leave it disabled.
 
 To enable set it to 1. Disabled by default.
 
 @warning This feature is experimental
 */
 #define CC_DIRECTOR_DISPATCH_FAST_EVENTS 0

/** @def CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
If enabled, cocos2d-mac will run on the Display Link thread. If disabled cocos2d-mac will run in its own thread.

If enabled, the images will be drawn at the "correct" time, but the events might not be very responsive.
If disabled, some frames might be skipped, but the events will be dispatched as they arrived.

To enable set it to a 1, to disable it set to 0. Enabled by default.

Only valid for cocos2d-mac. Not supported on cocos2d-ios.

*/
#define CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD 1

/** @def CC_COCOSNODE_RENDER_SUBPIXEL
 If enabled, the CCNode objects (CCSprite, CCLabel,etc) will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to 1. Enabled by default.
 */
#define CC_COCOSNODE_RENDER_SUBPIXEL 1

/** @def CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
 If enabled, the CCSprite objects rendered with CCSpriteBatchNode will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to 1. Enabled by default.
 */
#define CC_SPRITEBATCHNODE_RENDER_SUBPIXEL	1

/** @def CC_USES_VBO
If enabled, batch nodes (texture atlas and particle system) will use VBO instead of vertex list (VBO is recommended by Apple)

To enable set it to 1.
Enabled by default on iPhone with ARMv7 processors, iPhone Simulator and Mac
Disabled by default on iPhone with ARMv6 processors.

@since v0.99.5
*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
#define CC_USES_VBO 0
#else
#define CC_USES_VBO 1
#endif

/** @def CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
 If enabled, CCNode will transform the nodes using a cached Affine matrix.
 If disabled, the node will be transformed using glTranslate,glRotate,glScale.
 Using the affine matrix only requires 2 GL calls.
 Using the translate/rotate/scale requires 5 GL calls.
 But computing the Affine matrix is relative expensive.
 But according to performance tests, Affine matrix performs better.
 This parameter doesn't affect SpriteSheet nodes.
 
 To enable set it to a value different than 0. Enabled by default.

 */
#define CC_NODE_TRANSFORM_USING_AFFINE_MATRIX 1

/** @def CC_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA
If most of your imamges have pre-multiplied alpha, set it to 1 (if you are going to use .PNG/.JPG file images).
Only set to 0 if ALL your images by-pass Apple UIImage loading system (eg: if you use libpng or PVR images)

To enable set it to a value different than 0. Enabled by default.

@since v0.99.5
*/
#define CC_OPTIMIZE_BLEND_FUNC_FOR_PREMULTIPLIED_ALPHA 1

/** @def CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP
 Use GL_TRIANGLE_STRIP instead of GL_TRIANGLES when rendering the texture atlas.
 It seems it is the recommend way, but it is much slower, so, enable it at your own risk
 
 To enable set it to a value different than 0. Disabled by default.

 */
#define CC_TEXTURE_ATLAS_USE_TRIANGLE_STRIP 0

/** @def CC_TEXTURE_NPOT_SUPPORT
 If enabled, NPOT textures will be used where available. Only 3rd gen (and newer) devices support NPOT textures.
 NPOT textures have the following limitations:
	- They can't have mipmaps
	- They only accept GL_CLAMP_TO_EDGE in GL_TEXTURE_WRAP_{S,T}
 
 To enable set it to a value different than 0. Disabled by default.

 @since v0.99.2
 */
#define CC_TEXTURE_NPOT_SUPPORT 0

/** @def CC_RETINA_DISPLAY_SUPPORT
If enabled, cocos2d supports retina display. 
For performance reasons, it's recommended disable it in games without retina display support, like iPad only games.

To enable set it to 1. Use 0 to disable it. Enabled by default.

@since v0.99.5
*/
#define CC_RETINA_DISPLAY_SUPPORT 1

/** @def CC_RETINA_DISPLAY_FILENAME_SUFFIX
It's the suffix that will be appended to the files in order to load "retina display" images.

On an iPhone4 with Retina Display support enabled, the file @"sprite-hd.png" will be loaded instead of @"sprite.png".
If the file doesn't exist it will use the non-retina display image.

Platforms: Only used on Retina Display devices like iPhone 4.

@since v0.99.5
*/ 
#define CC_RETINA_DISPLAY_FILENAME_SUFFIX "-hd"

/** @def CC_USE_RGBA32_LABELS_ON_NEON_ARCH
If enabled, it will use RGBA8888 (32-bit textures) on Neon devices for CCLabelTTF objects.
If it is disabled, or if it is used on another architecture it will use A8 (8-bit textures).
On Neon devices, RGBA8888 textures are 6% faster than A8 textures, but then will consule 4x memory.

This feature is disabled by default.

Platforms: Only used on ARM Neon architectures like iPhone 3GS or newer and iPad.

@since v0.99.5
*/
#define CC_USE_RGBA32_LABELS_ON_NEON_ARCH 0

/** @def CC_SPRITE_DEBUG_DRAW
 If enabled, all subclasses of CCSprite will draw a bounding box
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#define CC_SPRITE_DEBUG_DRAW 0

/** @def CC_SPRITEBATCHNODE_DEBUG_DRAW
If enabled, all subclasses of CCSprite that are rendered using an CCSpriteSheet draw a bounding box.
Useful for debugging purposes only. It is recommened to leave it disabled.

To enable set it to a value different than 0. Disabled by default.
*/
#define CC_SPRITEBATCHNODE_DEBUG_DRAW 0

/** @def CC_BITMAPFONTATLAS_DEBUG_DRAW
 If enabled, all subclasses of BitmapFontAtlas will draw a bounding box
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#define CC_BITMAPFONTATLAS_DEBUG_DRAW 0

/** @def CC_LABELATLAS_DEBUG_DRAW
 If enabled, all subclasses of LabeltAtlas will draw a bounding box
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#define CC_LABELATLAS_DEBUG_DRAW 0

/** @def CC_ENABLE_PROFILERS
 If enabled, will activate various profilers withing cocos2d. This statistical data will be output to the console
 once per second showing average time (in milliseconds) required to execute the specific routine(s).
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#define CC_ENABLE_PROFILERS 0

/** @def CC_COMPATIBILITY_WITH_0_8
 Enable it if you want to support v0.8 compatbility.
 Basically, classes without namespaces will work.
 It is recommended to disable compatibility once you have migrated your game to v0.9 to avoid class name polution
 
 To enable set it to a value different than 0. Disabled by default.
 */
#define CC_COMPATIBILITY_WITH_0_8 0

#if CC_RETINA_DISPLAY_SUPPORT
#define CC_IS_RETINA_DISPLAY_SUPPORTED 1
#else
#define CC_IS_RETINA_DISPLAY_SUPPORTED 0
#endif

#endif // __CCCONFIG_H__
