//
//  CCExtTextField.cpp
//  cocos2d_libs
//
//  Created by Kenneth Hurley on 11/28/14.
//
//
#include "CCExtTextField.h"

namespace spritebuilder {
    
ExtTextField* ExtTextField::create() {
    
    ExtTextField *pRet = new (std::nothrow) ExtTextField();
    
    if (pRet != nullptr)
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;

}

bool ExtTextField::init() {
    return EditBox::initWithSizeAndBackgroundSprite(_size, _bgSpriteFrame);
}

}
