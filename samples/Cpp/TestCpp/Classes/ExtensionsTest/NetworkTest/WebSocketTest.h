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
#include "cocos-ext.h"
#include "WebSocket.h"

class WebSocketTestLayer
: public cocos2d::Layer
, public cocos2d::extension::WebSocket::Delegate
{
public:
    WebSocketTestLayer();
    virtual ~WebSocketTestLayer();
    
    virtual void onOpen(cocos2d::extension::WebSocket* ws);
    virtual void onMessage(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::Data& data);
    virtual void onClose(cocos2d::extension::WebSocket* ws);
    virtual void onError(cocos2d::extension::WebSocket* ws, const cocos2d::extension::WebSocket::ErrorCode& error);
    
    void toExtensionsMainLayer(cocos2d::Object *sender);
    
    // Menu Callbacks
    void onMenuSendTextClicked(cocos2d::Object *sender);
    void onMenuSendBinaryClicked(cocos2d::Object *sender);

private:
    cocos2d::extension::WebSocket* _wsiSendText;
    cocos2d::extension::WebSocket* _wsiSendBinary;
    cocos2d::extension::WebSocket* _wsiError;
    
    cocos2d::LabelTTF* _sendTextStatus;
    cocos2d::LabelTTF* _sendBinaryStatus;
    cocos2d::LabelTTF* _errorStatus;
    
    int _sendTextTimes;
    int _sendBinaryTimes;
};

void runWebSocketTest();

#endif /* defined(__TestCpp__WebSocketTest__) */
