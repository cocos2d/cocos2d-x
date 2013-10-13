#include "lua_cocos2dx_auto.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"

static int tolua_cocos2d_MenuItemImage_create(lua_State* tolua_S)
{
    if (NULL == tolua_S) 
        return 0;

    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"MenuItemImage",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    do {
        if (argc == 0)
        {
            MenuItemImage* tolua_ret = (MenuItemImage*)MenuItemImage::create();
            //Uncheck
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
            return 1;
        }
    } while (0);
    do {
#if COCOS2D_DEBUG >= 1
		if (!tolua_isstring(tolua_S,2,0,&tolua_err) ||
            !tolua_isstring(tolua_S,3,0,&tolua_err))
        {
            ok = false;
		}
#endif        
        if (!ok)
        {
            ok = true;
            break;
        }
        const char* normalImage = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char* selectedImage = ((const char*)  tolua_tostring(tolua_S,3,0));
        MenuItemImage* tolua_ret = (MenuItemImage*)  MenuItemImage::create(normalImage,selectedImage);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
        return 1;
        
    } while (0);
    do {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S,2,0,&tolua_err) ||
            !tolua_isstring(tolua_S,3,0,&tolua_err) ||
            !tolua_isstring(tolua_S,4,0,&tolua_err) )
        {
            goto tolua_lerror;
            break;
        }
#endif
        const char* normalImage = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char* selectedImage = ((const char*)  tolua_tostring(tolua_S,3,0));
        const char* disabledImage = ((const char*)  tolua_tostring(tolua_S,4,0));
        
        MenuItemImage* tolua_ret = (MenuItemImage*)  MenuItemImage::create(normalImage,selectedImage,disabledImage);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
        return 1;
        
    } while (0);

	CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_MenuItemImage_create'.\n",&tolua_err);
#endif
	return 0;
    
}

static int tolua_cocos2d_MenuItemLabel_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"MenuItemLabel",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(1 == argc)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        Node* label = ((Node*)  tolua_tousertype(tolua_S,2,0));
        MenuItemLabel* tolua_ret = (MenuItemLabel*)  MenuItemLabel::create(label);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemLabel");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItemFont_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"MenuItemFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(1 == argc)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S, 2, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* value = ((const char*)  tolua_tostring(tolua_S,2,0));
        MenuItemFont* tolua_ret = (MenuItemFont*)  MenuItemFont::create(value);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemFont");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItemSprite_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"MenuItemSprite",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(argc >= 2 && argc <= 3)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
            !tolua_isusertype(tolua_S,3,"Node",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
        
        if (3 == argc && !tolua_isusertype(tolua_S,4,"Node",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        Node* normalSprite = ((Node*)  tolua_tousertype(tolua_S,2,0));
        Node* selectedSprite = ((Node*)  tolua_tousertype(tolua_S,3,0));
        Node* disabledSprite = NULL;
        if (3 == argc)
        {
            disabledSprite = (Node*)  tolua_tousertype(tolua_S,4,0);
        }
        MenuItemSprite* tolua_ret = (MenuItemSprite*)  MenuItemSprite::create(normalSprite,selectedSprite,disabledSprite);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemSprite");
        return 1;
    }
    
    CCLOG("create has wrong number of arguments: %d, was expecting %d\n", argc, 3);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Menu_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"Menu",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0 )
    {
        cocos2d::Array* array = cocos2d::Array::create();
        if (NULL == array)
        {
            CCLOG("Menu create method create array fail\n");
            return 0;
        }
        uint32_t i = 1;
        while (i <= argc)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isusertype(tolua_S, 1 + i, "MenuItem", 0, &tolua_err))
                goto tolua_lerror;
#endif
            
            cocos2d::Object* item = static_cast<cocos2d::Object*>(tolua_tousertype(tolua_S, 1 + i, NULL));
            if (NULL != item)
            {
                array->addObject(item);
                ++i;
            }
            
        }
        cocos2d::Menu* tolua_ret = cocos2d::Menu::createWithArray(array);
        //UnCheck
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Menu");
        return 1;
    }
    else if(argc == 0)
    {
        cocos2d::Menu* tolua_ret = cocos2d::Menu::create();
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Menu");
        return 1;
    }
    
    CCLOG("create wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Menu_create'.\n",&tolua_err);
