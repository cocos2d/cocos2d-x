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

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

//------------------------------------------------------------------
//
// SpineTestScene
//
//------------------------------------------------------------------
void SpineTestScene::runThisTest()
{
    CCLayer* pLayer = SpineTestLayer::create();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
}

bool SpineTestLayer::init () {
	if (!CCLayer::init()) return false;

	skeletonNode = CCSkeleton::createWithFile("spine/spineboy.json", "spine/spineboy.atlas");
	AnimationStateData_setMixByName(skeletonNode->state->data, "walk", "jump", 0.4f);
	AnimationStateData_setMixByName(skeletonNode->state->data, "jump", "walk", 0.4f);
	AnimationState_setAnimationByName(skeletonNode->state, "walk", true);
	skeletonNode->timeScale = 0.3f;
	skeletonNode->debugBones = true;

	skeletonNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1),
		CCFadeIn::create(1),
		CCDelayTime::create(5),
		NULL)));

	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	skeletonNode->setPosition(ccp(windowSize.width / 2, 20));
	addChild(skeletonNode);

	scheduleUpdate();

	return true;
}

void SpineTestLayer::update (float deltaTime) {
    if (skeletonNode->state->loop) {
        if (skeletonNode->state->time > 2) AnimationState_setAnimationByName(skeletonNode->state, "jump", false);
    } else {
        if (skeletonNode->state->time > 1) AnimationState_setAnimationByName(skeletonNode->state, "walk", true);
    }
}
