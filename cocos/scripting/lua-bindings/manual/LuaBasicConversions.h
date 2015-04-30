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
}
#include "tolua_fix.h"
#include "cocos2d.h"

using namespace cocos2d;

extern std::unordered_map<std::string, std::string>  g_luaType;
extern std::unordered_map<std::string, std::string>  g_typeCast;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName = "");
#endif

#define LUA_PRECONDITION( condition, ...) if( ! (condition) ) {														\
cocos2d::log("lua: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );                                                         \
cocos2d::log(__VA_ARGS__);                                                  \
}                                                                           \

/**
 * @addtogroup lua
 * @{
 */

/**
 * If the typename of userdata at the given accepteable index of stack is equal to type it return true,otherwise return false .
 * If def != 0, lo could greater than the top index of stack, return value is true.
 * If the value of the given index is nil, retrun value also is true.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param type the typename used to judge.
 * @param def whether has default value.
 * @return Return true if the typename of userdata at the given accepteable index of stack is equal to type, otherwise return false.
 */
extern bool luaval_is_usertype(lua_State* L,int lo,const char* type, int def);
// to native

/**
 * @name luaval_to_native
 * The following function are all used to convert the Lua values at the given acceptable index to the corresponding c++ values.
 * If the Lua values can be converted the return value is true, otherwise return false.
 * If it happens error during the conversion process, it outputs the error msg in the console to provide infromation about the name of calling function, the typename of value at the given acceptable index, and so on.
 * @{
 **/


/**
 * Get a unsigned long value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_ulong(lua_State* L,int lo, unsigned long* outValue, const char* funcName="");

/**
 * Get a unsigned short value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the unsigned short value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_ushort(lua_State* L, int lo, unsigned short* outValue, const char* funcName = "");

/**
 * Get a int value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the int value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_int32(lua_State* L,int lo,int* outValue, const char* funcName = "");

/**
 * Get a unsigned int value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the unsigned int value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue, const char* funcName = "");

/**
 * Get a uint16_t value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false .
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the uint16_t value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue, const char* funcName = "");

/**
 * Get a boolean value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack has type boolean it returns true, otherwise returns false.
 * Any Lua value is different from false and nil, the value of conversion is true, otherwise the value is false.
 * If the lo is non-valid index, the value of coversion also is false.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the boolean value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_boolean(lua_State* L,int lo,bool* outValue, const char* funcName = "");

/**
 * Get a double value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the double value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_number(lua_State* L,int lo,double* outValue, const char* funcName = "");

/**
 * Get a long long value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the long long value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_long_long(lua_State* L,int lo,long long* outValue, const char* funcName = "");

/**
 * Get a std::string value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a string or a number convertible to a string it returns true, otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store std::string value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is is a string or a number convertible to a string, otherwise return false.
 */
extern bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue, const char* funcName = "");

/**
 * Get a long value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the long value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_long(lua_State* L,int lo, long* outValue, const char* funcName = "");

/**
 * Get a ssize_t value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a number or a string convertible to a number it returns true, otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to store the ssize_t value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a number or a string convertible to a number, otherwise return false.
 */
extern bool luaval_to_ssize(lua_State* L,int lo, ssize_t* outValue, const char* funcName = "");

