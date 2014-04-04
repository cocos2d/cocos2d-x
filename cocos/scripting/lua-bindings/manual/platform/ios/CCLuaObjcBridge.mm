
#include "CCLuaObjcBridge.h"
#include <Foundation/Foundation.h>

NS_CC_BEGIN

void LuaObjcBridge::luaopen_luaoc(lua_State *L)
{
    s_luaState = L;
    lua_newtable(L);
    lua_pushstring(L, "callStaticMethod");
    lua_pushcfunction(L, LuaObjcBridge::callObjcStaticMethod);
    lua_rawset(L, -3);
    lua_setglobal(L, "LuaObjcBridge");
}

/**
 className
 methodName
 args
 */
int LuaObjcBridge::callObjcStaticMethod(lua_State *L)
{
    if (lua_gettop(L) != 3 || !lua_isstring(L, -3) || !lua_isstring(L, -2))
    {
    	lua_pushboolean(L, 0);
    	lua_pushinteger(L, kLuaBridgeErrorInvalidParameters);
    	return 2;
    }
    
    const char *className  = lua_tostring(L, -3);
    const char *methodName = lua_tostring(L, -2);
    if (!className || !methodName)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kLuaBridgeErrorInvalidParameters);
        return 2;
    }
    
    Class targetClass = NSClassFromString([NSString stringWithCString:className encoding:NSUTF8StringEncoding]);
    if (!targetClass)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kLuaBridgeErrorClassNotFound);
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
        lua_pushinteger(L, kLuaBridgeErrorMethodNotFound);
        return 2;
    }
    
    NSMethodSignature *methodSig = [targetClass methodSignatureForSelector:(SEL)methodSel];
    if (methodSig == nil)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, kLuaBridgeErrorMethodSignature);
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
            NSMutableDictionary *dict = [NSMutableDictionary dictionary];
            lua_pushnil(L);
            while (lua_next(L, -2))
            {
                NSString *key = [NSString stringWithCString:lua_tostring(L, -2) encoding:NSUTF8StringEncoding];
                
                switch (lua_type(L, -1))
                {
                    case LUA_TNUMBER:
                        [dict setObject:[NSNumber numberWithFloat:lua_tonumber(L, -1)] forKey:key];
                        break;
                        
                    case LUA_TBOOLEAN:
                        [dict setObject:[NSNumber numberWithBool:lua_toboolean(L, -1)] forKey:key];
                        break;
                        
                    case LUA_TSTRING:
                        [dict setObject:[NSString stringWithCString:lua_tostring(L, -1) encoding:NSUTF8StringEncoding]
                                 forKey:key];
                        break;
                        
                    case LUA_TFUNCTION:
                        int functionId = retainLuaFunction(L, -1, NULL);
                        [dict setObject:[NSNumber numberWithInt:functionId] forKey:key];
                        break;
                }
                
                lua_pop(L, 1);
            }
            
            [invocation setArgument:&dict atIndex:2];
            [invocation invoke];
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
        lua_pushinteger(L, kLuaBridgeErrorExceptionOccurred);
        return 2; 
    }
}

void LuaObjcBridge::pushValue(lua_State *L, void *val)
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
    else
    {
        lua_pushstring(L, [[NSString stringWithFormat:@"%@", oval] cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

NS_CC_END
