/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "TestFacebookShare.h"
#include "PluginManager.h"
#include "HelloWorldScene.h"
#include "Configs.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
    TAG_FBS_LINK = 0,
    TAG_FBS_OPEN_GRAPH,
    TAG_FBS_PHOTOT,
    TAG_FBS_LINK_MESSAGE,
    TAG_FBS_OPEN_GRAPH_MESSAGE,
    TAG_FBS_PHOTO_MESSAGE,
    TAG_FBS_APP_REQUEST
};

enum {
    TAG_FBSS_SIMPLE_LINK = 0,
    TAG_FBSS_TEXT_LINK,
    TAG_FBSS_PICTURE_LINK,
    TAG_FBSS_MEDIA_LINK,
    TAG_FBSS_INVITES_REQUEST,
    TAG_FBSS_TIE,
    TAG_FBSS_SLOF,
    TAG_FBSS_SRE,
    TAG_FBSS_TBG
};

struct FBShareMenuItem {
    std::string name;
    int tag;
};

static FBShareMenuItem s_FBShareMenuItem[] =
{
    {"Share link",  TAG_FBS_LINK},
    {"Share open graph", TAG_FBS_OPEN_GRAPH},
    {"Share photo", TAG_FBS_PHOTOT},
    {"Link message", TAG_FBS_LINK_MESSAGE},
    {"Open graph message", TAG_FBS_OPEN_GRAPH_MESSAGE},
    {"Photo message", TAG_FBS_PHOTO_MESSAGE},
    {"App request", TAG_FBS_APP_REQUEST}
};

static FBShareMenuItem s_FBS_LinkMenuItem[] =
{
    {"share a simple link", TAG_FBSS_SIMPLE_LINK},
    {"share a Text link", TAG_FBSS_TEXT_LINK},
    {"share a Picture link", TAG_FBSS_PICTURE_LINK},
    {"share a media link", TAG_FBSS_MEDIA_LINK}
};

static FBShareMenuItem s_FBA_RequestMenuItem[] =
{
    {"Invites request", TAG_FBSS_INVITES_REQUEST},
    {"Target invite request", TAG_FBSS_TIE},
    {"specific lists of friends",TAG_FBSS_SLOF},
    {"Sending requests explicitly", TAG_FBSS_SRE},
    {"Turn-based games", TAG_FBSS_TBG},
};

Scene* TestFacebookShare::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestFacebookShare *layer = TestFacebookShare::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestFacebookShare::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
        return false;
    
    tipsLabel = nullptr;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posBR = Point(origin.x + visibleSize.width, origin.y);
    
    
    //2.Add Title
    auto title = Label::createWithSystemFont("Test Facebook share", "Arial", 32);
    title->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 64);
    addChild(title);
    
    std::string sdkVersion = "SDK Version is: " + FacebookAgent::getInstance()->getSDKVersion();
    auto subTitle = Label::createWithSystemFont(sdkVersion.c_str(), "Arial", 18);
    subTitle->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 88);
    addChild(subTitle);
    

    /////////////////////////////
    // 3. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *backItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestFacebookShare::menuBackCallback, this));
    Size backSize = backItem->getContentSize();
    backItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    // create menu, it's an autorelease object
    Menu* menu = Menu::create(backItem, NULL);
    menu->setPosition( Point::ZERO );
    addChild(menu, 0, 1);

    float yPos = 0;
    for (int i = 0; i < sizeof(s_FBShareMenuItem)/sizeof(s_FBShareMenuItem[0]); i++) {
        Label* label = Label::createWithSystemFont(s_FBShareMenuItem[i].name.c_str(), "Arial", 24);
        MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestFacebookShare::eventMenuCallback, this));
        menu->addChild(pMenuItem, 0, s_FBShareMenuItem[i].tag);
        yPos = visibleSize.height - 35*i - 100;
        pMenuItem->setPosition( Point(origin.x + 150, yPos));
    }
    
