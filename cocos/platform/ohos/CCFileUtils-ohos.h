#ifndef __CC_FILEUTILS_OHOS_H__
#define __CC_FILEUTILS_OHOS_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "napi/modules/RawFileUtils.h"

NS_CC_BEGIN

class ZipFile;

/**
 * @addtogroup platform
 * @{
 */

//! @brief  Helper class to handle file operations
class CC_DLL FileUtilsOhos : public FileUtils
{
    friend class FileUtils;
public:
    FileUtilsOhos();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~FileUtilsOhos();

    static void setassetmanager(NativeResourceManager* a);
    static NativeResourceManager* getAssetManager() { return nativeResourceManager_; }
    static ZipFile* getObbFile() { return obbfile; }
    FileUtils::Status getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor);

    /* override functions */
    bool init() override;

    virtual FileUtils::Status getContents(const std::string& filename, ResizableBuffer* buffer);

    virtual std::string getWritablePath() const override;
    virtual bool isAbsolutePath(const std::string& strPath) const override;
    
    virtual long getFileSize(const std::string& filepath);
    static std::string ohWritablePath;
private:
    virtual bool isFileExistInternal(const std::string& strFilePath) const override;
    virtual bool isDirectoryExistInternal(const std::string& dirPath) const override;

    static NativeResourceManager* nativeResourceManager_;
    static ZipFile* obbfile;
};

// end of platform group
/// @}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#endif    // __CC_FILEUTILS_OHOS_H__