#endif
	return 0;
}



static int tolua_cocos2dx_Menu_alignItemsInRows(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Menu* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Menu*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'lua_cocos2dx_Menu_alignItemsInRows'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0)
    {
        Array* array = NULL;
        if (luavals_variadic_to_array(tolua_S, argc, &array))
        {
            self->alignItemsInRowsWithArray(array);
        }
        return 0;
    }
    
    CCLOG("'alignItemsInRows' has wrong number of arguments in tolua_cocos2dx_Menu_alignItemsInRows: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'alignItemsInRows'.\n",&tolua_err);
#endif
	return 0;
}

static int tolua_cocos2dx_Menu_alignItemsInColumns(lua_State* tolua_S)
{
    
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Menu* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Menu*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_Menu_alignItemsInColumns'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0)
    {
        Array* array = NULL;
        if (luavals_variadic_to_array(tolua_S, argc, &array))
        {
            self->alignItemsInColumnsWithArray(array);
        }
        return 0;
    }
    
    CCLOG("'alignItemsInColumns' has wrong number of arguments in tolua_cocos2dx_Menu_alignItemsInColumns: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'alignItemsInColumns'.\n",&tolua_err);
#endif
	return 0;
}

static int tolua_cocos2d_MenuItemToggle_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"MenuItemToggle",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(argc >= 1)
    {
        MenuItemToggle* tolua_ret = MenuItemToggle::create();
        if (NULL == tolua_ret)
        {
            return 0;
        }
        
        for (uint32_t i = 0; i < argc; ++i)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isusertype(tolua_S, i + 2,"MenuItem",0,&tolua_err) )
            {
                goto tolua_lerror;
            }
#endif
            MenuItem* item = static_cast<MenuItem*>(tolua_tousertype(tolua_S, i + 2,0));
            if (0 == i)
            {
                tolua_ret->initWithItem(item);
            }
            else
            {
                tolua_ret->addSubItem(item);
            }
        }
        
        int  nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemToggle");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItem_registerScriptTapHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    MenuItem* cobj = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"MenuItem",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = static_cast<cocos2d::MenuItemImage*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2d_MenuItem_registerScriptTapHandler'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)cobj, handler, ScriptHandlerMgr::HandlerType::MENU_CLICKED);
        return 0;
    }
    
    CCLOG("'registerScriptTapHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItem_unregisterScriptTapHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    MenuItem* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"MenuItem",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = static_cast<cocos2d::MenuItemImage*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2d_MenuItem_unregisterScriptTapHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)cobj, ScriptHandlerMgr::HandlerType::MENU_CLICKED);
        return 0;
    }
    
    CCLOG("'unregisterScriptTapHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptTouchHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptTouchHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >=1 && argc <= 4) {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        bool isMultiTouches  = false;
        int  priority        = 0;
        bool swallowTouches  = true;
        
        if (argc >= 2) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isboolean(tolua_S,3,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            isMultiTouches = (bool)tolua_toboolean(tolua_S,3,false);
        }
        
        if (argc >= 3) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,4,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            priority = (int)tolua_tonumber(tolua_S,4,0);
        }
        
        if (argc == 4) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isboolean(tolua_S,5,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            swallowTouches = (bool)tolua_toboolean(tolua_S,5,true);
        }
        
        Touch::DispatchMode touchesMode = Touch::DispatchMode::ALL_AT_ONCE;
        if (!isMultiTouches)
            touchesMode = Touch::DispatchMode::ONE_BY_ONE;
        self->setTouchMode(touchesMode);
