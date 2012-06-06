#ifndef _CCNODE_LOADER_LIBRARY_H_
#define _CCNODE_LOADER_LIBRARY_H_

#include "cocos2d.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

class CC_DLL CCNodeLoaderLibrary : public CCObject {
    private:
        std::map<std::string, CCNodeLoader *> mCCNodeLoaders;

    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCNodeLoaderLibrary, library);

        CCNodeLoaderLibrary();
        ~CCNodeLoaderLibrary();

        void registerDefaultCCNodeLoaders();
        void registerCCNodeLoader(const char * pClassName, CCNodeLoader * pCCNodeLoader);
        void unregisterCCNodeLoader(const char * pClassName);
        CCNodeLoader * getCCNodeLoader(const char * pClassName);
        void purge(bool pDelete);

    public:
        static CCNodeLoaderLibrary * sharedCCNodeLoaderLibrary();
        static CCNodeLoaderLibrary * newDefaultCCNodeLoaderLibrary();
};

NS_CC_EXT_END

#endif
