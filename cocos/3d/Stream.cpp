#include "Stream.h"
#include "cocos2d.h"

namespace cocos2d
{
#if defined(__ANDROID__)
extern void printError(const char* format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    LOGI(format, argptr);
    va_end(argptr);
}  
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray = nullptr;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays = nullptr;
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays = nullptr;
PFNGLISVERTEXARRAYOESPROC glIsVertexArray = nullptr;
#elif WIN32
extern void printError(const char* format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    fprintf(stderr, "\n");
    int sz = vfprintf(stderr, format, argptr);
    if (sz > 0)
    {
        char* buf = new char[sz + 2];
        vsprintf(buf, format, argptr);
        buf[sz] = '\n';
        buf[sz+1] = 0;
        OutputDebugStringA(buf);
        CC_SAFE_DELETE_ARRAY(buf);
    }
    va_end(argptr);
}
#elif __APPLE__
extern void printError(const char* format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, format, argptr);
    fprintf(stderr, "\n");
    va_end(argptr);
}   
#endif

std::string Stream::readString()
{
    unsigned int length;
if(read(&length, 4, 1) != 1)
    {
        return std::string();
    }

    std::string str;
    if (length > 0)
    {
        str.resize(length);
if (read(&str[0], 1, length) != length)
        {
            return std::string();
        }
    }
    return str;
}

bool Stream::readMatrix(float* m)
{
    return (read(m, sizeof(float), 16) == 16);
}

bool Stream::writeString(const std::string& str)
{
    unsigned int length = str.length();
    if (write(&length, 4, 1) != 1)
    {
        return false;
    }
    
    if (length > 0)
    {
        return write(str);
    }
    return true;
}

bool Stream::writeMatrix(const float* m)
{
    return write(m, sizeof(float), 16) == 16;
}

bool Stream::write(const char* str)
{
    return write(str, strlen(str), 1) == 1;
}
    
//...

C3DFileStream::C3DFileStream(FILE* file)   
{
    _file = file;
}

C3DFileStream::~C3DFileStream()
{
    if (_file)
    {
        close();
    }
}

C3DFileStream* C3DFileStream::create(const char* filePath, const char* mode)
{
    FILE* file = fopen(filePath, mode);
    if (file)
    {
        C3DFileStream* stream = new C3DFileStream(file);      

        return stream;
    }
    return nullptr;
}


void C3DFileStream::close()
{
    if (_file)
        fclose(_file);
    _file = nullptr;
}

size_t C3DFileStream::read(void* ptr, size_t size, size_t count)
{
    if (!_file || feof(_file))
        return 0;
    return fread(ptr, size, count, _file);
}

char* C3DFileStream::readLine(int num,char* line)
{
    if (!_file)
        return 0;
    return fgets(line, num, _file);
}

size_t C3DFileStream::write(const void* ptr, size_t size, size_t count)
{
    if (!_file)
        return 0;
    return fwrite(ptr, size, count, _file);
}

bool C3DFileStream::eof()
{
    if (!_file || feof(_file))
        return true;
    return ((size_t)tell()) >= length();
}

size_t C3DFileStream::length()
{
    size_t len = 0;
    if (_file != nullptr)
    {
        long int curpos = tell();
        if (seek(0, SEEK_END))
        {
            len = tell();
        }
        seek(curpos, SEEK_SET);
    }
    return len;
}

long int C3DFileStream::tell()
{
    if (!_file)
        return -1;
    return ftell(_file);
}

bool C3DFileStream::seek(long int offset, int origin)
{
    if (!_file)
        return false;
    return fseek(_file, offset, origin) == 0;
}

bool C3DFileStream::rewind()
{
    if (_file != nullptr)
    {
        ::rewind(_file);
        return true;
    }
    return false;
}

/*
char* C3DFileStream::readAll(int* fileSize)
{
    if (!_file)
{
CCLOG("Failed to load file");
        return nullptr;
}   

long int curpos = ftell(_file);      
   

    // Obtain file length.
    fseek(_file, 0, SEEK_END);
    int size = (int)ftell(_file);
    fseek(_file, 0, SEEK_SET);

    // Read entire file contents.
    char* buffer = new char[size + 1];
    int read = (int)fread(buffer, 1, size, _file);
fseek(_file,curpos, SEEK_SET);
    assert(read == size);
    if (read != size)
    {
        CCLOG("Read error for file: (%d < %d)", (int)read, (int)size);
        CC_SAFE_DELETE_ARRAY(buffer);
        return nullptr;
    }
    // Force the character buffer to be nullptr-terminated.
    buffer[size] = '\0';

    if (fileSize)
    {
        *fileSize = size; 
    }
    return buffer;
}
*/

///..............
C3DMemoryStream::C3DMemoryStream()
{
_buffer = nullptr;
_position = 0;
_length = 0;
}


C3DMemoryStream::C3DMemoryStream(char* lpbuffer, unsigned int length)
{
_position = 0;
_buffer  = lpbuffer;
_length = length;


}; 

C3DMemoryStream::~C3DMemoryStream()
{
close();
}

