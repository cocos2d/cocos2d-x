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

class CCBAnimationManager : public Object
{
private:
    Array *mSequences;
    Dictionary *mNodeSequences;
    Dictionary *mBaseValues;
    int mAutoPlaySequenceId;
    
    Node *mRootNode;
    
    Size mRootContainerSize;
    
    CCBAnimationManagerDelegate *mDelegate;
    CCBSequence *mRunningSequence;
    
    Array *mDocumentOutletNames;
    Array *mDocumentOutletNodes;
    Array *mDocumentCallbackNames;
    Array *mDocumentCallbackNodes;
    Array *mKeyframeCallbacks;
    Dictionary *mKeyframeCallFuncs;

    std::string mDocumentControllerName;
    std::string lastCompletedSequenceName;

    SEL_CallFunc mAnimationCompleteCallbackFunc;
    Object *mTarget;
    
    
public:
    bool jsControlled;
    CCBAnimationManager();
    ~CCBAnimationManager();


    Object *mOwner;
    
    virtual bool init();
    
    Array* getSequences();
    void setSequences(Array* seq);

    
    int getAutoPlaySequenceId();
    void setAutoPlaySequenceId(int autoPlaySequenceId);
    
    Node* getRootNode();
    void setRootNode(Node* pRootNode); // weak reference    
    

    void addDocumentCallbackNode(Node *node);
    void addDocumentCallbackName(std::string name);
    void addDocumentOutletNode(Node *node);
    void addDocumentOutletName(std::string name);

    void setDocumentControllerName(const std::string &name);
    
    std::string getDocumentControllerName();
    Array* getDocumentCallbackNames();
    Array* getDocumentCallbackNodes();
    Array* getDocumentOutletNames();
    Array* getDocumentOutletNodes();
    std::string getLastCompletedSequenceName();
    
    Array* getKeyframeCallbacks();
    
    const Size& getRootContainerSize();
    void setRootContainerSize(const Size &rootContainerSize);
    
    CCBAnimationManagerDelegate* getDelegate();
    void setDelegate(CCBAnimationManagerDelegate* pDelegate); // retain
    
    const char* getRunningSequenceName();
    
    const Size& getContainerSize(Node* pNode);
    
    void addNode(Node *pNode, Dictionary *pSeq);
    void setBaseValue(Object *pValue, Node *pNode, const char *pPropName);
    void moveAnimationsFromNode(Node* fromNode, Node* toNode);

    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(const char *pName, float fTweenDuration);
    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(const char *pName);
    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(int nSeqId, float fTweenDuraiton);

    void runAnimationsForSequenceNamedTweenDuration(const char *pName, float fTweenDuration);
    void runAnimationsForSequenceNamed(const char *pName);
    void runAnimationsForSequenceIdTweenDuration(int nSeqId, float fTweenDuraiton);

    void setAnimationCompletedCallback(Object *target, SEL_CallFunc callbackFunc);

    void debug();
    
    void setCallFunc(CallFunc *callFunc, const std::string &callbackNamed);

    Object* actionForCallbackChannel(CCBSequenceProperty* channel);
    Object* actionForSoundChannel(CCBSequenceProperty* channel);
    
private:
    Object* getBaseValue(Node *pNode, const char* pPropName);
    int getSequenceId(const char* pSequenceName);
    CCBSequence* getSequence(int nSequenceId);
    ActionInterval* getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *pPropName, Node *pNode);
    void setAnimatedProperty(const char *pPropName, Node *pNode, Object *pValue, float fTweenDuraion);
    void setFirstFrame(Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    ActionInterval* getEaseAction(ActionInterval *pAction, int nEasingType, float fEasingOpt);
    void runAction(Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    void sequenceCompleted();
};

class CCBSetSpriteFrame : public ActionInstant
{
private:
    SpriteFrame *mSpriteFrame;
    
public:
    ~CCBSetSpriteFrame();
    
    /** creates a Place action with a position */
    static CCBSetSpriteFrame* create(SpriteFrame *pSpriteFrame);
    bool initWithSpriteFrame(SpriteFrame *pSpriteFrame);
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCBSetSpriteFrame* clone() const;

	/** returns a new reversed action */
	virtual CCBSetSpriteFrame* reverse() const;

    virtual Object* copyWithZone(Zone *pZone);
};



class CCBSoundEffect : public ActionInstant
{
private:
  std::string mSoundFile;
  float mPitch, mPan, mGain;
    
public:
    ~CCBSoundEffect();
    
    static CCBSoundEffect* actionWithSoundFile(const std::string &file, float pitch, float pan, float gain);
    bool initWithSoundFile(const std::string &file, float pitch, float pan, float gain);
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCBSoundEffect* clone() const;

	/** returns a new reversed action */
	virtual CCBSoundEffect* reverse() const;

    virtual Object* copyWithZone(Zone *pZone);
};


class CCBRotateTo : public ActionInterval
{
private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
    
public:
    static CCBRotateTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);
    virtual void update(float time);
	/** returns a new clone of the action */
	virtual CCBRotateTo* clone() const;

	/** returns a new reversed action */
	virtual CCBRotateTo* reverse() const;

    virtual Object* copyWithZone(Zone *pZone);
    virtual void startWithTarget(Node *pNode);
};


class CCBRotateXTo: public ActionInterval {
private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;
public:
    static CCBRotateXTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);
    virtual void startWithTarget(Node *pNode);
	/** returns a new clone of the action */
	virtual CCBRotateXTo* clone() const;

	/** returns a new reversed action */
	virtual CCBRotateXTo* reverse() const;

    virtual Object* copyWithZone(Zone *pZone);
    virtual void update(float time);
};


class CCBRotateYTo: public ActionInterval {
private:
    float mStartAngle;
    float mDstAngle;
    float mDiffAngle;

public:
    static CCBRotateYTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);
    virtual void startWithTarget(Node *pNode);
	/** returns a new clone of the action */
	virtual CCBRotateYTo* clone() const;

	/** returns a new reversed action */
	virtual CCBRotateYTo* reverse() const;

    virtual Object* copyWithZone(Zone *pZone);
    virtual void update(float time);
};


class CCBEaseInstant : public ActionEase
{
public:
    static CCBEaseInstant* create(ActionInterval *pAction);

	/** returns a new clone of the action */
	virtual CCBEaseInstant* clone() const;

	/** returns a new reversed action */
	virtual CCBEaseInstant* reverse() const;
	
    virtual void update(float dt);
};


NS_CC_EXT_END

#endif // __CCB_CCBANIMATION_MANAGER_H__
