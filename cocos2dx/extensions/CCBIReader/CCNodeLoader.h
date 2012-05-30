#ifndef _CCNODE_LOADER_H_
#define _CCNODE_LOADER_H_

#include "cocos2d.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCNodeLoader {
    public:
        virtual cocos2d::CCNode * loadCCNode(cocos2d::CCNode *, CCBReader *);
        virtual void parseProperties(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);

    protected:
        virtual cocos2d::CCNode * createCCNode(cocos2d::CCNode *, CCBReader *);

        virtual cocos2d::CCPoint parsePropTypePosition(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::CCPoint parsePropTypePoint(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::CCPoint parsePropTypePointLock(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::CCSize parsePropTypeSize(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual float * parsePropTypeScaleLock(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual float parsePropTypeFloat(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual float parsePropTypeDegrees(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual float parsePropTypeFloatScale(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual int parsePropTypeInteger(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual int parsePropTypeIntegerLabeled(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual float * parsePropTypeFloatVar(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual bool parsePropTypeCheck(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::CCSpriteFrame * parsePropTypeSpriteFrame(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::CCAnimation * parsePropTypeAnimation(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::CCTexture2D * parsePropTypeTexture(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual unsigned char parsePropTypeByte(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::ccColor3B parsePropTypeColor3(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::ccColor4F * parsePropTypeColor4FVar(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual bool * parsePropTypeFlip(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual cocos2d::ccBlendFunc parsePropTypeBlendFunc(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual std::string parsePropTypeFntFile(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual std::string parsePropTypeString(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual std::string parsePropTypeText(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual std::string parsePropTypeFontTTF(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual void * parsePropTypeBlock(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual void * parsePropTypeBlockCCControl(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);
        virtual std::string parsePropTypeCCBFile(cocos2d::CCNode *, cocos2d::CCNode *, CCBReader *);


        virtual void onHandlePropTypePosition(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::CCPoint, CCBReader *);
        virtual void onHandlePropTypePoint(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::CCPoint, CCBReader *);
        virtual void onHandlePropTypePointLock(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::CCPoint, CCBReader *);
        virtual void onHandlePropTypeSize(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::CCSize, CCBReader *);
        virtual void onHandlePropTypeScaleLock(cocos2d::CCNode *, cocos2d::CCNode *, std::string, float *, CCBReader *);
        virtual void onHandlePropTypeFloat(cocos2d::CCNode *, cocos2d::CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypeDegrees(cocos2d::CCNode *, cocos2d::CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypeFloatScale(cocos2d::CCNode *, cocos2d::CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypeInteger(cocos2d::CCNode *, cocos2d::CCNode *, std::string, int, CCBReader *);
        virtual void onHandlePropTypeIntegerLabeled(cocos2d::CCNode *, cocos2d::CCNode *, std::string, int, CCBReader *);
        virtual void onHandlePropTypeFloatVar(cocos2d::CCNode *, cocos2d::CCNode *, std::string, float *, CCBReader *);
        virtual void onHandlePropTypeCheck(cocos2d::CCNode *, cocos2d::CCNode *, std::string, bool, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeAnimation(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::CCAnimation *, CCBReader *);
        virtual void onHandlePropTypeTexture(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::CCTexture2D *, CCBReader *);
        virtual void onHandlePropTypeByte(cocos2d::CCNode *, cocos2d::CCNode *, std::string, unsigned char, CCBReader *);
        virtual void onHandlePropTypeColor3(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::ccColor3B, CCBReader *);
        virtual void onHandlePropTypeColor4FVar(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::ccColor4F *, CCBReader *);
        virtual void onHandlePropTypeFlip(cocos2d::CCNode *, cocos2d::CCNode *, std::string, bool *, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeFntFile(cocos2d::CCNode *, cocos2d::CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeString(cocos2d::CCNode *, cocos2d::CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeText(cocos2d::CCNode *, cocos2d::CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeFontTTF(cocos2d::CCNode *, cocos2d::CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeBlock(cocos2d::CCNode *, cocos2d::CCNode *, std::string, void *, CCBReader *);
        virtual void onHandlePropTypeBlockCCControl(cocos2d::CCNode *, cocos2d::CCNode *, std::string, void *, CCBReader *);
        virtual void onHandlePropTypeCCBFile(cocos2d::CCNode *, cocos2d::CCNode *, std::string, std::string, CCBReader *);
};

NS_CC_EXT_END

#endif
