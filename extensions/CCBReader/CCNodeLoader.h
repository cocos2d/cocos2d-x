#ifndef _CCB_CCNODELOADER_H_
#define _CCB_CCNODELOADER_H_

#include "../GUI/CCControlExtension/CCInvocation.h"
#include "cocos2d.h"
#include "CCBReader.h"
#include "CCBValue.h"

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

#define ASSERT_FAIL_UNEXPECTED_PROPERTY(PROPERTY) CCLog("Unexpected property: '%s'!\n", PROPERTY); assert(false)
#define ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(PROPERTYTYPE) CCLog("Unexpected property type: '%d'!\n", PROPERTYTYPE); assert(false)

#define CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createNode(cocos2d::Node * pParent, cocos2d::extension::CCBReader * pCCBReader) { \
    return T::create(); \
}

#define CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createNode(cocos2d::Node * pParent, cocos2d::extension::CCBReader * pCCBReader) = 0

struct BlockData {
    SEL_MenuHandler mSELMenuHandler;
    Object * mTarget;
};

struct BlockControlData {
    SEL_CCControlHandler mSELControlHandler;
    Object * mTarget;
    int mControlEvents;
};

/* Forward declaration. */
class CCBReader;

class NodeLoader : public Object {
    public:
        NodeLoader();
        virtual ~NodeLoader();
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(NodeLoader, loader);

        virtual Node * loadNode(Node *, CCBReader * pCCBReader);
        virtual void parseProperties(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual Dictionary* getCustomProperties();
    
    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Node);

        virtual Point parsePropTypePosition(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual Point parsePropTypePoint(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual Point parsePropTypePointLock(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual Size parsePropTypeSize(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual float * parsePropTypeScaleLock(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual float parsePropTypeFloat(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual float parsePropTypeDegrees(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual float parsePropTypeFloatScale(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual int parsePropTypeInteger(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual int parsePropTypeIntegerLabeled(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual float * parsePropTypeFloatVar(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual bool parsePropTypeCheck(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual SpriteFrame * parsePropTypeSpriteFrame(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual Animation * parsePropTypeAnimation(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual Texture2D * parsePropTypeTexture(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual unsigned char parsePropTypeByte(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual ccColor3B parsePropTypeColor3(Node * pNode, Node * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual ccColor4F * parsePropTypeColor4FVar(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual bool * parsePropTypeFlip(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual ccBlendFunc parsePropTypeBlendFunc(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual std::string parsePropTypeFntFile(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual std::string parsePropTypeString(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual std::string parsePropTypeText(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual std::string parsePropTypeFontTTF(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual BlockData * parsePropTypeBlock(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual BlockControlData * parsePropTypeBlockControl(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual Node * parsePropTypeCCBFile(Node * pNode, Node * pParent, CCBReader * pCCBReader);
        virtual float * parsePropTypeFloatXY(Node * pNode, Node * pParent, CCBReader * pCCBReader);


        virtual void onHandlePropTypePosition(Node * pNode, Node * pParent, const char* pPropertyName, Point pPosition, CCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(Node * pNode, Node * pParent, const char* pPropertyName, Point pPoint, CCBReader * pCCBReader);
        virtual void onHandlePropTypePointLock(Node * pNode, Node * pParent, const char* pPropertyName, Point pPointLock, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(Node * pNode, Node * pParent, const char* pPropertyName, Size pSize, CCBReader * pCCBReader);
        virtual void onHandlePropTypeScaleLock(Node * pNode, Node * pParent, const char* pPropertyName, float * pScaleLock, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(Node * pNode, Node * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
        virtual void onHandlePropTypeDegrees(Node * pNode, Node * pParent, const char* pPropertyName, float pDegrees, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * pCCBReader);
        virtual void onHandlePropTypeInteger(Node * pNode, Node * pParent, const char* pPropertyName, int pInteger, CCBReader * pCCBReader);
        virtual void onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatVar(Node * pNode, Node * pParent, const char* pPropertyName, float * pFoatVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatXY(Node * pNode, Node * pParent, const char* pPropertyName, float * pFoatVar, CCBReader * pCCBReader);

        virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char* pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * pCCBReader);
        virtual void onHandlePropTypeAnimation(Node * pNode, Node * pParent, const char* pPropertyName, Animation * pAnimation, CCBReader * pCCBReader);
        virtual void onHandlePropTypeTexture(Node * pNode, Node * pParent, const char* pPropertyName, Texture2D * pTexture2D, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(Node * pNode, Node * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor3(Node * pNode, Node * pParent, const char* pPropertyName, ccColor3B pColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor4FVar(Node * pNode, Node * pParent, const char* pPropertyName, ccColor4F * pColor4FVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFlip(Node * pNode, Node * pParent, const char* pPropertyName, bool * pFlip, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char* pPropertyName, ccBlendFunc pBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFntFile(Node * pNode, Node * pParent, const char* pPropertyName, const char * pFntFile, CCBReader * pCCBReader);
        virtual void onHandlePropTypeString(Node * pNode, Node * pParent, const char* pPropertyName, const char * pString, CCBReader * pCCBReader);
        virtual void onHandlePropTypeText(Node * pNode, Node * pParent, const char* pPropertyName, const char * pText, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char* pPropertyName, const char * pFontTTF, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlock(Node * pNode, Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char* pPropertyName, BlockControlData * pBlockControlData, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char* pPropertyName, Node * pCCBFileNode, CCBReader * pCCBReader);

protected:
        Dictionary* _customProperties;
};

NS_CC_EXT_END

#endif
