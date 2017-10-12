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
#include "AnimationClipProperties.h"

NS_CCR_BEGIN

class AnimationClip: public cocos2d::Ref
{
public:
    enum class WrapMode {Default, Normal, Loop, PingPong, Reverse, LoopReverse, PingPongReverse};

    static AnimationClip* create();
    virtual ~AnimationClip();
    
    bool init();

    void setName(const std::string& name);
    const std::string& getName() const;

    void setDuration(float duration);
    float getDuration() const;

    void setSample(float sample);
    float getSample() const;

    void setSpeed(float speed);
    float getSpeed() const;

    void setWrapMode(WrapMode wrapMode);
    WrapMode getWrapMode() const;

    void addAnimProperties(const AnimProperties& properties);
    const std::vector<AnimProperties>& getAnimProperties() const;
    
private:
    AnimationClip();

    std::string _name;
    float _duration;
    float _sample;
    float _speed;
    WrapMode _wrapMode;
    std::vector<AnimProperties> _animPropertiesVec;
};

NS_CCR_END
