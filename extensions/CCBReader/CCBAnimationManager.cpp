#include "CCBAnimationManager.h"
#include "CCBSequence.h"
#include "CCBSequenceProperty.h"
#include "CCBReader.h"
#include "CCBKeyframe.h"
#include "CCNode+CCBRelativePositioning.h"
#include <string>
#include <set>
#include "SimpleAudioEngine.h"
#include "CCBSelectorResolver.h"

using namespace cocos2d;
using namespace std;

NS_CC_EXT_BEGIN

// Implementation of CCBAinmationManager

CCBAnimationManager::CCBAnimationManager()
: _jsControlled(false)
, _owner(NULL)
, _sequences(NULL)
, _nodeSequences(NULL)
, _baseValues(NULL)
, _autoPlaySequenceId(0)
, _rootNode(NULL)
, _rootContainerSize(Size::ZERO)
, _delegate(NULL)
, _runningSequence(NULL)

{
    init();
}

bool CCBAnimationManager::init()
{
    _sequences = new Array();
    _nodeSequences = new Dictionary();
    _baseValues = new Dictionary();
    
    _documentOutletNames = new Array();
    _documentOutletNodes = new Array();
    _documentCallbackNames = new Array();
    _documentCallbackNodes = new Array();
    _keyframeCallbacks = new Array();
    _keyframeCallFuncs = new Dictionary();

    _target = NULL;
    _animationCompleteCallbackFunc = NULL;
    
    return true;
}

CCBAnimationManager::~CCBAnimationManager()
{
//     DictElement *pElement = NULL;
//     CCDICT_FOREACH(_nodeSequences, pElement)
//     {
//         Node *node = (Node*)pElement->getIntKey();
//         node->release();
//     }
//     
//     CCDICT_FOREACH(_baseValues, pElement)
//     {
//         Node *node = (Node*)pElement->getIntKey();
//         node->release();
//     }
    
    _nodeSequences->release();
    _baseValues->release();
    _sequences->release();
    setRootNode(NULL);
    setDelegate(NULL);

    CC_SAFE_RELEASE(_documentOutletNames);
    CC_SAFE_RELEASE(_documentOutletNodes);
    CC_SAFE_RELEASE(_documentCallbackNames);
    CC_SAFE_RELEASE(_documentCallbackNodes);
    
    CC_SAFE_RELEASE(_keyframeCallFuncs);
    CC_SAFE_RELEASE(_keyframeCallbacks);
    CC_SAFE_RELEASE(_target);
}

Array* CCBAnimationManager::getSequences()
{
    return _sequences;
}

void CCBAnimationManager::setSequences(Array* seq)
{
    _sequences = seq;
}

int CCBAnimationManager::getAutoPlaySequenceId()
{
    return _autoPlaySequenceId;
}

void CCBAnimationManager::setAutoPlaySequenceId(int autoPlaySequenceId)
{
    _autoPlaySequenceId = autoPlaySequenceId;
}

Node* CCBAnimationManager::getRootNode()
{
    return _rootNode;
}

void CCBAnimationManager::setRootNode(Node *pRootNode)
{
    _rootNode = pRootNode;
}

void CCBAnimationManager::setDocumentControllerName(const std::string &name) {
    _documentControllerName = name;
}


std::string CCBAnimationManager::getDocumentControllerName() {
    return _documentControllerName;
}

void CCBAnimationManager::addDocumentCallbackNode(Node *node) {
    _documentCallbackNodes->addObject(node);
}

void CCBAnimationManager::addDocumentCallbackName(std::string name) {
    String *tmpName = String::create(name);
    _documentCallbackNames->addObject(tmpName);
}

Array* CCBAnimationManager::getDocumentCallbackNames() {
    return _documentCallbackNames;
}

Array* CCBAnimationManager::getDocumentCallbackNodes() {
    return _documentCallbackNodes;
}

void CCBAnimationManager::addDocumentOutletNode(Node *node) {
    _documentOutletNodes->addObject(node);
}

void CCBAnimationManager::addDocumentOutletName(std::string name) {
    _documentOutletNames->addObject(String::create(name));
}

Array* CCBAnimationManager::getDocumentOutletNames() {
    return _documentOutletNames;
}

Array* CCBAnimationManager::getDocumentOutletNodes() {
    return _documentOutletNodes;
}

std::string CCBAnimationManager::getLastCompletedSequenceName() {
    return _lastCompletedSequenceName;
}

Array* CCBAnimationManager::getKeyframeCallbacks() {
    return _keyframeCallbacks;
}

