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

#ifndef __CCB_CCSEQUENCE_H__
#define __CCB_CCSEQUENCE_H__

#include <string>

#include "base/CCRef.h"
#include "editor-support/cocosbuilder/CCBSequenceProperty.h"

namespace cocosbuilder {

class CC_DLL CCBSequence : public cocos2d::Ref
{
public:
    CCBSequence();
    /**
     * @js NA
     * @lua NA
     */
    ~CCBSequence();
    float getDuration();
    void setDuration(float fDuration);
    
    CCBSequenceProperty* getCallbackChannel();
    void setCallbackChannel(CCBSequenceProperty* callbackChannel);

    CCBSequenceProperty* getSoundChannel();
    void setSoundChannel(CCBSequenceProperty* soundChannel);
    
    const char* getName();
    void setName(const char *pName);
    
    int getSequenceId();
    void setSequenceId(int nSequenceId);
    
    int getChainedSequenceId();
    void setChainedSequenceId(int nChainedSequenceId);
    
private:
    float _duration;
    std::string _name;
    int mSequenceId;
    int mChainedSequenceId;
    CCBSequenceProperty* mCallbackChannel;
    CCBSequenceProperty* mSoundChannel;
};


}


#endif // __CCB_CCSEQUENCE_H__
