#include "AccelerometerTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include <android/log.h>

#define FIX_POS(_pos, _min, _max) \
    if (_pos < _min)        \
    _pos = _min;        \
else if (_pos > _max)   \
    _pos = _max;        \

#define  LOG_TAG    "AccelerometerTest"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

//------------------------------------------------------------------
//
// AccelerometerTest
//
//------------------------------------------------------------------
AccelerometerTest::AccelerometerTest(void)
: m_fLastTime(0.0)
{
}

AccelerometerTest::~AccelerometerTest(void)
{
    m_pBall->release();
}

std::string AccelerometerTest::title()
{
	return "AccelerometerTest";
}

void AccelerometerTest::onEnter()
{
	CCLayer::onEnter();

    setIsAccelerometerEnabled(true);

	CGSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 32);
	addChild(label, 1);
	label->setPosition( CGPointMake(s.width/2, s.height-50) );

    m_pBall = CCSprite::spriteWithFile("Images/ball.png");
    m_pBall->setPosition(ccp(s.width / 2, s.height / 2));
    addChild(m_pBall);

    m_pBall->retain();
}

void AccelerometerTest::didAccelerate(UIAcceleration* pAccelerationValue)
{
//     double fNow = pAccelerationValue->timestamp;
// 
//     if (m_fLastTime > 0.0)
//     {
//         CGPoint ptNow = convertToUI
//     }
// 
//     m_fLastTime = fNow;

    CCDirector* pDir = CCDirector::sharedDirector();
    CGSize winSize   = pDir->getWinSize();

    /*FIXME: Testing on the Nexus S sometimes m_pBall is NULL */
    if ( m_pBall == NULL ) {
    	return;
    }

    CGSize ballSize  = m_pBall->getContentSize();

    CGPoint ptNow  = m_pBall->getPosition();
    CGPoint ptTemp = pDir->convertToUI(ptNow);

    ptTemp.x += pAccelerationValue->x * 9.81f;
    ptTemp.y -= pAccelerationValue->y * 9.81f;

    CGPoint ptNext = pDir->convertToGL(ptTemp);
    FIX_POS(ptNext.x, (ballSize.width / 2.0), (winSize.width - ballSize.width / 2.0));
    FIX_POS(ptNext.y, (ballSize.height / 2.0), (winSize.height - ballSize.height / 2.0));
    m_pBall->setPosition(ptNext);
}

//------------------------------------------------------------------
//
// AccelerometerTestScene
//
//------------------------------------------------------------------
void AccelerometerTestScene::runThisTest()
{
    CCLayer* pLayer = new AccelerometerTest();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
