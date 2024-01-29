/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "editor-support/cocosbuilder/CCNodeLoaderLibrary.h"

#include "editor-support/cocosbuilder/CCLayerLoader.h"
#include "editor-support/cocosbuilder/CCLayerColorLoader.h"
#include "editor-support/cocosbuilder/CCLayerGradientLoader.h"
#include "editor-support/cocosbuilder/CCLabelBMFontLoader.h"
#include "editor-support/cocosbuilder/CCLabelTTFLoader.h"
#include "editor-support/cocosbuilder/CCSpriteLoader.h"
#include "editor-support/cocosbuilder/CCScale9SpriteLoader.h"
#include "editor-support/cocosbuilder/CCBFileLoader.h"
#include "editor-support/cocosbuilder/CCMenuLoader.h"
#include "editor-support/cocosbuilder/CCMenuItemLoader.h"
#include "editor-support/cocosbuilder/CCMenuItemImageLoader.h"
#include "editor-support/cocosbuilder/CCControlButtonLoader.h"
#include "editor-support/cocosbuilder/CCParticleSystemQuadLoader.h"
#include "editor-support/cocosbuilder/CCScrollViewLoader.h"

using namespace cocos2d;

namespace cocosbuilder {

NodeLoaderLibrary::NodeLoaderLibrary() {

}

NodeLoaderLibrary::~NodeLoaderLibrary() {
    this->purge(true);
}

void NodeLoaderLibrary::registerDefaultNodeLoaders() {
    this->registerNodeLoader("CCNode", NodeLoader::loader());
    this->registerNodeLoader("CCLayer", LayerLoader::loader());
    this->registerNodeLoader("CCLayerColor", LayerColorLoader::loader());
    this->registerNodeLoader("CCLayerGradient", LayerGradientLoader::loader());
    this->registerNodeLoader("CCSprite", SpriteLoader::loader());
    this->registerNodeLoader("CCLabelBMFont", LabelBMFontLoader::loader());
    this->registerNodeLoader("CCLabelTTF", LabelTTFLoader::loader());
    this->registerNodeLoader("CCScale9Sprite", Scale9SpriteLoader::loader());
    this->registerNodeLoader("CCScrollView", ScrollViewLoader::loader());
    this->registerNodeLoader("CCBFile", CCBFileLoader::loader());
    this->registerNodeLoader("CCMenu", MenuLoader::loader());
    this->registerNodeLoader("CCMenuItemImage", MenuItemImageLoader::loader());
    this->registerNodeLoader("CCControlButton", ControlButtonLoader::loader());
    this->registerNodeLoader("CCParticleSystemQuad", ParticleSystemQuadLoader::loader());
}

void NodeLoaderLibrary::registerNodeLoader(const char * pClassName, NodeLoader * pNodeLoader) {
    pNodeLoader->retain();
    this->_nodeLoaders.insert(NodeLoaderMapEntry(pClassName, pNodeLoader));
}

void NodeLoaderLibrary::unregisterNodeLoader(const char * pClassName) {
    NodeLoaderMap::iterator ccNodeLoadersIterator = this->_nodeLoaders.find(pClassName);
    if (ccNodeLoadersIterator != this->_nodeLoaders.end())
    {
        ccNodeLoadersIterator->second->release();
        _nodeLoaders.erase(ccNodeLoadersIterator);
    }
    else
    {
        CCLOG("The loader (%s) doesn't exist", pClassName);
    }
}

NodeLoader * NodeLoaderLibrary::getNodeLoader(const char* pClassName) {
    NodeLoaderMap::iterator ccNodeLoadersIterator = this->_nodeLoaders.find(pClassName);
    assert(ccNodeLoadersIterator != this->_nodeLoaders.end());
    return ccNodeLoadersIterator->second;
}

void NodeLoaderLibrary::purge(bool pReleaseNodeLoaders) {
    if(pReleaseNodeLoaders) {
        for(auto& it : this->_nodeLoaders) {
            it.second->release();
        }
    }
    this->_nodeLoaders.clear();
}



static NodeLoaderLibrary * sSharedNodeLoaderLibrary = nullptr;

NodeLoaderLibrary * NodeLoaderLibrary::getInstance() {
    if(sSharedNodeLoaderLibrary == nullptr) {
        sSharedNodeLoaderLibrary = new (std::nothrow) NodeLoaderLibrary();

        sSharedNodeLoaderLibrary->registerDefaultNodeLoaders();
    }
    return sSharedNodeLoaderLibrary;
}

void NodeLoaderLibrary::destroyInstance() {
    CC_SAFE_DELETE(sSharedNodeLoaderLibrary);
}

NodeLoaderLibrary * NodeLoaderLibrary::newDefaultNodeLoaderLibrary() {
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::library();
    
    ccNodeLoaderLibrary->registerDefaultNodeLoaders();

    return ccNodeLoaderLibrary;
}

}
