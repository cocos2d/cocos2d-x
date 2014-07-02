
#include "cocos2d.h"
#include "CCLuaBridge.h"
#include "AnySDKListener.h"


namespace anysdk { namespace framework {

AnySDKListener* AnySDKListener::gInstance = NULL;

AdsListenerLua::AdsListenerLua()
{
}

AdsListenerLua::~AdsListenerLua()
{
}

void AdsListenerLua::onAdsResult(AdsResultCode code, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction("ads", msg);
}

void AdsListenerLua::onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points)
{
	AnySDKListener::getInstance()->callLuaFunction("ads", "");
}

PayResultListenerLua::PayResultListenerLua()
{
}

PayResultListenerLua::~PayResultListenerLua()
{
}

void PayResultListenerLua::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
	AnySDKListener::getInstance()->callLuaFunction("iap", msg);
}

PushActionListenerLua::PushActionListenerLua()
{
}

PushActionListenerLua::~PushActionListenerLua()
{

}

void PushActionListenerLua::onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction("push", msg);
}

ShareResultListenerLua::ShareResultListenerLua()
{

}

ShareResultListenerLua::~ShareResultListenerLua()
{

}

void ShareResultListenerLua::onShareResult(ShareResultCode ret, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction("share", msg);
}

SocialListenerLua::SocialListenerLua()
{

}

SocialListenerLua::~SocialListenerLua()
{

}

void SocialListenerLua::onSocialResult(SocialRetCode code, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction("social", msg);
}

UserActionListenerLua::UserActionListenerLua()
{

}

UserActionListenerLua::~UserActionListenerLua()
{

}

void UserActionListenerLua::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction("user", msg);
}


AnySDKListener::AnySDKListener()
{

}

AnySDKListener::~AnySDKListener()
{

}

AnySDKListener* AnySDKListener::getInstance()
{
	if (NULL == gInstance)
	{
		gInstance = new AnySDKListener();
	}

	return gInstance;
}

void AnySDKListener::regListener(int luaFunction)
{
	if (0 != m_luaFunction)
	{
		cocos2d::LuaBridge::releaseLuaFunctionById(m_luaFunction);
	}
	m_luaFunction = luaFunction;
}

void AnySDKListener::callLuaFunction(const char* protocolName, const char* jsonStr)
{
	cocos2d::LuaEngine *engine = cocos2d::LuaEngine::getInstance();
    cocos2d::LuaStack *stack = engine->getLuaStack();
    cocos2d::LuaBridge::pushLuaFunctionById(m_luaFunction);
    stack->pushString(protocolName);
    stack->pushString(jsonStr);
    stack->executeFunction(2);
}

}}