//        self->setTouchPriority(priority);
		self->setSwallowsTouches(swallowTouches);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::TOUCHES);
        return 0;
    }
    
    CCLOG("'registerScriptTouchHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptTouchHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptTouchHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptTouchHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::HandlerType::TOUCHES);
        return 0;
    }
    
    CCLOG("'unregisterScriptTouchHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptKeypadHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
    {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptKeypadHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::KEYPAD);
        return 0;
    }
    
    CCLOG("'registerScriptKeypadHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptKeypadHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptKeypadHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
    {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptKeypadHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler(self, ScriptHandlerMgr::HandlerType::KEYPAD);
        return 0;
    }

    CCLOG("'unregisterScriptKeypadHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptKeypadHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptAccelerateHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptAccelerateHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::ACCELEROMETER);
        return 0;
    }
    
    CCLOG("'registerScriptAccelerateHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptAccelerateHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptAccelerateHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptAccelerateHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::HandlerType::ACCELEROMETER);
        return 0;
    }
    
    CCLOG("'unregisterScriptAccelerateHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptAccelerateHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Scheduler_scheduleScriptFunc(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Scheduler* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Scheduler",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Scheduler*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Scheduler_scheduleScriptFunc'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (3 == argc) {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
            !tolua_isboolean(tolua_S,4,0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        float interval = (float)  tolua_tonumber(tolua_S,3,0);
        bool  paused   = (bool)  tolua_toboolean(tolua_S,4,0);
        unsigned int tolua_ret = (unsigned int)  self->scheduleScriptFunc(handler,interval,paused);
        tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        return 1;
    }
    
    CCLOG("'scheduleScriptFunc' has wrong number of arguments: %d, was expecting %d\n", argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'scheduleScriptFunc'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Scheduler_unscheduleScriptEntry(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Scheduler* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Scheduler",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Scheduler*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Scheduler_unscheduleScriptEntry'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc) {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        unsigned int scheduleScriptEntryID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        self->unscheduleScriptEntry(scheduleScriptEntryID);
        return 0;
    }
    
    CCLOG("'unscheduleScriptEntry' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unscheduleScriptEntry'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_Sequence_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"Sequence",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(argc > 0)
    {
        cocos2d::Array* array = cocos2d::Array::create();
        if (NULL == array)
        {
            CCLOG("Sequence create method create array fail\n");
            return 0;
        }
        uint32_t i = 1;
        while (i <= argc)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isusertype(tolua_S, 1 + i, "Object", 0, &tolua_err))
                goto tolua_lerror;
#endif
            
            cocos2d::Object* item = static_cast<cocos2d::Object*>(tolua_tousertype(tolua_S, 1 + i, NULL));
            if (NULL != item)
            {
                array->addObject(item);
                ++i;
            }
            
        }
        cocos2d::Sequence* tolua_ret = cocos2d::Sequence::create(array);
        //issue 2433 uncheck
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Sequence");
        return 1;
    }
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_CallFunc_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"CallFunc",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if(!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
            goto tolua_lerror;
#endif
        
        LUA_FUNCTION funcID = (  toluafix_ref_function(tolua_S,2,0));
        LuaCallFunc* tolua_ret = (LuaCallFunc*)  LuaCallFunc::create(funcID);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CallFunc");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
    
}

static int tolua_cocos2d_Node_registerScriptHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Node_registerScriptHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if(!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
            goto tolua_lerror;
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::NODE);

        return 0;
    }
    
    CCLOG("'registerScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Node_unregisterScriptHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Node_unregisterScriptHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::HandlerType::NODE);
        return 0;
    }
    
    CCLOG("'unregisterScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if(!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
            goto tolua_lerror;
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        int priority = 0;
        if (luaval_to_int32(tolua_S, 3, &priority))
        {
           self->scheduleUpdateWithPriorityLua(handler,priority);
        }
        return 0;
    }
    
    CCLOG("'scheduleUpdateWithPriorityLua' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'scheduleUpdateWithPriorityLua'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Node_unscheduleUpdate(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Node_unscheduleUpdate'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        self->unscheduleUpdate();
        return 0;
    }
    
    CCLOG("'unscheduleUpdate' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unscheduleUpdate'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Node_getPosition(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Node_getPosition'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >= 0 && argc <= 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S,2,1,&tolua_err) || !tolua_isnumber(tolua_S,3,1,&tolua_err) )
            goto tolua_lerror;
#endif
        float x = (float)  tolua_tonumber(tolua_S,2,0);
        float y = (float)  tolua_tonumber(tolua_S,3,0);
        
        self->getPosition(&x,&y);
        
        tolua_pushnumber(tolua_S,(lua_Number)x);
        tolua_pushnumber(tolua_S,(lua_Number)y);
        
        return 2;
    }
    
    CCLOG("'getPosition' function in Node has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Spawn_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"Spawn",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc > 0)
    {
        cocos2d::Array* array = cocos2d::Array::create();
        if (NULL  == array)
        {
            CCLOG("Spawn create method create array fail\n");
            return 0;
        }
        
        uint32_t i = 1;
        while (i <= argc)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isusertype(tolua_S, 1 + i, "Object", 0, &tolua_err))
                goto tolua_lerror;
#endif
            
            cocos2d::Object* item = static_cast<cocos2d::Object*>(tolua_tousertype(tolua_S, 1 + i, NULL));
            if (NULL != item)
            {
                array->addObject(item);
                ++i;
            }
        }
        
        cocos2d::Spawn * tolua_ret = cocos2d::Spawn::create(array);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Spawn");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2d_CardinalSplineBy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"CardinalSplineBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 3)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        double ten = 0.0;
        ok &= luaval_to_number(tolua_S, 4, &ten);
        if (!ok)
            return false;
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                free(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            free(arr);
            CardinalSplineBy* tolua_ret = CardinalSplineBy::create(dur, points, ten);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CardinalSplineBy");
                return 1;
            }
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_CatmullRomBy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"CatmullRomBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                free(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            free(arr);
            CatmullRomBy* tolua_ret = CatmullRomBy::create(dur, points);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CatmullRomBy");
                return 1;
            }
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_CatmullRomTo_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"CatmullRomTo",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                free(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            free(arr);
            CatmullRomTo* tolua_ret = CatmullRomTo::create(dur, points);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CatmullRomTo");
                return 1;
            }
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_BezierBy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"BezierBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double t = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &t);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        if (num < 3)
        {
            free(arr);
            return false;
        }
        
        ccBezierConfig config;
        config.controlPoint_1 = arr[0];
        config.controlPoint_2 = arr[1];
        config.endPosition = arr[2];
        free(arr);
        
        BezierBy* tolua_ret = BezierBy::create(t, config);
        if (NULL != tolua_ret)
        {
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"BezierBy");
            return 1;
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_BezierTo_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"BezierTo",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double t = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &t);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        if (num < 3)
        {
            free(arr);
            return false;
        }
        
        ccBezierConfig config;
        config.controlPoint_1 = arr[0];
        config.controlPoint_2 = arr[1];
        config.endPosition = arr[2];
        free(arr);
        
        BezierTo* tolua_ret = BezierTo::create(t, config);
        if (NULL != tolua_ret)
        {
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"BezierTo");
            return 1;
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_DrawNode_drawPolygon(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    DrawNode* self = nullptr;
  
    tolua_Error tolua_err;
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::DrawNode*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_DrawNode_drawPolygon'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (5 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if(
        !tolua_istable(tolua_S, 2, 0, &tolua_err)  ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_istable(tolua_S, 4, 0,&tolua_err)   ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err) ||
        !tolua_istable(tolua_S,6, 0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        size_t size = lua_tonumber(tolua_S, 3);
        if ( size > 0 )
        {
            Point* points = new Point[size];
            if (NULL == points)
                return 0;
            
            for (int i = 0; i < size; i++)
            {
                lua_pushnumber(tolua_S,i + 1);
                lua_gettable(tolua_S,2);
                if (!tolua_istable(tolua_S,-1, 0, &tolua_err))
                {
                    CC_SAFE_DELETE_ARRAY(points);
#if COCOS2D_DEBUG >= 1
                    goto tolua_lerror;
#endif
                }
                
                if(!luaval_to_point(tolua_S, lua_gettop(tolua_S), &points[i]))
                {
                    lua_pop(tolua_S, 1);
                    CC_SAFE_DELETE_ARRAY(points);
                    return 0;
                }
                lua_pop(tolua_S, 1);
            }
            
            Color4F fillColor;
            if (!luaval_to_color4f(tolua_S, 4, &fillColor))
            {
                CC_SAFE_DELETE_ARRAY(points);
                return 0;
            }
            
            float borderWidth  = (float)tolua_tonumber(tolua_S, 5, 0);
            
            Color4F borderColor;
            if (!luaval_to_color4f(tolua_S, 6, &borderColor))
            {
                CC_SAFE_DELETE_ARRAY(points);
                return 0;
            }
            
            self->drawPolygon(points, size, fillColor, borderWidth, borderColor);
            CC_SAFE_DELETE_ARRAY(points);
            return 0;
        }        
    }
    
    CCLOG("'drawPolygon' has wrong number of arguments: %d, was expecting %d\n", argc, 5);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'drawPolygon'.",&tolua_err);
    return 0;
