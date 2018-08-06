/****************************************************************************
 Copyright (c) 2015 Chris Hannon http://www.channon.us
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#ifndef __TestCpp__SocketIOTest__
#define __TestCpp__SocketIOTest__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/SocketIO.h"
#include "BaseTest.h"

DEFINE_TEST_SUITE(SocketIOTests);

class SocketIOTest: public TestCase
	, public cocos2d::network::SocketIO::SIODelegate
{
public:
    CREATE_FUNC(SocketIOTest);

    SocketIOTest();
    virtual ~SocketIOTest();

	/**
	*  @brief Used for network level socket close (not for disconnect from the socket.io server)
	*/
	virtual void onClose(cocos2d::network::SIOClient* client)override;
	/**
	*  @brief Used for network level socket error (not for disconnect from the socket.io server)
	**/
	virtual void onError(cocos2d::network::SIOClient* client, const std::string& data)override;
	/**
	*  @brief Common function to call on both socket.io disconnect and websocket close
	**/
	void closedSocketAction(cocos2d::network::SIOClient* client);
	
	// test action handlers for main Test Client that connects to default namespace "" or "/"
	void onMenuSIOClientClicked(cocos2d::Ref *sender);
	void onMenuTestMessageClicked(cocos2d::Ref *sender);
	void onMenuTestEventClicked(cocos2d::Ref *sender);
	void onMenuTestClientDisconnectClicked(cocos2d::Ref *sender);

	// test action handlers for Test Endpoint that connects to /testpoint endpoint
	void onMenuSIOEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestMessageEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestEventEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestEndpointDisconnectClicked(cocos2d::Ref *sender);

	// custom handlers for socket.io related events

	/**
	*  @brief Socket.io event handler for custom event "testevent"
	**/
	void testevent(cocos2d::network::SIOClient *client, const std::string& data);
	/**
	*  @brief Socket.io event handler for custom event "echoevent"
	**/
	void echotest(cocos2d::network::SIOClient *client, const std::string& data);
	/**
	*  @brief Socket.io event handler for event "connect"
	**/
	void connect(cocos2d::network::SIOClient* client, const std::string& data);
	/**
	*  @brief Socket.io event handler for event "disconnect"
	**/
	void disconnect(cocos2d::network::SIOClient* client, const std::string& data);
	/**
	*  @brief Socket.io event handler for event "message"
	**/
	void message(cocos2d::network::SIOClient* client, const std::string& data);
	/**
	*  @brief Socket.io event handler for event "json"
	*         This is only used in v 0.9.x, in 1.x this is handled as a "message" event
	**/
	void json(cocos2d::network::SIOClient* client, const std::string& data);

    virtual std::string title() const override{ return "SocketIO Extension Test"; }

protected:

	cocos2d::network::SIOClient *_sioClient, *_sioEndpoint;

	cocos2d::Label *_sioClientStatus;
};

#endif /* defined(__TestCpp__SocketIOTest__) */
