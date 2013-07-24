#ifndef __LUA_SCROLLVIEW_H__
#define __LUA_SCROLLVIEW_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif
#include "GUI/CCScrollView/CCScrollView.h"

class LuaScrollView:public cocos2d::extension::ScrollView,public cocos2d::extension::ScrollViewDelegate
{
public:
    virtual ~LuaScrollView();
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view);
    enum ScrollViewScriptHandlerType
    {
        kScrollViewScriptScroll   = 0,
        kScrollViewScriptZoom,
    };
    
};

TOLUA_API int tolua_scroll_view_open(lua_State* tolua_S);

#endif //__LUA_SCROLLVIEW_H__
