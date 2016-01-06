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
    PrettyPrinter vistor;
    
    // print dictionary
    auto dict = __Dictionary::createWithContentsOfFile("animations/animations.plist");
    dict->acceptVisitor(vistor);
    log("%s", vistor.getResult().c_str());
    log("-------------------------------");
    
    __Set myset;
    for (int i = 0; i < 30; ++i) {
        myset.addObject(__String::createWithFormat("str: %d", i));
    }
    vistor.clear();
    myset.acceptVisitor(vistor);
    log("%s", vistor.getResult().c_str());
    log("-------------------------------");
    
    vistor.clear();
    addSprite();
//    dict = Director::getInstance()->getTextureCache()->snapshotTextures();
//    dict->acceptVisitor(vistor);
//    log("%s", vistor.getResult().c_str());
}
