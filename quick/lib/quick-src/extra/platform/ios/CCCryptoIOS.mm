
#include "crypto/CCCrypto.h"

#if CC_LUA_ENGINE_ENABLED > 0
extern "C" {
#include "lua.h"
}
#include "tolua_fix.h"
#endif

#import <CommonCrypto/CommonCryptor.h>

NS_CC_EXTRA_BEGIN

int Crypto::getAES256KeyLength(void)
{
    return kCCKeySizeAES256;
}

int Crypto::cryptAES256(bool isDecrypt,
                          unsigned char* input,
                          int inputLength,
                          unsigned char* output,
                          int outputBufferLength,
                          unsigned char* key,
                          int keyLength)
{
    int maxKeyLength = getAES256KeyLength();
    unsigned char key_[maxKeyLength];
    memset(key_, 0, sizeof(key_));
    memcpy(key_, key, keyLength > maxKeyLength ? maxKeyLength : keyLength);

    int bufferSize = inputLength + kCCBlockSizeAES128;
    void* buffer = malloc(bufferSize);
    size_t dataUsed = 0;

    CCCryptorStatus status = CCCrypt(isDecrypt ? kCCDecrypt : kCCEncrypt,
                                     kCCAlgorithmAES128,
                                     kCCOptionPKCS7Padding | kCCOptionECBMode,
                                     key_, maxKeyLength,
                                     NULL,
                                     input, inputLength,
                                     buffer, bufferSize,
                                     &dataUsed);

    if (status == kCCSuccess)
    {
        if (outputBufferLength >= dataUsed + 1)
        {
            memset(output, 0, outputBufferLength);
            memcpy(output, buffer, dataUsed);
            return dataUsed;
        }
        // output buffer too small
        return 0;
    }

    switch (status)
    {
        case kCCParamError:
            CCLOG("[Crypto] cryptAES256(%s) param error", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCBufferTooSmall:
            CCLOG("[Crypto] cryptAES256(%s) buffer too small", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCMemoryFailure:
            CCLOG("[Crypto] cryptAES256(%s) memory failure", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCAlignmentError:
            CCLOG("[Crypto] cryptAES256(%s) alignment error", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCDecodeError:
            CCLOG("[Crypto] cryptAES256(%s) decode error", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        case kCCUnimplemented:
            CCLOG("[Crypto] cryptAES256(%s) unimplemented", isDecrypt ? "Decrypt" : "Encrypt");
            break;
        default:
            CCLOG("[Crypto] cryptAES256(%s) unknown error", isDecrypt ? "Decrypt" : "Encrypt");
    }

    return 0;
}

NS_CC_EXTRA_END
