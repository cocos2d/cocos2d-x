//
//  RuntimeJsImpl.cpp
//  Simulator
//
//

#include "RuntimeJsImpl.h"

#include "cocos2d.h"        // 2dx engine

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)

#include "runtime/ConfigParser.h"   // config
#include "runtime/Runtime.h"
#include "runtime/FileServer.h"

// js
#include "js_module_register.h"


USING_NS_CC;

static const char *RUNTIME_JS_BOOT_SCRIPT = "script/jsb_boot.js";

static bool reloadScript(const string& file)
{
    auto director = Director::getInstance();
    FontFNT::purgeCachedData();
    if (director->getOpenGLView())
    {
        SpriteFrameCache::getInstance()->removeSpriteFrames();
        director->getTextureCache()->removeAllTextures();
    }
    FileUtils::getInstance()->purgeCachedEntries();
    
    //director->getScheduler()->unscheduleAll();
    //director->getScheduler()->scheduleUpdate(director->getActionManager(), Scheduler::PRIORITY_SYSTEM, false);
    
    string modulefile = file;
    if (modulefile.empty())
    {
        modulefile = ConfigParser::getInstance()->getEntryFile().c_str();
    }
    
    return ScriptingCore::getInstance()->runScript(modulefile.c_str());
}

bool runtime_FileUtils_addSearchPath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "cocos2dx_FileUtils_addSearchPath : Invalid Native Object");
    if (argc == 1 || argc == 2) {
        std::string arg0;
        bool arg1 = false;

        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "cocos2dx_FileUtils_addSearchPath : Error processing arguments");

        if (argc == 2)
        {
            arg1 = JS::ToBoolean(JS::RootedValue(cx, args.get(1)));
        }

        if (! FileUtils::getInstance()->isAbsolutePath(arg0))
        {
            // add write path to search path
            if (FileServer::getShareInstance()->getIsUsingWritePath())
            {
                cobj->addSearchPath(FileServer::getShareInstance()->getWritePath() + arg0, arg1);
            } else
            {
                cobj->addSearchPath(arg0, arg1);
            }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            // add project path to search path
            cobj->addSearchPath(RuntimeEngine::getInstance()->getRuntime()->getProjectPath() + arg0, arg1);
#endif
        }

        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "cocos2dx_FileUtils_addSearchPath : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool runtime_FileUtils_setSearchPaths(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_FileUtils_setSearchPaths : Invalid Native Object");
    if (argc == 1) {
        std::vector<std::string> vecPaths, writePaths;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &vecPaths);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_FileUtils_setSearchPaths : Error processing arguments");

        std::vector<std::string> originPath; // for IOS platform.
        std::vector<std::string> projPath; // for Desktop platform.
        for (int i = 0; i < vecPaths.size(); i++)
        {
            if (!FileUtils::getInstance()->isAbsolutePath(vecPaths[i]))
            {
                originPath.push_back(vecPaths[i]); // for IOS platform.
                projPath.push_back(RuntimeEngine::getInstance()->getRuntime()->getProjectPath()+vecPaths[i]); //for Desktop platform.
                writePaths.push_back(FileServer::getShareInstance()->getWritePath() + vecPaths[i]);
            }
        }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        vecPaths.insert(vecPaths.end(), projPath.begin(), projPath.end());
#endif
        if (FileServer::getShareInstance()->getIsUsingWritePath())
        {
            vecPaths.insert(vecPaths.end(), writePaths.begin(), writePaths.end());
        } else
        {
            vecPaths.insert(vecPaths.end(), originPath.begin(), originPath.end());
        }

        cobj->setSearchPaths(vecPaths);

        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_FileUtils_setSearchPaths : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

void register_FileUtils(JSContext *cx, JS::HandleObject global)
{
    JS::RootedValue  nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, global, "cc", &nsval);
    if (nsval == JSVAL_VOID) {
        return;
    } else {
        ns.set(nsval.toObjectOrNull());
    }

    JS::RootedObject proto(cx, jsb_cocos2d_FileUtils_prototype);
    JS_DefineFunction(cx, proto, "addSearchPath", runtime_FileUtils_addSearchPath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, proto, "setSearchPaths", runtime_FileUtils_setSearchPaths, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);
}

