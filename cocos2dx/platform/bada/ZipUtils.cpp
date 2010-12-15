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
#include <zlib.h>

#include "ZipUtils.h"
#include "ccMacros.h"

namespace cocos2d
{
	int ZipUtils::inflateMemory_(unsigned char *in, unsigned int inLength, unsigned char **out, unsigned int *outLength)
	{
#if 1
		/* ret value */
		int err = Z_OK;

		/* 256k initial decompress buffer */
		int bufferSize = 256 * 1024;
		*out = new unsigned char[bufferSize];

		z_stream d_stream; /* decompression stream */	
		d_stream.zalloc = (alloc_func)0;
		d_stream.zfree = (free_func)0;
		d_stream.opaque = (voidpf)0;

		d_stream.next_in  = in;
		d_stream.avail_in = inLength;
		d_stream.next_out = *out;
		d_stream.avail_out = bufferSize;

		/* window size to hold 256k */
		if( (err = inflateInit2(&d_stream, 15 + 32)) != Z_OK )
		{
			return err;
		}

		for (;;) {
			err = inflate(&d_stream, Z_NO_FLUSH);

			if (err == Z_STREAM_END)
			{
				break;
			}

			switch (err) {
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
				// memory in iPhone is precious
				// Should buffer factor be 1.5 instead of 2 ?
#define BUFFER_INC_FACTOR (2)
				delete [] *out;
				*out = new unsigned char[bufferSize * BUFFER_INC_FACTOR];

				/* not enough memory, ouch */
				if (! *out ) 
				{
					CCLOG("cocos2d: ZipUtils: realloc failed");
					inflateEnd(&d_stream);
					return Z_MEM_ERROR;
				}

				d_stream.next_out = *out + bufferSize;
				d_stream.avail_out = bufferSize;
				bufferSize *= BUFFER_INC_FACTOR;
			}
		}


		*outLength = bufferSize - d_stream.avail_out;
		err = inflateEnd(&d_stream);
		return err;
#else
		return 0;
#endif
	}

	int ZipUtils::inflateMemory(unsigned char *in, unsigned int inLength, unsigned char **out)
	{
#if 1
		unsigned int outLength = 0;
		int err = inflateMemory_(in, inLength, out, &outLength);

		if (err != Z_OK || *out == NULL) {
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

			delete[] *out;
			*out = NULL;
			outLength = 0;
		}

		return outLength;
#else
		return 0;
#endif
	}

} // end of namespace cocos2d
