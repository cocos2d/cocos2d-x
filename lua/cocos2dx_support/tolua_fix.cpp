
#include "tolua_fix.h"
#include "CCObject.h"

using namespace cocos2d;

TOLUA_API void tolua_prepare_ccobject_table(lua_State* L)
{
    lua_pushstring(L, "tolua_refid_ptr_mapping");
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);
    
    lua_pushstring(L, "tolua_refid_type_mapping");
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);
}

TOLUA_API void tolua_pushusertype_ccobject(lua_State* L, int refid, int* p_refid, void* ptr, const char* type)
{
    if (*p_refid == 0)
    {
        *p_refid = refid;
        
        lua_pushstring(L, "tolua_refid_ptr_mapping");
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: refid_ptr */
        lua_pushinteger(L, refid);                                  /* stack: refid_ptr refid */
        lua_pushlightuserdata(L, ptr);                              /* stack: refid_ptr refid ptr */
        lua_rawset(L, -3);                  /* refid_ptr[refid] = ptr, stack: refid_ptr */
        lua_pop(L, 1);                                              /* stack: - */
        
        lua_pushstring(L, "tolua_refid_type_mapping");
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: refid_type */
        lua_pushinteger(L, refid);                                  /* stack: refid_type refid */
        lua_pushstring(L, type);                                    /* stack: refid_type refid type */
        lua_rawset(L, -3);                /* refid_type[refid] = type, stack: refid_type */
        lua_pop(L, 1);                                              /* stack: - */
        
//        printf("push ccobject() - refid: %d, ptr: %x, type: %s\n", *p_refid, (int)ptr, type);
    }
    else
    {
//        printf("push ccobject() - refid: %d, ptr: %x, type: %s, exists\n", *p_refid, (int)ptr, type);
    }
    
    tolua_pushusertype(L, ptr, type);
}

TOLUA_API void tolua_remove_ccobject_by_refid(lua_State* L, int refid)
{
    if (refid == 0) return;
    
    // get ptr from tolua_refid_ptr_mapping
    lua_pushstring(L, "tolua_refid_ptr_mapping");
    lua_rawget(L, LUA_REGISTRYINDEX);                               /* stack: refid_ptr */
    lua_pushinteger(L, refid);                                      /* stack: refid_ptr refid */
    lua_rawget(L, -2);                                              /* stack: refid_ptr ptr */
    void* ptr = lua_touserdata(L, -1);
    lua_pop(L, 1);                                                  /* stack: refid_ptr */
    if (ptr == NULL)
    {
        lua_pop(L, 1);
        printf("remove ccobject() error - refid: %d, ptr: NONE\n", refid);
        return;
    }
    
    // remove ptr from tolua_refid_ptr_mapping
    lua_pushinteger(L, refid);                                      /* stack: refid_ptr refid */
    lua_pushnil(L);                                                 /* stack: refid_ptr refid nil */
    lua_rawset(L, -3);                     /* delete refid_ptr[refid], stack: refid_ptr */
    lua_pop(L, 1);                                                  /* stack: - */
    
    
    // get type from tolua_refid_type_mapping
    lua_pushstring(L, "tolua_refid_type_mapping");
    lua_rawget(L, LUA_REGISTRYINDEX);                               /* stack: refid_type */
    lua_pushinteger(L, refid);                                      /* stack: refid_type refid */
    lua_rawget(L, -2);                                              /* stack: refid_type type */
    if (lua_isnil(L, -1))
    {
        lua_pop(L, 2);
        printf("remove ccobject() error - refid: %d, ptr: %x, type: NONE\n", refid, (int)ptr);
        return;
    }

    const char* type = lua_tostring(L, -1);
    lua_pop(L, 1);                                                  /* stack: refid_type */
    
    // remove type from tolua_refid_type_mapping
    lua_pushinteger(L, refid);                                      /* stack: refid_type refid */
    lua_pushnil(L);                                                 /* stack: refid_type refid nil */
    lua_rawset(L, -3);                    /* delete refid_type[refid], stack: refid_type */
    lua_pop(L, 1);                                                  /* stack: - */
    
    // get ubox
    luaL_getmetatable(L, type);                                     /* stack: mt */
    lua_pushstring(L, "tolua_ubox");                                /* stack: mt key */
    lua_rawget(L, -2);                                              /* stack: mt ubox */
    if (lua_isnil(L, -1))
    {
        // use global ubox
        lua_pop(L, 1);                                              /* stack: mt */
        lua_pushstring(L, "tolua_ubox");                            /* stack: mt key */
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: mt ubox */
    };

    lua_pushlightuserdata(L, ptr);                                  /* stack: mt ubox ptr */
    lua_rawget(L,-2);                                               /* stack: mt ubox ud */
    if (lua_isnil(L, -1))
    {
        // Lua object has released (GC), C++ object not in ubox.
//        printf("remove ccobject() error - refid: %d, ptr: %x, type: %s, ubox: NONE\n", refid, (int)ptr, type);
        lua_pop(L, 3);
        return;
    }
    
    void** ud = (void**)lua_touserdata(L, -1);
    lua_pop(L, 1);                                                  /* stack: mt ubox */
    if (ud == NULL)
    {
        printf("remove ccobject() error - refid: %d, ptr: %x, type: %s, userdata: NULL\n", refid, (int)ptr, type);
        lua_pop(L, 2);
        return;
    }
    
    // clean userdata
    *ud = NULL;
    
    lua_pushlightuserdata(L, ptr);                                  /* stack: mt ubox ptr */
    lua_pushnil(L);                                                 /* stack: mt ubox ptr nil */
    lua_rawset(L, -3);                             /* ubox[ptr] = nil, stack: mt ubox */

    lua_pop(L, 2);
//    printf("remove ccobject() - refid: %d, ptr: %x, type: %s OK\n", refid, (int)ptr, type);
}

