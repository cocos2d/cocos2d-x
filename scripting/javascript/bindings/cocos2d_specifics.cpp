#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocos2d_specifics.hpp"
#include <typeinfo>
#include "js_bindings_config.h"
#include "generated/jsb_cocos2dx_auto.hpp"

USING_NS_CC_EXT;

schedFunc_proxy_t *_schedFunc_target_ht = NULL;
schedTarget_proxy_t *_schedObj_target_ht = NULL;
callfuncTarget_proxy_t *_callfuncTarget_native_ht = NULL;

JSTouchDelegate::TouchDelegateMap JSTouchDelegate::sTouchDelegateMap;

void JSTouchDelegate::setDelegateForJSObject(JSObject* pJSObj, JSTouchDelegate* pDelegate)
{
    CCASSERT(sTouchDelegateMap.find(pJSObj) == sTouchDelegateMap.end(), "");
    sTouchDelegateMap.insert(TouchDelegatePair(pJSObj, pDelegate));
}

JSTouchDelegate* JSTouchDelegate::getDelegateForJSObject(JSObject* pJSObj)
{
    JSTouchDelegate* pRet = NULL;
    TouchDelegateMap::iterator iter = sTouchDelegateMap.find(pJSObj);
    if (iter != sTouchDelegateMap.end())
    {
        pRet = iter->second;
    }
    return pRet;
}

void JSTouchDelegate::removeDelegateForJSObject(JSObject* pJSObj)
{
    TouchDelegateMap::iterator iter = sTouchDelegateMap.find(pJSObj);
    CCASSERT(iter != sTouchDelegateMap.end(), "");
    sTouchDelegateMap.erase(pJSObj);
}

void JSTouchDelegate::setJSObject(JSObject *obj) {
    _mObj = obj;
}

void JSTouchDelegate::registerStandardDelegate() {
    Director* pDirector = Director::getInstance();
    pDirector->getTouchDispatcher()->addStandardDelegate(this,0);
}

void JSTouchDelegate::registerTargettedDelegate(int priority, bool swallowsTouches) {
    Director* pDirector = Director::getInstance();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this,
                                                         priority,
                                                         swallowsTouches);

}

void JSTouchDelegate::unregisterTouchDelegate()
{
    Director* pDirector = Director::getInstance();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}

bool JSTouchDelegate::ccTouchBegan(Touch *pTouch, Event *pEvent) {
    CC_UNUSED_PARAM(pEvent); 
    jsval retval;
    bool bRet = false;

    js_proxy_t* p = jsb_get_js_proxy(_mObj);
    CCASSERT(p, "js object has been unrooted.");

    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHBEGAN, 
        pTouch, _mObj, retval);
    if(JSVAL_IS_BOOLEAN(retval)) {
        bRet = JSVAL_TO_BOOLEAN(retval);
    } 

    return bRet;
};
// optional

void JSTouchDelegate::ccTouchMoved(Touch *pTouch, Event *pEvent) {
    CC_UNUSED_PARAM(pEvent);

    //jsval retval;
    js_proxy_t* p = jsb_get_js_proxy(_mObj);
    CCASSERT(p, "js object has been unrooted.");

    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHMOVED, 
        pTouch, _mObj);
}

void JSTouchDelegate::ccTouchEnded(Touch *pTouch, Event *pEvent) {
    CC_UNUSED_PARAM(pEvent);

    js_proxy_t* p = jsb_get_js_proxy(_mObj);
    CCASSERT(p, "js object has been unrooted.");

    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHENDED, 
        pTouch, _mObj);
}

void JSTouchDelegate::ccTouchCancelled(Touch *pTouch, Event *pEvent) {
    CC_UNUSED_PARAM(pEvent);
    js_proxy_t* p = jsb_get_js_proxy(_mObj);
    CCASSERT(p, "js object has been unrooted.");

    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHCANCELLED, 
        pTouch, _mObj);
}

// optional
void JSTouchDelegate::ccTouchesBegan(Set *pTouches, Event *pEvent) {
    CC_UNUSED_PARAM(pEvent);
    ScriptingCore::getInstance()->executeCustomTouchesEvent(CCTOUCHBEGAN, 
        pTouches, _mObj);
}

void JSTouchDelegate::ccTouchesMoved(Set *pTouches, Event *pEvent) {
    CC_UNUSED_PARAM(pEvent);
    ScriptingCore::getInstance()->executeCustomTouchesEvent(CCTOUCHMOVED, 
        pTouches, _mObj);        
}
void JSTouchDelegate::ccTouchesEnded(Set *pTouches, Event *pEvent) {
    CC_UNUSED_PARAM(pEvent);
    ScriptingCore::getInstance()->executeCustomTouchesEvent(CCTOUCHENDED, 
        pTouches, _mObj);
}
void JSTouchDelegate::ccTouchesCancelled(Set *pTouches, Event *pEvent) {
    CC_UNUSED_PARAM(pEvent);
    ScriptingCore::getInstance()->executeCustomTouchesEvent(CCTOUCHCANCELLED, 
        pTouches, _mObj);
}

static void addCallBackAndThis(JSObject *obj, jsval callback, jsval &thisObj) {
    if(callback != JSVAL_VOID) {
        ScriptingCore::getInstance()->setReservedSpot(0, obj, callback);
    }
    if(thisObj != JSVAL_VOID) {
        ScriptingCore::getInstance()->setReservedSpot(1, obj, thisObj);
    }
}

template<class T>
JSObject* bind_menu_item(JSContext *cx, T* nativeObj, jsval callback, jsval thisObj) {    
	js_proxy_t *p = jsb_get_native_proxy(nativeObj);
	if (p) {
		addCallBackAndThis(p->obj, callback, thisObj);
		return p->obj;
	} else {
		js_type_class_t *classType = js_get_type_from_native<T>(nativeObj);
		assert(classType);
		JSObject *tmp = JS_NewObject(cx, classType->jsclass, classType->proto, classType->parentProto);

		// bind nativeObj <-> JSObject
		js_proxy_t *proxy = jsb_new_proxy(nativeObj, tmp);
		JS_AddNamedObjectRoot(cx, &proxy->obj, typeid(*nativeObj).name());        
		addCallBackAndThis(tmp, callback, thisObj);

		return tmp;
	}
}

JSBool js_cocos2dx_CCMenu_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	if (argc > 0) {
		cocos2d::Array* array = cocos2d::Array::create();
		uint32_t i = 0;
		while (i < argc) {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
			proxy = jsb_get_js_proxy(tmpObj);
			cocos2d::Object *item = (cocos2d::Object*)(proxy ? proxy->ptr : NULL);
			TEST_NATIVE_OBJECT(cx, item)
			array->addObject(item);
			i++;
		}
		cocos2d::Menu* ret = cocos2d::Menu::createWithArray(array);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *p = jsb_get_native_proxy(ret);
				if (p) {
					jsret = OBJECT_TO_JSVAL(p->obj);
				} else {
					// create a new js obj of that class
					js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Menu>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				}
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 0) {
		cocos2d::Menu* ret = cocos2d::Menu::create();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *p = jsb_get_native_proxy(ret);
				if (p) {
					jsret = OBJECT_TO_JSVAL(p->obj);
				} else {
					// create a new js obj of that class
					js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Menu>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				}
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_CCSequence_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	if (argc > 0) {
		cocos2d::Array* array = cocos2d::Array::create();
		uint32_t i = 0;
		while (i < argc) {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
			proxy = jsb_get_js_proxy(tmpObj);
			cocos2d::Object *item = (cocos2d::Object*)(proxy ? proxy->ptr : NULL);
			TEST_NATIVE_OBJECT(cx, item)
			array->addObject(item);
			i++;
		}
		cocos2d::FiniteTimeAction* ret = cocos2d::Sequence::create(array);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *p = jsb_get_native_proxy(ret);
				if (p) {
					jsret = OBJECT_TO_JSVAL(p->obj);
				} else {
					// create a new js obj of that class
					js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::FiniteTimeAction>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				}
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_CCSpawn_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	if (argc > 0) {
		cocos2d::Array* array = cocos2d::Array::create();
		uint32_t i = 0;
		while (i < argc) {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
			proxy = jsb_get_js_proxy(tmpObj);
			cocos2d::Object *item = (cocos2d::Object*)(proxy ? proxy->ptr : NULL);
			TEST_NATIVE_OBJECT(cx, item)
			array->addObject(item);
			i++;
		}
		cocos2d::FiniteTimeAction* ret = cocos2d::Spawn::create(array);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *p = jsb_get_native_proxy(ret);
				if (p) {
					jsret = OBJECT_TO_JSVAL(p->obj);
				} else {
					// create a new js obj of that class
					js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::FiniteTimeAction>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				}
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_CCMenuItem_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc >= 1) {
		jsval *argv = JS_ARGV(cx, vp);
		cocos2d::MenuItem* ret = cocos2d::MenuItem::create();
		JSObject *obj = bind_menu_item<cocos2d::MenuItem>(cx, ret, argv[0], argc == 2? argv[1] : JSVAL_VOID);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

// "create" in JS
// cc.MenuItemSprite.create( normalSprite, selectedSprite, [disabledSprite], [callback_fn], [this]
JSBool js_cocos2dx_CCMenuItemSprite_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc >= 2 && argc <= 5) {
		jsval *argv = JS_ARGV(cx, vp);
		js_proxy_t *proxy;
		JSObject *tmpObj;
		
		tmpObj = JSVAL_TO_OBJECT(argv[0]);
		proxy = jsb_get_js_proxy(tmpObj);
		cocos2d::Node* arg0 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
		TEST_NATIVE_OBJECT(cx, arg0);

		tmpObj = JSVAL_TO_OBJECT(argv[1]);
		proxy = jsb_get_js_proxy(tmpObj);
		cocos2d::Node* arg1 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
		TEST_NATIVE_OBJECT(cx, arg1);

        int last = 2;
		JSBool thirdArgIsCallback = JS_FALSE;

		jsval jsCallback = JSVAL_VOID;
		jsval jsThis = JSVAL_VOID;

		cocos2d::Node* arg2 = NULL;
		if (argc >= 3) {
			tmpObj = JSVAL_TO_OBJECT(argv[2]);
			thirdArgIsCallback = JS_ObjectIsFunction(cx, tmpObj);
			if (!thirdArgIsCallback) { 
				proxy = jsb_get_js_proxy(tmpObj);
				arg2 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
				TEST_NATIVE_OBJECT(cx, arg2);
				last = 3;
			}
		}
		cocos2d::MenuItemSprite* ret = cocos2d::MenuItemSprite::create(arg0, arg1, arg2);
		if (argc >= 3) { 
			if (thirdArgIsCallback) {
				//cc.MenuItemSprite.create( normalSprite, selectedSprite, callback_fn, [this] )
				jsCallback = argv[last++];
				if (argc == 4) {
					jsThis = argv[last];
				}
			}
			else { 
				//cc.MenuItemSprite.create( normalSprite, selectedSprite, disabledSprite, callback_fn, [this] )
				if (argc >= 4) {
					jsCallback = argv[last++];
					if (argc == 5) {
						jsThis = argv[last];
					}
				}
			}
		}

		JSObject *obj = bind_menu_item<cocos2d::MenuItemSprite>(cx, ret, jsCallback, jsThis);

		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
    JS_ReportError(cx, "Invalid number of arguments. Expecting: 2 <= args <= 5");
	return JS_FALSE;
}

// "create" in JS
// cc.MenuItemImage.create( normalImage, selectedImage, [disabledImage], callback_fn, [this] 
JSBool js_cocos2dx_CCMenuItemImage_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc >= 2 && argc <= 5) {
		jsval *argv = JS_ARGV(cx, vp);
		JSStringWrapper arg0(argv[0]);
		JSStringWrapper arg1(argv[1]);
		JSStringWrapper arg2;

		bool thirdArgIsString = true;

		jsval jsCallback = JSVAL_VOID;
		jsval jsThis = JSVAL_VOID;

		int last = 2;
		if (argc >= 3) {
			thirdArgIsString = argv[2].isString();
			if (thirdArgIsString) {
				arg2.set(argv[2], cx);
				last = 3;
			}
		}
		cocos2d::MenuItemImage* ret = cocos2d::MenuItemImage::create((char*)arg0, (char*)arg1, (char*)arg2);

		if (argc >= 3) { 
			if (!thirdArgIsString) {
				//cc.MenuItemImage.create( normalImage, selectedImage, callback_fn, [this] )
				jsCallback = argv[last++];
				if (argc == 4) {
					jsThis = argv[last];
				}
			}
			else { 
				//cc.MenuItemImage.create( normalImage, selectedImage, disabledImage, callback_fn, [this] )
				if (argc >= 4) {
					jsCallback = argv[last++];
					if (argc == 5) {
						jsThis = argv[last];
					}
				}
			}
		}

        JSObject *obj = bind_menu_item<cocos2d::MenuItemImage>(cx, ret, jsCallback, jsThis);

		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
    JS_ReportError(cx, "Invalid number of arguments. Expecting: 2 <= args <= 5");
	return JS_FALSE;
}

// "create" in JS:
// cc.MenuItemLabel.create( label, callback_fn, [this] );
JSBool js_cocos2dx_CCMenuItemLabel_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc >= 1 && argc <= 3) {
		jsval *argv = JS_ARGV(cx, vp);
		js_proxy_t *proxy;
		JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
		proxy = jsb_get_js_proxy(tmpObj);
		cocos2d::Node* arg0 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
		TEST_NATIVE_OBJECT(cx, arg0)
		cocos2d::MenuItemLabel* ret = cocos2d::MenuItemLabel::create(arg0);
		JSObject *obj = bind_menu_item<cocos2d::MenuItemLabel>(cx, ret, (argc >= 2 ? argv[1] : JSVAL_VOID), (argc == 3 ? argv[2] : JSVAL_VOID) );
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d or %d or %d", argc, 1, 2, 3);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCMenuItemAtlasFont_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc >= 5) {
        JSBool ok = JS_TRUE;
		jsval *argv = JS_ARGV(cx, vp);
		JSStringWrapper arg0(argv[0]);
		JSStringWrapper arg1(argv[1]);
		int arg2; ok &= jsval_to_int32(cx, argv[2], &arg2);
		int arg3; ok &= jsval_to_int32(cx, argv[3], &arg3);
		int arg4; ok &= jsval_to_int32(cx, argv[4], &arg4);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::MenuItemAtlasFont* ret = cocos2d::MenuItemAtlasFont::create(arg0, arg1, arg2, arg3, arg4);
		JSObject *obj = bind_menu_item<cocos2d::MenuItemAtlasFont>(cx, ret, (argc >= 6 ? argv[5] : JSVAL_VOID), (argc == 7 ? argv[6] : JSVAL_VOID));
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

// "create" in JS
// cc.MenuItemFont.create( string, callback_fn, [this] );
JSBool js_cocos2dx_CCMenuItemFont_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc >= 1 && argc <= 3) {
		jsval *argv = JS_ARGV(cx, vp);
		JSStringWrapper arg0(argv[0]);
		cocos2d::MenuItemFont* ret = cocos2d::MenuItemFont::create(arg0);
		JSObject *obj = bind_menu_item<cocos2d::MenuItemFont>(cx, ret, (argc >= 2 ? argv[1] : JSVAL_VOID), (argc == 3 ? argv[2] : JSVAL_VOID));
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d or %d or %d", argc, 1, 2, 3);
	return JS_FALSE;
}


