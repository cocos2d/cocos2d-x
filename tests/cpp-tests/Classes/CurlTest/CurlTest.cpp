#include "CurlTest.h"
#include "stdio.h"
#include "stdlib.h"
#include "curl/curl.h"

USING_NS_CC;

CurlTests::CurlTests()
{
    ADD_TEST_CASE(CurlTest);
}

CurlTest::CurlTest()
{
    auto label = Label::createWithTTF("Curl Test", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition(VisibleRect::center().x, VisibleRect::top().y-50);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(CurlTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // create a label to display the tip string
    _label = Label::createWithTTF("Touch the screen to connect", "fonts/arial.ttf", 22);
    _label->setPosition(VisibleRect::center());
    addChild(_label, 0);
    
    _label->retain();
}

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 

// the test code is
// http://curl.haxx.se/mail/lib-2009-12/0071.html
void CurlTest::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    CURL *curl;
    CURLcode res;
    char buffer[10];

    struct MemoryStruct chunk;
    
    chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */

    curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://webtest.cocos2d-x.org/curltest");
		//code from http://curl.haxx.se/libcurl/c/getinmemory.html
        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		//If we don't provide a write function for curl, it will recieve error code 23 on windows.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        if (res == 0)
        {
            _label->setString(StringUtils::format("Connect successfully!\n%s", chunk.memory));
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
