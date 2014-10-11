/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

// FIXME: hack, must be included before ziputils
#include "unzip.h"
#include "base/ZipUtils.h"

#include <zlib.h>
#include <assert.h>
#include <stdlib.h>

#include "base/CCData.h"
#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include <map>

// FIXME: Other platforms should use upstream minizip like mingw-w64  
#ifdef __MINGW32__
#define unzGoToFirstFile64(A,B,C,D) unzGoToFirstFile2(A,B,C,D, NULL, 0, NULL, 0)
#define unzGoToNextFile64(A,B,C,D) unzGoToNextFile2(A,B,C,D, NULL, 0, NULL, 0)
#endif

NS_CC_BEGIN

unsigned int ZipUtils::s_uEncryptedPvrKeyParts[4] = {0,0,0,0};
unsigned int ZipUtils::s_uEncryptionKey[1024];
bool ZipUtils::s_bEncryptionKeyIsValid = false;

// --------------------- ZipUtils ---------------------

inline void ZipUtils::decodeEncodedPvr(unsigned int *data, ssize_t len)
{
    const int enclen = 1024;
    const int securelen = 512;
    const int distance = 64;
    
    // check if key was set
    // make sure to call caw_setkey_part() for all 4 key parts
    CCASSERT(s_uEncryptedPvrKeyParts[0] != 0, "Cocos2D: CCZ file is encrypted but key part 0 is not set. Did you call ZipUtils::setPvrEncryptionKeyPart(...)?");
    CCASSERT(s_uEncryptedPvrKeyParts[1] != 0, "Cocos2D: CCZ file is encrypted but key part 1 is not set. Did you call ZipUtils::setPvrEncryptionKeyPart(...)?");
    CCASSERT(s_uEncryptedPvrKeyParts[2] != 0, "Cocos2D: CCZ file is encrypted but key part 2 is not set. Did you call ZipUtils::setPvrEncryptionKeyPart(...)?");
    CCASSERT(s_uEncryptedPvrKeyParts[3] != 0, "Cocos2D: CCZ file is encrypted but key part 3 is not set. Did you call ZipUtils::setPvrEncryptionKeyPart(...)?");
    
    // create long key
    if(!s_bEncryptionKeyIsValid)
    {
        unsigned int y, p, e;
        unsigned int rounds = 6;
        unsigned int sum = 0;
        unsigned int z = s_uEncryptionKey[enclen-1];
        
        do
        {
#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (s_uEncryptedPvrKeyParts[(p&3)^e] ^ z)))
            
            sum += DELTA;
            e = (sum >> 2) & 3;
            
            for (p = 0; p < enclen - 1; p++)
            {
                y = s_uEncryptionKey[p + 1];
                z = s_uEncryptionKey[p] += MX;
            }
            
            y = s_uEncryptionKey[0];
            z = s_uEncryptionKey[enclen - 1] += MX;
            
        } while (--rounds);
        
        s_bEncryptionKeyIsValid = true;
    }
    
    int b = 0;
    int i = 0;
    
    // encrypt first part completely
    for(; i < len && i < securelen; i++)
    {
        data[i] ^= s_uEncryptionKey[b++];
        
        if(b >= enclen)
        {
            b = 0;
        }
    }
    
    // encrypt second section partially
    for(; i < len; i += distance)
    {
        data[i] ^= s_uEncryptionKey[b++];
        
        if(b >= enclen)
        {
            b = 0;
        }
    }
}

inline unsigned int ZipUtils::checksumPvr(const unsigned int *data, ssize_t len)
{
    unsigned int cs = 0;
    const int cslen = 128;
    
    len = (len < cslen) ? len : cslen;
    
    for(int i = 0; i < len; i++)
    {
        cs = cs ^ data[i];
    }
    
    return cs;
}

// memory in iPhone is precious
// Should buffer factor be 1.5 instead of 2 ?
#define BUFFER_INC_FACTOR (2)

int ZipUtils::inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t *outLength, ssize_t outLenghtHint)
{
    /* ret value */
    int err = Z_OK;
    
    ssize_t bufferSize = outLenghtHint;
    *out = (unsigned char*)malloc(bufferSize);
    
    z_stream d_stream; /* decompression stream */
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;
    
    d_stream.next_in  = in;
    d_stream.avail_in = static_cast<unsigned int>(inLength);
    d_stream.next_out = *out;
    d_stream.avail_out = static_cast<unsigned int>(bufferSize);
    
    /* window size to hold 256k */
    if( (err = inflateInit2(&d_stream, 15 + 32)) != Z_OK )
        return err;
    
    for (;;)
    {
        err = inflate(&d_stream, Z_NO_FLUSH);
        
        if (err == Z_STREAM_END)
        {
            break;
        }
        
        switch (err)
        {
            case Z_NEED_DICT:
                err = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&d_stream);
                return err;
        }
        
        // not enough memory ?
        if (err != Z_STREAM_END)
        {
            *out = (unsigned char*)realloc(*out, bufferSize * BUFFER_INC_FACTOR);
            
            /* not enough memory, ouch */
            if (! *out )
            {
                CCLOG("cocos2d: ZipUtils: realloc failed");
                inflateEnd(&d_stream);
                return Z_MEM_ERROR;
            }
            
            d_stream.next_out = *out + bufferSize;
            d_stream.avail_out = static_cast<unsigned int>(bufferSize);
            bufferSize *= BUFFER_INC_FACTOR;
        }
    }
    
    *outLength = bufferSize - d_stream.avail_out;
    err = inflateEnd(&d_stream);
    return err;
}

