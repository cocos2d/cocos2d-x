
#include "CCLuaJavaBridge.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#define  LOG_TAG    "luajc"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {
#include "tolua_fix.h"
}

LuaJavaBridge::CallInfo::~CallInfo(void)
{
	if (m_returnType == TypeString && m_ret.stringValue)
	{
		delete m_ret.stringValue;
	}
}

bool LuaJavaBridge::CallInfo::execute(void)
{
	switch (m_returnType)
    {
        case TypeVoid:
            m_env->CallStaticVoidMethod(m_classID, m_methodID);
            break;

        case TypeInteger:
            m_ret.intValue = m_env->CallStaticIntMethod(m_classID, m_methodID);
            break;

        case TypeFloat:
            m_ret.floatValue = m_env->CallStaticFloatMethod(m_classID, m_methodID);
            break;

        case TypeBoolean:
            m_ret.boolValue = m_env->CallStaticBooleanMethod(m_classID, m_methodID);
            break;

        case TypeString:
            m_retjs = (jstring)m_env->CallStaticObjectMethod(m_classID, m_methodID);
            const char *stringBuff = m_env->GetStringUTFChars(m_retjs, 0);
            m_ret.stringValue = new string(stringBuff);
            m_env->ReleaseStringUTFChars(m_retjs, stringBuff);
           break;
    }

	if (m_env->ExceptionCheck() == JNI_TRUE)
	{
		m_env->ExceptionDescribe();
		m_env->ExceptionClear();
		m_error = LUAJ_ERR_EXCEPTION_OCCURRED;
		return false;
	}

	return true;
}


bool LuaJavaBridge::CallInfo::executeWithArgs(jvalue *args)
{
    switch (m_returnType)
     {
         case TypeVoid:
             m_env->CallStaticVoidMethodA(m_classID, m_methodID, args);
             break;

         case TypeInteger:
             m_ret.intValue = m_env->CallStaticIntMethodA(m_classID, m_methodID, args);
             break;

         case TypeFloat:
             m_ret.floatValue = m_env->CallStaticFloatMethodA(m_classID, m_methodID, args);
             break;

         case TypeBoolean:
             m_ret.boolValue = m_env->CallStaticBooleanMethodA(m_classID, m_methodID, args);
             break;

         case TypeString:
        	 m_retjs = (jstring)m_env->CallStaticObjectMethodA(m_classID, m_methodID, args);
			 const char *stringBuff = m_env->GetStringUTFChars(m_retjs, 0);
			 m_ret.stringValue = new string(stringBuff);
			 m_env->ReleaseStringUTFChars(m_retjs, stringBuff);
            break;
     }

	if (m_env->ExceptionCheck() == JNI_TRUE)
	{
		m_env->ExceptionDescribe();
		m_env->ExceptionClear();
		m_error = LUAJ_ERR_EXCEPTION_OCCURRED;
		return false;
	}

	return true;
}

int LuaJavaBridge::CallInfo::pushReturnValue(lua_State *L)
{
	if (m_error != LUAJ_ERR_OK)
	{
		lua_pushinteger(L, m_error);
		return 1;
	}

	switch (m_returnType)
	{
		case TypeInteger:
			lua_pushinteger(L, m_ret.intValue);
			return 1;
		case TypeFloat:
			lua_pushnumber(L, m_ret.floatValue);
			return 1;
		case TypeBoolean:
			lua_pushboolean(L, m_ret.boolValue);
			return 1;
		case TypeString:
			lua_pushstring(L, m_ret.stringValue->c_str());
			return 1;
	}

	return 0;
}


bool LuaJavaBridge::CallInfo::validateMethodSig(void)
{
    size_t len = m_methodSig.length();
    if (len < 3 || m_methodSig[0] != '(') // min sig is "()V"
    {
    	m_error = LUAJ_ERR_INVALID_SIGNATURES;
    	return false;
	}

    size_t pos = 1;
    while (pos < len && m_methodSig[pos] != ')')
    {
    	LuaJavaBridge::ValueType type = checkType(m_methodSig, &pos);
    	if (type == TypeInvalid) return false;

		m_argumentsCount++;
		m_argumentsType.push_back(type);
        pos++;
    }

    if (pos >= len || m_methodSig[pos] != ')')
	{
    	m_error = LUAJ_ERR_INVALID_SIGNATURES;
    	return false;
	}

    pos++;
    m_returnType = checkType(m_methodSig, &pos);
    return true;
}

