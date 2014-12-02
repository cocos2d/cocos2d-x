/*
 *
 * Copyright (c) 2014 Nguyen Thai Duong
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __cocos2d_libs__CCSliderLoader__
#define __cocos2d_libs__CCSliderLoader__

#include "CCControlLoader.h"
#include "extensions/cocos-ext.h"


namespace spritebuilder {
    
    /* Forward declaration. */
    class CCBReader;
    
    class SliderLoader : public ControlLoader{
    public:
        /**
         * @js NA
         * @lua NA
         */
        virtual ~SliderLoader() {};
        SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SliderLoader, loader);
        
    protected:
        virtual cocos2d::extension::ControlSlider * createNode(cocos2d::Node * pParent, CCBReader * ccbReader) {
            auto pRet = cocos2d::extension::ControlSlider::create(cocos2d::Sprite::create(), cocos2d::Sprite::create(), cocos2d::Sprite::create());
            
            return pRet;
        }
        
        virtual void onHandlePropTypeBlock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * ccbReader);
        
        virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
        virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
        virtual void onDone(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlockControl(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader);

        /*
        virtual void onHandlePropTypeCheck(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);*/
    protected:
        cocos2d::SpriteFrame* _progressSprite;
        cocos2d::SpriteFrame* _backgroundSprite;
        cocos2d::SpriteFrame* _handleSprite;
        cocos2d::SpriteFrame* _selectedHandleSprite;
        cocos2d::Size         _contentSize;
    };
    
}
#endif /* defined(__cocos2d_libs__CCSliderLoader__) */
