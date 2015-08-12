/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
 * @file
 * @~english
 * cocos2d (cc) configuration file.
 * @~chinese 
 * cocos2d(cc)配置文件。
*/


/** @def CC_ENABLE_STACKABLE_ACTIONS
 * @~english If enabled, actions that alter the position property (eg: MoveBy, JumpBy, BezierBy, etc..) will be stacked.
 * If you run 2 or more 'position' actions at the same time on a node, then end position will be the sum of all the positions.
 * If disabled, only the last run action will take effect.
 * Enabled by default. Disable to be compatible with v2.0 and older versions.
 * @~chinese 
 * 如果启用, 改变位置属性的动作(如 MoveBy, JumpBy, BezierBy..)将会放到栈里面.
 * 如果在一个对象(`node`)上同时运行了2个或更多改变位置属性的动作, 这个对象(`node`)的最终位置会是所有改变位置属性动作的矢量和.
 * 如果禁用, 只有最后一个改变位置属性的动作会生效.
 * 默认启用. 禁用是为了和v2.0或更旧的版本兼容.
 * @since v2.1
 */
#ifndef CC_ENABLE_STACKABLE_ACTIONS
#define CC_ENABLE_STACKABLE_ACTIONS 1
#endif


/** @def CC_ENABLE_GL_STATE_CACHE
 * @~english If enabled, cocos2d will maintain an OpenGL state cache internally to avoid unnecessary switches.
 * In order to use them, you have to use the following functions, instead of the the GL ones:
 *  - ccGLUseProgram() instead of glUseProgram().
 *  - GL::deleteProgram() instead of glDeleteProgram().
 *  - GL::blendFunc() instead of glBlendFunc().

 * If this functionality is disabled, then ccGLUseProgram(), GL::deleteProgram(), GL::blendFunc() will call the GL ones, without using the cache.

 * It is recommended to enable whenever possible to improve speed.
 * If you are migrating your code from GL ES 1.1, then keep it disabled. Once all your code works as expected, turn it on.

 * Default value: Enabled by default

 * @~chinese 
 * 如果启用,cocos2d将维护一个OpenGL内部缓存,以避免不必要的切换。
 * 为了使用它们,你必须使用以下函数,而不是GL的函数:
 * - 使用ccGLUseProgram()而不是glUseProgram()。
 * - 使用GL::deleteProgram()而不是glDeleteProgram()。
 * - GL::blendFunc()而不是glBlendFunc()。
 * 
 * 如果禁用此功能,那么ccGLUseProgram(),GL:deleteProgram(),GL:blendFunc()将调用GL的函数,而不使用缓存。
 * 
 * 建议启用以尽可能提高速度。
 * 如果你正在从GL ES 1.1迁移您的代码,先禁用它。一旦所有代码像预期的那样工作,再把它打开。
 * 
 * 默认值:默认启用
 * 
 * @since v2.0.0
 */
#ifndef CC_ENABLE_GL_STATE_CACHE
#define CC_ENABLE_GL_STATE_CACHE 1
#endif


/** @def CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
 * @~english If enabled, the texture coordinates will be calculated by using this formula:
 * - texCoord.left = (rect.origin.x*2+1) / (texture.wide*2);
 * - texCoord.right = texCoord.left + (rect.size.width*2-2)/(texture.wide*2);

 * The same for bottom and top.

 * This formula prevents artifacts by using 99% of the texture.
 * The "correct" way to prevent artifacts is by using the spritesheet-artifact-fixer.py or a similar tool.

 * Affected nodes:
 * - Sprite / SpriteBatchNode and subclasses: LabelBMFont, TMXTiledMap.
 * - LabelAtlas.
 * - QuadParticleSystem.
 * - TileMap.

 * To enabled set it to 1. Disabled by default.

 * @~chinese 
 * 如果启用,纹理坐标计算通过使用这个公式:
 * - texCoord.left = (rect.origin.x*2+1) / (texture.wide*2);
 * - texCoord.right = texCoord.left + (rect.size.width*2-2)/(texture.wide*2);
 *
 * 底部和顶部的计算方式也类似。
 * 
 * 这个公式使用了其纹理的99%的防止失真.
 * 正确防止失真的方法是使用spritesheet-artifact-fixer.py或一个相似的工具.
 *
 * 影响节点:
 * - Sprite / SpriteBatchNode and subclasses: LabelBMFont, TMXTiledMap.
 * - LabelAtlas.
 * - QuadParticleSystem.
 * - TileMap.
 * 
 * 使将其设置为1为开启。默认情况下禁用。
 * 
 * @since v0.99.5
 */
