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

#include "WebSocketTest.h"
#include "../ExtensionsTest.h"
#include "testResource.h"

#include "WebSocketDelayTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

WebSocketTests::WebSocketTests()
{
    ADD_TEST_CASE(WebSocketTest);
    ADD_TEST_CASE(WebSocketCloseTest);
    ADD_TEST_CASE(WebSocketDelayTest);
}

WebSocketTest::WebSocketTest()
: _wsiSendText(nullptr)
, _wsiSendBinary(nullptr)
, _wsiError(nullptr)
, _sendTextStatus(nullptr)
, _sendBinaryStatus(nullptr)
, _errorStatus(nullptr)
, _sendTextTimes(0)
, _sendBinaryTimes(0)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    const int MARGIN = 40;
    const int SPACE = 35;
    
    auto menuRequest = Menu::create();
    menuRequest->setPosition(Vec2::ZERO);
    addChild(menuRequest);
    
    // Send Text
    auto labelSendText = Label::createWithTTF("Send Text", "fonts/arial.ttf", 20);
    auto itemSendText = MenuItemLabel::create(labelSendText, CC_CALLBACK_1(WebSocketTest::onMenuSendTextClicked, this));
    itemSendText->setPosition(Vec2(winSize.width / 2, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSendText);
    
    labelSendText = Label::createWithTTF("Send Multiple Text", "fonts/arial.ttf", 20);
    itemSendText = MenuItemLabel::create(labelSendText, CC_CALLBACK_1(WebSocketTest::onMenuSendMultipleTextClicked, this));
    itemSendText->setPosition(Vec2(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemSendText);
    
    // Send Binary
    auto labelSendBinary = Label::createWithTTF("Send Binary", "fonts/arial.ttf", 20);
    auto itemSendBinary = MenuItemLabel::create(labelSendBinary, CC_CALLBACK_1(WebSocketTest::onMenuSendBinaryClicked, this));
    itemSendBinary->setPosition(Vec2(winSize.width / 2, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemSendBinary);
    

    // Send Text Status Label
    _sendTextStatus = Label::createWithTTF("Send Text WS is waiting...", "fonts/arial.ttf", 16, Size(160, 100), TextHAlignment::CENTER, TextVAlignment::TOP);
    _sendTextStatus->setAnchorPoint(Vec2(0, 0));
    _sendTextStatus->setPosition(Vec2(VisibleRect::left().x, VisibleRect::rightBottom().y + 25));
    this->addChild(_sendTextStatus);
    
    // Send Binary Status Label
    _sendBinaryStatus = Label::createWithTTF("Send Binary WS is waiting...", "fonts/arial.ttf", 16, Size(160, 100), TextHAlignment::CENTER, TextVAlignment::TOP);
    _sendBinaryStatus->setAnchorPoint(Vec2(0, 0));
    _sendBinaryStatus->setPosition(Vec2(VisibleRect::left().x + 160, VisibleRect::rightBottom().y + 25));
    this->addChild(_sendBinaryStatus);
    
    // Error Label
    _errorStatus = Label::createWithTTF("Error WS is waiting...", "fonts/arial.ttf", 16, Size(160, 100), TextHAlignment::CENTER, TextVAlignment::TOP);
    _errorStatus->setAnchorPoint(Vec2(0, 0));
    _errorStatus->setPosition(Vec2(VisibleRect::left().x + 320, VisibleRect::rightBottom().y + 25));
    this->addChild(_errorStatus);
    
    auto startTestLabel = Label::createWithTTF("Start Test WebSocket", "fonts/arial.ttf", 16);
    auto startTestItem = MenuItemLabel::create(startTestLabel, CC_CALLBACK_1(WebSocketTest::startTestCallback, this));
    startTestItem->setPosition(Vec2(VisibleRect::center().x - 150, VisibleRect::bottom().y + 150));
    _startTestMenu = Menu::create(startTestItem, nullptr);
    _startTestMenu->setPosition(Vec2::ZERO);
    this->addChild(_startTestMenu, 1);
}

WebSocketTest::~WebSocketTest()
{

}

void WebSocketTest::onExit()
{
    if (_wsiSendText)
    {
        _wsiSendText->closeAsync();
    }

    if (_wsiSendBinary)
    {
        _wsiSendBinary->closeAsync();
    }

    if (_wsiError)
    {
        _wsiError->closeAsync();
    }
    Node::onExit();
}

void WebSocketTest::startTestCallback(Ref* sender)
{
    removeChild(_startTestMenu);
    _startTestMenu = nullptr;

    _wsiSendText = new network::WebSocket();
    _wsiSendBinary = new network::WebSocket();
    _wsiError = new network::WebSocket();

    std::vector<std::string> protocols;
    protocols.push_back("myprotocol_1");
    protocols.push_back("myprotocol_2");
    if (!_wsiSendText->init(*this, "wss://echo.websocket.org", &protocols, "cacert.pem"))
    {
        CC_SAFE_DELETE(_wsiSendText);
    }
    else
    {
        retain(); // Retain self to avoid WebSocketTest instance be deleted immediately, it will be released in WebSocketTest::onClose.
    }

    protocols.erase(protocols.begin());
    if (!_wsiSendBinary->init(*this, "wss://echo.websocket.org", &protocols, "cacert.pem"))
    {
        CC_SAFE_DELETE(_wsiSendBinary);
    }
    else
    {
        retain(); // Retain self to avoid WebSocketTest instance be deleted immediately, it will be released in WebSocketTest::onClose.
    }

    if (!_wsiError->init(*this, "ws://invalid.urlxxxxxxxx.com"))
    {
        CC_SAFE_DELETE(_wsiError);
    }
    else
    {
        retain(); // Retain self to avoid WebSocketTest instance be deleted immediately, it will be released in WebSocketTest::onClose.
    }
}

// Delegate methods
void WebSocketTest::onOpen(network::WebSocket* ws)
{
    char status[256] = {0};
    sprintf(status, "Opened, url: %s, protocol: %s", ws->getUrl().c_str(), ws->getProtocol().c_str());

    log("Websocket (%p) was opened, url: %s, protocol: %s", ws, ws->getUrl().c_str(), ws->getProtocol().c_str());
    if (ws == _wsiSendText)
    {
        _sendTextStatus->setString(status);
    }
    else if (ws == _wsiSendBinary)
    {
        _sendBinaryStatus->setString(status);
    }
    else if (ws == _wsiError)
    {
        CCASSERT(0, "error test will never go here.");
    }
}

void WebSocketTest::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data)
{
    if (!data.isBinary)
    {
        _sendTextTimes++;
        char times[100] = {0};
        sprintf(times, "%d", _sendTextTimes);
        std::string textStr = std::string("response text msg: ")+data.bytes+", "+times;
        log("%s", textStr.c_str());
        
        _sendTextStatus->setString(textStr.c_str());
    }
    else
    {
        _sendBinaryTimes++;
        char times[100] = {0};
        sprintf(times, "%d", _sendBinaryTimes);

        std::string binaryStr = "response bin msg: ";
        
        for (int i = 0; i < data.len; ++i) {
            if (data.bytes[i] != '\0')
            {
                binaryStr += data.bytes[i];
            }
            else
            {
                binaryStr += "\'\\0\'";
            }
        }
        
        binaryStr += std::string(", ")+times;
        log("%s", binaryStr.c_str());
        _sendBinaryStatus->setString(binaryStr.c_str());
    }
}

void WebSocketTest::onClose(network::WebSocket* ws)
{
    log("onClose: websocket instance (%p) closed.", ws);
    if (ws == _wsiSendText)
    {
        _wsiSendText = nullptr;
        _sendTextStatus->setString("Send Text WS was closed");
    }
    else if (ws == _wsiSendBinary)
    {
        _wsiSendBinary = nullptr;
        _sendBinaryStatus->setString("Send Binary WS was closed");
    }
    else if (ws == _wsiError)
    {
        _wsiError = nullptr;
        _errorStatus->setString("Test invalid URL WS was closed");
    }
    // Delete websocket instance.
    CC_SAFE_DELETE(ws);
    log("WebSocketTest ref: %u", _referenceCount);
    release();
}

void WebSocketTest::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error)
{
    log("Error was fired, error code: %d", static_cast<int>(error));
    char buf[100] = {0};
    sprintf(buf, "An error was fired, code: %d", static_cast<int>(error));

    if (ws == _wsiSendText)
    {
        _sendTextStatus->setString(buf);
    }
    else if (ws == _wsiSendBinary)
    {
        _sendBinaryStatus->setString(buf);
    }
    else if (ws == _wsiError)
    {
        _errorStatus->setString(buf);
    }
}

