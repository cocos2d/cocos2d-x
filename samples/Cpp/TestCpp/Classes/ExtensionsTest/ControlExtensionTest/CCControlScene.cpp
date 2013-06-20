/*
 * ControlScene.m
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

ControlScene::ControlScene()
: _sceneTitleLabel(NULL)
{

}

ControlScene::~ControlScene()
{
    CC_SAFE_RELEASE_NULL(_sceneTitleLabel);
}

bool ControlScene::init()
{
    if (Layer::init())
    {    
        MenuItemFont* pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(ControlScene::toExtensionsMainLayer, this));
        pBackItem->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        Menu* pBackMenu = Menu::create(pBackItem, NULL);
        pBackMenu->setPosition( PointZero );
        addChild(pBackMenu, 10);

        // Add the generated background
        Sprite *background = Sprite::create("extensions/background.png");
        background->setPosition(VisibleRect::center());
        addChild(background);
        
        // Add the ribbon
        Scale9Sprite *ribbon = Scale9Sprite::create("extensions/ribbon.png", CCRectMake(1, 1, 48, 55));
        ribbon->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 57));
        ribbon->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y - ribbon->getContentSize().height / 2.0f));
        addChild(ribbon);
        
        // Add the title
        setSceneTitleLabel(LabelTTF::create("Title", "Arial", 12));
        _sceneTitleLabel->setPosition(ccp (VisibleRect::center().x, VisibleRect::top().y - _sceneTitleLabel->getContentSize().height / 2 - 5));
        addChild(_sceneTitleLabel, 1);
        
        // Add the menu
        MenuItemImage *item1 = MenuItemImage::create("Images/b1.png", "Images/b2.png", CC_CALLBACK_1(ControlScene::previousCallback, this));
        MenuItemImage *item2 = MenuItemImage::create("Images/r1.png", "Images/r2.png", CC_CALLBACK_1(ControlScene::restartCallback, this));
        MenuItemImage *item3 = MenuItemImage::create("Images/f1.png", "Images/f2.png", CC_CALLBACK_1(ControlScene::nextCallback, this));
        
        Menu *menu = Menu::create(item1, item3, item2, NULL);
        menu->setPosition(PointZero);
        item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
        item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
        
        addChild(menu ,1);

        return true;
    }
    return false;
}

void ControlScene::toExtensionsMainLayer(Object* sender)
{
    ExtensionsTestScene* pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void ControlScene::previousCallback(Object* sender)
{
    Director::sharedDirector()->replaceScene(ControlSceneManager::sharedControlSceneManager()->previousControlScene());
}

void ControlScene::restartCallback(Object* sender)
{
    Director::sharedDirector()->replaceScene(ControlSceneManager::sharedControlSceneManager()->currentControlScene());
}

void ControlScene::nextCallback(Object* sender)
{
    Director::sharedDirector()->replaceScene(ControlSceneManager::sharedControlSceneManager()->nextControlScene());
}