#endif
}

// setBlendFunc
template<class T>
static int tolua_cocos2dx_setBlendFunc(lua_State* tolua_S,const char* className)
{
    if (NULL == tolua_S || NULL == className || strlen(className) == 0)
        return 0;
    
    int argc = 0;
    T* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,className,0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<T*>(tolua_tousertype(tolua_S,1,0));
    
    argc = lua_gettop(tolua_S) - 1;
    if (2 == argc)
    {
        GLenum src, dst;
        if (!luaval_to_int32(tolua_S, 2, (int32_t*)&src))
            return 0;
        
        if (!luaval_to_int32(tolua_S, 3, (int32_t*)&dst))
            return 0;
        
        BlendFunc blendFunc = {src, dst};
        self->setBlendFunc(blendFunc);
        return 0;
    }

    
    CCLOG("'setBlendFunc' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_Sprite_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<Sprite>(tolua_S,"Sprite");
}

static int tolua_cocos2dx_LayerColor_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<LayerColor>(tolua_S,"LayerColor");
}

static int tolua_cocos2dx_ParticleSystem_setBlendFunc(lua_State* tolua_S) 
{
    return tolua_cocos2dx_setBlendFunc<ParticleSystem>(tolua_S,"ParticleSystem");
}

static int tolua_cocos2dx_LayerMultiplex_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Array* array = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "LayerMultiplex", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
 
    if (argc > 0)
    {
        if (luavals_variadic_to_array(tolua_S, argc, &array) && nullptr != array  )
        {
            LayerMultiplex* tolua_ret =  LayerMultiplex::createWithArray(array);
            int  nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LayerMultiplex");
            return 1;
        }
        else
        {
            CCLOG("error in tolua_cocos2dx_LayerMultiplex_create \n");
            return 0;
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_Camera_getCenter(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Camera* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Camera *>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_Camera_getCenter'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        float x;
        float y;
        float z;
        self->getCenter(&x, &y, &z);
        tolua_pushnumber(tolua_S,(lua_Number)x);
        tolua_pushnumber(tolua_S, (lua_Number)y);
        tolua_pushnumber(tolua_S, (lua_Number)z);
        return 3;
    }
    
    CCLOG("'getCenter' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getCenter'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_Camera_getEye(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Camera* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Camera *>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_Camera_getEye'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        float x;
        float y;
        float z;
        self->getEye(&x, &y, &z);
        tolua_pushnumber(tolua_S,(lua_Number)x);
        tolua_pushnumber(tolua_S, (lua_Number)y);
        tolua_pushnumber(tolua_S, (lua_Number)z);
        return 3;
    }
    
    CCLOG("'getEye' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getEye'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_Camera_getUp(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Camera* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Camera *>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_Camera_getUp'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        float x;
        float y;
        float z;
        self->getUp(&x, &y, &z);
        tolua_pushnumber(tolua_S,(lua_Number)x);
        tolua_pushnumber(tolua_S, (lua_Number)y);
        tolua_pushnumber(tolua_S, (lua_Number)z);
        return 3;
    }
    
    CCLOG("'getUp' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getUp'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_FileUtils_getStringFromFile(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    FileUtils* self = nullptr;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<FileUtils *>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_FileUtils_getStringFromFile'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if (ok)
        {
            std::string fullPathName = FileUtils::getInstance()->fullPathForFilename(arg0);
            String* contentsOfFile = String::createWithContentsOfFile(fullPathName.c_str());
            if (nullptr != contentsOfFile)
            {
                const char* tolua_ret = contentsOfFile->getCString();
                tolua_pushstring(tolua_S, tolua_ret);
            }
            return 1;
        }
    }
    
    CCLOG("'getStringFromFile' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getStringFromFile'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_UserDefault_getInstance(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"UserDefault",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(0 == argc)
    {
        UserDefault* tolua_ret = (UserDefault*)  UserDefault::getInstance();
        tolua_pushusertype(tolua_S,(void*)tolua_ret,"UserDefault");
        return 1;
    }
    
    CCLOG("'getInstance' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_GLProgram_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = false;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(2 == argc)
    {
        const char *arg0, *arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        GLProgram* tolua_ret = new GLProgram();
        if (nullptr == tolua_ret)
            return 0;        

        tolua_ret->autorelease();
        tolua_ret->initWithVertexShaderFilename(arg0, arg1);
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"GLProgram");
        return 1;
        
    }
    
    CCLOG("'create' function of GLProgram wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_GLProgram_getProgram(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    GLProgram* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_GLProgram_getProgram'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (0 == argc)
    {
        unsigned const int tolua_ret = ( unsigned const int)  self->getProgram();
        tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        return 1;
    }
    
    CCLOG("'getProgram' function of GLProgram wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getProgram'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_GLProgram_setUniformLocationF32(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    GLProgram* self = nullptr;
    int location = 0;
    double f1 = 0.0;
    double f2 = 0.0;
    double f3 = 0.0;
    double f4 = 0.0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_GLProgram_getProgram'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >= 2 && argc <= 5)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
            !tolua_isnumber(tolua_S,3,0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        location = (int)  tolua_tonumber(tolua_S,2,0);
        f1 = (float)  tolua_tonumber(tolua_S,3,0);
        
        if (2 == argc)
        {
            self->setUniformLocationWith1f(location,f1);
            return 0;
        }
        
        if (argc >= 3)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,4,0,&tolua_err))
                goto tolua_lerror;
#endif
            
            f2 = (float)  tolua_tonumber(tolua_S,3,0);
            if (3 == argc)
            {
                self->setUniformLocationWith2f(location, f1, f2);
                return 0;
            }
        }
        
        if (argc >= 4)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,5,0,&tolua_err))
                goto tolua_lerror;
#endif
            
            f3 = (float)  tolua_tonumber(tolua_S,3,0);
            if (4 == argc)
            {
                self->setUniformLocationWith3f(location, f1, f2, f3);
                return 0;
            }
        }
        
        if (argc == 5)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,6,0,&tolua_err))
                goto tolua_lerror;
