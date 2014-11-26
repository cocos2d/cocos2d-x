
#ifndef __CC_EXTENSION_CCCRYPTO_H_
#define __CC_EXTENSION_CCCRYPTO_H_

#include "cocos2dx_extra.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

NS_CC_EXTRA_BEGIN

class Crypto
{
public:
    static const int MD5_BUFFER_LENGTH = 16;
    
    /** @brief Return AES256 key length */
    static int getAES256KeyLength(void);
    
    /** @brief Encrypt data with AES256 algorithm, return ciphertext length */
    static int encryptAES256(unsigned char* plaintext,
                             int plaintextLength,
                             unsigned char* ciphertext,
                             int ciphertextBufferLength,
                             unsigned char* key,
                             int keyLength)
    {
        return cryptAES256(false, plaintext, plaintextLength, ciphertext, ciphertextBufferLength, key, keyLength);
    }
    
    /** @brief Decrypt data with AES256 algorithm, return plaintext length */
    static int decryptAES256(unsigned char* ciphertext,
                             int ciphertextLength,
                             unsigned char* plaintext,
                             int plaintextBufferLength,
                             unsigned char* key,
                             int keyLength)
    {
        return cryptAES256(true, ciphertext, ciphertextLength, plaintext, plaintextBufferLength, key, keyLength);
    }
    
    /** @brief Encrypt data with XXTEA algorithm, return ciphertext, free ciphertext after used */
    static unsigned char* encryptXXTEA(unsigned char* plaintext,
                                       int plaintextLength,
                                       unsigned char* key,
                                       int keyLength,
                                       int* resultLength);
    
    /** @brief Decrypt data with XXTEA algorithm, return plaintext, free plaintext after used */
    static unsigned char* decryptXXTEA(unsigned char* ciphertext,
                                       int ciphertextLength,
                                       unsigned char* key,
                                       int keyLength,
                                       int* resultLength);

    /** @brief Get length of encoding data with Base64 algorithm */
    static int encodeBase64Len(const char* input, int inputLength);
    
    /** @brief Encoding data with Base64 algorithm, return encoded string length */
    static int encodeBase64(const char* input, int inputLength,
                            char* output, int outputBufferLength);
    
    /** @brief Get length of Decoding Base 64 */
    static int decodeBase64Len(const char* input);

    /** @brief Decoding Base64 string to data, return decoded data length */
    static int decodeBase64(const char* input,
                            char* output, int outputBufferLength);
    
    /** @brief Calculate MD5, get MD5 code (not string) */
    static void MD5(void* input, int inputLength,
                    unsigned char* output);
    
    static void MD5File(const char* path, unsigned char* output);
    
    

    static const std::string MD5String(void* input, int inputLength);
    
#pragma mark -
#pragma mark for Lua
    
#if CC_LUA_ENGINE_ENABLED > 0
    
    /** @brief Encrypt data with AES256 algorithm, return ciphertext string, return nil if failed */
    static LUA_STRING encryptAES256Lua(const char* plaintext,
                                       int plaintextLength,
                                       const char* key,
                                       int keyLength)
    {
        return cryptAES256Lua(false, plaintext, plaintextLength, key, keyLength);
    }
    
    /** @brief Decrypt data with AES256 algorithm, return plaintext string, return nil if failed */
    static LUA_STRING decryptAES256Lua(const char* ciphertext,
                                       int ciphertextLength,
                                       const char* key,
                                       int keyLength)
    {
        return cryptAES256Lua(true, ciphertext, ciphertextLength, key, keyLength);
    }
    
    /** @brief Encrypt data with XXTEA algorithm, return ciphertext string and length, return nil if failed */
    static LUA_STRING encryptXXTEALua(const char* plaintext,
                                      int plaintextLength,
                                      const char* key,
                                      int keyLength);
    
    /** @brief Decrypt data with XXTEA algorithm, return plaintext string and length, return nil if failed */
    static LUA_STRING decryptXXTEALua(const char* ciphertext,
                                      int ciphertextLength,
                                      const char* key,
                                      int keyLength);
    
    /** @brief Encoding data with Base64 algorithm, return encoded string */
    static LUA_STRING encodeBase64Lua(const char* input, int inputLength)
    {
        return encodingBase64Lua(false, input, inputLength);
    }
    
    /** @brief Decoding Base64 string to data, return decoded data length */
    static LUA_STRING decodeBase64Lua(const char* input)
    {
        return encodingBase64Lua(true, input, (int)strlen(input));
    }
    
    /** @brief Calculate MD5, return MD5 string */
    static LUA_STRING MD5Lua(const char* input, bool isRawOutput);

    static LUA_STRING MD5FileLua(const char* path);

#endif /* CC_LUA_ENGINE_ENABLED */
    
#pragma mark -
#pragma mark private methods
    
private:
    Crypto(void) {}
    
    static int cryptAES256(bool isDecrypt,
                           unsigned char* input,
                           int inputLength,
                           unsigned char* output,
                           int outputBufferLength,
                           unsigned char* key,
                           int keyLength);
    
#if CC_LUA_ENGINE_ENABLED > 0
    static LUA_STRING cryptAES256Lua(bool isDecrypt,
                                     const char* input,
                                     int inputLength,
                                     const char* key,
                                     int keyLength);
    
    static LUA_STRING encodingBase64Lua(bool isDecoding,
                                        const char* input,
                                        int inputLength);
    
    static char* bin2hex(unsigned char* bin, int binLength);
#endif /* CC_LUA_ENGINE_ENABLED */
    
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCCRYPTO_H_
