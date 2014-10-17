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

static std::function<Layer*()> createFunctions[] =
{
    CL(SpineTestLayerNormal),
    CL(SpineTestLayerFFD),
    CL(SpineTestPerformanceLayer),
};

static int sceneIdx = -1;

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextSpineTestLayer()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backSpineTestLayer()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartSpineTestLayer()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

void SpineTestScene::runThisTest()
{
    auto layer = nextSpineTestLayer();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

void SpineTestSceneFFD::runThisTest()
{
    auto layer = SpineTestLayer::create();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

SpineTestLayer::SpineTestLayer(void)
: BaseTest()
{
}

SpineTestLayer::~SpineTestLayer(void)
{
}

std::string SpineTestLayer::title() const
{
    return "No title";
}

std::string SpineTestLayer::subtitle() const
{
    return "";
}

void SpineTestLayer::onEnter()
{
    BaseTest::onEnter();
}

void SpineTestLayer::restartCallback(Ref* sender)
{
    auto s = new SpineTestScene();
    s->addChild(restartSpineTestLayer());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SpineTestLayer::nextCallback(Ref* sender)
{
    auto s = new SpineTestScene();
    s->addChild( nextSpineTestLayer() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void SpineTestLayer::backCallback(Ref* sender)
{
    auto s = new SpineTestScene();
    s->addChild( backSpineTestLayer() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

bool SpineTestLayerNormal::init () {
    if (!Layer::init()) return false;
    
	skeletonNode = SkeletonAnimation::createWithFile("spine/spineboy.json", "spine/spineboy.atlas", 0.6f);
    skeletonNode->setScale(0.5);
    
	skeletonNode->setStartListener( [this] (int trackIndex) {
		spTrackEntry* entry = spAnimationState_getCurrent(skeletonNode->getState(), trackIndex);
		const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;
		log("%d start: %s", trackIndex, animationName);
	});
	skeletonNode->setEndListener( [] (int trackIndex) {
		log("%d end", trackIndex);
	});
	skeletonNode->setCompleteListener( [] (int trackIndex, int loopCount) {
		log("%d complete: %d", trackIndex, loopCount);
	});
	skeletonNode->setEventListener( [] (int trackIndex, spEvent* event) {
		log("%d event: %s, %d, %f, %s", trackIndex, event->data->name, event->intValue, event->floatValue, event->stringValue);
	});
    
	skeletonNode->setMix("walk", "jump", 0.2f);
	skeletonNode->setMix("jump", "run", 0.2f);
	skeletonNode->setAnimation(0, "walk", true);
	spTrackEntry* jumpEntry = skeletonNode->addAnimation(0, "jump", false, 3);
	skeletonNode->addAnimation(0, "run", true);
    
	skeletonNode->setTrackStartListener(jumpEntry, [] (int trackIndex) {
		log("jumped!");
	});
    
    Size windowSize = Director::getInstance()->getWinSize();
	skeletonNode->setPosition(Vec2(windowSize.width / 2, 20));
	addChild(skeletonNode);
    
	scheduleUpdate();
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this] (Touch* touch, Event* event) -> bool {
		if (!skeletonNode->getDebugBonesEnabled())
			skeletonNode->setDebugBonesEnabled(true);
		else if (skeletonNode->getTimeScale() == 1)
			skeletonNode->setTimeScale(0.3f);
        else
        {
            skeletonNode->setTimeScale(1);
            skeletonNode->setDebugBonesEnabled(false);
        }
		
        return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	return true;
}

void SpineTestLayerNormal::update (float deltaTime) {
    
}

bool SpineTestLayerFFD::init () {
    if (!Layer::init()) return false;
    
	skeletonNode = SkeletonAnimation::createWithFile("spine/goblins-ffd.json", "spine/goblins-ffd.atlas", 1.5f);
	skeletonNode->setAnimation(0, "walk", true);
	skeletonNode->setSkin("goblin");
    
    skeletonNode->setScale(0.5);
	Size windowSize = Director::getInstance()->getWinSize();
	skeletonNode->setPosition(Vec2(windowSize.width / 2, 20));
	addChild(skeletonNode);
    
	scheduleUpdate();
	
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this] (Touch* touch, Event* event) -> bool {
		if (!skeletonNode->getDebugBonesEnabled())
			skeletonNode->setDebugBonesEnabled(true);
		else if (skeletonNode->getTimeScale() == 1)
			skeletonNode->setTimeScale(0.3f);
        else
        {
            skeletonNode->setTimeScale(1);
            skeletonNode->setDebugBonesEnabled(false);
        }
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	return true;
}

void SpineTestLayerFFD::update (float deltaTime) {
    
}

bool SpineTestPerformanceLayer::init () {
    if (!Layer::init()) return false;
    
	scheduleUpdate();
	
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this] (Touch* touch, Event* event) -> bool
    {
        
        Vec2 pos = convertToNodeSpace(touch->getLocation());
        auto skeletonNode = SkeletonAnimation::createWithFile("spine/goblins-ffd.json", "spine/goblins-ffd.atlas", 1.5f);
        skeletonNode->setAnimation(0, "walk", true);
        skeletonNode->setSkin("goblin");
        
        skeletonNode->setScale(0.2);
        skeletonNode->setPosition(pos);
        addChild(skeletonNode);
        return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	return true;
}

void SpineTestPerformanceLayer::update (float deltaTime) {
    
}