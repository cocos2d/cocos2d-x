
#include "CCSprite3DDataCache.h"
#include "CCMesh.h"
#include "2d/platform/CCFileUtils.h"
#include "2d/CCTextureCache.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

Sprite3DDataCache* Sprite3DDataCache::_cacheInstance = nullptr;

Sprite3DDataCache::Sprite3DDataCache()
{
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     // listen the event when app go to foreground
     _backToForegroundlistener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(Sprite3DDataCache::listenBackToForeground, this));
     Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundlistener, -1);
 #endif
}

Sprite3DDataCache::~Sprite3DDataCache()
{
    removeAllSprite3DData();
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundlistener);
 #endif
}

Sprite3DDataCache* Sprite3DDataCache::getInstance()
{
    if (! _cacheInstance)
    {
        _cacheInstance = new Sprite3DDataCache();
    }
    
    return _cacheInstance;
}

void Sprite3DDataCache::purgeMeshCache()
{
    if (_cacheInstance)
    {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

bool Sprite3DDataCache::addSprite3D(const std::string& fileName, Mesh* mesh, const std::string& texture)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto itr = _sprite3DDatas.find(fullPath);
    if (itr == _sprite3DDatas.end())
    {
        Sprite3DData data;
        data.mesh = mesh;
        CC_SAFE_RETAIN(mesh);
        data.texture = texture;
        _sprite3DDatas[fullPath] = data;
        return true;
    }
    return false;
}

Mesh* Sprite3DDataCache::getSprite3DMesh(const std::string& fileName)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto itr = _sprite3DDatas.find(fullPath);
    if (itr != _sprite3DDatas.end())
        return itr->second.mesh;
    return nullptr;
}

Texture2D* Sprite3DDataCache::getSprite3DTexture(const std::string& fileName)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto itr = _sprite3DDatas.find(fullPath);
    if (itr != _sprite3DDatas.end())
    {
        auto cache = Director::getInstance()->getTextureCache();
        return cache->addImage(itr->second.texture);
    }
    return nullptr;
}

void Sprite3DDataCache::removeAllSprite3DData()
{
    for (auto itr = _sprite3DDatas.begin(); itr != _sprite3DDatas.end(); itr++) {
        CC_SAFE_RELEASE_NULL(itr->second.mesh);
    }
    _sprite3DDatas.clear();
}
void Sprite3DDataCache::removeUnusedSprite3DData()
{
    for( auto it=_sprite3DDatas.cbegin(); it!=_sprite3DDatas.cend(); /* nothing */) {
        auto value = it->second;
        if( value.mesh->getReferenceCount() == 1 ) {
            CCLOG("cocos2d: GLProgramStateCache: removing unused GLProgramState");
            
            value.mesh->release();
            _sprite3DDatas.erase(it++);
        } else {
            ++it;
        }
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void Sprite3DDataCache::listenBackToForeground(EventCustom* event)
{
    for (auto iter = _sprite3DDatas.begin(); iter != _sprite3DDatas.end(); ++iter)
    {
        auto mesh = iter->second.mesh;
        mesh->restore();
    }
}
#endif

NS_CC_END
