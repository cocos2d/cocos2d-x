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
#ifndef __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
#define __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "tolua_fix.h"
}

#include "cocos2d.h"

using namespace cocos2d;

extern std::unordered_map<std::string, std::string>  g_luaType;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err);
#endif

#define LUA_PRECONDITION( condition, ...) if( ! (condition) ) {														\
cocos2d::log("lua: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );                                                         \
cocos2d::log(__VA_ARGS__);                                                  \
}                                                                           \

extern bool luaval_is_usertype(lua_State* L,int lo,const char* type, int def);
// to native
extern bool luaval_to_ushort(lua_State* L, int lo, unsigned short* outValue);
extern bool luaval_to_int32(lua_State* L,int lo,int* outValue);
extern bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue);
extern bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue);
extern bool luaval_to_boolean(lua_State* L,int lo,bool* outValue);
extern bool luaval_to_number(lua_State* L,int lo,double* outValue);
extern bool luaval_to_long_long(lua_State* L,int lo,long long* outValue);
extern bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue);
extern bool luaval_to_long(lua_State* L,int lo, long* outValue);
extern bool luaval_to_ssize(lua_State* L,int lo, ssize_t* outValue);

extern bool luaval_to_point(lua_State* L,int lo,Point* outValue);
extern bool luaval_to_size(lua_State* L,int lo,Size* outValue);
extern bool luaval_to_rect(lua_State* L,int lo,Rect* outValue);
extern bool luaval_to_color3b(lua_State* L,int lo,Color3B* outValue);
extern bool luaval_to_color4b(lua_State* L,int lo,Color4B* outValue);
extern bool luaval_to_color4f(lua_State* L,int lo,Color4F* outValue);
extern bool luaval_to_physics_material(lua_State* L,int lo, cocos2d::PhysicsMaterial* outValue);
extern bool luaval_to_affinetransform(lua_State* L,int lo, AffineTransform* outValue);
extern bool luaval_to_fontdefinition(lua_State* L, int lo, FontDefinition* outValue );
extern bool luaval_to_array(lua_State* L,int lo, Array** outValue);
extern bool luaval_to_dictionary(lua_State* L,int lo, Dictionary** outValue);
extern bool luaval_to_array_of_Point(lua_State* L,int lo,Point **points, int *numPoints);
extern bool luavals_variadic_to_array(lua_State* L,int argc, Array** ret);
extern bool luavals_variadic_to_ccvaluevector(lua_State* L, int argc, cocos2d::ValueVector* ret);

template <class T>
bool luavals_variadic_to_ccvector( lua_State* L, int argc, cocos2d::Vector<T>* ret)
{
    if (nullptr == L || argc == 0 )
        return false;
    
    bool ok = true;
    
    for (int i = 0; i < argc; i++)
    {
        if (lua_isuserdata(L, i + 2))
        {
            tolua_Error err;
            //Undo check
            if (!tolua_isusertype(L, i + 2, "Object", 0, &err))
            {
                ok = false;
                break;
            }
            T obj = static_cast<T>(tolua_tousertype(L, i + 2, nullptr));
            ret->pushBack(obj);
        }
    }
    
    return ok;
}

template <class T>
bool luaval_to_ccvector(lua_State* L, int lo , cocos2d::Vector<T>* ret)
{
    if (nullptr == L || nullptr == ret)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
        ok = false;
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            
            if (lua_isnil(L, -1) || !lua_isuserdata(L, -1))
            {
                lua_pop(L, 1);
                continue;
            }
            

            T cobj = static_cast<T>(tolua_tousertype(L, -1, NULL) );
            if (NULL != cobj)
                ret->pushBack(cobj);
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret);
bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret);

