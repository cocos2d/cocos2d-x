/*
** Lua binding: cocos2dx_extra_luabinding
** Generated automatically by tolua++-1.0.92 on Tue Jul 15 15:28:05 2014.
*/

#include "cocos2dx_extra_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "crypto/CCCrypto.h"
#include "native/CCNative.h"
#include "network/CCNetwork.h"
using namespace std;
using namespace cocos2d;
using namespace cocos2d::extra;

/* function to release collected object via destructor */
#ifdef __cplusplus


#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"cc.Ref");
 tolua_usertype(tolua_S,"Network");
 tolua_usertype(tolua_S,"Crypto");

 tolua_usertype(tolua_S,"Native");
 tolua_usertype(tolua_S,"HTTPRequest");

}

/* method: getAES256KeyLength of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_getAES256KeyLength00
static int tolua_cocos2dx_extra_luabinding_Crypto_getAES256KeyLength00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  Crypto::getAES256KeyLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAES256KeyLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: encryptAES256Lua of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_encryptAES25600
static int tolua_cocos2dx_extra_luabinding_Crypto_encryptAES25600(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* plaintext = ((const char*)  tolua_tostring(tolua_S,2,0));
  int plaintextLength = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,4,0));
  int keyLength = ((int)  tolua_tonumber(tolua_S,5,0));
  {
     Crypto::encryptAES256Lua(plaintext,plaintextLength,key,keyLength);

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'encryptAES256'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: decryptAES256Lua of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_decryptAES25600
static int tolua_cocos2dx_extra_luabinding_Crypto_decryptAES25600(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* ciphertext = ((const char*)  tolua_tostring(tolua_S,2,0));
  int ciphertextLength = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,4,0));
  int keyLength = ((int)  tolua_tonumber(tolua_S,5,0));
  {
     Crypto::decryptAES256Lua(ciphertext,ciphertextLength,key,keyLength);

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'decryptAES256'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: encryptXXTEALua of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_encryptXXTEA00
static int tolua_cocos2dx_extra_luabinding_Crypto_encryptXXTEA00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* plaintext = ((const char*)  tolua_tostring(tolua_S,2,0));
  int plaintextLength = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,4,0));
  int keyLength = ((int)  tolua_tonumber(tolua_S,5,0));
  {
     Crypto::encryptXXTEALua(plaintext,plaintextLength,key,keyLength);

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'encryptXXTEA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: decryptXXTEALua of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_decryptXXTEA00
static int tolua_cocos2dx_extra_luabinding_Crypto_decryptXXTEA00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* ciphertext = ((const char*)  tolua_tostring(tolua_S,2,0));
  int ciphertextLength = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,4,0));
  int keyLength = ((int)  tolua_tonumber(tolua_S,5,0));
  {
     Crypto::decryptXXTEALua(ciphertext,ciphertextLength,key,keyLength);

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'decryptXXTEA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: encodeBase64Lua of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_encodeBase6400
static int tolua_cocos2dx_extra_luabinding_Crypto_encodeBase6400(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* input = ((const char*)  tolua_tostring(tolua_S,2,0));
  int inputLength = ((int)  tolua_tonumber(tolua_S,3,0));
  {
     Crypto::encodeBase64Lua(input,inputLength);

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'encodeBase64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: decodeBase64Lua of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_decodeBase6400
static int tolua_cocos2dx_extra_luabinding_Crypto_decodeBase6400(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* input = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
     Crypto::decodeBase64Lua(input);

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'decodeBase64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MD5Lua of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_MD500
static int tolua_cocos2dx_extra_luabinding_Crypto_MD500(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* input = ((char*)  tolua_tostring(tolua_S,2,0));
  bool isRawOutput = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
     Crypto::MD5Lua(input,isRawOutput);

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MD5'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MD5FileLua of class  Crypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Crypto_MD5File00
static int tolua_cocos2dx_extra_luabinding_Crypto_MD5File00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Crypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
     Crypto::MD5FileLua(path);

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MD5File'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showActivityIndicator of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_showActivityIndicator00
static int tolua_cocos2dx_extra_luabinding_Native_showActivityIndicator00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Native::showActivityIndicator();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showActivityIndicator'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hideActivityIndicator of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_hideActivityIndicator00
static int tolua_cocos2dx_extra_luabinding_Native_hideActivityIndicator00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Native::hideActivityIndicator();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hideActivityIndicator'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createAlert of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_createAlert00
static int tolua_cocos2dx_extra_luabinding_Native_createAlert00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* title = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* cancelButtonTitle = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   Native::createAlert(title,message,cancelButtonTitle);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createAlert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addAlertButton of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_addAlertButton00
static int tolua_cocos2dx_extra_luabinding_Native_addAlertButton00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* buttonTitle = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   int tolua_ret = (int)  Native::addAlertButton(buttonTitle);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addAlertButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showAlertLua of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_showAlert00
static int tolua_cocos2dx_extra_luabinding_Native_showAlert00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LUA_FUNCTION listener = (  toluafix_ref_function(tolua_S,2,0));
  {
   Native::showAlertLua(listener);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showAlert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancelAlert of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_cancelAlert00
static int tolua_cocos2dx_extra_luabinding_Native_cancelAlert00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Native::cancelAlert();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancelAlert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpenUDID of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_getOpenUDID00
static int tolua_cocos2dx_extra_luabinding_Native_getOpenUDID00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   string tolua_ret = (string)  Native::getOpenUDID();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOpenUDID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openURL of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_openURL00
static int tolua_cocos2dx_extra_luabinding_Native_openURL00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* url = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Native::openURL(url);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openURL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInputText of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_getInputText00
static int tolua_cocos2dx_extra_luabinding_Native_getInputText00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* title = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* defaultValue = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   string tolua_ret = (string)  Native::getInputText(title,message,defaultValue);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInputText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDeviceName of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_getDeviceName00
static int tolua_cocos2dx_extra_luabinding_Native_getDeviceName00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   const string tolua_ret = (const string)  Native::getDeviceName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeviceName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vibrate of class  Native */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Native_vibrate00
static int tolua_cocos2dx_extra_luabinding_Native_vibrate00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Native::vibrate();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'vibrate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithUrlLua of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_createWithUrl00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_createWithUrl00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LUA_FUNCTION listener = (  toluafix_ref_function(tolua_S,2,0));
  const char* url = ((const char*)  tolua_tostring(tolua_S,3,0));
  int method = ((int)  tolua_tonumber(tolua_S,4,kCCHTTPRequestMethodGET));
  {
   HTTPRequest* tolua_ret = (HTTPRequest*)  HTTPRequest::createWithUrlLua(listener,url,method);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HTTPRequest");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRequestUrl of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_setRequestUrl00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_setRequestUrl00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* url = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRequestUrl'", NULL);