#ifndef CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0
#endif


/** @def CC_DIRECTOR_STATS_INTERVAL
 * @~english Seconds between FPS updates.
 * 0.5 seconds, means that the FPS number will be updated every 0.5 seconds.
 * Having a bigger number means a more reliable FPS.

 * Default value: 0.1f
 * @~chinese 
 * FPS更新秒间隔。
 * 0.5秒,意味着FPS数量将每0.5秒更新一次。
 * 更大的值意味着一个更可靠的FPS。
 * 
 * 默认值:0.1 f
 */
#ifndef CC_DIRECTOR_STATS_INTERVAL
#define CC_DIRECTOR_STATS_INTERVAL (0.1f)
#endif


/** @def CC_DIRECTOR_FPS_POSITION
 * @~english Position of the FPS.

 * Default: 0,0 (bottom-left corner).
 * @~chinese CC_DIRECTOR_FPS_POSITION
 * FPS的位置。
 * 
 * 默认值:0,0(左下部的角落)。
 */
#ifndef CC_DIRECTOR_FPS_POSITION
#define CC_DIRECTOR_FPS_POSITION Vec2(0,0)
#endif


/** @def CC_DIRECTOR_DISPATCH_FAST_EVENTS
 * @~english If enabled, and only when it is used with FastDirector, the main loop will wait 0.04 seconds to
 * dispatch all the events, even if there are not events to dispatch.
 * If your game uses lot's of events (eg: touches) it might be a good idea to enable this feature.
 * Otherwise, it is safe to leave it disabled.

 * To enable set it to 1. Disabled by default.
 * @~chinese
 * 如果启用, 只有此功能被FastDirector使用时, 主循环才会等待 0.04 秒去分发所有的活动(Event), 即使此时没有
 * 任何活动需要分发。
 * 如果你的游戏使用很多的事件(如:触摸事件)，这可能是一个好主意来启用这个特性。
 * 否则,它是安全的把它禁用。
 * 
 * 使将其设置为1以启用。默认情况下禁用。
 * 
 * @warning @~english This feature is experimental.
 * @~chinese 这个特性目前是试验性的。
 * @warning This feature is experimental.
 */
#ifndef CC_DIRECTOR_DISPATCH_FAST_EVENTS
 #define CC_DIRECTOR_DISPATCH_FAST_EVENTS 0
#endif


/** @def CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
 * @~english If enabled, cocos2d-mac will run on the Display Link thread. If disabled cocos2d-mac will run in its own thread.
 * If enabled, the images will be drawn at the "correct" time, but the events might not be very responsive.
 * If disabled, some frames might be skipped, but the events will be dispatched as they arrived.
 * To enable set it to a 1, to disable it set to 0. Enabled by default.
 * Only valid for cocos2d-mac. Not supported on cocos2d-ios.
 * @~chinese 
 * 如果启用,cocos2d-mac会工作在Display Link线程上。如果禁用cocos2d-mac将运行在它自己的线程。
 * 如果启用，图片将会在正确的时间绘制，但是事件可能不会响应的很及时。
 * 如果禁用,一些帧可能被忽略,但是事件一旦到达将会被马上分发。
 * 使将其设置为1启用,设置为0禁用。默认启用。
 * 只有cocos2d-mac有效。不支持cocos2d-ios。
 */
#ifndef CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
#define CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD 1
#endif


/** @def CC_NODE_RENDER_SUBPIXEL
 * @~english If enabled, the Node objects (Sprite, Label,etc) will be able to render in subpixels.
 * If disabled, integer pixels will be used.
 * To enable set it to 1. Enabled by default.
 * @~chinese 
 * 如果启用,节点对象(Sprite, Label等)能够用子像素渲染。
 * 如果禁用,将使用整数像素。
 * 使将其设置为1启用。默认启用。
 */
#ifndef CC_NODE_RENDER_SUBPIXEL
#define CC_NODE_RENDER_SUBPIXEL 1
#endif


