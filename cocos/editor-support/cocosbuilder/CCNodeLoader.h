#ifndef _CCB_CCNODELOADER_H_
#define _CCB_CCNODELOADER_H_

#include "extensions/GUI/CCControlExtension/CCInvocation.h"
#include "CCBReader.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"

namespace cocosbuilder {

#define PROPERTY_POSITION "position"
#define PROPERTY_CONTENTSIZE "contentSize"
#define PROPERTY_SKEW "skew"
#define PROPERTY_ANCHORPOINT "anchorPoint"
#define PROPERTY_SCALE "scale"
#define PROPERTY_ROTATION "rotation"
#define PROPERTY_ROTATIONX "rotationX"
#define PROPERTY_ROTATIONY "rotationY"
#define PROPERTY_TAG "tag"
#define PROPERTY_IGNOREANCHORPOINTFORPOSITION "ignoreAnchorPointForPosition"
#define PROPERTY_VISIBLE "visible"

#define ASSERT_FAIL_UNEXPECTED_PROPERTY(PROPERTY) cocos2d::log("Unexpected property: '%s'!\n", PROPERTY); assert(false)
#define ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(PROPERTYTYPE) cocos2d::log("Unexpected property type: '%d'!\n", PROPERTYTYPE); assert(false)

#define CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * ccbReader) { \
    return T::create(); \
}

#define CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * ccbReader) = 0

struct BlockData {
    cocos2d::SEL_MenuHandler mSELMenuHandler;
    cocos2d::Object * _target;
};

struct BlockControlData {
    cocos2d::extension::Control::Handler mSELControlHandler;
    cocos2d::Object * _target;
    cocos2d::extension::Control::EventType mControlEvents;
};

/* Forward declaration. */
class CCBReader;

class NodeLoader : public cocos2d::Object {
    public:
        /**
         * @js NA
         * @lua NA
         */
        NodeLoader();
        /**
         * @js NA
         * @lua NA
         */
        virtual ~NodeLoader();
        /**
         * @js NA
         * @lua NA
         */
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(NodeLoader, loader);
        /**
         * @js NA
         * @lua NA
         */
        virtual cocos2d::Node * loadNode(cocos2d::Node *, CCBReader * ccbReader);
        /**
         * @js NA
         * @lua NA
         */
        virtual void parseProperties(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        /**
         * @js NA
         * @lua NA
         */
        virtual cocos2d::ValueMap& getCustomProperties();
    
    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::Node);

        virtual cocos2d::Point parsePropTypePosition(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual cocos2d::Point parsePropTypePoint(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual cocos2d::Point parsePropTypePointLock(cocos2d::Node * pNode,cocos2d:: Node * pParent, CCBReader * ccbReader);
        virtual cocos2d::Size parsePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual float * parsePropTypeScaleLock(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual float parsePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual float parsePropTypeDegrees(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual float parsePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual int parsePropTypeInteger(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual int parsePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual float * parsePropTypeFloatVar(cocos2d::Node * pNode,cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual bool parsePropTypeCheck(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual cocos2d::SpriteFrame * parsePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual cocos2d::Animation * parsePropTypeAnimation(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual cocos2d::Texture2D * parsePropTypeTexture(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual unsigned char parsePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual cocos2d::Color3B parsePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual cocos2d::Color4F * parsePropTypeColor4FVar(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual bool * parsePropTypeFlip(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual cocos2d::BlendFunc parsePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual std::string parsePropTypeFntFile(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual std::string parsePropTypeString(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual std::string parsePropTypeText(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual std::string parsePropTypeFontTTF(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual BlockData * parsePropTypeBlock(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual BlockControlData * parsePropTypeBlockControl(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual cocos2d::Node * parsePropTypeCCBFile(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);
        virtual float * parsePropTypeFloatXY(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader);


        virtual void onHandlePropTypePosition(cocos2d::Node * pNode,cocos2d:: Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * ccbReader);
        virtual void onHandlePropTypePoint(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Point pPoint, CCBReader * ccbReader);
        virtual void onHandlePropTypePointLock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Point pPointLock, CCBReader * ccbReader);
        virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
        virtual void onHandlePropTypeScaleLock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float * pScaleLock, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader);
        virtual void onHandlePropTypeDegrees(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pDegrees, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader);
        virtual void onHandlePropTypeInteger(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, int pInteger, CCBReader * ccbReader);
        virtual void onHandlePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloatVar(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float * pFoatVar, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloatXY(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float * pFoatVar, CCBReader * ccbReader);

        virtual void onHandlePropTypeCheck(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, bool pCheck, CCBReader * ccbReader);
        virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
        virtual void onHandlePropTypeAnimation(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Animation * pAnimation, CCBReader * ccbReader);
        virtual void onHandlePropTypeTexture(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Texture2D * pTexture2D, CCBReader * ccbReader);
        virtual void onHandlePropTypeByte(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * ccbReader);
        virtual void onHandlePropTypeColor3(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Color3B pColor3B, CCBReader * ccbReader);
        virtual void onHandlePropTypeColor4FVar(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Color4F * pColor4FVar, CCBReader * ccbReader);
        virtual void onHandlePropTypeFlip(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, bool * pFlip, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader);
        virtual void onHandlePropTypeFntFile(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, const char * pFntFile, CCBReader * ccbReader);
        virtual void onHandlePropTypeString(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, const char * pString, CCBReader * ccbReader);
        virtual void onHandlePropTypeText(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, const char * pText, CCBReader * ccbReader);
        virtual void onHandlePropTypeFontTTF(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, const char * pFontTTF, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlockControl(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader);
        virtual void onHandlePropTypeCCBFile(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Node * pCCBFileNode, CCBReader * ccbReader);

protected:
        cocos2d::ValueMap _customProperties;
};

}

#endif
