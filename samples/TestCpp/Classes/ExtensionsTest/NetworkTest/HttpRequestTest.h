#ifndef __HTTPREQUESTHTTP_H
#define __HTTPREQUESTHTTP_H

#include "cocos2d.h"
#include "cocos-ext.h"

class HttpRequestTest : public cocos2d::CCLayer
{
    CC_SYNTHESIZE(CCLabelTTF *, m_labelStatusCode, LabelStatusCode);
public:
    HttpRequestTest();
    void toExtensionsMainLayer(cocos2d::CCObject *sender);
    
    //Menu Callbacks
    void onLabelGetTestClicked(cocos2d::CCObject *sender);
    void onLabelPostTestClicked(cocos2d::CCObject *sender);
    void onLabelPostBinaryTestClicked(cocos2d::CCObject *sender);
    void onLabelDownloadTestClicked(cocos2d::CCObject *sender);
    
    //Http Response Callback
    void onHttpRequestCompleted(cocos2d::CCObject *sender, void *data);
};

void runHttpRequestTest();

#endif //__HTTPREQUESTHTTP_H
