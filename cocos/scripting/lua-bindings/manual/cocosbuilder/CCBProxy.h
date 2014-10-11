#ifndef __CCBPROXY_H_
#define __CCBPROXY_H_

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;


class CCBProxy : public Layer{
public:
    CCBProxy() { }
    virtual ~ CCBProxy(){ }
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBProxy, create);
    CCBReader* createCCBReader();
    Node* readCCBFromFile(const char *pszFileName,CCBReader* pCCBReader,bool bSetOwner = false);
    const char* getNodeTypeName(Node* pNode);
    void setCallback(Node* node,int handle, int controlEvents = 0);
};

class CCBLayerLoader:public LayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBLayerLoader, loader);
};

#endif // __CCBPROXY_H_
