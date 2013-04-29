/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

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
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AdsAdmob.h"

class MyAdsListener : public cocos2d::plugin::AdsListener
{
public:
	virtual void onAdsResult(cocos2d::plugin::AdsResultCode code, const char* msg);
	virtual void onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points);
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
	void typeChanged(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::plugin::AdsAdmob* m_pAdmob;
    MyAdsListener* m_pListener;

    cocos2d::CCMenuItemToggle* m_pCaseItem;
    cocos2d::CCMenuItemToggle* m_pTypeItem;
    cocos2d::CCMenuItemToggle* m_pPosItem;

    cocos2d::plugin::ProtocolAds* m_pAds;
    cocos2d::plugin::ProtocolAds::AdsPos m_ePos;
    cocos2d::plugin::ProtocolAds::AdsType m_eType;
};

#endif // __HELLOWORLD_SCENE_H__
