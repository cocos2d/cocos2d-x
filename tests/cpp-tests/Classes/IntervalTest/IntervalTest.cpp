#include "IntervalTest.h"
#include "../testResource.h"

#define SID_STEP1    100
#define SID_STEP2    101
#define SID_STEP3    102

#define IDC_PAUSE    200

IntervalLayer::IntervalLayer()
{
    _time0 = _time1 = _time2 = _time3 = _time4 = 0.0f;

    auto s = Director::getInstance()->getWinSize();
    // sun
    auto sun = ParticleSun::create();
    sun->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
    sun->setPosition(VisibleRect::rightTop().x-32,VisibleRect::rightTop().y-32);

    sun->setTotalParticles(130);
    sun->setLife(0.6f);
    this->addChild(sun);

    // timers
    _label0 = Label::createWithBMFont("fonts/bitmapFontTest4.fnt", "0");
    _label1 = Label::createWithBMFont("fonts/bitmapFontTest4.fnt", "0");
    _label2 = Label::createWithBMFont("fonts/bitmapFontTest4.fnt", "0");
    _label3 = Label::createWithBMFont("fonts/bitmapFontTest4.fnt", "0");
    _label4 = Label::createWithBMFont("fonts/bitmapFontTest4.fnt", "0");

    scheduleUpdate();
    schedule([&](float dt){
        _time1 +=dt;

        char str[10] = {0};
        sprintf(str, "%2.1f", _time1);
        _label1->setString( str );
    }, "step_1");

    schedule([&](float dt){
        _time2 +=dt;

        char str[10] = {0};
        sprintf(str, "%2.1f", _time2);
        _label2->setString( str );
    }, 0.5, "step_2");

    schedule([&](float dt){
        _time3 +=dt;

        char str[10] = {0};
        sprintf(str, "%2.1f", _time3);
        _label3->setString( str );
    }, 1, "step_3");

    schedule([&](float dt){
        _time4 +=dt;

        char str[10] = {0};
        sprintf(str, "%2.1f", _time4);
        _label4->setString( str );
    }, 2, "step_4");

    _label0->setPosition(s.width*1/6, s.height/2);
    _label1->setPosition(s.width*2/6, s.height/2);
    _label2->setPosition(s.width*3/6, s.height/2);
    _label3->setPosition(s.width*4/6, s.height/2);
    _label4->setPosition(s.width*5/6, s.height/2);

    addChild(_label0);
    addChild(_label1);
    addChild(_label2);
    addChild(_label3);
    addChild(_label4);

    // Sprite
    auto sprite = Sprite::create(s_pathGrossini);
    sprite->setPosition(VisibleRect::left().x + 40, VisibleRect::bottom().y + 50);
    
    auto jump = JumpBy::create(3, Vec2(s.width-80,0), 50, 4);
    
    addChild(sprite);
    sprite->runAction( RepeatForever::create(Sequence::create(jump, jump->reverse(), nullptr) ));
    // pause button
    auto item1 = MenuItemFont::create("Pause", [&](Ref* sender) {
		if(Director::getInstance()->isPaused())
			Director::getInstance()->resume();
		else
			Director::getInstance()->pause();
	});
    auto menu = Menu::create(item1, nullptr);
    menu->setPosition(s.width/2, s.height-50);

    addChild( menu );
}

IntervalLayer::~IntervalLayer()
{
    if(Director::getInstance()->isPaused())
    {
        Director::getInstance()->resume();
    }
}

void IntervalLayer::update(float dt)
{
    _time0 +=dt;
    char time[10] = {0};
    sprintf(time, "%2.1f", _time0);
    _label0->setString(time);
}

void IntervalTestScene::runThisTest()
{
    auto layer = new (std::nothrow) IntervalLayer();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}
