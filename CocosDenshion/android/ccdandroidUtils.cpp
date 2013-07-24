#include "ccdandroidUtils.h"
#include "cocos2d.h"

#include <jni.h>
#include <android/log.h>
#include "jni/JniHelper.h"

USING_NS_CC;

namespace CocosDenshion {
    namespace android {

#define  I9100_MODEL "GT-I9100"
#define  LOG_TAG     "Device Model"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  CLASS_NAME   "org/cocos2dx/lib/Cocos2dxHelper"
#define  METHOD_NAME  "getDeviceModel"

        bool is_buggy_device(void) {
            JniMethodInfo methodInfo;
            jstring jstr;
            if (JniHelper::getStaticMethodInfo(methodInfo,
                                               CLASS_NAME,
                                               METHOD_NAME,
                                               "()Ljava/lang/String;")) {
                jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID,
                                                                       methodInfo.methodID);
            }
	
            const char* deviceModel = methodInfo.env->GetStringUTFChars(jstr, NULL);
            if (NULL == deviceModel) {
                return false;
            }

            LOGD("deviceModel = %s", deviceModel);
            methodInfo.env->ReleaseStringUTFChars(jstr, deviceModel);
            methodInfo.env->DeleteLocalRef(jstr);
    
            if (strcmp(I9100_MODEL, deviceModel) == 0) {
                LOGD("i9100 model\nSwitch to OpenSLES");
                return true;
            }

            return false;
        }

        std::string getFullPathWithoutAssetsPrefix(const char* pszFilename) {
            // Changing file path to full path
            std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(pszFilename);
            // Removing `assets` since it isn't needed for the API of playing sound.
            size_t pos = fullPath.find("assets/");
            if (pos == 0)
                {
                    fullPath = fullPath.substr(strlen("assets/"));
                }
            return fullPath;
        }
    }
}
