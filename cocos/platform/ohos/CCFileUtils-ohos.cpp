#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/ohos/CCFileUtils-ohos.h"
#include "platform/CCCommon.h"
#include "base/ZipUtils.h"
#include "platform/ohos/CCLogOhos.h"

#include <stdlib.h>
#include <sys/stat.h>

using namespace std;

#define DECLARE_GUARD std::lock_guard<std::recursive_mutex> mutexGuard(mutex)

NS_CC_BEGIN
NativeResourceManager* FileUtilsOhos::nativeResourceManager_ = nullptr;
string FileUtilsOhos::ohWritablePath;

void FileUtilsOhos::setassetmanager(NativeResourceManager* a) {
    if (nullptr == a) {
        return;
    }

    cocos2d::FileUtilsOhos::nativeResourceManager_ = a;
}

FileUtils* FileUtils::getInstance() {
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsOhos();
        s_sharedFileUtils->init();
        std::string resourcePath("");
    }
    return s_sharedFileUtils;
}

FileUtilsOhos::FileUtilsOhos() {
}

FileUtilsOhos::~FileUtilsOhos() {
}

bool FileUtilsOhos::init() {
    DECLARE_GUARD;
    _defaultResRootPath = "";   
    OHOS_LOGI("FileUtilsOhos::init()");
    return FileUtils::init();
}

bool FileUtilsOhos::isFileExistInternal(const std::string& strFilePath) const {
    if (strFilePath.empty()) {
        return false;
    }

    bool bFound = false;
    if (strFilePath[0] != '/') {
        RawFile *fp = RawFileUtils::GetInstance().Open(strFilePath.c_str());
        if(fp) {
            OHOS_LOGI("FileUtilsOhos::isFileExistInternal() - open %{public}s success", strFilePath.c_str());
            bFound = true;
            RawFileUtils::GetInstance().Close(fp);
        }
    } else {
        FILE *fp = fopen(strFilePath.c_str(), "r");
        if (fp) {
            bFound = true;
            fclose(fp);
        }
    }
    return bFound;
}

bool FileUtilsOhos::isDirectoryExistInternal(const std::string& dirPath) const {
    if (dirPath.empty()) return false;
    std::string dirPathMf = dirPath[dirPath.length() - 1] == '/' ? dirPath.substr(0, dirPath.length() - 1) : dirPath;

    if (dirPathMf[0] == '/') {
        struct stat st;
        return stat(dirPathMf.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
    }

    if (dirPathMf.find(_defaultResRootPath) == 0) {
        dirPathMf = dirPathMf.substr(_defaultResRootPath.length(), dirPathMf.length());
    }

    RawDir* rawDir = RawFileUtils::GetInstance().OpenDir(dirPathMf.c_str());
    if(rawDir) {
        int file_count = RawFileUtils::GetInstance().GetDirSize(rawDir);
        RawFileUtils::GetInstance().CloseDir(rawDir);
        if (file_count) {
            return true;
        }
    }
    return false;
}

bool FileUtilsOhos::isAbsolutePath(const std::string& strPath) const {
    DECLARE_GUARD;
    if (strPath[0] == '/' || (!_defaultResRootPath.empty() && strPath.find(_defaultResRootPath) == 0)) {
        return true;
    }
    return false;
}

long FileUtilsOhos::getFileSize(const std::string& filepath) {
    DECLARE_GUARD;

    if(filepath[0] == '/') {
        return FileUtils::getFileSize(filepath);
    }

    RawFile *fp = RawFileUtils::GetInstance().Open(filepath.c_str());//fopen(strFilePath.c_str(), "r");
    OHOS_LOGI("FileUtilsOhos::getFileSize ===================> doGetFileData %{public}s", filepath.c_str());
    long size = RawFileUtils::GetInstance().GetSize(fp);
    RawFileUtils::GetInstance().Close(fp);
    if (size != -1) {
        return size;
    }
    return size;
}

std::vector<std::string> FileUtilsOhos::listFiles(const std::string& dirPath) {
    if(!dirPath.empty() && dirPath[0] == '/') {
        return FileUtils::listFiles(dirPath);
    }
    return RawFileUtils::GetInstance().searchFiles(dirPath.c_str(), false);
}

FileUtils::Status FileUtilsOhos::getContents(const std::string& filename, ResizableBuffer* buffer) {
    if (filename.empty()) {
        OHOS_LOGD("FileUtilsOhos::getContents() - filename is empty");
        return FileUtils::Status::NotExists;
    }

    string fullPath = fullPathForFilename(filename);

    if (fullPath[0] == '/') {
        OHOS_LOGD("FileUtilsOhos::getContents() - fullPath[0] == '/'");
        return FileUtils::getContents(fullPath, buffer);
    }

    RawFile *fp = RawFileUtils::GetInstance().Open(fullPath.c_str());
    if (!fp) {
        OHOS_LOGD("FileUtilsOhos::fp is nullptr");
        return FileUtils::Status::NotInitialized;
    }
    auto size = RawFileUtils::GetInstance().GetSize(fp);
    buffer->resize(size);

    int readsize = RawFileUtils::GetInstance().Read(fp, buffer->buffer(), size);
    RawFileUtils::GetInstance().Close(fp);

    if (readsize < size) {
        if (readsize >= 0)
           buffer->resize(readsize);
           OHOS_LOGD("FileUtilsOhos::getContents() - readsize < size");
        return FileUtils::Status::ReadFailed;
    }

    if (!buffer->buffer())
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        OHOS_LOGD("%{public}s", msg.c_str());
    }

    return FileUtils::Status::OK;
}

FileUtils::Status FileUtilsOhos::getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor) {
    if (filename.empty()) {
        return FileUtils::Status::NotExists;
    }
    string fullPath = fullPathForFilename(filename);
    
    RawFile *fp = RawFileUtils::GetInstance().Open(fullPath.c_str());//fopen(strFilePath.c_str(), "r");
    if (!fp) {
        OHOS_LOGD("FileUtilsOhos::fp is nullptr");
        return FileUtils::Status::NotInitialized;
    }

    bool result = RawFileUtils::GetInstance().GetRawFileDescriptor(fp, descriptor);
    RawFileUtils::GetInstance().Close(fp);
    if (!result) {
        return FileUtils::Status::OpenFailed;
    }
    return FileUtils::Status::OK;
}

string FileUtilsOhos::getWritablePath() const {
    return ohWritablePath;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