/**
 * Get a Size object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `width` and `height` key and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Size object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_size(lua_State* L,int lo,Size* outValue, const char* funcName = "");

/**
 * Get a Rect object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`,`y`,`width` and `height` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Rect object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_rect(lua_State* L,int lo,Rect* outValue, const char* funcName = "");

/**
 * Get a Color3B object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `r`,`g` and `b` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Color3B object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_color3b(lua_State* L,int lo,Color3B* outValue, const char* funcName = "");

/**
 * Get a Color4B object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `r`,`g`, `b` and 'a' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Color4B object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_color4b(lua_State* L,int lo,Color4B* outValue, const char* funcName = "");

/**
 * Get a Color4F object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `r`,`g`, `b` and 'a' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Color4F object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_color4f(lua_State* L,int lo,Color4F* outValue, const char* funcName = "");
#if CC_USE_PHYSICS

/**
 * Get a PhysicsMaterial object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `density`,`restitution` and 'friction' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a cocos2d::PhysicsMaterial object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_physics_material(lua_State* L,int lo, cocos2d::PhysicsMaterial* outValue, const char* funcName = "");
#endif //#if CC_USE_PHYSICS

/**
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `a`, `b`, `c`, `d` , `tx` and `ty` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a AffineTransform object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_affinetransform(lua_State* L,int lo, AffineTransform* outValue, const char* funcName = "");

/**
 * Get a FontDefinition object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `fontName`, `fontSize`, `fontAlignmentH`, `fontAlignmentV` , `fontFillColor` ,`fontDimensions`, `shadowEnabled` and `strokeEnabled` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 * If the values about `shadowEnabled` and `strokeEnabled` are true, there would be more keys such as `shadowOffset`, `shadowBlur` ,`shadowOpacity`, `strokeColor`, and `strokeSize`.
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a FontDefinition object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_fontdefinition(lua_State* L, int lo, FontDefinition* outValue , const char* funcName = "");

/**
 * Get a Mat object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * The table is array-table which begin the index starts at 1.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Mat object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_mat4(lua_State* L, int lo, cocos2d::Mat4* outValue , const char* funcName = "");

/**
 * Get a __Array object value frome the given accpetable index of stack.
 * Because __Array is deprecated, so this function would be not called anymore.
 */
extern bool luaval_to_array(lua_State* L,int lo, __Array** outValue, const char* funcName = "");

/**
 * Get a __Dictionary object value from the given accpetable index of stack.
 * Because __Dictionary is deprecated, so this function would be not called anymore.
 */
extern bool luaval_to_dictionary(lua_State* L,int lo, __Dictionary** outValue, const char* funcName = "");

/**
 * Get a array of Vec2 object from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param points the pointer to a array of Vec2 object which stores the values from the Lua table.
 * @param numPoints a int pointer to store the size of a Vec2 object array.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_array_of_vec2(lua_State* L,int lo,cocos2d::Vec2 **points, int *numPoints, const char* funcName = "");

/**
 * Get a __Array object value by the argc numbers of Lua values in the stack.
 * Because __Array is deprecated, so this function would be not called anymore.
 */
extern bool luavals_variadic_to_array(lua_State* L,int argc, __Array** ret);

/**
 * Get a cocos2d::ValueVector object value by the argc numbers of Lua values in the stack.
 *
 * @param L the current lua_State.
 * @param argc the numbers of Lua values in the stack.
 * @param ret the pointer to a ValueVector object which stores the values from the Lua table.
 * @return Return false if argc equal to 0 or L equal to nullptr, otherwise return true.
 */
extern bool luavals_variadic_to_ccvaluevector(lua_State* L, int argc, cocos2d::ValueVector* ret);

/**
 * Get a Vec2 object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`,and 'y' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Vec2 object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_vec2(lua_State* L,int lo,cocos2d::Vec2* outValue, const char* funcName = "");

/**
 * Get a Vec3 object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, 'y' and `z` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Vec3 object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_vec3(lua_State* L,int lo,cocos2d::Vec3* outValue, const char* funcName = "");

/**
 * Get a Vec4 object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, 'y', `z` and `w` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Vec4 object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_vec4(lua_State* L,int lo,cocos2d::Vec4* outValue, const char* funcName = "");

/**
 * Get a BlendFunc object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `src` and 'dst' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a BlendFunc object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_blendfunc(lua_State* L, int lo, cocos2d::BlendFunc* outValue, const char* funcName = "");

/**
 * Get a TTFConfig object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `fontFilePath`, `fontSize`, `glyphs`, `customGlyphs`, `distanceFieldEnabled` and 'outlineSize' keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be given the default value.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a TTFConfig object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_ttfconfig(lua_State* L, int lo, cocos2d::TTFConfig* outValue, const char* funcName = "");

/**
 * Get a Uniform object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `location`, `size`, `type` and `name` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be given the default value.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a Uniform object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_uniform(lua_State* L, int lo, cocos2d::Uniform* outValue, const char* funcName = "");

/**
 * Get a VertexAttrib object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `index`, `size`, `type` and `name` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be given the default value.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a VertexAttrib object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_vertexattrib(lua_State* L, int lo, cocos2d::VertexAttrib* outValue, const char* funcName = "");


/**
 * Get a Vec2 object value from the given accpetable index of stack.
 * At current, the Point is typedef of Vec2.
 * @see luaval_to_vec2
 */
