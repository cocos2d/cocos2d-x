//
// Created on 2022/11/29.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "CCJsAudioEngine.h"
#include "CCLogOhos.h"

#include <vector>
#include <js_native_api.h>
#include <js_native_api_types.h>
NS_CC_BEGIN
napi_env CCJsAudioEngine::_env = nullptr;


napi_value CCJsAudioEngine::initJsAudioEngine(napi_env env, napi_value exports)
{
    OHOS_LOGD("initJsAudioEngine start!");
    _env = env;
    return 0;
}

void CCJsAudioEngine::preLoadBackgroundMusic(std::string& audioUri)
{
    OHOS_LOGD("JsAudioEngine preLoadBackMusic start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::preLoadBackMusic get global failed! status:%d", status);
        return;
    }
    napi_value preloadMusicFunc = getEngineFunc("preloadBackgroundMusic");
    if (preloadMusicFunc == nullptr) {
        return;
    }    
    napi_value argUri;
    napi_create_string_utf8(_env, audioUri.data(), audioUri.length() ,&argUri);
    napi_value args[] = {argUri};
    napi_value return_val;
    status = napi_call_function(_env, global, preloadMusicFunc, 1, args, &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::preLoadBackMusic napi_call_function failed! status:%d", status);
        return;
    }
}


void CCJsAudioEngine::playBackgroundMusic(std::string& audioUri, bool bLoop)
{
    playBackgroundMusic(audioUri, -1, bLoop);
}
void CCJsAudioEngine::playBackgroundMusic(std::string& audioUri, int seek, bool bLoop)
{
    OHOS_LOGD("JsAudioEngine playBackgroundMusic start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::playBackgroundMusic get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("playBackgroundMusic");
    if (playFunc == nullptr) {
        return;
    }

    std::vector<napi_value> args;

    napi_value argUri;
    napi_create_string_utf8(_env, audioUri.data(), audioUri.length() ,&argUri);
    args.push_back(argUri);
    napi_value argSeek;
    napi_create_int32(_env, seek, &argSeek);
    args.push_back(argSeek);
    napi_value argStartPlay;
    napi_create_int32(_env, 1, &argStartPlay);
    args.push_back(argStartPlay);
    napi_value argLoop;
    napi_get_boolean(_env, bLoop, &argLoop);
    args.push_back(argLoop);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::playBackgroundMusic napi_call_function failed! status:%d", status);
        return;
    } else {
        OHOS_LOGE("CCJsAudioEngine::playBackgroundMusic napi_call_function success! status:%d", status);
    }
    
}

void CCJsAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    OHOS_LOGD("JsAudioEngine stopBackgroundMusic start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::stopBackgroundMusic get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("stopBackgroundMusic");
    if (playFunc == nullptr) {
        return;
    }
    napi_value argRelease;
    napi_get_boolean(_env, bReleaseData, &argRelease);  

    napi_value args[1] = {argRelease};

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, 1, args, &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::stopBackgroundMusic napi_call_function failed! status:%d", status);
        return;
    }    
}

void CCJsAudioEngine::pauseBackgroundMusic()
{
    OHOS_LOGD("JsAudioEngine pauseBackgroundMusic start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::pauseBackgroundMusic get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("pauseBackgroundMusic");
    if (playFunc == nullptr) {
        return;
    }

    napi_value args[0] = {};

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, 0, args, &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::pauseBackgroundMusic napi_call_function failed! status:%d", status);
        return;
    }        
}

void CCJsAudioEngine::resumeBackgroundMusic()
{
   OHOS_LOGD("JsAudioEngine resumeBackgroundMusic start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::resumeBackgroundMusic get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("resumeBackgroundMusic");
    if (playFunc == nullptr) {
        return;
    }

    napi_value args[0] = {};

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, 0, args, &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::pauseBackgroundMusic napi_call_function failed! status:%d", status);
        return;
    }     
}

void CCJsAudioEngine::rewindBackgroundMusic()
{
    // seek 到 0 后重新播放。先暂停，然后重新播放
//    pauseBackgroundMusic();
    seekBackgroundMusic(0);
    std::string uri("hello");
    playBackgroundMusic(uri, 0);
}

void CCJsAudioEngine::seekBackgroundMusic(int seek)
{
    OHOS_LOGD("JsAudioEngine seekBackgroundMusic start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::seekBackgroundMusic get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("seekBackgroundMusic");
    if (playFunc == nullptr) {
        return;
    }
 
    napi_value argSeek;
    napi_create_int32(_env, seek, &argSeek);    
    napi_value args[1] = {argSeek};
 
    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, 1, args, &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::seekBackgroundMusic napi_call_function failed! status:%d", status);
        return;
    }     
}