ssize_t ZipUtils::inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t outLengthHint)
{
    ssize_t outLength = 0;
    int err = inflateMemoryWithHint(in, inLength, out, &outLength, outLengthHint);
    
    if (err != Z_OK || *out == nullptr) {
        if (err == Z_MEM_ERROR)
        {
            CCLOG("cocos2d: ZipUtils: Out of memory while decompressing map data!");
        } else
            if (err == Z_VERSION_ERROR)
            {
                CCLOG("cocos2d: ZipUtils: Incompatible zlib version!");
            } else
                if (err == Z_DATA_ERROR)
                {
                    CCLOG("cocos2d: ZipUtils: Incorrect zlib compressed data!");
                }
                else
                {
                    CCLOG("cocos2d: ZipUtils: Unknown error while decompressing map data!");
                }

        if(*out) {
            free(*out);
            *out = nullptr;
        }
        outLength = 0;
    }
    
    return outLength;
}

ssize_t ZipUtils::inflateMemory(unsigned char *in, ssize_t inLength, unsigned char **out)
{
    // 256k for hint
    return inflateMemoryWithHint(in, inLength, out, 256 * 1024);
}

int ZipUtils::inflateGZipFile(const char *path, unsigned char **out)
{
    int len;
    unsigned int offset = 0;
    
    CCASSERT(out, "");
    CCASSERT(&*out, "");
    
    gzFile inFile = gzopen(path, "rb");
    if( inFile == nullptr ) {
        CCLOG("cocos2d: ZipUtils: error open gzip file: %s", path);
        return -1;
    }
    
    /* 512k initial decompress buffer */
    unsigned int bufferSize = 512 * 1024;
    unsigned int totalBufferSize = bufferSize;
    
    *out = (unsigned char*)malloc( bufferSize );
    if( ! out )
    {
        CCLOG("cocos2d: ZipUtils: out of memory");
        return -1;
    }
    
    for (;;) {
        len = gzread(inFile, *out + offset, bufferSize);
        if (len < 0)
        {
            CCLOG("cocos2d: ZipUtils: error in gzread");
            free( *out );
            *out = nullptr;
            return -1;
        }
        if (len == 0)
        {
            break;
        }
        
        offset += len;
        
        // finish reading the file
        if( (unsigned int)len < bufferSize )
        {
            break;
        }
        
        bufferSize *= BUFFER_INC_FACTOR;
        totalBufferSize += bufferSize;
        unsigned char *tmp = (unsigned char*)realloc(*out, totalBufferSize );
        
        if( ! tmp )
        {
            CCLOG("cocos2d: ZipUtils: out of memory");
            free( *out );
            *out = nullptr;
            return -1;
        }
        
        *out = tmp;
    }
    
    if (gzclose(inFile) != Z_OK)
    {
        CCLOG("cocos2d: ZipUtils: gzclose failed");
    }
    
    return offset;
}

bool ZipUtils::isCCZFile(const char *path)
{
    // load file into memory
    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);

    if (compressedData.isNull())
    {
        CCLOG("cocos2d: ZipUtils: loading file failed");
        return false;
    }

    return isCCZBuffer(compressedData.getBytes(), compressedData.getSize());
}

bool ZipUtils::isCCZBuffer(const unsigned char *buffer, ssize_t len)
{
    if (static_cast<size_t>(len) < sizeof(struct CCZHeader))
    {
        return false;
    }
    
    struct CCZHeader *header = (struct CCZHeader*) buffer;
    return header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && (header->sig[3] == '!' || header->sig[3] == 'p');
}


bool ZipUtils::isGZipFile(const char *path)
{
    // load file into memory
    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);

    if (compressedData.isNull())
    {
        CCLOG("cocos2d: ZipUtils: loading file failed");
        return false;
    }

    return isGZipBuffer(compressedData.getBytes(), compressedData.getSize());
}

bool ZipUtils::isGZipBuffer(const unsigned char *buffer, ssize_t len)
{
    if (len < 2)
    {
        return false;
    }

    return buffer[0] == 0x1F && buffer[1] == 0x8B;
}


