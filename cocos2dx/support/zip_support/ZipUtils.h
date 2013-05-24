/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include <string>
#include "CCPlatformDefine.h"

namespace cocos2d
{
    /* XXX: pragma pack ??? */
    /** @struct CCZHeader
    */
    struct CCZHeader {
        unsigned char   sig[4];             // signature. Should be 'CCZ!' 4 bytes
        unsigned short  compression_type;   // should 0
        unsigned short  version;            // should be 2 (although version type==1 is also supported)
        unsigned int    reserved;           // Reserved for users.
        unsigned int    len;                // size of the uncompressed file
    };

    enum {
        CCZ_COMPRESSION_ZLIB,               // zlib format.
        CCZ_COMPRESSION_BZIP2,              // bzip2 format (not supported yet)
        CCZ_COMPRESSION_GZIP,               // gzip format (not supported yet)
        CCZ_COMPRESSION_NONE,               // plain (not supported yet)
    };

    class CC_DLL ZipUtils
    {
    public:
        /** 
        * Inflates either zlib or gzip deflated memory. The inflated memory is
        * expected to be freed by the caller.
        *
        * It will allocate 256k for the destination buffer. If it is not enough it will multiply the previous buffer size per 2, until there is enough memory.
        * @returns the length of the deflated buffer
        *
        @since v0.8.1
        */
        static int ccInflateMemory(unsigned char *in, unsigned int inLength, unsigned char **out);

        /** 
        * Inflates either zlib or gzip deflated memory. The inflated memory is
        * expected to be freed by the caller.
        *
        * outLenghtHint is assumed to be the needed room to allocate the inflated buffer.
        *
        * @returns the length of the deflated buffer
        *
        @since v1.0.0
        */
        static int ccInflateMemoryWithHint(unsigned char *in, unsigned int inLength, unsigned char **out, unsigned int outLenghtHint);

        /** inflates a GZip file into memory
        *
        * @returns the length of the deflated buffer
        *
        * @since v0.99.5
        */
        static int ccInflateGZipFile(const char *filename, unsigned char **out);

        /** inflates a CCZ file into memory
        *
        * @returns the length of the deflated buffer
        *
        * @since v0.99.5
        */
        static int ccInflateCCZFile(const char *filename, unsigned char **out);

        /** Sets the pvr.ccz encryption key parts separately for added
        * security.
        *
        * Example: If the key used to encrypt the pvr.ccz file is
        * 0xaaaaaaaabbbbbbbbccccccccdddddddd you will call this function 4 
        * different times, preferably from 4 different source files, as follows
        *
        * ZipUtils::ccSetPvrEncryptionKeyPart(0, 0xaaaaaaaa);
        * ZipUtils::ccSetPvrEncryptionKeyPart(1, 0xbbbbbbbb);
        * ZipUtils::ccSetPvrEncryptionKeyPart(2, 0xcccccccc);
        * ZipUtils::ccSetPvrEncryptionKeyPart(3, 0xdddddddd);
        *
        * Splitting the key into 4 parts and calling the function
        * from 4 different source files increases the difficulty to
        * reverse engineer the encryption key. Be aware that encrpytion 
        * is *never* 100% secure and the key code can be cracked by
        * knowledgable persons.
        *
        * IMPORTANT: Be sure to call ccSetPvrEncryptionKey or
        * ccSetPvrEncryptionKeyPart with all of the key parts *before* loading
        * the spritesheet or decryption will fail and the spritesheet
        * will fail to load.
        *
        * @param index part of the key [0..3]
        * @param value value of the key part
        */
        static void ccSetPvrEncryptionKeyPart(int index, unsigned int value);
        
        /** Sets the pvr.ccz encryption key.
        *
        * Example: If the key used to encrypt the pvr.ccz file is
        * 0xaaaaaaaabbbbbbbbccccccccdddddddd you will call this function with
        * the key split into 4 parts as follows
        *
        * ZipUtils::ccSetPvrEncryptionKey(0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd);
        *
        * Note that using this function makes it easier to reverse engineer and
        * discover the complete key because the key parts are present in one 
        * function call.
        *
        * IMPORTANT: Be sure to call ccSetPvrEncryptionKey or
        * ccSetPvrEncryptionKeyPart with all of the key parts *before* loading 
        * the spritesheet or decryption will fail and the spritesheet
        * will fail to load.
        *
        * @param keyPart1 the key value part 1.
        * @param keyPart2 the key value part 2.
        * @param keyPart3 the key value part 3.
        * @param keyPart4 the key value part 4.
        */
        static void ccSetPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4);

    private:
        static int ccInflateMemoryWithHint(unsigned char *in, unsigned int inLength, unsigned char **out, unsigned int *outLength, 
                                           unsigned int outLenghtHint);
        static inline void ccDecodeEncodedPvr (unsigned int *data, int len);
        static inline unsigned int ccChecksumPvr(const unsigned int *data, int len);

        static unsigned int s_uEncryptedPvrKeyParts[4];
        static unsigned int s_uEncryptionKey[1024];
        static bool s_bEncryptionKeyIsValid;
    };

    // forward declaration
    class ZipFilePrivate;

    /**
    * Zip file - reader helper class.
    *
    * It will cache the file list of a particular zip file with positions inside an archive,
    * so it would be much faster to read some particular files or to check their existance.
    *
    * @since v2.0.5
    */
    class ZipFile
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
        * @return Upon success, a pointer to the data is returned, otherwise NULL.
        * @warning Recall: you are responsible for calling delete[] on any Non-NULL pointer returned.
        *
        * @since v2.0.5
        */
        unsigned char *getFileData(const std::string &fileName, unsigned long *pSize);

    private:
        /** Internal data like zip file pointer / file list array and so on */
        ZipFilePrivate *m_data;
    };
} // end of namespace cocos2d
#endif // __SUPPORT_ZIPUTILS_H__

