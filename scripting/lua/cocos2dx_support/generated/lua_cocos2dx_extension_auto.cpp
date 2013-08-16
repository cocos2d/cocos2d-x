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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setEnabled'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setEnabled'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_getState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		int ret = (int)cobj->getState();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_getState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isTouchInside'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->isTouchInside(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isTouchInside'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_sendActionsForControlEvents'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::EventType arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->sendActionsForControlEvents(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_sendActionsForControlEvents'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setSelected'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setSelected'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_registerWithTouchDispatcher'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->registerWithTouchDispatcher();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_registerWithTouchDispatcher'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isEnabled'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isEnabled();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isEnabled'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setOpacityModifyRGB'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setOpacityModifyRGB'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_needsLayout'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->needsLayout();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_needsLayout'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_hasVisibleParents'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->hasVisibleParents();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_hasVisibleParents'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isSelected'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isSelected();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isSelected'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_init'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_init'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setHighlighted'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setHighlighted'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isOpacityModifyRGB'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isOpacityModifyRGB();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isOpacityModifyRGB'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_getTouchLocation'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cocos2d::Point ret = cobj->getTouchLocation(arg0);
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_getTouchLocation'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isHighlighted'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isHighlighted();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isHighlighted'.",&tolua_err);
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
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Control");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Control");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_create'.",&tolua_err);
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
		if(!ok)
			return 0;
		cobj = new cocos2d::extension::Control();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj)) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    	toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"Control");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"Control");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_constructor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_addOwnerOutletName'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_addOwnerOutletName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getOwnerCallbackNames'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getOwnerCallbackNames();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getOwnerCallbackNames'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_setCCBRootPath'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_setCCBRootPath'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_addOwnerOutletNode'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->addOwnerOutletNode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_addOwnerOutletNode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getOwnerCallbackNodes'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getOwnerCallbackNodes();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getOwnerCallbackNodes'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_readSoundKeyframesForSeq'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::CCBSequence*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->readSoundKeyframesForSeq(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_readSoundKeyframesForSeq'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getCCBRootPath'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		std::string ret = cobj->getCCBRootPath();
		tolua_pushcppstring(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getCCBRootPath'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getOwnerOutletNodes'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getOwnerOutletNodes();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getOwnerOutletNodes'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_readUTF8'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		std::string ret = cobj->readUTF8();
		tolua_pushcppstring(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_readUTF8'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getOwnerOutletNames'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getOwnerOutletNames();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getOwnerOutletNames'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_setAnimationManager'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::CCBAnimationManager*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setAnimationManager(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_setAnimationManager'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_readCallbackKeyframesForSeq'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::CCBSequence*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->readCallbackKeyframesForSeq(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_readCallbackKeyframesForSeq'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getAnimationManagersForNodes'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getAnimationManagersForNodes();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getAnimationManagersForNodes'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getNodesWithAnimationManagers'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getNodesWithAnimationManagers();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getNodesWithAnimationManagers'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBReader_getAnimationManager'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::extension::CCBAnimationManager* ret = cobj->getAnimationManager();
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"CCBAnimationManager");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"CCBAnimationManager");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_getAnimationManager'.",&tolua_err);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_setResolutionScale'.",&tolua_err);
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
		if (ok){
			arg0 = (cocos2d::extension::CCBReader*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0);
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj) ) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"CCBReader");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
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
		if (ok){
			arg0 = (cocos2d::extension::NodeLoaderLibrary*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0);
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj) ) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"CCBReader");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
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
		if (ok){
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
		if (ok){
			arg1 = (cocos2d::extension::CCBMemberVariableAssigner*)tolua_tousertype(tolua_S,3,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0, arg1);
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj) ) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"CCBReader");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
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
		if (ok){
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
		if (ok){
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
		if (ok){
			arg2 = (cocos2d::extension::CCBSelectorResolver*)tolua_tousertype(tolua_S,4,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0, arg1, arg2);
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj) ) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"CCBReader");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
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
		if (ok){
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
		if (ok){
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
		if (ok){
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
		if (ok){
			arg3 = (cocos2d::extension::NodeLoaderListener*)tolua_tousertype(tolua_S,5,0);
		};

			if (!ok) { ok = true; break; }
			cobj = new cocos2d::extension::CCBReader(arg0, arg1, arg2, arg3);
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj) ) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"CCBReader");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
		}
	}while(0);
	do{
		if (argc == 0) {
			cobj = new cocos2d::extension::CCBReader();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj) ) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBReader");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"CCBReader");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBReader_constructor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_resizableSpriteWithCapInsets'", NULL);
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
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_resizableSpriteWithCapInsets'.",&tolua_err);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrameName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setOpacityModifyRGB'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setOpacityModifyRGB'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setContentSize'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setContentSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetBottom'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetBottom'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_isOpacityModifyRGB'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isOpacityModifyRGB();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_isOpacityModifyRGB'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setOpacity'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setOpacity'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetTop'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetTop'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_updateDisplayedOpacity'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_updateDisplayedOpacity'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_init'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_init'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setPreferredSize'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setPreferredSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getOpacity'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		unsigned char ret = cobj->getOpacity();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getOpacity'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setSpriteFrame'", NULL);
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
		if (ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setSpriteFrame(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setSpriteFrame'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getColor'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Color3B ret = cobj->getColor();
		color3b_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getColor'.",&tolua_err);
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
		if (ok){
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
		if (ok){
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 4);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_initWithBatchNode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetBottom'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		float ret = cobj->getInsetBottom();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetBottom'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getCapInsets'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Rect ret = cobj->getCapInsets();
		rect_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getCapInsets'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_updateWithBatchNode'", NULL);
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
		if (ok){
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 4);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_updateWithBatchNode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetRight'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		float ret = cobj->getInsetRight();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetRight'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getOriginalSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Size ret = cobj->getOriginalSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getOriginalSize'.",&tolua_err);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_initWithFile'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setColor'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setColor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetTop'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		float ret = cobj->getInsetTop();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetTop'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetLeft'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetLeft'.",&tolua_err);
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
		if (ok){
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
		if (ok){
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_initWithSpriteFrame'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getPreferredSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Size ret = cobj->getPreferredSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getPreferredSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setCapInsets'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setCapInsets'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetLeft'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		float ret = cobj->getInsetLeft();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_getInsetLeft'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_updateDisplayedColor'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_updateDisplayedColor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetRight'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_setInsetRight'.",&tolua_err);
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
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	do {
		if (argc == 0) {
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::create();
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
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
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
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
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::create(arg0);
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_create'.",&tolua_err);
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
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::createWithSpriteFrameName(arg0);
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_createWithSpriteFrameName'.",&tolua_err);
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
		if (ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= luaval_to_rect(tolua_S, 3, &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::createWithSpriteFrame(arg0, arg1);
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
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
		if (ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::Scale9Sprite* ret = cocos2d::extension::Scale9Sprite::createWithSpriteFrame(arg0);
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_createWithSpriteFrame'.",&tolua_err);
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
		if(!ok)
			return 0;
		cobj = new cocos2d::extension::Scale9Sprite();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj)) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    	toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"Scale9Sprite");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"Scale9Sprite");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Scale9Sprite_constructor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleColorDispatchTable'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleColorDispatchTable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_isPushed'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isPushed();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_isPushed'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setSelected'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setSelected'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelForState'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleLabelForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_ccTouchBegan'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->ccTouchBegan(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_ccTouchBegan'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_ccTouchEnded'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchEnded(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_ccTouchEnded'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setHighlighted'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setHighlighted'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteDispatchTable'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteDispatchTable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleForState'", NULL);
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
		if (ok){
			arg0 = (cocos2d::String*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleDispatchTable'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Dictionary* ret = cobj->getTitleDispatchTable();
		dictionary_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleDispatchTable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getPreferredSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Size ret = cobj->getPreferredSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getPreferredSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Point ret = cobj->getLabelAnchorPoint();
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_initWithBackgroundSprite'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithBackgroundSprite(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_initWithBackgroundSprite'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		float ret = cobj->getTitleTTFSizeForState(arg0);
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleDispatchTable'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleDispatchTable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setOpacity'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setOpacity'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_init'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_init'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		cocos2d::extension::Control::State arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleTTFForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		double arg0;
		cocos2d::extension::Control::State arg1;
		ok &= luaval_to_number(tolua_S, 2,&arg0);
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleTTFSizeForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleLabel'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setTitleLabel(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleLabel'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_ccTouchMoved'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchMoved(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_ccTouchMoved'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getOpacity'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		unsigned char ret = cobj->getOpacity();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getOpacity'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitleColor'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Color3B ret = cobj->getCurrentTitleColor();
		color3b_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitleColor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleColorDispatchTable'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Dictionary* ret = cobj->getTitleColorDispatchTable();
		dictionary_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleColorDispatchTable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setEnabled'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setEnabled'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSprite'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setBackgroundSprite(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSprite'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cocos2d::extension::Scale9Sprite* ret = cobj->getBackgroundSpriteForState(arg0);
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getColor'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Color3B ret = cobj->getColor();
		color3b_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getColor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setMargins'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		int arg0;
		int arg1;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setMargins(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setMargins'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_needsLayout'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->needsLayout();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_needsLayout'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 3);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitle'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::String* ret = cobj->getCurrentTitle();
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"String");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"String");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitle'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getHorizontalOrigin'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		int ret = cobj->getHorizontalOrigin();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getHorizontalOrigin'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		const char* ret = cobj->getTitleTTFForState(arg0);
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSprite'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::extension::Scale9Sprite* ret = cobj->getBackgroundSprite();
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Scale9Sprite");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Scale9Sprite");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSprite'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleColorForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cocos2d::Color3B ret = cobj->getTitleColorForState(arg0);
		color3b_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleColorForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleColorForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		cocos2d::Color3B arg0;
		cocos2d::extension::Control::State arg1;
		ok &= luaval_to_color3b(tolua_S, 2, &arg0);
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleColorForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleColorForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->doesAdjustBackgroundImage();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState'", NULL);
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
		if (ok){
			arg0 = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setBackgroundSpriteFrameForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setBackgroundSpriteForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setColor'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setColor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelDispatchTable'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Dictionary* ret = cobj->getTitleLabelDispatchTable();
		dictionary_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelDispatchTable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithLabelAndBackgroundSprite(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setPreferredSize'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setPreferredSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelDispatchTable'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelDispatchTable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleLabel'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Node* ret = cobj->getTitleLabel();
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Node");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Node");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleLabel'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_ccTouchCancelled'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchCancelled(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_ccTouchCancelled'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getVerticalMargin'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		int ret = cobj->getVerticalMargin();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getVerticalMargin'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteDispatchTable'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Dictionary* ret = cobj->getBackgroundSpriteDispatchTable();
		dictionary_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteDispatchTable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cocos2d::Node* ret = cobj->getTitleLabelForState(arg0);
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Node");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Node");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleBMFontForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		cocos2d::extension::Control::State arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setTitleBMFontForState(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleBMFontForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleBMFontForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		const char* ret = cobj->getTitleBMFontForState(arg0);
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleBMFontForState'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->getZoomOnTouchDown();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleForState'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::Control::State arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cocos2d::String* ret = cobj->getTitleForState(arg0);
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"String");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"String");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleForState'.",&tolua_err);
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
		if (ok){
			arg0 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,2,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0);
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"ControlButton");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"ControlButton");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	do {
		if (argc == 0) {
			cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create();
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"ControlButton");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"ControlButton");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
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
		if (ok){
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
		if (ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0, arg1);
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"ControlButton");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"ControlButton");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
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
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"ControlButton");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"ControlButton");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d", argc, 3);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_create'.",&tolua_err);
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
		if(!ok)
			return 0;
		cobj = new cocos2d::extension::ControlButton();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj)) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    	toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ControlButton");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"ControlButton");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_constructor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isClippingToBounds'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isClippingToBounds();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isClippingToBounds'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContainer'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setContainer(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContainer'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration'.",&tolua_err);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			int arg1;
			ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
			int arg1;
			ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

			if (!ok) { ok = true; break; }
			int arg2;
			ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);

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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};

			if (!ok) { ok = true; break; }
		cobj->addChild(arg0);
		return 0;
		}
	}while(0);
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_addChild'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_ccTouchBegan'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->ccTouchBegan(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_ccTouchBegan'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getContainer'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Node* ret = cobj->getContainer();
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Node");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Node");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getContainer'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_ccTouchEnded'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchEnded(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_ccTouchEnded'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getDirection'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		int ret = (int)cobj->getDirection();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getDirection'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getZoomScale'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		float ret = cobj->getZoomScale();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getZoomScale'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_updateInset'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->updateInset();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_updateInset'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_initWithViewSize'", NULL);
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
		if (ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithViewSize(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_initWithViewSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_pause'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Object*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->pause(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_pause'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setDirection'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::ScrollView::Direction arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setDirection(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setDirection'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setBounceable'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setBounceable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContentOffset'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContentOffset'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isDragging'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isDragging();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isDragging'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_init'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_init'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isBounceable'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isBounceable();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isBounceable'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getContentSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Size ret = cobj->getContentSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getContentSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_ccTouchMoved'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchMoved(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_ccTouchMoved'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setTouchEnabled'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setTouchEnabled'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getContentOffset'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Point ret = cobj->getContentOffset();
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getContentOffset'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_resume'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Object*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->resume(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_resume'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setClippingToBounds'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setClippingToBounds'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setViewSize'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setViewSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getViewSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Size ret = cobj->getViewSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getViewSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_maxContainerOffset'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Point ret = cobj->maxContainerOffset();
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_maxContainerOffset'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContentSize'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContentSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isTouchMoved'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->isTouchMoved();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isTouchMoved'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isNodeVisible'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->isNodeVisible(arg0);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isNodeVisible'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_ccTouchCancelled'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchCancelled(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_ccTouchCancelled'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_minContainerOffset'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Point ret = cobj->minContainerOffset();
		point_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_minContainerOffset'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_registerWithTouchDispatcher'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->registerWithTouchDispatcher();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_registerWithTouchDispatcher'.",&tolua_err);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setZoomScale'.",&tolua_err);
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
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"ScrollView");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"ScrollView");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	do {
		if (argc == 1) {
			cocos2d::Size arg0;
			ok &= luaval_to_size(tolua_S, 2, &arg0);
			if (!ok) { ok = true; break; }
			cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create(arg0);
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"ScrollView");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"ScrollView");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
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
		if (ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
			if (!ok) { ok = true; break; }
			cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create(arg0, arg1);
			do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"ScrollView");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"ScrollView");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
			return 1;
		}
	} while (0);
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_create'.",&tolua_err);
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
		if(!ok)
			return 0;
		cobj = new cocos2d::extension::ScrollView();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj)) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    	toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ScrollView");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"ScrollView");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_constructor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_moveAnimationsFromNode'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->moveAnimationsFromNode(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_moveAnimationsFromNode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setAutoPlaySequenceId'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setAutoPlaySequenceId(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setAutoPlaySequenceId'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNames'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getDocumentCallbackNames();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNames'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_actionForSoundChannel'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::CCBSequenceProperty*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cocos2d::Object* ret = cobj->actionForSoundChannel(arg0);
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Object");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Object");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_actionForSoundChannel'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setBaseValue'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Object*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Node",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
		std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
		if(!ok)
			return 0;
		cobj->setBaseValue(arg0, arg1, arg2);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 3);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setBaseValue'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNodes'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getDocumentOutletNodes();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNodes'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addNode'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_dictionary(tolua_S, 3, &arg1);
		if(!ok)
			return 0;
		cobj->addNode(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addNode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getLastCompletedSequenceName'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		std::string ret = cobj->getLastCompletedSequenceName();
		tolua_pushcppstring(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getLastCompletedSequenceName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setRootNode'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->setRootNode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setRootNode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletName'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getSequences'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getSequences();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getSequences'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getRootContainerSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Size ret = cobj->getRootContainerSize();
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getRootContainerSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setDocumentControllerName'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setDocumentControllerName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getContainerSize'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cocos2d::Size ret = cobj->getContainerSize(arg0);
		size_to_luaval(tolua_S, ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getContainerSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_actionForCallbackChannel'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::CCBSequenceProperty*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cocos2d::Object* ret = cobj->actionForCallbackChannel(arg0);
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Object");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Object");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_actionForCallbackChannel'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNames'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getDocumentOutletNames();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentOutletNames'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_init'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		bool ret = cobj->init();
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_init'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getKeyframeCallbacks'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getKeyframeCallbacks();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getKeyframeCallbacks'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setRootContainerSize'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setRootContainerSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		int arg0;
		double arg1;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		ok &= luaval_to_number(tolua_S, 3,&arg1);
		if(!ok)
			return 0;
		cobj->runAnimationsForSequenceIdTweenDuration(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getRunningSequenceName'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		const char* ret = cobj->getRunningSequenceName();
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getRunningSequenceName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getAutoPlaySequenceId'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		int ret = cobj->getAutoPlaySequenceId();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getAutoPlaySequenceId'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackName'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getRootNode'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Node* ret = cobj->getRootNode();
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"Node");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"Node");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getRootNode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletNode'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->addDocumentOutletNode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentOutletNode'.",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getSequenceDuration(lua_State* tolua_S)
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getSequenceDuration'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		if(!ok)
			return 0;
		float ret = cobj->getSequenceDuration(arg0);
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getSequenceDuration'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackNode'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Node*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->addDocumentCallbackNode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackNode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setCallFunc'", NULL);
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
		if (ok){
			arg0 = (cocos2d::CallFunc*)tolua_tousertype(tolua_S,2,0);
		};
		ok &= luaval_to_std_string(tolua_S, 3,&arg1);
		if(!ok)
			return 0;
		cobj->setCallFunc(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setCallFunc'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamed'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamed'.",&tolua_err);
#endif
	return 0;
}
static int lua_cocos2dx_extension_CCBAnimationManager_getSequenceId(lua_State* tolua_S)
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getSequenceId'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		if(!ok)
			return 0;
		int ret = cobj->getSequenceId(arg0);
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getSequenceId'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNodes'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::Array* ret = cobj->getDocumentCallbackNodes();
		array_to_luaval(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentCallbackNodes'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_setSequences'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::Array* arg0;
		ok &= luaval_to_array(tolua_S, 2, &arg0);
		if(!ok)
			return 0;
		cobj->setSequences(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_setSequences'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_debug'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->debug();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_debug'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentControllerName'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		std::string ret = cobj->getDocumentControllerName();
		tolua_pushcppstring(tolua_S,ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_getDocumentControllerName'.",&tolua_err);
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
		if(!ok)
			return 0;
		cobj = new cocos2d::extension::CCBAnimationManager();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj)) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    	toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"CCBAnimationManager");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"CCBAnimationManager");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_CCBAnimationManager_constructor'.",&tolua_err);
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
		tolua_function(tolua_S,"getSequenceDuration",lua_cocos2dx_extension_CCBAnimationManager_getSequenceDuration);
		tolua_function(tolua_S,"addDocumentCallbackNode",lua_cocos2dx_extension_CCBAnimationManager_addDocumentCallbackNode);
		tolua_function(tolua_S,"setCallFuncForJSCallbackNamed",lua_cocos2dx_extension_CCBAnimationManager_setCallFunc);
		tolua_function(tolua_S,"runAnimationsForSequenceNamed",lua_cocos2dx_extension_CCBAnimationManager_runAnimationsForSequenceNamed);
		tolua_function(tolua_S,"getSequenceId",lua_cocos2dx_extension_CCBAnimationManager_getSequenceId);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_reset'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->reset();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_reset'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_setIdx'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_setIdx'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_setObjectID'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_setObjectID'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_getObjectID'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		unsigned int ret = cobj->getObjectID();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_getObjectID'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_getIdx'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		unsigned int ret = cobj->getIdx();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_getIdx'.",&tolua_err);
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
		if(!ok)
			return 0;
		cobj = new cocos2d::extension::TableViewCell();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj)) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    	toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"TableViewCell");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"TableViewCell");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_constructor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_updateCellAtIndex'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_updateCellAtIndex'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_setVerticalFillOrder'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::TableView::VerticalFillOrder arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setVerticalFillOrder(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_setVerticalFillOrder'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_scrollViewDidZoom'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->scrollViewDidZoom(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_scrollViewDidZoom'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_ccTouchBegan'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->ccTouchBegan(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_ccTouchBegan'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_getVerticalFillOrder'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		int ret = (int)cobj->getVerticalFillOrder();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_getVerticalFillOrder'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_removeCellAtIndex'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_removeCellAtIndex'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_initWithViewSize'", NULL);
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
		if (ok){
			arg1 = (cocos2d::Node*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithViewSize(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_initWithViewSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_scrollViewDidScroll'", NULL);
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
		if (ok){
			arg0 = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,2,0);
		};
		if(!ok)
			return 0;
		cobj->scrollViewDidScroll(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_scrollViewDidScroll'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_reloadData'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->reloadData();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_reloadData'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_ccTouchCancelled'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchCancelled(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_ccTouchCancelled'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_ccTouchEnded'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchEnded(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_ccTouchEnded'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_ccTouchMoved'", NULL);
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
		if (ok){
			arg0 = (cocos2d::Touch*)tolua_tousertype(tolua_S,2,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,3,"Event",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg1 = (cocos2d::Event*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cobj->ccTouchMoved(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_ccTouchMoved'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView__updateContentSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cobj->_updateContentSize();
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView__updateContentSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_insertCellAtIndex'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_insertCellAtIndex'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_cellAtIndex'", NULL);
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
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"TableViewCell");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"TableViewCell");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_cellAtIndex'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_dequeueCell'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		cocos2d::extension::TableViewCell* ret = cobj->dequeueCell();
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"TableViewCell");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"TableViewCell");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_dequeueCell'.",&tolua_err);
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
		if(!ok)
			return 0;
		cobj = new cocos2d::extension::TableView();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj)) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    	toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"TableView");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"TableView");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_constructor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setAnchorPoint'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setAnchorPoint'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_getText'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		const char* ret = cobj->getText();
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_getText'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontName'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_getPlaceHolder'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		const char* ret = cobj->getPlaceHolder();
		tolua_pushstring(tolua_S,(const char*)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_getPlaceHolder'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setFontName'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setFontName'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setPlaceholderFontSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setInputMode'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::EditBox::InputMode arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setInputMode(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setInputMode'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontColor'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFontColor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setFontColor'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setFontColor'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFont'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setPlaceholderFont(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceholderFont'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setFontSize'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setFontSize(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setFontSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_initWithSizeAndBackgroundSprite'", NULL);
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
		if (ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1);
		tolua_pushboolean(tolua_S,(bool)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_initWithSizeAndBackgroundSprite'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPlaceHolder'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPlaceHolder'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setPosition'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setPosition'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setReturnType'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::EditBox::KeyboardReturnType arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setReturnType(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setReturnType'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setInputFlag'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		cocos2d::extension::EditBox::InputFlag arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setInputFlag(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setInputFlag'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_getMaxLength'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 0) {
		if(!ok)
			return 0;
		int ret = cobj->getMaxLength();
		tolua_pushnumber(tolua_S,(lua_Number)ret);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_getMaxLength'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setText'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setText'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setMaxLength'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 1) {
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
		if(!ok)
			return 0;
		cobj->setMaxLength(arg0);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setMaxLength'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setContentSize'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setContentSize'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setFont'", NULL);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S)-1;
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
		if(!ok)
			return 0;
		cobj->setFont(arg0, arg1);
		return 0;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setFont'.",&tolua_err);
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
		tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_EditBox_setVisible'", NULL);
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
	printf("wrong number of arguments: %d, was expecting %d", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_setVisible'.",&tolua_err);
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
		if (ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		if(!ok)
			return 0;
		cocos2d::extension::EditBox* ret = cocos2d::extension::EditBox::create(arg0, arg1);
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"EditBox");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"EditBox");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
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
		if (ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,4,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg2 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,4,0);
		};
		if(!ok)
			return 0;
		cocos2d::extension::EditBox* ret = cocos2d::extension::EditBox::create(arg0, arg1, arg2);
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"EditBox");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"EditBox");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
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
		if (ok){
			arg1 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,3,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,4,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg2 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,4,0);
		};
		#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S,5,"Scale9Sprite",0,&tolua_err)){
			tolua_error(tolua_S,"#ferror:",&tolua_err);
			ok = false;
		}
		#endif
		if (ok){
			arg3 = (cocos2d::extension::Scale9Sprite*)tolua_tousertype(tolua_S,5,0);
		};
		if(!ok)
			return 0;
		cocos2d::extension::EditBox* ret = cocos2d::extension::EditBox::create(arg0, arg1, arg2, arg3);
		do {
			if (NULL != ret){
				cocos2d::Object *cobj = dynamic_cast<cocos2d::Object *>(ret);
				if (NULL != cobj) {
					int ID = ret ? (int)(cobj->_ID) : -1;
					int* luaID = ret ? &(cobj->_luaID) : NULL;
					toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"EditBox");
				} else {
					 tolua_pushusertype(tolua_S,(void*)ret,"EditBox");
			}} else {
				lua_pushnil(tolua_S);
			}
		} while (0);
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_create'.",&tolua_err);
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
		if(!ok)
			return 0;
		cobj = new cocos2d::extension::EditBox();
		if (NULL != dynamic_cast<cocos2d::Object *>(cobj)) {
			cobj->autorelease();
			int ID = (cobj) ? (int)cobj->_ID : -1;
	    	int* luaID = (cobj) ? &cobj->_luaID : NULL;
	    	toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"EditBox");
		}
		else
		{
			tolua_pushusertype(tolua_S,(void*)cobj,"EditBox");
			tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		}
	    return 1;
	}
	printf("wrong number of arguments: %d, was expecting %d", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_EditBox_constructor'.",&tolua_err);
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

