#ifndef __CCB_CCBANIMATION_MANAGER_H__
#define __CCB_CCBANIMATION_MANAGER_H__

#include "base/CCMap.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionEase.h"

#include "extensions/ExtensionMacros.h"
#include "CCBSequence.h"
#include "CCBSequenceProperty.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"

namespace cocosbuilder {

class CCBAnimationManagerDelegate
{
public:
    virtual ~CCBAnimationManagerDelegate() {}
    virtual void completedAnimationSequenceNamed(const char *name) = 0;
};

class CCBAnimationManager : public cocos2d::Ref
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


    cocos2d::Ref *_owner;
    
    virtual bool init();
    
    cocos2d::Vector<CCBSequence*>& getSequences();
    void setSequences(const cocos2d::Vector<CCBSequence*>& seq);

    
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
    cocos2d::ValueVector& getDocumentCallbackNames();
    cocos2d::Vector<cocos2d::Node*>& getDocumentCallbackNodes();
    cocos2d::ValueVector& getDocumentCallbackControlEvents();
    
    cocos2d::ValueVector& getDocumentOutletNames();
    cocos2d::Vector<cocos2d::Node*>& getDocumentOutletNodes();
    std::string getLastCompletedSequenceName();
    
    cocos2d::ValueVector& getKeyframeCallbacks();
    
    const cocos2d::Size& getRootContainerSize();
    void setRootContainerSize(const cocos2d::Size &rootContainerSize);
    
    CCBAnimationManagerDelegate* getDelegate();
    void setDelegate(CCBAnimationManagerDelegate* pDelegate); // retain
    
    const char* getRunningSequenceName();
    
    const cocos2d::Size& getContainerSize(cocos2d::Node* pNode);
    
    void addNode(cocos2d::Node *pNode, const std::unordered_map<int, cocos2d::Map<std::string, CCBSequenceProperty*>>& seq);
    void setBaseValue(const cocos2d::Value& value, cocos2d::Node *pNode, const std::string& propName);
    void setObject(cocos2d::Ref* obj, cocos2d::Node *pNode, const std::string& propName);
    
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
    void setAnimationCompletedCallback(cocos2d::Ref *target, cocos2d::SEL_CallFunc callbackFunc);

    void debug();
    /**
     * @js setCallFuncForJSCallbackNamed
     */
    void setCallFunc(cocos2d::CallFunc *callFunc, const std::string &callbackNamed);

    cocos2d::Sequence* actionForCallbackChannel(CCBSequenceProperty* channel);
    cocos2d::Sequence* actionForSoundChannel(CCBSequenceProperty* channel);

	// return -1 if timeline not exsit
    int getSequenceId(const char* pSequenceName);
    
    // get timeline duration
    float getSequenceDuration(const char* pSequenceName);
    
private:
    const cocos2d::Value& getBaseValue(cocos2d::Node *pNode, const std::string& propName);
    Ref* getObject(cocos2d::Node *pNode, const std::string& propName);
    
    CCBSequence* getSequence(int nSequenceId);
    cocos2d::ActionInterval* getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const std::string& propName, cocos2d::Node *pNode);
    void setAnimatedProperty(const std::string& propName,cocos2d::Node *pNode, const cocos2d::Value& value, Ref* obj, float fTweenDuraion);
    void setFirstFrame(cocos2d::Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    cocos2d::ActionInterval* getEaseAction(cocos2d::ActionInterval *pAction, CCBKeyframe::EasingType easingType, float fEasingOpt);
    void runAction(cocos2d::Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    void sequenceCompleted();
    
private:
    cocos2d::Vector<CCBSequence*> _sequences;
    std::unordered_map<cocos2d::Node*, std::unordered_map<int, cocos2d::Map<std::string, CCBSequenceProperty*>>> _nodeSequences;
    std::unordered_map<cocos2d::Node*, std::unordered_map<std::string, cocos2d::Value>> _baseValues;
    std::unordered_map<cocos2d::Node*, std::unordered_map<std::string, cocos2d::Ref*>> _objects;
    
    int _autoPlaySequenceId;
    
    cocos2d::Node *_rootNode;
    
    cocos2d::Size _rootContainerSize;
    
    CCBAnimationManagerDelegate *_delegate;
    CCBSequence *_runningSequence;
    
    cocos2d::ValueVector _documentOutletNames;
    cocos2d::Vector<cocos2d::Node*> _documentOutletNodes;
    cocos2d::ValueVector _documentCallbackNames;
    cocos2d::Vector<cocos2d::Node*> _documentCallbackNodes;
    cocos2d::ValueVector _documentCallbackControlEvents;
    cocos2d::ValueVector _keyframeCallbacks;
    cocos2d::Map<std::string, cocos2d::CallFunc*> _keyframeCallFuncs;
    
    std::string _documentControllerName;
    std::string _lastCompletedSequenceName;
    
    cocos2d::SEL_CallFunc _animationCompleteCallbackFunc;
    cocos2d::Ref *_target;
    
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
