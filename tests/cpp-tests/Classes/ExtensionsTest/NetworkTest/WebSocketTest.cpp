//
//  WebSocketTest.cpp
//  TestCpp
//
//  Created by James Chen on 5/31/13.
//
//

#include "WebSocketTest.h"
#include "../ExtensionsTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

WebSocketTestLayer::WebSocketTestLayer()
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
    
    auto label = Label::createWithTTF("WebSocket Test", "fonts/arial.ttf", 28);
    label->setPosition(Vec2(winSize.width / 2, winSize.height - MARGIN));
    addChild(label, 0);
    
    auto menuRequest = Menu::create();
    menuRequest->setPosition(Vec2::ZERO);
    addChild(menuRequest);
    
    // Send Text
    auto labelSendText = Label::createWithTTF("Send Text", "fonts/arial.ttf", 22);
    auto itemSendText = MenuItemLabel::create(labelSendText, CC_CALLBACK_1(WebSocketTestLayer::onMenuSendTextClicked, this));
    itemSendText->setPosition(Vec2(winSize.width / 2, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSendText);
    
    // Send Binary
    auto labelSendBinary = Label::createWithTTF("Send Binary", "fonts/arial.ttf", 22);
    auto itemSendBinary = MenuItemLabel::create(labelSendBinary, CC_CALLBACK_1(WebSocketTestLayer::onMenuSendBinaryClicked, this));
    itemSendBinary->setPosition(Vec2(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemSendBinary);
    

    // Send Text Status Label
    _sendTextStatus = Label::createWithTTF("Send Text WS is waiting...", "fonts/arial.ttf", 14, Size(160, 100), TextHAlignment::CENTER, TextVAlignment::TOP);
    _sendTextStatus->setAnchorPoint(Vec2(0, 0));
    _sendTextStatus->setPosition(Vec2(VisibleRect::left().x, VisibleRect::rightBottom().y + 25));
    this->addChild(_sendTextStatus);
    
    // Send Binary Status Label
    _sendBinaryStatus = Label::createWithTTF("Send Binary WS is waiting...", "fonts/arial.ttf", 14, Size(160, 100), TextHAlignment::CENTER, TextVAlignment::TOP);
    _sendBinaryStatus->setAnchorPoint(Vec2(0, 0));
    _sendBinaryStatus->setPosition(Vec2(VisibleRect::left().x + 160, VisibleRect::rightBottom().y + 25));
    this->addChild(_sendBinaryStatus);
    
    // Error Label
    _errorStatus = Label::createWithTTF("Error WS is waiting...", "fonts/arial.ttf", 14, Size(160, 100), TextHAlignment::CENTER, TextVAlignment::TOP);
    _errorStatus->setAnchorPoint(Vec2(0, 0));
    _errorStatus->setPosition(Vec2(VisibleRect::left().x + 320, VisibleRect::rightBottom().y + 25));
    this->addChild(_errorStatus);
    
    // Back Menu
    auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(WebSocketTestLayer::toExtensionsMainLayer, this));
    itemBack->setPosition(Vec2(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    auto menuBack = Menu::create(itemBack, nullptr);
    menuBack->setPosition(Vec2::ZERO);
    addChild(menuBack);
    
    _wsiSendText = new network::WebSocket();
    _wsiSendBinary = new network::WebSocket();
    _wsiError = new network::WebSocket();
    
    if (!_wsiSendText->init(*this, "ws://echo.websocket.org"))
    {
        CC_SAFE_DELETE(_wsiSendText);
    }
    
    if (!_wsiSendBinary->init(*this, "ws://echo.websocket.org"))
    {
        CC_SAFE_DELETE(_wsiSendBinary);
    }
    
    if (!_wsiError->init(*this, "ws://invalid.url.com"))
    {
        CC_SAFE_DELETE(_wsiError);
    }
}


WebSocketTestLayer::~WebSocketTestLayer()
{
    if (_wsiSendText)
        _wsiSendText->close();
    
    if (_wsiSendBinary)
        _wsiSendBinary->close();
    
    if (_wsiError)
        _wsiError->close();
}

// Delegate methods
void WebSocketTestLayer::onOpen(network::WebSocket* ws)
{
    log("Websocket (%p) opened", ws);
    if (ws == _wsiSendText)
    {
        _sendTextStatus->setString("Send Text WS was opened.");
    }
    else if (ws == _wsiSendBinary)
    {
        _sendBinaryStatus->setString("Send Binary WS was opened.");
    }
    else if (ws == _wsiError)
    {
        CCASSERT(0, "error test will never go here.");
    }
}

void WebSocketTestLayer::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data)
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

void WebSocketTestLayer::onClose(network::WebSocket* ws)
{
    log("websocket instance (%p) closed.", ws);
    if (ws == _wsiSendText)
    {
        _wsiSendText = nullptr;
    }
    else if (ws == _wsiSendBinary)
    {
        _wsiSendBinary = nullptr;
    }
    else if (ws == _wsiError)
    {
        _wsiError = nullptr;
    }
    // Delete websocket instance.
    CC_SAFE_DELETE(ws);
}

void WebSocketTestLayer::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error)
{
    log("Error was fired, error code: %d", error);
    if (ws == _wsiError)
    {
        char buf[100] = {0};
        sprintf(buf, "an error was fired, code: %d", error);
        _errorStatus->setString(buf);
    }
}

void WebSocketTestLayer::toExtensionsMainLayer(cocos2d::Ref *sender)
{
    auto scene = new ExtensionsTestScene();
    scene->runThisTest();
    scene->release();
}

// Menu Callbacks
void WebSocketTestLayer::onMenuSendTextClicked(cocos2d::Ref *sender)
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

void WebSocketTestLayer::onMenuSendBinaryClicked(cocos2d::Ref *sender)
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

void runWebSocketTest()
{
    auto scene = Scene::create();
    auto layer = new WebSocketTestLayer();
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
    layer->release();
}