//    auto logo = Sprite::create("cocos2dx.png");
//    logo->setPosition(visibleSize.width * 2 / 3, visibleSize.height / 2);
//    addChild(logo);

    //4. create result label
    tipsLabel = Label::createWithSystemFont("This share function is not available on web version of Facebook plugin", "Arial", 22);
    tipsLabel->setDimensions(350, 120);
    tipsLabel->setPosition(origin.x + visibleSize.width - tipsLabel->getWidth() / 2 + 20 , origin.y + visibleSize.height - 100);
    tipsLabel->setVisible(false);
    addChild(tipsLabel, 0, 100);
    
    //5. create second menu
    Menu* secondMenu = Menu::create();
    secondMenu->setPosition(Vec2(340, 0));
    addChild(secondMenu, 0, 2);

    return true;
}

void TestFacebookShare::onExit()
{
    Layer::onExit();
}

void TestFacebookShare::eventMenuCallback(Ref* sender)
{
    MenuItemLabel* menuItem = (MenuItemLabel*)sender;

    switch (menuItem->getTag())
    {
    case TAG_FBS_LINK:
        {
            showSecondMenu(TAG_FBS_LINK);
        }
        break;
    case TAG_FBS_OPEN_GRAPH:
        {
            FacebookAgent::FBInfo params;
            params.insert(std::make_pair("dialog", "share_open_graph"));
            params.insert(std::make_pair("action_type", "cocostestmyfc:share"));
            params.insert(std::make_pair("preview_property_name", "cocos_document"));
            params.insert(std::make_pair("title", "Cocos2d-x Game Engine"));
            params.insert(std::make_pair("image", "http://files.cocos2d-x.org/images/orgsite/logo.png"));
            params.insert(std::make_pair("url", "http://cocos2d-x.org/docs/catalog/en"));
            params.insert(std::make_pair("description", "cocos document"));
            
            if (FacebookAgent::getInstance()->canPresentDialogWithParams(params))
            {
                FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            else
            {
                CCLOG("Can't open dialog for share_open_graph");
            }
        }
        break;
    case TAG_FBS_PHOTOT:
        {
            std::string fileName = "facebookshare.jpg";
            std::string imgPath = sceenshot(fileName);
            
            auto delay = DelayTime::create(2.0);
            auto share = CallFunc::create([=](){
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("dialog", "share_photo"));
                params.insert(std::make_pair("photo", imgPath));
                
                if (FacebookAgent::getInstance()->canPresentDialogWithParams(params))
                {
                    FacebookAgent::getInstance()->dialog(params, [=](int ret, std::string& msg){
                        CCLOG("%s", msg.c_str());
                    });
                }
                else
                {
                    CCLOG("Can't open dialog for share_photo");
                }
            });
            
            auto seq = Sequence::create(delay, share, nullptr);
            runAction(seq);
        }
        break;
    case TAG_FBS_LINK_MESSAGE:
        {
            FacebookAgent::FBInfo params;
            params.insert(std::make_pair("dialog", "message_link"));
            params.insert(std::make_pair("description", "Cocos2d-x is a great game engine"));
            params.insert(std::make_pair("title", "Cocos2d-x"));
            params.insert(std::make_pair("link", "http://www.cocos2d-x.org"));
            params.insert(std::make_pair("imageUrl", "http://files.cocos2d-x.org/images/orgsite/logo.png"));
            
            if (FacebookAgent::getInstance()->canPresentDialogWithParams(params))
            {
                FacebookAgent::getInstance()->dialog(params, [=](int ret, std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            else
            {
               CCLOG("Can't open dialog for message_link");
            }
        }
        break;
    case TAG_FBS_OPEN_GRAPH_MESSAGE:
        {
            FacebookAgent::FBInfo params;
            params.insert(std::make_pair("dialog", "message_open_graph"));
            params.insert(std::make_pair("action_type", "cocostestmyfc:share"));
            params.insert(std::make_pair("preview_property_name", "cocos_document"));
            params.insert(std::make_pair("title", "Cocos2d-x Game Engine"));
            params.insert(std::make_pair("image", "http://files.cocos2d-x.org/images/orgsite/logo.png"));
            params.insert(std::make_pair("url", "http://cocos2d-x.org/docs/catalog/en"));
            params.insert(std::make_pair("description", "cocos document"));
            if (FacebookAgent::getInstance()->canPresentDialogWithParams(params))
            {
                FacebookAgent::getInstance()->dialog(params, [=](int ret, std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            else
            {
                CCLOG("Can't open dialog for message_open_graph");
            }

        }
        break;
    case TAG_FBS_PHOTO_MESSAGE:
        {
            std::string fileName = "facebookmessage.jpg";
            std::string imgPath = sceenshot(fileName);
            
            auto delay = DelayTime::create(2.0);
            auto share = CallFunc::create([=](){
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("dialog", "message_photo"));
                params.insert(std::make_pair("photo", imgPath));
                
                if (FacebookAgent::getInstance()->canPresentDialogWithParams(params))
                {
                    FacebookAgent::getInstance()->dialog(params, [=](int ret, std::string& msg){
                        CCLOG("%s", msg.c_str());
                    });
                }
                else
                {
                    CCLOG("Can't open dialog for message_photo");
                }
            });
            
            auto seq = Sequence::create(delay, share, nullptr);
            runAction(seq);
        }
        break;
    case TAG_FBS_APP_REQUEST:
        {
            showSecondMenu(TAG_FBS_APP_REQUEST);
        }
        break;
    default:
        break;
    }
}

void TestFacebookShare::menuBackCallback(Ref* sender)
{
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}

std::string TestFacebookShare::sceenshot(std::string& filename)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto tex = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
    tex->setPosition((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2);
    tex->begin();
    Director::getInstance()->getRunningScene()->visit();
    tex->end();
    
    std::string imgPath = FileUtils::getInstance()->getWritablePath();
    if (imgPath.length() == 0) {
        return "";
    }
    
    bool ret = tex->saveToFile(filename, Image::Format::JPG);
    if (ret) {
        imgPath += filename;
        CCLOG("save image to %s", imgPath.c_str());
        return imgPath;
    }
    return "";
}

void TestFacebookShare::showSecondMenu(int menuTag)
{
    Menu* secondMenu = static_cast<Menu*>(getChildByTag(2));
    if (nullptr != secondMenu)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        Point posBR = Point(origin.x + visibleSize.width, origin.y);
        
        secondMenu->removeAllChildren();
        int top = 70;
        
        switch (menuTag) {
            case TAG_FBS_LINK:
                {
                    for (int i = 0; i < sizeof(s_FBS_LinkMenuItem)/sizeof(s_FBS_LinkMenuItem[0]); i++) {
                        Label* label = Label::createWithSystemFont(s_FBS_LinkMenuItem[i].name.c_str(), "Arial", 24);
                        MenuItemLabel* menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestFacebookShare::secondMenuCallback, this));
                        menuItem->setPosition(Vec2(visibleSize.width / 3, visibleSize.height - top));
                        secondMenu->addChild(menuItem, 0, s_FBS_LinkMenuItem[i].tag);
                        top += 50;
                    }
                }
                break;
            case TAG_FBS_APP_REQUEST:
                {
                    for (int i = 0; i < sizeof(s_FBA_RequestMenuItem)/sizeof(s_FBA_RequestMenuItem[0]); i++) {
                        Label* label = Label::createWithSystemFont(s_FBA_RequestMenuItem[i].name.c_str(), "Arial", 24);
                        MenuItemLabel* menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestFacebookShare::secondMenuCallback, this));
                        menuItem->setPosition(Vec2(visibleSize.width / 3, visibleSize.height - top));
                        secondMenu->addChild(menuItem, 0, s_FBA_RequestMenuItem[i].tag);
                        top += 50;
                    }
                }
                break;
                
            default:
                break;
        }
    }
}

