/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2015 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "NavMeshTest.h"

USING_NS_CC_EXT;
USING_NS_CC;

#define START_POS_X -0.5
#define START_POS_Y -2.5
#define START_POS_Z -0.5

#define ARRAY_SIZE_X 4
#define ARRAY_SIZE_Y 3
#define ARRAY_SIZE_Z 4

NavMeshTests::NavMeshTests()
{
#if CC_USE_NAVMESH == 0
	ADD_TEST_CASE(NavMeshDisabled);
#else
    ADD_TEST_CASE(NavMeshTestDemo);
#endif
};

#if CC_USE_NAVMESH == 0
void NavMeshDisabled::onEnter()
{
	TTFConfig ttfConfig("fonts/arial.ttf", 16);
	auto label = Label::createWithTTF(ttfConfig, "Should define CC_USE_NAVMESH\n to run this test case");
	
	auto size = Director::getInstance()->getWinSize();
	label->setPosition(Vec2(size.width / 2, size.height / 2));

	addChild(label);

	TestCase::onEnter();
}
#else
std::string NavMeshTestDemo::title() const
{
    return "Navigation Mesh Test";
}

std::string NavMeshTestDemo::subtitle() const
{
    return "";
}

bool NavMeshTestDemo::init()
{
    if (!TestCase::init()) return false;
    
    
    return true;
}

void NavMeshTestDemo::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    
}

void NavMeshTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
}

void NavMeshTestDemo::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
}

NavMeshTestDemo::NavMeshTestDemo( void )
: _camera(nullptr)
{

}

void NavMeshTestDemo::update( float delta )
{
    
}

NavMeshTestDemo::~NavMeshTestDemo( void )
{
    
}

#endif
