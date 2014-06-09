
#include "CCLuaJavaBridge.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#define  LOG_TAG    "luajc"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {
#include "tolua_fix.h"
}

inline string jString2stdString(JNIEnv* env, jstring jstr)
{
	std::string ret;
	if(jstr){
		char* utf = (char*)env->GetStringUTFChars(jstr, 0);
		ret = utf;
		env->ReleaseStringUTFChars(jstr, utf);
	}
	else ret ="";
    
	return ret;
}

inline map<string, string> jHashMap2StdMap(JNIEnv* env, jobject jhashmap)
{
    std::map<std::string, std::string> retmap;
	do
	{
		if (jhashmap == NULL)
		{
			break;
		}
        
		if (env == NULL)
		{
			break;
		}
		static jclass mapClass = env->FindClass("java/util/HashMap");
		if (mapClass == NULL)
		{
			break;
		}
		static jmethodID mapClass_keySet = env->GetMethodID(mapClass, "keySet", "()Ljava/util/Set;");
		if (mapClass_keySet == NULL)
		{
			break;
		}
		static jmethodID mapClass_get = env->GetMethodID(mapClass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
		if (mapClass_get == NULL)
		{
			break;
		}
		jobject keyset =  env->CallObjectMethod(jhashmap, mapClass_keySet);
		if (keyset == NULL)
		{
			break;
		}
		static jclass setClass =  env->FindClass("java/util/Set");
		if (setClass == NULL)
		{
			break;
		}
		static jmethodID setClass_toArray = env->GetMethodID(setClass, "toArray", "()[Ljava/lang/Object;");
		if (setClass_toArray == NULL)
		{
			break;
		}
		jobjectArray keyarray = (jobjectArray)env->CallObjectMethod(keyset, setClass_toArray);
		if (keyarray == NULL)
		{
			break;
		}
		jint arraysize = env->GetArrayLength(keyarray);
		for(jint i = 0; i < arraysize; i++)
		{
			jstring key = (jstring)env->GetObjectArrayElement(keyarray, i);
			jstring value = (jstring)env->CallObjectMethod(jhashmap, mapClass_get, key);
			retmap.insert(pair<std::string, std::string>(jString2stdString(env,key), jString2stdString(env,value)));
			env->DeleteLocalRef(key);
			env->DeleteLocalRef(value);
		}
        env->DeleteLocalRef(keyset);
        env->DeleteLocalRef(keyarray);
	} while (0);
	return retmap;
}

inline vector<string> jVector2stdVector(JNIEnv* env, jobject jVector)
{
    vector<string> v;
    do {
        if (jVector == NULL)
		{
			break;
		}
        
		if (env == NULL)
		{
			break;
		}
		static jclass vectorClass = env->FindClass("java/util/Vector");
		if (vectorClass == NULL)
		{
			break;
		}
        static jmethodID vectorClass_toArray = env->GetMethodID(vectorClass, "toArray", "()[Ljava/lang/Object;");
		if (vectorClass_toArray == NULL)
		{
			break;
		}
		jobjectArray valuearray = (jobjectArray)env->CallObjectMethod(jVector, vectorClass_toArray);
		if (valuearray == NULL)
		{
			break;
		}
		jint arraysize = env->GetArrayLength(valuearray);
		for(jint i = 0; i < arraysize; i++)
		{
			jstring value = (jstring)env->GetObjectArrayElement(valuearray, i);
            v.push_back(jString2stdString(env, value));
			env->DeleteLocalRef(value);
		}
        
    } while (0);
	return v;
}

inline vector<string> jArray2stdVector(JNIEnv* env, jobject jArray)
{
    vector<string> v;
    do {
        if (jArray == NULL)
		{
			break;
		}
        
		if (env == NULL)
		{
			break;
		}
		static jclass arrayClass = env->FindClass("java/util/ArrayList");
		if (arrayClass == NULL)
		{
			break;
		}
        static jmethodID arrayClass_toArray = env->GetMethodID(arrayClass, "toArray", "()[Ljava/lang/Object;");
		if (arrayClass_toArray == NULL)
		{
			break;
		}
		jobjectArray valuearray = (jobjectArray)env->CallObjectMethod(jArray, arrayClass_toArray);
		if (valuearray == NULL)
		{
			break;
		}
		jint arraysize = env->GetArrayLength(valuearray);
		for(jint i = 0; i < arraysize; i++)
		{
			jstring value = (jstring)env->GetObjectArrayElement(valuearray, i);
            v.push_back(jString2stdString(env, value));
			env->DeleteLocalRef(value);
		}
        
    } while (0);
	return v;
}

CCLuaJavaBridge::CallInfo::~CallInfo(void)
{
    switch (m_returnType)
    {
        case TypeVoid:
        case TypeInteger:
        case TypeFloat:
        case TypeBoolean:
            break;            
        case TypeString:
            if (m_ret.stringValue)
                delete m_ret.stringValue;
            break;
        case TypeVector:
        case TypeArrayList:
        case TypeMap:
            if (m_ret.objectValue)
                m_env->DeleteLocalRef( m_ret.objectValue );
            break;
    }
}

bool CCLuaJavaBridge::CallInfo::execute(void)
{
	switch (m_returnType)
    {
        case TypeVoid:
        {
            m_env->CallStaticVoidMethod(m_classID, m_methodID);
            break;
        }
        case TypeInteger:
        {
            m_ret.intValue = m_env->CallStaticIntMethod(m_classID, m_methodID);
            break;
        }
        case TypeFloat:
        {
            m_ret.floatValue = m_env->CallStaticFloatMethod(m_classID, m_methodID);
            break;
        }
        case TypeBoolean:
        {
            m_ret.boolValue = m_env->CallStaticBooleanMethod(m_classID, m_methodID);
            break;
        }
        case TypeString:
        {
            m_retjs = (jstring)m_env->CallStaticObjectMethod(m_classID, m_methodID);
            const char *stringBuff = m_env->GetStringUTFChars(m_retjs, 0);
            m_ret.stringValue = new string(stringBuff);
            m_env->ReleaseStringUTFChars(m_retjs, stringBuff);
           break;
        }
        case TypeVector:
        case TypeArrayList:
        case TypeMap:
        {
            m_ret.objectValue = (jobject)m_env->CallStaticObjectMethod(m_classID, m_methodID);
            break;
        }
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


bool CCLuaJavaBridge::CallInfo::executeWithArgs(jvalue *args)
{
    switch (m_returnType)
     {
         case TypeVoid:
         {
             m_env->CallStaticVoidMethodA(m_classID, m_methodID, args);
             break;
         }
         case TypeInteger:
         {
             m_ret.intValue = m_env->CallStaticIntMethodA(m_classID, m_methodID, args);
             break;
         }
         case TypeFloat:
         {
             m_ret.floatValue = m_env->CallStaticFloatMethodA(m_classID, m_methodID, args);
             break;
         }
         case TypeBoolean:
         {
             m_ret.boolValue = m_env->CallStaticBooleanMethodA(m_classID, m_methodID, args);
             break;
         }
         case TypeString:
         {
        	 m_retjs = (jstring)m_env->CallStaticObjectMethodA(m_classID, m_methodID, args);
			 const char *stringBuff = m_env->GetStringUTFChars(m_retjs, 0);
			 m_ret.stringValue = new string(stringBuff);
			 m_env->ReleaseStringUTFChars(m_retjs, stringBuff);
            break;
         }
         case TypeVector:
         case TypeArrayList:
         case TypeMap:
         {
             m_ret.objectValue = (jobject)m_env->CallStaticObjectMethodA(m_classID, m_methodID, args);
             break;
         }
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

int CCLuaJavaBridge::CallInfo::pushReturnValue(lua_State *L)
{
	if (m_error != LUAJ_ERR_OK)
	{
		lua_pushinteger(L, m_error);
		return 1;
	}

	switch (m_returnType)
	{
		case TypeInteger:
        {
			lua_pushinteger(L, m_ret.intValue);
			return 1;
        }
		case TypeFloat:
        {
			lua_pushnumber(L, m_ret.floatValue);
			return 1;
        }
		case TypeBoolean:
        {
			lua_pushboolean(L, m_ret.boolValue);
			return 1;
        }
		case TypeString:
        {
			lua_pushstring(L, m_ret.stringValue->c_str());
			return 1;
        }
        case TypeVector:
        {
            lua_newtable(L);
            vector<string> vec = jVector2stdVector(m_env, m_ret.objectValue);
            for (int i=0; i<vec.size(); ++i)
            {
                string s = vec[i];
                int len = lua_objlen(L, -1);
                lua_pushstring(L, s.c_str());
                lua_rawseti(L, -2, len+1);
            }
            return 1;
        }
        case TypeArrayList:
        {
            lua_newtable(L);
            vector<string> vec = jArray2stdVector(m_env, m_ret.objectValue);
            for (int i=0; i<vec.size(); ++i)
            {
                string s = vec[i];
                int len = lua_objlen(L, -1);
                lua_pushstring(L, s.c_str());
                lua_rawseti(L, -2, len+1);
            }
            return 1;
        }
        case TypeMap:
        {
            lua_newtable(L);
            map<string, string> ma = jHashMap2StdMap(m_env, m_ret.objectValue);
            for(map<string, string>::iterator it=ma.begin(); it!=ma.end(); ++it)
            {
                lua_pushstring(L, it->first.c_str());
                lua_pushstring(L, it->second.c_str());
                lua_rawset(L, -3);
            }
            return 1;
        }
	}

	return 0;
}


bool CCLuaJavaBridge::CallInfo::validateMethodSig(void)
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
    	CCLuaJavaBridge::ValueType type = checkType(m_methodSig, &pos);
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

CCLuaJavaBridge::ValueType CCLuaJavaBridge::CallInfo::checkType(const string& sig, size_t *pos)
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
            else if (t.compare("Ljava/util/HashMap;") == 0)
            {
                *pos = pos2;
                return TypeMap;
            }
            else if (t.compare("Ljava/util/ArrayList;") == 0)
            {
                *pos = pos2;
                return TypeArrayList;
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


bool CCLuaJavaBridge::CallInfo::getMethodInfo(void)
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

    m_classID = m_env->FindClass(m_className.c_str());
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

lua_State *CCLuaJavaBridge::s_luaState = NULL;
int CCLuaJavaBridge::s_newFunctionId = 0;

void CCLuaJavaBridge::luaopen_luaj(lua_State *L)
{
	s_luaState = L;
    lua_newtable(L);
    lua_pushstring(L, "callStaticMethod");
    lua_pushcfunction(L, CCLuaJavaBridge::callJavaStaticMethod);
    lua_rawset(L, -3);
    lua_setglobal(L, "CCLuaJavaBridge");
}

inline string formatString(string format, ...)
{
    string result = format;
	va_list arg;
	int len;
	va_start( arg, format );
	len = vsnprintf( NULL, 0, result.c_str(), arg);
	va_end( arg );
	char* str = new char[ len + 1 ];
	va_start( arg, format );
	vsnprintf( str, len + 1, result.c_str(), arg );
	va_end( arg );
	result = str;
	delete str;
	return result;
}

string CCLuaJavaBridge::checkObj(lua_State *L)
{
    switch (lua_type(L, -1))
    {
        case LUA_TNUMBER:
        {
            lua_Number number = lua_tonumber(L, -1);
            int value1 = (int)number;
            float value2 = (float)number;
            if (value1 == value2) {
                return formatString("%d", value1);
            } else {
                return formatString("%f", value2);
            }
        }
            
        case LUA_TBOOLEAN:
        {
            if (lua_toboolean(L, -1) == 0)
                return "false";
            else
                return "true";
        }
            
        case LUA_TSTRING:
        {
            return lua_tostring(L, -1);
        }
            
        case LUA_TFUNCTION:
        {
            int funcId = retainLuaFunction(L, -1, NULL);
            return formatString("%d", funcId);
        }
            
        case LUA_TTABLE:
        {
            return lua_tostring(L, -1);
        }
    }
    
    return "";
}

jobject CCLuaJavaBridge::checkHashMap(lua_State *L)
{
    map<string, string> stdMap;
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        string key = lua_tostring(L, -2);
        LOGD("key-%s", key.c_str());
        stdMap[key] = checkObj(L);
        lua_pop(L, 1);
    }
    
    JNIEnv *env = 0;
    JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
    jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    switch (ret) {
        case JNI_OK:
            break;
            
        case JNI_EDETACHED :
            if (jvm->AttachCurrentThread(&env, NULL) < 0)
            {
                LOGD("Failed to get the environment using AttachCurrentThread()");
                return NULL;
            }
            break;
            
        case JNI_EVERSION :
        default :
            LOGD("Failed to get the environment using GetEnv()");
            return NULL;
    }

    PSJNIHelper::createHashMap();
    for(map<string, string>::iterator it = stdMap.begin(); it != stdMap.end(); ++it)
    {
        PSJNIHelper::pushHashMapElement(it->first, it->second);
    }
    
    return PSJNIHelper::getHashMap();
}

jobject CCLuaJavaBridge::checkVector(lua_State *L)
{
    vector<string> strings;
    lua_pushnil(L);  /* first key */
    while (lua_next(L, -2)) {
        int index = lua_tonumber(L, -2) - 1;
        strings.push_back(checkObj(L));
        lua_pop(L, 1);
    }
    
    JNIEnv *env = 0;
    JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
    jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    switch (ret) {
        case JNI_OK:
            break;
            
        case JNI_EDETACHED :
            if (jvm->AttachCurrentThread(&env, NULL) < 0)
            {
                LOGD("Failed to get the environment using AttachCurrentThread()");
                return NULL;
            }
            break;
            
        case JNI_EVERSION :
        default :
            LOGD("Failed to get the environment using GetEnv()");
            return NULL;
    }
    
    PSJNIHelper::createVector();
    for(vector<string>::iterator it = strings.begin(); it != strings.end(); ++it)
    {
        PSJNIHelper::pushVectorElement(*it);
    }
    
    return PSJNIHelper::getVector();
}

jobject CCLuaJavaBridge::checkArrayList(lua_State *L)
{
    vector<string> strings;
    lua_pushnil(L);  /* first key */
    while (lua_next(L, -2)) {
        int index = lua_tonumber(L, -2) - 1;
        string temp = checkObj(L);
        LOGD("%s", temp.c_str());
        strings.push_back(checkObj(L));
        lua_pop(L, 1);
    }
    
    JNIEnv *env = 0;
    JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
    jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    switch (ret) {
        case JNI_OK:
            break;
            
        case JNI_EDETACHED :
            if (jvm->AttachCurrentThread(&env, NULL) < 0)
            {
                LOGD("Failed to get the environment using AttachCurrentThread()");
                return NULL;
            }
            break;
            
        case JNI_EVERSION :
        default :
            LOGD("Failed to get the environment using GetEnv()");
            return NULL;
    }
    
    PSJNIHelper::createArrayList();
    for(vector<string>::iterator it = strings.begin(); it != strings.end(); ++it)
    {
        PSJNIHelper::pushArrayListElement(*it);
    }
    
    return PSJNIHelper::getArrayList();
}


/*
args:
    const char *className
    const char *methodName
    LUA_TABLE   args
    const char *sig
*/
int CCLuaJavaBridge::callJavaStaticMethod(lua_State *L)
{
    if (!lua_isstring(L, -4) || !lua_isstring(L, -3)  || !lua_istable(L, -2) || !lua_isstring(L, -1))
    {
    	lua_pushboolean(L, 0);
    	lua_pushinteger(L, LUAJ_ERR_INVALID_SIGNATURES);
    	return 2;
    }

    LOGD("%s", "CCLuaJavaBridge::callJavaStaticMethod(lua_State *L)");

    const char *className  = lua_tostring(L, -4);
    const char *methodName = lua_tostring(L, -3);
    const char *methodSig  = lua_tostring(L, -1);
    CallInfo call(className, methodName, methodSig);

    if (!call.isValid())
    {
    	LOGD("CCLuaJavaBridge::callJavaStaticMethod(\"%s\", \"%s\", args, \"%s\") CHECK FAILURE, ERROR CODE: %d",
    			className, methodName, methodSig, call.getErrorCode());

        lua_pushboolean(L, 0);
        lua_pushinteger(L, call.getErrorCode());
    	return 2;
    }

    // check args
    lua_pop(L, 1);													/* L: args */
    int count = fetchArrayElements(L, -1);                      	/* L: args e1 e2 e3 e4 ... */
    jvalue *args = NULL;
    if (count > 0)
    {
	    args = new jvalue[count];
	    for (int i = count - 1; i >= 0; --i)
	    {
	        int index = -count + i;
	        switch (call.argumentTypeAtIndex(i))
	        {
	            case TypeInteger:
	            	if (lua_isfunction(L, -1))
	            	{
	                    args[i].i = retainLuaFunction(L, -1, NULL);
	            	}
	            	else
	            	{
	            		args[i].i = (int)lua_tonumber(L, -1);
	            	}
	                break;

	            case TypeFloat:
	                args[i].f = lua_tonumber(L, -1);
	                break;

	            case TypeBoolean:
	                args[i].z = lua_toboolean(L, -1) != 0 ? JNI_TRUE : JNI_FALSE;
	                break;
                case TypeVector:
                    args[i].l = CCLuaJavaBridge::checkVector(L);
                    break;
                case TypeMap:
                    args[i].l = CCLuaJavaBridge::checkHashMap(L);
                    break;
                case TypeArrayList:
                    args[i].l = CCLuaJavaBridge::checkArrayList(L);
                    break;
	            case TypeString:
	            default:
	                args[i].l = call.getEnv()->NewStringUTF(lua_tostring(L, -1));
	                break;
	        }
            lua_pop(L, 1);
	    }
	    //lua_pop(L, count);                               			/* L: args */
    }

    bool success = args ? call.executeWithArgs(args) : call.execute();
    if (args) delete []args;

    if (!success)
    {
    	LOGD("CCLuaJavaBridge::callJavaStaticMethod(\"%s\", \"%s\", args, \"%s\") EXECUTE FAILURE, ERROR CODE: %d",
    			className, methodName, methodSig, call.getErrorCode());

    	lua_pushboolean(L, 0);
    	lua_pushinteger(L, call.getErrorCode());
    	return 2;
    }

	LOGD("CCLuaJavaBridge::callJavaStaticMethod(\"%s\", \"%s\", args, \"%s\") SUCCESS",
			className, methodName, methodSig);

	lua_pushboolean(L, 1);
	return 1 + call.pushReturnValue(L);
}

// increase lua function refernece counter, return counter
int CCLuaJavaBridge::retainLuaFunctionById(int functionId)
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
int CCLuaJavaBridge::releaseLuaFunctionById(int functionId)
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

int CCLuaJavaBridge::callLuaFunctionById(int functionId, const char *arg)
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
int CCLuaJavaBridge::callLuaGlobalFunction(const char *functionName, const char *arg)
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
int CCLuaJavaBridge::retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn)
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

int CCLuaJavaBridge::fetchArrayElements(lua_State *L, int index)
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

void CCLuaJavaBridge::PSJNIHelper::createHashMap(){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "createHashMap"
                                       , "()V"))
    {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
    }
    
}

jobject CCLuaJavaBridge::PSJNIHelper::getHashMap(){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "getHashMap"
                                       , "()Ljava/util/HashMap;"))
    {
		jobject jobj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);        
		t.env->DeleteLocalRef(t.classID);
		return jobj;
    }
    return NULL;
}

