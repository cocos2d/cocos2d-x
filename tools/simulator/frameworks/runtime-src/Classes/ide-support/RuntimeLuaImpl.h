//
//  RuntimeLuaImpl.h
//  Simulator
//
//

#ifndef __Simulator__RuntimeLuaImpl__
#define __Simulator__RuntimeLuaImpl__

#include "CodeIDESupport.h"
#include "cocos2d.h"

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)

#include "runtime/RuntimeProtocol.h"

class RuntimeLuaImpl : public RuntimeProtocol
{
public:
    static RuntimeLuaImpl *create();
    
    void onStartDebuger(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    void onReload(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    void startScript(const std::string& strDebugArg);
    
private:
    void init();
};

#endif // (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)

#endif /* defined(__Simulator__RuntimeLua__) */
