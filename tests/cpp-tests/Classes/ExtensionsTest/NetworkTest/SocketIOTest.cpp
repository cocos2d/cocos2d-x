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


#include "SocketIOTest.h"
#include "../ExtensionsTest.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace  cocos2d::network;

SocketIOTestLayer::SocketIOTestLayer()
	: SocketIOTestLayer("09") {
}

SocketIOTestLayer::SocketIOTestLayer(std::string version)
	: _sioClient(nullptr)
	, _sioEndpoint(nullptr)
	, _sioClientStatus(nullptr)
	, _sioVersion(version)
{//set the clients to nullptr until we are ready to connect

	Size winSize = Director::getInstance()->getWinSize();
    
    const int MARGIN = 40;
    const int SPACE = 35;
    
    auto label = Label::createWithTTF("SocketIO Extension Test for v" + this->getSIOVersion(), "fonts/arial.ttf", 28);
    label->setPosition(Vec2(winSize.width / 2, winSize.height - MARGIN));
    addChild(label, 0);
    	
    auto menuRequest = Menu::create();
    menuRequest->setPosition(Vec2::ZERO);
    addChild(menuRequest);
    
    // Test to create basic client in the default namespace
    auto labelSIOClient = Label::createWithTTF("Open SocketIO Client", "fonts/arial.ttf", 22);
    auto itemSIOClient = MenuItemLabel::create(labelSIOClient, CC_CALLBACK_1(SocketIOTestLayer::onMenuSIOClientClicked, this));
	itemSIOClient->setPosition(Vec2(VisibleRect::left().x + labelSIOClient->getContentSize().width / 2 + 5, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSIOClient);

	// Test to create a client at the endpoint '/testpoint'
    auto labelSIOEndpoint = Label::createWithTTF("Open SocketIO Endpoint", "fonts/arial.ttf", 22);
    auto itemSIOEndpoint = MenuItemLabel::create(labelSIOEndpoint, CC_CALLBACK_1(SocketIOTestLayer::onMenuSIOEndpointClicked, this));
	itemSIOEndpoint->setPosition(Vec2(VisibleRect::right().x - labelSIOEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSIOEndpoint);

	// Test sending message to default namespace
    auto labelTestMessage = Label::createWithTTF("Send Test Message", "fonts/arial.ttf", 22);
    auto itemTestMessage = MenuItemLabel::create(labelTestMessage, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestMessageClicked, this));
    itemTestMessage->setPosition(Vec2(VisibleRect::left().x + labelTestMessage->getContentSize().width / 2 + 5, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemTestMessage);

	// Test sending message to the endpoint '/testpoint'
    auto labelTestMessageEndpoint = Label::createWithTTF("Test Endpoint Message", "fonts/arial.ttf", 22);
    auto itemTestMessageEndpoint = MenuItemLabel::create(labelTestMessageEndpoint, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestMessageEndpointClicked, this));
    itemTestMessageEndpoint->setPosition(Vec2(VisibleRect::right().x - labelTestMessageEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemTestMessageEndpoint);

	// Test sending event 'echotest' to default namespace
    auto labelTestEvent = Label::createWithTTF("Send Test Event", "fonts/arial.ttf", 22);
    auto itemTestEvent = MenuItemLabel::create(labelTestEvent, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestEventClicked, this));
    itemTestEvent->setPosition(Vec2(VisibleRect::left().x + labelTestEvent->getContentSize().width / 2 + 5, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemTestEvent);

	// Test sending event 'echotest' to the endpoint '/testpoint'
    auto labelTestEventEndpoint = Label::createWithTTF("Test Endpoint Event", "fonts/arial.ttf", 22);
    auto itemTestEventEndpoint = MenuItemLabel::create(labelTestEventEndpoint, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestEventEndpointClicked, this));
    itemTestEventEndpoint->setPosition(Vec2(VisibleRect::right().x - labelTestEventEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemTestEventEndpoint);

	// Test disconnecting basic client
    auto labelTestClientDisconnect = Label::createWithTTF("Disconnect Socket", "fonts/arial.ttf", 22);
    auto itemClientDisconnect = MenuItemLabel::create(labelTestClientDisconnect, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestClientDisconnectClicked, this));
    itemClientDisconnect->setPosition(Vec2(VisibleRect::left().x + labelTestClientDisconnect->getContentSize().width / 2 + 5, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemClientDisconnect);

	// Test disconnecting the endpoint '/testpoint'
    auto labelTestEndpointDisconnect = Label::createWithTTF("Disconnect Endpoint", "fonts/arial.ttf", 22);
    auto itemTestEndpointDisconnect = MenuItemLabel::create(labelTestEndpointDisconnect, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestEndpointDisconnectClicked, this));
    itemTestEndpointDisconnect->setPosition(Vec2(VisibleRect::right().x - labelTestEndpointDisconnect->getContentSize().width / 2 - 5, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemTestEndpointDisconnect);
    
	// Shared Status Label
    _sioClientStatus = Label::createWithTTF("Not connected...", "fonts/arial.ttf", 14, Size(320, 100), TextHAlignment::LEFT);
    _sioClientStatus->setAnchorPoint(Vec2(0, 0));
    _sioClientStatus->setPosition(Vec2(VisibleRect::left().x, VisibleRect::rightBottom().y));
    this->addChild(_sioClientStatus);

	// Back Menu
    auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(SocketIOTestLayer::toExtensionsMainLayer, this));
    itemBack->setPosition(Vec2(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    auto menuBack = Menu::create(itemBack, nullptr);
    menuBack->setPosition(Vec2::ZERO);
    addChild(menuBack);

}


SocketIOTestLayer::~SocketIOTestLayer(void)
{
}

//test event callback handlers, these will be registered with socket.io
void SocketIOTestLayer::testevent(SIOClient *client, const std::string& data) {

	CCLOGINFO("SocketIOTestLayer::testevent called with data: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received event testevent with data: " << data.c_str();	

	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::echotest(SIOClient *client, const std::string& data) {

	CCLOGINFO("SocketIOTestLayer::echotest called with data: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received event echotest with data: " << data.c_str();	

	_sioClientStatus->setString(s.str().c_str());

}

// onMessage is no longer a required override from the delegate class
// 'message' events and handlers are now registered in the same way that other events are
void SocketIOTestLayer::message(network::SIOClient* client, const std::string& data)
{
	CCLOGINFO("SocketIOTestLayer::message received: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received message with content: " << data.c_str();
	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::json(network::SIOClient* client, const std::string& data)
{
	CCLOGINFO("SocketIOTestLayer::json received: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received json message with content: " << data.c_str();
	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::connect(network::SIOClient* client, const std::string& data)
{
	CCLOGINFO("SocketIOTestLayer::connect called");

	std::stringstream s;
	s << client->getTag() << " connected!";
	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::disconnect(network::SIOClient* client, const std::string& data)
{
	CCLOGINFO("SocketIOTestLayer::disconnect called");

	std::stringstream s;
	s << client->getTag() << " disconnected by server!";
	_sioClientStatus->setString(s.str().c_str());

	this->closedSocketAction(client);

}

void SocketIOTestLayer::closedSocketAction(network::SIOClient* client)
{
	//set the local pointer to nullptr or connect to another client
	//the client object will be released on its own after this method completes
	if (client == _sioClient) {

		_sioClient = nullptr;
	}
	else if (client == _sioEndpoint) {

		_sioEndpoint = nullptr;
	}
}

void SocketIOTestLayer::toExtensionsMainLayer(cocos2d::Ref *sender)
{
	ExtensionsTestScene *scene = new (std::nothrow) ExtensionsTestScene();
    scene->runThisTest();
    scene->release();

	if(_sioEndpoint) _sioEndpoint->disconnect();
	if(_sioClient) _sioClient->disconnect();

}

void SocketIOTestLayer::onMenuSIOClientClicked(cocos2d::Ref *sender)
{
	//create a client by using this static method, url does not need to contain the protocol
	_sioClient = SocketIO::connect("ws://dev.channon.us:30" + this->getSIOVersion(), *this);
	//you may set a tag for the client for reference in callbacks
	_sioClient->setTag("Test Client");

	//register event callbacks using the CC_CALLBACK_2() macro and passing the instance of the target class
	_sioClient->on("testevent", CC_CALLBACK_2(SocketIOTestLayer::testevent, this));
	_sioClient->on("echotest", CC_CALLBACK_2(SocketIOTestLayer::echotest, this));
	_sioClient->on("message", CC_CALLBACK_2(SocketIOTestLayer::message, this));
	_sioClient->on("json", CC_CALLBACK_2(SocketIOTestLayer::json, this));
	_sioClient->on("connect", CC_CALLBACK_2(SocketIOTestLayer::connect, this));
	_sioClient->on("disconnect", CC_CALLBACK_2(SocketIOTestLayer::disconnect, this));

}

void SocketIOTestLayer::onMenuSIOEndpointClicked(cocos2d::Ref *sender)
{
	//repeat the same connection steps for the namespace "testpoint"
	_sioEndpoint = SocketIO::connect("ws://dev.channon.us:30" + this->getSIOVersion() + "/testpoint", *this);
	//a tag to differentiate in shared callbacks
	_sioEndpoint->setTag("Test Endpoint");	

	//demonstrating how callbacks can be shared within a delegate
	_sioEndpoint->on("testevent", CC_CALLBACK_2(SocketIOTestLayer::testevent, this));
	_sioEndpoint->on("echotest", CC_CALLBACK_2(SocketIOTestLayer::echotest, this));
	_sioEndpoint->on("message", CC_CALLBACK_2(SocketIOTestLayer::message, this));
	_sioEndpoint->on("json", CC_CALLBACK_2(SocketIOTestLayer::json, this));
	_sioEndpoint->on("connect", CC_CALLBACK_2(SocketIOTestLayer::connect, this));
	_sioEndpoint->on("disconnect", CC_CALLBACK_2(SocketIOTestLayer::disconnect, this));


}

void SocketIOTestLayer::onMenuTestMessageClicked(cocos2d::Ref *sender)
{
	//check that the socket is != nullptr before sending or emitting events
	//the client should be nullptr either before initialization and connection or after disconnect
	if(_sioClient != nullptr) _sioClient->send("Hello Socket.IO!");

}

void SocketIOTestLayer::onMenuTestMessageEndpointClicked(cocos2d::Ref *sender)
{

	if(_sioEndpoint != nullptr) _sioEndpoint->send("Hello Socket.IO!");

}

void SocketIOTestLayer::onMenuTestEventClicked(cocos2d::Ref *sender)
{
	//check that the socket is != nullptr before sending or emitting events
	//the client should be nullptr either before initialization and connection or after disconnect
	if(_sioClient != nullptr) _sioClient->emit("echotest","{\"name\":\"myname\",\"type\":\"mytype\"}");

}

void SocketIOTestLayer::onMenuTestEventEndpointClicked(cocos2d::Ref *sender)
{

	if(_sioEndpoint != nullptr) _sioEndpoint->emit("echotest","{\"name\":\"myname\",\"type\":\"mytype\"}");

}

void SocketIOTestLayer::onMenuTestClientDisconnectClicked(cocos2d::Ref *sender)
{
	// Disconnecting from the default namespace "" or "/" will also disconnect all other endpoints
	std::stringstream s;

	if (_sioClient != nullptr) {
		s << _sioClient->getTag() << " manually closed!";
		_sioClient->disconnect();
		_sioClient = nullptr;
	}
	else {
		s << "Socket.io Test Client not initialized!";
	}

	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::onMenuTestEndpointDisconnectClicked(cocos2d::Ref *sender)
{
	std::stringstream s;
	
	if (_sioEndpoint != nullptr) {
		s << _sioEndpoint->getTag() << " manually closed!";
		_sioEndpoint->disconnect();		
		_sioEndpoint = nullptr;
	}
	else {
		s << "Socket.io Test Endpoint not initialized!";
	}

	_sioClientStatus->setString(s.str().c_str());

}

// SIODelegate methods to catch network/socket level events outside of the socket.io events

void SocketIOTestLayer::onClose(network::SIOClient* client)
{
	CCLOGINFO("SocketIOTestLayer::onClose called");

	std::stringstream s;
	s << client->getTag() << " closed!";	
	_sioClientStatus->setString(s.str().c_str());

	this->closedSocketAction(client);
	
}

void SocketIOTestLayer::onError(network::SIOClient* client, const std::string& data)
{
	CCLOGINFO("SocketIOTestLayer::onError received: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received error with content: " << data.c_str();	
	_sioClientStatus->setString(s.str().c_str());
}

void runSocketIOTest(std::string sioversion)
{
    auto scene = Scene::create();
    auto layer = new (std::nothrow) SocketIOTestLayer(sioversion);
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
    layer->release();
}