JSBool js_cocos2dx_CCMenuItemToggle_create(JSContext *cx, uint32_t argc, jsval *vp)
{
  if (argc >= 1) {
    jsval *argv = JS_ARGV(cx, vp);
    cocos2d::MenuItemToggle* ret = cocos2d::MenuItemToggle::create();

    for (uint32_t i=0; i < argc; i++) {
      js_proxy_t *proxy;
      JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
      proxy = jsb_get_js_proxy(tmpObj);
      cocos2d::MenuItem* item = (cocos2d::MenuItem*)(proxy ? proxy->ptr : NULL);
      TEST_NATIVE_OBJECT(cx, item)
	if(i == 0) ret->initWithItem(item);
	else ret->addSubItem(item);
    }
        
    jsval jsret;
    if (ret) {
      js_proxy_t *proxy = jsb_get_native_proxy(ret);
      if (proxy) {
	jsret = OBJECT_TO_JSVAL(proxy->obj);
      } else {
	// create a new js obj of that class
	proxy = js_get_or_create_proxy<cocos2d::MenuItemToggle>(cx, ret);
	jsret = OBJECT_TO_JSVAL(proxy->obj);
      }
    } else {
      jsret = JSVAL_NULL;
    }
        
    JS_SET_RVAL(cx, vp, jsret);
    return JS_TRUE;
  }
  JS_ReportError(cx, "wrong number of arguments");
  return JS_FALSE;
}

// "setCallback" in JS
// item.setCallback( callback_fn, [this]);
template<class T>
JSBool js_cocos2dx_setCallback(JSContext *cx, uint32_t argc, jsval *vp) {

    if(argc == 1 || argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        jsval jsThis = JSVAL_VOID;
        jsval jsFunc = argv[0];
        if (argc == 2) {
            jsThis = argv[1];
        }
        
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        T* item = (T*)(proxy ? proxy->ptr : NULL);
        TEST_NATIVE_OBJECT(cx, item)
        bind_menu_item(cx, item, jsFunc, jsThis);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d or %d", argc, 1, 2);
    return JS_FALSE;
}

JSBool js_cocos2dx_CCMenuItem_setCallback(JSContext *cx, uint32_t argc, jsval *vp) {
    return js_cocos2dx_setCallback<cocos2d::MenuItem>(cx, argc, vp);
}


JSBool js_cocos2dx_CCAnimation_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
	jsval *argv = JS_ARGV(cx, vp);
	if (argc <= 3) {
		cocos2d::Array* arg0;
		if (argc > 0) {
			ok &= jsval_to_ccarray(cx, argv[0], &arg0);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		}
		cocos2d::Animation* ret = nullptr;
		double arg1 = 0.0f;
		if (argc == 2) {
            ok &= JS_ValueToNumber(cx, argv[1], &arg1);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
			ret = cocos2d::Animation::createWithSpriteFrames(arg0, arg1);
		} else if (argc == 3) {
			unsigned int loops;
			ok &= JS_ValueToNumber(cx, argv[1], &arg1);
			ok &= jsval_to_uint32(cx, argv[2], &loops);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
			ret = cocos2d::Animation::create(arg0, arg1, loops);
		} else if (argc == 1) {
			ret = cocos2d::Animation::createWithSpriteFrames(arg0);
		} else if (argc == 0) {
            ret = cocos2d::Animation::create();
        }
		jsval jsret;
		if (ret) {
			js_proxy_t *proxy = jsb_get_native_proxy(ret);
			if (proxy) {
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				// create a new js obj of that class
				proxy = js_get_or_create_proxy<cocos2d::Animation>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			}
		} else {
			jsret = JSVAL_NULL;
		}
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_CCLayerMultiplex_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	cocos2d::Array* arg0;
    JSBool ok = JS_TRUE;
	ok &= jsvals_variadic_to_ccarray(cx, argv, argc, &arg0);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    
	cocos2d::LayerMultiplex* ret = cocos2d::LayerMultiplex::createWithArray(arg0);
	jsval jsret;
	do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::LayerMultiplex>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
	JS_SET_RVAL(cx, vp, jsret);
	return JS_TRUE;
}

JSBool js_cocos2dx_JSTouchDelegate_registerStandardDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc >= 1) {
		jsval *argv = JS_ARGV(cx, vp);
        JSObject* jsobj = NULL;

        JSTouchDelegate *touch = new JSTouchDelegate();
        touch->autorelease();
        touch->registerStandardDelegate();
        jsobj = (argc == 1 ? JSVAL_TO_OBJECT(argv[0]) : JSVAL_TO_OBJECT(JSVAL_VOID));
        touch->setJSObject(jsobj);
        JSTouchDelegate::setDelegateForJSObject(jsobj, touch);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting >= 1", argc);
	return JS_FALSE;
}

JSBool js_cocos2dx_JSTouchDelegate_registerTargettedDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc >= 1) {
		jsval *argv = JS_ARGV(cx, vp);
        JSObject* jsobj = NULL;

        JSTouchDelegate *touch = new JSTouchDelegate();
        touch->autorelease();
        touch->registerTargettedDelegate((argc >= 1 ? JSVAL_TO_INT(argv[0]) : 0), (argc >= 2 ? JSVAL_TO_BOOLEAN(argv[1]) : true));
        
        jsobj = (argc == 3 ? JSVAL_TO_OBJECT(argv[2]) : JSVAL_TO_OBJECT(JSVAL_VOID));
        touch->setJSObject(jsobj);
        JSTouchDelegate::setDelegateForJSObject(jsobj, touch);

		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting >=1", argc);
	return JS_FALSE;
}

JSBool js_cocos2dx_JSTouchDelegate_unregisterTouchDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        jsval *argv = JS_ARGV(cx, vp);
        JSObject* jsobj = JSVAL_TO_OBJECT(argv[0]);
        JSTouchDelegate* pDelegate = JSTouchDelegate::getDelegateForJSObject(jsobj);
        if (pDelegate)
        {
            pDelegate->unregisterTouchDelegate();
            JSTouchDelegate::removeDelegateForJSObject(jsobj);
        }
        
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

JSBool js_cocos2dx_swap_native_object(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 2) {
		// get the native object from the second object to the first object
		jsval *argv = JS_ARGV(cx, vp);
		JSObject *one = JSVAL_TO_OBJECT(argv[0]);
		JSObject *two = JSVAL_TO_OBJECT(argv[1]);
		js_proxy_t *jsproxy = jsb_get_js_proxy(two);
		void *ptrTwo = (jsproxy ? jsproxy->ptr : NULL);
		if (jsproxy) {
			js_proxy_t *nproxy = jsb_get_native_proxy(ptrTwo);
			if (nproxy) {
                JS_RemoveObjectRoot(cx, &jsproxy->obj);
				jsb_remove_proxy(nproxy, jsproxy);
                jsproxy = jsb_new_proxy(ptrTwo, one);
                JS_AddNamedObjectRoot(cx, &jsproxy->obj, typeid(*((Object*)jsproxy->ptr)).name());
			}
		}
	}
	return JS_TRUE;
}

template <class T>
JSBool js_cocos2dx_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy = jsb_get_js_proxy(obj);
		T *clonable = (T *)(proxy ? proxy->ptr : NULL);
		TEST_NATIVE_OBJECT(cx, clonable)
		cocos2d::Object *ret = clonable->clone();
        proxy = js_get_or_create_proxy<cocos2d::Object>(cx, ret);
		if (ret && proxy) {
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(proxy->obj));
			return JS_TRUE;
		}
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSObject* getObjectFromNamespace(JSContext* cx, JSObject *ns, const char *name) {
	jsval out;
    JSBool ok = JS_TRUE;
	if (JS_GetProperty(cx, ns, name, &out) == JS_TRUE) {
		JSObject *obj;
		ok &= JS_ValueToObject(cx, out, &obj);
        JSB_PRECONDITION2(ok, cx, NULL, "Error processing arguments");
	}
	return NULL;
}

