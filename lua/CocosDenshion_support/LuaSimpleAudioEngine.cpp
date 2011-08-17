/*
** Lua binding: SimpleAudioEngine
** Generated automatically by tolua++-1.0.92 on Tue Aug 16 22:48:34 2011.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

#include "LuaSimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

/* Exported function */
TOLUA_API int  tolua_SimpleAudioEngine_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CocosDenshion__SimpleAudioEngine (lua_State* tolua_S)
{
 CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CocosDenshion::SimpleAudioEngine");
}

/* method: new of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_new00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CocosDenshion::SimpleAudioEngine* tolua_ret = (CocosDenshion::SimpleAudioEngine*)  new CocosDenshion::SimpleAudioEngine();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"CocosDenshion::SimpleAudioEngine");
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

/* method: new_local of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_new00_local
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CocosDenshion::SimpleAudioEngine* tolua_ret = (CocosDenshion::SimpleAudioEngine*)  new CocosDenshion::SimpleAudioEngine();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"CocosDenshion::SimpleAudioEngine");
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

/* method: delete of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_delete00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedEngine of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_sharedEngine00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_sharedEngine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CocosDenshion::SimpleAudioEngine* tolua_ret = (CocosDenshion::SimpleAudioEngine*)  CocosDenshion::SimpleAudioEngine::sharedEngine();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"CocosDenshion::SimpleAudioEngine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedEngine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: end of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_end00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_end00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CocosDenshion::SimpleAudioEngine::end();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'end'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setResource of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setResource00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setResource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszZipFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CocosDenshion::SimpleAudioEngine::setResource(pszZipFileName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preloadBackgroundMusic of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_preloadBackgroundMusic00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_preloadBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preloadBackgroundMusic'",NULL);
#endif
  {
   self->preloadBackgroundMusic(pszFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preloadBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playBackgroundMusic of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_playBackgroundMusic00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_playBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playBackgroundMusic'",NULL);
#endif
  {
   self->playBackgroundMusic(pszFilePath,bLoop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopBackgroundMusic of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_stopBackgroundMusic00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_stopBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  bool bReleaseData = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopBackgroundMusic'",NULL);
#endif
  {
   self->stopBackgroundMusic(bReleaseData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseBackgroundMusic of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_pauseBackgroundMusic00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_pauseBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseBackgroundMusic'",NULL);
#endif
  {
   self->pauseBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeBackgroundMusic of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_resumeBackgroundMusic00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_resumeBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeBackgroundMusic'",NULL);
#endif
  {
   self->resumeBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rewindBackgroundMusic of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_rewindBackgroundMusic00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_rewindBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rewindBackgroundMusic'",NULL);
#endif
  {
   self->rewindBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rewindBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: willPlayBackgroundMusic of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_willPlayBackgroundMusic00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_willPlayBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'willPlayBackgroundMusic'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->willPlayBackgroundMusic();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'willPlayBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBackgroundMusicPlaying of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_isBackgroundMusicPlaying00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_isBackgroundMusicPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBackgroundMusicPlaying'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBackgroundMusicPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBackgroundMusicPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundMusicVolume of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_getBackgroundMusicVolume00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_getBackgroundMusicVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundMusicVolume'",NULL);
#endif
  {
   float tolua_ret = (float)  self->getBackgroundMusicVolume();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundMusicVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundMusicVolume of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setBackgroundMusicVolume00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setBackgroundMusicVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  float volume = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundMusicVolume'",NULL);
#endif
  {
   self->setBackgroundMusicVolume(volume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundMusicVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEffectsVolume of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_getEffectsVolume00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_getEffectsVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEffectsVolume'",NULL);
#endif
  {
   float tolua_ret = (float)  self->getEffectsVolume();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEffectsVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEffectsVolume of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setEffectsVolume00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setEffectsVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  float volume = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEffectsVolume'",NULL);
#endif
  {
   self->setEffectsVolume(volume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEffectsVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playEffect of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_playEffect00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_playEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playEffect'",NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->playEffect(pszFilePath,bLoop);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopEffect of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_stopEffect00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_stopEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopEffect'",NULL);
#endif
  {
   self->stopEffect(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preloadEffect of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_preloadEffect00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_preloadEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preloadEffect'",NULL);
#endif
  {
   self->preloadEffect(pszFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preloadEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unloadEffect of class  CocosDenshion::SimpleAudioEngine */
#ifndef TOLUA_DISABLE_tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_unloadEffect00
static int tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_unloadEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CocosDenshion::SimpleAudioEngine",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CocosDenshion::SimpleAudioEngine* self = (CocosDenshion::SimpleAudioEngine*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unloadEffect'",NULL);
#endif
  {
   self->unloadEffect(pszFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unloadEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SimpleAudioEngine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"CocosDenshion",0);
  tolua_beginmodule(tolua_S,"CocosDenshion");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"SimpleAudioEngine","CocosDenshion::SimpleAudioEngine","",tolua_collect_CocosDenshion__SimpleAudioEngine);
   #else
   tolua_cclass(tolua_S,"SimpleAudioEngine","CocosDenshion::SimpleAudioEngine","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"SimpleAudioEngine");
    tolua_function(tolua_S,"new",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_new00);
    tolua_function(tolua_S,"new_local",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_new00_local);
    tolua_function(tolua_S,".call",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_new00_local);
    tolua_function(tolua_S,"delete",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_delete00);
    tolua_function(tolua_S,"sharedEngine",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_sharedEngine00);
    tolua_function(tolua_S,"end",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_end00);
    tolua_function(tolua_S,"setResource",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setResource00);
    tolua_function(tolua_S,"preloadBackgroundMusic",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_preloadBackgroundMusic00);
    tolua_function(tolua_S,"playBackgroundMusic",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_playBackgroundMusic00);
    tolua_function(tolua_S,"stopBackgroundMusic",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_stopBackgroundMusic00);
    tolua_function(tolua_S,"pauseBackgroundMusic",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_pauseBackgroundMusic00);
    tolua_function(tolua_S,"resumeBackgroundMusic",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_resumeBackgroundMusic00);
    tolua_function(tolua_S,"rewindBackgroundMusic",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_rewindBackgroundMusic00);
    tolua_function(tolua_S,"willPlayBackgroundMusic",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_willPlayBackgroundMusic00);
    tolua_function(tolua_S,"isBackgroundMusicPlaying",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_isBackgroundMusicPlaying00);
    tolua_function(tolua_S,"getBackgroundMusicVolume",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_getBackgroundMusicVolume00);
    tolua_function(tolua_S,"setBackgroundMusicVolume",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setBackgroundMusicVolume00);
    tolua_function(tolua_S,"getEffectsVolume",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_getEffectsVolume00);
    tolua_function(tolua_S,"setEffectsVolume",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_setEffectsVolume00);
    tolua_function(tolua_S,"playEffect",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_playEffect00);
    tolua_function(tolua_S,"stopEffect",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_stopEffect00);
    tolua_function(tolua_S,"preloadEffect",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_preloadEffect00);
    tolua_function(tolua_S,"unloadEffect",tolua_SimpleAudioEngine_CocosDenshion_SimpleAudioEngine_unloadEffect00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SimpleAudioEngine (lua_State* tolua_S) {
 return tolua_SimpleAudioEngine_open(tolua_S);
};
#endif

