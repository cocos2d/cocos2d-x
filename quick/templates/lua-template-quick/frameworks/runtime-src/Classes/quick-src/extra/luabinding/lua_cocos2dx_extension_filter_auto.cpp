#include "lua_cocos2dx_extension_filter_auto.hpp"
#include "filters/cocos2dFilters.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_extension_filter_Filter_getGLProgramState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Filter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Filter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_Filter_getGLProgramState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::GLProgramState* ret = cobj->getGLProgramState();
        object_to_luaval<cocos2d::GLProgramState>(tolua_S, "cc.GLProgramState",(cocos2d::GLProgramState*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getGLProgramState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_getGLProgramState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_Filter_draw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Filter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Filter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_Filter_draw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->draw();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "draw",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_draw'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_Filter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Filter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Filter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_Filter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_Filter_getProgram(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Filter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Filter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_Filter_getProgram'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::GLProgram* ret = cobj->getProgram();
        object_to_luaval<cocos2d::GLProgram>(tolua_S, "cc.GLProgram",(cocos2d::GLProgram*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getProgram",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_getProgram'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_Filter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Filter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::Filter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Filter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Filter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_Filter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_Filter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Filter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_Filter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Filter");
    tolua_cclass(tolua_S,"Filter","cc.Filter","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Filter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_Filter_constructor);
        tolua_function(tolua_S,"getGLProgramState",lua_cocos2dx_extension_filter_Filter_getGLProgramState);
        tolua_function(tolua_S,"draw",lua_cocos2dx_extension_filter_Filter_draw);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_Filter_initSprite);
        tolua_function(tolua_S,"getProgram",lua_cocos2dx_extension_filter_Filter_getProgram);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::Filter).name();
    g_luaType[typeName] = "cc.Filter";
    g_typeCast["Filter"] = "cc.Filter";
    return 1;
}

int lua_cocos2dx_extension_filter_SingleFloatParamFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SingleFloatParamFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SingleFloatParamFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::SingleFloatParamFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_SingleFloatParamFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SingleFloatParamFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_SingleFloatParamFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SingleFloatParamFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::SingleFloatParamFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SingleFloatParamFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "SingleFloatParamFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SingleFloatParamFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_SingleFloatParamFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SingleFloatParamFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_SingleFloatParamFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.SingleFloatParamFilter");
    tolua_cclass(tolua_S,"SingleFloatParamFilter","cc.SingleFloatParamFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"SingleFloatParamFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_SingleFloatParamFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_SingleFloatParamFilter_setParameter);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::SingleFloatParamFilter).name();
    g_luaType[typeName] = "cc.SingleFloatParamFilter";
    g_typeCast["SingleFloatParamFilter"] = "cc.SingleFloatParamFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_GrayFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::GrayFilter* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GrayFilter",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::extension::GrayFilter*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_GrayFilter_setParameter'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);

            if (!ok) { break; }
            cobj->setParameter(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);

            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3);

            if (!ok) { break; }
            cobj->setParameter(arg0, arg1, arg2, arg3);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color4F arg0;
            ok &=luaval_to_color4f(tolua_S, 2, &arg0);

            if (!ok) { break; }
            cobj->setParameter(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GrayFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_GrayFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GrayFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            cocos2d::Color4F arg0;
            ok &=luaval_to_color4f(tolua_S, 2, &arg0);
            if (!ok) { break; }
            cocos2d::extension::GrayFilter* ret = cocos2d::extension::GrayFilter::create(arg0);
            object_to_luaval<cocos2d::extension::GrayFilter>(tolua_S, "cc.GrayFilter",(cocos2d::extension::GrayFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::GrayFilter* ret = cocos2d::extension::GrayFilter::create();
            object_to_luaval<cocos2d::extension::GrayFilter>(tolua_S, "cc.GrayFilter",(cocos2d::extension::GrayFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            cocos2d::extension::GrayFilter* ret = cocos2d::extension::GrayFilter::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::extension::GrayFilter>(tolua_S, "cc.GrayFilter",(cocos2d::extension::GrayFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3);
            if (!ok) { break; }
            cocos2d::extension::GrayFilter* ret = cocos2d::extension::GrayFilter::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::extension::GrayFilter>(tolua_S, "cc.GrayFilter",(cocos2d::extension::GrayFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GrayFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_GrayFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::GrayFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::GrayFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.GrayFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GrayFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GrayFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_GrayFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GrayFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_GrayFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.GrayFilter");
    tolua_cclass(tolua_S,"GrayFilter","cc.GrayFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"GrayFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_GrayFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_GrayFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_GrayFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::GrayFilter).name();
    g_luaType[typeName] = "cc.GrayFilter";
    g_typeCast["GrayFilter"] = "cc.GrayFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_BlurBaseFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::BlurBaseFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BlurBaseFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::BlurBaseFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_BlurBaseFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_BlurBaseFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_BlurBaseFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::BlurBaseFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::BlurBaseFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.BlurBaseFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "BlurBaseFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_BlurBaseFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_BlurBaseFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BlurBaseFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_BlurBaseFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.BlurBaseFilter");
    tolua_cclass(tolua_S,"BlurBaseFilter","cc.BlurBaseFilter","cc.SingleFloatParamFilter",nullptr);

    tolua_beginmodule(tolua_S,"BlurBaseFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_BlurBaseFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_BlurBaseFilter_setParameter);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::BlurBaseFilter).name();
    g_luaType[typeName] = "cc.BlurBaseFilter";
    g_typeCast["BlurBaseFilter"] = "cc.BlurBaseFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_HBlurFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.HBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::HBlurFilter* ret = cocos2d::extension::HBlurFilter::create(arg0);
            object_to_luaval<cocos2d::extension::HBlurFilter>(tolua_S, "cc.HBlurFilter",(cocos2d::extension::HBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::HBlurFilter* ret = cocos2d::extension::HBlurFilter::create();
            object_to_luaval<cocos2d::extension::HBlurFilter>(tolua_S, "cc.HBlurFilter",(cocos2d::extension::HBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_HBlurFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_HBlurFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::HBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::HBlurFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.HBlurFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "HBlurFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_HBlurFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_HBlurFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (HBlurFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_HBlurFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.HBlurFilter");
    tolua_cclass(tolua_S,"HBlurFilter","cc.HBlurFilter","cc.BlurBaseFilter",nullptr);

    tolua_beginmodule(tolua_S,"HBlurFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_HBlurFilter_constructor);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_HBlurFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::HBlurFilter).name();
    g_luaType[typeName] = "cc.HBlurFilter";
    g_typeCast["HBlurFilter"] = "cc.HBlurFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_VBlurFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.VBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::VBlurFilter* ret = cocos2d::extension::VBlurFilter::create(arg0);
            object_to_luaval<cocos2d::extension::VBlurFilter>(tolua_S, "cc.VBlurFilter",(cocos2d::extension::VBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::VBlurFilter* ret = cocos2d::extension::VBlurFilter::create();
            object_to_luaval<cocos2d::extension::VBlurFilter>(tolua_S, "cc.VBlurFilter",(cocos2d::extension::VBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_VBlurFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_VBlurFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::VBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::VBlurFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.VBlurFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "VBlurFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_VBlurFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_VBlurFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (VBlurFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_VBlurFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.VBlurFilter");
    tolua_cclass(tolua_S,"VBlurFilter","cc.VBlurFilter","cc.BlurBaseFilter",nullptr);

    tolua_beginmodule(tolua_S,"VBlurFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_VBlurFilter_constructor);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_VBlurFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::VBlurFilter).name();
    g_luaType[typeName] = "cc.VBlurFilter";
    g_typeCast["VBlurFilter"] = "cc.VBlurFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_GaussianHBlurFilter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::GaussianHBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GaussianHBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::GaussianHBlurFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_GaussianHBlurFilter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GaussianHBlurFilter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_GaussianHBlurFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GaussianHBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::GaussianHBlurFilter* ret = cocos2d::extension::GaussianHBlurFilter::create(arg0);
            object_to_luaval<cocos2d::extension::GaussianHBlurFilter>(tolua_S, "cc.GaussianHBlurFilter",(cocos2d::extension::GaussianHBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::GaussianHBlurFilter* ret = cocos2d::extension::GaussianHBlurFilter::create();
            object_to_luaval<cocos2d::extension::GaussianHBlurFilter>(tolua_S, "cc.GaussianHBlurFilter",(cocos2d::extension::GaussianHBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GaussianHBlurFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_GaussianHBlurFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::GaussianHBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::GaussianHBlurFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.GaussianHBlurFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GaussianHBlurFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GaussianHBlurFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_GaussianHBlurFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GaussianHBlurFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_GaussianHBlurFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.GaussianHBlurFilter");
    tolua_cclass(tolua_S,"GaussianHBlurFilter","cc.GaussianHBlurFilter","cc.BlurBaseFilter",nullptr);

    tolua_beginmodule(tolua_S,"GaussianHBlurFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_GaussianHBlurFilter_constructor);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_GaussianHBlurFilter_initSprite);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_GaussianHBlurFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::GaussianHBlurFilter).name();
    g_luaType[typeName] = "cc.GaussianHBlurFilter";
    g_typeCast["GaussianHBlurFilter"] = "cc.GaussianHBlurFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_GaussianVBlurFilter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::GaussianVBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GaussianVBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::GaussianVBlurFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_GaussianVBlurFilter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GaussianVBlurFilter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_GaussianVBlurFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GaussianVBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::GaussianVBlurFilter* ret = cocos2d::extension::GaussianVBlurFilter::create(arg0);
            object_to_luaval<cocos2d::extension::GaussianVBlurFilter>(tolua_S, "cc.GaussianVBlurFilter",(cocos2d::extension::GaussianVBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::GaussianVBlurFilter* ret = cocos2d::extension::GaussianVBlurFilter::create();
            object_to_luaval<cocos2d::extension::GaussianVBlurFilter>(tolua_S, "cc.GaussianVBlurFilter",(cocos2d::extension::GaussianVBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GaussianVBlurFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_GaussianVBlurFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::GaussianVBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::GaussianVBlurFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.GaussianVBlurFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GaussianVBlurFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GaussianVBlurFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_GaussianVBlurFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GaussianVBlurFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_GaussianVBlurFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.GaussianVBlurFilter");
    tolua_cclass(tolua_S,"GaussianVBlurFilter","cc.GaussianVBlurFilter","cc.BlurBaseFilter",nullptr);

    tolua_beginmodule(tolua_S,"GaussianVBlurFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_GaussianVBlurFilter_constructor);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_GaussianVBlurFilter_initSprite);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_GaussianVBlurFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::GaussianVBlurFilter).name();
    g_luaType[typeName] = "cc.GaussianVBlurFilter";
    g_typeCast["GaussianVBlurFilter"] = "cc.GaussianVBlurFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_ZoomBlurFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ZoomBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ZoomBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ZoomBlurFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_ZoomBlurFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        double arg0;
        double arg1;
        double arg2;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);

        ok &= luaval_to_number(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        cobj->setParameter(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ZoomBlurFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_ZoomBlurFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ZoomBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            cocos2d::extension::ZoomBlurFilter* ret = cocos2d::extension::ZoomBlurFilter::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::extension::ZoomBlurFilter>(tolua_S, "cc.ZoomBlurFilter",(cocos2d::extension::ZoomBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::ZoomBlurFilter* ret = cocos2d::extension::ZoomBlurFilter::create();
            object_to_luaval<cocos2d::extension::ZoomBlurFilter>(tolua_S, "cc.ZoomBlurFilter",(cocos2d::extension::ZoomBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ZoomBlurFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_ZoomBlurFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ZoomBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::ZoomBlurFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ZoomBlurFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ZoomBlurFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ZoomBlurFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_ZoomBlurFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ZoomBlurFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_ZoomBlurFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ZoomBlurFilter");
    tolua_cclass(tolua_S,"ZoomBlurFilter","cc.ZoomBlurFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"ZoomBlurFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_ZoomBlurFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_ZoomBlurFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_ZoomBlurFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::ZoomBlurFilter).name();
    g_luaType[typeName] = "cc.ZoomBlurFilter";
    g_typeCast["ZoomBlurFilter"] = "cc.ZoomBlurFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_MotionBlurFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::MotionBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::MotionBlurFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_MotionBlurFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->setParameter(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MotionBlurFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_MotionBlurFilter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::MotionBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::MotionBlurFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_MotionBlurFilter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MotionBlurFilter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_MotionBlurFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MotionBlurFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            cocos2d::extension::MotionBlurFilter* ret = cocos2d::extension::MotionBlurFilter::create(arg0, arg1);
            object_to_luaval<cocos2d::extension::MotionBlurFilter>(tolua_S, "cc.MotionBlurFilter",(cocos2d::extension::MotionBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::MotionBlurFilter* ret = cocos2d::extension::MotionBlurFilter::create();
            object_to_luaval<cocos2d::extension::MotionBlurFilter>(tolua_S, "cc.MotionBlurFilter",(cocos2d::extension::MotionBlurFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MotionBlurFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_MotionBlurFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::MotionBlurFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::MotionBlurFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MotionBlurFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "MotionBlurFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MotionBlurFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_MotionBlurFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MotionBlurFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_MotionBlurFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.MotionBlurFilter");
    tolua_cclass(tolua_S,"MotionBlurFilter","cc.MotionBlurFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"MotionBlurFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_MotionBlurFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_MotionBlurFilter_setParameter);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_MotionBlurFilter_initSprite);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_MotionBlurFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::MotionBlurFilter).name();
    g_luaType[typeName] = "cc.MotionBlurFilter";
    g_typeCast["MotionBlurFilter"] = "cc.MotionBlurFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_MaskFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::MaskFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MaskFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::MaskFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_MaskFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR std::string*;
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MaskFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_MaskFilter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::MaskFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MaskFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::MaskFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_MaskFilter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MaskFilter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_MaskFilter_setIsSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::MaskFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MaskFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::MaskFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_MaskFilter_setIsSpriteFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setIsSpriteFrame(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setIsSpriteFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MaskFilter_setIsSpriteFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_MaskFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MaskFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string* arg0;
            #pragma warning NO CONVERSION TO NATIVE FOR std::string*;
            if (!ok) { break; }
            cocos2d::extension::MaskFilter* ret = cocos2d::extension::MaskFilter::create(arg0);
            object_to_luaval<cocos2d::extension::MaskFilter>(tolua_S, "cc.MaskFilter",(cocos2d::extension::MaskFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::MaskFilter* ret = cocos2d::extension::MaskFilter::create();
            object_to_luaval<cocos2d::extension::MaskFilter>(tolua_S, "cc.MaskFilter",(cocos2d::extension::MaskFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MaskFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_MaskFilter_createWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MaskFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR std::string*;
        if(!ok)
            return 0;
        cocos2d::extension::MaskFilter* ret = cocos2d::extension::MaskFilter::createWithSpriteFrameName(arg0);
        object_to_luaval<cocos2d::extension::MaskFilter>(tolua_S, "cc.MaskFilter",(cocos2d::extension::MaskFilter*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithSpriteFrameName",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MaskFilter_createWithSpriteFrameName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_MaskFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::MaskFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::MaskFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MaskFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "MaskFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_MaskFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_MaskFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MaskFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_MaskFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.MaskFilter");
    tolua_cclass(tolua_S,"MaskFilter","cc.MaskFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"MaskFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_MaskFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_MaskFilter_setParameter);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_MaskFilter_initSprite);
        tolua_function(tolua_S,"setIsSpriteFrame",lua_cocos2dx_extension_filter_MaskFilter_setIsSpriteFrame);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_MaskFilter_create);
        tolua_function(tolua_S,"createWithSpriteFrameName", lua_cocos2dx_extension_filter_MaskFilter_createWithSpriteFrameName);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::MaskFilter).name();
    g_luaType[typeName] = "cc.MaskFilter";
    g_typeCast["MaskFilter"] = "cc.MaskFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_SharpenFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SharpenFilter* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SharpenFilter",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::extension::SharpenFilter*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_SharpenFilter_setParameter'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

            if (!ok) { break; }
            cobj->setParameter(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);

            if (!ok) { break; }
            cobj->setParameter(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SharpenFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_SharpenFilter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SharpenFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SharpenFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::SharpenFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_SharpenFilter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SharpenFilter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_SharpenFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SharpenFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            cocos2d::extension::SharpenFilter* ret = cocos2d::extension::SharpenFilter::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::extension::SharpenFilter>(tolua_S, "cc.SharpenFilter",(cocos2d::extension::SharpenFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::SharpenFilter* ret = cocos2d::extension::SharpenFilter::create();
            object_to_luaval<cocos2d::extension::SharpenFilter>(tolua_S, "cc.SharpenFilter",(cocos2d::extension::SharpenFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
            if (!ok) { break; }
            cocos2d::extension::SharpenFilter* ret = cocos2d::extension::SharpenFilter::create(arg0, arg1);
            object_to_luaval<cocos2d::extension::SharpenFilter>(tolua_S, "cc.SharpenFilter",(cocos2d::extension::SharpenFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SharpenFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_SharpenFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SharpenFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::SharpenFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SharpenFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "SharpenFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SharpenFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_SharpenFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SharpenFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_SharpenFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.SharpenFilter");
    tolua_cclass(tolua_S,"SharpenFilter","cc.SharpenFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"SharpenFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_SharpenFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_SharpenFilter_setParameter);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_SharpenFilter_initSprite);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_SharpenFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::SharpenFilter).name();
    g_luaType[typeName] = "cc.SharpenFilter";
    g_typeCast["SharpenFilter"] = "cc.SharpenFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_RGBFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::RGBFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RGBFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::RGBFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_RGBFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        double arg0;
        double arg1;
        double arg2;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);

        ok &= luaval_to_number(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        cobj->setParameter(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_RGBFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_RGBFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.RGBFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            cocos2d::extension::RGBFilter* ret = cocos2d::extension::RGBFilter::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::extension::RGBFilter>(tolua_S, "cc.RGBFilter",(cocos2d::extension::RGBFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::RGBFilter* ret = cocos2d::extension::RGBFilter::create();
            object_to_luaval<cocos2d::extension::RGBFilter>(tolua_S, "cc.RGBFilter",(cocos2d::extension::RGBFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_RGBFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_RGBFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::RGBFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::RGBFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.RGBFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "RGBFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_RGBFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_RGBFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RGBFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_RGBFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.RGBFilter");
    tolua_cclass(tolua_S,"RGBFilter","cc.RGBFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"RGBFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_RGBFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_RGBFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_RGBFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::RGBFilter).name();
    g_luaType[typeName] = "cc.RGBFilter";
    g_typeCast["RGBFilter"] = "cc.RGBFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_BrightnessFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::BrightnessFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BrightnessFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::BrightnessFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_BrightnessFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_BrightnessFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_BrightnessFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.BrightnessFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::BrightnessFilter* ret = cocos2d::extension::BrightnessFilter::create(arg0);
            object_to_luaval<cocos2d::extension::BrightnessFilter>(tolua_S, "cc.BrightnessFilter",(cocos2d::extension::BrightnessFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::BrightnessFilter* ret = cocos2d::extension::BrightnessFilter::create();
            object_to_luaval<cocos2d::extension::BrightnessFilter>(tolua_S, "cc.BrightnessFilter",(cocos2d::extension::BrightnessFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_BrightnessFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_BrightnessFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::BrightnessFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::BrightnessFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.BrightnessFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "BrightnessFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_BrightnessFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_BrightnessFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BrightnessFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_BrightnessFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.BrightnessFilter");
    tolua_cclass(tolua_S,"BrightnessFilter","cc.BrightnessFilter","cc.SingleFloatParamFilter",nullptr);

    tolua_beginmodule(tolua_S,"BrightnessFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_BrightnessFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_BrightnessFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_BrightnessFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::BrightnessFilter).name();
    g_luaType[typeName] = "cc.BrightnessFilter";
    g_typeCast["BrightnessFilter"] = "cc.BrightnessFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_ExposureFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ExposureFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ExposureFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ExposureFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_ExposureFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ExposureFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_ExposureFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ExposureFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::ExposureFilter* ret = cocos2d::extension::ExposureFilter::create(arg0);
            object_to_luaval<cocos2d::extension::ExposureFilter>(tolua_S, "cc.ExposureFilter",(cocos2d::extension::ExposureFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::ExposureFilter* ret = cocos2d::extension::ExposureFilter::create();
            object_to_luaval<cocos2d::extension::ExposureFilter>(tolua_S, "cc.ExposureFilter",(cocos2d::extension::ExposureFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ExposureFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_ExposureFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ExposureFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::ExposureFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ExposureFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ExposureFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ExposureFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_ExposureFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ExposureFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_ExposureFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ExposureFilter");
    tolua_cclass(tolua_S,"ExposureFilter","cc.ExposureFilter","cc.SingleFloatParamFilter",nullptr);

    tolua_beginmodule(tolua_S,"ExposureFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_ExposureFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_ExposureFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_ExposureFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::ExposureFilter).name();
    g_luaType[typeName] = "cc.ExposureFilter";
    g_typeCast["ExposureFilter"] = "cc.ExposureFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_ContrastFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ContrastFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ContrastFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ContrastFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_ContrastFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ContrastFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_ContrastFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ContrastFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::ContrastFilter* ret = cocos2d::extension::ContrastFilter::create(arg0);
            object_to_luaval<cocos2d::extension::ContrastFilter>(tolua_S, "cc.ContrastFilter",(cocos2d::extension::ContrastFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::ContrastFilter* ret = cocos2d::extension::ContrastFilter::create();
            object_to_luaval<cocos2d::extension::ContrastFilter>(tolua_S, "cc.ContrastFilter",(cocos2d::extension::ContrastFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ContrastFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_ContrastFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ContrastFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::ContrastFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ContrastFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ContrastFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_ContrastFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_ContrastFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ContrastFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_ContrastFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ContrastFilter");
    tolua_cclass(tolua_S,"ContrastFilter","cc.ContrastFilter","cc.SingleFloatParamFilter",nullptr);

    tolua_beginmodule(tolua_S,"ContrastFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_ContrastFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_ContrastFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_ContrastFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::ContrastFilter).name();
    g_luaType[typeName] = "cc.ContrastFilter";
    g_typeCast["ContrastFilter"] = "cc.ContrastFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_DropShadowFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::DropShadowFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DropShadowFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::DropShadowFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_DropShadowFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_DropShadowFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_DropShadowFilter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::DropShadowFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DropShadowFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::DropShadowFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_DropShadowFilter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_DropShadowFilter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_DropShadowFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.DropShadowFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::DropShadowFilter* ret = cocos2d::extension::DropShadowFilter::create(arg0);
            object_to_luaval<cocos2d::extension::DropShadowFilter>(tolua_S, "cc.DropShadowFilter",(cocos2d::extension::DropShadowFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::DropShadowFilter* ret = cocos2d::extension::DropShadowFilter::create();
            object_to_luaval<cocos2d::extension::DropShadowFilter>(tolua_S, "cc.DropShadowFilter",(cocos2d::extension::DropShadowFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_DropShadowFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_DropShadowFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::DropShadowFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::DropShadowFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.DropShadowFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "DropShadowFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_DropShadowFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_DropShadowFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (DropShadowFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_DropShadowFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.DropShadowFilter");
    tolua_cclass(tolua_S,"DropShadowFilter","cc.DropShadowFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"DropShadowFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_DropShadowFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_DropShadowFilter_setParameter);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_DropShadowFilter_initSprite);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_DropShadowFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::DropShadowFilter).name();
    g_luaType[typeName] = "cc.DropShadowFilter";
    g_typeCast["DropShadowFilter"] = "cc.DropShadowFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_GammaFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::GammaFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GammaFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::GammaFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_GammaFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GammaFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_GammaFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GammaFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::GammaFilter* ret = cocos2d::extension::GammaFilter::create(arg0);
            object_to_luaval<cocos2d::extension::GammaFilter>(tolua_S, "cc.GammaFilter",(cocos2d::extension::GammaFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::GammaFilter* ret = cocos2d::extension::GammaFilter::create();
            object_to_luaval<cocos2d::extension::GammaFilter>(tolua_S, "cc.GammaFilter",(cocos2d::extension::GammaFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GammaFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_GammaFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::GammaFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::GammaFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.GammaFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GammaFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_GammaFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_GammaFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GammaFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_GammaFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.GammaFilter");
    tolua_cclass(tolua_S,"GammaFilter","cc.GammaFilter","cc.SingleFloatParamFilter",nullptr);

    tolua_beginmodule(tolua_S,"GammaFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_GammaFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_GammaFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_GammaFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::GammaFilter).name();
    g_luaType[typeName] = "cc.GammaFilter";
    g_typeCast["GammaFilter"] = "cc.GammaFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_HazeFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::HazeFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.HazeFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::HazeFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_HazeFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0);

        ok &= luaval_to_number(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->setParameter(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_HazeFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_HazeFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.HazeFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            cocos2d::extension::HazeFilter* ret = cocos2d::extension::HazeFilter::create(arg0, arg1);
            object_to_luaval<cocos2d::extension::HazeFilter>(tolua_S, "cc.HazeFilter",(cocos2d::extension::HazeFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::HazeFilter* ret = cocos2d::extension::HazeFilter::create();
            object_to_luaval<cocos2d::extension::HazeFilter>(tolua_S, "cc.HazeFilter",(cocos2d::extension::HazeFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_HazeFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_HazeFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::HazeFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::HazeFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.HazeFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "HazeFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_HazeFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_HazeFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (HazeFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_HazeFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.HazeFilter");
    tolua_cclass(tolua_S,"HazeFilter","cc.HazeFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"HazeFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_HazeFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_HazeFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_HazeFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::HazeFilter).name();
    g_luaType[typeName] = "cc.HazeFilter";
    g_typeCast["HazeFilter"] = "cc.HazeFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_HueFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::HueFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.HueFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::HueFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_HueFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_HueFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_HueFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.HueFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::HueFilter* ret = cocos2d::extension::HueFilter::create(arg0);
            object_to_luaval<cocos2d::extension::HueFilter>(tolua_S, "cc.HueFilter",(cocos2d::extension::HueFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::HueFilter* ret = cocos2d::extension::HueFilter::create();
            object_to_luaval<cocos2d::extension::HueFilter>(tolua_S, "cc.HueFilter",(cocos2d::extension::HueFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_HueFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_HueFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::HueFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::HueFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.HueFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "HueFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_HueFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_HueFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (HueFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_HueFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.HueFilter");
    tolua_cclass(tolua_S,"HueFilter","cc.HueFilter","cc.SingleFloatParamFilter",nullptr);

    tolua_beginmodule(tolua_S,"HueFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_HueFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_HueFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_HueFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::HueFilter).name();
    g_luaType[typeName] = "cc.HueFilter";
    g_typeCast["HueFilter"] = "cc.HueFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_SaturationFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SaturationFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SaturationFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::SaturationFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_SaturationFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SaturationFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_SaturationFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SaturationFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::SaturationFilter* ret = cocos2d::extension::SaturationFilter::create(arg0);
            object_to_luaval<cocos2d::extension::SaturationFilter>(tolua_S, "cc.SaturationFilter",(cocos2d::extension::SaturationFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::SaturationFilter* ret = cocos2d::extension::SaturationFilter::create();
            object_to_luaval<cocos2d::extension::SaturationFilter>(tolua_S, "cc.SaturationFilter",(cocos2d::extension::SaturationFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SaturationFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_SaturationFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SaturationFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::SaturationFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SaturationFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "SaturationFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SaturationFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_SaturationFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SaturationFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_SaturationFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.SaturationFilter");
    tolua_cclass(tolua_S,"SaturationFilter","cc.SaturationFilter","cc.SingleFloatParamFilter",nullptr);

    tolua_beginmodule(tolua_S,"SaturationFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_SaturationFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_SaturationFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_SaturationFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::SaturationFilter).name();
    g_luaType[typeName] = "cc.SaturationFilter";
    g_typeCast["SaturationFilter"] = "cc.SaturationFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_SepiaFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SepiaFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SepiaFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::SepiaFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_SepiaFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->setParameter();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SepiaFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_SepiaFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SepiaFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::SepiaFilter* ret = cocos2d::extension::SepiaFilter::create(arg0);
            object_to_luaval<cocos2d::extension::SepiaFilter>(tolua_S, "cc.SepiaFilter",(cocos2d::extension::SepiaFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::SepiaFilter* ret = cocos2d::extension::SepiaFilter::create();
            object_to_luaval<cocos2d::extension::SepiaFilter>(tolua_S, "cc.SepiaFilter",(cocos2d::extension::SepiaFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SepiaFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_SepiaFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::SepiaFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::SepiaFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SepiaFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "SepiaFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_SepiaFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_SepiaFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SepiaFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_SepiaFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.SepiaFilter");
    tolua_cclass(tolua_S,"SepiaFilter","cc.SepiaFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"SepiaFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_SepiaFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_SepiaFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_SepiaFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::SepiaFilter).name();
    g_luaType[typeName] = "cc.SepiaFilter";
    g_typeCast["SepiaFilter"] = "cc.SepiaFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_TestFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TestFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TestFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TestFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_TestFilter_setParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_TestFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_TestFilter_initSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TestFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TestFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TestFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_TestFilter_initSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::FilteredSprite* arg0;

        ok &= luaval_to_object<cocos2d::extension::FilteredSprite>(tolua_S, 2, "cc.FilteredSprite",&arg0);
        if(!ok)
            return 0;
        cobj->initSprite(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_TestFilter_initSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_TestFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.TestFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::TestFilter* ret = cocos2d::extension::TestFilter::create(arg0);
            object_to_luaval<cocos2d::extension::TestFilter>(tolua_S, "cc.TestFilter",(cocos2d::extension::TestFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::TestFilter* ret = cocos2d::extension::TestFilter::create();
            object_to_luaval<cocos2d::extension::TestFilter>(tolua_S, "cc.TestFilter",(cocos2d::extension::TestFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_TestFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_TestFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TestFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::TestFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TestFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "TestFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_TestFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_TestFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TestFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_TestFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.TestFilter");
    tolua_cclass(tolua_S,"TestFilter","cc.TestFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"TestFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_TestFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_TestFilter_setParameter);
        tolua_function(tolua_S,"initSprite",lua_cocos2dx_extension_filter_TestFilter_initSprite);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_TestFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::TestFilter).name();
    g_luaType[typeName] = "cc.TestFilter";
    g_typeCast["TestFilter"] = "cc.TestFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_CustomFilter_setParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::CustomFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CustomFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::CustomFilter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_CustomFilter_setParameter'", nullptr);
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
        cobj->setParameter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_CustomFilter_setParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_CustomFilter_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CustomFilter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);
            if (!ok) { break; }
            cocos2d::extension::CustomFilter* ret = cocos2d::extension::CustomFilter::create(arg0);
            object_to_luaval<cocos2d::extension::CustomFilter>(tolua_S, "cc.CustomFilter",(cocos2d::extension::CustomFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::CustomFilter* ret = cocos2d::extension::CustomFilter::create();
            object_to_luaval<cocos2d::extension::CustomFilter>(tolua_S, "cc.CustomFilter",(cocos2d::extension::CustomFilter*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_CustomFilter_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_CustomFilter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::CustomFilter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::CustomFilter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CustomFilter");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "CustomFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_CustomFilter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_CustomFilter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CustomFilter)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_CustomFilter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.CustomFilter");
    tolua_cclass(tolua_S,"CustomFilter","cc.CustomFilter","cc.Filter",nullptr);

    tolua_beginmodule(tolua_S,"CustomFilter");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_CustomFilter_constructor);
        tolua_function(tolua_S,"setParameter",lua_cocos2dx_extension_filter_CustomFilter_setParameter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_CustomFilter_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::CustomFilter).name();
    g_luaType[typeName] = "cc.CustomFilter";
    g_typeCast["CustomFilter"] = "cc.CustomFilter";
    return 1;
}

int lua_cocos2dx_extension_filter_FilteredSprite_getFilters(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSprite_getFilters'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Vector<cocos2d::extension::Filter *>& ret = cobj->getFilters();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFilters",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSprite_getFilters'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSprite_setFilters(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSprite_setFilters'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::extension::Filter *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setFilters(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFilters",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSprite_setFilters'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSprite_getFilter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSprite_getFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::extension::Filter* ret = cobj->getFilter();
        object_to_luaval<cocos2d::extension::Filter>(tolua_S, "cc.Filter",(cocos2d::extension::Filter*)ret);
        return 1;
    }
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cocos2d::extension::Filter* ret = cobj->getFilter(arg0);
        object_to_luaval<cocos2d::extension::Filter>(tolua_S, "cc.Filter",(cocos2d::extension::Filter*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSprite_getFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSprite_clearFilter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSprite_clearFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearFilter();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clearFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSprite_clearFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSprite_setFilter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSprite_setFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Filter* arg0;

        ok &= luaval_to_object<cocos2d::extension::Filter>(tolua_S, 2, "cc.Filter",&arg0);
        if(!ok)
            return 0;
        cobj->setFilter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFilter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSprite_setFilter'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_extension_filter_FilteredSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (FilteredSprite)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_FilteredSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.FilteredSprite");
    tolua_cclass(tolua_S,"FilteredSprite","cc.FilteredSprite","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"FilteredSprite");
        tolua_function(tolua_S,"getFilters",lua_cocos2dx_extension_filter_FilteredSprite_getFilters);
        tolua_function(tolua_S,"setFilters",lua_cocos2dx_extension_filter_FilteredSprite_setFilters);
        tolua_function(tolua_S,"getFilter",lua_cocos2dx_extension_filter_FilteredSprite_getFilter);
        tolua_function(tolua_S,"clearFilter",lua_cocos2dx_extension_filter_FilteredSprite_clearFilter);
        tolua_function(tolua_S,"setFilter",lua_cocos2dx_extension_filter_FilteredSprite_setFilter);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::FilteredSprite).name();
    g_luaType[typeName] = "cc.FilteredSprite";
    g_typeCast["FilteredSprite"] = "cc.FilteredSprite";
    return 1;
}

int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_setFilters(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithOne* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithOne",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithOne*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_setFilters'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::extension::Filter *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setFilters(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFilters",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_setFilters'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_getFilter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithOne* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithOne",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithOne*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_getFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::extension::Filter* ret = cobj->getFilter();
        object_to_luaval<cocos2d::extension::Filter>(tolua_S, "cc.Filter",(cocos2d::extension::Filter*)ret);
        return 1;
    }
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cocos2d::extension::Filter* ret = cobj->getFilter(arg0);
        object_to_luaval<cocos2d::extension::Filter>(tolua_S, "cc.Filter",(cocos2d::extension::Filter*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_getFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_clearFilter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithOne* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithOne",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithOne*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_clearFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearFilter();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clearFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_clearFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_setFilter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithOne* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithOne",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithOne*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_setFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Filter* arg0;

        ok &= luaval_to_object<cocos2d::extension::Filter>(tolua_S, 2, "cc.Filter",&arg0);
        if(!ok)
            return 0;
        cobj->setFilter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFilter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_setFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FilteredSpriteWithOne",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            cocos2d::extension::FilteredSpriteWithOne* ret = cocos2d::extension::FilteredSpriteWithOne::create(arg0);
            object_to_luaval<cocos2d::extension::FilteredSpriteWithOne>(tolua_S, "cc.FilteredSpriteWithOne",(cocos2d::extension::FilteredSpriteWithOne*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::FilteredSpriteWithOne* ret = cocos2d::extension::FilteredSpriteWithOne::create();
            object_to_luaval<cocos2d::extension::FilteredSpriteWithOne>(tolua_S, "cc.FilteredSpriteWithOne",(cocos2d::extension::FilteredSpriteWithOne*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1);
            if (!ok) { break; }
            cocos2d::extension::FilteredSpriteWithOne* ret = cocos2d::extension::FilteredSpriteWithOne::create(arg0, arg1);
            object_to_luaval<cocos2d::extension::FilteredSpriteWithOne>(tolua_S, "cc.FilteredSpriteWithOne",(cocos2d::extension::FilteredSpriteWithOne*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FilteredSpriteWithOne",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1);
            if (!ok) { break; }
            cocos2d::extension::FilteredSpriteWithOne* ret = cocos2d::extension::FilteredSpriteWithOne::createWithTexture(arg0, arg1);
            object_to_luaval<cocos2d::extension::FilteredSpriteWithOne>(tolua_S, "cc.FilteredSpriteWithOne",(cocos2d::extension::FilteredSpriteWithOne*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
            if (!ok) { break; }
            cocos2d::extension::FilteredSpriteWithOne* ret = cocos2d::extension::FilteredSpriteWithOne::createWithTexture(arg0);
            object_to_luaval<cocos2d::extension::FilteredSpriteWithOne>(tolua_S, "cc.FilteredSpriteWithOne",(cocos2d::extension::FilteredSpriteWithOne*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "createWithTexture",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithTexture'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FilteredSpriteWithOne",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cocos2d::extension::FilteredSpriteWithOne* ret = cocos2d::extension::FilteredSpriteWithOne::createWithSpriteFrameName(arg0);
        object_to_luaval<cocos2d::extension::FilteredSpriteWithOne>(tolua_S, "cc.FilteredSpriteWithOne",(cocos2d::extension::FilteredSpriteWithOne*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithSpriteFrameName",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithSpriteFrameName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FilteredSpriteWithOne",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::SpriteFrame* arg0;
        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
        if(!ok)
            return 0;
        cocos2d::extension::FilteredSpriteWithOne* ret = cocos2d::extension::FilteredSpriteWithOne::createWithSpriteFrame(arg0);
        object_to_luaval<cocos2d::extension::FilteredSpriteWithOne>(tolua_S, "cc.FilteredSpriteWithOne",(cocos2d::extension::FilteredSpriteWithOne*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithSpriteFrame",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithSpriteFrame'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extension_filter_FilteredSpriteWithOne_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (FilteredSpriteWithOne)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_FilteredSpriteWithOne(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.FilteredSpriteWithOne");
    tolua_cclass(tolua_S,"FilteredSpriteWithOne","cc.FilteredSpriteWithOne","cc.FilteredSprite",nullptr);

    tolua_beginmodule(tolua_S,"FilteredSpriteWithOne");
        tolua_function(tolua_S,"setFilters",lua_cocos2dx_extension_filter_FilteredSpriteWithOne_setFilters);
        tolua_function(tolua_S,"getFilter",lua_cocos2dx_extension_filter_FilteredSpriteWithOne_getFilter);
        tolua_function(tolua_S,"clearFilter",lua_cocos2dx_extension_filter_FilteredSpriteWithOne_clearFilter);
        tolua_function(tolua_S,"setFilter",lua_cocos2dx_extension_filter_FilteredSpriteWithOne_setFilter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_FilteredSpriteWithOne_create);
        tolua_function(tolua_S,"createWithTexture", lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithTexture);
        tolua_function(tolua_S,"createWithSpriteFrameName", lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithSpriteFrameName);
        tolua_function(tolua_S,"createWithSpriteFrame", lua_cocos2dx_extension_filter_FilteredSpriteWithOne_createWithSpriteFrame);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::FilteredSpriteWithOne).name();
    g_luaType[typeName] = "cc.FilteredSpriteWithOne";
    g_typeCast["FilteredSpriteWithOne"] = "cc.FilteredSpriteWithOne";
    return 1;
}

int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithMulti*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SpriteFrame* arg0;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
        if(!ok)
            return 0;
        cobj->setTSFrame(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTSFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithMulti*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
        if(!ok)
            return 0;
        cobj->setTSTexture(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTSTexture",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithMulti*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setTSRect(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTSRect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithMulti*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::SpriteFrame* ret = cobj->getTSFrame();
        object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTSFrame",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_clearFilter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithMulti*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_clearFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearFilter();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clearFilter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_clearFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithMulti*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->getTSRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTSRect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithMulti*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Texture2D* ret = cobj->getTSTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTSTexture",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setFilter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::FilteredSpriteWithMulti*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setFilter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Filter* arg0;

        ok &= luaval_to_object<cocos2d::extension::Filter>(tolua_S, 2, "cc.Filter",&arg0);
        if(!ok)
            return 0;
        cobj->setFilter(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFilter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setFilter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            cocos2d::extension::FilteredSpriteWithMulti* ret = cocos2d::extension::FilteredSpriteWithMulti::create(arg0);
            object_to_luaval<cocos2d::extension::FilteredSpriteWithMulti>(tolua_S, "cc.FilteredSpriteWithMulti",(cocos2d::extension::FilteredSpriteWithMulti*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::FilteredSpriteWithMulti* ret = cocos2d::extension::FilteredSpriteWithMulti::create();
            object_to_luaval<cocos2d::extension::FilteredSpriteWithMulti>(tolua_S, "cc.FilteredSpriteWithMulti",(cocos2d::extension::FilteredSpriteWithMulti*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1);
            if (!ok) { break; }
            cocos2d::extension::FilteredSpriteWithMulti* ret = cocos2d::extension::FilteredSpriteWithMulti::create(arg0, arg1);
            object_to_luaval<cocos2d::extension::FilteredSpriteWithMulti>(tolua_S, "cc.FilteredSpriteWithMulti",(cocos2d::extension::FilteredSpriteWithMulti*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1);
            if (!ok) { break; }
            cocos2d::extension::FilteredSpriteWithMulti* ret = cocos2d::extension::FilteredSpriteWithMulti::createWithTexture(arg0, arg1);
            object_to_luaval<cocos2d::extension::FilteredSpriteWithMulti>(tolua_S, "cc.FilteredSpriteWithMulti",(cocos2d::extension::FilteredSpriteWithMulti*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
            if (!ok) { break; }
            cocos2d::extension::FilteredSpriteWithMulti* ret = cocos2d::extension::FilteredSpriteWithMulti::createWithTexture(arg0);
            object_to_luaval<cocos2d::extension::FilteredSpriteWithMulti>(tolua_S, "cc.FilteredSpriteWithMulti",(cocos2d::extension::FilteredSpriteWithMulti*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "createWithTexture",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithTexture'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cocos2d::extension::FilteredSpriteWithMulti* ret = cocos2d::extension::FilteredSpriteWithMulti::createWithSpriteFrameName(arg0);
        object_to_luaval<cocos2d::extension::FilteredSpriteWithMulti>(tolua_S, "cc.FilteredSpriteWithMulti",(cocos2d::extension::FilteredSpriteWithMulti*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithSpriteFrameName",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithSpriteFrameName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FilteredSpriteWithMulti",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::SpriteFrame* arg0;
        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
        if(!ok)
            return 0;
        cocos2d::extension::FilteredSpriteWithMulti* ret = cocos2d::extension::FilteredSpriteWithMulti::createWithSpriteFrame(arg0);
        object_to_luaval<cocos2d::extension::FilteredSpriteWithMulti>(tolua_S, "cc.FilteredSpriteWithMulti",(cocos2d::extension::FilteredSpriteWithMulti*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithSpriteFrame",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithSpriteFrame'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::FilteredSpriteWithMulti* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::extension::FilteredSpriteWithMulti();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FilteredSpriteWithMulti");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "FilteredSpriteWithMulti",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (FilteredSpriteWithMulti)");
    return 0;
}

int lua_register_cocos2dx_extension_filter_FilteredSpriteWithMulti(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.FilteredSpriteWithMulti");
    tolua_cclass(tolua_S,"FilteredSpriteWithMulti","cc.FilteredSpriteWithMulti","cc.FilteredSprite",nullptr);

    tolua_beginmodule(tolua_S,"FilteredSpriteWithMulti");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_constructor);
        tolua_function(tolua_S,"setTSFrame",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSFrame);
        tolua_function(tolua_S,"setTSTexture",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSTexture);
        tolua_function(tolua_S,"setTSRect",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setTSRect);
        tolua_function(tolua_S,"getTSFrame",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSFrame);
        tolua_function(tolua_S,"clearFilter",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_clearFilter);
        tolua_function(tolua_S,"getTSRect",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSRect);
        tolua_function(tolua_S,"getTSTexture",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_getTSTexture);
        tolua_function(tolua_S,"setFilter",lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_setFilter);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_create);
        tolua_function(tolua_S,"createWithTexture", lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithTexture);
        tolua_function(tolua_S,"createWithSpriteFrameName", lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithSpriteFrameName);
        tolua_function(tolua_S,"createWithSpriteFrame", lua_cocos2dx_extension_filter_FilteredSpriteWithMulti_createWithSpriteFrame);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::FilteredSpriteWithMulti).name();
    g_luaType[typeName] = "cc.FilteredSpriteWithMulti";
    g_typeCast["FilteredSpriteWithMulti"] = "cc.FilteredSpriteWithMulti";
    return 1;
}
TOLUA_API int register_all_cocos2dx_extension_filter(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_extension_filter_FilteredSprite(tolua_S);
	lua_register_cocos2dx_extension_filter_Filter(tolua_S);
	lua_register_cocos2dx_extension_filter_RGBFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_TestFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_ZoomBlurFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_MotionBlurFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_FilteredSpriteWithMulti(tolua_S);
	lua_register_cocos2dx_extension_filter_MaskFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_DropShadowFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_SingleFloatParamFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_BlurBaseFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_GaussianHBlurFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_ExposureFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_SharpenFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_HBlurFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_BrightnessFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_SaturationFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_HueFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_ContrastFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_HazeFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_FilteredSpriteWithOne(tolua_S);
	lua_register_cocos2dx_extension_filter_GrayFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_GaussianVBlurFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_CustomFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_SepiaFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_VBlurFilter(tolua_S);
	lua_register_cocos2dx_extension_filter_GammaFilter(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

