//
//  RuntimeJsImpl.h
//  Simulator
//
//

#ifndef __Simulator__RuntimeJsImpl__
#define __Simulator__RuntimeJsImpl__

#include "CodeIDESupport.h"
#include "cocos2d.h"

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
#include "runtime/RuntimeProtocol.h"

class RuntimeJsImpl : public RuntimeProtocol
{
public:
    static RuntimeJsImpl* create();
    
    void startScript(const std::string& file);
    void onStartDebuger(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    void onClearCompile(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    void onPrecompile(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    void onReload(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    void onRemove(const std::string &filename);
    void end();
    
    bool startWithDebugger();
private:
    RuntimeJsImpl();
    bool initJsEnv();
    bool loadScriptFile(const std::string& file);
    bool _hasStarted;
};

#endif // (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)

#endif /* defined(__Simulator__RuntimeLua__) */
