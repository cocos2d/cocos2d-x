#include "CCNodeLoaderLibrary.h"

#include "CCLayerLoader.h"
#include "CCLayerColorLoader.h"
#include "CCLayerGradientLoader.h"
#include "CCLabelBMFontLoader.h"
#include "CCLabelTTFLoader.h"
#include "CCSpriteLoader.h"
#include "CCScale9SpriteLoader.h"
#include "CCBFileLoader.h"
#include "CCMenuLoader.h"
#include "CCMenuItemLoader.h"
#include "CCMenuItemImageLoader.h"
#include "CCControlButtonLoader.h"
#include "CCParticleSystemQuadLoader.h"
#include "CCScrollViewLoader.h"



NS_CC_EXT_BEGIN

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
    this->mNodeLoaders.insert(NodeLoaderMapEntry(pClassName, pNodeLoader));
}

void NodeLoaderLibrary::unregisterNodeLoader(const char * pClassName) {
    NodeLoaderMap::iterator ccNodeLoadersIterator = this->mNodeLoaders.find(pClassName);
    if (ccNodeLoadersIterator != this->mNodeLoaders.end())
    {
        ccNodeLoadersIterator->second->release();
        mNodeLoaders.erase(ccNodeLoadersIterator);
    }
    else
    {
        CCLOG("The loader (%s) doesn't exist", pClassName);
    }
}

NodeLoader * NodeLoaderLibrary::getNodeLoader(const char* pClassName) {
    NodeLoaderMap::iterator ccNodeLoadersIterator = this->mNodeLoaders.find(pClassName);
    assert(ccNodeLoadersIterator != this->mNodeLoaders.end());
    return ccNodeLoadersIterator->second;
}

void NodeLoaderLibrary::purge(bool pReleaseNodeLoaders) {
    if(pReleaseNodeLoaders) {
        for(NodeLoaderMap::iterator it = this->mNodeLoaders.begin(); it != this->mNodeLoaders.end(); it++) {
            it->second->release();
        }
    }
    this->mNodeLoaders.clear();
}



static NodeLoaderLibrary * sSharedNodeLoaderLibrary = NULL;

NodeLoaderLibrary * NodeLoaderLibrary::sharedNodeLoaderLibrary() {
    if(sSharedNodeLoaderLibrary == NULL) {
        sSharedNodeLoaderLibrary = new NodeLoaderLibrary();

        sSharedNodeLoaderLibrary->registerDefaultNodeLoaders();
    }
    return sSharedNodeLoaderLibrary;
}

void NodeLoaderLibrary::purgeSharedNodeLoaderLibrary() {
    CC_SAFE_DELETE(sSharedNodeLoaderLibrary);
}

NodeLoaderLibrary * NodeLoaderLibrary::newDefaultNodeLoaderLibrary() {
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::library();
    
    ccNodeLoaderLibrary->registerDefaultNodeLoaders();

    return ccNodeLoaderLibrary;
}

NS_CC_EXT_END