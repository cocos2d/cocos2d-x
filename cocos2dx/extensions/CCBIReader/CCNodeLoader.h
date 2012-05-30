#ifndef _CCNODE_LOADER_H_
#define _CCNODE_LOADER_H_

#include "cocos2d.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCNodeLoader {
    public:
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
        virtual std::string parsePropTypeFntFile(CCNode *, CCNode *, CCBReader *);
        virtual std::string parsePropTypeString(CCNode *, CCNode *, CCBReader *);
        virtual std::string parsePropTypeText(CCNode *, CCNode *, CCBReader *);
        virtual std::string parsePropTypeFontTTF(CCNode *, CCNode *, CCBReader *);
        virtual void * parsePropTypeBlock(CCNode *, CCNode *, CCBReader *);
        virtual void * parsePropTypeBlockCCControl(CCNode *, CCNode *, CCBReader *);
        virtual std::string parsePropTypeCCBFile(CCNode *, CCNode *, CCBReader *);


        virtual void onHandlePropTypePosition(CCNode *, CCNode *, std::string, CCPoint, CCBReader *);
        virtual void onHandlePropTypePoint(CCNode *, CCNode *, std::string, CCPoint, CCBReader *);
        virtual void onHandlePropTypePointLock(CCNode *, CCNode *, std::string, CCPoint, CCBReader *);
        virtual void onHandlePropTypeSize(CCNode *, CCNode *, std::string, CCSize, CCBReader *);
        virtual void onHandlePropTypeScaleLock(CCNode *, CCNode *, std::string, float *, CCBReader *);
        virtual void onHandlePropTypeFloat(CCNode *, CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypeDegrees(CCNode *, CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypeFloatScale(CCNode *, CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypeInteger(CCNode *, CCNode *, std::string, int, CCBReader *);
        virtual void onHandlePropTypeIntegerLabeled(CCNode *, CCNode *, std::string, int, CCBReader *);
        virtual void onHandlePropTypeFloatVar(CCNode *, CCNode *, std::string, float *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode *, CCNode *, std::string, bool, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode *, CCNode *, std::string, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeAnimation(CCNode *, CCNode *, std::string, CCAnimation *, CCBReader *);
        virtual void onHandlePropTypeTexture(CCNode *, CCNode *, std::string, CCTexture2D *, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode *, CCNode *, std::string, unsigned char, CCBReader *);
        virtual void onHandlePropTypeColor3(CCNode *, CCNode *, std::string, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeColor4FVar(CCNode *, CCNode *, std::string, ccColor4F *, CCBReader *);
        virtual void onHandlePropTypeFlip(CCNode *, CCNode *, std::string, bool *, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, std::string, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeFntFile(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeString(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeText(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeFontTTF(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeBlock(CCNode *, CCNode *, std::string, void *, CCBReader *);
        virtual void onHandlePropTypeBlockCCControl(CCNode *, CCNode *, std::string, void *, CCBReader *);
        virtual void onHandlePropTypeCCBFile(CCNode *, CCNode *, std::string, std::string, CCBReader *);
};

NS_CC_EXT_END

#endif
