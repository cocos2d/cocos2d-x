//
//  WebSocketTest.h
//  TestCpp
//
//  Created by James Chen on 5/31/13.
//
//

#ifndef __TestCpp__WebSocketTest__
#define __TestCpp__WebSocketTest__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/WebSocket.h"
#include "BaseTest.h"

DEFINE_TEST_SUITE(WebSocketTests);

class WebSocketTest : public TestCase
, public cocos2d::network::WebSocket::Delegate
{
public:
    CREATE_FUNC(WebSocketTest);

    WebSocketTest();
    virtual ~WebSocketTest();
    
    virtual void onOpen(cocos2d::network::WebSocket* ws);
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    virtual void onClose(cocos2d::network::WebSocket* ws);
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    
    // Menu Callbacks
    void onMenuSendTextClicked(cocos2d::Ref *sender);
    void onMenuSendBinaryClicked(cocos2d::Ref *sender);

    virtual std::string title() const override { return "WebSocket Test"; }
    void startTestCallback(cocos2d::Ref* sender);

private:
    cocos2d::network::WebSocket* _wsiSendText;
    cocos2d::network::WebSocket* _wsiSendBinary;
    cocos2d::network::WebSocket* _wsiError;
    
    cocos2d::Label* _sendTextStatus;
    cocos2d::Label* _sendBinaryStatus;
    cocos2d::Label* _errorStatus;
    cocos2d::Menu* _startTestMenu;
    
    int _sendTextTimes;
    int _sendBinaryTimes;
};

#endif /* defined(__TestCpp__WebSocketTest__) */