// Menu Callbacks
void WebSocketTest::onMenuSendTextClicked(cocos2d::Ref *sender)
{
    if (! _wsiSendText)
    {
        return;
    }

    if (_wsiSendText->getReadyState() == network::WebSocket::State::OPEN)
    {
        _sendTextStatus->setString("Send Text WS is waiting...");
        _wsiSendText->send("Hello WebSocket, I'm a text message.");
    }
    else
    {
        std::string warningStr = "send text websocket instance wasn't ready...";
        log("%s", warningStr.c_str());
        _sendTextStatus->setString(warningStr.c_str());
    }
}

void WebSocketTest::onMenuSendMultipleTextClicked(cocos2d::Ref *sender)
{
    if (! _wsiSendText)
    {
        return;
    }
    
    if (_wsiSendText->getReadyState() == network::WebSocket::State::OPEN)
    {
        _sendTextStatus->setString("Send Multiple Text WS is waiting...");
        for (int index = 0; index < 15; ++index) {
            _wsiSendText->send(StringUtils::format("Hello WebSocket, text message index:%d", index));
        }
    }
    else
    {
        std::string warningStr = "send text websocket instance wasn't ready...";
        log("%s", warningStr.c_str());
        _sendTextStatus->setString(warningStr.c_str());
    }
}