const Size& CCBAnimationManager::getRootContainerSize()
{
    return _rootContainerSize;
}

void CCBAnimationManager::setRootContainerSize(const Size &rootContainerSize)
{
    _rootContainerSize.setSize(rootContainerSize.width, rootContainerSize.height);
}

CCBAnimationManagerDelegate* CCBAnimationManager::getDelegate()
{
    return _delegate;
}

void CCBAnimationManager::setDelegate(CCBAnimationManagerDelegate *pDelegate)
{
    CC_SAFE_RELEASE(dynamic_cast<Object*>(_delegate));
    _delegate = pDelegate;
    CC_SAFE_RETAIN(dynamic_cast<Object*>(_delegate));
}

const char* CCBAnimationManager::getRunningSequenceName()
{
    if (_runningSequence)
    {
        return _runningSequence->getName();
    }
    return NULL;
}

const Size& CCBAnimationManager::getContainerSize(Node *pNode)
{
    if (pNode)
    {
        return pNode->getContentSize();
    }
    else 
    {
        return _rootContainerSize;
    }
}

// refer to CCBReader::readNodeGraph() for data structure of pSeq
void CCBAnimationManager::addNode(Node *pNode, Dictionary *pSeq)
{
    // pNode->retain();
    
    _nodeSequences->setObject(pSeq, (intptr_t)pNode);
}

void CCBAnimationManager::setBaseValue(Object *pValue, Node *pNode, const char *propName)
{
    Dictionary *props = (Dictionary*)_baseValues->objectForKey((intptr_t)pNode);
    if (! props)
    {
        props = Dictionary::create();
        _baseValues->setObject(props, (intptr_t)pNode);
        // pNode->retain();
    }
    
    props->setObject(pValue, propName);
}

Object* CCBAnimationManager::getBaseValue(Node *pNode, const char* propName)
{
    Dictionary *props = (Dictionary*)_baseValues->objectForKey((intptr_t)pNode);
    
    return props->objectForKey(propName);
}

int CCBAnimationManager::getSequenceId(const char* pSequenceName)
{
    Object *pElement = NULL;
    string seqName(pSequenceName);
    CCARRAY_FOREACH(_sequences, pElement)
    {
        CCBSequence *seq = static_cast<CCBSequence*>(pElement);
        if (seqName.compare(seq->getName()) == 0)
        {
            return seq->getSequenceId();
        }
    }
    return -1;
}

CCBSequence* CCBAnimationManager::getSequence(int nSequenceId)
{
    Object *pElement = NULL;
    CCARRAY_FOREACH(_sequences, pElement)
    {
        CCBSequence *seq = static_cast<CCBSequence*>(pElement);
        if (seq->getSequenceId() == nSequenceId)
        {
            return seq;
        }
    }
    return NULL;
}


void CCBAnimationManager::moveAnimationsFromNode(Node* fromNode, Node* toNode) {

    // Move base values
    Object* baseValue = _baseValues->objectForKey((intptr_t)fromNode);
    if(baseValue) {
        _baseValues->setObject(baseValue, (intptr_t)toNode);
        _baseValues->removeObjectForKey((intptr_t)fromNode);

//         fromNode->release();
//         toNode->retain();
    }
    
    // Move seqs
    Object *seqs = _nodeSequences->objectForKey((intptr_t)fromNode);
    if(seqs) {
        _nodeSequences->setObject(seqs, (intptr_t)toNode);
        _nodeSequences->removeObjectForKey((intptr_t)fromNode);

//         fromNode->release();
//         toNode->retain();
    }
}

