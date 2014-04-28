//
//  HelloWorldScene.cpp
//  CuteAPultCocos2D-x
//
//  Created by Clawoo on 9/8/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#include "HelloWorldScene.h"
#include "CCGleed2DLevel.h"

USING_NS_CC;
bool HelloWorld::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Gleed2DLevel * level=Gleed2DLevel::create("polytest.xml","sprites.plist","sprites.png");
	addChild(level);
	return true;
}
HelloWorld::HelloWorld()
{
}

HelloWorld::~HelloWorld()
{

}


Scene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Layer* layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}