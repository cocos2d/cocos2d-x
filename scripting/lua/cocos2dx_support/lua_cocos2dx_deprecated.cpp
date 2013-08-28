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
#define deprecatedFunctionTip(oldFun,newFun) CCLOG("%s was deprecated please use %s instead ",oldFun, newFun)
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
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Point  tolua_ret;
        point_to_luaval(tolua_S, tolua_ret);
        return 1;
    }

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
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Point  tolua_ret;
        point_to_luaval(tolua_S, tolua_ret);
        return 1;
    }
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
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        Point  tolua_ret = Point(x,y);
        point_to_luaval(tolua_S, tolua_ret);
        return 1;
    }
tolua_lerror:
    return tolua_cocos2d_Point_new00(tolua_S);
}


static int tolua_cocos2d_Point_new01_local(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        Point  tolua_ret = Point(x,y);
        point_to_luaval(tolua_S, tolua_ret);
        return 1;
    }
tolua_lerror:
    return tolua_cocos2d_Point_new00_local(tolua_S);
}


static int tolua_cocos2d_Point_new02(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_istable(tolua_S, 2, 0, &tolua_err)||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Size size;
        luaval_to_size(tolua_S, 2, &size);
        Point  tolua_ret = Point(size);
        point_to_luaval(tolua_S, tolua_ret);
        return 1;
    }

tolua_lerror:
    return tolua_cocos2d_Point_new01(tolua_S);
}


static int tolua_cocos2d_Point_new02_local(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
        !tolua_istable(tolua_S, 2, 0, &tolua_err)||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Size size;
        luaval_to_size(tolua_S, 2, &size);
        Point  tolua_ret = Point(size);
        point_to_luaval(tolua_S, tolua_ret);
        return 1;
    }
tolua_lerror:
    return tolua_cocos2d_Point_new01_local(tolua_S);
}