/** @def CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
 * @~english If enabled, the Sprite objects rendered with SpriteBatchNode will be able to render in subpixels.
 * If disabled, integer pixels will be used.
 * To enable set it to 1. Enabled by default.
 * @~chinese 
 * 如果启用,使用SpriteBatchNode渲染的Sprite能够在子像素渲染。
 * 如果禁用,将使用整数像素。
 * 使将其设置为1启用。默认启用。
 */
#ifndef CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define CC_SPRITEBATCHNODE_RENDER_SUBPIXEL    1
#endif


/** @def CC_TEXTURE_ATLAS_USE_VAO
 * @~english By default, TextureAtlas (used by many cocos2d classes) will use VAO (Vertex Array Objects).
 * Apple recommends its usage but they might consume a lot of memory, specially if you use many of them.
 * So for certain cases, where you might need hundreds of VAO objects, it might be a good idea to disable it.
 * To disable it set it to 0. Enabled by default.
 * @~chinese 
 * 默认情况下,TextureAtlas(许多cocos2d类使用)将使用VAO(顶点数组对象)。
 * 苹果公司建议使用,但他们可能会消耗大量的内存,特别如果你使用很多的话。
 * 所以在某些情况下,您可能需要数百个VAO对象,这时候禁用它可能是一个好主意。
 * 将其设置为0禁用它。默认启用。
 */
#ifndef CC_TEXTURE_ATLAS_USE_VAO
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        #define CC_TEXTURE_ATLAS_USE_VAO 1
    #else

        /* @~english Some Windows display adapter driver cannot support VAO.
         * Some android devices cannot support VAO very well, so we disable it by default for android platform.
         * Blackberry also doesn't support this feature.
         * @~chinese 一些Windows显示适配器驱动程序不支持VAO。
         * 一些安卓设备不能很好的支持VAO，所以我们在安卓平台默认是禁用它的。
         * 黑莓手机也不支持这个特性。
         * Blackberry also doesn't support this feature.
         */
		#define CC_TEXTURE_ATLAS_USE_VAO 0
    #endif
#endif



/** @def CC_USE_LA88_LABELS
 * @~english If enabled, it will use LA88 (Luminance Alpha 16-bit textures) for LabelTTF objects.
 * If it is disabled, it will use A8 (Alpha 8-bit textures).
 * LA88 textures are 6% faster than A8 textures, but they will consume 2x memory.
 * This feature is enabled by default.
 * @~chinese 
 * 如果启用,它将为LabelTTF对象使用LA88(Luminance Alpha 16-bit的纹理)。
 * 如果它是禁用的,它将使用A8(Alpha 8-bit纹理)。
 * LA88纹理比A8纹理快6%,但他们会消耗2倍的内存。
 * 这个功能是默认启用。
 * @since v0.99.5
 */
#ifndef CC_USE_LA88_LABELS
#define CC_USE_LA88_LABELS 1
#endif


/** @def CC_SPRITE_DEBUG_DRAW
 * @~english If enabled, all subclasses of Sprite will draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default:
 * 0 -- disabled
 * 1 -- draw bounding box
 * 2 -- draw texture box
 * @~chinese 
 * 如果启用,所有的Sprite子类将画一个边界框。
 * 仅用于调试目的。建议把它禁用。
 * 使将其设置为不是0的值即启用。默认情况下禁用。
 * 0——禁用
 * 1——画边界框
 * 2——绘制纹理
 */
#ifndef CC_SPRITE_DEBUG_DRAW
#define CC_SPRITE_DEBUG_DRAW 0
#endif


/** @def CC_SPRITEBATCHNODE_DEBUG_DRAW
 * @~english If enabled, all subclasses of Sprite that are rendered using an SpriteBatchNode draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 * @~chinese 
 * 如果启用,所有子类的雪碧呈现使用SpriteBatchNode画一个边界框。
 * 仅用于调试目的。建议把它禁用。
 * 使将其设置为不是0的值即启用。默认情况下禁用。
 */
#ifndef CC_SPRITEBATCHNODE_DEBUG_DRAW
#define CC_SPRITEBATCHNODE_DEBUG_DRAW 0
#endif


/** @def CC_LABELBMFONT_DEBUG_DRAW
 * @~english If enabled, all subclasses of LabelBMFont will draw a bounding box.
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 * @~chinese 
 * 如果启用,所有的子类LabelBMFont将画一个边界框。
 * 仅用于调试目的。建议把它禁用。
 * 使将其设置为不是0的值即启用。默认情况下禁用。
 */
