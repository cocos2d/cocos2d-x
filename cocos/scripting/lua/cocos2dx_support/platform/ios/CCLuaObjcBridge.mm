
#include "CCLuaObjcBridge.h"

extern "C"{
#include "tolua++.h"
#include "tolua_fix.h"
};

NS_CC_BEGIN

void CCLuaObjcBridge::luaopen_luaoc(lua_State *L)
{
    s_luaState = L;
    lua_newtable(L);
    lua_pushstring(L, "callStaticMethod");
    lua_pushcfunction(L, CCLuaObjcBridge::callObjcStaticMethod);
    lua_rawset(L, -3);
    lua_setglobal(L, "CCLuaObjcBridge");
}

/**
 className
 methodName
 args
 */
int CCLuaObjcBridge::callObjcStaticMethod(lua_State *L)
{
    if (lua_gettop(L) != 3 || !lua_isstring(L, -3) || !lua_isstring(L, -2))
    {
    	lua_pushboolean(L, 0);
    	lua_pushinteger(L, kCCLuaBridgeErrorInvalidParameters);
    	return 2;
    }
    
    const char *className  = lua_tostring(L, -3);
    const char *methodName = lua_tostring(L, -2);
    if (!className || !methodName)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kCCLuaBridgeErrorInvalidParameters);
        return 2;
    }
    
    Class targetClass = NSClassFromString([NSString stringWithCString:className encoding:NSUTF8StringEncoding]);
    if (!targetClass)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kCCLuaBridgeErrorClassNotFound);
        return 2;
    }
    
    SEL methodSel;
    bool hasArguments = lua_istable(L, -1);
    if (hasArguments)
    {
        NSString *methodName_ = [NSString stringWithCString:methodName encoding:NSUTF8StringEncoding];
        methodName_ = [NSString stringWithFormat:@"%@:", methodName_];
        methodSel = NSSelectorFromString(methodName_);
    }
    else
    {
        methodSel = NSSelectorFromString([NSString stringWithCString:methodName encoding:NSUTF8StringEncoding]);
    }
    if (methodSel == (SEL)0)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kCCLuaBridgeErrorMethodNotFound);
        return 2;
    }
    
    NSMethodSignature *methodSig = [targetClass methodSignatureForSelector:(SEL)methodSel];
    if (methodSig == nil)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kCCLuaBridgeErrorMethodSignature);
        return 2;
    }
    
    @try {
        NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:methodSig];
        [invocation setTarget:targetClass];
        [invocation setSelector:methodSel];
        NSUInteger returnLength = [methodSig methodReturnLength];
        const char *returnType = [methodSig methodReturnType];
        
        if (hasArguments)
        {
            NSObject *obj = (NSObject *)CCLuaObjcBridge::copyToObjc(L);
            /*
             // modify by guorui.chen
             NSMutableDictionary *dict = [NSMutableDictionary dictionary];
             lua_pushnil(L);
             while (lua_next(L, -2))
             {
             NSString *key = [NSString stringWithCString:lua_tostring(L, -2) encoding:NSUTF8StringEncoding];
             switch (lua_type(L, -1))
             {
             case LUA_TNUMBER:
             {
             [dict setObject:[NSNumber numberWithFloat:lua_tonumber(L, -1)] forKey:key];
             break;
             }
             
             case LUA_TBOOLEAN:
             {
             [dict setObject:[NSNumber numberWithBool:lua_toboolean(L, -1)] forKey:key];
             break;
             }
             
             case LUA_TSTRING:
             {
             [dict setObject:[NSString stringWithCString:lua_tostring(L, -1) encoding:NSUTF8StringEncoding]
             forKey:key];
             break;
             }
             
             case LUA_TFUNCTION:
             {
             int functionId = retainLuaFunction(L, -1, NULL);
             [dict setObject:[NSNumber numberWithInt:functionId] forKey:key];
             break;
             }
             
             case LUA_TTABLE:
             {
             const char* test = lua_tostring(L, -1);
             int l = 0;
             break;
             }
             }
             
             lua_pop(L, 1);
             }
             //*/
            if ([obj isKindOfClass:[NSArray class]]) {
                NSArray *array = (NSArray *)obj;
                NSString *methodName_ = [NSString stringWithCString:methodName encoding:NSUTF8StringEncoding];
                NSArray *argNames = [methodName_ componentsSeparatedByString:@":"];
                int argCount = [argNames count];
                if (argCount > [array count]) {
                    lua_pushboolean(L, 0);
                    lua_pushinteger(L, kCCLuaBridgeErrorInvalidParameters);
                    NSLog(@"Arguments are too much in %@~", methodName_);
                    return 2;
                } else if (argCount < [array count]) {
                    lua_pushboolean(L, 0);
                    lua_pushinteger(L, kCCLuaBridgeErrorInvalidParameters);
                    NSLog(@"Arguments are too less in %@~", methodName_);
                    return 2;
                }
                
                for(int i=0; i<argCount; ++i)
                {
                    NSObject *arg = [array objectAtIndex:i];
                    if([arg isKindOfClass:[NSNull class]])
                    {
                        arg = nil;
                    }
                    else if([arg isKindOfClass:[NSNumber class]])
                    {
                        NSNumber *number = (NSNumber *)arg;
                        const char *numberType = [number objCType];
                        if (strcmp(numberType, @encode(BOOL)) == 0)
                        {
                            bool value = [(NSNumber *)arg boolValue];
                            [invocation setArgument:&value atIndex:2+i];
                        }
                        else if (strcmp(numberType, @encode(int)) == 0)
                        {
                            int value = [(NSNumber *)arg intValue];
                            [invocation setArgument:&value atIndex:2+i];
                        }
                        else
                        {
                            float value = [(NSNumber *)arg floatValue];
                            [invocation setArgument:&value atIndex:2+i];
                        }
                        continue;
                    }
                    [invocation setArgument:&arg atIndex:2+i];
                }
                
                [invocation invoke];
                
            }
            else
            {
                [invocation setArgument:&obj atIndex:2];
                [invocation invoke];
            }
        }
        else
        {
            [invocation invoke];
        }
        
        lua_pushboolean(L, 1);
        if (returnLength > 0)
        {
            if (strcmp(returnType, "@") == 0)
            {
                id ret;
                [invocation getReturnValue:&ret];
                pushValue(L, ret);
            }
            else if (strcmp(returnType, "c") == 0) // BOOL
            {
                char ret;
                [invocation getReturnValue:&ret];
                lua_pushboolean(L, ret);
            }
            else if (strcmp(returnType, "i") == 0) // int
            {
                int ret;
                [invocation getReturnValue:&ret];
                lua_pushinteger(L, ret);
            }
            else if (strcmp(returnType, "f") == 0) // float
            {
                float ret;
                [invocation getReturnValue:&ret];
                lua_pushnumber(L, ret);
            }
            else
            {
                NSLog(@"not support return type = %s", returnType);
                lua_pushnil(L);
            }
        }
        else
        {
            lua_pushnil(L);
        }
        return 2;
    }
    @catch (NSException *exception)
    {
        NSLog(@"EXCEPTION THROW: %@", exception);
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kCCLuaBridgeErrorExceptionOccurred);
        return 2; 
    }
}

