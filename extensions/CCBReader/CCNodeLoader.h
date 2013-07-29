#ifndef _CCB_CCNODELOADER_H_
#define _CCB_CCNODELOADER_H_

#include "../GUI/CCControlExtension/CCInvocation.h"
#include "cocos2d.h"
#include "CCBReader.h"
#include "CCBValue.h"
#include "../GUI/CCControlExtension/CCControl.h"

NS_CC_EXT_BEGIN

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

#define CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createNode(cocos2d::Node * pParent, cocos2d::extension::CCBReader * ccbReader) { \
    return T::create(); \
}

#define CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createNode(cocos2d::Node * pParent, cocos2d::extension::CCBReader * ccbReader) = 0

struct BlockData {
    SEL_MenuHandler mSELMenuHandler;
    Object * _target;
};

struct BlockControlData {
    Control::Handler mSELControlHandler;
    Object * _target;
    Control::EventType mControlEvents;
};

/* Forward declaration. */
class CCBReader;

class NodeLoader : public Object {
    public:
        NodeLoader();
        virtual ~NodeLoader();
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(NodeLoader, loader);

        virtual Node * loadNode(Node *, CCBReader * ccbReader);
        virtual void parseProperties(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual Dictionary* getCustomProperties();
    
    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Node);

        virtual Point parsePropTypePosition(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual Point parsePropTypePoint(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual Point parsePropTypePointLock(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual Size parsePropTypeSize(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual float * parsePropTypeScaleLock(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual float parsePropTypeFloat(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual float parsePropTypeDegrees(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual float parsePropTypeFloatScale(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual int parsePropTypeInteger(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual int parsePropTypeIntegerLabeled(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual float * parsePropTypeFloatVar(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual bool parsePropTypeCheck(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual SpriteFrame * parsePropTypeSpriteFrame(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual Animation * parsePropTypeAnimation(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual Texture2D * parsePropTypeTexture(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual unsigned char parsePropTypeByte(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual Color3B parsePropTypeColor3(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName);
        virtual Color4F * parsePropTypeColor4FVar(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual bool * parsePropTypeFlip(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual BlendFunc parsePropTypeBlendFunc(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual std::string parsePropTypeFntFile(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual std::string parsePropTypeString(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual std::string parsePropTypeText(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual std::string parsePropTypeFontTTF(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual BlockData * parsePropTypeBlock(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual BlockControlData * parsePropTypeBlockControl(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual Node * parsePropTypeCCBFile(Node * pNode, Node * pParent, CCBReader * ccbReader);
        virtual float * parsePropTypeFloatXY(Node * pNode, Node * pParent, CCBReader * ccbReader);


        virtual void onHandlePropTypePosition(Node * pNode, Node * pParent, const char* pPropertyName, Point pPosition, CCBReader * ccbReader);
        virtual void onHandlePropTypePoint(Node * pNode, Node * pParent, const char* pPropertyName, Point pPoint, CCBReader * ccbReader);
        virtual void onHandlePropTypePointLock(Node * pNode, Node * pParent, const char* pPropertyName, Point pPointLock, CCBReader * ccbReader);
        virtual void onHandlePropTypeSize(Node * pNode, Node * pParent, const char* pPropertyName, Size pSize, CCBReader * ccbReader);
        virtual void onHandlePropTypeScaleLock(Node * pNode, Node * pParent, const char* pPropertyName, float * pScaleLock, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloat(Node * pNode, Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader);
        virtual void onHandlePropTypeDegrees(Node * pNode, Node * pParent, const char* pPropertyName, float pDegrees, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader);
        virtual void onHandlePropTypeInteger(Node * pNode, Node * pParent, const char* pPropertyName, int pInteger, CCBReader * ccbReader);
        virtual void onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloatVar(Node * pNode, Node * pParent, const char* pPropertyName, float * pFoatVar, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloatXY(Node * pNode, Node * pParent, const char* pPropertyName, float * pFoatVar, CCBReader * ccbReader);

        virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char* pPropertyName, bool pCheck, CCBReader * ccbReader);
        virtual void onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char* pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
        virtual void onHandlePropTypeAnimation(Node * pNode, Node * pParent, const char* pPropertyName, Animation * pAnimation, CCBReader * ccbReader);
        virtual void onHandlePropTypeTexture(Node * pNode, Node * pParent, const char* pPropertyName, Texture2D * pTexture2D, CCBReader * ccbReader);
        virtual void onHandlePropTypeByte(Node * pNode, Node * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * ccbReader);
        virtual void onHandlePropTypeColor3(Node * pNode, Node * pParent, const char* pPropertyName, Color3B pColor3B, CCBReader * ccbReader);
        virtual void onHandlePropTypeColor4FVar(Node * pNode, Node * pParent, const char* pPropertyName, Color4F * pColor4FVar, CCBReader * ccbReader);
        virtual void onHandlePropTypeFlip(Node * pNode, Node * pParent, const char* pPropertyName, bool * pFlip, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char* pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader);
        virtual void onHandlePropTypeFntFile(Node * pNode, Node * pParent, const char* pPropertyName, const char * pFntFile, CCBReader * ccbReader);
        virtual void onHandlePropTypeString(Node * pNode, Node * pParent, const char* pPropertyName, const char * pString, CCBReader * ccbReader);
        virtual void onHandlePropTypeText(Node * pNode, Node * pParent, const char* pPropertyName, const char * pText, CCBReader * ccbReader);
        virtual void onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char* pPropertyName, const char * pFontTTF, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlock(Node * pNode, Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char* pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader);
        virtual void onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char* pPropertyName, Node * pCCBFileNode, CCBReader * ccbReader);

protected:
        Dictionary* _customProperties;
};

NS_CC_EXT_END

#endif
