#include "cocos2d.h"
extern "C" {
#include "lua.h"
#include "xxtea.h"
}
#include "CCLuaEngine.h"
#include "HelperFunc.h"


USING_NS_CC;

unsigned char* CZHelperFunc::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    ssize_t size;
    unsigned char* buf = FileUtils::getInstance()->getFileData(pszFileName, pszMode, &size);
    if (NULL==buf || size<1) return NULL;
    
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	unsigned char* buffer = NULL;

        bool isXXTEA = stack && stack->_xxteaEnabled;
        for (unsigned int i = 0; isXXTEA && ((int)i) < stack->_xxteaSignLen && i < size; ++i)
        {
            isXXTEA = buf[i] == stack->_xxteaSign[i];
        }

        if (isXXTEA)
        {
            // decrypt XXTEA
            xxtea_long len = 0;
            buffer = xxtea_decrypt(buf + stack->_xxteaSignLen,
                                   (xxtea_long)size - (xxtea_long)stack->_xxteaSignLen,
                                   (unsigned char*)stack->_xxteaKey,
                                   (xxtea_long)stack->_xxteaKeyLen,
                                   &len);
            delete []buf;
            buf = NULL;
			size = len;
        }
        else
        {
			buffer = buf;
        }

		if (pSize) *pSize = size;
		return buffer;
}

int CZHelperFunc::getFileData(const char *pPathFile)
{
    unsigned long size;
    unsigned char* buf = CZHelperFunc::getFileData(pPathFile, "rb", &size);
    if (NULL==buf) return 0;
    
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	stack->clean();
    stack->pushString((const char*)(buf), size);
    delete buf;
    return 1;
}
