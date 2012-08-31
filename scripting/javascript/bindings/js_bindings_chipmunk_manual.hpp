//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef __js_bindings_chipmunk_manual
#define __js_bindings_chipmunk_manual

#include "chipmunk.h"
#include "jsapi.h"
#include "js_bindings_chipmunk_functions.hpp"

JSBool JSPROXY_cpSpaceAddCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceRemoveCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp);

JSBool JSPROXY_cpArbiterGetBodies(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterGetShapes(JSContext *cx, uint32_t argc, jsval *vp);

JSBool JSPROXY_cpBodySetUserData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetUserData(JSContext *cx, uint32_t argc, jsval *vp);


void register_chipmunk_manual(JSContext* cx, JSObject* obj);

extern "C" {
    void JSPROXY_CCPhysicsSprite_createClass(JSContext *cx, JSObject* globalObj);
}

void register_CCPhysicsSprite(JSContext *cx, JSObject *obj);

#endif // __js_bindings_chipmunk_manual
