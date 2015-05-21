//
//  SocketIOTest.cpp
//  TestCpp
//
//  Created by Chris Hannon on 6/26/13.
//
//


#include "SocketIOTest.h"
#include "../ExtensionsTest.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace  cocos2d::network;

SocketIOTests::SocketIOTests()
{
    ADD_TEST_CASE(SocketIOTest);
}

SocketIOTest::SocketIOTest()
	: _sioClient(nullptr)
	, _sioEndpoint(nullptr)
{
	//set the clients to nullptr until we are ready to connect

	Size winSize = Director::getInstance()->getWinSize();
    
    const int MARGIN = 40;
    const int SPACE = 35;
    	
    auto menuRequest = Menu::create();
    menuRequest->setPosition(Vec2::ZERO);
    addChild(menuRequest);
    
    // Test to create basic client in the default namespace
    auto labelSIOClient = Label::createWithTTF("Open SocketIO Client", "fonts/arial.ttf", 22);
    auto itemSIOClient = MenuItemLabel::create(labelSIOClient, CC_CALLBACK_1(SocketIOTest::onMenuSIOClientClicked, this));
	itemSIOClient->setPosition(Vec2(VisibleRect::left().x + labelSIOClient->getContentSize().width / 2 + 5, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSIOClient);

	// Test to create a client at the endpoint '/testpoint'
    auto labelSIOEndpoint = Label::createWithTTF("Open SocketIO Endpoint", "fonts/arial.ttf", 22);
    auto itemSIOEndpoint = MenuItemLabel::create(labelSIOEndpoint, CC_CALLBACK_1(SocketIOTest::onMenuSIOEndpointClicked, this));
	itemSIOEndpoint->setPosition(Vec2(VisibleRect::right().x - labelSIOEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSIOEndpoint);

	// Test sending message to default namespace
    auto labelTestMessage = Label::createWithTTF("Send Test Message", "fonts/arial.ttf", 22);
    auto itemTestMessage = MenuItemLabel::create(labelTestMessage, CC_CALLBACK_1(SocketIOTest::onMenuTestMessageClicked, this));
    itemTestMessage->setPosition(Vec2(VisibleRect::left().x + labelTestMessage->getContentSize().width / 2 + 5, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemTestMessage);

	// Test sending message to the endpoint '/testpoint'
    auto labelTestMessageEndpoint = Label::createWithTTF("Test Endpoint Message", "fonts/arial.ttf", 22);
    auto itemTestMessageEndpoint = MenuItemLabel::create(labelTestMessageEndpoint, CC_CALLBACK_1(SocketIOTest::onMenuTestMessageEndpointClicked, this));
    itemTestMessageEndpoint->setPosition(Vec2(VisibleRect::right().x - labelTestMessageEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemTestMessageEndpoint);

	// Test sending event 'echotest' to default namespace
    auto labelTestEvent = Label::createWithTTF("Send Test Event", "fonts/arial.ttf", 22);
    auto itemTestEvent = MenuItemLabel::create(labelTestEvent, CC_CALLBACK_1(SocketIOTest::onMenuTestEventClicked, this));
    itemTestEvent->setPosition(Vec2(VisibleRect::left().x + labelTestEvent->getContentSize().width / 2 + 5, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemTestEvent);

	// Test sending event 'echotest' to the endpoint '/testpoint'
    auto labelTestEventEndpoint = Label::createWithTTF("Test Endpoint Event", "fonts/arial.ttf", 22);
    auto itemTestEventEndpoint = MenuItemLabel::create(labelTestEventEndpoint, CC_CALLBACK_1(SocketIOTest::onMenuTestEventEndpointClicked, this));
    itemTestEventEndpoint->setPosition(Vec2(VisibleRect::right().x - labelTestEventEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemTestEventEndpoint);

	// Test disconnecting basic client
    auto labelTestClientDisconnect = Label::createWithTTF("Disconnect Socket", "fonts/arial.ttf", 22);
    auto itemClientDisconnect = MenuItemLabel::create(labelTestClientDisconnect, CC_CALLBACK_1(SocketIOTest::onMenuTestClientDisconnectClicked, this));
    itemClientDisconnect->setPosition(Vec2(VisibleRect::left().x + labelTestClientDisconnect->getContentSize().width / 2 + 5, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemClientDisconnect);

	// Test disconnecting the endpoint '/testpoint'
    auto labelTestEndpointDisconnect = Label::createWithTTF("Disconnect Endpoint", "fonts/arial.ttf", 22);
    auto itemTestEndpointDisconnect = MenuItemLabel::create(labelTestEndpointDisconnect, CC_CALLBACK_1(SocketIOTest::onMenuTestEndpointDisconnectClicked, this));
    itemTestEndpointDisconnect->setPosition(Vec2(VisibleRect::right().x - labelTestEndpointDisconnect->getContentSize().width / 2 - 5, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemTestEndpointDisconnect);
    
	// Shared Status Label
    _sioClientStatus = Label::createWithTTF("Not connected...", "fonts/arial.ttf", 14, Size(320, 100), TextHAlignment::LEFT);
    _sioClientStatus->setAnchorPoint(Vec2(0, 0));
    _sioClientStatus->setPosition(Vec2(VisibleRect::left().x, VisibleRect::rightBottom().y));
    this->addChild(_sioClientStatus);
}

SocketIOTest::~SocketIOTest()
{
}

//test event callback handlers, these will be registered with socket.io
void SocketIOTest::testevent(SIOClient *client, const std::string& data) {

	log("SocketIOTest::testevent called with data: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received event testevent with data: " << data.c_str();	

	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTest::echotest(SIOClient *client, const std::string& data) {

	log("SocketIOTest::echotest called with data: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received event echotest with data: " << data.c_str();	

	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTest::onMenuSIOClientClicked(cocos2d::Ref *sender)
{
	//create a client by using this static method, url does not need to contain the protocol
	_sioClient = SocketIO::connect("ws://channon.us:3000", *this);
	//you may set a tag for the client for reference in callbacks
	_sioClient->setTag("Test Client");

	//register event callbacks using the CC_CALLBACK_2() macro and passing the instance of the target class
	_sioClient->on("testevent", CC_CALLBACK_2(SocketIOTest::testevent, this));
	_sioClient->on("echotest", CC_CALLBACK_2(SocketIOTest::echotest, this));

}

void SocketIOTest::onMenuSIOEndpointClicked(cocos2d::Ref *sender)
{
	//repeat the same connection steps for the namespace "testpoint"
	_sioEndpoint = SocketIO::connect("ws://channon.us:3000/testpoint", *this);
	//a tag to differentiate in shared callbacks
	_sioEndpoint->setTag("Test Endpoint");	

	//demonstrating how callbacks can be shared within a delegate
	_sioEndpoint->on("testevent", CC_CALLBACK_2(SocketIOTest::testevent, this));
	_sioEndpoint->on("echotest", CC_CALLBACK_2(SocketIOTest::echotest, this));

}

void SocketIOTest::onMenuTestMessageClicked(cocos2d::Ref *sender)
{
	//check that the socket is != nullptr before sending or emitting events
	//the client should be nullptr either before initialization and connection or after disconnect
	if(_sioClient != nullptr) _sioClient->send("Hello Socket.IO!");

}

void SocketIOTest::onMenuTestMessageEndpointClicked(cocos2d::Ref *sender)
{

	if(_sioEndpoint != nullptr) _sioEndpoint->send("Hello Socket.IO!");

}

void SocketIOTest::onMenuTestEventClicked(cocos2d::Ref *sender)
{
	//check that the socket is != nullptr before sending or emitting events
	//the client should be nullptr either before initialization and connection or after disconnect
	if(_sioClient != nullptr) _sioClient->emit("echotest","[{\"name\":\"myname\",\"type\":\"mytype\"}]");

}

void SocketIOTest::onMenuTestEventEndpointClicked(cocos2d::Ref *sender)
{

	if(_sioEndpoint != nullptr) _sioEndpoint->emit("echotest","[{\"name\":\"myname\",\"type\":\"mytype\"}]");

}

void SocketIOTest::onMenuTestClientDisconnectClicked(cocos2d::Ref *sender)
{

	if(_sioClient != nullptr) _sioClient->disconnect();

}

void SocketIOTest::onMenuTestEndpointDisconnectClicked(cocos2d::Ref *sender)
{

	if(_sioEndpoint != nullptr) _sioEndpoint->disconnect();

}

// Delegate methods

void SocketIOTest::onConnect(network::SIOClient* client)
{
	log("SocketIOTest::onConnect called");

	std::stringstream s;
	s << client->getTag() << " connected!";	
	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTest::onMessage(network::SIOClient* client, const std::string& data)
{
	log("SocketIOTest::onMessage received: %s", data.c_str());
	
	std::stringstream s;
	s << client->getTag() << " received message with content: " << data.c_str();	
	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTest::onClose(network::SIOClient* client)
{
	log("SocketIOTest::onClose called");

	std::stringstream s;
	s << client->getTag() << " closed!";	
	_sioClientStatus->setString(s.str().c_str());

	//set the local pointer to nullptr or connect to another client
	//the client object will be released on its own after this method completes
	if(client == _sioClient) {
		
		_sioClient = nullptr;
	} else if(client == _sioEndpoint) {
		
		_sioEndpoint = nullptr;
	}
	
}

void SocketIOTest::onError(network::SIOClient* client, const std::string& data)
{
	log("SocketIOTest::onError received: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received error with content: " << data.c_str();	
	_sioClientStatus->setString(s.str().c_str());
}