// Refer to CCBReader::readKeyframe() for the real type of value
ActionInterval* CCBAnimationManager::getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *propName, Node *pNode)
{
    float duration = pKeyframe1->getTime() - (pKeyframe0 ? pKeyframe0->getTime() : 0);
    
    if (strcmp(propName, "rotationX") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return CCBRotateXTo::create(duration, value->getFloatValue());
    }
    else if(strcmp(propName, "rotationY") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return CCBRotateYTo::create(duration, value->getFloatValue());
    }
    else if (strcmp(propName, "rotation") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return CCBRotateTo::create(duration, value->getFloatValue());
    } 
    else if (strcmp(propName, "opacity") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return FadeTo::create(duration, value->getByteValue());
    }
    else if (strcmp(propName, "color") == 0)
    {
        Color3BWapper* color = (Color3BWapper*)pKeyframe1->getValue();
        Color3B c = color->getColor();
        
        return TintTo::create(duration, c.r, c.g, c.b);
    }
    else if (strcmp(propName, "visible") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        if (value->getBoolValue())
        {
            return Sequence::createWithTwoActions(DelayTime::create(duration), Show::create());
        }
        else 
        {
            return Sequence::createWithTwoActions(DelayTime::create(duration), Hide::create());
        }
    }
    else if (strcmp(propName, "displayFrame") == 0)
    {
        return Sequence::createWithTwoActions(DelayTime::create(duration),
                                                CCBSetSpriteFrame::create((SpriteFrame *)pKeyframe1->getValue()));
    }
    else if (strcmp(propName, "position") == 0)
    {
        // Get position type
        Array *array = static_cast<Array*>(getBaseValue(pNode, propName));
        CCBReader::PositionType type = (CCBReader::PositionType)((CCBValue*)array->objectAtIndex(2))->getIntValue();
        
        // Get relative position
        Array *value = static_cast<Array*>(pKeyframe1->getValue());
        float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
        float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
        
        Size containerSize = getContainerSize(pNode->getParent());
        
        Point absPos = getAbsolutePosition(Point(x,y), type, containerSize, propName);
        
        return MoveTo::create(duration, absPos);
    }
    else if (strcmp(propName, "scale") == 0)
    {
        // Get position type
        Array *array = (Array*)getBaseValue(pNode, propName);
        CCBReader::ScaleType type = (CCBReader::ScaleType)((CCBValue*)array->objectAtIndex(2))->getIntValue();
        
        // Get relative scale
        Array *value = (Array*)pKeyframe1->getValue();
        float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
        float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
        
        if (type == CCBReader::ScaleType::MULTIPLY_RESOLUTION)
        {
            float resolutionScale = CCBReader::getResolutionScale();
            x *= resolutionScale;
            y *= resolutionScale;
        }
        
        return ScaleTo::create(duration, x, y);
    }
    else if(strcmp(propName, "skew") == 0) 
    {
        // Get relative skew
        Array *value = (Array*)pKeyframe1->getValue();
        float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
        float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
        
        return SkewTo::create(duration, x, y);
    }
    else 
    {
        log("CCBReader: Failed to create animation for property: %s", propName);
    }
    
    return NULL;
}

void CCBAnimationManager::setAnimatedProperty(const char *propName, Node *pNode, Object *pValue, float fTweenDuration)
{
    if (fTweenDuration > 0)
    {
        // Create a fake keyframe to generate the action from
        CCBKeyframe *kf1 = new CCBKeyframe();
        kf1->autorelease();
        kf1->setValue(pValue);
        kf1->setTime(fTweenDuration);
        kf1->setEasingType(CCBKeyframe::EasingType::LINEAR);
        
        // Animate
        ActionInterval *tweenAction = getAction(NULL, kf1, propName, pNode);
        pNode->runAction(tweenAction);
    }
    else 
    {
        // Just set the value
        
        if (strcmp(propName, "position") == 0)
        {
            // Get position type
            Array *array = (Array*)getBaseValue(pNode, propName);
            CCBReader::PositionType type = (CCBReader::PositionType)((CCBValue*)array->objectAtIndex(2))->getIntValue();
            
            // Get relative position
            Array *value = (Array*)pValue;
            float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
            float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
            
            pNode->setPosition(getAbsolutePosition(Point(x,y), type, getContainerSize(pNode->getParent()), propName));
        }
        else if (strcmp(propName, "scale") == 0)
        {
            // Get scale type
            Array *array = (Array*)getBaseValue(pNode, propName);
            CCBReader::ScaleType type = (CCBReader::ScaleType)((CCBValue*)array->objectAtIndex(2))->getIntValue();
            
            // Get relative scale
            Array *value = (Array*)pValue;
            float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
            float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
            
            setRelativeScale(pNode, x, y, type, propName);
        }
        else if(strcmp(propName, "skew") == 0)
        {
            // Get relative scale
            Array *value = (Array*)pValue;
            float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
            float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();

            pNode->setSkewX(x);
            pNode->setSkewY(y);
        }
        else 
        {
            // [node setValue:value forKey:name];

            // TODO only handle rotation, opacity, displayFrame, color
            if (strcmp(propName, "rotation") == 0)
            {
                float rotate = ((CCBValue*)pValue)->getFloatValue();
                pNode->setRotation(rotate);
            } else if(strcmp(propName, "rotationX") == 0)
            {
                float rotate = ((CCBValue*)pValue)->getFloatValue();
                pNode->setRotationX(rotate);
            }else if(strcmp(propName, "rotationY") == 0)
            {
                float rotate = ((CCBValue*)pValue)->getFloatValue();
                pNode->setRotationY(rotate);
            }
            else if (strcmp(propName, "opacity") == 0)
            {
                int opacity = ((CCBValue*)pValue)->getByteValue();
                (dynamic_cast<RGBAProtocol*>(pNode))->setOpacity(opacity);
            }
            else if (strcmp(propName, "displayFrame") == 0)
            {
                ((Sprite*)pNode)->setDisplayFrame((SpriteFrame*)pValue);
            }
            else if (strcmp(propName, "color") == 0)
            {
                Color3BWapper *color = (Color3BWapper*)pValue;
                (dynamic_cast<RGBAProtocol*>(pNode))->setColor(color->getColor());
            }
            else if (strcmp(propName, "visible") == 0)
            {
                bool visible = ((CCBValue*)pValue)->getBoolValue();
                pNode->setVisible(visible);
            }
            else
            {
                log("unsupported property name is %s", propName);
                CCASSERT(false, "unsupported property now");
            }
        }
    }
}

