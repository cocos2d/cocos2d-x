/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

+(void) printLuaTableToDictionary:(NSDictionary *)dict{
    NSLog(@"lua to OC data is :%@",dict);
}

- (id)init
{
    _scriptHandler = 0;
    return self;
}

@end