static int tolua_cocos2d_Point__sub00(lua_State* tolua_S)
{
    deprecatedClassTip("Point");

#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_istable(tolua_S, 1, 0, &tolua_err)||
        !tolua_istable(tolua_S, 2, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Point self;
        luaval_to_point(tolua_S, 1, &self);
        Point right;
        luaval_to_point(tolua_S, 2, &right);
        Point tolua_ret = (Point)  self.operator-(right);
        point_to_luaval(tolua_S, tolua_ret);
        return 1;
    }

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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
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
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
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
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
        !tolua_isusertable(tolua_S,1,"CCPoint",0,&tolua_err) ||
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
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
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
            unsigned int tolua_ret = (unsigned int)  self->getIndexOfObject(object);
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
            Object* tolua_ret = (Object*)  self->getObjectAtIndex(index);
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
            Object* tolua_ret = (Object*)  self->getLastObject();
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
            Object* tolua_ret = (Object*)  self->getRandomObject();
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


static int tolua_Cocos2d_CCPointArray_initWithCapacity00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
        unsigned int capacity = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithCapacity'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->initWithCapacity(capacity);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'initWithCapacity'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_CCPointArray_addControlPoint00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if ( !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
        
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addControlPoint'", NULL);
#endif
        Point controlPoint;
        if (luaval_to_point(tolua_S, 2, &controlPoint))
        {
            self->addControlPoint(controlPoint);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addControlPoint'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_insertControlPoint00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
        Point* controlPoint = ((Point*)  tolua_tousertype(tolua_S,2,0));
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertControlPoint'", NULL);
#endif
        {
            self->insertControlPoint(*controlPoint,index);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'insertControlPoint'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_replaceControlPoint00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
        Point* controlPoint = ((Point*)  tolua_tousertype(tolua_S,2,0));
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'replaceControlPoint'", NULL);
#endif
        {
            self->replaceControlPoint(*controlPoint,index);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'replaceControlPoint'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_getControlPointAtIndex00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getControlPointAtIndex'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->getControlPointAtIndex(index);
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getControlPointAtIndex'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_removeControlPointAtIndex00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeControlPointAtIndex'", NULL);
#endif
        {
            self->removeControlPointAtIndex(index);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'removeControlPointAtIndex'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_count00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
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


static int tolua_Cocos2d_CCPointArray_reverse00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reverse'", NULL);
#endif
        {
            PointArray* tolua_ret = (PointArray*)  self->reverse();
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCPointArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'reverse'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_reverseInline00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reverseInline'", NULL);
#endif
        {
            self->reverseInline();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'reverseInline'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_getControlPoints00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getControlPoints'", NULL);
#endif
        {
            const std::vector<Point*>* tolua_ret = (const std::vector<Point*>*)  self->getControlPoints();
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"const std::vector<Point*>");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getControlPoints'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_setControlPoints00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"std::vector<Point*>",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        PointArray* self = (PointArray*)  tolua_tousertype(tolua_S,1,0);
        std::vector<Point*>* controlPoints = ((std::vector<Point*>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setControlPoints'", NULL);
#endif
        {
            self->setControlPoints(controlPoints);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setControlPoints'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPointArray_create00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPointArray");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int capacity = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        {
            PointArray* tolua_ret = (PointArray*)  PointArray::create(capacity);
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCPointArray");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int register_cocos2dx_deprecated_PointArray(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "CCPointArray");
    tolua_cclass(tolua_S,"CCPointArray","CCPointArray","CCNode",NULL);
    
    tolua_beginmodule(tolua_S,"CCPointArray");
        tolua_function(tolua_S,"initWithCapacity",tolua_Cocos2d_CCPointArray_initWithCapacity00);
        tolua_function(tolua_S,"addControlPoint",tolua_Cocos2d_CCPointArray_addControlPoint00);
        tolua_function(tolua_S,"insertControlPoint",tolua_Cocos2d_CCPointArray_insertControlPoint00);
        tolua_function(tolua_S,"replaceControlPoint",tolua_Cocos2d_CCPointArray_replaceControlPoint00);
        tolua_function(tolua_S,"getControlPointAtIndex",tolua_Cocos2d_CCPointArray_getControlPointAtIndex00);
        tolua_function(tolua_S,"removeControlPointAtIndex",tolua_Cocos2d_CCPointArray_removeControlPointAtIndex00);
        tolua_function(tolua_S,"count",tolua_Cocos2d_CCPointArray_count00);
        tolua_function(tolua_S,"reverse",tolua_Cocos2d_CCPointArray_reverse00);
        tolua_function(tolua_S,"reverseInline",tolua_Cocos2d_CCPointArray_reverseInline00);
        tolua_function(tolua_S,"getControlPoints",tolua_Cocos2d_CCPointArray_getControlPoints00);
        tolua_function(tolua_S,"setControlPoints",tolua_Cocos2d_CCPointArray_setControlPoints00);
        tolua_function(tolua_S,"create",tolua_Cocos2d_CCPointArray_create00);
    tolua_endmodule(tolua_S);
    return 1;
}


static int tolua_Cocos2d_ccBezierConfig_new00(lua_State* tolua_S)
{
    deprecatedClassTip("ccBezierConfig");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"ccBezierConfig",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ccBezierConfig* tolua_ret = (ccBezierConfig*)  Mtolua_new((ccBezierConfig)());
        tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccBezierConfig");
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_ccBezierConfig_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("ccBezierConfig");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"ccBezierConfig",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            ccBezierConfig* tolua_ret = (ccBezierConfig*)  Mtolua_new((ccBezierConfig)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccBezierConfig");
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


static int tolua_get_ccBezierConfig_endPosition(lua_State* tolua_S)
{
    deprecatedClassTip("ccBezierConfig");
    
    ccBezierConfig* self = (ccBezierConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endPosition'",NULL);
#endif
    tolua_pushusertype(tolua_S,(void*)&self->endPosition,"CCPoint");
    return 1;
}

static int tolua_set_ccBezierConfig_endPosition(lua_State* tolua_S)
{
    deprecatedClassTip("ccBezierConfig");
    
    ccBezierConfig* self = (ccBezierConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endPosition'",NULL);
    if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_istable(tolua_S, 2, 0, &tolua_err)))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    
    Point endPosition;
    if (luaval_to_point(tolua_S, 2, &endPosition))
    {
        self->endPosition = endPosition;
    }
    return 0;
}

static int tolua_get_ccBezierConfig_controlPoint_1(lua_State* tolua_S)
{
    deprecatedClassTip("ccBezierConfig");
    
    ccBezierConfig* self = (ccBezierConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'controlPoint_1'",NULL);
#endif
    tolua_pushusertype(tolua_S,(void*)&self->controlPoint_1,"CCPoint");
    return 1;
}


static int tolua_set_ccBezierConfig_controlPoint_1(lua_State* tolua_S)
{
    deprecatedClassTip("ccBezierConfig");
    
    ccBezierConfig* self = (ccBezierConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'controlPoint_1'",NULL);
    if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_istable(tolua_S, 2, 0, &tolua_err)))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    
    Point controlPoint_1;
    if (luaval_to_point(tolua_S, 2, &controlPoint_1))
    {
        self->controlPoint_1 = controlPoint_1;
    }
    return 0;
}


static int tolua_get_ccBezierConfig_controlPoint_2(lua_State* tolua_S)
{
    deprecatedClassTip("ccBezierConfig");
    
    ccBezierConfig* self = (ccBezierConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'controlPoint_2'",NULL);
#endif
    tolua_pushusertype(tolua_S,(void*)&self->controlPoint_2,"CCPoint");
    return 1;
}


static int tolua_set_ccBezierConfig_controlPoint_2(lua_State* tolua_S)
{
    deprecatedClassTip("ccBezierConfig");
    
    ccBezierConfig* self = (ccBezierConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'controlPoint_2'",NULL);
    if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_istable(tolua_S, 2, 0, &tolua_err)))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    
    Point controlPoint_2;
    if (luaval_to_point(tolua_S, 2, &controlPoint_2))
    {
        self->controlPoint_2 = controlPoint_2;
    }
    return 0;
}

static int tolua_collect_ccBezierConfig (lua_State* tolua_S)
{
    ccBezierConfig* self = (ccBezierConfig*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int register_cocos2dx_deprecated_ccBezierConfig(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "ccBezierConfig");
    tolua_cclass(tolua_S,"ccBezierConfig","ccBezierConfig","",tolua_collect_ccBezierConfig);
    
    tolua_beginmodule(tolua_S,"ccBezierConfig");
    tolua_function(tolua_S,"new",tolua_Cocos2d_ccBezierConfig_new00);
    tolua_function(tolua_S,"new_local",tolua_Cocos2d_ccBezierConfig_new00_local);
    tolua_function(tolua_S,".call",tolua_Cocos2d_ccBezierConfig_new00_local);
    tolua_variable(tolua_S,"endPosition",tolua_get_ccBezierConfig_endPosition,tolua_set_ccBezierConfig_endPosition);
    tolua_variable(tolua_S,"controlPoint_1",tolua_get_ccBezierConfig_controlPoint_1,tolua_set_ccBezierConfig_controlPoint_1);
    tolua_variable(tolua_S,"controlPoint_2",tolua_get_ccBezierConfig_controlPoint_2,tolua_set_ccBezierConfig_controlPoint_2);
    tolua_endmodule(tolua_S);
    
    return 1;
}


static int tolua_Cocos2d_CCEGLViewProtocol_getFrameSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const EGLViewProtocol* self = (const EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrameSize'", NULL);
#endif
        {
            const Size& tolua_ret = (const Size&)  self->getFrameSize();
            tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getFrameSize'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_setFrameSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        EGLViewProtocol* self = (EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
        float width = ((float)  tolua_tonumber(tolua_S,2,0));
        float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFrameSize'", NULL);
#endif
        {
            self->setFrameSize(width,height);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setFrameSize'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_getVisibleSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const EGLViewProtocol* self = (const EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVisibleSize'", NULL);
#endif
        {
            Size tolua_ret = (Size)  self->getVisibleSize();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Size)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Size));
                tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getVisibleSize'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_getVisibleOrigin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const EGLViewProtocol* self = (const EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVisibleOrigin'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->getVisibleOrigin();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Point));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getVisibleOrigin'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_setDesignResolutionSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        EGLViewProtocol* self = (EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
        float width = ((float)  tolua_tonumber(tolua_S,2,0));
        float height = ((float)  tolua_tonumber(tolua_S,3,0));
        ResolutionPolicy resolutionPolicy = ((ResolutionPolicy) (int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDesignResolutionSize'", NULL);
#endif
        {
            self->setDesignResolutionSize(width,height,resolutionPolicy);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setDesignResolutionSize'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_getDesignResolutionSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const EGLViewProtocol* self = (const EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDesignResolutionSize'", NULL);
#endif
        {
            const Size& tolua_ret = (const Size&)  self->getDesignResolutionSize();
            tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getDesignResolutionSize'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_setTouchDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"EGLTouchDelegate",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        EGLViewProtocol* self = (EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
        EGLTouchDelegate* pDelegate = ((EGLTouchDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchDelegate'", NULL);
#endif
        {
            self->setTouchDelegate(pDelegate);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTouchDelegate'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_setViewPortInPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        EGLViewProtocol* self = (EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        float w = ((float)  tolua_tonumber(tolua_S,4,0));
        float h = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewPortInPoints'", NULL);
#endif
        {
            self->setViewPortInPoints(x,y,w,h);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setViewPortInPoints'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_setScissorInPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        EGLViewProtocol* self = (EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
        float x = ((float)  tolua_tonumber(tolua_S,2,0));
        float y = ((float)  tolua_tonumber(tolua_S,3,0));
        float w = ((float)  tolua_tonumber(tolua_S,4,0));
        float h = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScissorInPoints'", NULL);
#endif
        {
            self->setScissorInPoints(x,y,w,h);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setScissorInPoints'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_getViewPortRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const EGLViewProtocol* self = (const EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getViewPortRect'", NULL);
#endif
        {
            const Rect& tolua_ret = (const Rect&)  self->getViewPortRect();
            tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCRect");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getViewPortRect'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_getScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const EGLViewProtocol* self = (const EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleX'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getScaleX();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getScaleX'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCEGLViewProtocol_getScaleY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCEGLViewProtocol",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const EGLViewProtocol* self = (const EGLViewProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleY'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getScaleY();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getScaleY'.",&tolua_err);
    return 0;
#endif
}

static int register_cocos2d_deprecated_EGLViewProtocol(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "CCEGLViewProtocol");
    tolua_cclass(tolua_S,"CCEGLViewProtocol","CCEGLViewProtocol","",NULL);
    
    tolua_beginmodule(tolua_S,"CCEGLViewProtocol");
        tolua_function(tolua_S,"getFrameSize",tolua_Cocos2d_CCEGLViewProtocol_getFrameSize00);
        tolua_function(tolua_S,"setFrameSize",tolua_Cocos2d_CCEGLViewProtocol_setFrameSize00);
        tolua_function(tolua_S,"getVisibleSize",tolua_Cocos2d_CCEGLViewProtocol_getVisibleSize00);
        tolua_function(tolua_S,"getVisibleOrigin",tolua_Cocos2d_CCEGLViewProtocol_getVisibleOrigin00);
        tolua_function(tolua_S,"setDesignResolutionSize",tolua_Cocos2d_CCEGLViewProtocol_setDesignResolutionSize00);
        tolua_function(tolua_S,"getDesignResolutionSize",tolua_Cocos2d_CCEGLViewProtocol_getDesignResolutionSize00);
        tolua_function(tolua_S,"setTouchDelegate",tolua_Cocos2d_CCEGLViewProtocol_setTouchDelegate00);
        tolua_function(tolua_S,"setViewPortInPoints",tolua_Cocos2d_CCEGLViewProtocol_setViewPortInPoints00);
        tolua_function(tolua_S,"setScissorInPoints",tolua_Cocos2d_CCEGLViewProtocol_setScissorInPoints00);
        tolua_function(tolua_S,"getViewPortRect",tolua_Cocos2d_CCEGLViewProtocol_getViewPortRect00);
        tolua_function(tolua_S,"getScaleX",tolua_Cocos2d_CCEGLViewProtocol_getScaleX00);
        tolua_function(tolua_S,"getScaleY",tolua_Cocos2d_CCEGLViewProtocol_getScaleY00);
    tolua_endmodule(tolua_S);
    return 1;
}

static int tolua_Cocos2d_CCEGLView_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCEGLView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            EGLView* tolua_ret = (EGLView*)  EGLView::getInstance();
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCEGLView");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
    return 0;
#endif
}

static int register_cocos2d_deprecated_EGLView(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "CCEGLView");
    tolua_cclass(tolua_S,"CCEGLView","CCEGLView","CCEGLViewProtocol",NULL);
    
    tolua_beginmodule(tolua_S,"CCEGLView");
        tolua_function(tolua_S,"getInstance",tolua_Cocos2d_CCEGLView_getInstance00);
    tolua_endmodule(tolua_S);
    return 1;
}

static int tolua_Cocos2d_BlendFunc_new00(lua_State* tolua_S)
{
    deprecatedClassTip("BlendFunc");
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"BlendFunc",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            BlendFunc* tolua_ret = (BlendFunc*)  Mtolua_new((BlendFunc)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"BlendFunc");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_BlendFunc_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("BlendFunc");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"BlendFunc",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            BlendFunc* tolua_ret = (BlendFunc*)  Mtolua_new((BlendFunc)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"BlendFunc");
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


static int tolua_get_BlendFunc_unsigned_src(lua_State* tolua_S)
{
    deprecatedClassTip("BlendFunc");
    
    BlendFunc* self = (BlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'src'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->src);
    return 1;
}


static int tolua_set_BlendFunc_unsigned_src(lua_State* tolua_S)
{
    deprecatedClassTip("BlendFunc");
    
    BlendFunc* self = (BlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'src'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->src = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}


static int tolua_get_BlendFunc_unsigned_dst(lua_State* tolua_S)
{
    deprecatedClassTip("BlendFunc");
    
    BlendFunc* self = (BlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dst'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->dst);
    return 1;
}


static int tolua_set_BlendFunc_unsigned_dst(lua_State* tolua_S)
{
    deprecatedClassTip("BlendFunc");
    
    BlendFunc* self = (BlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dst'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->dst = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}

static int tolua_cocos2d_kmGLPushMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S,1,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        kmGLPushMatrix();
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'kmGLPushMatrix'.",&tolua_err);
    return 0;
#endif
}

static int tolua_collect_BlendFunc (lua_State* tolua_S)
{
    BlendFunc* self = (BlendFunc*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int register_cocos2d_deprecated_BlendFunc(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "BlendFunc");
#ifdef __cplusplus
    tolua_cclass(tolua_S,"BlendFunc","BlendFunc","",tolua_collect_BlendFunc);
#else
    tolua_cclass(tolua_S,"BlendFunc","BlendFunc","",NULL);
#endif
    
    tolua_beginmodule(tolua_S,"BlendFunc");
        tolua_function(tolua_S,"new",tolua_Cocos2d_BlendFunc_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_BlendFunc_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_BlendFunc_new00_local);
        tolua_variable(tolua_S,"src",tolua_get_BlendFunc_unsigned_src,tolua_set_BlendFunc_unsigned_src);
        tolua_variable(tolua_S,"dst",tolua_get_BlendFunc_unsigned_dst,tolua_set_BlendFunc_unsigned_dst);
    tolua_endmodule(tolua_S);
    
    return 1;
}

static int tolua_cocos2d_kmGLTranslatef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        float x = ((float)  tolua_tonumber(tolua_S,1,0));
        float y = ((float)  tolua_tonumber(tolua_S,2,0));
        float z = ((float)  tolua_tonumber(tolua_S,3,0));
        {
            kmGLTranslatef(x,y,z);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'kmGLTranslatef'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_kmGLPopMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S,1,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            kmGLPopMatrix();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'kmGLPopMatrix'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_intValue00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCString",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intValue'", NULL);
#endif
        {
            int tolua_ret = (int)  self->intValue();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'intValue'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_uintValue00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCString",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'uintValue'", NULL);
#endif
        {
            unsigned int tolua_ret = (unsigned int)  self->uintValue();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'uintValue'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_floatValue00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCString",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'floatValue'", NULL);
#endif
        {
            float tolua_ret = (float)  self->floatValue();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'floatValue'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_doubleValue00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCString",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doubleValue'", NULL);
#endif
        {
            double tolua_ret = (double)  self->doubleValue();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'doubleValue'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_boolValue00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCString",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'boolValue'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->boolValue();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'boolValue'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_getCString00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCString",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCString'", NULL);
#endif
        {
            const char* tolua_ret = (const char*)  self->getCString();
            tolua_pushstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getCString'.",&tolua_err);
    return 0;
#endif
}



static int tolua_Cocos2d_CCString_length00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCString",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length'", NULL);
#endif
        {
            unsigned int tolua_ret = (unsigned int)  self->length();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'length'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_compare00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const CCString",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
        const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'compare'", NULL);
#endif
        {
            int tolua_ret = (int)  self->compare(str);
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'compare'.",&tolua_err);
    return 0;
#endif
}



static int tolua_Cocos2d_CCString_isEqual00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCString",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"const CCObject",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        String* self = (String*)  tolua_tousertype(tolua_S,1,0);
        const Object* pObject = ((const Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEqual'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->isEqual(pObject);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isEqual'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_create00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCString",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const char* pStr = ((const char*)  tolua_tostring(tolua_S,2,0));
        {
            String* tolua_ret = (String*)  String::create(pStr);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCString");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_createWithData00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCString",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned char* pData = ((unsigned char*)  tolua_tostring(tolua_S,2,0));
        unsigned long nLen = ((unsigned long)  tolua_tonumber(tolua_S,3,0));
        {
            String* tolua_ret = (String*)  String::createWithData(pData,nLen);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCString");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithData'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCString_createWithContentsOfFile00(lua_State* tolua_S)
{
    deprecatedClassTip("CCString");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCString",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
        {
            String* tolua_ret = (String*)  String::createWithContentsOfFile(pszFileName);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCString");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithContentsOfFile'.",&tolua_err);
    return 0;
#endif
}

static int register_cocos2dx_deprecated_String(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "CCString");
    tolua_cclass(tolua_S,"CCString","CCString","Object",NULL);
    tolua_beginmodule(tolua_S,"CCString");
        tolua_function(tolua_S,"intValue",tolua_Cocos2d_CCString_intValue00);
        tolua_function(tolua_S,"uintValue",tolua_Cocos2d_CCString_uintValue00);
        tolua_function(tolua_S,"floatValue",tolua_Cocos2d_CCString_floatValue00);
        tolua_function(tolua_S,"doubleValue",tolua_Cocos2d_CCString_doubleValue00);
        tolua_function(tolua_S,"boolValue",tolua_Cocos2d_CCString_boolValue00);
        tolua_function(tolua_S,"getCString",tolua_Cocos2d_CCString_getCString00);
        tolua_function(tolua_S,"length",tolua_Cocos2d_CCString_length00);
        tolua_function(tolua_S,"compare",tolua_Cocos2d_CCString_compare00);
        tolua_function(tolua_S,"isEqual",tolua_Cocos2d_CCString_isEqual00);
        tolua_function(tolua_S,"create",tolua_Cocos2d_CCString_create00);
        tolua_function(tolua_S,"createWithData",tolua_Cocos2d_CCString_createWithData00);
        tolua_function(tolua_S,"createWithContentsOfFile",tolua_Cocos2d_CCString_createWithContentsOfFile00);
    tolua_endmodule(tolua_S);
    return 1;
}

static int tolua_Cocos2d_ccTexParams_new00(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"ccTexParams",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Texture2D::TexParams* tolua_ret = (Texture2D::TexParams*)  Mtolua_new((Texture2D::TexParams)());
        tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccTexParams");
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_ccTexParams_new00_local(lua_State* tolua_S)
{
    
    deprecatedClassTip("ccTexParams");
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"ccTexParams",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            Texture2D::TexParams* tolua_ret = (Texture2D::TexParams*)  Mtolua_new((Texture2D::TexParams)());
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccTexParams");
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


static int tolua_get_ccTexParams_unsigned_minFilter(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
    Texture2D::TexParams* self = (Texture2D::TexParams*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'minFilter'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->minFilter);
    return 1;
}


static int tolua_set_ccTexParams_unsigned_minFilter(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
    Texture2D::TexParams* self = (Texture2D::TexParams*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'minFilter'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->minFilter = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}


static int tolua_get_ccTexParams_unsigned_magFilter(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
    Texture2D::TexParams* self = (Texture2D::TexParams*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'magFilter'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->magFilter);
    return 1;
}


static int tolua_set_ccTexParams_unsigned_magFilter(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
    Texture2D::TexParams* self = (Texture2D::TexParams*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'magFilter'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->magFilter = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}


static int tolua_get_ccTexParams_unsigned_wrapS(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
    Texture2D::TexParams* self = (Texture2D::TexParams*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wrapS'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->wrapS);
    return 1;
}


static int tolua_set_ccTexParams_unsigned_wrapS(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
    Texture2D::TexParams* self = (Texture2D::TexParams*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wrapS'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->wrapS = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}


static int tolua_get_ccTexParams_unsigned_wrapT(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
    Texture2D::TexParams* self = (Texture2D::TexParams*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wrapT'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->wrapT);
    return 1;
}


static int tolua_set_ccTexParams_unsigned_wrapT(lua_State* tolua_S)
{
    deprecatedClassTip("ccTexParams");
    
    Texture2D::TexParams* self = (Texture2D::TexParams*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wrapT'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->wrapT = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
    ;
    return 0;
}

static int tolua_collect_ccTexParams (lua_State* tolua_S)
{
    Texture2D::TexParams* self = (Texture2D::TexParams*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int register_cocos2dx_deprecated_Texparams(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccTexParams");
    
#ifdef __cplusplus
    tolua_cclass(tolua_S,"ccTexParams","ccTexParams","",tolua_collect_ccTexParams);
#else
    tolua_cclass(tolua_S,"ccTexParams","ccTexParams","",NULL);
#endif
    
    tolua_beginmodule(tolua_S,"ccTexParams");
        tolua_function(tolua_S,"new",tolua_Cocos2d_ccTexParams_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_ccTexParams_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_ccTexParams_new00_local);
        tolua_variable(tolua_S,"minFilter",tolua_get_ccTexParams_unsigned_minFilter,tolua_set_ccTexParams_unsigned_minFilter);
        tolua_variable(tolua_S,"magFilter",tolua_get_ccTexParams_unsigned_magFilter,tolua_set_ccTexParams_unsigned_magFilter);
        tolua_variable(tolua_S,"wrapS",tolua_get_ccTexParams_unsigned_wrapS,tolua_set_ccTexParams_unsigned_wrapS);
        tolua_variable(tolua_S,"wrapT",tolua_get_ccTexParams_unsigned_wrapT,tolua_set_ccTexParams_unsigned_wrapT);
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
    register_cocos2dx_deprecated_PointArray(tolua_S);
    register_cocos2dx_deprecated_ccBezierConfig(tolua_S);
    register_cocos2d_deprecated_EGLViewProtocol(tolua_S);
    register_cocos2d_deprecated_EGLView(tolua_S);
    register_cocos2d_deprecated_BlendFunc(tolua_S);
    register_cocos2dx_deprecated_String(tolua_S);
    register_cocos2dx_deprecated_Texparams(tolua_S);
    tolua_function(tolua_S,"kmGLPushMatrix",tolua_cocos2d_kmGLPushMatrix00);
    tolua_function(tolua_S,"kmGLTranslatef",tolua_cocos2d_kmGLTranslatef00);
    tolua_function(tolua_S,"kmGLPopMatrix",tolua_cocos2d_kmGLPopMatrix00);
    tolua_endmodule(tolua_S);
    
    return 0;
}

extern int lua_cocos2dx_Node_setPosition(lua_State* tolua_S);

static int tolua_cocos2dx_Node_setPosition_deprecated(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
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

static int tolua_cocos2d_Sequence_createWithTwoActions(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Sequence",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        FiniteTimeAction* pActionOne = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,2,0));
        FiniteTimeAction* pActionTwo = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,3,0));
        {
            Sequence* tolua_ret = (Sequence*)  Sequence::createWithTwoActions(pActionOne,pActionTwo);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Sequence");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithTwoActions'.",&tolua_err);
    return 0;
#endif
}

extern int tolua_cocos2d_Sequence_create(lua_State* tolua_S);
static int tolua_Cocos2d_Sequence_create_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Sequence",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Array* actions = ((Array*)  tolua_tousertype(tolua_S,2,0));
        {
            Sequence* tolua_ret = (Sequence*)  Sequence::create(actions);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Sequence");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_Sequence_create(tolua_S);
}

static int extendSequenceDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Sequence");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithTwoActions",tolua_cocos2d_Sequence_createWithTwoActions);
        tolua_function(tolua_S, "create", tolua_Cocos2d_Sequence_create_deprecated00);
    }
    
    return 1;
}

extern int lua_cocos2d_CardinalSplineBy_create(lua_State* tolua_S);

static int tolua_cocos2d_CardinalSplineBy_create_deprecated(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CardinalSplineBy",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCPointArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float duration = ((float)  tolua_tonumber(tolua_S,2,0));
        PointArray* points = ((PointArray*)  tolua_tousertype(tolua_S,3,0));
        float tension = ((float)  tolua_tonumber(tolua_S,4,0));
        {
            CardinalSplineBy* tolua_ret = (CardinalSplineBy*)  CardinalSplineBy::create(duration,points,tension);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CardinalSplineBy");
        }
    }
    return 1;
tolua_lerror:
    return lua_cocos2d_CardinalSplineBy_create(tolua_S);
}

static int extendCardinalSplineByDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"CardinalSplineBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CardinalSplineBy_create_deprecated);
        lua_rawset(tolua_S,-3);
    }
    
    return 1;
}


extern int tolua_Cocos2d_CCDrawPrimitives_ccDrawCardinalSpline00(lua_State* tolua_S);
static int tolua_cocos2d_CCDrawPrimitives_ccDrawCardinalSpline_deprecate00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        PointArray* config = ((PointArray*)  tolua_tousertype(tolua_S,1,0));
        float tension = ((float)  tolua_tonumber(tolua_S,2,0));
        unsigned int segments = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
        DrawPrimitives::drawCardinalSpline(config,tension,segments);
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_CCDrawPrimitives_ccDrawCardinalSpline00(tolua_S);
}

extern int tolua_Cocos2d_CCDrawPrimitives_ccDrawCatmullRom00(lua_State* tolua_S);
static int tolua_cocos2d_CCDrawPrimitives_ccDrawCatmullRom_deprecated00(lua_State* tolua_S)
{
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCPointArray",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        PointArray* arrayOfControlPoints = ((PointArray*)  tolua_tousertype(tolua_S,1,0));
        unsigned int segments = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        DrawPrimitives::drawCatmullRom(arrayOfControlPoints,segments);
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_CCDrawPrimitives_ccDrawCatmullRom00(tolua_S);
}

static int extendDrawPrimitivesDeprecated(lua_State* tolua_S)
{
    lua_getglobal(tolua_S, "_G");
    if (lua_istable(tolua_S,-1))//stack:...,_G,
    {
        lua_pushstring(tolua_S,"gl");//stack:_G,keyValue
        lua_gettable(tolua_S, -2);//stack:_G,glMoule
        if (lua_istable(tolua_S,-1))
        {
            lua_pushstring(tolua_S, "DrawPrimitives");//stack:_G,glMoudle,keyValue
            lua_gettable(tolua_S, -2);//statck:_G,glMoudle,gl.DrawPrimitives
            if (lua_istable(tolua_S,-1))//statck:_G,glMoudle,gl.DrawPrimitives
            {
                lua_pushstring(tolua_S,"ccDrawCardinalSpline");//statck:_G,glMoudle,gl.DrawPrimitives keyValue
                lua_pushcfunction(tolua_S,tolua_cocos2d_CCDrawPrimitives_ccDrawCardinalSpline_deprecate00);//statck:_G,glMoudle,gl.DrawPrimitives keyValue,func
                lua_rawset(tolua_S,-3);//statck:_G,glMoudle,gl.DrawPrimitives
                
                lua_pushstring(tolua_S,"ccDrawCatmullRom");//statck:_G,glMoudle,gl.DrawPrimitives keyValue
                lua_pushcfunction(tolua_S,tolua_cocos2d_CCDrawPrimitives_ccDrawCatmullRom_deprecated00);//statck:_G,glMoudle,gl.DrawPrimitives keyValue,func
                lua_rawset(tolua_S,-3);//statck:_G,glMoudle,gl.DrawPrimitives
            }
            lua_pop(tolua_S, 1);//statck:_G,glMoudle
        }
        lua_pop(tolua_S, 1);//statck:_G
    }
    lua_pop(tolua_S, 1);//statck:...
    
    return 1;
}

extern int tolua_cocos2d_CatmullRomBy_create(lua_State* tolua_S);
static int tolua_cocos2d_CatmullRomBy_create_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CatmullRomBy",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCPointArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float dt = ((float)  tolua_tonumber(tolua_S,2,0));
        PointArray* points = ((PointArray*)  tolua_tousertype(tolua_S,3,0));
        {
            CatmullRomBy* tolua_ret = (CatmullRomBy*)  CatmullRomBy::create(dt,points);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CatmullRomBy");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_CatmullRomBy_create(tolua_S);
}

static int extendCatmullRomByDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"CatmullRomBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CatmullRomBy_create_deprecated00);
        lua_rawset(tolua_S,-3);
    }
    return 1;
}

extern int tolua_cocos2d_CatmullRomTo_create(lua_State* tolua_S);
static int tolua_cocos2d_CatmullRomTo_create_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CatmullRomTo",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCPointArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float dt = ((float)  tolua_tonumber(tolua_S,2,0));
        PointArray* points = ((PointArray*)  tolua_tousertype(tolua_S,3,0));
        {
            CatmullRomTo* tolua_ret = (CatmullRomTo*)  CatmullRomTo::create(dt,points);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CatmullRomTo");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_CatmullRomTo_create(tolua_S);
}

static int extendCatmullRomToDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"CatmullRomTo");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CatmullRomTo_create_deprecated00);
        lua_rawset(tolua_S,-3);
    }
    return 1;
}

extern int tolua_cocos2d_BezierBy_create(lua_State* tolua_S);
static int tolua_Cocos2d_BezierBy_create_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"BezierBy",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"ccBezierConfig",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float t = ((float)  tolua_tonumber(tolua_S,2,0));
        ccBezierConfig c = *((ccBezierConfig*)  tolua_tousertype(tolua_S,3,0));
        {
            BezierBy* tolua_ret = (BezierBy*)  BezierBy::create(t,c);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"BezierBy");
        }
    }
    return 1;

tolua_lerror:
    return tolua_cocos2d_BezierBy_create(tolua_S);
}

static int extendBezierByDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"BezierBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_Cocos2d_BezierBy_create_deprecated00);
        lua_rawset(tolua_S,-3);
    }
    return 1;
}


extern int tolua_cocos2d_BezierTo_create(lua_State* tolua_S);
static int tolua_Cocos2d_BezierTo_create_deprecated00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"BezierTo",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"ccBezierConfig",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        float t = ((float)  tolua_tonumber(tolua_S,2,0));
        ccBezierConfig c = *((ccBezierConfig*)  tolua_tousertype(tolua_S,3,0));
        {
            BezierTo* tolua_ret = (BezierTo*)  BezierTo::create(t,c);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"BezierTo");
        }
    }
    return 1;
tolua_lerror:
    return tolua_cocos2d_BezierTo_create(tolua_S);
}

static int extendBezierToDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"BezierTo");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_Cocos2d_BezierTo_create_deprecated00);
        lua_rawset(tolua_S,-3);
    }
    return 1;
}

#ifdef __cplusplus
extern "C" {
#endif
extern int tolua_bnd_cast(lua_State* tolua_S);
#ifdef __cplusplus
}
#endif

static int tolua_bnd_cast_deprecated00(lua_State* tolua_S)
{
    void* v = nullptr;
    std::string strValue = "";
    strValue = tolua_tostring(tolua_S,2,NULL);
    int pos = strValue.find("CC");
    if (pos == 0 &&
        std::string::npos == strValue.find("CCBAnimationManager") &&
        std::string::npos == strValue.find("CCBReader") &&
        std::string::npos == strValue.find("CCString"))
    {
        strValue = strValue.substr(2);
        if (lua_islightuserdata(tolua_S, 1)) {
            v = tolua_touserdata(tolua_S, 1, NULL);
        } else {
            v = tolua_tousertype(tolua_S, 1, 0);
        };
        if (v && !strValue.empty())
            tolua_pushusertype(tolua_S,v,strValue.c_str());
        else
            lua_pushnil(tolua_S);
        return 1;        
    }
    else
    {
        return tolua_bnd_cast(tolua_S);
    }
}

static int extendToluaDeprecated(lua_State* tolua_S)
{
    lua_getglobal(tolua_S, "_G");
    if (lua_istable(tolua_S,-1))//stack:...,_G,
    {
        lua_pushstring(tolua_S,"tolua");//stack:_G,keyValue
        lua_gettable(tolua_S, -2);//stack:_G,toluaModule
        if (lua_istable(tolua_S,-1))
        {
            tolua_function(tolua_S, "cast", tolua_bnd_cast_deprecated00);
        }
        lua_pop(tolua_S, 1);//statck:_G
    }
    lua_pop(tolua_S, 1);//statck:...
    
    return 1;
}

static int tolua_cocos2d_Spawn_createWithTwoActions_deprcated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Spawn",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        FiniteTimeAction* pAction1 = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,2,0));
        FiniteTimeAction* pAction2 = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,3,0));
        {
            Spawn* tolua_ret = (Spawn*)  Spawn::createWithTwoActions(pAction1,pAction2);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Spawn");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithTwoActions'.",&tolua_err);
    return 0;
#endif
}

static int extendSpawnDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Spawn");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithTwoActions", tolua_cocos2d_Spawn_createWithTwoActions_deprcated00);
    }
    
    return 1;
}


static int tolua_cocos2d_Menu_createWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Menu",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Array* pArrayOfItems = ((Array*)  tolua_tousertype(tolua_S,2,0));
        {
            Menu* tolua_ret = (Menu*)  Menu::createWithArray(pArrayOfItems);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Menu");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithArray'.",&tolua_err);
    return 0;
#endif
}

static int extendMenuDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Menu");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithArray", tolua_cocos2d_Menu_createWithArray00);
    }
    
    return 1;
}

extern int lua_cocos2dx_LabelTTF_setString(lua_State* tolua_S);
static int tolua_cocos2dx_LabelTTF_setString_deprecated00(lua_State* tolua_S)
{
    deprecatedFunctionTip("LabelTTF:setString(String object)","LabelTTF:setString(lua string)");
    
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"LabelTTF",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        LabelTTF* self = (LabelTTF*)  tolua_tousertype(tolua_S,1,0);
        const char* label = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setString'", NULL);
#endif
        {
            self->setString(label);
        }
    }
    return 0;
tolua_lerror:
    return lua_cocos2dx_LabelTTF_setString(tolua_S);
}

static int extendLabelTTFDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"LabelTTF");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setString", tolua_cocos2dx_LabelTTF_setString_deprecated00);
    }
    
    return 1;
}

