#include "C3DStream.h"
#include "cocos2d.h"

namespace cocos3d
{
#if defined(__ANDROID__)
extern void printError(const char* format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    LOGI(format, argptr);
    va_end(argptr);
}  
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays = NULL;
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays = NULL;
PFNGLISVERTEXARRAYOESPROC glIsVertexArray = NULL;
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
        SAFE_DELETE_ARRAY(buf);
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

std::string C3DStream::readString()
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

bool C3DStream::readMatrix(float* m)
{
    return (read(m, sizeof(float), 16) == 16);
}

bool C3DStream::writeString(const std::string& str)
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

bool C3DStream::writeMatrix(const float* m)
{
    return write(m, sizeof(float), 16) == 16;
}

bool C3DStream::write(const char* str)
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
    return NULL;
}


void C3DFileStream::close()
{
    if (_file)
        fclose(_file);
    _file = NULL;
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
    if (_file != NULL)
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
    if (_file != NULL)
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
		LOG_ERROR("Failed to load file");
        return NULL;
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
        LOG_ERROR_VARG("Read error for file: (%d < %d)", (int)read, (int)size);
        SAFE_DELETE_ARRAY(buffer);
        return NULL;
    }
    // Force the character buffer to be NULL-terminated.
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
	m_buffer = NULL;
	m_position = 0;	
	m_length = 0;
}


C3DMemoryStream::C3DMemoryStream(char* lpbuffer, unsigned int length)
{
	m_position = 0;
	m_buffer  = lpbuffer; 	
	m_length = length;

	
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
    return NULL;
}


void C3DMemoryStream::close()
{
	SAFE_DELETE(m_buffer);
}

size_t C3DMemoryStream::read(void* ptr, size_t size, size_t count)
{
    if (!m_buffer || eof())
        return 0;
	
	size_t validCount;
	size_t validLength = m_length - m_position;
	size_t needLength = size*count;
	char* ptr1 = (char*)ptr;
	if(validLength <= needLength)
	{
		validCount = validLength/size;
		size_t readLength = size*validCount;
		memcpy(ptr1,(char*)m_buffer+m_position,readLength);
		ptr1 += readLength;	
		m_position += readLength;
		readLength = validLength - readLength;
		if(readLength>0)
		{
			memcpy(ptr1,(char*)m_buffer+m_position,readLength);
		    m_position += readLength;
			validCount+=1;
		}
	
	}
	else
	{
		memcpy(ptr1,(char*)m_buffer+m_position,needLength);
		m_position += needLength;
		validCount = count;
	}
	//*ptr1 = 0;

	return validCount;	

}

char* C3DMemoryStream::readLine(int num,char* line)
{
    if (!m_buffer)
        return 0;
		
	//char* str = new char[num];
	char* buffer = (char*)m_buffer+m_position;
	
	char* p = line;
	char c;
	size_t readNum = 0;
	while((c=*buffer) != 10 && readNum < num && m_position<m_length)
	{		
		*p = c;
		p++;
		buffer++;
		m_position++; 
		readNum++;
	}
	*p = '\0';

	return line;

}

size_t C3DMemoryStream::write(const void* ptr, size_t size, size_t count)
{
    if (!m_buffer)
        return 0;
    
	size_t validCount;
	size_t validLength = m_length - m_position;
	size_t needLength = size*count;
	const char* ptr1 = (const char*)ptr;
	if (validLength <= needLength)
	{
		validCount = validLength / size;
		size_t readLength = size * validCount;
		memcpy((char*)m_buffer + m_position, ptr1, readLength);
		ptr1 += readLength;
		m_position += readLength;
		readLength = validLength - readLength;
		if(readLength > 0)
		{
			memcpy((char*)m_buffer+m_position, ptr1, readLength);
		    m_position += readLength;
			validCount += 1;
		}
        
	}
	else
	{
		memcpy((char*)m_buffer + m_position, ptr1, needLength);
		m_position += needLength;
		validCount = count;
	}
    
	return validCount;
}
    


bool C3DMemoryStream::eof()
{
    if (!m_buffer)
        return true;
    return ((size_t)tell()) >= length();
}

size_t C3DMemoryStream::length()
{
    return m_length;
}

long int C3DMemoryStream::tell()
{
    if (!m_buffer)
        return -1;
    return m_position;
}

bool C3DMemoryStream::seek(long int offset, int origin)
{
    if (!m_buffer)
        return false;

	if(origin == SEEK_CUR)
	{
		m_position += offset;
	}
	else if(origin == SEEK_SET)
	{
		m_position = offset;
	}
	else if(origin == SEEK_END)
	{
		m_position = m_length+offset;
	}
	else
		return false;

	return true;
   
}

bool C3DMemoryStream::rewind()
{
    if (m_buffer != NULL)
    {
		m_position = 0;
		return true;
    }
    return false;
}

/*
char* C3DMemoryStream::readAll(int* fileSize)
{
    if (!m_buffer)
	{
		LOG_ERROR("Failed to load file");
        return NULL;
	} 	

    if (fileSize)
    {
        *fileSize = m_length; 
    }
    return m_buffer;
}
*/

C3DStreamManager::C3DStreamManager()
{
}

C3DStreamManager::~C3DStreamManager()
{
}


char* C3DStreamManager::readAll(const char* filePath, int* fileSize)
{
    // Open file for reading.
	
	C3DStream* stream = C3DStreamManager::openStream(filePath, "rb");
    if (stream == NULL)
    {
        LOG_ERROR_VARG("Failed to load file: %s", filePath);
        return NULL;
    }
	size_t size = stream->length();
	
    // Read entire file contents.
    char* buffer = new char[size + 1];
	size_t read = stream->read(buffer, 1, size);
 
    assert(read == size);
    if (read != size)
    {
        LOG_ERROR_VARG("Read error for file: %s (%d < %d)", filePath, (int)read, (int)size);
        SAFE_DELETE_ARRAY(buffer);
        return NULL;
    }

    // Force the character buffer to be NULL-terminated.
    buffer[size] = '\0';


	delete stream;
    if (fileSize)
    {
        *fileSize = size+1; 
    }
    return buffer;
}



C3DStream* C3DStreamManager::openStream(const char* fileName, const char* openMode, StreamType streamType)
{
	//streamType = StreamType_File;
	std::string fullpath = fileName;
	fullpath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    if (fullpath.size() == 0)
    {
        return NULL;
    }   
	   
	C3DStream* stream = NULL;
	if(streamType == StreamType_File)
	{
		stream = C3DFileStream::create(fullpath.c_str(),openMode);
	}
	else if(streamType == StreamType_Memory)
	{
		unsigned long nSize = 0;
        char* pBuffer = reinterpret_cast<char*>(cocos2d::CCFileUtils::sharedFileUtils()->getFileData(fullpath.c_str(), openMode, &nSize));
		stream = C3DMemoryStream::create(pBuffer,nSize);
	}
	else{}
	
	return stream;
}



}
