
#include "crypto/CCCrypto.h"

NS_CC_EXTRA_BEGIN

int Crypto::getAES256KeyLength(void)
{
    CCLOG("Crypto::getAES256KeyLength() - not support this platform.");
    return 0;
}

int Crypto::cryptAES256(bool isDecrypt,
                          unsigned char* input,
                          int inputLength,
                          unsigned char* output,
                          int outputBufferLength,
                          unsigned char* key,
                          int keyLength)
{
    CCLOG("Crypto::cryptAES256() - not support this platform.");
    return 0;
}

NS_CC_EXTRA_END