void* CCLuaObjcBridge::copyToObjc(lua_State *L)
{
    switch (lua_type(L, -1))
    {
        case LUA_TNIL:
        {
            return [[[NSNull alloc] init] autorelease];
        }
        case LUA_TNUMBER:
        {
            lua_Number number = lua_tonumber(L, -1);
            int value1 = (int)number;
            float value2 = (float)number;
            if (value1 == value2) {
                return [NSNumber numberWithInt:value1];
            } else {
                return [NSNumber numberWithFloat:value2];
            }
        }
            
        case LUA_TBOOLEAN:
        {
            return [NSNumber numberWithBool:lua_toboolean(L, -1)];
        }
            
        case LUA_TSTRING:
        {
            NSString *str = [NSString stringWithCString:lua_tostring(L, -1) encoding:NSUTF8StringEncoding];
            if ([str isEqualToString:@"__nil__"])
                return [[[NSNull alloc] init] autorelease];
            return str;
        }
            
        case LUA_TFUNCTION:
        {
            int functionId = retainLuaFunction(L, -1, NULL);
            return [NSNumber numberWithInt:functionId];
        }
            
        case LUA_TTABLE:
        {
            BOOL bDictionary = NO;
            
            lua_pushnil(L);  /* first key */
            while (!bDictionary && lua_next(L, -2)) {
                if (lua_type(L, -2) != LUA_TNUMBER) {
                    bDictionary = YES;
                    lua_pop(L, 2); // pop key and value off the stack
                }
                else {
                    lua_pop(L, 1);
                }
            }
            
            if (bDictionary) {
                return CCLuaObjcBridge::checkDictionary(L);
            }
            else {
                return CCLuaObjcBridge::checkArray(L);
            }
        }
    }
    return nil;
}

