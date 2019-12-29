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
#include <spine/spine-cocos2dx.h>

#ifdef COCOS2D_DEBUG
#include <spine/Debug.h>
#endif

//DEFINE_TEST_SUITE(SpineTests);

class SpineTests : public TestSuite
{
public:
    SpineTests();

    virtual ~SpineTests();
private:
    std::vector<std::string> _searchPaths;
#ifdef COCOS2D_DEBUG
    spine::DebugExtension* debugExtension = nullptr;
#endif
};

class SpineTestLayer : public TestCase
{
public:
    SpineTestLayer();
    virtual ~SpineTestLayer();

    virtual bool init();
    virtual std::string title() const override;
protected:
    std::string    _title;
    spine::SkeletonAnimation* skeletonNode = nullptr;
    int _touchIndex = 0;
};


class BatchingExample : public SpineTestLayer {
public:

    CREATE_FUNC(BatchingExample);
    ~BatchingExample();

    virtual bool init();

protected:
    spine::Atlas* _atlas;
    spine::AttachmentLoader* _attachmentLoader;
    spine::SkeletonData* _skeletonData;
    spine::AnimationStateData* _stateData;
};


class CoinExample : public SpineTestLayer {
public:

    CREATE_FUNC(CoinExample);

    virtual bool init();

};
class GoblinsExample : public SpineTestLayer {
public:
    CREATE_FUNC(GoblinsExample);
    
    virtual bool init ();
    
};

class IKExample : public SpineTestLayer {
public:

    CREATE_FUNC(IKExample);

    virtual bool init();

private:
    cocos2d::Vec2 position;
};

class MixAndMatchExample : public SpineTestLayer {
public:
    
    CREATE_FUNC(MixAndMatchExample);

    virtual bool init();

    virtual ~MixAndMatchExample();

private:
    spine::Skin* skin;
};

class RaptorExample : public SpineTestLayer {
public:
    CREATE_FUNC(RaptorExample);

    virtual bool init();

    virtual void update(float fDelta);

private:
    float swirlTime;
};

class SkeletonRendererSeparatorExample : public SpineTestLayer {
public:
    CREATE_FUNC(SkeletonRendererSeparatorExample);

    virtual bool init();

    virtual void update(float deltaTime);

private:
    spine::SkeletonRenderer* frontNode;
    cocos2d::DrawNode* betweenNode;

};

class SpineboyExample : public SpineTestLayer {
public:
    CREATE_FUNC(SpineboyExample);

    virtual bool init();

    virtual void update(float deltaTime);

};

class TankExample : public SpineTestLayer {
public:
    CREATE_FUNC(TankExample);

    virtual bool init();

};

#endif // _EXAMPLELAYER_H_
