#ifndef _CCB_CCNODELOADER_H_
#define _CCB_CCNODELOADER_H_

#include "cocos2d.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

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

class CC_DLL CCNodeLoader : public CCObject {
    public:
        virtual ~CCNodeLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCNodeLoader, loader);

        virtual CCNode * loadCCNode(CCNode *, CCBReader * pCCBReader);
        virtual void parseProperties(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCNode);

        virtual CCPoint parsePropTypePosition(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCPoint parsePropTypePoint(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCPoint parsePropTypePointLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCSize parsePropTypeSize(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual float * parsePropTypeScaleLock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual float parsePropTypeFloat(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual float parsePropTypeDegrees(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual float parsePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual int parsePropTypeInteger(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual int parsePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual float * parsePropTypeFloatVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual bool parsePropTypeCheck(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCSpriteFrame * parsePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCAnimation * parsePropTypeAnimation(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCTexture2D * parsePropTypeTexture(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual unsigned char parsePropTypeByte(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual ccColor3B parsePropTypeColor3(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual ccColor4F * parsePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual bool * parsePropTypeFlip(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual ccBlendFunc parsePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCString * parsePropTypeFntFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCString * parsePropTypeString(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCString * parsePropTypeText(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCString * parsePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual BlockData * parsePropTypeBlock(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual BlockCCControlData * parsePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);
        virtual CCNode * parsePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCBReader * pCCBReader);


        virtual void onHandlePropTypePosition(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPosition, CCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader);
        virtual void onHandlePropTypePointLock(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPointLock, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSize pSize, CCBReader * pCCBReader);
        virtual void onHandlePropTypeScaleLock(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float * pScaleLock, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloat, CCBReader * pCCBReader);
        virtual void onHandlePropTypeDegrees(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pDegrees, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloatScale, CCBReader * pCCBReader);
        virtual void onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, int pInteger, CCBReader * pCCBReader);
        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatVar(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float * pFoatVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool pCheck, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader);
        virtual void onHandlePropTypeAnimation(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCAnimation * pCCAnimation, CCBReader * pCCBReader);
        virtual void onHandlePropTypeTexture(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCTexture2D * pCCTexture2D, CCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, unsigned char pByte, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor4F * pCCColor4FVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool * pFlip, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pFntFile, CCBReader * pCCBReader);
        virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pString, CCBReader * pCCBReader);
        virtual void onHandlePropTypeText(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pText, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pFontTTF, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, BlockCCControlData * pBlockCCControlData, CCBReader * pCCBReader);
        virtual void onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
