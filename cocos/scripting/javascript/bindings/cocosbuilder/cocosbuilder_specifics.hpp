#ifndef __JS_COCOSBUILDER_SPECIFICS_H__
#define __JS_COCOSBUILDER_SPECIFICS_H__

#include "../cocos2d_specifics.hpp"

class JSCCBAnimationWrapper: public JSCallbackWrapper {
public:
    JSCCBAnimationWrapper() {}
    virtual ~JSCCBAnimationWrapper() {}
    
    void animationCompleteCallback() {
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        if(!JSVAL_IS_VOID(_jsCallback)  && !JSVAL_IS_VOID(_jsThisObj)) {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            
            JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(_jsThisObj), _jsCallback, 0, NULL, &retval);
        }
    }
    
};

#endif
