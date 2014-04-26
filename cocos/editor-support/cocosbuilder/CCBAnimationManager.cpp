#include "CCBAnimationManager.h"
#include "CCBSequence.h"
#include "CCBSequenceProperty.h"
#include "CCBReader.h"
#include "CCBKeyframe.h"
#include "CCNode+CCBRelativePositioning.h"
#include "SimpleAudioEngine.h"
#include "CCBSelectorResolver.h"

#include <string>
#include <sstream>
#include <set>

using namespace cocos2d;
using namespace std;
using namespace cocos2d::extension;

namespace cocosbuilder {

// Implementation of CCBAinmationManager

CCBAnimationManager::CCBAnimationManager()
: _jsControlled(false)
, _owner(nullptr)
, _autoPlaySequenceId(0)
, _rootNode(nullptr)
, _rootContainerSize(Size::ZERO)
, _delegate(nullptr)
, _runningSequence(nullptr)
{
    init();
}

bool CCBAnimationManager::init()
{
    _target = nullptr;
    _animationCompleteCallbackFunc = nullptr;
    
    return true;
}

CCBAnimationManager::~CCBAnimationManager()
{
//     DictElement *pElement = nullptr;
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
    if (_rootNode)
    {
        _rootNode->stopAllActions();
    }
    
    setRootNode(nullptr);
    setDelegate(nullptr);
    
    for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
    {
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
        {
            iter2->second->release();
        }
    }
    
    CC_SAFE_RELEASE(_target);
}

Vector<CCBSequence*>& CCBAnimationManager::getSequences()
{
    return _sequences;
}

void CCBAnimationManager::setSequences(const Vector<CCBSequence*>& seq)
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

void CCBAnimationManager::setDocumentControllerName(const std::string &name)
{
    _documentControllerName = name;
}


std::string CCBAnimationManager::getDocumentControllerName()
{
    return _documentControllerName;
}

void CCBAnimationManager::addDocumentCallbackNode(Node *node)
{
    _documentCallbackNodes.pushBack(node);
}

void CCBAnimationManager::addDocumentCallbackName(std::string name)
{
    _documentCallbackNames.push_back(Value(name));
}

void CCBAnimationManager::addDocumentCallbackControlEvents(Control::EventType eventType)
{
    _documentCallbackControlEvents.push_back(Value(static_cast<int>(eventType)));
}

ValueVector& CCBAnimationManager::getDocumentCallbackNames()
{
    return _documentCallbackNames;
}

Vector<Node*>& CCBAnimationManager::getDocumentCallbackNodes()
{
    return _documentCallbackNodes;
}

ValueVector& CCBAnimationManager::getDocumentCallbackControlEvents()
{
    return _documentCallbackControlEvents;
}

void CCBAnimationManager::addDocumentOutletNode(Node *node)
{
    _documentOutletNodes.pushBack(node);
}

void CCBAnimationManager::addDocumentOutletName(std::string name)
{
    _documentOutletNames.push_back(Value(name));
}

ValueVector& CCBAnimationManager::getDocumentOutletNames()
{
    return _documentOutletNames;
}

Vector<Node*>& CCBAnimationManager::getDocumentOutletNodes()
{
    return _documentOutletNodes;
}

std::string CCBAnimationManager::getLastCompletedSequenceName()
{
    return _lastCompletedSequenceName;
}

ValueVector& CCBAnimationManager::getKeyframeCallbacks()
{
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
    CC_SAFE_RELEASE(dynamic_cast<Ref*>(_delegate));
    _delegate = pDelegate;
    CC_SAFE_RETAIN(dynamic_cast<Ref*>(_delegate));
}

const char* CCBAnimationManager::getRunningSequenceName()
{
    if (_runningSequence)
    {
        return _runningSequence->getName();
    }
    return nullptr;
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
void CCBAnimationManager::addNode(Node *pNode, const std::unordered_map<int, Map<std::string, CCBSequenceProperty*>>& seq)
{
    // pNode->retain();
    
    _nodeSequences[pNode] = seq;
}

void CCBAnimationManager::setBaseValue(const Value& value, Node *pNode, const std::string& propName)
{
    auto& props = _baseValues[pNode];
    props[propName] = value;
}

const Value& CCBAnimationManager::getBaseValue(Node *pNode, const std::string& propName)
{
    auto& props = _baseValues[pNode];
    return props[propName];
}
    
void CCBAnimationManager::setObject(Ref* obj, Node *pNode, const std::string& propName)
{
    auto& props = _objects[pNode];
    auto iter = props.find(propName);
    if (iter != props.end())
        iter->second->release();
        
    props[propName] = obj;
    obj->retain();
}

Ref* CCBAnimationManager::getObject(Node *pNode, const std::string& propName)
{
    auto& props = _objects[pNode];
    auto iter = props.find(propName);
    if (iter != props.end())
        return iter->second;
    
    return nullptr;
}

int CCBAnimationManager::getSequenceId(const char* pSequenceName)
{
    string seqName(pSequenceName);
    for (auto& seq : _sequences)
    {
        if (seqName.compare(seq->getName()) == 0)
        {
            return seq->getSequenceId();
        }
    }
    return -1;
}

CCBSequence* CCBAnimationManager::getSequence(int nSequenceId)
{
    for (auto& seq : _sequences)
    {
        if (seq->getSequenceId() == nSequenceId)
        {
            return seq;
        }
    }
    return nullptr;
}

float CCBAnimationManager::getSequenceDuration(const char *pSequenceName)
{
    int id = getSequenceId(pSequenceName);
    if (id != -1)
        return getSequence(id)->getDuration();
    return 0;
}


void CCBAnimationManager::moveAnimationsFromNode(Node* fromNode, Node* toNode)
{
    // Move base values
    auto baseValueIter = _baseValues.find(fromNode);
    if(baseValueIter != _baseValues.end())
    {
        _baseValues[toNode] = baseValueIter->second;
        _baseValues.erase(baseValueIter);
//         fromNode->release();
//         toNode->retain();
    }
    
    auto objIter = _objects.find(fromNode);
    if (objIter != _objects.end())
    {
        _objects[toNode] = objIter->second;
        _objects.erase(objIter);
    }
    
    
    // Move seqs
    auto seqsIter = _nodeSequences.find(fromNode);
    if (seqsIter != _nodeSequences.end())
    {
        _nodeSequences[toNode] = seqsIter->second;
        _nodeSequences.erase(seqsIter);
//         fromNode->release();
//         toNode->retain();
    }
}

// Refer to CCBReader::readKeyframe() for the real type of value
ActionInterval* CCBAnimationManager::getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const std::string& propName, Node *pNode)
{
    float duration = pKeyframe1->getTime() - (pKeyframe0 ? pKeyframe0->getTime() : 0);
    
    if (propName == "rotationX")
    {
        return CCBRotateXTo::create(duration, pKeyframe1->getValue().asFloat());
    }
    else if (propName == "rotationY")
    {
        return CCBRotateYTo::create(duration, pKeyframe1->getValue().asFloat());
    }
    else if (propName == "rotation")
    {
        return CCBRotateTo::create(duration, pKeyframe1->getValue().asFloat());
    } 
    else if (propName == "opacity")
    {
        return FadeTo::create(duration, pKeyframe1->getValue().asByte());
    }
    else if (propName == "color")
    {
        auto c = pKeyframe1->getValue().asValueMap();
        unsigned char r = c["r"].asByte();
        unsigned char g = c["g"].asByte();
        unsigned char b = c["b"].asByte();
        return TintTo::create(duration, r, g, b);
    }
    else if (propName == "visible")
    {
        if (pKeyframe1->getValue().asBool())
        {
            return Sequence::createWithTwoActions(DelayTime::create(duration), Show::create());
        }
        else 
        {
            return Sequence::createWithTwoActions(DelayTime::create(duration), Hide::create());
        }
    }
    else if (propName == "displayFrame")
    {
        return Sequence::createWithTwoActions(DelayTime::create(duration),
                    CCBSetSpriteFrame::create(static_cast<SpriteFrame*>(pKeyframe1->getObject())));
    }
    else if (propName == "position")
    {
        // Get position type
        auto& array = getBaseValue(pNode, propName).asValueVector();
        CCBReader::PositionType type = (CCBReader::PositionType)array[2].asInt();
        
        // Get relative position
        auto value = pKeyframe1->getValue().asValueVector();
        float x = value[0].asFloat();
        float y = value[1].asFloat();
        
        Size containerSize = getContainerSize(pNode->getParent());
        
        Vector2 absPos = getAbsolutePosition(Vector2(x,y), type, containerSize, propName);
        
        return MoveTo::create(duration, absPos);
    }
    else if (propName == "scale")
    {
        // Get position type
        auto& array = getBaseValue(pNode, propName).asValueVector();
        CCBReader::ScaleType type = (CCBReader::ScaleType)array[2].asInt();
        
        // Get relative scale
        auto value = pKeyframe1->getValue().asValueVector();
        float x = value[0].asFloat();
        float y = value[1].asFloat();
        
        if (type == CCBReader::ScaleType::MULTIPLY_RESOLUTION)
        {
            float resolutionScale = CCBReader::getResolutionScale();
            x *= resolutionScale;
            y *= resolutionScale;
        }
        
        return ScaleTo::create(duration, x, y);
    }
    else if (propName == "skew")
    {
        // Get relative skew
        auto& value = pKeyframe1->getValue().asValueVector();
        float x = value[0].asFloat();
        float y = value[1].asFloat();
        
        return SkewTo::create(duration, x, y);
    }
    else 
    {
        log("CCBReader: Failed to create animation for property: %s", propName.c_str());
    }
    
    return nullptr;
}

void CCBAnimationManager::setAnimatedProperty(const std::string& propName, Node *pNode, const Value& value, Ref* obj, float fTweenDuration)
{
    if (fTweenDuration > 0)
    {
        // Create a fake keyframe to generate the action from
        CCBKeyframe *kf1 = new CCBKeyframe();
        kf1->autorelease();
        
        kf1->setObject(obj);
        kf1->setValue(value);
        kf1->setTime(fTweenDuration);
        kf1->setEasingType(CCBKeyframe::EasingType::LINEAR);
        
        // Animate
        ActionInterval *tweenAction = getAction(nullptr, kf1, propName, pNode);
        pNode->runAction(tweenAction);
    }
    else 
    {
        // Just set the value
        
        if (propName == "position")
        {
            // Get position type
            auto& array = getBaseValue(pNode, propName).asValueVector();
            CCBReader::PositionType type = (CCBReader::PositionType)array[2].asInt();
            // Get relative position
            auto& valueVector = value.asValueVector();
            float x = valueVector[0].asFloat();
            float y = valueVector[1].asFloat();
            
            pNode->setPosition(getAbsolutePosition(Vector2(x,y), type, getContainerSize(pNode->getParent()), propName));
        }
        else if (propName == "scale")
        {
            // Get scale type
            auto& array = getBaseValue(pNode, propName).asValueVector();
            CCBReader::ScaleType type = (CCBReader::ScaleType)array[2].asInt();
            
            // Get relative scale
            auto& valueVector = value.asValueVector();
            float x = valueVector[0].asFloat();
            float y = valueVector[1].asFloat();
            
            setRelativeScale(pNode, x, y, type, propName);
        }
        else if(propName == "skew")
        {
            // Get relative scale
            auto& valueVector = value.asValueVector();
            float x = valueVector[0].asFloat();
            float y = valueVector[1].asFloat();

            pNode->setSkewX(x);
            pNode->setSkewY(y);
        }
        else 
        {
            // [node setValue:value forKey:name];

            // TODO only handle rotation, opacity, displayFrame, color
            if (propName == "rotation")
            {
                float rotate = value.asFloat();
                pNode->setRotation(rotate);
            } else if(propName == "rotationX")
            {
                float rotate = value.asFloat();
                pNode->setRotationSkewX(rotate);
            }else if(propName == "rotationY")
            {
                float rotate = value.asFloat();
                pNode->setRotationSkewY(rotate);
            }
            else if (propName == "opacity")
            {
                unsigned char opacity = value.asByte();
                pNode->setOpacity(opacity);
            }
            else if (propName == "displayFrame")
            {
                static_cast<Sprite*>(pNode)->setSpriteFrame(static_cast<SpriteFrame*>(obj));
            }
            else if (propName == "color")
            {
                auto c = value.asValueMap();
                unsigned char r = c["r"].asByte();
                unsigned char g = c["g"].asByte();
                unsigned char b = c["b"].asByte();
                pNode->setColor(Color3B(r, g, b));
            }
            else if (propName == "visible")
            {
                bool visible = value.asBool();
                pNode->setVisible(visible);
            }
            else
            {
                log("unsupported property name is %s", propName.c_str());
                CCASSERT(false, "unsupported property now");
            }
        }
    }
}

void CCBAnimationManager::setFirstFrame(Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration)
{
    auto& keyframes = pSeqProp->getKeyframes();
    
    if (keyframes.empty())
    {
        // Use base value (no animation)
        auto& baseValue = getBaseValue(pNode, pSeqProp->getName());
        auto obj = getObject(pNode, pSeqProp->getName());
        CCASSERT(!baseValue.isNull(), "No baseValue found for property");
        setAnimatedProperty(pSeqProp->getName(), pNode, baseValue, obj, fTweenDuration);
    }
    else 
    {
        // Use first keyframe
        CCBKeyframe *keyframe = keyframes.at(0);
        setAnimatedProperty(pSeqProp->getName(), pNode, keyframe->getValue(), keyframe->getObject(), fTweenDuration);
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

Sequence*  CCBAnimationManager::actionForCallbackChannel(CCBSequenceProperty* channel) {
  
    float lastKeyframeTime = 0;
    
    Vector<FiniteTimeAction*> actions;
    auto& keyframes = channel->getKeyframes();
    ssize_t numKeyframes = keyframes.size();

    for (long i = 0; i < numKeyframes; ++i)
    {

        CCBKeyframe *keyframe = keyframes.at(i);
        float timeSinceLastKeyframe = keyframe->getTime() - lastKeyframeTime;
        lastKeyframeTime = keyframe->getTime();
        if(timeSinceLastKeyframe > 0) {
            actions.pushBack(DelayTime::create(timeSinceLastKeyframe));
        }
	
        auto& keyVal = keyframe->getValue().asValueVector();
        std::string selectorName = keyVal[0].asString();
        CCBReader::TargetType selectorTarget = (CCBReader::TargetType)keyVal[1].asInt();
	
        if(_jsControlled) {
            std::stringstream callbackName;
            callbackName << static_cast<int>(selectorTarget);
            callbackName << ":" + selectorName;
            
            auto callback = _keyframeCallFuncs.at(callbackName.str());
            if (nullptr != callback)
            {
                CallFunc* callbackClone = callback->clone();
    
                if (callbackClone != nullptr)
                {
                    actions.pushBack(callbackClone);
                }
            }
        }
        else
        {
            Ref* target = nullptr;
            
            if(selectorTarget == CCBReader::TargetType::DOCUMENT_ROOT)
                target = _rootNode;
            else if (selectorTarget == CCBReader::TargetType::OWNER)
                target = _owner;
            
            if(target != nullptr)
            {
                if(selectorName.length() > 0)
                {
                    SEL_CallFuncN selCallFunc = 0;
                    
                    CCBSelectorResolver* targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);

                    if(targetAsCCBSelectorResolver != nullptr)
                    {
                        selCallFunc = targetAsCCBSelectorResolver->onResolveCCBCCCallFuncSelector(target, selectorName.c_str    ());
                    }
                    
                    if(selCallFunc == 0)
                    {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    }
                    else
                    {
                        auto savedTarget = std::make_shared<Vector<Ref*>>();
                        savedTarget->pushBack(target);
                        
                        auto callback = CallFuncN::create([savedTarget, selCallFunc](Node* sender){
                            auto t = savedTarget->at(0);
                            (t->*selCallFunc)(sender);
                        });

                        actions.pushBack(callback);
                    }
                }
                else
                {
                    CCLOG("Unexpected empty selector.");
                }
            }
        }
    }
    if(actions.size() < 1) return nullptr;
    
    return Sequence::create(actions);
}

Sequence*  CCBAnimationManager::actionForSoundChannel(CCBSequenceProperty* channel) {
    
    float lastKeyframeTime = 0;
    
    Vector<FiniteTimeAction*> actions;
    auto& keyframes = channel->getKeyframes();
    ssize_t numKeyframes = keyframes.size();

    for (int i = 0; i < numKeyframes; ++i)
    {
        CCBKeyframe *keyframe = keyframes.at(i);
        float timeSinceLastKeyframe = keyframe->getTime() - lastKeyframeTime;
        lastKeyframeTime = keyframe->getTime();
        if(timeSinceLastKeyframe > 0) {
            actions.pushBack(DelayTime::create(timeSinceLastKeyframe));
        }
	
        stringstream ss (stringstream::in | stringstream::out);
        auto& keyVal = keyframe->getValue().asValueVector();
        std::string soundFile = keyVal[0].asString();
    
        float pitch, pan, gain;
        ss << keyVal[1].asString();
        ss >> pitch;
        ss.flush();
    
        ss << keyVal[2].asString();
        ss >> pan;
        ss.flush();
        
        ss << keyVal[3].asString();
        ss >> gain;
        ss.flush();
        
        actions.pushBack(CCBSoundEffect::actionWithSoundFile(soundFile, pitch, pan, gain));
    }

    if(actions.size() < 1) return nullptr;
    
    return Sequence::create(actions);
}



void CCBAnimationManager::runAction(Node *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration)
{
    auto& keyframes = pSeqProp->getKeyframes();
    ssize_t numKeyframes = keyframes.size();
    
    if (numKeyframes > 1)
    {
        // Make an animation!
        Vector<FiniteTimeAction*> actions;
        
        CCBKeyframe *keyframeFirst = keyframes.at(0);
        float timeFirst = keyframeFirst->getTime() + fTweenDuration;
        
        if (timeFirst > 0)
        {
            actions.pushBack(DelayTime::create(timeFirst));
        }
        
        for (ssize_t i = 0; i < numKeyframes - 1; ++i)
        {
            CCBKeyframe *kf0 = keyframes.at(i);
            CCBKeyframe *kf1 = keyframes.at(i+1);
            
            ActionInterval *action = getAction(kf0, kf1, pSeqProp->getName(), pNode);
            if (action)
            {
                // Apply easing
                action = getEaseAction(action, kf0->getEasingType(), kf0->getEasingOpt());
                
                actions.pushBack(action);
            }
        }
        
        auto seq = Sequence::create(actions);
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
    
    for (auto nodeSeqIter = _nodeSequences.begin(); nodeSeqIter != _nodeSequences.end(); ++nodeSeqIter)
    {
        Node *node = nodeSeqIter->first;
        node->stopAllActions();
        
        // Refer to CCBReader::readKeyframe() for the real type of value
        auto seqs = nodeSeqIter->second;
        auto seqNodeProps = seqs[nSeqId];
        
        std::set<std::string> seqNodePropNames;
        
        if (!seqNodeProps.empty())
        {
            // Reset nodes that have sequence node properties, and run actions on them
            for (auto iter = seqNodeProps.begin(); iter != seqNodeProps.end(); ++iter)
            {
                const std::string propName = iter->first;
                CCBSequenceProperty *seqProp = iter->second;
                seqNodePropNames.insert(propName);
                
                setFirstFrame(node, seqProp, fTweenDuration);
                runAction(node, seqProp, fTweenDuration);
            }
        }
        
        // Reset the nodes that may have been changed by other timelines
        auto& nodeBaseValues = _baseValues[node];
        
        if (!nodeBaseValues.empty())
        {
            for (auto iter = nodeBaseValues.begin(); iter != nodeBaseValues.end(); ++iter)
            {
                if (seqNodePropNames.find(iter->first) == seqNodePropNames.end())
                {
                    setAnimatedProperty(iter->first, node, iter->second, nullptr, fTweenDuration);
                }
            }
        }
        
        auto& nodeObject = _objects[node];
        
        if (!nodeObject.empty())
        {
            for (auto iter = nodeObject.begin(); iter != nodeObject.end(); ++iter)
            {
                if (seqNodePropNames.find(iter->first) == seqNodePropNames.end())
                {
                    setAnimatedProperty(iter->first, node, Value(), iter->second, fTweenDuration);
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

    if(seq->getCallbackChannel() != nullptr) {
        Action* action = (Action *)actionForCallbackChannel(seq->getCallbackChannel());
        if(action != nullptr) {
            _rootNode->runAction(action);
        }
    } 

    if(seq->getSoundChannel() != nullptr) {
        Action* action = (Action *)actionForSoundChannel(seq->getSoundChannel());
        if(action != nullptr) {
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

void CCBAnimationManager::setAnimationCompletedCallback(Ref *target, SEL_CallFunc callbackFunc) {
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

void CCBAnimationManager::setCallFunc(CallFunc* callFunc, const std::string &callbackNamed)
{
    _keyframeCallFuncs.insert(callbackNamed, callFunc);
}

void CCBAnimationManager::sequenceCompleted()
{
    const char *runningSequenceName = _runningSequence->getName();
    int nextSeqId = _runningSequence->getChainedSequenceId();
    _runningSequence = nullptr;
    
    if(_lastCompletedSequenceName != runningSequenceName) {
        _lastCompletedSequenceName = runningSequenceName;
    }
    
    if (nextSeqId != -1)
    {
        runAnimationsForSequenceIdTweenDuration(nextSeqId, 0);
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
    static_cast<Sprite*>(_target)->setSpriteFrame(_spriteFrame);
}


/************************************************************
 CCBSoundEffect
 ************************************************************/

CCBSoundEffect* CCBSoundEffect::actionWithSoundFile(const std::string &filename, float pitch, float pan, float gain) {
  CCBSoundEffect* pRet = new CCBSoundEffect();
  if (pRet != nullptr && pRet->initWithSoundFile(filename, pitch, pan, gain))
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
    _startAngle = _target->getRotationSkewX();
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
    _target->setRotationSkewX(_startAngle + (_diffAngle * time));
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
    _startAngle = _target->getRotationSkewY();
    _diffAngle = _dstAngle - _startAngle;
}

void CCBRotateYTo::update(float time)
{
    _target->setRotationSkewY(_startAngle + (_diffAngle * time));
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


}
