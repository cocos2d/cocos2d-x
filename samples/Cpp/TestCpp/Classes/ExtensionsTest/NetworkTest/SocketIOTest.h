//
//  SocketIOTest.h
//  TestCpp
//
//  Created by Chris Hannon on 6/26/13.
//
//
#ifndef __TestCpp__SocketIOTest__
#define __TestCpp__SocketIOTest__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/SocketIO.h"

class SocketIOTestLayer
	: public cc::Layer
	, public cc::extension::SocketIO::SIODelegate
{
public:
	SocketIOTestLayer(void);
	virtual ~SocketIOTestLayer(void);

	virtual void onConnect(cc::extension::SIOClient* client);
    virtual void onMessage(cc::extension::SIOClient* client, const std::string& data);
    virtual void onClose(cc::extension::SIOClient* client);
    virtual void onError(cc::extension::SIOClient* client, const std::string& data);

	void toExtensionsMainLayer(cc::Object *sender);
	
	void onMenuSIOClientClicked(cc::Object *sender);
	void onMenuTestMessageClicked(cc::Object *sender);
	void onMenuTestEventClicked(cc::Object *sender);
	void onMenuTestClientDisconnectClicked(cc::Object *sender);

	void onMenuSIOEndpointClicked(cc::Object *sender);
	void onMenuTestMessageEndpointClicked(cc::Object *sender);
	void onMenuTestEventEndpointClicked(cc::Object *sender);
	void onMenuTestEndpointDisconnectClicked(cc::Object *sender);


	void testevent(cc::extension::SIOClient *client, const std::string& data);
	void echotest(cc::extension::SIOClient *client, const std::string& data);

	cc::extension::SIOClient *_sioClient, *_sioEndpoint;

	cc::LabelTTF *_sioClientStatus;
};

void runSocketIOTest();

#endif /* defined(__TestCpp__SocketIOTest__) */