static inline bool luaval_to_point(lua_State* L,int lo,cocos2d::Vec2* outValue, const char* funcName = "")
{
    return luaval_to_vec2(L, lo, outValue);
}

CC_DEPRECATED_ATTRIBUTE static inline bool luaval_to_kmMat4(lua_State* L, int lo, cocos2d::Mat4* outValue , const char* funcName = "")
{
    return luaval_to_mat4(L, lo, outValue);
}
CC_DEPRECATED_ATTRIBUTE static inline bool luaval_to_array_of_Point(lua_State* L,int lo,cocos2d::Vec2 **points, int *numPoints, const char* funcName = "")
{
    return luaval_to_array_of_vec2(L, lo, points, numPoints);
}

/**
 * Get a cocos2d::Vector of type T objects by the argc numbers of Lua values in the stack.
 *
 * @param L the current lua_State.
 * @param argc the numbers of Lua values in the stack.
 * @param ret a cocos2d::Vector of type T objects.
 * @return Return false if argc equal to 0 , L equal to nullptr or the Lua userdata at the index isn't `cc.Ref` type, otherwise return true.
 */
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
            
            if (!tolua_isusertype(L, i + 2, "cc.Ref", 0, &err))
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


/**
 * Get a cocos2d::Vector of type T objects from a Lua table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a cocos2d::Vector of type T objects.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
template <class T>
bool luaval_to_ccvector(lua_State* L, int lo , cocos2d::Vector<T>* ret, const char* funcName = "")
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
        for (size_t i = 0; i < len; i++)
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

/**
 * Get a pointer points to a std::vector<std::string> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a std::vector<std::string>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<std::int> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a std::vector<int>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret, const char* funcName = "");


/**
 * Get a pointer points to a cocos2d::Map whose key/value pair is string value and T object from a Lua hash-map table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a cocos2d::Map whose key/value pair is string value and T object.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
template <class T>
bool luaval_to_ccmap_string_key(lua_State* L, int lo, cocos2d::Map<std::string, T>* ret, const char* funcName = "")
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

/**
 * Get a cocos2d::Value object from the given accpetable index of stack.
 * The type of Lua value at the index could be a Lua table, LUA_TSTRING, LUA_TBOOLEAN and LUA_TNUMBER.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a cocos2d::Value object.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the L and ret is not nullptr,otherwise return false.
 */
extern bool luaval_to_ccvalue(lua_State* L, int lo, cocos2d::Value* ret, const char* funcName = "");

/**
 * Get a cocos2d::ValueMap object from the given accpetable index of stack.
 * The type of Lua value at the index should be a Lua table.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a cocos2d::ValueMap object.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the type of Lua value at the index is a Lua table, otherwise return false.
 */
extern bool luaval_to_ccvaluemap(lua_State* L, int lo, cocos2d::ValueMap* ret, const char* funcName = "");

/**
 * Get a cocos2d::ValueMapIntKey object from the given accpetable index of stack.
 * The type of Lua value at the index should be a Lua table.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a cocos2d::ValueMapIntKey object.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the type of Lua value at the index is a Lua table, otherwise return false.
 */
extern bool luaval_to_ccvaluemapintkey(lua_State* L, int lo, cocos2d::ValueMapIntKey* ret, const char* funcName = "");

/**
 * Get a cocos2d::ValueVector object from the given accpetable index of stack.
 * The type of Lua value at the index should be a Lua array table.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a cocos2d::ValueVector object.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the type of Lua value at the index is a Lua table, otherwise return false.
 */
extern bool luaval_to_ccvaluevector(lua_State* L, int lo, cocos2d::ValueVector* ret, const char* funcName = "");


/**
 * Get a Type T object from the given accpetable index of stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param type a string pointer points to the type name.
 * @param ret the pointer points to a Type T object.
 * @return Return true if the type of Lua value at the index is a Lua userdata, otherwise return false.
 */
template <class T>
bool luaval_to_object(lua_State* L, int lo, const char* type, T** ret)
{
    if(nullptr == L || lua_gettop(L) < lo)
        return false;
    
    if (!luaval_is_usertype(L, lo, type, 0))
        return false;
    
    *ret = static_cast<T*>(tolua_tousertype(L, lo, 0));
    
    if (nullptr == ret)
        LUA_PRECONDITION(ret, "Invalid Native Object");
    
    return true;
}

