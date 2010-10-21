#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include "TG3.h"

class FileUtils
{
public:
    static bool isFileExisted(const char* pFilePath)
    {
        TUChar fileName[MAX_PATH] = {0};
        TUString::StrGBToUnicode(fileName, (const Char*)pFilePath);

        Boolean bExisted = EOS_IsFileExist(fileName);

        return bExisted ? true : false;
    }
};

#endif