void CCBAnimationManager::setFirstFrame(Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration)
{
    Array *keyframes = pSeqProp->getKeyframes();
    
    if (keyframes->count() == 0)
    {
        // Use base value (no animation)
        Object *baseValue = getBaseValue(pNode, pSeqProp->getName());
        CCASSERT(baseValue, "No baseValue found for property");
        setAnimatedProperty(pSeqProp->getName(), pNode, baseValue, fTweenDuration);
    }
    else 
    {
        // Use first keyframe
        CCBKeyframe *keyframe = (CCBKeyframe*)keyframes->objectAtIndex(0);
        setAnimatedProperty(pSeqProp->getName(), pNode, keyframe->getValue(), fTweenDuration);
    }
}

ActionInterval* CCBAnimationManager::getEaseAction(ActionInterval *pAction, CCBKeyframe::EasingType easingType, float fEasingOpt)
{
    if (dynamic_cast<Sequence*>(pAction))
    {
        return pAction;
    }
    
    if (easingType == CCBKeyframe::EasingType::LINEAR)
    {
        return pAction;
    }
    else if (easingType == CCBKeyframe::EasingType::INSTANT)
    {
        return CCBEaseInstant::create(pAction);
    }
    else if (easingType == CCBKeyframe::EasingType::CUBIC_IN)
    {
        return EaseIn::create(pAction, fEasingOpt);
    }
    else if (easingType == CCBKeyframe::EasingType::CUBIC_OUT)
    {
        return EaseOut::create(pAction, fEasingOpt);
    }
    else if (easingType == CCBKeyframe::EasingType::CUBIC_INOUT)
    {
        return EaseInOut::create(pAction, fEasingOpt);
    }
    else if (easingType == CCBKeyframe::EasingType::BACK_IN)
    {
        return EaseBackIn::create(pAction);
    }
    else if (easingType == CCBKeyframe::EasingType::BACK_OUT)
    {
        return EaseBackOut::create(pAction);
    }
    else if (easingType == CCBKeyframe::EasingType::BACK_INOUT)
    {
        return EaseBackInOut::create(pAction);
    }
    else if (easingType == CCBKeyframe::EasingType::BOUNCE_IN)
    {
        return EaseBounceIn::create(pAction);
    }
    else if (easingType == CCBKeyframe::EasingType::BOUNCE_OUT)
    {
        return EaseBounceOut::create(pAction);
    }
    else if (easingType == CCBKeyframe::EasingType::BOUNCE_INOUT)
    {
        return EaseBounceInOut::create(pAction);
    }
    else if (easingType == CCBKeyframe::EasingType::ELASTIC_IN)
    {
        return EaseElasticIn::create(pAction, fEasingOpt);
    }
    else if (easingType == CCBKeyframe::EasingType::ELASTIC_OUT)
    {
        return EaseElasticOut::create(pAction, fEasingOpt);
    }
    else if (easingType == CCBKeyframe::EasingType::ELASTIC_INOUT)
    {
        return EaseElasticInOut::create(pAction, fEasingOpt);
    }
    else
    {
        log("CCBReader: Unkown easing type %d", easingType);
        return pAction;
    }
}

