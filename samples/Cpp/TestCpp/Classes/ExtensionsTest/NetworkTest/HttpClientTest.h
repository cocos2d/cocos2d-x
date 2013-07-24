#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class HttpClientTest : public cc::Layer
{
public:
    HttpClientTest();
    virtual ~HttpClientTest();
    void toExtensionsMainLayer(cc::Object *sender);
    
    //Menu Callbacks
    void onMenuGetTestClicked(cc::Object *sender);
    void onMenuPostTestClicked(cc::Object *sender);
    void onMenuPostBinaryTestClicked(cc::Object *sender);
    void onMenuPutTestClicked(cc::Object *sender);
    void onMenuDeleteTestClicked(cc::Object *sender);
    
    //Http Response Callback
    void onHttpRequestCompleted(cc::extension::HttpClient *sender, cc::extension::HttpResponse *response);

private:
    cc::LabelTTF* _labelStatusCode;
};

void runHttpClientTest();

#endif //__HTTPREQUESTHTTP_H
