/****************************************************************************
Copyright (c) 2013-2015 Chris Hannon http://www.channon.us
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

/**
*  @brief Layer for socket.io test, implements SIODelegate for network level socket events such as disconnect and close
*/
class SocketIOTestLayer
	: public cocos2d::Layer
	, public cocos2d::network::SocketIO::SIODelegate
{
public:
	SocketIOTestLayer(void);
	SocketIOTestLayer(std::string);
	virtual ~SocketIOTestLayer(void);

	/**
	*  @brief Used for network level socket close (not for disconnect from the socket.io server)
	*/
	virtual void onClose(cocos2d::network::SIOClient* client);
	/**
	*  @brief Used for network level socket error (not for disconnect from the socket.io server)
	**/
	virtual void onError(cocos2d::network::SIOClient* client, const std::string& data);
	/**
	*  @brief Common function to call on both socket.io disconnect and websocket close
	**/
	void closedSocketAction(cocos2d::network::SIOClient* client);

	void toExtensionsMainLayer(cocos2d::Ref *sender);
	
	// test action handlers for main Test Client that connects to defaul namespace "" or "/"
	void onMenuSIOClientClicked(cocos2d::Ref *sender);
	void onMenuTestMessageClicked(cocos2d::Ref *sender);
	void onMenuTestEventClicked(cocos2d::Ref *sender);
	void onMenuTestClientDisconnectClicked(cocos2d::Ref *sender);

	// test action handlers for Test Endpoint that connects to /testpoint endpoint
	void onMenuSIOEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestMessageEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestEventEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestEndpointDisconnectClicked(cocos2d::Ref *sender);

	// handlers for socket.io related events

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
	
	virtual void setSIOVersion(std::string v) { _sioVersion = v; };
	virtual std::string getSIOVersion() { return _sioVersion; };

protected:
	cocos2d::network::SIOClient *_sioClient, *_sioEndpoint;

	cocos2d::Label *_sioClientStatus;

	std::string _sioVersion;

};

void runSocketIOTest(std::string);

#endif /* defined(__TestCpp__SocketIOTest__) */
