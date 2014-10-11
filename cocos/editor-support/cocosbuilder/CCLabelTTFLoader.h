#ifndef _CCB_CCLABELTTFLOADER_H_
#define _CCB_CCLABELTTFLOADER_H_

#include "base/CCRef.h"
#include "2d/CCLabel.h"

#include "CCNodeLoader.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class CC_DLL LabelTTFLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelTTFLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LabelTTFLoader, loader);

protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::Label);

    virtual void onHandlePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color3B pColor3B, CCBReader * ccbReader);
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader);
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader);
    virtual void onHandlePropTypeFontTTF(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader);
    virtual void onHandlePropTypeText(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pText, CCBReader * ccbReader);
    virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader);
    virtual void onHandlePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader);
    virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
};

}

#endif
