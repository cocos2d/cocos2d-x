/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.

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

#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxEngineDataManager.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/CCFileUtils.h"
#include "platform/android/CCApplication-android.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "renderer/CCRenderer.h"
#include "2d/CCParticleSystem.h"
#include "2d/CCActionManager.h"
#include "audio/include/AudioEngine.h"
#include <android/log.h>
#include <limits.h>
#include <sstream>

#define LOG_TAG    "EngineDataManager.cpp"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define EDM_DEBUG 0

#define JNI_FUNC_PREFIX(func) Java_org_cocos2dx_lib_Cocos2dxEngineDataManager_##func

using namespace cocos2d;

#if EDM_DEBUG
#include "platform/android/jni/ProcessCpuTracker.h"

namespace {

std::string& trim(std::string& s)
{
    if (s.empty())
        return s;

    s.erase(0, s.find_first_not_of(" \t"));
    s.erase(s.find_last_not_of(" \t") + 1);
    return s;
}

void split(const std::string& s, const std::string& delim, std::vector<std::string>* ret)
{
    size_t last = 0;
    size_t index = s.find(delim, last);
    while (index != std::string::npos)
    {
        ret->push_back(s.substr(last, index - last));
        last = index + delim.length();
        index = s.find(delim, last);
    }
    if (index - last > 0)
    {
        ret->push_back(s.substr(last, index - last));
    }
}

std::string& deleteChar(std::string& s, const char* toDeleteChar)
{
    if (s.empty())
        return s;

    size_t pos = s.find_first_of(toDeleteChar);
    while (pos != std::string::npos)
    {
        s.erase(pos, 1);
        pos = s.find_first_of(toDeleteChar);
    }

    return s;
}

bool getValueFromMap(const std::map<std::string, std::string>& m, const std::string& key, std::string* outValue)
{
    if (m.empty() || outValue == NULL)
        return false;

    std::map<std::string, std::string>::const_iterator iter = m.find(key);
    if (iter != m.end())
    {
        *outValue = iter->second;
        return true;
    }
    outValue->clear();
    return false;
}

std::string& toLowercase(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

} // namespace {

#endif

namespace {

const char* ENGINE_DATA_MANAGER_VERSION = "5";
const char* CLASS_NAME_ENGINE_DATA_MANAGER = "org/cocos2dx/lib/Cocos2dxEngineDataManager";
const char* CLASS_NAME_RENDERER = "org/cocos2dx/lib/Cocos2dxRenderer";

bool _isInitialized = false;
bool _isSupported = false;
bool _isFirstSetNextScene = true;
bool _isReplaceScene = false;
bool _isReadFile = false;
bool _isInBackground = false;

uint32_t _drawCountInterval = 0;
const uint32_t _drawCountThreshold = 30;

#if EDM_DEBUG
uint32_t _printCpuGpuLevelCounter = 0;
uint32_t _printCpuGpuLevelThreshold = UINT_MAX; // Print cpu/gpu level in every 60 frames even if levels aren't changed.

uint32_t _printCpuUsageCounter = 0;
uint32_t _printCpuUsageThreshold = UINT_MAX;

ProcessCpuTracker _cpuTracker;
bool _forceEnableOptimization = false;
#endif

/* last time frame lost cycle was calculated */
std::chrono::steady_clock::time_point _lastContinuousFrameLostUpdate;
std::chrono::steady_clock::time_point _lastFrameLost100msUpdate;

/* last time low fps cycle was calculated */
std::chrono::steady_clock::time_point _lastLowFpsUpdate;

int _continuousFrameLostCycle = 5000;
int _continuousFrameLostThreshold = 3;
int _continuousFrameLostCount = 0;
int _frameLostCounter = 0;

int _lowFpsCycle = 1000;
float _lowFpsThreshold = 0.3f;
int _lowFpsCounter = 0;

int _oldCpuLevel = -1;
int _oldGpuLevel = -1;

int _oldCpuLevelMulFactor = -1;
int _oldGpuLevelMulFactor = -1;

float _levelDecreaseThreshold = 0.2f;

float _cpuFpsFactor = 1.0f;
float _gpuFpsFactor = 1.0f;
bool _isFpsChanged = false;
float _oldRealFps = 60.0f;

uint32_t _lowFpsCheckMode = 0; // 0: Continuous mode, 1: Average mode
float _lowRealFpsThreshold = 0.5f; // Unit: percentage (0 ~ 1)
std::chrono::steady_clock::time_point _lastTimeNotifyLevelByLowFps; // Only used in continuous mode 
float _notifyLevelByLowFpsThreshold = 0.5f; // Unit: seconds, only used in continuous mode 
int _minValueOfNotifyCpuLevelByLowFps = 4;
int _minValueOfNotifyGpuLevelByLowFps = 5;
uint32_t _continuousLowRealFpsCount = 0; // Only used in continuous mode 
uint32_t _continuousLowRealFpsThreshold = 1; // Only used in continuous mode
uint32_t _calculateAvgFpsCount = 0; // Only used in average mode
float _calculateAvgFpsSum = 0.0f; // Only used in average mode
std::chrono::steady_clock::time_point _lastTimeCalculateAvgFps; // Only used in average mode

const float DEFAULT_INTERVAL = (1.0f / 60.0f);
// The final animation interval which is used in 'onDrawFrame'
float _animationInterval = DEFAULT_INTERVAL;

// The animation interval set by engine.
// It could be updated by 'Director::getInstance()->setAnimationInterval(value);'
// or 'Director::getInstance()->resume();', 'Director::getInstance()->startAnimation();'.
float _animationIntervalByEngineOrGame = DEFAULT_INTERVAL;

// The animation interval set by system.
// System could set this variable through EngineDataManager to override the default FPS set by developer.
// By using this variable, system will be able to control temperature better
// and waste less power while device is in low battery mode, so game could be played longer when battery is nearly dead.
// setAnimationInterval will reset _animationIntervalBySystem to -1 since last change last takes effect.
// Currently, only HuaWei Android devices may use this variable.
float _animationIntervalBySystem = -1.0f;

// The animation interval when scene is changing.
// _animationIntervalByEngineOrGame & _animationIntervalBySystem will not take effect
// while _animationIntervalBySceneChange is greater than 0,
// but _animationIntervalByEngineOrGame will be effective while
// Its priority is highest while it's valid ( > 0) , and it will be invalid (set to -1) after changing scene finishes.
// Currently, only HuaWei Android devices may use this variable.
float _animationIntervalBySceneChange = -1.0f;

// The animation interval when director is paused.
// It could be updated by 'Director::getInstance()->pause();'
// Its priority is higher than _animationIntervalBySystem.
float _animationIntervalByDirectorPaused = -1.0f;

#define CARRAY_SIZE(arr) ((int)(arr.size()))

enum LevelChangeReason
{
    LEVEL_CHANGE_REASON_NONE = 0,
    LEVEL_CHANGE_REASON_CPU = (1 << 0),
    LEVEL_CHANGE_REASON_GPU = (1 << 1),
    LEVEL_CHANGE_REASON_CPU_AND_GPU = (LEVEL_CHANGE_REASON_CPU | LEVEL_CHANGE_REASON_GPU)
};

// CPU Level

struct CpuLevelInfo
{
    unsigned int nodeCount;
    unsigned int particleCount;
    unsigned int actionCount;
    unsigned int audioCount;
};

std::vector<CpuLevelInfo> _cpuLevelArr = {
    {500 , 500,  500,   6},
    {1250, 1500, 2000,  20},
    {1750, 2000, 3000,  32},
    {2750, 2500, 7000,  50}
};

// GPU Level

struct GpuLevelInfo
{
    unsigned int vertexCount;
    unsigned int drawCount;
};

std::vector<GpuLevelInfo> _gpuLevelArr = {
    {2000, 400},
    {4000, 800},
    {6000, 1000},
    {8000, 1100},
    {10000, 1200},
    {15000, 1300},
    {22000, 1350},
    {30000, 1400},
    {40000, 1450}
};

// Particle Level
const std::vector<float> _particleLevelArr = {
    0.0f,
    0.2f,
    0.4f,
    0.6f,
    0.8f,
    1.0f
};


#if EDM_DEBUG
class FpsCollector
{
public:
    FpsCollector(float intervalInSeconds)
    : _collectFpsInterval(intervalInSeconds)
    {}