#ifndef CC_LABELBMFONT_DEBUG_DRAW
#define CC_LABELBMFONT_DEBUG_DRAW 0
#endif


/** @def CC_LABELATLAS_DEBUG_DRAW
 * @~english If enabled, all subclasses of LabeltAtlas will draw a bounding box
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 * @~chinese 
 * 如果启用,所有的子类LabeltAtlas将画一个边界框
 * 仅用于调试目的。建议把它禁用。
 * 使将其设置为不是0的值即启用。默认情况下禁用。
 */
#ifndef CC_LABELATLAS_DEBUG_DRAW
#define CC_LABELATLAS_DEBUG_DRAW 0
#endif


/** @def CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
 * @~english If enabled (in conjunction with assertion macros) will verify on Node destruction that the node being destroyed has no event
 * listeners still associated with it in the event dispatcher. This can be used to track down problems where the event dispatch
 * system has dangling pointers to destroyed nodes.
 * Note: event listener verification will always be disabled in builds where assertions are disabled regardless of this setting.
 * @~chinese 
 * 如果启用(和断言一起), 将会验证 Node 对象析构—— node 析构时没有与 EventDispather 联系的 EventListener.
 * 这个可以用来查出那些问题—— EventDispather 系统含有指向已析构node的悬空指针.
 * 注意: 当断言被禁用时, 无论此处设置为何值, 构建过程中 EventListener 验证将总是禁用的.
 */
#ifndef CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
#define CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS 0
#endif


/** @def CC_ENABLE_PROFILERS
 * @~english If enabled, will activate various profilers within cocos2d. This statistical data will be output to the console
 * once per second showing average time (in milliseconds) required to execute the specific routine(s).
 * Useful for debugging purposes only. It is recommended to leave it disabled.
 * To enable set it to a value different than 0. Disabled by default.
 * @~chinese 
 * 如果启用,将在cocos2d激活各种分析器。这个统计数据将被输出到控制台
 * 一旦每秒显示所需的平均时间(以毫秒为单位)来执行特定的例程(s)。
 * 仅用于调试目的。建议把它禁用。
 * 要启用可以将其设置为不为0的值。默认情况下禁用。
 */
#ifndef CC_ENABLE_PROFILERS
#define CC_ENABLE_PROFILERS 0
#endif


/** @~english Enable Lua engine debug log.  @~chinese 是否使用Lua引擎调试日志。*/
#ifndef CC_LUA_ENGINE_DEBUG
#define CC_LUA_ENGINE_DEBUG 0
#endif


/** @~english Use physics integration API.  @~chinese 使用物理集成API。*/
#ifndef CC_USE_PHYSICS
#define CC_USE_PHYSICS 1
#endif


/** @~english Use 3d physics integration API.  @~chinese 使用3d物理集成API。*/
#ifndef CC_USE_3D_PHYSICS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define CC_USE_3D_PHYSICS 1
#endif
#endif

#if (CC_USE_3D_PHYSICS)
/** Use bullet physics engine. */
#ifndef CC_ENABLE_BULLET_INTEGRATION
#define CC_ENABLE_BULLET_INTEGRATION 1
#endif
#endif

/** @~english Use 3D navigation API. @~chinese 是否使用导航网格功能。*/
#ifndef CC_USE_NAVMESH
#define CC_USE_NAVMESH 1
#endif

/** @~english Use culling or not.  @~chinese 是否使用剔除功能。*/
#ifndef CC_USE_CULLING
#define CC_USE_CULLING 1
#endif


/** @~english Support PNG or not. If your application don't use png format picture, you can undefine this macro to save package size.
 * @~chinese 支持PNG与否。如果您的应用程序不使用png格式的图片,你可以命令取消这个宏保存包的大小。
*/
#ifndef CC_USE_PNG
#define CC_USE_PNG  1
#endif // CC_USE_PNG


/** @~english Support JPEG or not. If your application don't use jpeg format picture, you can undefine this macro to save package size.
 * @~chinese 支持JPEG与否。如果您的应用程序不使用jpeg格式的图片,你可以取消这个宏定义来减小包大小。
 */
