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

#ifndef __CCCONFIG_H__
#define __CCCONFIG_H__

/** @def CC_FONT_LABEL_SUPPORT
 If enabled, FontLabel will be used to render .ttf files.
 If the .ttf file is not found, then it will use the standard UIFont class
 If disabled, the standard UIFont class will be used.
 
 To enable set it to a value different than 0. Enabled by default.
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
#define CC_DIRECTOR_FPS_INTERVAL (0.1f)

/** @def CC_DIRECTOR_DISPATCH_FAST_EVENTS
 If enabled, and only when it is used with CCFastDirector, the main loop will wait 0.04 seconds to
 dispatch all the events, even if there are not events to dispatch.
 If your game uses lot's of events (eg: touches) it might be a good idea to enable this feature.
 Otherwise, it is safe to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 
 @warning This feature is experimental
 */
 #define CC_DIRECTOR_DISPATCH_FAST_EVENTS 0

/** @def CC_COCOSNODE_RENDER_SUBPIXEL
 If enabled, the CCNode objects (CCSprite, CCLabel,etc) will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to a value different than 0. Enabled by default.
 */
#define CC_COCOSNODE_RENDER_SUBPIXEL 1

/** @def CC_SPRITESHEET_RENDER_SUBPIXEL
 If enabled, the CCSprite objects rendered with CCSpriteSheet will be able to render in subpixels.
 If disabled, integer pixels will be used.
 
 To enable set it to a value different than 0. Enabled by default.
 */
#define CC_SPRITESHEET_RENDER_SUBPIXEL	1

/** @def CC_TEXTURE_ATLAS_USES_VBO
 If enabled, the CCTextureAtlas object will use VBO instead of vertex list (VBO is recommended by Apple)
 
 To enable set it to a value different than 0. Enabled by default.

 @since v0.99.0
 */
#define CC_TEXTURE_ATLAS_USES_VBO 1

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

/** @def CC_SPRITE_DEBUG_DRAW
 If enabled, all subclasses of CCSprite will draw a bounding box
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#define CC_SPRITE_DEBUG_DRAW 0

/** @def CC_SPRITESHEET_DEBUG_DRAW
 If enabled, all subclasses of CCSprite that are rendered using an CCSpriteSheet draw a bounding box.
 Useful for debugging purposes only. It is recommened to leave it disabled.
 
 To enable set it to a value different than 0. Disabled by default.
 */
#define CC_SPRITESHEET_DEBUG_DRAW 0

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

#endif // __CCCONFIG_H__
