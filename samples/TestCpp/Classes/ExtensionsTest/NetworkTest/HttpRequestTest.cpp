#include "HttpRequestTest.h"
#include "../ExtensionsTest.h"

#define GETURL "http://www.google.com"
#define POSTURL "http://www.replacewithyours.com/post.php"
#define DOWNLOADURL "http://www.google.com/index.html"

USING_NS_CC;
USING_NS_CC_EXT;

HttpRequestTest::HttpRequestTest() : m_labelStatusCode(NULL)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label = CCLabelTTF::create("Http Request Test", "Arial", 28);
    label->setPosition(ccp(winSize.width / 2, winSize.height - 50));
    addChild(label, 0);
    
    CCMenu *menuRequest = CCMenu::create();
    menuRequest->setPosition(CCPointZero);
    addChild(menuRequest);
    
    //Get 
    CCLabelTTF *labelGet = CCLabelTTF::create("Test Get", "Arial", 15);
    CCMenuItemLabel *itemGet = CCMenuItemLabel::create(labelGet, this, menu_selector(HttpRequestTest::onLabelGetTestClicked));
    itemGet->setPosition(ccp(winSize.width / 2, winSize.height - 100));
    menuRequest->addChild(itemGet);
    
    //Post
    CCLabelTTF *labelPost = CCLabelTTF::create("Test Post", "Arial", 15);
    CCMenuItemLabel *itemPost = CCMenuItemLabel::create(labelPost, this, menu_selector(HttpRequestTest::onLabelPostTestClicked));
    itemPost->setPosition(ccp(winSize.width / 2, winSize.height - 130));
    menuRequest->addChild(itemPost);
    
    //Post Binary
    CCLabelTTF *labelPostBinary = CCLabelTTF::create("Test Post Binary", "Arial", 15);
    CCMenuItemLabel *itemPostBinary = CCMenuItemLabel::create(labelPostBinary, this, menu_selector(HttpRequestTest::onLabelPostBinaryTestClicked));
    itemPostBinary->setPosition(ccp(winSize.width / 2, winSize.height - 160));
    menuRequest->addChild(itemPostBinary);
    
    //Response Code Label
    CCLabelTTF *labelStatus = CCLabelTTF::create("Notice: Replace Post Url With Your Own", "Marker Felt", 20);
    labelStatus->setPosition(ccp(winSize.width / 2,  winSize.height - 250));
    addChild(labelStatus);
    setLabelStatusCode(labelStatus);
    
    //Back Menu
    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(HttpRequestTest::toExtensionsMainLayer));
    itemBack->setPosition(ccp(winSize.width - 50, 25));
    CCMenu *menuBack = CCMenu::create(itemBack, NULL);
    menuBack->setPosition(CCPointZero);
    addChild(menuBack);
}

void HttpRequestTest::onLabelGetTestClicked(cocos2d::CCObject *sender)
{    
    /*****
     test 1
     ******/
    
    HttpRequest* request1 = new HttpRequest();
    // required fields
    request1->setUrl("http://www.httpbin.org/ip");
    request1->setRequestType(HttpRequest::kHttpGet);
    request1->setResponseCallback(this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
    // optional fields                            
    request1->setTag("HttpTest: GET");
    
    CCHttpClient::getInstance()->send(request1);
    
    // don't forget to release it, pair to new
    request1->release();
    
    /*****
     test 2
     ******/    
    HttpRequest* request2 = new HttpRequest();
    request2->setUrl("http://www.httpbin.org/get");
    request2->setRequestType(HttpRequest::kHttpGet);
    request2->setResponseCallback(this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
    CCHttpClient::getInstance()->send(request2);
    request2->release();
    
    /*****
     test 3
     ******/ 
    HttpRequest* request3 = new HttpRequest();
    request3->setUrl("http://just-make-this-request-failed.com");
    request3->setRequestType(HttpRequest::kHttpGet);
    request3->setResponseCallback(this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
    CCHttpClient::getInstance()->send(request3);
    request3->release();

}

void HttpRequestTest::onLabelPostTestClicked(cocos2d::CCObject *sender)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl("http://www.httpbin.org/post");
    request->setRequestType(HttpRequest::kHttpPost);
    request->setResponseCallback(this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
    
    // write the post data
    const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetowrkTest";
    request->setRequestData(postData, strlen(postData)); 
    
    request->setTag("HttpRequestTest: POST JSON");
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void HttpRequestTest::onLabelPostBinaryTestClicked(cocos2d::CCObject *sender)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl("http://www.httpbin.org/post");
    request->setRequestType(HttpRequest::kHttpPost);
    request->setResponseCallback(this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
    
    // write the post data
    char postData[22] = "binary=hello\0\0cocos2d";  // including \0, the strings after \0 should not be cut in response
    request->setRequestData(postData, 22); 
    
    request->setTag("HttpRequestTest: POST Binary");
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void HttpRequestTest::onHttpRequestCompleted(cocos2d::CCObject *sender, void *data)
{
    HttpResponse *response = (HttpResponse*)data;

    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag())) 
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    CCLog("response code: %d", response->getResponseCode());
    
    if (!response->isSucceed()) 
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    for (int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
    }
    printf("\n");
}

void HttpRequestTest::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void runHttpRequestTest()
{
    CCScene *pScene = CCScene::create();
    HttpRequestTest *pLayer = new HttpRequestTest();
    pScene->addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
    pLayer->release();
}

