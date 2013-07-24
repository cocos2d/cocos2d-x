#ifndef _CCB_CCNODELOADERLIBRARY_H_
#define _CCB_CCNODELOADERLIBRARY_H_

#include "cocos2d.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

class NodeLoader;

typedef std::map<std::string, NodeLoader *> NodeLoaderMap;
typedef std::pair<std::string, NodeLoader *> NodeLoaderMapEntry;

class NodeLoaderLibrary : public Object {
    private:
        NodeLoaderMap mNodeLoaders;

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

    public:
        static NodeLoaderLibrary * sharedNodeLoaderLibrary();
        static void purgeSharedNodeLoaderLibrary();

        static NodeLoaderLibrary * newDefaultNodeLoaderLibrary();
};

NS_CC_EXT_END

#endif
