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
: mSequences(NULL)
, mNodeSequences(NULL)
, mBaseValues(NULL)
, mAutoPlaySequenceId(0)
, mRootNode(NULL)
, mRootContainerSize(SizeZero)
, mDelegate(NULL)
, mRunningSequence(NULL)
, jsControlled(false)
, mOwner(NULL)
{
    init();
}

bool CCBAnimationManager::init()
{
    mSequences = new Array();
    mNodeSequences = new Dictionary();
    mBaseValues = new Dictionary();
    
    mDocumentOutletNames = new Array();
    mDocumentOutletNodes = new Array();
    mDocumentCallbackNames = new Array();
    mDocumentCallbackNodes = new Array();
    mKeyframeCallbacks = new Array();
    mKeyframeCallFuncs = new Dictionary();

    mTarget = NULL;
    mAnimationCompleteCallbackFunc = NULL;
    
    return true;
}

CCBAnimationManager::~CCBAnimationManager()
{
//     DictElement *pElement = NULL;
//     CCDICT_FOREACH(mNodeSequences, pElement)
//     {
//         Node *node = (Node*)pElement->getIntKey();
//         node->release();
//     }
//     
//     CCDICT_FOREACH(mBaseValues, pElement)
//     {
//         Node *node = (Node*)pElement->getIntKey();
//         node->release();
//     }
    
    mNodeSequences->release();
    mBaseValues->release();
    mSequences->release();
    setRootNode(NULL);
    setDelegate(NULL);

    CC_SAFE_RELEASE(mDocumentOutletNames);
    CC_SAFE_RELEASE(mDocumentOutletNodes);
    CC_SAFE_RELEASE(mDocumentCallbackNames);
    CC_SAFE_RELEASE(mDocumentCallbackNodes);
    
    CC_SAFE_RELEASE(mKeyframeCallFuncs);
    CC_SAFE_RELEASE(mKeyframeCallbacks);
    CC_SAFE_RELEASE(mTarget);
}

Array* CCBAnimationManager::getSequences()
{
    return mSequences;
}

void CCBAnimationManager::setSequences(Array* seq)
{
    mSequences = seq;
}

int CCBAnimationManager::getAutoPlaySequenceId()
{
    return mAutoPlaySequenceId;
}

void CCBAnimationManager::setAutoPlaySequenceId(int autoPlaySequenceId)
{
    mAutoPlaySequenceId = autoPlaySequenceId;
}

Node* CCBAnimationManager::getRootNode()
{
    return mRootNode;
}

void CCBAnimationManager::setRootNode(Node *pRootNode)
{
    mRootNode = pRootNode;
}

void CCBAnimationManager::setDocumentControllerName(const std::string &name) {
    mDocumentControllerName = name;
}


std::string CCBAnimationManager::getDocumentControllerName() {
    return mDocumentControllerName;
}

void CCBAnimationManager::addDocumentCallbackNode(Node *node) {
    mDocumentCallbackNodes->addObject(node);
}

void CCBAnimationManager::addDocumentCallbackName(std::string name) {
    String *tmpName = String::create(name);
    mDocumentCallbackNames->addObject(tmpName);
}

Array* CCBAnimationManager::getDocumentCallbackNames() {
    return mDocumentCallbackNames;
}

Array* CCBAnimationManager::getDocumentCallbackNodes() {
    return mDocumentCallbackNodes;
}

void CCBAnimationManager::addDocumentOutletNode(Node *node) {
    mDocumentOutletNodes->addObject(node);
}

void CCBAnimationManager::addDocumentOutletName(std::string name) {
    mDocumentOutletNames->addObject(String::create(name));
}

Array* CCBAnimationManager::getDocumentOutletNames() {
    return mDocumentOutletNames;
}

Array* CCBAnimationManager::getDocumentOutletNodes() {
    return mDocumentOutletNodes;
}

std::string CCBAnimationManager::getLastCompletedSequenceName() {
    return lastCompletedSequenceName;
}

Array* CCBAnimationManager::getKeyframeCallbacks() {
    return mKeyframeCallbacks;
}

const Size& CCBAnimationManager::getRootContainerSize()
{
    return mRootContainerSize;
}

