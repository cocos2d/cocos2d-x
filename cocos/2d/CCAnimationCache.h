/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
CopyRight (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __CC_ANIMATION_CACHE_H__
#define __CC_ANIMATION_CACHE_H__

#include "base/CCRef.h"
#include "base/CCMap.h"
#include "base/CCValue.h"
#include "2d/CCAnimation.h"

#include <string>

NS_CC_BEGIN


class Animation;

/**
 * @addtogroup _2d
 * @{
 */

/** @~english Singleton that manages the Animations.
It saves in a cache the animations. You should use this class if you want to save your animations in a cache.

Before v0.99.5, the recommend way was to save them on the Sprite. Since v0.99.5, you should use this class instead.

 * @~chinese 管理动画的单例。
 * 它用于缓存的动画。如果你想在缓存中保存你的动画，你应该使用这个类。
 * 
 * v0.99.5之前,推荐的方法是在Sprite保存它们。从v0.99.5后,你应该使用这个类来替代之前的做法。
 * 
@since v0.99.5
@js cc.animationCache
*/
class CC_DLL AnimationCache : public Ref
{
public:
    /**
     * @js ctor
     */
    AnimationCache();
    /**
     * @js NA
     * @lua NA
     */
    ~AnimationCache();
    /** @~english Returns the shared instance of the Animation cache 
     * @~chinese 返回动画缓存的共享实例
	 @js NA
	*/
    static AnimationCache* getInstance();

    /** @~english Purges the cache. It releases all the Animation objects and the shared instance.
     * @~chinese 清除缓存。它会释放所有的动画对象和共享实例。
		@js NA
     */
    static void destroyInstance();

    /** @deprecated Use getInstance() instead. */
    CC_DEPRECATED_ATTRIBUTE static AnimationCache* sharedAnimationCache() { return AnimationCache::getInstance(); }

    /** @deprecated Use destroyInstance() instead. */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedAnimationCache() { return AnimationCache::destroyInstance(); }

    bool init(void);

    /** @~english Adds a Animation with a name.
     *
     * @~chinese 通过名字和动画添加到缓存。
     * 
     * @param animation @~english An animation.
     * @~chinese 指定动画。
     * @param name @~english The name of animation.
     * @~chinese 动画的名字。
     */
    void addAnimation(Animation *animation, const std::string& name);

    /** @~english Deletes a Animation from the cache.
     *
     * @~chinese 从缓存中删除一个动画。
     * 
     * @param name @~english The name of animation.
     * @~chinese 动画的名字。
     */
    void removeAnimation(const std::string& name);
    /** @deprecated. Use removeAnimation() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void removeAnimationByName(const std::string& name){ removeAnimation(name);}

    /** @~english Returns a Animation that was previously added.
     * If the name is not found it will return nil.
     * You should retain the returned copy if you are going to use it.
     *
     * @~chinese 返回一个之前添加的动画。
     * 如果没有找到它将返回空。
     * 如果你要使用它，你应该retain返回的这个拷贝。
     * 
     * @return @~english A Animation that was previously added. If the name is not found it will return nil.
     * @~chinese 一个之前添加的动画。如果没有找到这个名字它将返回空。
     */
    Animation* getAnimation(const std::string& name);
    /**
     * @deprecated. Use getAnimation() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Animation* animationByName(const std::string& name){ return getAnimation(name); }

    /** @~english Adds an animation from an VaulueMap.
     * Make sure that the frames were previously loaded in the SpriteFrameCache.
     * @~chinese 从NSDictionary添加一个动画。
     * 确保SpriteFrameCache的帧在之前就加载过了。
     * @param dictionary @~english An ValueMap.
     * @~chinese 一个指定的ValueMap。
     * @param plist @~english The path of the relative file,it use to find the plist path for load SpriteFrames.
     * @~chinese 相对的文件路径,它将找到的plist路径来加载SpriteFrames。
     * @since v1.1
	 @js NA
     */
    void addAnimationsWithDictionary(const ValueMap& dictionary,const std::string& plist);

    /** @~english Adds an animation from a plist file.
     * Make sure that the frames were previously loaded in the SpriteFrameCache.
     * @~chinese 从plist文件添加一个动画。
     * 确保SpriteFrameCache的帧在之前就加载过了。
     * @since v1.1
     * @js addAnimations
     * @lua addAnimations
     * @param plist @~english An animation from a plist file.
     * @~chinese 一个动画的plist文件。
     */
    void addAnimationsWithFile(const std::string& plist);

private:
    void parseVersion1(const ValueMap& animations);
    void parseVersion2(const ValueMap& animations);

private:
    Map<std::string, Animation*> _animations;
    static AnimationCache* s_sharedAnimationCache;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CC_ANIMATION_CACHE_H__
