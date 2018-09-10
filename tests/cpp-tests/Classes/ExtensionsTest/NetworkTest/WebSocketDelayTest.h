#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/WebSocket.h"
#include "BaseTest.h"

#include <chrono>

class WebSocketDelayTest : public TestCase
, public cocos2d::network::WebSocket::Delegate
{
public:
    CREATE_FUNC(WebSocketDelayTest);

    WebSocketDelayTest();
    virtual ~WebSocketDelayTest();

    virtual void onExit() override;
    
    virtual void onOpen(cocos2d::network::WebSocket* ws)override;
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)override;
    virtual void onClose(cocos2d::network::WebSocket* ws)override;
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)override;
    
    // Menu Callbacks
    void onMenuSendTextClicked(cocos2d::Ref *sender);

    virtual std::string title() const override { return "WebSocket Delay Test"; }
    void startTestCallback(cocos2d::Ref* sender);

    int64_t getNowMircroSeconds()
    {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    }

    void doSendText();
    void doReceiveText();

private:
    cocos2d::network::WebSocket* _wsiSendText;
    
    cocos2d::Label* _sendTextStatus;
    cocos2d::Label* _progressStatus;
    cocos2d::Menu* _startTestMenu;
   
    int64_t _totalDelayMircoSec = 0;
    int64_t _sendTimeMircoSec = 0;
    int64_t _receiveTimeMircoSec = 0;

    int _sendTextTimes = 0;
    int _receiveTextTimes = 0;
};

