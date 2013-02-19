#include "CCBAnimationManager.h"
#include "CCBSequence.h"
#include "CCBSequenceProperty.h"
#include "CCBReader.h"
#include "CCBKeyframe.h"
#include "CCNode+CCBRelativePositioning.h"
#include <string>
#include <set>

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
, mRootContainerSize(CCSizeZero)
, mDelegate(NULL)
, mRunningSequence(NULL)
{
    init();
}

bool CCBAnimationManager::init()
{
    mSequences = new CCArray();
    mNodeSequences = new CCDictionary();
    mBaseValues = new CCDictionary();
    
    mDocumentOutletNames = new CCArray();
    mDocumentOutletNodes = new CCArray();
    mDocumentCallbackNames = new CCArray();
    mDocumentCallbackNodes = new CCArray();
    
    mTarget = NULL;
    mAnimationCompleteCallbackFunc = NULL;
    
    return true;
}

CCBAnimationManager::~CCBAnimationManager()
{
//     CCDictElement *pElement = NULL;
//     CCDICT_FOREACH(mNodeSequences, pElement)
//     {
//         CCNode *node = (CCNode*)pElement->getIntKey();
//         node->release();
//     }
//     
//     CCDICT_FOREACH(mBaseValues, pElement)
//     {
//         CCNode *node = (CCNode*)pElement->getIntKey();
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

    CC_SAFE_RELEASE(mTarget);
}

CCArray* CCBAnimationManager::getSequences()
{
    return mSequences;
}

void CCBAnimationManager::setSequences(CCArray* seq)
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

CCNode* CCBAnimationManager::getRootNode()
{
    return mRootNode;
}

void CCBAnimationManager::setRootNode(CCNode *pRootNode)
{
    mRootNode = pRootNode;
}

void CCBAnimationManager::setDocumentControllerName(const std::string &name) {
    mDocumentControllerName = name;
}


std::string CCBAnimationManager::getDocumentControllerName() {
    return mDocumentControllerName;
}

void CCBAnimationManager::addDocumentCallbackNode(CCNode *node) {
    mDocumentCallbackNodes->addObject(node);
}

void CCBAnimationManager::addDocumentCallbackName(std::string name) {
    CCString *tmpName = CCString::create(name);
    mDocumentCallbackNames->addObject(tmpName);
}

CCArray* CCBAnimationManager::getDocumentCallbackNames() {
    return mDocumentCallbackNames;
}

CCArray* CCBAnimationManager::getDocumentCallbackNodes() {
    return mDocumentCallbackNodes;
}

void CCBAnimationManager::addDocumentOutletNode(CCNode *node) {
    mDocumentOutletNodes->addObject(node);
}

void CCBAnimationManager::addDocumentOutletName(std::string name) {
    mDocumentOutletNames->addObject(CCString::create(name));
}

CCArray* CCBAnimationManager::getDocumentOutletNames() {
    return mDocumentOutletNames;
}

CCArray* CCBAnimationManager::getDocumentOutletNodes() {
    return mDocumentOutletNodes;
}

std::string CCBAnimationManager::getLastCompletedSequenceName() {
    return lastCompletedSequenceName;
}

const CCSize& CCBAnimationManager::getRootContainerSize()
{
    return mRootContainerSize;
}

void CCBAnimationManager::setRootContainerSize(const CCSize &rootContainerSize)
{
    mRootContainerSize.setSize(rootContainerSize.width, rootContainerSize.height);
}

CCBAnimationManagerDelegate* CCBAnimationManager::getDelegate()
{
    return mDelegate;
}

void CCBAnimationManager::setDelegate(CCBAnimationManagerDelegate *pDelegate)
{
    CC_SAFE_RELEASE(dynamic_cast<CCObject*>(mDelegate));
    mDelegate = pDelegate;
    CC_SAFE_RETAIN(dynamic_cast<CCObject*>(mDelegate));
}

const char* CCBAnimationManager::getRunningSequenceName()
{
    return mRunningSequence->getName();
}

const CCSize& CCBAnimationManager::getContainerSize(CCNode *pNode)
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
void CCBAnimationManager::addNode(CCNode *pNode, CCDictionary *pSeq)
{
    // pNode->retain();
    
    mNodeSequences->setObject(pSeq, (intptr_t)pNode);
}

void CCBAnimationManager::setBaseValue(CCObject *pValue, CCNode *pNode, const char *pPropName)
{
    CCDictionary *props = (CCDictionary*)mBaseValues->objectForKey((intptr_t)pNode);
    if (! props)
    {
        props = CCDictionary::create();
        mBaseValues->setObject(props, (intptr_t)pNode);
        // pNode->retain();
    }
    
    props->setObject(pValue, pPropName);
}

