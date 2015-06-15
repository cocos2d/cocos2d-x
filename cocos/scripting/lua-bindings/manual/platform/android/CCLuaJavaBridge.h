#ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H
#define COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H

#include <jni.h>
#include <string>
#include <vector>

using namespace std;

extern "C" {
#include "lua.h"
}


#define LUAJ_ERR_OK                 0
#define LUAJ_ERR_TYPE_NOT_SUPPORT   (-1)
#define LUAJ_ERR_INVALID_SIGNATURES (-2)
#define LUAJ_ERR_METHOD_NOT_FOUND   (-3)
#define LUAJ_ERR_EXCEPTION_OCCURRED (-4)
#define LUAJ_ERR_VM_THREAD_DETACHED (-5)
#define LUAJ_ERR_VM_FAILURE         (-6)

#define LUAJ_REGISTRY_FUNCTION      "luaj_function_id"          // table[function] = id
#define LUAJ_REGISTRY_RETAIN        "luaj_function_id_retain"   // table[id] = retain count

/**
 * @addtogroup lua
 * @{
 */

/**@~english
 * Build a bridge between Java and Lua script.
 * This mechanism make Lua and Java call each other easily.
 * @~chinese 
 * 构建一个Java和Lua之间的桥梁。
 * 它使Java和Lua间可以方便地互相调用。
 */
class LuaJavaBridge
{
public:
    ///@cond
    /**@~english
     * Bind callStaticMethod of LuaJavaBridge to Lua.
     * In current mechanism,we could call LuaJavaBridge.callStaticMethod(className, methodName, args) in Lua directly.
     * Meanwhile the callStaticMethod of LuaObjcBridge binding function is wrapped in the luaj.lua
     * @~chinese d
     * 绑定LuaJavaBridge的callStaticMethod到Lua中。
     * 当前的机制下,我们可以在Lua脚本中直接调用LuaJavaBridge.callStaticMethod(className, methodName, args)
     * 同时,callStaticMethod绑定在luaj.lua还进行了一层封装。
     */
    static void luaopen_luaj(lua_State *L);
    ///@endcond

    /**@~english
     * Add a reference count for the Lua functionId(+1),and save this reference in the Lua table named luaj_function_id_retain.
     * 
     * @~chinese 
     * 增加functionId的引用计数(+1)，同时把这个值存在luaj_function_id_retain table中。
     * 
     * @param functionId @~english the reference id of Lua function.
     * @~chinese Lua函数的引用id。
     * @return @~english the reference count of the functionId if luaj_function_id_retain table exists and the corresponding value for functionId exists, otherwise return 0.
     *
     * @~chinese 如果在luaj_function_id_retain table中可以找到对应functionId的引用计数值,引用计数加1，返回更新后的引用计数,否则返回0。
     * 
     * @lua NA
     * @js NA
     */
    static int retainLuaFunctionById(int functionId);

    /**@~english
     * Release a reference count for the Lua functionId(-1).If the reference count is still greater than 0,save this reference in the Lua table named luaj_function_id_retain.
     * Otherwise, remove the refrence about this functionId in the luaj_function_id table and the luaj_function_id_retain table by set the corresponding value nil. 
     * 
     * @~chinese 
     * 。
     * 减少functionId对应的引用计数(-1)。如果更新后的引用计数还是大于0，那么更新luaj_function_id_retain中对应的值。否则,通过设置对应的值设置为nil移除关于functionId在luaj_function_id table和luaj_function_id_retain table的引用。
     * 
     * @param functionId @~english the reference id of Lua function.
     * @~chinese Lua函数的引用id。
     * @return @~english the retain count or 0.
     *
     * @~chinese 引用计数或0。
     * 
     * @lua NA
     * @js NA
     */
    static int releaseLuaFunctionById(int functionId);

