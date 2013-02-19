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
#include "../ExtensionsTest.h"

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
        CCMenuItemFont* pBackItem = CCMenuItemFont::create("Back", this,
            menu_selector(CCControlScene::toExtensionsMainLayer));
        pBackItem->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        CCMenu* pBackMenu = CCMenu::create(pBackItem, NULL);
        pBackMenu->setPosition( CCPointZero );
        addChild(pBackMenu, 10);

        // Add the generated background
        CCSprite *background = CCSprite::create("extensions/background.png");
        background->setPosition(VisibleRect::center());
        addChild(background);
        
        // Add the ribbon
        CCScale9Sprite *ribbon = CCScale9Sprite::create("extensions/ribbon.png", CCRectMake(1, 1, 48, 55));
        ribbon->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 57));
        ribbon->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y - ribbon->getContentSize().height / 2.0f));
        addChild(ribbon);
        
        // Add the title
        setSceneTitleLabel(CCLabelTTF::create("Title", "Arial", 12));
        m_pSceneTitleLabel->setPosition(ccp (VisibleRect::center().x, VisibleRect::top().y - m_pSceneTitleLabel->getContentSize().height / 2 - 5));
        addChild(m_pSceneTitleLabel, 1);
        
        // Add the menu
        CCMenuItemImage *item1 = CCMenuItemImage::create("Images/b1.png", "Images/b2.png", this, menu_selector(CCControlScene::previousCallback));
        CCMenuItemImage *item2 = CCMenuItemImage::create("Images/r1.png", "Images/r2.png", this, menu_selector(CCControlScene::restartCallback));
        CCMenuItemImage *item3 = CCMenuItemImage::create("Images/f1.png", "Images/f2.png", this, menu_selector(CCControlScene::nextCallback));
        
        CCMenu *menu = CCMenu::create(item1, item3, item2, NULL);
        menu->setPosition(CCPointZero);
        item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
        
        addChild(menu ,1);

        return true;
    }
    return false;
}

void CCControlScene::toExtensionsMainLayer(CCObject* sender)
{
    ExtensionsTestScene* pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void CCControlScene::previousCallback(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(CCControlSceneManager::sharedControlSceneManager()->previousControlScene());
}

void CCControlScene::restartCallback(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(CCControlSceneManager::sharedControlSceneManager()->currentControlScene());
}

void CCControlScene::nextCallback(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(CCControlSceneManager::sharedControlSceneManager()->nextControlScene());
}

