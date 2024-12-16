#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/ohos/CCFileUtils-ohos.h"
#include "platform/CCCommon.h"
#include "platform/ohos/CCLogOhos.h"
#include <stdlib.h>

using namespace std;

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
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = nullptr;
        }
    }
    return s_sharedFileUtils;
}

FileUtilsOhos::FileUtilsOhos() {
}

FileUtilsOhos::~FileUtilsOhos() {
}

bool FileUtilsOhos::init() {
    _defaultResRootPath = "";
    return FileUtils::init();
}

bool FileUtilsOhos::isFileExist(const std::string& filename) const {
	if (isAbsolutePath(filename)) {
        return isFileExistInternal(filename);
    }
    std::string fullpath = const_cast<FileUtilsOhos*>(this)->fullPathForFilename(filename);
    return !fullpath.empty();
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
    } else  {
        FILE *fp = fopen(strFilePath.c_str(), "r");
        if (fp) {
            bFound = true;
            fclose(fp);
        }
    }
    return bFound;
}

bool FileUtilsOhos::isAbsolutePath(const std::string& dirPath) const {
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

std::vector<std::string> FileUtilsOhos::listFiles(const std::string& dirPath) {
    return RawFileUtils::GetInstance().searchFiles(dirPath.c_str(), false);
}

Data FileUtilsOhos::getData(const std::string& filename) {
    if (filename.empty()) {
        return Data::Null;
    }
    
    unsigned char* data = nullptr;
    ssize_t size = 0;

    std::string fullpath = fullPathForFilename(filename);
    do {
        if(isAbsolutePath(fullpath)) {
            FILE *fp = fopen(fullpath.c_str(), "r");
            if (!fp) break;
#if defined(_MSC_VER)
            auto descriptor = _fileno(fp);
#else
            auto descriptor = fileno(fp);
#endif
            struct stat statBuf;
            if (fstat(descriptor, &statBuf) == -1) {
                fclose(fp);
                break;
            }
            ssize_t fileSize = statBuf.st_size;
            data = new unsigned char[fileSize];
            size = fread(data, 1, fileSize, fp);
            fclose(fp);
        } else {
            RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());
            CC_BREAK_IF(!fp);
            ssize_t fileSize = RawFileUtils::GetInstance().GetSize(fp);
            data = new unsigned char[fileSize];
            fileSize = RawFileUtils::GetInstance().Read(fp, data, fileSize);
            RawFileUtils::GetInstance().Close(fp);
            size = fileSize;
        }
    } while (0);
    
    Data ret;
    if (data == nullptr || size == 0) {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        OHOS_LOGD("%{public}s", msg.c_str());
    } else {
        ret.fastSet(data, size);
    }

    return ret;
}

bool FileUtilsOhos::getContents(const std::string& filename, ResizableBuffer* buffer) {
    if (filename.empty()) {
        OHOS_LOGD("FileUtilsOhos::getContents() - filename is empty");
        return false;
    }

    std::string fullpath = isAbsolutePath(filename)? filename:fullPathForFilename(filename);

    if (fullpath[0] == '/') {
        FILE *fp = fopen(fullpath.c_str(), "rb");
        if (!fp)
            return false;

#if defined(_MSC_VER)
        auto descriptor = _fileno(fp);
#else
        auto descriptor = fileno(fp);
#endif
        struct stat statBuf;
        if (fstat(descriptor, &statBuf) == -1) {
            fclose(fp);
            return false;
        }
        size_t size = statBuf.st_size;

        buffer->resize(size);
        size_t readsize = fread(buffer->buffer(), 1, size, fp);
        fclose(fp);

        if (readsize < size) {
            buffer->resize(readsize);
            return false;
        }
    } else {
        RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());
        if (!fp) {
            OHOS_LOGD("FileUtilsOhos::fp is nullptr");
            return false;
        }
        auto size = RawFileUtils::GetInstance().GetSize(fp);
        buffer->resize(size);

        int readsize = RawFileUtils::GetInstance().Read(fp, buffer->buffer(), size);
        RawFileUtils::GetInstance().Close(fp);

        if (readsize < size) {
            if (readsize >= 0)
                buffer->resize(readsize);
                OHOS_LOGD("FileUtilsOhos::getContents() - readsize < size");
                return false;
        }

        if (!buffer->buffer()) {
            std::string msg = "Get data from file(" + filename + ") failed!";
            OHOS_LOGI("%{public}s", msg.c_str());
        }
    }

    return true;
}

std::string FileUtilsOhos::getStringFromFile(const std::string& filename) {
    std::string s;
    getContents(filename, &s);
    return s;
}
    
Data FileUtilsOhos::getDataFromFile(const std::string& filename) {
    Data d;
    getContents(filename, &d);
    return d;
}

unsigned char* FileUtilsOhos::getFileData(const std::string& filename, const char* mode, ssize_t * size) {    
    unsigned char * data = 0;
    
    if ( filename.empty() || (! mode) ) {
        return 0;
    }

    std::string fullpath = isAbsolutePath(filename)? filename:fullPathForFilename(filename);

    if(fullpath[0] == '/') {
        do {
            // read rrom other path than user set it
            //CCLOG("GETTING FILE ABSOLUTE DATA: %s", filename);
            FILE *fp = fopen(fullpath.c_str(), mode);
            CC_BREAK_IF(!fp);

            long fileSize;
            fseek(fp,0,SEEK_END);
            fileSize = ftell(fp);
            fseek(fp,0,SEEK_SET);
            data = (unsigned char*) malloc(fileSize);
            fileSize = fread(data,sizeof(unsigned char), fileSize,fp);
            fclose(fp);

            if (size) {
                *size = fileSize;
            }
        } while (0);
    } else {
        do{
            RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());
            CC_BREAK_IF(!fp);
            ssize_t fileSize = RawFileUtils::GetInstance().GetSize(fp);
            data = new unsigned char[fileSize];
            fileSize = RawFileUtils::GetInstance().Read(fp, data, fileSize);
            RawFileUtils::GetInstance().Close(fp);

            if (size) {
                *size = fileSize;
            }
        } while (0);
    }

    if (! data) {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        OHOS_LOGD("%{public}s", msg.c_str());
    }
    return data;
}

bool FileUtilsOhos::getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor) {
    if (filename.empty()) {
        return false;
    }
    std::string fullpath = isAbsolutePath(filename)? filename:fullPathForFilename(filename);

    RawFile *fp = RawFileUtils::GetInstance().Open(fullpath.c_str());//fopen(strFilePath.c_str(), "r");
    if (!fp) {
        OHOS_LOGE("FileUtilsOhos::fp is nullptr");
        return false;
    }

    bool result = RawFileUtils::GetInstance().GetRawFileDescriptor(fp, descriptor);
    RawFileUtils::GetInstance().Close(fp);
    return result;
}

string FileUtilsOhos::getWritablePath() const {
    return ohWritablePath;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
