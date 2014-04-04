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

class WebSocketTestLayer
: public cocos2d::Layer
, public cocos2d::network::WebSocket::Delegate
{
public:
    WebSocketTestLayer();
    virtual ~WebSocketTestLayer();
    
    virtual void onOpen(cocos2d::network::WebSocket* ws);
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    virtual void onClose(cocos2d::network::WebSocket* ws);
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    
    void toExtensionsMainLayer(cocos2d::Ref *sender);
    
    // Menu Callbacks
    void onMenuSendTextClicked(cocos2d::Ref *sender);
    void onMenuSendBinaryClicked(cocos2d::Ref *sender);

private:
    cocos2d::network::WebSocket* _wsiSendText;
    cocos2d::network::WebSocket* _wsiSendBinary;
    cocos2d::network::WebSocket* _wsiError;
    
    cocos2d::Label* _sendTextStatus;
    cocos2d::Label* _sendBinaryStatus;
    cocos2d::Label* _errorStatus;
    
    int _sendTextTimes;
    int _sendBinaryTimes;
};

void runWebSocketTest();

#endif /* defined(__TestCpp__WebSocketTest__) */
