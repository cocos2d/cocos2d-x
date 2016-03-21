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

#include "scripting/js-bindings/manual/js_bindings_config.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"


// chipmunk
#include "scripting/js-bindings/auto/js_bindings_chipmunk_auto_classes.h"
#include "scripting/js-bindings/auto/js_bindings_chipmunk_functions.h"
#include "scripting/js-bindings/manual/chipmunk/js_bindings_chipmunk_manual.h"


void jsb_register_chipmunk(JSContext* cx, JS::HandleObject object)
{
    //
    // Chipmunk
    //
    JS::RootedObject chipmunk(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
    JS::RootedValue chipmunkVal(cx);
    
    chipmunkVal = OBJECT_TO_JSVAL(chipmunk);
    JS_SetProperty(cx, object, "cp", chipmunkVal);
    
    JSB_cpBase_createClass(cx, chipmunk, "Base");  // manual base class registration
#include "scripting/js-bindings/auto/js_bindings_chipmunk_auto_classes_registration.h"
#include "scripting/js-bindings/auto/js_bindings_chipmunk_functions_registration.h"

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

    // Compatibility with Chipmunk 6.2
    JS_DefineFunction(cx, chipmunk, "momentForSegment", JSB_cpMomentForSegment, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    JS::RootedObject space(cx, JSB_cpSpace_object);
    JS_DefineFunction(cx, space, "segmentQueryFirst", JSB_cpSpace_segmentQueryFirst, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, space, "pointQueryNearest", JSB_cpSpace_pointQueryNearest, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    // Compatibility with Chipmunk 6.2
    JS_DefineFunction(cx, space, "removeCollisionHandler", JSB_cpSpace_removeCollisionHandler, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, space, "setDefaultCollisionHandler", JSB_cpSpace_setDefaultCollisionHandler, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    JS::RootedObject polyShape(cx, JSB_cpPolyShape_object);
    JS_DefineFunction(cx, polyShape, "getVerts", JSB_cpPolyShape_getVerts, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    register_CCPhysicsSprite(cx, object);
    register_CCPhysicsDebugNode(cx, object);
}