#endif
            
            f4 = (float)  tolua_tonumber(tolua_S,3,0);
            if (4 == argc)
            {
                self->setUniformLocationWith4f(location, f1, f2, f3, f4);
                return 0;
            }

        }
    }
    
    CCLOG("'setUniformLocationF32' function of GLProgram wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationF32'.",&tolua_err);
    return 0;
#endif    
    
}

static void extendGLProgram(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "GLProgram");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_GLProgram_create );
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"getProgram");
        lua_pushcfunction(tolua_S,tolua_cocos2d_GLProgram_getProgram );
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"setUniformLocationF32");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_GLProgram_setUniformLocationF32 );
        lua_rawset(tolua_S,-3);
    }
}

static int tolua_cocos2dx_Texture2D_setTexParameters(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Texture2D* self = nullptr;
    GLuint arg1 = 0;
    GLuint arg2 = 0;
    GLuint arg3 = 0;
    GLuint arg4 = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (Texture2D*)  tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_Texture2D_setTexParameters'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (4 == argc)
    {        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 4, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 5, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        arg1 = (GLuint)tolua_tonumber(tolua_S, 2, 0);
        arg2 = (GLuint)tolua_tonumber(tolua_S, 3, 0);
        arg3 = (GLuint)tolua_tonumber(tolua_S, 4, 0);
        arg4 = (GLuint)tolua_tonumber(tolua_S, 5, 0);
        
        Texture2D::TexParams param = { arg1, arg2, arg3, arg4 };
        
        self->setTexParameters(param);
        
        return 0;
    }
    
    CCLOG("'setTexParameters' function of Texture2D wrong number of arguments: %d, was expecting %d\n", argc,4);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTexParameters'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_SpriteBatchNode_getDescendants(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2dx_SpriteBatchNode_getDescendants'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        std::vector<Sprite*> ret = cobj->getDescendants();

        lua_newtable(tolua_S);
        
        if (ret.empty())
            return 1;
        
        auto iter = ret.begin();
        int  indexTable = 1;
        for (; iter != ret.end(); ++iter)
        {
            if (nullptr == *iter)
                continue;
            
            lua_pushnumber(tolua_S, (lua_Number)indexTable);
            toluafix_pushusertype_ccobject(tolua_S, (*iter)->_ID, &((*iter)->_luaID), (void*)(*iter),"Sprite");
            lua_rawset(tolua_S, -3);
            (*iter)->retain();
            ++indexTable;
        }
        
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDescendants",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_SpriteBatchNode_getDescendants'.",&tolua_err);
#endif
    return 0;
}

