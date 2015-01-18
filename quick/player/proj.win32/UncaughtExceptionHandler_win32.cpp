
#include "stdafx.h"
#include "UncaughtExceptionHandler.h"
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

void InstallUncaughtExceptionHandler()
{
	SetUnhandledExceptionFilter(handleException);
}