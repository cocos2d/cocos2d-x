#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include "TG3.h"

/**
@class FileUtils
@brief Offer tools of file system
*/
class FileUtils
{
public:
    /**
    @brief Whether the file is existed or not
    @param pFilePath The absolute path of file.
    @return If existed return true,or return false
    */
    static bool isFileExisted(const char* pFilePath)
    {
        TUChar fileName[MAX_PATH] = {0};
        TUString::StrGBToUnicode(fileName, (const Char*)pFilePath);

        Boolean bExisted = EOS_IsFileExist(fileName);

        return bExisted ? true : false;
    }
};

#endif