    /**@~english
     * Call the Lua function corresponding to the functionId with the string pointer arg.
     * 
     * @~chinese 
     * 以arg为函数参数，调用functionId对应的Lua函数指针。
     * 
     * @param functionId @~english the reference id to the Lua function.
     * @~chinese Lua函数的引用id。
     * @param arg @~english the string pointer point to the argument.
     * @~chinese 作为函数参数的字符串指针。
     * @return @~english a number value returned from the Lua function when call sucessfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN,LUA_ERRMEM and LUA_ERRERR.
     *
     * @~chinese 调用成功，返回Lua函数的返回值。否则，返回-1或LUA_ERRRUN,LUA_ERRMEM LUA_ERRERR三个错误码其中一个的相反数。
     * 
     * @lua NA
     * @js NA
     */
    static int callLuaFunctionById(int functionId, const char *arg);

    /**@~english
     * Call a global Lua function named functionName with the string pointer arg.
     * 
     * @~chinese 
     * 以arg为函数参数，调用一个名字为functionName的Lua全局函数。
     * 
     * @param functionName @~english the name of global function.
     * @~chinese 全局函数名。
     * @param arg @~english the string pointer point to the argument.
     * @~chinese 作为函数参数的字符串指针。
     * @return @~english a number value returned frome the Lua function when call sucessfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN,LUA_ERRMEM and LUA_ERRERR.
     *
     * @~chinese 调用成功，返回Lua函数的返回值。否则，返回-1或LUA_ERRRUN,LUA_ERRMEM LUA_ERRERR三个错误码其中一个的相反数。
     * 
     * @lua NA
     * @js NA
     */
    static int callLuaGlobalFunction(const char *functionName, const char *arg);

private:
    typedef enum
    {
        TypeInvalid = -1,
        TypeVoid    = 0,
        TypeInteger = 1,
        TypeFloat   = 2,
        TypeBoolean = 3,
        TypeString  = 4,
        TypeVector  = 5,
        TypeFunction= 6,
    } ValueType;

    typedef vector<ValueType> ValueTypes;

    typedef union
    {
        int     intValue;
        float   floatValue;
        int     boolValue;
        string *stringValue;
    } ReturnValue;

    class CallInfo
    {
    public:
        CallInfo(const char *className, const char *methodName, const char *methodSig)
        : m_valid(false)
        , m_error(LUAJ_ERR_OK)
        , m_className(className)
        , m_methodName(methodName)
        , m_methodSig(methodSig)
        , m_returnType(TypeVoid)
        , m_argumentsCount(0)
        , m_retjs(NULL)
        , m_env(NULL)
        , m_classID(NULL)
        , m_methodID(NULL)
        {
            memset(&m_ret, 0, sizeof(m_ret));
        	m_valid = validateMethodSig() && getMethodInfo();
        }
    	~CallInfo(void);

        bool isValid(void) {
        	return m_valid;
        }

        int getErrorCode(void) {
        	return m_error;
        }

        JNIEnv *getEnv(void) {
        	return m_env;
        }

        int argumentTypeAtIndex(size_t index) {
        	return m_argumentsType.at(index);
        }

        bool execute(void);
        bool executeWithArgs(jvalue *args);
        int pushReturnValue(lua_State *L);


    private:
        bool 		m_valid;
        int 		m_error;

        string      m_className;
        string      m_methodName;
        string      m_methodSig;
        int         m_argumentsCount;
        ValueTypes  m_argumentsType;
        ValueType   m_returnType;

        ReturnValue m_ret;
        jstring     m_retjs;

        JNIEnv     *m_env;
        jclass      m_classID;
        jmethodID   m_methodID;

        bool validateMethodSig(void);
        bool getMethodInfo(void);
        ValueType checkType(const string& sig, size_t *pos);
    };

    static int callJavaStaticMethod(lua_State *L);
    static int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn);
    static int getMethodInfo(CallInfo *call, const char *className, const char *methodName, const char *paramCode);
    static int fetchArrayElements(lua_State *L, int index);
    static int callAndPushReturnValue(lua_State *L, CallInfo *call, jvalue *args);

    static lua_State *s_luaState;
    static int        s_newFunctionId;
};

// end group
/// @}
#endif //COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H
