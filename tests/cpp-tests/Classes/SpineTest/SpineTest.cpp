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
    _atlas = spAtlas_createFromFile("spine/spineboy.atlas", 0);
    CCASSERT(_atlas, "Error reading atlas file.");
    
    // This attachment loader configures attachments with data needed for cocos2d-x rendering.
    // Do not dispose the attachment loader until the skeleton data is disposed!
    _attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);
    
    // Load the skeleton data.
    spSkeletonJson* json = spSkeletonJson_createWithLoader(_attachmentLoader);
    json->scale = 0.6f; // Resizes skeleton data to 60% of the size it was in Spine.
    _skeletonData = spSkeletonJson_readSkeletonDataFile(json, "spine/spineboy-ess.json");
    CCASSERT(_skeletonData, json->error ? json->error : "Error reading skeleton data file.");
    spSkeletonJson_dispose(json);
    
    // Setup mix times.
    _stateData = spAnimationStateData_create(_skeletonData);
    spAnimationStateData_setMixByName(_stateData, "walk", "jump", 0.2f);
    spAnimationStateData_setMixByName(_stateData, "jump", "run", 0.2f);
    
    int xMin = _contentSize.width * 0.10f, xMax = _contentSize.width * 0.90f;
    int yMin = 0, yMax = _contentSize.height * 0.7f;
    for (int i = 0; i < 50; i++) {
        // Each skeleton node shares the same atlas, skeleton data, and mix times.
        SkeletonAnimation* skeletonNode = SkeletonAnimation::createWithData(_skeletonData, false);
        skeletonNode->setAnimationStateData(_stateData);
        
        skeletonNode->setAnimation(0, "walk", true);
        skeletonNode->addAnimation(0, "jump", false, 3);
        skeletonNode->addAnimation(0, "run", true);
        
        skeletonNode->setPosition(Vec2(
                                       RandomHelper::random_int(xMin, xMax),
                                       RandomHelper::random_int(yMin, yMax)
                                       ));
        skeletonNode->setScale(0.8);
        addChild(skeletonNode);
    }
    
    return true;
}

BatchingExample::~BatchingExample () {
    // SkeletonAnimation instances are cocos2d-x nodes and are disposed of automatically as normal, but the data created
    // manually to be shared across multiple SkeletonAnimations needs to be disposed of manually.
    spSkeletonData_dispose(_skeletonData);
    spAnimationStateData_dispose(_stateData);
    spAttachmentLoader_dispose(_attachmentLoader);
    spAtlas_dispose(_atlas);
}

// CoinExample

bool CoinExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "CoinExample";
    
    skeletonNode = SkeletonAnimation::createWithJsonFile("spine/coin-pro.json", "spine/coin.atlas", 1.f);
    skeletonNode->setAnimation(0, "rotate", true);
    
    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 100));
    addChild(skeletonNode);
    
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
    skeletonNode->setAnimation(1, "empty", false);
    skeletonNode->addAnimation(1, "gungrab", false, 2);
    
    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    skeletonNode->setScale(0.6);
    addChild(skeletonNode);
    return true;
}

// SpineboyExample

bool SpineboyExample::init () {
    if (!SpineTestLayer::init()) return false;
    
    _title = "SpineboyExample";
    skeletonNode = SkeletonAnimation::createWithJsonFile("spine/spineboy-ess.json", "spine/spineboy.atlas", 0.6f);
    skeletonNode->setStartListener( [] (spTrackEntry* entry) {
        log("%d start: %s", entry->trackIndex, entry->animation->name);
    });
    skeletonNode->setInterruptListener( [] (spTrackEntry* entry) {
        log("%d interrupt", entry->trackIndex);
    });
    skeletonNode->setEndListener( [] (spTrackEntry* entry) {
        log("%d end", entry->trackIndex);
    });
    skeletonNode->setCompleteListener( [] (spTrackEntry* entry) {
        log("%d complete", entry->trackIndex);
    });
    skeletonNode->setDisposeListener( [] (spTrackEntry* entry) {
        log("%d dispose", entry->trackIndex);
    });
    skeletonNode->setEventListener( [] (spTrackEntry* entry, spEvent* event) {
        log("%d event: %s, %d, %f, %s", entry->trackIndex, event->data->name, event->intValue, event->floatValue, event->stringValue);
    });
    
    skeletonNode->setMix("walk", "jump", 0.4);
    skeletonNode->setMix("jump", "run", 0.4);
    skeletonNode->setAnimation(0, "walk", true);
    spTrackEntry* jumpEntry = skeletonNode->addAnimation(0, "jump", false, 1);
    skeletonNode->addAnimation(0, "run", true);
    
    skeletonNode->setTrackStartListener(jumpEntry, [] (spTrackEntry* entry) {
        log("jumped!");
    });
    
    // skeletonNode->addAnimation(1, "test", true);
    // skeletonNode->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), DelayTime::create(5), NULL)));
    
    skeletonNode->setPosition(Vec2(_contentSize.width / 2, 20));
    skeletonNode->setScale(0.8);
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
    skeletonNode = SkeletonAnimation::createWithJsonFile("spine/tank-pro.json", "spine/tank.atlas", 0.5f);
    skeletonNode->setAnimation(0, "drive", true);
    
    skeletonNode->setPosition(Vec2(_contentSize.width / 2 + 400, 20));
    skeletonNode->setScale(0.8);
    addChild(skeletonNode);
    
    return true;
}