void WebSocketTest::onMenuSendBinaryClicked(cocos2d::Ref *sender)
{
    if (! _wsiSendBinary) {
        return;
    }

    if (_wsiSendBinary->getReadyState() == network::WebSocket::State::OPEN)
    {
        _sendBinaryStatus->setString("Send Binary WS is waiting...");
        char buf[] = "Hello WebSocket,\0 I'm\0 a\0 binary\0 message\0.";
        _wsiSendBinary->send((unsigned char*)buf, sizeof(buf));
    }
    else
    {
        std::string warningStr = "send binary websocket instance wasn't ready...";
        log("%s", warningStr.c_str());
        _sendBinaryStatus->setString(warningStr.c_str());
    }
}

WebSocketCloseTest::WebSocketCloseTest()
: _wsiTest(nullptr)
{
    auto winSize = Director::getInstance()->getWinSize();

    _wsiTest = new network::WebSocket();

    if (!_wsiTest->init(*this, "ws://echo.websocket.org"))
    {
        delete _wsiTest;
        _wsiTest = nullptr;
    }

    auto closeItem = MenuItemImage::create(s_pathClose, s_pathClose, [](Ref* sender){
        Director::getInstance()->end();
    });
    closeItem->setPosition(VisibleRect::right().x / 2, VisibleRect::top().y * 2 / 3);

    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

    auto notifyLabel = Label::createWithTTF("See log window, when enter there's should have\n'Websocket opened' log,\nwhen close there's should have'websocket closed' log", "fonts/arial.ttf", 20);
    notifyLabel->setPosition(VisibleRect::right().x / 2, VisibleRect::top().y / 3);
    notifyLabel->setAlignment(TextHAlignment::CENTER);
    addChild(notifyLabel, 1);
}

WebSocketCloseTest::~WebSocketCloseTest()
{
    if (_wsiTest != nullptr)
    {
        _wsiTest->close();
    }
}

// Delegate methods
void WebSocketCloseTest::onOpen(network::WebSocket* ws)
{
    log("Websocket (%p) opened", ws);
}

void WebSocketCloseTest::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data)
{
    log("Websocket get message from %p", ws);
}

void WebSocketCloseTest::onClose(network::WebSocket* ws)
{
    log("websocket (%p) closed.", ws);
    if (ws == _wsiTest) {
        _wsiTest = nullptr;
    }
    CC_SAFE_DELETE(ws);
}

void WebSocketCloseTest::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error)
{
    log("Error was fired, error code: %d", static_cast<int>(error));
}

