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

void updateBackSprite(Skeleton * skeleton, Sprite * sprite)
{
    auto pos = skeleton->getPosition();
    auto bounds = skeleton->getBoundingBox();
    auto origBounds = sprite->getTextureRect();
    
    sprite->setPosition(Point(bounds.getMinX(), bounds.getMinY()));
    sprite->setScale((bounds.getMaxX() - bounds.getMinX()) / (origBounds.getMaxX() - origBounds.getMinX()),
                     (bounds.getMaxY() - bounds.getMinY()) / (origBounds.getMaxY() - origBounds.getMinY()));
}

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
    
    
    spineboy = SkeletonAnimation::createWithFile("spine/spineboy.json", "spine/spineboy.atlas");
    spineboy->setAnimation(0, "walk", false);
    spineboy->addAnimation(0, "jump", true);
    spineboy->addAnimation(0, "walk", true, 3);
    spineboy->timeScale = 1.f;
    spineboy->update(0);
    
    spineboy_back = Sprite::create("Images/MagentaSquare.png");
    spineboy_back->setOpacity(128);
    spineboy_back->setAnchorPoint(Point(0,0));
    
    monster = SkeletonAnimation::createWithFile("spine/skeleton.json", "spine/skeleton.atlas");
    monster->setAnimation(0, "animation", true);
    monster->timeScale = 1.f;
    monster->update(0);
    
    monster_back = Sprite::create("Images/MagentaSquare.png");
    monster_back->setOpacity(128);
    monster_back->setAnchorPoint(Point(0,0));
    
    goblin = SkeletonAnimation::createWithFile("spine/goblins.json", "spine/goblins.atlas");
    goblin->setSkin("goblin");
    goblin->setSlotsToSetupPose();
    goblin->timeScale = 1.f;
    goblin->update(0);
    goblin->setAnimation(0, "walk", true);

    goblin_back = Sprite::create("Images/MagentaSquare.png");
    goblin_back->setOpacity(128);
    goblin_back->setAnchorPoint(Point(0,0));
    
    Size windowSize = Director::getInstance()->getWinSize();
    spineboy->setPosition(Point(1 * windowSize.width / 4, windowSize.height / 5));
    addChild(spineboy_back);
    addChild(spineboy);
    monster->setPosition(Point(2 * windowSize.width / 4, windowSize.height / 5));
    addChild(monster_back);
    addChild(monster);
    goblin->setPosition(Point(3 *windowSize.width / 4, windowSize.height / 5));
    addChild(goblin_back);
    addChild(goblin);
    
    scheduleUpdate();
    
    return true;
}

void SpineTestLayer::update (float deltaTime) {
    updateBackSprite(spineboy, spineboy_back);
    updateBackSprite(monster, monster_back);
    updateBackSprite(goblin, goblin_back);
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
