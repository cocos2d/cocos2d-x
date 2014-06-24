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
    unsigned long size;
    unsigned char* buf = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, &size);
    if (NULL==buf || size<1) return NULL;
    
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	unsigned char* buffer = NULL;

        bool isXXTEA = stack && stack->m_xxteaEnabled;
        for (unsigned int i = 0; isXXTEA && ((int)i) < stack->m_xxteaSignLen && i < size; ++i)
        {
            isXXTEA = buf[i] == stack->m_xxteaSign[i];
        }

        if (isXXTEA)
        {
            // decrypt XXTEA
            xxtea_long len = 0;
            buffer = xxtea_decrypt(buf + stack->m_xxteaSignLen,
                                   (xxtea_long)size - (xxtea_long)stack->m_xxteaSignLen,
                                   (unsigned char*)stack->m_xxteaKey,
                                   (xxtea_long)stack->m_xxteaKeyLen,
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