void CCBAnimationManager::setRootContainerSize(const Size &rootContainerSize)
{
    mRootContainerSize.setSize(rootContainerSize.width, rootContainerSize.height);
}

CCBAnimationManagerDelegate* CCBAnimationManager::getDelegate()
{
    return mDelegate;
}

void CCBAnimationManager::setDelegate(CCBAnimationManagerDelegate *pDelegate)
{
    CC_SAFE_RELEASE(dynamic_cast<Object*>(mDelegate));
    mDelegate = pDelegate;
    CC_SAFE_RETAIN(dynamic_cast<Object*>(mDelegate));
}

const char* CCBAnimationManager::getRunningSequenceName()
{
    if (mRunningSequence)
    {
        return mRunningSequence->getName();
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
        return mRootContainerSize;
    }
}

// refer to CCBReader::readNodeGraph() for data structure of pSeq
void CCBAnimationManager::addNode(Node *pNode, Dictionary *pSeq)
{
    // pNode->retain();
    
    mNodeSequences->setObject(pSeq, (intptr_t)pNode);
}

void CCBAnimationManager::setBaseValue(Object *pValue, Node *pNode, const char *pPropName)
{
    Dictionary *props = (Dictionary*)mBaseValues->objectForKey((intptr_t)pNode);
    if (! props)
    {
        props = Dictionary::create();
        mBaseValues->setObject(props, (intptr_t)pNode);
        // pNode->retain();
    }
    
    props->setObject(pValue, pPropName);
}

Object* CCBAnimationManager::getBaseValue(Node *pNode, const char* pPropName)
{
    Dictionary *props = (Dictionary*)mBaseValues->objectForKey((intptr_t)pNode);
    
    return props->objectForKey(pPropName);
}

int CCBAnimationManager::getSequenceId(const char* pSequenceName)
{
    Object *pElement = NULL;
    string seqName(pSequenceName);
    CCARRAY_FOREACH(mSequences, pElement)
    {
        CCBSequence *seq = (CCBSequence*)pElement;
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
    CCARRAY_FOREACH(mSequences, pElement)
    {
        CCBSequence *seq = (CCBSequence*)pElement;
        if (seq->getSequenceId() == nSequenceId)
        {
            return seq;
        }
    }
    return NULL;
}


void CCBAnimationManager::moveAnimationsFromNode(Node* fromNode, Node* toNode) {

    // Move base values
    Object* baseValue = mBaseValues->objectForKey((intptr_t)fromNode);
    if(baseValue) {
        mBaseValues->setObject(baseValue, (intptr_t)toNode);
        mBaseValues->removeObjectForKey((intptr_t)fromNode);

//         fromNode->release();
//         toNode->retain();
    }
    
    // Move seqs
    Object *seqs = mNodeSequences->objectForKey((intptr_t)fromNode);
    if(seqs) {
        mNodeSequences->setObject(seqs, (intptr_t)toNode);
        mNodeSequences->removeObjectForKey((intptr_t)fromNode);

//         fromNode->release();
//         toNode->retain();
    }
}

// Refer to CCBReader::readKeyframe() for the real type of value
ActionInterval* CCBAnimationManager::getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *pPropName, Node *pNode)
{
    float duration = pKeyframe1->getTime() - (pKeyframe0 ? pKeyframe0->getTime() : 0);
    
    if (strcmp(pPropName, "rotationX") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return CCBRotateXTo::create(duration, value->getFloatValue());
    }
    else if(strcmp(pPropName, "rotationY") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return CCBRotateYTo::create(duration, value->getFloatValue());
    }
    else if (strcmp(pPropName, "rotation") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return CCBRotateTo::create(duration, value->getFloatValue());
    } 
    else if (strcmp(pPropName, "opacity") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return FadeTo::create(duration, value->getByteValue());
    }
    else if (strcmp(pPropName, "color") == 0)
    {
        ccColor3BWapper* color = (ccColor3BWapper*)pKeyframe1->getValue();
        ccColor3B c = color->getColor();
        
        return TintTo::create(duration, c.r, c.g, c.b);
    }
    else if (strcmp(pPropName, "visible") == 0)
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
    else if (strcmp(pPropName, "displayFrame") == 0)
    {
        return Sequence::createWithTwoActions(DelayTime::create(duration),
                                                CCBSetSpriteFrame::create((SpriteFrame *)pKeyframe1->getValue()));
    }
    else if (strcmp(pPropName, "position") == 0)
    {
        // Get position type
        Array *array = (Array*)getBaseValue(pNode, pPropName);
        int type = ((CCBValue*)array->objectAtIndex(2))->getIntValue();
        
        // Get relative position
        Array *value = (Array*)pKeyframe1->getValue();
        float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
        float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
        
        Size containerSize = getContainerSize(pNode->getParent());
        
        Point absPos = getAbsolutePosition(ccp(x,y), type, containerSize, pPropName);
        
        return MoveTo::create(duration, absPos);
    }
    else if (strcmp(pPropName, "scale") == 0)
    {
        // Get position type
        Array *array = (Array*)getBaseValue(pNode, pPropName);
        int type = ((CCBValue*)array->objectAtIndex(2))->getIntValue();
        
        // Get relative scale
        Array *value = (Array*)pKeyframe1->getValue();
        float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
        float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
        
        if (type == kCCBScaleTypeMultiplyResolution)
        {
            float resolutionScale = CCBReader::getResolutionScale();
            x *= resolutionScale;
            y *= resolutionScale;
        }
        
        return ScaleTo::create(duration, x, y);
    }
    else if(strcmp(pPropName, "skew") == 0) 
    {
        // Get relative skew
        Array *value = (Array*)pKeyframe1->getValue();
        float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
        float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
        
        return SkewTo::create(duration, x, y);
    }
    else 
    {
        CCLog("CCBReader: Failed to create animation for property: %s", pPropName);
    }
    
    return NULL;
}

