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
void SpineTestScene::runThisTest()
{
    auto layer = SpineTestLayer::create();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

bool SpineTestLayer::init () {
    if (!Layer::init()) return false;
    
    skeletonNode = SkeletonAnimation::createWithFile("spine/spineboy.json", "spine/spineboy.atlas");
    skeletonNode->setMix("walk", "jump", 0.2f);
    skeletonNode->setMix("jump", "walk", 0.4f);
    
    skeletonNode->setAnimationListener(this, animationStateEvent_selector(SpineTestLayer::animationStateEvent));
    skeletonNode->setAnimation(0, "walk", false);
    skeletonNode->addAnimation(0, "jump", false);
    skeletonNode->addAnimation(0, "walk", true);
    skeletonNode->addAnimation(0, "jump", true, 4);
    // skeletonNode->addAnimation(1, "drawOrder", true);
    
    skeletonNode->timeScale = 0.3f;
    skeletonNode->debugBones = true;
    skeletonNode->update(0);
    
    skeletonNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1),
                                                                       CCFadeIn::create(1),
                                                                       CCDelayTime::create(5),
                                                                       NULL)));
    
    Size windowSize = Director::getInstance()->getWinSize();
    skeletonNode->setPosition(Vec2(windowSize.width / 2, 20));
    addChild(skeletonNode);
    
    scheduleUpdate();
    
    return true;
}

void SpineTestLayer::update (float deltaTime) {
    
}

void SpineTestLayer::animationStateEvent (SkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount) {
    spTrackEntry* entry = spAnimationState_getCurrent(node->state, trackIndex);
    const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;
    
    switch (type) {
        case ANIMATION_START:
            log("%d start: %s", trackIndex, animationName);
            break;
        case ANIMATION_END:
            log("%d end: %s", trackIndex, animationName);
            break;
        case ANIMATION_COMPLETE:
            log("%d complete: %s, %d", trackIndex, animationName, loopCount);
            break;
        case ANIMATION_EVENT:
            log("%d event: %s, %s: %d, %f, %s", trackIndex, animationName, event->data->name, event->intValue, event->floatValue, event->stringValue);
            break;
    }
}
