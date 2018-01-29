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

    virtual void onExit() override;
    
    virtual void onOpen(cocos2d::network::WebSocket* ws)override;
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)override;
    virtual void onClose(cocos2d::network::WebSocket* ws)override;
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)override;
    
    // Menu Callbacks
    void onMenuSendTextClicked(cocos2d::Ref *sender);
    void onMenuSendMultipleTextClicked(cocos2d::Ref *sender);
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

class WebSocketCloseTest : public TestCase
    , public cocos2d::network::WebSocket::Delegate
{
public:
    CREATE_FUNC(WebSocketCloseTest);

    virtual void onOpen(cocos2d::network::WebSocket* ws)override;
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)override;
    virtual void onClose(cocos2d::network::WebSocket* ws)override;
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)override;

    WebSocketCloseTest();
    virtual ~WebSocketCloseTest();

    virtual std::string title() const override { return "WebSocket close by resetDirector event Test"; }
    std::string subtitle() const override { return "Click close button, Program should close without crash."; }

private:
    cocos2d::network::WebSocket* _wsiTest;
};

#endif /* defined(__TestCpp__WebSocketTest__) */
