/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __SUPPORT_ZIPUTILS_H__
#define __SUPPORT_ZIPUTILS_H__
/// @cond DO_NOT_SHOW

#include <string>
#include "platform/CCPlatformConfig.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCPlatformDefine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/CCFileUtils-android.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
// for import ssize_t on win32 platform
#include "platform/CCStdC.h"
#endif

/**
 * @addtogroup base
 * @{
 */

namespace cocos2d
{
#ifndef _unz64_H
typedef struct unz_file_info_s unz_file_info;
#endif
    /** XXX: pragma pack ???
     * @struct CCZHeader
     */
    struct CCZHeader {
        unsigned char   sig[4];             /** Signature. Should be 'CCZ!' 4 bytes. */
        unsigned short  compression_type;   /** Should be 0. */
        unsigned short  version;            /** Should be 2 (although version type==1 is also supported). */
        unsigned int    reserved;           /** Reserved for users. */
        unsigned int    len;                /** Size of the uncompressed file. */
    };

    enum {
        CCZ_COMPRESSION_ZLIB,               /** zlib format. */
        CCZ_COMPRESSION_BZIP2,              /** bzip2 format (not supported yet). */
        CCZ_COMPRESSION_GZIP,               /** gzip format (not supported yet). */
        CCZ_COMPRESSION_NONE,               /** plain (not supported yet). */
    };

    class CC_DLL ZipUtils
    {
    public:
        /** 
         * Inflates either zlib or gzip deflated memory. The inflated memory is expected to be freed by the caller.
         *
         * It will allocate 256k for the destination buffer. If it is not enough it will multiply the previous buffer size per 2, until there is enough memory.
         *
         * @return The length of the deflated buffer.
         * @since v0.8.1
         */
        CC_DEPRECATED_ATTRIBUTE static ssize_t ccInflateMemory(unsigned char *in, ssize_t inLength, unsigned char **out) { return inflateMemory(in, inLength, out); }
        static ssize_t inflateMemory(unsigned char *in, ssize_t inLength, unsigned char **out);

