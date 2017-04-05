#include "scripting/lua-bindings/auto/lua_cocos2dx_cocosbuilder_auto.hpp"
#include "editor-support/cocosbuilder/CocosBuilder.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cocos2dx_cocosbuilder_CCBAnimationManager_moveAnimationsFromNode(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_moveAnimationsFromNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        cocos2d::Node* arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.CCBAnimationManager:moveAnimationsFromNode");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1, "cc.CCBAnimationManager:moveAnimationsFromNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_moveAnimationsFromNode'", nullptr);
            return 0;
        }
        cobj->moveAnimationsFromNode(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:moveAnimationsFromNode",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_moveAnimationsFromNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_setAutoPlaySequenceId(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setAutoPlaySequenceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.CCBAnimationManager:setAutoPlaySequenceId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setAutoPlaySequenceId'", nullptr);
            return 0;
        }
        cobj->setAutoPlaySequenceId(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:setAutoPlaySequenceId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setAutoPlaySequenceId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNames(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNames'", nullptr);
            return 0;
        }
        cocos2d::ValueVector& ret = cobj->getDocumentCallbackNames();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getDocumentCallbackNames",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNames'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForSoundChannel(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForSoundChannel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocosbuilder::CCBSequenceProperty* arg0;

        ok &= luaval_to_object<cocosbuilder::CCBSequenceProperty>(tolua_S, 2, "cc.CCBSequenceProperty",&arg0, "cc.CCBAnimationManager:actionForSoundChannel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForSoundChannel'", nullptr);
            return 0;
        }
        cocos2d::Sequence* ret = cobj->actionForSoundChannel(arg0);
        object_to_luaval<cocos2d::Sequence>(tolua_S, "cc.Sequence",(cocos2d::Sequence*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:actionForSoundChannel",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForSoundChannel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_setBaseValue(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setBaseValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Value arg0;
        cocos2d::Node* arg1;
        std::string arg2;

        ok &= luaval_to_ccvalue(tolua_S, 2, &arg0, "cc.CCBAnimationManager:setBaseValue");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1, "cc.CCBAnimationManager:setBaseValue");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "cc.CCBAnimationManager:setBaseValue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setBaseValue'", nullptr);
            return 0;
        }
        cobj->setBaseValue(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:setBaseValue",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setBaseValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNodes(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNodes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNodes'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getDocumentOutletNodes();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getDocumentOutletNodes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNodes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getLastCompletedSequenceName(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getLastCompletedSequenceName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getLastCompletedSequenceName'", nullptr);
            return 0;
        }
        std::string ret = cobj->getLastCompletedSequenceName();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getLastCompletedSequenceName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getLastCompletedSequenceName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootNode(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.CCBAnimationManager:setRootNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootNode'", nullptr);
            return 0;
        }
        cobj->setRootNode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:setRootNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        double arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.CCBAnimationManager:runAnimationsForSequenceNamedTweenDuration"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.CCBAnimationManager:runAnimationsForSequenceNamedTweenDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration'", nullptr);
            return 0;
        }
        cobj->runAnimationsForSequenceNamedTweenDuration(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:runAnimationsForSequenceNamedTweenDuration",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletName(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CCBAnimationManager:addDocumentOutletName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletName'", nullptr);
            return 0;
        }
        cobj->addDocumentOutletName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:addDocumentOutletName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequences(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequences'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequences'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocosbuilder::CCBSequence *>& ret = cobj->getSequences();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getSequences",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequences'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootContainerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootContainerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootContainerSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getRootContainerSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getRootContainerSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootContainerSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_setDocumentControllerName(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setDocumentControllerName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CCBAnimationManager:setDocumentControllerName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setDocumentControllerName'", nullptr);
            return 0;
        }
        cobj->setDocumentControllerName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:setDocumentControllerName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setDocumentControllerName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_setObject(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Ref* arg0;
        cocos2d::Node* arg1;
        std::string arg2;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0, "cc.CCBAnimationManager:setObject");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1, "cc.CCBAnimationManager:setObject");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "cc.CCBAnimationManager:setObject");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setObject'", nullptr);
            return 0;
        }
        cobj->setObject(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:setObject",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setObject'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getContainerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getContainerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.CCBAnimationManager:getContainerSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getContainerSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getContainerSize(arg0);
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getContainerSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getContainerSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForCallbackChannel(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForCallbackChannel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocosbuilder::CCBSequenceProperty* arg0;

        ok &= luaval_to_object<cocosbuilder::CCBSequenceProperty>(tolua_S, 2, "cc.CCBSequenceProperty",&arg0, "cc.CCBAnimationManager:actionForCallbackChannel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForCallbackChannel'", nullptr);
            return 0;
        }
        cocos2d::Sequence* ret = cobj->actionForCallbackChannel(arg0);
        object_to_luaval<cocos2d::Sequence>(tolua_S, "cc.Sequence",(cocos2d::Sequence*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:actionForCallbackChannel",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForCallbackChannel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNames(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNames'", nullptr);
            return 0;
        }
        cocos2d::ValueVector& ret = cobj->getDocumentOutletNames();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getDocumentOutletNames",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNames'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackControlEvents(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackControlEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::EventType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.CCBAnimationManager:addDocumentCallbackControlEvents");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackControlEvents'", nullptr);
            return 0;
        }
        cobj->addDocumentCallbackControlEvents(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:addDocumentCallbackControlEvents",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackControlEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_init(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getKeyframeCallbacks(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getKeyframeCallbacks'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getKeyframeCallbacks'", nullptr);
            return 0;
        }
        cocos2d::ValueVector& ret = cobj->getKeyframeCallbacks();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getKeyframeCallbacks",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getKeyframeCallbacks'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackControlEvents(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackControlEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackControlEvents'", nullptr);
            return 0;
        }
        cocos2d::ValueVector& ret = cobj->getDocumentCallbackControlEvents();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getDocumentCallbackControlEvents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackControlEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootContainerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootContainerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.CCBAnimationManager:setRootContainerSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootContainerSize'", nullptr);
            return 0;
        }
        cobj->setRootContainerSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:setRootContainerSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootContainerSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        double arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.CCBAnimationManager:runAnimationsForSequenceIdTweenDuration");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.CCBAnimationManager:runAnimationsForSequenceIdTweenDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration'", nullptr);
            return 0;
        }
        cobj->runAnimationsForSequenceIdTweenDuration(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:runAnimationsForSequenceIdTweenDuration",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRunningSequenceName(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRunningSequenceName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRunningSequenceName'", nullptr);
            return 0;
        }
        const char* ret = cobj->getRunningSequenceName();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getRunningSequenceName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRunningSequenceName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getAutoPlaySequenceId(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getAutoPlaySequenceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getAutoPlaySequenceId'", nullptr);
            return 0;
        }
        int ret = cobj->getAutoPlaySequenceId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getAutoPlaySequenceId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getAutoPlaySequenceId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackName(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CCBAnimationManager:addDocumentCallbackName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackName'", nullptr);
            return 0;
        }
        cobj->addDocumentCallbackName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:addDocumentCallbackName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootNode(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootNode'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getRootNode();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getRootNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletNode(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.CCBAnimationManager:addDocumentOutletNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletNode'", nullptr);
            return 0;
        }
        cobj->addDocumentOutletNode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:addDocumentOutletNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.CCBAnimationManager:getSequenceDuration"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceDuration'", nullptr);
            return 0;
        }
        double ret = cobj->getSequenceDuration(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getSequenceDuration",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackNode(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.CCBAnimationManager:addDocumentCallbackNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackNode'", nullptr);
            return 0;
        }
        cobj->addDocumentCallbackNode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:addDocumentCallbackNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamed(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.CCBAnimationManager:runAnimationsForSequenceNamed"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamed'", nullptr);
            return 0;
        }
        cobj->runAnimationsForSequenceNamed(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:runAnimationsForSequenceNamed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceId(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.CCBAnimationManager:getSequenceId"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceId'", nullptr);
            return 0;
        }
        int ret = cobj->getSequenceId(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getSequenceId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNodes(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNodes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNodes'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getDocumentCallbackNodes();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getDocumentCallbackNodes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNodes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_setSequences(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setSequences'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocosbuilder::CCBSequence *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.CCBAnimationManager:setSequences");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setSequences'", nullptr);
            return 0;
        }
        cobj->setSequences(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:setSequences",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_setSequences'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_debug(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_debug'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_debug'", nullptr);
            return 0;
        }
        cobj->debug();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:debug",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_debug'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentControllerName(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentControllerName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentControllerName'", nullptr);
            return 0;
        }
        std::string ret = cobj->getDocumentControllerName();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:getDocumentControllerName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentControllerName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBAnimationManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBAnimationManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocosbuilder::CCBAnimationManager();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CCBAnimationManager");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBAnimationManager:CCBAnimationManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBAnimationManager_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_cocosbuilder_CCBAnimationManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCBAnimationManager)");
    return 0;
}