int ZipUtils::inflateCCZBuffer(const unsigned char *buffer, ssize_t bufferLen, unsigned char **out)
{
    struct CCZHeader *header = (struct CCZHeader*) buffer;

    // verify header
    if( header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && header->sig[3] == '!' )
    {
        // verify header version
        unsigned int version = CC_SWAP_INT16_BIG_TO_HOST( header->version );
        if( version > 2 )
        {
            CCLOG("cocos2d: Unsupported CCZ header format");
            return -1;
        }

        // verify compression format
        if( CC_SWAP_INT16_BIG_TO_HOST(header->compression_type) != CCZ_COMPRESSION_ZLIB )
        {
            CCLOG("cocos2d: CCZ Unsupported compression method");
            return -1;
        }
    }
    else if( header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && header->sig[3] == 'p' )
    {
        // encrypted ccz file
        header = (struct CCZHeader*) buffer;

        // verify header version
        unsigned int version = CC_SWAP_INT16_BIG_TO_HOST( header->version );
        if( version > 0 )
        {
            CCLOG("cocos2d: Unsupported CCZ header format");
            return -1;
        }

        // verify compression format
        if( CC_SWAP_INT16_BIG_TO_HOST(header->compression_type) != CCZ_COMPRESSION_ZLIB )
        {
            CCLOG("cocos2d: CCZ Unsupported compression method");
            return -1;
        }

        // decrypt
        unsigned int* ints = (unsigned int*)(buffer+12);
        ssize_t enclen = (bufferLen-12)/4;

        decodeEncodedPvr(ints, enclen);

#if COCOS2D_DEBUG > 0
        // verify checksum in debug mode
        unsigned int calculated = checksumPvr(ints, enclen);
        unsigned int required = CC_SWAP_INT32_BIG_TO_HOST( header->reserved );

        if(calculated != required)
        {
            CCLOG("cocos2d: Can't decrypt image file. Is the decryption key valid?");
            return -1;
        }
#endif
    }
    else
    {
        CCLOG("cocos2d: Invalid CCZ file");
        return -1;
    }

    unsigned int len = CC_SWAP_INT32_BIG_TO_HOST( header->len );

    *out = (unsigned char*)malloc( len );
    if(! *out )
    {
        CCLOG("cocos2d: CCZ: Failed to allocate memory for texture");
        return -1;
    }

    unsigned long destlen = len;
    size_t source = (size_t) buffer + sizeof(*header);
    int ret = uncompress(*out, &destlen, (Bytef*)source, bufferLen - sizeof(*header) );

    if( ret != Z_OK )
    {
        CCLOG("cocos2d: CCZ: Failed to uncompress data");
        free( *out );
        *out = nullptr;
        return -1;
    }

    return len;
}

int ZipUtils::inflateCCZFile(const char *path, unsigned char **out)
{
    CCASSERT(out, "Invalid pointer for buffer!");
    
    // load file into memory
    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);
    
    if (compressedData.isNull())
    {
        CCLOG("cocos2d: Error loading CCZ compressed file");
        return -1;
    }
    
    return inflateCCZBuffer(compressedData.getBytes(), compressedData.getSize(), out);
}

void ZipUtils::setPvrEncryptionKeyPart(int index, unsigned int value)
{
    CCASSERT(index >= 0, "Cocos2d: key part index cannot be less than 0");
    CCASSERT(index <= 3, "Cocos2d: key part index cannot be greater than 3");
    
    if(s_uEncryptedPvrKeyParts[index] != value)
    {
        s_uEncryptedPvrKeyParts[index] = value;
        s_bEncryptionKeyIsValid = false;
    }
}

void ZipUtils::setPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4)
{
    setPvrEncryptionKeyPart(0, keyPart1);
    setPvrEncryptionKeyPart(1, keyPart2);
    setPvrEncryptionKeyPart(2, keyPart3);
    setPvrEncryptionKeyPart(3, keyPart4);
}

// --------------------- ZipFile ---------------------
// from unzip.cpp
#define UNZ_MAXFILENAMEINZIP 256

static const std::string emptyFilename("");

struct ZipEntryInfo
{
    unz_file_pos pos;
    uLong uncompressed_size;
};

class ZipFilePrivate
{
public:
    unzFile zipFile;
    
    // std::unordered_map is faster if available on the platform
    typedef std::unordered_map<std::string, struct ZipEntryInfo> FileListContainer;
    FileListContainer fileList;
};

ZipFile *ZipFile::createWithBuffer(const void* buffer, uLong size)
{
    ZipFile *zip = new ZipFile();
    if (zip && zip->initWithBuffer(buffer, size)) {
        return zip;
    } else {
        if (zip) delete zip;
        return nullptr;
    }
}

