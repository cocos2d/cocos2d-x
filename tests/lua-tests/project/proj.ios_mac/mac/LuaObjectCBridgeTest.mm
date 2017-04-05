#import "LuaObjectCBridgeTest.h"

#include "cocos2d.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/CCLuaBridge.h"

using namespace cocos2d;

@implementation LuaObjectCBridgeTest

static LuaObjectCBridgeTest* s_instance = nil;

+ (LuaObjectCBridgeTest*) getInstance
{
    if (!s_instance)
    {
        s_instance = [LuaObjectCBridgeTest alloc];
        [s_instance init];
    }
    
    return s_instance;
}

+ (void) destroyInstance
{
    [s_instance release];
}

- (void) setScriptHandler:(int)scriptHandler
{
    if (_scriptHandler)
    {
        LuaBridge::releaseLuaFunctionById(_scriptHandler);
        _scriptHandler = 0;
    }
    _scriptHandler = scriptHandler;
}

- (int) getScriptHandler
{
    return _scriptHandler;
}


+(void) registerScriptHandler:(NSDictionary *)dict
{
    [[LuaObjectCBridgeTest getInstance] setScriptHandler:[[dict objectForKey:@"scriptHandler"] intValue]];
}


+ (void) unregisterScriptHandler
{
    [[LuaObjectCBridgeTest getInstance] setScriptHandler:0];
}

+ (int)  addTwoNumbers:(NSDictionary *)dict
{
    int num1 = [[dict objectForKey:@"num1"] intValue];
    int num2 = [[dict objectForKey:@"num2"] intValue];
    
    return num1 + num2;
}

+ (void) callbackScriptHandler
{
    int scriptHandler = [[LuaObjectCBridgeTest getInstance] getScriptHandler];
    if (scriptHandler)
    {
        LuaBridge::pushLuaFunctionById(scriptHandler);
        LuaStack *stack = LuaBridge::getStack();
        stack->pushString("success");
        stack->executeFunction(1);
    }
}

- (id)init
{
    _scriptHandler = 0;
    return self;
}

@end
