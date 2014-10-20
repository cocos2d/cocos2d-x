#include "lua_cocos2dx_studio_auto.hpp"
#include "CocoStudio.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_studio_ActionFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_getAction'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionFrame:getAction");

            if (!ok) { break; }
            cocostudio::ActionFrame* arg1;
            ok &= luaval_to_object<cocostudio::ActionFrame>(tolua_S, 3, "ccs.ActionFrame",&arg1);

            if (!ok) { break; }
            cocos2d::ActionInterval* ret = cobj->getAction(arg0, arg1);
            object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionFrame:getAction");

            if (!ok) { break; }
            cocos2d::ActionInterval* ret = cobj->getAction(arg0);
            object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionFrame:getAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_getAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_getFrameType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_getFrameType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getFrameType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:getFrameType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_getFrameType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_setFrameTime(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_setFrameTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionFrame:setFrameTime");
        if(!ok)
            return 0;
        cobj->setFrameTime(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setFrameTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_setFrameTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_setEasingType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_setEasingType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionFrame:setEasingType");
        if(!ok)
            return 0;
        cobj->setEasingType(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setEasingType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_setEasingType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_getFrameTime(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_getFrameTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFrameTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:getFrameTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_getFrameTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_getFrameIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_getFrameIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getFrameIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:getFrameIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_getFrameIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_setFrameType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_setFrameType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionFrame:setFrameType");
        if(!ok)
            return 0;
        cobj->setFrameType(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setFrameType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_setFrameType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_setFrameIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_setFrameIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionFrame:setFrameIndex");
        if(!ok)
            return 0;
        cobj->setFrameIndex(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setFrameIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_setFrameIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_setEasingParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_setEasingParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<float, std::allocator<float> > arg0;

        ok &= luaval_to_std_vector_float(tolua_S, 2, &arg0, "ccs.ActionFrame:setEasingParameter");
        if(!ok)
            return 0;
        cobj->setEasingParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setEasingParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_setEasingParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_getEasingType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFrame_getEasingType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getEasingType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:getEasingType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_getEasingType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ActionFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:ActionFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ActionFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionFrame");
    tolua_cclass(tolua_S,"ActionFrame","ccs.ActionFrame","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ActionFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ActionFrame_constructor);
        tolua_function(tolua_S,"getAction",lua_cocos2dx_studio_ActionFrame_getAction);
        tolua_function(tolua_S,"getFrameType",lua_cocos2dx_studio_ActionFrame_getFrameType);
        tolua_function(tolua_S,"setFrameTime",lua_cocos2dx_studio_ActionFrame_setFrameTime);
        tolua_function(tolua_S,"setEasingType",lua_cocos2dx_studio_ActionFrame_setEasingType);
        tolua_function(tolua_S,"getFrameTime",lua_cocos2dx_studio_ActionFrame_getFrameTime);
        tolua_function(tolua_S,"getFrameIndex",lua_cocos2dx_studio_ActionFrame_getFrameIndex);
        tolua_function(tolua_S,"setFrameType",lua_cocos2dx_studio_ActionFrame_setFrameType);
        tolua_function(tolua_S,"setFrameIndex",lua_cocos2dx_studio_ActionFrame_setFrameIndex);
        tolua_function(tolua_S,"setEasingParameter",lua_cocos2dx_studio_ActionFrame_setEasingParameter);
        tolua_function(tolua_S,"getEasingType",lua_cocos2dx_studio_ActionFrame_getEasingType);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ActionFrame).name();
    g_luaType[typeName] = "ccs.ActionFrame";
    g_typeCast["ActionFrame"] = "ccs.ActionFrame";
    return 1;
}

int lua_cocos2dx_studio_ActionMoveFrame_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionMoveFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionMoveFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionMoveFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionMoveFrame_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccs.ActionMoveFrame:setPosition");
        if(!ok)
            return 0;
        cobj->setPosition(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionMoveFrame:setPosition",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionMoveFrame_setPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionMoveFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionMoveFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionMoveFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionMoveFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionMoveFrame_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionMoveFrame:getAction");
        if(!ok)
            return 0;
        cocos2d::ActionInterval* ret = cobj->getAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionMoveFrame:getAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionMoveFrame_getAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionMoveFrame_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionMoveFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionMoveFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionMoveFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionMoveFrame_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Vec2 ret = cobj->getPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionMoveFrame:getPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionMoveFrame_getPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionMoveFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionMoveFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ActionMoveFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionMoveFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionMoveFrame:ActionMoveFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionMoveFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ActionMoveFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionMoveFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionMoveFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionMoveFrame");
    tolua_cclass(tolua_S,"ActionMoveFrame","ccs.ActionMoveFrame","ccs.ActionFrame",nullptr);

    tolua_beginmodule(tolua_S,"ActionMoveFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ActionMoveFrame_constructor);
        tolua_function(tolua_S,"setPosition",lua_cocos2dx_studio_ActionMoveFrame_setPosition);
        tolua_function(tolua_S,"getAction",lua_cocos2dx_studio_ActionMoveFrame_getAction);
        tolua_function(tolua_S,"getPosition",lua_cocos2dx_studio_ActionMoveFrame_getPosition);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ActionMoveFrame).name();
    g_luaType[typeName] = "ccs.ActionMoveFrame";
    g_typeCast["ActionMoveFrame"] = "ccs.ActionMoveFrame";
    return 1;
}

int lua_cocos2dx_studio_ActionScaleFrame_setScaleY(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionScaleFrame_setScaleY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionScaleFrame:setScaleY");
        if(!ok)
            return 0;
        cobj->setScaleY(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:setScaleY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionScaleFrame_setScaleY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionScaleFrame_setScaleX(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionScaleFrame_setScaleX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionScaleFrame:setScaleX");
        if(!ok)
            return 0;
        cobj->setScaleX(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:setScaleX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionScaleFrame_setScaleX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionScaleFrame_getScaleY(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionScaleFrame_getScaleY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getScaleY();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:getScaleY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionScaleFrame_getScaleY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionScaleFrame_getScaleX(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionScaleFrame_getScaleX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getScaleX();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:getScaleX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionScaleFrame_getScaleX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionScaleFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionScaleFrame_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionScaleFrame:getAction");
        if(!ok)
            return 0;
        cocos2d::ActionInterval* ret = cobj->getAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:getAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionScaleFrame_getAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionScaleFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ActionScaleFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionScaleFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:ActionScaleFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionScaleFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ActionScaleFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionScaleFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionScaleFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionScaleFrame");
    tolua_cclass(tolua_S,"ActionScaleFrame","ccs.ActionScaleFrame","ccs.ActionFrame",nullptr);

    tolua_beginmodule(tolua_S,"ActionScaleFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ActionScaleFrame_constructor);
        tolua_function(tolua_S,"setScaleY",lua_cocos2dx_studio_ActionScaleFrame_setScaleY);
        tolua_function(tolua_S,"setScaleX",lua_cocos2dx_studio_ActionScaleFrame_setScaleX);
        tolua_function(tolua_S,"getScaleY",lua_cocos2dx_studio_ActionScaleFrame_getScaleY);
        tolua_function(tolua_S,"getScaleX",lua_cocos2dx_studio_ActionScaleFrame_getScaleX);
        tolua_function(tolua_S,"getAction",lua_cocos2dx_studio_ActionScaleFrame_getAction);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ActionScaleFrame).name();
    g_luaType[typeName] = "ccs.ActionScaleFrame";
    g_typeCast["ActionScaleFrame"] = "ccs.ActionScaleFrame";
    return 1;
}

int lua_cocos2dx_studio_ActionRotationFrame_setRotation(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionRotationFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionRotationFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionRotationFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionRotationFrame_setRotation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionRotationFrame:setRotation");
        if(!ok)
            return 0;
        cobj->setRotation(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionRotationFrame:setRotation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionRotationFrame_setRotation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionRotationFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionRotationFrame* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionRotationFrame",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ActionRotationFrame*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionRotationFrame_getAction'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionRotationFrame:getAction");

            if (!ok) { break; }
            cocostudio::ActionFrame* arg1;
            ok &= luaval_to_object<cocostudio::ActionFrame>(tolua_S, 3, "ccs.ActionFrame",&arg1);

            if (!ok) { break; }
            cocos2d::ActionInterval* ret = cobj->getAction(arg0, arg1);
            object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionRotationFrame:getAction");

            if (!ok) { break; }
            cocos2d::ActionInterval* ret = cobj->getAction(arg0);
            object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionRotationFrame:getAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionRotationFrame_getAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionRotationFrame_getRotation(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionRotationFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionRotationFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionRotationFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionRotationFrame_getRotation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getRotation();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionRotationFrame:getRotation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionRotationFrame_getRotation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionRotationFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionRotationFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ActionRotationFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionRotationFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionRotationFrame:ActionRotationFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionRotationFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ActionRotationFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionRotationFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionRotationFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionRotationFrame");
    tolua_cclass(tolua_S,"ActionRotationFrame","ccs.ActionRotationFrame","ccs.ActionFrame",nullptr);

    tolua_beginmodule(tolua_S,"ActionRotationFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ActionRotationFrame_constructor);
        tolua_function(tolua_S,"setRotation",lua_cocos2dx_studio_ActionRotationFrame_setRotation);
        tolua_function(tolua_S,"getAction",lua_cocos2dx_studio_ActionRotationFrame_getAction);
        tolua_function(tolua_S,"getRotation",lua_cocos2dx_studio_ActionRotationFrame_getRotation);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ActionRotationFrame).name();
    g_luaType[typeName] = "ccs.ActionRotationFrame";
    g_typeCast["ActionRotationFrame"] = "ccs.ActionRotationFrame";
    return 1;
}

int lua_cocos2dx_studio_ActionFadeFrame_getOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFadeFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFadeFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFadeFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFadeFrame_getOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getOpacity();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFadeFrame:getOpacity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFadeFrame_getOpacity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFadeFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFadeFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFadeFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFadeFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFadeFrame_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionFadeFrame:getAction");
        if(!ok)
            return 0;
        cocos2d::ActionInterval* ret = cobj->getAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFadeFrame:getAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFadeFrame_getAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFadeFrame_setOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFadeFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFadeFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFadeFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionFadeFrame_setOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionFadeFrame:setOpacity");
        if(!ok)
            return 0;
        cobj->setOpacity(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFadeFrame:setOpacity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFadeFrame_setOpacity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionFadeFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFadeFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ActionFadeFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionFadeFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFadeFrame:ActionFadeFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionFadeFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ActionFadeFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionFadeFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionFadeFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionFadeFrame");
    tolua_cclass(tolua_S,"ActionFadeFrame","ccs.ActionFadeFrame","ccs.ActionFrame",nullptr);

    tolua_beginmodule(tolua_S,"ActionFadeFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ActionFadeFrame_constructor);
        tolua_function(tolua_S,"getOpacity",lua_cocos2dx_studio_ActionFadeFrame_getOpacity);
        tolua_function(tolua_S,"getAction",lua_cocos2dx_studio_ActionFadeFrame_getAction);
        tolua_function(tolua_S,"setOpacity",lua_cocos2dx_studio_ActionFadeFrame_setOpacity);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ActionFadeFrame).name();
    g_luaType[typeName] = "ccs.ActionFadeFrame";
    g_typeCast["ActionFadeFrame"] = "ccs.ActionFadeFrame";
    return 1;
}

int lua_cocos2dx_studio_ActionTintFrame_getColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionTintFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTintFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionTintFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTintFrame_getColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Color3B ret = cobj->getColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTintFrame:getColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTintFrame_getColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTintFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionTintFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTintFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionTintFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTintFrame_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionTintFrame:getAction");
        if(!ok)
            return 0;
        cocos2d::ActionInterval* ret = cobj->getAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTintFrame:getAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTintFrame_getAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTintFrame_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionTintFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTintFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionTintFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTintFrame_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccs.ActionTintFrame:setColor");
        if(!ok)
            return 0;
        cobj->setColor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTintFrame:setColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTintFrame_setColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTintFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionTintFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ActionTintFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionTintFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTintFrame:ActionTintFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTintFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ActionTintFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionTintFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionTintFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionTintFrame");
    tolua_cclass(tolua_S,"ActionTintFrame","ccs.ActionTintFrame","ccs.ActionFrame",nullptr);

    tolua_beginmodule(tolua_S,"ActionTintFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ActionTintFrame_constructor);
        tolua_function(tolua_S,"getColor",lua_cocos2dx_studio_ActionTintFrame_getColor);
        tolua_function(tolua_S,"getAction",lua_cocos2dx_studio_ActionTintFrame_getAction);
        tolua_function(tolua_S,"setColor",lua_cocos2dx_studio_ActionTintFrame_setColor);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ActionTintFrame).name();
    g_luaType[typeName] = "ccs.ActionTintFrame";
    g_typeCast["ActionTintFrame"] = "ccs.ActionTintFrame";
    return 1;
}

int lua_cocos2dx_studio_ActionObject_setCurrentTime(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_setCurrentTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionObject:setCurrentTime");
        if(!ok)
            return 0;
        cobj->setCurrentTime(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:setCurrentTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_setCurrentTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_pause(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->pause();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:pause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_pause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_setName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_setName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ActionObject:setName"); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->setName(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:setName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_setName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_setUnitTime(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_setUnitTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionObject:setUnitTime");
        if(!ok)
            return 0;
        cobj->setUnitTime(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:setUnitTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_setUnitTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_getTotalTime(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_getTotalTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getTotalTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getTotalTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_getTotalTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_getName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_getName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const char* ret = cobj->getName();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_getName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_stop(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->stop();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_play(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_play'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::CallFunc* arg0;
            ok &= luaval_to_object<cocos2d::CallFunc>(tolua_S, 2, "cc.CallFunc",&arg0);

            if (!ok) { break; }
            cobj->play(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj->play();
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionObject:play",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_play'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_getCurrentTime(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_getCurrentTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getCurrentTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getCurrentTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_getCurrentTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_removeActionNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_removeActionNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::ActionNode* arg0;

        ok &= luaval_to_object<cocostudio::ActionNode>(tolua_S, 2, "ccs.ActionNode",&arg0);
        if(!ok)
            return 0;
        cobj->removeActionNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:removeActionNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_removeActionNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_getLoop(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_getLoop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getLoop();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getLoop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_getLoop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_addActionNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_addActionNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::ActionNode* arg0;

        ok &= luaval_to_object<cocostudio::ActionNode>(tolua_S, 2, "ccs.ActionNode",&arg0);
        if(!ok)
            return 0;
        cobj->addActionNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:addActionNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_addActionNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_getUnitTime(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_getUnitTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getUnitTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getUnitTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_getUnitTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_isPlaying(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_isPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:isPlaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_isPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_updateToFrameByTime(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_updateToFrameByTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionObject:updateToFrameByTime");
        if(!ok)
            return 0;
        cobj->updateToFrameByTime(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:updateToFrameByTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_updateToFrameByTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_setLoop(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_setLoop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.ActionObject:setLoop");
        if(!ok)
            return 0;
        cobj->setLoop(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:setLoop",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_setLoop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_simulationActionUpdate(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionObject_simulationActionUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionObject:simulationActionUpdate");
        if(!ok)
            return 0;
        cobj->simulationActionUpdate(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:simulationActionUpdate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_simulationActionUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionObject_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ActionObject();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionObject");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:ActionObject",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionObject_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ActionObject_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionObject)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionObject(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionObject");
    tolua_cclass(tolua_S,"ActionObject","ccs.ActionObject","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ActionObject");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ActionObject_constructor);
        tolua_function(tolua_S,"setCurrentTime",lua_cocos2dx_studio_ActionObject_setCurrentTime);
        tolua_function(tolua_S,"pause",lua_cocos2dx_studio_ActionObject_pause);
        tolua_function(tolua_S,"setName",lua_cocos2dx_studio_ActionObject_setName);
        tolua_function(tolua_S,"setUnitTime",lua_cocos2dx_studio_ActionObject_setUnitTime);
        tolua_function(tolua_S,"getTotalTime",lua_cocos2dx_studio_ActionObject_getTotalTime);
        tolua_function(tolua_S,"getName",lua_cocos2dx_studio_ActionObject_getName);
        tolua_function(tolua_S,"stop",lua_cocos2dx_studio_ActionObject_stop);
        tolua_function(tolua_S,"play",lua_cocos2dx_studio_ActionObject_play);
        tolua_function(tolua_S,"getCurrentTime",lua_cocos2dx_studio_ActionObject_getCurrentTime);
        tolua_function(tolua_S,"removeActionNode",lua_cocos2dx_studio_ActionObject_removeActionNode);
        tolua_function(tolua_S,"getLoop",lua_cocos2dx_studio_ActionObject_getLoop);
        tolua_function(tolua_S,"addActionNode",lua_cocos2dx_studio_ActionObject_addActionNode);
        tolua_function(tolua_S,"getUnitTime",lua_cocos2dx_studio_ActionObject_getUnitTime);
        tolua_function(tolua_S,"isPlaying",lua_cocos2dx_studio_ActionObject_isPlaying);
        tolua_function(tolua_S,"updateToFrameByTime",lua_cocos2dx_studio_ActionObject_updateToFrameByTime);
        tolua_function(tolua_S,"setLoop",lua_cocos2dx_studio_ActionObject_setLoop);
        tolua_function(tolua_S,"simulationActionUpdate",lua_cocos2dx_studio_ActionObject_simulationActionUpdate);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ActionObject).name();
    g_luaType[typeName] = "ccs.ActionObject";
    g_typeCast["ActionObject"] = "ccs.ActionObject";
    return 1;
}

int lua_cocos2dx_studio_ActionManagerEx_playActionByName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionManagerEx* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ActionManagerEx*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionManagerEx_playActionByName'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ActionManagerEx:playActionByName"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "ccs.ActionManagerEx:playActionByName"); arg1 = arg1_tmp.c_str();

            if (!ok) { break; }
            cocos2d::CallFunc* arg2;
            ok &= luaval_to_object<cocos2d::CallFunc>(tolua_S, 4, "cc.CallFunc",&arg2);

            if (!ok) { break; }
            cocostudio::ActionObject* ret = cobj->playActionByName(arg0, arg1, arg2);
            object_to_luaval<cocostudio::ActionObject>(tolua_S, "ccs.ActionObject",(cocostudio::ActionObject*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ActionManagerEx:playActionByName"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "ccs.ActionManagerEx:playActionByName"); arg1 = arg1_tmp.c_str();

            if (!ok) { break; }
            cocostudio::ActionObject* ret = cobj->playActionByName(arg0, arg1);
            object_to_luaval<cocostudio::ActionObject>(tolua_S, "ccs.ActionObject",(cocostudio::ActionObject*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionManagerEx:playActionByName",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionManagerEx_playActionByName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionManagerEx_getActionByName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionManagerEx_getActionByName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ActionManagerEx:getActionByName"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "ccs.ActionManagerEx:getActionByName"); arg1 = arg1_tmp.c_str();
        if(!ok)
            return 0;
        cocostudio::ActionObject* ret = cobj->getActionByName(arg0, arg1);
        object_to_luaval<cocostudio::ActionObject>(tolua_S, "ccs.ActionObject",(cocostudio::ActionObject*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionManagerEx:getActionByName",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionManagerEx_getActionByName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionManagerEx_releaseActions(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionManagerEx_releaseActions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->releaseActions();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionManagerEx:releaseActions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionManagerEx_releaseActions'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionManagerEx_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ActionManagerEx::destroyInstance();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionManagerEx:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionManagerEx_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ActionManagerEx_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ActionManagerEx* ret = cocostudio::ActionManagerEx::getInstance();
        object_to_luaval<cocostudio::ActionManagerEx>(tolua_S, "ccs.ActionManagerEx",(cocostudio::ActionManagerEx*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionManagerEx:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionManagerEx_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_ActionManagerEx_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionManagerEx)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionManagerEx(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionManagerEx");
    tolua_cclass(tolua_S,"ActionManagerEx","ccs.ActionManagerEx","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ActionManagerEx");
        tolua_function(tolua_S,"playActionByName",lua_cocos2dx_studio_ActionManagerEx_playActionByName);
        tolua_function(tolua_S,"getActionByName",lua_cocos2dx_studio_ActionManagerEx_getActionByName);
        tolua_function(tolua_S,"releaseActions",lua_cocos2dx_studio_ActionManagerEx_releaseActions);
        tolua_function(tolua_S,"destroyInstance", lua_cocos2dx_studio_ActionManagerEx_destroyInstance);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_studio_ActionManagerEx_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ActionManagerEx).name();
    g_luaType[typeName] = "ccs.ActionManagerEx";
    g_typeCast["ActionManagerEx"] = "ccs.ActionManagerEx";
    return 1;
}

int lua_cocos2dx_studio_BaseData_getColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BaseData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BaseData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::BaseData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_BaseData_getColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Color4B ret = cobj->getColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BaseData:getColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BaseData_getColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_BaseData_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BaseData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BaseData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::BaseData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_BaseData_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccs.BaseData:setColor");
        if(!ok)
            return 0;
        cobj->setColor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BaseData:setColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BaseData_setColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_BaseData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.BaseData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::BaseData* ret = cocostudio::BaseData::create();
        object_to_luaval<cocostudio::BaseData>(tolua_S, "ccs.BaseData",(cocostudio::BaseData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.BaseData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BaseData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_BaseData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BaseData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::BaseData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.BaseData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BaseData:BaseData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BaseData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_BaseData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BaseData)");
    return 0;
}

int lua_register_cocos2dx_studio_BaseData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.BaseData");
    tolua_cclass(tolua_S,"BaseData","ccs.BaseData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"BaseData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_BaseData_constructor);
        tolua_function(tolua_S,"getColor",lua_cocos2dx_studio_BaseData_getColor);
        tolua_function(tolua_S,"setColor",lua_cocos2dx_studio_BaseData_setColor);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_BaseData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::BaseData).name();
    g_luaType[typeName] = "ccs.BaseData";
    g_typeCast["BaseData"] = "ccs.BaseData";
    return 1;
}

int lua_cocos2dx_studio_DisplayData_copy(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayData_copy'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::DisplayData* arg0;

        ok &= luaval_to_object<cocostudio::DisplayData>(tolua_S, 2, "ccs.DisplayData",&arg0);
        if(!ok)
            return 0;
        cobj->copy(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayData:copy",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayData_copy'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayData_changeDisplayToTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.DisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.DisplayData:changeDisplayToTexture");
        if(!ok)
            return 0;
        const std::string ret = cocostudio::DisplayData::changeDisplayToTexture(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.DisplayData:changeDisplayToTexture",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayData_changeDisplayToTexture'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_DisplayData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.DisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::DisplayData* ret = cocostudio::DisplayData::create();
        object_to_luaval<cocostudio::DisplayData>(tolua_S, "ccs.DisplayData",(cocostudio::DisplayData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.DisplayData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_DisplayData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::DisplayData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.DisplayData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayData:DisplayData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_DisplayData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (DisplayData)");
    return 0;
}

int lua_register_cocos2dx_studio_DisplayData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.DisplayData");
    tolua_cclass(tolua_S,"DisplayData","ccs.DisplayData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"DisplayData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_DisplayData_constructor);
        tolua_function(tolua_S,"copy",lua_cocos2dx_studio_DisplayData_copy);
        tolua_function(tolua_S,"changeDisplayToTexture", lua_cocos2dx_studio_DisplayData_changeDisplayToTexture);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_DisplayData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::DisplayData).name();
    g_luaType[typeName] = "ccs.DisplayData";
    g_typeCast["DisplayData"] = "ccs.DisplayData";
    return 1;
}

int lua_cocos2dx_studio_SpriteDisplayData_copy(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SpriteDisplayData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SpriteDisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::SpriteDisplayData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SpriteDisplayData_copy'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::DisplayData* arg0;

        ok &= luaval_to_object<cocostudio::DisplayData>(tolua_S, 2, "ccs.DisplayData",&arg0);
        if(!ok)
            return 0;
        cobj->copy(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SpriteDisplayData:copy",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SpriteDisplayData_copy'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SpriteDisplayData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.SpriteDisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::SpriteDisplayData* ret = cocostudio::SpriteDisplayData::create();
        object_to_luaval<cocostudio::SpriteDisplayData>(tolua_S, "ccs.SpriteDisplayData",(cocostudio::SpriteDisplayData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SpriteDisplayData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SpriteDisplayData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_SpriteDisplayData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SpriteDisplayData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::SpriteDisplayData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.SpriteDisplayData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SpriteDisplayData:SpriteDisplayData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SpriteDisplayData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_SpriteDisplayData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SpriteDisplayData)");
    return 0;
}

int lua_register_cocos2dx_studio_SpriteDisplayData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.SpriteDisplayData");
    tolua_cclass(tolua_S,"SpriteDisplayData","ccs.SpriteDisplayData","ccs.DisplayData",nullptr);

    tolua_beginmodule(tolua_S,"SpriteDisplayData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_SpriteDisplayData_constructor);
        tolua_function(tolua_S,"copy",lua_cocos2dx_studio_SpriteDisplayData_copy);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_SpriteDisplayData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::SpriteDisplayData).name();
    g_luaType[typeName] = "ccs.SpriteDisplayData";
    g_typeCast["SpriteDisplayData"] = "ccs.SpriteDisplayData";
    return 1;
}

int lua_cocos2dx_studio_ArmatureDisplayData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ArmatureDisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ArmatureDisplayData* ret = cocostudio::ArmatureDisplayData::create();
        object_to_luaval<cocostudio::ArmatureDisplayData>(tolua_S, "ccs.ArmatureDisplayData",(cocostudio::ArmatureDisplayData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureDisplayData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDisplayData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ArmatureDisplayData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDisplayData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ArmatureDisplayData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ArmatureDisplayData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDisplayData:ArmatureDisplayData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDisplayData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ArmatureDisplayData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ArmatureDisplayData)");
    return 0;
}

int lua_register_cocos2dx_studio_ArmatureDisplayData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ArmatureDisplayData");
    tolua_cclass(tolua_S,"ArmatureDisplayData","ccs.ArmatureDisplayData","ccs.DisplayData",nullptr);

    tolua_beginmodule(tolua_S,"ArmatureDisplayData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ArmatureDisplayData_constructor);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ArmatureDisplayData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ArmatureDisplayData).name();
    g_luaType[typeName] = "ccs.ArmatureDisplayData";
    g_typeCast["ArmatureDisplayData"] = "ccs.ArmatureDisplayData";
    return 1;
}

int lua_cocos2dx_studio_ParticleDisplayData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ParticleDisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ParticleDisplayData* ret = cocostudio::ParticleDisplayData::create();
        object_to_luaval<cocostudio::ParticleDisplayData>(tolua_S, "ccs.ParticleDisplayData",(cocostudio::ParticleDisplayData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ParticleDisplayData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ParticleDisplayData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ParticleDisplayData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ParticleDisplayData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ParticleDisplayData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ParticleDisplayData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ParticleDisplayData:ParticleDisplayData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ParticleDisplayData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ParticleDisplayData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ParticleDisplayData)");
    return 0;
}

int lua_register_cocos2dx_studio_ParticleDisplayData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ParticleDisplayData");
    tolua_cclass(tolua_S,"ParticleDisplayData","ccs.ParticleDisplayData","ccs.DisplayData",nullptr);

    tolua_beginmodule(tolua_S,"ParticleDisplayData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ParticleDisplayData_constructor);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ParticleDisplayData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ParticleDisplayData).name();
    g_luaType[typeName] = "ccs.ParticleDisplayData";
    g_typeCast["ParticleDisplayData"] = "ccs.ParticleDisplayData";
    return 1;
}

int lua_cocos2dx_studio_BoneData_getDisplayData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BoneData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::BoneData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_BoneData_getDisplayData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.BoneData:getDisplayData");
        if(!ok)
            return 0;
        cocostudio::DisplayData* ret = cobj->getDisplayData(arg0);
        object_to_luaval<cocostudio::DisplayData>(tolua_S, "ccs.DisplayData",(cocostudio::DisplayData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneData:getDisplayData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BoneData_getDisplayData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_BoneData_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BoneData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::BoneData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_BoneData_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneData:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BoneData_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_BoneData_addDisplayData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BoneData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::BoneData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_BoneData_addDisplayData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::DisplayData* arg0;

        ok &= luaval_to_object<cocostudio::DisplayData>(tolua_S, 2, "ccs.DisplayData",&arg0);
        if(!ok)
            return 0;
        cobj->addDisplayData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneData:addDisplayData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BoneData_addDisplayData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_BoneData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.BoneData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::BoneData* ret = cocostudio::BoneData::create();
        object_to_luaval<cocostudio::BoneData>(tolua_S, "ccs.BoneData",(cocostudio::BoneData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.BoneData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BoneData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_BoneData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BoneData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::BoneData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.BoneData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneData:BoneData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BoneData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_BoneData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BoneData)");
    return 0;
}

int lua_register_cocos2dx_studio_BoneData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.BoneData");
    tolua_cclass(tolua_S,"BoneData","ccs.BoneData","ccs.BaseData",nullptr);

    tolua_beginmodule(tolua_S,"BoneData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_BoneData_constructor);
        tolua_function(tolua_S,"getDisplayData",lua_cocos2dx_studio_BoneData_getDisplayData);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_BoneData_init);
        tolua_function(tolua_S,"addDisplayData",lua_cocos2dx_studio_BoneData_addDisplayData);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_BoneData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::BoneData).name();
    g_luaType[typeName] = "ccs.BoneData";
    g_typeCast["BoneData"] = "ccs.BoneData";
    return 1;
}

int lua_cocos2dx_studio_ArmatureData_addBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureData_addBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::BoneData* arg0;

        ok &= luaval_to_object<cocostudio::BoneData>(tolua_S, 2, "ccs.BoneData",&arg0);
        if(!ok)
            return 0;
        cobj->addBoneData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureData:addBoneData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureData_addBoneData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureData_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureData_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureData:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureData_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureData_getBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureData_getBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureData:getBoneData");
        if(!ok)
            return 0;
        cocostudio::BoneData* ret = cobj->getBoneData(arg0);
        object_to_luaval<cocostudio::BoneData>(tolua_S, "ccs.BoneData",(cocostudio::BoneData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureData:getBoneData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureData_getBoneData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ArmatureData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ArmatureData* ret = cocostudio::ArmatureData::create();
        object_to_luaval<cocostudio::ArmatureData>(tolua_S, "ccs.ArmatureData",(cocostudio::ArmatureData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ArmatureData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ArmatureData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ArmatureData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureData:ArmatureData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ArmatureData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ArmatureData)");
    return 0;
}

int lua_register_cocos2dx_studio_ArmatureData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ArmatureData");
    tolua_cclass(tolua_S,"ArmatureData","ccs.ArmatureData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ArmatureData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ArmatureData_constructor);
        tolua_function(tolua_S,"addBoneData",lua_cocos2dx_studio_ArmatureData_addBoneData);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_ArmatureData_init);
        tolua_function(tolua_S,"getBoneData",lua_cocos2dx_studio_ArmatureData_getBoneData);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ArmatureData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ArmatureData).name();
    g_luaType[typeName] = "ccs.ArmatureData";
    g_typeCast["ArmatureData"] = "ccs.ArmatureData";
    return 1;
}

int lua_cocos2dx_studio_FrameData_copy(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::FrameData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.FrameData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::FrameData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_FrameData_copy'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const cocostudio::BaseData* arg0;

        ok &= luaval_to_object<const cocostudio::BaseData>(tolua_S, 2, "ccs.BaseData",&arg0);
        if(!ok)
            return 0;
        cobj->copy(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.FrameData:copy",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_FrameData_copy'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_FrameData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.FrameData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::FrameData* ret = cocostudio::FrameData::create();
        object_to_luaval<cocostudio::FrameData>(tolua_S, "ccs.FrameData",(cocostudio::FrameData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.FrameData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_FrameData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_FrameData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::FrameData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::FrameData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.FrameData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.FrameData:FrameData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_FrameData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_FrameData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (FrameData)");
    return 0;
}

int lua_register_cocos2dx_studio_FrameData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.FrameData");
    tolua_cclass(tolua_S,"FrameData","ccs.FrameData","ccs.BaseData",nullptr);

    tolua_beginmodule(tolua_S,"FrameData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_FrameData_constructor);
        tolua_function(tolua_S,"copy",lua_cocos2dx_studio_FrameData_copy);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_FrameData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::FrameData).name();
    g_luaType[typeName] = "ccs.FrameData";
    g_typeCast["FrameData"] = "ccs.FrameData";
    return 1;
}

int lua_cocos2dx_studio_MovementBoneData_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementBoneData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.MovementBoneData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::MovementBoneData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_MovementBoneData_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementBoneData:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementBoneData_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_MovementBoneData_getFrameData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementBoneData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.MovementBoneData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::MovementBoneData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_MovementBoneData_getFrameData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.MovementBoneData:getFrameData");
        if(!ok)
            return 0;
        cocostudio::FrameData* ret = cobj->getFrameData(arg0);
        object_to_luaval<cocostudio::FrameData>(tolua_S, "ccs.FrameData",(cocostudio::FrameData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementBoneData:getFrameData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementBoneData_getFrameData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_MovementBoneData_addFrameData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementBoneData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.MovementBoneData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::MovementBoneData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_MovementBoneData_addFrameData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::FrameData* arg0;

        ok &= luaval_to_object<cocostudio::FrameData>(tolua_S, 2, "ccs.FrameData",&arg0);
        if(!ok)
            return 0;
        cobj->addFrameData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementBoneData:addFrameData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementBoneData_addFrameData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_MovementBoneData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.MovementBoneData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::MovementBoneData* ret = cocostudio::MovementBoneData::create();
        object_to_luaval<cocostudio::MovementBoneData>(tolua_S, "ccs.MovementBoneData",(cocostudio::MovementBoneData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.MovementBoneData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementBoneData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_MovementBoneData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementBoneData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::MovementBoneData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.MovementBoneData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementBoneData:MovementBoneData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementBoneData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_MovementBoneData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MovementBoneData)");
    return 0;
}

int lua_register_cocos2dx_studio_MovementBoneData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.MovementBoneData");
    tolua_cclass(tolua_S,"MovementBoneData","ccs.MovementBoneData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"MovementBoneData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_MovementBoneData_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_MovementBoneData_init);
        tolua_function(tolua_S,"getFrameData",lua_cocos2dx_studio_MovementBoneData_getFrameData);
        tolua_function(tolua_S,"addFrameData",lua_cocos2dx_studio_MovementBoneData_addFrameData);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_MovementBoneData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::MovementBoneData).name();
    g_luaType[typeName] = "ccs.MovementBoneData";
    g_typeCast["MovementBoneData"] = "ccs.MovementBoneData";
    return 1;
}

int lua_cocos2dx_studio_MovementData_getMovementBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.MovementData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::MovementData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_MovementData_getMovementBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.MovementData:getMovementBoneData");
        if(!ok)
            return 0;
        cocostudio::MovementBoneData* ret = cobj->getMovementBoneData(arg0);
        object_to_luaval<cocostudio::MovementBoneData>(tolua_S, "ccs.MovementBoneData",(cocostudio::MovementBoneData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementData:getMovementBoneData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementData_getMovementBoneData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_MovementData_addMovementBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.MovementData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::MovementData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_MovementData_addMovementBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::MovementBoneData* arg0;

        ok &= luaval_to_object<cocostudio::MovementBoneData>(tolua_S, 2, "ccs.MovementBoneData",&arg0);
        if(!ok)
            return 0;
        cobj->addMovementBoneData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementData:addMovementBoneData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementData_addMovementBoneData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_MovementData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.MovementData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::MovementData* ret = cocostudio::MovementData::create();
        object_to_luaval<cocostudio::MovementData>(tolua_S, "ccs.MovementData",(cocostudio::MovementData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.MovementData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_MovementData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::MovementData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.MovementData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementData:MovementData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_MovementData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_MovementData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MovementData)");
    return 0;
}

int lua_register_cocos2dx_studio_MovementData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.MovementData");
    tolua_cclass(tolua_S,"MovementData","ccs.MovementData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"MovementData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_MovementData_constructor);
        tolua_function(tolua_S,"getMovementBoneData",lua_cocos2dx_studio_MovementData_getMovementBoneData);
        tolua_function(tolua_S,"addMovementBoneData",lua_cocos2dx_studio_MovementData_addMovementBoneData);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_MovementData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::MovementData).name();
    g_luaType[typeName] = "ccs.MovementData";
    g_typeCast["MovementData"] = "ccs.MovementData";
    return 1;
}

int lua_cocos2dx_studio_AnimationData_getMovement(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::AnimationData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AnimationData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::AnimationData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_AnimationData_getMovement'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.AnimationData:getMovement");
        if(!ok)
            return 0;
        cocostudio::MovementData* ret = cobj->getMovement(arg0);
        object_to_luaval<cocostudio::MovementData>(tolua_S, "ccs.MovementData",(cocostudio::MovementData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnimationData:getMovement",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnimationData_getMovement'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_AnimationData_getMovementCount(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::AnimationData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AnimationData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::AnimationData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_AnimationData_getMovementCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ssize_t ret = cobj->getMovementCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnimationData:getMovementCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnimationData_getMovementCount'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_AnimationData_addMovement(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::AnimationData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AnimationData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::AnimationData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_AnimationData_addMovement'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::MovementData* arg0;

        ok &= luaval_to_object<cocostudio::MovementData>(tolua_S, 2, "ccs.MovementData",&arg0);
        if(!ok)
            return 0;
        cobj->addMovement(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnimationData:addMovement",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnimationData_addMovement'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_AnimationData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.AnimationData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::AnimationData* ret = cocostudio::AnimationData::create();
        object_to_luaval<cocostudio::AnimationData>(tolua_S, "ccs.AnimationData",(cocostudio::AnimationData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.AnimationData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnimationData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_AnimationData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::AnimationData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::AnimationData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.AnimationData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnimationData:AnimationData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnimationData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_AnimationData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AnimationData)");
    return 0;
}

int lua_register_cocos2dx_studio_AnimationData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.AnimationData");
    tolua_cclass(tolua_S,"AnimationData","ccs.AnimationData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"AnimationData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_AnimationData_constructor);
        tolua_function(tolua_S,"getMovement",lua_cocos2dx_studio_AnimationData_getMovement);
        tolua_function(tolua_S,"getMovementCount",lua_cocos2dx_studio_AnimationData_getMovementCount);
        tolua_function(tolua_S,"addMovement",lua_cocos2dx_studio_AnimationData_addMovement);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_AnimationData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::AnimationData).name();
    g_luaType[typeName] = "ccs.AnimationData";
    g_typeCast["AnimationData"] = "ccs.AnimationData";
    return 1;
}

int lua_cocos2dx_studio_ContourData_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ContourData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ContourData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ContourData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ContourData_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ContourData:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ContourData_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ContourData_addVertex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ContourData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ContourData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ContourData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ContourData_addVertex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccs.ContourData:addVertex");
        if(!ok)
            return 0;
        cobj->addVertex(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ContourData:addVertex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ContourData_addVertex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ContourData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ContourData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ContourData* ret = cocostudio::ContourData::create();
        object_to_luaval<cocostudio::ContourData>(tolua_S, "ccs.ContourData",(cocostudio::ContourData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ContourData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ContourData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ContourData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ContourData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ContourData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ContourData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ContourData:ContourData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ContourData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ContourData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ContourData)");
    return 0;
}

int lua_register_cocos2dx_studio_ContourData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ContourData");
    tolua_cclass(tolua_S,"ContourData","ccs.ContourData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ContourData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ContourData_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_ContourData_init);
        tolua_function(tolua_S,"addVertex",lua_cocos2dx_studio_ContourData_addVertex);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ContourData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ContourData).name();
    g_luaType[typeName] = "ccs.ContourData";
    g_typeCast["ContourData"] = "ccs.ContourData";
    return 1;
}

int lua_cocos2dx_studio_TextureData_getContourData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::TextureData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.TextureData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::TextureData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_TextureData_getContourData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.TextureData:getContourData");
        if(!ok)
            return 0;
        cocostudio::ContourData* ret = cobj->getContourData(arg0);
        object_to_luaval<cocostudio::ContourData>(tolua_S, "ccs.ContourData",(cocostudio::ContourData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureData:getContourData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureData_getContourData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_TextureData_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::TextureData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.TextureData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::TextureData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_TextureData_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureData:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureData_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_TextureData_addContourData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::TextureData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.TextureData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::TextureData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_TextureData_addContourData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::ContourData* arg0;

        ok &= luaval_to_object<cocostudio::ContourData>(tolua_S, 2, "ccs.ContourData",&arg0);
        if(!ok)
            return 0;
        cobj->addContourData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureData:addContourData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureData_addContourData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_TextureData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.TextureData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::TextureData* ret = cocostudio::TextureData::create();
        object_to_luaval<cocostudio::TextureData>(tolua_S, "ccs.TextureData",(cocostudio::TextureData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.TextureData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_TextureData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::TextureData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::TextureData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.TextureData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureData:TextureData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_TextureData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TextureData)");
    return 0;
}

int lua_register_cocos2dx_studio_TextureData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.TextureData");
    tolua_cclass(tolua_S,"TextureData","ccs.TextureData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"TextureData");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_TextureData_constructor);
        tolua_function(tolua_S,"getContourData",lua_cocos2dx_studio_TextureData_getContourData);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_TextureData_init);
        tolua_function(tolua_S,"addContourData",lua_cocos2dx_studio_TextureData_addContourData);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_TextureData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::TextureData).name();
    g_luaType[typeName] = "ccs.TextureData";
    g_typeCast["TextureData"] = "ccs.TextureData";
    return 1;
}

int lua_cocos2dx_studio_Tween_getAnimation(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Tween",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Tween*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Tween_getAnimation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::ArmatureAnimation* ret = cobj->getAnimation();
        object_to_luaval<cocostudio::ArmatureAnimation>(tolua_S, "ccs.ArmatureAnimation",(cocostudio::ArmatureAnimation*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:getAnimation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Tween_getAnimation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Tween_gotoAndPause(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Tween",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Tween*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Tween_gotoAndPause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.Tween:gotoAndPause");
        if(!ok)
            return 0;
        cobj->gotoAndPause(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:gotoAndPause",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Tween_gotoAndPause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Tween_play(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Tween",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Tween*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Tween_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        cocostudio::MovementBoneData* arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;

        ok &= luaval_to_object<cocostudio::MovementBoneData>(tolua_S, 2, "ccs.MovementBoneData",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.Tween:play");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccs.Tween:play");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccs.Tween:play");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "ccs.Tween:play");
        if(!ok)
            return 0;
        cobj->play(arg0, arg1, arg2, arg3, arg4);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:play",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Tween_play'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Tween_gotoAndPlay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Tween",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Tween*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Tween_gotoAndPlay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.Tween:gotoAndPlay");
        if(!ok)
            return 0;
        cobj->gotoAndPlay(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:gotoAndPlay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Tween_gotoAndPlay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Tween_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Tween",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Tween*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Tween_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Bone* arg0;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:init",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Tween_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Tween_setAnimation(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Tween",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Tween*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Tween_setAnimation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::ArmatureAnimation* arg0;

        ok &= luaval_to_object<cocostudio::ArmatureAnimation>(tolua_S, 2, "ccs.ArmatureAnimation",&arg0);
        if(!ok)
            return 0;
        cobj->setAnimation(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:setAnimation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Tween_setAnimation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Tween_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Tween",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocostudio::Bone* arg0;
        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);
        if(!ok)
            return 0;
        cocostudio::Tween* ret = cocostudio::Tween::create(arg0);
        object_to_luaval<cocostudio::Tween>(tolua_S, "ccs.Tween",(cocostudio::Tween*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.Tween:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Tween_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_Tween_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::Tween();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Tween");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:Tween",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Tween_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_Tween_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Tween)");
    return 0;
}

int lua_register_cocos2dx_studio_Tween(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.Tween");
    tolua_cclass(tolua_S,"Tween","ccs.Tween","ccs.ProcessBase",nullptr);

    tolua_beginmodule(tolua_S,"Tween");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_Tween_constructor);
        tolua_function(tolua_S,"getAnimation",lua_cocos2dx_studio_Tween_getAnimation);
        tolua_function(tolua_S,"gotoAndPause",lua_cocos2dx_studio_Tween_gotoAndPause);
        tolua_function(tolua_S,"play",lua_cocos2dx_studio_Tween_play);
        tolua_function(tolua_S,"gotoAndPlay",lua_cocos2dx_studio_Tween_gotoAndPlay);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_Tween_init);
        tolua_function(tolua_S,"setAnimation",lua_cocos2dx_studio_Tween_setAnimation);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_Tween_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::Tween).name();
    g_luaType[typeName] = "ccs.Tween";
    g_typeCast["Tween"] = "ccs.Tween";
    return 1;
}

int lua_cocos2dx_studio_DisplayManager_getDisplayRenderNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_getDisplayRenderNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->getDisplayRenderNode();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getDisplayRenderNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_getDisplayRenderNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_getAnchorPointInPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_getAnchorPointInPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Vec2 ret = cobj->getAnchorPointInPoints();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getAnchorPointInPoints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_getAnchorPointInPoints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getDisplayRenderNodeType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getDisplayRenderNodeType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_removeDisplay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_removeDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.DisplayManager:removeDisplay");
        if(!ok)
            return 0;
        cobj->removeDisplay(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:removeDisplay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_removeDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_setForceChangeDisplay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_setForceChangeDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.DisplayManager:setForceChangeDisplay");
        if(!ok)
            return 0;
        cobj->setForceChangeDisplay(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:setForceChangeDisplay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_setForceChangeDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Bone* arg0;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:init",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_getContentSize(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_getContentSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Size ret = cobj->getContentSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getContentSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_getContentSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_getBoundingBox(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_getBoundingBox'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->getBoundingBox();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getBoundingBox",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_getBoundingBox'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_addDisplay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_addDisplay'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.DisplayManager:addDisplay");

            if (!ok) { break; }
            cobj->addDisplay(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocostudio::DisplayData* arg0;
            ok &= luaval_to_object<cocostudio::DisplayData>(tolua_S, 2, "ccs.DisplayData",&arg0);

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.DisplayManager:addDisplay");

            if (!ok) { break; }
            cobj->addDisplay(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.DisplayManager:addDisplay",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_addDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_containPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_containPoint'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.DisplayManager:containPoint");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "ccs.DisplayManager:containPoint");

            if (!ok) { break; }
            bool ret = cobj->containPoint(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccs.DisplayManager:containPoint");

            if (!ok) { break; }
            bool ret = cobj->containPoint(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.DisplayManager:containPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_containPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_changeDisplayWithIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_changeDisplayWithIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        bool arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.DisplayManager:changeDisplayWithIndex");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.DisplayManager:changeDisplayWithIndex");
        if(!ok)
            return 0;
        cobj->changeDisplayWithIndex(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:changeDisplayWithIndex",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_changeDisplayWithIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_changeDisplayWithName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_changeDisplayWithName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.DisplayManager:changeDisplayWithName");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.DisplayManager:changeDisplayWithName");
        if(!ok)
            return 0;
        cobj->changeDisplayWithName(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:changeDisplayWithName",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_changeDisplayWithName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_isForceChangeDisplay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_isForceChangeDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isForceChangeDisplay();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:isForceChangeDisplay",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_isForceChangeDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getCurrentDisplayIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getCurrentDisplayIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_getAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_getAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Vec2 ret = cobj->getAnchorPoint();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getAnchorPoint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_getAnchorPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_getDecorativeDisplayList(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_getDecorativeDisplayList'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Vector<cocostudio::DecorativeDisplay *>& ret = cobj->getDecorativeDisplayList();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getDecorativeDisplayList",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_getDecorativeDisplayList'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_isVisible(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_isVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isVisible();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:isVisible",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_isVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_setVisible(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_DisplayManager_setVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.DisplayManager:setVisible");
        if(!ok)
            return 0;
        cobj->setVisible(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:setVisible",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_setVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_DisplayManager_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocostudio::Bone* arg0;
        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);
        if(!ok)
            return 0;
        cocostudio::DisplayManager* ret = cocostudio::DisplayManager::create(arg0);
        object_to_luaval<cocostudio::DisplayManager>(tolua_S, "ccs.DisplayManager",(cocostudio::DisplayManager*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.DisplayManager:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_DisplayManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::DisplayManager();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.DisplayManager");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:DisplayManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_DisplayManager_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_DisplayManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (DisplayManager)");
    return 0;
}

int lua_register_cocos2dx_studio_DisplayManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.DisplayManager");
    tolua_cclass(tolua_S,"DisplayManager","ccs.DisplayManager","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"DisplayManager");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_DisplayManager_constructor);
        tolua_function(tolua_S,"getDisplayRenderNode",lua_cocos2dx_studio_DisplayManager_getDisplayRenderNode);
        tolua_function(tolua_S,"getAnchorPointInPoints",lua_cocos2dx_studio_DisplayManager_getAnchorPointInPoints);
        tolua_function(tolua_S,"getDisplayRenderNodeType",lua_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType);
        tolua_function(tolua_S,"removeDisplay",lua_cocos2dx_studio_DisplayManager_removeDisplay);
        tolua_function(tolua_S,"setForceChangeDisplay",lua_cocos2dx_studio_DisplayManager_setForceChangeDisplay);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_DisplayManager_init);
        tolua_function(tolua_S,"getContentSize",lua_cocos2dx_studio_DisplayManager_getContentSize);
        tolua_function(tolua_S,"getBoundingBox",lua_cocos2dx_studio_DisplayManager_getBoundingBox);
        tolua_function(tolua_S,"addDisplay",lua_cocos2dx_studio_DisplayManager_addDisplay);
        tolua_function(tolua_S,"containPoint",lua_cocos2dx_studio_DisplayManager_containPoint);
        tolua_function(tolua_S,"changeDisplayWithIndex",lua_cocos2dx_studio_DisplayManager_changeDisplayWithIndex);
        tolua_function(tolua_S,"changeDisplayWithName",lua_cocos2dx_studio_DisplayManager_changeDisplayWithName);
        tolua_function(tolua_S,"isForceChangeDisplay",lua_cocos2dx_studio_DisplayManager_isForceChangeDisplay);
        tolua_function(tolua_S,"getCurrentDisplayIndex",lua_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex);
        tolua_function(tolua_S,"getAnchorPoint",lua_cocos2dx_studio_DisplayManager_getAnchorPoint);
        tolua_function(tolua_S,"getDecorativeDisplayList",lua_cocos2dx_studio_DisplayManager_getDecorativeDisplayList);
        tolua_function(tolua_S,"isVisible",lua_cocos2dx_studio_DisplayManager_isVisible);
        tolua_function(tolua_S,"setVisible",lua_cocos2dx_studio_DisplayManager_setVisible);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_DisplayManager_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::DisplayManager).name();
    g_luaType[typeName] = "ccs.DisplayManager";
    g_typeCast["DisplayManager"] = "ccs.DisplayManager";
    return 1;
}

int lua_cocos2dx_studio_Bone_isTransformDirty(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_isTransformDirty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isTransformDirty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:isTransformDirty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_isTransformDirty'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_isIgnoreMovementBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_isIgnoreMovementBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isIgnoreMovementBoneData();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:isIgnoreMovementBoneData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_isIgnoreMovementBoneData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_updateZOrder(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_updateZOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateZOrder();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:updateZOrder",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_updateZOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getDisplayRenderNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getDisplayRenderNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->getDisplayRenderNode();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getDisplayRenderNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getDisplayRenderNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_isBlendDirty(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_isBlendDirty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isBlendDirty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:isBlendDirty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_isBlendDirty'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_addChildBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_addChildBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Bone* arg0;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);
        if(!ok)
            return 0;
        cobj->addChildBone(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:addChildBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_addChildBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getWorldInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getWorldInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::BaseData* ret = cobj->getWorldInfo();
        object_to_luaval<cocostudio::BaseData>(tolua_S, "ccs.BaseData",(cocostudio::BaseData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getWorldInfo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getWorldInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getTween(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getTween'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::Tween* ret = cobj->getTween();
        object_to_luaval<cocostudio::Tween>(tolua_S, "ccs.Tween",(cocostudio::Tween*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getTween",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getTween'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getParentBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getParentBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::Bone* ret = cobj->getParentBone();
        object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getParentBone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getParentBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_updateColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_updateColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateColor();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:updateColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_updateColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_setTransformDirty(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_setTransformDirty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.Bone:setTransformDirty");
        if(!ok)
            return 0;
        cobj->setTransformDirty(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setTransformDirty",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_setTransformDirty'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getDisplayRenderNodeType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getDisplayRenderNodeType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getDisplayRenderNodeType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getDisplayRenderNodeType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getDisplayRenderNodeType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_removeDisplay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_removeDisplay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.Bone:removeDisplay");
        if(!ok)
            return 0;
        cobj->removeDisplay(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:removeDisplay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_removeDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_setBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_setBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::BoneData* arg0;

        ok &= luaval_to_object<cocostudio::BoneData>(tolua_S, 2, "ccs.BoneData",&arg0);
        if(!ok)
            return 0;
        cobj->setBoneData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setBoneData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_setBoneData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_init'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Bone:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            bool ret = cobj->init();
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.Bone:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_setParentBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_setParentBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Bone* arg0;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);
        if(!ok)
            return 0;
        cobj->setParentBone(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setParentBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_setParentBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_addDisplay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_addDisplay'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.Bone:addDisplay");

            if (!ok) { break; }
            cobj->addDisplay(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocostudio::DisplayData* arg0;
            ok &= luaval_to_object<cocostudio::DisplayData>(tolua_S, 2, "ccs.DisplayData",&arg0);

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.Bone:addDisplay");

            if (!ok) { break; }
            cobj->addDisplay(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.Bone:addDisplay",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_addDisplay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_removeFromParent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_removeFromParent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.Bone:removeFromParent");
        if(!ok)
            return 0;
        cobj->removeFromParent(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:removeFromParent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_removeFromParent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getColliderDetector(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getColliderDetector'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::ColliderDetector* ret = cobj->getColliderDetector();
        object_to_luaval<cocostudio::ColliderDetector>(tolua_S, "ccs.ColliderDetector",(cocostudio::ColliderDetector*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getColliderDetector",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getColliderDetector'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getChildArmature(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getChildArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::Armature* ret = cobj->getChildArmature();
        object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getChildArmature",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getChildArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getTweenData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getTweenData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::FrameData* ret = cobj->getTweenData();
        object_to_luaval<cocostudio::FrameData>(tolua_S, "ccs.FrameData",(cocostudio::FrameData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getTweenData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getTweenData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_changeDisplayWithIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_changeDisplayWithIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        bool arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.Bone:changeDisplayWithIndex");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.Bone:changeDisplayWithIndex");
        if(!ok)
            return 0;
        cobj->changeDisplayWithIndex(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:changeDisplayWithIndex",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_changeDisplayWithIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_changeDisplayWithName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_changeDisplayWithName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Bone:changeDisplayWithName");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.Bone:changeDisplayWithName");
        if(!ok)
            return 0;
        cobj->changeDisplayWithName(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:changeDisplayWithName",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_changeDisplayWithName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_setArmature(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_setArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Armature* arg0;

        ok &= luaval_to_object<cocostudio::Armature>(tolua_S, 2, "ccs.Armature",&arg0);
        if(!ok)
            return 0;
        cobj->setArmature(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setArmature",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_setArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_setBlendDirty(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_setBlendDirty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.Bone:setBlendDirty");
        if(!ok)
            return 0;
        cobj->setBlendDirty(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setBlendDirty",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_setBlendDirty'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_removeChildBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_removeChildBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocostudio::Bone* arg0;
        bool arg1;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.Bone:removeChildBone");
        if(!ok)
            return 0;
        cobj->removeChildBone(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:removeChildBone",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_removeChildBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_setChildArmature(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_setChildArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Armature* arg0;

        ok &= luaval_to_object<cocostudio::Armature>(tolua_S, 2, "ccs.Armature",&arg0);
        if(!ok)
            return 0;
        cobj->setChildArmature(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setChildArmature",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_setChildArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getNodeToArmatureTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getNodeToArmatureTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Mat4 ret = cobj->getNodeToArmatureTransform();
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getNodeToArmatureTransform",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getNodeToArmatureTransform'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getDisplayManager(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getDisplayManager'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::DisplayManager* ret = cobj->getDisplayManager();
        object_to_luaval<cocostudio::DisplayManager>(tolua_S, "ccs.DisplayManager",(cocostudio::DisplayManager*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getDisplayManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getDisplayManager'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getArmature(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::Armature* ret = cobj->getArmature();
        object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getArmature",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_getBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Bone_getBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::BoneData* ret = cobj->getBoneData();
        object_to_luaval<cocostudio::BoneData>(tolua_S, "ccs.BoneData",(cocostudio::BoneData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getBoneData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_getBoneData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Bone_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Bone:create");
            if (!ok) { break; }
            cocostudio::Bone* ret = cocostudio::Bone::create(arg0);
            object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocostudio::Bone* ret = cocostudio::Bone::create();
            object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "ccs.Bone:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_Bone_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::Bone();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Bone");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:Bone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Bone_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_Bone_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Bone)");
    return 0;
}

int lua_register_cocos2dx_studio_Bone(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.Bone");
    tolua_cclass(tolua_S,"Bone","ccs.Bone","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"Bone");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_Bone_constructor);
        tolua_function(tolua_S,"isTransformDirty",lua_cocos2dx_studio_Bone_isTransformDirty);
        tolua_function(tolua_S,"isIgnoreMovementBoneData",lua_cocos2dx_studio_Bone_isIgnoreMovementBoneData);
        tolua_function(tolua_S,"updateZOrder",lua_cocos2dx_studio_Bone_updateZOrder);
        tolua_function(tolua_S,"getDisplayRenderNode",lua_cocos2dx_studio_Bone_getDisplayRenderNode);
        tolua_function(tolua_S,"isBlendDirty",lua_cocos2dx_studio_Bone_isBlendDirty);
        tolua_function(tolua_S,"addChildBone",lua_cocos2dx_studio_Bone_addChildBone);
        tolua_function(tolua_S,"getWorldInfo",lua_cocos2dx_studio_Bone_getWorldInfo);
        tolua_function(tolua_S,"getTween",lua_cocos2dx_studio_Bone_getTween);
        tolua_function(tolua_S,"getParentBone",lua_cocos2dx_studio_Bone_getParentBone);
        tolua_function(tolua_S,"updateColor",lua_cocos2dx_studio_Bone_updateColor);
        tolua_function(tolua_S,"setTransformDirty",lua_cocos2dx_studio_Bone_setTransformDirty);
        tolua_function(tolua_S,"getDisplayRenderNodeType",lua_cocos2dx_studio_Bone_getDisplayRenderNodeType);
        tolua_function(tolua_S,"removeDisplay",lua_cocos2dx_studio_Bone_removeDisplay);
        tolua_function(tolua_S,"setBoneData",lua_cocos2dx_studio_Bone_setBoneData);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_Bone_init);
        tolua_function(tolua_S,"setParentBone",lua_cocos2dx_studio_Bone_setParentBone);
        tolua_function(tolua_S,"addDisplay",lua_cocos2dx_studio_Bone_addDisplay);
        tolua_function(tolua_S,"removeFromParent",lua_cocos2dx_studio_Bone_removeFromParent);
        tolua_function(tolua_S,"getColliderDetector",lua_cocos2dx_studio_Bone_getColliderDetector);
        tolua_function(tolua_S,"getChildArmature",lua_cocos2dx_studio_Bone_getChildArmature);
        tolua_function(tolua_S,"getTweenData",lua_cocos2dx_studio_Bone_getTweenData);
        tolua_function(tolua_S,"changeDisplayWithIndex",lua_cocos2dx_studio_Bone_changeDisplayWithIndex);
        tolua_function(tolua_S,"changeDisplayWithName",lua_cocos2dx_studio_Bone_changeDisplayWithName);
        tolua_function(tolua_S,"setArmature",lua_cocos2dx_studio_Bone_setArmature);
        tolua_function(tolua_S,"setBlendDirty",lua_cocos2dx_studio_Bone_setBlendDirty);
        tolua_function(tolua_S,"removeChildBone",lua_cocos2dx_studio_Bone_removeChildBone);
        tolua_function(tolua_S,"setChildArmature",lua_cocos2dx_studio_Bone_setChildArmature);
        tolua_function(tolua_S,"getNodeToArmatureTransform",lua_cocos2dx_studio_Bone_getNodeToArmatureTransform);
        tolua_function(tolua_S,"getDisplayManager",lua_cocos2dx_studio_Bone_getDisplayManager);
        tolua_function(tolua_S,"getArmature",lua_cocos2dx_studio_Bone_getArmature);
        tolua_function(tolua_S,"getBoneData",lua_cocos2dx_studio_Bone_getBoneData);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_Bone_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::Bone).name();
    g_luaType[typeName] = "ccs.Bone";
    g_typeCast["Bone"] = "ccs.Bone";
    return 1;
}

int lua_cocos2dx_studio_BatchNode_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BatchNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::BatchNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_BatchNode_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BatchNode:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BatchNode_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_BatchNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.BatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::BatchNode* ret = cocostudio::BatchNode::create();
        object_to_luaval<cocostudio::BatchNode>(tolua_S, "ccs.BatchNode",(cocostudio::BatchNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.BatchNode:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_BatchNode_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_BatchNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BatchNode)");
    return 0;
}

int lua_register_cocos2dx_studio_BatchNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.BatchNode");
    tolua_cclass(tolua_S,"BatchNode","ccs.BatchNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"BatchNode");
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_BatchNode_init);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_BatchNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::BatchNode).name();
    g_luaType[typeName] = "ccs.BatchNode";
    g_typeCast["BatchNode"] = "ccs.BatchNode";
    return 1;
}

int lua_cocos2dx_studio_ArmatureAnimation_getSpeedScale(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_getSpeedScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getSpeedScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:getSpeedScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_getSpeedScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_pause(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->pause();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:pause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_pause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_setSpeedScale(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_setSpeedScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ArmatureAnimation:setSpeedScale");
        if(!ok)
            return 0;
        cobj->setSpeedScale(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:setSpeedScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_setSpeedScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Armature* arg0;

        ok &= luaval_to_object<cocostudio::Armature>(tolua_S, 2, "ccs.Armature",&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:init",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_playWithIndexes(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_playWithIndexes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<int> arg0;

        ok &= luaval_to_std_vector_int(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithIndexes");
        if(!ok)
            return 0;
        cobj->playWithIndexes(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        std::vector<int> arg0;
        int arg1;

        ok &= luaval_to_std_vector_int(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithIndexes");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithIndexes");
        if(!ok)
            return 0;
        cobj->playWithIndexes(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        std::vector<int> arg0;
        int arg1;
        bool arg2;

        ok &= luaval_to_std_vector_int(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithIndexes");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithIndexes");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccs.ArmatureAnimation:playWithIndexes");
        if(!ok)
            return 0;
        cobj->playWithIndexes(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:playWithIndexes",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_playWithIndexes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_play(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureAnimation:play");
        if(!ok)
            return 0;
        cobj->play(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        std::string arg0;
        int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureAnimation:play");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:play");
        if(!ok)
            return 0;
        cobj->play(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        std::string arg0;
        int arg1;
        int arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureAnimation:play");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:play");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccs.ArmatureAnimation:play");
        if(!ok)
            return 0;
        cobj->play(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:play",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_play'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_gotoAndPause(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_gotoAndPause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ArmatureAnimation:gotoAndPause");
        if(!ok)
            return 0;
        cobj->gotoAndPause(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:gotoAndPause",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_gotoAndPause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_resume(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_resume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->resume();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:resume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_resume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_stop(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->stop();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_update(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ArmatureAnimation:update");
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_getAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_getAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::AnimationData* ret = cobj->getAnimationData();
        object_to_luaval<cocostudio::AnimationData>(tolua_S, "ccs.AnimationData",(cocostudio::AnimationData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:getAnimationData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_getAnimationData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_playWithIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_playWithIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ArmatureAnimation:playWithIndex");
        if(!ok)
            return 0;
        cobj->playWithIndex(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ArmatureAnimation:playWithIndex");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithIndex");
        if(!ok)
            return 0;
        cobj->playWithIndex(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        int arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ArmatureAnimation:playWithIndex");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithIndex");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccs.ArmatureAnimation:playWithIndex");
        if(!ok)
            return 0;
        cobj->playWithIndex(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:playWithIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_playWithIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getCurrentMovementID();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:getCurrentMovementID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_setAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_setAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::AnimationData* arg0;

        ok &= luaval_to_object<cocostudio::AnimationData>(tolua_S, 2, "ccs.AnimationData",&arg0);
        if(!ok)
            return 0;
        cobj->setAnimationData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:setAnimationData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_setAnimationData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_gotoAndPlay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_gotoAndPlay'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ArmatureAnimation:gotoAndPlay");
        if(!ok)
            return 0;
        cobj->gotoAndPlay(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:gotoAndPlay",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_gotoAndPlay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_playWithNames(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_playWithNames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<std::string> arg0;

        ok &= luaval_to_std_vector_string(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithNames");
        if(!ok)
            return 0;
        cobj->playWithNames(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        std::vector<std::string> arg0;
        int arg1;

        ok &= luaval_to_std_vector_string(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithNames");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithNames");
        if(!ok)
            return 0;
        cobj->playWithNames(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        std::vector<std::string> arg0;
        int arg1;
        bool arg2;

        ok &= luaval_to_std_vector_string(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithNames");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithNames");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccs.ArmatureAnimation:playWithNames");
        if(!ok)
            return 0;
        cobj->playWithNames(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:playWithNames",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_playWithNames'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_getMovementCount(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureAnimation_getMovementCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ssize_t ret = cobj->getMovementCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:getMovementCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_getMovementCount'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocostudio::Armature* arg0;
        ok &= luaval_to_object<cocostudio::Armature>(tolua_S, 2, "ccs.Armature",&arg0);
        if(!ok)
            return 0;
        cocostudio::ArmatureAnimation* ret = cocostudio::ArmatureAnimation::create(arg0);
        object_to_luaval<cocostudio::ArmatureAnimation>(tolua_S, "ccs.ArmatureAnimation",(cocostudio::ArmatureAnimation*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureAnimation:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ArmatureAnimation_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ArmatureAnimation();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ArmatureAnimation");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:ArmatureAnimation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureAnimation_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ArmatureAnimation_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ArmatureAnimation)");
    return 0;
}

int lua_register_cocos2dx_studio_ArmatureAnimation(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ArmatureAnimation");
    tolua_cclass(tolua_S,"ArmatureAnimation","ccs.ArmatureAnimation","ccs.ProcessBase",nullptr);

    tolua_beginmodule(tolua_S,"ArmatureAnimation");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ArmatureAnimation_constructor);
        tolua_function(tolua_S,"getSpeedScale",lua_cocos2dx_studio_ArmatureAnimation_getSpeedScale);
        tolua_function(tolua_S,"pause",lua_cocos2dx_studio_ArmatureAnimation_pause);
        tolua_function(tolua_S,"setSpeedScale",lua_cocos2dx_studio_ArmatureAnimation_setSpeedScale);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_ArmatureAnimation_init);
        tolua_function(tolua_S,"playWithIndexes",lua_cocos2dx_studio_ArmatureAnimation_playWithIndexes);
        tolua_function(tolua_S,"play",lua_cocos2dx_studio_ArmatureAnimation_play);
        tolua_function(tolua_S,"gotoAndPause",lua_cocos2dx_studio_ArmatureAnimation_gotoAndPause);
        tolua_function(tolua_S,"resume",lua_cocos2dx_studio_ArmatureAnimation_resume);
        tolua_function(tolua_S,"stop",lua_cocos2dx_studio_ArmatureAnimation_stop);
        tolua_function(tolua_S,"update",lua_cocos2dx_studio_ArmatureAnimation_update);
        tolua_function(tolua_S,"getAnimationData",lua_cocos2dx_studio_ArmatureAnimation_getAnimationData);
        tolua_function(tolua_S,"playWithIndex",lua_cocos2dx_studio_ArmatureAnimation_playWithIndex);
        tolua_function(tolua_S,"getCurrentMovementID",lua_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID);
        tolua_function(tolua_S,"setAnimationData",lua_cocos2dx_studio_ArmatureAnimation_setAnimationData);
        tolua_function(tolua_S,"gotoAndPlay",lua_cocos2dx_studio_ArmatureAnimation_gotoAndPlay);
        tolua_function(tolua_S,"playWithNames",lua_cocos2dx_studio_ArmatureAnimation_playWithNames);
        tolua_function(tolua_S,"getMovementCount",lua_cocos2dx_studio_ArmatureAnimation_getMovementCount);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ArmatureAnimation_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ArmatureAnimation).name();
    g_luaType[typeName] = "ccs.ArmatureAnimation";
    g_typeCast["ArmatureAnimation"] = "ccs.ArmatureAnimation";
    return 1;
}

int lua_cocos2dx_studio_ArmatureDataManager_getAnimationDatas(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_getAnimationDatas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Map<std::string, cocostudio::AnimationData *>& ret = cobj->getAnimationDatas();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getAnimationDatas",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_getAnimationDatas'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_removeAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_removeAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:removeAnimationData");
        if(!ok)
            return 0;
        cobj->removeAnimationData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:removeAnimationData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_removeAnimationData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_addArmatureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_addArmatureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocostudio::ArmatureData* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addArmatureData");

        ok &= luaval_to_object<cocostudio::ArmatureData>(tolua_S, 3, "ccs.ArmatureData",&arg1);
        if(!ok)
            return 0;
        cobj->addArmatureData(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        std::string arg0;
        cocostudio::ArmatureData* arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addArmatureData");

        ok &= luaval_to_object<cocostudio::ArmatureData>(tolua_S, 3, "ccs.ArmatureData",&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addArmatureData");
        if(!ok)
            return 0;
        cobj->addArmatureData(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addArmatureData",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_addArmatureData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addArmatureFileInfo");

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccs.ArmatureDataManager:addArmatureFileInfo");

            if (!ok) { break; }
            std::string arg2;
            ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addArmatureFileInfo");

            if (!ok) { break; }
            cobj->addArmatureFileInfo(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addArmatureFileInfo");

            if (!ok) { break; }
            cobj->addArmatureFileInfo(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ArmatureDataManager:addArmatureFileInfo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:removeArmatureFileInfo");
        if(!ok)
            return 0;
        cobj->removeArmatureFileInfo(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:removeArmatureFileInfo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_getTextureDatas(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_getTextureDatas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Map<std::string, cocostudio::TextureData *>& ret = cobj->getTextureDatas();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getTextureDatas",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_getTextureDatas'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_getTextureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_getTextureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:getTextureData");
        if(!ok)
            return 0;
        cocostudio::TextureData* ret = cobj->getTextureData(arg0);
        object_to_luaval<cocostudio::TextureData>(tolua_S, "ccs.TextureData",(cocostudio::TextureData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getTextureData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_getTextureData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_getArmatureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_getArmatureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:getArmatureData");
        if(!ok)
            return 0;
        cocostudio::ArmatureData* ret = cobj->getArmatureData(arg0);
        object_to_luaval<cocostudio::ArmatureData>(tolua_S, "ccs.ArmatureData",(cocostudio::ArmatureData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getArmatureData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_getArmatureData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_getAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_getAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:getAnimationData");
        if(!ok)
            return 0;
        cocostudio::AnimationData* ret = cobj->getAnimationData(arg0);
        object_to_luaval<cocostudio::AnimationData>(tolua_S, "ccs.AnimationData",(cocostudio::AnimationData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getAnimationData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_getAnimationData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_addAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_addAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocostudio::AnimationData* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addAnimationData");

        ok &= luaval_to_object<cocostudio::AnimationData>(tolua_S, 3, "ccs.AnimationData",&arg1);
        if(!ok)
            return 0;
        cobj->addAnimationData(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        std::string arg0;
        cocostudio::AnimationData* arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addAnimationData");

        ok &= luaval_to_object<cocostudio::AnimationData>(tolua_S, 3, "ccs.AnimationData",&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addAnimationData");
        if(!ok)
            return 0;
        cobj->addAnimationData(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addAnimationData",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_addAnimationData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_removeArmatureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_removeArmatureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:removeArmatureData");
        if(!ok)
            return 0;
        cobj->removeArmatureData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:removeArmatureData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_removeArmatureData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_getArmatureDatas(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_getArmatureDatas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Map<std::string, cocostudio::ArmatureData *>& ret = cobj->getArmatureDatas();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getArmatureDatas",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_getArmatureDatas'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_removeTextureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_removeTextureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:removeTextureData");
        if(!ok)
            return 0;
        cobj->removeTextureData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:removeTextureData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_removeTextureData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_addTextureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_addTextureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocostudio::TextureData* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addTextureData");

        ok &= luaval_to_object<cocostudio::TextureData>(tolua_S, 3, "ccs.TextureData",&arg1);
        if(!ok)
            return 0;
        cobj->addTextureData(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        std::string arg0;
        cocostudio::TextureData* arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addTextureData");

        ok &= luaval_to_object<cocostudio::TextureData>(tolua_S, 3, "ccs.TextureData",&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addTextureData");
        if(!ok)
            return 0;
        cobj->addTextureData(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addTextureData",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_addTextureData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isAutoLoadSpriteFile();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:isAutoLoadSpriteFile",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addSpriteFrameFromFile");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccs.ArmatureDataManager:addSpriteFrameFromFile");
        if(!ok)
            return 0;
        cobj->addSpriteFrameFromFile(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addSpriteFrameFromFile");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccs.ArmatureDataManager:addSpriteFrameFromFile");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addSpriteFrameFromFile");
        if(!ok)
            return 0;
        cobj->addSpriteFrameFromFile(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addSpriteFrameFromFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ArmatureDataManager::destroyInstance();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureDataManager:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ArmatureDataManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ArmatureDataManager* ret = cocostudio::ArmatureDataManager::getInstance();
        object_to_luaval<cocostudio::ArmatureDataManager>(tolua_S, "ccs.ArmatureDataManager",(cocostudio::ArmatureDataManager*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureDataManager:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ArmatureDataManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_ArmatureDataManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ArmatureDataManager)");
    return 0;
}

int lua_register_cocos2dx_studio_ArmatureDataManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ArmatureDataManager");
    tolua_cclass(tolua_S,"ArmatureDataManager","ccs.ArmatureDataManager","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ArmatureDataManager");
        tolua_function(tolua_S,"getAnimationDatas",lua_cocos2dx_studio_ArmatureDataManager_getAnimationDatas);
        tolua_function(tolua_S,"removeAnimationData",lua_cocos2dx_studio_ArmatureDataManager_removeAnimationData);
        tolua_function(tolua_S,"addArmatureData",lua_cocos2dx_studio_ArmatureDataManager_addArmatureData);
        tolua_function(tolua_S,"addArmatureFileInfo",lua_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo);
        tolua_function(tolua_S,"removeArmatureFileInfo",lua_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo);
        tolua_function(tolua_S,"getTextureDatas",lua_cocos2dx_studio_ArmatureDataManager_getTextureDatas);
        tolua_function(tolua_S,"getTextureData",lua_cocos2dx_studio_ArmatureDataManager_getTextureData);
        tolua_function(tolua_S,"getArmatureData",lua_cocos2dx_studio_ArmatureDataManager_getArmatureData);
        tolua_function(tolua_S,"getAnimationData",lua_cocos2dx_studio_ArmatureDataManager_getAnimationData);
        tolua_function(tolua_S,"addAnimationData",lua_cocos2dx_studio_ArmatureDataManager_addAnimationData);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_ArmatureDataManager_init);
        tolua_function(tolua_S,"removeArmatureData",lua_cocos2dx_studio_ArmatureDataManager_removeArmatureData);
        tolua_function(tolua_S,"getArmatureDatas",lua_cocos2dx_studio_ArmatureDataManager_getArmatureDatas);
        tolua_function(tolua_S,"removeTextureData",lua_cocos2dx_studio_ArmatureDataManager_removeTextureData);
        tolua_function(tolua_S,"addTextureData",lua_cocos2dx_studio_ArmatureDataManager_addTextureData);
        tolua_function(tolua_S,"isAutoLoadSpriteFile",lua_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile);
        tolua_function(tolua_S,"addSpriteFrameFromFile",lua_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile);
        tolua_function(tolua_S,"destroyInstance", lua_cocos2dx_studio_ArmatureDataManager_destroyInstance);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_studio_ArmatureDataManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ArmatureDataManager).name();
    g_luaType[typeName] = "ccs.ArmatureDataManager";
    g_typeCast["ArmatureDataManager"] = "ccs.ArmatureDataManager";
    return 1;
}

int lua_cocos2dx_studio_Armature_getBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Armature:getBone");
        if(!ok)
            return 0;
        cocostudio::Bone* ret = cobj->getBone(arg0);
        object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_changeBoneParent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_changeBoneParent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocostudio::Bone* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccs.Armature:changeBoneParent");
        if(!ok)
            return 0;
        cobj->changeBoneParent(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:changeBoneParent",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_changeBoneParent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_setAnimation(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_setAnimation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::ArmatureAnimation* arg0;

        ok &= luaval_to_object<cocostudio::ArmatureAnimation>(tolua_S, 2, "ccs.ArmatureAnimation",&arg0);
        if(!ok)
            return 0;
        cobj->setAnimation(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setAnimation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_setAnimation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getBoneAtPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getBoneAtPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.Armature:getBoneAtPoint");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccs.Armature:getBoneAtPoint");
        if(!ok)
            return 0;
        cocostudio::Bone* ret = cobj->getBoneAtPoint(arg0, arg1);
        object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBoneAtPoint",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getBoneAtPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getArmatureTransformDirty(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getArmatureTransformDirty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getArmatureTransformDirty();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getArmatureTransformDirty",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getArmatureTransformDirty'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_setVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_setVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.Armature:setVersion");
        if(!ok)
            return 0;
        cobj->setVersion(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setVersion",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_setVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_updateOffsetPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_updateOffsetPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateOffsetPoint();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:updateOffsetPoint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_updateOffsetPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getParentBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getParentBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::Bone* ret = cobj->getParentBone();
        object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getParentBone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getParentBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_removeBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_removeBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocostudio::Bone* arg0;
        bool arg1;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.Armature:removeBone");
        if(!ok)
            return 0;
        cobj->removeBone(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:removeBone",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_removeBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getBatchNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getBatchNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::BatchNode* ret = cobj->getBatchNode();
        object_to_luaval<cocostudio::BatchNode>(tolua_S, "ccs.BatchNode",(cocostudio::BatchNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBatchNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getBatchNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_init'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Armature:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            bool ret = cobj->init();
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Armature:init");

            if (!ok) { break; }
            cocostudio::Bone* arg1;
            ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 3, "ccs.Bone",&arg1);

            if (!ok) { break; }
            bool ret = cobj->init(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.Armature:init",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_setParentBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_setParentBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Bone* arg0;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);
        if(!ok)
            return 0;
        cobj->setParentBone(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setParentBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_setParentBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_drawContour(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_drawContour'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->drawContour();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:drawContour",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_drawContour'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_setBatchNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_setBatchNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::BatchNode* arg0;

        ok &= luaval_to_object<cocostudio::BatchNode>(tolua_S, 2, "ccs.BatchNode",&arg0);
        if(!ok)
            return 0;
        cobj->setBatchNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setBatchNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_setBatchNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_setArmatureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_setArmatureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::ArmatureData* arg0;

        ok &= luaval_to_object<cocostudio::ArmatureData>(tolua_S, 2, "ccs.ArmatureData",&arg0);
        if(!ok)
            return 0;
        cobj->setArmatureData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setArmatureData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_setArmatureData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_addBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_addBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocostudio::Bone* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccs.Armature:addBone");
        if(!ok)
            return 0;
        cobj->addBone(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:addBone",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_addBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getArmatureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getArmatureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::ArmatureData* ret = cobj->getArmatureData();
        object_to_luaval<cocostudio::ArmatureData>(tolua_S, "ccs.ArmatureData",(cocostudio::ArmatureData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getArmatureData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getArmatureData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getVersion();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getAnimation(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getAnimation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::ArmatureAnimation* ret = cobj->getAnimation();
        object_to_luaval<cocostudio::ArmatureAnimation>(tolua_S, "ccs.ArmatureAnimation",(cocostudio::ArmatureAnimation*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getAnimation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getAnimation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getOffsetPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getOffsetPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Vec2& ret = cobj->getOffsetPoints();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getOffsetPoints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getOffsetPoints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_getBoneDic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Armature_getBoneDic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Map<std::string, cocostudio::Bone *>& ret = cobj->getBoneDic();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBoneDic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_getBoneDic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Armature_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Armature:create");
            if (!ok) { break; }
            cocostudio::Armature* ret = cocostudio::Armature::create(arg0);
            object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocostudio::Armature* ret = cocostudio::Armature::create();
            object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Armature:create");
            if (!ok) { break; }
            cocostudio::Bone* arg1;
            ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 3, "ccs.Bone",&arg1);
            if (!ok) { break; }
            cocostudio::Armature* ret = cocostudio::Armature::create(arg0, arg1);
            object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "ccs.Armature:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_Armature_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::Armature();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Armature");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:Armature",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Armature_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_Armature_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Armature)");
    return 0;
}

int lua_register_cocos2dx_studio_Armature(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.Armature");
    tolua_cclass(tolua_S,"Armature","ccs.Armature","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"Armature");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_Armature_constructor);
        tolua_function(tolua_S,"getBone",lua_cocos2dx_studio_Armature_getBone);
        tolua_function(tolua_S,"changeBoneParent",lua_cocos2dx_studio_Armature_changeBoneParent);
        tolua_function(tolua_S,"setAnimation",lua_cocos2dx_studio_Armature_setAnimation);
        tolua_function(tolua_S,"getBoneAtPoint",lua_cocos2dx_studio_Armature_getBoneAtPoint);
        tolua_function(tolua_S,"getArmatureTransformDirty",lua_cocos2dx_studio_Armature_getArmatureTransformDirty);
        tolua_function(tolua_S,"setVersion",lua_cocos2dx_studio_Armature_setVersion);
        tolua_function(tolua_S,"updateOffsetPoint",lua_cocos2dx_studio_Armature_updateOffsetPoint);
        tolua_function(tolua_S,"getParentBone",lua_cocos2dx_studio_Armature_getParentBone);
        tolua_function(tolua_S,"removeBone",lua_cocos2dx_studio_Armature_removeBone);
        tolua_function(tolua_S,"getBatchNode",lua_cocos2dx_studio_Armature_getBatchNode);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_Armature_init);
        tolua_function(tolua_S,"setParentBone",lua_cocos2dx_studio_Armature_setParentBone);
        tolua_function(tolua_S,"drawContour",lua_cocos2dx_studio_Armature_drawContour);
        tolua_function(tolua_S,"setBatchNode",lua_cocos2dx_studio_Armature_setBatchNode);
        tolua_function(tolua_S,"setArmatureData",lua_cocos2dx_studio_Armature_setArmatureData);
        tolua_function(tolua_S,"addBone",lua_cocos2dx_studio_Armature_addBone);
        tolua_function(tolua_S,"getArmatureData",lua_cocos2dx_studio_Armature_getArmatureData);
        tolua_function(tolua_S,"getVersion",lua_cocos2dx_studio_Armature_getVersion);
        tolua_function(tolua_S,"getAnimation",lua_cocos2dx_studio_Armature_getAnimation);
        tolua_function(tolua_S,"getOffsetPoints",lua_cocos2dx_studio_Armature_getOffsetPoints);
        tolua_function(tolua_S,"getBoneDic",lua_cocos2dx_studio_Armature_getBoneDic);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_Armature_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::Armature).name();
    g_luaType[typeName] = "ccs.Armature";
    g_typeCast["Armature"] = "ccs.Armature";
    return 1;
}

int lua_cocos2dx_studio_Skin_getBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Skin*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Skin_getBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::Bone* ret = cobj->getBone();
        object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:getBone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_getBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Skin_getNodeToWorldTransformAR(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Skin*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Skin_getNodeToWorldTransformAR'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Mat4 ret = cobj->getNodeToWorldTransformAR();
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:getNodeToWorldTransformAR",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_getNodeToWorldTransformAR'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Skin_initWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Skin*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Skin_initWithFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Skin:initWithFile");
        if(!ok)
            return 0;
        bool ret = cobj->initWithFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:initWithFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_initWithFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Skin_getDisplayName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Skin*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Skin_getDisplayName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getDisplayName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:getDisplayName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_getDisplayName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Skin_updateArmatureTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Skin*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Skin_updateArmatureTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateArmatureTransform();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:updateArmatureTransform",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_updateArmatureTransform'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Skin_initWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Skin*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Skin_initWithSpriteFrameName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Skin:initWithSpriteFrameName");
        if(!ok)
            return 0;
        bool ret = cobj->initWithSpriteFrameName(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:initWithSpriteFrameName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_initWithSpriteFrameName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Skin_setBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Skin*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Skin_setBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::Bone* arg0;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);
        if(!ok)
            return 0;
        cobj->setBone(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:setBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_setBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Skin_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Skin:create");
            if (!ok) { break; }
            cocostudio::Skin* ret = cocostudio::Skin::create(arg0);
            object_to_luaval<cocostudio::Skin>(tolua_S, "ccs.Skin",(cocostudio::Skin*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocostudio::Skin* ret = cocostudio::Skin::create();
            object_to_luaval<cocostudio::Skin>(tolua_S, "ccs.Skin",(cocostudio::Skin*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "ccs.Skin:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_Skin_createWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.Skin:createWithSpriteFrameName");
        if(!ok)
            return 0;
        cocostudio::Skin* ret = cocostudio::Skin::createWithSpriteFrameName(arg0);
        object_to_luaval<cocostudio::Skin>(tolua_S, "ccs.Skin",(cocostudio::Skin*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.Skin:createWithSpriteFrameName",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_createWithSpriteFrameName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_Skin_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::Skin();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Skin");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:Skin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Skin_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_Skin_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Skin)");
    return 0;
}

int lua_register_cocos2dx_studio_Skin(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.Skin");
    tolua_cclass(tolua_S,"Skin","ccs.Skin","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"Skin");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_Skin_constructor);
        tolua_function(tolua_S,"getBone",lua_cocos2dx_studio_Skin_getBone);
        tolua_function(tolua_S,"getNodeToWorldTransformAR",lua_cocos2dx_studio_Skin_getNodeToWorldTransformAR);
        tolua_function(tolua_S,"initWithFile",lua_cocos2dx_studio_Skin_initWithFile);
        tolua_function(tolua_S,"getDisplayName",lua_cocos2dx_studio_Skin_getDisplayName);
        tolua_function(tolua_S,"updateArmatureTransform",lua_cocos2dx_studio_Skin_updateArmatureTransform);
        tolua_function(tolua_S,"initWithSpriteFrameName",lua_cocos2dx_studio_Skin_initWithSpriteFrameName);
        tolua_function(tolua_S,"setBone",lua_cocos2dx_studio_Skin_setBone);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_Skin_create);
        tolua_function(tolua_S,"createWithSpriteFrameName", lua_cocos2dx_studio_Skin_createWithSpriteFrameName);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::Skin).name();
    g_luaType[typeName] = "ccs.Skin";
    g_typeCast["Skin"] = "ccs.Skin";
    return 1;
}

int lua_cocos2dx_studio_ComAttribute_getFloat(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_getFloat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:getFloat");
        if(!ok)
            return 0;
        double ret = cobj->getFloat(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:getFloat");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccs.ComAttribute:getFloat");
        if(!ok)
            return 0;
        double ret = cobj->getFloat(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:getFloat",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_getFloat'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_getString(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_getString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:getString");
        if(!ok)
            return 0;
        std::string ret = cobj->getString(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:getString");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccs.ComAttribute:getString");
        if(!ok)
            return 0;
        std::string ret = cobj->getString(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:getString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_getString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_setFloat(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_setFloat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        double arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:setFloat");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccs.ComAttribute:setFloat");
        if(!ok)
            return 0;
        cobj->setFloat(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:setFloat",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_setFloat'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_setString(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_setString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:setString");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccs.ComAttribute:setString");
        if(!ok)
            return 0;
        cobj->setString(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:setString",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_setString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_getBool(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_getBool'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:getBool");
        if(!ok)
            return 0;
        bool ret = cobj->getBool(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:getBool");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.ComAttribute:getBool");
        if(!ok)
            return 0;
        bool ret = cobj->getBool(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:getBool",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_getBool'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_setInt(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_setInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:setInt");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ComAttribute:setInt");
        if(!ok)
            return 0;
        cobj->setInt(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:setInt",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_setInt'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_parse(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_parse'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:parse");
        if(!ok)
            return 0;
        bool ret = cobj->parse(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:parse",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_parse'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_getInt(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_getInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:getInt");
        if(!ok)
            return 0;
        int ret = cobj->getInt(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:getInt");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ComAttribute:getInt");
        if(!ok)
            return 0;
        int ret = cobj->getInt(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:getInt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_getInt'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_setBool(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAttribute_setBool'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ComAttribute:setBool");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.ComAttribute:setBool");
        if(!ok)
            return 0;
        cobj->setBool(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:setBool",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_setBool'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAttribute_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ComAttribute* ret = cocostudio::ComAttribute::create();
        object_to_luaval<cocostudio::ComAttribute>(tolua_S, "ccs.ComAttribute",(cocostudio::ComAttribute*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComAttribute:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ComAttribute_createInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::Ref* ret = cocostudio::ComAttribute::createInstance();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComAttribute:createInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAttribute_createInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_ComAttribute_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ComAttribute)");
    return 0;
}

int lua_register_cocos2dx_studio_ComAttribute(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ComAttribute");
    tolua_cclass(tolua_S,"ComAttribute","ccs.ComAttribute","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"ComAttribute");
        tolua_function(tolua_S,"getFloat",lua_cocos2dx_studio_ComAttribute_getFloat);
        tolua_function(tolua_S,"getString",lua_cocos2dx_studio_ComAttribute_getString);
        tolua_function(tolua_S,"setFloat",lua_cocos2dx_studio_ComAttribute_setFloat);
        tolua_function(tolua_S,"setString",lua_cocos2dx_studio_ComAttribute_setString);
        tolua_function(tolua_S,"getBool",lua_cocos2dx_studio_ComAttribute_getBool);
        tolua_function(tolua_S,"setInt",lua_cocos2dx_studio_ComAttribute_setInt);
        tolua_function(tolua_S,"parse",lua_cocos2dx_studio_ComAttribute_parse);
        tolua_function(tolua_S,"getInt",lua_cocos2dx_studio_ComAttribute_getInt);
        tolua_function(tolua_S,"setBool",lua_cocos2dx_studio_ComAttribute_setBool);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ComAttribute_create);
        tolua_function(tolua_S,"createInstance", lua_cocos2dx_studio_ComAttribute_createInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ComAttribute).name();
    g_luaType[typeName] = "ccs.ComAttribute";
    g_typeCast["ComAttribute"] = "ccs.ComAttribute";
    return 1;
}

int lua_cocos2dx_studio_ComAudio_stopAllEffects(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_stopAllEffects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->stopAllEffects();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:stopAllEffects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_stopAllEffects'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_getEffectsVolume(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_getEffectsVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getEffectsVolume();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:getEffectsVolume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_getEffectsVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_stopEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_stopEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccs.ComAudio:stopEffect");
        if(!ok)
            return 0;
        cobj->stopEffect(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:stopEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_stopEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_getBackgroundMusicVolume(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_getBackgroundMusicVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getBackgroundMusicVolume();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:getBackgroundMusicVolume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_getBackgroundMusicVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_willPlayBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_willPlayBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->willPlayBackgroundMusic();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:willPlayBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_willPlayBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_setBackgroundMusicVolume(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_setBackgroundMusicVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ComAudio:setBackgroundMusicVolume");
        if(!ok)
            return 0;
        cobj->setBackgroundMusicVolume(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:setBackgroundMusicVolume",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_setBackgroundMusicVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_end(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_end'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->end();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:end",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_end'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_stopBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_stopBackgroundMusic'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cobj->stopBackgroundMusic();
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            bool arg0;
            ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.ComAudio:stopBackgroundMusic");

            if (!ok) { break; }
            cobj->stopBackgroundMusic(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ComAudio:stopBackgroundMusic",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_stopBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_pauseBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_pauseBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->pauseBackgroundMusic();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:pauseBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_pauseBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isBackgroundMusicPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:isBackgroundMusicPlaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_isLoop(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_isLoop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isLoop();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:isLoop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_isLoop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_resumeAllEffects(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_resumeAllEffects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->resumeAllEffects();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:resumeAllEffects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_resumeAllEffects'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_pauseAllEffects(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_pauseAllEffects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->pauseAllEffects();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:pauseAllEffects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_pauseAllEffects'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_preloadBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_preloadBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ComAudio:preloadBackgroundMusic"); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->preloadBackgroundMusic(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:preloadBackgroundMusic",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_preloadBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_playBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_playBackgroundMusic'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ComAudio:playBackgroundMusic"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            cobj->playBackgroundMusic(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ComAudio:playBackgroundMusic"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.ComAudio:playBackgroundMusic");

            if (!ok) { break; }
            cobj->playBackgroundMusic(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj->playBackgroundMusic();
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ComAudio:playBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_playBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_playEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_playEffect'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ComAudio:playEffect"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            unsigned int ret = cobj->playEffect(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ComAudio:playEffect"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.ComAudio:playEffect");

            if (!ok) { break; }
            unsigned int ret = cobj->playEffect(arg0, arg1);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            unsigned int ret = cobj->playEffect();
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ComAudio:playEffect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_playEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_preloadEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_preloadEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ComAudio:preloadEffect"); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->preloadEffect(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:preloadEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_preloadEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_setLoop(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_setLoop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.ComAudio:setLoop");
        if(!ok)
            return 0;
        cobj->setLoop(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:setLoop",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_setLoop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_unloadEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_unloadEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ComAudio:unloadEffect"); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->unloadEffect(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:unloadEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_unloadEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_rewindBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_rewindBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->rewindBackgroundMusic();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:rewindBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_rewindBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_pauseEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_pauseEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccs.ComAudio:pauseEffect");
        if(!ok)
            return 0;
        cobj->pauseEffect(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:pauseEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_pauseEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_resumeBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_resumeBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->resumeBackgroundMusic();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:resumeBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_resumeBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_setFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_setFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.ComAudio:setFile"); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->setFile(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:setFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_setFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_setEffectsVolume(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_setEffectsVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ComAudio:setEffectsVolume");
        if(!ok)
            return 0;
        cobj->setEffectsVolume(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:setEffectsVolume",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_setEffectsVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_getFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_getFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const char* ret = cobj->getFile();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:getFile",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_getFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_resumeEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComAudio_resumeEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccs.ComAudio:resumeEffect");
        if(!ok)
            return 0;
        cobj->resumeEffect(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:resumeEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_resumeEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComAudio_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ComAudio* ret = cocostudio::ComAudio::create();
        object_to_luaval<cocostudio::ComAudio>(tolua_S, "ccs.ComAudio",(cocostudio::ComAudio*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComAudio:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ComAudio_createInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::Ref* ret = cocostudio::ComAudio::createInstance();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComAudio:createInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComAudio_createInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_ComAudio_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ComAudio)");
    return 0;
}

int lua_register_cocos2dx_studio_ComAudio(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ComAudio");
    tolua_cclass(tolua_S,"ComAudio","ccs.ComAudio","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"ComAudio");
        tolua_function(tolua_S,"stopAllEffects",lua_cocos2dx_studio_ComAudio_stopAllEffects);
        tolua_function(tolua_S,"getEffectsVolume",lua_cocos2dx_studio_ComAudio_getEffectsVolume);
        tolua_function(tolua_S,"stopEffect",lua_cocos2dx_studio_ComAudio_stopEffect);
        tolua_function(tolua_S,"getBackgroundMusicVolume",lua_cocos2dx_studio_ComAudio_getBackgroundMusicVolume);
        tolua_function(tolua_S,"willPlayBackgroundMusic",lua_cocos2dx_studio_ComAudio_willPlayBackgroundMusic);
        tolua_function(tolua_S,"setBackgroundMusicVolume",lua_cocos2dx_studio_ComAudio_setBackgroundMusicVolume);
        tolua_function(tolua_S,"end",lua_cocos2dx_studio_ComAudio_end);
        tolua_function(tolua_S,"stopBackgroundMusic",lua_cocos2dx_studio_ComAudio_stopBackgroundMusic);
        tolua_function(tolua_S,"pauseBackgroundMusic",lua_cocos2dx_studio_ComAudio_pauseBackgroundMusic);
        tolua_function(tolua_S,"isBackgroundMusicPlaying",lua_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying);
        tolua_function(tolua_S,"isLoop",lua_cocos2dx_studio_ComAudio_isLoop);
        tolua_function(tolua_S,"resumeAllEffects",lua_cocos2dx_studio_ComAudio_resumeAllEffects);
        tolua_function(tolua_S,"pauseAllEffects",lua_cocos2dx_studio_ComAudio_pauseAllEffects);
        tolua_function(tolua_S,"preloadBackgroundMusic",lua_cocos2dx_studio_ComAudio_preloadBackgroundMusic);
        tolua_function(tolua_S,"playBackgroundMusic",lua_cocos2dx_studio_ComAudio_playBackgroundMusic);
        tolua_function(tolua_S,"playEffect",lua_cocos2dx_studio_ComAudio_playEffect);
        tolua_function(tolua_S,"preloadEffect",lua_cocos2dx_studio_ComAudio_preloadEffect);
        tolua_function(tolua_S,"setLoop",lua_cocos2dx_studio_ComAudio_setLoop);
        tolua_function(tolua_S,"unloadEffect",lua_cocos2dx_studio_ComAudio_unloadEffect);
        tolua_function(tolua_S,"rewindBackgroundMusic",lua_cocos2dx_studio_ComAudio_rewindBackgroundMusic);
        tolua_function(tolua_S,"pauseEffect",lua_cocos2dx_studio_ComAudio_pauseEffect);
        tolua_function(tolua_S,"resumeBackgroundMusic",lua_cocos2dx_studio_ComAudio_resumeBackgroundMusic);
        tolua_function(tolua_S,"setFile",lua_cocos2dx_studio_ComAudio_setFile);
        tolua_function(tolua_S,"setEffectsVolume",lua_cocos2dx_studio_ComAudio_setEffectsVolume);
        tolua_function(tolua_S,"getFile",lua_cocos2dx_studio_ComAudio_getFile);
        tolua_function(tolua_S,"resumeEffect",lua_cocos2dx_studio_ComAudio_resumeEffect);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ComAudio_create);
        tolua_function(tolua_S,"createInstance", lua_cocos2dx_studio_ComAudio_createInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ComAudio).name();
    g_luaType[typeName] = "ccs.ComAudio";
    g_typeCast["ComAudio"] = "ccs.ComAudio";
    return 1;
}

int lua_cocos2dx_studio_ComController_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ComController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::ComController* ret = cocostudio::ComController::create();
        object_to_luaval<cocostudio::ComController>(tolua_S, "ccs.ComController",(cocostudio::ComController*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComController:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComController_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ComController_createInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ComController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::Ref* ret = cocostudio::ComController::createInstance();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComController:createInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComController_createInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ComController_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::ComController();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ComController");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComController:ComController",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComController_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ComController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ComController)");
    return 0;
}

int lua_register_cocos2dx_studio_ComController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ComController");
    tolua_cclass(tolua_S,"ComController","ccs.ComController","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"ComController");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ComController_constructor);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ComController_create);
        tolua_function(tolua_S,"createInstance", lua_cocos2dx_studio_ComController_createInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ComController).name();
    g_luaType[typeName] = "ccs.ComController";
    g_typeCast["ComController"] = "ccs.ComController";
    return 1;
}

int lua_cocos2dx_studio_ComRender_setNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComRender* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComRender",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComRender*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComRender_setNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
            return 0;
        cobj->setNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComRender:setNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComRender_setNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComRender_getNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComRender* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComRender",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComRender*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ComRender_getNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->getNode();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComRender:getNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComRender_getNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ComRender_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ComRender",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "ccs.ComRender:create"); arg1 = arg1_tmp.c_str();
            if (!ok) { break; }
            cocostudio::ComRender* ret = cocostudio::ComRender::create(arg0, arg1);
            object_to_luaval<cocostudio::ComRender>(tolua_S, "ccs.ComRender",(cocostudio::ComRender*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocostudio::ComRender* ret = cocostudio::ComRender::create();
            object_to_luaval<cocostudio::ComRender>(tolua_S, "ccs.ComRender",(cocostudio::ComRender*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "ccs.ComRender:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComRender_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ComRender_createInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ComRender",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::Ref* ret = cocostudio::ComRender::createInstance();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComRender:createInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ComRender_createInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_ComRender_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ComRender)");
    return 0;
}

int lua_register_cocos2dx_studio_ComRender(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ComRender");
    tolua_cclass(tolua_S,"ComRender","ccs.ComRender","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"ComRender");
        tolua_function(tolua_S,"setNode",lua_cocos2dx_studio_ComRender_setNode);
        tolua_function(tolua_S,"getNode",lua_cocos2dx_studio_ComRender_getNode);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ComRender_create);
        tolua_function(tolua_S,"createInstance", lua_cocos2dx_studio_ComRender_createInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::ComRender).name();
    g_luaType[typeName] = "ccs.ComRender";
    g_typeCast["ComRender"] = "ccs.ComRender";
    return 1;
}

int lua_cocos2dx_studio_GUIReader_setFilePath(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::GUIReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.GUIReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::GUIReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_GUIReader_setFilePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.GUIReader:setFilePath");
        if(!ok)
            return 0;
        cobj->setFilePath(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:setFilePath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_GUIReader_setFilePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_GUIReader_widgetFromJsonFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::GUIReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.GUIReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::GUIReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_GUIReader_widgetFromJsonFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.GUIReader:widgetFromJsonFile"); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cocos2d::ui::Widget* ret = cobj->widgetFromJsonFile(arg0);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:widgetFromJsonFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_GUIReader_widgetFromJsonFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_GUIReader_getFilePath(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::GUIReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.GUIReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::GUIReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_GUIReader_getFilePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getFilePath();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:getFilePath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_GUIReader_getFilePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_GUIReader_widgetFromBinaryFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::GUIReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.GUIReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::GUIReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_GUIReader_widgetFromBinaryFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.GUIReader:widgetFromBinaryFile"); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cocos2d::ui::Widget* ret = cobj->widgetFromBinaryFile(arg0);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:widgetFromBinaryFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_GUIReader_widgetFromBinaryFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_GUIReader_getVersionInteger(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::GUIReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.GUIReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::GUIReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_GUIReader_getVersionInteger'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccs.GUIReader:getVersionInteger"); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        int ret = cobj->getVersionInteger(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:getVersionInteger",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_GUIReader_getVersionInteger'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_GUIReader_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.GUIReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::GUIReader::destroyInstance();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.GUIReader:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_GUIReader_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_GUIReader_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.GUIReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::GUIReader* ret = cocostudio::GUIReader::getInstance();
        object_to_luaval<cocostudio::GUIReader>(tolua_S, "ccs.GUIReader",(cocostudio::GUIReader*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.GUIReader:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_GUIReader_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_GUIReader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GUIReader)");
    return 0;
}

int lua_register_cocos2dx_studio_GUIReader(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.GUIReader");
    tolua_cclass(tolua_S,"GUIReader","ccs.GUIReader","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"GUIReader");
        tolua_function(tolua_S,"setFilePath",lua_cocos2dx_studio_GUIReader_setFilePath);
        tolua_function(tolua_S,"widgetFromJsonFile",lua_cocos2dx_studio_GUIReader_widgetFromJsonFile);
        tolua_function(tolua_S,"getFilePath",lua_cocos2dx_studio_GUIReader_getFilePath);
        tolua_function(tolua_S,"widgetFromBinaryFile",lua_cocos2dx_studio_GUIReader_widgetFromBinaryFile);
        tolua_function(tolua_S,"getVersionInteger",lua_cocos2dx_studio_GUIReader_getVersionInteger);
        tolua_function(tolua_S,"destroyInstance", lua_cocos2dx_studio_GUIReader_destroyInstance);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_studio_GUIReader_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::GUIReader).name();
    g_luaType[typeName] = "ccs.GUIReader";
    g_typeCast["GUIReader"] = "ccs.GUIReader";
    return 1;
}

int lua_cocos2dx_studio_SceneReader_setTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SceneReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::SceneReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SceneReader_setTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (cocos2d::Ref *, void *)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        cobj->setTarget(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SceneReader:setTarget",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SceneReader_setTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SceneReader_createNodeWithSceneFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SceneReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::SceneReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SceneReader_createNodeWithSceneFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.SceneReader:createNodeWithSceneFile");
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->createNodeWithSceneFile(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        cocostudio::SceneReader::AttachComponentType arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.SceneReader:createNodeWithSceneFile");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.SceneReader:createNodeWithSceneFile");
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->createNodeWithSceneFile(arg0, arg1);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SceneReader:createNodeWithSceneFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SceneReader_createNodeWithSceneFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SceneReader_getAttachComponentType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SceneReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::SceneReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SceneReader_getAttachComponentType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getAttachComponentType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SceneReader:getAttachComponentType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SceneReader_getAttachComponentType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SceneReader_getNodeByTag(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SceneReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::SceneReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SceneReader_getNodeByTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.SceneReader:getNodeByTag");
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->getNodeByTag(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SceneReader:getNodeByTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SceneReader_getNodeByTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SceneReader_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::SceneReader::destroyInstance();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SceneReader:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SceneReader_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_SceneReader_sceneReaderVersion(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        const char* ret = cocostudio::SceneReader::sceneReaderVersion();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SceneReader:sceneReaderVersion",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SceneReader_sceneReaderVersion'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_SceneReader_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::SceneReader* ret = cocostudio::SceneReader::getInstance();
        object_to_luaval<cocostudio::SceneReader>(tolua_S, "ccs.SceneReader",(cocostudio::SceneReader*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SceneReader:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SceneReader_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_SceneReader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SceneReader)");
    return 0;
}

int lua_register_cocos2dx_studio_SceneReader(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.SceneReader");
    tolua_cclass(tolua_S,"SceneReader","ccs.SceneReader","",nullptr);

    tolua_beginmodule(tolua_S,"SceneReader");
        tolua_function(tolua_S,"setTarget",lua_cocos2dx_studio_SceneReader_setTarget);
        tolua_function(tolua_S,"createNodeWithSceneFile",lua_cocos2dx_studio_SceneReader_createNodeWithSceneFile);
        tolua_function(tolua_S,"getAttachComponentType",lua_cocos2dx_studio_SceneReader_getAttachComponentType);
        tolua_function(tolua_S,"getNodeByTag",lua_cocos2dx_studio_SceneReader_getNodeByTag);
        tolua_function(tolua_S,"destroyInstance", lua_cocos2dx_studio_SceneReader_destroyInstance);
        tolua_function(tolua_S,"sceneReaderVersion", lua_cocos2dx_studio_SceneReader_sceneReaderVersion);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_studio_SceneReader_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::SceneReader).name();
    g_luaType[typeName] = "ccs.SceneReader";
    g_typeCast["SceneReader"] = "ccs.SceneReader";
    return 1;
}

int lua_cocos2dx_studio_ActionTimelineCache_createActionFromJson(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_createActionFromJson'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createActionFromJson");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cobj->createActionFromJson(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:createActionFromJson",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_createActionFromJson'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_createActionFromProtocolBuffers(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_createActionFromProtocolBuffers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createActionFromProtocolBuffers");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cobj->createActionFromProtocolBuffers(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:createActionFromProtocolBuffers",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_createActionFromProtocolBuffers'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_createActionFromXML(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_createActionFromXML'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createActionFromXML");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cobj->createActionFromXML(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:createActionFromXML",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_createActionFromXML'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFileFromProtocolBuffers(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFileFromProtocolBuffers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:loadAnimationActionWithFileFromProtocolBuffers");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cobj->loadAnimationActionWithFileFromProtocolBuffers(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:loadAnimationActionWithFileFromProtocolBuffers",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFileFromProtocolBuffers'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFileFromXML(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFileFromXML'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:loadAnimationActionWithFileFromXML");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cobj->loadAnimationActionWithFileFromXML(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:loadAnimationActionWithFileFromXML",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFileFromXML'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_purge(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_purge'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->purge();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:purge",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_purge'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->init();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:loadAnimationActionWithFile");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cobj->loadAnimationActionWithFile(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:loadAnimationActionWithFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithContent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithContent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:loadAnimationActionWithContent");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccs.ActionTimelineCache:loadAnimationActionWithContent");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cobj->loadAnimationActionWithContent(arg0, arg1);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:loadAnimationActionWithContent",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithContent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_removeAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineCache_removeAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:removeAction");
        if(!ok)
            return 0;
        cobj->removeAction(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:removeAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_removeAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimelineCache::destroyInstance();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineCache:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ActionTimelineCache_createAction(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createAction");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cocostudio::timeline::ActionTimelineCache::createAction(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineCache:createAction",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineCache_createAction'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_ActionTimelineCache_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionTimelineCache)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionTimelineCache(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionTimelineCache");
    tolua_cclass(tolua_S,"ActionTimelineCache","ccs.ActionTimelineCache","",nullptr);

    tolua_beginmodule(tolua_S,"ActionTimelineCache");
        tolua_function(tolua_S,"createActionFromJson",lua_cocos2dx_studio_ActionTimelineCache_createActionFromJson);
        tolua_function(tolua_S,"createActionFromProtocolBuffers",lua_cocos2dx_studio_ActionTimelineCache_createActionFromProtocolBuffers);
        tolua_function(tolua_S,"createActionFromXML",lua_cocos2dx_studio_ActionTimelineCache_createActionFromXML);
        tolua_function(tolua_S,"loadAnimationActionWithFileFromProtocolBuffers",lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFileFromProtocolBuffers);
        tolua_function(tolua_S,"loadAnimationActionWithFileFromXML",lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFileFromXML);
        tolua_function(tolua_S,"purge",lua_cocos2dx_studio_ActionTimelineCache_purge);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_ActionTimelineCache_init);
        tolua_function(tolua_S,"loadAnimationActionWithFile",lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithFile);
        tolua_function(tolua_S,"loadAnimationActionWithContent",lua_cocos2dx_studio_ActionTimelineCache_loadAnimationActionWithContent);
        tolua_function(tolua_S,"removeAction",lua_cocos2dx_studio_ActionTimelineCache_removeAction);
        tolua_function(tolua_S,"destroyInstance", lua_cocos2dx_studio_ActionTimelineCache_destroyInstance);
        tolua_function(tolua_S,"createAction", lua_cocos2dx_studio_ActionTimelineCache_createAction);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::ActionTimelineCache).name();
    g_luaType[typeName] = "ccs.ActionTimelineCache";
    g_typeCast["ActionTimelineCache"] = "ccs.ActionTimelineCache";
    return 1;
}

int lua_cocos2dx_studio_Frame_clone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::timeline::Frame* ret = cobj->clone();
        object_to_luaval<cocostudio::timeline::Frame>(tolua_S, "ccs.Frame",(cocostudio::timeline::Frame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_setNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_setNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
            return 0;
        cobj->setNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_setNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_setTimeline(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_setTimeline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::timeline::Timeline* arg0;

        ok &= luaval_to_object<cocostudio::timeline::Timeline>(tolua_S, 2, "ccs.Timeline",&arg0);
        if(!ok)
            return 0;
        cobj->setTimeline(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setTimeline",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_setTimeline'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_getFrameIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_getFrameIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        unsigned int ret = cobj->getFrameIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:getFrameIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_getFrameIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_apply(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_apply'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.Frame:apply");
        if(!ok)
            return 0;
        cobj->apply(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:apply",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_apply'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_isTween(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_isTween'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isTween();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:isTween",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_isTween'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_setFrameIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_setFrameIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccs.Frame:setFrameIndex");
        if(!ok)
            return 0;
        cobj->setFrameIndex(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setFrameIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_setFrameIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_setTween(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_setTween'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.Frame:setTween");
        if(!ok)
            return 0;
        cobj->setTween(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setTween",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_setTween'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_getTimeline(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_getTimeline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::timeline::Timeline* ret = cobj->getTimeline();
        object_to_luaval<cocostudio::timeline::Timeline>(tolua_S, "ccs.Timeline",(cocostudio::timeline::Timeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:getTimeline",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_getTimeline'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Frame_getNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Frame_getNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->getNode();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:getNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Frame_getNode'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_studio_Frame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Frame)");
    return 0;
}

int lua_register_cocos2dx_studio_Frame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.Frame");
    tolua_cclass(tolua_S,"Frame","ccs.Frame","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Frame");
        tolua_function(tolua_S,"clone",lua_cocos2dx_studio_Frame_clone);
        tolua_function(tolua_S,"setNode",lua_cocos2dx_studio_Frame_setNode);
        tolua_function(tolua_S,"setTimeline",lua_cocos2dx_studio_Frame_setTimeline);
        tolua_function(tolua_S,"getFrameIndex",lua_cocos2dx_studio_Frame_getFrameIndex);
        tolua_function(tolua_S,"apply",lua_cocos2dx_studio_Frame_apply);
        tolua_function(tolua_S,"isTween",lua_cocos2dx_studio_Frame_isTween);
        tolua_function(tolua_S,"setFrameIndex",lua_cocos2dx_studio_Frame_setFrameIndex);
        tolua_function(tolua_S,"setTween",lua_cocos2dx_studio_Frame_setTween);
        tolua_function(tolua_S,"getTimeline",lua_cocos2dx_studio_Frame_getTimeline);
        tolua_function(tolua_S,"getNode",lua_cocos2dx_studio_Frame_getNode);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::Frame).name();
    g_luaType[typeName] = "ccs.Frame";
    g_typeCast["Frame"] = "ccs.Frame";
    return 1;
}

int lua_cocos2dx_studio_VisibleFrame_isVisible(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::VisibleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.VisibleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::VisibleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_VisibleFrame_isVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isVisible();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.VisibleFrame:isVisible",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_VisibleFrame_isVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_VisibleFrame_setVisible(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::VisibleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.VisibleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::VisibleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_VisibleFrame_setVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.VisibleFrame:setVisible");
        if(!ok)
            return 0;
        cobj->setVisible(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.VisibleFrame:setVisible",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_VisibleFrame_setVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_VisibleFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.VisibleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::VisibleFrame* ret = cocostudio::timeline::VisibleFrame::create();
        object_to_luaval<cocostudio::timeline::VisibleFrame>(tolua_S, "ccs.VisibleFrame",(cocostudio::timeline::VisibleFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.VisibleFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_VisibleFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_VisibleFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::VisibleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::VisibleFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.VisibleFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.VisibleFrame:VisibleFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_VisibleFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_VisibleFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (VisibleFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_VisibleFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.VisibleFrame");
    tolua_cclass(tolua_S,"VisibleFrame","ccs.VisibleFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"VisibleFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_VisibleFrame_constructor);
        tolua_function(tolua_S,"isVisible",lua_cocos2dx_studio_VisibleFrame_isVisible);
        tolua_function(tolua_S,"setVisible",lua_cocos2dx_studio_VisibleFrame_setVisible);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_VisibleFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::VisibleFrame).name();
    g_luaType[typeName] = "ccs.VisibleFrame";
    g_typeCast["VisibleFrame"] = "ccs.VisibleFrame";
    return 1;
}

int lua_cocos2dx_studio_TextureFrame_getTextureName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::TextureFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.TextureFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::TextureFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_TextureFrame_getTextureName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getTextureName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureFrame:getTextureName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureFrame_getTextureName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_TextureFrame_setNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::TextureFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.TextureFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::TextureFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_TextureFrame_setNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
            return 0;
        cobj->setNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureFrame:setNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureFrame_setNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_TextureFrame_setTextureName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::TextureFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.TextureFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::TextureFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_TextureFrame_setTextureName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.TextureFrame:setTextureName");
        if(!ok)
            return 0;
        cobj->setTextureName(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureFrame:setTextureName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureFrame_setTextureName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_TextureFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.TextureFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::TextureFrame* ret = cocostudio::timeline::TextureFrame::create();
        object_to_luaval<cocostudio::timeline::TextureFrame>(tolua_S, "ccs.TextureFrame",(cocostudio::timeline::TextureFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.TextureFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_TextureFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::TextureFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::TextureFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.TextureFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureFrame:TextureFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_TextureFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_TextureFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TextureFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_TextureFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.TextureFrame");
    tolua_cclass(tolua_S,"TextureFrame","ccs.TextureFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"TextureFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_TextureFrame_constructor);
        tolua_function(tolua_S,"getTextureName",lua_cocos2dx_studio_TextureFrame_getTextureName);
        tolua_function(tolua_S,"setNode",lua_cocos2dx_studio_TextureFrame_setNode);
        tolua_function(tolua_S,"setTextureName",lua_cocos2dx_studio_TextureFrame_setTextureName);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_TextureFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::TextureFrame).name();
    g_luaType[typeName] = "ccs.TextureFrame";
    g_typeCast["TextureFrame"] = "ccs.TextureFrame";
    return 1;
}

int lua_cocos2dx_studio_RotationFrame_setRotation(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::RotationFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.RotationFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::RotationFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_RotationFrame_setRotation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.RotationFrame:setRotation");
        if(!ok)
            return 0;
        cobj->setRotation(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.RotationFrame:setRotation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_RotationFrame_setRotation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_RotationFrame_getRotation(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::RotationFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.RotationFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::RotationFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_RotationFrame_getRotation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getRotation();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.RotationFrame:getRotation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_RotationFrame_getRotation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_RotationFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.RotationFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::RotationFrame* ret = cocostudio::timeline::RotationFrame::create();
        object_to_luaval<cocostudio::timeline::RotationFrame>(tolua_S, "ccs.RotationFrame",(cocostudio::timeline::RotationFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.RotationFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_RotationFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_RotationFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::RotationFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::RotationFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.RotationFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.RotationFrame:RotationFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_RotationFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_RotationFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RotationFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_RotationFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.RotationFrame");
    tolua_cclass(tolua_S,"RotationFrame","ccs.RotationFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"RotationFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_RotationFrame_constructor);
        tolua_function(tolua_S,"setRotation",lua_cocos2dx_studio_RotationFrame_setRotation);
        tolua_function(tolua_S,"getRotation",lua_cocos2dx_studio_RotationFrame_getRotation);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_RotationFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::RotationFrame).name();
    g_luaType[typeName] = "ccs.RotationFrame";
    g_typeCast["RotationFrame"] = "ccs.RotationFrame";
    return 1;
}

int lua_cocos2dx_studio_SkewFrame_getSkewY(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkewFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SkewFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::SkewFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SkewFrame_getSkewY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getSkewY();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:getSkewY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SkewFrame_getSkewY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SkewFrame_setSkewX(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkewFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SkewFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::SkewFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SkewFrame_setSkewX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.SkewFrame:setSkewX");
        if(!ok)
            return 0;
        cobj->setSkewX(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:setSkewX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SkewFrame_setSkewX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SkewFrame_setSkewY(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkewFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SkewFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::SkewFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SkewFrame_setSkewY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.SkewFrame:setSkewY");
        if(!ok)
            return 0;
        cobj->setSkewY(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:setSkewY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SkewFrame_setSkewY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SkewFrame_getSkewX(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkewFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SkewFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::SkewFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_SkewFrame_getSkewX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getSkewX();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:getSkewX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SkewFrame_getSkewX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_SkewFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.SkewFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::SkewFrame* ret = cocostudio::timeline::SkewFrame::create();
        object_to_luaval<cocostudio::timeline::SkewFrame>(tolua_S, "ccs.SkewFrame",(cocostudio::timeline::SkewFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SkewFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SkewFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_SkewFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkewFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::SkewFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.SkewFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:SkewFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_SkewFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_SkewFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SkewFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_SkewFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.SkewFrame");
    tolua_cclass(tolua_S,"SkewFrame","ccs.SkewFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"SkewFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_SkewFrame_constructor);
        tolua_function(tolua_S,"getSkewY",lua_cocos2dx_studio_SkewFrame_getSkewY);
        tolua_function(tolua_S,"setSkewX",lua_cocos2dx_studio_SkewFrame_setSkewX);
        tolua_function(tolua_S,"setSkewY",lua_cocos2dx_studio_SkewFrame_setSkewY);
        tolua_function(tolua_S,"getSkewX",lua_cocos2dx_studio_SkewFrame_getSkewX);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_SkewFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::SkewFrame).name();
    g_luaType[typeName] = "ccs.SkewFrame";
    g_typeCast["SkewFrame"] = "ccs.SkewFrame";
    return 1;
}

int lua_cocos2dx_studio_RotationSkewFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.RotationSkewFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::RotationSkewFrame* ret = cocostudio::timeline::RotationSkewFrame::create();
        object_to_luaval<cocostudio::timeline::RotationSkewFrame>(tolua_S, "ccs.RotationSkewFrame",(cocostudio::timeline::RotationSkewFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.RotationSkewFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_RotationSkewFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_RotationSkewFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::RotationSkewFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::RotationSkewFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.RotationSkewFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.RotationSkewFrame:RotationSkewFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_RotationSkewFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_RotationSkewFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RotationSkewFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_RotationSkewFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.RotationSkewFrame");
    tolua_cclass(tolua_S,"RotationSkewFrame","ccs.RotationSkewFrame","ccs.SkewFrame",nullptr);

    tolua_beginmodule(tolua_S,"RotationSkewFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_RotationSkewFrame_constructor);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_RotationSkewFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::RotationSkewFrame).name();
    g_luaType[typeName] = "ccs.RotationSkewFrame";
    g_typeCast["RotationSkewFrame"] = "ccs.RotationSkewFrame";
    return 1;
}

int lua_cocos2dx_studio_PositionFrame_getX(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::PositionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_PositionFrame_getX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getX();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:getX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_PositionFrame_getX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_PositionFrame_getY(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::PositionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_PositionFrame_getY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getY();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:getY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_PositionFrame_getY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_PositionFrame_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::PositionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_PositionFrame_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0, "ccs.PositionFrame:setPosition");
        if(!ok)
            return 0;
        cobj->setPosition(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:setPosition",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_PositionFrame_setPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_PositionFrame_setX(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::PositionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_PositionFrame_setX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.PositionFrame:setX");
        if(!ok)
            return 0;
        cobj->setX(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:setX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_PositionFrame_setX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_PositionFrame_setY(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::PositionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_PositionFrame_setY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.PositionFrame:setY");
        if(!ok)
            return 0;
        cobj->setY(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:setY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_PositionFrame_setY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_PositionFrame_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::PositionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_PositionFrame_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Point ret = cobj->getPosition();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:getPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_PositionFrame_getPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_PositionFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::PositionFrame* ret = cocostudio::timeline::PositionFrame::create();
        object_to_luaval<cocostudio::timeline::PositionFrame>(tolua_S, "ccs.PositionFrame",(cocostudio::timeline::PositionFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.PositionFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_PositionFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_PositionFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::PositionFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.PositionFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:PositionFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_PositionFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_PositionFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PositionFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_PositionFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.PositionFrame");
    tolua_cclass(tolua_S,"PositionFrame","ccs.PositionFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"PositionFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_PositionFrame_constructor);
        tolua_function(tolua_S,"getX",lua_cocos2dx_studio_PositionFrame_getX);
        tolua_function(tolua_S,"getY",lua_cocos2dx_studio_PositionFrame_getY);
        tolua_function(tolua_S,"setPosition",lua_cocos2dx_studio_PositionFrame_setPosition);
        tolua_function(tolua_S,"setX",lua_cocos2dx_studio_PositionFrame_setX);
        tolua_function(tolua_S,"setY",lua_cocos2dx_studio_PositionFrame_setY);
        tolua_function(tolua_S,"getPosition",lua_cocos2dx_studio_PositionFrame_getPosition);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_PositionFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::PositionFrame).name();
    g_luaType[typeName] = "ccs.PositionFrame";
    g_typeCast["PositionFrame"] = "ccs.PositionFrame";
    return 1;
}

int lua_cocos2dx_studio_ScaleFrame_setScaleY(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ScaleFrame_setScaleY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ScaleFrame:setScaleY");
        if(!ok)
            return 0;
        cobj->setScaleY(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:setScaleY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ScaleFrame_setScaleY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ScaleFrame_setScaleX(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ScaleFrame_setScaleX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ScaleFrame:setScaleX");
        if(!ok)
            return 0;
        cobj->setScaleX(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:setScaleX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ScaleFrame_setScaleX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ScaleFrame_getScaleY(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ScaleFrame_getScaleY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getScaleY();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:getScaleY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ScaleFrame_getScaleY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ScaleFrame_getScaleX(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ScaleFrame_getScaleX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getScaleX();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:getScaleX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ScaleFrame_getScaleX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ScaleFrame_setScale(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ScaleFrame_setScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ScaleFrame:setScale");
        if(!ok)
            return 0;
        cobj->setScale(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:setScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ScaleFrame_setScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ScaleFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::ScaleFrame* ret = cocostudio::timeline::ScaleFrame::create();
        object_to_luaval<cocostudio::timeline::ScaleFrame>(tolua_S, "ccs.ScaleFrame",(cocostudio::timeline::ScaleFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ScaleFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ScaleFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ScaleFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ScaleFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::ScaleFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ScaleFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:ScaleFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ScaleFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ScaleFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ScaleFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ScaleFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ScaleFrame");
    tolua_cclass(tolua_S,"ScaleFrame","ccs.ScaleFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"ScaleFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ScaleFrame_constructor);
        tolua_function(tolua_S,"setScaleY",lua_cocos2dx_studio_ScaleFrame_setScaleY);
        tolua_function(tolua_S,"setScaleX",lua_cocos2dx_studio_ScaleFrame_setScaleX);
        tolua_function(tolua_S,"getScaleY",lua_cocos2dx_studio_ScaleFrame_getScaleY);
        tolua_function(tolua_S,"getScaleX",lua_cocos2dx_studio_ScaleFrame_getScaleX);
        tolua_function(tolua_S,"setScale",lua_cocos2dx_studio_ScaleFrame_setScale);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ScaleFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::ScaleFrame).name();
    g_luaType[typeName] = "ccs.ScaleFrame";
    g_typeCast["ScaleFrame"] = "ccs.ScaleFrame";
    return 1;
}

int lua_cocos2dx_studio_AnchorPointFrame_setAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::AnchorPointFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AnchorPointFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::AnchorPointFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_AnchorPointFrame_setAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0, "ccs.AnchorPointFrame:setAnchorPoint");
        if(!ok)
            return 0;
        cobj->setAnchorPoint(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnchorPointFrame:setAnchorPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnchorPointFrame_setAnchorPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_AnchorPointFrame_getAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::AnchorPointFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AnchorPointFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::AnchorPointFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_AnchorPointFrame_getAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Point ret = cobj->getAnchorPoint();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnchorPointFrame:getAnchorPoint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnchorPointFrame_getAnchorPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_AnchorPointFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.AnchorPointFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::AnchorPointFrame* ret = cocostudio::timeline::AnchorPointFrame::create();
        object_to_luaval<cocostudio::timeline::AnchorPointFrame>(tolua_S, "ccs.AnchorPointFrame",(cocostudio::timeline::AnchorPointFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.AnchorPointFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnchorPointFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_AnchorPointFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::AnchorPointFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::AnchorPointFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.AnchorPointFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnchorPointFrame:AnchorPointFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_AnchorPointFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_AnchorPointFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AnchorPointFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_AnchorPointFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.AnchorPointFrame");
    tolua_cclass(tolua_S,"AnchorPointFrame","ccs.AnchorPointFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"AnchorPointFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_AnchorPointFrame_constructor);
        tolua_function(tolua_S,"setAnchorPoint",lua_cocos2dx_studio_AnchorPointFrame_setAnchorPoint);
        tolua_function(tolua_S,"getAnchorPoint",lua_cocos2dx_studio_AnchorPointFrame_getAnchorPoint);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_AnchorPointFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::AnchorPointFrame).name();
    g_luaType[typeName] = "ccs.AnchorPointFrame";
    g_typeCast["AnchorPointFrame"] = "ccs.AnchorPointFrame";
    return 1;
}

int lua_cocos2dx_studio_InnerActionFrame_getInnerActionType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::InnerActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.InnerActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::InnerActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_InnerActionFrame_getInnerActionType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getInnerActionType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:getInnerActionType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_InnerActionFrame_getInnerActionType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_InnerActionFrame_setStartFrameIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::InnerActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.InnerActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::InnerActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_InnerActionFrame_setStartFrameIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.InnerActionFrame:setStartFrameIndex");
        if(!ok)
            return 0;
        cobj->setStartFrameIndex(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:setStartFrameIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_InnerActionFrame_setStartFrameIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_InnerActionFrame_setInnerActionType(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::InnerActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.InnerActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::InnerActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_InnerActionFrame_setInnerActionType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::timeline::InnerActionType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.InnerActionFrame:setInnerActionType");
        if(!ok)
            return 0;
        cobj->setInnerActionType(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:setInnerActionType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_InnerActionFrame_setInnerActionType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_InnerActionFrame_getStartFrameIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::InnerActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.InnerActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::InnerActionFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_InnerActionFrame_getStartFrameIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getStartFrameIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:getStartFrameIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_InnerActionFrame_getStartFrameIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_InnerActionFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.InnerActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::InnerActionFrame* ret = cocostudio::timeline::InnerActionFrame::create();
        object_to_luaval<cocostudio::timeline::InnerActionFrame>(tolua_S, "ccs.InnerActionFrame",(cocostudio::timeline::InnerActionFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.InnerActionFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_InnerActionFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_InnerActionFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::InnerActionFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::InnerActionFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.InnerActionFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:InnerActionFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_InnerActionFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_InnerActionFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (InnerActionFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_InnerActionFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.InnerActionFrame");
    tolua_cclass(tolua_S,"InnerActionFrame","ccs.InnerActionFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"InnerActionFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_InnerActionFrame_constructor);
        tolua_function(tolua_S,"getInnerActionType",lua_cocos2dx_studio_InnerActionFrame_getInnerActionType);
        tolua_function(tolua_S,"setStartFrameIndex",lua_cocos2dx_studio_InnerActionFrame_setStartFrameIndex);
        tolua_function(tolua_S,"setInnerActionType",lua_cocos2dx_studio_InnerActionFrame_setInnerActionType);
        tolua_function(tolua_S,"getStartFrameIndex",lua_cocos2dx_studio_InnerActionFrame_getStartFrameIndex);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_InnerActionFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::InnerActionFrame).name();
    g_luaType[typeName] = "ccs.InnerActionFrame";
    g_typeCast["InnerActionFrame"] = "ccs.InnerActionFrame";
    return 1;
}

int lua_cocos2dx_studio_ColorFrame_getAlpha(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ColorFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ColorFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ColorFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ColorFrame_getAlpha'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        uint16_t ret = cobj->getAlpha();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ColorFrame:getAlpha",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ColorFrame_getAlpha'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ColorFrame_getColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ColorFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ColorFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ColorFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ColorFrame_getColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Color3B ret = cobj->getColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ColorFrame:getColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ColorFrame_getColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ColorFrame_setAlpha(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ColorFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ColorFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ColorFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ColorFrame_setAlpha'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "ccs.ColorFrame:setAlpha");
        if(!ok)
            return 0;
        cobj->setAlpha(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ColorFrame:setAlpha",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ColorFrame_setAlpha'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ColorFrame_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ColorFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ColorFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ColorFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ColorFrame_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccs.ColorFrame:setColor");
        if(!ok)
            return 0;
        cobj->setColor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ColorFrame:setColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ColorFrame_setColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ColorFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ColorFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::ColorFrame* ret = cocostudio::timeline::ColorFrame::create();
        object_to_luaval<cocostudio::timeline::ColorFrame>(tolua_S, "ccs.ColorFrame",(cocostudio::timeline::ColorFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ColorFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ColorFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ColorFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ColorFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::ColorFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ColorFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ColorFrame:ColorFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ColorFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ColorFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ColorFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ColorFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ColorFrame");
    tolua_cclass(tolua_S,"ColorFrame","ccs.ColorFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"ColorFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ColorFrame_constructor);
        tolua_function(tolua_S,"getAlpha",lua_cocos2dx_studio_ColorFrame_getAlpha);
        tolua_function(tolua_S,"getColor",lua_cocos2dx_studio_ColorFrame_getColor);
        tolua_function(tolua_S,"setAlpha",lua_cocos2dx_studio_ColorFrame_setAlpha);
        tolua_function(tolua_S,"setColor",lua_cocos2dx_studio_ColorFrame_setColor);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ColorFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::ColorFrame).name();
    g_luaType[typeName] = "ccs.ColorFrame";
    g_typeCast["ColorFrame"] = "ccs.ColorFrame";
    return 1;
}

int lua_cocos2dx_studio_EventFrame_setEvent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::EventFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.EventFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::EventFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_EventFrame_setEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.EventFrame:setEvent");
        if(!ok)
            return 0;
        cobj->setEvent(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.EventFrame:setEvent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_EventFrame_setEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_EventFrame_getEvent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::EventFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.EventFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::EventFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_EventFrame_getEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getEvent();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.EventFrame:getEvent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_EventFrame_getEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_EventFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.EventFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::EventFrame* ret = cocostudio::timeline::EventFrame::create();
        object_to_luaval<cocostudio::timeline::EventFrame>(tolua_S, "ccs.EventFrame",(cocostudio::timeline::EventFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.EventFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_EventFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_EventFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::EventFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::EventFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.EventFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.EventFrame:EventFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_EventFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_EventFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_EventFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.EventFrame");
    tolua_cclass(tolua_S,"EventFrame","ccs.EventFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"EventFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_EventFrame_constructor);
        tolua_function(tolua_S,"setEvent",lua_cocos2dx_studio_EventFrame_setEvent);
        tolua_function(tolua_S,"getEvent",lua_cocos2dx_studio_EventFrame_getEvent);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_EventFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::EventFrame).name();
    g_luaType[typeName] = "ccs.EventFrame";
    g_typeCast["EventFrame"] = "ccs.EventFrame";
    return 1;
}

int lua_cocos2dx_studio_ZOrderFrame_getZOrder(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ZOrderFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ZOrderFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ZOrderFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ZOrderFrame_getZOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getZOrder();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ZOrderFrame:getZOrder",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ZOrderFrame_getZOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ZOrderFrame_setZOrder(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ZOrderFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ZOrderFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ZOrderFrame*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ZOrderFrame_setZOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ZOrderFrame:setZOrder");
        if(!ok)
            return 0;
        cobj->setZOrder(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ZOrderFrame:setZOrder",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ZOrderFrame_setZOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ZOrderFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ZOrderFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::ZOrderFrame* ret = cocostudio::timeline::ZOrderFrame::create();
        object_to_luaval<cocostudio::timeline::ZOrderFrame>(tolua_S, "ccs.ZOrderFrame",(cocostudio::timeline::ZOrderFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ZOrderFrame:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ZOrderFrame_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ZOrderFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ZOrderFrame* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::ZOrderFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ZOrderFrame");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ZOrderFrame:ZOrderFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ZOrderFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ZOrderFrame_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ZOrderFrame)");
    return 0;
}

int lua_register_cocos2dx_studio_ZOrderFrame(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ZOrderFrame");
    tolua_cclass(tolua_S,"ZOrderFrame","ccs.ZOrderFrame","ccs.Frame",nullptr);

    tolua_beginmodule(tolua_S,"ZOrderFrame");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ZOrderFrame_constructor);
        tolua_function(tolua_S,"getZOrder",lua_cocos2dx_studio_ZOrderFrame_getZOrder);
        tolua_function(tolua_S,"setZOrder",lua_cocos2dx_studio_ZOrderFrame_setZOrder);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ZOrderFrame_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::ZOrderFrame).name();
    g_luaType[typeName] = "ccs.ZOrderFrame";
    g_typeCast["ZOrderFrame"] = "ccs.ZOrderFrame";
    return 1;
}

int lua_cocos2dx_studio_Timeline_clone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::timeline::Timeline* ret = cobj->clone();
        object_to_luaval<cocostudio::timeline::Timeline>(tolua_S, "ccs.Timeline",(cocostudio::timeline::Timeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_gotoFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_gotoFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.Timeline:gotoFrame");
        if(!ok)
            return 0;
        cobj->gotoFrame(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:gotoFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_gotoFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_setNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_setNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
            return 0;
        cobj->setNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:setNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_setNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_getActionTimeline(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_getActionTimeline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cobj->getActionTimeline();
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:getActionTimeline",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_getActionTimeline'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_insertFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_insertFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocostudio::timeline::Frame* arg0;
        int arg1;

        ok &= luaval_to_object<cocostudio::timeline::Frame>(tolua_S, 2, "ccs.Frame",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.Timeline:insertFrame");
        if(!ok)
            return 0;
        cobj->insertFrame(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:insertFrame",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_insertFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_setActionTag(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_setActionTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.Timeline:setActionTag");
        if(!ok)
            return 0;
        cobj->setActionTag(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:setActionTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_setActionTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_addFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_addFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::timeline::Frame* arg0;

        ok &= luaval_to_object<cocostudio::timeline::Frame>(tolua_S, 2, "ccs.Frame",&arg0);
        if(!ok)
            return 0;
        cobj->addFrame(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:addFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_addFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_getFrames(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_getFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Vector<cocostudio::timeline::Frame *>& ret = cobj->getFrames();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:getFrames",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_getFrames'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_getActionTag(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_getActionTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getActionTag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:getActionTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_getActionTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_getNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_getNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->getNode();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:getNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_getNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_removeFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_removeFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::timeline::Frame* arg0;

        ok &= luaval_to_object<cocostudio::timeline::Frame>(tolua_S, 2, "ccs.Frame",&arg0);
        if(!ok)
            return 0;
        cobj->removeFrame(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:removeFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_removeFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_setActionTimeline(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_setActionTimeline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::timeline::ActionTimeline* arg0;

        ok &= luaval_to_object<cocostudio::timeline::ActionTimeline>(tolua_S, 2, "ccs.ActionTimeline",&arg0);
        if(!ok)
            return 0;
        cobj->setActionTimeline(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:setActionTimeline",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_setActionTimeline'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_stepToFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_Timeline_stepToFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.Timeline:stepToFrame");
        if(!ok)
            return 0;
        cobj->stepToFrame(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:stepToFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_stepToFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_Timeline_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::Timeline* ret = cocostudio::timeline::Timeline::create();
        object_to_luaval<cocostudio::timeline::Timeline>(tolua_S, "ccs.Timeline",(cocostudio::timeline::Timeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.Timeline:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_Timeline_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::Timeline();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Timeline");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:Timeline",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_Timeline_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_Timeline_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Timeline)");
    return 0;
}

int lua_register_cocos2dx_studio_Timeline(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.Timeline");
    tolua_cclass(tolua_S,"Timeline","ccs.Timeline","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Timeline");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_Timeline_constructor);
        tolua_function(tolua_S,"clone",lua_cocos2dx_studio_Timeline_clone);
        tolua_function(tolua_S,"gotoFrame",lua_cocos2dx_studio_Timeline_gotoFrame);
        tolua_function(tolua_S,"setNode",lua_cocos2dx_studio_Timeline_setNode);
        tolua_function(tolua_S,"getActionTimeline",lua_cocos2dx_studio_Timeline_getActionTimeline);
        tolua_function(tolua_S,"insertFrame",lua_cocos2dx_studio_Timeline_insertFrame);
        tolua_function(tolua_S,"setActionTag",lua_cocos2dx_studio_Timeline_setActionTag);
        tolua_function(tolua_S,"addFrame",lua_cocos2dx_studio_Timeline_addFrame);
        tolua_function(tolua_S,"getFrames",lua_cocos2dx_studio_Timeline_getFrames);
        tolua_function(tolua_S,"getActionTag",lua_cocos2dx_studio_Timeline_getActionTag);
        tolua_function(tolua_S,"getNode",lua_cocos2dx_studio_Timeline_getNode);
        tolua_function(tolua_S,"removeFrame",lua_cocos2dx_studio_Timeline_removeFrame);
        tolua_function(tolua_S,"setActionTimeline",lua_cocos2dx_studio_Timeline_setActionTimeline);
        tolua_function(tolua_S,"stepToFrame",lua_cocos2dx_studio_Timeline_stepToFrame);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_Timeline_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::Timeline).name();
    g_luaType[typeName] = "ccs.Timeline";
    g_typeCast["Timeline"] = "ccs.Timeline";
    return 1;
}

int lua_cocos2dx_studio_ActionTimelineData_setActionTag(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineData_setActionTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimelineData:setActionTag");
        if(!ok)
            return 0;
        cobj->setActionTag(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineData:setActionTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineData_setActionTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineData_getActionTag(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimelineData_getActionTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getActionTag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineData:getActionTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineData_getActionTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimelineData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionTimelineData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimelineData:create");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimelineData* ret = cocostudio::timeline::ActionTimelineData::create(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimelineData>(tolua_S, "ccs.ActionTimelineData",(cocostudio::timeline::ActionTimelineData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineData:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimelineData_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_studio_ActionTimelineData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionTimelineData)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionTimelineData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionTimelineData");
    tolua_cclass(tolua_S,"ActionTimelineData","ccs.ActionTimelineData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ActionTimelineData");
        tolua_function(tolua_S,"setActionTag",lua_cocos2dx_studio_ActionTimelineData_setActionTag);
        tolua_function(tolua_S,"getActionTag",lua_cocos2dx_studio_ActionTimelineData_getActionTag);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ActionTimelineData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::ActionTimelineData).name();
    g_luaType[typeName] = "ccs.ActionTimelineData";
    g_typeCast["ActionTimelineData"] = "ccs.ActionTimelineData";
    return 1;
}

int lua_cocos2dx_studio_ActionTimeline_getTimelines(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_getTimelines'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Vector<cocostudio::timeline::Timeline *>& ret = cobj->getTimelines();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getTimelines",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_getTimelines'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_getCurrentFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_getCurrentFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getCurrentFrame();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getCurrentFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_getCurrentFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_getStartFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_getStartFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getStartFrame();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getStartFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_getStartFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_pause(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->pause();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:pause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_pause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (cocostudio::timeline::Frame *)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        cobj->setFrameEventCallFunc(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setFrameEventCallFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_resume(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_resume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->resume();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:resume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_resume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_getDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_getDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getDuration();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getDuration",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_getDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_addTimeline(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_addTimeline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::timeline::Timeline* arg0;

        ok &= luaval_to_object<cocostudio::timeline::Timeline>(tolua_S, 2, "ccs.Timeline",&arg0);
        if(!ok)
            return 0;
        cobj->addTimeline(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:addTimeline",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_addTimeline'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_getEndFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_getEndFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getEndFrame();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getEndFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_getEndFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_setCurrentFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_setCurrentFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:setCurrentFrame");
        if(!ok)
            return 0;
        cobj->setCurrentFrame(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setCurrentFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_setCurrentFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_setTimeSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_setTimeSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionTimeline:setTimeSpeed");
        if(!ok)
            return 0;
        cobj->setTimeSpeed(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setTimeSpeed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_setTimeSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_setDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_setDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:setDuration");
        if(!ok)
            return 0;
        cobj->setDuration(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setDuration",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_setDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_getTimeSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_getTimeSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getTimeSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getTimeSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_getTimeSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_gotoFrameAndPause(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_gotoFrameAndPause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:gotoFrameAndPause");
        if(!ok)
            return 0;
        cobj->gotoFrameAndPause(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:gotoFrameAndPause",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_gotoFrameAndPause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_isPlaying(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_isPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:isPlaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_isPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            cobj->gotoFrameAndPlay(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            cobj->gotoFrameAndPlay(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            cobj->gotoFrameAndPlay(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "ccs.ActionTimeline:gotoFrameAndPlay");

            if (!ok) { break; }
            cobj->gotoFrameAndPlay(arg0, arg1, arg2, arg3);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionTimeline:gotoFrameAndPlay",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_removeTimeline(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_removeTimeline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::timeline::Timeline* arg0;

        ok &= luaval_to_object<cocostudio::timeline::Timeline>(tolua_S, 2, "ccs.Timeline",&arg0);
        if(!ok)
            return 0;
        cobj->removeTimeline(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:removeTimeline",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_removeTimeline'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearFrameEventCallFunc();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:clearFrameEventCallFunc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cocostudio::timeline::ActionTimeline::create();
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimeline:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_studio_ActionTimeline_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocostudio::timeline::ActionTimeline();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionTimeline");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:ActionTimeline",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_studio_ActionTimeline_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_studio_ActionTimeline_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionTimeline)");
    return 0;
}

int lua_register_cocos2dx_studio_ActionTimeline(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccs.ActionTimeline");
    tolua_cclass(tolua_S,"ActionTimeline","ccs.ActionTimeline","cc.Action",nullptr);

    tolua_beginmodule(tolua_S,"ActionTimeline");
        tolua_function(tolua_S,"new",lua_cocos2dx_studio_ActionTimeline_constructor);
        tolua_function(tolua_S,"getTimelines",lua_cocos2dx_studio_ActionTimeline_getTimelines);
        tolua_function(tolua_S,"getCurrentFrame",lua_cocos2dx_studio_ActionTimeline_getCurrentFrame);
        tolua_function(tolua_S,"getStartFrame",lua_cocos2dx_studio_ActionTimeline_getStartFrame);
        tolua_function(tolua_S,"pause",lua_cocos2dx_studio_ActionTimeline_pause);
        tolua_function(tolua_S,"setFrameEventCallFunc",lua_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc);
        tolua_function(tolua_S,"resume",lua_cocos2dx_studio_ActionTimeline_resume);
        tolua_function(tolua_S,"getDuration",lua_cocos2dx_studio_ActionTimeline_getDuration);
        tolua_function(tolua_S,"addTimeline",lua_cocos2dx_studio_ActionTimeline_addTimeline);
        tolua_function(tolua_S,"getEndFrame",lua_cocos2dx_studio_ActionTimeline_getEndFrame);
        tolua_function(tolua_S,"setCurrentFrame",lua_cocos2dx_studio_ActionTimeline_setCurrentFrame);
        tolua_function(tolua_S,"setTimeSpeed",lua_cocos2dx_studio_ActionTimeline_setTimeSpeed);
        tolua_function(tolua_S,"init",lua_cocos2dx_studio_ActionTimeline_init);
        tolua_function(tolua_S,"setDuration",lua_cocos2dx_studio_ActionTimeline_setDuration);
        tolua_function(tolua_S,"getTimeSpeed",lua_cocos2dx_studio_ActionTimeline_getTimeSpeed);
        tolua_function(tolua_S,"gotoFrameAndPause",lua_cocos2dx_studio_ActionTimeline_gotoFrameAndPause);
        tolua_function(tolua_S,"isPlaying",lua_cocos2dx_studio_ActionTimeline_isPlaying);
        tolua_function(tolua_S,"gotoFrameAndPlay",lua_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay);
        tolua_function(tolua_S,"removeTimeline",lua_cocos2dx_studio_ActionTimeline_removeTimeline);
        tolua_function(tolua_S,"clearFrameEventCallFunc",lua_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc);
        tolua_function(tolua_S,"create", lua_cocos2dx_studio_ActionTimeline_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocostudio::timeline::ActionTimeline).name();
    g_luaType[typeName] = "ccs.ActionTimeline";
    g_typeCast["ActionTimeline"] = "ccs.ActionTimeline";
    return 1;
}
TOLUA_API int register_all_cocos2dx_studio(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccs",0);
	tolua_beginmodule(tolua_S,"ccs");

	lua_register_cocos2dx_studio_ActionFrame(tolua_S);
	lua_register_cocos2dx_studio_ActionRotationFrame(tolua_S);
	lua_register_cocos2dx_studio_Frame(tolua_S);
	lua_register_cocos2dx_studio_ScaleFrame(tolua_S);
	lua_register_cocos2dx_studio_Tween(tolua_S);
	lua_register_cocos2dx_studio_ContourData(tolua_S);
	lua_register_cocos2dx_studio_ComAudio(tolua_S);
	lua_register_cocos2dx_studio_ActionTimeline(tolua_S);
	lua_register_cocos2dx_studio_InnerActionFrame(tolua_S);
	lua_register_cocos2dx_studio_ActionTimelineData(tolua_S);
	lua_register_cocos2dx_studio_DisplayData(tolua_S);
	lua_register_cocos2dx_studio_ArmatureDisplayData(tolua_S);
	lua_register_cocos2dx_studio_MovementData(tolua_S);
	lua_register_cocos2dx_studio_ArmatureDataManager(tolua_S);
	lua_register_cocos2dx_studio_ColorFrame(tolua_S);
	lua_register_cocos2dx_studio_BatchNode(tolua_S);
	lua_register_cocos2dx_studio_BaseData(tolua_S);
	lua_register_cocos2dx_studio_FrameData(tolua_S);
	lua_register_cocos2dx_studio_Timeline(tolua_S);
	lua_register_cocos2dx_studio_ComController(tolua_S);
	lua_register_cocos2dx_studio_BoneData(tolua_S);
	lua_register_cocos2dx_studio_ComRender(tolua_S);
	lua_register_cocos2dx_studio_SkewFrame(tolua_S);
	lua_register_cocos2dx_studio_RotationSkewFrame(tolua_S);
	lua_register_cocos2dx_studio_ParticleDisplayData(tolua_S);
	lua_register_cocos2dx_studio_ActionFadeFrame(tolua_S);
	lua_register_cocos2dx_studio_VisibleFrame(tolua_S);
	lua_register_cocos2dx_studio_PositionFrame(tolua_S);
	lua_register_cocos2dx_studio_RotationFrame(tolua_S);
	lua_register_cocos2dx_studio_ArmatureData(tolua_S);
	lua_register_cocos2dx_studio_ActionObject(tolua_S);
	lua_register_cocos2dx_studio_Skin(tolua_S);
	lua_register_cocos2dx_studio_MovementBoneData(tolua_S);
	lua_register_cocos2dx_studio_EventFrame(tolua_S);
	lua_register_cocos2dx_studio_DisplayManager(tolua_S);
	lua_register_cocos2dx_studio_GUIReader(tolua_S);
	lua_register_cocos2dx_studio_ArmatureAnimation(tolua_S);
	lua_register_cocos2dx_studio_Armature(tolua_S);
	lua_register_cocos2dx_studio_SpriteDisplayData(tolua_S);
	lua_register_cocos2dx_studio_ActionManagerEx(tolua_S);
	lua_register_cocos2dx_studio_Bone(tolua_S);
	lua_register_cocos2dx_studio_ZOrderFrame(tolua_S);
	lua_register_cocos2dx_studio_ActionTintFrame(tolua_S);
	lua_register_cocos2dx_studio_TextureData(tolua_S);
	lua_register_cocos2dx_studio_ActionMoveFrame(tolua_S);
	lua_register_cocos2dx_studio_SceneReader(tolua_S);
	lua_register_cocos2dx_studio_ActionTimelineCache(tolua_S);
	lua_register_cocos2dx_studio_AnimationData(tolua_S);
	lua_register_cocos2dx_studio_AnchorPointFrame(tolua_S);
	lua_register_cocos2dx_studio_ActionScaleFrame(tolua_S);
	lua_register_cocos2dx_studio_TextureFrame(tolua_S);
	lua_register_cocos2dx_studio_ComAttribute(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

