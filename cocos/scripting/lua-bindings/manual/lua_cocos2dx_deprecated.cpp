/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "lua_cocos2dx_deprecated.h"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

template <class T>
bool array_to_vector_t_deprecated(__Array& array,Vector<T>& vec)
{
    if ( 0 == array.count() )
        return false;
    
    vec.clear();
    
    for (int i = 0; i < array.count() ; i++)
    {
        T obj = dynamic_cast<T>(array.getObjectAtIndex(i));
        if (nullptr  != obj)
            vec.pushBack(obj);
    }
    
    return true;
}

bool array_to_valuevector_deprecated(__Array& array,ValueVector& valueVec)
{
    if (0 == array.count())
        return false;
    
    valueVec.clear();
    
    __String* strVal = nullptr;
    __Double* doubleVal = nullptr;
    __Bool* boolVal = nullptr;
    __Float* floatVal = nullptr;
    __Integer* intVal = nullptr;
    
    for (int i = 0; i < array.count(); i++)
    {
        if( (strVal = dynamic_cast<__String *>(array.getObjectAtIndex(i))))
        {
            valueVec.push_back(Value(strVal->getCString()));
        }
        else if ((doubleVal = dynamic_cast<__Double*>(array.getObjectAtIndex(i))))
        {
            valueVec.push_back(Value(doubleVal->getValue()));
        }
        else if ((floatVal = dynamic_cast<__Float*>(array.getObjectAtIndex(i))))
        {
            valueVec.push_back(Value(floatVal->getValue()));
        }
        else if ((intVal = dynamic_cast<__Integer*>(array.getObjectAtIndex(i))))
        {
            valueVec.push_back(Value(intVal->getValue()));
        }
        else if ((boolVal = dynamic_cast<__Bool*>(array.getObjectAtIndex(i))))
        {
            valueVec.push_back(Value(boolVal->getValue()));
        }
        else
        {
            CCASSERT(false, "the type isn't suppored.");
        }
    }
    
    return true;
}

#define deprecatedClassTip(className) CCLOG("%s will be not binded in lua,please use the lua's table instead",className)
#define deprecatedFunctionTip(oldFun,newFun) CCLOG("%s was deprecated please use %s instead ",oldFun, newFun)
static int tolua_Cocos2d_CCPoint_new00(lua_State* tolua_S)
{
    deprecatedClassTip("CCPoint");
    
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
        Point tolua_ret;
        point_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPoint_new00_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCPoint");
    
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
        Point tolua_ret;
        point_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_CCPoint_new01(lua_State* tolua_S)
{
    deprecatedClassTip("CCPoint");
    
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
        Point tolua_ret(x,y);
        point_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCPoint_new00(tolua_S);
}


static int tolua_Cocos2d_CCPoint_new01_local(lua_State* tolua_S)
{
    deprecatedClassTip("CCPoint");
    
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
        Point tolua_ret(x,y);
        point_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCPoint_new00_local(tolua_S);
}

static int tolua_collect_CCPoint (lua_State* tolua_S)
{
    Point* self = (Point*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int register_cocos2dx_deprecated_Point(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"CCPoint");
#ifdef __cplusplus
    tolua_cclass(tolua_S,"CCPoint","CCPoint","",tolua_collect_CCPoint);
#else
    tolua_cclass(tolua_S,"CCPoint","CCPoint","",NULL);
#endif
    tolua_beginmodule(tolua_S,"CCPoint");
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCPoint_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCPoint_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCPoint_new00_local);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCPoint_new01);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCPoint_new01_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCPoint_new01_local);
    tolua_endmodule(tolua_S);
    
    return 1;
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
        Rect tolua_ret;
        rect_to_luaval(tolua_S, tolua_ret);
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
        Rect tolua_ret;
        rect_to_luaval(tolua_S, tolua_ret);
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
        Rect tolua_ret(x, y, width, height);
        rect_to_luaval(tolua_S, tolua_ret);
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
        Rect tolua_ret(x, y, width, height);
        rect_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCRect_new00_local(tolua_S);
}

