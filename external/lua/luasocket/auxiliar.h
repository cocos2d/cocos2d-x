#ifndef AUXILIAR_H
#define AUXILIAR_H
/*=========================================================================*\
* Auxiliar routines for class hierarchy manipulation
* LuaSocket toolkit (but completely independent of other LuaSocket modules)
*
* A LuaSocket class is a name associated with Lua metatables. A LuaSocket 
* group is a name associated with a class. A class can belong to any number 
* of groups. This module provides the functionality to:
*
*   - create new classes 
*   - add classes to groups 
*   - set the class of objects
*   - check if an object belongs to a given class or group
*   - get the userdata associated to objects
*   - print objects in a pretty way
*
* LuaSocket class names follow the convention <module>{<class>}. Modules
* can define any number of classes and groups. The module tcp.c, for
* example, defines the classes tcp{master}, tcp{client} and tcp{server} and
* the groups tcp{client,server} and tcp{any}. Module functions can then
* perform type-checking on their arguments by either class or group.
*
* LuaSocket metatables define the __index metamethod as being a table. This
* table has one field for each method supported by the class, and a field
* "class" with the class name.
*
* The mapping from class name to the corresponding metatable and the
* reverse mapping are done using lauxlib. 
\*=========================================================================*/

#include "lua.h"
#include "lauxlib.h"

int auxiliar_open(lua_State *L);
void auxiliar_newclass(lua_State *L, const char *classname, luaL_Reg *func);
void auxiliar_add2group(lua_State *L, const char *classname, const char *group);
void auxiliar_setclass(lua_State *L, const char *classname, int objidx);
void *auxiliar_checkclass(lua_State *L, const char *classname, int objidx);
void *auxiliar_checkgroup(lua_State *L, const char *groupname, int objidx);
void *auxiliar_getclassudata(lua_State *L, const char *groupname, int objidx);
void *auxiliar_getgroupudata(lua_State *L, const char *groupname, int objidx);
int auxiliar_checkboolean(lua_State *L, int objidx);
int auxiliar_tostring(lua_State *L);
int auxiliar_typeerror(lua_State *L, int narg, const char *tname);

#endif /* AUXILIAR_H */
