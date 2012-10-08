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

class CCBAnimationManager : public CCObject
{
private:
    CCArray *mSequences;
    CCDictionary *mNodeSequences;
    CCDictionary *mBaseValues;
    int mAutoPlaySequenceId;
    
    CCNode *mRootNode;
    CCSize mRootContainerSize;
    
    CCBAnimationManagerDelegate *mDelegate;
    CCBSequence *mRunningSequence;
    
public:
    CCBAnimationManager();
    ~CCBAnimationManager();
    
    virtual bool init();
    
    CCArray* getSequences();
    
    int getAutoPlaySequenceId();
    void setAutoPlaySequenceId(int autoPlaySequenceId);
    
    CCNode* getRootNode();
    void setRootNode(CCNode* pRootNode); // retain
    
    const CCSize& getRootContainerSize();
    void setRootContainerSize(const CCSize &rootContainerSize);
    
    CCBAnimationManagerDelegate* getDelegate();
    void setDelegate(CCBAnimationManagerDelegate* pDelegate); // retain
    
    const char* getRunningSequenceName();
    
    const CCSize& getContainerSize(CCNode* pNode);
    
    void addNode(CCNode *pNode, CCDictionary *pSeq);
    void setBaseValue(CCObject *pValue, CCNode *pNode, const char *pPropName);
    
    void runAnimations(const char *pName, float fTweenDuration);
    void runAnimations(const char *pName);
    void runAnimations(int nSeqId, float fTweenDuraiton);
    
    void debug();
    
private:
    CCObject* getBaseValue(CCNode *pNode, const char* pPropName);
    int getSequenceId(const char* pSequenceName);
    CCBSequence* getSequence(int nSequenceId);
    CCActionInterval* getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *pPropName, CCNode *pNode);
    void setAnimatedProperty(const char *pPropName, CCNode *pNode, CCObject *pValue, float fTweenDuraion);
    void setFirstFrame(CCNode *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    CCActionInterval* getEaseAction(CCActionInterval *pAction, int nEasingType, float fEasingOpt);
    void runAction(CCNode *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    void sequenceCompleted();
};

class CCBSetSpriteFrame : public CCActionInstant
{
private:
    CCSpriteFrame *mSpriteFrame;
    
public:
    ~CCBSetSpriteFrame();
    
    /** creates a Place action with a position */
    static CCBSetSpriteFrame* create(CCSpriteFrame *pSpriteFrame);
    bool initWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone *pZone);
};

class CCBRotateTo : public CCActionInterval
{
private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
    
public:
    static CCBRotateTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);
    virtual void update(float time);
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void startWithTarget(CCNode *pNode);
};

NS_CC_EXT_END

#endif // __CCB_CCBANIMATION_MANAGER_H__
