/*
** Lua binding: player_luabinding
** Generated automatically by tolua++-1.0.92 on Tue Jun 24 17:11:04 2014.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_player_luabinding_open (lua_State* tolua_S);

#include <string>
#include <vector>
#include "PlayerProtocol.h"
#include "tolua_fix.h"
using namespace std;
using namespace player;
#define CLASS_HASH_CODE(x) x.hash_code()

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_std__vector_std__string_ (lua_State* tolua_S)
{
 std::vector<std::string>* self = (std::vector<std::string>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_PlayerMenuItem (lua_State* tolua_S)
{
 PlayerMenuItem* self = (PlayerMenuItem*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"LUA_FUNCTION");
 tolua_usertype(tolua_S,"PlayerMenuItem");
 tolua_usertype(tolua_S,"PlayerMessageBoxServiceProtocol");
 tolua_usertype(tolua_S,"PlayerMenuServiceProtocol");
 tolua_usertype(tolua_S,"PlayerFileDialogServiceProtocol");
 tolua_usertype(tolua_S,"PlayerProtocol");
 tolua_usertype(tolua_S,"std::vector<std::string>");
 tolua_usertype(tolua_S,"PlayerServiceProtocol");
}

/* method: getInstance of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getInstance00
static int tolua_player_luabinding_PlayerProtocol_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerProtocol* tolua_ret = (PlayerProtocol*)  PlayerProtocol::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerProtocol");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeInstance of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_purgeInstance00
static int tolua_player_luabinding_PlayerProtocol_purgeInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerProtocol::purgeInstance();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileDialogService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getFileDialogService00
static int tolua_player_luabinding_PlayerProtocol_getFileDialogService00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileDialogService'", NULL);
#endif
  {
   PlayerFileDialogServiceProtocol* tolua_ret = (PlayerFileDialogServiceProtocol*)  self->getFileDialogService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerFileDialogServiceProtocol");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileDialogService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMessageBoxService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getMessageBoxService00
static int tolua_player_luabinding_PlayerProtocol_getMessageBoxService00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMessageBoxService'", NULL);
#endif
  {
   PlayerMessageBoxServiceProtocol* tolua_ret = (PlayerMessageBoxServiceProtocol*)  self->getMessageBoxService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMessageBoxServiceProtocol");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMessageBoxService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMenuService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerProtocol_getMenuService00
static int tolua_player_luabinding_PlayerProtocol_getMenuService00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMenuService'", NULL);
#endif
  {
   PlayerMenuServiceProtocol* tolua_ret = (PlayerMenuServiceProtocol*)  self->getMenuService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuServiceProtocol");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMenuService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openFile of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerFileDialogServiceProtocol_openFile00
static int tolua_player_luabinding_PlayerFileDialogServiceProtocol_openFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const char* title = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* directory = ((const char*)  tolua_tostring(tolua_S,3,NULL));
  const char* extensions = ((const char*)  tolua_tostring(tolua_S,4,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openFile'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->openFile(title,directory,extensions);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openDirectory of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerFileDialogServiceProtocol_openDirectory00
static int tolua_player_luabinding_PlayerFileDialogServiceProtocol_openDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const char* title = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* directory = ((const char*)  tolua_tostring(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openDirectory'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->openDirectory(title,directory);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openMultiple of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerFileDialogServiceProtocol_openMultiple00
static int tolua_player_luabinding_PlayerFileDialogServiceProtocol_openMultiple00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const char* title = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* directory = ((const char*)  tolua_tostring(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openMultiple'", NULL);
#endif
  {
   std::vector<std::string> tolua_ret = (std::vector<std::string>)  self->openMultiple(title,directory);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((std::vector<std::string>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<std::string>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::vector<std::string>));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<std::string>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openMultiple'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: saveFile of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerFileDialogServiceProtocol_saveFile00
static int tolua_player_luabinding_PlayerFileDialogServiceProtocol_saveFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const char* title = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* filename = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* directory = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'saveFile'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->saveFile(title,filename,directory);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'saveFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_new00
static int tolua_player_luabinding_PlayerMenuItem_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  Mtolua_new((PlayerMenuItem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuItem");
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

/* method: new_local of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuItem_new00_local
static int tolua_player_luabinding_PlayerMenuItem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  Mtolua_new((PlayerMenuItem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuItem");
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

/* get function: itemId of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_PlayerMenuItem_itemId
static int tolua_get_PlayerMenuItem_itemId(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'itemId'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->itemId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: itemId of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_set_PlayerMenuItem_itemId
static int tolua_set_PlayerMenuItem_itemId(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'itemId'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->itemId = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: title of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_PlayerMenuItem_title
static int tolua_get_PlayerMenuItem_title(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'title'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->title);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: title of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_set_PlayerMenuItem_title
static int tolua_set_PlayerMenuItem_title(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'title'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->title = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isGroup of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_PlayerMenuItem_isGroup
static int tolua_get_PlayerMenuItem_isGroup(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isGroup'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isGroup);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isGroup of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_set_PlayerMenuItem_isGroup
static int tolua_set_PlayerMenuItem_isGroup(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isGroup'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isGroup = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isEnabled of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_PlayerMenuItem_isEnabled
static int tolua_get_PlayerMenuItem_isEnabled(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isEnabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isEnabled);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isEnabled of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_set_PlayerMenuItem_isEnabled
static int tolua_set_PlayerMenuItem_isEnabled(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isEnabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isEnabled = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isChecked of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_PlayerMenuItem_isChecked
static int tolua_get_PlayerMenuItem_isChecked(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isChecked'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isChecked);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isChecked of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_set_PlayerMenuItem_isChecked
static int tolua_set_PlayerMenuItem_isChecked(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isChecked'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isChecked = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: shortcut of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_PlayerMenuItem_shortcut
static int tolua_get_PlayerMenuItem_shortcut(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shortcut'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->shortcut);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: shortcut of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_set_PlayerMenuItem_shortcut
static int tolua_set_PlayerMenuItem_shortcut(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shortcut'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->shortcut = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scriptHandlerId of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_PlayerMenuItem_scriptHandlerId
static int tolua_get_PlayerMenuItem_scriptHandlerId(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scriptHandlerId'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->scriptHandlerId,"LUA_FUNCTION");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scriptHandlerId of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_set_PlayerMenuItem_scriptHandlerId
static int tolua_set_PlayerMenuItem_scriptHandlerId(lua_State* tolua_S)
{
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scriptHandlerId'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scriptHandlerId = (int)(  toluafix_ref_function(tolua_S,2,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_addItem00
static int tolua_player_luabinding_PlayerMenuServiceProtocol_addItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const PlayerMenuItem",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const PlayerMenuItem* item = ((const PlayerMenuItem*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   self->addItem(*item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_addItem01
static int tolua_player_luabinding_PlayerMenuServiceProtocol_addItem01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const PlayerMenuItem",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const PlayerMenuItem* item = ((const PlayerMenuItem*)  tolua_tousertype(tolua_S,2,0));
  std::string parentId = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  int index = ((int)  tolua_tonumber(tolua_S,4,MAX_INT));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   self->addItem(*item,parentId,index);
  }
 }
 return 0;
tolua_lerror:
 return tolua_player_luabinding_PlayerMenuServiceProtocol_addItem00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: modifyItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_modifyItem00
static int tolua_player_luabinding_PlayerMenuServiceProtocol_modifyItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const PlayerMenuItem",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const PlayerMenuItem* item = ((const PlayerMenuItem*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'modifyItem'", NULL);
#endif
  {
   self->modifyItem(*item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'modifyItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: deleteItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMenuServiceProtocol_deleteItem00
static int tolua_player_luabinding_PlayerMenuServiceProtocol_deleteItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const PlayerMenuItem",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const PlayerMenuItem* item = ((const PlayerMenuItem*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'deleteItem'", NULL);
#endif
  {
   self->deleteItem(*item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'deleteItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showMessageBox of class  PlayerMessageBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox00
static int tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMessageBoxServiceProtocol",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMessageBoxServiceProtocol* self = (PlayerMessageBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const char* title = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,3,0));
  MessageBoxButtonsType buttons = ((MessageBoxButtonsType) (int)  tolua_tonumber(tolua_S,4,MessageBoxOK));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showMessageBox'", NULL);
#endif
  {
   int tolua_ret = (int)  self->showMessageBox(title,message,buttons);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showMessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_player_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"PlayerProtocol","PlayerProtocol","",NULL);
  tolua_beginmodule(tolua_S,"PlayerProtocol");
   tolua_function(tolua_S,"getInstance",tolua_player_luabinding_PlayerProtocol_getInstance00);
   tolua_function(tolua_S,"purgeInstance",tolua_player_luabinding_PlayerProtocol_purgeInstance00);
   tolua_function(tolua_S,"getFileDialogService",tolua_player_luabinding_PlayerProtocol_getFileDialogService00);
   tolua_function(tolua_S,"getMessageBoxService",tolua_player_luabinding_PlayerProtocol_getMessageBoxService00);
   tolua_function(tolua_S,"getMenuService",tolua_player_luabinding_PlayerProtocol_getMenuService00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerFileDialogServiceProtocol","PlayerFileDialogServiceProtocol","PlayerServiceProtocol",NULL);
  tolua_beginmodule(tolua_S,"PlayerFileDialogServiceProtocol");
   tolua_function(tolua_S,"openFile",tolua_player_luabinding_PlayerFileDialogServiceProtocol_openFile00);
   tolua_function(tolua_S,"openDirectory",tolua_player_luabinding_PlayerFileDialogServiceProtocol_openDirectory00);
   tolua_function(tolua_S,"openMultiple",tolua_player_luabinding_PlayerFileDialogServiceProtocol_openMultiple00);
   tolua_function(tolua_S,"saveFile",tolua_player_luabinding_PlayerFileDialogServiceProtocol_saveFile00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"MAX_INT",MAX_INT);
  tolua_constant(tolua_S,"MIN_INT",MIN_INT);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PlayerMenuItem","PlayerMenuItem","",tolua_collect_PlayerMenuItem);
  #else
  tolua_cclass(tolua_S,"PlayerMenuItem","PlayerMenuItem","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PlayerMenuItem");
   tolua_function(tolua_S,"new",tolua_player_luabinding_PlayerMenuItem_new00);
   tolua_function(tolua_S,"new_local",tolua_player_luabinding_PlayerMenuItem_new00_local);
   tolua_function(tolua_S,".call",tolua_player_luabinding_PlayerMenuItem_new00_local);
   tolua_variable(tolua_S,"itemId",tolua_get_PlayerMenuItem_itemId,tolua_set_PlayerMenuItem_itemId);
   tolua_variable(tolua_S,"title",tolua_get_PlayerMenuItem_title,tolua_set_PlayerMenuItem_title);
   tolua_variable(tolua_S,"isGroup",tolua_get_PlayerMenuItem_isGroup,tolua_set_PlayerMenuItem_isGroup);
   tolua_variable(tolua_S,"isEnabled",tolua_get_PlayerMenuItem_isEnabled,tolua_set_PlayerMenuItem_isEnabled);
   tolua_variable(tolua_S,"isChecked",tolua_get_PlayerMenuItem_isChecked,tolua_set_PlayerMenuItem_isChecked);
   tolua_variable(tolua_S,"shortcut",tolua_get_PlayerMenuItem_shortcut,tolua_set_PlayerMenuItem_shortcut);
   tolua_variable(tolua_S,"scriptHandlerId",tolua_get_PlayerMenuItem_scriptHandlerId,tolua_set_PlayerMenuItem_scriptHandlerId);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerMenuServiceProtocol","PlayerMenuServiceProtocol","",NULL);
  tolua_beginmodule(tolua_S,"PlayerMenuServiceProtocol");
   tolua_function(tolua_S,"addItem",tolua_player_luabinding_PlayerMenuServiceProtocol_addItem00);
   tolua_function(tolua_S,"addItem",tolua_player_luabinding_PlayerMenuServiceProtocol_addItem01);
   tolua_function(tolua_S,"modifyItem",tolua_player_luabinding_PlayerMenuServiceProtocol_modifyItem00);
   tolua_function(tolua_S,"deleteItem",tolua_player_luabinding_PlayerMenuServiceProtocol_deleteItem00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"MessageBoxOK",MessageBoxOK);
  tolua_constant(tolua_S,"MessageBoxOKCancel",MessageBoxOKCancel);
  tolua_constant(tolua_S,"MessageBoxYesNo",MessageBoxYesNo);
  tolua_constant(tolua_S,"MessageBoxYesNoCancel",MessageBoxYesNoCancel);
  tolua_cclass(tolua_S,"PlayerMessageBoxServiceProtocol","PlayerMessageBoxServiceProtocol","PlayerServiceProtocol",NULL);
  tolua_beginmodule(tolua_S,"PlayerMessageBoxServiceProtocol");
   tolua_function(tolua_S,"showMessageBox",tolua_player_luabinding_PlayerMessageBoxServiceProtocol_showMessageBox00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_player_luabinding (lua_State* tolua_S) {
 return tolua_player_luabinding_open(tolua_S);
};
#endif

