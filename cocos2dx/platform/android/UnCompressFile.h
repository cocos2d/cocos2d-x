#include <stdio.h>

namespace cocos2d
{
	typedef struct _LocalFileHeader
	{
		unsigned int	signature;			// local file header signature
		unsigned short	version_extract;	// version needed to extract
		unsigned short  flag;				// general purpose bit flag
		unsigned short  compression_method;	// compression method
		unsigned short  last_mod_file_time; // last modified file time
		unsigned short  last_mod_file_date; // last modified file date
		unsigned int	crc_32;				// crc-32
		unsigned int    compressed_size;	// compressed size
		unsigned int    uncompressed_size;	// uncompressed size
		unsigned short	file_name_lengh;	// file name length
		unsigned short  extra_field_length; // extra field length
		char            *file_name;         // file name (variable size)
		char            *extra_field;       // extra field (variable size)
	} LocalFileHeader;

	class UncompressFile
	{
	public:
		UncompressFile();
		~UncompressFile();

		void decompressFile(const char *fileName);
		unsigned char* getFileData();
		int getFileLength();

	private:
		bool doDecompress(FILE *fp);
		bool initFileHeader(FILE *fp);
		unsigned short convertUnsignedShort(const unsigned char *buffer);
		unsigned int convertUnsignedInt(const unsigned char *buffer);

	private:
		unsigned char *m_pData;
		int m_nDatalength;
	};

} // end of namespace cocos2d
