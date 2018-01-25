/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
