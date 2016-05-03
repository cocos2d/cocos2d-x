#include "lua_pluginx_basic_conversions.h"

using namespace cocos2d::plugin;

namespace pluginx {

bool luaval_to_TIAPDeveloperInfo(lua_State* L, int lo, TIAPDeveloperInfo* outValue, const char* funcName)
{
    ValueMap ret;
    if (!luaval_to_ccvaluemap(L, lo, &ret, funcName)) return false;
    TIAPDeveloperInfo& dict = *outValue;
    for (auto e : ret) {
        dict[e.first] = e.second.asString();
    }
    return true;
}

bool luaval_to_TProductInfo(lua_State* L, int lo, cocos2d::plugin::TProductInfo* outValue, const char* funcName)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue, funcName);
}


bool luaval_to_FBInfo(lua_State* L, int lo, cocos2d::plugin::FacebookAgent::FBInfo* outValue, const char* funcName)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue, funcName);
}

bool luaval_to_TAdsDeveloperInfo(lua_State *L, int lo, TAdsDeveloperInfo* outValue)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue);
}

bool luaval_to_TAdsInfo(lua_State *L, int lo, TAdsInfo* outValue)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue);
}

bool luaval_to_TShareDeveloperInfo(lua_State *L, int lo, TShareDeveloperInfo* outValue)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue);
}

bool luaval_to_TShareInfo(lua_State *L, int lo, TShareInfo* outValue)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue);
}

bool luaval_to_TSocialDeveloperInfo(lua_State *L, int lo, cocos2d::plugin::TSocialDeveloperInfo* outValue)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue);
}

bool luaval_to_TAchievementInfo(lua_State *L, int lo, cocos2d::plugin::TAchievementInfo* outValue)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue);
}

bool luaval_to_TUserDeveloperInfo(lua_State *L, int lo, TUserDeveloperInfo* outValue)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue);
}

}// namespace pluginx {
