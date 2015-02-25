/*
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
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


void jsb_register_chipmunk(JSContext* cx, JSObject *object)
{
    //
    // Chipmunk
    //
    JSObject *chipmunk = JS_NewObject(cx, NULL, NULL, NULL);
    JS::RootedValue chipmunkVal(cx);
    
    chipmunkVal = OBJECT_TO_JSVAL(chipmunk);
    JS_SetProperty(cx, object, "cp", chipmunkVal);
    
    JSB_cpBase_createClass(cx, chipmunk, "Base");  // manual base class registration
#include "js_bindings_chipmunk_auto_classes_registration.h"
#include "js_bindings_chipmunk_functions_registration.h"

    // manual
    JS_DefineFunction(cx, chipmunk, "spaceAddCollisionHandler", JSB_cpSpaceAddCollisionHandler, 8, JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceRemoveCollisionHandler", JSB_cpSpaceRemoveCollisionHandler, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetBodies", JSB_cpArbiterGetBodies, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetShapes", JSB_cpArbiterGetShapes, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetUserData", JSB_cpBodyGetUserData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetUserData", JSB_cpBodySetUserData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE );

    JS_DefineFunction(cx, chipmunk, "areaForPoly", JSB_cpAreaForPoly, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "momentForPoly", JSB_cpMomentForPoly, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "centroidForPoly", JSB_cpCentroidForPoly, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "recenterPoly", JSB_cpRecenterPoly, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE );

    JS_DefineFunction(cx, JSB_cpSpace_object, "segmentQueryFirst", JSB_cpSpace_segmentQueryFirst, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, JSB_cpSpace_object, "nearestPointQueryNearest", JSB_cpSpace_nearestPointQueryNearest, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, JSB_cpSpace_object, "eachShape", JSB_cpSpace_eachShape, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, JSB_cpSpace_object, "eachBody", JSB_cpSpace_eachBody, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, JSB_cpSpace_object, "eachConstraint", JSB_cpSpace_eachConstraint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    register_CCPhysicsSprite(cx, object);
    register_CCPhysicsDebugNode(cx, object);
}

