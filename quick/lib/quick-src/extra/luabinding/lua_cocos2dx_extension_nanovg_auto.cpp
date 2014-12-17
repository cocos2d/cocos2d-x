#include "lua_cocos2dx_extension_nanovg_auto.hpp"
#include "nanovg/nanonode/NVGDrawNode.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



static int lua_cocos2dx_extension_nanovg_NVGNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NVGNode)");
    return 0;
}

int lua_register_cocos2dx_extension_nanovg_NVGNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.NVGNode");
    tolua_cclass(tolua_S,"NVGNode","cc.NVGNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"NVGNode");
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::NVGNode).name();
    g_luaType[typeName] = "cc.NVGNode";
    g_typeCast["NVGNode"] = "cc.NVGNode";
    return 1;
}

int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawArc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawArc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        int arg4;
        cocos2d::Color4F arg5;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawArc");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.NVGDrawNode:drawArc");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.NVGDrawNode:drawArc");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.NVGDrawNode:drawArc");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.NVGDrawNode:drawArc");

        ok &=luaval_to_color4f(tolua_S, 7, &arg5, "cc.NVGDrawNode:drawArc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawArc'", nullptr);
            return 0;
        }
        cobj->drawArc(arg0, arg1, arg2, arg3, arg4, arg5);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawArc",argc, 6);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawArc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawLine(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawLine'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Color4F arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawLine");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.NVGDrawNode:drawLine");

        ok &=luaval_to_color4f(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawLine");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawLine'", nullptr);
            return 0;
        }
        cobj->drawLine(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawLine",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawLine'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawRect'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Color4F arg1;
            ok &=luaval_to_color4f(tolua_S, 3, &arg1, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cobj->drawRect(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Color4F arg2;
            ok &=luaval_to_color4f(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cobj->drawRect(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Color4F arg4;
            ok &=luaval_to_color4f(tolua_S, 6, &arg4, "cc.NVGDrawNode:drawRect");

            if (!ok) { break; }
            cobj->drawRect(arg0, arg1, arg2, arg3, arg4);
            return 0;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.NVGDrawNode:drawRect",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.NVGDrawNode:setLineColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineColor'", nullptr);
            return 0;
        }
        cobj->setLineColor(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:setLineColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidCircle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidCircle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        double arg1;
        cocos2d::Color4F arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawSolidCircle");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.NVGDrawNode:drawSolidCircle");

        ok &=luaval_to_color4f(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawSolidCircle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidCircle'", nullptr);
            return 0;
        }
        cobj->drawSolidCircle(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawSolidCircle",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidCircle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineWidth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineWidth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NVGDrawNode:setLineWidth");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineWidth'", nullptr);
            return 0;
        }
        cobj->setLineWidth(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:setLineWidth",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineWidth'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawDot(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawDot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        double arg1;
        cocos2d::Color4F arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawDot");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.NVGDrawNode:drawDot");

        ok &=luaval_to_color4f(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawDot");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawDot'", nullptr);
            return 0;
        }
        cobj->drawDot(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawDot",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawDot'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_setOpacityf(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setOpacityf'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NVGDrawNode:setOpacityf");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setOpacityf'", nullptr);
            return 0;
        }
        cobj->setOpacityf(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:setOpacityf",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setOpacityf'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_addPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_addPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:addPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_addPoint'", nullptr);
            return 0;
        }
        cobj->addPoint(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:addPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_addPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_setFillColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setFillColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.NVGDrawNode:setFillColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setFillColor'", nullptr);
            return 0;
        }
        cobj->setFillColor(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:setFillColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setFillColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCircle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCircle'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            cocos2d::Color4F arg2;
            ok &=luaval_to_color4f(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            cobj->drawCircle(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 8) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            unsigned int arg3;
            ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            bool arg4;
            ok &= luaval_to_boolean(tolua_S, 6,&arg4, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            double arg5;
            ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            double arg6;
            ok &= luaval_to_number(tolua_S, 8,&arg6, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            cocos2d::Color4F arg7;
            ok &=luaval_to_color4f(tolua_S, 9, &arg7, "cc.NVGDrawNode:drawCircle");

            if (!ok) { break; }
            cobj->drawCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            return 0;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.NVGDrawNode:drawCircle",argc, 8);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCircle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawQuadBezier(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawQuadBezier'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Color4F arg3;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawQuadBezier");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.NVGDrawNode:drawQuadBezier");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawQuadBezier");

        ok &=luaval_to_color4f(tolua_S, 5, &arg3, "cc.NVGDrawNode:drawQuadBezier");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawQuadBezier'", nullptr);
            return 0;
        }
        cobj->drawQuadBezier(arg0, arg1, arg2, arg3);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawQuadBezier",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawQuadBezier'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.NVGDrawNode:setColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setColor'", nullptr);
            return 0;
        }
        cobj->setColor(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:setColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_clear(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Color4F arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawSolidRect");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.NVGDrawNode:drawSolidRect");

        ok &=luaval_to_color4f(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawSolidRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidRect'", nullptr);
            return 0;
        }
        cobj->drawSolidRect(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawSolidRect",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Color4F arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawPoint");

        ok &=luaval_to_color4f(tolua_S, 3, &arg1, "cc.NVGDrawNode:drawPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawPoint'", nullptr);
            return 0;
        }
        cobj->drawPoint(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawPoint",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCubicBezier(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCubicBezier'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        cocos2d::Color4F arg4;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.NVGDrawNode:drawCubicBezier");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.NVGDrawNode:drawCubicBezier");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawCubicBezier");

        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.NVGDrawNode:drawCubicBezier");

        ok &=luaval_to_color4f(tolua_S, 6, &arg4, "cc.NVGDrawNode:drawCubicBezier");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCubicBezier'", nullptr);
            return 0;
        }
        cobj->drawCubicBezier(arg0, arg1, arg2, arg3, arg4);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawCubicBezier",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCubicBezier'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_setRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NVGDrawNode:setRadius");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setRadius'", nullptr);
            return 0;
        }
        cobj->setRadius(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:setRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_setFill(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setFill'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.NVGDrawNode:setFill");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setFill'", nullptr);
            return 0;
        }
        cobj->setFill(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:setFill",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_setFill'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_nanovg_NVGDrawNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_create'", nullptr);
            return 0;
        }
        cocos2d::extension::NVGDrawNode* ret = cocos2d::extension::NVGDrawNode::create();
        object_to_luaval<cocos2d::extension::NVGDrawNode>(tolua_S, "cc.NVGDrawNode",(cocos2d::extension::NVGDrawNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.NVGDrawNode:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_nanovg_NVGDrawNode_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extension_nanovg_NVGDrawNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NVGDrawNode)");
    return 0;
}

