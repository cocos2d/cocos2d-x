#ifndef _CCB_CCNODELOADERLIBRARY_H_
#define _CCB_CCNODELOADERLIBRARY_H_

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
        void registerCCNodeLoader(std::string pClassName, CCNodeLoader * pCCNodeLoader);
        void unregisterCCNodeLoader(std::string pClassName);
        CCNodeLoader * getCCNodeLoader(std::string pClassName);
        void purge(bool pDelete);

    public:
        static CCNodeLoaderLibrary * sharedCCNodeLoaderLibrary();
        static void purgeSharedCCNodeLoaderLibrary();

        static CCNodeLoaderLibrary * newDefaultCCNodeLoaderLibrary();
};

NS_CC_EXT_END

#endif
