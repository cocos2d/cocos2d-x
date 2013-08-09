#include "lua_cocos2dx_extension_auto.hpp"
#include "cocos-ext.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



static int lua_cocos2dx_extension_Control_setEnabled(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setEnabled'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setEnabled(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setEnabled'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_getState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_getState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		int ret = (int)cobj->getState();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_getState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_isTouchInside(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isTouchInside'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Touch* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->isTouchInside(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isTouchInside'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_sendActionsForControlEvents(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_sendActionsForControlEvents'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::EventType arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->sendActionsForControlEvents(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_sendActionsForControlEvents'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_setSelected(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setSelected'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setSelected(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setSelected'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_registerWithTouchDispatcher(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_registerWithTouchDispatcher'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->registerWithTouchDispatcher();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_registerWithTouchDispatcher'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_isEnabled(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isEnabled'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isEnabled();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isEnabled'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_setOpacityModifyRGB(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setOpacityModifyRGB'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setOpacityModifyRGB(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setOpacityModifyRGB'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_needsLayout(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_needsLayout'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->needsLayout();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_needsLayout'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_hasVisibleParents(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_hasVisibleParents'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->hasVisibleParents();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_hasVisibleParents'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_isSelected(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isSelected'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isSelected();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isSelected'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_init(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_init'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_init'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_setHighlighted(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setHighlighted'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setHighlighted(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setHighlighted'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_isOpacityModifyRGB(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isOpacityModifyRGB'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isOpacityModifyRGB();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isOpacityModifyRGB'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_getTouchLocation(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_getTouchLocation'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Touch* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cocos2d::Point ret = cobj->getTouchLocation(arg0);
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_getTouchLocation'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_isHighlighted(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isHighlighted'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isHighlighted();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isHighlighted'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Control_create(lua_State* tolua_S)
{
	int argc = 0;
	bool ok  = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::extension::Control* ret = cocos2d::extension::Control::create();
		tolua_pushusertype(tolua_S,ret,"Control");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_create'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_Control_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Control* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj = new cocos2d::extension::Control();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"Control");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_Control_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Control)");
	return 0;
}

int lua_register_cocos2dx_extension_Control(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"Control");
	tolua_cclass(tolua_S,"Control","Control","LayerRGBA",NULL);

	tolua_beginmodule(tolua_S,"Control");
		tolua_function(tolua_S,"setEnabled",lua_cocos2dx_extension_Control_setEnabled);
		tolua_function(tolua_S,"getState",lua_cocos2dx_extension_Control_getState);
		tolua_function(tolua_S,"isTouchInside",lua_cocos2dx_extension_Control_isTouchInside);
		tolua_function(tolua_S,"sendActionsForControlEvents",lua_cocos2dx_extension_Control_sendActionsForControlEvents);
		tolua_function(tolua_S,"setSelected",lua_cocos2dx_extension_Control_setSelected);
		tolua_function(tolua_S,"registerWithTouchDispatcher",lua_cocos2dx_extension_Control_registerWithTouchDispatcher);
		tolua_function(tolua_S,"isEnabled",lua_cocos2dx_extension_Control_isEnabled);
		tolua_function(tolua_S,"setOpacityModifyRGB",lua_cocos2dx_extension_Control_setOpacityModifyRGB);
		tolua_function(tolua_S,"needsLayout",lua_cocos2dx_extension_Control_needsLayout);
		tolua_function(tolua_S,"hasVisibleParents",lua_cocos2dx_extension_Control_hasVisibleParents);
		tolua_function(tolua_S,"isSelected",lua_cocos2dx_extension_Control_isSelected);
		tolua_function(tolua_S,"init",lua_cocos2dx_extension_Control_init);
		tolua_function(tolua_S,"setHighlighted",lua_cocos2dx_extension_Control_setHighlighted);
		tolua_function(tolua_S,"isOpacityModifyRGB",lua_cocos2dx_extension_Control_isOpacityModifyRGB);
		tolua_function(tolua_S,"getTouchLocation",lua_cocos2dx_extension_Control_getTouchLocation);
		tolua_function(tolua_S,"isHighlighted",lua_cocos2dx_extension_Control_isHighlighted);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_Control_constructor);
		tolua_function(tolua_S,"create", lua_cocos2dx_extension_Control_create);
	tolua_endmodule(tolua_S);
	return 1;
}


static int lua_cocos2dx_extension_CCBReader_addOwnerOutletName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_addOwnerOutletName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->addOwnerOutletName(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_addOwnerOutletName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_getOwnerCallbackNames(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getOwnerCallbackNames'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getOwnerCallbackNames();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getOwnerCallbackNames'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_setCCBRootPath(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_setCCBRootPath'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		if(!ok)
			return 0;
		cobj->setCCBRootPath(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_setCCBRootPath'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_addOwnerOutletNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_addOwnerOutletNode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Node* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->addOwnerOutletNode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_addOwnerOutletNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_getOwnerCallbackNodes(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getOwnerCallbackNodes'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getOwnerCallbackNodes();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getOwnerCallbackNodes'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_readSoundKeyframesForSeq(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_readSoundKeyframesForSeq'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::CCBSequence* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"CCBSequence",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::CCBSequence*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->readSoundKeyframesForSeq(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_readSoundKeyframesForSeq'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_getCCBRootPath(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getCCBRootPath'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		std::string ret = cobj->getCCBRootPath();
		tolua_pushcppstring(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getCCBRootPath'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_getOwnerOutletNodes(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getOwnerOutletNodes'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getOwnerOutletNodes();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getOwnerOutletNodes'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_readUTF8(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_readUTF8'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		std::string ret = cobj->readUTF8();
		tolua_pushcppstring(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_readUTF8'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_getOwnerOutletNames(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getOwnerOutletNames'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getOwnerOutletNames();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getOwnerOutletNames'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_setAnimationManager(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_setAnimationManager'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::CCBAnimationManager* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"CCBAnimationManager",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setAnimationManager(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_setAnimationManager'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_readCallbackKeyframesForSeq(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_readCallbackKeyframesForSeq'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::CCBSequence* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"CCBSequence",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::CCBSequence*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->readCallbackKeyframesForSeq(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_readCallbackKeyframesForSeq'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_getAnimationManagersForNodes(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getAnimationManagersForNodes'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getAnimationManagersForNodes();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getAnimationManagersForNodes'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_getNodesWithAnimationManagers(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getNodesWithAnimationManagers'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getNodesWithAnimationManagers();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getNodesWithAnimationManagers'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_getAnimationManager(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getAnimationManager'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::extension::CCBAnimationManager* ret = cobj->getAnimationManager();
		tolua_pushusertype(tolua_S,ret,"CCBAnimationManager");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getAnimationManager'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBReader_setResolutionScale(lua_State* tolua_S)
{
	int argc = 0;
	bool ok  = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cocos2d::extension::CCBReader::setResolutionScale(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_setResolutionScale'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_CCBReader_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBReader* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	do{
		if (argc == 1) {
			cocos2d::extension::CCBReader* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"CCBReader",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0);
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
	    return 1;
		}
	}while(0);
	do{
		if (argc == 1) {
			cocos2d::extension::NodeLoaderLibrary* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"NodeLoaderLibrary",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::NodeLoaderLibrary*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0);
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
	    return 1;
		}
	}while(0);
	do{
		if (argc == 2) {
			cocos2d::extension::NodeLoaderLibrary* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"NodeLoaderLibrary",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::NodeLoaderLibrary*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::extension::CCBMemberVariableAssigner* arg1;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"CCBMemberVariableAssigner",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::CCBMemberVariableAssigner*)tolua_tousertype(tolua_S,3,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0, arg1);
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
	    return 1;
		}
	}while(0);
	do{
		if (argc == 3) {
			cocos2d::extension::NodeLoaderLibrary* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"NodeLoaderLibrary",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::NodeLoaderLibrary*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::extension::CCBMemberVariableAssigner* arg1;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"CCBMemberVariableAssigner",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::CCBMemberVariableAssigner*)tolua_tousertype(tolua_S,3,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::extension::CCBSelectorResolver* arg2;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,4,"CCBSelectorResolver",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg2 = (cocos2d::extension::CCBSelectorResolver*)tolua_tousertype(tolua_S,4,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0, arg1, arg2);
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
	    return 1;
		}
	}while(0);
	do{
		if (argc == 4) {
			cocos2d::extension::NodeLoaderLibrary* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"NodeLoaderLibrary",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::NodeLoaderLibrary*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::extension::CCBMemberVariableAssigner* arg1;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"CCBMemberVariableAssigner",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::CCBMemberVariableAssigner*)tolua_tousertype(tolua_S,3,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::extension::CCBSelectorResolver* arg2;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,4,"CCBSelectorResolver",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg2 = (cocos2d::extension::CCBSelectorResolver*)tolua_tousertype(tolua_S,4,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::extension::NodeLoaderListener* arg3;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,5,"NodeLoaderListener",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg3 = (cocos2d::extension::NodeLoaderListener*)tolua_tousertype(tolua_S,5,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0, arg1, arg2, arg3);
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
	    return 1;
		}
	}while(0);
	do{
		if (argc == 0) {
			cobj = new cocos2d::extension::CCBReader();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
	    return 1;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_CCBReader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCBReader)");
	return 0;
}

int lua_register_cocos2dx_extension_CCBReader(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"CCBReader");
	tolua_cclass(tolua_S,"CCBReader","CCBReader","",NULL);

	tolua_beginmodule(tolua_S,"CCBReader");
		tolua_function(tolua_S,"addOwnerOutletName",lua_cocos2dx_extension_CCBReader_addOwnerOutletName);
		tolua_function(tolua_S,"getOwnerCallbackNames",lua_cocos2dx_extension_CCBReader_getOwnerCallbackNames);
		tolua_function(tolua_S,"setCCBRootPath",lua_cocos2dx_extension_CCBReader_setCCBRootPath);
		tolua_function(tolua_S,"addOwnerOutletNode",lua_cocos2dx_extension_CCBReader_addOwnerOutletNode);
		tolua_function(tolua_S,"getOwnerCallbackNodes",lua_cocos2dx_extension_CCBReader_getOwnerCallbackNodes);
		tolua_function(tolua_S,"readSoundKeyframesForSeq",lua_cocos2dx_extension_CCBReader_readSoundKeyframesForSeq);
		tolua_function(tolua_S,"getCCBRootPath",lua_cocos2dx_extension_CCBReader_getCCBRootPath);
		tolua_function(tolua_S,"getOwnerOutletNodes",lua_cocos2dx_extension_CCBReader_getOwnerOutletNodes);
		tolua_function(tolua_S,"readUTF8",lua_cocos2dx_extension_CCBReader_readUTF8);
		tolua_function(tolua_S,"getOwnerOutletNames",lua_cocos2dx_extension_CCBReader_getOwnerOutletNames);
		tolua_function(tolua_S,"setActionManager",lua_cocos2dx_extension_CCBReader_setAnimationManager);
		tolua_function(tolua_S,"readCallbackKeyframesForSeq",lua_cocos2dx_extension_CCBReader_readCallbackKeyframesForSeq);
		tolua_function(tolua_S,"getAnimationManagersForNodes",lua_cocos2dx_extension_CCBReader_getAnimationManagersForNodes);
		tolua_function(tolua_S,"getNodesWithAnimationManagers",lua_cocos2dx_extension_CCBReader_getNodesWithAnimationManagers);
		tolua_function(tolua_S,"getActionManager",lua_cocos2dx_extension_CCBReader_getAnimationManager);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_CCBReader_constructor);
		tolua_function(tolua_S,"setResolutionScale", lua_cocos2dx_extension_CCBReader_setResolutionScale);
	tolua_endmodule(tolua_S);
	return 1;
}


static int lua_cocos2dx_extension_Scale9Sprite_resizableSpriteWithCapInsets(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_resizableSpriteWithCapInsets'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= luaval_to_rect(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cocos2d::extension::Scale9Sprite* ret = cobj->resizableSpriteWithCapInsets(arg0);
		tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_resizableSpriteWithCapInsets'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrameName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrameName'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	do{
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithSpriteFrameName(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	do{
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithSpriteFrameName(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrameName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setOpacityModifyRGB(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setOpacityModifyRGB'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setOpacityModifyRGB(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setOpacityModifyRGB'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setContentSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setContentSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setContentSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setContentSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setInsetBottom(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetBottom'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setInsetBottom(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetBottom'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_isOpacityModifyRGB(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_isOpacityModifyRGB'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isOpacityModifyRGB();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_isOpacityModifyRGB'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setOpacity(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setOpacity'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		uint16_t arg0;
		ok &= luaval_to_uint16(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setOpacity(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setOpacity'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setInsetTop(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetTop'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setInsetTop(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetTop'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_updateDisplayedOpacity(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_updateDisplayedOpacity'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		uint16_t arg0;
		ok &= luaval_to_uint16(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->updateDisplayedOpacity(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_updateDisplayedOpacity'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_init(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_init'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_init'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setPreferredSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setPreferredSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setPreferredSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setPreferredSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getOpacity(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getOpacity'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		unsigned char ret = cobj->getOpacity();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getOpacity'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setSpriteFrame(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setSpriteFrame'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::SpriteFrame* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteFrame",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setSpriteFrame(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setSpriteFrame'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getColor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getColor'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Color3B ret = cobj->getColor();
		color3b_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getColor'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_initWithBatchNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_initWithBatchNode'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	do{
		if (argc == 3) {
			cocos2d::SpriteBatchNode* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteBatchNode",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg2;
			ok &= luaval_to_rect(tolua_S, 4, &arg2);

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithBatchNode(arg0, arg1, arg2);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	do{
		if (argc == 4) {
			cocos2d::SpriteBatchNode* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteBatchNode",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);

			if (!ok) { ok = true; break; }
			bool arg2;
			ok &= luaval_to_boolean(tolua_S, 4,&arg2);

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg3;
			ok &= luaval_to_rect(tolua_S, 5, &arg3);

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithBatchNode(arg0, arg1, arg2, arg3);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 4);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_initWithBatchNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getInsetBottom(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetBottom'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		float ret = cobj->getInsetBottom();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetBottom'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getCapInsets(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getCapInsets'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Rect ret = cobj->getCapInsets();
		rect_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getCapInsets'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_updateWithBatchNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_updateWithBatchNode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 4) {
		cocos2d::SpriteBatchNode* arg0;
		cocos2d::Rect arg1;
		bool arg2;
		cocos2d::Rect arg3;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteBatchNode",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_rect(tolua_S, 3, &arg1);
		ok &= luaval_to_boolean(tolua_S, 4,&arg2);
		ok &= luaval_to_rect(tolua_S, 5, &arg3);
		if(!ok)
			return 0;
		bool ret = cobj->updateWithBatchNode(arg0, arg1, arg2, arg3);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 4);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_updateWithBatchNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getInsetRight(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetRight'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		float ret = cobj->getInsetRight();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetRight'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getOriginalSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getOriginalSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Size ret = cobj->getOriginalSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getOriginalSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_initWithFile(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_initWithFile'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	do{
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithFile(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	do{
		if (argc == 3) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg2;
			ok &= luaval_to_rect(tolua_S, 4, &arg2);

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithFile(arg0, arg1, arg2);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	do{
		if (argc == 2) {
			cocos2d::Rect arg0;
			ok &= luaval_to_rect(tolua_S, 2, &arg0);

			if (!ok) { ok = true; break; }
			const char* arg1;
			std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithFile(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	do{
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithFile(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_initWithFile'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setColor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setColor'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Color3B arg0;
		ok &= luaval_to_color3b(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setColor(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setColor'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getInsetTop(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetTop'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		float ret = cobj->getInsetTop();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetTop'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setInsetLeft(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetLeft'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setInsetLeft(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetLeft'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrame(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrame'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	do{
		if (argc == 1) {
			cocos2d::SpriteFrame* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteFrame",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithSpriteFrame(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	do{
		if (argc == 2) {
			cocos2d::SpriteFrame* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteFrame",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);

			if (!ok) { ok = true; break; }
		bool ret = cobj->initWithSpriteFrame(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrame'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getPreferredSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getPreferredSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Size ret = cobj->getPreferredSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getPreferredSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setCapInsets(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setCapInsets'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= luaval_to_rect(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setCapInsets(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setCapInsets'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_getInsetLeft(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetLeft'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		float ret = cobj->getInsetLeft();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetLeft'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_updateDisplayedColor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_updateDisplayedColor'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Color3B arg0;
		ok &= luaval_to_color3b(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->updateDisplayedColor(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_updateDisplayedColor'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_setInsetRight(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetRight'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		double arg0;
		ok &= luaval_to_number(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setInsetRight(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetRight'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_create(lua_State* tolua_S)
{
	int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S)-1;

	do {
		if (argc == 3) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg2;
			ok &= luaval_to_rect(tolua_S, 4, &arg2);
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::create(arg0, arg1, arg2);
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	do {
		if (argc == 0) {
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::create();
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	do {
		if (argc == 2) {
			cocos2d::Rect arg0;
			ok &= luaval_to_rect(tolua_S, 2, &arg0);
			if (!ok) { ok = true; break; }
			const char* arg1;
			std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::create(arg0, arg1);
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::create(arg0, arg1);
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::create(arg0);
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_create'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_createWithSpriteFrameName(lua_State* tolua_S)
{
	int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S)-1;

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::createWithSpriteFrameName(arg0, arg1);
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::createWithSpriteFrameName(arg0);
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_createWithSpriteFrameName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_createWithSpriteFrame(lua_State* tolua_S)
{
	int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S)-1;

	do {
		if (argc == 2) {
			cocos2d::SpriteFrame* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteFrame",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::createWithSpriteFrame(arg0, arg1);
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	do {
		if (argc == 1) {
			cocos2d::SpriteFrame* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteFrame",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::createWithSpriteFrame(arg0);
			tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_createWithSpriteFrame'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_Scale9Sprite_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::Scale9Sprite* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj = new cocos2d::extension::Scale9Sprite();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"Scale9Sprite");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_Scale9Sprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Scale9Sprite)");
	return 0;
}

int lua_register_cocos2dx_extension_Scale9Sprite(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"Scale9Sprite");
	tolua_cclass(tolua_S,"Scale9Sprite","Scale9Sprite","NodeRGBA",NULL);

	tolua_beginmodule(tolua_S,"Scale9Sprite");
		tolua_function(tolua_S,"resizableSpriteWithCapInsets",lua_cocos2dx_extension_Scale9Sprite_resizableSpriteWithCapInsets);
		tolua_function(tolua_S,"initWithSpriteFrameName",lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrameName);
		tolua_function(tolua_S,"setOpacityModifyRGB",lua_cocos2dx_extension_Scale9Sprite_setOpacityModifyRGB);
		tolua_function(tolua_S,"setContentSize",lua_cocos2dx_extension_Scale9Sprite_setContentSize);
		tolua_function(tolua_S,"setInsetBottom",lua_cocos2dx_extension_Scale9Sprite_setInsetBottom);
		tolua_function(tolua_S,"isOpacityModifyRGB",lua_cocos2dx_extension_Scale9Sprite_isOpacityModifyRGB);
		tolua_function(tolua_S,"setOpacity",lua_cocos2dx_extension_Scale9Sprite_setOpacity);
		tolua_function(tolua_S,"setInsetTop",lua_cocos2dx_extension_Scale9Sprite_setInsetTop);
		tolua_function(tolua_S,"updateDisplayedOpacity",lua_cocos2dx_extension_Scale9Sprite_updateDisplayedOpacity);
		tolua_function(tolua_S,"init",lua_cocos2dx_extension_Scale9Sprite_init);
		tolua_function(tolua_S,"setPreferredSize",lua_cocos2dx_extension_Scale9Sprite_setPreferredSize);
		tolua_function(tolua_S,"getOpacity",lua_cocos2dx_extension_Scale9Sprite_getOpacity);
		tolua_function(tolua_S,"setSpriteFrame",lua_cocos2dx_extension_Scale9Sprite_setSpriteFrame);
		tolua_function(tolua_S,"getColor",lua_cocos2dx_extension_Scale9Sprite_getColor);
		tolua_function(tolua_S,"initWithBatchNode",lua_cocos2dx_extension_Scale9Sprite_initWithBatchNode);
		tolua_function(tolua_S,"getInsetBottom",lua_cocos2dx_extension_Scale9Sprite_getInsetBottom);
		tolua_function(tolua_S,"getCapInsets",lua_cocos2dx_extension_Scale9Sprite_getCapInsets);
		tolua_function(tolua_S,"updateWithBatchNode",lua_cocos2dx_extension_Scale9Sprite_updateWithBatchNode);
		tolua_function(tolua_S,"getInsetRight",lua_cocos2dx_extension_Scale9Sprite_getInsetRight);
		tolua_function(tolua_S,"getOriginalSize",lua_cocos2dx_extension_Scale9Sprite_getOriginalSize);
		tolua_function(tolua_S,"initWithFile",lua_cocos2dx_extension_Scale9Sprite_initWithFile);
		tolua_function(tolua_S,"setColor",lua_cocos2dx_extension_Scale9Sprite_setColor);
		tolua_function(tolua_S,"getInsetTop",lua_cocos2dx_extension_Scale9Sprite_getInsetTop);
		tolua_function(tolua_S,"setInsetLeft",lua_cocos2dx_extension_Scale9Sprite_setInsetLeft);
		tolua_function(tolua_S,"initWithSpriteFrame",lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrame);
		tolua_function(tolua_S,"getPreferredSize",lua_cocos2dx_extension_Scale9Sprite_getPreferredSize);
		tolua_function(tolua_S,"setCapInsets",lua_cocos2dx_extension_Scale9Sprite_setCapInsets);
		tolua_function(tolua_S,"getInsetLeft",lua_cocos2dx_extension_Scale9Sprite_getInsetLeft);
		tolua_function(tolua_S,"updateDisplayedColor",lua_cocos2dx_extension_Scale9Sprite_updateDisplayedColor);
		tolua_function(tolua_S,"setInsetRight",lua_cocos2dx_extension_Scale9Sprite_setInsetRight);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_Scale9Sprite_constructor);
		tolua_function(tolua_S,"create", lua_cocos2dx_extension_Scale9Sprite_create);
		tolua_function(tolua_S,"createWithSpriteFrameName", lua_cocos2dx_extension_Scale9Sprite_createWithSpriteFrameName);
		tolua_function(tolua_S,"createWithSpriteFrame", lua_cocos2dx_extension_Scale9Sprite_createWithSpriteFrame);
	tolua_endmodule(tolua_S);
	return 1;
}


static int lua_cocos2dx_extension_ControlButton_setTitleColorDispatchTable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleColorDispatchTable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Dictionary* arg0;
		ok &= luaval_to_dictionary(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setTitleColorDispatchTable(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleColorDispatchTable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_isPushed(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_isPushed'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isPushed();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_isPushed'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setSelected(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setSelected'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setSelected(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setSelected'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleLabelForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Node* arg0;
		cocos2d::extension::Control::State arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleLabelForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_ccTouchBegan(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_ccTouchBegan'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#pragma warning NO CONVERSION TO NATIVE FOR Event*;
		if(!ok)
			return 0;
		bool ret = cobj->ccTouchBegan(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_ccTouchBegan'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setAdjustBackgroundImage(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_ccTouchEnded(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_ccTouchEnded'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#pragma warning NO CONVERSION TO NATIVE FOR Event*;
		if(!ok)
			return 0;
		cobj->ccTouchEnded(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_ccTouchEnded'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setHighlighted(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setHighlighted'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setHighlighted(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setHighlighted'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setZoomOnTouchDown(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setBackgroundSpriteDispatchTable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteDispatchTable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Dictionary* arg0;
		ok &= luaval_to_dictionary(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setBackgroundSpriteDispatchTable(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteDispatchTable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::String* arg0;
		cocos2d::extension::Control::State arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"String",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::String*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleDispatchTable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleDispatchTable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Dictionary* ret = cobj->getTitleDispatchTable();
		dictionary_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleDispatchTable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= luaval_to_point(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setLabelAnchorPoint(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getPreferredSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getPreferredSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Size ret = cobj->getPreferredSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getPreferredSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Point ret = cobj->getLabelAnchorPoint();
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_initWithBackgroundSprite(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_initWithBackgroundSprite'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Scale9Sprite* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithBackgroundSprite(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_initWithBackgroundSprite'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		float ret = cobj->getTitleTTFSizeForState(arg0);
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleDispatchTable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleDispatchTable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Dictionary* arg0;
		ok &= luaval_to_dictionary(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setTitleDispatchTable(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleDispatchTable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setOpacity(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setOpacity'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		uint16_t arg0;
		ok &= luaval_to_uint16(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setOpacity(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setOpacity'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_init(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_init'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_init'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleTTFForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		cocos2d::extension::Control::State arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleTTFForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		double arg0;
		cocos2d::extension::Control::State arg1;
		ok &= luaval_to_number(tolua_S, 2,&arg0);
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleTTFSizeForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleLabel(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleLabel'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Node* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setTitleLabel(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleLabel'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_ccTouchMoved(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_ccTouchMoved'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#pragma warning NO CONVERSION TO NATIVE FOR Event*;
		if(!ok)
			return 0;
		cobj->ccTouchMoved(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_ccTouchMoved'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getOpacity(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getOpacity'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		unsigned char ret = cobj->getOpacity();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getOpacity'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getCurrentTitleColor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitleColor'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Color3B ret = cobj->getCurrentTitleColor();
		color3b_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitleColor'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleColorDispatchTable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleColorDispatchTable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Dictionary* ret = cobj->getTitleColorDispatchTable();
		dictionary_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleColorDispatchTable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setEnabled(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setEnabled'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setEnabled(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setEnabled'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setBackgroundSprite(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSprite'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Scale9Sprite* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setBackgroundSprite(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSprite'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cocos2d::extension::Scale9Sprite* ret = cobj->getBackgroundSpriteForState(arg0);
		tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getColor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getColor'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Color3B ret = cobj->getColor();
		color3b_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getColor'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setMargins(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setMargins'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		int arg0;
		int arg1;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setMargins(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setMargins'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_needsLayout(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_needsLayout'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->needsLayout();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_needsLayout'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 3) {
		std::string arg0;
		const char* arg1;
		double arg2;
		ok &= luaval_to_std_string(tolua_S, 2,&arg0);
		std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
		ok &= luaval_to_number(tolua_S, 4,&arg2);
		if(!ok)
			return 0;
		bool ret = cobj->initWithTitleAndFontNameAndFontSize(arg0, arg1, arg2);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 3);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getCurrentTitle(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitle'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::String* ret = cobj->getCurrentTitle();
		tolua_pushusertype(tolua_S,ret,"String");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitle'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getHorizontalOrigin(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getHorizontalOrigin'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		int ret = cobj->getHorizontalOrigin();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getHorizontalOrigin'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleTTFForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		const char* ret = cobj->getTitleTTFForState(arg0);
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getBackgroundSprite(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSprite'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::extension::Scale9Sprite* ret = cobj->getBackgroundSprite();
		tolua_pushusertype(tolua_S,ret,"Scale9Sprite");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSprite'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleColorForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleColorForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cocos2d::Color3B ret = cobj->getTitleColorForState(arg0);
		color3b_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleColorForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleColorForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleColorForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Color3B arg0;
		cocos2d::extension::Control::State arg1;
		ok &= luaval_to_color3b(tolua_S, 2, &arg0);
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleColorForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleColorForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->doesAdjustBackgroundImage();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::SpriteFrame* arg0;
		cocos2d::extension::Control::State arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"SpriteFrame",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setBackgroundSpriteFrameForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::extension::Scale9Sprite* arg0;
		cocos2d::extension::Control::State arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setBackgroundSpriteForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setColor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setColor'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Color3B arg0;
		ok &= luaval_to_color3b(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setColor(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setColor'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleLabelDispatchTable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelDispatchTable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Dictionary* ret = cobj->getTitleLabelDispatchTable();
		dictionary_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelDispatchTable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Node* arg0;
		cocos2d::extension::Scale9Sprite* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithLabelAndBackgroundSprite(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setPreferredSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setPreferredSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setPreferredSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setPreferredSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleLabelDispatchTable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelDispatchTable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Dictionary* arg0;
		ok &= luaval_to_dictionary(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setTitleLabelDispatchTable(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelDispatchTable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleLabel(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleLabel'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Node* ret = cobj->getTitleLabel();
		tolua_pushusertype(tolua_S,ret,"Node");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleLabel'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_ccTouchCancelled(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_ccTouchCancelled'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#pragma warning NO CONVERSION TO NATIVE FOR Event*;
		if(!ok)
			return 0;
		cobj->ccTouchCancelled(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_ccTouchCancelled'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getVerticalMargin(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getVerticalMargin'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		int ret = cobj->getVerticalMargin();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getVerticalMargin'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getBackgroundSpriteDispatchTable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteDispatchTable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Dictionary* ret = cobj->getBackgroundSpriteDispatchTable();
		dictionary_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteDispatchTable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleLabelForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cocos2d::Node* ret = cobj->getTitleLabelForState(arg0);
		tolua_pushusertype(tolua_S,ret,"Node");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_setTitleBMFontForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleBMFontForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		cocos2d::extension::Control::State arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleBMFontForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleBMFontForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleBMFontForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleBMFontForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		const char* ret = cobj->getTitleBMFontForState(arg0);
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleBMFontForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->getZoomOnTouchDown();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_getTitleForState(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleForState'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cocos2d::String* ret = cobj->getTitleForState(arg0);
		tolua_pushusertype(tolua_S,ret,"String");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleForState'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_create(lua_State* tolua_S)
{
	int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S)-1;

	do {
		if (argc == 1) {
			cocos2d::extension::Scale9Sprite* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,2,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0);
			tolua_pushusertype(tolua_S,ret,"ControlButton");
			return 1;
		}
	} while (0);
	do {
		if (argc == 0) {
			cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create();
			tolua_pushusertype(tolua_S,ret,"ControlButton");
			return 1;
		}
	} while (0);
	do {
		if (argc == 2) {
			cocos2d::Node* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* arg1;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0, arg1);
			tolua_pushusertype(tolua_S,ret,"ControlButton");
			return 1;
		}
	} while (0);
	do {
		if (argc == 3) {
			std::string arg0;
			ok &= luaval_to_std_string(tolua_S, 2,&arg0);
			if (!ok) { ok = true; break; }
			const char* arg1;
			std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
			if (!ok) { ok = true; break; }
			double arg2;
			ok &= luaval_to_number(tolua_S, 4,&arg2);
			if (!ok) { ok = true; break; }
			cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0, arg1, arg2);
			tolua_pushusertype(tolua_S,ret,"ControlButton");
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 3);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_create'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ControlButton_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ControlButton* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj = new cocos2d::extension::ControlButton();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ControlButton");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_ControlButton_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ControlButton)");
	return 0;
}

int lua_register_cocos2dx_extension_ControlButton(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"ControlButton");
	tolua_cclass(tolua_S,"ControlButton","ControlButton","Control",NULL);

	tolua_beginmodule(tolua_S,"ControlButton");
		tolua_function(tolua_S,"setTitleColorDispatchTable",lua_cocos2dx_extension_ControlButton_setTitleColorDispatchTable);
		tolua_function(tolua_S,"isPushed",lua_cocos2dx_extension_ControlButton_isPushed);
		tolua_function(tolua_S,"setSelected",lua_cocos2dx_extension_ControlButton_setSelected);
		tolua_function(tolua_S,"setTitleLabelForState",lua_cocos2dx_extension_ControlButton_setTitleLabelForState);
		tolua_function(tolua_S,"ccTouchBegan",lua_cocos2dx_extension_ControlButton_ccTouchBegan);
		tolua_function(tolua_S,"setAdjustBackgroundImage",lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage);
		tolua_function(tolua_S,"ccTouchEnded",lua_cocos2dx_extension_ControlButton_ccTouchEnded);
		tolua_function(tolua_S,"setHighlighted",lua_cocos2dx_extension_ControlButton_setHighlighted);
		tolua_function(tolua_S,"setZoomOnTouchDown",lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown);
		tolua_function(tolua_S,"setBackgroundSpriteDispatchTable",lua_cocos2dx_extension_ControlButton_setBackgroundSpriteDispatchTable);
		tolua_function(tolua_S,"setTitleForState",lua_cocos2dx_extension_ControlButton_setTitleForState);
		tolua_function(tolua_S,"getTitleDispatchTable",lua_cocos2dx_extension_ControlButton_getTitleDispatchTable);
		tolua_function(tolua_S,"setLabelAnchorPoint",lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint);
		tolua_function(tolua_S,"getPreferredSize",lua_cocos2dx_extension_ControlButton_getPreferredSize);
		tolua_function(tolua_S,"getLabelAnchorPoint",lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint);
		tolua_function(tolua_S,"initWithBackgroundSprite",lua_cocos2dx_extension_ControlButton_initWithBackgroundSprite);
		tolua_function(tolua_S,"getTitleTTFSizeForState",lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState);
		tolua_function(tolua_S,"setTitleDispatchTable",lua_cocos2dx_extension_ControlButton_setTitleDispatchTable);
		tolua_function(tolua_S,"setOpacity",lua_cocos2dx_extension_ControlButton_setOpacity);
		tolua_function(tolua_S,"init",lua_cocos2dx_extension_ControlButton_init);
		tolua_function(tolua_S,"setTitleTTFForState",lua_cocos2dx_extension_ControlButton_setTitleTTFForState);
		tolua_function(tolua_S,"setTitleTTFSizeForState",lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState);
		tolua_function(tolua_S,"setTitleLabel",lua_cocos2dx_extension_ControlButton_setTitleLabel);
		tolua_function(tolua_S,"ccTouchMoved",lua_cocos2dx_extension_ControlButton_ccTouchMoved);
		tolua_function(tolua_S,"getOpacity",lua_cocos2dx_extension_ControlButton_getOpacity);
		tolua_function(tolua_S,"getCurrentTitleColor",lua_cocos2dx_extension_ControlButton_getCurrentTitleColor);
		tolua_function(tolua_S,"getTitleColorDispatchTable",lua_cocos2dx_extension_ControlButton_getTitleColorDispatchTable);
		tolua_function(tolua_S,"setEnabled",lua_cocos2dx_extension_ControlButton_setEnabled);
		tolua_function(tolua_S,"setBackgroundSprite",lua_cocos2dx_extension_ControlButton_setBackgroundSprite);
		tolua_function(tolua_S,"getBackgroundSpriteForState",lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState);
		tolua_function(tolua_S,"getColor",lua_cocos2dx_extension_ControlButton_getColor);
		tolua_function(tolua_S,"setMargins",lua_cocos2dx_extension_ControlButton_setMargins);
		tolua_function(tolua_S,"needsLayout",lua_cocos2dx_extension_ControlButton_needsLayout);
		tolua_function(tolua_S,"initWithTitleAndFontNameAndFontSize",lua_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize);
		tolua_function(tolua_S,"getCurrentTitle",lua_cocos2dx_extension_ControlButton_getCurrentTitle);
		tolua_function(tolua_S,"getHorizontalOrigin",lua_cocos2dx_extension_ControlButton_getHorizontalOrigin);
		tolua_function(tolua_S,"getTitleTTFForState",lua_cocos2dx_extension_ControlButton_getTitleTTFForState);
		tolua_function(tolua_S,"getBackgroundSprite",lua_cocos2dx_extension_ControlButton_getBackgroundSprite);
		tolua_function(tolua_S,"getTitleColorForState",lua_cocos2dx_extension_ControlButton_getTitleColorForState);
		tolua_function(tolua_S,"setTitleColorForState",lua_cocos2dx_extension_ControlButton_setTitleColorForState);
		tolua_function(tolua_S,"doesAdjustBackgroundImage",lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage);
		tolua_function(tolua_S,"setBackgroundSpriteFrameForState",lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState);
		tolua_function(tolua_S,"setBackgroundSpriteForState",lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState);
		tolua_function(tolua_S,"setColor",lua_cocos2dx_extension_ControlButton_setColor);
		tolua_function(tolua_S,"getTitleLabelDispatchTable",lua_cocos2dx_extension_ControlButton_getTitleLabelDispatchTable);
		tolua_function(tolua_S,"initWithLabelAndBackgroundSprite",lua_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite);
		tolua_function(tolua_S,"setPreferredSize",lua_cocos2dx_extension_ControlButton_setPreferredSize);
		tolua_function(tolua_S,"setTitleLabelDispatchTable",lua_cocos2dx_extension_ControlButton_setTitleLabelDispatchTable);
		tolua_function(tolua_S,"getTitleLabel",lua_cocos2dx_extension_ControlButton_getTitleLabel);
		tolua_function(tolua_S,"ccTouchCancelled",lua_cocos2dx_extension_ControlButton_ccTouchCancelled);
		tolua_function(tolua_S,"getVerticalMargin",lua_cocos2dx_extension_ControlButton_getVerticalMargin);
		tolua_function(tolua_S,"getBackgroundSpriteDispatchTable",lua_cocos2dx_extension_ControlButton_getBackgroundSpriteDispatchTable);
		tolua_function(tolua_S,"getTitleLabelForState",lua_cocos2dx_extension_ControlButton_getTitleLabelForState);
		tolua_function(tolua_S,"setTitleBMFontForState",lua_cocos2dx_extension_ControlButton_setTitleBMFontForState);
		tolua_function(tolua_S,"getTitleBMFontForState",lua_cocos2dx_extension_ControlButton_getTitleBMFontForState);
		tolua_function(tolua_S,"getZoomOnTouchDown",lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown);
		tolua_function(tolua_S,"getTitleForState",lua_cocos2dx_extension_ControlButton_getTitleForState);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_ControlButton_constructor);
		tolua_function(tolua_S,"create", lua_cocos2dx_extension_ControlButton_create);
	tolua_endmodule(tolua_S);
	return 1;
}


static int lua_cocos2dx_extension_ScrollView_isClippingToBounds(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isClippingToBounds'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isClippingToBounds();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isClippingToBounds'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setContainer(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContainer'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Node* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setContainer(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContainer'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Point arg0;
		double arg1;
		ok &= luaval_to_point(tolua_S, 2, &arg0);
		ok &= luaval_to_number(tolua_S, 3,&arg1);
		if(!ok)
			return 0;
		cobj->setContentOffsetInDuration(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		double arg0;
		double arg1;
		ok &= luaval_to_number(tolua_S, 2,&arg0);
		ok &= luaval_to_number(tolua_S, 3,&arg1);
		if(!ok)
			return 0;
		cobj->setZoomScaleInDuration(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_addChild(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_addChild'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	do{
		if (argc == 2) {
			cocos2d::Node* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			int arg1;
			ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);

			if (!ok) { ok = true; break; }
		cobj->addChild(arg0, arg1);
		return 0;
		}
	}while(0);
	do{
		if (argc == 3) {
			cocos2d::Node* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			int arg1;
			ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);

			if (!ok) { ok = true; break; }
			int arg2;
			ok &= luaval_to_int32(tolua_S, 4,(int*)&arg2);

			if (!ok) { ok = true; break; }
		cobj->addChild(arg0, arg1, arg2);
		return 0;
		}
	}while(0);
	do{
		if (argc == 1) {
			cocos2d::Node* arg0;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
		cobj->addChild(arg0);
		return 0;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_addChild'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_ccTouchBegan(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_ccTouchBegan'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->ccTouchBegan(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_ccTouchBegan'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_getContainer(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getContainer'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Node* ret = cobj->getContainer();
		tolua_pushusertype(tolua_S,ret,"Node");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getContainer'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_ccTouchEnded(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_ccTouchEnded'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchEnded(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_ccTouchEnded'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_getDirection(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getDirection'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		int ret = (int)cobj->getDirection();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getDirection'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_getZoomScale(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getZoomScale'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		float ret = cobj->getZoomScale();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getZoomScale'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_updateInset(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_updateInset'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->updateInset();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_updateInset'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_initWithViewSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_initWithViewSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		bool ret = cobj->initWithViewSize(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	if (argc == 2) {
		cocos2d::Size arg0;
		cocos2d::Node* arg1;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithViewSize(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_initWithViewSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_pause(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_pause'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Object* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Object",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Object*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->pause(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_pause'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setDirection(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setDirection'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::ScrollView::Direction arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setDirection(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setDirection'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setBounceable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setBounceable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setBounceable(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setBounceable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setContentOffset(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContentOffset'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= luaval_to_point(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setContentOffset(arg0);
		return 0;
	}
	if (argc == 2) {
		cocos2d::Point arg0;
		bool arg1;
		ok &= luaval_to_point(tolua_S, 2, &arg0);
		ok &= luaval_to_boolean(tolua_S, 3,&arg1);
		if(!ok)
			return 0;
		cobj->setContentOffset(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContentOffset'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_isDragging(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isDragging'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isDragging();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isDragging'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_init(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_init'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_init'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_isBounceable(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isBounceable'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isBounceable();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isBounceable'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_getContentSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getContentSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Size ret = cobj->getContentSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getContentSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_ccTouchMoved(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_ccTouchMoved'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchMoved(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_ccTouchMoved'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setTouchEnabled(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setTouchEnabled'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setTouchEnabled(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setTouchEnabled'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_getContentOffset(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getContentOffset'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Point ret = cobj->getContentOffset();
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getContentOffset'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_resume(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_resume'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Object* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Object",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Object*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->resume(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_resume'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setClippingToBounds(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setClippingToBounds'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setClippingToBounds(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setClippingToBounds'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setViewSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setViewSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setViewSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setViewSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_getViewSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getViewSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Size ret = cobj->getViewSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getViewSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_maxContainerOffset(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_maxContainerOffset'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Point ret = cobj->maxContainerOffset();
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_maxContainerOffset'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setContentSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContentSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setContentSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContentSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_isTouchMoved(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isTouchMoved'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->isTouchMoved();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isTouchMoved'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_isNodeVisible(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isNodeVisible'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Node* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->isNodeVisible(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isNodeVisible'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_ccTouchCancelled(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_ccTouchCancelled'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchCancelled(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_ccTouchCancelled'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_minContainerOffset(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_minContainerOffset'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Point ret = cobj->minContainerOffset();
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_minContainerOffset'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_registerWithTouchDispatcher(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_registerWithTouchDispatcher'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->registerWithTouchDispatcher();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_registerWithTouchDispatcher'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_setZoomScale(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setZoomScale'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	do{
		if (argc == 2) {
			double arg0;
			ok &= luaval_to_number(tolua_S, 2,&arg0);

			if (!ok) { ok = true; break; }
			bool arg1;
			ok &= luaval_to_boolean(tolua_S, 3,&arg1);

			if (!ok) { ok = true; break; }
		cobj->setZoomScale(arg0, arg1);
		return 0;
		}
	}while(0);
	do{
		if (argc == 1) {
			double arg0;
			ok &= luaval_to_number(tolua_S, 2,&arg0);

			if (!ok) { ok = true; break; }
		cobj->setZoomScale(arg0);
		return 0;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setZoomScale'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_create(lua_State* tolua_S)
{
	int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S)-1;

	do {
		if (argc == 0) {
			cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create();
			tolua_pushusertype(tolua_S,ret,"ScrollView");
			return 1;
		}
	} while (0);
	do {
		if (argc == 1) {
			cocos2d::Size arg0;
			ok &= luaval_to_size(tolua_S, 2, &arg0);
			if (!ok) { ok = true; break; }
			cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create(arg0);
			tolua_pushusertype(tolua_S,ret,"ScrollView");
			return 1;
		}
	} while (0);
	do {
		if (argc == 2) {
			cocos2d::Size arg0;
			ok &= luaval_to_size(tolua_S, 2, &arg0);
			if (!ok) { ok = true; break; }
			cocos2d::Node* arg1;
			#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create(arg0, arg1);
			tolua_pushusertype(tolua_S,ret,"ScrollView");
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_create'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_ScrollView_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::ScrollView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj = new cocos2d::extension::ScrollView();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ScrollView");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_ScrollView_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ScrollView)");
	return 0;
}

int lua_register_cocos2dx_extension_ScrollView(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"ScrollView");
	tolua_cclass(tolua_S,"ScrollView","ScrollView","Layer",NULL);

	tolua_beginmodule(tolua_S,"ScrollView");
		tolua_function(tolua_S,"isClippingToBounds",lua_cocos2dx_extension_ScrollView_isClippingToBounds);
		tolua_function(tolua_S,"setContainer",lua_cocos2dx_extension_ScrollView_setContainer);
		tolua_function(tolua_S,"setContentOffsetInDuration",lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration);
		tolua_function(tolua_S,"setZoomScaleInDuration",lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration);
		tolua_function(tolua_S,"addChild",lua_cocos2dx_extension_ScrollView_addChild);
		tolua_function(tolua_S,"ccTouchBegan",lua_cocos2dx_extension_ScrollView_ccTouchBegan);
		tolua_function(tolua_S,"getContainer",lua_cocos2dx_extension_ScrollView_getContainer);
		tolua_function(tolua_S,"ccTouchEnded",lua_cocos2dx_extension_ScrollView_ccTouchEnded);
		tolua_function(tolua_S,"getDirection",lua_cocos2dx_extension_ScrollView_getDirection);
		tolua_function(tolua_S,"getZoomScale",lua_cocos2dx_extension_ScrollView_getZoomScale);
		tolua_function(tolua_S,"updateInset",lua_cocos2dx_extension_ScrollView_updateInset);
		tolua_function(tolua_S,"initWithViewSize",lua_cocos2dx_extension_ScrollView_initWithViewSize);
		tolua_function(tolua_S,"pause",lua_cocos2dx_extension_ScrollView_pause);
		tolua_function(tolua_S,"setDirection",lua_cocos2dx_extension_ScrollView_setDirection);
		tolua_function(tolua_S,"setBounceable",lua_cocos2dx_extension_ScrollView_setBounceable);
		tolua_function(tolua_S,"setContentOffset",lua_cocos2dx_extension_ScrollView_setContentOffset);
		tolua_function(tolua_S,"isDragging",lua_cocos2dx_extension_ScrollView_isDragging);
		tolua_function(tolua_S,"init",lua_cocos2dx_extension_ScrollView_init);
		tolua_function(tolua_S,"isBounceable",lua_cocos2dx_extension_ScrollView_isBounceable);
		tolua_function(tolua_S,"getContentSize",lua_cocos2dx_extension_ScrollView_getContentSize);
		tolua_function(tolua_S,"ccTouchMoved",lua_cocos2dx_extension_ScrollView_ccTouchMoved);
		tolua_function(tolua_S,"setTouchEnabled",lua_cocos2dx_extension_ScrollView_setTouchEnabled);
		tolua_function(tolua_S,"getContentOffset",lua_cocos2dx_extension_ScrollView_getContentOffset);
		tolua_function(tolua_S,"resume",lua_cocos2dx_extension_ScrollView_resume);
		tolua_function(tolua_S,"setClippingToBounds",lua_cocos2dx_extension_ScrollView_setClippingToBounds);
		tolua_function(tolua_S,"setViewSize",lua_cocos2dx_extension_ScrollView_setViewSize);
		tolua_function(tolua_S,"getViewSize",lua_cocos2dx_extension_ScrollView_getViewSize);
		tolua_function(tolua_S,"maxContainerOffset",lua_cocos2dx_extension_ScrollView_maxContainerOffset);
		tolua_function(tolua_S,"setContentSize",lua_cocos2dx_extension_ScrollView_setContentSize);
		tolua_function(tolua_S,"isTouchMoved",lua_cocos2dx_extension_ScrollView_isTouchMoved);
		tolua_function(tolua_S,"isNodeVisible",lua_cocos2dx_extension_ScrollView_isNodeVisible);
		tolua_function(tolua_S,"ccTouchCancelled",lua_cocos2dx_extension_ScrollView_ccTouchCancelled);
		tolua_function(tolua_S,"minContainerOffset",lua_cocos2dx_extension_ScrollView_minContainerOffset);
		tolua_function(tolua_S,"registerWithTouchDispatcher",lua_cocos2dx_extension_ScrollView_registerWithTouchDispatcher);
		tolua_function(tolua_S,"setZoomScale",lua_cocos2dx_extension_ScrollView_setZoomScale);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_ScrollView_constructor);
		tolua_function(tolua_S,"create", lua_cocos2dx_extension_ScrollView_create);
	tolua_endmodule(tolua_S);
	return 1;
}


static int lua_cocos2dx_extension_CCBAnimationManager_moveAnimationsFromNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_moveAnimationsFromNode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Node* arg0;
		cocos2d::Node* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->moveAnimationsFromNode(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_moveAnimationsFromNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_setAutoPlaySequenceId(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setAutoPlaySequenceId'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setAutoPlaySequenceId(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setAutoPlaySequenceId'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNames(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNames'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getDocumentCallbackNames();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNames'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_actionForSoundChannel(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_actionForSoundChannel'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::CCBSequenceProperty* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"CCBSequenceProperty",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::CCBSequenceProperty*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cocos2d::Object* ret = cobj->actionForSoundChannel(arg0);
		tolua_pushusertype(tolua_S,ret,"Object");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_actionForSoundChannel'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_setBaseValue(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setBaseValue'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 3) {
		cocos2d::Object* arg0;
		cocos2d::Node* arg1;
		const char* arg2;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Object",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Object*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
		std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
		if(!ok)
			return 0;
		cobj->setBaseValue(arg0, arg1, arg2);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 3);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setBaseValue'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNodes(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNodes'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getDocumentOutletNodes();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNodes'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_addNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addNode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Node* arg0;
		cocos2d::Dictionary* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_dictionary(tolua_S, 3, &arg1);
		if(!ok)
			return 0;
		cobj->addNode(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getLastCompletedSequenceName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getLastCompletedSequenceName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		std::string ret = cobj->getLastCompletedSequenceName();
		tolua_pushcppstring(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getLastCompletedSequenceName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_setRootNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setRootNode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Node* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setRootNode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setRootNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->addDocumentOutletName(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getSequences(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getSequences'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getSequences();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getSequences'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getRootContainerSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getRootContainerSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Size ret = cobj->getRootContainerSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getRootContainerSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_setDocumentControllerName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setDocumentControllerName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setDocumentControllerName(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setDocumentControllerName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getContainerSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getContainerSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Node* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cocos2d::Size ret = cobj->getContainerSize(arg0);
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getContainerSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_actionForCallbackChannel(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_actionForCallbackChannel'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::CCBSequenceProperty* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"CCBSequenceProperty",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::CCBSequenceProperty*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cocos2d::Object* ret = cobj->actionForCallbackChannel(arg0);
		tolua_pushusertype(tolua_S,ret,"Object");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_actionForCallbackChannel'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNames(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNames'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getDocumentOutletNames();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNames'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_init(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_init'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_init'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getKeyframeCallbacks(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getKeyframeCallbacks'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getKeyframeCallbacks();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getKeyframeCallbacks'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		double arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_number(tolua_S, 3,&arg1);
		if(!ok)
			return 0;
		cobj->runAnimationsForSequenceNamedTweenDuration(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_setRootContainerSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setRootContainerSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setRootContainerSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setRootContainerSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		int arg0;
		double arg1;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		ok &= luaval_to_number(tolua_S, 3,&arg1);
		if(!ok)
			return 0;
		cobj->runAnimationsForSequenceIdTweenDuration(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getRunningSequenceName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getRunningSequenceName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		const char* ret = cobj->getRunningSequenceName();
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getRunningSequenceName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getAutoPlaySequenceId(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getAutoPlaySequenceId'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		int ret = cobj->getAutoPlaySequenceId();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getAutoPlaySequenceId'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		std::string arg0;
		ok &= luaval_to_std_string(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->addDocumentCallbackName(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getRootNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getRootNode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Node* ret = cobj->getRootNode();
		tolua_pushusertype(tolua_S,ret,"Node");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getRootNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletNode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Node* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->addDocumentOutletNode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_setDelegate(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setDelegate'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::CCBAnimationManagerDelegate* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"CCBAnimationManagerDelegate",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::CCBAnimationManagerDelegate*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setDelegate(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setDelegate'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackNode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackNode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Node* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->addDocumentCallbackNode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackNode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_setCallFunc(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setCallFunc'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::CallFunc* arg0;
		std::string arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"CallFunc",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::CallFunc*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_std_string(tolua_S, 3,&arg1);
		if(!ok)
			return 0;
		cobj->setCallFunc(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setCallFunc'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getDelegate(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDelegate'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::extension::CCBAnimationManagerDelegate* ret = cobj->getDelegate();
		tolua_pushusertype(tolua_S,ret,"CCBAnimationManagerDelegate");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDelegate'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamed(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamed'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		if(!ok)
			return 0;
		cobj->runAnimationsForSequenceNamed(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamed'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNodes(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNodes'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::Array* ret = cobj->getDocumentCallbackNodes();
		array_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNodes'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_setSequences(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setSequences'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Array* arg0;
		ok &= luaval_to_array(tolua_S,  2, &arg0);
		if(!ok)
			return 0;
		cobj->setSequences(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setSequences'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_debug(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_debug'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->debug();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_debug'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getDocumentControllerName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentControllerName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		std::string ret = cobj->getDocumentControllerName();
		tolua_pushcppstring(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentControllerName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::CCBAnimationManager* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj = new cocos2d::extension::CCBAnimationManager();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBAnimationManager");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_CCBAnimationManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCBAnimationManager)");
	return 0;
}

int lua_register_cocos2dx_extension_CCBAnimationManager(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"CCBAnimationManager");
	tolua_cclass(tolua_S,"CCBAnimationManager","CCBAnimationManager","",NULL);

	tolua_beginmodule(tolua_S,"CCBAnimationManager");
		tolua_function(tolua_S,"moveAnimationsFromNode",lua_cocos2dx_extension_CCBAnimationManager_moveAnimationsFromNode);
		tolua_function(tolua_S,"setAutoPlaySequenceId",lua_cocos2dx_extension_CCBAnimationManager_setAutoPlaySequenceId);
		tolua_function(tolua_S,"getDocumentCallbackNames",lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNames);
		tolua_function(tolua_S,"actionForSoundChannel",lua_cocos2dx_extension_CCBAnimationManager_actionForSoundChannel);
		tolua_function(tolua_S,"setBaseValue",lua_cocos2dx_extension_CCBAnimationManager_setBaseValue);
		tolua_function(tolua_S,"getDocumentOutletNodes",lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNodes);
		tolua_function(tolua_S,"addNode",lua_cocos2dx_extension_CCBAnimationManager_addNode);
		tolua_function(tolua_S,"getLastCompletedSequenceName",lua_cocos2dx_extension_CCBAnimationManager_getLastCompletedSequenceName);
		tolua_function(tolua_S,"setRootNode",lua_cocos2dx_extension_CCBAnimationManager_setRootNode);
		tolua_function(tolua_S,"addDocumentOutletName",lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletName);
		tolua_function(tolua_S,"getSequences",lua_cocos2dx_extension_CCBAnimationManager_getSequences);
		tolua_function(tolua_S,"getRootContainerSize",lua_cocos2dx_extension_CCBAnimationManager_getRootContainerSize);
		tolua_function(tolua_S,"setDocumentControllerName",lua_cocos2dx_extension_CCBAnimationManager_setDocumentControllerName);
		tolua_function(tolua_S,"getContainerSize",lua_cocos2dx_extension_CCBAnimationManager_getContainerSize);
		tolua_function(tolua_S,"actionForCallbackChannel",lua_cocos2dx_extension_CCBAnimationManager_actionForCallbackChannel);
		tolua_function(tolua_S,"getDocumentOutletNames",lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNames);
		tolua_function(tolua_S,"init",lua_cocos2dx_extension_CCBAnimationManager_init);
		tolua_function(tolua_S,"getKeyframeCallbacks",lua_cocos2dx_extension_CCBAnimationManager_getKeyframeCallbacks);
		tolua_function(tolua_S,"runAnimationsForSequenceNamedTweenDuration",lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration);
		tolua_function(tolua_S,"setRootContainerSize",lua_cocos2dx_extension_CCBAnimationManager_setRootContainerSize);
		tolua_function(tolua_S,"runAnimationsForSequenceIdTweenDuration",lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration);
		tolua_function(tolua_S,"getRunningSequenceName",lua_cocos2dx_extension_CCBAnimationManager_getRunningSequenceName);
		tolua_function(tolua_S,"getAutoPlaySequenceId",lua_cocos2dx_extension_CCBAnimationManager_getAutoPlaySequenceId);
		tolua_function(tolua_S,"addDocumentCallbackName",lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackName);
		tolua_function(tolua_S,"getRootNode",lua_cocos2dx_extension_CCBAnimationManager_getRootNode);
		tolua_function(tolua_S,"addDocumentOutletNode",lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletNode);
		tolua_function(tolua_S,"setDelegate",lua_cocos2dx_extension_CCBAnimationManager_setDelegate);
		tolua_function(tolua_S,"addDocumentCallbackNode",lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackNode);
		tolua_function(tolua_S,"setCallFuncForJSCallbackNamed",lua_cocos2dx_extension_CCBAnimationManager_setCallFunc);
		tolua_function(tolua_S,"getDelegate",lua_cocos2dx_extension_CCBAnimationManager_getDelegate);
		tolua_function(tolua_S,"runAnimationsForSequenceNamed",lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamed);
		tolua_function(tolua_S,"getDocumentCallbackNodes",lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNodes);
		tolua_function(tolua_S,"setSequences",lua_cocos2dx_extension_CCBAnimationManager_setSequences);
		tolua_function(tolua_S,"debug",lua_cocos2dx_extension_CCBAnimationManager_debug);
		tolua_function(tolua_S,"getDocumentControllerName",lua_cocos2dx_extension_CCBAnimationManager_getDocumentControllerName);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_CCBAnimationManager_constructor);
	tolua_endmodule(tolua_S);
	return 1;
}


static int lua_cocos2dx_extension_TableViewCell_reset(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableViewCell* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableViewCell*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_reset'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->reset();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_reset'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableViewCell_setIdx(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableViewCell* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableViewCell*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_setIdx'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		unsigned int arg0;
		ok &= luaval_to_uint32(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setIdx(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_setIdx'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableViewCell_setObjectID(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableViewCell* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableViewCell*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_setObjectID'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		unsigned int arg0;
		ok &= luaval_to_uint32(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setObjectID(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_setObjectID'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableViewCell_getObjectID(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableViewCell* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableViewCell*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_getObjectID'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		unsigned int ret = cobj->getObjectID();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_getObjectID'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableViewCell_getIdx(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableViewCell* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableViewCell*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_getIdx'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		unsigned int ret = cobj->getIdx();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_getIdx'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableViewCell_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableViewCell* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj = new cocos2d::extension::TableViewCell();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"TableViewCell");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_TableViewCell_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TableViewCell)");
	return 0;
}

int lua_register_cocos2dx_extension_TableViewCell(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"TableViewCell");
	tolua_cclass(tolua_S,"TableViewCell","TableViewCell","Node",NULL);

	tolua_beginmodule(tolua_S,"TableViewCell");
		tolua_function(tolua_S,"reset",lua_cocos2dx_extension_TableViewCell_reset);
		tolua_function(tolua_S,"setIdx",lua_cocos2dx_extension_TableViewCell_setIdx);
		tolua_function(tolua_S,"setObjectID",lua_cocos2dx_extension_TableViewCell_setObjectID);
		tolua_function(tolua_S,"getObjectID",lua_cocos2dx_extension_TableViewCell_getObjectID);
		tolua_function(tolua_S,"getIdx",lua_cocos2dx_extension_TableViewCell_getIdx);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_TableViewCell_constructor);
	tolua_endmodule(tolua_S);
	return 1;
}


static int lua_cocos2dx_extension_TableView_updateCellAtIndex(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_updateCellAtIndex'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		unsigned int arg0;
		ok &= luaval_to_uint32(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->updateCellAtIndex(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_updateCellAtIndex'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_setVerticalFillOrder(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_setVerticalFillOrder'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::TableView::VerticalFillOrder arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setVerticalFillOrder(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_setVerticalFillOrder'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_scrollViewDidZoom(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_scrollViewDidZoom'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::ScrollView* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"ScrollView",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->scrollViewDidZoom(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_scrollViewDidZoom'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_ccTouchBegan(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_ccTouchBegan'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->ccTouchBegan(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_ccTouchBegan'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_getVerticalFillOrder(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_getVerticalFillOrder'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		int ret = (int)cobj->getVerticalFillOrder();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_getVerticalFillOrder'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_removeCellAtIndex(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_removeCellAtIndex'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		unsigned int arg0;
		ok &= luaval_to_uint32(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->removeCellAtIndex(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_removeCellAtIndex'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_initWithViewSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_initWithViewSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		bool ret = cobj->initWithViewSize(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	if (argc == 2) {
		cocos2d::Size arg0;
		cocos2d::Node* arg1;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithViewSize(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_initWithViewSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_scrollViewDidScroll(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_scrollViewDidScroll'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::ScrollView* arg0;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"ScrollView",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->scrollViewDidScroll(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_scrollViewDidScroll'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_reloadData(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_reloadData'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->reloadData();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_reloadData'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_ccTouchCancelled(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_ccTouchCancelled'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchCancelled(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_ccTouchCancelled'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_ccTouchEnded(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_ccTouchEnded'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchEnded(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_ccTouchEnded'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_ccTouchMoved(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_ccTouchMoved'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Touch* arg0;
		cocos2d::Event* arg1;
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,2,"Touch",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchMoved(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_ccTouchMoved'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView__updateContentSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView__updateContentSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj->_updateContentSize();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView__updateContentSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_insertCellAtIndex(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_insertCellAtIndex'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		unsigned int arg0;
		ok &= luaval_to_uint32(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->insertCellAtIndex(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_insertCellAtIndex'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_cellAtIndex(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_cellAtIndex'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		unsigned int arg0;
		ok &= luaval_to_uint32(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cocos2d::extension::TableViewCell* ret = cobj->cellAtIndex(arg0);
		tolua_pushusertype(tolua_S,ret,"TableViewCell");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_cellAtIndex'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_dequeueCell(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"TableView",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_dequeueCell'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cocos2d::extension::TableViewCell* ret = cobj->dequeueCell();
		tolua_pushusertype(tolua_S,ret,"TableViewCell");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_dequeueCell'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_TableView_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::TableView* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj = new cocos2d::extension::TableView();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"TableView");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_TableView_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TableView)");
	return 0;
}

int lua_register_cocos2dx_extension_TableView(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"TableView");
	tolua_cclass(tolua_S,"TableView","TableView","ScrollView",NULL);

	tolua_beginmodule(tolua_S,"TableView");
		tolua_function(tolua_S,"updateCellAtIndex",lua_cocos2dx_extension_TableView_updateCellAtIndex);
		tolua_function(tolua_S,"setVerticalFillOrder",lua_cocos2dx_extension_TableView_setVerticalFillOrder);
		tolua_function(tolua_S,"scrollViewDidZoom",lua_cocos2dx_extension_TableView_scrollViewDidZoom);
		tolua_function(tolua_S,"ccTouchBegan",lua_cocos2dx_extension_TableView_ccTouchBegan);
		tolua_function(tolua_S,"getVerticalFillOrder",lua_cocos2dx_extension_TableView_getVerticalFillOrder);
		tolua_function(tolua_S,"removeCellAtIndex",lua_cocos2dx_extension_TableView_removeCellAtIndex);
		tolua_function(tolua_S,"initWithViewSize",lua_cocos2dx_extension_TableView_initWithViewSize);
		tolua_function(tolua_S,"scrollViewDidScroll",lua_cocos2dx_extension_TableView_scrollViewDidScroll);
		tolua_function(tolua_S,"reloadData",lua_cocos2dx_extension_TableView_reloadData);
		tolua_function(tolua_S,"ccTouchCancelled",lua_cocos2dx_extension_TableView_ccTouchCancelled);
		tolua_function(tolua_S,"ccTouchEnded",lua_cocos2dx_extension_TableView_ccTouchEnded);
		tolua_function(tolua_S,"ccTouchMoved",lua_cocos2dx_extension_TableView_ccTouchMoved);
		tolua_function(tolua_S,"_updateContentSize",lua_cocos2dx_extension_TableView__updateContentSize);
		tolua_function(tolua_S,"insertCellAtIndex",lua_cocos2dx_extension_TableView_insertCellAtIndex);
		tolua_function(tolua_S,"cellAtIndex",lua_cocos2dx_extension_TableView_cellAtIndex);
		tolua_function(tolua_S,"dequeueCell",lua_cocos2dx_extension_TableView_dequeueCell);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_TableView_constructor);
	tolua_endmodule(tolua_S);
	return 1;
}


static int lua_cocos2dx_extension_EditBox_setAnchorPoint(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setAnchorPoint'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= luaval_to_point(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setAnchorPoint(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setAnchorPoint'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_getText(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_getText'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		const char* ret = cobj->getText();
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_getText'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setPlaceholderFontName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		if(!ok)
			return 0;
		cobj->setPlaceholderFontName(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_getPlaceHolder(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_getPlaceHolder'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		const char* ret = cobj->getPlaceHolder();
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_getPlaceHolder'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setFontName(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setFontName'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		if(!ok)
			return 0;
		cobj->setFontName(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setFontName'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setPlaceholderFontSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setPlaceholderFontSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setInputMode(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setInputMode'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::EditBox::InputMode arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setInputMode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setInputMode'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setPlaceholderFontColor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontColor'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Color3B arg0;
		ok &= luaval_to_color3b(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setPlaceholderFontColor(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontColor'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setFontColor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setFontColor'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Color3B arg0;
		ok &= luaval_to_color3b(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setFontColor(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setFontColor'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setPlaceholderFont(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFont'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setPlaceholderFont(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFont'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setFontSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setFontSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setFontSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setFontSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_initWithSizeAndBackgroundSprite(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_initWithSizeAndBackgroundSprite'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Size arg0;
		cocos2d::extension::Scale9Sprite* arg1;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_initWithSizeAndBackgroundSprite'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setPlaceHolder(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceHolder'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		if(!ok)
			return 0;
		cobj->setPlaceHolder(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceHolder'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setPosition(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPosition'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= luaval_to_point(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setPosition(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPosition'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setReturnType(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setReturnType'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::EditBox::KeyboardReturnType arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setReturnType(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setReturnType'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setInputFlag(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setInputFlag'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::EditBox::InputFlag arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setInputFlag(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setInputFlag'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_getMaxLength(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_getMaxLength'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		int ret = cobj->getMaxLength();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_getMaxLength'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setText(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setText'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		if(!ok)
			return 0;
		cobj->setText(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setText'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setMaxLength(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setMaxLength'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int*)&arg0);
		if(!ok)
			return 0;
		cobj->setMaxLength(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setMaxLength'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setContentSize(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setContentSize'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setContentSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setContentSize'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setFont(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setFont'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_int32(tolua_S, 3,(int*)&arg1);
		if(!ok)
			return 0;
		cobj->setFont(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setFont'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_setVisible(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
	cobj = (cocos2d::extension::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
	if (!cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setVisible'\n", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		bool arg0;
		ok &= luaval_to_boolean(tolua_S, 2,&arg0);
		if(!ok)
			return 0;
		cobj->setVisible(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setVisible'.\n",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_EditBox_create(lua_State* tolua_S)
{
	int argc = 0;
	bool ok  = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 2) {
		cocos2d::Size arg0;
		cocos2d::extension::Scale9Sprite* arg1;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cocos2d::extension::EditBox* ret = cocos2d::extension::EditBox::create(arg0, arg1);
		tolua_pushusertype(tolua_S,ret,"EditBox");
	    return 1;
	}
	if (argc == 3) {
		cocos2d::Size arg0;
		cocos2d::extension::Scale9Sprite* arg1;
		cocos2d::extension::Scale9Sprite* arg2;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,4,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg2 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,4,0);
		};
		if(!ok)
			return 0;
		cocos2d::extension::EditBox* ret = cocos2d::extension::EditBox::create(arg0, arg1, arg2);
		tolua_pushusertype(tolua_S,ret,"EditBox");
	    return 1;
	}
	if (argc == 4) {
		cocos2d::Size arg0;
		cocos2d::extension::Scale9Sprite* arg1;
		cocos2d::extension::Scale9Sprite* arg2;
		cocos2d::extension::Scale9Sprite* arg3;
		ok &= luaval_to_size(tolua_S, 2, &arg0);
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,4,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg2 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,4,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,5,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if(ok){
			arg3 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,5,0);
		};
		if(!ok)
			return 0;
		cocos2d::extension::EditBox* ret = cocos2d::extension::EditBox::create(arg0, arg1, arg2, arg3);
		tolua_pushusertype(tolua_S,ret,"EditBox");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_create'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_EditBox_constructor(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::extension::EditBox* cobj = nullptr;
	bool ok  = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		cobj = new cocos2d::extension::EditBox();
		cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (cobj) {
			cobj->autorelease();
		}
	    int ID = (cobj) ? (int)cobj->_ID : -1;
	    int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"EditBox");
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_constructor'.\n",&tolua_err);
#endif
	return 0;
}

static int lua_cocos2dx_extension_EditBox_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EditBox)");
	return 0;
}

int lua_register_cocos2dx_extension_EditBox(lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"EditBox");
	tolua_cclass(tolua_S,"EditBox","EditBox","ControlButton",NULL);

	tolua_beginmodule(tolua_S,"EditBox");
		tolua_function(tolua_S,"setAnchorPoint",lua_cocos2dx_extension_EditBox_setAnchorPoint);
		tolua_function(tolua_S,"getText",lua_cocos2dx_extension_EditBox_getText);
		tolua_function(tolua_S,"setPlaceholderFontName",lua_cocos2dx_extension_EditBox_setPlaceholderFontName);
		tolua_function(tolua_S,"getPlaceHolder",lua_cocos2dx_extension_EditBox_getPlaceHolder);
		tolua_function(tolua_S,"setFontName",lua_cocos2dx_extension_EditBox_setFontName);
		tolua_function(tolua_S,"setPlaceholderFontSize",lua_cocos2dx_extension_EditBox_setPlaceholderFontSize);
		tolua_function(tolua_S,"setInputMode",lua_cocos2dx_extension_EditBox_setInputMode);
		tolua_function(tolua_S,"setPlaceholderFontColor",lua_cocos2dx_extension_EditBox_setPlaceholderFontColor);
		tolua_function(tolua_S,"setFontColor",lua_cocos2dx_extension_EditBox_setFontColor);
		tolua_function(tolua_S,"setPlaceholderFont",lua_cocos2dx_extension_EditBox_setPlaceholderFont);
		tolua_function(tolua_S,"setFontSize",lua_cocos2dx_extension_EditBox_setFontSize);
		tolua_function(tolua_S,"initWithSizeAndBackgroundSprite",lua_cocos2dx_extension_EditBox_initWithSizeAndBackgroundSprite);
		tolua_function(tolua_S,"setPlaceHolder",lua_cocos2dx_extension_EditBox_setPlaceHolder);
		tolua_function(tolua_S,"setPosition",lua_cocos2dx_extension_EditBox_setPosition);
		tolua_function(tolua_S,"setReturnType",lua_cocos2dx_extension_EditBox_setReturnType);
		tolua_function(tolua_S,"setInputFlag",lua_cocos2dx_extension_EditBox_setInputFlag);
		tolua_function(tolua_S,"getMaxLength",lua_cocos2dx_extension_EditBox_getMaxLength);
		tolua_function(tolua_S,"setText",lua_cocos2dx_extension_EditBox_setText);
		tolua_function(tolua_S,"setMaxLength",lua_cocos2dx_extension_EditBox_setMaxLength);
		tolua_function(tolua_S,"setContentSize",lua_cocos2dx_extension_EditBox_setContentSize);
		tolua_function(tolua_S,"setFont",lua_cocos2dx_extension_EditBox_setFont);
		tolua_function(tolua_S,"setVisible",lua_cocos2dx_extension_EditBox_setVisible);
		tolua_function(tolua_S,"new",lua_cocos2dx_extension_EditBox_constructor);
		tolua_function(tolua_S,"create", lua_cocos2dx_extension_EditBox_create);
	tolua_endmodule(tolua_S);
	return 1;
}

TOLUA_API int register_all_cocos2dx_extension(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_extension_Control(tolua_S);
	lua_register_cocos2dx_extension_TableViewCell(tolua_S);
	lua_register_cocos2dx_extension_Scale9Sprite(tolua_S);
	lua_register_cocos2dx_extension_ControlButton(tolua_S);
	lua_register_cocos2dx_extension_EditBox(tolua_S);
	lua_register_cocos2dx_extension_CCBReader(tolua_S);
	lua_register_cocos2dx_extension_ScrollView(tolua_S);
	lua_register_cocos2dx_extension_CCBAnimationManager(tolua_S);
	lua_register_cocos2dx_extension_TableView(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