Object* CCBAnimationManager::actionForCallbackChannel(CCBSequenceProperty* channel) {
  
    float lastKeyframeTime = 0;
    
    Array *actions = Array::create();
    Array *keyframes = channel->getKeyframes();
    int numKeyframes = keyframes->count();

    for (int i = 0; i < numKeyframes; ++i)
    {

        CCBKeyframe *keyframe = (CCBKeyframe*)keyframes->objectAtIndex(i);
        float timeSinceLastKeyframe = keyframe->getTime() - lastKeyframeTime;
        lastKeyframeTime = keyframe->getTime();
        if(timeSinceLastKeyframe > 0) {
            actions->addObject(DelayTime::create(timeSinceLastKeyframe));
        }
	
        Array* keyVal = static_cast<Array *>(keyframe->getValue());
        std::string selectorName = static_cast<String *>(keyVal->objectAtIndex(0))->getCString();
        CCBReader::TargetType selectorTarget = (CCBReader::TargetType)atoi(static_cast<String *>(keyVal->objectAtIndex(1))->getCString());
	
        if(_jsControlled) {
            String* callbackName = String::createWithFormat("%d:%s", selectorTarget, selectorName.c_str());
            CallFunc *callback = ((CallFunc*)(_keyframeCallFuncs->objectForKey(callbackName->getCString())))->clone();

            if(callback != NULL) {
                actions->addObject(callback);
            }
        }
        else
        {
            Object* target = NULL;
            
            if(selectorTarget == CCBReader::TargetType::DOCUMENT_ROOT)
                target = _rootNode;
            else if (selectorTarget == CCBReader::TargetType::OWNER)
                target = _owner;
            
            if(target != NULL)
            {
                if(selectorName.length() > 0)
                {
                    SEL_CallFuncN selCallFunc = 0;
                    
                    CCBSelectorResolver* targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);

                    if(targetAsCCBSelectorResolver != NULL)
                    {
                        selCallFunc = targetAsCCBSelectorResolver->onResolveCCBCCCallFuncSelector(target, selectorName.c_str    ());
                    }
                    
                    if(selCallFunc == 0)
                    {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    }
                    else
                    {
                        CallFuncN *callback = CallFuncN::create(target, selCallFunc);
                        actions->addObject(callback);
                    }
                }
                else
                {
                    CCLOG("Unexpected empty selector.");
                }
            }
        }
    }
    if(actions->count() < 1) return NULL;
    
    return (Object *) Sequence::create(actions);
}

Object* CCBAnimationManager::actionForSoundChannel(CCBSequenceProperty* channel) {
    
    float lastKeyframeTime = 0;
    
    Array *actions = Array::create();
    Array *keyframes = channel->getKeyframes();
    int numKeyframes = keyframes->count();

    for (int i = 0; i < numKeyframes; ++i) {

        CCBKeyframe *keyframe = (CCBKeyframe*)keyframes->objectAtIndex(i);
        float timeSinceLastKeyframe = keyframe->getTime() - lastKeyframeTime;
        lastKeyframeTime = keyframe->getTime();
        if(timeSinceLastKeyframe > 0) {
            actions->addObject(DelayTime::create(timeSinceLastKeyframe));
        }
	
        stringstream ss (stringstream::in | stringstream::out);
        Array* keyVal = (Array*)keyframe->getValue();
        std::string soundFile = ((String *)keyVal->objectAtIndex(0))->getCString();
    
        float pitch, pan, gain;
        ss << ((String *)keyVal->objectAtIndex(1))->getCString();
        ss >> pitch;
        ss.flush();
    
        ss << ((String *)keyVal->objectAtIndex(2))->getCString();
        ss >> pan;
        ss.flush();
        
        ss << ((String *)keyVal->objectAtIndex(3))->getCString();
        ss >> gain;
        ss.flush();
        
        actions->addObject(CCBSoundEffect::actionWithSoundFile(soundFile, pitch, pan, gain));
    }

    if(actions->count() < 1) return NULL;
    
    return (Object *) Sequence::create(actions);    
}



void CCBAnimationManager::runAction(Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration)
{
    Array *keyframes = pSeqProp->getKeyframes();
    int numKeyframes = keyframes->count();
    
    if (numKeyframes > 1)
    {
        // Make an animation!
        Array *actions = Array::create();
        
        CCBKeyframe *keyframeFirst = (CCBKeyframe*)keyframes->objectAtIndex(0);
        float timeFirst = keyframeFirst->getTime() + fTweenDuration;
        
        if (timeFirst > 0)
        {
            actions->addObject(DelayTime::create(timeFirst));
        }
        
        for (int i = 0; i < numKeyframes - 1; ++i)
        {
            CCBKeyframe *kf0 = (CCBKeyframe*)keyframes->objectAtIndex(i);
            CCBKeyframe *kf1 = (CCBKeyframe*)keyframes->objectAtIndex(i+1);
            
            ActionInterval *action = getAction(kf0, kf1, pSeqProp->getName(), pNode);
            if (action)
            {
                // Apply easing
                action = getEaseAction(action, kf0->getEasingType(), kf0->getEasingOpt());
                
                actions->addObject(action);
            }
        }
        
        FiniteTimeAction *seq = Sequence::create(actions);
        pNode->runAction(seq);
    }
}

