#ifndef __CCBX_CCBANIMATION_MANAGER_H__
#define __CCBX_CCBANIMATION_MANAGER_H__

#include "base/CCMap.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionEase.h"

#include "CCBXSequence.h"
#include "CCBXKeyframe.h"
#include "CCBXSequenceProperty.h"

NS_CC_BEGIN

namespace spritebuilder {
    
class CCBXReaderOwner;
    
enum class AnimationCompleteType
{
    CHAINED,
    COMPLETED,
    STOPED
};

class CC_DLL CCBAnimationManagerDelegate
{
public:
    virtual ~CCBAnimationManagerDelegate() {}
    virtual void completedAnimationSequenceNamed(const char *name, AnimationCompleteType type) = 0;
};

class CC_DLL CCBAnimationManager : public cocos2d::Ref
{
public:
    CCBAnimationManager(float mainScale, float additionalScale, cocos2d::Node *rootNode, CCBXReaderOwner *owner);
    ~CCBAnimationManager();
    
    static CCBAnimationManager *fromNode(Node *node);
    
    virtual bool init();
    
    cocos2d::Vector<CCBSequence*>& getSequences();
    void setSequences(const cocos2d::Vector<CCBSequence*>& seq);

    
    int getAutoPlaySequenceId();
    void setAutoPlaySequenceId(int autoPlaySequenceId);
    
    cocos2d::Node* getRootNode() const;

    void addDocumentCallbackNode(cocos2d::Node *node);
    void addDocumentCallbackName(std::string name);
    
    void addDocumentOutletNode(cocos2d::Node *node);
    void addDocumentOutletName(std::string name);

    void setDocumentControllerName(const std::string &name);
    
    std::string getDocumentControllerName();
    cocos2d::ValueVector& getDocumentCallbackNames();
    cocos2d::Vector<cocos2d::Node*>& getDocumentCallbackNodes();
    
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

    void runAnimationsForSequenceNamedTweenDuration(const char *pName, float fTweenDuration, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &callback = nullptr);
    void runAnimationsForSequenceNamed(const char *pName, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &callback = nullptr);
    void runAnimationsForSequenceIdTweenDuration(int nSeqId, float fTweenDuraiton, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &callback = nullptr);
    
    void stopAnimations(bool reset);

    void debug();

    cocos2d::Sequence* actionForCallbackChannel(CCBSequenceProperty* channel);
    cocos2d::Sequence* actionForSoundChannel(CCBSequenceProperty* channel);

	// return -1 if timeline not exsit
    int getSequenceId(const char* pSequenceName);
    
    // get timeline duration
    float getSequenceDuration(const char* pSequenceName);
    
    float getMainScale();
    void setMainScale(float scale);
    
    float getAdditionalScale();
    void setAdditionalScale(float scale);
    
private:
    const cocos2d::Value& getBaseValue(cocos2d::Node *pNode, const std::string& propName);
    Ref* getObject(cocos2d::Node *pNode, const std::string& propName);
    
    CCBSequence* getSequence(int nSequenceId);
    cocos2d::ActionInterval* getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const std::string& propName, cocos2d::Node *pNode);
    void setAnimatedProperty(const std::string& propName,cocos2d::Node *pNode, const cocos2d::Value& value, Ref* obj, float fTweenDuraion, bool isBaseValue);
    void setFirstFrame(cocos2d::Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    cocos2d::ActionInterval* getEaseAction(cocos2d::ActionInterval *pAction, CCBKeyframe::EasingType easingType, float fEasingOpt);
    void runAction(cocos2d::Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration);
    void sequenceCompleted(const std::function<void(cocos2d::Node*, AnimationCompleteType)> &callback);
    
private:
    cocos2d::Vector<CCBSequence*> _sequences;
    std::unordered_map<cocos2d::Node*, std::unordered_map<int, cocos2d::Map<std::string, CCBSequenceProperty*>>> _nodeSequences;
    std::unordered_map<cocos2d::Node*, std::unordered_map<std::string, cocos2d::Value>> _baseValues;
    std::unordered_map<cocos2d::Node*, std::unordered_map<std::string, cocos2d::Ref*>> _objects;
    
    int _autoPlaySequenceId;
    
    cocos2d::Node *_rootNode;
    CCBXReaderOwner *_owner;
    
    cocos2d::Size _rootContainerSize;
    
    CCBAnimationManagerDelegate *_delegate;
    std::pair<CCBSequence*, std::function<void(cocos2d::Node*, AnimationCompleteType)>>_runningSequence;
    
    cocos2d::ValueVector _documentOutletNames;
    cocos2d::Vector<cocos2d::Node*> _documentOutletNodes;
    cocos2d::ValueVector _documentCallbackNames;
    cocos2d::Vector<cocos2d::Node*> _documentCallbackNodes;
    cocos2d::ValueVector _documentCallbackControlEvents;
    cocos2d::ValueVector _keyframeCallbacks;
    
    std::string _documentControllerName;
    std::string _lastCompletedSequenceName;
    
    float _mainScale;
    float _additionalScale;
    
};

}

NS_CC_END

#endif // __CCB_CCBANIMATION_MANAGER_H__
