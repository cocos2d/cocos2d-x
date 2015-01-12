//
//  RuntimeLuaImpl.cpp
//  Simulator
//
//

#include "RuntimeLuaImpl.h"

#include <cstdio>
#include <string>

#include "lua_debugger.h"
#include "CCLuaEngine.h"
#include "LuaBasicConversions.h"

#include "Runtime.h"
#include "ConfigParser.h"
#include "FileServer.h"

extern std::string g_projectPath; // Runtime.cpp

USING_NS_CC;
using namespace std;

static void resetLuaModule(const string& fileName)
{
    if (fileName.empty())
    {
        return;
    }
    auto engine = LuaEngine::getInstance();
    LuaStack* luaStack = engine->getLuaStack();
    lua_State* stack = luaStack->getLuaState();
    lua_getglobal(stack, "package");                         /* L: package */
    lua_getfield(stack, -1, "loaded");                       /* L: package loaded */
    lua_pushnil(stack);                                     /* L: lotable ?-.. nil */
    while (0 != lua_next(stack, -2))                     /* L: lotable ?-.. key value */
    {
        //CCLOG("%s - %s \n", tolua_tostring(stack, -2, ""), lua_typename(stack, lua_type(stack, -1)));
        std::string key = tolua_tostring(stack, -2, "");
        std::string tableKey = key;
        size_t found = tableKey.rfind(".lua");
        if (found != std::string::npos)
        tableKey = tableKey.substr(0, found);
        tableKey = replaceAll(tableKey, ".", "/");
        tableKey = replaceAll(tableKey, "\\", "/");
        tableKey.append(".lua");
        found = fileName.rfind(tableKey);
        if (0 == found || (found != std::string::npos && fileName.at(found - 1) == '/'))
        {
            lua_pushstring(stack, key.c_str());
            lua_pushnil(stack);
            if (lua_istable(stack, -5))
            {
                lua_settable(stack, -5);
            }
        }
        lua_pop(stack, 1);
    }
    lua_pop(stack, 2);
}

bool reloadScript(const string& file)
{
    auto director = Director::getInstance();
    FontFNT::purgeCachedData();
    if (director->getOpenGLView())
    {
        SpriteFrameCache::getInstance()->removeSpriteFrames();
        director->getTextureCache()->removeAllTextures();
    }
    FileUtils::getInstance()->purgeCachedEntries();
    string modulefile = file;
    
    if (! modulefile.empty())
    {
        resetLuaModule(modulefile);
    }
    else
    {
        modulefile = ConfigParser::getInstance()->getEntryFile().c_str();
    }
    
    auto engine = LuaEngine::getInstance();
    LuaStack* luaStack = engine->getLuaStack();
    std::string require = "require \'" + modulefile + "\'";
    return luaStack->executeString(require.c_str());
}

int lua_cocos2dx_runtime_addSearchPath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_FileUtils_addSearchPath'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1 || argc == 2)
    {
        std::string arg0;
        bool arg1 = false;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        
        if (argc == 2)
        {
            ok &= luaval_to_boolean(tolua_S, 3, &arg1);
        }
        
        if(!ok)
        return 0;
        
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
            cobj->addSearchPath(g_projectPath + arg0, arg1);
#endif
        }
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addSearchPath",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_FileUtils_addSearchPath'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_runtime_setSearchPaths(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_runtime_setSearchPaths'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::vector<std::string> vecPaths, writePaths;
        
        ok &= luaval_to_std_vector_string(tolua_S, 2, &vecPaths);
        if(!ok)
        return 0;
        std::vector<std::string> originPath; // for IOS platform.
        std::vector<std::string> projPath; // for Desktop platform.
        for (size_t i = 0; i < vecPaths.size(); i++)
        {
            if (!FileUtils::getInstance()->isAbsolutePath(vecPaths[i]))
            {
                originPath.push_back(vecPaths[i]); // for IOS platform.
                projPath.push_back(g_projectPath + vecPaths[i]); //for Desktop platform.
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
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSearchPaths",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_runtime_setSearchPaths'.",&tolua_err);
#endif
    
    return 0;
}

static void register_runtime_override_function(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.FileUtils");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1)){
        tolua_function(tolua_S,"addSearchPath",lua_cocos2dx_runtime_addSearchPath);
        tolua_function(tolua_S,"setSearchPaths",lua_cocos2dx_runtime_setSearchPaths);
    }
    lua_pop(tolua_S, 1);
}

static void luaScriptLoader(std::string strDebugArg)
{

}

////////////////////////////////////////

RuntimeLuaImpl *RuntimeLuaImpl::create()
{
    auto instance = new RuntimeLuaImpl();
    instance->init();
    return instance;
}

void RuntimeLuaImpl::onStartDebuger(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
    // Lua
    char szDebugArg[1024] = {0};
    sprintf(szDebugArg, "require('debugger')(%s,'%s')",dArgParse["debugcfg"].GetString(), "");
    startScript(szDebugArg);
    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
}

void RuntimeLuaImpl::onReload(const rapidjson::Document &dArgParse, rapidjson::Document &dReplyParse)
{
    // lua
    if (dArgParse.HasMember("modulefiles"))
    {
        rapidjson::Value bodyvalue(rapidjson::kObjectType);
        const rapidjson::Value& objectfiles = dArgParse["modulefiles"];
        for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
        {
            if (!reloadScript(objectfiles[i].GetString()))
            {
                bodyvalue.AddMember(objectfiles[i].GetString(), 1, dReplyParse.GetAllocator());
            }
        }
        if (0 == objectfiles.Size())
        {
            reloadScript("");
        }
        dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
    }
    
    dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
}

void RuntimeLuaImpl::startScript(const std::string& strDebugArg)
{
    auto engine = LuaEngine::getInstance();
    auto stack = engine->getLuaStack();
    
    const ProjectConfig &project = RuntimeEngine::getInstance()->getProjectConfig();
    
    // set search path
    string path = FileUtils::getInstance()->fullPathForFilename(project.getScriptFileRealPath().c_str());
    size_t pos;
    while ((pos = path.find_first_of("\\")) != std::string::npos)
    {
        path.replace(pos, 1, "/");
    }
    size_t p = path.find_last_of("/");
    string workdir;
    if (p != path.npos)
    {
        workdir = path.substr(0, p);
        stack->addSearchPath(workdir.c_str());
        FileUtils::getInstance()->addSearchPath(workdir);
    }
    
    // register lua engine
    if (!strDebugArg.empty())
    {
        // open debugger.lua module
        cocos2d::log("debug args = %s", strDebugArg.c_str());
        luaopen_lua_debugger(engine->getLuaStack()->getLuaState());
        engine->executeString(strDebugArg.c_str());
    }
    std::string code("require \"");
    code.append(ConfigParser::getInstance()->getEntryFile().c_str());
    code.append("\"");
    engine->executeString(code.c_str());
}

//
// private
//

void RuntimeLuaImpl::init()
{
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    register_runtime_override_function(engine->getLuaStack()->getLuaState());
}
