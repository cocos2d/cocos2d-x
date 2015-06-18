/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "jsb_cocos2dx_navmesh_auto.hpp"
#if CC_USE_NAVMESH
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "cocos2d.h"
#include "navmesh/CCNavMesh.h"
#include "js_manual_conversions.h"

static bool jsb_cocos2dx_navmesh_NavMeshAgent_move(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "Invalid Native Object");

	bool ok = true;

	if (argc == 1){
		JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
		cocos2d::Vec3 arg0;
		ok &= jsval_to_vector3(cx, args.get(0), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "jsb_cocos2dx_navmesh_NavMeshAgent_move : Error processing arguments");
		cobj->move(arg0);
		return true;
	}

	if (argc == 2){
		JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
		cocos2d::Vec3 arg0;
		ok &= jsval_to_vector3(cx, args.get(0), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "jsb_cocos2dx_navmesh_NavMeshAgent_move : Error processing arguments");

		std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, obj, args.get(1)));

		cobj->move(arg0, [=](cocos2d::NavMeshAgent *agent, float totalTimeAfterMove)->void{
			jsval arg[2];
			js_proxy_t *agentProxy = js_get_or_create_proxy(cx, agent);
			if (proxy)
				arg[0] = OBJECT_TO_JSVAL(agentProxy->obj);
			else
				arg[0] = JSVAL_NULL;
			arg[1] = DOUBLE_TO_JSVAL((double)totalTimeAfterMove);
			JS::RootedValue rval(cx);

			bool invokeOk = func->invoke(2, arg, &rval);
			if (!invokeOk && JS_IsExceptionPending(cx)) {
				JS_ReportPendingException(cx);
			}
		});
		return true;
	}
    
    JS_ReportError(cx, "jsb_cocos2dx_navmesh_NavMeshAgent_move : wrong number of arguments: %d, was expecting %d or %d", argc, 1, 2);
    return false;
}

extern JSObject *jsb_cocos2d_NavMeshAgent_prototype;

void register_all_cocos2dx_navmesh_manual(JSContext *cx, JS::HandleObject global)
{
	JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocos2d_NavMeshAgent_prototype), "move", jsb_cocos2dx_navmesh_NavMeshAgent_move, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
#endif //#if CC_USE_NAVMESH
