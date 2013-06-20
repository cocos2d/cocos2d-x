#include "HttpClientTest.h"
#include "../ExtensionsTest.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;

HttpClientTest::HttpClientTest() 
: _labelStatusCode(NULL)
{
    Size winSize = Director::sharedDirector()->getWinSize();

    const int MARGIN = 40;
    const int SPACE = 35;
    
    LabelTTF *label = LabelTTF::create("Http Request Test", "Arial", 28);
    label->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN));
    addChild(label, 0);
    
    Menu *menuRequest = Menu::create();
    menuRequest->setPosition(PointZero);
    addChild(menuRequest);
    
    // Get 
    LabelTTF *labelGet = LabelTTF::create("Test Get", "Arial", 22);
    MenuItemLabel *itemGet = MenuItemLabel::create(labelGet, CC_CALLBACK_1(HttpClientTest::onMenuGetTestClicked, this));
    itemGet->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemGet);
    
    // Post
    LabelTTF *labelPost = LabelTTF::create("Test Post", "Arial", 22);
    MenuItemLabel *itemPost = MenuItemLabel::create(labelPost, CC_CALLBACK_1(HttpClientTest::onMenuPostTestClicked, this));
    itemPost->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemPost);
    
    // Post Binary
    LabelTTF *labelPostBinary = LabelTTF::create("Test Post Binary", "Arial", 22);
    MenuItemLabel *itemPostBinary = MenuItemLabel::create(labelPostBinary, CC_CALLBACK_1(HttpClientTest::onMenuPostBinaryTestClicked, this));
    itemPostBinary->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemPostBinary);

    // Put
    LabelTTF *labelPut = LabelTTF::create("Test Put", "Arial", 22);
    MenuItemLabel *itemPut = MenuItemLabel::create(labelPut, CC_CALLBACK_1(HttpClientTest::onMenuPutTestClicked, this));
    itemPut->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemPut);

    // Delete
    LabelTTF *labelDelete = LabelTTF::create("Test Delete", "Arial", 22);
    MenuItemLabel *itemDelete = MenuItemLabel::create(labelDelete, CC_CALLBACK_1(HttpClientTest::onMenuDeleteTestClicked, this));
    itemDelete->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 5 * SPACE));
    menuRequest->addChild(itemDelete);
    
    // Response Code Label
    _labelStatusCode = LabelTTF::create("HTTP Status Code", "Marker Felt", 20);
    _labelStatusCode->setPosition(ccp(winSize.width / 2,  winSize.height - MARGIN - 6 * SPACE));
    addChild(_labelStatusCode);
    
    // Back Menu
    MenuItemFont *itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(HttpClientTest::toExtensionsMainLayer, this));
    itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    Menu *menuBack = Menu::create(itemBack, NULL);
    menuBack->setPosition(PointZero);
    addChild(menuBack);
}

HttpClientTest::~HttpClientTest()
{
    HttpClient::getInstance()->destroyInstance();
}

void HttpClientTest::onMenuGetTestClicked(cocos2d::Object *sender)
{    
    // test 1
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://just-make-this-request-failed.com");
        request->setRequestType(HttpRequest::kHttpGet);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("GET test1");
        HttpClient::getInstance()->send(request);
        request->release();
    }
    
    // test 2
    {
        HttpRequest* request = new HttpRequest();
        // required fields
        request->setUrl("http://httpbin.org/ip");
        request->setRequestType(HttpRequest::kHttpGet);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        // optional fields                            
        request->setTag("GET test2");
    
        HttpClient::getInstance()->send(request);
    
        // don't forget to release it, pair to new
        request->release();
    }
    
    // test 3   
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/get");
        request->setRequestType(HttpRequest::kHttpGet);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("GET test3");
        HttpClient::getInstance()->send(request);
        request->release();
    }
        
    // waiting
    _labelStatusCode->setString("waiting...");
 
}

void HttpClientTest::onMenuPostTestClicked(cocos2d::Object *sender)
{
    // test 1
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/post");
        request->setRequestType(HttpRequest::kHttpPost);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        
        // write the post data
        const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
        request->setRequestData(postData, strlen(postData)); 
        
        request->setTag("POST test1");
        HttpClient::getInstance()->send(request);
        request->release();
    }
    
    // test 2: set Content-Type
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/post");
        request->setRequestType(HttpRequest::kHttpPost);
        std::vector<std::string> headers;
        headers.push_back("Content-Type: application/json; charset=utf-8");
        request->setHeaders(headers);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        
        // write the post data
        const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
        request->setRequestData(postData, strlen(postData)); 
        
        request->setTag("POST test2");
        HttpClient::getInstance()->send(request);
        request->release();
    }
    
    // waiting
    _labelStatusCode->setString("waiting...");
}

void HttpClientTest::onMenuPostBinaryTestClicked(cocos2d::Object *sender)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl("http://httpbin.org/post");
    request->setRequestType(HttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
    
    // write the post data
    char postData[22] = "binary=hello\0\0cocos2d";  // including \0, the strings after \0 should not be cut in response
    request->setRequestData(postData, 22); 
    
    request->setTag("POST Binary test");
    HttpClient::getInstance()->send(request);
    request->release();
    
    // waiting
    _labelStatusCode->setString("waiting...");
}



void HttpClientTest::onMenuPutTestClicked(Object *sender)
{
    // test 1
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/put");
        request->setRequestType(HttpRequest::kHttpPut);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

        // write the post data
        const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
        request->setRequestData(postData, strlen(postData));

        request->setTag("PUT test1");
        HttpClient::getInstance()->send(request);
        request->release();
    }

    // test 2: set Content-Type
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/put");
        request->setRequestType(HttpRequest::kHttpPut);
        std::vector<std::string> headers;
        headers.push_back("Content-Type: application/json; charset=utf-8");
        request->setHeaders(headers);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

        // write the post data
        const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
        request->setRequestData(postData, strlen(postData));

        request->setTag("PUT test2");
        HttpClient::getInstance()->send(request);
        request->release();
    }

    // waiting
    _labelStatusCode->setString("waiting...");
}

void HttpClientTest::onMenuDeleteTestClicked(Object *sender)
{
    // test 1
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://just-make-this-request-failed.com");
        request->setRequestType(HttpRequest::kHttpDelete);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("DELETE test1");
        HttpClient::getInstance()->send(request);
        request->release();
    }

    // test 2
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/delete");
        request->setRequestType(HttpRequest::kHttpDelete);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("DELETE test2");
        HttpClient::getInstance()->send(request);
        request->release();
    }

    // waiting
    _labelStatusCode->setString("waiting...");
}

void HttpClientTest::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
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
    _labelStatusCode->setString(statusString);
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

void HttpClientTest::toExtensionsMainLayer(cocos2d::Object *sender)
{
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void runHttpClientTest()
{
    Scene *pScene = Scene::create();
    HttpClientTest *pLayer = new HttpClientTest();
    pScene->addChild(pLayer);
    
    Director::sharedDirector()->replaceScene(pScene);
    pLayer->release();
}