    void setCollectFpsInterval(float intervalInSeconds)
    {
        _collectFpsInterval = intervalInSeconds;
    }

    inline float getCollectFpsInterval() const { return _collectFpsInterval; }

    void update(float fps)
    {
        auto now = std::chrono::steady_clock::now();
        // collect
        _fpsContainer.push_back(fps);
        
        float duration = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastTimeCollectFps).count() / 1000000.0f;
        if (duration > _collectFpsInterval)
        {
            // output info
            _lastTimeCollectFps = now;
            print();
        }
    }

    void reset(const std::chrono::steady_clock::time_point& time)
    {
        _lastTimeCollectFps = time;
        _fpsContainer.clear();
    }

private:
    void print()
    {
        if (_fpsContainer.empty())
            return;

        std::stringstream ss;
        ss.precision(3);
        float sum = 0.0f;
        float fps = 0.0f;
        std::vector<float>::iterator iter = _fpsContainer.begin();
        for (; iter != _fpsContainer.end(); ++iter)
        {
            fps = *iter;
            ss << fps << ", ";
            sum += fps;
        }
        std::string s = ss.str();
        LOGD("Collected FPS: %savg: %.01f, sum:%d", s.c_str(), sum/_fpsContainer.size(), (int)_fpsContainer.size());

        _fpsContainer.clear();
    }
private:
    float _collectFpsInterval;
    std::chrono::steady_clock::time_point _lastTimeCollectFps;
    std::vector<float> _fpsContainer;
};

#endif

class FpsUpdatedWatcher
{
public:
    FpsUpdatedWatcher(float threshold)
    : _threshold(threshold)
    , _updateCount(0)
    , _isStarted(false)
    {
        _data.reserve(12);
    }

    ~FpsUpdatedWatcher()
    {}

    void start()
    {
        reset();
        _isStarted = true;
    }
    inline bool isStarted() { return _isStarted; }

    void update(float fps)
    {
        if (!_isStarted)
            return;

        if (_data.size() >= 12)
            _data.erase(_data.begin());

        _data.push_back(fps);
        ++_updateCount;
    }

    void reset()
    {
        _data.clear();
        _updateCount = 0;
        _isStarted = false;
    }

