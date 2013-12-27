#ifndef Stream_H_
#define Stream_H_

#include "cocos2d.h"

namespace cocos2d
{

/**
 * Stream is an interface for reading and writing a sequence of bytes.
 */
class Stream
{
public:
	/**
     * Constructor.
     */
	Stream(){};

	/**
     * Destructor.
     */
    virtual ~Stream() {};

	/**
     * Closes the stream.
     */
    virtual void close() = 0;        

	/**
     * Reads an array of elements.
	 *
	 * @param ptr   The pointer to the memory to copy into.
	 *              The available size should be at least bytes.
	 * @param size  The size of each element to be read, in bytes.
	 * @param count The number of elements to read.
	 *
	 * @return The number of elements read.
     */
    virtual size_t read(void* ptr, size_t size, size_t count) = 0;	 

	/**
     * Reads a line from the stream.
     */
	virtual char* readLine(int num,char* line) = 0;

	 /**
     * Writes an array of elements.
     *
     * @param ptr   The pointer to the array of elements to be written.
     * @param size  The size of each element to be written, in bytes.
     * @param count The number of elements to write.
     * 
     * @return The number of elements written.
     */
	virtual size_t write(const void* ptr, size_t size, size_t count) = 0;	   

	/**
     * Returns true if the end of the stream has been reached.
     */
    virtual bool eof() = 0;	   

	/**
     * Returns the length of the stream in bytes.
     */
    virtual size_t length() = 0;

	/**
     * Returns the position of the file pointer.
     */
    virtual long int tell() = 0;	

	/**
     * Sets the position of the file pointer.
     */
    virtual bool seek(long int offset, int origin) = 0;	   

	/**
	 * Sets the file pointer at the start of the file.
	 */
    virtual bool rewind() = 0;

	/**
    * read binary typed value.
    */
	template<typename T> bool read(T* ptr);
	template<typename T> bool readArray(unsigned int* length, std::vector<T>* values);
	
	/**
	* first read length, then read string text
	*/
    virtual std::string readString();
    virtual bool readMatrix(float* m);
   
	/**
	*  write binary typed value
	*/
    template<typename T> bool write(const T& ptr);
    template<typename T> bool writeArray(const std::vector<T>& values);

	/**
	*  first write length, then write string text, DO NOT call writeString for text file, call write(string) instead
	*/
    virtual bool writeString(const std::string& str);
    virtual bool writeMatrix(const float* m);
    virtual bool write(const char* str);

};

/**
 * Defines a set of functions for interacting with the device filesystem.
 */
class C3DFileStream : public Stream
{
public:
	/**
     * Constructor.
     */
	C3DFileStream(FILE* file);
	
	/**
     * Destructor.
     */
    ~C3DFileStream();   
	
	/**
     * Creates C3DFileStream.
     */
	static C3DFileStream* create(const char* filePath, const char* mode);

	/**
     * Closes the stream.
     */
    virtual void close();

	/**
     * Reads an array of elements.
	 */
    virtual size_t read(void* ptr, size_t size, size_t count);

	/**
     * Reads a line from the stream.
     */
    virtual char* readLine(int num,char* line);

	/**
     * Writes an array of elements.
     */
    virtual size_t write(const void* ptr, size_t size, size_t count);

	/**
     * Returns true if the end of the stream has been reached.
     */
    virtual bool eof();

	/**
     * Returns the length of the stream in bytes.
     */
    virtual size_t length();

	/**
     * Returns the position of the file pointer.
     */
    virtual long int tell();

	/**
     * Sets the position of the file pointer.
     */
    virtual bool seek(long int offset, int origin);

	/**
	 * Sets the file pointer at the start of the file.
	 */
    virtual bool rewind();  

private:
    FILE* _file;
};

/**
 * Defines a set of functions for interacting with the device memory stream.
 */
class C3DMemoryStream : public Stream
{  			
public:
	/**
     * Constructor.
     */
    C3DMemoryStream();	

	/**
     * Destructor.
     */
    C3DMemoryStream(char* lpbuffer, unsigned int len);

	/**
     * Closes the stream.
     */
	~C3DMemoryStream();

