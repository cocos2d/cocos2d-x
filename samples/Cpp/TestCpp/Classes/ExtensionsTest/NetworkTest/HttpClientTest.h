#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class HttpClientTest : public cocos2d::CCLayer
{
public:
    HttpClientTest();
    virtual ~HttpClientTest();
    void toExtensionsMainLayer(cocos2d::CCObject *sender);
    
    //Menu Callbacks
    void onMenuGetTestClicked(cocos2d::CCObject *sender);
    void onMenuPostTestClicked(cocos2d::CCObject *sender);
    void onMenuPostBinaryTestClicked(cocos2d::CCObject *sender);
    void onMenuPutTestClicked(cocos2d::CCObject *sender);
    void onMenuDeleteTestClicked(cocos2d::CCObject *sender);
    
    //Http Response Callback
    void onHttpRequestCompleted(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response);

private:
    cocos2d::CCLabelTTF* m_labelStatusCode;
};

#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT && !defined(WINRT_8_1)
inline void runHttpClientTest()  { return; }
#else
void runHttpClientTest();
#endif

#endif //__HTTPREQUESTHTTP_H
