/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "WebSocketDelayTest.h"
#include "../ExtensionsTest.h"
#include "testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SEND_TEXT_TIMES 100

WebSocketDelayTest::WebSocketDelayTest()
: _wsiSendText(nullptr)
, _sendTextStatus(nullptr)
, _progressStatus(nullptr)
, _sendTextTimes(0)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    const int MARGIN = 40;
    const int SPACE = 35;
    
    auto menuRequest = Menu::create();
    menuRequest->setPosition(Vec2::ZERO);
    addChild(menuRequest);
    
    // Send Text
    char cmdLabel[60] = { 0 };
    snprintf(cmdLabel, 60, "Send %d Text", SEND_TEXT_TIMES);
    auto labelSendText = Label::createWithTTF(cmdLabel, "fonts/arial.ttf", 20);
    auto itemSendText = MenuItemLabel::create(labelSendText, CC_CALLBACK_1(WebSocketDelayTest::onMenuSendTextClicked, this));
    itemSendText->setPosition(Vec2(winSize.width / 2, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSendText);
    
    // Send Text Status Label
    _sendTextStatus = Label::createWithTTF("Waiting connection...", "fonts/arial.ttf", 16, Size(160, 100), TextHAlignment::CENTER, TextVAlignment::TOP);
    _sendTextStatus->setAnchorPoint(Vec2(0, 0));
    _sendTextStatus->setPosition(Vec2(VisibleRect::left().x, VisibleRect::rightBottom().y + 25));
    this->addChild(_sendTextStatus);
   

    // Error Label
    _progressStatus = Label::createWithTTF(".", "fonts/arial.ttf", 16, Size(160, 100), TextHAlignment::CENTER, TextVAlignment::TOP);
    _progressStatus->setAnchorPoint(Vec2(0, 0));
    _progressStatus->setPosition(Vec2(VisibleRect::left().x + 320, VisibleRect::rightBottom().y + 25));
    this->addChild(_progressStatus);
    
    auto startTestLabel = Label::createWithTTF("DO Connect!", "fonts/arial.ttf", 16);
    auto startTestItem = MenuItemLabel::create(startTestLabel, CC_CALLBACK_1(WebSocketDelayTest::startTestCallback, this));
    startTestItem->setPosition(Vec2(VisibleRect::center().x - 150, VisibleRect::bottom().y + 150));
    _startTestMenu = Menu::create(startTestItem, nullptr);
    _startTestMenu->setPosition(Vec2::ZERO);
    this->addChild(_startTestMenu, 1);
}

WebSocketDelayTest::~WebSocketDelayTest()
{

}

void WebSocketDelayTest::onExit()
{
    if (_wsiSendText)
    {
        _wsiSendText->closeAsync();
    }

    Node::onExit();
}

void WebSocketDelayTest::startTestCallback(Ref* sender)
{
    removeChild(_startTestMenu);
    _startTestMenu = nullptr;

    _wsiSendText = new network::WebSocket();
    
    std::vector<std::string> protocols;
    protocols.push_back("myprotocol_1");
    protocols.push_back("myprotocol_2");
    if (!_wsiSendText->init(*this, "wss://echo.websocket.org", &protocols, "cacert.pem"))
    {
        CC_SAFE_DELETE(_wsiSendText);
    }
    else
    {
        retain(); // Retain self to avoid WebSocketDelayTest instance be deleted immediately, it will be released in WebSocketDelayTest::onClose.

    }

}

void WebSocketDelayTest::doSendText()
{
    _sendTextTimes += 1;
    if (_sendTextTimes > SEND_TEXT_TIMES) 
    {
        _sendTextStatus->setString("Test Done!");
        return;
    }

    char statueBuffer[80] = { 0 };
    snprintf(statueBuffer, 80, "Sending #%d/%d text", _sendTextTimes, SEND_TEXT_TIMES);
    _sendTextStatus->setString(statueBuffer);
    _sendTimeMircoSec = getNowMircroSeconds();
    _wsiSendText->send("Hello WebSocket, I'm a text message.");
}

void WebSocketDelayTest::doReceiveText()
{
    _receiveTimeMircoSec = getNowMircroSeconds();
    if(_sendTimeMircoSec > 0)
        _totalDelayMircoSec += (_receiveTimeMircoSec - _sendTimeMircoSec);
    doSendText(); //send next 
}

// Delegate methods
void WebSocketDelayTest::onOpen(network::WebSocket* ws)
{
    char status[256] = {0};
    sprintf(status, "Opened, url: %s, protocol: %s", ws->getUrl().c_str(), ws->getProtocol().c_str());

    log("Websocket (%p) was opened, url: %s, protocol: %s", ws, ws->getUrl().c_str(), ws->getProtocol().c_str());
    if (ws == _wsiSendText)
    {
        _sendTextStatus->setString(status);

    }
}

void WebSocketDelayTest::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data)
{
    if (!data.isBinary)
    {
        _receiveTextTimes++;
        char times[100] = {0};
        sprintf(times, "%d", _receiveTextTimes);
        std::string textStr = std::string("response text msg: ")+data.bytes+", "+times;
        log("%s", textStr.c_str());
        doReceiveText();
        memset(times, 0, 100);
        snprintf(times, 100, "total delay %f seconds", (float)(_totalDelayMircoSec/ 1000000.0));
        _progressStatus->setString(times);
    }
}

void WebSocketDelayTest::onClose(network::WebSocket* ws)
{
    log("onClose: websocket instance (%p) closed.", ws);
    if (ws == _wsiSendText)
    {
        _wsiSendText = nullptr;
        _sendTextStatus->setString("Send Text WS was closed");
    }
    // Delete websocket instance.
    CC_SAFE_DELETE(ws);
    log("WebSocketDelayTest ref: %u", _referenceCount);
    release();
}

void WebSocketDelayTest::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error)
{
    log("Error was fired, error code: %d", static_cast<int>(error));
    char buf[100] = {0};
    sprintf(buf, "An error was fired, code: %d", static_cast<int>(error));

    if (ws == _wsiSendText)
    {
        _sendTextStatus->setString(buf);
    }

    _sendTimeMircoSec = 0;
}

// Menu Callbacks
void WebSocketDelayTest::onMenuSendTextClicked(cocos2d::Ref *sender)
{
    if (! _wsiSendText)
    {
        return;
    }

    if (_wsiSendText->getReadyState() == network::WebSocket::State::OPEN)
    {
        
        _sendTextTimes = 0;
        _receiveTextTimes = 0;
        doSendText();
    }
    else
    {
        std::string warningStr = "send text websocket instance wasn't ready...";
        log("%s", warningStr.c_str());
        _sendTextStatus->setString(warningStr.c_str());
    }
}
