/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 
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

#include "CocosBuilderTest.h"
#include "../../testResource.h"
#include "HelloCocosBuilder/HelloCocosBuilderLayerLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

void CocosBuilderTestScene::runThisTest() {
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("HelloCocosBuilderLayer", HelloCocosBuilderLayerLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    CCNode * node = ccbReader->readNodeGraphFromFile("ccb/HelloCocosBuilder.ccbi", this);
    
    ccbReader->release();

    if(node != NULL) {
        this->addChild(node);
    }

    CCDirector::sharedDirector()->replaceScene(this);
}


//void CocosBuilderTestScene::runThisTest() {
//    CCBIReaderLayer * ccbiReaderLayer = CCBIReaderLayer::node();
//    
//    /* Create an autorelease CCNodeLoaderLibrary. */
//    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    
//    /* Create an autorelease CCBReader. */
//    CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary, ccbiReaderLayer, ccbiReaderLayer);
//    ccbReader->autorelease();
//    
//    /* Read a ccbi file. */
//    CCNode * node = ccbReader->readNodeGraphFromFile("ccb/simple/pub/", "ccb/test.ccbi", ccbiReaderLayer);
//    
//    if(node != NULL) {
//        ccbiReaderLayer->addChild(node);
//    }
//    
//    this->addChild(ccbiReaderLayer);
//    
//    CCDirector::sharedDirector()->replaceScene(this);
//}
