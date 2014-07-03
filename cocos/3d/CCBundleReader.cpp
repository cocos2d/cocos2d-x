#include "CCBundleReader.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

BundleReader::BundleReader()
{
    m_buffer = NULL;
    m_position = 0;
    m_length = 0;
};

BundleReader::~BundleReader()
{
    
};

void BundleReader::init(char* lpbuffer, ssize_t length)
{
    m_position = 0;
    m_buffer  = lpbuffer;
    m_length = length;
}

ssize_t BundleReader::read(void* ptr, ssize_t size, ssize_t count)
{
    if (!m_buffer || eof())
        return 0;

    ssize_t validCount;
    ssize_t validLength = m_length - m_position;
    ssize_t needLength = size*count;
    char* ptr1 = (char*)ptr;
    if(validLength <= needLength)
    {
        validCount = validLength/size;
        ssize_t readLength = size*validCount;
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

    return validCount;
}

char* BundleReader::readLine(int num,char* line)
{
    if (!m_buffer)
        return 0;

    char* buffer = (char*)m_buffer+m_position;
    char* p = line;
    char c;
    ssize_t readNum = 0;
    while((c=*buffer) != 10 && readNum < (ssize_t)num && m_position<(long int)m_length)
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

bool BundleReader::eof()
{
    if (!m_buffer)
        return true;
    
    return ((ssize_t)tell()) >= length();
}

ssize_t BundleReader::length()
{
    return m_length;
}

long int BundleReader::tell()
{
    if (!m_buffer)
        return -1;
    return m_position;
}

bool BundleReader::seek(long int offset, int origin)
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

bool BundleReader::rewind()
{
    if (m_buffer != NULL)
    {
        m_position = 0;
        return true;
    }
    return false;
}

std::string BundleReader::readString()
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

bool BundleReader::readMatrix(float* m)
{
    return (read(m, sizeof(float), 16) == 16);
}

}