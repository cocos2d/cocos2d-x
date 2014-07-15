#include "cocos2d.h"
extern "C" {
#include "lua.h"
#include "xxtea.h"
}
#include "CCLuaEngine.h"
#include "HelperFunc.h"


USING_NS_CC;

unsigned char* HelperFunc::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    ssize_t size;
    unsigned char* buf = FileUtils::getInstance()->getFileData(pszFileName, pszMode, &size);
    if (NULL==buf || size<1) return NULL;
    
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    if (NULL==stack) {
        return NULL;
    }
    int xxteaKeyLen = 0;
    const char *xxteaKey = stack->getXXTEAKey(&xxteaKeyLen);
    int xxteaSignLen = 0;
    const char *xxteaSign = stack->getXXTEASign(&xxteaSignLen);
    if (!xxteaKey || !xxteaSign) {
        return NULL;
    }
    
	unsigned char* buffer = NULL;
    bool isXXTEA = true;
    for (int i = 0; isXXTEA && i<xxteaSignLen && i<size; ++i) {
            isXXTEA = buf[i] == xxteaSign[i];
    }

    if (isXXTEA) { // decrypt XXTEA
        xxtea_long len = 0;
        buffer = xxtea_decrypt(
                    buf + xxteaSignLen,
                    (xxtea_long)size - (xxtea_long)xxteaSignLen,
                    (unsigned char*)xxteaKey,
                    (xxtea_long)xxteaKeyLen,
                    &len);
        delete []buf;
        buf = NULL;
        size = len;
    } else {
        buffer = buf;
    }

    if (pSize) *pSize = size;
    return buffer;
}

int HelperFunc::getFileData(const char *pPathFile)
{
    unsigned long size;
    unsigned char* buf = HelperFunc::getFileData(pPathFile, "rb", &size);
    
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	stack->clean();
    if (buf) {
        stack->pushString((const char*)(buf), (int)size);
        delete buf;
    } else {
        stack->pushNil();
    }
    return 1;
}
