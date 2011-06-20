#include "CCScriptSupport.h"

NS_CC_BEGIN;

CCScriptEngineManager::CCScriptEngineManager() : m_pScriptEngine(NULL) {}

CCScriptEngineManager::~CCScriptEngineManager() 
{
	CC_SAFE_DELETE(m_pScriptEngine);
}

void CCScriptEngineManager::registerScriptEngine(CCScriptEngineProtocol *pScriptEngine)
{
	this->m_pScriptEngine = pScriptEngine;
}

CCScriptEngineProtocol* CCScriptEngineManager::getScriptEngine()
{
	return m_pScriptEngine;
}

CCScriptEngineManager* CCScriptEngineManager::sharedScriptEngineManager()
{
	static CCScriptEngineManager scriptEngineManager;

	return &scriptEngineManager;
}

NS_CC_END;