/**
 * Get a cocos2d::MeshVertexAttrib object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `size`, `type`, `vertexAttrib`, `vertexAttrib` and `attribSizeBytes` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret the pointer to a cocos2d::MeshVertexAttrib object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_mesh_vertex_attrib(lua_State* L, int lo, cocos2d::MeshVertexAttrib* ret, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<float> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a std::vector<float>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_std_vector_float(lua_State* L, int lo, std::vector<float>* ret, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<unsigned shortt> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a std::vector<unsigned short>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_std_vector_ushort(lua_State* L, int lo, std::vector<unsigned short>* ret, const char* funcName = "");

/**
 * Get a cocos2d::Quaternion object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, `y`, `z` and `w` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.Otherwise, the value of members of outValue would be 0.
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a cocos2d::Quaternion object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_quaternion(lua_State* L,int lo,cocos2d::Quaternion* outValue, const char* funcName = "");

/**
 * Get a cocos2d::Texture2D::TexParams object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `minFilter`, `magFilter`, `wrapS` and `wrapT` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.Otherwise, the value of members of outValue would be 0.
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a cocos2d::Quaternion object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_texparams(lua_State* L,int lo,cocos2d::Texture2D::TexParams* outValue, const char* funcName = "");

/**
 * Get a cocos2d::V3F_C4B_T2F object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `vertices`, `colors`, and `texCoords` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a cocos2d::V3F_C4B_T2F object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_v3f_c4b_t2f(lua_State* L,int lo,cocos2d::V3F_C4B_T2F* outValue, const char* funcName = "");


/**
 * Get a cocos2d::Tex2F object value from the given accpetable index of stack.
 * If the value at the given accpetable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `u`, and `v` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue.Otherwise, the value of members of outValue would be 0.
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param outValue the pointer to a cocos2d::Tex2F object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_tex2f(lua_State* L, int lo, cocos2d::Tex2F* outValue, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<cocos2d::V3F_C4B_T2F> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a std::vector<cocos2d::V3F_C4B_T2F>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_std_vector_v3f_c4b_t2f(lua_State* L, int lo, std::vector<cocos2d::V3F_C4B_T2F>* ret, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<cocos2d::Vec2> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given accpetable index of stack.
 * @param ret a pointer points to a std::vector<cocos2d::Vec2>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given accpetable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_std_vector_vec2(lua_State* L, int lo, std::vector<cocos2d::Vec2>* ret, const char* funcName = "");

/**@}**/

// from native

/**
 * @name native_to_luaval
 * The following function are all used to convert native c++ values to the the corresponding Lua values,then push it into the Lua stack.
 *
 * @{
 **/

/**
 * Push a table converted from a cocos2d::Vec2 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2}
 *
 * @param L the current lua_State.
 * @param vec2  a cocos2d::Vec2 object.
 */
extern void vec2_to_luaval(lua_State* L,const cocos2d::Vec2& vec2);

/**
 * Push a table converted from a cocos2d::Vec3 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3}
 *
 * @param L the current lua_State.
 * @param vec3  a cocos2d::Vec3 object.
 */
extern void vec3_to_luaval(lua_State* L,const cocos2d::Vec3& vec3);

/**
 * Push a table converted from a cocos2d::Vec4 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3, w=numberValue4}
 *
 * @param L the current lua_State.
 * @param vec4  a cocos2d::Vec4 object.
 */
extern void vec4_to_luaval(lua_State* L,const cocos2d::Vec4& vec4);

/**
 * Push a table converted from a cocos2d::Vec2 array into the Lua stack.
 * The table size is count.
 * The format of table as follows: {vec2_table1,vec2_table2,...,vec2_tableCount}.
 *
 * @param L the current lua_State.
 * @param points a pointer points to a cocos2d::Vec2 array.
 * @param count the number of cocos2d::Vec2 object should be converted to a Lua table and push into the Lua stack.
 */
extern void vec2_array_to_luaval(lua_State* L,const cocos2d::Vec2* points, int count);

/**
 * Push a table converted from a cocos2d::Size object into the Lua stack.
 * The format of table as follows: {width=numberValue1, height=numberValue2}
 *
 * @param L the current lua_State.
 * @param sz  a cocos2d::Size object.
 */
extern void size_to_luaval(lua_State* L,const Size& sz);

/**
 * Push a table converted from a cocos2d::Rect object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, width=numberValue3, height=numberValue4}
 *
 * @param L the current lua_State.
 * @param rt  a cocos2d::Rect object.
 */