    bool isStable()
    {
        if (_updateCount > 24)
            return true;

        if (_data.size() < 12)
            return false;

        float sum = 0.0f;
        float average = 0.0f;
        uint32_t stableCount = 0;

        std::vector<float>::iterator iter = _data.begin();
        for (; iter != _data.end(); ++iter)
            sum += *iter;

        average = sum / _data.size();

        iter = _data.begin();
        for (; iter != _data.end(); ++iter)
        {
            if (fabs(*iter - average) < _threshold)
                ++stableCount;
        }

        return stableCount > 9;
    }
private:
    std::vector<float> _data; // Collect 12 frames data
    float _threshold;
    int _updateCount;
    bool _isStarted;
};

FpsUpdatedWatcher _fpsUpdatedWatcher(2.0f);

#if EDM_DEBUG
FpsCollector _fpsCollector(0.2f);
bool _isCollectFpsEnabled = false;
#endif

int cbCpuLevelNode(int i) { return _cpuLevelArr[i].nodeCount; }
int cbCpuLevelParticle(int i) { return _cpuLevelArr[i].particleCount; }
int cbCpuLevelAction(int i) { return _cpuLevelArr[i].actionCount; }
int cbCpuLevelAudio(int i) { return _cpuLevelArr[i].audioCount; }

float toCpuLevelPerFactor(int value, int (*cb)(int i))
{
    int len = CARRAY_SIZE(_cpuLevelArr);
    int prevStep = 0;
    int curStep = 0;
    for (int i = 0; i < len; ++i)
    {
        curStep = cb(i);
        if (value < curStep)
        {
            // The return value should be a float value.
            // Do linear interpolation here
            return i + (1.0f / (curStep - prevStep) * (value - prevStep));
        }
        prevStep = curStep;
    }
    return len;
}

int cbGpuLevelVertex(int i) { return _gpuLevelArr[i].vertexCount; }
int cbGpuLevelDraw(int i) { return _gpuLevelArr[i].drawCount; }

float toGpuLevelPerFactor(int value, int (*cb)(int i))
{
    int len = CARRAY_SIZE(_gpuLevelArr);
    int prevStep = 0;
    int curStep = 0;

    for (int i = 0; i < len; ++i)
    {
        curStep = cb(i);
        if (value < curStep)
        {
            // The return value should be a float value.
            // Do linear interpolation here
            return i + (1.0f / (curStep - prevStep) * (value - prevStep));
        }

        prevStep = curStep;

    }
    return len;
}

void resetLastTime()
{
    _lastFrameLost100msUpdate = std::chrono::steady_clock::now();
    _lastContinuousFrameLostUpdate = _lastFrameLost100msUpdate;
    _lastLowFpsUpdate = _lastFrameLost100msUpdate;
    _lastTimeNotifyLevelByLowFps = _lastFrameLost100msUpdate;
    _lastTimeCalculateAvgFps = _lastFrameLost100msUpdate;

#if EDM_DEBUG
    _fpsCollector.reset(_lastFrameLost100msUpdate);
#endif
}

void parseDebugConfig()
{
#if EDM_DEBUG
    auto fileUtils = FileUtils::getInstance();

    const char* configPath = "/sdcard/cc-res-level.json";

    if (!fileUtils->isFileExist(configPath))
    {
        return;
    }

    LOGD("Using debug level config: %s", configPath);

    std::string buffer;
    unsigned long size = 0;
    unsigned char* resLevelConfig = fileUtils->getFileData(configPath, "rb", &size);
    if (resLevelConfig != NULL && size > 0)
    {
        buffer.insert(0, (const char*)resLevelConfig, (size_t)size);
    }
    delete[] resLevelConfig;

    // Get std::map from config file
    {
        size_t pos = buffer.find_first_of('{');
        if (pos != std::string::npos)
        {
            buffer.replace(pos, 1, "");
        }
        pos = buffer.find_last_of('}');

        if (pos != std::string::npos)
        {
            buffer.replace(pos, 1, "");
        }
    }

    deleteChar(buffer, "\r");
    deleteChar(buffer, "\n");
    deleteChar(buffer, "\t");
    deleteChar(buffer, " ");

    std::string cpuLevelBuffer;
    {
        const char* cpuLevelStartKey = "\"cpu_level\":[";
        const size_t cpuLevelStartKeyLen = strlen(cpuLevelStartKey);
        size_t cpuLevelStartPos = buffer.find(cpuLevelStartKey);
        if (cpuLevelStartPos != std::string::npos)
        {
            cpuLevelStartPos += cpuLevelStartKeyLen;
            size_t cpuLevelEndPos = buffer.find("]", cpuLevelStartPos);
            cpuLevelBuffer = buffer.substr(cpuLevelStartPos, cpuLevelEndPos - cpuLevelStartPos);
            buffer.erase(cpuLevelStartPos-cpuLevelStartKeyLen, cpuLevelBuffer.length() + cpuLevelStartKeyLen + 1);
        }
    }

    if (!cpuLevelBuffer.empty())
    {
        LOGD("cpuLevelBuffer: %s", cpuLevelBuffer.c_str());
    }

    std::string gpuLevelBuffer;
    {
        const char* gpuLevelStartKey = "\"gpu_level\":[";
        const size_t gpuLevelStartKeyLen = strlen(gpuLevelStartKey);
        size_t gpuLevelStartPos = buffer.find(gpuLevelStartKey);
        if (gpuLevelStartPos != std::string::npos)
        {
            gpuLevelStartPos += gpuLevelStartKeyLen;
            size_t gpuLevelEndPos = buffer.find("]", gpuLevelStartPos);
            gpuLevelBuffer = buffer.substr(gpuLevelStartPos, gpuLevelEndPos - gpuLevelStartPos);
            buffer.erase(gpuLevelStartPos-gpuLevelStartKeyLen, gpuLevelBuffer.length() + gpuLevelStartKeyLen + 1);
        }
    }

    if (gpuLevelBuffer.empty())
    {
        LOGD("gpuLevelBuffer: %s", gpuLevelBuffer.c_str());
    }

    LOGD("remain: %s", buffer.c_str());

    std::vector<std::string> keyValueArr;
    split(buffer, ",", &keyValueArr);

    if (keyValueArr.empty())
    {
        LOGE("Parse cc-res-level.json failed!");
        return;
    }

    LOGD("element count: %d", (int)keyValueArr.size());

    std::map<std::string, std::string> configMap;
    for (size_t i = 0, len = keyValueArr.size(); i < len; ++i)
    {
        std::string e = keyValueArr[i];
        if (e.empty())
            continue;

        std::vector<std::string> keyValue;
        split(e, ":", &keyValue);
        if (keyValue.empty() || keyValue.size() != 2)
        {
            LOGE("Parse (%s) failed, size: %d", e.c_str(), (int)keyValue.size());
            return;
        }

        deleteChar(keyValue[0], "\"");

        configMap.insert(std::make_pair(keyValue[0], keyValue[1]));
    }

    std::string tmp;
    if (getValueFromMap(configMap, "force_enable_optimization", &tmp))
    {
        toLowercase(tmp);
        if (tmp == "true")
        {
            _forceEnableOptimization = true;
        }
        LOGD("[changed] force_enable_optimization: %d", _forceEnableOptimization);
    }
    else
    {
        LOGD("[default] force_enable_optimization: %d", _forceEnableOptimization);
    }


    if (getValueFromMap(configMap, "level_log_freq", &tmp))
    {
        _printCpuGpuLevelThreshold = (uint32_t)atoi(tmp.c_str());
        LOGD("[changed] level_log_freq: %u", _printCpuGpuLevelThreshold);
    }
    else
    {
        LOGD("[default] level_log_freq: %u", _printCpuGpuLevelThreshold);
    }
    

    if (getValueFromMap(configMap, "cpu_usage_log_freq", &tmp))
    {
        _printCpuUsageThreshold = (uint32_t)atoi(tmp.c_str());
        LOGD("[changed] cpu_usage_log_freq: %u", _printCpuUsageThreshold);
    }
    else
    {
        LOGD("[default] cpu_usage_log_freq: %u", _printCpuUsageThreshold);
    }

    if (getValueFromMap(configMap, "level_decrease_threshold", &tmp))
    {
        _levelDecreaseThreshold = atof(tmp.c_str());
        LOGD("[changed] level_decrease_threshold: %f", _levelDecreaseThreshold);
    }
    else
    {
        LOGD("[default] level_decrease_threshold: %f", _levelDecreaseThreshold);
    }

    if (getValueFromMap(configMap, "low_fps_check_mode", &tmp))
    {
        _lowFpsCheckMode = (uint32_t)atoi(tmp.c_str());
        LOGD("[changed] low_fps_check_mode: %u", _lowFpsCheckMode);
    }
    else
    {
        LOGD("[default] low_fps_check_mode: %u", _lowFpsCheckMode);
    }

    if (getValueFromMap(configMap, "low_realfps_threshold", &tmp))
    {
        _lowRealFpsThreshold = atof(tmp.c_str());
        LOGD("[changed] low_realfps_threshold: %f", _lowRealFpsThreshold);
    }
    else
    {
        LOGD("[default] low_realfps_threshold: %f", _lowRealFpsThreshold);
    }

    if (getValueFromMap(configMap, "notify_level_by_low_fps_threshold", &tmp))
    {
        _notifyLevelByLowFpsThreshold = atof(tmp.c_str());
        LOGD("[changed] notify_level_by_low_fps_threshold: %f", _notifyLevelByLowFpsThreshold);
    }
    else
    {
        LOGD("[default] notify_level_by_low_fps_threshold: %f", _notifyLevelByLowFpsThreshold);
    }

    if (getValueFromMap(configMap, "min_value_of_notify_cpu_level_by_low_fps", &tmp))
    {
        _minValueOfNotifyCpuLevelByLowFps = atoi(tmp.c_str());
        if (_minValueOfNotifyCpuLevelByLowFps > CARRAY_SIZE(_cpuLevelArr))
        {
            _minValueOfNotifyCpuLevelByLowFps = CARRAY_SIZE(_cpuLevelArr);
        }
        LOGD("[changed] min_value_of_notify_cpu_level_by_low_fps: %d", _minValueOfNotifyCpuLevelByLowFps);
    }
    else
    {
        LOGD("[default] min_value_of_notify_cpu_level_by_low_fps: %d", _minValueOfNotifyCpuLevelByLowFps);
    }

    if (getValueFromMap(configMap, "min_value_of_notify_gpu_level_by_low_fps", &tmp))
    {
        _minValueOfNotifyGpuLevelByLowFps = atoi(tmp.c_str());
        if (_minValueOfNotifyGpuLevelByLowFps > CARRAY_SIZE(_gpuLevelArr))
        {
            _minValueOfNotifyGpuLevelByLowFps = CARRAY_SIZE(_gpuLevelArr);
        }
        LOGD("[changed] min_value_of_notify_gpu_level_by_low_fps: %d", _minValueOfNotifyGpuLevelByLowFps);
    }
    else
    {
        LOGD("[default] min_value_of_notify_gpu_level_by_low_fps: %d", _minValueOfNotifyGpuLevelByLowFps);
    }

    if (getValueFromMap(configMap, "continuous_low_realfps_threshold", &tmp))
    {
        _continuousLowRealFpsThreshold = (uint32_t)atoi(tmp.c_str());
        LOGD("[changed] continuous_low_realfps_threshold: %u", _continuousLowRealFpsThreshold);
    }
    else
    {
        LOGD("[default] continuous_low_realfps_threshold: %u", _continuousLowRealFpsThreshold);
    }

    if (getValueFromMap(configMap, "enable_collect_fps", &tmp))
    {
        toLowercase(tmp);
        if (tmp == "true")
        {
            _isCollectFpsEnabled = true;
        }
        LOGD("[changed] enable_collect_fps: %d", (int)_isCollectFpsEnabled);
    }
    else
    {
        LOGD("[default] enable_collect_fps: %d", (int)_isCollectFpsEnabled);
    }

    if (getValueFromMap(configMap, "collect_fps_interval", &tmp))
    {
        _fpsCollector.setCollectFpsInterval(atof(tmp.c_str()));
        LOGD("[changed] collect_fps_interval: %f", _fpsCollector.getCollectFpsInterval());
    }
    else
    {
        LOGD("[default] collect_fps_interval: %f", _fpsCollector.getCollectFpsInterval());
    }

    if (!cpuLevelBuffer.empty())
    {
        std::vector<std::string> cpuObjectArray;
        split(cpuLevelBuffer, "},", &cpuObjectArray);
        if (!cpuObjectArray.empty())
        {
            _cpuLevelArr.clear();
            CpuLevelInfo cpuLevelInfo;

            for (size_t i = 0, len = cpuObjectArray.size(); i < len; ++i)
            {
                std::string& e = cpuObjectArray[i];
                size_t pos = e.find_first_of('{');
                if (pos != std::string::npos)
                {
                    e.replace(pos, 1, "");
                }
                pos = e.find_last_of('}');

                if (pos != std::string::npos)
                {
                    e.replace(pos, 1, "");
                }

                LOGD("cpu level: %s", e.c_str());

                std::vector<std::string> cpuLevelElement;
                split(e, ",", &cpuLevelElement);

                for (size_t j = 0; j < cpuLevelElement.size(); ++j)
                {
                    std::map<std::string, std::string> kvMap;
                    std::vector<std::string> kvArr;
                    split(cpuLevelElement[j], ":", &kvArr);
                    if (kvArr.size() != 2)
                    {
                        LOGE("cpu level configuration error: %d", (int)kvArr.size());
                        return;
                    }
                    deleteChar(kvArr[0], "\"");

                    kvMap.insert(std::make_pair(kvArr[0], kvArr[1]));

                    if (getValueFromMap(kvMap, "node", &tmp))
                    {
                        cpuLevelInfo.nodeCount = (uint32_t)atoi(tmp.c_str());
                    }

                    if (getValueFromMap(kvMap, "particle", &tmp))
                    {
                        cpuLevelInfo.particleCount = (uint32_t)atoi(tmp.c_str());
                    }
                    if (getValueFromMap(kvMap, "action", &tmp))
                    {
                        cpuLevelInfo.actionCount = (uint32_t)atoi(tmp.c_str());
                    }
                    if (getValueFromMap(kvMap, "audio", &tmp))
                    {
                        cpuLevelInfo.audioCount = (uint32_t)atoi(tmp.c_str());
                    }
                }

                _cpuLevelArr.push_back(cpuLevelInfo);
            }
        }
    }

    if (!gpuLevelBuffer.empty())
    {
        std::vector<std::string> gpuObjectArray;
        split(gpuLevelBuffer, "},", &gpuObjectArray);
        if (!gpuObjectArray.empty())
        {
            _gpuLevelArr.clear();
            GpuLevelInfo gpuLevelInfo;

            for (size_t i = 0, len = gpuObjectArray.size(); i < len; ++i)
            {
                std::string& e = gpuObjectArray[i];
                size_t pos = e.find_first_of('{');
                if (pos != std::string::npos)
                {
                    e.replace(pos, 1, "");
                }
                pos = e.find_last_of('}');

                if (pos != std::string::npos)
                {
                    e.replace(pos, 1, "");
                }

                LOGD("gpu level: %s", e.c_str());

                std::vector<std::string> gpuLevelElement;
                split(e, ",", &gpuLevelElement);

                for (size_t j = 0; j < gpuLevelElement.size(); ++j)
                {
                    std::map<std::string, std::string> kvMap;
                    std::vector<std::string> kvArr;
                    split(gpuLevelElement[j], ":", &kvArr);
                    if (kvArr.size() != 2)
                    {
                        LOGE("gpu level configuration error: %d", (int)kvArr.size());
                        return;
                    }
                    deleteChar(kvArr[0], "\"");

                    kvMap.insert(std::make_pair(kvArr[0], kvArr[1]));

                    if (getValueFromMap(kvMap, "vertex", &tmp))
                    {
                        gpuLevelInfo.vertexCount = (uint32_t)atoi(tmp.c_str());
                    }

                    if (getValueFromMap(kvMap, "draw", &tmp))
                    {
                        gpuLevelInfo.drawCount = (uint32_t)atoi(tmp.c_str());
                    }
                }
                
                _gpuLevelArr.push_back(gpuLevelInfo);
            }
        }
    }

     {
         LOGD("-----------------------------------------");
         std::vector<CpuLevelInfo>::iterator iter = _cpuLevelArr.begin();
         for (; iter != _cpuLevelArr.end(); ++iter)
         {
             CpuLevelInfo level = *iter;
             LOGD("cpu level: %u, %u, %u, %u", level.nodeCount, level.particleCount, level.actionCount, level.audioCount);
         }
         LOGD("-----------------------------------------");
     }

     {
         LOGD("=========================================");
         std::vector<GpuLevelInfo>::iterator iter = _gpuLevelArr.begin();
         for (; iter != _gpuLevelArr.end(); ++iter)
         {
             GpuLevelInfo level = *iter;
             LOGD("gpu level: %u, %u", level.vertexCount, level.drawCount);
         }
         LOGD("=========================================");
     }
#endif // EDM_DEBUG
}

void setAnimationIntervalBySystem(float interval)
{
    if (!_isSupported)
        return;

    LOGD("Set FPS %f by system", std::ceil(1.0f / interval));
    EngineDataManager::setAnimationInterval(interval, SetIntervalReason::BY_SYSTEM);
}

void setAnimationIntervalBySceneChange(float interval)
{
    if (!_isSupported)
        return;

    LOGD("Set FPS %f while changing scene", std::ceil(1.0f / interval));
    EngineDataManager::setAnimationInterval(interval, SetIntervalReason::BY_SCENE_CHANGE);
}

} // namespace {

