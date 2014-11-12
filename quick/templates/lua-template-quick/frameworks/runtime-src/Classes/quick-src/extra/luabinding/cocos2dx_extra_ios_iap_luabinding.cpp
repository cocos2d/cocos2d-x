/*
** Lua binding: cocos2dx_extra_ios_iap_luabinding
** Generated automatically by tolua++-1.0.92 on Tue Jul 15 15:28:05 2014.
*/

#include "cocos2dx_extra_ios_iap_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "store/CCStore.h"
using namespace std;
using namespace cocos2d;
using namespace cocos2d::extra;

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 
 tolua_usertype(tolua_S,"Store");
 
}

/* method: sharedStore of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_sharedStore00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_sharedStore00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Store* tolua_ret = (Store*)  Store::sharedStore();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Store");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedStore'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeSharedStore of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_purgeSharedStore00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_purgeSharedStore00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Store::purgeSharedStore();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeSharedStore'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: postInitWithTransactionListenerLua of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_postInitWithTransactionListener00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_postInitWithTransactionListener00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION listener = (  toluafix_ref_function(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'postInitWithTransactionListenerLua'", NULL);
#endif
  {
   self->postInitWithTransactionListenerLua(listener);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'postInitWithTransactionListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canMakePurchases of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_canMakePurchases00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_canMakePurchases00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'canMakePurchases'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->canMakePurchases();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canMakePurchases'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadProductsLua of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_loadProducts00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_loadProducts00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_istable(tolua_S,2,"LUA_TABLE",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
  LUA_TABLE __LUA_TABLE__ = (  toluafix_totable(tolua_S,2,0));
  LUA_FUNCTION callback = (  toluafix_ref_function(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadProductsLua'", NULL);
#endif
  {
   self->loadProductsLua(__LUA_TABLE__,callback);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadProducts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancelLoadProducts of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_cancelLoadProducts00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_cancelLoadProducts00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancelLoadProducts'", NULL);
#endif
  {
   self->cancelLoadProducts();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancelLoadProducts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isProductLoaded of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_isProductLoaded00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_isProductLoaded00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
  const char* productId = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isProductLoaded'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isProductLoaded(productId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isProductLoaded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purchase of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_purchase00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_purchase00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
  const char* productId = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purchase'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->purchase(productId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purchase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: restore of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_restore00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_restore00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'restore'", NULL);
#endif
  {
   self->restore();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'restore'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: finishTransactionLua of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_finishTransaction00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_finishTransaction00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
  const char* transactionIdentifier = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'finishTransactionLua'", NULL);
#endif
  {
   self->finishTransactionLua(transactionIdentifier);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'finishTransaction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getReceiptVerifyMode of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_getReceiptVerifyMode00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_getReceiptVerifyMode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getReceiptVerifyMode'", NULL);
#endif
  {
   CCStoreReceiptVerifyMode tolua_ret = (CCStoreReceiptVerifyMode)  self->getReceiptVerifyMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getReceiptVerifyMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setReceiptVerifyMode of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_setReceiptVerifyMode00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_setReceiptVerifyMode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
  CCStoreReceiptVerifyMode mode = ((CCStoreReceiptVerifyMode) (int)  tolua_tonumber(tolua_S,2,0));
  bool isSandbox = ((bool)  tolua_toboolean(tolua_S,3,true));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setReceiptVerifyMode'", NULL);
#endif
  {
   self->setReceiptVerifyMode(mode,isSandbox);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setReceiptVerifyMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getReceiptVerifyServerUrl of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_getReceiptVerifyServerUrl00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_getReceiptVerifyServerUrl00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getReceiptVerifyServerUrl'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getReceiptVerifyServerUrl();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getReceiptVerifyServerUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setReceiptVerifyServerUrl of class  Store */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extra_ios_iap_luabinding_Store_setReceiptVerifyServerUrl00
static int tolua_cocos2dx_extra_ios_iap_luabinding_Store_setReceiptVerifyServerUrl00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Store",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Store* self = (Store*)  tolua_tousertype(tolua_S,1,0);
  const char* url = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setReceiptVerifyServerUrl'", NULL);