float CCJsAudioEngine::getBackgroundMusicVolume()
{
    OHOS_LOGD("JsAudioEngine getBackgroundMusicVolume start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::getBackgroundMusicVolume get global failed! status:%d", status);
        return DEFAULT_VOLUME;
    }
    napi_value playFunc = getEngineFunc("getBackgroundVolume");
    if (playFunc == nullptr) {
        return DEFAULT_VOLUME;
    }

    napi_value args[0] = {};

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, 0, args, &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::getBackgroundMusicVolume napi_call_function failed! status:%d", status);
        return DEFAULT_VOLUME;
    }      
    double result;
    napi_get_value_double(_env, return_val, &result);
    return result;
}

void CCJsAudioEngine::setBackgroundMusicVolume(const float volume)
{
    OHOS_LOGD("JsAudioEngine setBackgroundMusicVolume start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::setBackgroundMusicVolume get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("setBackgroundVolume");
    if (playFunc == nullptr) {
        return;
    }

    napi_value napiVolume;
    napi_create_double(_env, volume, &napiVolume);
    napi_value args[1] = {napiVolume};

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, 1, args, &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::setBackgroundMusicVolume napi_call_function failed! status:%d", status);
        return;
    }        
}

float CCJsAudioEngine::getEffectsVolume()
{
    OHOS_LOGD("JsAudioEngine getEffectsVolume start!");
     napi_value global;
     napi_status status = napi_get_global(_env, &global);
     if (status != napi_ok) {
         OHOS_LOGE("CCJsAudioEngine::getEffectsVolume get global failed! status:%d", status);
         return DEFAULT_VOLUME;
     }
     napi_value playFunc = getEngineFunc("getEffectsVolume");
     if (playFunc == nullptr) {
         return DEFAULT_VOLUME;
     }
 
     napi_value args[0] = {};
 
     napi_value return_val;
     status = napi_call_function(_env, global, playFunc, 0, args, &return_val);
     if (status != napi_ok) {
         OHOS_LOGE("CCJsAudioEngine::getEffectsVolume napi_call_function failed! status:%d", status);
         return DEFAULT_VOLUME;
     }      
     double result;
     napi_get_value_double(_env, return_val, &result);
     return result;   
}

void CCJsAudioEngine::setEffectsVolume(float volume)
{
    OHOS_LOGD("JsAudioEngine setEffectsVolume start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::setEffectsVolume get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("setEffectsVolume");
    if (playFunc == nullptr) {
        return;
    }

    napi_value napiVolume;
    napi_create_double(_env, volume, &napiVolume);
    napi_value args[1] = {napiVolume};

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, 1, args, &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::setEffectsVolume napi_call_function failed! status:%d", status);
        return;
    }      
}

unsigned int CCJsAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
    OHOS_LOGD("JsAudioEngine playEffect start!");
    std::string audioUri(pszFilePath);
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::playEffect get global failed! status:%d", status);
        return 0;
    }
    napi_value playFunc = getEngineFunc("playEffect");
    if (playFunc == nullptr) {
        return 0;
    }
    
    std::vector<napi_value> args;
    napi_value argUri;
    napi_create_string_utf8(_env, audioUri.data(), audioUri.length() ,&argUri);
    napi_value argLoop;
    napi_get_boolean(_env, bLoop, &argLoop);    
    args.push_back(argUri);
    args.push_back(argLoop);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::playEffect napi_call_function failed! status:%d", status);
        return 0;
    } else {
        OHOS_LOGE("CCJsAudioEngine::playEffect napi_call_function success! status:%d", status);
    }
    unsigned int result;
    napi_get_value_uint32(_env, return_val, &result);
    return result;
}

void CCJsAudioEngine::pauseEffect(unsigned int nSoundId) 
{
    OHOS_LOGD("JsAudioEngine pauseEffect start! nSoundId:%d", nSoundId);
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::pauseEffect get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("pauseEffect");
    if (playFunc == nullptr) {
        return;
    }

    std::vector<napi_value> args;
    napi_value argSoundId;
    napi_create_uint32(_env, nSoundId, &argSoundId);
    args.push_back(argSoundId);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::pauseEffect napi_call_function failed! status:%d", status);
        return;
    }       
}

void CCJsAudioEngine::pauseAllEffects()
{
    OHOS_LOGD("JsAudioEngine pauseAllEffects start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::pauseAllEffects get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("pauseAllEffects");
    if (playFunc == nullptr) {
        return;
    }

    std::vector<napi_value> args;

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::pauseEffect napi_call_function failed! status:%d", status);
        return;
    }       
}