void CCBAnimationManager::runAnimations(const char *pName, float fTweenDuration)
{
    runAnimationsForSequenceNamedTweenDuration(pName, fTweenDuration);
}

void CCBAnimationManager::runAnimations(const char *pName)
{
    runAnimationsForSequenceNamed(pName);
}
    
void CCBAnimationManager::runAnimations(int nSeqId, float fTweenDuraiton)
{
    runAnimationsForSequenceIdTweenDuration(nSeqId, fTweenDuraiton);
}

void CCBAnimationManager::runAnimationsForSequenceIdTweenDuration(int nSeqId, float fTweenDuration)
{
    CCASSERT(nSeqId != -1, "Sequence id couldn't be found");
    
    _rootNode->stopAllActions();
    
    DictElement* pElement = NULL;
    CCDICT_FOREACH(_nodeSequences, pElement)
    {
        Node *node = reinterpret_cast<Node*>(pElement->getIntKey());
        node->stopAllActions();
        
        // Refer to CCBReader::readKeyframe() for the real type of value
        Dictionary *seqs = (Dictionary*)pElement->getObject();
        Dictionary *seqNodeProps = (Dictionary*)seqs->objectForKey(nSeqId);
        
        set<string> seqNodePropNames;
        
        if (seqNodeProps)
        {
            // Reset nodes that have sequence node properties, and run actions on them
            DictElement* pElement1 = NULL;
            CCDICT_FOREACH(seqNodeProps, pElement1)
            {
                const char *propName = pElement1->getStrKey();
                CCBSequenceProperty *seqProp = static_cast<CCBSequenceProperty*>(seqNodeProps->objectForKey(propName));
                seqNodePropNames.insert(propName);
                
                setFirstFrame(node, seqProp, fTweenDuration);
                runAction(node, seqProp, fTweenDuration);
            }
        }
        
        // Reset the nodes that may have been changed by other timelines
        Dictionary *nodeBaseValues = (Dictionary*)_baseValues->objectForKey(pElement->getIntKey());
        if (nodeBaseValues)
        {
            DictElement* pElement2 = NULL;
            CCDICT_FOREACH(nodeBaseValues, pElement2)
            {
                if (seqNodePropNames.find(pElement2->getStrKey()) == seqNodePropNames.end())
                {
                    Object *value = pElement2->getObject();
                    
                    if (value)
                    {
                       setAnimatedProperty(pElement2->getStrKey(), node, value, fTweenDuration);
                    }
                }
            }
        }
    }
    
    // Make callback at end of sequence
    CCBSequence *seq = getSequence(nSeqId);
    Action *completeAction = Sequence::createWithTwoActions(DelayTime::create(seq->getDuration() + fTweenDuration),
                                                                CallFunc::create( CC_CALLBACK_0(CCBAnimationManager::sequenceCompleted,this)));
    _rootNode->runAction(completeAction);
    
    // Set the running scene

    if(seq->getCallbackChannel() != NULL) {
        Action* action = (Action *)actionForCallbackChannel(seq->getCallbackChannel());
        if(action != NULL) {
            _rootNode->runAction(action);
        }
    } 

    if(seq->getSoundChannel() != NULL) {
        Action* action = (Action *)actionForSoundChannel(seq->getSoundChannel());
        if(action != NULL) {
            _rootNode->runAction(action);
        }
    }

    _runningSequence = getSequence(nSeqId);
}

void CCBAnimationManager::runAnimationsForSequenceNamedTweenDuration(const char *pName, float fTweenDuration)
{
    int seqId = getSequenceId(pName);
    runAnimationsForSequenceIdTweenDuration(seqId, fTweenDuration);
}

void CCBAnimationManager::runAnimationsForSequenceNamed(const char *pName)
{
    runAnimationsForSequenceNamedTweenDuration(pName, 0);
}

void CCBAnimationManager::debug()
{
    
}

void CCBAnimationManager::setAnimationCompletedCallback(Object *target, SEL_CallFunc callbackFunc) {
    if (target)
    {
        target->retain();
    }
    
    if (_target)
    {
        _target->release();
    }
    
    _target = target;
    _animationCompleteCallbackFunc = callbackFunc;
}

