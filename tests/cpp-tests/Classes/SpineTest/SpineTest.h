/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef _SPINETEST_H_
#define _SPINETEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"
#include <spine/spine-cocos2dx.h>

class SpineTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class SpineTestSceneFFD : public TestScene
{
public:
    virtual void runThisTest();
};

class SpineTestLayer : public BaseTest
{
protected:
    std::string    _title;
    
public:
    SpineTestLayer(void);
    virtual ~SpineTestLayer(void);
    
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    
    // overrides
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};

class SpineTestLayerNormal: public SpineTestLayer {
private:
	spine::SkeletonAnimation* skeletonNode;
    
public:
    virtual std::string title() const override
    {
        return "Spine Test";
    }
    virtual std::string subtitle() const override
    {
        return "Normal Spine";
    }
	virtual bool init ();
	virtual void update (float deltaTime);
    //    void animationStateEvent (spine::SkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount);
    
	CREATE_FUNC (SpineTestLayerNormal);
};

class SpineTestLayerFFD: public SpineTestLayer {
private:
	spine::SkeletonAnimation* skeletonNode;
    
public:
    virtual std::string title() const override
    {
        return "Spine Test";
    }
    virtual std::string subtitle() const override
    {
        return "FFD Spine";
    }
	virtual bool init ();
	virtual void update (float deltaTime);
    //    void animationStateEvent (spine::SkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount);
    
	CREATE_FUNC (SpineTestLayerFFD);
};

class SpineTestPerformanceLayer: public SpineTestLayer
{
public:
    virtual std::string title() const override
    {
        return "Spine Test";
    }
    virtual std::string subtitle() const override
    {
        return "Performance Test for Spine";
    }
	virtual bool init ();
	virtual void update (float deltaTime);
    //    void animationStateEvent (spine::SkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount);
    
	CREATE_FUNC (SpineTestPerformanceLayer);
};

#endif // _EXAMPLELAYER_H_
