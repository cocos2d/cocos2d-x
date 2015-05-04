#include "lua_cocos2dx_manual.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"


USING_NS_CC;

static int tolua_Cocos2d_CCNode_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
        CCPoint point = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
        {
            self->setAnchorPoint(point);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCNode_setAnchorPoint01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
        double pointX = tolua_tonumber(tolua_S, 2, 0);
        double pointY = tolua_tonumber(tolua_S, 3, 0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
        self->setAnchorPoint(ccp(pointX,pointY));
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_CCNode_setAnchorPoint00(tolua_S);
}

static int tolua_Cocos2d_CCNode_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
        const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
        {
            self->setContentSize(*size);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setContentSize'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCNode_setContentSize01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
        double width = tolua_tonumber(tolua_S, 2, 0);
        double height = tolua_tonumber(tolua_S, 3, 0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
        self->setContentSize(CCSizeMake(width, height));
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_CCNode_setContentSize00(tolua_S);
}

static void extendCCNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCNode");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setAnchorPoint", tolua_Cocos2d_CCNode_setAnchorPoint01);
        tolua_function(tolua_S, "setContentSize", tolua_Cocos2d_CCNode_setContentSize01);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_Cocos2d_CCLens3D_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCLens3D",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCLens3D* self = (CCLens3D*)  tolua_tousertype(tolua_S,1,0);
        CCPoint position = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
        {
            self->setPosition(position);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCLens3D_setPosition01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCLens3D",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        CCLens3D* self = (CCLens3D*)  tolua_tousertype(tolua_S,1,0);
        double x = tolua_tonumber(tolua_S, 2, 0);
        double y = tolua_tonumber(tolua_S, 3, 0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
        self->setPosition(ccp(x,y));
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_CCLens3D_setPosition00(tolua_S);
}

static void extendCCLens3D(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCLens3D");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setPosition", tolua_Cocos2d_CCLens3D_setPosition01);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_Cocos2d_CCRipple3D_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCRipple3D",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCRipple3D* self = (CCRipple3D*)  tolua_tousertype(tolua_S,1,0);
        CCPoint position = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
        {
            self->setPosition(position);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCRipple3D_setPosition01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCRipple3D",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        CCRipple3D* self = (CCRipple3D*)  tolua_tousertype(tolua_S,1,0);
        double x = tolua_tonumber(tolua_S, 2, 0);
        double y = tolua_tonumber(tolua_S, 3, 0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
        self->setPosition(ccp(x,y));
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_CCRipple3D_setPosition00(tolua_S);
}

static void extendCCRipple3D(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCRipple3D");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setPosition", tolua_Cocos2d_CCRipple3D_setPosition01);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_Cocos2d_CCTwirl_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCTwirl",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCTwirl* self = (CCTwirl*)  tolua_tousertype(tolua_S,1,0);
        CCPoint position = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
        {
            self->setPosition(position);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCTwirl_setPosition01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCTwirl",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        CCTwirl* self = (CCTwirl*)  tolua_tousertype(tolua_S,1,0);
        double x = tolua_tonumber(tolua_S, 2, 0);
        double y = tolua_tonumber(tolua_S, 3, 0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
        self->setPosition(ccp(x,y));
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_CCTwirl_setPosition00(tolua_S);
}

static void extendCCTwirl(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCTwirl");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setPosition", tolua_Cocos2d_CCTwirl_setPosition01);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_Cocos2d_CCApplication_isIOS64bit(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCApplication",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCApplication* self = (CCApplication*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
        bool isIOS64bit = false;
        TargetPlatform platform = cocos2d::CCApplication::sharedApplication()->getTargetPlatform();
        if (kTargetIphone == platform || kTargetIpad == platform)
        {
#if defined(__LP64__)
            isIOS64bit = true;
#endif
        }
        tolua_pushboolean(tolua_S, isIOS64bit);
        return 1;
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isIOS64bit'.",&tolua_err);
    return 0;
#endif
}

static void extendApplication(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCApplication");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "isIOS64bit", tolua_Cocos2d_CCApplication_isIOS64bit);
    }
    lua_pop(tolua_S, 1);
}

int register_all_cocos2dx_manual(lua_State* tolua_S)
{
    extendCCNode(tolua_S);
    extendCCLens3D(tolua_S);
    extendCCRipple3D(tolua_S);
    extendCCTwirl(tolua_S);
    extendApplication(tolua_S);
    return 0;
}
