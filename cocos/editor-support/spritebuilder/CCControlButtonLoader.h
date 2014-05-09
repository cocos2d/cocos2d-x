#ifndef _CCB_CCCONTROLBUTTONLOADER_H_
#define _CCB_CCCONTROLBUTTONLOADER_H_

#include "CCControlLoader.h"
#include "extensions//GUI/CCControlExtension/CCControlButton.h"

namespace spritebuilder {

/* Forward declaration. */
class CCBReader;

class ControlButtonLoader : public ControlLoader {
    public:
        /**
         * @js NA
         * @lua NA
         */
        virtual ~ControlButtonLoader() {};
        /**
         * @js NA
         * @lua NA
         */
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ControlButtonLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::extension::ControlButton);

        virtual void onHandlePropTypePosition(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Vector2 pPosition, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCheck(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
        virtual void onHandlePropTypeString(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pString, CCBReader * ccbReader);
        virtual void onHandlePropTypeFontTTF(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader);
        virtual void onHandlePropTypePoint(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Vector2 pPoint, CCBReader * ccbReader);
        virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
        virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
        virtual void onHandlePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color3B pColor3B, CCBReader * ccbReader);
        virtual void onHandlePropTypeColor4(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Color4F pColor4F, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlockControl(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, BlockControlData * pBlockCCControlData, CCBReader * pCCBReader);
};

}

#endif
