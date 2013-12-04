/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

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

#include "ConsoleTest.h"
#include "../testResource.h"

//------------------------------------------------------------------
//
// EaseSpriteDemo
//
//------------------------------------------------------------------

static int sceneIdx = -1;

static std::function<Layer*()> createFunctions[] =
{
    CL(ConsoleTCP),
    CL(ConsoleStdin),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextConsoleTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backConsoleTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartConsoleTest()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
} 


BaseTestConsole::BaseTestConsole()
{
}

BaseTestConsole::~BaseTestConsole(void)
{
}

std::string BaseTestConsole::title()
{
    return "No title";
}

void BaseTestConsole::onEnter()
{
    BaseTest::onEnter();
}

void BaseTestConsole::restartCallback(Object* sender)
{
    auto s = new ConsoleTestScene();
    s->addChild(restartConsoleTest());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseTestConsole::nextCallback(Object* sender)
{
    auto s = new ConsoleTestScene();
    s->addChild( nextConsoleTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseTestConsole::backCallback(Object* sender)
{
    auto s = new ConsoleTestScene();
    s->addChild( backConsoleTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

void ConsoleTestScene::runThisTest()
{
    auto layer = nextConsoleTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

//------------------------------------------------------------------
//
// ConsoleTCP
//
//------------------------------------------------------------------

ConsoleTCP::ConsoleTCP()
{
    _console = Console::create();
    _console->retain();
}

ConsoleTCP::~ConsoleTCP()
{
    _console->cancel();
    _console->release();
}

void ConsoleTCP::onEnter()
{
    BaseTestConsole::onEnter();
    _console->listenOnTCP(5678);
}

std::string ConsoleTCP::title()
{
    return "Console TCP";
}

//------------------------------------------------------------------
//
// ConsoleStdin
//
//------------------------------------------------------------------

ConsoleStdin::ConsoleStdin()
{
    _console = Console::create();
    _console->retain();
}

ConsoleStdin::~ConsoleStdin()
{
    _console->cancel();
    _console->release();
}

void ConsoleStdin::onEnter()
{
    BaseTestConsole::onEnter();
    _console->listenOnStdin();
}

std::string ConsoleStdin::title()
{
    return "Console STDIN";
}
