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

#include "base/CCPlatformConfig.h"

/**
 @file
 cocos2d (cc) configuration file
*/

/** @def CC_ENABLE_STACKABLE_ACTIONS
 如果启用, 改变位置属性的动作(如 MoveBy, JumpBy, BezierBy..)将会放到栈里面. 
 如果在一个对象(`node`)上同时运行了2个或更多改变位置属性的动作, 这个对象(`node`)的最终位置会是所有改变位置属性动作的矢量和.
 如果禁用, 只有最后一个改变位置属性的动作会生效.
 
 默认启用. 禁用是为了和v2.0或更旧的版本兼容.
 @since v2.1
 */
#ifndef CC_ENABLE_STACKABLE_ACTIONS
#define CC_ENABLE_STACKABLE_ACTIONS 1
#endif

/** @def CC_ENABLE_GL_STATE_CACHE
 如果启用, cocos2d 会内部维护一个OpenGL状态缓存来避免不必要的切换.
 为了使用它们, 你必须要使用以下函数来替代 GL 那些.
    - ccGLUseProgram() 替代 glUseProgram()
    - GL::deleteProgram() 替代 glDeleteProgram()
    - GL::blendFunc() 替代 glBlendFunc()
 如果这个功能禁用了, ccGLUseProgram(), GL::deleteProgram(), GL::blendFunc()会不使用(OpenGL状态)缓存调用 GL 那些函数.
 推荐启用, 无论何时都有可能提升速度.
 如果你在从GL ES1.1迁移代码, 请保持禁用. 当所有代码都如预期那样工作的时候, 再启用这项功能.

 默认值: 默认启用
 @since v2.0.0
 */
#ifndef CC_ENABLE_GL_STATE_CACHE
#define CC_ENABLE_GL_STATE_CACHE 1
#endif

/** @def CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
如果启用, 纹理贴图坐标将会使用以下公式计算:
    - texCoord.left = (rect.origin.x*2+1) / (texture.wide*2);
    - texCoord.right = texCoord.left + (rect.size.width*2-2)/(texture.wide*2);
纹理贴图坐标的顶部和底部公式是同样的.

这个公式使用了其纹理的99%的防止失真.
正确防止失真的方法是使用spritesheet-artifact-fixer.py或一个相似的工具.

影响的对象(nodes):
    - Sprite / SpriteBatchNode 和子类: LabelBMFont, TMXTiledMap
    - LabelAtlas
    - QuadParticleSystem
    - TileMap
启用请设置值为 1, 默认禁用.

@since v0.99.5
*/
#ifndef CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 0
#endif

/** @def CC_DIRECTOR_FPS_INTERVAL
 FPS (数字)更新间隔(单位: 秒)
 0.5 秒表示 FPS 数字每隔0.5 秒更新一次.
 有一个更大的(FPS)数字表示一个更可靠的FPS.

 默认值: 0.1f
 */
#ifndef CC_DIRECTOR_STATS_INTERVAL
#define CC_DIRECTOR_STATS_INTERVAL (0.1f)
#endif

/** @def CC_DIRECTOR_FPS_POSITION
 FPS 数字的位置

 默认值: 0,0(左下角)
 */
#ifndef CC_DIRECTOR_FPS_POSITION
#define CC_DIRECTOR_FPS_POSITION Vec2(0,0)
#endif

/** @def CC_DIRECTOR_DISPATCH_FAST_EVENTS
 如果启用, 只有此功能被FastDirector使用时, 主循环才会等待 0.04 秒去分发所有的活动(Event), 即使此时没有
 任何活动需要分发.
 如果你的游戏使用了大量的活动(如:touches), 使用此功能是个不错的主意.
 否则的话, 安全起见保持禁用.

 启用请设置值为 1. 默认禁用.
 
 @warning This feature is experimental
 */
#ifndef CC_DIRECTOR_DISPATCH_FAST_EVENTS
 #define CC_DIRECTOR_DISPATCH_FAST_EVENTS 0
#endif

/** @def CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
如果启用, cocos2d-mac 将会在Display Link线程上运行. 如果禁用, cocos2d-mac 将会在自己的线程上运行.
如果启用, 图像将会在正确的时间绘制出, 但是活动(Event)可能不会很及时响应.
如果禁用, 一些帧会被跳过, 但是活动(Event)将会在到达时分发(产生即分发,及时响应).

启用请设置值为 1. 禁用请设置值为 0. 默认启用. 

仅仅在cocos2d-mac上有效. 不支持cocos2d-ios.

*/
#ifndef CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
#define CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD 1
#endif

/** @def CC_NODE_RENDER_SUBPIXEL
 如果启用, Node 对象(Sprite, Label等)将会以亚像素(subpixels)级别渲染.
 如果禁用, 将会使用整像素(integer pixels).

 启用请设置值为 1. 默认启用.
 */
#ifndef CC_NODE_RENDER_SUBPIXEL
#define CC_NODE_RENDER_SUBPIXEL 1
#endif

/** @def CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
 如果启用, 使用 SpriteBatchNode 渲染的 Sprite 对象将会以亚像素(subpixels)渲染.
 如果禁用, 将会使用整像素(integer pixels).

 启用请设置值为 1. 默认启用.
 */
