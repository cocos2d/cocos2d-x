#include "lua_cocos2dx_deprecated.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define deprecatedClassTip(className) CCLOG("%s will be not binded in lua,please use the lua's table instead",className)
static int tolua_cocos2d_Dictionary_count00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'count'", NULL);
#endif
        unsigned int tolua_ret = (unsigned int)  self->count();
        tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
    }
    return 1;
    
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'count'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Dictionary_allKeys00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {        
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'allKeys'", NULL);
#endif
        {
            Array* tolua_ret = (Array*)  self->allKeys();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Array");
        }
    }
    return 1;
    
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'allKeys'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Dictionary_allKeysForObject00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {        
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        Object* object = ((Object*)  tolua_tousertype(tolua_S,2,0));
        
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'allKeysForObject'", NULL);
#endif
        {
            Array* tolua_ret = (Array*)  self->allKeysForObject(object);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Array");
        }
    }
    return 1;
    
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'allKeysForObject'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Dictionary_objectForKey00(lua_State* tolua_S)
{
    
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
        
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'objectForKey'", NULL);
#endif
        {
            Object* tolua_ret = (Object*)  self->objectForKey(key);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Object");
            tolua_pushcppstring(tolua_S,(const char*)key);
        }
    }
    return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'objectForKey'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Dictionary_objectForKey01(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        CCLOG("Dictionary will be not binded in lua,please use the lua's table instead");
        
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        int key = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'objectForKey'", NULL);
#endif
        {
            Object* tolua_ret = (Object*)  self->objectForKey(key);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Object");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Dictionary_objectForKey00(tolua_S);
}

static int tolua_cocos2d_Dictionary_valueForKey00(lua_State* tolua_S)
{
    
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'valueForKey'", NULL);
#endif
        {
            const String* tolua_ret = (const String*)  self->valueForKey(key);
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"const String");
            tolua_pushcppstring(tolua_S,(const char*)key);
        }
    }
    return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'valueForKey'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Dictionary_valueForKey01(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        int key = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'valueForKey'", NULL);
#endif
        {
            const String* tolua_ret = (const String*)  self->valueForKey(key);
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"const String");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Dictionary_valueForKey00(tolua_S);
}


static int tolua_cocos2d_Dictionary_setObject00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        Object* pObject = ((Object*)  tolua_tousertype(tolua_S,2,0));
        const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setObject'", NULL);
#endif
        {
            self->setObject(pObject,key);
            tolua_pushcppstring(tolua_S,(const char*)key);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setObject'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Dictionary_setObject01(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        Object* pObject = ((Object*)  tolua_tousertype(tolua_S,2,0));
        int key = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setObject'", NULL);
#endif
        {
            self->setObject(pObject,key);
        }
    }
    return 0;
tolua_lerror:
    return tolua_cocos2d_Dictionary_setObject00(tolua_S);
}

static int tolua_cocos2d_Dictionary_removeObjectForKey00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        const std::string key = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeObjectForKey'", NULL);
#endif
        {
            self->removeObjectForKey(key);
            tolua_pushcppstring(tolua_S,(const char*)key);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeObjectForKey'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Dictionary_removeObjectForKey01(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        int key = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeObjectForKey'", NULL);
#endif
        {
            self->removeObjectForKey(key);
        }
    }
    return 0;
tolua_lerror:
    return tolua_cocos2d_Dictionary_removeObjectForKey00(tolua_S);
}

