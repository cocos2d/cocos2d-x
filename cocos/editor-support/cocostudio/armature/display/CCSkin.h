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

#ifndef __CCSKIN_H__
#define __CCSKIN_H__

#include "cocostudio/armature/utils/CCArmatureDefine.h"
#include "cocostudio/armature/CCBone.h"

namespace cocostudio {

class Skin : public cocos2d::Sprite
{
public:
    static Skin *create();
    static Skin *createWithSpriteFrameName(const char *pszSpriteFrameName);
    static Skin *create(const char *pszFileName);
public:
    Skin();

    bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    bool initWithFile(const char *pszFilename);

    void updateArmatureTransform();
    void updateTransform();

    cocos2d::AffineTransform getNodeToWorldTransform() const;
    cocos2d::AffineTransform getNodeToWorldTransformAR() const;

    CC_PROPERTY_PASS_BY_REF(BaseData, _skinData, SkinData);
    CC_SYNTHESIZE(Bone *, _bone, Bone);

protected:
    cocos2d::AffineTransform _skinTransform;
    CC_SYNTHESIZE_READONLY(std::string, _displayName, DisplayName)
};

}

#endif /*__CCSKIN_H__*/