static void extendTexture2D(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "Texture2D");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setTexParameters");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Texture2D_setTexParameters );
        lua_rawset(tolua_S,-3);
    }
}

static void extendMenuItem(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"MenuItem");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptTapHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItem_registerScriptTapHandler);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unregisterScriptTapHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItem_unregisterScriptTapHandler);
        lua_rawset(tolua_S, -3);
    }
}

static void extendMenuItemImage(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"MenuItemImage");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemImage_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendMenuItemLabel(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "MenuItemLabel");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemLabel_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendMenuItemFont(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "MenuItemFont");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemFont_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendMenuItemSprite(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "MenuItemSprite");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemSprite_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendMenuItemToggle(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "MenuItemToggle");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemToggle_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendMenu(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "Menu");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Menu_create);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"alignItemsInRows");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Menu_alignItemsInRows);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"alignItemsInColumns");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Menu_alignItemsInColumns);
        lua_rawset(tolua_S,-3);
    }
}

static void extendNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Node");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Node_registerScriptHandler);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"unregisterScriptHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Node_unregisterScriptHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S,"scheduleUpdateWithPriorityLua");
        lua_pushcfunction(tolua_S,tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S,"unscheduleUpdate");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Node_unscheduleUpdate);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S,"getPosition");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Node_getPosition);
        lua_rawset(tolua_S, -3);
    }
}