#ifndef CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define CC_SPRITEBATCHNODE_RENDER_SUBPIXEL    1
#endif

/** @def CC_TEXTURE_ATLAS_USE_VAO
 默认情况下, TextureAtlas(被很多 cocos2d 类使用)将会使用VAO(Vertex Array Objects).
 苹果公司推荐使用VAO, 不过VAO可能会消耗掉大量内存, 尤其是使用太多VAO的时候.
 所以在某些情况下, 当你需要使用数百个TextureAtlas对象时, 最好关闭这个功能.

 禁用请设置值为 0. 默认启用.
 
 */
#ifndef CC_TEXTURE_ATLAS_USE_VAO
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        #define CC_TEXTURE_ATLAS_USE_VAO 1
    #else
        /* 一些 Windows 显卡驱动程序不支持 VAO. */
        /* 一些 android设备也不能很好的支持 VAO, 所以在android平台上我们默认禁用了此功能. */
        /* Blackberry 也不支持这个功能. */
		#define CC_TEXTURE_ATLAS_USE_VAO 0
    #endif
#endif


/** @def CC_USE_LA88_LABELS
 如果启用, LabelTTF 对象将使用 LA88(Luminance Alpha 16-bit textures);
 如果禁用,将使用A8 (Alpha 8-bit textures).
 LA88 纹理比 A8 快 6%, 但LA88纹理使用了2倍于A8纹理的内存.
 
 这个功能默认启用.

 @since v0.99.5
 */
#ifndef CC_USE_LA88_LABELS
#define CC_USE_LA88_LABELS 1
#endif

/** @def CC_SPRITE_DEBUG_DRAW
 如果启用, 所有 Sprite 的子类都将绘制一个边界框(bounding box).
 仅在调试模式下有用. 推荐保持为禁用状态.

 设置一个非 0 值启用. 默认禁用.
 0 -- disabled
 1 -- draw bounding box // 绘制边界框
 2 -- draw texture box  // 绘制纹理框
*/
#ifndef CC_SPRITE_DEBUG_DRAW
#define CC_SPRITE_DEBUG_DRAW 0
#endif

/** @def CC_SPRITEBATCHNODE_DEBUG_DRAW
 如果启用, 所有渲染使用 SpriteBatchNode 的 Sprite 的子类都将绘制一个边界框(bounding box).
 仅在调试模式下有用. 推荐保持为禁用状态.

 设置一个非 0 值启用. 默认禁用.
*/
#ifndef CC_SPRITEBATCHNODE_DEBUG_DRAW
#define CC_SPRITEBATCHNODE_DEBUG_DRAW 0
#endif

/** @def CC_LABELBMFONT_DEBUG_DRAW
 如果启用, 所有 LabelBMFont 的子类都将绘制一个边界框(bounding box).
 仅在调试模式下有用. 推荐保持为禁用状态.

 设置一个非 0 值启用. 默认禁用.
*/
#ifndef CC_LABELBMFONT_DEBUG_DRAW
#define CC_LABELBMFONT_DEBUG_DRAW 0
#endif

/** @def CC_LABELATLAS_DEBUG_DRAW
 如果启用, 所有 LabeltAtlas 的子类都将绘制一个边界框(bounding box).
 仅在调试模式下有用. 推荐保持为禁用状态.

 设置一个非 0 值启用. 默认禁用.
 */
#ifndef CC_LABELATLAS_DEBUG_DRAW
#define CC_LABELATLAS_DEBUG_DRAW 0
#endif

/** @def CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
 如果启用(和断言一起), 将会验证 Node 对象析构—— node 析构时没有与 EventDispather 联系的 EventListener.
 这个可以用来查出那些问题—— EventDispather 系统含有指向已析构node的悬空指针.

 注意: 当断言被禁用时, 无论此处设置为何值, 构建过程中 EventListener 验证将总是禁用的.
 */
#ifndef CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
#define CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS 0
#endif

/** @def CC_ENABLE_PROFILERS
 如果启用, 将会激活 cocos2d 内各种各样的 profiler(分析工具). 这个统计数据每秒一次输出到控制台, 
 显示执行这些特定程式所需的平均时间(单位: 毫秒).
 仅在调试模式下有用. 推荐保持为禁用状态.

 设置一个非 0 值启用. 默认禁用.
 */
#ifndef CC_ENABLE_PROFILERS
#define CC_ENABLE_PROFILERS 0
#endif

/** 启用 lua 引擎调试日志 */
#ifndef CC_LUA_ENGINE_DEBUG
#define CC_LUA_ENGINE_DEBUG 0
#endif

/** 启用 physics 集成API */
#ifndef CC_USE_PHYSICS
#define CC_USE_PHYSICS 1
#endif

/** 启用脚本绑定 */
#ifndef CC_ENABLE_SCRIPT_BINDING
#define CC_ENABLE_SCRIPT_BINDING 1
#endif

/** @def CC_CONSTRUCTOR_ACCESS
 初始化函数的访问修饰符
 如果值为 protected, 那在这个修饰符下的函数都是 protected 的.
 如果值是 public, 那些函数就是 public 的.
 默认值 protected.
 */
#ifndef CC_CONSTRUCTOR_ACCESS
#define CC_CONSTRUCTOR_ACCESS protected
#endif

#endif // __CCCONFIG_H__
