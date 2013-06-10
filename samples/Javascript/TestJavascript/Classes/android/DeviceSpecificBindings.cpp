#include "DeviceSpecificBindings.h"
#include "TestHelperJNI.h"

class SwitcherCallbackLayer : public CCLayer
{
public:
    SwitcherCallbackLayer(void);
    ~SwitcherCallbackLayer();
    
    void switcherCallback(CCObject* pSender);
};

SwitcherCallbackLayer::SwitcherCallbackLayer() {
}

SwitcherCallbackLayer::~SwitcherCallbackLayer() {
}

void closeActivityJNI();
void SwitcherCallbackLayer:: switcherCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();
    closeActivityJNI();
}

/* 
 * For TestCpp. Unused for TestJavascript
 */

void switchAndKillActivity() {
    SwitcherCallbackLayer *t = new SwitcherCallbackLayer();
    t->autorelease();
    CCScene *sc = CCScene::create();
    CCLayer *l = CCLayer::create();
    CCMenuItemFont *item = CCMenuItemFont::create("switch activities", t, 
						  menu_selector(SwitcherCallbackLayer::switcherCallback) );
    CCMenu *m = CCMenu::create(item, NULL);
    l->addChild(m);
    sc->addChild(l);
    CCDirector::sharedDirector()->runWithScene(sc);
}


JSBool js_cocos2dx_switchActivity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
    SwitcherCallbackLayer *t = new SwitcherCallbackLayer();
    t->autorelease();
    t->switcherCallback(NULL);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void registerDeviceSpeceficTests(JSContext* cx, JSObject* global)
{
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
    
	JS_DefineFunction(cx, ns, "switchAndKillActivity", js_cocos2dx_switchActivity, 
			  1, JSPROP_READONLY | JSPROP_PERMANENT);
}
