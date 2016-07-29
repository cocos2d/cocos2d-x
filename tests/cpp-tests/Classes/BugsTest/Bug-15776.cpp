//
//  Bug-15776.cpp
//  cocos2d_tests
//
//  Created by Ricardo Quesada on 6/17/16.
//
//

#include "Bug-15776.h"


USING_NS_CC;

bool Bug15776Layer::init()
{
    if (BugsTestBase::init())
    {
        cocos2d::Image *cocos2dxImage = new cocos2d::Image();
        cocos2dxImage->initWithImageData(nullptr, 0);
        // should not crash. invalid cocos2dImage
        auto texture2d = Director::getInstance()->getTextureCache()->addImage(cocos2dxImage, "unused");
        return texture2d;
    }

    return false;
}
