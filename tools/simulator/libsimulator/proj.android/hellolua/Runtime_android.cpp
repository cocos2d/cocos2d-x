#include <jni.h>
#include <android/log.h>
#include "jni/JniHelper.h"
#include <string>
#include <vector>
using namespace std;
using namespace cocos2d;

string getIPAddress(int runtimeType)
{
	JniMethodInfo t;
    string IPAddress("");

    char* activityPath = nullptr;
    switch(runtimeType) {
    	case 1: {
    		activityPath = "org/cocos2dx/lua/AppActivity";
    		break;
    	}
    	case 2: {
    		activityPath = "org/cocos2dx/javascript/AppActivity";
    		break;
    	}
        default: {
            activityPath = "org/cocos2dx/lua/AppActivity";
            break;
        }
    }

    if (JniHelper::getStaticMethodInfo(t, activityPath, "getLocalIpAddress", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        IPAddress = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    return IPAddress;
}
