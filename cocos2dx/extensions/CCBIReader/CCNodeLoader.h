#ifndef _CCNODE_LOADER_H_
#define _CCNODE_LOADER_H_

#include "cocos2d.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

struct BlockData {
    SEL_MenuHandler mSELMenuHandler;
    CCObject * mTarget;
};

struct BlockCCControlData {
    SEL_MenuHandler mSELMenuHandler;
    CCObject * mTarget;
    int mControlEvents;
};

/* Forward declaration. */
class CCBReader;

class CC_DLL CCNodeLoader : public CCObject {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCNodeLoader, loader);

        virtual CCNode * loadCCNode(CCNode *, CCBReader *);
        virtual void parseProperties(CCNode *, CCNode *, CCBReader *);

    protected:
        virtual CCNode * createCCNode(CCNode *, CCBReader *);

        virtual CCPoint parsePropTypePosition(CCNode *, CCNode *, CCBReader *);
        virtual CCPoint parsePropTypePoint(CCNode *, CCNode *, CCBReader *);
        virtual CCPoint parsePropTypePointLock(CCNode *, CCNode *, CCBReader *);
        virtual CCSize parsePropTypeSize(CCNode *, CCNode *, CCBReader *);
        virtual float * parsePropTypeScaleLock(CCNode *, CCNode *, CCBReader *);
        virtual float parsePropTypeFloat(CCNode *, CCNode *, CCBReader *);
        virtual float parsePropTypeDegrees(CCNode *, CCNode *, CCBReader *);
        virtual float parsePropTypeFloatScale(CCNode *, CCNode *, CCBReader *);
        virtual int parsePropTypeInteger(CCNode *, CCNode *, CCBReader *);
        virtual int parsePropTypeIntegerLabeled(CCNode *, CCNode *, CCBReader *);
        virtual float * parsePropTypeFloatVar(CCNode *, CCNode *, CCBReader *);
        virtual bool parsePropTypeCheck(CCNode *, CCNode *, CCBReader *);
        virtual CCSpriteFrame * parsePropTypeSpriteFrame(CCNode *, CCNode *, CCBReader *);
        virtual CCAnimation * parsePropTypeAnimation(CCNode *, CCNode *, CCBReader *);
        virtual CCTexture2D * parsePropTypeTexture(CCNode *, CCNode *, CCBReader *);
        virtual unsigned char parsePropTypeByte(CCNode *, CCNode *, CCBReader *);
        virtual ccColor3B parsePropTypeColor3(CCNode *, CCNode *, CCBReader *);
        virtual ccColor4F * parsePropTypeColor4FVar(CCNode *, CCNode *, CCBReader *);
        virtual bool * parsePropTypeFlip(CCNode *, CCNode *, CCBReader *);
        virtual ccBlendFunc parsePropTypeBlendFunc(CCNode *, CCNode *, CCBReader *);
        virtual const char * parsePropTypeFntFile(CCNode *, CCNode *, CCBReader *);
        virtual const char * parsePropTypeString(CCNode *, CCNode *, CCBReader *);
        virtual const char * parsePropTypeText(CCNode *, CCNode *, CCBReader *);
        virtual const char * parsePropTypeFontTTF(CCNode *, CCNode *, CCBReader *);
        virtual BlockData * parsePropTypeBlock(CCNode *, CCNode *, CCBReader *);
        virtual BlockCCControlData * parsePropTypeBlockCCControl(CCNode *, CCNode *, CCBReader *);
        virtual CCNode * parsePropTypeCCBFile(CCNode *, CCNode *, CCBReader *);


        virtual void onHandlePropTypePosition(CCNode *, CCNode *, const char *, CCPoint, CCBReader *);
        virtual void onHandlePropTypePoint(CCNode *, CCNode *, const char *, CCPoint, CCBReader *);
        virtual void onHandlePropTypePointLock(CCNode *, CCNode *, const char *, CCPoint, CCBReader *);
        virtual void onHandlePropTypeSize(CCNode *, CCNode *, const char *, CCSize, CCBReader *);
        virtual void onHandlePropTypeScaleLock(CCNode *, CCNode *, const char *, float *, CCBReader *);
        virtual void onHandlePropTypeFloat(CCNode *, CCNode *, const char *, float, CCBReader *);
        virtual void onHandlePropTypeDegrees(CCNode *, CCNode *, const char *, float, CCBReader *);
        virtual void onHandlePropTypeFloatScale(CCNode *, CCNode *, const char *, float, CCBReader *);
        virtual void onHandlePropTypeInteger(CCNode *, CCNode *, const char *, int, CCBReader *);
        virtual void onHandlePropTypeIntegerLabeled(CCNode *, CCNode *, const char *, int, CCBReader *);
        virtual void onHandlePropTypeFloatVar(CCNode *, CCNode *, const char *, float *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode *, CCNode *, const char *, bool, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode *, CCNode *, const char *, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeAnimation(CCNode *, CCNode *, const char *, CCAnimation *, CCBReader *);
        virtual void onHandlePropTypeTexture(CCNode *, CCNode *, const char *, CCTexture2D *, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode *, CCNode *, const char *, unsigned char, CCBReader *);
        virtual void onHandlePropTypeColor3(CCNode *, CCNode *, const char *, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeColor4FVar(CCNode *, CCNode *, const char *, ccColor4F *, CCBReader *);
        virtual void onHandlePropTypeFlip(CCNode *, CCNode *, const char *, bool *, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, const char *, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeFntFile(CCNode *, CCNode *, const char *, const char *, CCBReader *);
        virtual void onHandlePropTypeString(CCNode *, CCNode *, const char *, const char *, CCBReader *);
        virtual void onHandlePropTypeText(CCNode *, CCNode *, const char *, const char *, CCBReader *);
        virtual void onHandlePropTypeFontTTF(CCNode *, CCNode *, const char *, const char *, CCBReader *);
        virtual void onHandlePropTypeBlock(CCNode *, CCNode *, const char *, BlockData *, CCBReader *);
        virtual void onHandlePropTypeBlockCCControl(CCNode *, CCNode *, const char *, BlockCCControlData *, CCBReader *);
        virtual void onHandlePropTypeCCBFile(CCNode *, CCNode *, const char *, CCNode *, CCBReader *);
};

NS_CC_EXT_END

#endif