void CCLuaJavaBridge::PSJNIHelper::pushHashMapElement(string key, string value){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "pushHashMapElement"
                                       , "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring jkey = t.env->NewStringUTF(key.c_str());
        jstring jvalue = t.env->NewStringUTF(value.c_str());
        
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jkey, jvalue);
        
		t.env->DeleteLocalRef(jkey);
        t.env->DeleteLocalRef(jvalue);
		t.env->DeleteLocalRef(t.classID);
    }
}

void CCLuaJavaBridge::PSJNIHelper::createVector(){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "createVector"
                                       , "()V"))
    {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
    }
}

jobject CCLuaJavaBridge::PSJNIHelper::getVector(){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "getVector"
                                       , "()Ljava/util/Vector;"))
    {
		jobject jobj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		return jobj;
    }
    return NULL;
    
}

void CCLuaJavaBridge::PSJNIHelper::pushVectorElement(string value){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "pushVectorElement"
                                       , "(Ljava/lang/String;)V"))
    {
        jstring jvalue = t.env->NewStringUTF(value.c_str());
        
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jvalue);
        
        t.env->DeleteLocalRef(jvalue);
		t.env->DeleteLocalRef(t.classID);
    }
}

void CCLuaJavaBridge::PSJNIHelper::createArrayList(){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "createArrayList"
                                       , "()V"))
    {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
    }
}

jobject CCLuaJavaBridge::PSJNIHelper::getArrayList(){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "getArrayList"
                                       , "()Ljava/util/ArrayList;"))
    {
		jobject jobj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		return jobj;
    }
    return NULL;
    
}

void CCLuaJavaBridge::PSJNIHelper::pushArrayListElement(string value){
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/utils/PSJNIHelper"
                                       , "pushArrayListElement"
                                       , "(Ljava/lang/String;)V"))
    {
        jstring jvalue = t.env->NewStringUTF(value.c_str());
        
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jvalue);
        
        t.env->DeleteLocalRef(jvalue);
		t.env->DeleteLocalRef(t.classID);
    }
}
