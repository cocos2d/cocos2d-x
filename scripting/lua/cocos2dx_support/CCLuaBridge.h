/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org
 
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

#ifndef __LUA_BRIDGE_H_
#define __LUA_BRIDGE_H_

#include <string>
#include <map>
#include "CCLuaEngine.h"

extern "C" {
#include "lua.h"
}

using namespace std;

NS_CC_BEGIN

typedef enum {
    kCCLuaBridgeErrorOk                   = 0,
    kCCLuaBridgeErrorInvalidParameters    = -1,
    kCCLuaBridgeErrorClassNotFound        = -2,
    kCCLuaBridgeErrorMethodNotFound       = -3,
    kCCLuaBridgeErrorExceptionOccurred    = -4,
    kCCLuaBridgeErrorMethodSignature      = -5,
    kCCLuaBridgeErrorJavaVMError          = -6,
} CCLuaBridgeError;

#define LUA_BRIDGE_REGISTRY_FUNCTION    "lua_bridge_function_id"        // table[function] = id
#define LUA_BRIDGE_REGISTRY_RETAIN      "lua_bridge_function_id_retain" // table[id] = retain count
/**
 *  @js NA
 *  @lua NA
 */
class CCLuaBridge
{
public:
    static CCLuaStack *getStack(void);
    static int pushLuaFunctionById(int functionId);

    static int retainLuaFunctionById(int functionId);
    static int releaseLuaFunctionById(int functionId);
    
protected:
    static int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn);

    static lua_State *s_luaState;
    static int        s_newFunctionId;
};

NS_CC_END

#endif // __LUA_BRIDGE_H_
