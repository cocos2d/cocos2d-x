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
#include "../BaseTest.h"
#include "spine/spine-cocos2dx.h"

DEFINE_TEST_SUITE(SpineTests);

class SpineTestLayer : public TestCase
{
public:
    SpineTestLayer();
    
    virtual std::string title() const;
protected:
    std::string    _title;
};

class BatchingExample: public SpineTestLayer {
public:
    CREATE_FUNC(BatchingExample);
    ~BatchingExample ();
    
    virtual bool init ();
    
protected:
    spAtlas* _atlas;
    spAttachmentLoader* _attachmentLoader;
    spSkeletonData* _skeletonData;
    spAnimationStateData* _stateData;
};

class CoinExample: public SpineTestLayer
{
public:
    CREATE_FUNC(CoinExample);
    
    virtual bool init();
    
private:
    spine::SkeletonAnimation* skeletonNode;
};

class GoblinsExample : public SpineTestLayer {
public:
    CREATE_FUNC(GoblinsExample);
    
    virtual bool init ();
    
private:
    spine::SkeletonAnimation* skeletonNode;
};

class RaptorExample : public SpineTestLayer {
public:
    CREATE_FUNC(RaptorExample);
    
    virtual bool init ();
    
private:
    spine::SkeletonAnimation* skeletonNode;
};

class SpineboyExample : public SpineTestLayer {
public:
    CREATE_FUNC (SpineboyExample);
    
    virtual bool init ();
    
    virtual void update (float deltaTime);
    
private:
    spine::SkeletonAnimation* skeletonNode;
};

class TankExample : public SpineTestLayer {
public:
    CREATE_FUNC(TankExample);
    
    virtual bool init ();
    
private:
    spine::SkeletonAnimation* skeletonNode;
};

#endif // _EXAMPLELAYER_H_
