#include "lua_cocos2dx_spine_auto.hpp"
#include "spine-cocos2dx.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_spine_Skeleton_setToSetupPose(lua_State* tolua_S)
{
    int argc = 0;
    spine::Skeleton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.Skeleton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::Skeleton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_Skeleton_setToSetupPose'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->setToSetupPose();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setToSetupPose",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_Skeleton_setToSetupPose'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_Skeleton_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    spine::Skeleton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.Skeleton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::Skeleton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_Skeleton_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR BlendFunc;
        if(!ok)
            return 0;
        cobj->setBlendFunc(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setBlendFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_Skeleton_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_Skeleton_onDraw(lua_State* tolua_S)
{
    int argc = 0;
    spine::Skeleton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.Skeleton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::Skeleton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_Skeleton_onDraw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Mat4 arg0;
        bool arg1;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->onDraw(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onDraw",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_Skeleton_onDraw'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_Skeleton_setSlotsToSetupPose(lua_State* tolua_S)
{
    int argc = 0;
    spine::Skeleton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.Skeleton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::Skeleton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_Skeleton_setSlotsToSetupPose'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->setSlotsToSetupPose();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSlotsToSetupPose",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_Skeleton_setSlotsToSetupPose'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_Skeleton_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    spine::Skeleton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.Skeleton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::Skeleton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_Skeleton_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBlendFunc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_Skeleton_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_Skeleton_setSkin(lua_State* tolua_S)
{
    int argc = 0;
    spine::Skeleton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.Skeleton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::Skeleton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_Skeleton_setSkin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        bool ret = cobj->setSkin(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSkin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_Skeleton_setSkin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_Skeleton_setBonesToSetupPose(lua_State* tolua_S)
{
    int argc = 0;
    spine::Skeleton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.Skeleton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::Skeleton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_Skeleton_setBonesToSetupPose'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->setBonesToSetupPose();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setBonesToSetupPose",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_Skeleton_setBonesToSetupPose'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_spine_Skeleton_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Skeleton)");
    return 0;
}

int lua_register_cocos2dx_spine_Skeleton(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sp.Skeleton");
    tolua_cclass(tolua_S,"Skeleton","sp.Skeleton","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"Skeleton");
        tolua_function(tolua_S,"setToSetupPose",lua_cocos2dx_spine_Skeleton_setToSetupPose);
        tolua_function(tolua_S,"setBlendFunc",lua_cocos2dx_spine_Skeleton_setBlendFunc);
        tolua_function(tolua_S,"onDraw",lua_cocos2dx_spine_Skeleton_onDraw);
        tolua_function(tolua_S,"setSlotsToSetupPose",lua_cocos2dx_spine_Skeleton_setSlotsToSetupPose);
        tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_spine_Skeleton_getBlendFunc);
        tolua_function(tolua_S,"setSkin",lua_cocos2dx_spine_Skeleton_setSkin);
        tolua_function(tolua_S,"setBonesToSetupPose",lua_cocos2dx_spine_Skeleton_setBonesToSetupPose);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(spine::Skeleton).name();
    g_luaType[typeName] = "sp.Skeleton";
    g_typeCast["Skeleton"] = "sp.Skeleton";
    return 1;
}

int lua_cocos2dx_spine_SkeletonAnimation_setMix(lua_State* tolua_S)
{
    int argc = 0;
    spine::SkeletonAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.SkeletonAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::SkeletonAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_SkeletonAnimation_setMix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        const char* arg0;
        const char* arg1;
        double arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();

        ok &= luaval_to_number(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        cobj->setMix(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setMix",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_SkeletonAnimation_setMix'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_SkeletonAnimation_clearTracks(lua_State* tolua_S)
{
    int argc = 0;
    spine::SkeletonAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.SkeletonAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::SkeletonAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_SkeletonAnimation_clearTracks'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearTracks();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clearTracks",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_SkeletonAnimation_clearTracks'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_SkeletonAnimation_clearTrack(lua_State* tolua_S)
{
    int argc = 0;
    spine::SkeletonAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.SkeletonAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::SkeletonAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_SkeletonAnimation_clearTrack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearTrack();
        return 0;
    }
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->clearTrack(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clearTrack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_SkeletonAnimation_clearTrack'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent(lua_State* tolua_S)
{
    int argc = 0;
    spine::SkeletonAnimation* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"sp.SkeletonAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (spine::SkeletonAnimation*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        int arg0;
        spEventType arg1;
        spEvent* arg2;
        int arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

        #pragma warning NO CONVERSION TO NATIVE FOR spEvent*;

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3);
        if(!ok)
            return 0;
        cobj->onAnimationStateEvent(arg0, arg1, arg2, arg3);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onAnimationStateEvent",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_spine_SkeletonAnimation_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SkeletonAnimation)");
    return 0;
}

int lua_register_cocos2dx_spine_SkeletonAnimation(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sp.SkeletonAnimation");
    tolua_cclass(tolua_S,"SkeletonAnimation","sp.SkeletonAnimation","sp.Skeleton",nullptr);

    tolua_beginmodule(tolua_S,"SkeletonAnimation");
        tolua_function(tolua_S,"setMix",lua_cocos2dx_spine_SkeletonAnimation_setMix);
        tolua_function(tolua_S,"clearTracks",lua_cocos2dx_spine_SkeletonAnimation_clearTracks);
        tolua_function(tolua_S,"clearTrack",lua_cocos2dx_spine_SkeletonAnimation_clearTrack);
        tolua_function(tolua_S,"onAnimationStateEvent",lua_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(spine::SkeletonAnimation).name();
    g_luaType[typeName] = "sp.SkeletonAnimation";
    g_typeCast["SkeletonAnimation"] = "sp.SkeletonAnimation";
    return 1;
}
TOLUA_API int register_all_cocos2dx_spine(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sp",0);
	tolua_beginmodule(tolua_S,"sp");

	lua_register_cocos2dx_spine_Skeleton(tolua_S);
	lua_register_cocos2dx_spine_SkeletonAnimation(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

