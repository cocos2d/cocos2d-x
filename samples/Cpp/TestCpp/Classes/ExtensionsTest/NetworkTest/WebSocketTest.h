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
#include "network/WebSocket.h"

class WebSocketTestLayer
: public cc::Layer
, public cc::extension::WebSocket::Delegate
{
public:
    WebSocketTestLayer();
    virtual ~WebSocketTestLayer();
    
    virtual void onOpen(cc::extension::WebSocket* ws);
    virtual void onMessage(cc::extension::WebSocket* ws, const cc::extension::WebSocket::Data& data);
    virtual void onClose(cc::extension::WebSocket* ws);
    virtual void onError(cc::extension::WebSocket* ws, const cc::extension::WebSocket::ErrorCode& error);
    
    void toExtensionsMainLayer(cc::Object *sender);
    
    // Menu Callbacks
    void onMenuSendTextClicked(cc::Object *sender);
    void onMenuSendBinaryClicked(cc::Object *sender);

private:
    cc::extension::WebSocket* _wsiSendText;
    cc::extension::WebSocket* _wsiSendBinary;
    cc::extension::WebSocket* _wsiError;
    
    cc::LabelTTF* _sendTextStatus;
    cc::LabelTTF* _sendBinaryStatus;
    cc::LabelTTF* _errorStatus;
    
    int _sendTextTimes;
    int _sendBinaryTimes;
};

void runWebSocketTest();

#endif /* defined(__TestCpp__WebSocketTest__) */
