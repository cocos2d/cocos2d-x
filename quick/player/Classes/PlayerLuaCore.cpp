/*
** Lua binding: PlayerLuaCore
** Generated automatically by tolua++-1.0.92 on Fri Nov 21 10:53:44 2014.
*/

#include "PlayerLuaCore.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include <string>
#include <vector>
#include "PlayerProtocol.h"
#include "tolua++.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
using namespace std;
using namespace player;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_PlayerSettings (lua_State* tolua_S)
{
 PlayerSettings* self = (PlayerSettings*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ProjectConfig (lua_State* tolua_S)
{
 ProjectConfig* self = (ProjectConfig*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_vector_string_ (lua_State* tolua_S)
{
 vector<string>* self = (vector<string>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_std__vector_std__string_ (lua_State* tolua_S)
{
 std::vector<std::string>* self = (std::vector<std::string>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 
 tolua_usertype(tolua_S,"PlayerEditBoxServiceProtocol");
 tolua_usertype(tolua_S,"cocos2d::Ref");
 tolua_usertype(tolua_S,"PlayerSettings");
 tolua_usertype(tolua_S,"PlayerTask");
 tolua_usertype(tolua_S,"PlayerServiceProtocol");
 tolua_usertype(tolua_S,"std::vector<std::string>");
 tolua_usertype(tolua_S,"PlayerMessageBoxServiceProtocol");
 tolua_usertype(tolua_S,"PlayerMenuItem");
 tolua_usertype(tolua_S,"vector<string>");
 tolua_usertype(tolua_S,"PlayerMenuServiceProtocol");
 tolua_usertype(tolua_S,"PlayerFileDialogServiceProtocol");
 tolua_usertype(tolua_S,"ProjectConfig");
 tolua_usertype(tolua_S,"PlayerTaskServiceProtocol");
 tolua_usertype(tolua_S,"PlayerProtocol");
}

/* method: clear of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string__clear00
static int tolua_PlayerLuaCore_vector_string__clear00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string__size00
static int tolua_PlayerLuaCore_vector_string__size00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<string>* self = (const vector<string>*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string___geti00
static int tolua_PlayerLuaCore_vector_string___geti00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<string>* self = (const vector<string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->operator[](index);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string___seti00
static int tolua_PlayerLuaCore_vector_string___seti00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  string tolua_value = ((string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](index) =  tolua_value;
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string___geti01
static int tolua_PlayerLuaCore_vector_string___geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   string tolua_ret = (string)  self->operator[](index);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_PlayerLuaCore_vector_string___geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string__push_back00
static int tolua_PlayerLuaCore_vector_string__push_back00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
  string val = ((string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'push_back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string__new00
static int tolua_PlayerLuaCore_vector_string__new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<string>* tolua_ret = (vector<string>*)  Mtolua_new((vector<string>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<string>");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string__new00_local
static int tolua_PlayerLuaCore_vector_string__new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<string>* tolua_ret = (vector<string>*)  Mtolua_new((vector<string>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<string>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_vector_string__delete00
static int tolua_PlayerLuaCore_vector_string__delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_new00
static int tolua_PlayerLuaCore_ProjectConfig_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ProjectConfig* tolua_ret = (ProjectConfig*)  Mtolua_new((ProjectConfig)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ProjectConfig");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_new00_local
static int tolua_PlayerLuaCore_ProjectConfig_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ProjectConfig* tolua_ret = (ProjectConfig*)  Mtolua_new((ProjectConfig)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ProjectConfig");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isWelcome of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isWelcome00
static int tolua_PlayerLuaCore_ProjectConfig_isWelcome00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isWelcome'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isWelcome();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isWelcome'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetToWelcome of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_resetToWelcome00
static int tolua_PlayerLuaCore_ProjectConfig_resetToWelcome00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetToWelcome'", NULL);
#endif
  {
   self->resetToWelcome();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetToWelcome'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetToCreator of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_resetToCreator00
static int tolua_PlayerLuaCore_ProjectConfig_resetToCreator00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetToCreator'", NULL);
#endif
  {
   self->resetToCreator();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetToCreator'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getProjectDir of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getProjectDir00
static int tolua_PlayerLuaCore_ProjectConfig_getProjectDir00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getProjectDir'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getProjectDir();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getProjectDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setProjectDir of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setProjectDir00
static int tolua_PlayerLuaCore_ProjectConfig_setProjectDir00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  const string projectDir = ((const string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setProjectDir'", NULL);
#endif
  {
   self->setProjectDir(projectDir);
   tolua_pushcppstring(tolua_S,(const char*)projectDir);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setProjectDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScriptFile of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getScriptFile00
static int tolua_PlayerLuaCore_ProjectConfig_getScriptFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScriptFile'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getScriptFile();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScriptFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScriptFileRealPath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getScriptFileRealPath00
static int tolua_PlayerLuaCore_ProjectConfig_getScriptFileRealPath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScriptFileRealPath'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getScriptFileRealPath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScriptFileRealPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScriptFile of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setScriptFile00
static int tolua_PlayerLuaCore_ProjectConfig_setScriptFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  const string scriptFile = ((const string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScriptFile'", NULL);
#endif
  {
   self->setScriptFile(scriptFile);
   tolua_pushcppstring(tolua_S,(const char*)scriptFile);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScriptFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWritablePath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getWritablePath00
static int tolua_PlayerLuaCore_ProjectConfig_getWritablePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWritablePath'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getWritablePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWritablePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWritableRealPath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getWritableRealPath00
static int tolua_PlayerLuaCore_ProjectConfig_getWritableRealPath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWritableRealPath'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getWritableRealPath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWritableRealPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWritablePath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setWritablePath00
static int tolua_PlayerLuaCore_ProjectConfig_setWritablePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  const string writablePath = ((const string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWritablePath'", NULL);
#endif
  {
   self->setWritablePath(writablePath);
   tolua_pushcppstring(tolua_S,(const char*)writablePath);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWritablePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPackagePath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getPackagePath00
static int tolua_PlayerLuaCore_ProjectConfig_getPackagePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPackagePath'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getPackagePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPackagePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNormalizedPackagePath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getNormalizedPackagePath00
static int tolua_PlayerLuaCore_ProjectConfig_getNormalizedPackagePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNormalizedPackagePath'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getNormalizedPackagePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNormalizedPackagePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPackagePath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setPackagePath00
static int tolua_PlayerLuaCore_ProjectConfig_setPackagePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  const string packagePath = ((const string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPackagePath'", NULL);
#endif
  {
   self->setPackagePath(packagePath);
   tolua_pushcppstring(tolua_S,(const char*)packagePath);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPackagePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addPackagePath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_addPackagePath00
static int tolua_PlayerLuaCore_ProjectConfig_addPackagePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  const string packagePath = ((const string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPackagePath'", NULL);
#endif
  {
   self->addPackagePath(packagePath);
   tolua_pushcppstring(tolua_S,(const char*)packagePath);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addPackagePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPackagePathArray of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getPackagePathArray00
static int tolua_PlayerLuaCore_ProjectConfig_getPackagePathArray00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPackagePathArray'", NULL);
#endif
  {
   vector<string> tolua_ret = (vector<string>)  self->getPackagePathArray();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((vector<string>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"vector<string>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(vector<string>));
     tolua_pushusertype(tolua_S,tolua_obj,"vector<string>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPackagePathArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLandscapeFrame of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isLandscapeFrame00
static int tolua_PlayerLuaCore_ProjectConfig_isLandscapeFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLandscapeFrame'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLandscapeFrame();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLandscapeFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPortraitFrame of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isPortraitFrame00
static int tolua_PlayerLuaCore_ProjectConfig_isPortraitFrame00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPortraitFrame'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPortraitFrame();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPortraitFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeFrameOrientation of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientation00
static int tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientation00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeFrameOrientation'", NULL);
#endif
  {
   self->changeFrameOrientation();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeFrameOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeFrameOrientationToPortait of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientationToPortait00
static int tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientationToPortait00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeFrameOrientationToPortait'", NULL);
#endif
  {
   self->changeFrameOrientationToPortait();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeFrameOrientationToPortait'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeFrameOrientationToLandscape of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientationToLandscape00
static int tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientationToLandscape00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeFrameOrientationToLandscape'", NULL);
#endif
  {
   self->changeFrameOrientationToLandscape();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeFrameOrientationToLandscape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrameScale of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getFrameScale00
static int tolua_PlayerLuaCore_ProjectConfig_getFrameScale00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrameScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFrameScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrameScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFrameScale of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setFrameScale00
static int tolua_PlayerLuaCore_ProjectConfig_setFrameScale00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  float frameScale = ((float)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFrameScale'", NULL);
#endif
  {
   self->setFrameScale(frameScale);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFrameScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isShowConsole of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isShowConsole00
static int tolua_PlayerLuaCore_ProjectConfig_isShowConsole00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isShowConsole'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isShowConsole();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isShowConsole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShowConsole of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setShowConsole00
static int tolua_PlayerLuaCore_ProjectConfig_setShowConsole00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  bool showConsole = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShowConsole'", NULL);
#endif
  {
   self->setShowConsole(showConsole);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShowConsole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLoadPrecompiledFramework of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isLoadPrecompiledFramework00
static int tolua_PlayerLuaCore_ProjectConfig_isLoadPrecompiledFramework00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLoadPrecompiledFramework'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLoadPrecompiledFramework();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLoadPrecompiledFramework'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLoadPrecompiledFramework of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setLoadPrecompiledFramework00
static int tolua_PlayerLuaCore_ProjectConfig_setLoadPrecompiledFramework00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  bool load = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLoadPrecompiledFramework'", NULL);
#endif
  {
   self->setLoadPrecompiledFramework(load);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLoadPrecompiledFramework'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isWriteDebugLogToFile of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isWriteDebugLogToFile00
static int tolua_PlayerLuaCore_ProjectConfig_isWriteDebugLogToFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isWriteDebugLogToFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isWriteDebugLogToFile();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isWriteDebugLogToFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWriteDebugLogToFile of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setWriteDebugLogToFile00
static int tolua_PlayerLuaCore_ProjectConfig_setWriteDebugLogToFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  bool writeDebugLogToFile = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWriteDebugLogToFile'", NULL);
#endif
  {
   self->setWriteDebugLogToFile(writeDebugLogToFile);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWriteDebugLogToFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDebugLogFilePath of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getDebugLogFilePath00
static int tolua_PlayerLuaCore_ProjectConfig_getDebugLogFilePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDebugLogFilePath'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getDebugLogFilePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDebugLogFilePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWindowOffset of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setWindowOffset00
static int tolua_PlayerLuaCore_ProjectConfig_setWindowOffset00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWindowOffset'", NULL);
#endif
  {
      self->setWindowOffset(cocos2d::Vec2(x,y));
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWindowOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDebuggerType of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_getDebuggerType00
static int tolua_PlayerLuaCore_ProjectConfig_getDebuggerType00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDebuggerType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDebuggerType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDebuggerType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDebuggerType of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_setDebuggerType00
static int tolua_PlayerLuaCore_ProjectConfig_setDebuggerType00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  int debuggerType = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebuggerType'", NULL);
#endif
  {
   self->setDebuggerType(debuggerType);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDebuggerType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: parseCommandLine of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_parseCommandLine00
static int tolua_PlayerLuaCore_ProjectConfig_parseCommandLine00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const vector<string>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  const vector<string>* args = ((const vector<string>*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'parseCommandLine'", NULL);
#endif
  {
   self->parseCommandLine(*args);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'parseCommandLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: makeCommandLine of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_makeCommandLine00
static int tolua_PlayerLuaCore_ProjectConfig_makeCommandLine00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
  unsigned int mask = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'makeCommandLine'", NULL);
#endif
  {
   string tolua_ret = (string)  self->makeCommandLine(mask);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'makeCommandLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isAppMenu of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isAppMenu00
static int tolua_PlayerLuaCore_ProjectConfig_isAppMenu00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isAppMenu'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isAppMenu();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isAppMenu'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isResizeWindow of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isResizeWindow00
static int tolua_PlayerLuaCore_ProjectConfig_isResizeWindow00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isResizeWindow'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isResizeWindow();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isResizeWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRetinaDisplay of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_isRetinaDisplay00
static int tolua_PlayerLuaCore_ProjectConfig_isRetinaDisplay00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRetinaDisplay'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRetinaDisplay();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRetinaDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: validate of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_validate00
static int tolua_PlayerLuaCore_ProjectConfig_validate00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ProjectConfig* self = (const ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'validate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->validate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'validate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dump of class  ProjectConfig */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_ProjectConfig_dump00
static int tolua_PlayerLuaCore_ProjectConfig_dump00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProjectConfig",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProjectConfig* self = (ProjectConfig*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dump'", NULL);
#endif
  {
   self->dump();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dump'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerSettings_new00
static int tolua_PlayerLuaCore_PlayerSettings_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerSettings",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerSettings* tolua_ret = (PlayerSettings*)  Mtolua_new((PlayerSettings)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerSettings");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerSettings_new00_local
static int tolua_PlayerLuaCore_PlayerSettings_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerSettings",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerSettings* tolua_ret = (PlayerSettings*)  Mtolua_new((PlayerSettings)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerSettings");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: openLastProject of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_get_PlayerSettings_openLastProject
static int tolua_get_PlayerSettings_openLastProject(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'openLastProject'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->openLastProject);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: openLastProject of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_set_PlayerSettings_openLastProject
static int tolua_set_PlayerSettings_openLastProject(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'openLastProject'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->openLastProject = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: offsetX of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_get_PlayerSettings_offsetX
static int tolua_get_PlayerSettings_offsetX(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->offsetX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: offsetX of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_set_PlayerSettings_offsetX
static int tolua_set_PlayerSettings_offsetX(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->offsetX = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: offsetY of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_get_PlayerSettings_offsetY
static int tolua_get_PlayerSettings_offsetY(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->offsetY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: offsetY of class  PlayerSettings */
#ifndef TOLUA_DISABLE_tolua_set_PlayerSettings_offsetY
static int tolua_set_PlayerSettings_offsetY(lua_State* tolua_S)
{
  PlayerSettings* self = (PlayerSettings*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->offsetY = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getInstance00
static int tolua_PlayerLuaCore_PlayerProtocol_getInstance00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeInstance of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_purgeInstance00
static int tolua_PlayerLuaCore_PlayerProtocol_purgeInstance00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlayerSettings of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_setPlayerSettings00
static int tolua_PlayerLuaCore_PlayerProtocol_setPlayerSettings00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const PlayerSettings",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
  const PlayerSettings* settings = ((const PlayerSettings*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlayerSettings'", NULL);
#endif
  {
   self->setPlayerSettings(*settings);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlayerSettings'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlayerSettings of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getPlayerSettings00
static int tolua_PlayerLuaCore_PlayerProtocol_getPlayerSettings00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerProtocol* self = (const PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlayerSettings'", NULL);
#endif
  {
   PlayerSettings tolua_ret = (PlayerSettings)  self->getPlayerSettings();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((PlayerSettings)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"PlayerSettings");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(PlayerSettings));
     tolua_pushusertype(tolua_S,tolua_obj,"PlayerSettings");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlayerSettings'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileDialogService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getFileDialogService00
static int tolua_PlayerLuaCore_PlayerProtocol_getFileDialogService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileDialogService'", NULL);
#endif
  {
   PlayerFileDialogServiceProtocol* tolua_ret = (PlayerFileDialogServiceProtocol*)  self->getFileDialogService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerFileDialogServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileDialogService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMessageBoxService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getMessageBoxService00
static int tolua_PlayerLuaCore_PlayerProtocol_getMessageBoxService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMessageBoxService'", NULL);
#endif
  {
   PlayerMessageBoxServiceProtocol* tolua_ret = (PlayerMessageBoxServiceProtocol*)  self->getMessageBoxService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMessageBoxServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMessageBoxService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMenuService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getMenuService00
static int tolua_PlayerLuaCore_PlayerProtocol_getMenuService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMenuService'", NULL);
#endif
  {
   PlayerMenuServiceProtocol* tolua_ret = (PlayerMenuServiceProtocol*)  self->getMenuService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerMenuServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMenuService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEditBoxService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getEditBoxService00
static int tolua_PlayerLuaCore_PlayerProtocol_getEditBoxService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEditBoxService'", NULL);
#endif
  {
   PlayerEditBoxServiceProtocol* tolua_ret = (PlayerEditBoxServiceProtocol*)  self->getEditBoxService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerEditBoxServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEditBoxService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTaskService of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getTaskService00
static int tolua_PlayerLuaCore_PlayerProtocol_getTaskService00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTaskService'", NULL);
#endif
  {
   PlayerTaskServiceProtocol* tolua_ret = (PlayerTaskServiceProtocol*)  self->getTaskService();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerTaskServiceProtocol");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTaskService'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: quit of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_quit00
static int tolua_PlayerLuaCore_PlayerProtocol_quit00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'quit'", NULL);
#endif
  {
   self->quit();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'quit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: relaunch of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_relaunch00
static int tolua_PlayerLuaCore_PlayerProtocol_relaunch00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'relaunch'", NULL);
#endif
  {
   self->relaunch();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'relaunch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openNewPlayer of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_openNewPlayer00
static int tolua_PlayerLuaCore_PlayerProtocol_openNewPlayer00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openNewPlayer'", NULL);
#endif
  {
   self->openNewPlayer();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openNewPlayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openNewPlayerWithProjectConfig of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_openNewPlayerWithProjectConfig00
static int tolua_PlayerLuaCore_PlayerProtocol_openNewPlayerWithProjectConfig00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ProjectConfig",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
  ProjectConfig config = *((ProjectConfig*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openNewPlayerWithProjectConfig'", NULL);
#endif
  {
   self->openNewPlayerWithProjectConfig(config);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openNewPlayerWithProjectConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openProjectWithProjectConfig of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_openProjectWithProjectConfig00
static int tolua_PlayerLuaCore_PlayerProtocol_openProjectWithProjectConfig00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ProjectConfig",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerProtocol* self = (PlayerProtocol*)  tolua_tousertype(tolua_S,1,0);
  ProjectConfig config = *((ProjectConfig*)  tolua_tousertype(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openProjectWithProjectConfig'", NULL);
#endif
  {
   self->openProjectWithProjectConfig(config);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openProjectWithProjectConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPositionX of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getPositionX00
static int tolua_PlayerLuaCore_PlayerProtocol_getPositionX00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPositionX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPositionX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPositionX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPositionY of class  PlayerProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerProtocol_getPositionY00
static int tolua_PlayerLuaCore_PlayerProtocol_getPositionY00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
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
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPositionY'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPositionY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPositionY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openFile of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openFile00
static int tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string directory = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string extensions = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openFile'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->openFile(title,directory,extensions);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)directory);
   tolua_pushcppstring(tolua_S,(const char*)extensions);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openMultiple of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openMultiple00
static int tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openMultiple00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerFileDialogServiceProtocol* self = (const PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string directory = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string extensions = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openMultiple'", NULL);
#endif
  {
   std::vector<std::string> tolua_ret = (std::vector<std::string>)  self->openMultiple(title,directory,extensions);
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
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)directory);
   tolua_pushcppstring(tolua_S,(const char*)extensions);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openMultiple'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: saveFile of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_saveFile00
static int tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_saveFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'saveFile'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->saveFile(title,path);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)path);
  }
 }
 return 3;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'saveFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openDirectory of class  PlayerFileDialogServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openDirectory00
static int tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openDirectory00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerFileDialogServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerFileDialogServiceProtocol* self = (PlayerFileDialogServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string directory = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openDirectory'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->openDirectory(title,directory);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)directory);
  }
 }
 return 3;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMenuId of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_getMenuId00
static int tolua_PlayerLuaCore_PlayerMenuItem_getMenuId00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMenuId'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getMenuId();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMenuId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitle of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_getTitle00
static int tolua_PlayerLuaCore_PlayerMenuItem_getTitle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitle'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getTitle();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOrder of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_getOrder00
static int tolua_PlayerLuaCore_PlayerMenuItem_getOrder00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOrder'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isGroup of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_isGroup00
static int tolua_PlayerLuaCore_PlayerMenuItem_isGroup00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isGroup'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isGroup();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_isEnabled00
static int tolua_PlayerLuaCore_PlayerMenuItem_isEnabled00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isChecked of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_isChecked00
static int tolua_PlayerLuaCore_PlayerMenuItem_isChecked00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isChecked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isChecked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getShortcut of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_getShortcut00
static int tolua_PlayerLuaCore_PlayerMenuItem_getShortcut00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerMenuItem* self = (const PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getShortcut'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getShortcut();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getShortcut'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitle of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_setTitle00
static int tolua_PlayerLuaCore_PlayerMenuItem_setTitle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitle'", NULL);
#endif
  {
   self->setTitle(title);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEnabled of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_setEnabled00
static int tolua_PlayerLuaCore_PlayerMenuItem_setEnabled00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(enabled);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setChecked of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_setChecked00
static int tolua_PlayerLuaCore_PlayerMenuItem_setChecked00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
  bool checked = ((bool)  tolua_toboolean(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setChecked'", NULL);
#endif
  {
   self->setChecked(checked);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShortcut of class  PlayerMenuItem */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuItem_setShortcut00
static int tolua_PlayerLuaCore_PlayerMenuItem_setShortcut00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuItem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuItem* self = (PlayerMenuItem*)  tolua_tousertype(tolua_S,1,0);
  const std::string shortcut = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShortcut'", NULL);
#endif
  {
   self->setShortcut(shortcut);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShortcut'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem00
static int tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string parentId = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  self->addItem(menuId,title,parentId);
    int nID = (tolua_ret) ? tolua_ret->_ID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PlayerMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)menuId);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)parentId);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem01
static int tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string parentId = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  int order = ((int)  tolua_tonumber(tolua_S,5,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  self->addItem(menuId,title,parentId,order);
    int nID = (tolua_ret) ? tolua_ret->_ID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PlayerMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)menuId);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)parentId);
  }
 }
 return 4;
tolua_lerror:
 return tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem02
static int tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addItem'", NULL);
#endif
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  self->addItem(menuId,title);
    int nID = (tolua_ret) ? tolua_ret->_ID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PlayerMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)menuId);
   tolua_pushcppstring(tolua_S,(const char*)title);
  }
 }
 return 3;
tolua_lerror:
 return tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuServiceProtocol_getItem00
static int tolua_PlayerLuaCore_PlayerMenuServiceProtocol_getItem00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getItem'", NULL);
#endif
  {
   PlayerMenuItem* tolua_ret = (PlayerMenuItem*)  self->getItem(menuId);
    int nID = (tolua_ret) ? tolua_ret->_ID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PlayerMenuItem");
   tolua_pushcppstring(tolua_S,(const char*)menuId);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeItem of class  PlayerMenuServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMenuServiceProtocol_removeItem00
static int tolua_PlayerLuaCore_PlayerMenuServiceProtocol_removeItem00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMenuServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMenuServiceProtocol* self = (PlayerMenuServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string menuId = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeItem'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeItem(menuId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)menuId);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showMessageBox of class  PlayerMessageBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMessageBoxServiceProtocol_showMessageBox00
static int tolua_PlayerLuaCore_PlayerMessageBoxServiceProtocol_showMessageBox00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMessageBoxServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerMessageBoxServiceProtocol* self = (PlayerMessageBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string message = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showMessageBox'", NULL);
#endif
  {
   int tolua_ret = (int)  self->showMessageBox(title,message);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)message);
  }
 }
 return 3;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showMessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showMessageBox of class  PlayerMessageBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerMessageBoxServiceProtocol_showMessageBox01
static int tolua_PlayerLuaCore_PlayerMessageBoxServiceProtocol_showMessageBox01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerMessageBoxServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  PlayerMessageBoxServiceProtocol* self = (PlayerMessageBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string title = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string message = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  int buttonsType = ((int)  tolua_tonumber(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showMessageBox'", NULL);
#endif
  {
   int tolua_ret = (int)  self->showMessageBox(title,message,buttonsType);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)title);
   tolua_pushcppstring(tolua_S,(const char*)message);
  }
 }
 return 3;
tolua_lerror:
 return tolua_PlayerLuaCore_PlayerMessageBoxServiceProtocol_showMessageBox00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_getName00
static int tolua_PlayerLuaCore_PlayerTask_getName00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getExecutePath of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_getExecutePath00
static int tolua_PlayerLuaCore_PlayerTask_getExecutePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getExecutePath'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getExecutePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getExecutePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCommandLineArguments of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_getCommandLineArguments00
static int tolua_PlayerLuaCore_PlayerTask_getCommandLineArguments00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCommandLineArguments'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getCommandLineArguments();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCommandLineArguments'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOutput of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_getOutput00
static int tolua_PlayerLuaCore_PlayerTask_getOutput00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOutput'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getOutput();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOutput'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getState of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_getState00
static int tolua_PlayerLuaCore_PlayerTask_getState00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getState'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isIdle of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_isIdle00
static int tolua_PlayerLuaCore_PlayerTask_isIdle00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isIdle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isIdle();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isIdle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRunning of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_isRunning00
static int tolua_PlayerLuaCore_PlayerTask_isRunning00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRunning'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRunning();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRunning'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCompleted of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_isCompleted00
static int tolua_PlayerLuaCore_PlayerTask_isCompleted00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCompleted'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCompleted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCompleted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLifetime of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_getLifetime00
static int tolua_PlayerLuaCore_PlayerTask_getLifetime00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLifetime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getLifetime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLifetime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getResultCode of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_getResultCode00
static int tolua_PlayerLuaCore_PlayerTask_getResultCode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PlayerTask* self = (const PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResultCode'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getResultCode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getResultCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: run of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_run00
static int tolua_PlayerLuaCore_PlayerTask_run00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerTask* self = (PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'run'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->run();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_stop00
static int tolua_PlayerLuaCore_PlayerTask_stop00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerTask* self = (PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: runInTerminal of class  PlayerTask */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTask_runInTerminal00
static int tolua_PlayerLuaCore_PlayerTask_runInTerminal00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerTask",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerTask* self = (PlayerTask*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runInTerminal'", NULL);
#endif
  {
   self->runInTerminal();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'runInTerminal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createTask of class  PlayerTaskServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTaskServiceProtocol_createTask00
static int tolua_PlayerLuaCore_PlayerTaskServiceProtocol_createTask00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerTaskServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerTaskServiceProtocol* self = (PlayerTaskServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string executePath = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string commandLineArguments = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createTask'", NULL);
#endif
  {
   PlayerTask* tolua_ret = (PlayerTask*)  self->createTask(name,executePath,commandLineArguments);
    int nID = (tolua_ret) ? tolua_ret->_ID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PlayerTask");
   tolua_pushcppstring(tolua_S,(const char*)name);
   tolua_pushcppstring(tolua_S,(const char*)executePath);
   tolua_pushcppstring(tolua_S,(const char*)commandLineArguments);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTask of class  PlayerTaskServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTaskServiceProtocol_getTask00
static int tolua_PlayerLuaCore_PlayerTaskServiceProtocol_getTask00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerTaskServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerTaskServiceProtocol* self = (PlayerTaskServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTask'", NULL);
#endif
  {
   PlayerTask* tolua_ret = (PlayerTask*)  self->getTask(name);
    int nID = (tolua_ret) ? tolua_ret->_ID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PlayerTask");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTask of class  PlayerTaskServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerTaskServiceProtocol_removeTask00
static int tolua_PlayerLuaCore_PlayerTaskServiceProtocol_removeTask00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerTaskServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerTaskServiceProtocol* self = (PlayerTaskServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTask'", NULL);
#endif
  {
   self->removeTask(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hide of class  PlayerEditBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_hide00
static int tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_hide00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerEditBoxServiceProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerEditBoxServiceProtocol* self = (PlayerEditBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hide'", NULL);
#endif
  {
   self->hide();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  PlayerEditBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setText00
static int tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setText00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerEditBoxServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerEditBoxServiceProtocol* self = (PlayerEditBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFont of class  PlayerEditBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setFont00
static int tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setFont00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerEditBoxServiceProtocol",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerEditBoxServiceProtocol* self = (PlayerEditBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int size = ((int)  tolua_tonumber(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFont'", NULL);
#endif
  {
   self->setFont(name,size);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFormator of class  PlayerEditBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setFormator00
static int tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setFormator00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerEditBoxServiceProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerEditBoxServiceProtocol* self = (PlayerEditBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  int formator = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFormator'", NULL);
#endif
  {
   self->setFormator(formator);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFormator'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerHandler of class  PlayerEditBoxServiceProtocol */
#ifndef TOLUA_DISABLE_tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_registerHandler00
static int tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_registerHandler00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerEditBoxServiceProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerEditBoxServiceProtocol* self = (PlayerEditBoxServiceProtocol*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerHandler'", NULL);
#endif
  {
   self->registerHandler(handler);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_PlayerLuaCore_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"vector_string_","vector<string>","",tolua_collect_vector_string_);
  #else
  tolua_cclass(tolua_S,"vector_string_","vector<string>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"vector_string_");
   tolua_function(tolua_S,"clear",tolua_PlayerLuaCore_vector_string__clear00);
   tolua_function(tolua_S,"size",tolua_PlayerLuaCore_vector_string__size00);
   tolua_function(tolua_S,".geti",tolua_PlayerLuaCore_vector_string___geti00);
   tolua_function(tolua_S,".seti",tolua_PlayerLuaCore_vector_string___seti00);
   tolua_function(tolua_S,".geti",tolua_PlayerLuaCore_vector_string___geti01);
   tolua_function(tolua_S,"push_back",tolua_PlayerLuaCore_vector_string__push_back00);
   tolua_function(tolua_S,"new",tolua_PlayerLuaCore_vector_string__new00);
   tolua_function(tolua_S,"new_local",tolua_PlayerLuaCore_vector_string__new00_local);
   tolua_function(tolua_S,".call",tolua_PlayerLuaCore_vector_string__new00_local);
   tolua_function(tolua_S,"delete",tolua_PlayerLuaCore_vector_string__delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ProjectConfig","ProjectConfig","",tolua_collect_ProjectConfig);
  #else
  tolua_cclass(tolua_S,"ProjectConfig","ProjectConfig","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ProjectConfig");
   tolua_function(tolua_S,"new",tolua_PlayerLuaCore_ProjectConfig_new00);
   tolua_function(tolua_S,"new_local",tolua_PlayerLuaCore_ProjectConfig_new00_local);
   tolua_function(tolua_S,".call",tolua_PlayerLuaCore_ProjectConfig_new00_local);
   tolua_function(tolua_S,"isWelcome",tolua_PlayerLuaCore_ProjectConfig_isWelcome00);
   tolua_function(tolua_S,"resetToWelcome",tolua_PlayerLuaCore_ProjectConfig_resetToWelcome00);
   tolua_function(tolua_S,"resetToCreator",tolua_PlayerLuaCore_ProjectConfig_resetToCreator00);
   tolua_function(tolua_S,"getProjectDir",tolua_PlayerLuaCore_ProjectConfig_getProjectDir00);
   tolua_function(tolua_S,"setProjectDir",tolua_PlayerLuaCore_ProjectConfig_setProjectDir00);
   tolua_function(tolua_S,"getScriptFile",tolua_PlayerLuaCore_ProjectConfig_getScriptFile00);
   tolua_function(tolua_S,"getScriptFileRealPath",tolua_PlayerLuaCore_ProjectConfig_getScriptFileRealPath00);
   tolua_function(tolua_S,"setScriptFile",tolua_PlayerLuaCore_ProjectConfig_setScriptFile00);
   tolua_function(tolua_S,"getWritablePath",tolua_PlayerLuaCore_ProjectConfig_getWritablePath00);
   tolua_function(tolua_S,"getWritableRealPath",tolua_PlayerLuaCore_ProjectConfig_getWritableRealPath00);
   tolua_function(tolua_S,"setWritablePath",tolua_PlayerLuaCore_ProjectConfig_setWritablePath00);
   tolua_function(tolua_S,"getPackagePath",tolua_PlayerLuaCore_ProjectConfig_getPackagePath00);
   tolua_function(tolua_S,"getNormalizedPackagePath",tolua_PlayerLuaCore_ProjectConfig_getNormalizedPackagePath00);
   tolua_function(tolua_S,"setPackagePath",tolua_PlayerLuaCore_ProjectConfig_setPackagePath00);
   tolua_function(tolua_S,"addPackagePath",tolua_PlayerLuaCore_ProjectConfig_addPackagePath00);
   tolua_function(tolua_S,"getPackagePathArray",tolua_PlayerLuaCore_ProjectConfig_getPackagePathArray00);
   tolua_function(tolua_S,"isLandscapeFrame",tolua_PlayerLuaCore_ProjectConfig_isLandscapeFrame00);
   tolua_function(tolua_S,"isPortraitFrame",tolua_PlayerLuaCore_ProjectConfig_isPortraitFrame00);
   tolua_function(tolua_S,"changeFrameOrientation",tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientation00);
   tolua_function(tolua_S,"changeFrameOrientationToPortait",tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientationToPortait00);
   tolua_function(tolua_S,"changeFrameOrientationToLandscape",tolua_PlayerLuaCore_ProjectConfig_changeFrameOrientationToLandscape00);
   tolua_function(tolua_S,"getFrameScale",tolua_PlayerLuaCore_ProjectConfig_getFrameScale00);
   tolua_function(tolua_S,"setFrameScale",tolua_PlayerLuaCore_ProjectConfig_setFrameScale00);
   tolua_function(tolua_S,"isShowConsole",tolua_PlayerLuaCore_ProjectConfig_isShowConsole00);
   tolua_function(tolua_S,"setShowConsole",tolua_PlayerLuaCore_ProjectConfig_setShowConsole00);
   tolua_function(tolua_S,"isLoadPrecompiledFramework",tolua_PlayerLuaCore_ProjectConfig_isLoadPrecompiledFramework00);
   tolua_function(tolua_S,"setLoadPrecompiledFramework",tolua_PlayerLuaCore_ProjectConfig_setLoadPrecompiledFramework00);
   tolua_function(tolua_S,"isWriteDebugLogToFile",tolua_PlayerLuaCore_ProjectConfig_isWriteDebugLogToFile00);
   tolua_function(tolua_S,"setWriteDebugLogToFile",tolua_PlayerLuaCore_ProjectConfig_setWriteDebugLogToFile00);
   tolua_function(tolua_S,"getDebugLogFilePath",tolua_PlayerLuaCore_ProjectConfig_getDebugLogFilePath00);
   tolua_function(tolua_S,"setWindowOffset",tolua_PlayerLuaCore_ProjectConfig_setWindowOffset00);
   tolua_function(tolua_S,"getDebuggerType",tolua_PlayerLuaCore_ProjectConfig_getDebuggerType00);
   tolua_function(tolua_S,"setDebuggerType",tolua_PlayerLuaCore_ProjectConfig_setDebuggerType00);
   tolua_function(tolua_S,"parseCommandLine",tolua_PlayerLuaCore_ProjectConfig_parseCommandLine00);
   tolua_function(tolua_S,"makeCommandLine",tolua_PlayerLuaCore_ProjectConfig_makeCommandLine00);
   tolua_function(tolua_S,"isAppMenu",tolua_PlayerLuaCore_ProjectConfig_isAppMenu00);
   tolua_function(tolua_S,"isResizeWindow",tolua_PlayerLuaCore_ProjectConfig_isResizeWindow00);
   tolua_function(tolua_S,"isRetinaDisplay",tolua_PlayerLuaCore_ProjectConfig_isRetinaDisplay00);
   tolua_function(tolua_S,"validate",tolua_PlayerLuaCore_ProjectConfig_validate00);
   tolua_function(tolua_S,"dump",tolua_PlayerLuaCore_ProjectConfig_dump00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PlayerSettings","PlayerSettings","",tolua_collect_PlayerSettings);
  #else
  tolua_cclass(tolua_S,"PlayerSettings","PlayerSettings","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PlayerSettings");
   tolua_function(tolua_S,"new",tolua_PlayerLuaCore_PlayerSettings_new00);
   tolua_function(tolua_S,"new_local",tolua_PlayerLuaCore_PlayerSettings_new00_local);
   tolua_function(tolua_S,".call",tolua_PlayerLuaCore_PlayerSettings_new00_local);
   tolua_variable(tolua_S,"openLastProject",tolua_get_PlayerSettings_openLastProject,tolua_set_PlayerSettings_openLastProject);
   tolua_variable(tolua_S,"offsetX",tolua_get_PlayerSettings_offsetX,tolua_set_PlayerSettings_offsetX);
   tolua_variable(tolua_S,"offsetY",tolua_get_PlayerSettings_offsetY,tolua_set_PlayerSettings_offsetY);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerProtocol","PlayerProtocol","",NULL);
  tolua_beginmodule(tolua_S,"PlayerProtocol");
   tolua_function(tolua_S,"getInstance",tolua_PlayerLuaCore_PlayerProtocol_getInstance00);
   tolua_function(tolua_S,"purgeInstance",tolua_PlayerLuaCore_PlayerProtocol_purgeInstance00);
   tolua_function(tolua_S,"setPlayerSettings",tolua_PlayerLuaCore_PlayerProtocol_setPlayerSettings00);
   tolua_function(tolua_S,"getPlayerSettings",tolua_PlayerLuaCore_PlayerProtocol_getPlayerSettings00);
   tolua_function(tolua_S,"getFileDialogService",tolua_PlayerLuaCore_PlayerProtocol_getFileDialogService00);
   tolua_function(tolua_S,"getMessageBoxService",tolua_PlayerLuaCore_PlayerProtocol_getMessageBoxService00);
   tolua_function(tolua_S,"getMenuService",tolua_PlayerLuaCore_PlayerProtocol_getMenuService00);
   tolua_function(tolua_S,"getEditBoxService",tolua_PlayerLuaCore_PlayerProtocol_getEditBoxService00);
   tolua_function(tolua_S,"getTaskService",tolua_PlayerLuaCore_PlayerProtocol_getTaskService00);
   tolua_function(tolua_S,"quit",tolua_PlayerLuaCore_PlayerProtocol_quit00);
   tolua_function(tolua_S,"relaunch",tolua_PlayerLuaCore_PlayerProtocol_relaunch00);
   tolua_function(tolua_S,"openNewPlayer",tolua_PlayerLuaCore_PlayerProtocol_openNewPlayer00);
   tolua_function(tolua_S,"openNewPlayerWithProjectConfig",tolua_PlayerLuaCore_PlayerProtocol_openNewPlayerWithProjectConfig00);
   tolua_function(tolua_S,"openProjectWithProjectConfig",tolua_PlayerLuaCore_PlayerProtocol_openProjectWithProjectConfig00);
   tolua_function(tolua_S,"getPositionX",tolua_PlayerLuaCore_PlayerProtocol_getPositionX00);
   tolua_function(tolua_S,"getPositionY",tolua_PlayerLuaCore_PlayerProtocol_getPositionY00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerFileDialogServiceProtocol","PlayerFileDialogServiceProtocol","PlayerServiceProtocol",NULL);
  tolua_beginmodule(tolua_S,"PlayerFileDialogServiceProtocol");
   tolua_function(tolua_S,"openFile",tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openFile00);
   tolua_function(tolua_S,"openMultiple",tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openMultiple00);
   tolua_function(tolua_S,"saveFile",tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_saveFile00);
   tolua_function(tolua_S,"openDirectory",tolua_PlayerLuaCore_PlayerFileDialogServiceProtocol_openDirectory00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerMenuItem","PlayerMenuItem","cocos2d::Ref",NULL);
  tolua_beginmodule(tolua_S,"PlayerMenuItem");
   tolua_function(tolua_S,"getMenuId",tolua_PlayerLuaCore_PlayerMenuItem_getMenuId00);
   tolua_function(tolua_S,"getTitle",tolua_PlayerLuaCore_PlayerMenuItem_getTitle00);
   tolua_function(tolua_S,"getOrder",tolua_PlayerLuaCore_PlayerMenuItem_getOrder00);
   tolua_function(tolua_S,"isGroup",tolua_PlayerLuaCore_PlayerMenuItem_isGroup00);
   tolua_function(tolua_S,"isEnabled",tolua_PlayerLuaCore_PlayerMenuItem_isEnabled00);
   tolua_function(tolua_S,"isChecked",tolua_PlayerLuaCore_PlayerMenuItem_isChecked00);
   tolua_function(tolua_S,"getShortcut",tolua_PlayerLuaCore_PlayerMenuItem_getShortcut00);
   tolua_function(tolua_S,"setTitle",tolua_PlayerLuaCore_PlayerMenuItem_setTitle00);
   tolua_function(tolua_S,"setEnabled",tolua_PlayerLuaCore_PlayerMenuItem_setEnabled00);
   tolua_function(tolua_S,"setChecked",tolua_PlayerLuaCore_PlayerMenuItem_setChecked00);
   tolua_function(tolua_S,"setShortcut",tolua_PlayerLuaCore_PlayerMenuItem_setShortcut00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerMenuServiceProtocol","PlayerMenuServiceProtocol","",NULL);
  tolua_beginmodule(tolua_S,"PlayerMenuServiceProtocol");
   tolua_function(tolua_S,"addItem",tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem00);
   tolua_function(tolua_S,"addItem",tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem01);
   tolua_function(tolua_S,"addItem",tolua_PlayerLuaCore_PlayerMenuServiceProtocol_addItem02);
   tolua_function(tolua_S,"getItem",tolua_PlayerLuaCore_PlayerMenuServiceProtocol_getItem00);
   tolua_function(tolua_S,"removeItem",tolua_PlayerLuaCore_PlayerMenuServiceProtocol_removeItem00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerMessageBoxServiceProtocol","PlayerMessageBoxServiceProtocol","PlayerServiceProtocol",NULL);
  tolua_beginmodule(tolua_S,"PlayerMessageBoxServiceProtocol");
   tolua_function(tolua_S,"showMessageBox",tolua_PlayerLuaCore_PlayerMessageBoxServiceProtocol_showMessageBox00);
   tolua_function(tolua_S,"showMessageBox",tolua_PlayerLuaCore_PlayerMessageBoxServiceProtocol_showMessageBox01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerTask","PlayerTask","cocos2d::Ref",NULL);
  tolua_beginmodule(tolua_S,"PlayerTask");
   tolua_function(tolua_S,"getName",tolua_PlayerLuaCore_PlayerTask_getName00);
   tolua_function(tolua_S,"getExecutePath",tolua_PlayerLuaCore_PlayerTask_getExecutePath00);
   tolua_function(tolua_S,"getCommandLineArguments",tolua_PlayerLuaCore_PlayerTask_getCommandLineArguments00);
   tolua_function(tolua_S,"getOutput",tolua_PlayerLuaCore_PlayerTask_getOutput00);
   tolua_function(tolua_S,"getState",tolua_PlayerLuaCore_PlayerTask_getState00);
   tolua_function(tolua_S,"isIdle",tolua_PlayerLuaCore_PlayerTask_isIdle00);
   tolua_function(tolua_S,"isRunning",tolua_PlayerLuaCore_PlayerTask_isRunning00);
   tolua_function(tolua_S,"isCompleted",tolua_PlayerLuaCore_PlayerTask_isCompleted00);
   tolua_function(tolua_S,"getLifetime",tolua_PlayerLuaCore_PlayerTask_getLifetime00);
   tolua_function(tolua_S,"getResultCode",tolua_PlayerLuaCore_PlayerTask_getResultCode00);
   tolua_function(tolua_S,"run",tolua_PlayerLuaCore_PlayerTask_run00);
   tolua_function(tolua_S,"stop",tolua_PlayerLuaCore_PlayerTask_stop00);
   tolua_function(tolua_S,"runInTerminal",tolua_PlayerLuaCore_PlayerTask_runInTerminal00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerTaskServiceProtocol","PlayerTaskServiceProtocol","PlayerServiceProtocol",NULL);
  tolua_beginmodule(tolua_S,"PlayerTaskServiceProtocol");
   tolua_function(tolua_S,"createTask",tolua_PlayerLuaCore_PlayerTaskServiceProtocol_createTask00);
   tolua_function(tolua_S,"getTask",tolua_PlayerLuaCore_PlayerTaskServiceProtocol_getTask00);
   tolua_function(tolua_S,"removeTask",tolua_PlayerLuaCore_PlayerTaskServiceProtocol_removeTask00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlayerEditBoxServiceProtocol","PlayerEditBoxServiceProtocol","PlayerServiceProtocol",NULL);
  tolua_beginmodule(tolua_S,"PlayerEditBoxServiceProtocol");
   tolua_function(tolua_S,"hide",tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_hide00);
   tolua_function(tolua_S,"setText",tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setText00);
   tolua_function(tolua_S,"setFont",tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setFont00);
   tolua_function(tolua_S,"setFormator",tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_setFormator00);
   tolua_function(tolua_S,"registerHandler",tolua_PlayerLuaCore_PlayerEditBoxServiceProtocol_registerHandler00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_PlayerLuaCore (lua_State* tolua_S) {
 return tolua_PlayerLuaCore_open(tolua_S);
};
#endif

