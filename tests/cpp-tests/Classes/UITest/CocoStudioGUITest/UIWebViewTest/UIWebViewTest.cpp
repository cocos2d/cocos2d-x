/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "UIWebViewTest.h"

WebViewTest::WebViewTest()
{
    
}

WebViewTest::~WebViewTest()
{

}

bool WebViewTest::init()
{
    if (UIScene::init()) {
        Size winSize = Director::getInstance()->getVisibleSize();

        
        _webView = cocos2d::experimental::ui::WebView::create();
        _webView->setPosition(winSize/2);
        _webView->setContentSize(winSize * 0.5);
        _webView->loadURL("http://www.baidu.com");
        _webView->setScalesPageToFit(true);
        
        _webView->setOnShouldStartLoading(CC_CALLBACK_2(WebViewTest::onWebViewShouldStartLoading, this));
        _webView->setOnDidFinishLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFinishLoading, this));
        _webView->setOnDidFailLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFailLoading, this));
        
        this->addChild(_webView);
        
        TextField *urlTextField = TextField::create("Input a URL here", "Arial", 20);
        urlTextField->setPlaceHolderColor(Color3B::RED);
        urlTextField->setPosition(Vec2(winSize/2) + Vec2(-80, _webView->getContentSize().height/2 +
                                                     urlTextField->getContentSize().height/2 + 10));
        this->addChild(urlTextField);
        
        Text *httpLabel = Text::create("http:// ", "Arial", 20);
        httpLabel->setTextColor(Color4B::GREEN);
        httpLabel->setAnchorPoint(Vec2(1.0,0.5));
        httpLabel->setPosition(urlTextField->getPosition() - Vec2(urlTextField->getContentSize().width/2,0));
        this->addChild(httpLabel);
        
        
        Button *resetBtn = Button::create("cocosui/animationbuttonnormal.png",
                                       "cocosui/animationbuttonpressed.png");
        resetBtn->setTitleText("Visit URL");
        resetBtn->setPosition(Vec2(winSize/2) + Vec2(50, _webView->getContentSize().height/2 +
                                            resetBtn->getContentSize().height/2 + 10));
        resetBtn->addClickEventListener([=](Ref*){
            if (urlTextField->getString().size() != 0)
            {
                _webView->loadURL(std::string("http://") + urlTextField->getString());
            }
        });
        this->addChild(resetBtn);
        
        
        Button *reloadBtn = Button::create("cocosui/animationbuttonnormal.png",
                                          "cocosui/animationbuttonpressed.png");
        reloadBtn->setTitleText("Reload");
        reloadBtn->setPosition(Vec2(winSize/2) + Vec2( _webView->getContentSize().width/2 +
                                                      reloadBtn->getContentSize().width/2 + 10,50 ));
        reloadBtn->addClickEventListener([=](Ref*){
            _webView->reload();
        });
        this->addChild(reloadBtn);
        
        Button *forwardBtn = Button::create("cocosui/animationbuttonnormal.png",
                                           "cocosui/animationbuttonpressed.png");
        forwardBtn->setTitleText("Forward");
        forwardBtn->setPosition(Vec2(winSize/2) + Vec2( _webView->getContentSize().width/2 +
                                                      forwardBtn->getContentSize().width/2 + 10,0 ));
        forwardBtn->addClickEventListener([=](Ref*){
            _webView->goForward();
        });
        this->addChild(forwardBtn);
        
        
        
        Button *backBtn = Button::create("cocosui/animationbuttonnormal.png",
                                           "cocosui/animationbuttonpressed.png");
        backBtn->setTitleText("Back");
        backBtn->setPosition(Vec2(winSize/2) + Vec2( _webView->getContentSize().width/2 +
                                                      backBtn->getContentSize().width/2 + 10,-50 ));
        backBtn->addClickEventListener([=](Ref*){
            _webView->goBack();
        });
        this->addChild(backBtn);
        
        
        Button *loadFileBtn = Button::create("cocosui/animationbuttonnormal.png",
                                           "cocosui/animationbuttonpressed.png");
        loadFileBtn->setTitleText("Load FILE");
        loadFileBtn->setPosition(Vec2(winSize/2) - Vec2( _webView->getContentSize().width/2 +
                                                      loadFileBtn->getContentSize().width/2 + 10,50 ));
        loadFileBtn->addClickEventListener([=](Ref*){
            _webView->loadFile("Test.html");
        });
        this->addChild(loadFileBtn);
        
        Button *loadHTMLBtn = Button::create("cocosui/animationbuttonnormal.png",
                                            "cocosui/animationbuttonpressed.png");
        loadHTMLBtn->setTitleText("Load Data");
        loadHTMLBtn->setPosition(Vec2(winSize/2) - Vec2( _webView->getContentSize().width/2 +
                                                       loadHTMLBtn->getContentSize().width/2 + 10,0 ));
        loadHTMLBtn->addClickEventListener([=](Ref*){
            _webView->loadHTMLString("<body style=\"font-size:50px;\">Hello World <img src=\"Icon.png\"/> </body>","Images/");
        });
        this->addChild(loadHTMLBtn);
        
        
        
        
        Button *evalJsBtn = Button::create("cocosui/animationbuttonnormal.png",
                                         "cocosui/animationbuttonpressed.png");
        evalJsBtn->setTitleText("Evaluate JS");
        evalJsBtn->setPosition(Vec2(winSize/2) - Vec2( _webView->getContentSize().width/2 +
                                                    evalJsBtn->getContentSize().width/2 + 10,-50 ));
        evalJsBtn->addClickEventListener([=](Ref*){
            _webView->evaluateJS("alert(\"hello\")");
        });
        this->addChild(evalJsBtn);
        
        return true;
    }
    return false;
}

bool WebViewTest::onWebViewShouldStartLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewShouldStartLoading, url is %s", url.c_str());
    
    return true;
}

void WebViewTest::onWebViewDidFinishLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewDidFinishLoading, url is %s", url.c_str());

}

void WebViewTest::onWebViewDidFailLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewDidFailLoading, url is %s", url.c_str());

}