void CCBAnimationManager::setCallFunc(CallFunc* callFunc, const std::string &callbackNamed) {
    _keyframeCallFuncs->setObject((Object*)callFunc, callbackNamed);
}

void CCBAnimationManager::sequenceCompleted()
{
    const char *runningSequenceName = _runningSequence->getName();
    int nextSeqId = _runningSequence->getChainedSequenceId();
    _runningSequence = NULL;
    
    if(_lastCompletedSequenceName != runningSequenceName) {
        _lastCompletedSequenceName = runningSequenceName;
    }
    
    if (_delegate)
    {
        // There may be another runAnimation() call in this delegate method
        // which will assign _runningSequence
        _delegate->completedAnimationSequenceNamed(runningSequenceName);
    }
    
    if (_target && _animationCompleteCallbackFunc) {
        (_target->*_animationCompleteCallbackFunc)();
    }
    
    if (nextSeqId != -1)
    {
        runAnimationsForSequenceIdTweenDuration(nextSeqId, 0);
    }
}

// Custom actions

/************************************************************
 CCBSetSpriteFrame
 ************************************************************/

CCBSetSpriteFrame* CCBSetSpriteFrame::create(SpriteFrame *pSpriteFrame)
{
    CCBSetSpriteFrame *ret = new CCBSetSpriteFrame();
    if (ret)
    {
        if (ret->initWithSpriteFrame(pSpriteFrame))
        {
            ret->autorelease();
        }
        else 
        {
            CC_SAFE_DELETE(ret);
        }
    }
    
    return ret;
}

bool CCBSetSpriteFrame::initWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    _spriteFrame = pSpriteFrame;
    CC_SAFE_RETAIN(_spriteFrame);
    
    return true;
}

CCBSetSpriteFrame::~CCBSetSpriteFrame()
{
    CC_SAFE_RELEASE_NULL(_spriteFrame);
}

CCBSetSpriteFrame* CCBSetSpriteFrame::clone() const
{
	// no copy constructor
	auto a = new CCBSetSpriteFrame();
    a->initWithSpriteFrame(_spriteFrame);
	a->autorelease();
	return a;
}

CCBSetSpriteFrame* CCBSetSpriteFrame::reverse() const
{
	// returns a copy of itself
	return this->clone();
}

void CCBSetSpriteFrame::update(float time)
{
    ((Sprite*)_target)->setDisplayFrame(_spriteFrame);
}


/************************************************************
 CCBSoundEffect
 ************************************************************/

CCBSoundEffect* CCBSoundEffect::actionWithSoundFile(const std::string &filename, float pitch, float pan, float gain) {
  CCBSoundEffect* pRet = new CCBSoundEffect();
  if (pRet != NULL && pRet->initWithSoundFile(filename, pitch, pan, gain))
    {
      pRet->autorelease();
    }
  else
    {
      CC_SAFE_DELETE(pRet);
    }
  return pRet;
}


CCBSoundEffect::~CCBSoundEffect()
{
}

bool CCBSoundEffect::initWithSoundFile(const std::string &filename, float pitch, float pan, float gain) {
    _soundFile = filename;
    _pitch = pitch;
    _pan = pan;
    _gain = gain;
    return true;
}

CCBSoundEffect* CCBSoundEffect::clone() const
{
	// no copy constructor
	auto a = new CCBSoundEffect();
    a->initWithSoundFile(_soundFile, _pitch, _pan, _gain);
	a->autorelease();
	return a;
}

CCBSoundEffect* CCBSoundEffect::reverse() const
{
	// returns a copy of itself
	return this->clone();
}

void CCBSoundEffect::update(float time)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(_soundFile.c_str());
}


/************************************************************
 CCBRotateTo
 ************************************************************/

CCBRotateTo* CCBRotateTo::create(float fDuration, float fAngle)
{
    CCBRotateTo *ret = new CCBRotateTo();
    if (ret)
    {
        if (ret->initWithDuration(fDuration, fAngle))
        {
            ret->autorelease();
        }
        else 
        {
            CC_SAFE_DELETE(ret);
        }
    }
    
    return ret;
}

bool CCBRotateTo::initWithDuration(float fDuration, float fAngle)
{
    if (ActionInterval::initWithDuration(fDuration))
    {
        _dstAngle = fAngle;
        
        return true;
    }
    else 
    {
        return false;
    }
}