extern void rect_to_luaval(lua_State* L,const Rect& rt);

/**
 * Push a table converted from a cocos2d::Color3B object into the Lua stack.
 * The format of table as follows: {r=numberValue1, g=numberValue2, b=numberValue3}
 *
 * @param L the current lua_State.
 * @param cc  a cocos2d::Color3B object.
 */
extern void color3b_to_luaval(lua_State* L,const Color3B& cc);

/**
 * Push a table converted from a cocos2d::Color4B object into the Lua stack.
 * The format of table as follows: {r=numberValue1, g=numberValue2, b=numberValue3, a=numberValue4}
 *
 * @param L the current lua_State.
 * @param cc a cocos2d::Color4B object.
 */
extern void color4b_to_luaval(lua_State* L,const Color4B& cc);

/**
 * Push a table converted from a cocos2d::Color4F object into the Lua stack.
 * The format of table as follows: {r=numberValue1, g=numberValue2, b=numberValue3, a=numberValue4}
 *
 * @param L the current lua_State.
 * @param cc a cocos2d::Color4F object.
 */
extern void color4f_to_luaval(lua_State* L,const Color4F& cc);
#if CC_USE_PHYSICS

/**
 * Push a table converted from a cocos2d::PhysicsMaterial object into the Lua stack.
 * The format of table as follows: {density=numberValue1, restitution=numberValue2, friction=numberValue3}
 *
 * @param L the current lua_State.
 * @param pm a cocos2d::PhysicsMaterial object.
 */
extern void physics_material_to_luaval(lua_State* L,const PhysicsMaterial& pm);

/**
 * Push a table converted from a cocos2d::PhysicsRayCastInfo object into the Lua stack.
 * The format of table as follows: {shape=userdata, start=vec2_table1, ended=vec2_table2, contact=vec2_table3, normal=vec2_table4, fraction=numberValue}
 *
 * @param L the current lua_State.
 * @param info a cocos2d::PhysicsRayCastInfo object.
 */
extern void physics_raycastinfo_to_luaval(lua_State* L, const PhysicsRayCastInfo& info);

/**
 * Push a table converted from a cocos2d::PhysicsContactData object into the Lua stack.
 * The format of table as follows: {points=vec2_array_table, normal=vec2_table, POINT_MAX=numberValue}
 *
 * @param L the current lua_State.
 * @param data a cocos2d::PhysicsContactData object.
 */
extern void physics_contactdata_to_luaval(lua_State* L, const PhysicsContactData* data);
#endif //#if CC_USE_PHYSICS

/**
 * Push a table converted from a cocos2d::AffineTransform object into the Lua stack.
 * The format of table as follows: {a=numberValue1, b=numberValue2, c=numberValue3, d=numberValue4,tx=numberValue5, ty=numberValue6}
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::AffineTransform object.
 */
extern void affinetransform_to_luaval(lua_State* L,const AffineTransform& inValue);

/**
 * Push a table converted from a cocos2d::FontDefinition object into the Lua stack.
 * The format of table as follows: {fontName=stringValue1, fontSize=numberValue1, fontAlignmentH=numberValue2, fontAlignmentV=numberValue3,fontFillColor=color3b_table1, fontDimensions=size_table1, shadowEnabled=booleanValue1, shadowOffset=size_table2, shadowBlur=numberValue4, shadowOpacity=numberValue5, shadowEnabled=booleanValue2, strokeColor=color3b_table2, strokeSize=size_table3}
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::FontDefinition object.
 */
extern void fontdefinition_to_luaval(lua_State* L,const FontDefinition& inValue);

extern void array_to_luaval(lua_State* L, __Array* inValue);
extern void dictionary_to_luaval(lua_State* L, __Dictionary* dict);


/**
 * Push a table converted from a cocos2d::Mat4 object into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberValue16}
 *
 * @param L the current lua_State.
 * @param mat a cocos2d::Mat4 object.
 */
extern void mat4_to_luaval(lua_State* L, const cocos2d::Mat4& mat);

/**
 * Push a table converted from a cocos2d::BlendFunc object into the Lua stack.
 * The format of table as follows: {src=numberValue1, dst=numberValue2}
 *
 * @param L the current lua_State.
 * @param func a cocos2d::BlendFunc object.
 */
