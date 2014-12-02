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

#include "CCSliderLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|Normal"
#define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|Highlighted"
#define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|Disabled"

#define PROPERTY_HANDLESPRITEFRAME_NORMAL "handleSpriteFrame|Normal"
#define PROPERTY_HANDLESPRITEFRAME_HIGHLIGHTED "handleSpriteFrame|Highlighted"
#define PROPERTY_HANDLESPRITEFRAME_DISABLED "handleSpriteFrame|Disabled"
#define PROPERTY_BLOCK     "block"

namespace spritebuilder {
    void SliderLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader) {

        if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
            ((Control *)pNode)->addTargetWithActionForControlEvents(pBlockControlData->_target, pBlockControlData->mSELControlHandler, Control::EventType::VALUE_CHANGED);
        } else {
            ControlLoader::onHandlePropTypeBlockControl(pNode, pParent, pPropertyName, pBlockControlData, ccbReader);
        }
    }
    void SliderLoader::onHandlePropTypeBlock(Node * pNode, Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * ccbReader) {
        if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
            ((ControlSlider*)pNode)->addTargetWithActionForControlEvents(pBlockData->_target, (Control::Handler)pBlockData->mSELMenuHandler, Control::EventType::VALUE_CHANGED);
        } else {
            NodeLoader::onHandlePropTypeBlock(pNode, pParent, pPropertyName, pBlockData, ccbReader);
        }
    }
    void SliderLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char* pPropertyName, Size pSize, CCBReader * ccbReader) {
        if(strcmp(pPropertyName, "preferredSize") == 0) {
            _contentSize = pSize;
        } else {
            NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
        }
    }
    
    void SliderLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char* pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
        if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
            if(pSpriteFrame != NULL) {
                //((Slider *)pNode)->loadSlidBallTextureNormal(pSpriteFrame, Control::State::NORMAL);
                //((ControlSlider*)pNode)->setBackgroundSprite(CCSprite::createWithSpriteFrame(pSpriteFrame));
                //((ControlSlider*)pNode)->setProgressSprite(CCSprite::createWithSpriteFrame(pSpriteFrame));
                //this->_progressSprite = pSpriteFrame;
                this->_backgroundSprite = pSpriteFrame;
                _backgroundSprite->retain();
            }
        } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
            if(pSpriteFrame != NULL) {
                //((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::HIGH_LIGHTED);
            }
        } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
            if(pSpriteFrame != NULL) {
                //((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::DISABLED);
            }
        } else if(strcmp(pPropertyName, PROPERTY_HANDLESPRITEFRAME_NORMAL) == 0) {
            if(pSpriteFrame != NULL) {
                this->_handleSprite = pSpriteFrame;
                _handleSprite->retain();
            }
        } else if(strcmp(pPropertyName, PROPERTY_HANDLESPRITEFRAME_HIGHLIGHTED) == 0) {
            if(pSpriteFrame != NULL) {
                this->_selectedHandleSprite = pSpriteFrame;
                _selectedHandleSprite->retain();
            }
        } else if(strcmp(pPropertyName, PROPERTY_HANDLESPRITEFRAME_DISABLED) == 0) {
            if(pSpriteFrame != NULL) {
                //((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::DISABLED);
            }
        } else {
            NodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
        }
    }

    void SliderLoader::onDone(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader) {
        Scale9Sprite* background = Scale9Sprite::createWithSpriteFrame(this->_backgroundSprite);
        background->setContentSize(_contentSize);

        Sprite* progressSprite = Sprite::create();
        progressSprite->setContentSize(_contentSize);
        progressSprite->addChild(background);
        background->setAnchorPoint(Point(0.0, 0.5));
        
        Sprite* sprite = Sprite::create();
        sprite->setContentSize(_contentSize);
        sprite->setAnchorPoint(Point(0.0, 0.0));
        
        ((ControlSlider*)pNode)->setContentSize(_contentSize);

        
        if (_selectedHandleSprite)
            ((ControlSlider *)pNode)->initWithSprites(sprite,
                                                  progressSprite,
                                                  Sprite::createWithSpriteFrame(this->_handleSprite),
                                                  Sprite::createWithSpriteFrame(this->_selectedHandleSprite));
        else
            ((ControlSlider *)pNode)->initWithSprites(sprite,
                                                      progressSprite,
                                                      Sprite::createWithSpriteFrame(this->_handleSprite));
        
        
        ((ControlSlider*)pNode)->setAnchorPoint(Point(0.0, 0.25));
        
        _backgroundSprite->release();
        _handleSprite->release();
        if (_selectedHandleSprite)
            _selectedHandleSprite->release();

    }
}

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif