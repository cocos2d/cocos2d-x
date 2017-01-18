#include "CCBXAnimationManager.h"

#include "SpriteBuilder.h"
#include "audio/include/SimpleAudioEngine.h"
#include "CCBXNodeLoader.h"
#include "2d/CCSprite.h"

#include <string>
#include <sstream>
#include <set>

NS_CC_BEGIN

namespace spritebuilder {
    
class CC_DLL CCBSetSpriteFrame : public cocos2d::ActionInstant
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
    
class CC_DLL CCBAnimation : public cocos2d::ActionInstant
{
public:
    /** creates a Place action with a position */
    static CCBAnimation* create(int animationId);
    /**
     * @js NA
     * @lua NA
     */
    ~CCBAnimation();
    
    bool initWithAnimationId(int animationId);
    
    // Overrides
    virtual void update(float time) override;
    virtual CCBAnimation* clone() const override;
    virtual CCBAnimation* reverse() const override;
    
private:
    int _animationId;
};


class CC_DLL CCBSoundEffect : public cocos2d::ActionInstant
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


class CC_DLL CCBRotateTo : public cocos2d::ActionInterval
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


class CC_DLL CCBRotateXTo: public cocos2d::ActionInterval
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


class CC_DLL CCBRotateYTo: public cocos2d::ActionInterval
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


class CC_DLL CCBEaseInstant : public cocos2d::ActionEase
{
public:
    static CCBEaseInstant* create(cocos2d::ActionInterval *pAction);
    
    virtual CCBEaseInstant* clone() const override;
    virtual CCBEaseInstant* reverse() const override;
    virtual void update(float dt) override;
};

// Implementation of CCBAinmationManager
    
#define LE_CHR(a,b,c,d) ( ((a)<<24) | ((b)<<16) | ((c)<<8) | (d) )
    
static int animationTag = LE_CHR('c','c','b','i');

CCBAnimationManager::CCBAnimationManager(float mainScale, float additionalScale, cocos2d::Node *rootNode, CCBXReaderOwner *owner)
: _autoPlaySequenceId(0)
, _rootNode(rootNode)
, _owner(owner)
, _rootContainerSize(Size::ZERO)
, _delegate(nullptr)
, _runningSequence(std::make_pair(nullptr, nullptr))
, _mainScale(mainScale)
, _additionalScale(additionalScale)
{
    init();
}
    
CCBAnimationManager *CCBAnimationManager::fromNode(Node *node)
{
    return dynamic_cast<CCBAnimationManager*>(node->getUserObject());
}

bool CCBAnimationManager::init()
{
    return true;
}

CCBAnimationManager::~CCBAnimationManager()
{
    setDelegate(nullptr);
    
    for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
    {
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
        {
            iter2->second->release();
        }
    }
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

Node* CCBAnimationManager::getRootNode() const
{
    return _rootNode;
}

void CCBAnimationManager::setRootContainerSize(const Size &rootContainerSize)
{
    _rootContainerSize = rootContainerSize;
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
    if (_runningSequence.first)
    {
        return _runningSequence.first->getName();
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

void CCBAnimationManager::addNode(Node *pNode, const std::unordered_map<int, Map<std::string, CCBSequenceProperty*>>& seq)
{
    if(!seq.empty())
        _nodeSequences[pNode] = seq;
}

void CCBAnimationManager::setBaseValue(const Value& value, Node *pNode, const std::string& propName)
{
    auto& props = _baseValues[pNode];
    props[propName] = value;
}

const Value& CCBAnimationManager::getBaseValue(Node *pNode, const std::string& propName)
{
    static Value empty;
    auto propsIt = _baseValues.find(pNode);
    if(propsIt != _baseValues.end())
    {
        auto it = propsIt->second.find(propName);
        if(it != propsIt->second.end())
            return it->second;
    }
    return empty;
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
    std::string seqName(pSequenceName);
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
    
float CCBAnimationManager::getMainScale()
{
    return _mainScale;
}
    
void CCBAnimationManager::setMainScale(float scale)
{
    _mainScale = scale;
}
    
float CCBAnimationManager::getAdditionalScale()
{
    return _additionalScale;
}
    
void CCBAnimationManager::setAdditionalScale(float scale)
{
    _additionalScale = scale;
}


void CCBAnimationManager::moveAnimationsFromNode(Node* fromNode, Node* toNode)
{
    // Move base values
    auto baseValueIter = _baseValues.find(fromNode);
    if(baseValueIter != _baseValues.end())
    {
        _baseValues[toNode] = baseValueIter->second;
        _baseValues.erase(baseValueIter);
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
        if(pKeyframe1->getValue().getType() == Value::Type::FLOAT)
            return FadeTo::create(duration, pKeyframe1->getValue().asFloat()*255.0);
        else
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
        bool val = pKeyframe1->getValue().asBool();
        if(pKeyframe0)
        {
            bool baseValue = getBaseValue(pNode, propName).asBool();
            if(val)
                val = !baseValue;
            else
                val = baseValue;
        }
        if (val)
            return Sequence::createWithTwoActions(DelayTime::create(duration), Show::create());
        else
            return Sequence::createWithTwoActions(DelayTime::create(duration), Hide::create());
    }
    else if ((propName == "displayFrame")||((propName == "spriteFrame")))
    {
        return Sequence::createWithTwoActions(DelayTime::create(duration),
                    CCBSetSpriteFrame::create(static_cast<SpriteFrame*>(pKeyframe1->getObject())));
    }
    else if (propName == "position")
    {
        // Get position type
        auto& array = getBaseValue(pNode, propName).asValueVector();
        PositionReferenceCorner corner = (PositionReferenceCorner)array[2].asInt();
        PositionUnit xUnit = (PositionUnit)array[3].asInt();
        PositionUnit yUnit = (PositionUnit)array[4].asInt();
        
        // Get relative position
        auto value = pKeyframe1->getValue().asValueVector();
        float x = value[0].asFloat();
        float y = value[1].asFloat();
        
        Size containerSize = getContainerSize(pNode->getParent());
        
        Vec2 absPos = getAbsolutePosition(_mainScale, _additionalScale, Vec2(x,y), corner, xUnit, yUnit, containerSize);
        
        return MoveTo::create(duration, absPos);
    }
    else if (propName == "scale")
    {
        // Get position type
        auto& array = getBaseValue(pNode, propName).asValueVector();
        int type = array[2].asInt();
        
        // Get relative scale
        auto value = pKeyframe1->getValue().asValueVector();
        
        Vec2 newScale = getAbsoluteScale(_mainScale, _additionalScale, value[0].asFloat(), value[1].asFloat(), type);
        
        return ScaleTo::create(duration, newScale.x, newScale.y);
    }
    else if (propName == "skew")
    {
        // Get relative skew
        auto& value = pKeyframe1->getValue().asValueVector();
        float x = value[0].asFloat();
        float y = value[1].asFloat();
        
        return SkewTo::create(duration, x, y);
    }
    else if (propName == "animation")
    {
        // Get sequence id
        int value = pKeyframe1->getValue().asInt();
        return Sequence::createWithTwoActions(DelayTime::create(duration), CCBAnimation::create(value));
    }
    else 
    {
        log("CCBReader: Failed to create animation for property: %s", propName.c_str());
    }
    
    return nullptr;
}

void CCBAnimationManager::setAnimatedProperty(const std::string& propName, Node *pNode, const Value& value, Ref* obj, float fTweenDuration, bool isBaseValue)
{
    if (fTweenDuration > 0)
    {
        // Create a fake keyframe to generate the action from
        CCBKeyframe *kf1 = new (std::nothrow) CCBKeyframe();
        kf1->autorelease();
        
        kf1->setObject(obj);
        kf1->setValue(value);
        kf1->setTime(fTweenDuration);
        kf1->setEasingType(CCBKeyframe::EasingType::LINEAR);
        
        // Animate
        ActionInterval *tweenAction = getAction(nullptr, kf1, propName, pNode);
        tweenAction->setTag(animationTag);
        pNode->runAction(tweenAction);
        _runningActions[pNode].pushBack(tweenAction);
    }
    else 
    {
        // Just set the value
        
        if (propName == "position")
        {
            // Get position type
            auto& array = getBaseValue(pNode, propName).asValueVector();
            PositionReferenceCorner corner = (PositionReferenceCorner)array[2].asInt();
            PositionUnit xUnit = (PositionUnit)array[3].asInt();
            PositionUnit yUnit = (PositionUnit)array[4].asInt();
            
            // Get relative position
            auto& valueVector = value.asValueVector();
            float x = valueVector[0].asFloat();
            float y = valueVector[1].asFloat();
            
            pNode->setPosition(getAbsolutePosition(_mainScale, _additionalScale, Vec2(x,y), corner, xUnit, yUnit, getContainerSize(pNode->getParent())));
        }
        else if (propName == "scale")
        {
            // Get scale type
            auto& array = getBaseValue(pNode, propName).asValueVector();
            int type = array[2].asInt();
            
            // Get relative scale
            auto& valueVector = value.asValueVector();
            float x = valueVector[0].asFloat();
            float y = valueVector[1].asFloat();
            
            Vec2 realScale = getAbsoluteScale(_mainScale, _additionalScale, x, y, type);
            pNode->setScale(realScale.x, realScale.y);
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

            // TODO: only handle rotation, opacity, displayFrame, color
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
                if(value.getType() == Value::Type::FLOAT)
                    pNode->setOpacity(value.asFloat()*255.0);
                else
                    pNode->setOpacity(value.asByte());
            }
            else if ((propName == "displayFrame")||(propName == "spriteFrame"))
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
                bool val = value.asBool();
                
                if(!isBaseValue)
                {
                    bool baseValue = getBaseValue(pNode, propName).asBool();
                    if(val)
                        val = !baseValue;
                    else
                        val = baseValue;
                }
                pNode->setVisible(val);
            }
            else if (propName == "animation")
            {
                int sequenceId = value.asInt();
                CCBAnimationManager *animationManager = CCBAnimationManager::fromNode(pNode);
                if(animationManager)
                {
                    if(sequenceId == -2)
                        animationManager->runAnimationsForSequenceIdTweenDuration(animationManager->getAutoPlaySequenceId(), 0);
                    else if(sequenceId == -1)
                        animationManager->stopAnimations(false);
                    else
                        animationManager->runAnimationsForSequenceIdTweenDuration(sequenceId, 0);
                }
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
    auto& baseValue = getBaseValue(pNode, pSeqProp->getName());
    auto obj = getObject(pNode, pSeqProp->getName());
    CCASSERT(!baseValue.isNull() || obj, "No baseValue found for property");
    
    auto& keyframes = pSeqProp->getKeyframes();
    CCBKeyframe *keyframeFirst = !keyframes.empty() ? keyframes.at(0) : nullptr;
    
    if (keyframeFirst && keyframeFirst->getTime() == 0)
    {
        setAnimatedProperty(pSeqProp->getName(), pNode, keyframeFirst->getValue(), keyframeFirst->getObject(), fTweenDuration, false);
    }
    else
    {
        setAnimatedProperty(pSeqProp->getName(), pNode, baseValue, obj, fTweenDuration, true);
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
        TargetType selectorTarget = (TargetType)keyVal[1].asInt();
	
        {
            CCBXReaderOwner* targetAsCCBSelectorResolver = nullptr;
            
            if(selectorTarget == TargetType::DOCUMENT_ROOT)
                targetAsCCBSelectorResolver = dynamic_cast<CCBXReaderOwner *>(_rootNode);
            else if (selectorTarget == TargetType::OWNER)
                targetAsCCBSelectorResolver = dynamic_cast<CCBXReaderOwner *>(_owner);
            
            if(_rootNode != nullptr)
            {
                if(selectorName.length() > 0)
                {
                    ccReaderEventCallback selCallFunc;

                    if(targetAsCCBSelectorResolver != nullptr)
                    {
                        selCallFunc = targetAsCCBSelectorResolver->onResolveCCBCallFuncSelector(selectorName, _rootNode);
                    }
                    
                    if(!selCallFunc)
                    {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    }
                    else
                    {
                        auto callback = CallFuncN::create(selCallFunc);
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
	
        std::stringstream ss (std::stringstream::in | std::stringstream::out);
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
    
    if (numKeyframes > 0)
    {
        // Make an animation!
        Vector<FiniteTimeAction*> actions;
        
        CCBKeyframe *keyframeFirst = keyframes.at(0);
        float timeFirst = keyframeFirst->getTime();
        
        if(timeFirst > 0 || fTweenDuration > 0)
            actions.pushBack(DelayTime::create(timeFirst + fTweenDuration));
        
        if (timeFirst > 0)
        {
            ActionInterval *action = getAction(keyframeFirst, keyframeFirst, pSeqProp->getName(), pNode);
            if (action)
                actions.pushBack(action);
        }
        
        if (numKeyframes > 1)
        {
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
        }
        
        if(actions.size())
        {
            auto seq = Sequence::create(actions);
            seq->setTag(animationTag);
            pNode->runAction(seq);
            _runningActions[pNode].pushBack(seq);
        }
    }
}

void CCBAnimationManager::runAnimationsForSequenceIdTweenDuration(int nSeqId, float fTweenDuration, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &callback)
{
    CCBSequence *seq = getSequence(nSeqId);
    CCASSERT(seq, "Sequence id couldn't be found");
    
    if(_runningSequence.first)
    {
        if (_delegate)
            _delegate->completedAnimationSequenceNamed(_runningSequence.first->getName(), AnimationCompleteType::CHAINED);
        if(_runningSequence.second)
            _runningSequence.second(_rootNode, AnimationCompleteType::STOPED);
    }
    
    for(const auto &pair:_runningActions)
    {
        for(const auto action:pair.second)
            pair.first->stopAction(action);
    }
    _runningActions.clear();
    
    for (auto nodeSeqIter = _nodeSequences.begin(); nodeSeqIter != _nodeSequences.end(); ++nodeSeqIter)
    {
        Node *node = nodeSeqIter->first;
        
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
    }
    
    // Make callback at end of sequence
    Action *completeAction = Sequence::createWithTwoActions(DelayTime::create(seq->getDuration() + fTweenDuration),
                                                                CallFunc::create(std::bind(&CCBAnimationManager::sequenceCompleted, this, callback)));
    completeAction->setTag(animationTag);
    _rootNode->runAction(completeAction);
    _runningActions[_rootNode].pushBack(completeAction);
    
    // Set the running scene

    if(seq->getCallbackChannel() != nullptr) {
        Action* action = (Action *)actionForCallbackChannel(seq->getCallbackChannel());
        if(action != nullptr) {
            action->setTag(animationTag);
            _rootNode->runAction(action);
            _runningActions[_rootNode].pushBack(action);
        }
    } 

    if(seq->getSoundChannel() != nullptr) {
        Action* action = (Action *)actionForSoundChannel(seq->getSoundChannel());
        if(action != nullptr) {
            action->setTag(animationTag);
            _rootNode->runAction(action);
            _runningActions[_rootNode].pushBack(action);
        }
    }

    _runningSequence.first = seq;
    _runningSequence.second = callback;
}
    
void CCBAnimationManager::stopAnimations(bool reset)
{
    if(_runningSequence.first)
    {
        if (_delegate)
            _delegate->completedAnimationSequenceNamed(_runningSequence.first->getName(), AnimationCompleteType::CHAINED);
        if(_runningSequence.second)
            _runningSequence.second(_rootNode, AnimationCompleteType::STOPED);
    }
    
    for(const auto &pair:_runningActions)
    {
        for(const auto action:pair.second)
            pair.first->stopAction(action);
    }
    _runningActions.clear();
    
    if(reset)
    {
        for(auto nodeIt:_baseValues)
        {
            for(const auto &iter:nodeIt.second)
            {
                if (iter.first == "animation")
                {
                    CCBAnimationManager *animationManager = CCBAnimationManager::fromNode(nodeIt.first);
                    if(animationManager)
                        animationManager->stopAnimations(true);
                }
                else
                {
                    setAnimatedProperty(iter.first, nodeIt.first, iter.second, nullptr, 0, true);
                }
            }
        }

        for(auto nodeIt:_objects)
        {
            for(const auto &iter:nodeIt.second)
            {
                setAnimatedProperty(iter.first, nodeIt.first, Value(), iter.second, 0, true);
            }
        }
    }
}

void CCBAnimationManager::runAnimationsForSequenceNamedTweenDuration(const char *pName, float fTweenDuration, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &callback)
{
    int seqId = getSequenceId(pName);
    runAnimationsForSequenceIdTweenDuration(seqId, fTweenDuration, callback);
}

void CCBAnimationManager::runAnimationsForSequenceNamed(const char *pName, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &callback)
{
    runAnimationsForSequenceNamedTweenDuration(pName, 0, callback);
}

void CCBAnimationManager::debug()
{
    
}

void CCBAnimationManager::sequenceCompleted(const std::function<void(cocos2d::Node*, AnimationCompleteType)> &callback)
{
    const char *runningSequenceName = _runningSequence.first->getName();
    int nextSeqId = _runningSequence.first->getChainedSequenceId();
    _runningSequence.first = nullptr;
    _runningSequence.second = nullptr;
    
    if(_lastCompletedSequenceName != runningSequenceName) {
        _lastCompletedSequenceName = runningSequenceName;
    }
    
    if (nextSeqId != -1)
    {
        if(callback)
            callback(_rootNode, AnimationCompleteType::CHAINED);
        if (_delegate)
            _delegate->completedAnimationSequenceNamed(runningSequenceName, AnimationCompleteType::CHAINED);
        runAnimationsForSequenceIdTweenDuration(nextSeqId, 0, callback);
    }
    else
    {
        if(callback)
            callback(_rootNode, AnimationCompleteType::COMPLETED);
        if (_delegate)
            _delegate->completedAnimationSequenceNamed(runningSequenceName, AnimationCompleteType::COMPLETED);
    }
}

// Custom actions

/************************************************************
 CCBSetSpriteFrame
 ************************************************************/

CCBSetSpriteFrame* CCBSetSpriteFrame::create(SpriteFrame *pSpriteFrame)
{
    CCBSetSpriteFrame *ret = new (std::nothrow) CCBSetSpriteFrame();
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
	auto a = new (std::nothrow) CCBSetSpriteFrame();
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
 CCBAnimation
 ************************************************************/

CCBAnimation* CCBAnimation::create(int animationId)
{
    CCBAnimation *ret = new (std::nothrow) CCBAnimation();
    if (ret)
    {
        if (ret->initWithAnimationId(animationId))
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

bool CCBAnimation::initWithAnimationId(int animationId)
{
    _animationId = animationId;
    
    return true;
}

CCBAnimation::~CCBAnimation()
{
}

CCBAnimation* CCBAnimation::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) CCBAnimation();
    a->initWithAnimationId(_animationId);
    a->autorelease();
    return a;
}

CCBAnimation* CCBAnimation::reverse() const
{
    // returns a copy of itself
    return this->clone();
}

void CCBAnimation::update(float time)
{
    CCBAnimationManager *manager = CCBAnimationManager::fromNode(_target);
    if(manager)
        manager->runAnimationsForSequenceIdTweenDuration(_animationId, 0.0f);
}

/************************************************************
 CCBSoundEffect
 ************************************************************/

CCBSoundEffect* CCBSoundEffect::actionWithSoundFile(const std::string &filename, float pitch, float pan, float gain) {
  CCBSoundEffect* pRet = new (std::nothrow) CCBSoundEffect();
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
    auto a = new (std::nothrow) CCBSoundEffect();
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
    if(CCBXReader::getPlaySound())
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(_soundFile.c_str());
}


/************************************************************
 CCBRotateTo
 ************************************************************/

CCBRotateTo* CCBRotateTo::create(float fDuration, float fAngle)
{
    CCBRotateTo *ret = new (std::nothrow) CCBRotateTo();
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
    auto a = new (std::nothrow) CCBRotateTo();
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
    CCBRotateXTo *ret = new (std::nothrow) CCBRotateXTo();
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
    auto a = new (std::nothrow) CCBRotateXTo();
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
    CCBRotateYTo *ret = new (std::nothrow) CCBRotateYTo();
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
    auto a = new (std::nothrow) CCBRotateYTo();
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
    CCBEaseInstant *pRet = new (std::nothrow) CCBEaseInstant();
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
    auto a = new (std::nothrow) CCBEaseInstant();
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

NS_CC_END