extern void blendfunc_to_luaval(lua_State* L, const cocos2d::BlendFunc& func);

/**
 * Push a table converted from a cocos2d::TTFConfig object into the Lua stack.
 * The format of table as follows: {fontFilePath=stringValue1, fontSize=numberValue1, glyphs=numberValue2, customGlyphs=stringValue2,distanceFieldEnabled=booleanValue1, outlineSize=numberValue3}
 *
 * @param L the current lua_State.
 * @param config a cocos2d::TTFConfig object.
 */
extern void ttfconfig_to_luaval(lua_State* L, const cocos2d::TTFConfig& config);

/**
 * Push a table converted from a cocos2d::Uniform object into the Lua stack.
 * The format of table as follows: {location=numberValue1, size=numberValue2, type=numberValue3, name=stringValue1}
 *
 * @param L the current lua_State.
 * @param uniform a cocos2d::Uniform object.
 */
extern void uniform_to_luaval(lua_State* L, const cocos2d::Uniform& uniform);

/**
 * Push a table converted from a cocos2d::VertexAttrib object into the Lua stack.
 * The format of table as follows: {index=numberValue1, size=numberValue2, type=numberValue3, name=stringValue1}
 *
 * @param L the current lua_State.
 * @param verAttrib a cocos2d::VertexAttrib object.
 */
extern void vertexattrib_to_luaval(lua_State* L, const cocos2d::VertexAttrib& verAttrib);


static inline void point_to_luaval(lua_State* L,const cocos2d::Vec2& pt)
{
    vec2_to_luaval(L, pt);
}


CC_DEPRECATED_ATTRIBUTE static inline void points_to_luaval(lua_State* L,const cocos2d::Vec2* points, int count)
{
    vec2_array_to_luaval(L, points, count);
}

/**
 * Push a table converted from a cocos2d::Vector object into the Lua stack.
 * The format of table as follows: {userdata1, userdata2, ..., userdataVectorSize}
 * The object in the cocos2d::Vector which would be pushed into the table should be Ref type.
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::Vector object.
 */
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
        

        if (nullptr != dynamic_cast<cocos2d::Ref *>(obj))
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
                ++indexTable;
            }
        }
    }
}

/**
 * Push a table converted from a cocos2d::Map object into the Lua stack.
 * The format of table as follows: {name1=userdata1, name2=userdata2, ..., nameMapSize=userdataMapSize}
 * The object in the cocos2d::Map which would be pushed into the table should be Ref type.
 *
 * @param L the current lua_State.
 * @param v a cocos2d::Map object.
 */
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
        if (nullptr != dynamic_cast<cocos2d::Ref *>(obj))
        {
            std::string name = typeid(*obj).name();
            auto typeIter = g_luaType.find(name);
            if (g_luaType.end() != typeIter)
            {
                lua_pushstring(L, key.c_str());
                int ID = (obj) ? (int)obj->_ID : -1;
                int* luaID = (obj) ? &obj->_luaID : NULL;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)obj,typeIter->second.c_str());
                lua_rawset(L, -3);
            }
        }
    }
}

/**
 * Push a Lua value converted from a cocos2d::Value object into the Lua stack.
 * Different cocos2d::Value type, different Lua value pushed into the Lua stack.
 * Value::Type::BOOLEAN -> push a boolean value into the Lua stack.
 * Value::Type::FLOAT,Value::Type::DOUBLE -> push a number value into the Lua stack.
 * Value::Type::INTEGER -> push a integer value into the Lua stack.
 * Value::Type::STRING -> push a string value into the Lua stack.
 * Value::Type::VECTOR -> push a array table into the Lua stack.
 * Value::Type::MAP  -> push a hash table into the Lua stack.
 * Value::Type::INT_KEY_MAP -> push a hash table into the Lua stack.
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::Value object.
 */
void ccvalue_to_luaval(lua_State* L,const cocos2d::Value& inValue);

/**
 * Push a Lua hash table converted from a cocos2d::ValueMap object into the Lua stack.
 * The type of value of the key/value pair would be boolean,number, integer, string, array table, hash table.
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::ValueMap object.
 */
void ccvaluemap_to_luaval(lua_State* L,const cocos2d::ValueMap& inValue);

/**
 * Push a Lua hash table converted from a cocos2d::ValueMapIntKey object into the Lua stack.
 * The type of value of the key/value pair would be boolean,number, integer, string, array table, hash table.
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::ValueMapIntKey object.
 */
