#ifndef __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
#define __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__

extern "C" {
#include "lua.h"
#include "tolua++.h"
}

#include "cocos2d.h"

using namespace cocos2d;

extern std::map<long, std::string>  g_luaType;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err);
#endif

#define LUA_PRECONDITION( condition, ...) if( ! (condition) ) {														\
cocos2d::log("lua: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );                                                         \
cocos2d::log(__VA_ARGS__);                                                  \
}                                                                           \

extern bool luaval_is_usertype(lua_State* L,int lo,const char* type, int def);
// to native
extern bool luaval_to_int32(lua_State* L,int lo,int* outValue);
extern bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue);
extern bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue);
extern bool luaval_to_boolean(lua_State* L,int lo,bool* outValue);
extern bool luaval_to_number(lua_State* L,int lo,double* outValue);
extern bool luaval_to_long_long(lua_State* L,int lo,long long* outValue);
extern bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue);
extern bool luaval_to_long(lua_State* L,int lo, long* outValue);

extern bool luaval_to_point(lua_State* L,int lo,Point* outValue);
extern bool luaval_to_size(lua_State* L,int lo,Size* outValue);
extern bool luaval_to_rect(lua_State* L,int lo,Rect* outValue);
extern bool luaval_to_color3b(lua_State* L,int lo,Color3B* outValue);
extern bool luaval_to_color4b(lua_State* L,int lo,Color4B* outValue);
extern bool luaval_to_color4f(lua_State* L,int lo,Color4F* outValue);
extern bool luaval_to_affinetransform(lua_State* L,int lo, AffineTransform* outValue);
extern bool luaval_to_fontdefinition(lua_State* L, int lo, FontDefinition* outValue );
extern bool luaval_to_array(lua_State* L,int lo, Array** outValue);
extern bool luaval_to_dictionary(lua_State* L,int lo, Dictionary** outValue);
extern bool luaval_to_array_of_Point(lua_State* L,int lo,Point **points, int *numPoints);
extern bool luavals_variadic_to_array(lua_State* L,int argc, Array** ret);

// from native
extern void point_to_luaval(lua_State* L,const Point& pt);
extern void size_to_luaval(lua_State* L,const Size& sz);
extern void rect_to_luaval(lua_State* L,const Rect& rt);
extern void color3b_to_luaval(lua_State* L,const Color3B& cc);
extern void color4b_to_luaval(lua_State* L,const Color4B& cc);
extern void color4f_to_luaval(lua_State* L,const Color4F& cc);
extern void affinetransform_to_luaval(lua_State* L,const AffineTransform& inValue);
extern void fontdefinition_to_luaval(lua_State* L,const FontDefinition& inValue);
extern void array_to_luaval(lua_State* L,Array* inValue);
extern void dictionary_to_luaval(lua_State* L, Dictionary* dict);
#endif //__COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
