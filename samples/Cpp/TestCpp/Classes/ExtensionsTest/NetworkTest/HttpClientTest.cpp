#include "HttpClientTest.h"
#include "../ExtensionsTest.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;

HttpClientTest::HttpClientTest() 
: m_labelStatusCode(NULL)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    const int MARGIN = 40;
    const int SPACE = 35;
    
    CCLabelTTF *label = CCLabelTTF::create("Http Request Test", "Arial", 28);
    label->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN));
    addChild(label, 0);
    
    CCMenu *menuRequest = CCMenu::create();
    menuRequest->setPosition(CCPointZero);
    addChild(menuRequest);
    
    // Get 
    CCLabelTTF *labelGet = CCLabelTTF::create("Test Get", "Arial", 22);
    CCMenuItemLabel *itemGet = CCMenuItemLabel::create(labelGet, this, menu_selector(HttpClientTest::onMenuGetTestClicked));
    itemGet->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemGet);
    
    // Post
    CCLabelTTF *labelPost = CCLabelTTF::create("Test Post", "Arial", 22);
    CCMenuItemLabel *itemPost = CCMenuItemLabel::create(labelPost, this, menu_selector(HttpClientTest::onMenuPostTestClicked));
    itemPost->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemPost);
    
    // Post Binary
    CCLabelTTF *labelPostBinary = CCLabelTTF::create("Test Post Binary", "Arial", 22);
    CCMenuItemLabel *itemPostBinary = CCMenuItemLabel::create(labelPostBinary, this, menu_selector(HttpClientTest::onMenuPostBinaryTestClicked));
    itemPostBinary->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemPostBinary);

    // Put
    CCLabelTTF *labelPut = CCLabelTTF::create("Test Put", "Arial", 22);
    CCMenuItemLabel *itemPut = CCMenuItemLabel::create(labelPut, this, menu_selector(HttpClientTest::onMenuPutTestClicked));
    itemPut->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemPut);

    // Delete
    CCLabelTTF *labelDelete = CCLabelTTF::create("Test Delete", "Arial", 22);
    CCMenuItemLabel *itemDelete = CCMenuItemLabel::create(labelDelete, this, menu_selector(HttpClientTest::onMenuDeleteTestClicked));
    itemDelete->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 5 * SPACE));
    menuRequest->addChild(itemDelete);
    
    // Response Code Label
    m_labelStatusCode = CCLabelTTF::create("HTTP Status Code", "Marker Felt", 20);
    m_labelStatusCode->setPosition(ccp(winSize.width / 2,  winSize.height - MARGIN - 6 * SPACE));
    addChild(m_labelStatusCode);
    
    // Back Menu
    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(HttpClientTest::toExtensionsMainLayer));
    itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    CCMenu *menuBack = CCMenu::create(itemBack, NULL);
    menuBack->setPosition(CCPointZero);
    addChild(menuBack);
}

HttpClientTest::~HttpClientTest()
{
    CCHttpClient::getInstance()->destroyInstance();
}

void HttpClientTest::onMenuGetTestClicked(cocos2d::CCObject *sender)
{    
    // test 1
    {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl("http://just-make-this-request-failed.com");
        request->setRequestType(CCHttpRequest::kHttpGet);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("GET test1");
        CCHttpClient::getInstance()->send(request);
        request->release();
    }
    
    // test 2
    {
        CCHttpRequest* request = new CCHttpRequest();
        // required fields
        request->setUrl("http://httpbin.org/ip");
        request->setRequestType(CCHttpRequest::kHttpGet);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        // optional fields                            
        request->setTag("GET test2");
    
        CCHttpClient::getInstance()->send(request);
    
        // don't forget to release it, pair to new
        request->release();
    }
    
    // test 3   
    {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl("http://httpbin.org/get");
        request->setRequestType(CCHttpRequest::kHttpGet);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("GET test3");
        CCHttpClient::getInstance()->send(request);
        request->release();
    }
        
    // waiting
    m_labelStatusCode->setString("waiting...");
 
}

void HttpClientTest::onMenuPostTestClicked(cocos2d::CCObject *sender)
{
    // test 1
    {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl("http://httpbin.org/post");
        request->setRequestType(CCHttpRequest::kHttpPost);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        
        // write the post data
        const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
        request->setRequestData(postData, strlen(postData)); 
        
        request->setTag("POST test1");
        CCHttpClient::getInstance()->send(request);
        request->release();
    }
    
    // test 2: set Content-Type
    {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl("http://httpbin.org/post");
        request->setRequestType(CCHttpRequest::kHttpPost);
        std::vector<std::string> headers;
        headers.push_back("Content-Type: application/json; charset=utf-8");
        request->setHeaders(headers);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        
        // write the post data
        const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
        request->setRequestData(postData, strlen(postData)); 
        
        request->setTag("POST test2");
        CCHttpClient::getInstance()->send(request);
        request->release();
    }
    
    // waiting
    m_labelStatusCode->setString("waiting...");
}

void HttpClientTest::onMenuPostBinaryTestClicked(cocos2d::CCObject *sender)
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://httpbin.org/post");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
    
    // write the post data
    char postData[22] = "binary=hello\0\0cocos2d";  // including \0, the strings after \0 should not be cut in response
    request->setRequestData(postData, 22); 
    
    request->setTag("POST Binary test");
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    // waiting
    m_labelStatusCode->setString("waiting...");
}



void HttpClientTest::onMenuPutTestClicked(CCObject *sender)
{
    // test 1
    {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl("http://httpbin.org/put");
        request->setRequestType(CCHttpRequest::kHttpPut);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

        // write the post data
        const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
        request->setRequestData(postData, strlen(postData));

        request->setTag("PUT test1");
        CCHttpClient::getInstance()->send(request);
        request->release();
    }

    // test 2: set Content-Type
    {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl("http://httpbin.org/put");
        request->setRequestType(CCHttpRequest::kHttpPut);
        std::vector<std::string> headers;
        headers.push_back("Content-Type: application/json; charset=utf-8");
        request->setHeaders(headers);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

        // write the post data
        const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
        request->setRequestData(postData, strlen(postData));

        request->setTag("PUT test2");
        CCHttpClient::getInstance()->send(request);
        request->release();
    }

    // waiting
    m_labelStatusCode->setString("waiting...");
}

void HttpClientTest::onMenuDeleteTestClicked(CCObject *sender)
{
    // test 1
    {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl("http://just-make-this-request-failed.com");
        request->setRequestType(CCHttpRequest::kHttpDelete);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("DELETE test1");
        CCHttpClient::getInstance()->send(request);
        request->release();
    }

    // test 2
    {
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl("http://httpbin.org/delete");
        request->setRequestType(CCHttpRequest::kHttpDelete);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("DELETE test2");
        CCHttpClient::getInstance()->send(request);
        request->release();
    }

    // waiting
    m_labelStatusCode->setString("waiting...");
}

void HttpClientTest::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag())) 
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    m_labelStatusCode->setString(statusString);
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed()) 
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
    }
    printf("\n");
}

void HttpClientTest::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void runHttpClientTest()
{
    CCScene *pScene = CCScene::create();
    HttpClientTest *pLayer = new HttpClientTest();
    pScene->addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
    pLayer->release();
}