#ifndef CC_USE_JPEG
#define CC_USE_JPEG  1
#endif // CC_USE_JPEG


/** @~english Support TIFF or not. If your application don't use TIFF format picture, you can undefine this macro to save package size.
 * @~chinese 支持TIFF与否。如果您的应用程序不使用TIFF格式的图片,你可以取消这个宏定义来减小包大小。
 */
#ifndef CC_USE_TIFF
#define CC_USE_TIFF  1
#endif // CC_USE_TIFF


/** @~english Support webp or not. If your application don't use webp format picture, you can undefine this macro to save package size.
 * @~chinese 支持webp与否。如果您的应用程序不使用webp格式图片,你可以取消这个宏定义来减小包大小。
 */
#ifndef CC_USE_WEBP
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#define CC_USE_WEBP  1
#endif
#endif // CC_USE_WEBP


 /** @~english Support WIC (Windows Image Component) or not. Replaces PNG, TIFF and JPEG
  * @~chinese 是否支持WIC(Windows图像组件)。取代PNG,TIFF和JPEG
 */
#ifndef CC_USE_WIC
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define CC_USE_WIC  1
#undef CC_USE_TIFF
#undef CC_USE_JPEG
#undef CC_USE_PNG
#endif
#endif // CC_USE_WIC


/** @~english Enable Script binding.  @~chinese 启用脚本绑定。*/
#ifndef CC_ENABLE_SCRIPT_BINDING
#define CC_ENABLE_SCRIPT_BINDING 1
#endif


/** @def CC_CONSTRUCTOR_ACCESS
 * @~english Indicate the init functions access modifier. If value equals to protected, then these functions are protected.
 * If value equals to public, these functions are public,
 * protected by default.
 * @~chinese 
 * 表明init函数访问修饰符。如果值等于protected,那么这些方法受到保护。
 * 如果值等于公众,这些功能是公开的,
 * 默认情况下保护。
 */
#ifndef CC_CONSTRUCTOR_ACCESS
#define CC_CONSTRUCTOR_ACCESS public
#endif


/** @def CC_ENABLE_ALLOCATOR
 * @~english Turn on creation of global allocator and pool allocators
 * as specified by CC_ALLOCATOR_GLOBAL below.
 * @~chinese 
 * 打开创建全局分配器和池分配器。
 * 如下CC_ALLOCATOR_GLOBAL规定。
 */
#ifndef CC_ENABLE_ALLOCATOR
# define CC_ENABLE_ALLOCATOR 0
#endif


/** @def CC_ENABLE_ALLOCATOR_DIAGNOSTICS
 * @~english Turn on debugging of allocators. This is slower, uses
 * more memory, and should not be used for production builds.
 * @~chinese 
 * 打开调试分配器。这会很慢,使用更多的内存,不要用于产品构建。
 */
#ifndef CC_ENABLE_ALLOCATOR_DIAGNOSTICS
# define CC_ENABLE_ALLOCATOR_DIAGNOSTICS CC_ENABLE_ALLOCATOR
#endif


/** @def CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE
 * @~english Turn on override of global new and delete
 * as specified by CC_ALLOCATOR_GLOBAL_NEW_DELETE below.
 * @~chinese 
 * 开启全局的new和delete的重写。
 * 如下CC_ALLOCATOR_GLOBAL_NEW_DELETE规定。
 */
#ifndef CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE
# define CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE 0
# endif//CC_ENABLE_ALLOCATOR_GLOBAL_NEW_DELETE


/** @def CC_ALLOCATOR_GLOBAL
 * @~english Specify allocator to use for global allocator.
 * @~chinese 
 * 指定要使用分配器用于全局分配器。
 */
#ifndef CC_ALLOCATOR_GLOBAL
# define CC_ALLOCATOR_GLOBAL cocos2d::allocator::AllocatorStrategyDefault
#endif


/** @def CC_ALLOCATOR_GLOBAL_NEW_DELETE
 * @~english Specify allocator to use when overriding of new and delete.
 * @~chinese 
 * 当重写了new和delete后指定要使用的分配器。
 */
#ifndef CC_ALLOCATOR_GLOBAL_NEW_DELETE
# define CC_ALLOCATOR_GLOBAL_NEW_DELETE cocos2d::allocator::AllocatorStrategyGlobalSmallBlock
#endif

#endif // __CCCONFIG_H__
