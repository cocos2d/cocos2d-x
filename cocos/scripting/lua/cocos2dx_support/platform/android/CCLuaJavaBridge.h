
#ifndef __LUA_JAVA_BRIDGE_H_
#define __LUA_JAVA_BRIDGE_H_

#include <jni.h>
#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"

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


class CCLuaJavaBridge
{
public:
    static void luaopen_luaj(lua_State *L);

    static int retainLuaFunctionById(int functionId);
    static int releaseLuaFunctionById(int functionId);

    static int callLuaFunctionById(int functionId, const char *arg);
    static int callLuaGlobalFunction(const char *functionName, const char *arg);
    
    // added by guorui.chen
    static jobject checkHashMap(lua_State *L);
    static jobject checkArrayList(lua_State *L);
    static jobject checkVector(lua_State *L);
    static string checkObj(lua_State *L);

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
        TypeMap     = 7,
        TypeArrayList = 8,
    } ValueType;

    typedef vector<ValueType> ValueTypes;

    typedef union
    {
        int     intValue;
        float   floatValue;
        int     boolValue;
        string *stringValue;
        jobject objectValue;
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
    
    class PSJNIHelper{
    public:
        static void createHashMap();
        static jobject getHashMap();
        static void pushHashMapElement(string key, string value);
        
        static void createVector();
        static jobject getVector();
        static void pushVectorElement(string value);
        
        static void createArrayList();
        static jobject getArrayList();
        static void pushArrayListElement(string value);
    };
};

#endif /* __LUA_JAVA_BRIDGE_H_ */