#endif
  {
   self->setReceiptVerifyServerUrl(url);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setReceiptVerifyServerUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_cocos2dx_extra_ios_iap_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,"cc",0);
 tolua_beginmodule(tolua_S,"cc");
  tolua_constant(tolua_S,"CCStoreReceiptVerifyModeNone",CCStoreReceiptVerifyModeNone);
  tolua_constant(tolua_S,"CCStoreReceiptVerifyModeDevice",CCStoreReceiptVerifyModeDevice);
  tolua_constant(tolua_S,"CCStoreReceiptVerifyModeServer",CCStoreReceiptVerifyModeServer);
  tolua_constant(tolua_S,"CCStoreReceiptVerifyStatusUnknownError",CCStoreReceiptVerifyStatusUnknownError);
  tolua_constant(tolua_S,"CCStoreReceiptVerifyStatusInvalidReceipt",CCStoreReceiptVerifyStatusInvalidReceipt);
  tolua_constant(tolua_S,"CCStoreReceiptVerifyStatusRequestFailed",CCStoreReceiptVerifyStatusRequestFailed);
  tolua_constant(tolua_S,"CCStoreReceiptVerifyStatusInvalidResult",CCStoreReceiptVerifyStatusInvalidResult);
  tolua_constant(tolua_S,"CCStoreReceiptVerifyStatusNone",CCStoreReceiptVerifyStatusNone);
  tolua_constant(tolua_S,"CCStoreReceiptVerifyStatusOK",CCStoreReceiptVerifyStatusOK);
  tolua_cclass(tolua_S,"Store","Store","",NULL);
  tolua_beginmodule(tolua_S,"Store");
   tolua_function(tolua_S,"sharedStore",tolua_cocos2dx_extra_ios_iap_luabinding_Store_sharedStore00);
   tolua_function(tolua_S,"purgeSharedStore",tolua_cocos2dx_extra_ios_iap_luabinding_Store_purgeSharedStore00);
   tolua_function(tolua_S,"postInitWithTransactionListener",tolua_cocos2dx_extra_ios_iap_luabinding_Store_postInitWithTransactionListener00);
   tolua_function(tolua_S,"canMakePurchases",tolua_cocos2dx_extra_ios_iap_luabinding_Store_canMakePurchases00);
   tolua_function(tolua_S,"loadProducts",tolua_cocos2dx_extra_ios_iap_luabinding_Store_loadProducts00);
   tolua_function(tolua_S,"cancelLoadProducts",tolua_cocos2dx_extra_ios_iap_luabinding_Store_cancelLoadProducts00);
   tolua_function(tolua_S,"isProductLoaded",tolua_cocos2dx_extra_ios_iap_luabinding_Store_isProductLoaded00);
   tolua_function(tolua_S,"purchase",tolua_cocos2dx_extra_ios_iap_luabinding_Store_purchase00);
   tolua_function(tolua_S,"restore",tolua_cocos2dx_extra_ios_iap_luabinding_Store_restore00);
   tolua_function(tolua_S,"finishTransaction",tolua_cocos2dx_extra_ios_iap_luabinding_Store_finishTransaction00);
   tolua_function(tolua_S,"getReceiptVerifyMode",tolua_cocos2dx_extra_ios_iap_luabinding_Store_getReceiptVerifyMode00);
   tolua_function(tolua_S,"setReceiptVerifyMode",tolua_cocos2dx_extra_ios_iap_luabinding_Store_setReceiptVerifyMode00);
   tolua_function(tolua_S,"getReceiptVerifyServerUrl",tolua_cocos2dx_extra_ios_iap_luabinding_Store_getReceiptVerifyServerUrl00);
   tolua_function(tolua_S,"setReceiptVerifyServerUrl",tolua_cocos2dx_extra_ios_iap_luabinding_Store_setReceiptVerifyServerUrl00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_cocos2dx_extra_ios_iap_luabinding (lua_State* tolua_S) {
 return tolua_cocos2dx_extra_ios_iap_luabinding_open(tolua_S);
};
#endif

