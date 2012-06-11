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

#include "HelloCocosBuilder.h"

USING_NS_CC;

HelloCocosBuilder::HelloCocosBuilder()
:m_pSpriteBurst(NULL)
,m_pSpriteIcon(NULL)
{
}

HelloCocosBuilder::~HelloCocosBuilder()
{
    CC_SAFE_RELEASE_NULL(m_pSpriteBurst);
    CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
}

bool HelloCocosBuilder::callbackSetChildren(const char* name, CCObject* node)
{
    bool bRetVal = false;
    
    if (strcmp(name, "sprtBurst") == 0)
    {
        m_pSpriteBurst = dynamic_cast<CCSprite*>(node);
        CC_ASSERT(m_pSpriteBurst);
        m_pSpriteBurst->retain();
    }
    else if (strcmp(name, "sprtIcon") == 0)
    {
        m_pSpriteIcon = dynamic_cast<CCSprite*>(node);
        CC_ASSERT(m_pSpriteIcon);
        m_pSpriteIcon->retain();
    }
    
    return bRetVal;
};

void HelloCocosBuilder::callbackAfterCCBLoaded()
{
    CCLOG("loading.....successed!") ;
    void* act = CCRotateBy::actionWithDuration(0.5f, 10) ;
    void* act1 = CCRepeatForever::actionWithAction((CCActionInterval*)act) ;
    m_pSpriteBurst->runAction((CCAction*)act1) ;
}

SEL_MenuHandler HelloCocosBuilder::callbackGetSelectors(const char* selectorName)
{
    if (strcmp(selectorName, "pressedButton") == 0)
    {
        return menu_selector(HelloCocosBuilder::pressedButton);
    }
    else if (strcmp(selectorName, "pressedButton2") == 0)
    {
        return menu_selector(HelloCocosBuilder::pressedButton2);
    }
    else
    {
        return NULL;
    }
}

void HelloCocosBuilder::pressedButton(CCObject*sender) 
{
    m_pSpriteIcon->stopAllActions() ;
    void* rotateAction = CCRotateBy::actionWithDuration(1, 360) ;
    m_pSpriteIcon->runAction((CCAction*)rotateAction) ;
}

void HelloCocosBuilder::pressedButton2(CCObject*sender) 
{
    CCLOG("pressed successed!") ;
}