/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef _CCB_CCPARTICLESYSTEMQUADLOADER_H_
#define _CCB_CCPARTICLESYSTEMQUADLOADER_H_

#include "base/CCRef.h"
#include "2d/CCParticleSystemQuad.h"

#include "editor-support/cocosbuilder/CCNodeLoader.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class CC_DLL ParticleSystemQuadLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSystemQuadLoader() {};
    /**
     * @js NA
     * @lua NA
     */
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(cocosbuilder::ParticleSystemQuadLoader, loader);

protected:
    /**
     * @js NA
     * @lua NA
     */
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::ParticleSystemQuad);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypePoint(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Vec2 pPoint, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloat, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeInteger(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, int pInteger, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeFloatVar(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float * pFloatVar, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeColor4FVar(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color4F * pColor4FVar, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeTexture(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Texture2D * pTexture2D, CCBReader * ccbReader);
};

}

#endif