namespace cocos2d {

int EngineDataManager::getTotalParticleCount()
{
    auto& particleSystems = ParticleSystem::getAllParticleSystems();
    if (particleSystems.empty())
    {
        return 0;
    }

    int count = 0;
    for (auto&& system : particleSystems)
    {
        count += system->getTotalParticles();
    }

    return count;
}

// calculates frame lost event
// static
void EngineDataManager::calculateFrameLost()
{
    auto director = Director::getInstance();

    if (_lowFpsThreshold > 0 && _continuousFrameLostThreshold > 0)
    {
        float frameRate = director->getFrameRate();

        float expectedFps = 1.0f / _animationInterval;
        float frameLostRate = (expectedFps - frameRate) * _animationInterval;
        if (frameLostRate > _lowFpsThreshold)
        {
            ++_frameLostCounter;
            ++_lowFpsCounter;
//            LOGD("_frameLostCounter: %d, _lowFpsCounter=%d", _frameLostCounter, _lowFpsCounter);
        }
        
        auto now = std::chrono::steady_clock::now();
        float interval = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastFrameLost100msUpdate).count() / 1000000.0f;
        if (interval > 0.1f)
        {
            _lastFrameLost100msUpdate = now;
            // check lost frame count
            if (_frameLostCounter >= _continuousFrameLostThreshold)
            {
                ++_continuousFrameLostCount;
            }
            // Reset frame lost counter after 100ms interval 
            // even it's smaller than _continuousFrameLostThreshold
            _frameLostCounter = 0;
        }
        
        interval = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastContinuousFrameLostUpdate).count() / 1000000.0f;
        if (interval > (_continuousFrameLostCycle / 1000.0f))
        {
            _lastContinuousFrameLostUpdate = now;
            if (_continuousFrameLostCount > 0)
            {
                // notify continuous frame lost event to system
                notifyContinuousFrameLost(_continuousFrameLostCycle, _continuousFrameLostThreshold, _continuousFrameLostCount);

                // LOGD("continuous frame lost: %d", _continuousFrameLostCount);
                _continuousFrameLostCount = 0;
            }
        }
        