void CCBAnimationManager::setAnimatedProperty(const char *pPropName, Node *pNode, Object *pValue, float fTweenDuration)
{
    if (fTweenDuration > 0)
    {
        // Create a fake keyframe to generate the action from
        CCBKeyframe *kf1 = new CCBKeyframe();
        kf1->autorelease();
        kf1->setValue(pValue);
        kf1->setTime(fTweenDuration);
        kf1->setEasingType(kCCBKeyframeEasingLinear);
        
        // Animate
        ActionInterval *tweenAction = getAction(NULL, kf1, pPropName, pNode);
        pNode->runAction(tweenAction);
    }
    else 
    {
        // Just set the value
        
        if (strcmp(pPropName, "position") == 0)
        {
            // Get position type
            Array *array = (Array*)getBaseValue(pNode, pPropName);
            int type = ((CCBValue*)array->objectAtIndex(2))->getIntValue();
            
            // Get relative position
            Array *value = (Array*)pValue;
            float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
            float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
            
            pNode->setPosition(getAbsolutePosition(ccp(x,y), type, getContainerSize(pNode->getParent()), pPropName));
        }
        else if (strcmp(pPropName, "scale") == 0)
        {
            // Get scale type
            Array *array = (Array*)getBaseValue(pNode, pPropName);
            int type = ((CCBValue*)array->objectAtIndex(2))->getIntValue();
            
            // Get relative scale
            Array *value = (Array*)pValue;
            float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
            float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
            
            setRelativeScale(pNode, x, y, type, pPropName);
        }
        else if(strcmp(pPropName, "skew") == 0)
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
            if (strcmp(pPropName, "rotation") == 0)
            {
                float rotate = ((CCBValue*)pValue)->getFloatValue();
                pNode->setRotation(rotate);
            } else if(strcmp(pPropName, "rotationX") == 0)
            {
                float rotate = ((CCBValue*)pValue)->getFloatValue();
                pNode->setRotationX(rotate);
            }else if(strcmp(pPropName, "rotationY") == 0)
            {
                float rotate = ((CCBValue*)pValue)->getFloatValue();
                pNode->setRotationY(rotate);
            }
            else if (strcmp(pPropName, "opacity") == 0)
            {
                int opacity = ((CCBValue*)pValue)->getByteValue();
                (dynamic_cast<RGBAProtocol*>(pNode))->setOpacity(opacity);
            }
            else if (strcmp(pPropName, "displayFrame") == 0)
            {
                ((Sprite*)pNode)->setDisplayFrame((SpriteFrame*)pValue);
            }
            else if (strcmp(pPropName, "color") == 0)
            {
                ccColor3BWapper *color = (ccColor3BWapper*)pValue;
                (dynamic_cast<RGBAProtocol*>(pNode))->setColor(color->getColor());
            }
            else if (strcmp(pPropName, "visible") == 0)
            {
                bool visible = ((CCBValue*)pValue)->getBoolValue();
                pNode->setVisible(visible);
            }
            else
            {
                CCLog("unsupported property name is %s", pPropName);
                CCAssert(false, "unsupported property now");
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
        CCAssert(baseValue, "No baseValue found for property");
        setAnimatedProperty(pSeqProp->getName(), pNode, baseValue, fTweenDuration);
    }
    else 
    {
        // Use first keyframe
        CCBKeyframe *keyframe = (CCBKeyframe*)keyframes->objectAtIndex(0);
        setAnimatedProperty(pSeqProp->getName(), pNode, keyframe->getValue(), fTweenDuration);
    }
}

ActionInterval* CCBAnimationManager::getEaseAction(ActionInterval *pAction, int nEasingType, float fEasingOpt)
{
    if (dynamic_cast<Sequence*>(pAction))
    {
        return pAction;
    }
    
    if (nEasingType == kCCBKeyframeEasingLinear)
    {
        return pAction;
    }
    else if (nEasingType == kCCBKeyframeEasingInstant)
    {
        return CCBEaseInstant::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingCubicIn)
    {
        return EaseIn::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingCubicOut)
    {
        return EaseOut::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingCubicInOut)
    {
        return EaseInOut::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingBackIn)
    {
        return EaseBackIn::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBackOut)
    {
        return EaseBackOut::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBackInOut)
    {
        return EaseBackInOut::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBounceIn)
    {
        return EaseBounceIn::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBounceOut)
    {
        return EaseBounceOut::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBounceInOut)
    {
        return EaseBounceInOut::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingElasticIn)
    {
        return EaseElasticIn::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingElasticOut)
    {
        return EaseElasticOut::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingElasticInOut)
    {
        return EaseElasticInOut::create(pAction, fEasingOpt);
    }
    else
    {
        CCLog("CCBReader: Unkown easing type %d", nEasingType);
        return pAction;
    }
}

Object* CCBAnimationManager::actionForCallbackChannel(CCBSequenceProperty* channel) {
  
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
	
        Array* keyVal = (Array *)keyframe->getValue();
        std::string selectorName = ((String *)keyVal->objectAtIndex(0))->getCString();
        int selectorTarget = atoi(((String *)keyVal->objectAtIndex(1))->getCString());
	
        if(jsControlled) {
            String* callbackName = String::createWithFormat("%d:%s", selectorTarget, selectorName.c_str());
            CallFunc *callback = (CallFunc*)(mKeyframeCallFuncs->objectForKey(callbackName->getCString()))->copy()->autorelease();

            if(callback != NULL) {
                actions->addObject(callback);
            }
        } else {
            Object* target = NULL;
            if(selectorTarget == kCCBTargetTypeDocumentRoot) target = mRootNode;
            else if (selectorTarget == kCCBTargetTypeOwner) target = mOwner;
            if(target != NULL) {
                if(selectorName.length() > 0) {
                    SEL_CallFuncN selCallFunc = 0;
                    
                    CCBSelectorResolver* targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);

                    if(targetAsCCBSelectorResolver != NULL) {
                        selCallFunc = targetAsCCBSelectorResolver->onResolveCCBCallFuncSelector(target, selectorName.c_str    ());
                    }
                    if(selCallFunc == 0) {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    } else {
                        CallFuncN *callback = CallFuncN::create(target, selCallFunc);
                        actions->addObject(callback);
                    }
                } else {
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
    CCAssert(nSeqId != -1, "Sequence id couldn't be found");
    
    mRootNode->stopAllActions();
    
    DictElement* pElement = NULL;
    CCDICT_FOREACH(mNodeSequences, pElement)
    {
        Node *node = (Node*)pElement->getIntKey();
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
                CCBSequenceProperty *seqProp = (CCBSequenceProperty*)seqNodeProps->objectForKey(propName);
                seqNodePropNames.insert(propName);
                
                setFirstFrame(node, seqProp, fTweenDuration);
                runAction(node, seqProp, fTweenDuration);
            }
        }
        
        // Reset the nodes that may have been changed by other timelines
        Dictionary *nodeBaseValues = (Dictionary*)mBaseValues->objectForKey(pElement->getIntKey());
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
                                                                CallFunc::create(this, callfunc_selector(CCBAnimationManager::sequenceCompleted)));
    mRootNode->runAction(completeAction);
    
    // Set the running scene

    if(seq->getCallbackChannel() != NULL) {
        Action* action = (Action *)actionForCallbackChannel(seq->getCallbackChannel());
        if(action != NULL) {
            mRootNode->runAction(action);
        }
    } 

    if(seq->getSoundChannel() != NULL) {
        Action* action = (Action *)actionForSoundChannel(seq->getSoundChannel());
        if(action != NULL) {
            mRootNode->runAction(action);
        }
    }

    mRunningSequence = getSequence(nSeqId);
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
    
    if (mTarget)
    {
        mTarget->release();
    }
    
    mTarget = target;
    mAnimationCompleteCallbackFunc = callbackFunc;
}

void CCBAnimationManager::setCallFunc(CallFunc* callFunc, const std::string &callbackNamed) {
    mKeyframeCallFuncs->setObject((Object*)callFunc, callbackNamed);
}

void CCBAnimationManager::sequenceCompleted()
{
    const char *runningSequenceName = mRunningSequence->getName();
    int nextSeqId = mRunningSequence->getChainedSequenceId();
    mRunningSequence = NULL;
    
    if(lastCompletedSequenceName != runningSequenceName) {
        lastCompletedSequenceName = runningSequenceName;
    }
    
    if (mDelegate)
    {
        // There may be another runAnimation() call in this delegate method
        // which will assign mRunningSequence
        mDelegate->completedAnimationSequenceNamed(runningSequenceName);
    }
    
    if (mTarget && mAnimationCompleteCallbackFunc) {
        (mTarget->*mAnimationCompleteCallbackFunc)();
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
    mSpriteFrame = pSpriteFrame;
    CC_SAFE_RETAIN(mSpriteFrame);
    
    return true;
}

CCBSetSpriteFrame::~CCBSetSpriteFrame()
{
    CC_SAFE_RELEASE_NULL(mSpriteFrame);
}

CCBSetSpriteFrame* CCBSetSpriteFrame::clone() const
{
	// no copy constructor
	auto a = new CCBSetSpriteFrame();
    a->initWithSpriteFrame(mSpriteFrame);
	a->autorelease();
	return a;
}

CCBSetSpriteFrame* CCBSetSpriteFrame::reverse() const
{
	// returns a copy of itself
	return this->clone();
}

Object* CCBSetSpriteFrame::copyWithZone(Zone *pZone)
{
    Zone *pNewZone = NULL;
    CCBSetSpriteFrame *pRet = NULL;
    
    if (pZone && pZone->_copyObject) {
        pRet = (CCBSetSpriteFrame*) (pZone->_copyObject);
    } else {
        pRet = new CCBSetSpriteFrame();
        pZone = pNewZone = new Zone(pRet);
    }
    
    pRet->initWithSpriteFrame(mSpriteFrame);
    ActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCBSetSpriteFrame::update(float time)
{
    ((Sprite*)_target)->setDisplayFrame(mSpriteFrame);
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
    mSoundFile = filename;
    mPitch = pitch;
    mPan = pan;
    mGain = gain;
    return true;
}

CCBSoundEffect* CCBSoundEffect::clone() const
{
	// no copy constructor
	auto a = new CCBSoundEffect();
    a->initWithSoundFile(mSoundFile, mPitch, mPan, mGain);
	a->autorelease();
	return a;
}

CCBSoundEffect* CCBSoundEffect::reverse() const
{
	// returns a copy of itself
	return this->clone();
}

Object* CCBSoundEffect::copyWithZone(Zone *pZone)
{
    Zone *pNewZone = NULL;
    CCBSoundEffect *pRet = NULL;
    
    if (pZone && pZone->_copyObject) {
        pRet = (CCBSoundEffect*) (pZone->_copyObject);
    } else {
        pRet = new CCBSoundEffect();
        pZone = pNewZone = new Zone(pRet);
    }
    
    pRet->initWithSoundFile(mSoundFile, mPitch, mPan, mGain);
    ActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}


void CCBSoundEffect::update(float time)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(mSoundFile.c_str());
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
        mDstAngle = fAngle;
        
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
    a->initWithDuration(_duration, mDstAngle);
	a->autorelease();
	return a;
}

CCBRotateTo* CCBRotateTo::reverse() const
{
	CCAssert(false, "reverse() is not supported in CCBRotateTo");
	return nullptr;
}

Object* CCBRotateTo::copyWithZone(Zone *pZone)
{
    Zone *pNewZone = NULL;
    CCBRotateTo *pRet = NULL;
    
    if (pZone && pZone->_copyObject) {
        pRet = (CCBRotateTo*) (pZone->_copyObject);
    } else {
        pRet = new CCBRotateTo();
        pZone = pNewZone = new Zone(pRet);
    }
    
    pRet->initWithDuration(_duration, mDstAngle);
    ActionInterval::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCBRotateTo::startWithTarget(Node *pNode)
{
    ActionInterval::startWithTarget(pNode);
    mStartAngle = _target->getRotation();
    mDiffAngle = mDstAngle - mStartAngle;
}

void CCBRotateTo::update(float time)
{
    _target->setRotation(mStartAngle + (mDiffAngle * time))
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
        mDstAngle = fAngle;
        
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
    mStartAngle = _target->getRotationX();
    mDiffAngle = mDstAngle - mStartAngle;
}

CCBRotateXTo* CCBRotateXTo::clone() const
{
	// no copy constructor
	auto a = new CCBRotateXTo();
    a->initWithDuration(_duration, mDstAngle);
	a->autorelease();
	return a;
}

CCBRotateXTo* CCBRotateXTo::reverse() const
{
	CCAssert(false, "reverse() is not supported in CCBRotateXTo");
	return nullptr;
}

Object* CCBRotateXTo::copyWithZone(Zone *pZone)
{
    Zone *pNewZone = NULL;
    CCBRotateXTo *pRet = NULL;
    
    if (pZone && pZone->_copyObject) {
        pRet = (CCBRotateXTo*) (pZone->_copyObject);
    } else {
        pRet = new CCBRotateXTo();
        pZone = pNewZone = new Zone(pRet);
    }
    
    pRet->initWithDuration(_duration, mDstAngle);
    ActionInterval::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCBRotateXTo::update(float time)
{
    _target->setRotationX(mStartAngle + (mDiffAngle * time))
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
        mDstAngle = fAngle;
        
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
    a->initWithDuration(_duration, mDstAngle);
	a->autorelease();
	return a;
}

CCBRotateYTo* CCBRotateYTo::reverse() const
{
	CCAssert(false, "reverse() is not supported in CCBRotateXTo");
	return nullptr;
}


void CCBRotateYTo::startWithTarget(Node *pNode)
{
 //   ActionInterval::startWithTarget(pNode);
    _originalTarget = pNode;
    _target = pNode;
    _elapsed = 0.0f;
    _firstTick = true;
    mStartAngle = _target->getRotationY();
    mDiffAngle = mDstAngle - mStartAngle;
}


Object* CCBRotateYTo::copyWithZone(Zone *pZone)
{
    Zone *pNewZone = NULL;
    CCBRotateYTo *pRet = NULL;
    
    if (pZone && pZone->_copyObject) {
        pRet = (CCBRotateYTo*) (pZone->_copyObject);
    } else {
        pRet = new CCBRotateYTo();
        pZone = pNewZone = new Zone(pRet);
    }
    
    pRet->initWithDuration(_duration, mDstAngle);
    ActionInterval::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCBRotateYTo::update(float time)
{
    _target->setRotationY(mStartAngle + (mDiffAngle * time))
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
