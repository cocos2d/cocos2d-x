#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AdsAdmob.h"

class MyAdListener : public cocos2d::plugin::AdListener
{
public:
	virtual void onReceiveAd();
	virtual void onPresentScreen();
	virtual void onFailedToReceiveAd(EAdErrorCode code, const char* msg);
	virtual void onDismissScreen();
};

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void testShow(CCObject* pSender);
	void testHide(CCObject* pSender);

	// option changed callback
	void caseChanged(CCObject* pSender);
	void posChanged(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::plugin::AdsAdmob* m_pAdmob;
    MyAdListener* m_pListener;

    cocos2d::CCMenuItemToggle* m_pCaseItem;
    cocos2d::CCMenuItemToggle* m_pPosItem;
    cocos2d::plugin::ProtocolAds* m_pAds;
    cocos2d::plugin::ProtocolAds::EBannerPos m_ePos;
};

#endif // __HELLOWORLD_SCENE_H__
