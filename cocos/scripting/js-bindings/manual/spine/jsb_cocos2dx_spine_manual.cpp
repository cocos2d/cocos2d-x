/*
 * Created by ucchen on 2/12/14.
 * Copyright (c) 2014 Chukong Technologies Inc.
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

#include "jsb_cocos2dx_spine_manual.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "spine/spine-cocos2dx.h"

using namespace spine;

jsval speventdata_to_jsval(JSContext* cx, spEventData& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "name", c_string_to_jsval(cx, v.name), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "intValue", INT_TO_JSVAL(v.intValue), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "floatValue", DOUBLE_TO_JSVAL(v.floatValue), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "stringValue", c_string_to_jsval(cx, v.stringValue), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval spevent_to_jsval(JSContext* cx, spEvent& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "data", speventdata_to_jsval(cx, *v.data), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "intValue", INT_TO_JSVAL(v.intValue), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "floatValue", DOUBLE_TO_JSVAL(v.floatValue), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "stringValue", c_string_to_jsval(cx, v.stringValue), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spbonedata_to_jsval(JSContext* cx, const spBoneData* v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    // root haven't parent
    jsval parentVal = JSVAL_NULL;
    if (strcmp(v->name, "root"))
        parentVal = spbonedata_to_jsval(cx, v->parent);
    
    bool ok = JS_DefineProperty(cx, tmp, "name", c_string_to_jsval(cx, v->name), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "parent", parentVal, NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "length", DOUBLE_TO_JSVAL(v->length), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v->x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v->y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "rotation", DOUBLE_TO_JSVAL(v->rotation), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "scaleX", DOUBLE_TO_JSVAL(v->scaleX), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "scaleY", DOUBLE_TO_JSVAL(v->scaleY), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "inheritScale", INT_TO_JSVAL(v->inheritScale), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "inheritRotation", INT_TO_JSVAL(v->inheritRotation), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spbone_to_jsval(JSContext* cx, spBone& v)
{
    JSObject* tmp =JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    // root haven't parent
    jsval parentVal = JSVAL_NULL;
    if (strcmp(v.data->name, "root"))
        parentVal = spbone_to_jsval(cx, *v.parent);
    
    bool ok = JS_DefineProperty(cx, tmp, "data", spbonedata_to_jsval(cx, v.data), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "parent", parentVal, NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "rotation", DOUBLE_TO_JSVAL(v.rotation), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "scaleX", DOUBLE_TO_JSVAL(v.scaleX), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "scaleY", DOUBLE_TO_JSVAL(v.scaleY), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "m00", DOUBLE_TO_JSVAL(v.m00), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "m01", DOUBLE_TO_JSVAL(v.m01), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "worldX", DOUBLE_TO_JSVAL(v.worldX), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "m10", DOUBLE_TO_JSVAL(v.m10), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "m11", DOUBLE_TO_JSVAL(v.m11), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "worldY", DOUBLE_TO_JSVAL(v.worldY), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "worldRotation", DOUBLE_TO_JSVAL(v.worldRotation), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "worldScaleX", DOUBLE_TO_JSVAL(v.worldScaleX), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "worldScaleY", DOUBLE_TO_JSVAL(v.worldScaleY), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spskeleton_to_jsval(JSContext* cx, spSkeleton& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "flipX", DOUBLE_TO_JSVAL(v.flipX), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "flipY", DOUBLE_TO_JSVAL(v.flipY), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "time", DOUBLE_TO_JSVAL(v.time), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "boneCount", INT_TO_JSVAL(v.bonesCount), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "slotCount", INT_TO_JSVAL(v.slotsCount), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spattachment_to_jsval(JSContext* cx, spAttachment& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "name", c_string_to_jsval(cx, v.name), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "type", INT_TO_JSVAL(v.type), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spslotdata_to_jsval(JSContext* cx, spSlotData& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;

    bool ok = JS_DefineProperty(cx, tmp, "name", c_string_to_jsval(cx, v.name), NULL, NULL,  JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "attachmentName", c_string_to_jsval(cx, v.attachmentName), NULL, NULL,  JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "r", DOUBLE_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", DOUBLE_TO_JSVAL(v.b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "a", DOUBLE_TO_JSVAL(v.a), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "additiveBlending", INT_TO_JSVAL(v.additiveBlending), NULL, NULL,  JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "boneData", spbonedata_to_jsval(cx, v.boneData), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spslot_to_jsval(JSContext* cx, spSlot& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "r", DOUBLE_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
     JS_DefineProperty(cx, tmp, "g", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
     JS_DefineProperty(cx, tmp, "b", DOUBLE_TO_JSVAL(v.b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
     JS_DefineProperty(cx, tmp, "a", DOUBLE_TO_JSVAL(v.a), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
     JS_DefineProperty(cx, tmp, "bone", spbone_to_jsval(cx, *v.bone), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
     //JS_DefineProperty(cx, tmp, "skeleton", spskeleton_to_jsval(cx, *v.skeleton), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
     JS_DefineProperty(cx, tmp, "attachment", spattachment_to_jsval(cx, *v.attachment), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
     JS_DefineProperty(cx, tmp, "data", spslotdata_to_jsval(cx, *v.data), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
        
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval sptimeline_to_jsval(JSContext* cx, spTimeline& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "type", int32_to_jsval(cx, v.type), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spanimationstate_to_jsval(JSContext* cx, spAnimationState& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "timeScale", DOUBLE_TO_JSVAL(v.timeScale), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "trackCount", DOUBLE_TO_JSVAL(v.tracksCount), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spanimation_to_jsval(JSContext* cx, spAnimation& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "duration", DOUBLE_TO_JSVAL(v.duration), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "timelineCount", INT_TO_JSVAL(v.timelinesCount), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "name", c_string_to_jsval(cx, v.name), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "timelines", sptimeline_to_jsval(cx, **v.timelines), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval sptrackentry_to_jsval(JSContext* cx, spTrackEntry& v)
{
    JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    
    jsval nextVal = JSVAL_NULL;
    if (v.next)
        nextVal = sptrackentry_to_jsval(cx, *v.next);
    
    jsval previousVal = JSVAL_NULL;
    if (v.previous)
        previousVal = sptrackentry_to_jsval(cx, *v.previous);
    
    bool ok = JS_DefineProperty(cx, tmp, "delay", DOUBLE_TO_JSVAL(v.delay), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "time", DOUBLE_TO_JSVAL(v.time), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "lastTime", DOUBLE_TO_JSVAL(v.lastTime), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "endTime", DOUBLE_TO_JSVAL(v.endTime), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "timeScale", DOUBLE_TO_JSVAL(v.timeScale), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "mixTime", DOUBLE_TO_JSVAL(v.mixTime), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "mixDuration", DOUBLE_TO_JSVAL(v.mixDuration), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "animation", spanimation_to_jsval(cx, *v.animation), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "next", nextVal, NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "previous", previousVal, NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

bool jsb_cocos2dx_spine_findBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spBone* ret = cobj->findBone(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spbone_to_jsval(cx, *ret);
            }
        } while (0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_findSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spSlot* ret = cobj->findSlot(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spslot_to_jsval(cx, *ret);
            }
        } while (0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_setDebugBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        bool enable = JSVAL_TO_BOOLEAN(argv[0]);
        cobj->setDebugBonesEnabled(enable);
        
        JS_SET_RVAL(cx, vp, JSVAL_NULL);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_setDebugSolots(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        bool enable = JSVAL_TO_BOOLEAN(argv[0]);
        cobj->setDebugSlotsEnabled(enable);
        
        JS_SET_RVAL(cx, vp, JSVAL_NULL);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_getAttachment(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spAttachment* ret = cobj->getAttachment(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spattachment_to_jsval(cx, *ret);
            }
        } while(0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_getCurrent(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spTrackEntry* ret = cobj->getCurrent(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while (0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    else if (argc == 0) {
        spTrackEntry* ret = cobj->getCurrent();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while (0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_setAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 3) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        bool arg2 = JS::ToBoolean(JS::RootedValue(cx, argv[2]));
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->setAnimation(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_addAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 3) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        bool arg2 = JS::ToBoolean(JS::RootedValue(cx, argv[2]));
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->addAnimation(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    } else if (argc == 4) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        bool arg2 = JS::ToBoolean(JS::RootedValue(cx, argv[2]));
        
        double arg3;
        ok &= JS::ToNumber(cx, JS::RootedValue(cx, argv[3]), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->addAnimation(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }    
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}


class JSSkeletonAnimationWrapper: public JSCallbackWrapper
{
public:
    JSSkeletonAnimationWrapper() {}
    virtual ~JSSkeletonAnimationWrapper() {}
    
    void animationCallbackFunc(spine::SkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount) const {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
        js_proxy_t *proxy = js_get_or_create_proxy(cx, node);
        jsval retval;
        if (_jsCallback != JSVAL_VOID)
        {
            jsval nodeVal = OBJECT_TO_JSVAL(proxy->obj);
            jsval trackIndexVal = INT_TO_JSVAL(trackIndex);
            int tmpType = (int)type;
            jsval typeVal = INT_TO_JSVAL(tmpType);
            jsval eventVal = JSVAL_NULL;
            if (event)
                eventVal = spevent_to_jsval(cx, *event);
            jsval loopCountVal = INT_TO_JSVAL(loopCount);
            
            jsval valArr[5];
            valArr[0] = nodeVal;
            valArr[1] = trackIndexVal;
            valArr[2] = typeVal;
            valArr[3] = eventVal;
            valArr[4] = loopCountVal;
            
            JS_AddValueRoot(cx, valArr);
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            JS_CallFunctionValue(cx, thisObj, _jsCallback, 5, valArr, &retval);
            JS_RemoveValueRoot(cx, valArr);
        }
    }
};

static bool jsb_cocos2dx_spine_setAnimationListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    
    spine::SkeletonAnimation* node = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( node, cx, false, "Invalid Native Object");
    if (argc == 2) {
        JSSkeletonAnimationWrapper *tmpCobj = new JSSkeletonAnimationWrapper();
        jsval *argv = JS_ARGV(cx, vp);
        
        tmpCobj->setJSCallbackFunc(argv[1]);
        tmpCobj->setJSCallbackThis(argv[0]);
        
        //node->setAnimationListener(tmpCobj, animationStateEvent_selector(JSSkeletonAnimationWrapper::animationCallbackFunc));
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        
        return true;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return false;
}

extern JSObject* jsb_spine_SkeletonRenderer_prototype;
extern JSObject* jsb_spine_SkeletonAnimation_prototype;

void register_all_cocos2dx_spine_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_spine_SkeletonRenderer_prototype, "findBone", jsb_cocos2dx_spine_findBone, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_spine_SkeletonRenderer_prototype, "findSlot", jsb_cocos2dx_spine_findSlot, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_spine_SkeletonRenderer_prototype, "setDebugBones", jsb_cocos2dx_spine_setDebugBones, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_spine_SkeletonRenderer_prototype, "setDebugSolots", jsb_cocos2dx_spine_setDebugSolots, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_spine_SkeletonRenderer_prototype, "getAttachment", jsb_cocos2dx_spine_getAttachment, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_spine_SkeletonAnimation_prototype, "getCurrent", jsb_cocos2dx_spine_getCurrent, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_spine_SkeletonAnimation_prototype, "setAnimation", jsb_cocos2dx_spine_setAnimation, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_spine_SkeletonAnimation_prototype, "addAnimation", jsb_cocos2dx_spine_addAnimation, 4, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_spine_SkeletonAnimation_prototype, "setAnimationListener", jsb_cocos2dx_spine_setAnimationListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
