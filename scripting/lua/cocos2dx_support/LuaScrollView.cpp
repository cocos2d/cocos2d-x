#ifdef __cplusplus
extern "C" {
#endif
    #include "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include <map>
#include <string>
#include "LuaScrollView.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "LuaScriptHandlerMgr.h"

using namespace cocos2d;
using namespace cocos2d::extension;


LuaScrollView::~LuaScrollView()
{

}
    
void LuaScrollView::scrollViewDidScroll(ScrollView* view)
{
    LuaScrollView* luaView = dynamic_cast<LuaScrollView*>(view);
    if (NULL != luaView)
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)luaView, ScriptHandlerMgr::kScrollViewScrollHandler);
        if (0 != handler)
        {
            CommonScriptData data(handler,"");
            ScriptEvent event(kCommonEvent,(void*)&data);
            ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        }
    }
}
    
void LuaScrollView::scrollViewDidZoom(ScrollView* view)
{
    LuaScrollView* luaView = dynamic_cast<LuaScrollView*>(view);
    if (NULL != luaView)
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)luaView, ScriptHandlerMgr::kScrollViewZoomHandler);
        if (0 != handler)
        {
            CommonScriptData data(handler,"");
            ScriptEvent event(kCommonEvent,(void*)&data);
            ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        }
    }
}