void TestFacebookShare::secondMenuCallback(Ref* sender)
{
    MenuItemLabel* menuItem = static_cast<MenuItemLabel*>(sender);
    CCASSERT(nullptr != menuItem, "mentitem is nullptr");

    switch (menuItem->getTag())
    {
        case TAG_FBSS_SIMPLE_LINK:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("dialog", "share_link"));
                params.insert(std::make_pair("link", "http://www.cocos2d-x.org"));
                
                if (FacebookAgent::getInstance()->canPresentDialogWithParams(params))
                {
                    FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg){
                        CCLOG("%s", msg.c_str());
                    });
                }
                else
                {
                    params.insert(std::make_pair("dialog", "feed_dialog"));
                    FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg){
                        CCLOG("%s", msg.c_str());
                    });
                }
            }
            break;
        case TAG_FBSS_TEXT_LINK:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("dialog", "share_link"));
                params.insert(std::make_pair("name", "Cocos2d-x web site"));
                params.insert(std::make_pair("caption", "Cocos2d-x caption"));
                params.insert(std::make_pair("description", "Cocos2d-x description"));
                params.insert(std::make_pair("link", "http://www.cocos2d-x.org"));
                
                if (FacebookAgent::getInstance()->canPresentDialogWithParams(params))
                {
                    FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg){
                        CCLOG("%s", msg.c_str());
                    });
                }
                else
                {
                    params.insert(std::make_pair("dialog", "feed_dialog"));
                    FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg){
                        CCLOG("%s", msg.c_str());
                    });
                }
            }
            break;
        case TAG_FBSS_PICTURE_LINK:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("dialog", "share_link"));
                params.insert(std::make_pair("name", "Cocos2d-x web site"));
                params.insert(std::make_pair("caption", "Cocos2d-x caption"));
                params.insert(std::make_pair("description", "Cocos2d-x description"));
                params.insert(std::make_pair("to", "100006738453912")); // android only web view support
                params.insert(std::make_pair("picture", "http://files.cocos2d-x.org/images/orgsite/logo.png"));
                params.insert(std::make_pair("link", "http://www.cocos2d-x.org"));
                
                if (FacebookAgent::getInstance()->canPresentDialogWithParams(params))
                {
                    FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg){
                        CCLOG("%s", msg.c_str());
                    });
                }
                else
                {
                    params.insert(std::make_pair("dialog", "feed_dialog"));
                    FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg){
                        CCLOG("%s", msg.c_str());
                    });
                }
            }
            break;
        case TAG_FBSS_MEDIA_LINK:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("dialog", "share_link"));
                params.insert(std::make_pair("name", "Cocos2d-x web site"));
                params.insert(std::make_pair("caption", "Cocos2d-x caption"));
                params.insert(std::make_pair("description", "Cocos2d-x description"));
                params.insert(std::make_pair("media_source", "http://221.203.1.212/youku/6775B002C8F48839F6AFA63BDA/0300200100540438A173C515AA2BED245C4903-F675-B311-EF1A-4544B5C04370.mp4"));
                params.insert(std::make_pair("link", "http://www.cocos2d-x.org"));
                
                // only support in web dialog
                FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            break;
        case TAG_FBSS_INVITES_REQUEST:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("message", "Cocos2d-x is a great game engine"));
                params.insert(std::make_pair("title", "Cocos2d-x title"));
                
                FacebookAgent::getInstance()->appRequest(params, [=](int ret, std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            break;
        case TAG_FBSS_TIE:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("message", "Cocos2d-x is a great game engine"));
                params.insert(std::make_pair("title", "Cocos2d-x title"));
                params.insert(std::make_pair("to", "100006738453912, 10204182777160522"));
                // android only web view support to
                FacebookAgent::getInstance()->appRequest(params, [=](int ret, std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            break;
        case TAG_FBSS_SLOF:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("message", "Cocos2d-x is a great game engine"));
                params.insert(std::make_pair("title", "Cocos2d-x title"));
                params.insert(std::make_pair("filters", "[{\"name\":\"company\", \"user_ids\":[\"100006738453912\",\"10204182777160522\"]}]"));
                // android not support filters
                FacebookAgent::getInstance()->appRequest(params, [=](int ret, std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            break;
        case TAG_FBSS_SRE:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("message", "Cocos2d-x is a great game engine"));
                params.insert(std::make_pair("to", "100006738453912"));
                params.insert(std::make_pair("action_type", "send"));
                params.insert(std::make_pair("object_id", "191181717736427"));
                // android not support action_type
                FacebookAgent::getInstance()->appRequest(params, [=](int ret, std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            break;
        case TAG_FBSS_TBG:
            {
                FacebookAgent::FBInfo params;
                params.insert(std::make_pair("message", "Cocos2d-x is a great game engine"));
                params.insert(std::make_pair("title", "Cocos2d-x title"));
                params.insert(std::make_pair("to", "100006738453912"));
                params.insert(std::make_pair("action_type", "turn"));
                // android not support action_type
                FacebookAgent::getInstance()->appRequest(params, [=](int ret, std::string& msg){
                    CCLOG("%s", msg.c_str());
                });
            }
            break;
            
        default:
            break;
    }
}