template <class T>
bool luaval_to_ccmap_string_key(lua_State* L, int lo, cocos2d::Map<std::string, T>* ret)
{
    if(nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        std::string stringKey = "";
        lua_pushnil(L);                                             /* first key L: lotable ..... nil */
        while ( 0 != lua_next(L, lo ) )                             /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                continue;
            }
            
            if (lua_isnil(L, -1) || !lua_isuserdata(L, -1))
            {
                lua_pop(L, 1);
                continue;
            }
            
            luaval_to_std_string(L, -2, &stringKey);
            T obj = static_cast<T>(tolua_tousertype(L, -1, NULL) );
            if (nullptr != obj)
                ret->insert(stringKey, obj);
                
            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
    }
    
    return ok;
}


extern bool luaval_to_ccvalue(lua_State* L, int lo, cocos2d::Value* ret);
extern bool luaval_to_ccvaluemap(lua_State* L, int lo, cocos2d::ValueMap* ret);
extern bool luaval_to_ccvaluemapintkey(lua_State* L, int lo, cocos2d::ValueMapIntKey* ret);
extern bool luaval_to_ccvaluevector(lua_State* L, int lo, cocos2d::ValueVector* ret);


// from native
extern void point_to_luaval(lua_State* L,const Point& pt);
extern void points_to_luaval(lua_State* L,const Point* pt, int count);
extern void size_to_luaval(lua_State* L,const Size& sz);
extern void rect_to_luaval(lua_State* L,const Rect& rt);
extern void color3b_to_luaval(lua_State* L,const Color3B& cc);
extern void color4b_to_luaval(lua_State* L,const Color4B& cc);
extern void color4f_to_luaval(lua_State* L,const Color4F& cc);
extern void physics_material_to_luaval(lua_State* L,const PhysicsMaterial& pm);
extern void physics_raycastinfo_to_luaval(lua_State* L, const PhysicsRayCastInfo& info);
extern void affinetransform_to_luaval(lua_State* L,const AffineTransform& inValue);
extern void fontdefinition_to_luaval(lua_State* L,const FontDefinition& inValue);
extern void array_to_luaval(lua_State* L,Array* inValue);
extern void dictionary_to_luaval(lua_State* L, Dictionary* dict);

template <class T>
void ccvector_to_luaval(lua_State* L,const cocos2d::Vector<T>& inValue)
{
    lua_newtable(L);
    
    if (nullptr == L)
        return;
    
    int indexTable = 1;
    for (const auto& obj : inValue)
    {
        if (nullptr == obj)
            continue;
        

        if (nullptr != dynamic_cast<cocos2d::Object *>(obj))
        {
            std::string typeName = typeid(*obj).name();
            auto iter = g_luaType.find(typeName);
            if (g_luaType.end() != iter)
            {
                lua_pushnumber(L, (lua_Number)indexTable);
                int ID = (obj) ? (int)obj->_ID : -1;
                int* luaID = (obj) ? &obj->_luaID : NULL;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)obj,iter->second.c_str());
                lua_rawset(L, -3);
                obj->retain();
                ++indexTable;
            }
        }
    }
}

template <class T>
void ccmap_string_key_to_luaval(lua_State* L, const cocos2d::Map<std::string, T>& v)
{
    lua_newtable(L);
    
    if(nullptr == L)
        return;
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        std::string key = iter->first;
        T obj = iter->second;
        if (nullptr != dynamic_cast<cocos2d::Object *>(obj))
        {
            std::string name = typeid(*obj).name();
            auto typeIter = g_luaType.find(name);
            if (g_luaType.end() != typeIter)
            {
                lua_pushstring(L, name.c_str());
                int ID = (obj) ? (int)obj->_ID : -1;
                int* luaID = (obj) ? &obj->_luaID : NULL;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)obj,typeIter->second.c_str());
                lua_rawset(L, -3);
            }
        }
    }
}

void ccvalue_to_luaval(lua_State* L,const cocos2d::Value& inValue);
void ccvaluemap_to_luaval(lua_State* L,const cocos2d::ValueMap& inValue);
void ccvaluemapintkey_to_luaval(lua_State* L, const cocos2d::ValueMapIntKey& inValue);
void ccvaluevector_to_luaval(lua_State* L, const cocos2d::ValueVector& inValue);
#endif //__COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