LuaJavaBridge::ValueType LuaJavaBridge::CallInfo::checkType(const string& sig, size_t *pos)
{
    switch (sig[*pos])
    {
        case 'I':
            return TypeInteger;
        case 'F':
            return TypeFloat;
        case 'Z':
            return TypeBoolean;
        case 'V':
        	return TypeVoid;
        case 'L':
            size_t pos2 = sig.find_first_of(';', *pos + 1);
            if (pos2 == string::npos)
            {
                m_error = LUAJ_ERR_INVALID_SIGNATURES;
                return TypeInvalid;
            }

            const string t = sig.substr(*pos, pos2 - *pos + 1);
            if (t.compare("Ljava/lang/String;") == 0)
            {
            	*pos = pos2;
                return TypeString;
            }
            else if (t.compare("Ljava/util/Vector;") == 0)
            {
            	*pos = pos2;
                return TypeVector;
            }
            else
            {
            	m_error = LUAJ_ERR_TYPE_NOT_SUPPORT;
                return TypeInvalid;
            }
    }

    m_error = LUAJ_ERR_TYPE_NOT_SUPPORT;
    return TypeInvalid;
}


bool LuaJavaBridge::CallInfo::getMethodInfo(void)
{
    m_methodID = 0;
    m_env = 0;

    JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
    jint ret = jvm->GetEnv((void**)&m_env, JNI_VERSION_1_4);
    switch (ret) {
        case JNI_OK:
            break;

        case JNI_EDETACHED :
            if (jvm->AttachCurrentThread(&m_env, NULL) < 0)
            {
                LOGD("%s", "Failed to get the environment using AttachCurrentThread()");
                m_error = LUAJ_ERR_VM_THREAD_DETACHED;
                return false;
            }
            break;

        case JNI_EVERSION :
        default :
            LOGD("%s", "Failed to get the environment using GetEnv()");
            m_error = LUAJ_ERR_VM_FAILURE;
            return false;
    }
    jstring _jstrClassName = m_env->NewStringUTF(m_className.c_str());
    m_classID = (jclass) m_env->CallObjectMethod(cocos2d::JniHelper::classloader,
                                                   cocos2d::JniHelper::loadclassMethod_methodID,
                                                   _jstrClassName);

    if (NULL == m_classID) {
        LOGD("Classloader failed to find class of %s", m_className.c_str());
    }

    m_env->DeleteLocalRef(_jstrClassName);
    m_methodID = m_env->GetStaticMethodID(m_classID, m_methodName.c_str(), m_methodSig.c_str());
    if (!m_methodID)
    {
        m_env->ExceptionClear();
        LOGD("Failed to find method id of %s.%s %s",
                m_className.c_str(),
                m_methodName.c_str(),
                m_methodSig.c_str());
        m_error = LUAJ_ERR_METHOD_NOT_FOUND;
        return false;
    }

    return true;
}

/* ---------------------------------------- */

lua_State *LuaJavaBridge::s_luaState = NULL;
int LuaJavaBridge::s_newFunctionId = 0;

void LuaJavaBridge::luaopen_luaj(lua_State *L)
{
	s_luaState = L;
    lua_newtable(L);
    lua_pushstring(L, "callStaticMethod");
    lua_pushcfunction(L, LuaJavaBridge::callJavaStaticMethod);
    lua_rawset(L, -3);
    lua_setglobal(L, "LuaJavaBridge");
}