TOLUA_API void tolua_remove_function_by_refid(lua_State* L, int refid)
{
    luaL_unref(L, LUA_REGISTRYINDEX, refid);
}

//TOLUA_API void tolua_remove_function_by_refid(lua_State* L, int refid)
//{
//    lua_rawgeti(L, LUA_REGISTRYINDEX, refid);                       /* stack: function */
//    if (!lua_isfunction(L, -1))
//    {
//        lua_pop(L, 1);
//        return;
//    }
//    
//    luaL_unref(L, LUA_REGISTRYINDEX, refid);
//
//    lua_pushstring(L, "tolua_function_ref_mapping");                /* stack: function key */
//    lua_rawget(L, LUA_REGISTRYINDEX);                               /* stack: function mapping */
//    lua_pushvalue(L, -2);                                           /* stack: function mapping function */
//    lua_pushnil(L);                                                 /* stack: function mapping function nil */
//    lua_rawset(L, -3);                     /* mapping[function] = nil, stack: function mapping */
//    lua_pop(L, 2);                                                  /* stack: - */
//}

extern "C" {

TOLUA_API int tolua_isfunction(lua_State* L, int lo, tolua_Error* err)
{
    if (lua_gettop(L) >= abs(lo) && lua_isfunction(L, lo))
    {
        return 1;
    }
    err->index = lo;
    err->array = 0;
    err->type = "[not function]";
    return 0;
}

TOLUA_API int tolua_ref_function(lua_State* L, int lo, int def)
{
    if (lua_gettop(L) < abs(lo)) return 0;
    lua_pushvalue(L, lo);                                           /* stack: ... function ... function */
    return luaL_ref(L, LUA_REGISTRYINDEX);                     /* stack: ... function ... */
}

//TOLUA_API int tolua_ref_function(lua_State* L, int lo, int def)
//{
//    if (lua_gettop(L) < abs(lo)) return 0;
//    
//    int ix = lo > 0 ? lo : lua_gettop(L) + lo + 1;
//    
//    lua_pushstring(L, "tolua_function_ref_mapping");                /* stack: ... function ... key */
//    lua_rawget(L, LUA_REGISTRYINDEX);                               /* stack: ... function ... mapping */
//    
//    lua_pushvalue(L, ix);                                           /* stack: ... function ... mapping function */
//    lua_rawget(L, -2);                                              /* stack: ... function ... mapping refid */
//    
//    int refid = 0;
//    if (lua_isnil(L, -1))
//    {
//        // refid not exists
//        lua_pop(L, 1);                                              /* stack: ... function ... mapping */
//        lua_pushvalue(L, ix);                                       /* stack: ... function ... mapping function */
//        refid = luaL_ref(L, LUA_REGISTRYINDEX);                     /* stack: ... function ... mapping */
//        lua_pushvalue(L, ix);                                       /* stack: ... function ... mapping function */
//        lua_pushinteger(L, refid);                                  /* stack: ... function ... mapping function refid */
//        lua_rawset(L, -3);               /* mapping[function] = refid, stack: ... function ... mapping */
//        lua_pop(L, 1);                                              /* stack: ... function ... */
//    }
//    else
//    {
//        refid = lua_tointeger(L, -1);
//        lua_pop(L, 2);                                              /* stack: ... function ... */
//    }
//
//    return refid;
//}

}