void* CCLuaObjcBridge::checkArray(lua_State *L)
{
    NSMutableArray *array = [NSMutableArray array];
    lua_pushnil(L);  /* first key */
    while (lua_next(L, -2)) {
        int index = lua_tonumber(L, -2) - 1;
        NSObject *value = (NSObject*)CCLuaObjcBridge::copyToObjc(L);
        [array insertObject:value atIndex:index];
        lua_pop(L, 1);
    }
    return array;
}

void* CCLuaObjcBridge::checkDictionary(lua_State *L)
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        NSString *key = [NSString stringWithCString:lua_tostring(L, -2) encoding:NSUTF8StringEncoding];
        NSObject *value = (NSObject*)CCLuaObjcBridge::copyToObjc(L);
        [dict setObject:value forKey:key];
        lua_pop(L, 1);
    }
    return dict;
}

void CCLuaObjcBridge::pushValue(lua_State *L, void *val)
{
    id oval = (id)val;
    if (oval == nil)
    {
        lua_pushnil(L);
    }
    else if ([oval isKindOfClass:[NSNumber class]])
    {
        NSNumber *number = (NSNumber *)oval;
        const char *numberType = [number objCType];
        if (strcmp(numberType, @encode(BOOL)) == 0)
        {
            lua_pushboolean(L, [number boolValue]);
        }
        else if (strcmp(numberType, @encode(int)) == 0)
        {
            lua_pushinteger(L, [number intValue]);
        }
        else
        {
            lua_pushnumber(L, [number floatValue]);
        }
    }
    else if ([oval isKindOfClass:[NSString class]])
    {
        lua_pushstring(L, [oval cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    else if ([oval isKindOfClass:[NSDictionary class]])
    {
        lua_newtable(L);
        
        for (id key in oval)
        {
            const char *key_ = [[NSString stringWithFormat:@"%@", key] cStringUsingEncoding:NSUTF8StringEncoding];
            lua_pushstring(L, key_);
            pushValue(L, [oval objectForKey:key]);
            lua_rawset(L, -3);
        }
        return;
    }
    else if ([oval isKindOfClass:[NSArray class]])
    {
        // added by guorui.chen
        lua_newtable(L);
        int count = [oval count];
        for (int i=0; i<count; ++i)
        {
            int len = lua_objlen(L, -1);
            pushValue(L, [oval objectAtIndex:i]);
            lua_rawseti(L, -2, len+1);
        }
        return;
    }
    else
    {
        lua_pushstring(L, [[NSString stringWithFormat:@"%@", oval] cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

NS_CC_END
