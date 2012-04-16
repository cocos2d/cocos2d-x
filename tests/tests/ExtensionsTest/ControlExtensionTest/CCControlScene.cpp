/*
 * CCControlScene.m
 *
 * Copyright (c) 2011 Yannick Loriot
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
 *
 */

#include "CCControlScene.h"

#include "CCControlSceneManager.h"


CCControlScene::CCControlScene()
: m_pSceneTitleLabel(NULL)
{

}

CCControlScene::~CCControlScene()
{
    CC_SAFE_RELEASE_NULL(m_pSceneTitleLabel);
}

bool CCControlScene::init()
{
    if (CCLayer::init())
    {    
        // Get the sceensize
        CCSize screensize = CCDirector::sharedDirector()->getWinSize();

        // Add the generated background
        CCSprite *background = CCSprite spriteWithFile("background.png");
        background->setPosition(ccp(screensize.width / 2, screensize.height / 2));
        addChild(background);
        
        // Add the ribbon
        CCScale9Sprite *ribbon = CCScale9Sprite::spriteWithFile("ribbon.png", CCRectMake(1, 1, 48, 55));
        ribbon->setContentSize(CCSizeMake(screensize.width, 57));
        ribbon->setPosition(ccp(screensize.width / 2.0f, screensize.height - ribbon->getContentSize().height / 2.0f));
        addChild(ribbon);
        
        // Add the title
        setSceneTitleLabel(CCLabelTTF::labelWithString("Title", "Arial", 12));
        m_pSceneTitleLabel->setPosition(ccp (screensize.width / 2, screensize.height - m_pSceneTitleLabel->getContentSize().height / 2 - 5)];
        addChild(m_pSceneTitleLabel, 1);
        
        // Add the menu
		CCMenuItemImage *item1 = CCMenuItemImage::itemWithNormalImage("b1.png", "b2.png", this, menu_selector(CCControlScene::previousCallback)));
		CCMenuItemImage *item2 = CCMenuItemImage::itemWithNormalImage("r1.png", "r2.png", this, menu_selector(CCControlScene::restartCallback)));
		CCMenuItemImage *item3 = CCMenuItemImage::itemWithNormalImage("f1.png", "f2.png", this, menu_selector(CCControlScene::nextCallback)));
        
        CCMenu *menu = CCMenu::menuWithItems(item1, item3, item2, NULL);
        menu->setPosition(CCPointZero);
		item1 setPosition(ccp(screensize.width / 2 - 100, 37));
		item2 setPosition(ccp(screensize.width / 2, 35));
		item3 setPosition(ccp(screensize.width / 2 + 100, 37));
        
		addChild(menu ,1);
        return true;
    }
    return false;
}

void CCControlScene::previousCallback(CCNode* sender)
{
    CCDirector::sharedDirector()->replaceScene(CCControlSceneManager::sharedControlSceneManager()->previousControlScene());
}

void CCControlScene::restartCallback(CCNode* sender)
{
    CCDirector::sharedDirector()->replaceScene(CCControlSceneManager::sharedControlSceneManager()->currentControlScene());

}

void CCControlScene::nextCallback(CCNode* sender)
{
    CCDirector::sharedDirector()->replaceScene(CCControlSceneManager::sharedControlSceneManager()->nextControlScene());
}

