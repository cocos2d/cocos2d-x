/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2012 XiaoLong Zhang, Chukong Inc.
 
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

#include <iostream>
#include "HelloCocosBuilder.h"

using namespace cocos2d ;

IMPLEMENT_RUNTIME(HelloCocosBuilder)

CCSprite* HelloCocosBuilder::sprtBurst =NULL;
CCSprite* HelloCocosBuilder::sprtIcon = NULL ;

void HelloCocosBuilder::didLoadFromCCB()
{
    CCLOG("loading.....successed!") ;
    void* act = CCRotateBy::actionWithDuration(0.5f, 10) ;
    void* act1 = CCRepeatForever::actionWithAction((CCActionInterval*)act) ;
    sprtBurst->runAction((CCAction*)act1) ;
}

void HelloCocosBuilder::menuCallBack(CCObject *sender)
{
    int tag = ((CCMenuItemImage*)sender)->getTag() ;
    switch (tag) {
        case 100:
            // distribute msgs，@1.msg name  @2. param
            //CALLBACKMETHOD(pressedButton, sender)
            pressedButton(sender) ;
            break;
        case 101:
            //CALLBACKMETHOD(pressedButton2, sender)
            pressedButton2(sender) ;
        default:
            break;
    }
}

void HelloCocosBuilder::pressedButton(CCObject*sender) 
{
    sprtIcon->stopAllActions() ;
    void*rotAction = CCRotateBy::actionWithDuration(1, 360) ;
    sprtIcon->runAction((CCAction*)rotAction) ;
}

void HelloCocosBuilder::pressedButton2(CCObject*sender) 
{
    CCLOG("pressed successed!") ;
}