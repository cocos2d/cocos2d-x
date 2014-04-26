#include "CurlTest.h"
#include "stdio.h"
#include "stdlib.h"
#include "curl/curl.h"

CurlTest::CurlTest()
{
    auto label = Label::createWithTTF("Curl Test", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition( Vector2(VisibleRect::center().x, VisibleRect::top().y-50) );

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(CurlTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // create a label to display the tip string
    _label = Label::createWithTTF("Touch the screen to connect", "fonts/arial.ttf", 22);
    _label->setPosition(VisibleRect::center());
    addChild(_label, 0);
    
    _label->retain();
}


// the test code is
// http://curl.haxx.se/mail/lib-2009-12/0071.html
void CurlTest::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    CURL *curl;
    CURLcode res;
    char buffer[10];

    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, "google.com");
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        if (res == 0)
        {
            _label->setString("0 response");
        }
        else
        {
            sprintf(buffer,"code: %i",res);
            _label->setString(buffer);
        }
    } 
    else 
    {
        _label->setString("no curl");
    } 
}

CurlTest::~CurlTest()
{
    _label->release();
}

void CurlTestScene::runThisTest()
{
    auto layer = new CurlTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}
