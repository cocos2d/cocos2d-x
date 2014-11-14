#ifndef COCOS2DX_SAMPLES_TESTLUA_PROJ_IOS_LUAOBJECTCBRIDGETEST_H
#define COCOS2DX_SAMPLES_TESTLUA_PROJ_IOS_LUAOBJECTCBRIDGETEST_H
#import <Foundation/Foundation.h>

@interface LuaObjectCBridgeTest : NSObject {
    int _scriptHandler;
}
+ (LuaObjectCBridgeTest*) getInstance;
+ (void) destroyInstance;

+ (void) registerScriptHandler:(NSDictionary *)dict;
+ (void) unregisterScriptHandler;

+ (int)  addTwoNumbers:(NSDictionary *)dict;
+ (void) callbackScriptHandler;

- (id) init;
@end

#endif  //  COCOS2DX_SAMPLES_TESTLUA_PROJ_IOS_LUAOBJECTCBRIDGETEST_H
