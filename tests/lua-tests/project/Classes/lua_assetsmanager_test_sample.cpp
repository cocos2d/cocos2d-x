#include "lua_assetsmanager_test_sample.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "scripting/lua-bindings/manual/tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif

USING_NS_CC;
USING_NS_CC_EXT;


static int lua_cocos2dx_createDownloadDir(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = lua_gettop(L);

    if (0 == argc)
    {
        std::string pathToSave = FileUtils::getInstance()->getWritablePath();
        pathToSave += "tmpdir";
        
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
        DIR *pDir = NULL;
        
        pDir = opendir (pathToSave.c_str());
        if (! pDir)
        {
            mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        }
#else
        if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
        {
            CreateDirectoryA(pathToSave.c_str(), 0);
        }
#endif
        tolua_pushstring(L, pathToSave.c_str());
        return 1;
    }
    
    CCLOG("'createDownloadDir' function wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
}

static int lua_cocos2dx_deleteDownloadDir(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = lua_gettop(L);
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 1, 0, &tolua_err)) goto tolua_lerror;
#endif
        std::string pathToSave = tolua_tostring(L, 1, "");

#if CC_TARGET_OS_TVOS
        // Not implemented. "system" is not present on tvOS
        CCLOG("'lua_cocos2dx_deleteDownloadDir' not implemented on tvOS");
        return 0;

#elif (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
        std::string command = "rm -r ";
        // Path may include space.
        command += "\"" + pathToSave + "\"";
        system(command.c_str());
#else
        std::string command = "rd /s /q ";
        // Path may include space.
        command += "\"" + pathToSave + "\"";
        system(command.c_str());
#endif
        return 0;
    }
    
    CCLOG("'resetDownloadDir' function wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'resetDownloadDir'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_addSearchPath(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = lua_gettop(L);
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 1, 0, &tolua_err) ||
            !tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        std::string pathToSave = tolua_tostring(L, 1, "");
        bool before           = tolua_toboolean(L, 2, 0);
        std::vector<std::string> searchPaths = FileUtils::getInstance()->getSearchPaths();
        if (before)
        {
            searchPaths.insert(searchPaths.begin(), pathToSave);
        }
        else
        {
            searchPaths.push_back(pathToSave);
        }
        
        FileUtils::getInstance()->setSearchPaths(searchPaths);
        
        return 0;
    }
    CCLOG("'addSearchPath' function wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addSearchPath'.",&tolua_err);
    return 0;
#endif
}

int register_assetsmanager_test_sample(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, NULL, 0);
    tolua_beginmodule(L, NULL);
    tolua_function(L, "createDownloadDir", lua_cocos2dx_createDownloadDir);
    tolua_function(L, "deleteDownloadDir", lua_cocos2dx_deleteDownloadDir);
    tolua_function(L, "addSearchPath", lua_cocos2dx_addSearchPath);
    tolua_endmodule(L);
    return 0;
}
