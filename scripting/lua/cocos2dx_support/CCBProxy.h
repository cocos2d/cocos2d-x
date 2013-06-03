#ifndef __CCBPROXY_H_
#define __CCBPROXY_H_

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCBProxy : public CCLayer{
public:
    CCBProxy() { }
    virtual ~ CCBProxy(){ }
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBProxy, create);
    CCBReader* createCCBreader();
    CCNode* readCCBFromFile(const char *pszFileName,CCBReader* pCCBReader,bool bSetOwner = false);
    const char* getNodeTypeName(CCNode* pNode);
    void setCallback(CCNode* pNode,int nHandle);
};

class CCBLayerLoader:public CCLayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBLayerLoader, loader);
};

#endif // __CCBPROXY_H_