void ccvaluemapintkey_to_luaval(lua_State* L, const cocos2d::ValueMapIntKey& inValue);

/**
 * Push a Lua array table converted from a cocos2d::ValueVector object into the Lua stack.
 * The type of value of the key/value pair would be boolean,number, integer, string, array table, hash table.
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::ValueVector object.
 */
void ccvaluevector_to_luaval(lua_State* L, const cocos2d::ValueVector& inValue);

/**@}**/

/**
 * Get the real typename for the specified typename.
 * Because all override functions wouldn't be bound,so we must use `typeid` to get the real class name.
 *
 * @param ret the pointer points to a type T object.
 * @param type the string pointer points to specified typename.
 * @return return the pointer points to the real typename, or nullptr.
 */
template <class T>
const char* getLuaTypeName(T* ret,const char* type)
{
    if (nullptr != ret)
    {
        std::string hashName = typeid(*ret).name();
        auto iter =  g_luaType.find(hashName);
        if(g_luaType.end() != iter)
        {
            return iter->second.c_str();
        }
        else
        {
            return type;
        }
    }
    
    return nullptr;
}

/**
 * Push the native object by userdata format into the Lua stack by typename.
 *
 * @param L the current lua_State.
 * @param type the string pointer points to the typename.
 * @param ret the native object pointer.
 */
template <class T>
void object_to_luaval(lua_State* L,const char* type, T* ret)
{
    if(nullptr != ret)
    {
        if (std::is_base_of<cocos2d::Ref, T>::value)
        {
            // use c style cast, T may not polymorphic
            cocos2d::Ref* dynObject = (cocos2d::Ref*)(ret);
            int ID = (int)(dynObject->_ID) ;
            int* luaID = &(dynObject->_luaID);
            toluafix_pushusertype_ccobject(L,ID, luaID, (void*)ret,type);
        }
        else
        {
            tolua_pushusertype(L,(void*)ret,getLuaTypeName(ret, type));
        }
    }
    else
    {
        lua_pushnil(L);
    }
}

/**
 * Push a table converted from a cocos2d::MeshVertexAttrib object into the Lua stack.
 * The format of table as follows: {size=numberValue1, type=numberValue2, vertexAttrib=numberValue3, attribSizeBytes=numberValue4}
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::MeshVertexAttrib object.
 */
void mesh_vertex_attrib_to_luaval(lua_State* L, const cocos2d::MeshVertexAttrib& inValue);

/**
 * Push a Lua array table converted from a std::vector<std::string> into the Lua stack.
 * The format of table as follows: {stringValue1, stringValue2, ..., stringVectorSize}
 *
 * @param L the current lua_State.
 * @param inValue a std::vector<std::string> value.
 */
void ccvector_std_string_to_luaval(lua_State* L, const std::vector<std::string>& inValue);

/**
 * Push a Lua array table converted from a std::vector<int> into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberVectorSize}
 *
 * @param L the current lua_State.
 * @param inValue a std::vector<int> vaule.
 */
void ccvector_int_to_luaval(lua_State* L, const std::vector<int>& inValue);

/**
 * Push a Lua array table converted from a std::vector<float> into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberVectorSize}
 *
 * @param L the current lua_State.
 * @param inValue a std::vector<float> vaule.
 */
void ccvector_float_to_luaval(lua_State* L, const std::vector<float>& inValue);

/**
 * Push a Lua array table converted from a std::vector<unsigned short> into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberVectorSize}
 *
 * @param L the current lua_State.
 * @param inValue a std::vector<float> vaule.
 */
void ccvector_ushort_to_luaval(lua_State* L, const std::vector<unsigned short>& inValue);

/**
 * Push a table converted from a cocos2d::Quaternion object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3, w=numberValue4}
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::Quaternion object.
 */
void quaternion_to_luaval(lua_State* L,const cocos2d::Quaternion& inValue);

/**
 * Push a table converted from a cocos2d::Texture2D::TexParams object into the Lua stack.
 * The format of table as follows: {minFilter=numberValue1, magFilter=numberValue2, wrapS=numberValue3, wrapT=numberValue4}
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::Texture2D::TexParams object.
 */
void texParams_to_luaval(lua_State* L, const cocos2d::Texture2D::TexParams& inValue);

// end group
/// @}
#endif //__COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