static void extendLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Layer");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptTouchHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Layer_registerScriptTouchHandler);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unregisterScriptTouchHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Layer_unregisterScriptTouchHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "registerScriptKeypadHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_registerScriptKeypadHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptKeypadHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_unregisterScriptKeypadHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "registerScriptAccelerateHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_registerScriptAccelerateHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptAccelerateHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_unregisterScriptAccelerateHandler);
        lua_rawset(tolua_S, -3);
    }
}

static void extendScheduler(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Scheduler");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"scheduleScriptFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Scheduler_scheduleScriptFunc);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unscheduleScriptEntry");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Scheduler_unscheduleScriptEntry);
        lua_rawset(tolua_S, -3);
    }
}

static void extendSequence(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Sequence");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Sequence_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendCallFunc(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"CallFunc");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CallFunc_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendSpawn(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Spawn");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Spawn_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendCardinalSplineBy(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"CardinalSplineBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,lua_cocos2d_CardinalSplineBy_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendCatmullRomBy(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"CatmullRomBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CatmullRomBy_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendCatmullRomTo(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"CatmullRomTo");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CatmullRomTo_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendBezierBy(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"BezierBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_BezierBy_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendBezierTo(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"BezierTo");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_BezierTo_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendDrawNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"DrawNode");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"drawPolygon");
        lua_pushcfunction(tolua_S,tolua_cocos2d_DrawNode_drawPolygon);
        lua_rawset(tolua_S,-3);
    }
}