CCObject* CCBAnimationManager::getBaseValue(CCNode *pNode, const char* pPropName)
{
    CCDictionary *props = (CCDictionary*)mBaseValues->objectForKey((intptr_t)pNode);
    
    return props->objectForKey(pPropName);
}

int CCBAnimationManager::getSequenceId(const char* pSequenceName)
{
    CCObject *pElement = NULL;
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
    CCObject *pElement = NULL;
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


void CCBAnimationManager::moveAnimationsFromNode(CCNode* fromNode, CCNode* toNode) {

    // Move base values
    CCObject* baseValue = mBaseValues->objectForKey((intptr_t)fromNode);
    if(baseValue) {
        mBaseValues->setObject(baseValue, (intptr_t)toNode);
        mBaseValues->removeObjectForKey((intptr_t)fromNode);

//         fromNode->release();
//         toNode->retain();
    }
    
    // Move seqs
    CCObject *seqs = mNodeSequences->objectForKey((intptr_t)fromNode);
    if(seqs) {
        mNodeSequences->setObject(seqs, (intptr_t)toNode);
        mNodeSequences->removeObjectForKey((intptr_t)fromNode);

//         fromNode->release();
//         toNode->retain();
    }
}

// Refer to CCBReader::readKeyframe() for the real type of value
CCActionInterval* CCBAnimationManager::getAction(CCBKeyframe *pKeyframe0, CCBKeyframe *pKeyframe1, const char *pPropName, CCNode *pNode)
{
    float duration = pKeyframe1->getTime() - (pKeyframe0 ? pKeyframe0->getTime() : 0);
    
    if (strcmp(pPropName, "rotation") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return CCBRotateTo::create(duration, value->getFloatValue());
    }
    else if (strcmp(pPropName, "opacity") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        return CCFadeTo::create(duration, value->getByteValue());
    }
    else if (strcmp(pPropName, "color") == 0)
    {
        ccColor3BWapper* color = (ccColor3BWapper*)pKeyframe1->getValue();
        ccColor3B c = color->getColor();
        
        return CCTintTo::create(duration, c.r, c.g, c.b);
    }
    else if (strcmp(pPropName, "visible") == 0)
    {
        CCBValue *value = (CCBValue*)pKeyframe1->getValue();
        if (value->getBoolValue())
        {
            return CCSequence::createWithTwoActions(CCDelayTime::create(duration), CCShow::create());
        }
        else 
        {
            return CCSequence::createWithTwoActions(CCDelayTime::create(duration), CCHide::create());
        }
    }
    else if (strcmp(pPropName, "displayFrame") == 0)
    {
        return CCSequence::createWithTwoActions(CCDelayTime::create(duration),
                                                CCBSetSpriteFrame::create((CCSpriteFrame *)pKeyframe1->getValue()));
    }
    else if (strcmp(pPropName, "position") == 0)
    {
        // Get position type
        CCArray *array = (CCArray*)getBaseValue(pNode, pPropName);
        int type = ((CCBValue*)array->objectAtIndex(2))->getIntValue();
        
        // Get relative position
        CCArray *value = (CCArray*)pKeyframe1->getValue();
        float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
        float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
        
        CCSize containerSize = getContainerSize(pNode->getParent());
        
        CCPoint absPos = getAbsolutePosition(ccp(x,y), type, containerSize, pPropName);
        
        return CCMoveTo::create(duration, absPos);
    }
    else if (strcmp(pPropName, "scale") == 0)
    {
        // Get position type
        CCArray *array = (CCArray*)getBaseValue(pNode, pPropName);
        int type = ((CCBValue*)array->objectAtIndex(2))->getIntValue();
        
        // Get relative scale
        CCArray *value = (CCArray*)pKeyframe1->getValue();
        float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
        float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
        
        if (type == kCCBScaleTypeMultiplyResolution)
        {
            float resolutionScale = CCBReader::getResolutionScale();
            x *= resolutionScale;
            y *= resolutionScale;
        }
        
        return CCScaleTo::create(duration, x, y);
    }
    else 
    {
        CCLog("CCBReader: Failed to create animation for property: %s", pPropName);
    }
    
    return NULL;
}

void CCBAnimationManager::setAnimatedProperty(const char *pPropName, CCNode *pNode, CCObject *pValue, float fTweenDuration)
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
        CCActionInterval *tweenAction = getAction(NULL, kf1, pPropName, pNode);
        pNode->runAction(tweenAction);
    }
    else 
    {
        // Just set the value
        
        if (strcmp(pPropName, "position") == 0)
        {
            // Get position type
            CCArray *array = (CCArray*)getBaseValue(pNode, pPropName);
            int type = ((CCBValue*)array->objectAtIndex(2))->getIntValue();
            
            // Get relative position
            CCArray *value = (CCArray*)pValue;
            float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
            float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
            
            pNode->setPosition(getAbsolutePosition(ccp(x,y), type, getContainerSize(pNode->getParent()), pPropName));
        }
        else if (strcmp(pPropName, "scale") == 0)
        {
            // Get scale type
            CCArray *array = (CCArray*)getBaseValue(pNode, pPropName);
            int type = ((CCBValue*)array->objectAtIndex(2))->getIntValue();
            
            // Get relative scale
            CCArray *value = (CCArray*)pValue;
            float x = ((CCBValue*)value->objectAtIndex(0))->getFloatValue();
            float y = ((CCBValue*)value->objectAtIndex(1))->getFloatValue();
            
            setRelativeScale(pNode, x, y, type, pPropName);
        }
        else 
        {
            // [node setValue:value forKey:name];

            // TODO only handle rotation, opacity, displayFrame, color
            if (strcmp(pPropName, "rotation") == 0)
            {
                float rotate = ((CCBValue*)pValue)->getFloatValue();
                pNode->setRotation(rotate);
            }
            else if (strcmp(pPropName, "opacity") == 0)
            {
                int opacity = ((CCBValue*)pValue)->getByteValue();
                (dynamic_cast<CCRGBAProtocol*>(pNode))->setOpacity(opacity);
            }
            else if (strcmp(pPropName, "displayFrame") == 0)
            {
                ((CCSprite*)pNode)->setDisplayFrame((CCSpriteFrame*)pValue);
            }
            else if (strcmp(pPropName, "color") == 0)
            {
                ccColor3BWapper *color = (ccColor3BWapper*)pValue;
                (dynamic_cast<CCRGBAProtocol*>(pNode))->setColor(color->getColor());
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

void CCBAnimationManager::setFirstFrame(CCNode *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration)
{
    CCArray *keyframes = pSeqProp->getKeyframes();
    
    if (keyframes->count() == 0)
    {
        // Use base value (no animation)
        CCObject *baseValue = getBaseValue(pNode, pSeqProp->getName());
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

CCActionInterval* CCBAnimationManager::getEaseAction(CCActionInterval *pAction, int nEasingType, float fEasingOpt)
{
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
        return CCEaseIn::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingCubicOut)
    {
        return CCEaseOut::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingCubicInOut)
    {
        return CCEaseInOut::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingBackIn)
    {
        return CCEaseBackIn::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBackOut)
    {
        return CCEaseBackOut::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBackInOut)
    {
        return CCEaseBackInOut::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBounceIn)
    {
        return CCEaseBounceIn::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBounceOut)
    {
        return CCEaseBounceOut::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingBounceInOut)
    {
        return CCEaseBounceInOut::create(pAction);
    }
    else if (nEasingType == kCCBKeyframeEasingElasticIn)
    {
        return CCEaseElasticIn::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingElasticOut)
    {
        return CCEaseElasticOut::create(pAction, fEasingOpt);
    }
    else if (nEasingType == kCCBKeyframeEasingElasticInOut)
    {
        return CCEaseElasticInOut::create(pAction, fEasingOpt);
    }
    else
    {
        CCLog("CCBReader: Unkown easing type %d", nEasingType);
        return pAction;
    }
}

void CCBAnimationManager::runAction(CCNode *pNode, CCBSequenceProperty *pSeqProp, float fTweenDuration)
{
    CCArray *keyframes = pSeqProp->getKeyframes();
    int numKeyframes = keyframes->count();
    
    if (numKeyframes > 1)
    {
        // Make an animation!
        CCArray *actions = CCArray::create();
        
        CCBKeyframe *keyframeFirst = (CCBKeyframe*)keyframes->objectAtIndex(0);
        float timeFirst = keyframeFirst->getTime() + fTweenDuration;
        
        if (timeFirst > 0)
        {
            actions->addObject(CCDelayTime::create(timeFirst));
        }
        
        for (int i = 0; i < numKeyframes - 1; ++i)
        {
            CCBKeyframe *kf0 = (CCBKeyframe*)keyframes->objectAtIndex(i);
            CCBKeyframe *kf1 = (CCBKeyframe*)keyframes->objectAtIndex(i+1);
            
            CCActionInterval *action = getAction(kf0, kf1, pSeqProp->getName(), pNode);
            if (action)
            {
                // Apply easing
                action = getEaseAction(action, kf0->getEasingType(), kf0->getEasingOpt());
                
                actions->addObject(action);
            }
        }
        
        CCFiniteTimeAction *seq = CCSequence::create(actions);
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
    
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(mNodeSequences, pElement)
    {
        CCNode *node = (CCNode*)pElement->getIntKey();
        node->stopAllActions();
        
        // Refer to CCBReader::readKeyframe() for the real type of value
        CCDictionary *seqs = (CCDictionary*)pElement->getObject();
        CCDictionary *seqNodeProps = (CCDictionary*)seqs->objectForKey(nSeqId);
        
        set<string> seqNodePropNames;
        
        if (seqNodeProps)
        {
            // Reset nodes that have sequence node properties, and run actions on them
            CCDictElement* pElement1 = NULL;
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
        CCDictionary *nodeBaseValues = (CCDictionary*)mBaseValues->objectForKey(pElement->getIntKey());
        if (nodeBaseValues)
        {
            CCDictElement* pElement2 = NULL;
            CCDICT_FOREACH(nodeBaseValues, pElement2)
            {
                if (seqNodePropNames.find(pElement2->getStrKey()) == seqNodePropNames.end())
                {
                    CCObject *value = pElement2->getObject();
                    
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
    CCAction *completeAction = CCSequence::createWithTwoActions(CCDelayTime::create(seq->getDuration() + fTweenDuration),
                                                                CCCallFunc::create(this, callfunc_selector(CCBAnimationManager::sequenceCompleted)));
    mRootNode->runAction(completeAction);
    
    // Set the running scene
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

void CCBAnimationManager::setAnimationCompletedCallback(CCObject *target, SEL_CallFunc callbackFunc) {
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

CCBSetSpriteFrame* CCBSetSpriteFrame::create(CCSpriteFrame *pSpriteFrame)
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

bool CCBSetSpriteFrame::initWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    mSpriteFrame = pSpriteFrame;
    CC_SAFE_RETAIN(mSpriteFrame);
    
    return true;
}

CCBSetSpriteFrame::~CCBSetSpriteFrame()
{
    CC_SAFE_RELEASE_NULL(mSpriteFrame);
}

CCObject* CCBSetSpriteFrame::copyWithZone(CCZone *pZone)
{
    CCZone *pNewZone = NULL;
    CCBSetSpriteFrame *pRet = NULL;
    
    if (pZone && pZone->m_pCopyObject) {
        pRet = (CCBSetSpriteFrame*) (pZone->m_pCopyObject);
    } else {
        pRet = new CCBSetSpriteFrame();
        pZone = pNewZone = new CCZone(pRet);
    }
    
    pRet->initWithSpriteFrame(mSpriteFrame);
    CCActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCBSetSpriteFrame::update(float time)
{
    ((CCSprite*)m_pTarget)->setDisplayFrame(mSpriteFrame);
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
    if (CCActionInterval::initWithDuration(fDuration))
    {
        mDstAngle = fAngle;
        
        return true;
    }
    else 
    {
        return false;
    }
}

CCObject* CCBRotateTo::copyWithZone(CCZone *pZone)
{
    CCZone *pNewZone = NULL;
    CCBRotateTo *pRet = NULL;
    
    if (pZone && pZone->m_pCopyObject) {
        pRet = (CCBRotateTo*) (pZone->m_pCopyObject);
    } else {
        pRet = new CCBRotateTo();
        pZone = pNewZone = new CCZone(pRet);
    }
    
    pRet->initWithDuration(m_fDuration, mDstAngle);
    CCActionInterval::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCBRotateTo::startWithTarget(CCNode *pNode)
{
    CCActionInterval::startWithTarget(pNode);
    mStartAngle = m_pTarget->getRotation();
    mDiffAngle = mDstAngle - mStartAngle;
}

void CCBRotateTo::update(float time)
{
    m_pTarget->setRotation(mStartAngle + (mDiffAngle * time))
    ;
}

/************************************************************
 CCBEaseInstant
 ************************************************************/
CCBEaseInstant* CCBEaseInstant::create(CCActionInterval *pAction)
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

void CCBEaseInstant::update(float dt)
{
    if (dt < 0)
    {
        m_pInner->update(0);
    }
    else
    {
        m_pInner->update(1);
    }
}


NS_CC_EXT_END
