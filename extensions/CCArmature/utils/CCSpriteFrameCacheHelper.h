/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCArmatureDefine.h"
#include <stack>

using namespace std;

namespace cocos2d { namespace extension { namespace armature {

class  SpriteFrameCacheHelper
{
public:
    static SpriteFrameCacheHelper *sharedSpriteFrameCacheHelper();

    static void purgeSpriteFrameCacheHelper();
public:

    /**
     *	@brief	Add sprite frame to SpriteFrameCache, it will save display name and it's relative image name
     *
     */
    void addSpriteFrameFromFile(const char *plistPath, const char *imagePath);

    void addSpriteFrameFromDict(Dictionary *dictionary, Texture2D *pobTexture, const char *imagePath);

    /**
     * Get this display in which image
     */
    const char *getDisplayImagePath(const char *displayName);
    TextureAtlas *getTextureAtlas(const char *displayName);

private:
    SpriteFrameCacheHelper();
    ~SpriteFrameCacheHelper();

    std::map<std::string, std::string> _display2ImageMap;
    Dictionary *_display2TextureAtlas;

    static SpriteFrameCacheHelper *s_SpriteFrameCacheHelper;
};

}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCSPRITEFRAMECACHEHELPER_H__*/
