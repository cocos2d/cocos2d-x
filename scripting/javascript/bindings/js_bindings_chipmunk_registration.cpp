/*
 * JS Bindings: https://github.com/zynga/jsbindings
 *
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef JSB_INCLUDE_CHIPMUNK
#define JSB_INCLUDE_CHIPMUNK
#endif

#include "js_bindings_config.h"
#include "ScriptingCore.h"


// chipmunk
#include "js_bindings_chipmunk_auto_classes.h"
#include "js_bindings_chipmunk_functions.h"
#include "js_bindings_chipmunk_manual.h"


void jsb_register_chipmunk(JSContext *_cx, JSObject *object)
{
	//
	// Chipmunk
	//
	JSObject *chipmunk = JS_NewObject(_cx, NULL, NULL, NULL);
	jsval chipmunkVal = OBJECT_TO_JSVAL(chipmunk);
	JS_SetProperty(_cx, object, "cp", &chipmunkVal);
	
	JSB_cpBase_createClass(_cx, chipmunk, "Base");  // manual base class registration
#include "js_bindings_chipmunk_auto_classes_registration.h"
#include "js_bindings_chipmunk_functions_registration.h"
	
	// manual
	JS_DefineFunction(_cx, chipmunk, "spaceAddCollisionHandler", JSB_cpSpaceAddCollisionHandler, 8, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
	JS_DefineFunction(_cx, chipmunk, "spaceRemoveCollisionHandler", JSB_cpSpaceRemoveCollisionHandler, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
	JS_DefineFunction(_cx, chipmunk, "arbiterGetBodies", JSB_cpArbiterGetBodies, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
	JS_DefineFunction(_cx, chipmunk, "arbiterGetShapes", JSB_cpArbiterGetShapes, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
	JS_DefineFunction(_cx, chipmunk, "bodyGetUserData", JSB_cpBodyGetUserData, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
	JS_DefineFunction(_cx, chipmunk, "bodySetUserData", JSB_cpBodySetUserData, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );

	JS_DefineFunction(_cx, chipmunk, "areaForPoly", JSB_cpAreaForPoly, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
	JS_DefineFunction(_cx, chipmunk, "momentForPoly", JSB_cpMomentForPoly, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
	JS_DefineFunction(_cx, chipmunk, "centroidForPoly", JSB_cpCentroidForPoly, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
	JS_DefineFunction(_cx, chipmunk, "recenterPoly", JSB_cpRecenterPoly, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    register_CCPhysicsSprite(_cx, object);
    register_CCPhysicsDebugNode(_cx, object);
}

