#include "CurlTest.h"
#include "stdio.h"
#include "stdlib.h"
#include "curl/curl.h"

CurlTest::CurlTest()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* label = CCLabelTTF::labelWithString("Curl Test", "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );

    setIsTouchEnabled(true);

    // create a label to display the tip string
    m_pLabel = CCLabelTTF::labelWithString("Touch the screen to connect", "Arial", 22);
    m_pLabel->setPosition(ccp(s.width / 2, s.height / 2));
	addChild(m_pLabel, 0);
    
    m_pLabel->retain();
}


// the test code is
// http://curl.haxx.se/mail/lib-2009-12/0071.html
void CurlTest::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CURL *curl;
	CURLcode res;
	char buffer[10];

	curl = curl_easy_init();
	if (curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, "google.com");
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		if (res == 0)
		{
			m_pLabel->setString("0 response");
		}
		else
		{
			sprintf(buffer,"code: %i",res);
			m_pLabel->setString(buffer);
		}
	} 
	else 
	{
		m_pLabel->setString("no curl");
	} 
}

CurlTest::~CurlTest()
{
	m_pLabel->release();
}

void CurlTestScene::runThisTest()
{
    CCLayer* pLayer = new CurlTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}
