#include "IntervalTest.h"
#include "../testResource.h"

#define SID_STEP1    100
#define SID_STEP2    101
#define SID_STEP3    102

#define IDC_PAUSE    200



IntervalLayer::IntervalLayer()
{
    _time0 = _time1 = _time2 = _time3 = _time4 = 0.0f;

    Size s = Director::sharedDirector()->getWinSize();
    // sun
    ParticleSystem* sun = ParticleSun::create();
    sun->setTexture(TextureCache::sharedTextureCache()->addImage("Images/fire.png"));
    sun->setPosition( ccp(VisibleRect::rightTop().x-32,VisibleRect::rightTop().y-32) );

    sun->setTotalParticles(130);
    sun->setLife(0.6f);
    this->addChild(sun);

    // timers
    _label0 = LabelBMFont::create("0", "fonts/bitmapFontTest4.fnt");
    _label1 = LabelBMFont::create("0", "fonts/bitmapFontTest4.fnt");
    _label2 = LabelBMFont::create("0", "fonts/bitmapFontTest4.fnt");
    _label3 = LabelBMFont::create("0", "fonts/bitmapFontTest4.fnt");
    _label4 = LabelBMFont::create("0", "fonts/bitmapFontTest4.fnt");

    scheduleUpdate();
    schedule(schedule_selector(IntervalLayer::step1));
    schedule(schedule_selector(IntervalLayer::step2), 0);
    schedule(schedule_selector(IntervalLayer::step3), 1.0f);
    schedule(schedule_selector(IntervalLayer::step4), 2.0f);

    _label0->setPosition(ccp(s.width*1/6, s.height/2));
    _label1->setPosition(ccp(s.width*2/6, s.height/2));
    _label2->setPosition(ccp(s.width*3/6, s.height/2));
    _label3->setPosition(ccp(s.width*4/6, s.height/2));
    _label4->setPosition(ccp(s.width*5/6, s.height/2));

    addChild(_label0);
    addChild(_label1);
    addChild(_label2);
    addChild(_label3);
    addChild(_label4);

    // Sprite
    Sprite* sprite = Sprite::create(s_pPathGrossini);
    sprite->setPosition( ccp(VisibleRect::left().x + 40, VisibleRect::bottom().y + 50) );
    
    JumpBy* jump = JumpBy::create(3, ccp(s.width-80,0), 50, 4);
    
    addChild(sprite);
    sprite->runAction( RepeatForever::create(Sequence::create(jump, jump->reverse(), NULL) ));
    // pause button
    MenuItem* item1 = MenuItemFont::create("Pause", [&](Object* sender) {
		if(Director::sharedDirector()->isPaused())
			Director::sharedDirector()->resume();
		else
			Director::sharedDirector()->pause();
	});
    Menu* menu = Menu::create(item1, NULL);
    menu->setPosition( ccp(s.width/2, s.height-50) );

    addChild( menu );
}

IntervalLayer::~IntervalLayer()
{
    if(Director::sharedDirector()->isPaused())
    {
        Director::sharedDirector()->resume();
    }
}

void IntervalLayer::update(float dt)
{
    _time0 +=dt;
    char time[10] = {0};
    sprintf(time, "%2.1f", _time0);
    _label0->setString(time);
}

void IntervalLayer::step1(float dt)
{
    _time1 +=dt;

    char str[10] = {0};
    sprintf(str, "%2.1f", _time1);
    _label1->setString( str );
}

void IntervalLayer::step2(float dt)
{
    _time2 +=dt;

    char str[10] = {0};
    sprintf(str, "%2.1f", _time2);
    _label2->setString( str ); 
}

void IntervalLayer::step3(float dt)
{
    _time3 +=dt;

    char str[10] = {0};
    sprintf(str, "%2.1f", _time3);
    _label3->setString( str ); 
}

void IntervalLayer::step4(float dt)
{
    _time4 +=dt;

    char str[10] = {0};
    sprintf(str, "%2.1f", _time4);
    _label4->setString( str ); 
}

void IntervalTestScene::runThisTest()
{
    Layer* pLayer = new IntervalLayer();
    addChild(pLayer);
    pLayer->release();

    Director::sharedDirector()->replaceScene(this);
}