jsval anonEvaluate(JSContext *cx, JSObject *thisObj, const char* string) {
	jsval out;
	if (JS_EvaluateScript(cx, thisObj, string, strlen(string), "(string)", 1, &out) == JS_TRUE) {
		return out;
	}
	return JSVAL_VOID;
}

JSBool js_platform(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSString *str = JS_NewStringCopyZ(cx, "mobile");
	jsval out = STRING_TO_JSVAL(str);
	JS_SET_RVAL(cx, vp, out);
	return JS_TRUE;
}

JSCallbackWrapper::JSCallbackWrapper()
: _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID), _extraData(JSVAL_VOID)
{

}

JSCallbackWrapper::~JSCallbackWrapper()
{
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS_RemoveValueRoot(cx, &_jsCallback);
}

void JSCallbackWrapper::setJSCallbackFunc(jsval func) {
    _jsCallback = func;
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
	// Root the callback function.
    JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
}

void JSCallbackWrapper::setJSCallbackThis(jsval thisObj) {
    _jsThisObj = thisObj;
}

void JSCallbackWrapper::setJSExtraData(jsval data) {
    _extraData = data;
}

const jsval& JSCallbackWrapper::getJSCallbackFunc() const
{
    return _jsCallback;
}

const jsval& JSCallbackWrapper::getJSCallbackThis() const
{
    return _jsThisObj;
}

const jsval& JSCallbackWrapper::getJSExtraData() const
{
    return _extraData;
}

void JSCallFuncWrapper::setTargetForNativeNode(Node *pNode, JSCallFuncWrapper *target) {
    callfuncTarget_proxy_t *t;
    HASH_FIND_PTR(_callfuncTarget_native_ht, &pNode, t);
    
    Array *arr;
    if(!t) {
        arr = new Array();
    } else {
        arr = t->obj;
    }
    
    arr->addObject(target);
    
    callfuncTarget_proxy_t *p = (callfuncTarget_proxy_t *)malloc(sizeof(callfuncTarget_proxy_t));
    assert(p);
    p->ptr = (void *)pNode;
    p->obj = arr;
    HASH_ADD_PTR(_callfuncTarget_native_ht, ptr, p);
}

Array * JSCallFuncWrapper::getTargetForNativeNode(Node *pNode) {
    
    callfuncTarget_proxy_t *t;
    HASH_FIND_PTR(_callfuncTarget_native_ht, &pNode, t);
    if(!t) {
        return NULL;
    }
    return t->obj;
    
}

void JSCallFuncWrapper::callbackFunc(Node *node) {
    bool hasExtraData = !JSVAL_IS_VOID(_extraData);
    JSObject* thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Node>(cx, node);

    jsval retval;
    if(_jsCallback != JSVAL_VOID)
    {
        if (hasExtraData)
        {
            jsval valArr[2];
            valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
            valArr[1] = _extraData;

            JS_AddValueRoot(cx, valArr);
            JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
            JS_RemoveValueRoot(cx, valArr);
        }
        else
        {
            jsval senderVal = OBJECT_TO_JSVAL(proxy->obj);
            JS_AddValueRoot(cx, &senderVal);
            JS_CallFunctionValue(cx, thisObj, _jsCallback, 1, &senderVal, &retval);
            JS_RemoveValueRoot(cx, &senderVal);
        }
    }

    // I think the JSCallFuncWrapper isn't needed.
    // Since an action will be run by a cc.Node, it will be released at the Node::cleanup.
    // By James Chen
    // JSCallFuncWrapper::setTargetForNativeNode(node, (JSCallFuncWrapper *)this);
}

// cc.CallFunc.create( func, this, [data])
// cc.CallFunc.create( func )
static JSBool js_callFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    if (argc >= 1 && argc <= 3) {        
		jsval *argv = JS_ARGV(cx, vp);

        JSCallFuncWrapper *tmpCobj = new JSCallFuncWrapper();        
        tmpCobj->autorelease();
        
        tmpCobj->setJSCallbackFunc(argv[0]);
        if(argc >= 2) {
            tmpCobj->setJSCallbackThis(argv[1]);
        } if(argc == 3) {
            tmpCobj->setJSExtraData(argv[2]);
        }
        
        CallFuncN *ret = CallFuncN::create(tmpCobj, callfuncN_selector(JSCallFuncWrapper::callbackFunc));
        
		js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CallFunc>(cx, ret);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(proxy->obj));
        
        JS_SetReservedSlot(proxy->obj, 0, argv[0]);
        if(argc > 1) {
            JS_SetReservedSlot(proxy->obj, 1, argv[1]);
        }
//        if(argc == 3) {
//            JS_SetReservedSlot(proxy->obj, 2, argv[2]);
//        }
        
      //  test->execute();
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

JSScheduleWrapper::~JSScheduleWrapper()
{
    if (_pPureJSTarget) {
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_RemoveObjectRoot(cx, &_pPureJSTarget);
    }
}

void JSScheduleWrapper::setTargetForSchedule(jsval sched, JSScheduleWrapper *target) {
    do {
        JSObject* jsfunc = JSVAL_TO_OBJECT(sched);
        Array* targetArray = getTargetForSchedule(sched);
        if (NULL == targetArray) {
            targetArray = new Array();
            schedFunc_proxy_t *p = (schedFunc_proxy_t *)malloc(sizeof(schedFunc_proxy_t));
            assert(p);
            p->jsfuncObj = jsfunc;
            p->targets = targetArray;
            HASH_ADD_PTR(_schedFunc_target_ht, jsfuncObj, p);
        }

        CCASSERT(!targetArray->containsObject(target), "The target was already added.");

        targetArray->addObject(target);
    } while(0);
}

Array * JSScheduleWrapper::getTargetForSchedule(jsval sched) {
    schedFunc_proxy_t *t = NULL;
    JSObject *o = JSVAL_TO_OBJECT(sched);
    HASH_FIND_PTR(_schedFunc_target_ht, &o, t);
    return t != NULL ? t->targets : NULL;
}


void JSScheduleWrapper::setTargetForJSObject(JSObject* jsTargetObj, JSScheduleWrapper *target)
{
    Array* targetArray = getTargetForJSObject(jsTargetObj);
    if (NULL == targetArray) {
        targetArray = new Array();
        schedTarget_proxy_t *p = (schedTarget_proxy_t *)malloc(sizeof(schedTarget_proxy_t));
        assert(p);
        p->jsTargetObj = jsTargetObj;
        p->targets = targetArray;
        HASH_ADD_PTR(_schedObj_target_ht, jsTargetObj, p);
    }
    
    CCASSERT(!targetArray->containsObject(target), "The target was already added.");
    targetArray->addObject(target);
}

Array * JSScheduleWrapper::getTargetForJSObject(JSObject* jsTargetObj)
{
    schedTarget_proxy_t *t = NULL;
    HASH_FIND_PTR(_schedObj_target_ht, &jsTargetObj, t);
    return t != NULL ? t->targets : NULL;
}

void JSScheduleWrapper::removeAllTargets()
{
    CCLOGINFO("removeAllTargets begin");
    dump();
    
    {
        schedFunc_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
            current->targets->removeAllObjects();
            current->targets->release();
            HASH_DEL(_schedFunc_target_ht, current);
            free(current);
        }
    }
    
    {
        schedTarget_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedObj_target_ht, current, tmp) {
            current->targets->removeAllObjects();
            current->targets->release();
            HASH_DEL(_schedObj_target_ht, current);
            free(current);
        }
    }
    
    dump();
    CCLOGINFO("removeAllTargets end");
}

void JSScheduleWrapper::removeAllTargetsForMinPriority(int minPriority)
{
    CCLOGINFO("removeAllTargetsForPriority begin");
    dump();
    
    {
        schedFunc_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
            std::vector<Object*> objectsNeedToBeReleased;
            Array* targets = current->targets;
            Object* pObj = NULL;
            CCARRAY_FOREACH(targets, pObj)
            {
                JSScheduleWrapper* wrapper = static_cast<JSScheduleWrapper*>(pObj);
                bool isUpdateSchedule = wrapper->isUpdateSchedule();
                if (!isUpdateSchedule || (isUpdateSchedule && wrapper->getPriority() >= minPriority))
                {
                    objectsNeedToBeReleased.push_back(pObj);
                }
            }
            
            std::vector<Object*>::iterator iter = objectsNeedToBeReleased.begin();
            for (; iter != objectsNeedToBeReleased.end(); ++iter)
            {
                targets->removeObject(*iter, true);
            }
            
            if (targets->count() == 0)
            {
                HASH_DEL(_schedFunc_target_ht, current);
                targets->release();
                free(current);
            }
        }
    }
    
    {
        schedTarget_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedObj_target_ht, current, tmp) {
            std::vector<Object*> objectsNeedToBeReleased;
            Array* targets = current->targets;
            Object* pObj = NULL;
            CCARRAY_FOREACH(targets, pObj)
            {
                JSScheduleWrapper* wrapper = static_cast<JSScheduleWrapper*>(pObj);
                bool isUpdateSchedule = wrapper->isUpdateSchedule();
                if (!isUpdateSchedule || (isUpdateSchedule && wrapper->getPriority() >= minPriority))
                {
                    CCLOG("isUpdateSchedule2:%d", isUpdateSchedule);
                    objectsNeedToBeReleased.push_back(pObj);
                }
            }
            
            auto iter = objectsNeedToBeReleased.begin();
            for (; iter != objectsNeedToBeReleased.end(); ++iter)
            {
                targets->removeObject(*iter, true);
            }
            
            if (targets->count() == 0)
            {
                HASH_DEL(_schedObj_target_ht, current);
                targets->release();
                free(current);
            }
        }
    }
    
    dump();
    CCLOGINFO("removeAllTargetsForPriority end");
}

void JSScheduleWrapper::removeAllTargetsForJSObject(JSObject* jsTargetObj)
{
    CCLOGINFO("removeAllTargetsForNatiaveNode begin");
    dump();
    Array* removeNativeTargets = NULL;
    schedTarget_proxy_t *t = NULL;
    HASH_FIND_PTR(_schedObj_target_ht, &jsTargetObj, t);
    if (t != NULL) {
        removeNativeTargets = t->targets;
        HASH_DEL(_schedObj_target_ht, t);
    }

    if (removeNativeTargets == NULL) return;

    schedFunc_proxy_t *current, *tmp;
    HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
        std::vector<Object*> objectsNeedToBeReleased;
        Array* targets = current->targets;
        Object* pObj = NULL;
        CCARRAY_FOREACH(targets, pObj)
        {
            if (removeNativeTargets->containsObject(pObj))
            {
                objectsNeedToBeReleased.push_back(pObj);
            }
        }
        
        auto iter = objectsNeedToBeReleased.begin();
        for (; iter != objectsNeedToBeReleased.end(); ++iter)
        {
            targets->removeObject(*iter, true);
        }

        if (targets->count() == 0)
        {
            HASH_DEL(_schedFunc_target_ht, current);
            targets->release();
            free(current);
        }  
    }

    removeNativeTargets->removeAllObjects();
    removeNativeTargets->release();
    free(t);
    dump();
    CCLOGINFO("removeAllTargetsForNatiaveNode end");
}

