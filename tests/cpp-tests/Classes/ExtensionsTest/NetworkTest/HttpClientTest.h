#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"

class HttpClientTest : public cocos2d::Layer
{
public:
    HttpClientTest();
    virtual ~HttpClientTest();
    void toExtensionsMainLayer(cocos2d::Ref *sender);
    
    //Menu Callbacks
    void onMenuGetTestClicked(cocos2d::Ref *sender, bool isImmediate);
    void onMenuPostTestClicked(cocos2d::Ref *sender, bool isImmediate);
    void onMenuPostBinaryTestClicked(cocos2d::Ref *sender, bool isImmediate);
    void onMenuPutTestClicked(cocos2d::Ref *sender, bool isImmediate);
    void onMenuDeleteTestClicked(cocos2d::Ref *sender, bool isImmediate);
    
    //Http Response Callback
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

private:
    cocos2d::Label* _labelStatusCode;
};

void runHttpClientTest();

#endif //__HTTPREQUESTHTTP_H