RuntimeJsImpl* RuntimeJsImpl::create()
{
    RuntimeJsImpl *instance = new RuntimeJsImpl();
    return instance;
}

bool RuntimeJsImpl::initJsEnv()
{
    if (_hasStarted)
    {
        return true;
    }
    
    js_module_register();
    ScriptingCore::getInstance()->addRegisterCallback(register_FileUtils);
    ScriptingCore::getInstance()->start();
    _hasStarted = true;

    ScriptEngineProtocol *engine = ScriptingCore::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    
    return true;
}

bool RuntimeJsImpl::startWithDebugger()
{
    initJsEnv();
    
    int debugPort = 5086;
#if(CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
    debugPort = ConfigParser::getInstance()->getDebugPort();
#endif
    ScriptingCore::getInstance()->enableDebugger(debugPort);
    
    return true;
}

void RuntimeJsImpl::startScript(const std::string& path)
{
    loadScriptFile(path);
}

void RuntimeJsImpl::onStartDebuger(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
    if (loadScriptFile(ConfigParser::getInstance()->getEntryFile()))
    {
        dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
    }
    else
    {
        dReplyParse.AddMember("code",1,dReplyParse.GetAllocator());
    }
}

void RuntimeJsImpl::onClearCompile(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
    if (dArgParse.HasMember("modulefiles") && dArgParse["modulefiles"].Size() != 0)
    {
        const rapidjson::Value& objectfiles = dArgParse["modulefiles"];
        for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
        {
            ScriptingCore::getInstance()->cleanScript(objectfiles[i].GetString());
        }
    }
    else
    {
        std::unordered_map<std::string, JSScript*> filenameScript = ScriptingCore::getInstance()->getFileScript();
        filenameScript.clear();
    }
    
    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
}

void RuntimeJsImpl::onPrecompile(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
    const rapidjson::Value& objectfiles = dArgParse["modulefiles"];
    for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
    {
        ScriptingCore::getInstance()->compileScript(objectfiles[i].GetString());
    }
    
    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
}

void RuntimeJsImpl::onReload(const rapidjson::Document &dArgParse, rapidjson::Document &dReplyParse)
{
    if (dArgParse.HasMember("modulefiles")){
        auto& allocator = dReplyParse.GetAllocator();
        rapidjson::Value bodyvalue(rapidjson::kObjectType);
        const rapidjson::Value& objectfiles = dArgParse["modulefiles"];
        for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++){
            if (!reloadScript(objectfiles[i].GetString())) {
                bodyvalue.AddMember(rapidjson::Value(objectfiles[i].GetString(), allocator)
                                    , rapidjson::Value(1)
                                    , allocator);
            }
        }
        if (0 == objectfiles.Size())
        {
            reloadScript("");
        }
        dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
    }else
    {
        reloadScript("");
    }
    
    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
}

void RuntimeJsImpl::onRemove(const std::string &filename)
{
    ScriptingCore::getInstance()->cleanScript(filename.c_str());
}

void RuntimeJsImpl::end()
{
    ScriptEngineManager::destroyInstance();
    RuntimeProtocol::end();
}

// private

RuntimeJsImpl::RuntimeJsImpl()
: _hasStarted(false)
{
}

bool RuntimeJsImpl::loadScriptFile(const std::string& path)
{
    std::string filepath = path;
    if (filepath.empty())
    {
        filepath = ConfigParser::getInstance()->getEntryFile();
    }
    CCLOG("------------------------------------------------");
    CCLOG("LOAD Js FILE: %s", filepath.c_str());
    CCLOG("------------------------------------------------");
    
    initJsEnv();
    auto engine = ScriptingCore::getInstance();
    engine->runScript(RUNTIME_JS_BOOT_SCRIPT);
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    return ScriptingCore::getInstance()->runScript(filepath.c_str());
}


#endif // (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)