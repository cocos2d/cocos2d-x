/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
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

#include "HelloWorldAppDelegate.h"

using namespace cocos2d;

class MyLayer : public CCLayer {
public:
    bool init()
    {
        if (! CCLayer::init())
        {
            return false;
        }
		
        this->setIsTouchEnabled(true);
		
        return true;
    }
	
    void ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent)
    {
        CCDirector::sharedDirector()->end();
    }
	
    LAYER_NODE_FUNC(MyLayer);
};

HelloWorld::HelloWorld()
{
}

bool HelloWorld::applicationDidFinishLaunching()
{
    // init director
    CCDirector::sharedDirector()->setOpenGLView(new CCXEGLView());
    CCDirector::sharedDirector()->setDisplayFPS(true);
	
    // load image texture and get window size
    CCTexture2D *pTextrue = CCTextureCache::sharedTextureCache()->addImage("helloworld.png");
    CGSize size = CCDirector::sharedDirector()->getWinSize();
	
    // create sprite instance
    CCSprite *pSprite = CCSprite::spriteWithTexture(pTextrue);
    pSprite->setPosition(CGPoint(size.width / 2, size.height / 2));
	
    // create layer instance
    CCLayer *pLayer = MyLayer::node();
    pLayer->addChild(pSprite);
	
    // create scene and add layer to scene
    CCScene *pScene = CCScene::node();
    pScene->addChild(pLayer);
	
    // add scene to director
    CCDirector::sharedDirector()->runWithScene(pScene);
	
    return true;
}