C3DMemoryStream* C3DMemoryStream::create(char* lpbuffer, unsigned int length)
{
    if (lpbuffer)
    {
        C3DMemoryStream* stream = new C3DMemoryStream(lpbuffer, length);      

        return stream;
    }
    return nullptr;
}


void C3DMemoryStream::close()
{
CC_SAFE_DELETE(_buffer);
}

size_t C3DMemoryStream::read(void* ptr, size_t size, size_t count)
{
    if (!_buffer || eof())
        return 0;

size_t validCount;
size_t validLength = _length - _position;
size_t needLength = size*count;
char* ptr1 = (char*)ptr;
if(validLength <= needLength)
{
validCount = validLength/size;
size_t readLength = size*validCount;
memcpy(ptr1,(char*)_buffer+_position,readLength);
ptr1 += readLength;
_position += readLength;
readLength = validLength - readLength;
if(readLength>0)
{
memcpy(ptr1,(char*)_buffer+_position,readLength);
    _position += readLength;
validCount+=1;
}

}
else
{
memcpy(ptr1,(char*)_buffer+_position,needLength);
_position += needLength;
validCount = count;
}
//*ptr1 = 0;

return validCount;

}

char* C3DMemoryStream::readLine(int num,char* line)
{
    if (!_buffer)
        return 0;

//char* str = new char[num];
char* buffer = (char*)_buffer+_position;

char* p = line;
char c;
size_t readNum = 0;
while((c=*buffer) != 10 && readNum < (size_t)num && _position<(long int)_length)
{
*p = c;
p++;
buffer++;
_position++; 
readNum++;
}
*p = '\0';

return line;

}

size_t C3DMemoryStream::write(const void* ptr, size_t size, size_t count)
{
    if (!_buffer)
        return 0;
    
size_t validCount;
size_t validLength = _length - _position;
size_t needLength = size*count;
const char* ptr1 = (const char*)ptr;
if (validLength <= needLength)
{
validCount = validLength / size;
size_t readLength = size * validCount;
memcpy((char*)_buffer + _position, ptr1, readLength);
ptr1 += readLength;
_position += readLength;
readLength = validLength - readLength;
if(readLength > 0)
{
memcpy((char*)_buffer+_position, ptr1, readLength);
    _position += readLength;
validCount += 1;
}
        
}
else
{
memcpy((char*)_buffer + _position, ptr1, needLength);
_position += needLength;
validCount = count;
}
    
return validCount;
}
    


bool C3DMemoryStream::eof()
{
    if (!_buffer)
        return true;
    return ((size_t)tell()) >= length();
}

size_t C3DMemoryStream::length()
{
    return _length;
}

long int C3DMemoryStream::tell()
{
    if (!_buffer)
        return -1;
    return _position;
}

bool C3DMemoryStream::seek(long int offset, int origin)
{
    if (!_buffer)
        return false;

if(origin == SEEK_CUR)
{
_position += offset;
}
else if(origin == SEEK_SET)
{
_position = offset;
}
else if(origin == SEEK_END)
{
_position = _length+offset;
}
else
return false;

return true;
   
}

bool C3DMemoryStream::rewind()
{
    if (_buffer != nullptr)
    {
_position = 0;
return true;
    }
    return false;
}

/*
char* C3DMemoryStream::readAll(int* fileSize)
{
    if (!_buffer)
{
CCLOG("Failed to load file");
        return nullptr;
} 

    if (fileSize)
    {
        *fileSize = _length; 
    }
    return _buffer;
}
*/

StreamManager::StreamManager()
{
}

StreamManager::~StreamManager()
{
}


char* StreamManager::readAll(const char* filePath, int* fileSize)
{
    // Open file for reading.

Stream* stream = StreamManager::openStream(filePath, "rb");
    if (stream == nullptr)
    {
        CCLOG("Failed to load file: %s", filePath);
        return nullptr;
    }
size_t size = stream->length();

    // Read entire file contents.
    char* buffer = new char[size + 1];
size_t read = stream->read(buffer, 1, size);
 
    assert(read == size);
    if (read != size)
    {
        CCLOG("Read error for file: %s (%d < %d)", filePath, (int)read, (int)size);
        CC_SAFE_DELETE_ARRAY(buffer);
        return nullptr;
    }

    // Force the character buffer to be nullptr-terminated.
    buffer[size] = '\0';


delete stream;
    if (fileSize)
    {
        *fileSize = size+1; 
    }
    return buffer;
}



Stream* StreamManager::openStream(const char* fileName, const char* openMode, StreamType streamType)
{
//streamType = StreamType_File;
std::string fullpath = fileName;
fullpath = cocos2d::CCFileUtils::getInstance()->fullPathForFilename(fileName);
    if (fullpath.size() == 0)
    {
        return nullptr;
    }   
   
Stream* stream = nullptr;
if(streamType == StreamType_File)
{
stream = C3DFileStream::create(fullpath.c_str(),openMode);
}
else if(streamType == StreamType_Memory)
{
ssize_t nSize = 0;
        char* pBuffer = reinterpret_cast<char*>(cocos2d::CCFileUtils::getInstance()->getFileData(fullpath.c_str(), openMode, &nSize));
stream = C3DMemoryStream::create(pBuffer,nSize);
}
else{}

return stream;
}



}
