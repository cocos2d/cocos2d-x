/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.

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
#pragma once

#include "cocos2d.h"
#include "Macros.h"

NS_CCR_BEGIN

class AnimationClip;
struct AnimProperties;

class AnimateClip : public cocos2d::Node {
public:
    
    typedef std::function<void()> AnimateEndCallback;
    
    static AnimateClip* createWithAnimationClip(cocos2d::Node* rootTarget, AnimationClip* clip);
    
    void startAnimate();
    void stopAnimate();
    void pauseAnimate();
    void resumeAnimate();
    
    void setCallbackForEndevent(const AnimateEndCallback &callback);
    
    virtual ~AnimateClip();

    //
    // Overrides
    //
    virtual void update(float dt) override;
    
private:
    AnimateClip();
    bool initWithAnimationClip(cocos2d::Node* rootTarget, AnimationClip* clip);
    void doUpdate(const AnimProperties& animProperties) const;
    cocos2d::Node* getTarget(const std::string &path) const;
    float computeElapse() const;

    AnimationClip* _clip;
    
    float _elapsed;
    cocos2d::Node *_rootTarget;
    
    AnimateEndCallback _endCallback;
    bool _needStop;
    float _durationToStop;
};

NS_CCR_END