/*
args:
    const char *className
    const char *methodName
    LUA_TABLE   args
    const char *sig
*/
int LuaJavaBridge::callJavaStaticMethod(lua_State *L)
{
    if (!lua_isstring(L, -4) || !lua_isstring(L, -3)  || !lua_istable(L, -2) || !lua_isstring(L, -1))
    {
    	lua_pushboolean(L, 0);
    	lua_pushinteger(L, LUAJ_ERR_INVALID_SIGNATURES);
    	return 2;
    }

    LOGD("%s", "LuaJavaBridge::callJavaStaticMethod(lua_State *L)");

    const char *className  = lua_tostring(L, -4);
    const char *methodName = lua_tostring(L, -3);
    const char *methodSig  = lua_tostring(L, -1);

    CallInfo call(className, methodName, methodSig);

    // check args
    lua_pop(L, 1);													/* L: args */
    int count = fetchArrayElements(L, -1);                      	/* L: args e1 e2 e3 e4 ... */
    jvalue *args = NULL;
    if (count > 0)
    {
	    args = new jvalue[count];
	    for (int i = 0; i < count; ++i)
	    {
	        int index = -count + i;
	        switch (call.argumentTypeAtIndex(i))
	        {
	            case TypeInteger:
	            	if (lua_isfunction(L, index))
	            	{
	                    args[i].i = retainLuaFunction(L, index, NULL);
	            	}
	            	else
	            	{
	            		args[i].i = (int)lua_tonumber(L, index);
	            	}
	                break;

	            case TypeFloat:
	                args[i].f = lua_tonumber(L, index);
	                break;

	            case TypeBoolean:
	                args[i].z = lua_toboolean(L, index) != 0 ? JNI_TRUE : JNI_FALSE;
	                break;

	            case TypeString:
	            default:
	                args[i].l = call.getEnv()->NewStringUTF(lua_tostring(L, index));
	                break;
	        }
	    }
	    lua_pop(L, count);                               			/* L: args */
    }

    bool success = args ? call.executeWithArgs(args) : call.execute();
    if (args) delete []args;

    if (!success)
    {
    	LOGD("LuaJavaBridge::callJavaStaticMethod(\"%s\", \"%s\", args, \"%s\") EXECUTE FAILURE, ERROR CODE: %d",
    			className, methodName, methodSig, call.getErrorCode());

    	lua_pushboolean(L, 0);
    	lua_pushinteger(L, call.getErrorCode());
    	return 2;
    }

	LOGD("LuaJavaBridge::callJavaStaticMethod(\"%s\", \"%s\", args, \"%s\") SUCCESS",
			className, methodName, methodSig);

	lua_pushboolean(L, 1);
	return 1 + call.pushReturnValue(L);
}

// increase lua function refernece counter, return counter
int LuaJavaBridge::retainLuaFunctionById(int functionId)
{
    lua_State *L = s_luaState;

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN);                    /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return 0;
    }

    // get counter
    lua_pushinteger(L, functionId);                             /* L: id_r id */
    lua_rawget(L, -2);                                          /* L: id_r r */
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        lua_pop(L, 2);
        return 0;
    }

    // increase counter
    int retainCount = lua_tonumber(L, -1);
    retainCount++;
    lua_pop(L, 1);                                              /* L: id_r */
    lua_pushinteger(L, functionId);                             /* L: id_r id */
    lua_pushinteger(L, retainCount);                            /* L: id_r id r */
    lua_rawset(L, -3);                            /* id_r[id] = r, L: id_r */
    lua_pop(L, 1);

    LOGD("luajretainLuaFunctionById(%d) - retain count = %d", functionId, retainCount);

    return retainCount;
}

// decrease lua function reference counter, return counter
int LuaJavaBridge::releaseLuaFunctionById(int functionId)
{
    lua_State *L = s_luaState;
                                                                /* L: */
    lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);                  /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        LOGD("%s", "luajreleaseLuaFunctionById() - LUAJ_REGISTRY_FUNCTION not exists");
        return 0;
    }

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN);                    /* L: f_id key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 2);
        LOGD("%s", "luajreleaseLuaFunctionById() - LUAJ_REGISTRY_RETAIN not exists");
        return 0;
    }

    lua_pushinteger(L, functionId);                             /* L: f_id id_r id */
    lua_rawget(L, -2);                                          /* L: f_id id_r r */
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        lua_pop(L, 3);
        LOGD("luajreleaseLuaFunctionById() - function id %d not found", functionId);
        return 0;
    }

    int retainCount = lua_tonumber(L, -1);
    retainCount--;

    if (retainCount > 0)
    {
        // update counter
        lua_pop(L, 1);                                          /* L: f_id id_r */
        lua_pushinteger(L, functionId);                         /* L: f_id id_r id */
        lua_pushinteger(L, retainCount);                        /* L: f_id id_r id r */
        lua_rawset(L, -3);                        /* id_r[id] = r, L: f_id id_r */
        lua_pop(L, 2);
        LOGD("luajreleaseLuaFunctionById() - function id %d retain count = %d", functionId, retainCount);
        return retainCount;
    }

    // remove lua function reference
    lua_pop(L, 1);                                              /* L: f_id id_r */
    lua_pushinteger(L, functionId);                             /* L: f_id id_r id */
    lua_pushnil(L);                                             /* L: f_id id_r id nil */
    lua_rawset(L, -3);                          /* id_r[id] = nil, L: f_id id_r */

    lua_pop(L, 1);                                              /* L: f_id */
    lua_pushnil(L);                                             /* L: f_id nil */
    while (lua_next(L, -2) != 0)                                /* L: f_id f id */
    {
        int value = lua_tonumber(L, -1);
        lua_pop(L, 1);                                          /* L: f_id f */
        if (value == functionId)
        {
            lua_pushnil(L);                                     /* L: f_id f nil */
            lua_rawset(L, -3);                   /* f_id[f] = nil, L: f_id */
            break;
        }
    }                                                           /* L: f_id */

    lua_pop(L, 1);
    LOGD("luajreleaseLuaFunctionById() - function id %d released", functionId);
    return 0;
}

