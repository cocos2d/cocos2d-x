#ifndef Cocos2Dx_ZJF_HelperFunc_h
#define Cocos2Dx_ZJF_HelperFunc_h

#include "base/CCData.h"

NS_CC_BEGIN

class HelperFunc
{
public:
    static int getFileData(const char *pPathFile);
    static unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
    static Data getData(const std::string& filename);

private:

};

NS_CC_END

#endif //Cocos2Dx_ZJF_HelperFunc_h
