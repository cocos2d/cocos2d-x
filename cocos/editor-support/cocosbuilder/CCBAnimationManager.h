#ifndef __CCB_CCBANIMATION_MANAGER_H__
#define __CCB_CCBANIMATION_MANAGER_H__

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"
#include "CCBSequence.h"
#include "CCBValue.h"
#include "CCBSequenceProperty.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"

namespace cocosbuilder {

class CCBAnimationManagerDelegate
{
public:
    virtual ~CCBAnimationManagerDelegate() {}
    virtual void completedAnimationSequenceNamed(const char *name) = 0;
};

class CCBAnimationManager : public cocos2d::Object
{
public:
    bool _jsControlled;
    /**
     * @js ctor
     */
    CCBAnimationManager();
    /**
     * @js NA
     * @lua NA
     */
    ~CCBAnimationManager();


    cocos2d::Object *_owner;
    
    virtual bool init();
    
    cocos2d::Array* getSequences();
    void setSequences(cocos2d::Array* seq);

    
    int getAutoPlaySequenceId();
    void setAutoPlaySequenceId(int autoPlaySequenceId);
    
    cocos2d::Node* getRootNode();
    void setRootNode(cocos2d::Node* pRootNode); // weak reference    
    

    void addDocumentCallbackNode(cocos2d::Node *node);
    void addDocumentCallbackName(std::string name);
    void addDocumentCallbackControlEvents(cocos2d::extension::Control::EventType eventType);
    
    void addDocumentOutletNode(cocos2d::Node *node);
    void addDocumentOutletName(std::string name);

    void setDocumentControllerName(const std::string &name);
    
    std::string getDocumentControllerName();
    cocos2d::Array* getDocumentCallbackNames();
    cocos2d::Array* getDocumentCallbackNodes();
    cocos2d::Array* getDocumentCallbackControlEvents();
    
    cocos2d::Array* getDocumentOutletNames();
    cocos2d::Array* getDocumentOutletNodes();
    std::string getLastCompletedSequenceName();
    
    cocos2d::Array* getKeyframeCallbacks();
    
    const cocos2d::Size& getRootContainerSize();
    void setRootContainerSize(const cocos2d::Size &rootContainerSize);
    
    CCBAnimationManagerDelegate* getDelegate();
    void setDelegate(CCBAnimationManagerDelegate* pDelegate); // retain
    
    const char* getRunningSequenceName();
    
    const cocos2d::Size& getContainerSize(cocos2d::Node* pNode);
    
    void addNode(cocos2d::Node *pNode, cocos2d::Dictionary *pSeq);
    void setBaseValue(cocos2d::Object *pValue, cocos2d::Node *pNode, const char *propName);
    void moveAnimationsFromNode(cocos2d::Node* fromNode, cocos2d::Node* toNode);

    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(const char *pName, float fTweenDuration);
    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(const char *pName);
    /** @deprecated This interface will be deprecated sooner or later.*/
    CC_DEPRECATED_ATTRIBUTE void runAnimations(int nSeqId, float fTweenDuraiton);

    void runAnimationsForSequenceNamedTweenDuration(const char *pName, float fTweenDuration);
    void runAnimationsForSequenceNamed(const char *pName);
    void runAnimationsForSequenceIdTweenDuration(int nSeqId, float fTweenDuraiton);
    /**
     * when this function bound to js ,the second param are callfunc_selector
     * @lua NA
     */
    void setAnimationCompletedCallback(cocos2d::Object *target, cocos2d::SEL_CallFunc callbackFunc);

    void debug();
    /**
     * @js setCallFuncForJSCallbackNamed
     */
    void setCallFunc(cocos2d::CallFunc *callFunc, const std::string &callbackNamed);

    cocos2d::Object* actionForCallbackChannel(CCBSequenceProperty* channel);
    cocos2d::Object* actionForSoundChannel(CCBSequenceProperty* channel);

	// return -1 if timeline not exsit
    int getSequenceId(const char* pSequenceName);
    
