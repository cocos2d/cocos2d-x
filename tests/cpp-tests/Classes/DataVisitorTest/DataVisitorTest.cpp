/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "DataVisitorTest.h"
#include "../testResource.h"

USING_NS_CC;

DataVisitorTests::DataVisitorTests()
{
    ADD_TEST_CASE(PrettyPrinterDemo);
}
std::string PrettyPrinterDemo::title() const
{
    return "PrettyPrinter Test";
}

std::string PrettyPrinterDemo::subtitle() const
{
    return "Please see log!";
}

void PrettyPrinterDemo::addSprite()
{
    // create sprites
    
    auto s1 = Sprite::create("Images/grossini.png");
    auto s2 = Sprite::create("Images/grossini_dance_01.png");
    auto s3 = Sprite::create("Images/grossini_dance_02.png");
    auto s4 = Sprite::create("Images/grossini_dance_03.png");
    auto s5 = Sprite::create("Images/grossini_dance_04.png");
    
    s1->setPosition(50, 50);
    s2->setPosition(60, 50);
    s3->setPosition(70, 50);
    s4->setPosition(80, 50);
    s5->setPosition(90, 50);
    
    this->addChild(s1);
    this->addChild(s2);
    this->addChild(s3);
    this->addChild(s4);
    this->addChild(s5);
}

void PrettyPrinterDemo::onEnter()
{
    TestCase::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto label = Label::createWithTTF(title().c_str(), "fonts/arial.ttf", 28);
    label->setPosition(s.width/2, s.height * 4/5);
    this->addChild(label, 1);
    
    std::string strSubtitle = subtitle();
    if(strSubtitle.empty() == false)
    {
        auto subLabel = Label::createWithTTF(strSubtitle.c_str(), "fonts/Thonburi.ttf", 16);
        subLabel->setPosition(s.width/2, s.height * 3/5);
        this->addChild(subLabel, 1);
    }
    
    // Test code
    PrettyPrinter visitor;
    
    // print dictionary
    auto dict = __Dictionary::createWithContentsOfFile("animations/animations.plist");
    dict->acceptVisitor(visitor);
    log("%s", visitor.getResult().c_str());
    log("-------------------------------");
    
    __Set myset;
    for (int i = 0; i < 30; ++i) {
        myset.addObject(__String::createWithFormat("str: %d", i));
    }
    visitor.clear();
    myset.acceptVisitor(visitor);
    log("%s", visitor.getResult().c_str());
    log("-------------------------------");
    
    visitor.clear();
    addSprite();
//    dict = Director::getInstance()->getTextureCache()->snapshotTextures();
//    dict->acceptVisitor(visitor);
//    log("%s", visitor.getResult().c_str());
}
