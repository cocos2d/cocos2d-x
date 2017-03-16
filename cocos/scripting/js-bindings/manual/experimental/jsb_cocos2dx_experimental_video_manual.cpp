#include "scripting/js-bindings/manual/experimental/jsb_cocos2dx_experimental_video_manual.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "ui/UIVideoPlayer.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"


using namespace cocos2d;


static bool jsb_cocos2dx_experimental_ui_VideoPlayer_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    experimental::ui::VideoPlayer* cobj = (experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 1){
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, obj, args.get(0), args.thisv()));
        cobj->addEventListener([=](Ref* widget, experimental::ui::VideoPlayer::EventType type)->void{
            jsval arg[2];
            JS::RootedObject jsobj(cx, js_get_or_create_jsobject<Ref>(cx, widget));
            arg[0] = OBJECT_TO_JSVAL(jsobj);
            arg[1] = int32_to_jsval(cx, (int32_t)type);
            JS::RootedValue rval(cx);

            bool ok = func->invoke(2, arg, &rval);
            if (!ok && JS_IsExceptionPending(cx)) {
                JS_ReportPendingException(cx);
            }
        });
        return true;
    }

    JS_ReportError(cx, "jsb_cocos2dx_experimental_ui_VideoPlayer_addEventListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

extern JSObject* jsb_cocos2d_experimental_ui_VideoPlayer_prototype;

void register_all_cocos2dx_experimental_video_manual(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject proto(cx, jsb_cocos2d_experimental_ui_VideoPlayer_prototype);
    JS_DefineFunction(cx, proto, "addEventListener", jsb_cocos2dx_experimental_ui_VideoPlayer_addEventListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}

#endif
