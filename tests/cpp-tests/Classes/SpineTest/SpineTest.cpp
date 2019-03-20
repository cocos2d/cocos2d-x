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

#include "SpineTest.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "spine/spine.h"

using namespace cocos2d;
using namespace std;
using namespace spine;


#define NUM_SKELETONS 50
static Cocos2dTextureLoader textureLoader;

PowInterpolation pow2(2);
PowOutInterpolation powOut2(2);
SwirlVertexEffect effect(400, powOut2);

//------------------------------------------------------------------
//
// SpineTestScene
//
//------------------------------------------------------------------

SpineTests::SpineTests()
{
    ADD_TEST_CASE(BatchingExample);
    ADD_TEST_CASE(CoinExample);
    ADD_TEST_CASE(GoblinsExample);
    ADD_TEST_CASE(RaptorExample);
    ADD_TEST_CASE(SpineboyExample);
    ADD_TEST_CASE(TankExample);
}

SpineTestLayer::SpineTestLayer()
: _title("")
{}

std::string SpineTestLayer::title() const
 {
     return _title;
 }

// BatchingExample
bool BatchingExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "BatchingExample";
    
    // Load the texture atlas.
    // Load the texture atlas. Note that the texture loader has to live
    // as long as the Atlas, as the Atlas destructor will call TextureLoader::unload.
    _atlas = new (__FILE__, __LINE__) Atlas("spine/spineboy.atlas", &textureLoader);
    CCASSERT(_atlas, "Error reading atlas file.");

    // This attachment loader configures attachments with data needed for cocos2d-x rendering.
    // Do not dispose the attachment loader until the skeleton data is disposed!
    _attachmentLoader = new (__FILE__, __LINE__) Cocos2dAtlasAttachmentLoader(_atlas);

    // Load the skeleton data.
    SkeletonJson* json = new (__FILE__, __LINE__) SkeletonJson(_attachmentLoader);
    json->setScale(0.6f); // Resizes skeleton data to 60% of the size it was in Spine.
    _skeletonData = json->readSkeletonDataFile("spine/spineboy-pro.json");
    CCASSERT(_skeletonData, json->getError().isEmpty() ? json->getError().buffer() : "Error reading skeleton data file.");
    delete json;

    // Setup mix times.
    _stateData = new (__FILE__, __LINE__) AnimationStateData(_skeletonData);
    _stateData->setMix("walk", "jump", 0.2f);
    _stateData->setMix("jump", "run", 0.2f);

    int xMin = _contentSize.width * 0.10f, xMax = _contentSize.width * 0.90f;
    int yMin = 0, yMax = _contentSize.height * 0.7f;
    for (int i = 0; i < NUM_SKELETONS; i++) {
        // Each skeleton node shares the same atlas, skeleton data, and mix times.
        SkeletonAnimation* skeletonNode = SkeletonAnimation::createWithData(_skeletonData, false);
        skeletonNode->setAnimationStateData(_stateData);

        skeletonNode->setAnimation(0, "walk", true);
        skeletonNode->addAnimation(0, "jump", true, RandomHelper::random_int(0, 300) / 100.0f);
        skeletonNode->addAnimation(0, "run", true);

        // alternative setting two color tint for groups of 10 skeletons
        // should end up with #skeletons / 10 batches
        // if (j++ < 10)
        //			skeletonNode->setTwoColorTint(true);
        //		if (j == 20) j = 0;
        // skeletonNode->setTwoColorTint(true);

        skeletonNode->setPosition(Vec2(
            RandomHelper::random_int(xMin, xMax),
            RandomHelper::random_int(yMin, yMax)
        ));
        addChild(skeletonNode);
    }

    scheduleUpdate();
    
    return true;
}

BatchingExample::~BatchingExample () {
    // SkeletonAnimation instances are cocos2d-x nodes and are disposed of automatically as normal, but the data created
    // manually to be shared across multiple SkeletonAnimations needs to be disposed of manually.
    delete _skeletonData;
    delete _stateData;
    delete _attachmentLoader;
    delete _atlas;
}