        interval = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastLowFpsUpdate).count() / 1000000.0f;
        if (interval > (_lowFpsCycle / 1000.0f))
        {
            _lastLowFpsUpdate = now;
            if (_lowFpsCounter > 0)
            {
                // notify low fps event to system
                notifyLowFps(_lowFpsCycle, _lowFpsThreshold, _lowFpsCounter);
                // LOGD("low fps frame count: %d", _lowFpsCounter);
                _lowFpsCounter = 0;
            }
        }
    }
}

// static 
void EngineDataManager::onBeforeSetNextScene(EventCustom* event)
{
    // Reset the old status since we have changed CPU/GPU level manually.
    // If the CPU level isn't 5 and GPU level isn't 0 in the next time of checking CPU/GPU level,
    // Make sure that the changed CPU/GPU level will be notified.
    _oldCpuLevel = -1;
    _oldGpuLevel = -1;
    _oldCpuLevelMulFactor = -1;
    _oldGpuLevelMulFactor = -1;

    if (_isFirstSetNextScene)
    {
        _isFirstSetNextScene = false;
        notifyGameStatus(GameStatus::LAUNCH_END, -1, -1);
    }
    else if (_isReplaceScene)
    {
        notifyGameStatus(GameStatus::SCENE_CHANGE_END, -1, -1);
    }

    notifyGameStatus(GameStatus::SCENE_CHANGE_BEGIN, 5, 0);

    // SetAnimationIntervalBySceneChange to 1.0f/60.0f while there isn't in replacing scene.
    if (!_isReplaceScene)
    {
        // Modify fps to 60 
        setAnimationIntervalBySceneChange(DEFAULT_INTERVAL);
    }

    _isReplaceScene = true;
}

void EngineDataManager::onBeforeReadFile(EventCustom* event)
{
    _isReadFile = true;
}