	/**
     * Creates C3DMemoryStream.
     */
	static C3DMemoryStream* create(char* lpbuffer, unsigned int length);

	/**
     * Closes the stream.
     */
	virtual void close();

	/**
     * Reads an array of elements.
	 */
    virtual size_t read(void* ptr, size_t size, size_t count);

	/**
     * Reads a line from the stream.
     */
    virtual char* readLine(int num,char* line);

	/**
     * Writes an array of elements.
     */
    virtual size_t write(const void* ptr, size_t size, size_t count);

	/**
     * Returns true if the end of the stream has been reached.
     */
    virtual bool eof();

	/**
     * Returns the length of the stream in bytes.
     */
    virtual size_t length();

	/**
     * Returns the position of the file pointer.
     */
    virtual long int tell();

	/**
     * Sets the position of the file pointer.
     */
    virtual bool seek(long int offset, int origin);

	/**
	 * Sets the file pointer at the start of the file.
	 */
    virtual bool rewind();

private:              
    long int _position;    
    size_t  _length;        
    char* _buffer;

};  

/**
* Stream is an interface for managing stream.
*/
class StreamManager
{
public:
	/**
     * Constructor.
     */
	StreamManager();

	/**
     * Destructor.
     */
    ~StreamManager();

	/**
     * Define stream type.
     */
	enum StreamType
    {
		StreamType_File = 0,
		StreamType_Memory
        
    };
    
	/**
     * Read entire file contents to buffer.
     */
    static char* readAll(const char* filePath, int* fileSize = NULL);		

	/**
     * open file by Stream.
     */
	static Stream* openStream(const char* fileName, const char* openMode, StreamType streamType=StreamType_Memory);

};
    
// implements inline methods

// template read routines
template<typename T>
inline bool Stream::read(T *ptr)
{
    return (read(ptr, sizeof(T), 1) == 1);
}

/**
* template function to read array of value.
*/
template<typename T>
inline bool Stream::readArray(unsigned int *length, std::vector<T> *values)
{
    if (!read(length))
    {
        return false;
    }
    if (*length > 0 && values)
    {
        values->resize(*length);
        if (read(&(*values)[0], sizeof(T), *length) != *length)
        {
            return false;
        }
    }
    return true;
}

/**
* specalization for char
*/
template<>
inline bool Stream::read<char>(char *ptr)
{
    if (read(ptr, sizeof(char), 1) == 1)
    {
        return true;
    }
    else
    {
        *ptr = -1;
        return false;
    }
}

/**
* specalization for std::string
*/
template<>
inline bool Stream::read<std::string>(std::string *ptr)
{
    CCLOG("can not read std::string, use readString() instead");
    return false;
}

/**
* template function to read array of value.
*/
template<>
inline bool Stream::readArray<std::string>(unsigned int *length, std::vector<std::string> *values)
{
    if (!read(length))
    {
        return false;
    }
    values->clear();
    if (*length > 0 && values)
    {
        for (int i = 0; i < (int)*length; ++i)
        {
            values->push_back(readString());
        }
    }
    return true;
}

/**
* template write routines
*/
template<typename T>
inline bool Stream::write(const T& ptr)
{
    return write(&ptr, sizeof(T), 1) == 1;
}

/**
* template write array of value.
*/
template<typename T>
inline bool Stream::writeArray(const std::vector<T>& values)
{
    unsigned int length = (unsigned int)values.size();
    if (!write(length))
    {
        return false;
    }
    if (length > 0)
    {
        if (write(&values[0], sizeof(T), length) != length)
        {
            return false;
        }
    }
    return true;
}

/**
* specalization for std::string
*/
template<>
inline bool Stream::write<std::string>(const std::string& ptr)
{
    return write(ptr.c_str(), ptr.length(), 1) == 1;
}

/**
* template write array of value.
*/
template<>
inline bool Stream::writeArray<std::string>(const std::vector<std::string>& values)
{
    unsigned int length = (unsigned int)values.size();

    if (!write(length))
    {
        return false;
    }
    if (length > 0)
    {
        for (int i = 0; i < (int)length; ++i)
        {
            writeString(values[i]);
        }
    }
    return true;
}
    
}

#endif
