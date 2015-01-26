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
 * @addtogroup sprite_nodes
 * @{
 */

/** Singleton that manages the Animations.
It saves in a cache the animations. You should use this class if you want to save your animations in a cache.

Before v0.99.5, the recommend way was to save them on the Sprite. Since v0.99.5, you should use this class instead.

@since v0.99.5
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
    /** Returns the shared instance of the Animation cache */
    static AnimationCache* getInstance();

    /** Purges the cache. It releases all the Animation objects and the shared instance.
     */
    static void destroyInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static AnimationCache* sharedAnimationCache() { return AnimationCache::getInstance(); }

    /** @deprecated Use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedAnimationCache() { return AnimationCache::destroyInstance(); }

    bool init(void);

    /** Adds a Animation with a name.
    */
    void addAnimation(Animation *animation, const std::string& name);

    /** Deletes a Animation from the cache.
     
     */
    void removeAnimation(const std::string& name);
    /** @deprecated. Use removeAnimation() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void removeAnimationByName(const std::string& name){ removeAnimation(name);}

    /** Returns a Animation that was previously added.
    If the name is not found it will return nil.
    You should retain the returned copy if you are going to use it.
    */
    Animation* getAnimation(const std::string& name);
    /**
     @deprecated. Use getAnimation() instead
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE Animation* animationByName(const std::string& name){ return getAnimation(name); }

    /** Adds an animation from an NSDictionary
     Make sure that the frames were previously loaded in the SpriteFrameCache.
     @param plist The path of the relative file,it use to find the plist path for load SpriteFrames.
     @since v1.1
     */
    void addAnimationsWithDictionary(const ValueMap& dictionary,const std::string& plist);

    /** Adds an animation from a plist file.
     Make sure that the frames were previously loaded in the SpriteFrameCache.
     @since v1.1
     * @js addAnimations
     * @lua addAnimations
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
