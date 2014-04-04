#include "HttpClientTest.h"
#include "../ExtensionsTest.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::network;

HttpClientTest::HttpClientTest() 
: _labelStatusCode(NULL)
{
    auto winSize = Director::getInstance()->getWinSize();

    const int MARGIN = 40;
    const int SPACE = 35;
    
    auto label = Label::create("Http Request Test", "fonts/arial.ttf", 28);
    label->setPosition(Point(winSize.width / 2, winSize.height - MARGIN));
    addChild(label, 0);
    
    auto menuRequest = Menu::create();
    menuRequest->setPosition(Point::ZERO);
    addChild(menuRequest);
    
    // Get 
    auto labelGet = Label::create("Test Get", "fonts/arial.ttf", 22);
    auto itemGet = MenuItemLabel::create(labelGet, CC_CALLBACK_1(HttpClientTest::onMenuGetTestClicked, this));
    itemGet->setPosition(Point(winSize.width / 2, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemGet);
    
    // Post
    auto labelPost = Label::create("Test Post", "fonts/arial.ttf", 22);
    auto itemPost = MenuItemLabel::create(labelPost, CC_CALLBACK_1(HttpClientTest::onMenuPostTestClicked, this));
    itemPost->setPosition(Point(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemPost);
    
    // Post Binary
    auto labelPostBinary = Label::create("Test Post Binary", "fonts/arial.ttf", 22);
    auto itemPostBinary = MenuItemLabel::create(labelPostBinary, CC_CALLBACK_1(HttpClientTest::onMenuPostBinaryTestClicked, this));
    itemPostBinary->setPosition(Point(winSize.width / 2, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemPostBinary);

    // Put
    auto labelPut = Label::create("Test Put", "fonts/arial.ttf", 22);
    auto itemPut = MenuItemLabel::create(labelPut, CC_CALLBACK_1(HttpClientTest::onMenuPutTestClicked, this));
    itemPut->setPosition(Point(winSize.width / 2, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemPut);

    // Delete
    auto labelDelete = Label::create("Test Delete", "fonts/arial.ttf", 22);
    auto itemDelete = MenuItemLabel::create(labelDelete, CC_CALLBACK_1(HttpClientTest::onMenuDeleteTestClicked, this));
    itemDelete->setPosition(Point(winSize.width / 2, winSize.height - MARGIN - 5 * SPACE));
    menuRequest->addChild(itemDelete);
    
    // Response Code Label
    _labelStatusCode = Label::create("HTTP Status Code", "fonts/arial.ttf", 22);
    _labelStatusCode->setPosition(Point(winSize.width / 2,  winSize.height - MARGIN - 6 * SPACE));
    addChild(_labelStatusCode);
    
    // Back Menu
    auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(HttpClientTest::toExtensionsMainLayer, this));
    itemBack->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    auto menuBack = Menu::create(itemBack, NULL);
    menuBack->setPosition(Point::ZERO);
    addChild(menuBack);
}

HttpClientTest::~HttpClientTest()
{
    HttpClient::destroyInstance();
}

void HttpClientTest::onMenuGetTestClicked(cocos2d::Ref *sender)
{    
    // test 1
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://just-make-this-request-failed.com");
        request->setRequestType(HttpRequest::Type::GET);
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
        request->setRequestType(HttpRequest::Type::GET);
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
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("GET test3");
        HttpClient::getInstance()->send(request);
        request->release();
    }
        
    // waiting
    _labelStatusCode->setString("waiting...");
 
}

void HttpClientTest::onMenuPostTestClicked(cocos2d::Ref *sender)
{
    // test 1
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/post");
        request->setRequestType(HttpRequest::Type::POST);
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
        request->setRequestType(HttpRequest::Type::POST);
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

void HttpClientTest::onMenuPostBinaryTestClicked(cocos2d::Ref *sender)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl("http://httpbin.org/post");
    request->setRequestType(HttpRequest::Type::POST);
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



void HttpClientTest::onMenuPutTestClicked(Ref *sender)
{
    // test 1
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/put");
        request->setRequestType(HttpRequest::Type::PUT);
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
        request->setRequestType(HttpRequest::Type::PUT);
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

void HttpClientTest::onMenuDeleteTestClicked(Ref *sender)
{
    // test 1
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://just-make-this-request-failed.com");
        request->setRequestType(HttpRequest::Type::DELETE);
        request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));
        request->setTag("DELETE test1");
        HttpClient::getInstance()->send(request);
        request->release();
    }

    // test 2
    {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://httpbin.org/delete");
        request->setRequestType(HttpRequest::Type::DELETE);
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
        log("%s completed", response->getHttpRequest()->getTag());
    }
    
    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
    _labelStatusCode->setString(statusString);
    log("response code: %ld", statusCode);
    
    if (!response->isSucceed()) 
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
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

void HttpClientTest::toExtensionsMainLayer(cocos2d::Ref *sender)
{
    auto scene = new ExtensionsTestScene();
    scene->runThisTest();
    scene->release();
}

void runHttpClientTest()
{
    auto scene = Scene::create();
    HttpClientTest *layer = new HttpClientTest();
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
    layer->release();
}