void JSScheduleWrapper::removeTargetForJSObject(JSObject* jsTargetObj, JSScheduleWrapper* target)
{
    CCLOGINFO("removeTargetForJSObject begin");
    dump();
    schedTarget_proxy_t *t = NULL;
    HASH_FIND_PTR(_schedObj_target_ht, &jsTargetObj, t);
    if (t != NULL) {
        t->targets->removeObject(target);
        if (t->targets->count() == 0)
        {
            t->targets->release();
            HASH_DEL(_schedObj_target_ht, t);
            free(t);
        }
    }

    schedFunc_proxy_t *current, *tmp, *removed=NULL;

    HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
        Array* targets = current->targets;
        Object* pObj = NULL;
        
        CCARRAY_FOREACH(targets, pObj)
        {
            JSScheduleWrapper* pOneTarget = static_cast<JSScheduleWrapper*>(pObj);
            if (pOneTarget == target)
            {
                removed = current;
                break;
            }
        }
        if (removed) break;
    }

    if (removed)
    {
        removed->targets->removeObject(target);
        if (removed->targets->count() == 0)
        {
            removed->targets->release();
            HASH_DEL(_schedFunc_target_ht, removed);
            free(removed);
        }  
    }
    dump();
    CCLOGINFO("removeTargetForJSObject end");
}

void JSScheduleWrapper::dump()
{
#if COCOS2D_DEBUG > 1
    CCLOG("\n---------JSScheduleWrapper dump begin--------------\n");
    CCLOG("target hash count = %d, func hash count = %d", HASH_COUNT(_schedObj_target_ht), HASH_COUNT(_schedFunc_target_ht));
    schedTarget_proxy_t *current, *tmp;
    int nativeTargetsCount = 0;
    HASH_ITER(hh, _schedObj_target_ht, current, tmp) {
        Object* pObj = NULL;
        CCARRAY_FOREACH(current->targets, pObj)
        {
            CCLOG("js target ( %p ), native target[%d]=( %p )", current->jsTargetObj, nativeTargetsCount, pObj);
            nativeTargetsCount++;
        }
    }

    CCLOG("\n-----------------------------\n");

    schedFunc_proxy_t *current_func, *tmp_func;
    int jsfuncTargetCount = 0;
    HASH_ITER(hh, _schedFunc_target_ht, current_func, tmp_func) {
        Object* pObj = NULL;
        CCARRAY_FOREACH(current_func->targets, pObj)
        {
            CCLOG("js func ( %p ), native target[%d]=( %p )", current_func->jsfuncObj, jsfuncTargetCount, pObj);
            jsfuncTargetCount++;
        }
    }
    CCASSERT(nativeTargetsCount == jsfuncTargetCount, "");
    CCLOG("\n---------JSScheduleWrapper dump end--------------\n");
#endif
}

void JSScheduleWrapper::scheduleFunc(float dt)
{
    jsval retval = JSVAL_NULL;
    jsval data = DOUBLE_TO_JSVAL(dt);

    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();

    JSBool ok = JS_AddValueRoot(cx, &data);
    if (!ok) {
        CCLOG("scheduleFunc: Root value fails.");
        return;
    }

    if(!_jsCallback.isNullOrUndefined()) {
        if (!_jsThisObj.isNullOrUndefined()) {
            JSAutoCompartment ac(cx, JSVAL_TO_OBJECT(_jsThisObj));
            JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(_jsThisObj), _jsCallback, 1, &data, &retval);
        }
        else {
            JS_CallFunctionValue(cx, NULL, _jsCallback, 1, &data, &retval);
        }
    }

    JS_RemoveValueRoot(cx, &data);
}

void JSScheduleWrapper::update(float dt)
{
    jsval data = DOUBLE_TO_JSVAL(dt);
    
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    
    JSBool ok = JS_AddValueRoot(cx, &data);
    if (!ok) {
        CCLOG("scheduleFunc: Root value fails.");
        return;
    }
    
    ScriptingCore::getInstance()->executeFunctionWithOwner(_jsThisObj, "update", 1, &data);
    
    JS_RemoveValueRoot(cx, &data);
}

Object* JSScheduleWrapper::getTarget()
{
    return _pTarget;
}

void JSScheduleWrapper::setTarget(Object* pTarget)
{
    _pTarget = pTarget;
}

void JSScheduleWrapper::setPureJSTarget(JSObject* pPureJSTarget)
{
    CCASSERT(_pPureJSTarget == NULL, "The pure js target has been set");
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    _pPureJSTarget = pPureJSTarget;
    JS_AddNamedObjectRoot(cx, &_pPureJSTarget, "Pure JS target");
}

JSObject* JSScheduleWrapper::getPureJSTarget()
{
    return _pPureJSTarget;
}

void JSScheduleWrapper::setPriority(int priority)
{
    _priority = priority;
}

int  JSScheduleWrapper::getPriority()
{
    return _priority;
}

void JSScheduleWrapper::setUpdateSchedule(bool isUpdateSchedule)
{
    _isUpdateSchedule = isUpdateSchedule;
}

bool JSScheduleWrapper::isUpdateSchedule()
{
    return _isUpdateSchedule;
}

JSBool js_CCNode_unschedule(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy = jsb_get_js_proxy(obj);
		cocos2d::Node *node = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
        JSB_PRECONDITION2(node, cx, JS_FALSE, "Invalid Native Object");
        
        Scheduler *sched = node->getScheduler();
        
        Array* targetArray = JSScheduleWrapper::getTargetForSchedule(argv[0]);
        CCLOGINFO("unschedule target number: %d", targetArray->count());
        Object* tmp = NULL;
        CCARRAY_FOREACH(targetArray, tmp)
        {
            JSScheduleWrapper* target = static_cast<JSScheduleWrapper*>(tmp);
            if (node == target->getTarget())
            {
                sched->unscheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), target);
                JSScheduleWrapper::removeTargetForJSObject(obj, target);
                break;
            }
        }
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
    }
    return JS_TRUE;
}

JSBool js_cocos2dx_CCNode_unscheduleAllSelectors(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
    if (argc == 0)
    {
        cobj->unscheduleAllSelectors();

        Array *arr = JSScheduleWrapper::getTargetForJSObject(obj);
		// If there aren't any targets, just return true.
		// Otherwise, the for loop will break immediately. 
		// It will lead to logic errors. 
		// For details to reproduce it, please refer to SchedulerTest/SchedulerUpdate.
        if(! arr) return JS_TRUE;
        JSScheduleWrapper* wrapper = NULL;
        for(unsigned int i = 0; i < arr->count(); ++i) {
            wrapper = (JSScheduleWrapper*)arr->objectAtIndex(i);
            if(wrapper) {
                cobj->getScheduler()->unscheduleAllForTarget(wrapper);
            }
        }
        
        JSScheduleWrapper::removeAllTargetsForJSObject(obj);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

JSBool js_CCNode_scheduleOnce(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        JSBool ok = JS_TRUE;
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy = jsb_get_js_proxy(obj);
		cocos2d::Node *node = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
        
        Scheduler *sched = node->getScheduler();
        
        JSScheduleWrapper *tmpCobj = NULL;

        //
        // delay
        //
        double delay;
        if( argc >= 2 ) {
            ok &= JS_ValueToNumber(cx, argv[1], &delay );
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        }
        
        bool bFound = false;
        Array* pTargetArr = JSScheduleWrapper::getTargetForJSObject(obj);
        Object* pObj = NULL;
        CCARRAY_FOREACH(pTargetArr, pObj)
        {
            JSScheduleWrapper* pTarget = static_cast<JSScheduleWrapper*>(pObj);
            if (argv[0] == pTarget->getJSCallbackFunc())
            {
                tmpCobj = pTarget;
                bFound = true;
                break;
            }
        }

        if (!bFound)
        {
            tmpCobj = new JSScheduleWrapper();
            tmpCobj->autorelease();
            tmpCobj->setJSCallbackThis(OBJECT_TO_JSVAL(obj));
            tmpCobj->setJSCallbackFunc(argv[0]);
            tmpCobj->setTarget(node);

            JSScheduleWrapper::setTargetForSchedule(argv[0], tmpCobj);
            JSScheduleWrapper::setTargetForJSObject(obj, tmpCobj);
        }

        if(argc == 1) {
            sched->scheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), tmpCobj, 0, 0, 0.0f, !node->isRunning());
        } else {
            sched->scheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), tmpCobj, 0, 0, delay, !node->isRunning());
        }

		/* We shouldn't set the js callback function to reserved slot,
		   since the target object may execute more than one schedule.
		   Therefore, previous js callback function will be replaced 
		   by the current one. For example:
		      this.scheduleOnce(function() { temporary function 1 }, 0.5);
		      this.scheduleOnce(function() { temporary function 2 }, 0.5);
		   In this case, the temporary function 1 will be removed from reserved slot 0.
		   And temporary function 2 will be set to reserved slot 0 of this object.
		   If gc is triggered before the 'JSScheduleWrapper::scheduleFunc' is invoked, 
		   crash will happen. You could simply reproduce it by adding '__jsc__.garbageCollect();' after scheduleOnce.
		   
		   [Solution] Because one schedule corresponds to one JSScheduleWrapper, we root 
		   the js callback function in JSScheduleWrapper::setJSCallbackFunc and unroot it 
		   at the destructor of JSScheduleWrapper.
		*/
        //jsb_set_reserved_slot(proxy->obj, 0, argv[0]);

        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

JSBool js_CCNode_schedule(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        JSBool ok = JS_TRUE;
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy = jsb_get_js_proxy(obj);
		cocos2d::Node *node = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
        Scheduler *sched = node->getScheduler();

        JSScheduleWrapper *tmpCobj = NULL;

    	double interval = 0.0;
        if( argc >= 2 ) {
            ok &= JS_ValueToNumber(cx, argv[1], &interval );
        }
        
        //
        // repeat
        //
        double repeat = 0.0;
        if( argc >= 3 ) {
            ok &= JS_ValueToNumber(cx, argv[2], &repeat );
        }
        
        //
        // delay
        //
        double delay = 0.0;
        if( argc >= 4 ) {
            ok &= JS_ValueToNumber(cx, argv[3], &delay );
        }
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        bool bFound = false;
        Array* pTargetArr = JSScheduleWrapper::getTargetForJSObject(obj);
        Object* pObj = NULL;
        CCARRAY_FOREACH(pTargetArr, pObj)
        {
            JSScheduleWrapper* pTarget = static_cast<JSScheduleWrapper*>(pObj);
            if (argv[0] == pTarget->getJSCallbackFunc())
            {
                tmpCobj = pTarget;
                bFound = true;
                break;
            }
        }

        if (!bFound)
        {
            tmpCobj = new JSScheduleWrapper();
            tmpCobj->autorelease();
            tmpCobj->setJSCallbackThis(OBJECT_TO_JSVAL(obj));
            tmpCobj->setJSCallbackFunc(argv[0]);
            tmpCobj->setTarget(node);
            JSScheduleWrapper::setTargetForSchedule(argv[0], tmpCobj);        
            JSScheduleWrapper::setTargetForJSObject(obj, tmpCobj);
        }
        
        if(argc == 1) {
            sched->scheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), tmpCobj, 0, !node->isRunning());
        } if(argc == 2) {
            sched->scheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), tmpCobj, interval, !node->isRunning());
        } if(argc == 3) {
            sched->scheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), tmpCobj, interval, (unsigned int)repeat, 0, !node->isRunning());
        } if (argc == 4) {
            sched->scheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), tmpCobj, interval, (unsigned int)repeat, delay, !node->isRunning());
        }
		
        // I comment next line with the same reason in the js_CCNode_scheduleOnce.
        //jsb_set_reserved_slot(proxy->obj, 0, argv[0]);

        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

