#ifndef _CCB_CCNODELOADER_H_
#define _CCB_CCNODELOADER_H_

#include "../GUI/CCControlExtension/CCInvocation.h"
#include "cocos2d.h"
#include "CCBReader.h"
#include "CCBValue.h"

NS_CC_EXT_BEGIN

#define PROPERTY_POSITION "position"
#define PROPERTY_CONTENTSIZE "contentSize"
#define PROPERTY_ANCHORPOINT "anchorPoint"
#define PROPERTY_SCALE "scale"
#define PROPERTY_ROTATION "rotation"
#define PROPERTY_TAG "tag"
#define PROPERTY_IGNOREANCHORPOINTFORPOSITION "ignoreAnchorPointForPosition"
#define PROPERTY_VISIBLE "visible"

#define ASSERT_FAIL_UNEXPECTED_PROPERTY(PROPERTY) CCLog("Unexpected property: '%s'!\n", PROPERTY); assert(false)
#define ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(PROPERTYTYPE) CCLog("Unexpected property type: '%d'!\n", PROPERTYTYPE); assert(false)

#define CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) { \
    return T::create(); \
}

#define CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) = 0

struct BlockData {
    SEL_MenuHandler mSELMenuHandler;
    CCObject * mTarget;
};

struct BlockCCControlData {
    SEL_CCControlHandler mSELCCControlHandler;
    CCObject * mTarget;
    int mControlEvents;
};

/* Forward declaration. */
class CCBReader;

class CCNodeLoader : public CCObject {
    public:
        CCNodeLoader();
        virtual ~CCNodeLoader();
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCNodeLoader, loader);

        virtual CCNode * loadCCNode(CCNode *, CCBReader * pCCBReader);
        virtual void parseProperties(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCDictionary* getCustomProperties();
    
    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCNode);

        virtual CCPoint parsePropTypePosition(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual CCPoint parsePropTypePoint(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCPoint parsePropTypePointLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCSize parsePropTypeSize(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual float * parsePropTypeScaleLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual float parsePropTypeFloat(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual float parsePropTypeDegrees(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual float parsePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual int parsePropTypeInteger(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual int parsePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual float * parsePropTypeFloatVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual bool parsePropTypeCheck(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual CCSpriteFrame * parsePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual CCAnimation * parsePropTypeAnimation(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCTexture2D * parsePropTypeTexture(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual unsigned char parsePropTypeByte(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual ccColor3B parsePropTypeColor3(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader, const char *pPropertyName);
        virtual ccColor4F * parsePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual bool * parsePropTypeFlip(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual ccBlendFunc parsePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual std::string parsePropTypeFntFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual std::string parsePropTypeString(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual std::string parsePropTypeText(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual std::string parsePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual BlockData * parsePropTypeBlock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual BlockCCControlData * parsePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCNode * parsePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);


        virtual void onHandlePropTypePosition(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPosition, CCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPoint, CCBReader * pCCBReader);
        virtual void onHandlePropTypePointLock(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPointLock, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSize pSize, CCBReader * pCCBReader);
        virtual void onHandlePropTypeScaleLock(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float * pScaleLock, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader);
        virtual void onHandlePropTypeDegrees(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pDegrees, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloatScale, CCBReader * pCCBReader);
        virtual void onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pInteger, CCBReader * pCCBReader);
        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatVar(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float * pFoatVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader);
        virtual void onHandlePropTypeAnimation(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCAnimation * pCCAnimation, CCBReader * pCCBReader);
        virtual void onHandlePropTypeTexture(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCTexture2D * pCCTexture2D, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccColor4F * pCCColor4FVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool * pFlip, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pFntFile, CCBReader * pCCBReader);
        virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pString, CCBReader * pCCBReader);
        virtual void onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pText, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pFontTTF, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, const char* pPropertyName, BlockCCControlData * pBlockCCControlData, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader);

protected:
        CCDictionary* m_pCustomProperties;
};

NS_CC_EXT_END

#endif
