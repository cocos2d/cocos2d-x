#ifdef __cplusplus
extern "C" {
#endif
    #include "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include <map>
#include <string>
#include "Lua_extensions_CCB.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCBProxy.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#ifdef __cplusplus
static int tolua_collect_CCBAnimationManager (lua_State* tolua_S)
{
    CCBAnimationManager* self = (CCBAnimationManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCBReader (lua_State* tolua_S)
{
    CCBReader* self = (CCBReader*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCBProxy (lua_State* tolua_S)
{
    CCBProxy *self = (CCBProxy*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif
/* function to release collected object via destructor */
static void tolua_reg_extensions_ccb_type(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "CCBAnimationManager");
    tolua_usertype(tolua_S, "CCBReader");
    tolua_usertype(tolua_S, "CCBProxy");
}

/* method: delete of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_delete00
static int tolua_Cocos2d_CCBReader_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
        Mtolua_delete(self);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_new00
static int tolua_Cocos2d_CCBReader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            CCBReader* tolua_ret = (CCBReader*)  Mtolua_new((CCBReader)());
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBReader");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_new00_local
static int tolua_Cocos2d_CCBReader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            CCBReader* tolua_ret = (CCBReader*)  Mtolua_new((CCBReader)());
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBReader");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOwnerCallbackNames of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getOwnerCallbackNames00
static int tolua_Cocos2d_CCBReader_getOwnerCallbackNames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOwnerCallbackNames'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getOwnerCallbackNames();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getOwnerCallbackNames'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCCBRootPath of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_setCCBRootPath00
static int tolua_Cocos2d_CCBReader_setCCBRootPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
        const char* pCCBRootPath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCCBRootPath'", NULL);
#endif
        {
            self->setCCBRootPath(pCCBRootPath);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setCCBRootPath'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOwnerCallbackNodes of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getOwnerCallbackNodes00
static int tolua_Cocos2d_CCBReader_getOwnerCallbackNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOwnerCallbackNodes'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getOwnerCallbackNodes();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getOwnerCallbackNodes'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCCBRootPath of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getCCBRootPath00
static int tolua_Cocos2d_CCBReader_getCCBRootPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const CCBReader* self = (const CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCCBRootPath'", NULL);
#endif
        {
            const std::string tolua_ret = (const std::string)  self->getCCBRootPath();
            tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getCCBRootPath'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOwnerOutletNodes of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getOwnerOutletNodes00
static int tolua_Cocos2d_CCBReader_getOwnerOutletNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOwnerOutletNodes'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getOwnerOutletNodes();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getOwnerOutletNodes'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readUTF8 of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_readUTF800
static int tolua_Cocos2d_CCBReader_readUTF800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readUTF8'", NULL);
#endif
        {
            std::string tolua_ret = (std::string)  self->readUTF8();
            tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'readUTF8'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOwnerOutletNames of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getOwnerOutletNames00
static int tolua_Cocos2d_CCBReader_getOwnerOutletNames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOwnerOutletNames'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getOwnerOutletNames();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getOwnerOutletNames'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationManagers of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_setAnimationManagers00
static int tolua_Cocos2d_CCBReader_setAnimationManagers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCDictionary",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
        CCDictionary* x = ((CCDictionary*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationManagers'", NULL);
#endif
        {
            self->setAnimationManagers(x);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setAnimationManagers'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimationManagersForNodes of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getAnimationManagersForNodes00
static int tolua_Cocos2d_CCBReader_getAnimationManagersForNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationManagersForNodes'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getAnimationManagersForNodes();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getAnimationManagersForNodes'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNodesWithAnimationManagers of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getNodesWithAnimationManagers00
static int tolua_Cocos2d_CCBReader_getNodesWithAnimationManagers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodesWithAnimationManagers'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getNodesWithAnimationManagers();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getNodesWithAnimationManagers'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimationManager of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getAnimationManager00
static int tolua_Cocos2d_CCBReader_getAnimationManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationManager'", NULL);
#endif
        {
            CCBAnimationManager* tolua_ret = (CCBAnimationManager*)  self->getAnimationManager();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBAnimationManager");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getAnimationManager'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setResolutionScale of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_setResolutionScale00
static int tolua_Cocos2d_CCBReader_setResolutionScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        float scale = ((float)  tolua_tonumber(tolua_S,2,0));
        {
            CCBReader::setResolutionScale(scale);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setResolutionScale'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_new01
static int tolua_Cocos2d_CCBReader_new01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        {
            CCBReader* tolua_ret = (CCBReader*)  Mtolua_new((CCBReader)());
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBReader");
        }
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCBReader_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_new01_local
static int tolua_Cocos2d_CCBReader_new01_local(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        {
            CCBReader* tolua_ret = (CCBReader*)  Mtolua_new((CCBReader)());
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBReader");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCBReader_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOwner of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBReader_getAnimationManager00
static int tolua_Cocos2d_ccbreader_getOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBReader* self = (CCBReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOwner'", NULL);
#endif
        {
            CCObject* tolua_ret = (CCObject*)self->getOwner();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCObject");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getOwner'.",&tolua_err);
    return 0;
#endif
}
#endif//#ifndef TOLUA_DISABLE

/* method: new of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_new00
static int tolua_Cocos2d_CCBAnimationManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            CCBAnimationManager* tolua_ret = (CCBAnimationManager*)  Mtolua_new((CCBAnimationManager)());
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBAnimationManager");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_new00_local
static int tolua_Cocos2d_CCBAnimationManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            CCBAnimationManager* tolua_ret = (CCBAnimationManager*)  Mtolua_new((CCBAnimationManager)());
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBAnimationManager");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_delete00
static int tolua_Cocos2d_CCBAnimationManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
        Mtolua_delete(self);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: moveAnimationsFromNode of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_moveAnimationsFromNode00
static int tolua_Cocos2d_CCBAnimationManager_moveAnimationsFromNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        CCNode* fromNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
        CCNode* toNode = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'moveAnimationsFromNode'", NULL);
#endif
        {
            self->moveAnimationsFromNode(fromNode,toNode);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'moveAnimationsFromNode'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAutoPlaySequenceId of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_setAutoPlaySequenceId00
static int tolua_Cocos2d_CCBAnimationManager_setAutoPlaySequenceId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        int autoPlaySequenceId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAutoPlaySequenceId'", NULL);
#endif
        {
            self->setAutoPlaySequenceId(autoPlaySequenceId);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setAutoPlaySequenceId'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDocumentCallbackNames of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getDocumentCallbackNames00
static int tolua_Cocos2d_CCBAnimationManager_getDocumentCallbackNames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDocumentCallbackNames'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getDocumentCallbackNames();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getDocumentCallbackNames'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBaseValue of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_setBaseValue00
static int tolua_Cocos2d_CCBAnimationManager_setBaseValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
        !tolua_isstring(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        CCObject* pValue = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
        CCNode* pNode = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
        const char* pPropName = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBaseValue'", NULL);
#endif
        {
            self->setBaseValue(pValue,pNode,pPropName);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setBaseValue'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDocumentOutletNodes of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getDocumentOutletNodes00
static int tolua_Cocos2d_CCBAnimationManager_getDocumentOutletNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDocumentOutletNodes'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getDocumentOutletNodes();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getDocumentOutletNodes'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_addNode00
static int tolua_Cocos2d_CCBAnimationManager_addNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCDictionary",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        CCNode* pNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
        CCDictionary* pSeq = ((CCDictionary*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
        {
            self->addNode(pNode,pSeq);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addNode'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastCompletedSequenceName of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getLastCompletedSequenceName00
static int tolua_Cocos2d_CCBAnimationManager_getLastCompletedSequenceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastCompletedSequenceName'", NULL);
#endif
        {
            std::string tolua_ret = (std::string)  self->getLastCompletedSequenceName();
            tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getLastCompletedSequenceName'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRootNode of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_setRootNode00
static int tolua_Cocos2d_CCBAnimationManager_setRootNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        CCNode* pRootNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRootNode'", NULL);
#endif
        {
            self->setRootNode(pRootNode);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setRootNode'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDocumentOutletName of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_addDocumentOutletName00
static int tolua_Cocos2d_CCBAnimationManager_addDocumentOutletName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDocumentOutletName'", NULL);
#endif
        {
            self->addDocumentOutletName(name);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addDocumentOutletName'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSequences of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getSequences00
static int tolua_Cocos2d_CCBAnimationManager_getSequences00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSequences'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getSequences();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getSequences'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootContainerSize of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getRootContainerSize00
static int tolua_Cocos2d_CCBAnimationManager_getRootContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootContainerSize'", NULL);
#endif
        {
            const CCSize& tolua_ret = (const CCSize&)  self->getRootContainerSize();
            tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getRootContainerSize'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDocumentControllerName of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_setDocumentControllerName00
static int tolua_Cocos2d_CCBAnimationManager_setDocumentControllerName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDocumentControllerName'", NULL);
#endif
        {
            self->setDocumentControllerName(name);
            tolua_pushcppstring(tolua_S,(const char*)name);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setDocumentControllerName'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContainerSize of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getContainerSize00
static int tolua_Cocos2d_CCBAnimationManager_getContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        CCNode* pNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContainerSize'", NULL);
#endif
        {
            const CCSize& tolua_ret = (const CCSize&)  self->getContainerSize(pNode);
            tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getContainerSize'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDocumentOutletNames of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getDocumentOutletNames00
static int tolua_Cocos2d_CCBAnimationManager_getDocumentOutletNames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDocumentOutletNames'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getDocumentOutletNames();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getDocumentOutletNames'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_init00
static int tolua_Cocos2d_CCBAnimationManager_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->init();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getKeyframeCallbacks of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getKeyframeCallbacks00
static int tolua_Cocos2d_CCBAnimationManager_getKeyframeCallbacks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getKeyframeCallbacks'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getKeyframeCallbacks();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getKeyframeCallbacks'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: runAnimationsForSequenceNamedTweenDuration of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration00
static int tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        const char* pName = ((const char*)  tolua_tostring(tolua_S,2,0));
        float fTweenDuration = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runAnimationsForSequenceNamedTweenDuration'", NULL);
#endif
        {
            self->runAnimationsForSequenceNamedTweenDuration(pName,fTweenDuration);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'runAnimationsForSequenceNamedTweenDuration'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRootContainerSize of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_setRootContainerSize00
static int tolua_Cocos2d_CCBAnimationManager_setRootContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        const CCSize* rootContainerSize = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRootContainerSize'", NULL);
#endif
        {
            self->setRootContainerSize(*rootContainerSize);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setRootContainerSize'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: runAnimationsForSequenceIdTweenDuration of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration00
static int tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        int nSeqId = ((int)  tolua_tonumber(tolua_S,2,0));
        float fTweenDuraiton = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runAnimationsForSequenceIdTweenDuration'", NULL);
#endif
        {
            self->runAnimationsForSequenceIdTweenDuration(nSeqId,fTweenDuraiton);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'runAnimationsForSequenceIdTweenDuration'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRunningSequenceName of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getRunningSequenceName00
static int tolua_Cocos2d_CCBAnimationManager_getRunningSequenceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRunningSequenceName'", NULL);
#endif
        {
            const char* tolua_ret = (const char*)  self->getRunningSequenceName();
            tolua_pushstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getRunningSequenceName'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAutoPlaySequenceId of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getAutoPlaySequenceId00
static int tolua_Cocos2d_CCBAnimationManager_getAutoPlaySequenceId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAutoPlaySequenceId'", NULL);
#endif
        {
            int tolua_ret = (int)  self->getAutoPlaySequenceId();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getAutoPlaySequenceId'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDocumentCallbackName of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_addDocumentCallbackName00
static int tolua_Cocos2d_CCBAnimationManager_addDocumentCallbackName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDocumentCallbackName'", NULL);
#endif
        {
            self->addDocumentCallbackName(name);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addDocumentCallbackName'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootNode of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getRootNode00
static int tolua_Cocos2d_CCBAnimationManager_getRootNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootNode'", NULL);
#endif
        {
            CCNode* tolua_ret = (CCNode*)  self->getRootNode();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getRootNode'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDocumentOutletNode of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_addDocumentOutletNode00
static int tolua_Cocos2d_CCBAnimationManager_addDocumentOutletNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDocumentOutletNode'", NULL);
#endif
        {
            self->addDocumentOutletNode(node);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addDocumentOutletNode'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDocumentCallbackNode of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_addDocumentCallbackNode00
static int tolua_Cocos2d_CCBAnimationManager_addDocumentCallbackNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDocumentCallbackNode'", NULL);
#endif
        {
            self->addDocumentCallbackNode(node);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addDocumentCallbackNode'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: runAnimationsForSequenceNamedTweenDuration of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration01
static int tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        const char* pName = ((const char*)  tolua_tostring(tolua_S,2,0));
        float fTweenDuration = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runAnimationsForSequenceNamedTweenDuration'", NULL);
#endif
        {
            self->runAnimationsForSequenceNamedTweenDuration(pName,fTweenDuration);
        }
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: runAnimationsForSequenceNamed of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamed00
static int tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        const char* pName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runAnimationsForSequenceNamed'", NULL);
#endif
        {
            self->runAnimationsForSequenceNamed(pName);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'runAnimationsForSequenceNamed'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDocumentCallbackNodes of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getDocumentCallbackNodes00
static int tolua_Cocos2d_CCBAnimationManager_getDocumentCallbackNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDocumentCallbackNodes'", NULL);
#endif
        {
            CCArray* tolua_ret = (CCArray*)  self->getDocumentCallbackNodes();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getDocumentCallbackNodes'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSequences of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_setSequences00
static int tolua_Cocos2d_CCBAnimationManager_setSequences00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
        CCArray* seq = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSequences'", NULL);
#endif
        {
            self->setSequences(seq);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setSequences'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: debug of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_debug00
static int tolua_Cocos2d_CCBAnimationManager_debug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'debug'", NULL);
#endif
        {
            self->debug();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'debug'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDocumentControllerName of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_getDocumentControllerName00
static int tolua_Cocos2d_CCBAnimationManager_getDocumentControllerName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDocumentControllerName'", NULL);
#endif
        {
            std::string tolua_ret = (std::string)  self->getDocumentControllerName();
            tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getDocumentControllerName'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCallFunc of class  CCBAnimationManager */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed00
static int tolua_Cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2, "CCCallFunc", 0, &tolua_err)       ||
        !tolua_isstring(tolua_S, 3, 0, &tolua_err)                      ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBAnimationManager* self = (CCBAnimationManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCallFuncForLuaCallbackNamed'", NULL);
#endif
        {
            CCCallFunc* pCallFunc = ((CCCallFunc*)  tolua_tousertype(tolua_S,2,0));
            const char* keyframeCallback = ((const char*)  tolua_tostring(tolua_S,3,0));
            std::string strKey = "";
            if (NULL != keyframeCallback) {
                strKey = keyframeCallback;
            }
            self->setCallFunc(pCallFunc, strKey);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setCallFuncForLuaCallbackNamed'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCBProxy_ */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_create00
static int tolua_Cocos2d_CCBProxy_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBProxy",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            CCBProxy *tolua_ret = (CCBProxy*)CCBProxy::create();
            tolua_ret->init();
            int  nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int *pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBProxy");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCBProxy_delete00 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBProxy_delete00
static int tolua_Cocos2d_CCBProxy_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBProxy* self = (CCBProxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
        Mtolua_delete(self);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCBProxy */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBProxy_new00
static int tolua_Cocos2d_CCBProxy_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBProxy",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            CCBProxy* tolua_ret = (CCBProxy*)  Mtolua_new((CCBProxy)());
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBProxy");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCBProxy */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBProxy_new00_local
static int tolua_Cocos2d_CCBProxy_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCBProxy",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            CCBProxy* tolua_ret = (CCBProxy*)  Mtolua_new((CCBProxy)());
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBProxy");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOwnerCallbackNodes of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBProxy_createCCBreader00
static int tolua_Cocos2d_CCBProxy_createCCBreader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBProxy* self = (CCBProxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateCCBreader'", NULL);
#endif
        {
            CCBReader* tolua_ret = (CCBReader*) self->createCCBreader();
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBReader");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'CreateCCBreader'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOwnerCallbackNodes of class  CCBReader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBProxy_readCCBFromFile00
static int tolua_Cocos2d_CCBProxy_readCCBFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err)||
        !tolua_isstring(tolua_S, 2, 0, &tolua_err)||
        !tolua_isusertype(tolua_S,3,"CCBReader",0,&tolua_err)||
        !tolua_isboolean(tolua_S,4,0,&tolua_err ) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBProxy* self = (CCBProxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readCCBFromFile'", NULL);
#endif
        {
            const char* pCCBFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
            CCBReader*  pCCBReader   = ((CCBReader*)  tolua_tousertype(tolua_S,3,0));
            bool  bSetOwner = (bool)  tolua_toboolean(tolua_S,4,0);
            CCNode* tolua_ret = (CCNode*) self->readCCBFromFile(pCCBFilePath, pCCBReader,bSetOwner);
            int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'readCCBFromFile'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNodeTypeName of class  CCBProxy */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBProxy_getNodeTypeName00
static int tolua_Cocos2d_CCBProxy_getNodeTypeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err)   ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBProxy* self = (CCBProxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodeTypeName'", NULL);
#endif
        {
            CCNode* pNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
            const char* tolua_ret = (const char*)self->getNodeTypeName(pNode);
            tolua_pushstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getOwner'.",&tolua_err);
    return 0;
#endif

}
#endif //#ifndef TOLUA_DISABLE


/* method: setCallback of class  CCBProxy */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBProxy_setCallback00
static int tolua_Cocos2d_CCBProxy_setCallback00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err)  ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCBProxy* self = (CCBProxy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCallback'", NULL);
#endif
        {
            CCNode* pNode = ((CCNode*)tolua_tousertype(tolua_S,2,0));
            LUA_FUNCTION nFunID = (  toluafix_ref_function(tolua_S,3,0));
            self->setCallback(pNode, nFunID);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getOwner'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


TOLUA_API int tolua_extensions_ccb_open(lua_State* tolua_S){
    tolua_open(tolua_S);
    tolua_reg_extensions_ccb_type(tolua_S);
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
     #ifdef __cplusplus
     tolua_cclass(tolua_S,"CCBReader","CCBReader","CCObject",tolua_collect_CCBReader);
     #else
     tolua_cclass(tolua_S,"CCBReader","CCBReader","CCObject",NULL);
     #endif
     tolua_beginmodule(tolua_S,"CCBReader");
      tolua_function(tolua_S,"delete",tolua_Cocos2d_CCBReader_delete00);
      tolua_function(tolua_S,"new",tolua_Cocos2d_CCBReader_new00);
      tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCBReader_new00_local);
      tolua_function(tolua_S,".call",tolua_Cocos2d_CCBReader_new00_local);
      tolua_function(tolua_S,"getOwnerCallbackNames",tolua_Cocos2d_CCBReader_getOwnerCallbackNames00);
      tolua_function(tolua_S,"setCCBRootPath",tolua_Cocos2d_CCBReader_setCCBRootPath00);
      tolua_function(tolua_S,"getOwnerCallbackNodes",tolua_Cocos2d_CCBReader_getOwnerCallbackNodes00);
      tolua_function(tolua_S,"getCCBRootPath",tolua_Cocos2d_CCBReader_getCCBRootPath00);
      tolua_function(tolua_S,"getOwnerOutletNodes",tolua_Cocos2d_CCBReader_getOwnerOutletNodes00);
      tolua_function(tolua_S,"readUTF8",tolua_Cocos2d_CCBReader_readUTF800);
      tolua_function(tolua_S,"getOwnerOutletNames",tolua_Cocos2d_CCBReader_getOwnerOutletNames00);
      tolua_function(tolua_S,"setAnimationManagers",tolua_Cocos2d_CCBReader_setAnimationManagers00);
      tolua_function(tolua_S,"getAnimationManagersForNodes",tolua_Cocos2d_CCBReader_getAnimationManagersForNodes00);
      tolua_function(tolua_S,"getNodesWithAnimationManagers",tolua_Cocos2d_CCBReader_getNodesWithAnimationManagers00);
      tolua_function(tolua_S,"getAnimationManager",tolua_Cocos2d_CCBReader_getAnimationManager00);
      tolua_function(tolua_S,"setResolutionScale",tolua_Cocos2d_CCBReader_setResolutionScale00);
      tolua_function(tolua_S,"new",tolua_Cocos2d_CCBReader_new01);
      tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCBReader_new01_local);
      tolua_function(tolua_S,".call",tolua_Cocos2d_CCBReader_new01_local);
    tolua_function(tolua_S, "getOwner", tolua_Cocos2d_ccbreader_getOwner00);
     tolua_endmodule(tolua_S);
     #ifdef __cplusplus
     tolua_cclass(tolua_S,"CCBAnimationManager","CCBAnimationManager","CCObject",tolua_collect_CCBAnimationManager);
     #else
     tolua_cclass(tolua_S,"CCBAnimationManager","CCBAnimationManager","CCObject",NULL);
     #endif
     tolua_beginmodule(tolua_S,"CCBAnimationManager");
      tolua_function(tolua_S,"new",tolua_Cocos2d_CCBAnimationManager_new00);
      tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCBAnimationManager_new00_local);
      tolua_function(tolua_S,".call",tolua_Cocos2d_CCBAnimationManager_new00_local);
      tolua_function(tolua_S,"delete",tolua_Cocos2d_CCBAnimationManager_delete00);
      tolua_function(tolua_S,"moveAnimationsFromNode",tolua_Cocos2d_CCBAnimationManager_moveAnimationsFromNode00);
      tolua_function(tolua_S,"setAutoPlaySequenceId",tolua_Cocos2d_CCBAnimationManager_setAutoPlaySequenceId00);
      tolua_function(tolua_S,"getDocumentCallbackNames",tolua_Cocos2d_CCBAnimationManager_getDocumentCallbackNames00);
      tolua_function(tolua_S,"setBaseValue",tolua_Cocos2d_CCBAnimationManager_setBaseValue00);
      tolua_function(tolua_S,"getDocumentOutletNodes",tolua_Cocos2d_CCBAnimationManager_getDocumentOutletNodes00);
      tolua_function(tolua_S,"addNode",tolua_Cocos2d_CCBAnimationManager_addNode00);
      tolua_function(tolua_S,"getLastCompletedSequenceName",tolua_Cocos2d_CCBAnimationManager_getLastCompletedSequenceName00);
      tolua_function(tolua_S,"setRootNode",tolua_Cocos2d_CCBAnimationManager_setRootNode00);
      tolua_function(tolua_S,"addDocumentOutletName",tolua_Cocos2d_CCBAnimationManager_addDocumentOutletName00);
      tolua_function(tolua_S,"getSequences",tolua_Cocos2d_CCBAnimationManager_getSequences00);
      tolua_function(tolua_S,"getRootContainerSize",tolua_Cocos2d_CCBAnimationManager_getRootContainerSize00);
      tolua_function(tolua_S,"setDocumentControllerName",tolua_Cocos2d_CCBAnimationManager_setDocumentControllerName00);
      tolua_function(tolua_S,"getContainerSize",tolua_Cocos2d_CCBAnimationManager_getContainerSize00);
      tolua_function(tolua_S,"getDocumentOutletNames",tolua_Cocos2d_CCBAnimationManager_getDocumentOutletNames00);
      tolua_function(tolua_S,"init",tolua_Cocos2d_CCBAnimationManager_init00);
      tolua_function(tolua_S,"getKeyframeCallbacks",tolua_Cocos2d_CCBAnimationManager_getKeyframeCallbacks00);
      tolua_function(tolua_S,"runAnimationsForSequenceNamedTweenDuration",tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration00);
      tolua_function(tolua_S,"setRootContainerSize",tolua_Cocos2d_CCBAnimationManager_setRootContainerSize00);
      tolua_function(tolua_S,"runAnimationsForSequenceIdTweenDuration",tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration00);
      tolua_function(tolua_S,"getRunningSequenceName",tolua_Cocos2d_CCBAnimationManager_getRunningSequenceName00);
      tolua_function(tolua_S,"getAutoPlaySequenceId",tolua_Cocos2d_CCBAnimationManager_getAutoPlaySequenceId00);
      tolua_function(tolua_S,"addDocumentCallbackName",tolua_Cocos2d_CCBAnimationManager_addDocumentCallbackName00);
      tolua_function(tolua_S,"getRootNode",tolua_Cocos2d_CCBAnimationManager_getRootNode00);
      tolua_function(tolua_S,"addDocumentOutletNode",tolua_Cocos2d_CCBAnimationManager_addDocumentOutletNode00);
      tolua_function(tolua_S,"addDocumentCallbackNode",tolua_Cocos2d_CCBAnimationManager_addDocumentCallbackNode00);
      tolua_function(tolua_S,"runAnimationsForSequenceNamedTweenDuration",tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration01);
      tolua_function(tolua_S,"runAnimationsForSequenceNamed",tolua_Cocos2d_CCBAnimationManager_runAnimationsForSequenceNamed00);
      tolua_function(tolua_S,"getDocumentCallbackNodes",tolua_Cocos2d_CCBAnimationManager_getDocumentCallbackNodes00);
      tolua_function(tolua_S,"setSequences",tolua_Cocos2d_CCBAnimationManager_setSequences00);
      tolua_function(tolua_S,"debug",tolua_Cocos2d_CCBAnimationManager_debug00);
      tolua_function(tolua_S,"getDocumentControllerName",tolua_Cocos2d_CCBAnimationManager_getDocumentControllerName00);
      tolua_function(tolua_S, "setCallFuncForLuaCallbackNamed", tolua_Cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed00);
     tolua_endmodule(tolua_S);
     #ifdef __cplusplus
     tolua_cclass(tolua_S,"CCBProxy","CCBProxy","CCLayer",tolua_collect_CCBProxy);
     #else
     tolua_cclass(tolua_S,"CCBProxy","CCBProxy","CCLayer",NULL);
     #endif
     tolua_beginmodule(tolua_S,"CCBProxy");
      tolua_function(tolua_S,"new",tolua_Cocos2d_CCBProxy_new00);
      tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCBProxy_new00_local);
      tolua_function(tolua_S,".call",tolua_Cocos2d_CCBProxy_new00_local);
      tolua_function(tolua_S,"delete",tolua_Cocos2d_CCBProxy_delete00);
      tolua_function(tolua_S, "create", tolua_Cocos2d_CCBProxy_create00);
      tolua_function(tolua_S, "createCCBReader", tolua_Cocos2d_CCBProxy_createCCBreader00);
      tolua_function(tolua_S, "readCCBFromFile", tolua_Cocos2d_CCBProxy_readCCBFromFile00);
      tolua_function(tolua_S, "getNodeTypeName", tolua_Cocos2d_CCBProxy_getNodeTypeName00);
      tolua_function(tolua_S, "setCallback", tolua_Cocos2d_CCBProxy_setCallback00);
     tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
	return 1;
}
