//
//  RuntimeLuaImpl.h
//  Simulator
//
//

#ifndef __Simulator__RuntimeLuaImpl__
#define __Simulator__RuntimeLuaImpl__

#include "RuntimeProtocol.h"

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

#endif /* defined(__Simulator__RuntimeLua__) */
