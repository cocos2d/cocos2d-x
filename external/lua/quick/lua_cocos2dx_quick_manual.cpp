#include "lua_cocos2dx_quick_manual.hpp"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "LuaNodeManager.h"

static int tolua_Cocos2d_Node_isTouchEnabled(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchEnabled'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(self, false);
            bool tolua_ret = false;
            if (lnode) {
                tolua_ret = lnode->isTouchEnabled();
            }
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isTouchEnabled'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_setTouchEnabled(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* node = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
        bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
        if (!node) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEnabled'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(node, value);
            if (!lnode) {
                return 0;
            }
            lnode->setLuaTouchEnabled(value);
        }
    }
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTouchEnabled'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_isTouchSwallowEnabled(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchSwallowEnabled'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(self, false);
            bool tolua_ret = false;
            if (lnode) {
                tolua_ret = lnode->isTouchSwallowEnabled();
            }
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isTouchSwallowEnabled'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_setTouchSwallowEnabled(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
        bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchSwallowEnabled'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(self, true);
            if (!lnode) {
                return 0;
            }
            lnode->setTouchSwallowEnabled(value);
        }
    }
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTouchSwallowEnabled'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_isTouchCaptureEnabled(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchCaptureEnabled'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(self, false);
            bool tolua_ret = false;
            if (lnode) {
                tolua_ret = lnode->isTouchCaptureEnabled();
            }
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isTouchCaptureEnabled'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_setTouchCaptureEnabled(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
        bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchCaptureEnabled'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(self, true);
            if (!lnode) {
                return 0;
            }
            lnode->setTouchCaptureEnabled(value);
        }
    }
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTouchCaptureEnabled'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_setTouchMode(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
        int mode = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchMode'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(self, true);
            if (!lnode) {
                return 0;
            }
            lnode->setTouchMode(mode);
        }
    }
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTouchMode'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_getTouchMode(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchMode'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(self, false);
            int tolua_ret = LuaEventNode::modeTouchesOneByOne;
            if (lnode) {
                tolua_ret = lnode->getTouchMode();
            }
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getTouchMode'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_removeTouchEvent(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* node = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
        if (!node) tolua_error(tolua_S,"invalid 'self' in function 'removeTouchEvent'", nullptr);
#endif
        {
            auto mng = LuaNodeManager::getInstance();
            auto lnode = mng->getLuaNodeByNode(node, false);
            if (!lnode) {
                return 0;
            }
            lnode->setLuaTouchEnabled(false);
            lnode->detachNode();  //this LuaEventNode will be removed in TouchTargetNode
            mng->removeLuaNode(lnode);
        }
    }
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeTouchEvent'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_Node_getCascadeBoundingBox(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Node_getCascadeBoundingBox'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = utils::getCascadeBoundingBox(cobj);
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCascadeBoundingBox",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Node_getCascadeBoundingBox'.",&tolua_err);
#endif
    
    return 0;
}

static void extendNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.Node");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S, "isTouchEnabled");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_isTouchEnabled);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "setTouchEnabled");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_setTouchEnabled);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "isTouchSwallowEnabled");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_isTouchSwallowEnabled);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "setTouchSwallowEnabled");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_setTouchSwallowEnabled);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "isTouchCaptureEnabled");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_isTouchCaptureEnabled);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "setTouchCaptureEnabled");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_setTouchCaptureEnabled);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "setTouchMode");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_setTouchMode);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "getTouchMode");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_getTouchMode);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "removeTouchEvent");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_removeTouchEvent);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "getCascadeBoundingBox");
        lua_pushcfunction(tolua_S, lua_cocos2dx_Node_getCascadeBoundingBox);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_Cocos2d_Function_loadChunksFromZIP(lua_State* tolua_S)
{
    return LuaEngine::getInstance()->getLuaStack()->luaLoadChunksFromZIP(tolua_S);
}

static void extendFunctions(lua_State* tolua_S)
{
    tolua_module(tolua_S,"cc",0);
    tolua_beginmodule(tolua_S,"cc");
    tolua_function(tolua_S,"LuaLoadChunksFromZIP",tolua_Cocos2d_Function_loadChunksFromZIP);
    tolua_endmodule(tolua_S);
}

int register_all_quick_manual(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    extendFunctions(tolua_S);
    extendNode(tolua_S);

    CCLOG("Quick-Cocos2d-x C++ support ready.");
    
    return 0;
}

