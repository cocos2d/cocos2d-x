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
#ifndef __CC_FILEUTILS_OHOS_H__
#define __CC_FILEUTILS_OHOS_H__

#include "CCData.h"
#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"
#include "ccTypes.h"
#include "ccTypeInfo.h"
#include <string>
#include "napi/modules/RawFileUtils.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class ResizableBuffer {
public:
    virtual ~ResizableBuffer() {}
    virtual void resize(size_t size) = 0;
    virtual void* buffer() const = 0;
};

template<typename T>
class ResizableBufferAdapter { };


template<typename CharT, typename Traits, typename Allocator>
class ResizableBufferAdapter< std::basic_string<CharT, Traits, Allocator> > : public ResizableBuffer {
    typedef std::basic_string<CharT, Traits, Allocator> BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        _buffer->resize((size + sizeof(CharT) - 1) / sizeof(CharT));
    }
    virtual void* buffer() const override {
        // can not invoke string::front() if it is empty

        if (_buffer->empty())
            return nullptr;
        else
            return &_buffer->front();
    }
};

template<typename T, typename Allocator>
class ResizableBufferAdapter< std::vector<T, Allocator> > : public ResizableBuffer {
    typedef std::vector<T, Allocator> BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        _buffer->resize((size + sizeof(T) - 1) / sizeof(T));
    }
    virtual void* buffer() const override {
        // can not invoke vector::front() if it is empty

        if (_buffer->empty())
            return nullptr;
        else
            return &_buffer->front();
    }
};


template<>
class ResizableBufferAdapter<Data> : public ResizableBuffer {
    typedef Data BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        if (static_cast<size_t>(_buffer->getSize()) < size) {
            auto old = _buffer->getBytes();
            void* buffer = realloc(old, size);
            if (buffer)
                _buffer->fastSet((unsigned char*)buffer, size);
        }
    }
    virtual void* buffer() const override {
        return _buffer->getBytes();
    }
};


//! @brief  Helper class to handle file operations
class CC_DLL CCFileUtilsOhos : public CCFileUtils
{
    friend class CCFileUtils;
    CCFileUtilsOhos();
public:
    virtual ~CCFileUtilsOhos();

    /* override funtions */
    bool init();
    virtual unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
    virtual std::string getWritablePath();
    virtual bool isFileExist(const std::string& strFilePath);
    virtual bool isAbsolutePath(const std::string& dirPath);
    
    /** This function is android specific. It is used for CCTextureCache::addImageAsync(). 
     Don't use it in your codes.
     */
    unsigned char* getFileDataForAsync(const char* pszFileName, const char* pszMode, unsigned long * pSize);
    static std::string ohWritablePath;
    bool getRawFileDescriptor(const std::string &filename, RawFileDescriptor &descriptor);

    /**
     *  Creates binary data from a file.
     *  @return A data object.
     */
    virtual Data getDataFromFile(const std::string &filename);
    
private:
    unsigned char* doGetFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize, bool forAsync);
    template <
            typename T,
            typename Enable = typename std::enable_if<
                    std::is_base_of< ResizableBuffer, ResizableBufferAdapter<T> >::value
    >::type
    >
    bool getContents(const std::string& filename, T* buffer) {
        ResizableBufferAdapter<T> buf(buffer);
        return getContents(filename, &buf);
    }
    virtual bool getContents(const std::string& filename, ResizableBuffer* buffer);
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_FILEUTILS_ANDROID_H__