void EngineDataManager::notifyGameStatusIfCpuOrGpuLevelChanged()
{
    // calculate CPU & GPU levels
    int cpuLevel = 0;
    int gpuLevel = 0;

    int levelChangeReason = LEVEL_CHANGE_REASON_NONE;

    Director* director = Director::getInstance();
    int totalNodeCount = Node::getAttachedNodeCount();
    int totalParticleCount = getTotalParticleCount();
    int totalActionCount = director->getActionManager()->getNumberOfRunningActions();
    int totalPlayingAudioCount = experimental::AudioEngine::getPlayingAudioCount();

    {
        float cpuLevelNode = toCpuLevelPerFactor(totalNodeCount, cbCpuLevelNode);
        float cpuLevelParticle = toCpuLevelPerFactor(totalParticleCount, cbCpuLevelParticle);
        float cpuLevelAction = toCpuLevelPerFactor(totalActionCount, cbCpuLevelAction);
        float cpuLevelAudio = toCpuLevelPerFactor(totalPlayingAudioCount, cbCpuLevelAudio);
        float fCpuLevel = cpuLevelNode + cpuLevelParticle + cpuLevelAction + cpuLevelAudio;
        float highestCpuLevel = CARRAY_SIZE(_cpuLevelArr) * 1.0f;
        fCpuLevel = fCpuLevel > highestCpuLevel ? highestCpuLevel : fCpuLevel;
        cpuLevel = std::floor(fCpuLevel);

#if EDM_DEBUG
        if (_printCpuGpuLevelCounter > _printCpuGpuLevelThreshold)
        {
            LOGD("DEBUG: cpu level: %d, node: (%f, %d), particle: (%f, %d), action: (%f, %d), audio: (%f, %d)", 
                cpuLevel, cpuLevelNode, totalNodeCount, cpuLevelParticle, totalParticleCount, cpuLevelAction, totalActionCount, cpuLevelAudio, totalPlayingAudioCount);
        }
#endif
        if (_oldCpuLevel < 0
            || fCpuLevel < (1.0f * _oldCpuLevel - _levelDecreaseThreshold)
            || cpuLevel > _oldCpuLevel
            )
        {
            LOGD("NOTIFY: cpu level: %d, node: (%f, %d), particle: (%f, %d), action: (%f, %d), audio: (%f, %d)", 
                cpuLevel, cpuLevelNode, totalNodeCount, cpuLevelParticle, totalParticleCount, cpuLevelAction, totalActionCount, cpuLevelAudio, totalPlayingAudioCount);
            levelChangeReason |= LEVEL_CHANGE_REASON_CPU;
            _oldCpuLevel = cpuLevel;
        }
        else
        {
            // Adjust cpu level to old cpu level, it's necessary because we have a level decrease threshold.
            // For instance, if threshold is 0.2, fCpuLevel = 1.9, cpuLevel = 1, _oldCpuLevel = 2,
            // fCpuLevel is in the decrease threshold region, we need to still notify '2' to vendor.
            // Therefore, reset cpuLevel to 2 here.
            cpuLevel = _oldCpuLevel;
        }
    }

    {
        auto renderer = director->getRenderer();
        int vertexCount = renderer->getDrawnVertices();
        int drawCount = renderer->getDrawnBatches();

        float gpuLevelVertex = toGpuLevelPerFactor(vertexCount, cbGpuLevelVertex);
        float gpuLevelDraw = toGpuLevelPerFactor(drawCount, cbGpuLevelDraw);
        float fGpuLevel = gpuLevelVertex + gpuLevelDraw;
        float highestGpuLevel = CARRAY_SIZE(_gpuLevelArr) * 1.0f;
        fGpuLevel = fGpuLevel > highestGpuLevel ? highestGpuLevel : fGpuLevel;
        gpuLevel = std::floor(fGpuLevel);

#if EDM_DEBUG
        if (_printCpuGpuLevelCounter > _printCpuGpuLevelThreshold)
        {
            LOGD("DEBUG: gpu level: %d, vertex: (%f, %d), draw: (%f, %d)", gpuLevel, gpuLevelVertex, vertexCount, gpuLevelDraw, drawCount);
        }
#endif
        if (_oldGpuLevel < 0
            || fGpuLevel < (1.0f * _oldGpuLevel - _levelDecreaseThreshold)
            || gpuLevel > _oldGpuLevel
            )
        {
            LOGD("NOTIFY: gpu level: %d, vertex: (%f, %d), draw: (%f, %d)", gpuLevel, gpuLevelVertex, vertexCount, gpuLevelDraw, drawCount);
            levelChangeReason |= LEVEL_CHANGE_REASON_GPU;
            _oldGpuLevel = gpuLevel;
        }
        else
        {
            // Adjust gpu level to old gpu level, it's necessary because we have a level decrease threshold.
            // For instance, if threshold is 0.2, fGpuLevel = 1.9, gpuLevel = 1, _oldGpuLevel = 2,
            // fGpuLevel is in the decrease threshold region, we need to still notify '2' to vendor.
            // Therefore, reset gpuLevel to 2 here.
            gpuLevel = _oldGpuLevel;
        }
    }

    float expectedFps = 1.0f / _animationInterval;
    float realFps = director->getFrameRate();
    bool isLowRealFps = false;
    if (_fpsUpdatedWatcher.isStarted())
    {
        _fpsUpdatedWatcher.update(realFps);
        if (_fpsUpdatedWatcher.isStable())
        {
            LOGD("FPS(%.01f) is stable now!", realFps);
            _fpsUpdatedWatcher.reset();
        }
    }
    else
    {
#if EDM_DEBUG
        if (_isCollectFpsEnabled)
        {
            _fpsCollector.update(realFps);
        }
#endif
        if (0 == _lowFpsCheckMode)
        {
            // Low Real Fps definition:
            // CurrentFrameTimeCost > ExpectedFrameTimeCost + ExpectedFrameTimeCost * LowRealFpsThreshold
            isLowRealFps = (1.0f / realFps) > (_animationInterval + _animationInterval * _lowRealFpsThreshold);
            if (isLowRealFps)
            {
                auto now = std::chrono::steady_clock::now();
                float lowFpsIntervalInSeconds = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastTimeNotifyLevelByLowFps).count() / 1000000.0f;
          
                if (_continuousLowRealFpsCount >= _continuousLowRealFpsThreshold
                    && lowFpsIntervalInSeconds > _notifyLevelByLowFpsThreshold)
                {
                    _continuousLowRealFpsCount = 0;
                    LOGD("Detected low fps (mode 0): real: %.01f, expected: %.01f, interval: %.03fs", realFps, expectedFps, lowFpsIntervalInSeconds);
                    _lastTimeNotifyLevelByLowFps = now;
                }
                else
                {
                    // Reset this varible to false since it's smaller than notification threshold.
                    // In this way, we could avoid to notify vendor frequently.
                    isLowRealFps = false;

                    ++_continuousLowRealFpsCount;
                }
            }
            else
            {
                _continuousLowRealFpsCount = 0;
            }
        }
        else
        {
            ++_calculateAvgFpsCount;
            _calculateAvgFpsSum += realFps;

            auto now = std::chrono::steady_clock::now();
            float interval = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastTimeCalculateAvgFps).count() / 1000000.0f;

            if (interval > _notifyLevelByLowFpsThreshold)
            {
                float avgFps = _calculateAvgFpsSum / _calculateAvgFpsCount;
                // Low Real Fps definition:
                // CurrentFrameTimeCost > ExpectedFrameTimeCost + ExpectedFrameTimeCost * LowRealFpsThreshold
                isLowRealFps = (1.0f / avgFps) > (_animationInterval + _animationInterval * _lowRealFpsThreshold);

                if (isLowRealFps)
                {
                    LOGD("Detected low fps (mode 1): avg: %.01f, expected: %.01f, interval: %.03fs, framecount: %u", avgFps, expectedFps, interval, _calculateAvgFpsCount);
                }

                // Reset counter
                _calculateAvgFpsCount = 0;
                _calculateAvgFpsSum = 0.0f;

                // Reset last time of calculating average fps
                _lastTimeCalculateAvgFps = now;
            }
        }
    }

    if (levelChangeReason != LEVEL_CHANGE_REASON_NONE || _isFpsChanged || isLowRealFps)
    {
        _isFpsChanged = false;
        
        // LOGD("expectedFps: %f, realFps: %f", expectedFps, realFps);
        if (isLowRealFps)
        {
            _cpuFpsFactor = _gpuFpsFactor = 1.0f;
        }
        else
        {
            _cpuFpsFactor = _gpuFpsFactor = expectedFps / 60.0f;
        }

        int newCpuLevelMulFactor = std::ceil(cpuLevel * _cpuFpsFactor);
        int newGpuLevelMulFactor = std::ceil(gpuLevel * _gpuFpsFactor);

        if (isLowRealFps
            || newCpuLevelMulFactor != _oldCpuLevelMulFactor
            || newGpuLevelMulFactor != _oldGpuLevelMulFactor)
        {
            const char* logPrefix = "[level changed]";
            if (isLowRealFps)
            {
                logPrefix = "[low fps]";
                if (newCpuLevelMulFactor < _minValueOfNotifyCpuLevelByLowFps)
                {
                    newCpuLevelMulFactor = _minValueOfNotifyCpuLevelByLowFps;
                }

                if (newGpuLevelMulFactor < _minValueOfNotifyGpuLevelByLowFps)
                {
                    newGpuLevelMulFactor = _minValueOfNotifyGpuLevelByLowFps;
                }
            }

            int cpuLevelToNotify = newCpuLevelMulFactor;
            int gpuLevelToNotify = newGpuLevelMulFactor;

            // Set CPU or GPU level to -2 only when fps isn't changed and isn't in low fps.
            if (!_isFpsChanged && !isLowRealFps)
            {
                if (_oldGpuLevelMulFactor == newGpuLevelMulFactor)
                {
                    gpuLevelToNotify = -2; // Only CPU level has been changed, pass -2 to GPU level.
                }
                else if (_oldCpuLevelMulFactor == newCpuLevelMulFactor)
                {
                    cpuLevelToNotify = -2; // Only GPU level has been changed, pass -2 to CPU level.
                }
            }

            LOGD("%s notifyGameStatus: IN_SCENE(%d, %d), cpuLevel: %d->%d(%d), gpuLevel: %d->%d(%d), factor: %f",
                logPrefix,
                cpuLevel, gpuLevel,
                _oldCpuLevelMulFactor, cpuLevelToNotify, newCpuLevelMulFactor,
                _oldGpuLevelMulFactor, gpuLevelToNotify, newGpuLevelMulFactor,
                _cpuFpsFactor);

            notifyGameStatus(GameStatus::IN_SCENE, cpuLevelToNotify, gpuLevelToNotify);

            _oldCpuLevelMulFactor = newCpuLevelMulFactor;
            _oldGpuLevelMulFactor = newGpuLevelMulFactor;
        }
    }
}

