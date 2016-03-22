#include "scripting/lua-bindings/auto/lua_cocos2dx_experimental_webview_auto.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
#include "ui/UIWebView.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cocos2dx_experimental_webview_WebView_canGoBack(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_canGoBack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_canGoBack'", nullptr);
            return 0;
        }
        bool ret = cobj->canGoBack();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:canGoBack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_canGoBack'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_loadHTMLString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_loadHTMLString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.WebView:loadHTMLString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_loadHTMLString'", nullptr);
            return 0;
        }
        cobj->loadHTMLString(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.WebView:loadHTMLString");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccexp.WebView:loadHTMLString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_loadHTMLString'", nullptr);
            return 0;
        }
        cobj->loadHTMLString(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:loadHTMLString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_loadHTMLString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_goForward(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_goForward'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_goForward'", nullptr);
            return 0;
        }
        cobj->goForward();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:goForward",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_goForward'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_goBack(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_goBack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_goBack'", nullptr);
            return 0;
        }
        cobj->goBack();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:goBack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_goBack'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_setScalesPageToFit(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_setScalesPageToFit'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccexp.WebView:setScalesPageToFit");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_setScalesPageToFit'", nullptr);
            return 0;
        }
        cobj->setScalesPageToFit(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:setScalesPageToFit",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_setScalesPageToFit'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_loadFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_loadFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.WebView:loadFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_loadFile'", nullptr);
            return 0;
        }
        cobj->loadFile(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:loadFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_loadFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_loadURL(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_loadURL'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.WebView:loadURL");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_loadURL'", nullptr);
            return 0;
        }
        cobj->loadURL(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:loadURL",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_loadURL'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_evaluateJS(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_evaluateJS'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.WebView:evaluateJS");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_evaluateJS'", nullptr);
            return 0;
        }
        cobj->evaluateJS(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:evaluateJS",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_evaluateJS'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_getOnJSCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_getOnJSCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_getOnJSCallback'", nullptr);
            return 0;
        }
        cocos2d::experimental::ui::WebView::ccWebViewCallback ret = cobj->getOnJSCallback();
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:getOnJSCallback",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_getOnJSCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_canGoForward(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_canGoForward'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_canGoForward'", nullptr);
            return 0;
        }
        bool ret = cobj->canGoForward();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:canGoForward",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_canGoForward'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_stopLoading(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_stopLoading'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_stopLoading'", nullptr);
            return 0;
        }
        cobj->stopLoading();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:stopLoading",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_stopLoading'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_reload(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_reload'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_reload'", nullptr);
            return 0;
        }
        cobj->reload();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:reload",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_reload'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_setJavascriptInterfaceScheme(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::ui::WebView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_webview_WebView_setJavascriptInterfaceScheme'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.WebView:setJavascriptInterfaceScheme");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_setJavascriptInterfaceScheme'", nullptr);
            return 0;
        }
        cobj->setJavascriptInterfaceScheme(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:setJavascriptInterfaceScheme",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_setJavascriptInterfaceScheme'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::ui::WebView* ret = cocos2d::experimental::ui::WebView::create();
        object_to_luaval<cocos2d::experimental::ui::WebView>(tolua_S, "ccexp.WebView",(cocos2d::experimental::ui::WebView*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.WebView:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_webview_WebView_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::ui::WebView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_webview_WebView_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::experimental::ui::WebView();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccexp.WebView");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.WebView:WebView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_webview_WebView_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_experimental_webview_WebView_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (WebView)");
    return 0;
}

int lua_register_cocos2dx_experimental_webview_WebView(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.WebView");
    tolua_cclass(tolua_S,"WebView","ccexp.WebView","ccui.Widget",nullptr);

    tolua_beginmodule(tolua_S,"WebView");
        tolua_function(tolua_S,"new",lua_cocos2dx_experimental_webview_WebView_constructor);
        tolua_function(tolua_S,"canGoBack",lua_cocos2dx_experimental_webview_WebView_canGoBack);
        tolua_function(tolua_S,"loadHTMLString",lua_cocos2dx_experimental_webview_WebView_loadHTMLString);
        tolua_function(tolua_S,"goForward",lua_cocos2dx_experimental_webview_WebView_goForward);
        tolua_function(tolua_S,"goBack",lua_cocos2dx_experimental_webview_WebView_goBack);
        tolua_function(tolua_S,"setScalesPageToFit",lua_cocos2dx_experimental_webview_WebView_setScalesPageToFit);
        tolua_function(tolua_S,"loadFile",lua_cocos2dx_experimental_webview_WebView_loadFile);
        tolua_function(tolua_S,"loadURL",lua_cocos2dx_experimental_webview_WebView_loadURL);
        tolua_function(tolua_S,"evaluateJS",lua_cocos2dx_experimental_webview_WebView_evaluateJS);
        tolua_function(tolua_S,"getOnJSCallback",lua_cocos2dx_experimental_webview_WebView_getOnJSCallback);
        tolua_function(tolua_S,"canGoForward",lua_cocos2dx_experimental_webview_WebView_canGoForward);
        tolua_function(tolua_S,"stopLoading",lua_cocos2dx_experimental_webview_WebView_stopLoading);
        tolua_function(tolua_S,"reload",lua_cocos2dx_experimental_webview_WebView_reload);
        tolua_function(tolua_S,"setJavascriptInterfaceScheme",lua_cocos2dx_experimental_webview_WebView_setJavascriptInterfaceScheme);
        tolua_function(tolua_S,"create", lua_cocos2dx_experimental_webview_WebView_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::ui::WebView).name();
    g_luaType[typeName] = "ccexp.WebView";
    g_typeCast["WebView"] = "ccexp.WebView";
    return 1;
}
TOLUA_API int register_all_cocos2dx_experimental_webview(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccexp",0);
	tolua_beginmodule(tolua_S,"ccexp");

	lua_register_cocos2dx_experimental_webview_WebView(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

#endif
