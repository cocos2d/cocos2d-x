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
: _wsiSendText(NULL)
, _wsiSendBinary(NULL)
, _wsiError(NULL)
, _sendTextStatus(NULL)
, _sendBinaryStatus(NULL)
, _errorStatus(NULL)
, _sendTextTimes(0)
, _sendBinaryTimes(0)
{
    Size winSize = Director::sharedDirector()->getWinSize();
    
    const int MARGIN = 40;
    const int SPACE = 35;
    
    LabelTTF *label = LabelTTF::create("WebSocket Test", "Arial", 28);
    label->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN));
    addChild(label, 0);
    
    Menu *menuRequest = Menu::create();
    menuRequest->setPosition(PointZero);
    addChild(menuRequest);
    
    // Send Text
    LabelTTF *labelSendText = LabelTTF::create("Send Text", "Arial", 22);
    MenuItemLabel *itemSendText = MenuItemLabel::create(labelSendText, this, menu_selector(WebSocketTestLayer::onMenuSendTextClicked));
    itemSendText->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSendText);
    
    // Send Binary
    LabelTTF *labelSendBinary = LabelTTF::create("Send Binary", "Arial", 22);
    MenuItemLabel *itemSendBinary = MenuItemLabel::create(labelSendBinary, this, menu_selector(WebSocketTestLayer::onMenuSendBinaryClicked));
    itemSendBinary->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemSendBinary);
    

    // Send Text Status Label
    _sendTextStatus = LabelTTF::create("Send Text WS is waiting...", "Arial", 14, CCSizeMake(160, 100), kTextAlignmentCenter, kVerticalTextAlignmentTop);
    _sendTextStatus->setAnchorPoint(ccp(0, 0));
    _sendTextStatus->setPosition(ccp(VisibleRect::left().x, VisibleRect::rightBottom().y + 25));
    this->addChild(_sendTextStatus);
    
    // Send Binary Status Label
    _sendBinaryStatus = LabelTTF::create("Send Binary WS is waiting...", "Arial", 14, CCSizeMake(160, 100), kTextAlignmentCenter, kVerticalTextAlignmentTop);
    _sendBinaryStatus->setAnchorPoint(ccp(0, 0));
    _sendBinaryStatus->setPosition(ccp(VisibleRect::left().x + 160, VisibleRect::rightBottom().y + 25));
    this->addChild(_sendBinaryStatus);
    
    // Error Label
    _errorStatus = LabelTTF::create("Error WS is waiting...", "Arial", 14, CCSizeMake(160, 100), kTextAlignmentCenter, kVerticalTextAlignmentTop);
    _errorStatus->setAnchorPoint(ccp(0, 0));
    _errorStatus->setPosition(ccp(VisibleRect::left().x + 320, VisibleRect::rightBottom().y + 25));
    this->addChild(_errorStatus);
    
    // Back Menu
    MenuItemFont *itemBack = MenuItemFont::create("Back", this, menu_selector(WebSocketTestLayer::toExtensionsMainLayer));
    itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    Menu *menuBack = Menu::create(itemBack, NULL);
    menuBack->setPosition(PointZero);
    addChild(menuBack);
    
    _wsiSendText = new WebSocket();
    _wsiSendBinary = new WebSocket();
    _wsiError = new WebSocket();
    
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
void WebSocketTestLayer::onOpen(cocos2d::extension::WebSocket* ws)
{
    CCLog("Websocket (%p) opened", ws);
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
        CCAssert(0, "error test will never go here.");
    }
}

void WebSocketTestLayer::onMessage(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::Data& data)
{
    if (!data.isBinary)
    {
        _sendTextTimes++;
        char times[100] = {0};
        sprintf(times, "%d", _sendTextTimes);
        std::string textStr = std::string("response text msg: ")+data.bytes+", "+times;
        CCLog("%s", textStr.c_str());
        
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
        CCLog("%s", binaryStr.c_str());
        _sendBinaryStatus->setString(binaryStr.c_str());
    }
}

void WebSocketTestLayer::onClose(cocos2d::extension::WebSocket* ws)
{
    CCLog("websocket instance (%p) closed.", ws);
    if (ws == _wsiSendText)
    {
        _wsiSendText = NULL;
    }
    else if (ws == _wsiSendBinary)
    {
        _wsiSendBinary = NULL;
    }
    else if (ws == _wsiError)
    {
        _wsiError = NULL;
    }
    // Delete websocket instance.
    CC_SAFE_DELETE(ws);
}

void WebSocketTestLayer::onError(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::ErrorCode& error)
{
    CCLog("Error was fired, error code: %d", error);
    if (ws == _wsiError)
    {
        char buf[100] = {0};
        sprintf(buf, "an error was fired, code: %d", error);
        _errorStatus->setString(buf);
    }
}

void WebSocketTestLayer::toExtensionsMainLayer(cocos2d::Object *sender)
{
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

// Menu Callbacks
void WebSocketTestLayer::onMenuSendTextClicked(cocos2d::Object *sender)
{
    if (_wsiSendText->getReadyState() == WebSocket::kStateOpen)
    {
        _sendTextStatus->setString("Send Text WS is waiting...");
        _wsiSendText->send("Hello WebSocket, I'm a text message.");
    }
    else
    {
        std::string warningStr = "send text websocket instance wasn't ready...";
        CCLog("%s", warningStr.c_str());
        _sendTextStatus->setString(warningStr.c_str());
    }
}

void WebSocketTestLayer::onMenuSendBinaryClicked(cocos2d::Object *sender)
{
    if (_wsiSendBinary->getReadyState() == WebSocket::kStateOpen)
    {
        _sendBinaryStatus->setString("Send Binary WS is waiting...");
        char buf[] = "Hello WebSocket,\0 I'm\0 a\0 binary\0 message\0.";
        _wsiSendBinary->send((unsigned char*)buf, sizeof(buf));
    }
    else
    {
        std::string warningStr = "send binary websocket instance wasn't ready...";
        CCLog("%s", warningStr.c_str());
        _sendBinaryStatus->setString(warningStr.c_str());
    }
}

void runWebSocketTest()
{
    Scene *pScene = Scene::create();
    WebSocketTestLayer *pLayer = new WebSocketTestLayer();
    pScene->addChild(pLayer);
    
    Director::sharedDirector()->replaceScene(pScene);
    pLayer->release();
}
