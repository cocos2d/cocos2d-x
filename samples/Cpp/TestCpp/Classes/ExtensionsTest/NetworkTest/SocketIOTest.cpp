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
using namespace network;

SocketIOTestLayer::SocketIOTestLayer(void)
	: _sioClient(NULL)
	, _sioEndpoint(NULL)
{
	//set the clients to NULL until we are ready to connect

	Size winSize = Director::getInstance()->getWinSize();
    
    const int MARGIN = 40;
    const int SPACE = 35;
    
    auto label = LabelTTF::create("SocketIO Extension Test", "Arial", 28);
    label->setPosition(Point(winSize.width / 2, winSize.height - MARGIN));
    addChild(label, 0);
    	
    auto menuRequest = Menu::create();
    menuRequest->setPosition(Point::ZERO);
    addChild(menuRequest);
    
    // Test to create basic client in the default namespace
    auto labelSIOClient = LabelTTF::create("Open SocketIO Client", "Arial", 22);
    auto itemSIOClient = MenuItemLabel::create(labelSIOClient, CC_CALLBACK_1(SocketIOTestLayer::onMenuSIOClientClicked, this));
	itemSIOClient->setPosition(Point(VisibleRect::left().x + labelSIOClient->getContentSize().width / 2 + 5, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSIOClient);

	// Test to create a client at the endpoint '/testpoint'
    auto labelSIOEndpoint = LabelTTF::create("Open SocketIO Endpoint", "Arial", 22);
    auto itemSIOEndpoint = MenuItemLabel::create(labelSIOEndpoint, CC_CALLBACK_1(SocketIOTestLayer::onMenuSIOEndpointClicked, this));
	itemSIOEndpoint->setPosition(Point(VisibleRect::right().x - labelSIOEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemSIOEndpoint);

	// Test sending message to default namespace
    auto labelTestMessage = LabelTTF::create("Send Test Message", "Arial", 22);
    auto itemTestMessage = MenuItemLabel::create(labelTestMessage, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestMessageClicked, this));
    itemTestMessage->setPosition(Point(VisibleRect::left().x + labelTestMessage->getContentSize().width / 2 + 5, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemTestMessage);

	// Test sending message to the endpoint '/testpoint'
    auto labelTestMessageEndpoint = LabelTTF::create("Test Endpoint Message", "Arial", 22);
    auto itemTestMessageEndpoint = MenuItemLabel::create(labelTestMessageEndpoint, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestMessageEndpointClicked, this));
    itemTestMessageEndpoint->setPosition(Point(VisibleRect::right().x - labelTestMessageEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemTestMessageEndpoint);

	// Test sending event 'echotest' to default namespace
    auto labelTestEvent = LabelTTF::create("Send Test Event", "Arial", 22);
    auto itemTestEvent = MenuItemLabel::create(labelTestEvent, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestEventClicked, this));
    itemTestEvent->setPosition(Point(VisibleRect::left().x + labelTestEvent->getContentSize().width / 2 + 5, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemTestEvent);

	// Test sending event 'echotest' to the endpoint '/testpoint'
    auto labelTestEventEndpoint = LabelTTF::create("Test Endpoint Event", "Arial", 22);
    auto itemTestEventEndpoint = MenuItemLabel::create(labelTestEventEndpoint, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestEventEndpointClicked, this));
    itemTestEventEndpoint->setPosition(Point(VisibleRect::right().x - labelTestEventEndpoint->getContentSize().width / 2 - 5, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemTestEventEndpoint);

	// Test disconnecting basic client
    auto labelTestClientDisconnect = LabelTTF::create("Disconnect Socket", "Arial", 22);
    auto itemClientDisconnect = MenuItemLabel::create(labelTestClientDisconnect, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestClientDisconnectClicked, this));
    itemClientDisconnect->setPosition(Point(VisibleRect::left().x + labelTestClientDisconnect->getContentSize().width / 2 + 5, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemClientDisconnect);

	// Test disconnecting the endpoint '/testpoint'
    auto labelTestEndpointDisconnect = LabelTTF::create("Disconnect Endpoint", "Arial", 22);
    auto itemTestEndpointDisconnect = MenuItemLabel::create(labelTestEndpointDisconnect, CC_CALLBACK_1(SocketIOTestLayer::onMenuTestEndpointDisconnectClicked, this));
    itemTestEndpointDisconnect->setPosition(Point(VisibleRect::right().x - labelTestEndpointDisconnect->getContentSize().width / 2 - 5, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemTestEndpointDisconnect);
    
	// Sahred Status Label
    _sioClientStatus = LabelTTF::create("Not connected...", "Arial", 14, Size(320, 100), TextHAlignment::LEFT);
    _sioClientStatus->setAnchorPoint(Point(0, 0));
    _sioClientStatus->setPosition(Point(VisibleRect::left().x, VisibleRect::rightBottom().y));
    this->addChild(_sioClientStatus);

	// Back Menu
    auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(SocketIOTestLayer::toExtensionsMainLayer, this));
    itemBack->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    auto menuBack = Menu::create(itemBack, NULL);
    menuBack->setPosition(Point::ZERO);
    addChild(menuBack);

}


SocketIOTestLayer::~SocketIOTestLayer(void)
{
}

//test event callback handlers, these will be registered with socket.io
void SocketIOTestLayer::testevent(SIOClient *client, const std::string& data) {

	log("SocketIOTestLayer::testevent called with data: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received event testevent with data: " << data.c_str();	

	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::echotest(SIOClient *client, const std::string& data) {

	log("SocketIOTestLayer::echotest called with data: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received event echotest with data: " << data.c_str();	

	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::toExtensionsMainLayer(cocos2d::Object *sender)
{
	ExtensionsTestScene *scene = new ExtensionsTestScene();
    scene->runThisTest();
    scene->release();

	if(_sioEndpoint) _sioEndpoint->disconnect();
	if(_sioClient) _sioClient->disconnect();

}

void SocketIOTestLayer::onMenuSIOClientClicked(cocos2d::Object *sender)
{
	//create a client by using this static method, url does not need to contain the protocol
	_sioClient = SocketIO::connect(*this, "ws://channon.us:3000");
	//you may set a tag for the client for reference in callbacks
	_sioClient->setTag("Test Client");

	//register event callbacks using the CC_CALLBACK_2() macro and passing the instance of the target class
	_sioClient->on("testevent", CC_CALLBACK_2(SocketIOTestLayer::testevent, this));
	_sioClient->on("echotest", CC_CALLBACK_2(SocketIOTestLayer::echotest, this));

}

void SocketIOTestLayer::onMenuSIOEndpointClicked(cocos2d::Object *sender)
{
	//repeat the same connection steps for the namespace "testpoint"
	_sioEndpoint = SocketIO::connect(*this, "ws://channon.us:3000/testpoint");
	//a tag to differentiate in shared callbacks
	_sioEndpoint->setTag("Test Endpoint");	

	//demonstrating how callbacks can be shared within a delegate
	_sioEndpoint->on("testevent", CC_CALLBACK_2(SocketIOTestLayer::testevent, this));
	_sioEndpoint->on("echotest", CC_CALLBACK_2(SocketIOTestLayer::echotest, this));

}

void SocketIOTestLayer::onMenuTestMessageClicked(cocos2d::Object *sender)
{
	//check that the socket is != NULL before sending or emitting events
	//the client should be NULL either before initialization and connection or after disconnect
	if(_sioClient != NULL) _sioClient->send("Hello Socket.IO!");

}

void SocketIOTestLayer::onMenuTestMessageEndpointClicked(cocos2d::Object *sender)
{

	if(_sioEndpoint != NULL) _sioEndpoint->send("Hello Socket.IO!");

}

void SocketIOTestLayer::onMenuTestEventClicked(cocos2d::Object *sender)
{
	//check that the socket is != NULL before sending or emitting events
	//the client should be NULL either before initialization and connection or after disconnect
	if(_sioClient != NULL) _sioClient->emit("echotest","[{\"name\":\"myname\",\"type\":\"mytype\"}]");

}

void SocketIOTestLayer::onMenuTestEventEndpointClicked(cocos2d::Object *sender)
{

	if(_sioEndpoint != NULL) _sioEndpoint->emit("echotest","[{\"name\":\"myname\",\"type\":\"mytype\"}]");

}

void SocketIOTestLayer::onMenuTestClientDisconnectClicked(cocos2d::Object *sender)
{

	if(_sioClient != NULL) _sioClient->disconnect();

}

void SocketIOTestLayer::onMenuTestEndpointDisconnectClicked(cocos2d::Object *sender)
{

	if(_sioEndpoint != NULL) _sioEndpoint->disconnect();

}

// Delegate methods

void SocketIOTestLayer::onConnect(network::SIOClient* client)
{
	log("SocketIOTestLayer::onConnect called");

	std::stringstream s;
	s << client->getTag() << " connected!";	
	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::onMessage(network::SIOClient* client, const std::string& data)
{
	log("SocketIOTestLayer::onMessage received: %s", data.c_str());
	
	std::stringstream s;
	s << client->getTag() << " received message with content: " << data.c_str();	
	_sioClientStatus->setString(s.str().c_str());

}

void SocketIOTestLayer::onClose(network::SIOClient* client)
{
	log("SocketIOTestLayer::onClose called");

	std::stringstream s;
	s << client->getTag() << " closed!";	
	_sioClientStatus->setString(s.str().c_str());

	//set the local pointer to NULL or connect to another client
	//the client object will be released on its own after this method completes
	if(client == _sioClient) {
		
		_sioClient = NULL;
	} else if(client == _sioEndpoint) {
		
		_sioEndpoint = NULL;
	}
	
}

void SocketIOTestLayer::onError(network::SIOClient* client, const std::string& data)
{
	log("SocketIOTestLayer::onError received: %s", data.c_str());

	std::stringstream s;
	s << client->getTag() << " received error with content: " << data.c_str();	
	_sioClientStatus->setString(s.str().c_str());
}



void runSocketIOTest()
{
    auto scene = Scene::create();
    auto layer = new SocketIOTestLayer();
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
    layer->release();
}