#ifdef __cplusplus
static int tolua_collect_ScrollView (lua_State* tolua_S)
{
    ScrollView *self = (ScrollView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif

/* function to release collected object via destructor */
static void tolua_reg_scrollview_type(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "CCScrollView");
}

/* method: new of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_new00
static int tolua_Cocos2d_ScrollView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            LuaScrollView* tolua_ret = (LuaScrollView*)  Mtolua_new((ScrollView)());
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScrollView");
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

/* method: new_local of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_new00_local
static int tolua_Cocos2d_ScrollView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            LuaScrollView* tolua_ret = (LuaScrollView*)  Mtolua_new((ScrollView)());
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScrollView");
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

/* method: delete of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_delete00
static int tolua_Cocos2d_ScrollView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
        Mtolua_delete(self);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_create00
static int tolua_Cocos2d_ScrollView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
        !tolua_isusertype(tolua_S,3,"CCNode",1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Size size = *((Size*)  tolua_tousertype(tolua_S,2,0));
        Node* container = ((Node*)  tolua_tousertype(tolua_S,3,NULL));
        {
            LuaScrollView* tolua_ret = new LuaScrollView();
            if (NULL != tolua_ret && tolua_ret->initWithViewSize(size,container) )
            {
                tolua_ret->autorelease();
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScrollView");
                return 1;
            }
            else
            {
                CC_SAFE_DELETE(tolua_ret);
                return 0;
            }
        }
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_create01
static int tolua_Cocos2d_ScrollView_create01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        LuaScrollView* tolua_ret = new LuaScrollView();
        if (NULL != tolua_ret && tolua_ret->init() )
        {
            tolua_ret->autorelease();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScrollView");
            return 1;
        }
        else
        {
            CC_SAFE_DELETE(tolua_ret);
            return 0;
        }
    }
tolua_lerror:
    return tolua_Cocos2d_ScrollView_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE


/* method: isClippingToBounds of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_isClippingToBounds00
static int tolua_Cocos2d_ScrollView_isClippingToBounds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isClippingToBounds'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->isClippingToBounds();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isClippingToBounds'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContainer of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setContainer00
static int tolua_Cocos2d_ScrollView_setContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Node* pContainer = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContainer'", NULL);
#endif
        {
            self->setContainer(pContainer);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setContainer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentOffsetInDuration of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setContentOffsetInDuration00
static int tolua_Cocos2d_ScrollView_setContentOffsetInDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Point offset = *((Point*)  tolua_tousertype(tolua_S,2,0));
        float dt = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentOffsetInDuration'", NULL);
#endif
        {
            self->setContentOffsetInDuration(offset,dt);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setContentOffsetInDuration'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomScaleInDuration of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setZoomScaleInDuration00
static int tolua_Cocos2d_ScrollView_setZoomScaleInDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        float s = ((float)  tolua_tonumber(tolua_S,2,0));
        float dt = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomScaleInDuration'", NULL);
#endif
        {
            self->setZoomScaleInDuration(s,dt);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setZoomScaleInDuration'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_addChild00
static int tolua_Cocos2d_ScrollView_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Node* child = ((Node*)  tolua_tousertype(tolua_S,2,0));
        int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
        int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
        {
            self->addChild(child,zOrder,tag);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_addChild01
static int tolua_Cocos2d_ScrollView_addChild01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Node* child = ((Node*)  tolua_tousertype(tolua_S,2,0));
        int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
        {
            self->addChild(child,zOrder);
        }
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_ScrollView_addChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_addChild02
static int tolua_Cocos2d_ScrollView_addChild02(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Node* child = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
        {
            self->addChild(child);
        }
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_ScrollView_addChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_ccTouchBegan00
static int tolua_Cocos2d_ScrollView_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Touch* pTouch = ((Touch*)  tolua_tousertype(tolua_S,2,0));
        Event* pEvent = ((Event*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->ccTouchBegan(pTouch,pEvent);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContainer of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_getContainer00
static int tolua_Cocos2d_ScrollView_getContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContainer'", NULL);
#endif
        {
            Node* tolua_ret = (Node*)  self->getContainer();
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getContainer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_ccTouchEnded00
static int tolua_Cocos2d_ScrollView_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Touch* pTouch = ((Touch*)  tolua_tousertype(tolua_S,2,0));
        Event* pEvent = ((Event*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
        {
            self->ccTouchEnded(pTouch,pEvent);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDirection of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_getDirection00
static int tolua_Cocos2d_ScrollView_getDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDirection'", NULL);
#endif
        {
            ScrollView::Direction tolua_ret = (ScrollView::Direction)  self->getDirection();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getDirection'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZoomScale of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_getZoomScale00
static int tolua_Cocos2d_ScrollView_getZoomScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZoomScale'", NULL);
#endif
        {
            float tolua_ret = (float)  self->getZoomScale();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getZoomScale'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateInset of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_updateInset00
static int tolua_Cocos2d_ScrollView_updateInset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateInset'", NULL);
#endif
        {
            self->updateInset();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'updateInset'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithViewSize of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_initWithViewSize00
static int tolua_Cocos2d_ScrollView_initWithViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
        !tolua_isusertype(tolua_S,3,"CCNode",1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Size size = *((Size*)  tolua_tousertype(tolua_S,2,0));
        Node* container = ((Node*)  tolua_tousertype(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithViewSize'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->initWithViewSize(size,container);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'initWithViewSize'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_pause00
static int tolua_Cocos2d_ScrollView_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Object* sender = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
        {
            self->pause(sender);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDirection of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setDirection00
static int tolua_Cocos2d_ScrollView_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        ScrollView::Direction eDirection = ((ScrollView::Direction) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDirection'", NULL);
#endif
        {
            self->setDirection(eDirection);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setDirection'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBounceable of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setBounceable00
static int tolua_Cocos2d_ScrollView_setBounceable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        bool bBounceable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBounceable'", NULL);
#endif
        {
            self->setBounceable(bBounceable);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setBounceable'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentOffset of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setContentOffset00
static int tolua_Cocos2d_ScrollView_setContentOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
        !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Point offset = *((Point*)  tolua_tousertype(tolua_S,2,0));
        bool animated = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentOffset'", NULL);
#endif
        {
            self->setContentOffset(offset,animated);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setContentOffset'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDragging of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_isDragging00
static int tolua_Cocos2d_ScrollView_isDragging00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDragging'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->isDragging();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isDragging'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_init00
static int tolua_Cocos2d_ScrollView_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->init();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBounceable of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_isBounceable00
static int tolua_Cocos2d_ScrollView_isBounceable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBounceable'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->isBounceable();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isBounceable'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_getContentSize00
static int tolua_Cocos2d_ScrollView_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const LuaScrollView* self = (const LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
        {
            const Size& tolua_ret = (const Size&)  self->getContentSize();
            tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_ccTouchMoved00
static int tolua_Cocos2d_ScrollView_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Touch* pTouch = ((Touch*)  tolua_tousertype(tolua_S,2,0));
        Event* pEvent = ((Event*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
        {
            self->ccTouchMoved(pTouch,pEvent);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchEnabled of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setTouchEnabled00
static int tolua_Cocos2d_ScrollView_setTouchEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        bool e = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEnabled'", NULL);
#endif
        {
            self->setTouchEnabled(e);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTouchEnabled'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentOffset of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_getContentOffset00
static int tolua_Cocos2d_ScrollView_getContentOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentOffset'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->getContentOffset();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getContentOffset'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_resume00
static int tolua_Cocos2d_ScrollView_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Object* sender = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
        {
            self->resume(sender);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setClippingToBounds of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setClippingToBounds00
static int tolua_Cocos2d_ScrollView_setClippingToBounds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        bool bClippingToBounds = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setClippingToBounds'", NULL);
#endif
        {
            self->setClippingToBounds(bClippingToBounds);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setClippingToBounds'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewSize of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setViewSize00
static int tolua_Cocos2d_ScrollView_setViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Size size = *((Size*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewSize'", NULL);
#endif
        {
            self->setViewSize(size);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setViewSize'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getViewSize of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_getViewSize00
static int tolua_Cocos2d_ScrollView_getViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getViewSize'", NULL);
#endif
        {
            Size tolua_ret = (Size)  self->getViewSize();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Size)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
                tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getViewSize'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: maxContainerOffset of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_maxContainerOffset00
static int tolua_Cocos2d_ScrollView_maxContainerOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'maxContainerOffset'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->maxContainerOffset();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'maxContainerOffset'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentSize of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setContentSize00
static int tolua_Cocos2d_ScrollView_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        const Size* size = ((const Size*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
        {
            self->setContentSize(*size);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setContentSize'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchMoved of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_isTouchMoved00
static int tolua_Cocos2d_ScrollView_isTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchMoved'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->isTouchMoved();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isTouchMoved'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isNodeVisible of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_isNodeVisible00
static int tolua_Cocos2d_ScrollView_isNodeVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isNodeVisible'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->isNodeVisible(node);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'isNodeVisible'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchCancelled of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_ccTouchCancelled00
static int tolua_Cocos2d_ScrollView_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        Touch* pTouch = ((Touch*)  tolua_tousertype(tolua_S,2,0));
        Event* pEvent = ((Event*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchCancelled'", NULL);
#endif
        {
            self->ccTouchCancelled(pTouch,pEvent);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'ccTouchCancelled'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: minContainerOffset of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_minContainerOffset00
static int tolua_Cocos2d_ScrollView_minContainerOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'minContainerOffset'", NULL);
#endif
        {
            Point tolua_ret = (Point)  self->minContainerOffset();
            {
#ifdef __cplusplus
                void* tolua_obj = Mtolua_new((Point)(tolua_ret));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
                void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
                tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
                tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
            }
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'minContainerOffset'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_registerWithTouchDispatcher00
static int tolua_Cocos2d_ScrollView_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
        {
            self->registerWithTouchDispatcher();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomScale of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setZoomScale00
static int tolua_Cocos2d_ScrollView_setZoomScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        float s = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomScale'", NULL);
#endif
        {
            self->setZoomScale(s);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setZoomScale'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZoomScale of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setZoomScale01
static int tolua_Cocos2d_ScrollView_setZoomScale01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        float s = ((float)  tolua_tonumber(tolua_S,2,0));
        bool animated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZoomScale'", NULL);
#endif
        {
            self->setZoomScale(s,animated);
        }
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2d_ScrollView_setZoomScale00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegate of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScrollView_setDelegate00
static int tolua_Cocos2d_ScrollView_setDelegate00(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        LuaScrollView* self = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDelegate'", NULL);
#endif
        {
            self->setDelegate(self);
        }

    }
    return 0;
tolua_lerror:
    return 0;
}
#endif //#ifndef TOLUA_DISABLE


TOLUA_API int tolua_scroll_view_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_scrollview_type(tolua_S);
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
    tolua_constant(tolua_S,"kScrollViewDirectionNone",(int)ScrollView::Direction::NONE);
    tolua_constant(tolua_S,"kScrollViewDirectionHorizontal",(int)ScrollView::Direction::HORIZONTAL);
    tolua_constant(tolua_S,"kScrollViewDirectionVertical",(int)ScrollView::Direction::VERTICAL);
    tolua_constant(tolua_S,"kScrollViewDirectionBoth",(int)ScrollView::Direction::BOTH);
     tolua_constant(tolua_S,"kScrollViewScriptScroll",LuaScrollView::kScrollViewScriptScroll);
     tolua_constant(tolua_S,"kScrollViewScriptZoom",LuaScrollView::kScrollViewScriptZoom);
     #ifdef __cplusplus
     tolua_cclass(tolua_S,"CCScrollView","CCScrollView","CCLayer",tolua_collect_ScrollView);
     #else
     tolua_cclass(tolua_S,"CCScrollView","CCScrollView","CCLayer",NULL);
     #endif
     tolua_beginmodule(tolua_S,"CCScrollView");
        tolua_function(tolua_S,"new",tolua_Cocos2d_ScrollView_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_ScrollView_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_ScrollView_new00_local);
        tolua_function(tolua_S,"delete",tolua_Cocos2d_ScrollView_delete00);
        tolua_function(tolua_S,"create",tolua_Cocos2d_ScrollView_create00);
        tolua_function(tolua_S,"create",tolua_Cocos2d_ScrollView_create01);
        tolua_function(tolua_S,"isClippingToBounds",tolua_Cocos2d_ScrollView_isClippingToBounds00);
        tolua_function(tolua_S,"setContainer",tolua_Cocos2d_ScrollView_setContainer00);
        tolua_function(tolua_S,"setContentOffsetInDuration",tolua_Cocos2d_ScrollView_setContentOffsetInDuration00);
        tolua_function(tolua_S,"setZoomScaleInDuration",tolua_Cocos2d_ScrollView_setZoomScaleInDuration00);
        tolua_function(tolua_S,"addChild",tolua_Cocos2d_ScrollView_addChild00);
        tolua_function(tolua_S,"addChild",tolua_Cocos2d_ScrollView_addChild01);
        tolua_function(tolua_S,"addChild",tolua_Cocos2d_ScrollView_addChild02);
        tolua_function(tolua_S,"ccTouchBegan",tolua_Cocos2d_ScrollView_ccTouchBegan00);
        tolua_function(tolua_S,"getContainer",tolua_Cocos2d_ScrollView_getContainer00);
        tolua_function(tolua_S,"ccTouchEnded",tolua_Cocos2d_ScrollView_ccTouchEnded00);
        tolua_function(tolua_S,"getDirection",tolua_Cocos2d_ScrollView_getDirection00);
        tolua_function(tolua_S,"getZoomScale",tolua_Cocos2d_ScrollView_getZoomScale00);
        tolua_function(tolua_S,"updateInset",tolua_Cocos2d_ScrollView_updateInset00);
        tolua_function(tolua_S,"initWithViewSize",tolua_Cocos2d_ScrollView_initWithViewSize00);
        tolua_function(tolua_S,"pause",tolua_Cocos2d_ScrollView_pause00);
        tolua_function(tolua_S,"setDirection",tolua_Cocos2d_ScrollView_setDirection00);
        tolua_function(tolua_S,"setBounceable",tolua_Cocos2d_ScrollView_setBounceable00);
        tolua_function(tolua_S,"setContentOffset",tolua_Cocos2d_ScrollView_setContentOffset00);
        tolua_function(tolua_S,"isDragging",tolua_Cocos2d_ScrollView_isDragging00);
        tolua_function(tolua_S,"init",tolua_Cocos2d_ScrollView_init00);
        tolua_function(tolua_S,"isBounceable",tolua_Cocos2d_ScrollView_isBounceable00);
        tolua_function(tolua_S,"getContentSize",tolua_Cocos2d_ScrollView_getContentSize00);
        tolua_function(tolua_S,"ccTouchMoved",tolua_Cocos2d_ScrollView_ccTouchMoved00);
        tolua_function(tolua_S,"setTouchEnabled",tolua_Cocos2d_ScrollView_setTouchEnabled00);
        tolua_function(tolua_S,"getContentOffset",tolua_Cocos2d_ScrollView_getContentOffset00);
        tolua_function(tolua_S,"resume",tolua_Cocos2d_ScrollView_resume00);
        tolua_function(tolua_S,"setClippingToBounds",tolua_Cocos2d_ScrollView_setClippingToBounds00);
        tolua_function(tolua_S,"setViewSize",tolua_Cocos2d_ScrollView_setViewSize00);
        tolua_function(tolua_S,"getViewSize",tolua_Cocos2d_ScrollView_getViewSize00);
        tolua_function(tolua_S,"maxContainerOffset",tolua_Cocos2d_ScrollView_maxContainerOffset00);
        tolua_function(tolua_S,"setContentSize",tolua_Cocos2d_ScrollView_setContentSize00);
        tolua_function(tolua_S,"isTouchMoved",tolua_Cocos2d_ScrollView_isTouchMoved00);
        tolua_function(tolua_S,"isNodeVisible",tolua_Cocos2d_ScrollView_isNodeVisible00);
        tolua_function(tolua_S,"ccTouchCancelled",tolua_Cocos2d_ScrollView_ccTouchCancelled00);
        tolua_function(tolua_S,"minContainerOffset",tolua_Cocos2d_ScrollView_minContainerOffset00);
        tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_Cocos2d_ScrollView_registerWithTouchDispatcher00);
        tolua_function(tolua_S,"setZoomScale",tolua_Cocos2d_ScrollView_setZoomScale00);
        tolua_function(tolua_S,"setZoomScale",tolua_Cocos2d_ScrollView_setZoomScale01);
        tolua_function(tolua_S, "setDelegate", tolua_Cocos2d_ScrollView_setDelegate00);
     tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}


