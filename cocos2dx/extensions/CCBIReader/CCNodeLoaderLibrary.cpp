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

using namespace cocos2d;
using namespace cocos2d::extension;

CCNodeLoaderLibrary::CCNodeLoaderLibrary() {

}

CCNodeLoaderLibrary::~CCNodeLoaderLibrary() {
    this->purge(true);
}

void CCNodeLoaderLibrary::registerDefaultCCNodeLoaders() {
    this->registerCCNodeLoader("CCNode", CCNodeLoader::loader());
    this->registerCCNodeLoader("CCLayer", CCLayerLoader::loader());
    this->registerCCNodeLoader("CCLayerColor", CCLayerColorLoader::loader());
    this->registerCCNodeLoader("CCLayerGradient", CCLayerGradientLoader::loader());
    this->registerCCNodeLoader("CCSprite", CCSpriteLoader::loader());
    this->registerCCNodeLoader("CCLabelBMFont", CCLabelBMFontLoader::loader());
    this->registerCCNodeLoader("CCLabelTTF", CCLabelTTFLoader::loader());
    this->registerCCNodeLoader("CCScale9Sprite", CCScale9SpriteLoader::loader());
    this->registerCCNodeLoader("CCBFile", CCBFileLoader::loader());
    this->registerCCNodeLoader("CCMenu", CCMenuLoader::loader());
    this->registerCCNodeLoader("CCMenuItemImage", CCMenuItemImageLoader::loader());
    this->registerCCNodeLoader("CCControlButton", CCControlButtonLoader::loader());
    this->registerCCNodeLoader("CCParticleSystemQuad", CCParticleSystemQuadLoader::loader());
}

void CCNodeLoaderLibrary::registerCCNodeLoader(const char * pClassName, CCNodeLoader * pCCNodeLoader) {
    this->mCCNodeLoaders.insert(std::pair<const char *, CCNodeLoader *>(pClassName, pCCNodeLoader));
    pCCNodeLoader->retain();
}

void CCNodeLoaderLibrary::unregisterCCNodeLoader(const char * pClassName) {
    std::map<std::string, CCNodeLoader *>::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
    assert(ccNodeLoadersIterator != this->mCCNodeLoaders.end());
    ccNodeLoadersIterator->second->release();
}

CCNodeLoader * CCNodeLoaderLibrary::getCCNodeLoader(const char * pClassName) {
    std::map<std::string, CCNodeLoader *>::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
    assert(ccNodeLoadersIterator != this->mCCNodeLoaders.end());
    return ccNodeLoadersIterator->second;
}

void CCNodeLoaderLibrary::purge(bool pDelete) {
    if(pDelete) {
        for(std::map<std::string, CCNodeLoader *>::iterator it = this->mCCNodeLoaders.begin(); it != this->mCCNodeLoaders.end(); it++) {
            it->second->release();
        }
    }
    this->mCCNodeLoaders.clear();
}



static CCNodeLoaderLibrary * sSharedCCNodeLoaderLibrary = NULL;

CCNodeLoaderLibrary * CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() {
    if(sSharedCCNodeLoaderLibrary == NULL) {
        sSharedCCNodeLoaderLibrary = new CCNodeLoaderLibrary();

        sSharedCCNodeLoaderLibrary->registerDefaultCCNodeLoaders();
    }
    return sSharedCCNodeLoaderLibrary;
}

void CCNodeLoaderLibrary::purgeSharedCCNodeLoaderLibrary() {
    CC_SAFE_DELETE(sSharedCCNodeLoaderLibrary);
}

CCNodeLoaderLibrary * CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary() {
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::library();

    ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();

    return ccNodeLoaderLibrary;
}