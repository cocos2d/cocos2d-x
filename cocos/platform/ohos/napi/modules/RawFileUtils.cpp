#include <stdint.h>
#include <string>
#include <stdio.h>

#include <ace/xcomponent/native_interface_xcomponent.h>

#include "platform/ohos/napi/plugin_manager.h"
#include "../../CCLogOhos.h"

#include <js_native_api_types.h>
#include "RawFileUtils.h"


NativeResourceManager* RawFileUtils::nativeResourceManager_ = nullptr;

bool RawFileUtils::InitResourceManager(napi_env env, napi_value param) {
    nativeResourceManager_ = OH_ResourceManager_InitNativeResourceManager(env, param);
    OHOS_LOGD("cocos qgh  initResourceManager %{public}p", nativeResourceManager_);
    return true;
}

std::vector<std::string> RawFileUtils::searchFiles(const char *folder, bool recursive) {
    std::vector<std::string> results;
    char *realFolder = const_cast<char*> (folder);
    if (strcmp(folder, "/") == 0) {
        realFolder = "";
    }
    auto dir = OH_ResourceManager_OpenRawDir(nativeResourceManager_, realFolder);
    if (dir) {
        int file_count = GetDirSize(dir);
        for (int index = 0; index < file_count; index++) {
            std::string fileName = OH_ResourceManager_GetRawFileName(dir, index);
            auto item = std::string(realFolder) + "/" + fileName;
            results.push_back(item);
            if (recursive) {
                auto items = searchFiles(item.c_str(), recursive);
                results.insert(results.end(), items.begin(), items.end());
            }
        }
        OH_ResourceManager_CloseRawDir(dir);
    }
    return results;
}