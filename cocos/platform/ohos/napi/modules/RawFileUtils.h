#ifndef __RawFileUtils_H__
#define __RawFileUtils_H__


#include <string>
#include <unordered_map>

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <napi/native_api.h>
#include <uv.h>

#include "../common/native_common.h"

#include <rawfile/raw_dir.h>
#include <rawfile/raw_file.h>
#include <rawfile/raw_file_manager.h>

class RawFileUtils
{
public:
    static bool InitResourceManager(napi_env env, napi_value info);
    
    static napi_value nativeResourceManagerInit(napi_env env, napi_callback_info info) {
        size_t      argc = 1;
        napi_value  args[1];
        NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
        InitResourceManager(env, args[0]);
        return nullptr;
    }
    
    static RawFileUtils& GetInstance() {
        static RawFileUtils instance;
        return instance;
    }

    RawFile *Open(const char *fileName) {
        return OH_ResourceManager_OpenRawFile(nativeResourceManager_, fileName);
    }

    RawDir *OpenDir(const char *dirName) {
        return OH_ResourceManager_OpenRawDir(nativeResourceManager_, dirName);
    }

    void Close(RawFile *file) {
        return OH_ResourceManager_CloseRawFile(file);
    }
    
    void CloseDir(RawDir *rawDir) {
        return OH_ResourceManager_CloseRawDir(rawDir);
    }

    int Seek(const RawFile *file, long offset, int whence) {
        return OH_ResourceManager_SeekRawFile(file, offset, whence);
    }

    long GetSize(RawFile* file) {
        return OH_ResourceManager_GetRawFileSize(file);
    }

    long Read(RawFile *file, void* buf, size_t length) {
        return OH_ResourceManager_ReadRawFile(file, buf, length);
    }

    int GetDirSize(RawDir* rawDir) {
        return OH_ResourceManager_GetRawFileCount(rawDir);
    }

    bool GetRawFileDescriptor(RawFile *file, RawFileDescriptor &descriptor) {
        return OH_ResourceManager_GetRawFileDescriptor(file, descriptor);
    }

    bool ReleaseRawFileDescriptor(RawFileDescriptor &descriptor) {
       return OH_ResourceManager_ReleaseRawFileDescriptor(descriptor);
    }
    
    std::vector<std::string> searchFiles(const char *folder, bool recursive = false);

    static NativeResourceManager* GetRM() { return nativeResourceManager_;}
    
private:
    static NativeResourceManager* nativeResourceManager_;
};



#endif // __RawFileUtils_H__