ZipFile::ZipFile()
: _data(new ZipFilePrivate)
{
    _data->zipFile = nullptr;
}

ZipFile::ZipFile(const std::string &zipFile, const std::string &filter)
: _data(new ZipFilePrivate)
{
    _data->zipFile = unzOpen(zipFile.c_str());
    setFilter(filter);
}

ZipFile::~ZipFile()
{
    if (_data && _data->zipFile)
    {
        unzClose(_data->zipFile);
    }

    CC_SAFE_DELETE(_data);
}

bool ZipFile::setFilter(const std::string &filter)
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(!_data);
        CC_BREAK_IF(!_data->zipFile);
        
        // clear existing file list
        _data->fileList.clear();
        
        // UNZ_MAXFILENAMEINZIP + 1 - it is done so in unzLocateFile
        char szCurrentFileName[UNZ_MAXFILENAMEINZIP + 1];
        unz_file_info64 fileInfo;
        
        // go through all files and store position information about the required files
        int err = unzGoToFirstFile64(_data->zipFile, &fileInfo,
                                     szCurrentFileName, sizeof(szCurrentFileName) - 1);
        while (err == UNZ_OK)
        {
            unz_file_pos posInfo;
            int posErr = unzGetFilePos(_data->zipFile, &posInfo);
            if (posErr == UNZ_OK)
            {
                std::string currentFileName = szCurrentFileName;
                // cache info about filtered files only (like 'assets/')
                if (filter.empty()
                    || currentFileName.substr(0, filter.length()) == filter)
                {
                    ZipEntryInfo entry;
                    entry.pos = posInfo;
                    entry.uncompressed_size = (uLong)fileInfo.uncompressed_size;
                    _data->fileList[currentFileName] = entry;
                }
            }
            // next file - also get the information about it
            err = unzGoToNextFile64(_data->zipFile, &fileInfo,
                                    szCurrentFileName, sizeof(szCurrentFileName) - 1);
        }
        ret = true;
        
    } while(false);
    
    return ret;
}

bool ZipFile::fileExists(const std::string &fileName) const
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(!_data);
        
        ret = _data->fileList.find(fileName) != _data->fileList.end();
    } while(false);
    
    return ret;
}

unsigned char *ZipFile::getFileData(const std::string &fileName, ssize_t *size)
{
    unsigned char * buffer = nullptr;
    if (size)
        *size = 0;

    do
    {
        CC_BREAK_IF(!_data->zipFile);
        CC_BREAK_IF(fileName.empty());
        
        ZipFilePrivate::FileListContainer::const_iterator it = _data->fileList.find(fileName);
        CC_BREAK_IF(it ==  _data->fileList.end());
        
        ZipEntryInfo fileInfo = it->second;
        
        int nRet = unzGoToFilePos(_data->zipFile, &fileInfo.pos);
        CC_BREAK_IF(UNZ_OK != nRet);
        
        nRet = unzOpenCurrentFile(_data->zipFile);
        CC_BREAK_IF(UNZ_OK != nRet);
        
        buffer = (unsigned char*)malloc(fileInfo.uncompressed_size);
        int CC_UNUSED nSize = unzReadCurrentFile(_data->zipFile, buffer, static_cast<unsigned int>(fileInfo.uncompressed_size));
        CCASSERT(nSize == 0 || nSize == (int)fileInfo.uncompressed_size, "the file size is wrong");
        
        if (size)
        {
            *size = fileInfo.uncompressed_size;
        }
        unzCloseCurrentFile(_data->zipFile);
    } while (0);
    
    return buffer;
}

std::string ZipFile::getFirstFilename()
{
    if (unzGoToFirstFile(_data->zipFile) != UNZ_OK) return emptyFilename;
    std::string path;
    unz_file_info info;
    getCurrentFileInfo(&path, &info);
    return path;
}

std::string ZipFile::getNextFilename()
{
    if (unzGoToNextFile(_data->zipFile) != UNZ_OK) return emptyFilename;
    std::string path;
    unz_file_info info;
    getCurrentFileInfo(&path, &info);
    return path;
}

int ZipFile::getCurrentFileInfo(std::string *filename, unz_file_info *info)
{
    char path[FILENAME_MAX + 1];
    int ret = unzGetCurrentFileInfo(_data->zipFile, info, path, sizeof(path), nullptr, 0, nullptr, 0);
    if (ret != UNZ_OK) {
        *filename = emptyFilename;
    } else {
        filename->assign(path);
    }
    return ret;
}

bool ZipFile::initWithBuffer(const void *buffer, uLong size)
{
    if (!buffer || size == 0) return false;
    
    _data->zipFile = unzOpenBuffer(buffer, size);
    if (!_data->zipFile) return false;
    
    setFilter(emptyFilename);
    return true;
}

NS_CC_END
