#include "CurrentLanguageTest.h"

CurrentLanguageTest::CurrentLanguageTest()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* label = CCLabelTTF::labelWithString("Current language Test", "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );

	CCLabelTTF *labelLanguage = CCLabelTTF::labelWithString("", "Arial", 20);
	labelLanguage->setPosition(ccp(s.width/2, s.height/2));

	ccLanguageType currentLanguageType = CCApplication::sharedApplication().getCurrentLanguage();
	switch (currentLanguageType)
	{
	case kLanguageEnglish:
		labelLanguage->setString("current language is English");
		break;
	case kLanguageChinese:
		labelLanguage->setString("current language is Chinese");
		break;
	}

	addChild(labelLanguage);
}

void CurrentLanguageTestScene::runThisTest()
{
    CCLayer* pLayer = new CurrentLanguageTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}
