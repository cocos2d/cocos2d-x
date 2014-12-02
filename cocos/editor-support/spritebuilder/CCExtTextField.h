//
//  CCExtTextField.h
//  cocos2d_libs
//
//  Created by Kenneth Hurley on 11/28/14.
//
//

#ifndef SB_CCEXTTEXTFIELD_H
#define SB_CCEXTTEXTFIELD_H

#include "ui/UIEditBox/UIEditBox.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"

using namespace cocos2d;
using namespace cocos2d::ui;

namespace spritebuilder {
    
    class ExtTextField : public cocos2d::ui::EditBox {
        
    public:
        ExtTextField(): EditBox(), _target(NULL), mSELControlHandler(NULL),_size(0,0),_bgSpriteFrame(NULL) {
            setFontName("Helvetica");
            setFontColor(cocos2d::Color3B::BLACK);
        }
        
        /**
         * create a uninited edit box.
         * @return An autorelease pointer of ExtTextFiled, you don't need to release it only if you retain it again.
         */
        static ExtTextField* create();
        
        
        virtual void editBoxReturn(cocos2d::ui::EditBox* editBox) {
            if (_target && mSELControlHandler)
                (_target->*mSELControlHandler)(this, cocos2d::extension::Control::EventType::DRAG_EXIT);
        }
        
        void setTargetSelector(Ref* target, cocos2d::extension::Control::Handler handler) {
            _target = target;
            mSELControlHandler = handler;
        }
        
        void setBackgroundSpriteFrame(SpriteFrame * pSpriteFrame) {
            _bgSpriteFrame = Scale9Sprite::createWithSpriteFrame(pSpriteFrame);
        }
        
        void setPreferredSize(Size pSize) {
            _size = pSize;
        }
        
    CC_CONSTRUCTOR_ACCESS:
        virtual bool init() override;
        
    private:
        Ref* _target;
        cocos2d::extension::Control::Handler mSELControlHandler;
        cocos2d::Size _size;
        Scale9Sprite *_bgSpriteFrame;
    };
    
    

}

#endif  // #ifndef SB_CCEXTTEXTFIELD_H