static int register_cocos2dx_deprecated_Rect(lua_State* tolua_S)
{
    
    tolua_usertype(tolua_S,"CCRect");
    tolua_cclass(tolua_S,"CCRect","CCRect","",NULL);
    tolua_beginmodule(tolua_S,"CCRect");
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCRect_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCRect_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCRect_new00_local);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCRect_new01);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCRect_new01_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCRect_new01_local);
    tolua_endmodule(tolua_S);
    
    return 1;
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
        Size tolua_ret;
        size_to_luaval(tolua_S, tolua_ret);
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
        Size tolua_ret;
        size_to_luaval(tolua_S, tolua_ret);
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
        Size tolua_ret(width, height);
        size_to_luaval(tolua_S, tolua_ret);
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
        Size tolua_ret(width, height);
        size_to_luaval(tolua_S, tolua_ret);
    }
    return 1;
tolua_lerror:
    return tolua_Cocos2d_CCSize_new00_local(tolua_S);
}


static int register_cocos2dx_deprecated_Size(lua_State* tolua_S)
{
    
    tolua_usertype(tolua_S,"CCSize");
    tolua_cclass(tolua_S,"CCSize","CCSize","",NULL);
    tolua_beginmodule(tolua_S,"CCSize");
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCSize_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCSize_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCSize_new00_local);
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCSize_new01);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCSize_new01_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCSize_new01_local);
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
            __Array* tolua_ret = (__Array*)  Array::create();
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
        !tolua_isusertype(tolua_S,2,"cc.Ref",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Ref* pObject = ((Ref*)  tolua_tousertype(tolua_S,2,0));
        {
            __Array* tolua_ret = (__Array*)  __Array::createWithObject(pObject);
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
        __Array* otherArray = ((__Array*)  tolua_tousertype(tolua_S,2,0));
        {
            __Array* tolua_ret = (__Array*)  __Array::createWithArray(otherArray);
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
            __Array* tolua_ret = (__Array*)  __Array::createWithCapacity(capacity);
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
            __Array* tolua_ret = (__Array*)  __Array::createWithContentsOfFile(pFileName);
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        !tolua_isusertype(tolua_S,2,"cc.Ref",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        Ref* object = ((Ref*)  tolua_tousertype(tolua_S,2,0));
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'objectAtIndex'", NULL);
#endif
        {
            Ref* tolua_ret = (Ref*)  self->getObjectAtIndex(index);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Ref");
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lastObject'", NULL);
#endif
        {
            Ref* tolua_ret = (Ref*)  self->getLastObject();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Ref");
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'randomObject'", NULL);
#endif
        {
            Ref* tolua_ret = (Ref*)  self->getRandomObject();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Ref");
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        __Array* pOtherArray = ((__Array*)  tolua_tousertype(tolua_S,2,0));
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
        !tolua_isusertype(tolua_S,2,"cc.Ref",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        Ref* object = ((Ref*)  tolua_tousertype(tolua_S,2,0));
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
        !tolua_isusertype(tolua_S,2,"cc.Ref",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        Ref* object = ((Ref*)  tolua_tousertype(tolua_S,2,0));
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        __Array* otherArray = ((__Array*)  tolua_tousertype(tolua_S,2,0));
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
        !tolua_isusertype(tolua_S,2,"cc.Ref",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        Ref* object = ((Ref*)  tolua_tousertype(tolua_S,2,0));
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        !tolua_isusertype(tolua_S,2,"cc.Ref",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        Ref* object = ((Ref*)  tolua_tousertype(tolua_S,2,0));
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        __Array* otherArray = ((__Array*)  tolua_tousertype(tolua_S,2,0));
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        !tolua_isusertype(tolua_S,2,"cc.Ref",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        Ref* object = ((Ref*)  tolua_tousertype(tolua_S,2,0));
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        !tolua_isusertype(tolua_S,2,"cc.Ref",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"cc.Ref",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        Ref* object1 = ((Ref*)  tolua_tousertype(tolua_S,2,0));
        Ref* object2 = ((Ref*)  tolua_tousertype(tolua_S,3,0));
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
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
        !tolua_isusertype(tolua_S,3,"cc.Ref",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* self = (__Array*)  tolua_tousertype(tolua_S,1,0);
        unsigned int uIndex = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        Ref* pObject = ((Ref*)  tolua_tousertype(tolua_S,3,0));
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

static int tolua_cocos2d_kmGLLoadMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_istable(tolua_S, 1, 0, &tolua_err)||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        kmMat4 mat4;
        size_t len = lua_objlen(tolua_S, 1);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S,i + 1);
            lua_gettable(tolua_S,1);
#ifndef TOLUA_RELEASE
            if (!tolua_isnumber(tolua_S, -1, 0, &tolua_err))
            {
                lua_pop(tolua_S, 1);
                goto tolua_lerror;
            }
            else
#endif
            {
                mat4.mat[i] = tolua_tonumber(tolua_S, -1, 0);
                lua_pop(tolua_S, 1);
            }
        }
        kmGLLoadMatrix(&mat4);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'kmGLLoadMatrix'.",&tolua_err);
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
        const __String* self = (const __String*)  tolua_tousertype(tolua_S,1,0);
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
        const __String* self = (const __String*)  tolua_tousertype(tolua_S,1,0);
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
        const __String* self = (const __String*)  tolua_tousertype(tolua_S,1,0);
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
        const __String* self = (const __String*)  tolua_tousertype(tolua_S,1,0);
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
        const __String* self = (const __String*)  tolua_tousertype(tolua_S,1,0);
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
        const __String* self = (const __String*)  tolua_tousertype(tolua_S,1,0);
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
        const __String* self = (const __String*)  tolua_tousertype(tolua_S,1,0);
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
        const __String* self = (const __String*)  tolua_tousertype(tolua_S,1,0);
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
        __String* self = (__String*)  tolua_tousertype(tolua_S,1,0);
        const Ref* pObject = ((const Ref*)  tolua_tousertype(tolua_S,2,0));
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
            __String* tolua_ret = (__String*)  String::create(pStr);
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
            __String* tolua_ret = (__String*)  String::createWithData(pData,nLen);
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
            __String* tolua_ret = (__String*)  String::createWithContentsOfFile(pszFileName);
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
    tolua_cclass(tolua_S,"CCString","CCString","cc.Ref",NULL);
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


int register_all_cocos2dx_deprecated(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
    register_cocos2dx_deprecated_Point(tolua_S);
    register_cocos2dx_deprecated_Rect(tolua_S);
    register_cocos2dx_deprecated_Size(tolua_S);
    register_cocos2dx_deprecated_Array(tolua_S);
    register_cocos2dx_deprecated_String(tolua_S);
    tolua_function(tolua_S,"kmGLPushMatrix",tolua_cocos2d_kmGLPushMatrix00);
    tolua_function(tolua_S,"kmGLTranslatef",tolua_cocos2d_kmGLTranslatef00);
    tolua_function(tolua_S,"kmGLPopMatrix",tolua_cocos2d_kmGLPopMatrix00);
    tolua_function(tolua_S,"kmGLLoadMatrix",tolua_cocos2d_kmGLLoadMatrix00);
    tolua_endmodule(tolua_S);
    
    return 0;
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
        __Array* arrayOfSpriteFrameNames = ((__Array*)  tolua_tousertype(tolua_S,2,0));
        Vector<SpriteFrame*> vec;
        array_to_vector_t_deprecated(*arrayOfSpriteFrameNames, vec);
        float delay = ((float)  tolua_tonumber(tolua_S,3,0));
        cocos2d::Animation* tolua_ret = (cocos2d::Animation*)  cocos2d::Animation::createWithSpriteFrames(vec,delay);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Animation");
    
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
        __Array* arrayOfSpriteFrameNames = ((__Array*)  tolua_tousertype(tolua_S,2,0));
        Vector<SpriteFrame*> vec;
        array_to_vector_t_deprecated(*arrayOfSpriteFrameNames, vec);
        cocos2d::Animation* tolua_ret = (cocos2d::Animation*)  cocos2d::Animation::createWithSpriteFrames(vec);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Animation");
        
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
    lua_pop(tolua_S, 1);
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
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Sequence");
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
        __Array* actions = ((__Array*)  tolua_tousertype(tolua_S,2,0));
        Vector<FiniteTimeAction*> vec;
        array_to_vector_t_deprecated(*actions, vec);
        Sequence* tolua_ret = (Sequence*)  Sequence::create(vec);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Sequence");
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
    lua_pop(tolua_S, 1);
    
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
    size_t pos = strValue.find("CC");
    if (pos == 0 &&
        std::string::npos == strValue.find("CCBAnimationManager") &&
        std::string::npos == strValue.find("CCString") &&
        std::string::npos == strValue.find("CCPoint") &&
        std::string::npos == strValue.find("CCRect") &&
        std::string::npos == strValue.find("CCSize") &&
        std::string::npos == strValue.find("CCArray"))
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
        std::string castName = tolua_tostring(tolua_S,2,NULL);
        auto iter = g_typeCast.find(castName);
        if (iter != g_typeCast.end() )
        {
            CCLOG("Cast name %s doesn't include modular name which it belongs to,please add the modular name",iter->first.c_str());
            tolua_pushstring(tolua_S, iter->second.c_str());
            lua_insert(tolua_S, 2);
            lua_pop(tolua_S, 1);
        }
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
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Spawn");
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
    lua_pop(tolua_S, 1);
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
        __Array* arrayOfItems = ((__Array*)  tolua_tousertype(tolua_S,2,0));
        Vector<MenuItem*> vec;
        array_to_vector_t_deprecated(*arrayOfItems, vec);
        Menu* tolua_ret = (Menu*)  Menu::createWithArray(vec);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Menu");
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithArray'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Menu_alignItemsInColumnsWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
        __Array* rows = ((__Array*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignItemsInColumnsWithArray'", NULL);
#endif
        ValueVector valueVector;
        array_to_valuevector_deprecated(*rows, valueVector);
        self->alignItemsInColumnsWithArray(valueVector);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'alignItemsInColumnsWithArray'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Menu_alignItemsInRowsWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
        __Array* columns = ((__Array*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignItemsInRowsWithArray'", NULL);
#endif
        ValueVector valueVector;
        array_to_valuevector_deprecated(*columns, valueVector);
        self->alignItemsInRowsWithArray(valueVector);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'alignItemsInRowsWithArray'.",&tolua_err);
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
        tolua_function(tolua_S, "alignItemsInColumnsWithArray", tolua_cocos2d_Menu_alignItemsInColumnsWithArray00);
        tolua_function(tolua_S, "alignItemsInRowsWithArray", tolua_cocos2d_Menu_alignItemsInRowsWithArray00);
    }
    lua_pop(tolua_S, 1);
    return 1;
}

static int tolua_cocos2d_LayerMultiplex_createWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"LayerMultiplex",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        __Array* arrayOfLayers = ((__Array*)  tolua_tousertype(tolua_S,2,0));
        Vector<Layer*> vec;
        array_to_vector_t_deprecated(*arrayOfLayers, vec);
        LayerMultiplex* tolua_ret = (LayerMultiplex*)  LayerMultiplex::createWithArray(vec);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.LayerMultiplex");
        
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithArray'.",&tolua_err);
    return 0;
#endif
}

static int extendLayerMultiplexDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"LayerMultiplex");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithArray", tolua_cocos2d_LayerMultiplex_createWithArray00);
    }
    lua_pop(tolua_S, 1);
    return 1;
}


int register_all_cocos2dx_manual_deprecated(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    extendAnimationDeprecated(tolua_S);
    extendSequenceDeprecated(tolua_S);
    extendToluaDeprecated(tolua_S);
    extendMenuDeprecated(tolua_S);
    extendLayerMultiplexDeprecated(tolua_S);
    return 0;
}
