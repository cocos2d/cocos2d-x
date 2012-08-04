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
    
    //Download File
    CCLabelTTF *labelDownload = CCLabelTTF::create("Test Download", "Arial", 15);
    CCMenuItemLabel *itemDownload = CCMenuItemLabel::create(labelDownload, this, menu_selector(HttpRequestTest::onLabelDownloadTestClicked));
    itemDownload->setPosition(ccp(winSize.width / 2, winSize.height - 190));
    menuRequest->addChild(itemDownload);
    
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
    string url = GETURL;
    
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    requestor->addGetTask(url, this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
}

void HttpRequestTest::onLabelPostTestClicked(cocos2d::CCObject *sender)
{
    string url = POSTURL;
    string content = "username=hello&password=world";
    
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    //You may name the request
    requestor->setReqId("login");
    requestor->addPostTask(url, content, this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
}

void HttpRequestTest::onLabelPostBinaryTestClicked(cocos2d::CCObject *sender)
{
    string url = POSTURL;
    const char *content = "username=hello&password=worl\0d";
    
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    requestor->setReqId("postbinary");
    requestor->addPostTask(url, content, strlen(content) + 2, this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
}

void HttpRequestTest::onLabelDownloadTestClicked(cocos2d::CCObject *sender)
{
    string url = DOWNLOADURL;
    vector<string> files;
    
    files.push_back(url);
    
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    requestor->setReqId("download");
    requestor->addDownloadTask(files, this, callfuncND_selector(HttpRequestTest::onHttpRequestCompleted));
}

void HttpRequestTest::onHttpRequestCompleted(cocos2d::CCObject *sender, void *data)
{
    HttpResponsePacket *response = (HttpResponsePacket *)data;
    
    //You can get original request type from: response->request->reqType
    
    if (response->request->reqId != "") {
        CCLog("%s completed", response->request->reqId.c_str());
    }
    
    char buffer[128];
    sprintf(buffer, "Response code: %d", response->responseCode);
    getLabelStatusCode()->setString(buffer);
    
    if (!response->succeed) {
        return;
    }
    
    //If the response is binary, use response->responseData.data() and response->responseData.length()
    //To process the response
    CCLog("Response Content: %s", response->responseData.c_str());
    
    if (response->request->reqId == "download") {
        string downloaded = response->request->files[0];
        string saved = downloaded.substr(downloaded.rfind("/") + 1);
        
        CCLog("%s downloaded, and saved as %s in your application's writeable directory", downloaded.c_str(), saved.c_str());
    }
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

