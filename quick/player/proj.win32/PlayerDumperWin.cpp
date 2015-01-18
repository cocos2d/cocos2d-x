
#include "stdafx.h"
#include "PlayerDumper.h"
#include "base/CCDirector.h"

LONG WINAPI handleException(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
	auto engine = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine();;
	if (engine)
	{
		engine->handleAssert("UncaughtException", 0, 0, 0);
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

void activePlayerDumper()
{
	SetUnhandledExceptionFilter(handleException);
}