#ifndef _CCB_CCLABELBMFONTLOADER_H_
#define _CCB_CCLABELBMFONTLOADER_H_

#include "base/CCRef.h"
#include "2d/CCLabel.h"

#include "editor-support/cocosbuilder/CCNodeLoader.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class CC_DLL LabelBMFontLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelBMFontLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LabelBMFontLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::Label);

    virtual void onHandlePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color3B pColor3B, CCBReader * ccbReader);
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader);
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader);
    virtual void onHandlePropTypeFntFile(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char* pFntFile, CCBReader * ccbReader);
    virtual void onHandlePropTypeText(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char* pText, CCBReader * ccbReader);
};

}

#endif