void CCJsAudioEngine::resumeEffect(unsigned int nSoundId)
{
    OHOS_LOGD("JsAudioEngine resumeEffect start! nSoundId:%d", nSoundId);
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::resumeEffect get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("resumeEffect");
    if (playFunc == nullptr) {
        return;
    }

    std::vector<napi_value> args;
    napi_value argSoundId;
    napi_create_uint32(_env, nSoundId, &argSoundId);
    args.push_back(argSoundId);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::pauseBackgroundMusic napi_call_function failed! status:%d", status);
        return;
    }         
}

void CCJsAudioEngine::resumeAllEffects()
{
    OHOS_LOGD("JsAudioEngine resumeAllEffects start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::resumeAllEffects get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("resumeAllEffects");
    if (playFunc == nullptr) {
        return;
    }

    std::vector<napi_value> args;

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::resumeAllEffects napi_call_function failed! status:%d", status);
        return;
    }      
}

void CCJsAudioEngine::stopEffect(unsigned int nSoundId)
{
    OHOS_LOGD("JsAudioEngine stopEffect start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::stopEffect get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("stopEffect");
    if (playFunc == nullptr) {
        return;
    }
    
    std::vector<napi_value> args;
    napi_value argSoundId;
    napi_create_uint32(_env, nSoundId, &argSoundId);
    args.push_back(argSoundId);

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::stopEffect napi_call_function failed! status:%d", status);
        return;
    }        
}

void CCJsAudioEngine::stopAllEffects()
{
    OHOS_LOGD("JsAudioEngine stopAllEffects start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::stopAllEffects get global failed! status:%d", status);
        return;
    }
    napi_value playFunc = getEngineFunc("stopAllEffects");
    if (playFunc == nullptr) {
        return;
    }
    
    std::vector<napi_value> args;

    napi_value return_val;
    status = napi_call_function(_env, global, playFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::stopAllEffects napi_call_function failed! status:%d", status);
        return;
    }      
}

void CCJsAudioEngine::preloadEffect(const char* pszFilePath)
{
    OHOS_LOGD("JsAudioEngine preLoadBackMusic start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::preLoadBackMusic get global failed! status:%d", status);
        return;
    }
    napi_value preloadEffectFunc = getEngineFunc("preloadEffect");
    if (preloadEffectFunc == nullptr) {
        return;
    }    
    
    std::vector<napi_value> args;
    std::string uri(pszFilePath);
    napi_value argUri;
    napi_create_string_utf8(_env, uri.data(), uri.length() ,&argUri);
    args.push_back(argUri);
    
    napi_value return_val;
    status = napi_call_function(_env, global, preloadEffectFunc, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::preLoadBackMusic napi_call_function failed! status:%d", status);
        return;
    }        
}

void CCJsAudioEngine::unloadEffect(const char* pszFilePath)
{
    OHOS_LOGD("JsAudioEngine unloadEffect start!");
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::unloadEffect get global failed! status:%d", status);
        return;
    }
    napi_value func = getEngineFunc("unloadEffect");
    if (func == nullptr) {
        return;
    }    
    
    std::vector<napi_value> args;
    std::string uri(pszFilePath);
    napi_value argUri;
    napi_create_string_utf8(_env, uri.data(), uri.length() ,&argUri);
    args.push_back(argUri);
    
    napi_value return_val;
    status = napi_call_function(_env, global, func, args.size(), args.data(), &return_val);
    if (status != napi_ok) {
        OHOS_LOGE("CCJsAudioEngine::unloadEffect napi_call_function failed! status:%d", status);
        return;
    }           
}

napi_value CCJsAudioEngine::getEngineFunc(const char* funcName)
{
    // Get the function named "AddTwo" on the global object
    napi_value global;
    napi_status status = napi_get_global(_env, &global);
    if (status != napi_ok) {
        OHOS_LOGE("%s get global failed!", funcName);
        return nullptr;
    }
    
    napi_value cocosNs;
    status = napi_get_named_property(_env, global, "ccCpp2Js", &cocosNs);
    if (status != napi_ok) {
        OHOS_LOGE("%s get cocosNs failed!", funcName);
        return nullptr;
    }        
    
    napi_value func;
    status = napi_get_named_property(_env, cocosNs, funcName, &func);
    if (status != napi_ok) {
        OHOS_LOGE("%s get func failed!", funcName);
        return nullptr;
    }
    
    napi_valuetype functype;
    napi_typeof(_env, func, &functype);
    if (functype != napi_function) {
        OHOS_LOGE("%s get func but is not a function", funcName);
        return nullptr;
    }    
    return func;
}

NS_CC_END