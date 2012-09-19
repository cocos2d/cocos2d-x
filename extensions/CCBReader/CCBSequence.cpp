#include "CCBSequence.h"

using namespace cocos2d;
using namespace std;


NS_CC_EXT_BEGIN

CCBSequence::CCBSequence()
: mDuration(0.0f)
, mName("")
, mSequenceId(0)
, mChainedSequenceId(0)
{}

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

int CCBSequence::getChainedSequenceId()
{
    return mChainedSequenceId;
}

void CCBSequence::setChainedSequenceId(int nChainedSequenceId)
{
    mChainedSequenceId = nChainedSequenceId;
}

NS_CC_EXT_END