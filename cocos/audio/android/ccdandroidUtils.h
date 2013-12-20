#ifndef __CCDANDROIDUTILS_H__
#define __CCDANDROIDUTILS_H__

#include <string>

namespace CocosDenshion {
    namespace android {
        bool is_buggy_device(void);
        std::string getFullPathWithoutAssetsPrefix(const char* pszFilename);
    }
}

#endif //__CCDANDROIDUTILS_H__
