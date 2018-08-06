/*
 * Created by ucchen on 2/12/14.
 * Copyright (c) 2014-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#include "scripting/js-bindings/manual/spine/jsb_cocos2dx_spine_manual.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "editor-support/spine/spine-cocos2dx.h"

using namespace spine;

std::unordered_map<spTrackEntry*, JSObject*> _spTrackEntryMap;

jsval speventdata_to_jsval(JSContext* cx, spEventData& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    JS::RootedValue jsname(cx, c_string_to_jsval(cx, v.name));
    JS::RootedValue jsstr(cx, c_string_to_jsval(cx, v.stringValue));
    bool ok = JS_DefineProperty(cx, tmp, "name", jsname, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "intValue", v.intValue, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "floatValue", v.floatValue, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "stringValue", jsstr, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval spevent_to_jsval(JSContext* cx, spEvent& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    JS::RootedValue jsdata(cx, speventdata_to_jsval(cx, *v.data));
    JS::RootedValue jsstr(cx, c_string_to_jsval(cx, v.stringValue));
    bool ok = JS_DefineProperty(cx, tmp, "data", jsdata, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "intValue", v.intValue, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "floatValue", v.floatValue, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "stringValue", jsstr, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spbonedata_to_jsval(JSContext* cx, const spBoneData* v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    // root haven't parent
    JS::RootedValue parentVal(cx);
    if (strcmp(v->name, "root") && v->parent)
        parentVal = spbonedata_to_jsval(cx, v->parent);
    
    JS::RootedValue jsname(cx, c_string_to_jsval(cx, v->name));
    bool ok = JS_DefineProperty(cx, tmp, "index", v->index, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "name", jsname, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "parent", parentVal,JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "length", v->length, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "x", v->x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "y", v->y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "rotation", v->rotation, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "scaleX", v->scaleX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "scaleY", v->scaleY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "shearX", v->shearX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "shearY", v->shearY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "transformMode", v->transformMode, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spbone_to_jsval(JSContext* cx, spBone& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    // root haven't parent
    JS::RootedValue parentVal(cx);
    if (strcmp(v.data->name, "root") && v.parent)
        parentVal = spbone_to_jsval(cx, *v.parent);
    
    JS::RootedValue jsdata(cx, spbonedata_to_jsval(cx, v.data));
    bool ok = JS_DefineProperty(cx, tmp, "data", jsdata, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "parent", parentVal, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "rotation", v.rotation, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "scaleX", v.scaleX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "scaleY", v.scaleY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "shearX", v.shearX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "shearY", v.shearY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "m00", v.a, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "m01", v.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "worldX", v.worldX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "m10", v.c, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "m11", v.d, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "worldY", v.worldY, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    /*
        JS_DefineProperty(cx, tmp, "worldRotation", v.worldRotation, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "worldScaleX", v.worldScaleX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "worldScaleY", v.worldScaleY, JSPROP_ENUMERATE | JSPROP_PERMANENT);
     */

    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spskeleton_to_jsval(JSContext* cx, spSkeleton& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "flipX", v.flipX, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "flipY", v.flipY, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "time", v.time, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "boneCount", v.bonesCount, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "slotCount", v.slotsCount, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spattachment_to_jsval(JSContext* cx, spAttachment& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    JS::RootedValue jsname(cx, c_string_to_jsval(cx, v.name));
    bool ok = JS_DefineProperty(cx, tmp, "name", jsname, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "type", v.type, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spColor_to_jsval(JSContext* cx, const spColor* v)
{
    if (!v)
        return JSVAL_NULL;
        
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "r", v->r, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", v->g, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", v->b, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
        return OBJECT_TO_JSVAL(tmp);
    else
        return JSVAL_NULL;
}

jsval spslotdata_to_jsval(JSContext* cx, spSlotData& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;

    JS::RootedValue jsname(cx, c_string_to_jsval(cx, v.name));
    JS::RootedValue jsattachmentName(cx, c_string_to_jsval(cx, v.attachmentName));
    JS::RootedValue jsboneData(cx, spbonedata_to_jsval(cx, v.boneData));
    JS::RootedValue jscolor(cx, spColor_to_jsval(cx, &v.color));
    JS::RootedValue jsdarkColor(cx, spColor_to_jsval(cx, v.darkColor));
    bool ok = JS_DefineProperty(cx, tmp, "name", jsname, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "attachmentName", jsattachmentName, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "color", jscolor, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "darkColor", jsdarkColor, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "blendMode", v.blendMode, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "boneData", jsboneData, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "index", v.index, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spslot_to_jsval(JSContext* cx, spSlot& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    JS::RootedValue jsbone(cx, spbone_to_jsval(cx, *v.bone));
    JS::RootedValue jsattachment(cx, spattachment_to_jsval(cx, *v.attachment));
    JS::RootedValue jsdata(cx, spslotdata_to_jsval(cx, *v.data));
    JS::RootedValue jscolor(cx, spColor_to_jsval(cx, &v.color));
    JS::RootedValue jsdarkColor(cx, spColor_to_jsval(cx, v.darkColor));
    bool ok = JS_DefineProperty(cx, tmp, "color", jscolor, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "darkColor", jsdarkColor, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "bone", jsbone, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        //JS_DefineProperty(cx, tmp, "skeleton", spskeleton_to_jsval(cx, *v.skeleton), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "attachment", jsattachment, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "data", jsdata, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "attachmentVerticesCapacity", v.attachmentVerticesCapacity, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "attachmentVerticesCount", v.attachmentVerticesCount, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "attachmentVertices", *v.attachmentVertices, JSPROP_ENUMERATE | JSPROP_PERMANENT);
        
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval sptimeline_to_jsval(JSContext* cx, spTimeline& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "type", v.type, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spanimationstate_to_jsval(JSContext* cx, spAnimationState& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    bool ok = JS_DefineProperty(cx, tmp, "timeScale", v.timeScale, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "trackCount", v.tracksCount, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

jsval spanimation_to_jsval(JSContext* cx, spAnimation& v)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;
    
    JS::RootedValue jsname(cx, c_string_to_jsval(cx, v.name));
    JS::RootedValue jstimelines(cx, sptimeline_to_jsval(cx, **v.timelines));
    bool ok = JS_DefineProperty(cx, tmp, "duration", v.duration, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "timelineCount", v.timelinesCount, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "name", jsname, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "timelines", jstimelines, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok)
    {
        return OBJECT_TO_JSVAL(tmp);
    }
    
    return JSVAL_NULL;
}

JSClass  *jsb_spine_TrackEntry_class;
JSObject *jsb_spine_TrackEntry_prototype;

bool jsb_spine_TrackEntry_get_next(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
    spTrackEntry* cobj = (spTrackEntry *)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        JS::RootedValue jsret(cx, JS::NullValue());
        if (cobj->next)
        {
            jsret = sptrackentry_to_jsval(cx, *cobj->next);
        }
        args.rval().set(jsret);
        return true;
    }
    else {
        CCLOGERROR("jsb_spine_TrackEntry_get_next : Invalid Native Object");
        return false;
    }
}

bool jsb_spine_TrackEntry_get_mixingFrom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
    spTrackEntry* cobj = (spTrackEntry *)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        JS::RootedValue jsret(cx, JS::NullValue());
        if (cobj->mixingFrom)
        {
            jsret = sptrackentry_to_jsval(cx, *cobj->mixingFrom);
        }
        args.rval().set(jsret);
        return true;
    }
    else {
        CCLOGERROR("jsb_spine_TrackEntry_get_previous : Invalid Native Object");
        return false;
    }
}

void js_spine_TrackEntry_finalize(JSFreeOp *fop, JSObject *obj) {
    std::unordered_map<spTrackEntry*, JSObject*>::iterator existed = _spTrackEntryMap.begin();
    while (existed != _spTrackEntryMap.end()) {
        if (existed->second == obj)
        {
            _spTrackEntryMap.erase(existed);
            break;
        }
        ++existed;
    }
}

void js_register_spine_TrackEntry(JSContext *cx, JS::HandleObject global)
{
    jsb_spine_TrackEntry_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_spine_TrackEntry_class->name = "TrackEntry";
    jsb_spine_TrackEntry_class->addProperty = JS_PropertyStub;
    jsb_spine_TrackEntry_class->delProperty = JS_DeletePropertyStub;
    jsb_spine_TrackEntry_class->getProperty = JS_PropertyStub;
    jsb_spine_TrackEntry_class->setProperty = JS_StrictPropertyStub;
    jsb_spine_TrackEntry_class->enumerate = JS_EnumerateStub;
    jsb_spine_TrackEntry_class->resolve = JS_ResolveStub;
    jsb_spine_TrackEntry_class->convert = JS_ConvertStub;
    jsb_spine_TrackEntry_class->finalize = js_spine_TrackEntry_finalize;
    jsb_spine_TrackEntry_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] =
    {
        JS_PSG("mixingFrom", jsb_spine_TrackEntry_get_mixingFrom, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PSG("next", jsb_spine_TrackEntry_get_next, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };
    
    jsb_spine_TrackEntry_prototype = JS_InitClass(cx, global, JS::NullPtr(), jsb_spine_TrackEntry_class, nullptr, 0, properties, nullptr, nullptr, nullptr);
}

jsval sptrackentry_to_jsval(JSContext* cx, spTrackEntry& v)
{
    JS::RootedObject entry(cx);
    std::unordered_map<spTrackEntry*, JSObject*>::iterator existed = _spTrackEntryMap.find(&v);
    bool found = existed != _spTrackEntryMap.end();
    if (found)
    {
        entry.set(existed->second);
    }
    else
    {
        JS::RootedObject proto(cx, jsb_spine_TrackEntry_prototype);
        entry.set(JS_NewObject(cx, jsb_spine_TrackEntry_class, proto, JS::NullPtr()));
    }
    
    JS::RootedValue entryVal(cx, OBJECT_TO_JSVAL(entry));
    if (entryVal.isObject())
    {
        JS::RootedValue val(cx, spanimation_to_jsval(cx, *v.animation));
        bool ok = JS_SetProperty(cx, entry, "animation", val);
        val.set(INT_TO_JSVAL(v.trackIndex));
        ok &= JS_SetProperty(cx, entry, "trackIndex", val);
        val.set(INT_TO_JSVAL(v.loop));
        ok &= JS_SetProperty(cx, entry, "loop", val);
        val.set(DOUBLE_TO_JSVAL(v.eventThreshold));
        ok &= JS_SetProperty(cx, entry, "eventThreshold", val);
        val.set(DOUBLE_TO_JSVAL(v.attachmentThreshold));
        ok &= JS_SetProperty(cx, entry, "attachmentThreshold", val);
        val.set(DOUBLE_TO_JSVAL(v.drawOrderThreshold));
        ok &= JS_SetProperty(cx, entry, "drawOrderThreshold", val);
        val.set(DOUBLE_TO_JSVAL(v.animationStart));
        ok &= JS_SetProperty(cx, entry, "animationStart", val);
        val.set(DOUBLE_TO_JSVAL(v.animationEnd));
        ok &= JS_SetProperty(cx, entry, "animationEnd", val);
        val.set(DOUBLE_TO_JSVAL(v.animationLast));
        ok &= JS_SetProperty(cx, entry, "animationLast", val);
        val.set(DOUBLE_TO_JSVAL(v.nextAnimationLast));
        ok &= JS_SetProperty(cx, entry, "nextAnimationLast", val);
        val.set(DOUBLE_TO_JSVAL(v.delay));
        ok &= JS_SetProperty(cx, entry, "delay", val);
        val.set(DOUBLE_TO_JSVAL(v.trackTime));
        ok &= JS_SetProperty(cx, entry, "trackTime", val);
        val.set(DOUBLE_TO_JSVAL(v.trackLast));
        ok &= JS_SetProperty(cx, entry, "trackLast", val);
        val.set(DOUBLE_TO_JSVAL(v.nextTrackLast));
        ok &= JS_SetProperty(cx, entry, "nextTrackLast", val);
        val.set(DOUBLE_TO_JSVAL(v.trackEnd));
        ok &= JS_SetProperty(cx, entry, "trackEnd", val);
        val.set(DOUBLE_TO_JSVAL(v.timeScale));
        ok &= JS_SetProperty(cx, entry, "timeScale", val);
        val.set(DOUBLE_TO_JSVAL(v.alpha));
        ok &= JS_SetProperty(cx, entry, "alpha", val);
        val.set(DOUBLE_TO_JSVAL(v.mixTime));
        ok &= JS_SetProperty(cx, entry, "mixTime", val);
        val.set(DOUBLE_TO_JSVAL(v.mixDuration));
        ok &= JS_SetProperty(cx, entry, "mixDuration", val);
        val.set(DOUBLE_TO_JSVAL(v.interruptAlpha));
        ok &= JS_SetProperty(cx, entry, "interruptAlpha", val);
        val.set(DOUBLE_TO_JSVAL(v.totalAlpha));
        ok &= JS_SetProperty(cx, entry, "totalAlpha", val);
        
        if (v.timelinesRotation)
            val.set(DOUBLE_TO_JSVAL(*v.timelinesRotation));
        else
            val.set(JSVAL_NULL);
        ok &= JS_SetProperty(cx, entry, "timelinesRotation", val);
        
        val.set(INT_TO_JSVAL(v.timelinesRotationCount));
        ok &= JS_SetProperty(cx, entry, "timelinesRotationCount", val);
        
        if (ok)
        {
            if (!found)
            {
                _spTrackEntryMap.emplace(&v, entry);
            }
            return entryVal;
        }
    }
    
    return JSVAL_NULL;
}

bool jsb_cocos2dx_spine_findBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spBone* ret = cobj->findBone(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spbone_to_jsval(cx, *ret);
            }
        } while (0);
        
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_findSlot(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spSlot* ret = cobj->findSlot(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spslot_to_jsval(cx, *ret);
            }
        } while (0);
        
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_setDebugBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        bool enable = args.get(0).toBoolean();
        cobj->setDebugBonesEnabled(enable);
        
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_setDebugSolots(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        bool enable = args.get(0).toBoolean();
        cobj->setDebugSlotsEnabled(enable);
        
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_getAttachment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SkeletonRenderer* cobj = (SkeletonRenderer*)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spAttachment* ret = cobj->getAttachment(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = spattachment_to_jsval(cx, *ret);
            }
        } while(0);
        
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_getCurrent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        spTrackEntry* ret = cobj->getCurrent(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while (0);
        
        args.rval().set(jsret);
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
        
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_setAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 3) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        bool arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->setAnimation(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        args.rval().set(jsret);
        return true;
    }
    
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool jsb_cocos2dx_spine_addAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 3) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        bool arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->addAnimation(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        args.rval().set(jsret);
        return true;
    } else if (argc == 4) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        
        const char* arg1;
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        bool arg2 = JS::ToBoolean(args.get(2));
        
        double arg3;
        ok &= JS::ToNumber(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        spTrackEntry* ret = cobj->addAnimation(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        
        do {
            if (ret)
            {
                jsret = sptrackentry_to_jsval(cx, *ret);
            }
        } while(0);
        
        args.rval().set(jsret);
        return true;
    }    
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}


extern JSObject* jsb_spine_SkeletonRenderer_prototype;
extern JSObject* jsb_spine_SkeletonAnimation_prototype;

void register_all_cocos2dx_spine_manual(JSContext* cx, JS::HandleObject global)
{
    js_register_spine_TrackEntry(cx, global);
    
    JS::RootedObject skeletonRenderer(cx, jsb_spine_SkeletonRenderer_prototype);
    JS_DefineFunction(cx, skeletonRenderer, "findBone", jsb_cocos2dx_spine_findBone, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, skeletonRenderer, "findSlot", jsb_cocos2dx_spine_findSlot, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, skeletonRenderer, "setDebugBones", jsb_cocos2dx_spine_setDebugBones, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, skeletonRenderer, "setDebugSolots", jsb_cocos2dx_spine_setDebugSolots, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, skeletonRenderer, "getAttachment", jsb_cocos2dx_spine_getAttachment, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS::RootedObject skeletonAnimation(cx, jsb_spine_SkeletonAnimation_prototype);
    JS_DefineFunction(cx, skeletonAnimation, "getCurrent", jsb_cocos2dx_spine_getCurrent, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, skeletonAnimation, "setAnimation", jsb_cocos2dx_spine_setAnimation, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, skeletonAnimation, "addAnimation", jsb_cocos2dx_spine_addAnimation, 4, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
