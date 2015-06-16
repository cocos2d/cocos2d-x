/****************************************************************************
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
#ifndef __CCSPRITEFRAMECACHEHELPER_H__
#define __CCSPRITEFRAMECACHEHELPER_H__

#include "platform/CCPlatformMacros.h"
#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CocosStudioExport.h"
#include <string>
#include <map>
#include <vector>

namespace cocos2d {
    class SpriteFrame;
}

namespace cocostudio {

/**
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL SpriteFrameCacheHelper
{
public:
	/** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static SpriteFrameCacheHelper *sharedSpriteFrameCacheHelper(){ return SpriteFrameCacheHelper::getInstance(); }

    /**
    * @~english Get singleton.
    * @~chinese 获取单例。
    * @return @~english Singleton of `SpriteFrameCacheHelper`.
    * @~chinese 骨骼数据管理器的单例。
    */
    static SpriteFrameCacheHelper *getInstance();

    /**
    * @~english Destory singleton.
    * @~chinese 销毁单例。
    */
    static void purge();
public:

    /**
     * @~english Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name.
     * @~chinese 为CCSpriteFrameCache添加精灵帧，将会保存显示名称及相关图片名称。
     * @param plistPath @~english Path of plist.
     * @~chinese plist路径。
     * @param imagePath @~english Path of image.
     * @~chinese 图片路径。
     */
    void addSpriteFrameFromFile(const std::string& plistPath, const std::string& imagePath);

    /**
    * @~english Remove sprite frame from CCSpriteFrameCache.
    * @~chinese 为CCSpriteFrameCache移除精灵帧。
    * @param plistPath @~english Path of plist.
    * @~chinese plist路径。
    */
    void removeSpriteFrameFromFile(const std::string& plistPath);

private:
    void retainSpriteFrames(const std::string& plistPath);
    void releaseSpriteFrames(const std::string& plistPath);

    SpriteFrameCacheHelper();
    ~SpriteFrameCacheHelper();

    std::map<std::string, std::vector<cocos2d::SpriteFrame*> > _usingSpriteFrames;
    static SpriteFrameCacheHelper *_spriteFrameCacheHelper;
};

}

#endif /*__CCSPRITEFRAMECACHEHELPER_H__*/
