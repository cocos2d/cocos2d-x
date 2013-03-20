#include "CCBSequence.h"

using namespace cocos2d;
using namespace std;


NS_CC_EXT_BEGIN

CCBSequence::CCBSequence()
: mDuration(0.0f)
, mName("")
, mSequenceId(0)
, mChainedSequenceId(0)
, mCallbackChannel(NULL)
, mSoundChannel(NULL)
{}

CCBSequence::~CCBSequence() {
    CC_SAFE_RELEASE(mCallbackChannel);
    CC_SAFE_RELEASE(mSoundChannel);
}

float CCBSequence::getDuration()
{
    return mDuration;
}

void CCBSequence::setDuration(float fDuration)
{
    mDuration = fDuration;
}

const char* CCBSequence::getName()
{
    return mName.c_str();
}

void CCBSequence::setName(const char *pName)
{
    mName = pName;
}

int CCBSequence::getSequenceId()
{
    return mSequenceId;
}

void CCBSequence::setSequenceId(int nSequenceId)
{
    mSequenceId = nSequenceId;
}

CCBSequenceProperty* CCBSequence::getCallbackChannel()
{
    return mCallbackChannel;
}

void CCBSequence::setCallbackChannel(CCBSequenceProperty* callbackChannel)
{
    CC_SAFE_RELEASE(mCallbackChannel);
    mCallbackChannel = callbackChannel;
    CC_SAFE_RETAIN(mCallbackChannel);
}


CCBSequenceProperty* CCBSequence::getSoundChannel()
{
    return mSoundChannel;
}

void CCBSequence::setSoundChannel(CCBSequenceProperty* soundChannel)
{
    CC_SAFE_RELEASE(mSoundChannel);
    mSoundChannel = soundChannel;
    CC_SAFE_RETAIN(mSoundChannel);
}


int CCBSequence::getChainedSequenceId()
{
    return mChainedSequenceId;
}

void CCBSequence::setChainedSequenceId(int nChainedSequenceId)
{
    mChainedSequenceId = nChainedSequenceId;
}

NS_CC_EXT_END