JSBool js_cocos2dx_CCNode_scheduleUpdateWithPriority(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0 = 0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        JSBool isFoundUpdate = JS_FALSE;
        ok = JS_HasProperty(cx, obj, "update", &isFoundUpdate);
        jsval jsUpdateFunc;
        if (ok && isFoundUpdate) {
            ok = JS_GetProperty(cx, obj, "update", &jsUpdateFunc);
        }
        
        // if no 'update' property, return JS_TRUE directly.
        if (!ok) {
            JS_SET_RVAL(cx, vp, JSVAL_VOID);
            return JS_TRUE;
        }
        
        JSScheduleWrapper* tmpCobj = NULL;
        
        bool bFound = false;
        Array* pTargetArr = JSScheduleWrapper::getTargetForJSObject(obj);
        Object* pObj = NULL;
        CCARRAY_FOREACH(pTargetArr, pObj)
        {
            JSScheduleWrapper* pTarget = static_cast<JSScheduleWrapper*>(pObj);
            if (jsUpdateFunc == pTarget->getJSCallbackFunc())
            {
                tmpCobj = pTarget;
                bFound = true;
                break;
            }
        }
        
        if (!bFound)
        {
            tmpCobj = new JSScheduleWrapper();
            tmpCobj->autorelease();
            tmpCobj->setJSCallbackThis(OBJECT_TO_JSVAL(obj));
            tmpCobj->setJSCallbackFunc(jsUpdateFunc);
            tmpCobj->setTarget(cobj);
            tmpCobj->setUpdateSchedule(true);
            JSScheduleWrapper::setTargetForSchedule(jsUpdateFunc, tmpCobj);
            JSScheduleWrapper::setTargetForJSObject(obj, tmpCobj);
        }
        
        tmpCobj->setPriority(arg0);
        cobj->getScheduler()->scheduleUpdateForTarget(tmpCobj, arg0, !cobj->isRunning());
        
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCNode_unscheduleUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
    if (argc == 0)
    {
        cobj->unscheduleUpdate();
        do {
			JSObject *tmpObj = obj;
            
            Array *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
			// If there aren't any targets, just return true.
			// Otherwise, the for loop will break immediately.
			// It will lead to logic errors.
			// For details to reproduce it, please refer to SchedulerTest/SchedulerUpdate.
            if(! arr) return JS_TRUE;
            
            JSScheduleWrapper* wrapper = NULL;
            for(unsigned int i = 0; i < arr->count(); ++i) {
                wrapper = (JSScheduleWrapper*)arr->objectAtIndex(i);
                if(wrapper && wrapper->isUpdateSchedule()) {
                    cobj->getScheduler()->unscheduleUpdateForTarget(wrapper);
                    CCASSERT(OBJECT_TO_JSVAL(tmpObj) == wrapper->getJSCallbackThis(), "Wrong target object.");
                    JSScheduleWrapper::removeTargetForJSObject(tmpObj, wrapper);
                    break;
                }
            }
		} while (0);
        
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
    }
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCNode_scheduleUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
        
        JSBool isFoundUpdate = JS_FALSE;
        ok = JS_HasProperty(cx, obj, "update", &isFoundUpdate);
        jsval jsUpdateFunc;
        if (ok && isFoundUpdate) {
            ok = JS_GetProperty(cx, obj, "update", &jsUpdateFunc);
        }
        
        // if no 'update' property, return JS_TRUE directly.
        if (!ok) {
            JS_SET_RVAL(cx, vp, JSVAL_VOID);
            return JS_TRUE;
        }
        
        JSScheduleWrapper* tmpCobj = NULL;
        
        bool bFound = false;
        Array* pTargetArr = JSScheduleWrapper::getTargetForJSObject(obj);
        Object* pObj = NULL;
        CCARRAY_FOREACH(pTargetArr, pObj)
        {
            JSScheduleWrapper* pTarget = static_cast<JSScheduleWrapper*>(pObj);
            if (jsUpdateFunc == pTarget->getJSCallbackFunc())
            {
                tmpCobj = pTarget;
                bFound = true;
                break;
            }
        }
        
        if (!bFound)
        {
            tmpCobj = new JSScheduleWrapper();
            tmpCobj->autorelease();
            tmpCobj->setJSCallbackThis(OBJECT_TO_JSVAL(obj));
            tmpCobj->setJSCallbackFunc(jsUpdateFunc);
            tmpCobj->setTarget(cobj);
            tmpCobj->setUpdateSchedule(true);
            JSScheduleWrapper::setTargetForSchedule(jsUpdateFunc, tmpCobj);
            JSScheduleWrapper::setTargetForJSObject(obj, tmpCobj);
        }
        
        cobj->getScheduler()->scheduleUpdateForTarget(tmpCobj, 0, !cobj->isRunning());
        
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCScheduler_unscheduleAllSelectorsForTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Scheduler* cobj = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
	if (argc == 1) {
		do {
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            
            Array *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
			// If there aren't any targets, just return true.
			// Otherwise, the for loop will break immediately.
			// It will lead to logic errors.
			// For details to reproduce it, please refer to SchedulerTest/SchedulerUpdate.
            if(! arr) return JS_TRUE;
            
            JSScheduleWrapper* wrapper = NULL;
            for(unsigned int i = 0; i < arr->count(); ++i) {
                wrapper = (JSScheduleWrapper*)arr->objectAtIndex(i);
                if(wrapper) {
                    cobj->unscheduleAllForTarget(wrapper);
                }
            }
            JSScheduleWrapper::removeAllTargetsForJSObject(tmpObj);
            
		} while (0);
        
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_CCScheduler_scheduleUpdateForTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        JSBool ok = JS_TRUE;
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy = jsb_get_js_proxy(obj);
		cocos2d::Scheduler *sched = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
        
        JSScheduleWrapper *tmpCObj = NULL;
        
        JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
        proxy = jsb_get_js_proxy(tmpObj);
        bool isPureJSTarget = proxy ? false : true;
        
        JSBool isFoundUpdate = JS_FALSE;
        ok = JS_HasProperty(cx, tmpObj, "update", &isFoundUpdate);
        jsval jsUpdateFunc;
        if (ok && isFoundUpdate) {
            ok = JS_GetProperty(cx, tmpObj, "update", &jsUpdateFunc);
        }
        
        // if no 'update' property, return JS_TRUE directly.
        if (!ok) {
            JS_SET_RVAL(cx, vp, JSVAL_VOID);
            return JS_TRUE;
        }
        
        int arg1 = 0;
        if (argc >= 2) {
            ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        }

        JSBool paused = JS_FALSE;
        
        if( argc >= 3 ) {
            ok &= JS_ValueToBoolean(cx,  argv[2], &paused);
        }
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        bool bFound = false;
        Array* pTargetArr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
        Object* pObj = NULL;
        CCARRAY_FOREACH(pTargetArr, pObj)
        {
            JSScheduleWrapper* pTarget = static_cast<JSScheduleWrapper*>(pObj);
            if (jsUpdateFunc == pTarget->getJSCallbackFunc())
            {
                tmpCObj = pTarget;
                bFound = true;
                break;
            }
        }
        
        if (!bFound)
        {
            tmpCObj = new JSScheduleWrapper();
            tmpCObj->autorelease();
            tmpCObj->setJSCallbackThis(argv[0]);
            tmpCObj->setJSCallbackFunc(jsUpdateFunc);
            tmpCObj->setUpdateSchedule(true);
            if (isPureJSTarget) {
                tmpCObj->setPureJSTarget(tmpObj);
            }
            
            JSScheduleWrapper::setTargetForSchedule(jsUpdateFunc, tmpCObj);
            JSScheduleWrapper::setTargetForJSObject(tmpObj, tmpCObj);
        }
        tmpCObj->setPriority(arg1);
        sched->scheduleUpdateForTarget(tmpCObj, arg1, paused);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

JSBool js_CCScheduler_unscheduleUpdateForTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Scheduler* cobj = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
	if (argc == 1) {
		do {
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            
            Array *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
			// If there aren't any targets, just return true.
			// Otherwise, the for loop will break immediately.
			// It will lead to logic errors.
			// For details to reproduce it, please refer to SchedulerTest/SchedulerUpdate.
            if(! arr) return JS_TRUE;
            
            JSScheduleWrapper* wrapper = NULL;
            for(unsigned int i = 0; i < arr->count(); ++i) {
                wrapper = (JSScheduleWrapper*)arr->objectAtIndex(i);
                if(wrapper && wrapper->isUpdateSchedule()) {
                    cobj->unscheduleUpdateForTarget(wrapper);
                    CCASSERT(argv[0] == wrapper->getJSCallbackThis(), "Wrong target object.");
                    JSScheduleWrapper::removeTargetForJSObject(tmpObj, wrapper);
                    break;
                }
            }
		} while (0);
        
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_CCScheduler_schedule(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 2) {
        JSBool ok = JS_TRUE;
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy = jsb_get_js_proxy(obj);
		cocos2d::Scheduler *sched = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
        
        JSScheduleWrapper *tmpCObj = NULL;
        
        JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
        proxy = jsb_get_js_proxy(tmpObj);
        bool isPureJSTarget = proxy ? false : true;
        
    	double interval = 0;
        if( argc >= 3 ) {
            ok &= JS_ValueToNumber(cx, argv[2], &interval );
        }
        
        //
        // repeat
        //
        double repeat = -1;
        if( argc >= 4 ) {
            ok &= JS_ValueToNumber(cx, argv[3], &repeat );
        }
        
        //
        // delay
        //
        double delay = 0;
        if( argc >= 5 ) {
            ok &= JS_ValueToNumber(cx, argv[4], &delay );
        }
        
        JSBool paused = JS_FALSE;
        
        if( argc >= 6 ) {
            ok &= JS_ValueToBoolean(cx,  argv[5], &paused);
        }
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        bool bFound = false;
        Array* pTargetArr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
        Object* pObj = NULL;
        CCARRAY_FOREACH(pTargetArr, pObj)
        {
            JSScheduleWrapper* pTarget = static_cast<JSScheduleWrapper*>(pObj);
            if (argv[1] == pTarget->getJSCallbackFunc())
            {
                tmpCObj = pTarget;
                bFound = true;
                break;
            }
        }

        if (!bFound)
        {
            tmpCObj = new JSScheduleWrapper();
            tmpCObj->autorelease();
            tmpCObj->setJSCallbackThis(argv[0]);
            tmpCObj->setJSCallbackFunc(argv[1]);
            if (isPureJSTarget) {
                tmpCObj->setPureJSTarget(tmpObj);
            }
            
            JSScheduleWrapper::setTargetForSchedule(argv[1], tmpCObj);
            JSScheduleWrapper::setTargetForJSObject(tmpObj, tmpCObj);
        }
        
        sched->scheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), tmpCObj, interval, repeat, delay, paused);
                
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

JSBool js_CCScheduler_unscheduleCallbackForTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Scheduler* cobj = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
	if (argc == 2) {
		do {
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            
            Array *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
			// If there aren't any targets, just return true.
			// Otherwise, the for loop will break immediately.
			// It will lead to logic errors.
			// For details to reproduce it, please refer to SchedulerTest/SchedulerUpdate.
            if(! arr) return JS_TRUE;
            
            JSScheduleWrapper* wrapper = NULL;
            for(unsigned int i = 0; i < arr->count(); ++i) {
                wrapper = (JSScheduleWrapper*)arr->objectAtIndex(i);
                if(wrapper && wrapper->getJSCallbackFunc() == argv[1]) {
                    cobj->unscheduleSelector(schedule_selector(JSScheduleWrapper::scheduleFunc), wrapper);
                    JSScheduleWrapper::removeTargetForJSObject(tmpObj, wrapper);
                    break;
                }
            }
		} while (0);
        
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCScheduler_unscheduleAll(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Scheduler* cobj = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
        cobj->unscheduleAll();
        JSScheduleWrapper::removeAllTargets();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCScheduler_unscheduleAllCallbacksWithMinPriority(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Scheduler* cobj = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->unscheduleAllWithMinPriority(arg0);
        JSScheduleWrapper::removeAllTargetsForMinPriority(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


JSBool js_cocos2dx_CCScheduler_pauseTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Scheduler *sched = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
    
	if (argc == 1) {
		do {
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            Array *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
            if(! arr) return JS_TRUE;
            for(unsigned int i = 0; i < arr->count(); ++i) {
                if(arr->objectAtIndex(i)) {
                    sched->pauseTarget(arr->objectAtIndex(i));
                }
            }

		} while (0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCScheduler_resumeTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Scheduler *sched = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
    
	if (argc == 1) {
		do {
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            Array *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
            if(! arr) return JS_TRUE;
            for(unsigned int i = 0; i < arr->count(); ++i) {
                if(arr->objectAtIndex(i)) {
                    sched->resumeTarget(arr->objectAtIndex(i));
                }
            }
            
		} while (0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCScheduler_isTargetPaused(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Scheduler* cobj = (cocos2d::Scheduler *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
        JSBool ret = JS_FALSE;
		do {
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            Array *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
            if(! arr) return JS_TRUE;
            for(unsigned int i = 0; i < arr->count(); ++i) {
                if(arr->objectAtIndex(i)) {
                    ret = cobj->isTargetPaused(arr->objectAtIndex(i)) ? JS_TRUE : JS_FALSE;
                    // break directly since all targets have the same `pause` status.
                    break;
                }
            }
		} while (0);
        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_doNothing(JSContext *cx, uint32_t argc, jsval *vp) {
    return JS_TRUE;
}

JSBool js_forceGC(JSContext *cx, uint32_t argc, jsval *vp) {
    JSRuntime *rt = JS_GetRuntime(cx);
    JS_GC(rt);
    return JS_TRUE;
}

JSBool js_cocos2dx_retain(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *thisObj = JS_THIS_OBJECT(cx, vp);
	if (thisObj) {
		js_proxy_t *proxy = jsb_get_js_proxy(thisObj);
		if (proxy) {
			((Object *)proxy->ptr)->retain();
			return JS_TRUE;
		}
	}
    JS_ReportError(cx, "Invalid Native Object.");
	return JS_FALSE;
}

JSBool js_cocos2dx_release(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *thisObj = JS_THIS_OBJECT(cx, vp);
	if (thisObj) {
		js_proxy_t *proxy = jsb_get_js_proxy(thisObj);
		if (proxy) {
			((Object *)proxy->ptr)->release();
			return JS_TRUE;
		}
	}
    JS_ReportError(cx, "Invalid Native Object.");
	return JS_FALSE;
}

JSBool js_cocos2dx_CCSet_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj;
	cocos2d::Set* cobj = nullptr;

	if (argc == 0) {
		cobj = new cocos2d::Set();
		cobj->autorelease();
		TypeTest<cocos2d::Set> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		js_proxy_t *proxy = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &proxy->obj, typeid(cobj).name());
	}
	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
    
    JS_ReportError(cx, "Error in js_cocos2dx_CCSet_constructor");
	return JS_FALSE;
}

JSBool js_cocos2dx_CCNode_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    JSBool ok = JS_TRUE;
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
	if (argc == 1) {
		cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		cobj->setPosition(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	} if (argc == 2) {
        double x;
        ok &= JS_ValueToNumber(cx, argv[0], &x );
        double y;
        ok &= JS_ValueToNumber(cx, argv[1], &y );
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        cobj->setPosition(Point(x,y));
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


JSBool js_cocos2dx_CCSprite_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    JSBool ok = JS_TRUE;
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Sprite* cobj = (cocos2d::Sprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setPosition(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	} if (argc == 2) {
        double x;
        ok &= JS_ValueToNumber(cx, argv[0], &x );
        double y;
        ok &= JS_ValueToNumber(cx, argv[1], &y );

        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        cobj->setPosition(Point(x,y));
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


JSBool js_cocos2dx_CCTMXLayer_tileFlagsAt(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj;
    JSBool ok = JS_TRUE;
	cocos2d::TMXLayer* cobj;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (cocos2d::TMXLayer *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::ccTMXTileFlags flags = kTMXTileHorizontalFlag;
		jsval jsret;
        jsret = UINT_TO_JSVAL((uint32_t)flags);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

JSBool js_cocos2dx_CCTMXLayer_getTiles(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::TMXLayer* cobj = (cocos2d::TMXLayer *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		unsigned int* ret = cobj->getTiles();
        Size size = cobj->getLayerSize();
        int count = size.width * size.height;
        JSObject* array = JS_NewUint32Array(cx, count);
        if (NULL == array) {
            JS_ReportError(cx, "Can't allocate enough memory.");
            return JS_FALSE;
        }
        uint32_t* bufdata = (uint32_t*)JS_GetArrayBufferViewData(array);
        memcpy(bufdata, ret, count*sizeof(uint32_t));
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(array));
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


template<class T>
JSBool js_BezierActions_create(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);

    if (argc == 2) {
        double t;
        if( ! JS_ValueToNumber(cx, argv[0], &t) ) {
            return JS_FALSE;
        }
        
        int num;
        Point *arr;
        jsval_to_ccarray_of_CCPoint(cx, argv[1], &arr, &num);
        
        ccBezierConfig config;
        config.controlPoint_1 = arr[0];
        config.controlPoint_2 = arr[1];
        config.endPosition = arr[2];
        
        T* ret =  T::create(t, config);
        
        free(arr);

        jsval jsret;
		do {
			if (ret) {
				js_proxy_t *p = jsb_get_native_proxy(ret);
				if (p) {
					jsret = OBJECT_TO_JSVAL(p->obj);
				} else {
					// create a new js obj of that class
					js_proxy_t *proxy = js_get_or_create_proxy<T>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				}
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

template<class T>
JSBool js_CardinalSplineActions_create(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    
    if (argc == 3) {
        double dur;
        ok &= JS_ValueToNumber(cx, argv[0], &dur);
        
        int num;
        Point *arr;
        ok &= jsval_to_ccarray_of_CCPoint(cx, argv[1], &arr, &num);
        
        double ten;
        ok &= JS_ValueToNumber(cx, argv[2], &ten);
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        PointArray *points = PointArray::create(num);
        
        for( int i=0; i < num;i++) {
            points->addControlPoint(arr[i]);
        }
        
        T *ret = T::create(dur, points, ten);
        
        free(arr);
        
        jsval jsret;
		do {
			if (ret) {
				js_proxy_t *p = jsb_get_native_proxy(ret);
				if (p) {
					jsret = OBJECT_TO_JSVAL(p->obj);
				} else {
					// create a new js obj of that class
					js_proxy_t *proxy = js_get_or_create_proxy<T>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				}
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

template<class T>
JSBool js_CatmullRomActions_create(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    
    if (argc == 2) {
        double dur;
        ok &= JS_ValueToNumber(cx, argv[0], &dur);
        
        int num;
        Point *arr;
        ok &= jsval_to_ccarray_of_CCPoint(cx, argv[1], &arr, &num);
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        PointArray *points = PointArray::create(num);
        
        for( int i=0; i < num;i++) {
            points->addControlPoint(arr[i]);
        }
        
        T *ret = T::create(dur, points);
        
        free(arr);
        
        jsval jsret;
		do {
			if (ret) {
				js_proxy_t *p = jsb_get_native_proxy(ret);
				if (p) {
					jsret = OBJECT_TO_JSVAL(p->obj);
				} else {
					// create a new js obj of that class
					js_proxy_t *proxy = js_get_or_create_proxy<T>(cx, ret);
					jsret = OBJECT_TO_JSVAL(proxy->obj);
				}
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


JSBool JSB_CCBezierBy_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
    return js_BezierActions_create<cocos2d::BezierBy>(cx, argc, vp);
}

JSBool JSB_CCBezierTo_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	return js_BezierActions_create<cocos2d::BezierTo>(cx, argc, vp);
}


JSBool JSB_CCCardinalSplineBy_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
    return js_CardinalSplineActions_create<cocos2d::CardinalSplineBy>(cx, argc, vp);
}

JSBool JSB_CCCardinalSplineTo_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
    return js_CardinalSplineActions_create<cocos2d::CardinalSplineTo>(cx, argc, vp);
}

JSBool JSB_CCCatmullRomBy_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
    return js_CatmullRomActions_create<cocos2d::CatmullRomBy>(cx, argc, vp);
}

JSBool JSB_CCCatmullRomTo_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	return js_CatmullRomActions_create<cocos2d::CatmullRomTo>(cx, argc, vp);
}

JSBool js_cocos2dx_ccGLEnableVertexAttribs(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
	jsval *argv = JS_ARGV(cx, vp);
    
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        GL::enableVertexAttribs(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_NULL);
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}



JSBool js_cocos2dx_ccpAdd(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
	jsval *argv = JS_ARGV(cx, vp);
    
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0 + arg1;
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpDistanceSQ(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
	jsval *argv = JS_ARGV(cx, vp);
    
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
		
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		float ret = arg0.getDistanceSq(arg1);
		
		jsval jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpDistance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
	jsval *argv = JS_ARGV(cx, vp);
    
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
		
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		float ret = arg0.getDistance(arg1);
		
		jsval jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpClamp(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 3) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
		cocos2d::Point arg2;
		ok &= jsval_to_ccpoint(cx, argv[2], &arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0.getClampPoint(arg1, arg2);
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpLengthSQ(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		float ret = arg0.getLengthSq();

		jsval jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;

	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpLength(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 1) {
		cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

		float ret = arg0.getLength();

		jsval jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;

	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpNeg(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 1) {
		cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = -arg0;
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpSub(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0 - arg1;
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
        
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpMult(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 2) {
        cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        
		double arg1;
		ok &= JS_ValueToNumber(cx, argv[1], &arg1);
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		
		Point ret = arg0 * arg1;
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpMidpoint(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0.getMidpoint(arg1);
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}


JSBool js_cocos2dx_ccpDot(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		float ret = arg0.dot(arg1);
		
		jsval jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpCross(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		float ret = arg0.cross(arg1);
		
		jsval jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpPerp(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0.getPerp();
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


JSBool js_cocos2dx_ccpRPerp(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0.getRPerp();
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


JSBool js_cocos2dx_ccpProject(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0.project(arg1);
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpRotate(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		cocos2d::Point arg1;
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0.rotate(arg1);
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
        
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}

JSBool js_cocos2dx_ccpNormalize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		Point ret = arg0.normalize();
		
		jsval jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		
		return JS_TRUE;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

// setBlendFunc
template<class T>
JSBool js_cocos2dx_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj;
    T* cobj;
    obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (T*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)
    if (argc == 2)
    {
        GLenum src, dst;
        jsval_to_int32(cx, argv[0], (int32_t*)&src);
        jsval_to_int32(cx, argv[1], (int32_t*)&dst);
        BlendFunc blendFunc = {src, dst};
        cobj->setBlendFunc(blendFunc);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
    return JS_FALSE;
}

JSBool js_cocos2dx_CCSprite_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    return js_cocos2dx_setBlendFunc<Sprite>(cx, argc, vp);
}

JSBool js_cocos2dx_CCSpriteBatchNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    return js_cocos2dx_setBlendFunc<SpriteBatchNode>(cx, argc, vp);
}

// JSBool js_cocos2dx_CCMotionStreak_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
// {
//     return js_cocos2dx_setBlendFunc<MotionStreak>(cx, argc, vp);
// }

JSBool js_cocos2dx_CCAtlasNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    return js_cocos2dx_setBlendFunc<AtlasNode>(cx, argc, vp);
}

JSBool js_cocos2dx_CCParticleBatchNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    return js_cocos2dx_setBlendFunc<ParticleBatchNode>(cx, argc, vp);
}

JSBool js_cocos2dx_CCLayerColor_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    return js_cocos2dx_setBlendFunc<LayerColor>(cx, argc, vp);
}

JSBool js_cocos2dx_CCParticleSystem_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    return js_cocos2dx_setBlendFunc<ParticleSystem>(cx, argc, vp);
}

JSBool js_cocos2dx_CCDrawNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    return js_cocos2dx_setBlendFunc<DrawNode>(cx, argc, vp);
}

JSBool js_cocos2dx_CCTexture2D_setTexParameters(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Texture2D* cobj = (Texture2D*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)

    if (argc == 4)
    {
        jsval *argvp = JS_ARGV(cx,vp);
        JSBool ok = JS_TRUE;

        GLuint arg0, arg1, arg2, arg3;

        ok &= jsval_to_uint32(cx, *argvp++, &arg0);
        ok &= jsval_to_uint32(cx, *argvp++, &arg1);
        ok &= jsval_to_uint32(cx, *argvp++, &arg2);
        ok &= jsval_to_uint32(cx, *argvp++, &arg3);

        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

        ccTexParams param = { arg0, arg1, arg2, arg3 };

        cobj->setTexParameters(param);

        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 4);
    return JS_FALSE;		
}

JSBool js_cocos2dx_CCMenu_alignItemsInRows(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
    JSBool ok = JS_TRUE;
    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
    Menu* cobj = (Menu*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)

    jsval *argvp = JS_ARGV(cx,vp);

    Array* pArray = NULL;
    ok &= jsvals_variadic_to_ccarray(cx, argvp, argc, &pArray);
    if (ok && pArray)
    {
        cobj->alignItemsInRowsWithArray(pArray);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "Error in js_cocos2dx_CCMenu_alignItemsInRows");
    return JS_FALSE;
}

JSBool js_cocos2dx_CCMenu_alignItemsInColumns(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
    JSBool ok = JS_TRUE;
    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
    Menu* cobj = (Menu*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)

    jsval *argvp = JS_ARGV(cx,vp);
    Array* pArray = NULL;
    ok &= jsvals_variadic_to_ccarray(cx, argvp, argc, &pArray);
    if (ok && pArray)
    {
        cobj->alignItemsInColumnsWithArray(pArray);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "Error in js_cocos2dx_CCMenu_alignItemsInColumns");
    return JS_FALSE;
}

// TMXLayer
JSBool js_cocos2dx_CCTMXLayer_getTileFlagsAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj;
    TMXLayer* cobj;
    obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (TMXLayer*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)
    if (argc == 1)
    {
        ccTMXTileFlags flags;
        Point arg0;
        ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        cobj->getTileGIDAt(arg0, &flags);
        
        JS_SET_RVAL(cx, vp, UINT_TO_JSVAL((uint32_t)flags));
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
    return JS_FALSE;
}

//#pragma mark - DrawNode

// Arguments: Array of points, fill color (Color4F), width(float), border color (Color4F)
// Ret value: void
JSBool js_cocos2dx_CCDrawNode_drawPolygon(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    DrawNode* cobj = (DrawNode*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)

    if ( argc == 4) {
        jsval *argvp = JS_ARGV(cx,vp);
        JSBool ok = JS_TRUE;
        JSObject *argArray = NULL;
        Color4F argFillColor = Color4F(0.0f, 0.0f, 0.0f, 0.0f);
        double argWidth = 0.0;
        Color4F argBorderColor = Color4F(0.0f, 0.0f, 0.0f, 0.0f);

        // Points
        ok &= JS_ValueToObject(cx, *argvp++, &argArray);
        JSB_PRECONDITION2( (argArray && JS_IsArrayObject(cx, argArray)) , cx, JS_FALSE, "Vertex should be anArray object");

        // Color 4F
        ok &= jsval_to_cccolor4f(cx, *argvp++, &argFillColor);

        // Width
        ok &= JS_ValueToNumber( cx, *argvp++, &argWidth );

        // Color Border (4F)
        ok &= jsval_to_cccolor4f(cx, *argvp++, &argBorderColor);

        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error parsing arguments");

        {
            uint32_t l;
            if( ! JS_GetArrayLength(cx, argArray, &l) )
                return JS_FALSE;

            Point* verts = new Point[ l ];
            Point p;

            for( uint32_t i=0; i<l; i++ ) {
                jsval pointvp;
                ok &= JS_GetElement(cx, argArray, i, &pointvp);
                JSB_PRECONDITION2(ok, cx, JS_FALSE, "JS_GetElement fails.");
                
                ok &= jsval_to_ccpoint(cx, pointvp, &p);
                JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
                verts[i] = p;
            }

            cobj->drawPolygon(verts, l, argFillColor, argWidth, argBorderColor);
            CC_SAFE_DELETE_ARRAY(verts);
        }
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;	
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 4);
    return JS_FALSE;
}

static JSBool jsval_to_string_vector(JSContext* cx, jsval v, std::vector<std::string>& ret) {
    JSObject *jsobj;
    JSBool ok = JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
	JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj),  cx, JS_FALSE, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);

    for (uint32_t i=0; i < len; i++) {
        jsval elt;
        if (JS_GetElement(cx, jsobj, i, &elt)) {
            
            if (JSVAL_IS_STRING(elt))
            {
                JSStringWrapper str(JSVAL_TO_STRING(elt));
                ret.push_back(str.get());
            }
        }
    }

    return JS_TRUE;
}


static jsval string_vector_to_jsval(JSContext* cx, const std::vector<std::string>& arr) {
    
    JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);
    
    int i = 0;
    for(std::vector<std::string>::const_iterator iter = arr.begin(); iter != arr.end(); ++iter, ++i) {
        jsval arrElement = c_string_to_jsval(cx, iter->c_str());
        if(!JS_SetElement(cx, jsretArr, i, &arrElement)) {
            break;
        }
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

JSBool js_cocos2dx_CCFileUtils_setSearchResolutionsOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= jsval_to_string_vector(cx, argv[0], arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        cobj->setSearchResolutionsOrder(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

JSBool js_cocos2dx_CCFileUtils_setSearchPaths(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= jsval_to_string_vector(cx, argv[0], arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        cobj->setSearchPaths(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}
JSBool js_cocos2dx_CCFileUtils_getSearchPaths(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 0) {
        std::vector<std::string> ret = cobj->getSearchPaths();
        jsval jsret;
        jsret = string_vector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}

JSBool js_cocos2dx_CCFileUtils_getStringFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        unsigned long size = 0;
        unsigned char* data = cobj->getFileData(arg0, "rb", &size);
        if (data && size > 0) {
            jsval jsret = c_string_to_jsval(cx, (char*)data, size);
            JS_SET_RVAL(cx, vp, jsret);
            return JS_TRUE;
        }
        JS_ReportError(cx, "get file(%s) data fails", arg0);
        return JS_FALSE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
    return JS_FALSE;
}

JSBool js_cocos2dx_CCFileUtils_getByteArrayFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        unsigned long size = 0;
        unsigned char* data = cobj->getFileData(arg0, "rb", &size);
        do
        {
            if (data && size > 0) {
                JSObject* array = JS_NewUint8Array(cx, size);
                if (NULL == array) {
                    break;
                }
                uint8_t* bufdata = (uint8_t*)JS_GetArrayBufferViewData(array);
                memcpy(bufdata, data, size*sizeof(uint8_t));
                JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(array));
                return JS_TRUE;
            }
        } while(false);
        
        JS_ReportError(cx, "get file(%s) data fails", arg0);
        return JS_FALSE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
    return JS_FALSE;
}

JSBool js_cocos2dx_CCFileUtils_getSearchResolutionsOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 0) {
        std::vector<std::string> ret = cobj->getSearchResolutionsOrder();
        jsval jsret;
        jsret = string_vector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}

static JSBool js_cocos2dx_FileUtils_createDictionaryWithContentsOfFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::Dictionary* ret = Dictionary::createWithContentsOfFile(arg0.c_str());
		jsval jsret;
		jsret = ccdictionary_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCGLProgram_setUniformLocationWith4f(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::GLProgram* cobj = (cocos2d::GLProgram *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    int arg0;
    double arg1;
    double arg2;
    double arg3;
    double arg4;
    ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
    ok &= JS_ValueToNumber(cx, argv[1], &arg1);
    
    if(argc == 2) {
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        cobj->setUniformLocationWith1f(arg0, arg1);
    }
	if (argc == 3) {
        ok &= JS_ValueToNumber(cx, argv[2], &arg2);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setUniformLocationWith2f(arg0, arg1, arg2);
	}
    if(argc == 4) {
        ok &= JS_ValueToNumber(cx, argv[3], &arg3);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setUniformLocationWith3f(arg0, arg1, arg2, arg3);
    }
    if(argc == 5) {
        ok &= JS_ValueToNumber(cx, argv[4], &arg4);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setUniformLocationWith4f(arg0, arg1, arg2, arg3, arg4);
    }
    
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 5);
	return JS_FALSE;
}

JSBool js_cocos2dx_CCGLProgram_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
    if(argc != 2) {
        JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
        return JS_FALSE;
    }
    
    const char *arg0, *arg1;
    std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
    std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();

    GLProgram* ret = new GLProgram();
    ret->autorelease();
    
    ret->initWithVertexShaderFilename(arg0, arg1);
    
    jsval jsret;
    do {
        if (ret) {
            js_proxy_t *p = jsb_get_native_proxy(ret);
            if (p) {
                jsret = OBJECT_TO_JSVAL(p->obj);
            } else {
                // create a new js obj of that class
                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::GLProgram>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            }
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
    JS_SET_RVAL(cx, vp, jsret);
    return JS_TRUE;

}


JSBool js_cocos2dx_CCGLProgram_createWithString(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
    if(argc != 2) {
        JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
        return JS_FALSE;
    }
    
    const char *arg0, *arg1;
    std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
    std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
    
    GLProgram* ret = new GLProgram();
    ret->initWithVertexShaderByteArray(arg0, arg1);
    
    jsval jsret;
    do {
        if (ret) {
            js_proxy_t *p = jsb_get_native_proxy(ret);
            if (p) {
                jsret = OBJECT_TO_JSVAL(p->obj);
            } else {
                // create a new js obj of that class
                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::GLProgram>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            }
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
    JS_SET_RVAL(cx, vp, jsret);
    return JS_TRUE;
    
}

JSBool js_cocos2dx_CCGLProgram_getProgram(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::GLProgram* cobj = (cocos2d::GLProgram *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
        GLuint ret = cobj->getProgram();
        JS_SET_RVAL(cx, vp, UINT_TO_JSVAL((uint32_t)ret));
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

#define js_cocos2dx_CCCamera_getXYZ(funcName) \
    JSBool ok = JS_TRUE;                                                                                                  \
	JSObject *obj = JS_THIS_OBJECT(cx, vp);                                                                               \
	js_proxy_t *proxy = jsb_get_js_proxy(obj);                                                                            \
	cocos2d::Camera* cobj = (cocos2d::Camera *)(proxy ? proxy->ptr : NULL);                                           \
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");                                                      \
	if (argc == 0) {                                                                                                      \
		float x;                                                                                                          \
		float y;                                                                                                          \
		float z;                                                                                                          \
		cobj->funcName(&x, &y, &z);                                                                                       \
        JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);                                                               \
                                                                                                                          \
        do                                                                                                                \
        {                                                                                                                 \
            if (NULL == tmp) break;                                                                                       \
                                                                                                                          \
            ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&  \
            JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&       \
            JS_DefineProperty(cx, tmp, "z", DOUBLE_TO_JSVAL(z), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);         \
                                                                                                                          \
            if (ok) {                                                                                                     \
                JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));                                                                \
                return JS_TRUE;                                                                                           \
            }                                                                                                             \
        } while (false);                                                                                                  \
                                                                                                                          \
		JS_SET_RVAL(cx, vp, JSVAL_NULL);                                                                                  \
		return JS_TRUE;                                                                                                   \
	}                                                                                                                     \
                                                                                                                          \
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);                                       \
	return JS_FALSE;


static JSBool js_cocos2dx_CCCamera_getCenterXYZ(JSContext *cx, uint32_t argc, jsval *vp)
{
    js_cocos2dx_CCCamera_getXYZ(getCenterXYZ)
}

static JSBool js_cocos2dx_CCCamera_getUpXYZ(JSContext *cx, uint32_t argc, jsval *vp)
{
    js_cocos2dx_CCCamera_getXYZ(getUpXYZ)
}

static JSBool js_cocos2dx_CCCamera_getEyeXYZ(JSContext *cx, uint32_t argc, jsval *vp)
{
    js_cocos2dx_CCCamera_getXYZ(getEyeXYZ)
}

void register_cocos2dx_js_extensions(JSContext* cx, JSObject* global)
{
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, global, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, global, "cc", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}

	JS_DefineFunction(cx, global, "__associateObjWithNative", js_cocos2dx_swap_native_object, 2, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, global, "__getPlatform", js_platform, 0, JSPROP_READONLY | JSPROP_PERMANENT);

	JSObject *tmpObj;

    JS_DefineFunction(cx, jsb_Node_prototype, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_Node_prototype, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_GLProgram_prototype, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_GLProgram_prototype, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "onExit", js_doNothing, 1, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "onEnter", js_doNothing, 1, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "onEnterTransitionDidFinish", js_doNothing, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "onExitTransitionDidStart", js_doNothing, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "init", js_doNothing, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "schedule", js_CCNode_schedule, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "scheduleOnce", js_CCNode_scheduleOnce, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "scheduleUpdateWithPriority", js_cocos2dx_CCNode_scheduleUpdateWithPriority, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "unscheduleUpdate", js_cocos2dx_CCNode_unscheduleUpdate, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "scheduleUpdate", js_cocos2dx_CCNode_scheduleUpdate, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "unschedule", js_CCNode_unschedule, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "unscheduleAllCallbacks", js_cocos2dx_CCNode_unscheduleAllSelectors, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Node_prototype, "setPosition", js_cocos2dx_CCNode_setPosition, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_GLProgram_prototype, "setUniformLocationF32", js_cocos2dx_CCGLProgram_setUniformLocationWith4f, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_GLProgram_prototype, "getProgram", js_cocos2dx_CCGLProgram_getProgram, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_Scheduler_prototype, "resumeTarget", js_cocos2dx_CCScheduler_resumeTarget, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "pauseTarget", js_cocos2dx_CCScheduler_pauseTarget, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "scheduleUpdateForTarget", js_CCScheduler_scheduleUpdateForTarget, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "unscheduleUpdateForTarget", js_CCScheduler_unscheduleUpdateForTarget, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "scheduleCallbackForTarget", js_CCScheduler_schedule, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "unscheduleCallbackForTarget", js_CCScheduler_unscheduleCallbackForTarget, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "unscheduleAllCallbacksForTarget", js_cocos2dx_CCScheduler_unscheduleAllSelectorsForTarget, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "unscheduleAllCallbacks", js_cocos2dx_CCScheduler_unscheduleAll, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "unscheduleAllCallbacksWithMinPriority", js_cocos2dx_CCScheduler_unscheduleAllCallbacksWithMinPriority, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Scheduler_prototype, "isTargetPaused", js_cocos2dx_CCScheduler_isTargetPaused, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    
    JS_DefineFunction(cx, jsb_Sprite_prototype, "setPosition", js_cocos2dx_CCSprite_setPosition, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_TMXLayer_prototype, "getTileFlagsAt", js_cocos2dx_CCTMXLayer_getTileFlagsAt, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_DrawNode_prototype, "drawPoly", js_cocos2dx_CCDrawNode_drawPolygon, 4, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_DrawNode_prototype, "setBlendFunc", js_cocos2dx_CCDrawNode_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_Texture2D_prototype, "setTexParameters", js_cocos2dx_CCTexture2D_setTexParameters, 4, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Menu_prototype, "alignItemsInRows", js_cocos2dx_CCMenu_alignItemsInRows, 1, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Menu_prototype, "alignItemsInColumns", js_cocos2dx_CCMenu_alignItemsInColumns, 1, JSPROP_ENUMERATE  | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_FileUtils_prototype, "setSearchResolutionsOrder", js_cocos2dx_CCFileUtils_setSearchResolutionsOrder, 1, JSPROP_PERMANENT );
    JS_DefineFunction(cx, jsb_FileUtils_prototype, "setSearchPaths", js_cocos2dx_CCFileUtils_setSearchPaths, 1, JSPROP_PERMANENT );
    JS_DefineFunction(cx, jsb_FileUtils_prototype, "getSearchPaths", js_cocos2dx_CCFileUtils_getSearchPaths, 0, JSPROP_PERMANENT );
    JS_DefineFunction(cx, jsb_FileUtils_prototype, "getSearchResolutionsOrder", js_cocos2dx_CCFileUtils_getSearchResolutionsOrder, 0, JSPROP_PERMANENT );
    JS_DefineFunction(cx, jsb_FileUtils_prototype, "getStringFromFile", js_cocos2dx_CCFileUtils_getStringFromFile, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_FileUtils_prototype, "createDictionaryWithContentsOfFile", js_cocos2dx_FileUtils_createDictionaryWithContentsOfFile, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_FileUtils_prototype, "getByteArrayFromFile", js_cocos2dx_CCFileUtils_getByteArrayFromFile, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.BezierBy; })()"));
    JS_DefineFunction(cx, tmpObj, "create", JSB_CCBezierBy_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.BezierTo; })()"));
    JS_DefineFunction(cx, tmpObj, "create", JSB_CCBezierTo_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);    
    
    tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.CardinalSplineBy; })()"));
    JS_DefineFunction(cx, tmpObj, "create", JSB_CCCardinalSplineBy_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.CardinalSplineTo; })()"));
    JS_DefineFunction(cx, tmpObj, "create", JSB_CCCardinalSplineTo_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.CatmullRomBy; })()"));
    JS_DefineFunction(cx, tmpObj, "create", JSB_CCCatmullRomBy_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.CatmullRomTo; })()"));
    JS_DefineFunction(cx, tmpObj, "create", JSB_CCCatmullRomTo_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_Sprite_prototype, "setBlendFunc", js_cocos2dx_CCSprite_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_SpriteBatchNode_prototype, "setBlendFunc", js_cocos2dx_CCSpriteBatchNode_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    //JS_DefineFunction(cx, jsb_MotionStreak_prototype, "setBlendFunc", js_cocos2dx_CCMotionStreak_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_AtlasNode_prototype, "setBlendFunc", js_cocos2dx_CCAtlasNode_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_ParticleBatchNode_prototype, "setBlendFunc", js_cocos2dx_CCParticleBatchNode_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_LayerColor_prototype, "setBlendFunc", js_cocos2dx_CCLayerColor_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_ParticleSystem_prototype, "setBlendFunc", js_cocos2dx_CCParticleSystem_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_Camera_prototype, "getCenter", js_cocos2dx_CCCamera_getCenterXYZ, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Camera_prototype, "getUp", js_cocos2dx_CCCamera_getUpXYZ, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_Camera_prototype, "getEye", js_cocos2dx_CCCamera_getEyeXYZ, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    

	JS_DefineFunction(cx, jsb_Action_prototype, "clone", js_cocos2dx_clone<cocos2d::Action>, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_Action_prototype, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_Action_prototype, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_Animation_prototype, "clone", js_cocos2dx_clone<cocos2d::Animation>, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_Animation_prototype, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_Animation_prototype, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_SpriteFrame_prototype, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_SpriteFrame_prototype, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_MenuItem_prototype, "setCallback", js_cocos2dx_CCMenuItem_setCallback, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_TMXLayer_prototype, "getTileFlagsAt", js_cocos2dx_CCTMXLayer_tileFlagsAt, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_TMXLayer_prototype, "getTiles", js_cocos2dx_CCTMXLayer_getTiles, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.Menu; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCMenu_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.MenuItem; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCMenuItem_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.MenuItemSprite; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCMenuItemSprite_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.MenuItemImage; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCMenuItemImage_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.MenuItemLabel; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCMenuItemLabel_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.MenuItemAtlasFont; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCMenuItemAtlasFont_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.MenuItemFont; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCMenuItemFont_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.MenuItemToggle; })()"));
	JS_DefineFunction(cx, tmpObj, "_create", js_cocos2dx_CCMenuItemToggle_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.Sequence; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCSequence_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.Spawn; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCSpawn_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.Animation; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCAnimation_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.LayerMultiplex; })()"));
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCLayerMultiplex_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
	JS_DefineFunction(cx, ns, "registerTargettedDelegate", js_cocos2dx_JSTouchDelegate_registerTargettedDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, ns, "registerStandardDelegate", js_cocos2dx_JSTouchDelegate_registerStandardDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "unregisterTouchDelegate", js_cocos2dx_JSTouchDelegate_unregisterTouchDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);

	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.CallFunc; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_callFunc, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    
	tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.GLProgram; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCGLProgram_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "createWithString", js_cocos2dx_CCGLProgram_createWithString, 1, JSPROP_READONLY | JSPROP_PERMANENT);

     tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return this; })()"));
    JS_DefineFunction(cx, tmpObj, "garbageCollect", js_forceGC, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, ns, "glEnableVertexAttribs", js_cocos2dx_ccGLEnableVertexAttribs, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pAdd", js_cocos2dx_ccpAdd, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pDistanceSQ", js_cocos2dx_ccpDistanceSQ, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pDistance", js_cocos2dx_ccpDistance, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pSub", js_cocos2dx_ccpSub, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pNeg", js_cocos2dx_ccpNeg, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pMult", js_cocos2dx_ccpMult, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pMidpoint", js_cocos2dx_ccpMidpoint, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pDot", js_cocos2dx_ccpDot, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pCross", js_cocos2dx_ccpCross, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pPerp", js_cocos2dx_ccpPerp, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pRPerp", js_cocos2dx_ccpRPerp, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pProject", js_cocos2dx_ccpProject, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pRotate", js_cocos2dx_ccpRotate, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pNormalize", js_cocos2dx_ccpNormalize, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pClamp", js_cocos2dx_ccpClamp, 2, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, ns, "pLengthSQ", js_cocos2dx_ccpLengthSQ, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "pLength", js_cocos2dx_ccpLength, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    // add constructor for Set
    JSFunction *ccSetConstructor = JS_NewFunction(cx, js_cocos2dx_CCSet_constructor, 0, JSPROP_READONLY | JSPROP_PERMANENT, NULL, "constructor");
    JSObject *ctor = JS_GetFunctionObject(ccSetConstructor);
    JS_LinkConstructorAndPrototype(cx, ctor, jsb_Set_prototype);
}
