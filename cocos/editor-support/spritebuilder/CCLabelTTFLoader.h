#ifndef _CCB_CCLABELTTFLOADER_H_
#define _CCB_CCLABELTTFLOADER_H_

#include "CCRef.h"
#include "CCLabel.h"

#include "CCNodeLoader.h"

namespace spritebuilder {

/* Forward declaration. */
class CCBReader;

class LabelTTFLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelTTFLoader() {};
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LabelTTFLoader, loader);

protected:
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::Label);

    virtual void onHandlePropTypeColor4(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color4F pColor4F, CCBReader * ccbReader);
    virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader);
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader);
    virtual void onHandlePropTypeFontTTF(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader);
    virtual void onHandlePropTypeText(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pText, CCBReader * ccbReader);
    virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader);
    virtual void onHandlePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader);
    virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
    virtual void onHandlePropTypePosition(cocos2d::Node * pNode,cocos2d:: Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * ccbReader);
    virtual void onDone(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);    
private:
    cocos2d::Size _shadowOffset;
    float _shadowBlurRadius;
    cocos2d::Color4B _shadowColor;
    
    cocos2d::Color4B _outlineColor;
    float _outlineWidth;
};

}

#endif
