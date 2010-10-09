//
//  GameOverScene.m
//  Cocos2DSimpleGame
//
//  Created by Ray Wenderlich on 2/10/10.
//  Copyright 2010 Ray Wenderlich. All rights reserved.
//

#include "GameOverScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

bool GameOverScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = GameOverLayer::node();
		this->addChild(_layer);

		return true;
	}
	else
	{
		return false;
	}
}

GameOverScene::~GameOverScene()
{
	// _layer->release();
	// _layer = NULL;
}

//////////////////////////////
bool GameOverLayer::init()
{
	if ( CCColorLayer::initWithColor( ccc4(255,255,255,255) ) )
	{
		CGSize winSize = CCDirector::getSharedDirector()->getWinSize();
		this->_label = CCLabel::labelWithString("", "Artial", 32);
		_label->setColor( ccc3(0, 0, 0) );
		_label->setPosition( ccp(winSize.width/2, winSize.height/2) );
		this->addChild(_label);

		this->runAction( CCSequence::actions(
			CCDelayTime::actionWithDuration(3),
			CCCallFunc::actionWithTarget(this, callfunc_selector(GameOverLayer::gameOverDone)),
			NULL));

		return true;
	}
	else
	{
		return false;
	}
}

void GameOverLayer::gameOverDone()
{
	CCDirector::getSharedDirector()->replaceScene( HelloWorld::scene() );
}

GameOverLayer::~GameOverLayer()
{
	// _label->release();
	// _label = NULL;
}