static void extendSprite(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Sprite");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Sprite_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
}

static void extendLayerColor(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"LayerColor");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_LayerColor_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
}

static void extendLayerMultiplex(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"LayerMultiplex");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_LayerMultiplex_create);
        lua_rawset(tolua_S,-3);
    }
}

static void extendParticleSystem(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"ParticleSystem");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_ParticleSystem_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
}

static void extendCamera(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "Camera");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getCenter");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Camera_getCenter );
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"getUp");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Camera_getUp );
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"getEye");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Camera_getEye );
        lua_rawset(tolua_S,-3);
    }
}

static void extendFileUtils(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "FileUtils");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getStringFromFile");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_FileUtils_getStringFromFile );
        lua_rawset(tolua_S,-3);
    }
}

static void extendUserDefault(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "UserDefault");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getInstance");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_UserDefault_getInstance );
        lua_rawset(tolua_S,-3);
    }
}

static void extendSpriteBatchNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "SpriteBatchNode");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getDescendants");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_SpriteBatchNode_getDescendants );
        lua_rawset(tolua_S,-3);
    }
}


int register_all_cocos2dx_manual(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    extendNode(tolua_S);
    extendLayer(tolua_S);
    extendMenuItem(tolua_S);
    extendMenuItemImage(tolua_S);
    extendMenuItemLabel(tolua_S);
    extendMenuItemFont(tolua_S);
    extendMenuItemSprite(tolua_S);
    extendMenuItemToggle(tolua_S);
    extendMenu(tolua_S);
    extendScheduler(tolua_S);
    extendSequence(tolua_S);
    extendCallFunc(tolua_S);
    extendSpawn(tolua_S);
    extendCardinalSplineBy(tolua_S);
    extendCatmullRomBy(tolua_S);
    extendCatmullRomTo(tolua_S);
    extendBezierBy(tolua_S);
    extendBezierTo(tolua_S);
    extendDrawNode(tolua_S);
    extendSprite(tolua_S);
    extendLayerColor(tolua_S);
    extendLayerMultiplex(tolua_S);
    extendParticleSystem(tolua_S);
    extendCamera(tolua_S);
    extendFileUtils(tolua_S);
    extendUserDefault(tolua_S);
    extendGLProgram(tolua_S);
    extendTexture2D(tolua_S);
    extendSpriteBatchNode(tolua_S);
    return 0;
}