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
    Layer* pLayer = SpineTestLayer::create();
    addChild(pLayer);
    
    Director::sharedDirector()->replaceScene(this);
}

bool SpineTestLayer::init () {
	if (!Layer::init()) return false;

	skeletonNode = CCSkeletonAnimation::createWithFile("spine/spineboy.json", "spine/spineboy.atlas");
    skeletonNode->setMix("walk", "jump", 0.4f);
    skeletonNode->setMix("jump", "walk", 0.4f);    
    skeletonNode->setAnimation("walk", true);

	skeletonNode->timeScale = 0.3f;
	skeletonNode->debugBones = true;

	skeletonNode->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1),
		FadeIn::create(1),
		DelayTime::create(5),
		NULL)));

	Size windowSize = Director::sharedDirector()->getWinSize();
	skeletonNode->setPosition(ccp(windowSize.width / 2, 20));
	addChild(skeletonNode);

	scheduleUpdate();

	return true;
}

void SpineTestLayer::update (float deltaTime) {
    if (skeletonNode->states[0]->loop) {
        if (skeletonNode->states[0]->time > 2)
            skeletonNode->setAnimation("jump", false);
    } else {
        if (skeletonNode->states[0]->time > 1)
            skeletonNode->setAnimation("walk", true);
    }
}