int LuaJavaBridge::callLuaFunctionById(int functionId, const char *arg)
{
    lua_State *L = s_luaState;
    int top = lua_gettop(L);
                                                                /* L: */
    lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);                  /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return -1;
    }

    lua_pushnil(L);                                             /* L: f_id nil */
    while (lua_next(L, -2) != 0)                                /* L: f_id f id */
    {
        int value = lua_tonumber(L, -1);
        lua_pop(L, 1);                                          /* L: f_id f */
        if (value == functionId)
        {
            lua_pushstring(L, arg);                             /* L: f_id f arg */
            int ok = lua_pcall(L, 1, 1, 0);                     /* L: f_id ret|err */
            int ret;
            if (ok == 0)
            {
                ret = lua_tonumber(L, -1);
            }
            else
            {
                ret = -ok;
            }

            lua_settop(L, top);
            return ret;
        }
    }                                                           /* L: f_id */

    lua_settop(L, top);
    return -1;
}

// call lua global function
int LuaJavaBridge::callLuaGlobalFunction(const char *functionName, const char *arg)
{
    lua_State *L = s_luaState;

    int ret = -1;
    int top = lua_gettop(L);

    lua_getglobal(L, functionName);
    if (lua_isfunction(L, -1))
    {
        lua_pushstring(L, arg);
        int ok = lua_pcall(L, 1, 1, 0);
        if (ok == 0)
        {
            ret = lua_tonumber(L, -1);
        }
        else
        {
            ret = -ok;
        }
    }

    lua_settop(L, top);
    return ret;
}

// ----------------------------------------

// increase lua function reference counter, return functionId
int LuaJavaBridge::retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn)
{
                                                                /* L: f ... */
    lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);                  /* L: f ... key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f ... f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN);                    /* L: f ... f_id key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f ... f_id id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, LUAJ_REGISTRY_RETAIN);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }

    // get function id
    lua_pushvalue(L, functionIndex - 2);                        /* L: f ... f_id id_r f */
    lua_rawget(L, -3);                                          /* L: f ... f_id id_r id */

    int functionId;
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        // first retain, create new id
        lua_pop(L, 1);                                          /* L: f ... f_id id_r */
        s_newFunctionId++;
        functionId = s_newFunctionId;

        lua_pushvalue(L, functionIndex - 2);                    /* L: f ... f_id id_r f */
        lua_pushinteger(L, functionId);                         /* L: f ... f_id id_r f id */
        lua_rawset(L, -4);                        /* f_id[f] = id, L: f ... f_id id_r */
        lua_pushinteger(L, functionId);                         /* L: f ... f_id id_r id */
    }
    else
    {
        functionId = lua_tonumber(L, -1);
    }

    // get function retain
    lua_pushvalue(L, -1);                                       /* L: f ... f_id id_r id id */
    lua_rawget(L, -3);                                          /* L: f ... f_id id_r id r */
    int retainCount = 1;
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        // first retain, set retain count = 1
        lua_pop(L, 1);
        lua_pushinteger(L, retainCount);
    }
    else
    {
        // add retain count
        retainCount = lua_tonumber(L, -1);
        retainCount++;
        lua_pop(L, 1);
        lua_pushinteger(L, retainCount);
    }

    lua_rawset(L, -3);                            /* id_r[id] = r, L: f ... f_id id_r */
    lua_pop(L, 2);                                              /* L: f ... */

    if (retainCountReturn) *retainCountReturn = retainCount;
    return functionId;
}

int LuaJavaBridge::fetchArrayElements(lua_State *L, int index)
{
    int count = 0;
    do
    {
        lua_rawgeti(L, index - count, count + 1);
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            break;
        }
        ++count;
    } while (1);
    return count;
}
