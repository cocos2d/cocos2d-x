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

	virtual void onConnect(cocos2d::network::SIOClient* client);
    virtual void onMessage(cocos2d::network::SIOClient* client, const std::string& data);
    virtual void onClose(cocos2d::network::SIOClient* client);
    virtual void onError(cocos2d::network::SIOClient* client, const std::string& data);
	
	void onMenuSIOClientClicked(cocos2d::Ref *sender);
	void onMenuTestMessageClicked(cocos2d::Ref *sender);
	void onMenuTestEventClicked(cocos2d::Ref *sender);
	void onMenuTestClientDisconnectClicked(cocos2d::Ref *sender);

	void onMenuSIOEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestMessageEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestEventEndpointClicked(cocos2d::Ref *sender);
	void onMenuTestEndpointDisconnectClicked(cocos2d::Ref *sender);


	void testevent(cocos2d::network::SIOClient *client, const std::string& data);
	void echotest(cocos2d::network::SIOClient *client, const std::string& data);

    virtual std::string title() const override{ return "SocketIO Extension Test"; }

	cocos2d::network::SIOClient *_sioClient, *_sioEndpoint;

	cocos2d::Label *_sioClientStatus;
};

#endif /* defined(__TestCpp__SocketIOTest__) */