// static
void EngineDataManager::onAfterDrawScene(EventCustom* event)
{
    calculateFrameLost();

#if EDM_DEBUG
    ++_printCpuGpuLevelCounter;
    ++_printCpuUsageCounter;
#endif

    if (_isReplaceScene)
    {
        ++_drawCountInterval;

        if (_drawCountInterval > _drawCountThreshold)
        {
            _drawCountInterval = 0;
            _isReplaceScene = false;

            // setAnimationIntervalBySceneChange to -1.0f to
            // make developer's or huawei's FPS setting take effect.
            setAnimationIntervalBySceneChange(-1.0f);

            _oldCpuLevel = -1;
            _oldGpuLevel = -1;
            _oldCpuLevelMulFactor = -1;
            _oldGpuLevelMulFactor = -1;
            notifyGameStatus(GameStatus::SCENE_CHANGE_END, -1, -1);
        }
        else if (_isReadFile)
        {
            _drawCountInterval = 0;
        }
        _isReadFile = false;
    }
    else
    {
        notifyGameStatusIfCpuOrGpuLevelChanged();
    }

#if EDM_DEBUG
    if (_printCpuUsageCounter > _printCpuUsageThreshold)
    {
        _printCpuUsageCounter = 0;
        _cpuTracker.update();
        _cpuTracker.printCurrentState();
    }

    if (_printCpuGpuLevelCounter > _printCpuGpuLevelThreshold)
    {
        _printCpuGpuLevelCounter = 0;
    }
#endif
}

// static
void EngineDataManager::onEnterForeground(EventCustom* event)
{
    _isInBackground = false;

    static bool isFirstTime = true;
    LOGD("onEnterForeground, isFirstTime: %d", isFirstTime);

    if (isFirstTime)
    {
        isFirstTime = false;
    }
    else
    {
        resetLastTime();
        // Reset the old status
        _oldCpuLevel = -1;
        _oldGpuLevel = -1;
        _oldCpuLevelMulFactor = -1;
        _oldGpuLevelMulFactor = -1;
        // Notify CPU/GPU level to system since old levels have been changed.
        notifyGameStatusIfCpuOrGpuLevelChanged();  
    }
}

void EngineDataManager::onEnterBackground(EventCustom* event)
{
    LOGD("EngineDataManager::onEnterBackground ...");
    _isInBackground = true;
}

// static
void EngineDataManager::init()
{
    parseDebugConfig();

#if EDM_DEBUG
    if (_forceEnableOptimization)
    {
        LOGD("init, force enable optimization!");
        _isSupported = true;
    }
#endif

    if (!_isSupported)
        return;

    if (_isInitialized)
        return;

    resetLastTime();

    LOGD("EngineDataManager version: %s", ENGINE_DATA_MANAGER_VERSION);

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addCustomEventListener(Director::EVENT_AFTER_DRAW, std::bind(onAfterDrawScene, std::placeholders::_1));
    dispatcher->addCustomEventListener(Director::EVENT_BEFORE_SET_NEXT_SCENE, std::bind(onBeforeSetNextScene, std::placeholders::_1));
    dispatcher->addCustomEventListener(EVENT_COME_TO_FOREGROUND, std::bind(onEnterForeground, std::placeholders::_1));
    dispatcher->addCustomEventListener(EVENT_COME_TO_BACKGROUND, std::bind(onEnterBackground, std::placeholders::_1));
    dispatcher->addCustomEventListener(EVENT_BEFORE_READ_FILE, std::bind(onBeforeReadFile, std::placeholders::_1));

    notifyGameStatus(GameStatus::LAUNCH_BEGIN, 5, -1);


#if EDM_DEBUG
    _cpuTracker.update();
#endif
    _isInitialized = true;
}

// static 
void EngineDataManager::destroy()
{
    if (!_isSupported)
        return;
}

// static
void EngineDataManager::notifyGameStatus(GameStatus type, int cpuLevel, int gpuLevel)
{
    if (!_isSupported)
        return;

    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME_ENGINE_DATA_MANAGER, "notifyGameStatus", "(III)V"))
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)type, cpuLevel, gpuLevel);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

static void updateFinalAnimationInterval()
{
    if (_animationIntervalBySceneChange > 0.0f) {
        _animationInterval = _animationIntervalBySceneChange;
    } else if (_animationIntervalByDirectorPaused > 0.0f) {
        _animationInterval = _animationIntervalByDirectorPaused;
    } else if (_animationIntervalBySystem > 0.0f) {
        _animationInterval = _animationIntervalBySystem;
    } else {
        _animationInterval = _animationIntervalByEngineOrGame;
    }
}

void EngineDataManager::setAnimationInterval(float interval, SetIntervalReason reason)
{
    float oldFps = 0.0f;
    float newFps = 0.0f;

    if (reason == SetIntervalReason::BY_GAME) {
        LOGD("setAnimationInterval by game: %.04f", interval);

        if (_isSupported)
        {
            float oldInterval = _animationIntervalBySystem > 0.0f ? _animationIntervalBySystem : _animationIntervalByEngineOrGame;
            oldFps = (float)ceil(1.0f/oldInterval);
            newFps = (float)ceil(1.0f/interval);
        }

        _animationIntervalByDirectorPaused = -1.0f;
        // Reset _animationIntervalBySystem to -1 to make developer's FPS configuration take effect.
        _animationIntervalBySystem = -1.0f;
        _animationIntervalByEngineOrGame = interval;
    } else if (reason == SetIntervalReason::BY_ENGINE) {
        LOGD("setAnimationInterval by engine: %.04f", interval);
        _animationIntervalByDirectorPaused = -1.0f;
        _animationIntervalByEngineOrGame = interval;
    } else if (reason == SetIntervalReason::BY_SYSTEM) {
        LOGD("setAnimationInterval by system: %.04f", interval);
        if (interval > 0.0f) {
            _animationIntervalBySystem = interval;
        } else {
            _animationIntervalBySystem = -1.0f;
        }
    } else if (reason == SetIntervalReason::BY_SCENE_CHANGE) {
        LOGD("setAnimationInterval by scene change: %.04f", interval);
        if (interval > 0.0f) {
            _animationIntervalBySceneChange = interval;
        } else {
            _animationIntervalBySceneChange = -1.0f;
        }
    } else if (reason == SetIntervalReason::BY_DIRECTOR_PAUSE) {
        LOGD("setAnimationInterval by director paused: %.04f", interval);
        _animationIntervalByDirectorPaused = interval;
    } else {
        LOGD("setAnimationInterval by UNKNOWN reason: %.04f", interval);
    }
    updateFinalAnimationInterval();

    LOGD("JNI setAnimationInterval: %f", _animationInterval);
    JniHelper::callStaticVoidMethod(CLASS_NAME_RENDERER, "setAnimationInterval", _animationInterval);

    if (_isSupported)
    {
        // Notify system that FPS configuration has been changed by game.
        // notifyFpsChanged has to be invoked at the end.
        if (fabs(oldFps - newFps) > 1.0f)
        {
            _isFpsChanged = true;
            notifyFpsChanged(oldFps, newFps);
            _fpsUpdatedWatcher.start();
        }
    }
}

// static
void EngineDataManager::notifyContinuousFrameLost(int continueFrameLostCycle, int continueFrameLostThreshold, int times)
{
    if (!_isSupported)
        return;

    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME_ENGINE_DATA_MANAGER, "notifyContinuousFrameLost", "(III)V"))
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, continueFrameLostCycle, continueFrameLostThreshold, times);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

// static
void EngineDataManager::notifyLowFps(int lowFpsCycle, float lowFpsThreshold, int frames)
{
    if (!_isSupported)
        return;

    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME_ENGINE_DATA_MANAGER, "notifyLowFps", "(IFI)V"))
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, lowFpsCycle, lowFpsThreshold, frames);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

