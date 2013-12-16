/* tolua
** Support code for Lua bindings.
** Written by Waldemar Celes
** TeCGraf/PUC-Rio
** Apr 2003
** $Id: $
*/

/* This code is free software; you can redistribute it and/or modify it.
** The software provided hereunder is on an "as is" basis, and
** the author has no obligation to provide maintenance, support, updates,
** enhancements, or modifications.
*/


#ifndef TOLUA_H
#define TOLUA_H

#ifndef TOLUA_API
#define TOLUA_API extern
#endif

#define TOLUA_VERSION "tolua++-1.0.93"

#ifdef __cplusplus
extern "C" {
#endif

#define tolua_pushcppstring(x,y)                tolua_pushstring(x,y.c_str())
#define tolua_iscppstring                       tolua_isstring

#define tolua_iscppstringarray                  tolua_isstringarray
#define tolua_pushfieldcppstring(L,lo,idx,s)    tolua_pushfieldstring(L, lo, idx, s.c_str())

#ifndef TEMPLATE_BIND
#define TEMPLATE_BIND(p)
#endif

#define TOLUA_TEMPLATE_BIND(p)

#define TOLUA_PROTECTED_DESTRUCTOR
#define TOLUA_PROPERTY_TYPE(p)
    
#define TOLUA_VALUE_ROOT "tolua_value_root"

typedef int lua_Object;

#include "lua.h"
#include "lauxlib.h"

struct tolua_Error
{
    int index;
    int array;
    const char* type;
};
typedef struct tolua_Error tolua_Error;

#define TOLUA_NOPEER    LUA_REGISTRYINDEX /* for lua 5.1 */

TOLUA_API const char* tolua_typename (lua_State* L, int lo);
TOLUA_API void tolua_error (lua_State* L, const char* msg, tolua_Error* err);
TOLUA_API int tolua_isnoobj (lua_State* L, int lo, tolua_Error* err);
TOLUA_API int tolua_isvalue (lua_State* L, int lo, int def, tolua_Error* err);
TOLUA_API int tolua_isvaluenil (lua_State* L, int lo, tolua_Error* err);
TOLUA_API int tolua_isboolean (lua_State* L, int lo, int def, tolua_Error* err);
TOLUA_API int tolua_isnumber (lua_State* L, int lo, int def, tolua_Error* err);
TOLUA_API int tolua_isstring (lua_State* L, int lo, int def, tolua_Error* err);
TOLUA_API int tolua_istable (lua_State* L, int lo, int def, tolua_Error* err);
TOLUA_API int tolua_isusertable (lua_State* L, int lo, const char* type, int def, tolua_Error* err);
TOLUA_API int tolua_isuserdata (lua_State* L, int lo, int def, tolua_Error* err);
TOLUA_API int tolua_isusertype (lua_State* L, int lo, const char* type, int def, tolua_Error* err);
TOLUA_API int tolua_isvaluearray
(lua_State* L, int lo, int dim, int def, tolua_Error* err);
TOLUA_API int tolua_isbooleanarray
(lua_State* L, int lo, int dim, int def, tolua_Error* err);
TOLUA_API int tolua_isnumberarray
(lua_State* L, int lo, int dim, int def, tolua_Error* err);
TOLUA_API int tolua_isstringarray
(lua_State* L, int lo, int dim, int def, tolua_Error* err);
TOLUA_API int tolua_istablearray
(lua_State* L, int lo, int dim, int def, tolua_Error* err);
TOLUA_API int tolua_isuserdataarray
(lua_State* L, int lo, int dim, int def, tolua_Error* err);
TOLUA_API int tolua_isusertypearray
(lua_State* L, int lo, const char* type, int dim, int def, tolua_Error* err);

TOLUA_API void tolua_open (lua_State* L);

TOLUA_API void* tolua_copy (lua_State* L, void* value, unsigned int size);
TOLUA_API int tolua_register_gc (lua_State* L, int lo);
TOLUA_API int tolua_default_collect (lua_State* tolua_S);

TOLUA_API void tolua_usertype (lua_State* L, const char* type);
TOLUA_API void tolua_beginmodule (lua_State* L, const char* name);
TOLUA_API void tolua_endmodule (lua_State* L);
TOLUA_API void tolua_module (lua_State* L, const char* name, int hasvar);
TOLUA_API void tolua_class (lua_State* L, const char* name, const char* base);
TOLUA_API void tolua_cclass (lua_State* L, const char* lname, const char* name, const char* base, lua_CFunction col);
TOLUA_API void tolua_function (lua_State* L, const char* name, lua_CFunction func);
TOLUA_API void tolua_constant (lua_State* L, const char* name, lua_Number value);
TOLUA_API void tolua_variable (lua_State* L, const char* name, lua_CFunction get, lua_CFunction set);
TOLUA_API void tolua_array (lua_State* L,const char* name, lua_CFunction get, lua_CFunction set);

/* TOLUA_API void tolua_set_call_event(lua_State* L, lua_CFunction func, char* type); */
TOLUA_API void tolua_addbase(lua_State* L, char* name, char* base);

TOLUA_API void tolua_pushvalue (lua_State* L, int lo);
TOLUA_API void tolua_pushboolean (lua_State* L, int value);
TOLUA_API void tolua_pushnumber (lua_State* L, lua_Number value);
TOLUA_API void tolua_pushstring (lua_State* L, const char* value);
TOLUA_API void tolua_pushuserdata (lua_State* L, void* value);
TOLUA_API void tolua_pushusertype (lua_State* L, void* value, const char* type);
TOLUA_API void tolua_pushusertype_and_takeownership(lua_State* L, void* value, const char* type);
TOLUA_API void tolua_pushfieldvalue (lua_State* L, int lo, int index, int v);
TOLUA_API void tolua_pushfieldboolean (lua_State* L, int lo, int index, int v);
TOLUA_API void tolua_pushfieldnumber (lua_State* L, int lo, int index, lua_Number v);
TOLUA_API void tolua_pushfieldstring (lua_State* L, int lo, int index, const char* v);
TOLUA_API void tolua_pushfielduserdata (lua_State* L, int lo, int index, void* v);
TOLUA_API void tolua_pushfieldusertype (lua_State* L, int lo, int index, void* v, const char* type);
TOLUA_API void tolua_pushfieldusertype_and_takeownership (lua_State* L, int lo, int index, void* v, const char* type);
    
TOLUA_API void tolua_pushusertype_and_addtoroot (lua_State* L, void* value, const char* type);
TOLUA_API void tolua_add_value_to_root (lua_State* L, void* value);
TOLUA_API void tolua_remove_value_from_root (lua_State* L, void* value);

TOLUA_API lua_Number tolua_tonumber (lua_State* L, int narg, lua_Number def);
TOLUA_API const char* tolua_tostring (lua_State* L, int narg, const char* def);
TOLUA_API void* tolua_touserdata (lua_State* L, int narg, void* def);
TOLUA_API void* tolua_tousertype (lua_State* L, int narg, void* def);
TOLUA_API int tolua_tovalue (lua_State* L, int narg, int def);
TOLUA_API int tolua_toboolean (lua_State* L, int narg, int def);
TOLUA_API lua_Number tolua_tofieldnumber (lua_State* L, int lo, int index, lua_Number def);
TOLUA_API const char* tolua_tofieldstring (lua_State* L, int lo, int index, const char* def);
TOLUA_API void* tolua_tofielduserdata (lua_State* L, int lo, int index, void* def);
TOLUA_API void* tolua_tofieldusertype (lua_State* L, int lo, int index, void* def);
TOLUA_API int tolua_tofieldvalue (lua_State* L, int lo, int index, int def);
TOLUA_API int tolua_getfieldboolean (lua_State* L, int lo, int index, int def);

TOLUA_API void tolua_dobuffer(lua_State* L, char* B, unsigned int size, const char* name);

TOLUA_API int class_gc_event (lua_State* L);

#ifdef __cplusplus
static inline const char* tolua_tocppstring (lua_State* L, int narg, const char* def) {

    const char* s = tolua_tostring(L, narg, def);
    return s?s:"";
};

static inline const char* tolua_tofieldcppstring (lua_State* L, int lo, int index, const char* def) {

    const char* s = tolua_tofieldstring(L, lo, index, def);
    return s?s:"";
};

#else
#define tolua_tocppstring tolua_tostring
#define tolua_tofieldcppstring tolua_tofieldstring
#endif

TOLUA_API int tolua_fast_isa(lua_State *L, int mt_indexa, int mt_indexb, int super_index);

#ifndef Mtolua_new
#define Mtolua_new(EXP) new EXP
#endif

#ifndef Mtolua_delete
#define Mtolua_delete(EXP) delete EXP
#endif

#ifndef Mtolua_new_dim
#define Mtolua_new_dim(EXP, len) new EXP[len]
#endif

#ifndef Mtolua_delete_dim
#define Mtolua_delete_dim(EXP) delete [] EXP
#endif

#ifndef tolua_outside
#define tolua_outside
#endif

#ifndef tolua_owned
#define tolua_owned
#endif

#ifdef __cplusplus
}
#endif

#endif