        /** 
        * Inflates either zlib or gzip deflated memory. The inflated memory is expected to be freed by the caller.
        *
        * @param outLenghtHint It is assumed to be the needed room to allocate the inflated buffer.
        *
        * @return The length of the deflated buffer.
        * @since v1.0.0
        */
        CC_DEPRECATED_ATTRIBUTE static ssize_t ccInflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t outLengthHint) { return inflateMemoryWithHint(in, inLength, out, outLengthHint); }
        static ssize_t inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t outLengthHint);

        /** 
         * Inflates a GZip file into memory.
         *
         * @return The length of the deflated buffer.
         * @since v0.99.5
         */
        CC_DEPRECATED_ATTRIBUTE static int ccInflateGZipFile(const char *filename, unsigned char **out) { return inflateGZipFile(filename, out); }
        static int inflateGZipFile(const char *filename, unsigned char **out);
        
        /** 
         * Test a file is a GZip format file or not.
         *
         * @return True is a GZip format file. false is not.
         * @since v3.0
         */
        CC_DEPRECATED_ATTRIBUTE static bool ccIsGZipFile(const char *filename) { return isGZipFile(filename); }
        static bool isGZipFile(const char *filename);

        /** 
         * Test the buffer is GZip format or not.
         *
         * @return True is GZip format. false is not.
         * @since v3.0
         */
        CC_DEPRECATED_ATTRIBUTE static bool ccIsGZipBuffer(const unsigned char *buffer, ssize_t len) { return isGZipBuffer(buffer, len); }
        static bool isGZipBuffer(const unsigned char *buffer, ssize_t len);

        /** 
         * Inflates a CCZ file into memory.
         *
         * @return The length of the deflated buffer.
         * @since v0.99.5
         */
        CC_DEPRECATED_ATTRIBUTE static int ccInflateCCZFile(const char *filename, unsigned char **out) { return inflateCCZFile(filename, out); }
        static int inflateCCZFile(const char *filename, unsigned char **out);

        /** 
         * Inflates a buffer with CCZ format into memory.
         *
         * @return The length of the deflated buffer.
         * @since v3.0
         */
        CC_DEPRECATED_ATTRIBUTE static int ccInflateCCZBuffer(const unsigned char *buffer, ssize_t len, unsigned char **out) { return inflateCCZBuffer(buffer, len, out); }
        static int inflateCCZBuffer(const unsigned char *buffer, ssize_t len, unsigned char **out);
        
        /** 
         * Test a file is a CCZ format file or not.
         *
         * @return True is a CCZ format file. false is not.
         * @since v3.0
         */
        CC_DEPRECATED_ATTRIBUTE static bool ccIsCCZFile(const char *filename) { return isCCZFile(filename); }
        static bool isCCZFile(const char *filename);

        /** 
         * Test the buffer is CCZ format or not.
         *
         * @return True is CCZ format. false is not.
         * @since v3.0
         */
        CC_DEPRECATED_ATTRIBUTE static bool ccIsCCZBuffer(const unsigned char *buffer, ssize_t len) { return isCCZBuffer(buffer, len); }
        static bool isCCZBuffer(const unsigned char *buffer, ssize_t len);

        /** 
         * Sets the pvr.ccz encryption key parts separately for added security.
         *
         * Example: If the key used to encrypt the pvr.ccz file is
         * 0xaaaaaaaabbbbbbbbccccccccdddddddd you will call this function 4
         * different times, preferably from 4 different source files, as follows
         *
         * ZipUtils::setPvrEncryptionKeyPart(0, 0xaaaaaaaa);
         * ZipUtils::setPvrEncryptionKeyPart(1, 0xbbbbbbbb);
         * ZipUtils::setPvrEncryptionKeyPart(2, 0xcccccccc);
         * ZipUtils::setPvrEncryptionKeyPart(3, 0xdddddddd);
         *
         * Splitting the key into 4 parts and calling the function from 4 different source
         * files increases the difficulty to reverse engineer the encryption key.
         * Be aware that encrpytion is *never* 100% secure and the key code
         * can be cracked by knowledgable persons. 
         *
         * IMPORTANT: Be sure to call setPvrEncryptionKey or
         * setPvrEncryptionKeyPart with all of the key parts *before* loading
         * the sprite sheet or decryption will fail and the sprite sheet
         * will fail to load.
         *
         * @param index Part of the key [0..3].
         * @param value Value of the key part.
         */
        CC_DEPRECATED_ATTRIBUTE static void ccSetPvrEncryptionKeyPart(int index, unsigned int value) { setPvrEncryptionKeyPart(index, value); }
        static void setPvrEncryptionKeyPart(int index, unsigned int value);
        
        /** 
         * Sets the pvr.ccz encryption key.
         *
         * Example: If the key used to encrypt the pvr.ccz file is
         * 0xaaaaaaaabbbbbbbbccccccccdddddddd you will call this function with
         * the key split into 4 parts as follows
         *
         * ZipUtils::setPvrEncryptionKey(0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd);
         *
         * Note that using this function makes it easier to reverse engineer and discover
         * the complete key because the key parts are present in one function call.
         *
         * IMPORTANT: Be sure to call setPvrEncryptionKey or setPvrEncryptionKeyPart
         * with all of the key parts *before* loading the spritesheet or decryption
         * will fail and the sprite sheet will fail to load.
         *
         * @param keyPart1 The key value part 1.
         * @param keyPart2 The key value part 2.
         * @param keyPart3 The key value part 3.
         * @param keyPart4 The key value part 4.
         */
        CC_DEPRECATED_ATTRIBUTE static void ccSetPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4) { setPvrEncryptionKey(keyPart1, keyPart2, keyPart3, keyPart4); }
        static void setPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4);

    private:
        static int inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t *outLength, ssize_t outLenghtHint);
        static inline void decodeEncodedPvr (unsigned int *data, ssize_t len);
        static inline unsigned int checksumPvr(const unsigned int *data, ssize_t len);

        static unsigned int s_uEncryptedPvrKeyParts[4];
        static unsigned int s_uEncryptionKey[1024];
        static bool s_bEncryptionKeyIsValid;
    };

    // forward declaration
    class ZipFilePrivate;
    struct unz_file_info_s;

    /**
    * Zip file - reader helper class.
    *
    * It will cache the file list of a particular zip file with positions inside an archive,
    * so it would be much faster to read some particular files or to check their existance.
    *
    * @since v2.0.5
    */
    class CC_DLL ZipFile
    {
    public:
        /**
        * Constructor, open zip file and store file list.
        *
        * @param zipFile Zip file name
        * @param filter The first part of file names, which should be accessible.
        *               For example, "assets/". Other files will be missed.
        *
        * @since v2.0.5
        */
        ZipFile(const std::string &zipFile, const std::string &filter = std::string());
        virtual ~ZipFile();

        /**
        * Regenerate accessible file list based on a new filter string.
        *
        * @param filter New filter string (first part of files names)
        * @return true whenever zip file is open successfully and it is possible to locate
        *              at least the first file, false otherwise
        *
        * @since v2.0.5
        */
        bool setFilter(const std::string &filter);

        /**
        * Check does a file exists or not in zip file
        *
        * @param fileName File to be checked on existance
        * @return true whenever file exists, false otherwise
        *
        * @since v2.0.5
        */
        bool fileExists(const std::string &fileName) const;

        /**
        * Get resource file data from a zip file.
        * @param fileName File name
        * @param[out] pSize If the file read operation succeeds, it will be the data size, otherwise 0.
        * @return Upon success, a pointer to the data is returned, otherwise nullptr.
        * @warning Recall: you are responsible for calling free() on any Non-nullptr pointer returned.
        *
        * @since v2.0.5
        */
        unsigned char *getFileData(const std::string &fileName, ssize_t *size);

        std::string getFirstFilename();
        std::string getNextFilename();
        
        static ZipFile *createWithBuffer(const void* buffer, unsigned long size);
        
    private:
        /* Only used internal for createWithBuffer() */
        ZipFile();
        
        bool initWithBuffer(const void *buffer, unsigned long size);
        int getCurrentFileInfo(std::string *filename, unz_file_info *info);
        
        /** Internal data like zip file pointer / file list array and so on */
        ZipFilePrivate *_data;
    };
} // end of namespace cocos2d

// end group
/// @}

/// @endcond
#endif // __SUPPORT_ZIPUTILS_H__
