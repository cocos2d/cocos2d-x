#ifndef _CCB_CCNODELOADERLIBRARY_H_
#define _CCB_CCNODELOADERLIBRARY_H_

#include "cocos2d.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

class NodeLoader;

typedef std::map<std::string, NodeLoader *> NodeLoaderMap;
typedef std::pair<std::string, NodeLoader *> NodeLoaderMapEntry;

class NodeLoaderLibrary : public Object
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(NodeLoaderLibrary, library);

    NodeLoaderLibrary();
    virtual ~NodeLoaderLibrary();

    void registerDefaultNodeLoaders();
    void registerNodeLoader(const char * pClassName, NodeLoader * pNodeLoader);
    //void registerNodeLoader(String * pClassName, NodeLoader * pNodeLoader);
    void unregisterNodeLoader(const char * pClassName);
    //void unregisterNodeLoader(String * pClassName);
    NodeLoader * getNodeLoader(const char * pClassName);
    //CCNodeLoader * getNodeLoader(String * pClassName);
    void purge(bool pDelete);

    CC_DEPRECATED_ATTRIBUTE void registerDefaultCCNodeLoaders() { registerDefaultNodeLoaders(); }
    CC_DEPRECATED_ATTRIBUTE void registerCCNodeLoader(const char * pClassName, NodeLoader * pNodeLoader) { registerNodeLoader(pClassName, pNodeLoader); };
    CC_DEPRECATED_ATTRIBUTE void unregisterCCNodeLoader(const char * pClassName) { unregisterNodeLoader(pClassName); };
    CC_DEPRECATED_ATTRIBUTE NodeLoader * getCCNodeLoader(const char * pClassName) { return getNodeLoader(pClassName); };
    
public:
    static NodeLoaderLibrary * getInstance();
    static void destroyInstance();

    static NodeLoaderLibrary * newDefaultNodeLoaderLibrary();

    CC_DEPRECATED_ATTRIBUTE static NodeLoaderLibrary * sharedNodeLoaderLibrary() { return NodeLoaderLibrary::getInstance(); };
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedNodeLoaderLibrary() { NodeLoaderLibrary::destroyInstance(); };
        
    CC_DEPRECATED_ATTRIBUTE static NodeLoaderLibrary * newDefaultCCNodeLoaderLibrary() { return NodeLoaderLibrary::newDefaultNodeLoaderLibrary(); };
    
private:
    NodeLoaderMap _nodeLoaders;
};

NS_CC_EXT_END

#endif