CCBRotateTo* CCBRotateTo::clone() const
{
	// no copy constructor	
	auto a = new CCBRotateTo();
    a->initWithDuration(_duration, _dstAngle);
	a->autorelease();
	return a;
}

CCBRotateTo* CCBRotateTo::reverse() const
{
	CCASSERT(false, "reverse() is not supported in CCBRotateTo");
	return nullptr;
}

void CCBRotateTo::startWithTarget(Node *pNode)
{
    ActionInterval::startWithTarget(pNode);
    _startAngle = _target->getRotation();
    _diffAngle = _dstAngle - _startAngle;
}

void CCBRotateTo::update(float time)
{
    _target->setRotation(_startAngle + (_diffAngle * time))
    ;
}




/************************************************************
 CCBRotateXTO
 ************************************************************/


CCBRotateXTo* CCBRotateXTo::create(float fDuration, float fAngle)
{
    CCBRotateXTo *ret = new CCBRotateXTo();
    if (ret)
    {
        if (ret->initWithDuration(fDuration, fAngle))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
    }
    
    return ret;
}

bool CCBRotateXTo::initWithDuration(float fDuration, float fAngle)
{
    if (ActionInterval::initWithDuration(fDuration))
    {
        _dstAngle = fAngle;
        
        return true;
    }
    else
    {
        return false;
    }
}


void CCBRotateXTo::startWithTarget(Node *pNode)
{
    //CCActionInterval::startWithTarget(pNode);
    _originalTarget = pNode;
    _target = pNode;
    _elapsed = 0.0f;
    _firstTick = true;
    _startAngle = _target->getRotationX();
    _diffAngle = _dstAngle - _startAngle;
}

CCBRotateXTo* CCBRotateXTo::clone() const
{
	// no copy constructor
	auto a = new CCBRotateXTo();
    a->initWithDuration(_duration, _dstAngle);
	a->autorelease();
	return a;
}

CCBRotateXTo* CCBRotateXTo::reverse() const
{
	CCASSERT(false, "reverse() is not supported in CCBRotateXTo");
	return nullptr;
}

void CCBRotateXTo::update(float time)
{
    _target->setRotationX(_startAngle + (_diffAngle * time))
    ;
}



/************************************************************
 CCBRotateYTO
 ************************************************************/



CCBRotateYTo* CCBRotateYTo::create(float fDuration, float fAngle)
{
    CCBRotateYTo *ret = new CCBRotateYTo();
    if (ret)
    {
        if (ret->initWithDuration(fDuration, fAngle))
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
    }
    
    return ret;
}

bool CCBRotateYTo::initWithDuration(float fDuration, float fAngle)
{
    if (ActionInterval::initWithDuration(fDuration))
    {
        _dstAngle = fAngle;
        
        return true;
    }
    else
    {
        return false;
    }
}

CCBRotateYTo* CCBRotateYTo::clone() const
{
	// no copy constructor
	auto a = new CCBRotateYTo();
    a->initWithDuration(_duration, _dstAngle);
	a->autorelease();
	return a;
}

CCBRotateYTo* CCBRotateYTo::reverse() const
{
	CCASSERT(false, "reverse() is not supported in CCBRotateXTo");
	return nullptr;
}


void CCBRotateYTo::startWithTarget(Node *pNode)
{
 //   ActionInterval::startWithTarget(pNode);
    _originalTarget = pNode;
    _target = pNode;
    _elapsed = 0.0f;
    _firstTick = true;
    _startAngle = _target->getRotationY();
    _diffAngle = _dstAngle - _startAngle;
}

void CCBRotateYTo::update(float time)
{
    _target->setRotationY(_startAngle + (_diffAngle * time))
    ;
}



/************************************************************
 CCBEaseInstant
 ************************************************************/
CCBEaseInstant* CCBEaseInstant::create(ActionInterval *pAction)
{
    CCBEaseInstant *pRet = new CCBEaseInstant();
    if (pRet && pRet->initWithAction(pAction))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL(pRet);
    }
    
    return pRet;
}

CCBEaseInstant* CCBEaseInstant::clone() const
{
	// no copy constructor	
	auto a = new CCBEaseInstant();
    a->initWithAction(_inner);
	a->autorelease();
	return a;
}

CCBEaseInstant* CCBEaseInstant::reverse() const
{
	return CCBEaseInstant::create(_inner->reverse());
}

void CCBEaseInstant::update(float dt)
{
    if (dt < 0)
    {
        _inner->update(0);
    }
    else
    {
        _inner->update(1);
    }
}


NS_CC_EXT_END