    // get timeline duration
    float getSequenceDuration(const char* pSequenceName);
    
private:
    cocos2d::Object* getBaseValue(cocos2d::Node *pNode, const char* propName);
    CCBSequence* getSequence(int nSequenceId);
    cocos2d::ActionInterval* getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *propName, cocos2d::Node *pNode);
    void setAnimatedProperty(const char *propName,cocos2d::Node *pNode, Object *pValue, float fTweenDuraion);
    void setFirstFrame(cocos2d::Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    cocos2d::ActionInterval* getEaseAction(cocos2d::ActionInterval *pAction, CCBKeyframe::EasingType easingType, float fEasingOpt);
    void runAction(cocos2d::Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    void sequenceCompleted();
    
private:
    cocos2d::Array *_sequences;
    cocos2d::Dictionary *_nodeSequences;
    cocos2d::Dictionary *_baseValues;
    int _autoPlaySequenceId;
    
    cocos2d::Node *_rootNode;
    
    cocos2d::Size _rootContainerSize;
    
    CCBAnimationManagerDelegate *_delegate;
    CCBSequence *_runningSequence;
    
    cocos2d::Array *_documentOutletNames;
    cocos2d::Array *_documentOutletNodes;
    cocos2d::Array *_documentCallbackNames;
    cocos2d::Array *_documentCallbackNodes;
    cocos2d::Array *_documentCallbackControlEvents;
    cocos2d::Array *_keyframeCallbacks;
    cocos2d::Dictionary *_keyframeCallFuncs;
    
    std::string _documentControllerName;
    std::string _lastCompletedSequenceName;
    
    cocos2d::SEL_CallFunc _animationCompleteCallbackFunc;
    cocos2d::Object *_target;
};

class CCBSetSpriteFrame : public cocos2d::ActionInstant
{
public:
    /** creates a Place action with a position */
    static CCBSetSpriteFrame* create(cocos2d::SpriteFrame *pSpriteFrame);
    /**
     * @js NA
     * @lua NA
     */
    ~CCBSetSpriteFrame();
    
    bool initWithSpriteFrame(cocos2d::SpriteFrame *pSpriteFrame);

    // Overrides
    virtual void update(float time) override;
	virtual CCBSetSpriteFrame* clone() const override;
	virtual CCBSetSpriteFrame* reverse() const override;

private:
    cocos2d::SpriteFrame *_spriteFrame;
};


class CCBSoundEffect : public cocos2d::ActionInstant
{
public:
    static CCBSoundEffect* actionWithSoundFile(const std::string &file, float pitch, float pan, float gain);
    /**
     * @js NA
     * @lua NA
     */
    ~CCBSoundEffect();
    bool initWithSoundFile(const std::string &file, float pitch, float pan, float gain);

    // Overrides
    virtual void update(float time) override;
	virtual CCBSoundEffect* clone() const override;
	virtual CCBSoundEffect* reverse() const override;

private:
    std::string _soundFile;
    float _pitch, _pan, _gain;
};


class CCBRotateTo : public cocos2d::ActionInterval
{
public:
    static CCBRotateTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);

    // Override
    virtual void update(float time) override;
	virtual CCBRotateTo* clone() const override;
	virtual CCBRotateTo* reverse() const override;
    virtual void startWithTarget(cocos2d::Node *pNode) override;

private:
    float _startAngle;
    float _dstAngle;
    float _diffAngle;
};


class CCBRotateXTo: public cocos2d::ActionInterval
{
public:
    static CCBRotateXTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);

    // Overrides
    virtual void startWithTarget(cocos2d::Node *pNode) override;
	virtual CCBRotateXTo* clone() const override;
	virtual CCBRotateXTo* reverse() const override;
    virtual void update(float time) override;

private:
    float _startAngle;
    float _dstAngle;
    float _diffAngle;
};


class CCBRotateYTo: public cocos2d::ActionInterval
{
public:
    static CCBRotateYTo* create(float fDuration, float fAngle);
    bool initWithDuration(float fDuration, float fAngle);

    // Override
    virtual void startWithTarget(cocos2d::Node *pNode) override;
	virtual CCBRotateYTo* clone() const override;
	virtual CCBRotateYTo* reverse() const override;
    virtual void update(float time) override;

private:
    float _startAngle;
    float _dstAngle;
    float _diffAngle;
};


class CCBEaseInstant : public cocos2d::ActionEase
{
public:
    static CCBEaseInstant* create(cocos2d::ActionInterval *pAction);

	virtual CCBEaseInstant* clone() const override;
	virtual CCBEaseInstant* reverse() const override;
    virtual void update(float dt) override;
};


}

#endif // __CCB_CCBANIMATION_MANAGER_H__
