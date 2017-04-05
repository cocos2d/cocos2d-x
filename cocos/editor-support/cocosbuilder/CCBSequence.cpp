#include "editor-support/cocosbuilder/CCBSequence.h"

using namespace cocos2d;
using namespace std;


namespace cocosbuilder {

CCBSequence::CCBSequence()
: _duration(0.0f)
, _name("")
, mSequenceId(0)
, mChainedSequenceId(0)
, mCallbackChannel(nullptr)
, mSoundChannel(nullptr)
{}

CCBSequence::~CCBSequence() {
    CC_SAFE_RELEASE(mCallbackChannel);
    CC_SAFE_RELEASE(mSoundChannel);
}

float CCBSequence::getDuration()
{
    return _duration;
}

void CCBSequence::setDuration(float fDuration)
{
    _duration = fDuration;
}

const char* CCBSequence::getName()
{
    return _name.c_str();
}

void CCBSequence::setName(const char *pName)
{
    _name = pName;
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

}
