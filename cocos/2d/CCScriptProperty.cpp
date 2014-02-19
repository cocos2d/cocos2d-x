//
//  ScriptProperty.cpp
//  cocos2d_libs
//
//  Created by James Chen on 14-2-18.
//
//

#include "CCScriptProperty.h"
#include "CCScriptSupport.h"

NS_CC_BEGIN

ScriptProperty::ScriptProperty()
: _luaID(0)
, _owner(nullptr)
{
    static unsigned int uObjectCount = 0;
    _ID = ++uObjectCount;
}

ScriptProperty::~ScriptProperty()
{
    if (nullptr == _owner)
        return;
    
    // if the object is referenced by Lua engine, remove it
    if (_luaID)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptObjectByObject(this);
    }
    else
    {
        ScriptEngineProtocol* pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
        if (pEngine != nullptr && pEngine->getScriptType() == kScriptTypeJavascript)
        {
            CCASSERT(_owner != nullptr, "Owner should not be nullptr.");
            pEngine->removeScriptObjectByObject(this);
        }
    }
}

NS_CC_END
