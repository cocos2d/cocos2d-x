#ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H
#define COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H

#include <jni.h>
#include <string>
#include <vector>
#include "cocos2d.h"

using namespace std;

extern "C" {
#include "lua.h"
}

using namespace cocos2d;

#define LUAJ_ERR_OK                 0
#define LUAJ_ERR_TYPE_NOT_SUPPORT   (-1)
#define LUAJ_ERR_INVALID_SIGNATURES (-2)
#define LUAJ_ERR_METHOD_NOT_FOUND   (-3)
#define LUAJ_ERR_EXCEPTION_OCCURRED (-4)
#define LUAJ_ERR_VM_THREAD_DETACHED (-5)
#define LUAJ_ERR_VM_FAILURE         (-6)

#define LUAJ_REGISTRY_FUNCTION      "luaj_function_id"          // table[function] = id
#define LUAJ_REGISTRY_RETAIN        "luaj_function_id_retain"   // table[id] = retain count


class LuaJavaBridge
{
public:
    static void luaopen_luaj(lua_State *L);

    static int retainLuaFunctionById(int functionId);
    static int releaseLuaFunctionById(int functionId);

    static int callLuaFunctionById(int functionId, const char *arg);
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

#endif //COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_PLATFORM_ANDROID_LUA_JAVA_BRIDGE_H
