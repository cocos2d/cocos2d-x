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
, public network::WebSocket::Delegate
{
public:
    WebSocketTestLayer();
    virtual ~WebSocketTestLayer();
    
    virtual void onOpen(network::WebSocket* ws);
    virtual void onMessage(network::WebSocket* ws, const network::WebSocket::Data& data);
    virtual void onClose(network::WebSocket* ws);
    virtual void onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error);
    
    void toExtensionsMainLayer(cocos2d::Object *sender);
    
    // Menu Callbacks
    void onMenuSendTextClicked(cocos2d::Object *sender);
    void onMenuSendBinaryClicked(cocos2d::Object *sender);

private:
    network::WebSocket* _wsiSendText;
    network::WebSocket* _wsiSendBinary;
    network::WebSocket* _wsiError;
    
    cocos2d::LabelTTF* _sendTextStatus;
    cocos2d::LabelTTF* _sendBinaryStatus;
    cocos2d::LabelTTF* _errorStatus;
    
    int _sendTextTimes;
    int _sendBinaryTimes;
};

void runWebSocketTest();

#endif /* defined(__TestCpp__WebSocketTest__) */
