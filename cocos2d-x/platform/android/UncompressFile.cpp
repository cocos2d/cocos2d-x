#include "UnCompressFile.h"
#include "ZipUtils.h"
#include "CCXFileUtils_android.h"

#include <stddef.h>
#include <string.h>
#include <zlib.h>

//#include <android/log.h>

namespace cocos2d
{

#define FILE_NAME	"res/drawable/helloworld.png"
#define CONST_HEADER_SIZE		30
#define FILE_HEADER_SIGNATURE	0x04034b50

// because the compiler may align the memory address
// so we define the offsets of some fields here
#define OFFSET_COMPRESSED_SIZE		18
#define OFFSET_UNCOMPRESSED_SIZE	(OFFSET_COMPRESSED_SIZE+4)
#define OFFSET_FILE_NAME_LENGTH		(OFFSET_UNCOMPRESSED_SIZE+4)
#define OFFSET_EXTRA_FIELD_LENGTH   (OFFSET_FILE_NAME_LENGTH+2)

static LocalFileHeader localFileHeader;

UncompressFile::UncompressFile()
{
	m_pData = NULL;
	m_nDatalength = 0;
}

UncompressFile::~UncompressFile()
{
	if (localFileHeader.file_name)
	{
		delete[] localFileHeader.file_name;
	}
}

unsigned char* UncompressFile::getFileData()
{
	return m_pData;
}

int UncompressFile::getFileLength()
{
	return m_nDatalength;
}

unsigned int UncompressFile::convertUnsignedInt(const unsigned char *buffer)
{
	const unsigned char *temp = buffer;
	return (*temp | *(temp+1) << 8 | *(temp+2) << 16 | *(temp+3) << 24);
}

unsigned short UncompressFile::convertUnsignedShort(const unsigned char *buffer)
{
	const unsigned char *temp = buffer;
	return (*temp | *(temp+1) << 8);
}

bool UncompressFile::initFileHeader(FILE *fp)
{
	unsigned char *buffer = new unsigned char[CONST_HEADER_SIZE];
	int count = 0;

	count = fread(buffer, sizeof(unsigned char), CONST_HEADER_SIZE, fp);
	// not a local file header
	if (count != CONST_HEADER_SIZE)
	{
//		__android_log_write(ANDROID_LOG_DEBUG, "UncompressFile::initFileHeader", "not read 30");
		
		delete[] buffer;
		return false;
	}

	localFileHeader.signature = convertUnsignedInt(buffer);

	// not a local file header
	if (localFileHeader.signature != FILE_HEADER_SIGNATURE)
	{
//		__android_log_write(ANDROID_LOG_DEBUG, "UncompressFile::initFileHeader", "signature error");
		delete[] buffer;
		return false;
	}

	// compute compressed size
	localFileHeader.compressed_size = convertUnsignedInt(buffer + OFFSET_COMPRESSED_SIZE);
	localFileHeader.uncompressed_size = convertUnsignedInt(buffer + OFFSET_UNCOMPRESSED_SIZE);
	localFileHeader.extra_field_length = convertUnsignedShort(buffer + OFFSET_EXTRA_FIELD_LENGTH);

	// compute file name
	localFileHeader.file_name_lengh = convertUnsignedShort(buffer + OFFSET_FILE_NAME_LENGTH);
	localFileHeader.file_name = new char[localFileHeader.file_name_lengh + 1];
	if (! localFileHeader.file_name)
	{
//		__android_log_write(ANDROID_LOG_DEBUG, "UncompressFile::initFileHeader", "create memory for filename");
		delete[] buffer;
		return false;
	}
	fread(localFileHeader.file_name, sizeof(char), localFileHeader.file_name_lengh, fp);
	*(localFileHeader.file_name + localFileHeader.file_name_lengh) = '\0';

	// passed the extra field
	fseek(fp, localFileHeader.extra_field_length, SEEK_CUR);

	delete[] buffer;
	return true;
}

bool UncompressFile::doDecompress(FILE *fp)
{
	bool ret = true;
	unsigned char *compressedDataBuffer = new unsigned char[localFileHeader.compressed_size];
	if (! compressedDataBuffer)
	{
//		__android_log_write(ANDROID_LOG_DEBUG, "UncompressFile::doDecompress", "crate momery for compressed data");
		return false;
	}

	// read compressed data
	int len = fread(compressedDataBuffer, sizeof(char), localFileHeader.compressed_size, fp);

	if (localFileHeader.compressed_size != localFileHeader.uncompressed_size)
	{
		// the content is compressed
		m_nDatalength = ZipUtils::inflateMemory(compressedDataBuffer, localFileHeader.compressed_size, &m_pData);
		delete[] compressedDataBuffer;
	}
	else
	{
		m_pData = compressedDataBuffer;
		m_nDatalength = localFileHeader.compressed_size;
	}

	return true;
}

void UncompressFile::decompressFile(const char *fileName)
{
	FILE *fp = NULL;
	if (! (fp = fopen(CCFileUtils::getResourcePath(), "rb")))
	{
//		__android_log_write(ANDROID_LOG_DEBUG, "UncompressFile::decompressFile", "can not open APK_NAME");
		return;
	}

	while (initFileHeader(fp))
	{
		if (strcmp(fileName, localFileHeader.file_name) == 0)
		{
//			__android_log_write(ANDROID_LOG_DEBUG, "UncompressFile::decompressFile", "find file");
			// find the file
			doDecompress(fp);
			break;
		}

		// goto next local file header
		fseek(fp, localFileHeader.compressed_size, SEEK_CUR);
	}

	fclose(fp);
}

} // end of namespace cocos2d
