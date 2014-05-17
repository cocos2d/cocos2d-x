
#ifndef __CCSPRIT3DDATA_CACHE_H__
#define __CCSPRIT3DDATA_CACHE_H__

#include <string>
#include <unordered_map>
#include "base/ccTypes.h"
#include "base/CCMap.h"

NS_CC_BEGIN

class Sprite3D;
class Mesh;
class EventListenerCustom;
class EventCustom;
class Texture2D;

class Sprite3DDataCache
{
public:
    struct Sprite3DData
    {
        Mesh* mesh;
        std::string texture;
    };
    
    static Sprite3DDataCache* getInstance();
    static void purgeMeshCache();
    
    bool addSprite3D(const std::string& fileName, Mesh* mesh, const std::string& texture);
    
    Mesh* getSprite3DMesh(const std::string& fileName);
    
    Texture2D* getSprite3DTexture(const std::string& fileName);
    
    void removeAllSprite3DData();
    void removeUnusedSprite3DData();

    
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     void listenBackToForeground(EventCustom* event);
 #endif
    
protected:
    Sprite3DDataCache();
    
    ~Sprite3DDataCache();
    
    static Sprite3DDataCache* _cacheInstance;

    std::unordered_map<std::string, Sprite3DData> _sprite3DDatas; //sprites 
    
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     EventListenerCustom* _backToForegroundlistener;
 #endif
};

NS_CC_END

#endif // __CCSPRIT3DDATA_CACHE_H__
