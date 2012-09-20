#ifndef __CCB_CCBANIMATION_MANAGER_H__
#define __CCB_CCBANIMATION_MANAGER_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCBSequence.h"
#include "CCBValue.h"
#include "CCBSequenceProperty.h"

NS_CC_EXT_BEGIN

class CCBAnimationManagerDelegate
{
public:
    virtual void completedAnimationSequenceNamed(const char *name) = 0;
};

class CCBAnimationManager : public cocos2d::CCObject
{
private:
    cocos2d::CCArray *mSequences;
    cocos2d::CCDictionary *mNodeSequences;
    cocos2d::CCDictionary *mBaseValues;
    int mAutoPlaySequenceId;
    
    cocos2d::CCNode *mRootNode;
    CCSize mRootContainerSize;
    
    CCBAnimationManagerDelegate *mDelegate;
    CCBSequence *mRunningSequence;
    
public:
    CCBAnimationManager();
    ~CCBAnimationManager();
    
    virtual bool init();
    
    cocos2d::CCArray* getSequences();
    
    int getAutoPlaySequenceId();
    void setAutoPlaySequenceId(int autoPlaySequenceId);
    
    cocos2d::CCNode* getRootNode();
    void setRootNode(cocos2d::CCNode* pRootNode); // retain
    
    const cocos2d::CCSize& getRootContainerSize();
    void setRootContainerSize(const cocos2d::CCSize &rootContainerSize);
    
    CCBAnimationManagerDelegate* getDelegate();
    void setDelegate(CCBAnimationManagerDelegate* pDelegate); // retain
    
    const char* getRunningSequenceName();
    
    const CCSize& getContainerSize(cocos2d::CCNode* pNode);
    
    void addNode(cocos2d::CCNode *pNode, cocos2d::CCDictionary *pSeq);
    void setBaseValue(cocos2d::CCObject *pValue, cocos2d::CCNode *pNode, const char *pPropName);
    
    void runAnimations(const char *pName, float fTweenDuration);
    void runAnimations(const char *pName);
    void runAnimations(int nSeqId, float fTweenDuraiton);
    
    void debug();
    
private:
    cocos2d::CCObject* getBaseValue(cocos2d::CCNode *pNode, const char* pPropName);
    int getSequenceId(const char* pSequenceName);
    CCBSequence* getSequence(int nSequenceId);
    cocos2d::CCActionInterval* getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *pPropName, cocos2d::CCNode *pNode);
    void setAnimatedProperty(const char *pPropName, cocos2d::CCNode *pNode, cocos2d::CCObject *pValue, float fTweenDuraion);
    void setFirstFrame(cocos2d::CCNode *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    cocos2d::CCActionInterval* getEaseAction(cocos2d::CCActionInterval *pAction, int nEasingType, float fEasingOpt);
    void runAction(cocos2d::CCNode *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    void sequenceCompleted();
};

class CCBSetSpriteFrame : public cocos2d::CCActionInstant
{
private:
    cocos2d::CCSpriteFrame *mSpriteFrame;
    
public:
    ~CCBSetSpriteFrame();
    
    /** creates a Place action with a position */
    static CCBSetSpriteFrame* create(cocos2d::CCSpriteFrame *pSpriteFrame);
    bool initWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
    virtual void update(float time);
    virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone *pZone);
};

class CCBRotateTo : public cocos2d::CCActionInterval
{
private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
    
public:
    static CCBRotateTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);
    virtual void update(float time);
    virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone *pZone);
    virtual void startWithTarget(cocos2d::CCNode *pNode);
};

NS_CC_EXT_END

#endif // __CCB_CCBANIMATION_MANAGER_H__