static int tolua_cocos2d_Dictionary_removeObjectsForKeys00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Array",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
        Array* pKeyArray = ((Array*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeObjectsForKeys'", NULL);
#endif
        {
            self->removeObjectsForKeys(pKeyArray);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeObjectsForKeys'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Dictionary_removeAllObjects00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Dictionary* self = (Dictionary*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllObjects'", NULL);
#endif
        {
            self->removeAllObjects();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeAllObjects'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Dictionary_create00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Dictionary* tolua_ret = (Dictionary*)  Dictionary::create();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Dictionary");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Dictionary_createWithDictionary00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Dictionary",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Dictionary* srcDict = ((Dictionary*)  tolua_tousertype(tolua_S,2,0));
        {
            Dictionary* tolua_ret = (Dictionary*)  Dictionary::createWithDictionary(srcDict);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Dictionary");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithDictionary'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Dictionary_createWithContentsOfFile00(lua_State* tolua_S)
{
    deprecatedClassTip("Dictionary");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Dictionary",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const char* pFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
        {
            Dictionary* tolua_ret = (Dictionary*)  Dictionary::createWithContentsOfFile(pFileName);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Dictionary");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithContentsOfFile'.",&tolua_err);
    return 0;
#endif
}

static int register_cocos2dx_deprecated_Dictionary(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"CCDictionary");
    tolua_cclass(tolua_S,"CCDictionary","CCDictionary","Object",NULL);

    tolua_beginmodule(tolua_S,"CCDictionary");
      tolua_function(tolua_S,"count",tolua_cocos2d_Dictionary_count00);
      tolua_function(tolua_S,"allKeys",tolua_cocos2d_Dictionary_allKeys00);
      tolua_function(tolua_S,"allKeysForObject",tolua_cocos2d_Dictionary_allKeysForObject00);
      tolua_function(tolua_S,"objectForKey",tolua_cocos2d_Dictionary_objectForKey00);
      tolua_function(tolua_S,"objectForKey",tolua_cocos2d_Dictionary_objectForKey01);
      tolua_function(tolua_S,"valueForKey",tolua_cocos2d_Dictionary_valueForKey00);
      tolua_function(tolua_S,"valueForKey",tolua_cocos2d_Dictionary_valueForKey01);
      tolua_function(tolua_S,"setObject",tolua_cocos2d_Dictionary_setObject00);
      tolua_function(tolua_S,"setObject",tolua_cocos2d_Dictionary_setObject01);
      tolua_function(tolua_S,"removeObjectForKey",tolua_cocos2d_Dictionary_removeObjectForKey00);
      tolua_function(tolua_S,"removeObjectForKey",tolua_cocos2d_Dictionary_removeObjectForKey01);
      tolua_function(tolua_S,"removeObjectsForKeys",tolua_cocos2d_Dictionary_removeObjectsForKeys00);
      tolua_function(tolua_S,"removeAllObjects",tolua_cocos2d_Dictionary_removeAllObjects00);
      tolua_function(tolua_S,"create",tolua_cocos2d_Dictionary_create00);
      tolua_function(tolua_S,"createWithDictionary",tolua_cocos2d_Dictionary_createWithDictionary00);
      tolua_function(tolua_S,"createWithContentsOfFile",tolua_cocos2d_Dictionary_createWithContentsOfFile00);
    tolua_endmodule(tolua_S);
 
    //UNDO array_to_luaval has 
    //uint32_t typeId = cocos2d::getHashCodeByString(typeid(CCBProxy).name());
    //g_luaType[typeId] = "CCBProxy";
    return 1;
}


static int tolua_get_Point_x(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    Point* self = (Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->x);
    return 1;
}

static int tolua_set_Point_x(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    Point* self = (Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->x = ((float)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}

static int tolua_get_Point_y(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    Point* self = (Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->y);
    return 1;
}


static int tolua_set_Point_y(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    Point* self = (Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->y = ((float)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}


static int tolua_cocos2d_Point_new00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Point* tolua_ret = (Point*)  Mtolua_new((Point)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"Point");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Point* tolua_ret = (Point*)  Mtolua_new((Point)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"Point");
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


static int tolua_cocos2d_Point_new01(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        {
            Point* tolua_ret = (Point*)  Mtolua_new((Point)(x,y));
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"Point");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Point_new00(tolua_S);
}


static int tolua_cocos2d_Point_new01_local(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        {
            Point* tolua_ret = (Point*)  Mtolua_new((Point)(x,y));
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"Point");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Point_new00_local(tolua_S);
}


static int tolua_cocos2d_Point_new02(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        const Size* size = ((const Size*)  tolua_tousertype(tolua_S,2,0));
        {
            Point* tolua_ret = (Point*)  Mtolua_new((Point)(*size));
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"Point");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Point_new01(tolua_S);
}


static int tolua_cocos2d_Point_new02_local(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        const Size* size = ((const Size*)  tolua_tousertype(tolua_S,2,0));
        {
            Point* tolua_ret = (Point*)  Mtolua_new((Point)(*size));
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"Point");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Point_new01_local(tolua_S);
}


static int tolua_cocos2d_Point__sub00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* right = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->operator-(*right);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point__add00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* right = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->operator+(*right);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point__mul00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        float a = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->operator*(a);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getMidpoint00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* other = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMidpoint'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->getMidpoint(*other);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getMidpoint'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_dot00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* other = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dot'", NULL);
#endif
        {
            float tolua_ret = (float)  self->dot(*other);
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'dot'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_cross00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* other = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cross'", NULL);
#endif
        {
            float tolua_ret = (float)  self->cross(*other);
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'cross'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getPerp00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPerp'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->getPerp();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getPerp'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getRPerp00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRPerp'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->getRPerp();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getRPerp'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_project00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* other = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'project'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->project(*other);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'project'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_rotate00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* other = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->rotate(*other);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'rotate'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_unrotate00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* other = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unrotate'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->unrotate(*other);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unrotate'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getLengthSq00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLengthSq'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getLengthSq();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getLengthSq'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getLength00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLength'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getLength();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getLength'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getDistance00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* other = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDistance'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getDistance(*other);
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getDistance'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_normalize00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'normalize'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->normalize();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'normalize'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getAngle00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngle'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getAngle();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getAngle'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getClampPoint00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* min_inclusive = ((const Point*)  tolua_tousertype(tolua_S,2,0));
        const Point* max_inclusive = ((const Point*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClampPoint'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->getClampPoint(*min_inclusive,*max_inclusive);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getClampPoint'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_lerp00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* other = ((const Point*)  tolua_tousertype(tolua_S,2,0));
        float alpha = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lerp'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->lerp(*other,alpha);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lerp'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_fuzzyEquals00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* target = ((const Point*)  tolua_tousertype(tolua_S,2,0));
        float variance = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fuzzyEquals'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->fuzzyEquals(*target,variance);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'fuzzyEquals'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_rotateByAngle00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* pivot = ((const Point*)  tolua_tousertype(tolua_S,2,0));
        float angle = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotateByAngle'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->rotateByAngle(*pivot,angle);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'rotateByAngle'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_equals00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* self = (const Point*)  tolua_tousertype(tolua_S,1,0);
        const Point* target = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'equals'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->equals(*target);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'equals'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_isLineIntersect00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Point",0,&tolua_err)) ||
        !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,8,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* A = ((const Point*)  tolua_tousertype(tolua_S,2,0));
        const Point* B = ((const Point*)  tolua_tousertype(tolua_S,3,0));
        const Point* C = ((const Point*)  tolua_tousertype(tolua_S,4,0));
        const Point* D = ((const Point*)  tolua_tousertype(tolua_S,5,0));
        float S = ((float)  tolua_tonumber(tolua_S,6,0));
        float T = ((float)  tolua_tonumber(tolua_S,7,0));
        {
            bool tolua_ret = (bool)  Point::isLineIntersect(*A,*B,*C,*D,&S,&T);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
            tolua_pushnumber(tolua_S,(lua_Number)S);
            tolua_pushnumber(tolua_S,(lua_Number)T);
        }
    }
    return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isLineIntersect'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_isSegmentIntersect00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* A = ((const Point*)  tolua_tousertype(tolua_S,2,0));
        const Point* B = ((const Point*)  tolua_tousertype(tolua_S,3,0));
        const Point* C = ((const Point*)  tolua_tousertype(tolua_S,4,0));
        const Point* D = ((const Point*)  tolua_tousertype(tolua_S,5,0));
        {
            bool tolua_ret = (bool)  Point::isSegmentIntersect(*A,*B,*C,*D);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isSegmentIntersect'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_getIntersectPoint00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Point",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Point* A = ((const Point*)  tolua_tousertype(tolua_S,2,0));
        const Point* B = ((const Point*)  tolua_tousertype(tolua_S,3,0));
        const Point* C = ((const Point*)  tolua_tousertype(tolua_S,4,0));
        const Point* D = ((const Point*)  tolua_tousertype(tolua_S,5,0));
        {
            Point tolua_ret = (Point)  Point::getIntersectPoint(*A,*B,*C,*D);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getIntersectPoint'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Point_forAngle00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Point",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const float a = ((const float)  tolua_tonumber(tolua_S,2,0));
        {
            Point tolua_ret = (Point)  Point::forAngle(a);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"Point");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'forAngle'.",&tolua_err);
    return 0;
#endif
}

static int tolua_collect_Point (lua_State* tolua_S)
{
    Point* self = (Point*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int register_cocos2dx_deprecated_Point(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"CCPoint");
#ifdef __cplusplus
    tolua_cclass(tolua_S,"CCPoint","CCPoint","",tolua_collect_Point);
#else
    tolua_cclass(tolua_S,"CCPoint","CCPoint","",NULL);
#endif
    tolua_beginmodule(tolua_S,"CCPoint");
        tolua_variable(tolua_S,"x",tolua_get_Point_x,tolua_set_Point_x);
        tolua_variable(tolua_S,"y",tolua_get_Point_y,tolua_set_Point_y);
        tolua_function(tolua_S,"new",tolua_cocos2d_Point_new00);
        tolua_function(tolua_S,"new_local",tolua_cocos2d_Point_new00_local);
        tolua_function(tolua_S,".call",tolua_cocos2d_Point_new00_local);
        tolua_function(tolua_S,"new",tolua_cocos2d_Point_new01);
        tolua_function(tolua_S,"new_local",tolua_cocos2d_Point_new01_local);
        tolua_function(tolua_S,".call",tolua_cocos2d_Point_new01_local);
        tolua_function(tolua_S,"new",tolua_cocos2d_Point_new02);
        tolua_function(tolua_S,"new_local",tolua_cocos2d_Point_new02_local);
        tolua_function(tolua_S,".call",tolua_cocos2d_Point_new02_local);
        tolua_function(tolua_S,".sub",tolua_cocos2d_Point__sub00);
        tolua_function(tolua_S,".add",tolua_cocos2d_Point__add00);
        tolua_function(tolua_S,".mul",tolua_cocos2d_Point__mul00);
        tolua_function(tolua_S,"getMidpoint",tolua_cocos2d_Point_getMidpoint00);
        tolua_function(tolua_S,"dot",tolua_cocos2d_Point_dot00);
        tolua_function(tolua_S,"cross",tolua_cocos2d_Point_cross00);
        tolua_function(tolua_S,"getPerp",tolua_cocos2d_Point_getPerp00);
        tolua_function(tolua_S,"getRPerp",tolua_cocos2d_Point_getRPerp00);
        tolua_function(tolua_S,"project",tolua_cocos2d_Point_project00);
        tolua_function(tolua_S,"rotate",tolua_cocos2d_Point_rotate00);
        tolua_function(tolua_S,"unrotate",tolua_cocos2d_Point_unrotate00);
        tolua_function(tolua_S,"getLengthSq",tolua_cocos2d_Point_getLengthSq00);
        tolua_function(tolua_S,"getLength",tolua_cocos2d_Point_getLength00);
        tolua_function(tolua_S,"getDistance",tolua_cocos2d_Point_getDistance00);
        tolua_function(tolua_S,"normalize",tolua_cocos2d_Point_normalize00);
        tolua_function(tolua_S,"getAngle",tolua_cocos2d_Point_getAngle00);
        tolua_function(tolua_S,"getClampPoint",tolua_cocos2d_Point_getClampPoint00);
        tolua_function(tolua_S,"lerp",tolua_cocos2d_Point_lerp00);
        tolua_function(tolua_S,"fuzzyEquals",tolua_cocos2d_Point_fuzzyEquals00);
        tolua_function(tolua_S,"rotateByAngle",tolua_cocos2d_Point_rotateByAngle00);
        tolua_function(tolua_S,"equals",tolua_cocos2d_Point_equals00);
        tolua_function(tolua_S,"isLineIntersect",tolua_cocos2d_Point_isLineIntersect00);
        tolua_function(tolua_S,"isSegmentIntersect",tolua_cocos2d_Point_isSegmentIntersect00);
        tolua_function(tolua_S,"getIntersectPoint",tolua_cocos2d_Point_getIntersectPoint00);
        tolua_function(tolua_S,"forAngle",tolua_cocos2d_Point_forAngle00);
    tolua_endmodule(tolua_S);
    
    return 1;
}

static int tolua_get_CCRect_origin(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
    Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'origin'",NULL);
#endif
    tolua_pushusertype(tolua_S,(void*)&self->origin,"CCPoint");
    return 1;
}


static int tolua_set_CCRect_origin(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
    Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'origin'",NULL);
    if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->origin = *((Point*)  tolua_tousertype(tolua_S,2,0))
    ;
    return 0;
}

static int tolua_get_CCRect_size(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
    Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
#endif
    tolua_pushusertype(tolua_S,(void*)&self->size,"CCSize");
    return 1;
}

static int tolua_set_CCRect_size(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
    Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
    if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->size = *((Size*)  tolua_tousertype(tolua_S,2,0))
    ;
    return 0;
}

static int tolua_Cocos2d_CCRect_new00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Rect* tolua_ret = (Rect*)  Mtolua_new((Rect)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRect");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCRect_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Rect* tolua_ret = (Rect*)  Mtolua_new((Rect)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRect");
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

static int tolua_Cocos2d_CCRect_new01(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        float width = ((float)  tolua_tonumber(tolua_S,4,0));
        float height = ((float)  tolua_tonumber(tolua_S,5,0));
        {
            Rect* tolua_ret = (Rect*)  Mtolua_new((Rect)(x,y,width,height));
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRect");
        }
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCRect_new00(tolua_S);
}


static int tolua_Cocos2d_CCRect_new01_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        float width = ((float)  tolua_tonumber(tolua_S,4,0));
        float height = ((float)  tolua_tonumber(tolua_S,5,0));
        {
            Rect* tolua_ret = (Rect*)  Mtolua_new((Rect)(x,y,width,height));
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRect");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCRect_new00_local(tolua_S);
}


static int tolua_Cocos2d_CCRect_getMinX00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMinX'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getMinX();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getMinX'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCRect_getMidX00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMidX'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getMidX();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getMidX'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCRect_getMaxX00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxX'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getMaxX();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getMaxX'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCRect_getMinY00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMinY'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getMinY();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getMinY'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCRect_getMidY00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMidY'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getMidY();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getMidY'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCRect_getMaxY00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Rect* self = (Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxY'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getMaxY();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getMaxY'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCRect_equals00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCRect",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Rect* self = (const Rect*)  tolua_tousertype(tolua_S,1,0);
        const Rect* rect = ((const Rect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'equals'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->equals(*rect);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'equals'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCRect_containsPoint00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCRect",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Rect* self = (const Rect*)  tolua_tousertype(tolua_S,1,0);
        const Point* point = ((const Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containsPoint'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->containsPoint(*point);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'containsPoint'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCRect_intersectsRect00(lua_State* tolua_S)
{
    deprecatedClassTip("CCRect");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCRect",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Rect* self = (const Rect*)  tolua_tousertype(tolua_S,1,0);
        const Rect* rect = ((const Rect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersectsRect'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->intersectsRect(*rect);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'intersectsRect'.",&tolua_err);
    return 0;
#endif
}

static int tolua_collect_CCRect (lua_State* tolua_S)
{
    Rect* self = (Rect*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}


static int register_cocos2dx_deprecated_Rect(lua_State* tolua_S)
{
    
    tolua_usertype(tolua_S,"CCRect");
#ifdef __cplusplus
    tolua_cclass(tolua_S,"CCRect","CCRect","",tolua_collect_CCRect);
#else
    tolua_cclass(tolua_S,"CCRect","CCRect","",NULL);
#endif
    tolua_beginmodule(tolua_S,"CCRect");
        tolua_variable(tolua_S,"origin",tolua_get_CCRect_origin,tolua_set_CCRect_origin);
        tolua_variable(tolua_S,"size",tolua_get_CCRect_size,tolua_set_CCRect_size);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCRect_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCRect_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCRect_new00_local);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCRect_new01);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCRect_new01_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCRect_new01_local);
        tolua_function(tolua_S,"getMinX",tolua_Cocos2d_CCRect_getMinX00);
        tolua_function(tolua_S,"getMidX",tolua_Cocos2d_CCRect_getMidX00);
        tolua_function(tolua_S,"getMaxX",tolua_Cocos2d_CCRect_getMaxX00);
        tolua_function(tolua_S,"getMinY",tolua_Cocos2d_CCRect_getMinY00);
        tolua_function(tolua_S,"getMidY",tolua_Cocos2d_CCRect_getMidY00);
        tolua_function(tolua_S,"getMaxY",tolua_Cocos2d_CCRect_getMaxY00);
        tolua_function(tolua_S,"equals",tolua_Cocos2d_CCRect_equals00);
        tolua_function(tolua_S,"containsPoint",tolua_Cocos2d_CCRect_containsPoint00);
        tolua_function(tolua_S,"intersectsRect",tolua_Cocos2d_CCRect_intersectsRect00);
    tolua_endmodule(tolua_S);
    
    return 1;
}


static int tolua_get_CCSize_width(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
    Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->width);
    return 1;
}


static int tolua_set_CCSize_width(lua_State* tolua_S)
{
    Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->width = ((float)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}

static int tolua_get_CCSize_height(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
    Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->height);
    return 1;
}


static int tolua_set_CCSize_height(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
    Size* self = (Size*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->height = ((float)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}


static int tolua_Cocos2d_CCSize_new00(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Size* tolua_ret = (Size*)  Mtolua_new((Size)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSize");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCSize_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Size* tolua_ret = (Size*)  Mtolua_new((Size)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSize");
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


static int tolua_Cocos2d_CCSize_new01(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float width = ((float)  tolua_tonumber(tolua_S,2,0));
        float height = ((float)  tolua_tonumber(tolua_S,3,0));
        {
            Size* tolua_ret = (Size*)  Mtolua_new((Size)(width,height));
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSize");
        }
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCSize_new00(tolua_S);
}



static int tolua_Cocos2d_CCSize_new01_local(lua_State* tolua_S)
{
    
    deprecatedClassTip("CCSize");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float width = ((float)  tolua_tonumber(tolua_S,2,0));
        float height = ((float)  tolua_tonumber(tolua_S,3,0));
        {
            Size* tolua_ret = (Size*)  Mtolua_new((Size)(width,height));
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSize");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCSize_new00_local(tolua_S);
}


static int tolua_Cocos2d_CCSize_equals00(lua_State* tolua_S)
{
    deprecatedClassTip("CCSize");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCSize",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const Size* self = (const Size*)  tolua_tousertype(tolua_S,1,0);
        const Size* target = ((const Size*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'equals'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->equals(*target);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'equals'.",&tolua_err);
    return 0;
#endif
}

static int tolua_collect_CCSize (lua_State* tolua_S)
{
    Size* self = (Size*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int register_cocos2dx_deprecated_Size(lua_State* tolua_S)
{
    
    tolua_usertype(tolua_S,"CCSize");
    
#ifdef __cplusplus
    tolua_cclass(tolua_S,"CCSize","CCSize","",tolua_collect_CCSize);
#else
    tolua_cclass(tolua_S,"CCSize","CCSize","",NULL);
#endif
    tolua_beginmodule(tolua_S,"CCSize");
        tolua_variable(tolua_S,"width",tolua_get_CCSize_width,tolua_set_CCSize_width);
        tolua_variable(tolua_S,"height",tolua_get_CCSize_height,tolua_set_CCSize_height);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCSize_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCSize_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCSize_new00_local);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCSize_new01);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCSize_new01_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCSize_new01_local);
        tolua_function(tolua_S,"equals",tolua_Cocos2d_CCSize_equals00);
    tolua_endmodule(tolua_S);
    
    return 1;
}


static int tolua_Cocos2d_CCArray_create00(lua_State* tolua_S)
{
    
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Array* tolua_ret = (Array*)  Array::create();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_createWithObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Object* pObject = ((Object*)  tolua_tousertype(tolua_S,2,0));
        {
            Array* tolua_ret = (Array*)  Array::createWithObject(pObject);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithObject'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_createWithArray00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* otherArray = ((Array*)  tolua_tousertype(tolua_S,2,0));
        {
            Array* tolua_ret = (Array*)  Array::createWithArray(otherArray);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithArray'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_createWithCapacity00(lua_State* tolua_S)
{
    
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int capacity = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        {
            Array* tolua_ret = (Array*)  Array::createWithCapacity(capacity);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithCapacity'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_createWithContentsOfFile00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const char* pFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
        {
            Array* tolua_ret = (Array*)  Array::createWithContentsOfFile(pFileName);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithContentsOfFile'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_count00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'count'", NULL);
#endif
        {
            unsigned int tolua_ret = (unsigned int)  self->count();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'count'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_capacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'capacity'", NULL);
#endif
        {
            unsigned int tolua_ret = (unsigned int)  self->capacity();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'capacity'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_indexOfObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Object* object = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'indexOfObject'", NULL);
#endif
        {
            unsigned int tolua_ret = (unsigned int)  self->indexOfObject(object);
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'indexOfObject'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_objectAtIndex00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'objectAtIndex'", NULL);
#endif
        {
            Object* tolua_ret = (Object*)  self->objectAtIndex(index);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Object");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'objectAtIndex'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_lastObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lastObject'", NULL);
#endif
        {
            Object* tolua_ret = (Object*)  self->lastObject();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Object");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lastObject'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_randomObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'randomObject'", NULL);
#endif
        {
            Object* tolua_ret = (Object*)  self->randomObject();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Object");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'randomObject'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_isEqualToArray00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Array* pOtherArray = ((Array*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEqualToArray'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->isEqualToArray(pOtherArray);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isEqualToArray'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_containsObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Object* object = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containsObject'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->containsObject(object);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'containsObject'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_addObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Object* object = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addObject'", NULL);
#endif
        {
            self->addObject(object);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addObject'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCArray_addObjectsFromArray00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Array* otherArray = ((Array*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addObjectsFromArray'", NULL);
#endif
        {
            self->addObjectsFromArray(otherArray);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addObjectsFromArray'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_insertObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Object* object = ((Object*)  tolua_tousertype(tolua_S,2,0));
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertObject'", NULL);
#endif
        {
            self->insertObject(object,index);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'insertObject'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCArray_removeLastObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        bool bReleaseObj = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeLastObject'", NULL);
#endif
        {
            self->removeLastObject(bReleaseObj);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeLastObject'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_removeObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Object* object = ((Object*)  tolua_tousertype(tolua_S,2,0));
        bool bReleaseObj = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeObject'", NULL);
#endif
        {
            self->removeObject(object,bReleaseObj);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeObject'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_removeObjectAtIndex00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        bool bReleaseObj = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeObjectAtIndex'", NULL);
#endif
        {
            self->removeObjectAtIndex(index,bReleaseObj);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeObjectAtIndex'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCArray_removeObjectsInArray00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Array* otherArray = ((Array*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeObjectsInArray'", NULL);
#endif
        {
            self->removeObjectsInArray(otherArray);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeObjectsInArray'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCArray_removeAllObjects00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllObjects'", NULL);
#endif
        {
            self->removeAllObjects();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeAllObjects'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCArray_fastRemoveObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Object* object = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fastRemoveObject'", NULL);
#endif
        {
            self->fastRemoveObject(object);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'fastRemoveObject'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCArray_fastRemoveObjectAtIndex00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fastRemoveObjectAtIndex'", NULL);
#endif
        {
            self->fastRemoveObjectAtIndex(index);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'fastRemoveObjectAtIndex'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_exchangeObject00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"Object",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        Object* object1 = ((Object*)  tolua_tousertype(tolua_S,2,0));
        Object* object2 = ((Object*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'exchangeObject'", NULL);
#endif
        {
            self->exchangeObject(object1,object2);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'exchangeObject'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCArray_exchangeObjectAtIndex00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        unsigned int index1 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        unsigned int index2 = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'exchangeObjectAtIndex'", NULL);
#endif
        {
            self->exchangeObjectAtIndex(index1,index2);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'exchangeObjectAtIndex'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_reverseObjects00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reverseObjects'", NULL);
#endif
        {
            self->reverseObjects();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'reverseObjects'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_reduceMemoryFootprint00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reduceMemoryFootprint'", NULL);
#endif
        {
            self->reduceMemoryFootprint();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'reduceMemoryFootprint'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCArray_replaceObjectAtIndex00(lua_State* tolua_S)
{
    deprecatedClassTip("CCArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"Object",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* self = (Array*)  tolua_tousertype(tolua_S,1,0);
        unsigned int uIndex = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        Object* pObject = ((Object*)  tolua_tousertype(tolua_S,3,0));
        bool bReleaseObject = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'replaceObjectAtIndex'", NULL);
#endif
        {
            self->replaceObjectAtIndex(uIndex,pObject,bReleaseObject);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'replaceObjectAtIndex'.",&tolua_err);
    return 0;
#endif
}

static int register_cocos2dx_deprecated_Array(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "CCArray");
    
    tolua_cclass(tolua_S,"CCArray","CCArray","CCObject",NULL);
    tolua_beginmodule(tolua_S,"CCArray");
        tolua_function(tolua_S,"create",tolua_Cocos2d_CCArray_create00);
        tolua_function(tolua_S,"createWithObject",tolua_Cocos2d_CCArray_createWithObject00);
        tolua_function(tolua_S,"createWithArray",tolua_Cocos2d_CCArray_createWithArray00);
        tolua_function(tolua_S,"createWithCapacity",tolua_Cocos2d_CCArray_createWithCapacity00);
        tolua_function(tolua_S,"createWithContentsOfFile",tolua_Cocos2d_CCArray_createWithContentsOfFile00);
        tolua_function(tolua_S,"count",tolua_Cocos2d_CCArray_count00);
        tolua_function(tolua_S,"capacity",tolua_Cocos2d_CCArray_capacity00);
        tolua_function(tolua_S,"indexOfObject",tolua_Cocos2d_CCArray_indexOfObject00);
        tolua_function(tolua_S,"objectAtIndex",tolua_Cocos2d_CCArray_objectAtIndex00);
        tolua_function(tolua_S,"lastObject",tolua_Cocos2d_CCArray_lastObject00);
        tolua_function(tolua_S,"randomObject",tolua_Cocos2d_CCArray_randomObject00);
        tolua_function(tolua_S,"isEqualToArray",tolua_Cocos2d_CCArray_isEqualToArray00);
        tolua_function(tolua_S,"containsObject",tolua_Cocos2d_CCArray_containsObject00);
        tolua_function(tolua_S,"addObject",tolua_Cocos2d_CCArray_addObject00);
        tolua_function(tolua_S,"addObjectsFromArray",tolua_Cocos2d_CCArray_addObjectsFromArray00);
        tolua_function(tolua_S,"insertObject",tolua_Cocos2d_CCArray_insertObject00);
        tolua_function(tolua_S,"removeLastObject",tolua_Cocos2d_CCArray_removeLastObject00);
        tolua_function(tolua_S,"removeObject",tolua_Cocos2d_CCArray_removeObject00);
        tolua_function(tolua_S,"removeObjectAtIndex",tolua_Cocos2d_CCArray_removeObjectAtIndex00);
        tolua_function(tolua_S,"removeObjectsInArray",tolua_Cocos2d_CCArray_removeObjectsInArray00);
        tolua_function(tolua_S,"removeAllObjects",tolua_Cocos2d_CCArray_removeAllObjects00);
        tolua_function(tolua_S,"fastRemoveObject",tolua_Cocos2d_CCArray_fastRemoveObject00);
        tolua_function(tolua_S,"fastRemoveObjectAtIndex",tolua_Cocos2d_CCArray_fastRemoveObjectAtIndex00);
        tolua_function(tolua_S,"exchangeObject",tolua_Cocos2d_CCArray_exchangeObject00);
        tolua_function(tolua_S,"exchangeObjectAtIndex",tolua_Cocos2d_CCArray_exchangeObjectAtIndex00);
        tolua_function(tolua_S,"reverseObjects",tolua_Cocos2d_CCArray_reverseObjects00);
        tolua_function(tolua_S,"reduceMemoryFootprint",tolua_Cocos2d_CCArray_reduceMemoryFootprint00);
        tolua_function(tolua_S,"replaceObjectAtIndex",tolua_Cocos2d_CCArray_replaceObjectAtIndex00);
    tolua_endmodule(tolua_S);
    
    return 1;
}


int register_all_cocos2dx_deprecated(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
    register_cocos2dx_deprecated_Dictionary(tolua_S);
    register_cocos2dx_deprecated_Point(tolua_S);
    register_cocos2dx_deprecated_Rect(tolua_S);
    register_cocos2dx_deprecated_Size(tolua_S);
    register_cocos2dx_deprecated_Array(tolua_S);
    tolua_endmodule(tolua_S);
    
    return 0;
}

extern int lua_cocos2dx_Node_setPosition(lua_State* tolua_S);

static int tolua_cocos2dx_Node_setPosition_deprecated(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Point",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
        Point pos = *((Point*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
        {
            self->setPosition(pos);
        }
    }
    return 0;
tolua_lerror:
    return lua_cocos2dx_Node_setPosition(tolua_S);
}

static void extendNodeDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Node");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setPosition");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Node_setPosition_deprecated);
        lua_rawset(tolua_S,-3);
    }
}


extern int lua_cocos2dx_SpriteFrame_createWithTexture(lua_State* tolua_S);

static int tolua_cocos2d_SpriteFrame_createWithTexture_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"SpriteFrame",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Texture2D",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
        !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCPoint",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,7,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Texture2D* pobTexture = ((Texture2D*)  tolua_tousertype(tolua_S,2,0));
        Rect rect = *((Rect*)  tolua_tousertype(tolua_S,3,0));
        bool rotated = ((bool)  tolua_toboolean(tolua_S,4,0));
        Point offset = *((Point*)  tolua_tousertype(tolua_S,5,0));
        Size originalSize = *((Size*)  tolua_tousertype(tolua_S,6,0));
        {
            SpriteFrame* tolua_ret = (SpriteFrame*)  SpriteFrame::createWithTexture(pobTexture,rect,rotated,offset,originalSize);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"SpriteFrame");
        }
    }
    return 1;

tolua_lerror:
    return lua_cocos2dx_SpriteFrame_createWithTexture(tolua_S);

}


static int tolua_cocos2d_SpriteFrame_createWithTexture_deprecated01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"SpriteFrame",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"Texture2D",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Texture2D* pobTexture = ((Texture2D*)  tolua_tousertype(tolua_S,2,0));
        Rect rect = *((Rect*)  tolua_tousertype(tolua_S,3,0));
        {
            SpriteFrame* tolua_ret = (SpriteFrame*)  SpriteFrame::createWithTexture(pobTexture,rect);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"SpriteFrame");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_SpriteFrame_createWithTexture_deprecated00(tolua_S);
}

extern int lua_cocos2dx_SpriteFrame_create(lua_State* tolua_S);

static int tolua_Cocos2d_SpriteFrame_create00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"SpriteFrame",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
        !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCPoint",0,&tolua_err)) ||
        (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,7,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
        Rect rect = *((Rect*)  tolua_tousertype(tolua_S,3,0));
        bool rotated = ((bool)  tolua_toboolean(tolua_S,4,0));
        Point offset = *((Point*)  tolua_tousertype(tolua_S,5,0));
        Size originalSize = *((Size*)  tolua_tousertype(tolua_S,6,0));
        {
            SpriteFrame* tolua_ret = (SpriteFrame*)  SpriteFrame::create(filename,rect,rotated,offset,originalSize);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"SpriteFrame");
        }
    }
    return 1;
tolua_lerror:
    return lua_cocos2dx_SpriteFrame_create(tolua_S);
}


static int tolua_Cocos2d_SpriteFrame_create01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"SpriteFrame",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
        Rect rect = *((Rect*)  tolua_tousertype(tolua_S,3,0));
        {
            SpriteFrame* tolua_ret = (SpriteFrame*)  SpriteFrame::create(filename,rect);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"SpriteFrame");
        }
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_SpriteFrame_create00(tolua_S);
}


static void extendSpriteFrameDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"SpriteFrame");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"createWithTexture");
        lua_pushcfunction(tolua_S,tolua_cocos2d_SpriteFrame_createWithTexture_deprecated00);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"createWithTexture");
        lua_pushcfunction(tolua_S,tolua_cocos2d_SpriteFrame_createWithTexture_deprecated01);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_Cocos2d_SpriteFrame_create00);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_Cocos2d_SpriteFrame_create01);
        lua_rawset(tolua_S,-3);
    }
}

extern int lua_cocos2dx_Animation_createWithSpriteFrames(lua_State* tolua_S);

static int tolua_cocos2d_Animation_createWithSpriteFrames_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Array* arrayOfSpriteFrameNames = ((Array*)  tolua_tousertype(tolua_S,2,0));
        float delay = ((float)  tolua_tonumber(tolua_S,3,0));
        {
            cocos2d::Animation* tolua_ret = (cocos2d::Animation*)  cocos2d::Animation::createWithSpriteFrames(arrayOfSpriteFrameNames,delay);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Animation");
        }
    }
    return 1;
tolua_lerror:
    return lua_cocos2dx_Animation_createWithSpriteFrames(tolua_S);
}


static int tolua_cocos2d_Animation_createWithSpriteFrames_deprecated01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Array* arrayOfSpriteFrameNames = ((Array*)  tolua_tousertype(tolua_S,2,0));
        {
            cocos2d::Animation* tolua_ret = (cocos2d::Animation*)  cocos2d::Animation::createWithSpriteFrames(arrayOfSpriteFrameNames);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Animation");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Animation_createWithSpriteFrames_deprecated00(tolua_S);
}

static void extendAnimationDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Animation");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"createWithSpriteFrames");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Animation_createWithSpriteFrames_deprecated00);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"createWithSpriteFrames");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Animation_createWithSpriteFrames_deprecated01);
        lua_rawset(tolua_S,-3);
    }
}


int register_all_cocos2dx_manual_deprecated(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    extendNodeDeprecated(tolua_S);
    extendSpriteFrameDeprecated(tolua_S);
    extendAnimationDeprecated(tolua_S);
    return 0;
}
