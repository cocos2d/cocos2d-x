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

    static SpriteFrameCacheHelper *getInstance();

    static void purge();
public:

    /**
     *	@brief	Add sprite frame to CCSpriteFrameCache, it will save display name and it's relative image name
     */
    void addSpriteFrameFromFile(const std::string& plistPath, const std::string& imagePath);
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