// CoinExample

bool CoinExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "CoinExample";
    
    skeletonNode = SkeletonAnimation::createWithBinaryFile("spine/coin-pro.skel", "spine/coin.atlas", 1);
    skeletonNode->setAnimation(0, "animation", true);

    skeletonNode->setPosition(Vec2(_contentSize.width / 2, _contentSize.height / 2));
    addChild(skeletonNode);

    scheduleUpdate();
    
    return true;
}

// GoblinsExample

bool GoblinsExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "GoblinsExample";
    
    skeletonNode = SkeletonAnimation::createWithJsonFile("spine/goblins-pro.json", "spine/goblins.atlas", 1.5f);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->setSkin("goblin");
    
    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    skeletonNode->setScale(0.6);
    addChild(skeletonNode);
    return true;
}

// RaptorExample

bool RaptorExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "RaptorExample";
    skeletonNode = SkeletonAnimation::createWithJsonFile("spine/raptor-pro.json", "spine/raptor.atlas", 0.5f);
    skeletonNode->setAnimation(0, "walk", true);
    skeletonNode->addAnimation(1, "gun-grab", false, 2);
    skeletonNode->setTwoColorTint(true);

    effect.setCenterY(200);
    swirlTime = 0;

    skeletonNode->setVertexEffect(&effect);

    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    addChild(skeletonNode);

    scheduleUpdate();
    return true;
}

// SpineboyExample

bool SpineboyExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "SpineboyExample";

    skeletonNode = SkeletonAnimation::createWithJsonFile("spine/spineboy-pro.json", "spine/spineboy.atlas", 0.6f);

    skeletonNode->setStartListener([](TrackEntry* entry) {
        log("%d start: %s", entry->getTrackIndex(), entry->getAnimation()->getName().buffer());
    });
    skeletonNode->setInterruptListener([](TrackEntry* entry) {
        log("%d interrupt", entry->getTrackIndex());
    });
    skeletonNode->setEndListener([](TrackEntry* entry) {
        log("%d end", entry->getTrackIndex());
    });
    skeletonNode->setCompleteListener([](TrackEntry* entry) {
        log("%d complete", entry->getTrackIndex());
    });
    skeletonNode->setDisposeListener([](TrackEntry* entry) {
        log("%d dispose", entry->getTrackIndex());
    });
    skeletonNode->setEventListener([](TrackEntry* entry, spine::Event* event) {
        log("%d event: %s, %d, %f, %s", entry->getTrackIndex(), event->getData().getName().buffer(), event->getIntValue(), event->getFloatValue(), event->getStringValue().buffer());
    });

    skeletonNode->setMix("walk", "jump", 0.4);
    skeletonNode->setMix("jump", "run", 0.4);
    skeletonNode->setAnimation(0, "walk", true);
    TrackEntry* jumpEntry = skeletonNode->addAnimation(0, "jump", false, 1);
    skeletonNode->addAnimation(0, "run", true);

    skeletonNode->setTrackStartListener(jumpEntry, [](TrackEntry* entry) {
        log("jumped!");
    });

    // skeletonNode->addAnimation(1, "test", true);
    // skeletonNode->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), DelayTime::create(5), NULL)));

    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    addChild(skeletonNode);

    scheduleUpdate();
    
    return true;
}

void SpineboyExample::update (float deltaTime) {
    // Test releasing memory.
    // Director::getInstance()->replaceScene(SpineboyExample::scene());
}

// TankExample

bool TankExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "TankExample";
    skeletonNode = SkeletonAnimation::createWithBinaryFile("spine/tank-pro.skel", "spine/tank.atlas", 0.5f);
    skeletonNode->setAnimation(0, "shoot", true);

    skeletonNode->setPosition(Vec2(_contentSize.width / 2 + 400, 20));
    addChild(skeletonNode);

    scheduleUpdate();
    
    return true;
}