int lua_register_cocos2dx_cocosbuilder_CCBAnimationManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.CCBAnimationManager");
    tolua_cclass(tolua_S,"CCBAnimationManager","cc.CCBAnimationManager","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"CCBAnimationManager");
        tolua_function(tolua_S,"new",lua_cocos2dx_cocosbuilder_CCBAnimationManager_constructor);
        tolua_function(tolua_S,"moveAnimationsFromNode",lua_cocos2dx_cocosbuilder_CCBAnimationManager_moveAnimationsFromNode);
        tolua_function(tolua_S,"setAutoPlaySequenceId",lua_cocos2dx_cocosbuilder_CCBAnimationManager_setAutoPlaySequenceId);
        tolua_function(tolua_S,"getDocumentCallbackNames",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNames);
        tolua_function(tolua_S,"actionForSoundChannel",lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForSoundChannel);
        tolua_function(tolua_S,"setBaseValue",lua_cocos2dx_cocosbuilder_CCBAnimationManager_setBaseValue);
        tolua_function(tolua_S,"getDocumentOutletNodes",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNodes);
        tolua_function(tolua_S,"getLastCompletedSequenceName",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getLastCompletedSequenceName);
        tolua_function(tolua_S,"setRootNode",lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootNode);
        tolua_function(tolua_S,"runAnimationsForSequenceNamedTweenDuration",lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration);
        tolua_function(tolua_S,"addDocumentOutletName",lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletName);
        tolua_function(tolua_S,"getSequences",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequences);
        tolua_function(tolua_S,"getRootContainerSize",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootContainerSize);
        tolua_function(tolua_S,"setDocumentControllerName",lua_cocos2dx_cocosbuilder_CCBAnimationManager_setDocumentControllerName);
        tolua_function(tolua_S,"setObject",lua_cocos2dx_cocosbuilder_CCBAnimationManager_setObject);
        tolua_function(tolua_S,"getContainerSize",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getContainerSize);
        tolua_function(tolua_S,"actionForCallbackChannel",lua_cocos2dx_cocosbuilder_CCBAnimationManager_actionForCallbackChannel);
        tolua_function(tolua_S,"getDocumentOutletNames",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentOutletNames);
        tolua_function(tolua_S,"addDocumentCallbackControlEvents",lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackControlEvents);
        tolua_function(tolua_S,"init",lua_cocos2dx_cocosbuilder_CCBAnimationManager_init);
        tolua_function(tolua_S,"getKeyframeCallbacks",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getKeyframeCallbacks);
        tolua_function(tolua_S,"getDocumentCallbackControlEvents",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackControlEvents);
        tolua_function(tolua_S,"setRootContainerSize",lua_cocos2dx_cocosbuilder_CCBAnimationManager_setRootContainerSize);
        tolua_function(tolua_S,"runAnimationsForSequenceIdTweenDuration",lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration);
        tolua_function(tolua_S,"getRunningSequenceName",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRunningSequenceName);
        tolua_function(tolua_S,"getAutoPlaySequenceId",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getAutoPlaySequenceId);
        tolua_function(tolua_S,"addDocumentCallbackName",lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackName);
        tolua_function(tolua_S,"getRootNode",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getRootNode);
        tolua_function(tolua_S,"addDocumentOutletNode",lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentOutletNode);
        tolua_function(tolua_S,"getSequenceDuration",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceDuration);
        tolua_function(tolua_S,"addDocumentCallbackNode",lua_cocos2dx_cocosbuilder_CCBAnimationManager_addDocumentCallbackNode);
        tolua_function(tolua_S,"runAnimationsForSequenceNamed",lua_cocos2dx_cocosbuilder_CCBAnimationManager_runAnimationsForSequenceNamed);
        tolua_function(tolua_S,"getSequenceId",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getSequenceId);
        tolua_function(tolua_S,"getDocumentCallbackNodes",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentCallbackNodes);
        tolua_function(tolua_S,"setSequences",lua_cocos2dx_cocosbuilder_CCBAnimationManager_setSequences);
        tolua_function(tolua_S,"debug",lua_cocos2dx_cocosbuilder_CCBAnimationManager_debug);
        tolua_function(tolua_S,"getDocumentControllerName",lua_cocos2dx_cocosbuilder_CCBAnimationManager_getDocumentControllerName);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocosbuilder::CCBAnimationManager).name();
    g_luaType[typeName] = "cc.CCBAnimationManager";
    g_typeCast["CCBAnimationManager"] = "cc.CCBAnimationManager";
    return 1;
}

int lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletName(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CCBReader:addOwnerOutletName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletName'", nullptr);
            return 0;
        }
        cobj->addOwnerOutletName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:addOwnerOutletName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNames(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNames'", nullptr);
            return 0;
        }
        cocos2d::ValueVector ret = cobj->getOwnerCallbackNames();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getOwnerCallbackNames",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNames'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_addDocumentCallbackControlEvents(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_addDocumentCallbackControlEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::EventType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.CCBReader:addDocumentCallbackControlEvents");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_addDocumentCallbackControlEvents'", nullptr);
            return 0;
        }
        cobj->addDocumentCallbackControlEvents(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:addDocumentCallbackControlEvents",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_addDocumentCallbackControlEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_setCCBRootPath(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_setCCBRootPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.CCBReader:setCCBRootPath"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_setCCBRootPath'", nullptr);
            return 0;
        }
        cobj->setCCBRootPath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:setCCBRootPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_setCCBRootPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletNode(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.CCBReader:addOwnerOutletNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletNode'", nullptr);
            return 0;
        }
        cobj->addOwnerOutletNode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:addOwnerOutletNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNodes(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNodes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNodes'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getOwnerCallbackNodes();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getOwnerCallbackNodes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNodes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_readSoundKeyframesForSeq(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_readSoundKeyframesForSeq'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocosbuilder::CCBSequence* arg0;

        ok &= luaval_to_object<cocosbuilder::CCBSequence>(tolua_S, 2, "cc.CCBSequence",&arg0, "cc.CCBReader:readSoundKeyframesForSeq");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_readSoundKeyframesForSeq'", nullptr);
            return 0;
        }
        bool ret = cobj->readSoundKeyframesForSeq(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:readSoundKeyframesForSeq",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_readSoundKeyframesForSeq'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getCCBRootPath(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getCCBRootPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getCCBRootPath'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getCCBRootPath();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getCCBRootPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getCCBRootPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackControlEvents(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackControlEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackControlEvents'", nullptr);
            return 0;
        }
        cocos2d::ValueVector& ret = cobj->getOwnerCallbackControlEvents();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getOwnerCallbackControlEvents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackControlEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNodes(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNodes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNodes'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getOwnerOutletNodes();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getOwnerOutletNodes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNodes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_readUTF8(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_readUTF8'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_readUTF8'", nullptr);
            return 0;
        }
        std::string ret = cobj->readUTF8();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:readUTF8",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_readUTF8'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_addOwnerCallbackControlEvents(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerCallbackControlEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::EventType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.CCBReader:addOwnerCallbackControlEvents");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerCallbackControlEvents'", nullptr);
            return 0;
        }
        cobj->addOwnerCallbackControlEvents(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:addOwnerCallbackControlEvents",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_addOwnerCallbackControlEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNames(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNames'", nullptr);
            return 0;
        }
        cocos2d::ValueVector ret = cobj->getOwnerOutletNames();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getOwnerOutletNames",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNames'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_setAnimationManager(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_setAnimationManager'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocosbuilder::CCBAnimationManager* arg0;

        ok &= luaval_to_object<cocosbuilder::CCBAnimationManager>(tolua_S, 2, "cc.CCBAnimationManager",&arg0, "cc.CCBReader:setAnimationManager");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_setAnimationManager'", nullptr);
            return 0;
        }
        cobj->setAnimationManager(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:setAnimationManager",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_setAnimationManager'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_readCallbackKeyframesForSeq(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_readCallbackKeyframesForSeq'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocosbuilder::CCBSequence* arg0;

        ok &= luaval_to_object<cocosbuilder::CCBSequence>(tolua_S, 2, "cc.CCBSequence",&arg0, "cc.CCBReader:readCallbackKeyframesForSeq");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_readCallbackKeyframesForSeq'", nullptr);
            return 0;
        }
        bool ret = cobj->readCallbackKeyframesForSeq(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:readCallbackKeyframesForSeq",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_readCallbackKeyframesForSeq'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManagersForNodes(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManagersForNodes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManagersForNodes'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocosbuilder::CCBAnimationManager *>& ret = cobj->getAnimationManagersForNodes();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getAnimationManagersForNodes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManagersForNodes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getNodesWithAnimationManagers(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getNodesWithAnimationManagers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getNodesWithAnimationManagers'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getNodesWithAnimationManagers();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getNodesWithAnimationManagers",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getNodesWithAnimationManagers'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManager(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocosbuilder::CCBReader*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManager'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManager'", nullptr);
            return 0;
        }
        cocosbuilder::CCBAnimationManager* ret = cobj->getAnimationManager();
        object_to_luaval<cocosbuilder::CCBAnimationManager>(tolua_S, "cc.CCBAnimationManager",(cocosbuilder::CCBAnimationManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCBReader:getAnimationManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManager'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_setResolutionScale(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.CCBReader:setResolutionScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosbuilder_CCBReader_setResolutionScale'", nullptr);
            return 0;
        }
        cocosbuilder::CCBReader::setResolutionScale(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CCBReader:setResolutionScale",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_setResolutionScale'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_cocosbuilder_CCBReader_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocosbuilder::CCBReader* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocosbuilder::CCBReader* arg0;
            ok &= luaval_to_object<cocosbuilder::CCBReader>(tolua_S, 2, "cc.CCBReader",&arg0, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cobj = new cocosbuilder::CCBReader(arg0);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CCBReader");
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocosbuilder::NodeLoaderLibrary* arg0;
            ok &= luaval_to_object<cocosbuilder::NodeLoaderLibrary>(tolua_S, 2, "cc.NodeLoaderLibrary",&arg0, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cobj = new cocosbuilder::CCBReader(arg0);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CCBReader");
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocosbuilder::NodeLoaderLibrary* arg0;
            ok &= luaval_to_object<cocosbuilder::NodeLoaderLibrary>(tolua_S, 2, "cc.NodeLoaderLibrary",&arg0, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cocosbuilder::CCBMemberVariableAssigner* arg1;
            ok &= luaval_to_object<cocosbuilder::CCBMemberVariableAssigner>(tolua_S, 3, "cc.CCBMemberVariableAssigner",&arg1, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cobj = new cocosbuilder::CCBReader(arg0, arg1);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CCBReader");
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocosbuilder::NodeLoaderLibrary* arg0;
            ok &= luaval_to_object<cocosbuilder::NodeLoaderLibrary>(tolua_S, 2, "cc.NodeLoaderLibrary",&arg0, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cocosbuilder::CCBMemberVariableAssigner* arg1;
            ok &= luaval_to_object<cocosbuilder::CCBMemberVariableAssigner>(tolua_S, 3, "cc.CCBMemberVariableAssigner",&arg1, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cocosbuilder::CCBSelectorResolver* arg2;
            ok &= luaval_to_object<cocosbuilder::CCBSelectorResolver>(tolua_S, 4, "cc.CCBSelectorResolver",&arg2, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cobj = new cocosbuilder::CCBReader(arg0, arg1, arg2);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CCBReader");
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocosbuilder::NodeLoaderLibrary* arg0;
            ok &= luaval_to_object<cocosbuilder::NodeLoaderLibrary>(tolua_S, 2, "cc.NodeLoaderLibrary",&arg0, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cocosbuilder::CCBMemberVariableAssigner* arg1;
            ok &= luaval_to_object<cocosbuilder::CCBMemberVariableAssigner>(tolua_S, 3, "cc.CCBMemberVariableAssigner",&arg1, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cocosbuilder::CCBSelectorResolver* arg2;
            ok &= luaval_to_object<cocosbuilder::CCBSelectorResolver>(tolua_S, 4, "cc.CCBSelectorResolver",&arg2, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cocosbuilder::NodeLoaderListener* arg3;
            ok &= luaval_to_object<cocosbuilder::NodeLoaderListener>(tolua_S, 5, "cc.NodeLoaderListener",&arg3, "cc.CCBReader:CCBReader");

            if (!ok) { break; }
            cobj = new cocosbuilder::CCBReader(arg0, arg1, arg2, arg3);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CCBReader");
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj = new cocosbuilder::CCBReader();
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CCBReader");
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.CCBReader:CCBReader",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosbuilder_CCBReader_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_cocosbuilder_CCBReader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCBReader)");
    return 0;
}

int lua_register_cocos2dx_cocosbuilder_CCBReader(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.CCBReader");
    tolua_cclass(tolua_S,"CCBReader","cc.CCBReader","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"CCBReader");
        tolua_function(tolua_S,"new",lua_cocos2dx_cocosbuilder_CCBReader_constructor);
        tolua_function(tolua_S,"addOwnerOutletName",lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletName);
        tolua_function(tolua_S,"getOwnerCallbackNames",lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNames);
        tolua_function(tolua_S,"addDocumentCallbackControlEvents",lua_cocos2dx_cocosbuilder_CCBReader_addDocumentCallbackControlEvents);
        tolua_function(tolua_S,"setCCBRootPath",lua_cocos2dx_cocosbuilder_CCBReader_setCCBRootPath);
        tolua_function(tolua_S,"addOwnerOutletNode",lua_cocos2dx_cocosbuilder_CCBReader_addOwnerOutletNode);
        tolua_function(tolua_S,"getOwnerCallbackNodes",lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackNodes);
        tolua_function(tolua_S,"readSoundKeyframesForSeq",lua_cocos2dx_cocosbuilder_CCBReader_readSoundKeyframesForSeq);
        tolua_function(tolua_S,"getCCBRootPath",lua_cocos2dx_cocosbuilder_CCBReader_getCCBRootPath);
        tolua_function(tolua_S,"getOwnerCallbackControlEvents",lua_cocos2dx_cocosbuilder_CCBReader_getOwnerCallbackControlEvents);
        tolua_function(tolua_S,"getOwnerOutletNodes",lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNodes);
        tolua_function(tolua_S,"readUTF8",lua_cocos2dx_cocosbuilder_CCBReader_readUTF8);
        tolua_function(tolua_S,"addOwnerCallbackControlEvents",lua_cocos2dx_cocosbuilder_CCBReader_addOwnerCallbackControlEvents);
        tolua_function(tolua_S,"getOwnerOutletNames",lua_cocos2dx_cocosbuilder_CCBReader_getOwnerOutletNames);
        tolua_function(tolua_S,"setActionManager",lua_cocos2dx_cocosbuilder_CCBReader_setAnimationManager);
        tolua_function(tolua_S,"readCallbackKeyframesForSeq",lua_cocos2dx_cocosbuilder_CCBReader_readCallbackKeyframesForSeq);
        tolua_function(tolua_S,"getAnimationManagersForNodes",lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManagersForNodes);
        tolua_function(tolua_S,"getNodesWithAnimationManagers",lua_cocos2dx_cocosbuilder_CCBReader_getNodesWithAnimationManagers);
        tolua_function(tolua_S,"getActionManager",lua_cocos2dx_cocosbuilder_CCBReader_getAnimationManager);
        tolua_function(tolua_S,"setResolutionScale", lua_cocos2dx_cocosbuilder_CCBReader_setResolutionScale);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocosbuilder::CCBReader).name();
    g_luaType[typeName] = "cc.CCBReader";
    g_typeCast["CCBReader"] = "cc.CCBReader";
    return 1;
}
TOLUA_API int register_all_cocos2dx_cocosbuilder(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_cocosbuilder_CCBAnimationManager(tolua_S);
	lua_register_cocos2dx_cocosbuilder_CCBReader(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