#ifdef __cplusplus
extern "C" {
#endif
    extern int class_sub_event(lua_State* tolua_S);
#ifdef __cplusplus
}
#endif


static int tolua_cocos2d_Point_sub_event(lua_State* tolua_S)
{
    deprecatedFunctionTip("CCPoin.__Sub","cc.pSub");
    
    tolua_Error tolua_err;
    if (
        !tolua_istable(tolua_S, 1, 0, &tolua_err)||
        !tolua_istable(tolua_S, 2, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        Point self;
        luaval_to_point(tolua_S, 1, &self);
        Point right;
        luaval_to_point(tolua_S, 2, &right);
        Point tolua_ret = (Point)  self.operator-(right);
        point_to_luaval(tolua_S, tolua_ret);
        return 1;
    }
    
tolua_lerror:
    return class_sub_event(tolua_S);
}

static int extendCCPointDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"CCPoint");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "__sub", tolua_cocos2d_Point_sub_event);
    }
    
    return 1;
}

int register_all_cocos2dx_manual_deprecated(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    extendNodeDeprecated(tolua_S);
    extendSpriteFrameDeprecated(tolua_S);
    extendAnimationDeprecated(tolua_S);
    extendSequenceDeprecated(tolua_S);
    extendCardinalSplineByDeprecated(tolua_S);
    extendDrawPrimitivesDeprecated(tolua_S);
    extendCatmullRomByDeprecated(tolua_S);
    extendCatmullRomToDeprecated(tolua_S);
    extendBezierByDeprecated(tolua_S);
    extendBezierToDeprecated(tolua_S);
    extendToluaDeprecated(tolua_S);
    extendSpawnDeprecated(tolua_S);
    extendMenuDeprecated(tolua_S);
    extendLabelTTFDeprecated(tolua_S);
    extendCCPointDeprecated(tolua_S);
    return 0;
}
