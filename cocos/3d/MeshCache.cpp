#include "MeshCache.h"
#include "Mesh.h"
#include "cocos2d.h"
//#include "MeshMaterial.h"

NS_CC_BEGIN


typedef std::map<std::string, Mesh*>::iterator MeshMapIter;

MeshCache* MeshCache::_cacheInstance = nullptr;

MeshCache::MeshCache()
{
    _cachedMeshes.clear();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // listen the event when app go to foreground
    _backToForegroundlistener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(MeshCache::listenBackToForeground, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundlistener, -1);
#endif
}

MeshCache::~MeshCache()
{
    for (auto iter = _cachedMeshes.begin(); iter != _cachedMeshes.end(); ++iter) {
        CC_SAFE_DELETE(iter->second);
    }
    _cachedMeshes.clear();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundlistener);
#endif
}

MeshCache* MeshCache::getInstance()
{
    if (! _cacheInstance) {
        _cacheInstance = new MeshCache();
    }
    
    return _cacheInstance;
}

void MeshCache::purgeMeshCache()
{
    if (_cacheInstance) {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

bool MeshCache::addMesh(const std::string& fileName, Mesh* mesh)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto it = _cachedMeshes.find(fullPath);
    if (it == _cachedMeshes.end())
    {
        _cachedMeshes[fullPath] = mesh;
        return true;
    }
    return false;
}

Mesh* MeshCache::getMesh(const std::string& fileName)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto it = _cachedMeshes.find(fullPath);
    if (it != _cachedMeshes.end())
        return it->second;
    
    return nullptr;
}
void MeshCache::removeMesh(const std::string& fileName)
{
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto it = _cachedMeshes.find(fullPath);
    if (it != _cachedMeshes.end()) {
        CC_SAFE_DELETE(it->second);
        _cachedMeshes.erase(it);
    }
}

void MeshCache::removeMesh(const Mesh* mesh)
{
    auto it = _cachedMeshes.begin();
    for (; it != _cachedMeshes.end(); it++) {
        if (it->second == mesh)
        {
            _cachedMeshes.erase(it);
            return;
        }
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MeshCache::listenBackToForeground(EventCustom* event)
{
    for (auto iter = _cachedMeshes.begin(); iter != _cachedMeshes.end(); ++iter) {
        Mesh* mesh = iter->second;
        mesh->restore();
    }
    
    VertexDeclaration::restoreAllVertexDecl();
}
#endif

NS_CC_END
