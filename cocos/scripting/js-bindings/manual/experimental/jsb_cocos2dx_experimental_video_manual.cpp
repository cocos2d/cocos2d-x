#include "jsb_cocos2dx_experimental_video_manual.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "UIVideoPlayer.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "cocos2d.h"

using namespace cocos2d;


static bool jsb_cocos2dx_experimental_ui_VideoPlayer_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    experimental::ui::VideoPlayer* cobj = (experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 1){
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, obj, args.get(0)));
        cobj->addEventListener([=](Ref* widget, experimental::ui::VideoPlayer::EventType type)->void{
            jsval arg[2];
            js_proxy_t *proxy = js_get_or_create_proxy(cx, widget);
            if(proxy)
                arg[0] = OBJECT_TO_JSVAL(proxy->obj);
            else
                arg[0] = JSVAL_NULL;
            arg[1] = int32_to_jsval(cx, (int32_t)type);
            JS::RootedValue rval(cx);

            bool ok = func->invoke(2, arg, &rval);
            if (!ok && JS_IsExceptionPending(cx)) {
                JS_ReportPendingException(cx);
            }
        });
        return true;
    }
}

extern JSObject* jsb_cocos2d_experimental_ui_VideoPlayer_prototype;

void register_all_cocos2dx_experimental_video_manual(JSContext* cx, JS::HandleObject global)
{
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocos2d_experimental_ui_VideoPlayer_prototype), "addEventListener", jsb_cocos2dx_experimental_ui_VideoPlayer_addEventListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}

#endif