int lua_register_cocos2dx_extension_nanovg_NVGDrawNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.NVGDrawNode");
    tolua_cclass(tolua_S,"NVGDrawNode","cc.NVGDrawNode","cc.NVGNode",nullptr);

    tolua_beginmodule(tolua_S,"NVGDrawNode");
        tolua_function(tolua_S,"drawArc",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawArc);
        tolua_function(tolua_S,"drawLine",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawLine);
        tolua_function(tolua_S,"drawRect",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawRect);
        tolua_function(tolua_S,"setLineColor",lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineColor);
        tolua_function(tolua_S,"drawSolidCircle",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidCircle);
        tolua_function(tolua_S,"setLineWidth",lua_cocos2dx_extension_nanovg_NVGDrawNode_setLineWidth);
        tolua_function(tolua_S,"drawDot",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawDot);
        tolua_function(tolua_S,"setOpacityf",lua_cocos2dx_extension_nanovg_NVGDrawNode_setOpacityf);
        tolua_function(tolua_S,"addPoint",lua_cocos2dx_extension_nanovg_NVGDrawNode_addPoint);
        tolua_function(tolua_S,"setFillColor",lua_cocos2dx_extension_nanovg_NVGDrawNode_setFillColor);
        tolua_function(tolua_S,"drawCircle",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCircle);
        tolua_function(tolua_S,"drawQuadBezier",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawQuadBezier);
        tolua_function(tolua_S,"setColor",lua_cocos2dx_extension_nanovg_NVGDrawNode_setColor);
        tolua_function(tolua_S,"clear",lua_cocos2dx_extension_nanovg_NVGDrawNode_clear);
        tolua_function(tolua_S,"drawSolidRect",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawSolidRect);
        tolua_function(tolua_S,"drawPoint",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawPoint);
        tolua_function(tolua_S,"drawCubicBezier",lua_cocos2dx_extension_nanovg_NVGDrawNode_drawCubicBezier);
        tolua_function(tolua_S,"setRadius",lua_cocos2dx_extension_nanovg_NVGDrawNode_setRadius);
        tolua_function(tolua_S,"setFill",lua_cocos2dx_extension_nanovg_NVGDrawNode_setFill);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_nanovg_NVGDrawNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::NVGDrawNode).name();
    g_luaType[typeName] = "cc.NVGDrawNode";
    g_typeCast["NVGDrawNode"] = "cc.NVGDrawNode";
    return 1;
}
TOLUA_API int register_all_cocos2dx_extension_nanovg(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_extension_nanovg_NVGNode(tolua_S);
	lua_register_cocos2dx_extension_nanovg_NVGDrawNode(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