// static
void EngineDataManager::notifyFpsChanged(float oldFps, float newFps)
{
    if (!_isSupported)
        return;

    LOGD("notifyFpsChanged: %.0f -> %.0f", oldFps, newFps);
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME_ENGINE_DATA_MANAGER, "notifyFpsChanged", "(FF)V"))
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, oldFps, newFps);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void EngineDataManager::nativeOnQueryFps(JNIEnv* env, jobject thiz, jintArray arrExpectedFps, jintArray arrRealFps)
{
    if (!_isSupported)
        return;
    
    jsize arrLenExpectedFps = env->GetArrayLength(arrExpectedFps);
    jsize arrLenRealFps = env->GetArrayLength(arrRealFps);

    if (arrLenExpectedFps > 0 && arrLenRealFps > 0)
    {
        Director* director = Director::getInstance();
        jboolean isCopy = JNI_FALSE;
        jint* expectedFps = env->GetIntArrayElements(arrExpectedFps, &isCopy);
        float animationInterval = director->getAnimationInterval();
        *expectedFps = (int)std::ceil(1.0f / animationInterval);
        
        jint* realFps = env->GetIntArrayElements(arrRealFps, &isCopy);
        *realFps = (int)std::ceil(director->getFrameRate());

        // Log before expectedFps & realFps is released.
        LOGD("nativeOnQueryFps, realFps: %d, expected: %d", *realFps, *expectedFps);
        env->ReleaseIntArrayElements(arrExpectedFps, expectedFps, 0);
        env->ReleaseIntArrayElements(arrRealFps, realFps, 0);
    }
    else
    {
        LOGE("Invalid array size, expectedFps.size=%d, realFps.size=%d", arrLenExpectedFps, arrLenRealFps);
    }
}

void EngineDataManager::nativeOnChangeContinuousFrameLostConfig(JNIEnv* env, jobject thiz, jint continueFrameLostCycle, jint continueFrameLostThreshold)
{
    if (!_isSupported)
        return;

    LOGD("nativeOnChangeContinuousFrameLostConfig, continueFrameLostCycle: %d, continueFrameLostThreshold: %d", continueFrameLostCycle, continueFrameLostThreshold);

    _continuousFrameLostCycle = continueFrameLostCycle;
    _continuousFrameLostThreshold = continueFrameLostThreshold;
}

void EngineDataManager::nativeOnChangeLowFpsConfig(JNIEnv* env, jobject thiz, jint lowFpsCycle, jfloat lowFpsThreshold)
{
    if (!_isSupported)
        return;

    LOGD("nativeOnChangeLowFpsConfig, lowFpsCycle: %d, lowFpsThreshold: %f", lowFpsCycle, lowFpsThreshold);
    _lowFpsCycle = lowFpsCycle;
    _lowFpsThreshold = lowFpsThreshold;
}

void EngineDataManager::nativeOnChangeExpectedFps(JNIEnv* env, jobject thiz, jint fps)
{
    if (!_isSupported)
        return;

    if (fps < -1 || fps > 60)
    {
        LOGE("Setting fps (%d) isn't supported!", fps);
        return;
    }

    auto director = cocos2d::Director::getInstance();
    float defaultAnimationInterval = director->getAnimationInterval();

    int defaultFps = static_cast<int>(std::ceil(1.0f/defaultAnimationInterval));

    if (fps > defaultFps)
    {
        LOGD("nativeOnChangeExpectedFps, fps (%d) is greater than default fps (%d), reset it to default!", fps, defaultFps);
        fps = -1;
    }

    LOGD("nativeOnChangeExpectedFps, set fps: %d, default fps: %d", fps, defaultFps);

    if (fps > 0)
    {
        setAnimationIntervalBySystem(1.0f/fps);
        LOGD("nativeOnChangeExpectedFps, fps (%d) was set successfuly!", fps);
    }
    else if (fps == -1) // -1 means to reset to default FPS
    {
        setAnimationIntervalBySystem(-1.0f);
        LOGD("nativeOnChangeExpectedFps, fps (%d) was reset successfuly!", defaultFps);
    }
}

void EngineDataManager::nativeOnChangeSpecialEffectLevel(JNIEnv* env, jobject thiz, jint level)
{
    if (!_isSupported)
        return;

    LOGD("nativeOnChangeSpecialEffectLevel, set level: %d", level);

    if (level < 0 || level >= CARRAY_SIZE(_particleLevelArr))
    {
        LOGE("Pass a wrong level value: %d, only 0 ~ %d is supported!", level, CARRAY_SIZE(_particleLevelArr) - 1);
        return;
    }

    ParticleSystem::setTotalParticleCountFactor(_particleLevelArr[level]);
}

void EngineDataManager::nativeOnChangeMuteEnabled(JNIEnv* env, jobject thiz, jboolean isMuteEnabled)
{
    if (!_isSupported)
        return;

    LOGD("nativeOnChangeMuteEnabled, isMuteEnabled: %d", isMuteEnabled);
    cocos2d::experimental::AudioEngine::setEnabled(!isMuteEnabled);
}

} // namespace cocos2d {

/////////////////////////////
extern "C" {

JNIEXPORT void JNICALL JNI_FUNC_PREFIX(nativeSetSupportOptimization)(JNIEnv* env, jobject thiz, jboolean isSupported)
{
    LOGD("nativeSetSupportOptimization: %d", isSupported);
    _isSupported = (isSupported == JNI_TRUE);
}

JNIEXPORT void JNICALL JNI_FUNC_PREFIX(nativeOnQueryFps)(JNIEnv* env, jobject thiz, jintArray arrExpectedFps, jintArray arrRealFps)
{
    EngineDataManager::nativeOnQueryFps(env, thiz, arrExpectedFps, arrRealFps);
}

JNIEXPORT void JNICALL JNI_FUNC_PREFIX(nativeOnChangeContinuousFrameLostConfig)(JNIEnv* env, jobject thiz, jint continueFrameLostCycle, jint continueFrameLostThreshold)
{
    EngineDataManager::nativeOnChangeContinuousFrameLostConfig(env, thiz, continueFrameLostCycle, continueFrameLostThreshold);
}

JNIEXPORT void JNICALL JNI_FUNC_PREFIX(nativeOnChangeLowFpsConfig)(JNIEnv* env, jobject thiz, jint lowFpsCycle, jfloat lowFpsThreshold)
{
    EngineDataManager::nativeOnChangeLowFpsConfig(env, thiz, lowFpsCycle, lowFpsThreshold);
}

JNIEXPORT void JNICALL JNI_FUNC_PREFIX(nativeOnChangeExpectedFps)(JNIEnv* env, jobject thiz, jint fps)
{
    EngineDataManager::nativeOnChangeExpectedFps(env, thiz, fps);
}

JNIEXPORT void JNICALL JNI_FUNC_PREFIX(nativeOnChangeSpecialEffectLevel)(JNIEnv* env, jobject thiz, jint level)
{
    EngineDataManager::nativeOnChangeSpecialEffectLevel(env, thiz, level);
}

JNIEXPORT void JNICALL JNI_FUNC_PREFIX(nativeOnChangeMuteEnabled)(JNIEnv* env, jobject thiz, jboolean enabled)
{
    EngineDataManager::nativeOnChangeMuteEnabled(env, thiz, enabled);
}
/////////////////////////////

} // extern "C" {
