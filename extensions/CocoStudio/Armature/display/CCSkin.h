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

#include "../utils/CCArmatureDefine.h"
#include "../CCBone.h"

NS_CC_EXT_BEGIN
/**
 *  @lua NA
 */
class CC_EX_DLL CCSkin : public CCSprite
{
public:
    static CCSkin *create();
    static CCSkin *createWithSpriteFrameName(const char *pszSpriteFrameName);
    static CCSkin *create(const char *pszFileName);
public:
    /**
     *  @js ctor
     */
    CCSkin();

    bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    bool initWithFile(const char *pszFilename);

    void updateArmatureTransform();
    void updateTransform();

    CCAffineTransform nodeToWorldTransform();
    CCAffineTransform nodeToWorldTransformAR();

    CC_PROPERTY_PASS_BY_REF(CCBaseData, m_sSkinData, SkinData);
    CC_PROPERTY(CCBone *, m_pBone, Bone);

protected:
    CCArmature *m_pArmature;
    CCAffineTransform m_tSkinTransform;
    CC_SYNTHESIZE_READONLY(std::string, m_strDisplayName, DisplayName)
};

NS_CC_EXT_END

#endif /*__CCSKIN_H__*/
