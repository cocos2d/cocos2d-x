
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
	AnySDKListener::getInstance()->callLuaFunction(m_luaFunction, "ads", msg);
}

void AdsListenerLua::onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points)
{
	AnySDKListener::getInstance()->callLuaFunction(m_luaFunction, "ads", "");
}

PayResultListenerLua::PayResultListenerLua()
{
}

PayResultListenerLua::~PayResultListenerLua()
{
}

void PayResultListenerLua::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
	AnySDKListener::getInstance()->callLuaFunction(m_luaFunction, "iap", msg);
}

PushActionListenerLua::PushActionListenerLua()
{
}

PushActionListenerLua::~PushActionListenerLua()
{

}

void PushActionListenerLua::onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction(m_luaFunction, "push", msg);
}

ShareResultListenerLua::ShareResultListenerLua()
{

}

ShareResultListenerLua::~ShareResultListenerLua()
{

}

void ShareResultListenerLua::onShareResult(ShareResultCode ret, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction(m_luaFunction, "share", msg);
}

SocialListenerLua::SocialListenerLua()
{

}

SocialListenerLua::~SocialListenerLua()
{

}

void SocialListenerLua::onSocialResult(SocialRetCode code, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction(m_luaFunction, "social", msg);
}

UserActionListenerLua::UserActionListenerLua()
{

}

UserActionListenerLua::~UserActionListenerLua()
{

}

void UserActionListenerLua::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
{
	AnySDKListener::getInstance()->callLuaFunction(m_luaFunction, "user", msg);
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
	releaseLuaFunction(luaFunction);
	m_luaFunction = luaFunction;
}

void AnySDKListener::callLuaFunction(int luaFunction, const char* protocolName, const char* jsonStr)
{
	cocos2d::LuaEngine *engine = cocos2d::LuaEngine::getInstance();
    cocos2d::LuaStack *stack = engine->getLuaStack();
    cocos2d::LuaBridge::pushLuaFunctionById(luaFunction);
    stack->pushString(protocolName);
    stack->pushString(jsonStr);
    stack->executeFunction(2);
}

void AnySDKListener::releaseLuaFunction(int luaFunction)
{
	if (0 == m_luaFunction)
	{
		return;
	}
	cocos2d::LuaBridge::releaseLuaFunctionById(m_luaFunction);
}


void AnySDKListener::setAdListener(int luaFunction, ProtocolAds* ads = NULL)
{
	if (NULL == ads)
	{
		ads = AgentManager::getInstance()->getAdsPlugin();
	}
	if (NULL == m_listenerAds)
	{
		m_listenerAds = new AdsListenerLua();
	}
	ads->setAdsListener(m_listenerAds);
	m_listenerAds->m_luaFunction = luaFunction;
}

void AnySDKListener::setIAPListener(int luaFunction, ProtocolIAP* iap = NULL)
{
	if (NULL == iap)
	{
		return;
	}

	if (NULL == m_listenerIAP)
	{
		m_listenerIAP = new PayResultListenerLua();
	}
	iap->setResultListener(m_listenerIAP);
	m_listenerIAP->m_luaFunction = luaFunction;
}

void AnySDKListener::setPushListener(int luaFunction,, ProtocolPush* push = NULL)
{
	if (NULL == push)
	{
		push = AgentManager::getInstance()->getPushPlugin();
	}
	if (NULL == m_listenerPush)
	{
		m_listenerPush = new PushActionListenerLua();
	}
	push->setActionListener(m_listenerPush);
	m_listenerPush->m_luaFunction = luaFunction;
}

void AnySDKListener::setShareListener(int luaFunction, ProtocolShare* share = NULL)
{
	if (NULL == share)
	{
		share = AgentManager::getInstance()->getSharePlugin();
	}
	if (NULL == m_listenerShare)
	{
		m_listenerShare = new ShareResultListenerLua();
	}
	share->setResultListener(m_listenerShare);
	m_listenerShare->m_luaFunction = luaFunction;
}

void AnySDKListener::setSocialListener(int luaFunction, ProtocolSocial* social = NULL)
{
	if (NULL == social)
	{
		social = AgentManager::getInstance()->getSocialPlugin();
	}
	if (NULL == m_listenerSocial)
	{
		m_listenerSocial = new ShareResultListenerLua();
	}
	social->setResultListener(m_listenerSocial);
	m_listenerSocial->m_luaFunction = luaFunction;
}

void AnySDKListener::setUserListener(int luaFunction, ProtocolUser* user = NULL)
{
	if (NULL == user)
	{
		user = AgentManager::getInstance()->getUserPlugin();
	}
	if (NULL == m_listenerUser)
	{
		m_listenerUser = new ShareResultListenerLua();
	}
	user->setResultListener(m_listenerUser);
	m_listenerUser->m_luaFunction = luaFunction;
}

}}
