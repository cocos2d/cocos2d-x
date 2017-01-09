//
//  SpriteBuilder.cpp
//  cocos2d_libs
//
//  Created by Sergey on 28.10.14.
//
//

#include "SpriteBuilder.h"
#include <set>

#include "CCBXParser.h"
#include "CCBXNodeLoaderLibrary.h"
#include "CCBXNodeLoaderCache.h"
#include "CCBXNodeLoader.h"
#include "base/CCDirector.h"
#include "CCBXReaderParams.h"

NS_CC_BEGIN

namespace spritebuilder {
    
float CCBXReader::_resolutionScale = 1.0f;
Map<std::string,CCBReaderParams*> CCBXReader::_paramsMap;
Map<std::string,CCBXReader*> CCBXReader::_cache;
bool CCBXReader::_playSound = true;
    
CCBXReader* CCBXReader::addToCache(const std::string &pCCBFileName, const std::string &rootPath, const NodeLoaderLibrary *library, NodeLoaderCache *cache)
{
    CCBXReader* reader = CCBXReader::createFromFile(pCCBFileName, rootPath, library, cache);
    if(reader)
        _cache.insert(pCCBFileName, reader);
    return reader;
}

bool CCBXReader::removeFromCache(const std::string &pCCBFileName)
{
    auto it = _cache.find(pCCBFileName);
    if(it!=_cache.end())
    {
        _cache.erase(it);
        return true;
    }
    return false;
}
    
void CCBXReader::clearCache()
{
    _cache.clear();
}
    
void CCBXReader::setPlaySound(bool value)
{
    _playSound = value;
}
    
bool CCBXReader::getPlaySound()
{
    return _playSound;
}
    
CCBXReader* CCBXReader::createFromFile(const std::string &pCCBFileName, const std::string &rootPath, const NodeLoaderLibrary *library, NodeLoaderCache *cache)
{
    auto it = _cache.find(pCCBFileName);
    if(it!=_cache.end())
    {
        return it->second;
    }
    CCBReaderParams* params = createParams(rootPath);
    if(!params)
        return nullptr;
    
    if(!library)
        library = NodeLoaderLibrary::getDefault();
    
    if(!cache)
        cache = NodeLoaderCache::create();
    
    NodeLoader * loader = ParseCCBXFile(pCCBFileName, *library, *cache, rootPath, params);
    if(!loader)
        return nullptr;
    CCBXReader *ret = new CCBXReader(rootPath, params, loader);
    ret->autorelease();
    return ret;
}
    
CCBXReader* CCBXReader::createFromData(const Data &data, const std::string &rootPath, const NodeLoaderLibrary *library, NodeLoaderCache *cache)
{
    CCBReaderParams* params = createParams(rootPath);
    if(!params)
        return nullptr;
    
    if(!library)
        library = NodeLoaderLibrary::getDefault();
    
    if(!cache)
        cache = NodeLoaderCache::create();
    
    NodeLoader * loader = ParseCCBXData(data, *library, *cache, rootPath, params);
    if(!loader)
        return nullptr;
    CCBXReader *ret = new CCBXReader(rootPath, params, loader);
    ret->autorelease();
    return ret;
}
    
void CCBXReader::calcScales(SceneScaleType scaleType, const Size &parentSize, const Size &designResolution, float designScale, float &mainScale, float &additionalScale)
{
    assert(scaleType != SceneScaleType::DEFAULT); // not possible to calc scales for default scaleType
    if(scaleType == SceneScaleType::NONE)
    {
        mainScale = 1.0f;
        additionalScale = 1.0f;
    }
    else if(scaleType == SceneScaleType::CUSTOM)
    {
        //do nothing
    }
    else
    {
        float resolutionAspectX = parentSize.width / getResolutionScale();
        float resolutionAspectY = parentSize.height / getResolutionScale();
        
        float designAspectX = designResolution.width / designScale;
        float designAspectY = designResolution.height / designScale;
        
        if(scaleType == SceneScaleType::MINSCALE)
        {
            float mainScale1 = resolutionAspectX / designAspectX;
            float mainScale2 = resolutionAspectY / designAspectY;
            if(mainScale1<mainScale2)
            {
                mainScale = mainScale1;
                additionalScale = mainScale2/mainScale1;
            }
            else
            {
                mainScale = mainScale2;
                additionalScale = mainScale1/mainScale2;
            }
        }
        else if(scaleType == SceneScaleType::MAXSCALE)
        {
            float mainScale1 = resolutionAspectX / designAspectX;
            float mainScale2 = resolutionAspectY / designAspectY;
            if(mainScale1>mainScale2)
            {
                mainScale = mainScale1;
                additionalScale = mainScale2/mainScale1;
            }
            else
            {
                mainScale = mainScale2;
                additionalScale = mainScale1/mainScale2;
            }
        }
        
        else if((designResolution.width>designResolution.height)==(scaleType == SceneScaleType::MINSIZE))
        {
            mainScale = resolutionAspectY / designAspectY;
            additionalScale = (resolutionAspectX/mainScale)/designAspectX;
        }
        else
        {
            mainScale = resolutionAspectX / designAspectX;
            additionalScale = (resolutionAspectY/mainScale)/designAspectY;
        }
    }
}
    
void CCBXReader::calcScales(SceneScaleType scaleType, const Size &parentSize, float &mainScale, float &additionalScale) const
{
    CCBXReader::calcScales(scaleType == SceneScaleType::DEFAULT?_params->getDefaultSceneScaleType():scaleType, parentSize, _params->getDesignResolution(), _params->getDesignResolutionScale(), mainScale, additionalScale);
}

    
Node *CCBXReader::createNode(CCBXReaderOwner *pOwner, SceneScaleType scaleType, const CreateNodeFunction &createNodeFunction, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    return createNode(pOwner, Director::getInstance()->getWinSize(), Director::getInstance()->getWinSize(), scaleType, createNodeFunction, defaultAnimationCallback);
}
    
Node *CCBXReader::createNode(CCBXReaderOwner *pOwner, float mainScale, float additionalScale, const CreateNodeFunction &createNodeFunction, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    return createNode(pOwner, Director::getInstance()->getWinSize(), mainScale, additionalScale, createNodeFunction, defaultAnimationCallback);
}
    
Node *CCBXReader::createNode(CCBXReaderOwner *pOwner, const Size& parentSize, SceneScaleType scaleType, const CreateNodeFunction &createNodeFunction, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    return createNode(pOwner, parentSize, Director::getInstance()->getWinSize(), scaleType, createNodeFunction, defaultAnimationCallback);
}
    
Node *CCBXReader::createNode(CCBXReaderOwner *pOwner, const Size& parentSize, const Size& screenSize, SceneScaleType scaleType, const CreateNodeFunction &createNodeFunction, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    float mainScale = 1.0f;
    float additionalScale = 1.0f;
    calcScales(scaleType, screenSize, mainScale, additionalScale);
    Node * ret = _rootNodeLoader->createNode(parentSize, mainScale, additionalScale, pOwner, nullptr, nullptr, nullptr, createNodeFunction, defaultAnimationCallback);
    return ret;
}

Node *CCBXReader::createNode(CCBXReaderOwner *pOwner, const Size& parentSize, float mainScale, float additionalScale, const CreateNodeFunction &createNodeFunction, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    Node * ret = _rootNodeLoader->createNode(parentSize, mainScale, additionalScale, pOwner, nullptr, nullptr, nullptr, createNodeFunction, defaultAnimationCallback);
    return ret;
}
    
bool CCBXReader::loadNode(Node * node, CCBXReaderOwner *pOwner, SceneScaleType scaleType, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    return loadNode(node, pOwner, Director::getInstance()->getWinSize(), Director::getInstance()->getWinSize(), scaleType, defaultAnimationCallback);
}

bool CCBXReader::loadNode(Node * node, CCBXReaderOwner *pOwner, float mainScale, float additionalScale, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    return loadNode(node, pOwner, Director::getInstance()->getWinSize(), mainScale, additionalScale, defaultAnimationCallback);
}
    
bool CCBXReader::loadNode(Node * node, CCBXReaderOwner *pOwner, const Size& parentSize, SceneScaleType scaleType, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    return loadNode(node, pOwner, parentSize, Director::getInstance()->getWinSize(), scaleType, defaultAnimationCallback);
}
    
bool CCBXReader::loadNode(Node * node, CCBXReaderOwner *pOwner, const Size& parentSize, const Size& screenSize, SceneScaleType scaleType, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    float mainScale = 1.0f;
    float additionalScale = 1.0f;
    calcScales(scaleType, screenSize, mainScale, additionalScale);
    return _rootNodeLoader->loadNode(node, parentSize, mainScale, additionalScale, pOwner, nullptr, nullptr, nullptr, defaultAnimationCallback);
}

bool CCBXReader::loadNode(Node * node, CCBXReaderOwner *pOwner, const Size& parentSize, float mainScale, float additionalScale, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback) const
{
    return _rootNodeLoader->loadNode(node, parentSize, mainScale, additionalScale, pOwner, nullptr, nullptr, nullptr, defaultAnimationCallback);
}


float CCBXReader::getResolutionScale()
{
    return _resolutionScale;
}
void CCBXReader::setResolutionScale(float scale)
{
    _resolutionScale = scale;
}
    
const std::string& CCBXReader::getRootPath()
{
    return _rootPath;
}
    
CCBReaderParams* CCBXReader::getParams() const
{
    return _params;
}
    
CCBReaderParams* CCBXReader::createParams(const std::string &rootPath)
{
    auto it = _paramsMap.find(rootPath);
    if(it != _paramsMap.end())
        return it->second;
    CCBReaderParams* ret = CCBReaderParams::create(rootPath);
    if(ret)
    {
        _paramsMap.insert(rootPath, ret);
    }
    return ret;
}

CCBXReader::CCBXReader(const std::string &rootPath, CCBReaderParams *params, NodeLoader *rootNodeLoader)
    :_rootPath(rootPath)
    ,_params(params)
    ,_rootNodeLoader(rootNodeLoader)
{
    _rootNodeLoader->retain();
}
CCBXReader::~CCBXReader()
{
    _rootNodeLoader->release();
}

}

NS_CC_END
