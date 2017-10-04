#include <jni.h>
#include <android/log.h>
#include "jni/JniHelper.h"
#include <string>
#include <vector>
using namespace std;
using namespace cocos2d;

static const char* className = "org/cocos2dx/lua/AppActivity";

void setActivityPathForAndroid(const std::string& path)
{
    className = path;
}

string getIPAddress()
{
    return JniHelper::callStaticMethod<std::string>(className, "getLocalIpAddress");
}