#endif
  {
   self->setRequestUrl(url);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRequestUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRequestUrl of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getRequestUrl00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getRequestUrl00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRequestUrl'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getRequestUrl();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRequestUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addRequestHeader of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_addRequestHeader00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_addRequestHeader00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* header = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addRequestHeader'", NULL);
#endif
  {
   self->addRequestHeader(header);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addRequestHeader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addPOSTValue of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_addPOSTValue00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_addPOSTValue00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPOSTValue'", NULL);
#endif
  {
   self->addPOSTValue(key,value);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addPOSTValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPOSTData of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_setPOSTData00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_setPOSTData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPOSTData'", NULL);
#endif
  {
      size_t len;
      lua_tolstring(tolua_S, 2, &len);
      self->setPOSTData(data, len);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPOSTData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addFormFile of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_addFormFile00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_addFormFile00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* filePath = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* fileType = ((const char*)  tolua_tostring(tolua_S,4,"application/octet-stream"));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addFormFile'", NULL);
#endif
  {
   self->addFormFile(name,filePath,fileType);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addFormFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addFormContents of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_addFormContents00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_addFormContents00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addFormContents'", NULL);
#endif
  {
   self->addFormContents(name,value);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addFormContents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCookieString of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_setCookieString00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_setCookieString00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* cookie = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCookieString'", NULL);
#endif
  {
   self->setCookieString(cookie);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCookieString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCookieString of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getCookieString00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getCookieString00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCookieString'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getCookieString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCookieString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAcceptEncoding of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_setAcceptEncoding00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_setAcceptEncoding00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  int acceptEncoding = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAcceptEncoding'", NULL);
#endif
  {
   self->setAcceptEncoding(acceptEncoding);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAcceptEncoding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTimeout of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_setTimeout00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_setTimeout00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  int timeout = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTimeout'", NULL);
#endif
  {
   self->setTimeout(timeout);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTimeout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_start00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_start00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->start();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancel of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_cancel00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_cancel00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancel'", NULL);
#endif
  {
   self->cancel();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getState of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getState00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getState00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getResponseStatusCode of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseStatusCode00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseStatusCode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseStatusCode'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getResponseStatusCode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getResponseStatusCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getResponseHeadersString of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseHeadersString00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseHeadersString00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseHeadersString'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getResponseHeadersString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getResponseHeadersString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getResponseString of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseString00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseString00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseString'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getResponseString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getResponseString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getResponseDataLua of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseData00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseDataLua'", NULL);
#endif
  {
     self->getResponseDataLua();

  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getResponseData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getResponseDataLength of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseDataLength00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseDataLength00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseDataLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getResponseDataLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getResponseDataLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: saveResponseData of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_saveResponseData00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_saveResponseData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'saveResponseData'", NULL);
#endif
  {
   int tolua_ret = (int)  self->saveResponseData(filename);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'saveResponseData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getErrorCode of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getErrorCode00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getErrorCode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getErrorCode'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getErrorCode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getErrorCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getErrorMessage of class  HTTPRequest */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_HTTPRequest_getErrorMessage00
static int tolua_cocos2dx_extra_luabinding_HTTPRequest_getErrorMessage00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getErrorMessage'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getErrorMessage();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getErrorMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLocalWiFiAvailable of class  Network */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Network_isLocalWiFiAvailable00
static int tolua_cocos2dx_extra_luabinding_Network_isLocalWiFiAvailable00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  Network::isLocalWiFiAvailable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLocalWiFiAvailable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInternetConnectionAvailable of class  Network */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Network_isInternetConnectionAvailable00
static int tolua_cocos2dx_extra_luabinding_Network_isInternetConnectionAvailable00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  Network::isInternetConnectionAvailable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInternetConnectionAvailable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isHostNameReachable of class  Network */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Network_isHostNameReachable00
static int tolua_cocos2dx_extra_luabinding_Network_isHostNameReachable00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* hostName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Network::isHostNameReachable(hostName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isHostNameReachable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInternetConnectionStatus of class  Network */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Network_getInternetConnectionStatus00
static int tolua_cocos2dx_extra_luabinding_Network_getInternetConnectionStatus00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  Network::getInternetConnectionStatus();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInternetConnectionStatus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createHTTPRequestLua of class  Network */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_luabinding_Network_createHTTPRequest00
static int tolua_cocos2dx_extra_luabinding_Network_createHTTPRequest00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LUA_FUNCTION listener = (  toluafix_ref_function(tolua_S,2,0));
  const char* url = ((const char*)  tolua_tostring(tolua_S,3,0));
  int method = ((int)  tolua_tonumber(tolua_S,4,kCCHTTPRequestMethodGET));
  {
   HTTPRequest* tolua_ret = (HTTPRequest*)  Network::createHTTPRequestLua(listener,url,method);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HTTPRequest");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createHTTPRequest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_cocos2dx_extra_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,"cc",0);
 tolua_beginmodule(tolua_S,"cc");
  tolua_cclass(tolua_S,"Crypto","Crypto","",NULL);
  tolua_beginmodule(tolua_S,"Crypto");
   tolua_function(tolua_S,"getAES256KeyLength",tolua_cocos2dx_extra_luabinding_Crypto_getAES256KeyLength00);
   tolua_function(tolua_S,"encryptAES256",tolua_cocos2dx_extra_luabinding_Crypto_encryptAES25600);
   tolua_function(tolua_S,"decryptAES256",tolua_cocos2dx_extra_luabinding_Crypto_decryptAES25600);
   tolua_function(tolua_S,"encryptXXTEA",tolua_cocos2dx_extra_luabinding_Crypto_encryptXXTEA00);
   tolua_function(tolua_S,"decryptXXTEA",tolua_cocos2dx_extra_luabinding_Crypto_decryptXXTEA00);
   tolua_function(tolua_S,"encodeBase64",tolua_cocos2dx_extra_luabinding_Crypto_encodeBase6400);
   tolua_function(tolua_S,"decodeBase64",tolua_cocos2dx_extra_luabinding_Crypto_decodeBase6400);
   tolua_function(tolua_S,"MD5",tolua_cocos2dx_extra_luabinding_Crypto_MD500);
   tolua_function(tolua_S,"MD5File",tolua_cocos2dx_extra_luabinding_Crypto_MD5File00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Native","Native","",NULL);
  tolua_beginmodule(tolua_S,"Native");
   tolua_function(tolua_S,"showActivityIndicator",tolua_cocos2dx_extra_luabinding_Native_showActivityIndicator00);
   tolua_function(tolua_S,"hideActivityIndicator",tolua_cocos2dx_extra_luabinding_Native_hideActivityIndicator00);
   tolua_function(tolua_S,"createAlert",tolua_cocos2dx_extra_luabinding_Native_createAlert00);
   tolua_function(tolua_S,"addAlertButton",tolua_cocos2dx_extra_luabinding_Native_addAlertButton00);
   tolua_function(tolua_S,"showAlert",tolua_cocos2dx_extra_luabinding_Native_showAlert00);
   tolua_function(tolua_S,"cancelAlert",tolua_cocos2dx_extra_luabinding_Native_cancelAlert00);
   tolua_function(tolua_S,"getOpenUDID",tolua_cocos2dx_extra_luabinding_Native_getOpenUDID00);
   tolua_function(tolua_S,"openURL",tolua_cocos2dx_extra_luabinding_Native_openURL00);
   tolua_function(tolua_S,"getInputText",tolua_cocos2dx_extra_luabinding_Native_getInputText00);
   tolua_function(tolua_S,"getDeviceName",tolua_cocos2dx_extra_luabinding_Native_getDeviceName00);
   tolua_function(tolua_S,"vibrate",tolua_cocos2dx_extra_luabinding_Native_vibrate00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"kCCHTTPRequestMethodGET",kCCHTTPRequestMethodGET);
  tolua_constant(tolua_S,"kCCHTTPRequestMethodPOST",kCCHTTPRequestMethodPOST);
  tolua_constant(tolua_S,"kCCHTTPRequestAcceptEncodingIdentity",kCCHTTPRequestAcceptEncodingIdentity);
  tolua_constant(tolua_S,"kCCHTTPRequestAcceptEncodingGzip",kCCHTTPRequestAcceptEncodingGzip);
  tolua_constant(tolua_S,"kCCHTTPRequestAcceptEncodingDeflate",kCCHTTPRequestAcceptEncodingDeflate);
  tolua_constant(tolua_S,"kCCHTTPRequestStateIdle",kCCHTTPRequestStateIdle);
  tolua_constant(tolua_S,"kCCHTTPRequestStateCleared",kCCHTTPRequestStateCleared);
  tolua_constant(tolua_S,"kCCHTTPRequestStateInProgress",kCCHTTPRequestStateInProgress);
  tolua_constant(tolua_S,"kCCHTTPRequestStateCompleted",kCCHTTPRequestStateCompleted);
  tolua_constant(tolua_S,"kCCHTTPRequestStateCancelled",kCCHTTPRequestStateCancelled);
  tolua_constant(tolua_S,"kCCHTTPRequestStateFailed",kCCHTTPRequestStateFailed);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_USE_CURL)
  tolua_cclass(tolua_S,"HTTPRequest","HTTPRequest","cc.Ref",NULL);
  tolua_beginmodule(tolua_S,"HTTPRequest");
   tolua_function(tolua_S,"createWithUrl",tolua_cocos2dx_extra_luabinding_HTTPRequest_createWithUrl00);
   tolua_function(tolua_S,"setRequestUrl",tolua_cocos2dx_extra_luabinding_HTTPRequest_setRequestUrl00);
   tolua_function(tolua_S,"getRequestUrl",tolua_cocos2dx_extra_luabinding_HTTPRequest_getRequestUrl00);
   tolua_function(tolua_S,"addRequestHeader",tolua_cocos2dx_extra_luabinding_HTTPRequest_addRequestHeader00);
   tolua_function(tolua_S,"addPOSTValue",tolua_cocos2dx_extra_luabinding_HTTPRequest_addPOSTValue00);
   tolua_function(tolua_S,"setPOSTData",tolua_cocos2dx_extra_luabinding_HTTPRequest_setPOSTData00);
   tolua_function(tolua_S,"addFormFile",tolua_cocos2dx_extra_luabinding_HTTPRequest_addFormFile00);
   tolua_function(tolua_S,"addFormContents",tolua_cocos2dx_extra_luabinding_HTTPRequest_addFormContents00);
   tolua_function(tolua_S,"setCookieString",tolua_cocos2dx_extra_luabinding_HTTPRequest_setCookieString00);
   tolua_function(tolua_S,"getCookieString",tolua_cocos2dx_extra_luabinding_HTTPRequest_getCookieString00);
   tolua_function(tolua_S,"setAcceptEncoding",tolua_cocos2dx_extra_luabinding_HTTPRequest_setAcceptEncoding00);
   tolua_function(tolua_S,"setTimeout",tolua_cocos2dx_extra_luabinding_HTTPRequest_setTimeout00);
   tolua_function(tolua_S,"start",tolua_cocos2dx_extra_luabinding_HTTPRequest_start00);
   tolua_function(tolua_S,"cancel",tolua_cocos2dx_extra_luabinding_HTTPRequest_cancel00);
   tolua_function(tolua_S,"getState",tolua_cocos2dx_extra_luabinding_HTTPRequest_getState00);
   tolua_function(tolua_S,"getResponseStatusCode",tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseStatusCode00);
   tolua_function(tolua_S,"getResponseHeadersString",tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseHeadersString00);
   tolua_function(tolua_S,"getResponseString",tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseString00);
   tolua_function(tolua_S,"getResponseData",tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseData00);
   tolua_function(tolua_S,"getResponseDataLength",tolua_cocos2dx_extra_luabinding_HTTPRequest_getResponseDataLength00);
   tolua_function(tolua_S,"saveResponseData",tolua_cocos2dx_extra_luabinding_HTTPRequest_saveResponseData00);
   tolua_function(tolua_S,"getErrorCode",tolua_cocos2dx_extra_luabinding_HTTPRequest_getErrorCode00);
   tolua_function(tolua_S,"getErrorMessage",tolua_cocos2dx_extra_luabinding_HTTPRequest_getErrorMessage00);
  tolua_endmodule(tolua_S);
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_USE_CURL)
  tolua_constant(tolua_S,"kCCNetworkStatusNotReachable",kCCNetworkStatusNotReachable);
  tolua_constant(tolua_S,"kCCNetworkStatusReachableViaWiFi",kCCNetworkStatusReachableViaWiFi);
  tolua_constant(tolua_S,"kCCNetworkStatusReachableViaWWAN",kCCNetworkStatusReachableViaWWAN);
  tolua_cclass(tolua_S,"Network","Network","",NULL);
  tolua_beginmodule(tolua_S,"Network");
   tolua_function(tolua_S,"isLocalWiFiAvailable",tolua_cocos2dx_extra_luabinding_Network_isLocalWiFiAvailable00);
   tolua_function(tolua_S,"isInternetConnectionAvailable",tolua_cocos2dx_extra_luabinding_Network_isInternetConnectionAvailable00);
   tolua_function(tolua_S,"isHostNameReachable",tolua_cocos2dx_extra_luabinding_Network_isHostNameReachable00);
   tolua_function(tolua_S,"getInternetConnectionStatus",tolua_cocos2dx_extra_luabinding_Network_getInternetConnectionStatus00);
   tolua_function(tolua_S,"createHTTPRequest",tolua_cocos2dx_extra_luabinding_Network_createHTTPRequest00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_cocos2dx_extra_luabinding (lua_State* tolua_S) {
 return tolua_cocos2dx_extra_luabinding_open(tolua_S);
};
#endif

