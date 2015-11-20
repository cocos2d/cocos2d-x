/* -*- tab-width: 4; -*- */
/* vi: set sw=2 ts=4: */

/* $Id: d555f6fdc46c28e4db334b44fdb8ac5b4bcef91a $ */

/* @internal
 * @~English
 * @file
 *
 * Unpack a texture compressed with ETC1
 *
 * @author Mark Callow, HI Corporation.
 */

/*
Copyright (c) 2010 The Khronos Group Inc.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and/or associated documentation files (the
"Materials"), to deal in the Materials without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Materials, and to
permit persons to whom the Materials are furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
unaltered in all copies or substantial portions of the Materials.
Any additions, deletions, or changes to the original source files
must be clearly indicated in accompanying documentation.

If only executable code is distributed, then the accompanying
documentation must state that "this software is based in part on the
work of the Khronos Group."

THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

#include <assert.h>
#include <stdlib.h>
#include "etc2types.h"

#define CC_ETC2_DECODE_USE_THREAD   (1)     // 1 : CPU decode by thread
#if CC_ETC2_DECODE_USE_THREAD
#include <vector>
#include <future>
#endif

typedef unsigned int uint;
typedef unsigned char uint8;

extern void decompressBlockETC2c(uint block_part1, uint block_part2, uint8* img,
								 int width, int height, int startx, int starty, int channels);
extern void decompressBlockETC21BitAlphaC(uint block_part1, uint block_part2, uint8* img, uint8* alphaimg,
										  int width, int height, int startx, int starty, int channels);
extern void decompressBlockAlphaC(uint8* data, uint8* img, int width, int height, int ix, int iy, int channels);
extern void decompressBlockAlpha16bitC(uint8* data, uint8* img, int width, int height, int ix, int iy, int channels);

extern void setupAlphaTable();

extern ETC2_error_code
_unpackETC(const GLubyte* __restrict srcETC, const GLenum srcFormat,
			  etc2_uint32_t activeWidth, etc2_uint32_t activeHeight,
			  GLubyte** __restrict dstImage,
			  GLenum* __restrict format, GLenum* __restrict internalFormat, GLenum* __restrict type,
			  GLint R16Formats, GLboolean supportsSRGB);

// This global variable affects the behaviour of decompressBlockAlpha16bitC.
extern int formatSigned;

static void
readBigEndian4byteWord(uint32_t* __restrict pBlock, const GLubyte* __restrict s)
{
	*pBlock = (s[0] << 24) | (s[1] << 16) | (s[2] << 8) | s[3];
}


/* Unpack an ETC1_RGB8_OES format compressed texture */
ETC2_error_code
_unpackETC(const GLubyte* __restrict srcETC, const GLenum srcFormat,
			  etc2_uint32_t activeWidth, etc2_uint32_t activeHeight,
			  GLubyte** __restrict dstImage,
			  GLenum* __restrict format, GLenum* __restrict internalFormat, GLenum* __restrict type,
			  GLint R16Formats, GLboolean supportsSRGB)
{
	unsigned int width, height;
#if !CC_ETC2_DECODE_USE_THREAD
	unsigned int block_part1, block_part2;
#endif
	unsigned int x, y;
	/*const*/ GLubyte* src = (GLubyte*)srcETC;
	// AF_11BIT is used to compress R11 & RG11 though its not alpha data.
	enum {AF_NONE, AF_1BIT, AF_8BIT, AF_11BIT} alphaFormat = AF_NONE;
	int dstChannels, dstChannelBytes;

	switch (srcFormat) {
	  case GL_COMPRESSED_SIGNED_R11_EAC:
		if (R16Formats & ETC2_R16_FORMATS_SNORM) {
			dstChannelBytes = sizeof(GLshort);
			dstChannels = 1;
			formatSigned = GL_TRUE;
			*internalFormat = GL_R16_SNORM;
			*format = GL_RED;
			*type = GL_SHORT;
			alphaFormat = AF_11BIT;
		} else
			return ETC2_UNSUPPORTED_TEXTURE_TYPE; 
		break;

	  case GL_COMPRESSED_R11_EAC:
		if (R16Formats & ETC2_R16_FORMATS_NORM) {
			dstChannelBytes = sizeof(GLshort);
			dstChannels = 1;
			formatSigned = GL_FALSE;
			*internalFormat = GL_R16;
			*format = GL_RED;
			*type = GL_UNSIGNED_SHORT;
			alphaFormat = AF_11BIT;
		} else
			return ETC2_UNSUPPORTED_TEXTURE_TYPE; 
        break;

	  case GL_COMPRESSED_SIGNED_RG11_EAC:
		if (R16Formats & ETC2_R16_FORMATS_SNORM) {
			dstChannelBytes = sizeof(GLshort);
			dstChannels = 2;
			formatSigned = GL_TRUE;
			*internalFormat = GL_RG16_SNORM;
			*format = GL_RG;
			*type = GL_SHORT;
			alphaFormat = AF_11BIT;
		} else
			return ETC2_UNSUPPORTED_TEXTURE_TYPE; 
        break;

	  case GL_COMPRESSED_RG11_EAC:
		if (R16Formats & ETC2_R16_FORMATS_NORM) {
			dstChannelBytes = sizeof(GLshort);
			dstChannels = 2;
			formatSigned = GL_FALSE;
			*internalFormat = GL_RG16;
			*format = GL_RG;
			*type = GL_UNSIGNED_SHORT;
			alphaFormat = AF_11BIT;
		} else
			return ETC2_UNSUPPORTED_TEXTURE_TYPE; 
        break;

	  case GL_ETC1_RGB8_OES:
	  case GL_COMPRESSED_RGB8_ETC2:
	    dstChannelBytes = sizeof(GLubyte);
		dstChannels = 3;
		*internalFormat = GL_RGB8;
		*format = GL_RGB;
		*type = GL_UNSIGNED_BYTE;
        break;

	  case GL_COMPRESSED_RGBA8_ETC2_EAC:
	    dstChannelBytes = sizeof(GLubyte);
		dstChannels = 4;
		*internalFormat = GL_RGBA8;
		*format = GL_RGBA;
		*type = GL_UNSIGNED_BYTE;
	    alphaFormat = AF_8BIT;
		break;

	  case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
	    dstChannelBytes = sizeof(GLubyte);
		dstChannels = 4;
		*internalFormat = GL_RGBA8;
		*format = GL_RGBA;
		*type = GL_UNSIGNED_BYTE;
		alphaFormat = AF_1BIT;
        break;

	  case GL_COMPRESSED_SRGB8_ETC2:
		if (supportsSRGB) {
			dstChannelBytes = sizeof(GLubyte);
			dstChannels = 3;
			*internalFormat = GL_SRGB8;
			*format = GL_RGB;
			*type = GL_UNSIGNED_BYTE;
		} else
			return ETC2_UNSUPPORTED_TEXTURE_TYPE; 
        break;

	  case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
		if (supportsSRGB) {
			dstChannelBytes = sizeof(GLubyte);
			dstChannels = 4;
			*internalFormat = GL_SRGB8_ALPHA8;
 			*format = GL_RGBA;
			*type = GL_UNSIGNED_BYTE;
			alphaFormat = AF_8BIT;
		} else
			return ETC2_UNSUPPORTED_TEXTURE_TYPE; 
		break;

	  case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
		if (supportsSRGB) {
			dstChannelBytes = sizeof(GLubyte);
			dstChannels = 4;
			*internalFormat = GL_SRGB8_ALPHA8;
 			*format = GL_RGBA;
			*type = GL_UNSIGNED_BYTE;
			alphaFormat = AF_1BIT;
		} else
			return ETC2_UNSUPPORTED_TEXTURE_TYPE; 
        break;

	  default:
	    assert(0); // Upper levels should be passing only one of the above srcFormats.
	}

    /* active_{width,height} show how many pixels contain active data,
	 * (the rest are just for making sure we have a 2*a x 4*b size).
	 */

	/* Compute the full width & height. */
	width = ((activeWidth+3)/4)*4;
	height = ((activeHeight+3)/4)*4;

	/* printf("Width = %d, Height = %d\n", width, height); */
	/* printf("active pixel area: top left %d x %d area.\n", activeWidth, activeHeight); */

    *dstImage = new GLubyte[dstChannels*dstChannelBytes*width*height];
    if (!*dstImage) {
        return ETC2_OUT_OF_MEMORY;
    }
    
    if (alphaFormat != AF_NONE)
        setupAlphaTable();

    // NOTE: none of the decompress functions actually use the <height> parameter
    switch (alphaFormat)
    {
        case AF_11BIT:
        {
            // One or two 11-bit alpha channels for R or RG.
            for (y=0; y < height/4; y++) {
                for (x=0; x < width/4; x++) {
                    decompressBlockAlpha16bitC(src, *dstImage, width, height, 4*x, 4*y, dstChannels);
                    src += 8;
                    if (srcFormat == GL_COMPRESSED_RG11_EAC || srcFormat == GL_COMPRESSED_SIGNED_RG11_EAC) {
                        decompressBlockAlpha16bitC(src, *dstImage + dstChannelBytes, width, height, 4*x, 4*y, dstChannels);
                        src += 8;
                    }
                }
            }
        }
        break;
        case AF_8BIT:
        {
#if !CC_ETC2_DECODE_USE_THREAD
            for (y=0; y < height/4; y++) {
                for (x=0; x < width/4; x++) {
                    // Decode alpha channel for RGBA
                    decompressBlockAlphaC(src, *dstImage + 3, width, height, 4*x, 4*y, dstChannels);
                    src += 8;
                    // Decode color dstChannels
                    readBigEndian4byteWord(&block_part1, src);
                    src += 4;
                    readBigEndian4byteWord(&block_part2, src);
                    src += 4;
                    decompressBlockETC2c(block_part1, block_part2, *dstImage, width, height, 4*x, 4*y, dstChannels);
                }
            }
#else
            std::vector<std::thread> threads;
            std::function<void(unsigned int, unsigned int)> decodeFunction = [src, dstImage, width, height, dstChannels](unsigned int start_y, unsigned int end_y)
            {
                auto srcth = src + start_y * (16*width/4);
                for (unsigned int ty=start_y; ty < end_y; ty++)
                {
                    unsigned int th_block_part1, th_block_part2;
                    for (unsigned int tx=0; tx < width/4; tx++) {
                        // Decode alpha channel for RGBA
                        decompressBlockAlphaC(srcth, *dstImage + 3, width, height, 4*tx, 4*ty, dstChannels);
                        srcth += 8;
                        // Decode color dstChannels
                        readBigEndian4byteWord(&th_block_part1, srcth);
                        srcth += 4;
                        readBigEndian4byteWord(&th_block_part2, srcth);
                        srcth += 4;
                        decompressBlockETC2c(th_block_part1, th_block_part2, *dstImage, width, height, 4*tx, 4*ty, dstChannels);
                    }
                }
            };
            threads.push_back(std::thread(decodeFunction, 0, height/16));
            threads.push_back(std::thread(decodeFunction, height/16, height/12));
            threads.push_back(std::thread(decodeFunction, height/12, height/8));
            threads.push_back(std::thread(decodeFunction, height/8, height/4));
            for (std::thread &th : threads)
            {
                th.join();
            }
#endif
        }
        break;
        case AF_1BIT:
        {
#if !CC_ETC2_DECODE_USE_THREAD
            for (y=0; y < height/4; y++) {
                for (x=0; x < width/4; x++) {
                    // Decode color dstChannels
                    readBigEndian4byteWord(&block_part1, src);
                    src += 4;
                    readBigEndian4byteWord(&block_part2, src);
                    src += 4;
                    decompressBlockETC21BitAlphaC(block_part1, block_part2, *dstImage, 0, width, height, 4*x, 4*y, dstChannels);
                }
            }
#else
            std::vector<std::thread> threads;
            std::function<void(unsigned int, unsigned int)> decodeFunction = [src, dstImage, width, height, dstChannels](unsigned int start_y, unsigned int end_y)
            {
                auto srcth = src + start_y * (8*width/4);
                for (unsigned int ty=start_y; ty < end_y; ty++)
                {
                    unsigned int th_block_part1, th_block_part2;
                    for (unsigned int tx=0; tx < width/4; tx++)
                    {
                        // Decode color dstChannels
                        readBigEndian4byteWord(&th_block_part1, srcth);
                        srcth += 4;
                        readBigEndian4byteWord(&th_block_part2, srcth);
                        srcth += 4;
                        decompressBlockETC21BitAlphaC(th_block_part1, th_block_part2, *dstImage, 0, width, height, 4*tx, 4*ty, dstChannels);
                    }
                }
            };
            threads.push_back(std::thread(decodeFunction, 0, height/16));
            threads.push_back(std::thread(decodeFunction, height/16, height/12));
            threads.push_back(std::thread(decodeFunction, height/12, height/8));
            threads.push_back(std::thread(decodeFunction, height/8, height/4));
            for (std::thread &th : threads)
            {
                th.join();
            }
#endif
        }
        break;
        default:
        {
#if !CC_ETC2_DECODE_USE_THREAD
            for (y=0; y < height/4; y++) {
                for (x=0; x < width/4; x++) {
                    // Decode color dstChannels
                    readBigEndian4byteWord(&block_part1, src);
                    src += 4;
                    readBigEndian4byteWord(&block_part2, src);
                    src += 4;
                    decompressBlockETC2c(block_part1, block_part2, *dstImage, width, height, 4*x, 4*y, dstChannels);
                }
            }
#else
            std::vector<std::thread> threads;
            std::function<void(unsigned int, unsigned int)> decodeFunction = [src, dstImage, width, height, dstChannels](unsigned int start_y, unsigned int end_y)
            {
                auto srcth = src + start_y * (8*width/4);
                for (unsigned int ty=start_y; ty < end_y; ty++)
                {
                    unsigned int th_block_part1, th_block_part2;
                    for (unsigned int tx=0; tx < width/4; tx++)
                    {
                        // Decode color dstChannels
                        readBigEndian4byteWord(&th_block_part1, srcth);
                        srcth += 4;
                        readBigEndian4byteWord(&th_block_part2, srcth);
                        srcth += 4;
                        decompressBlockETC2c(th_block_part1, th_block_part2, *dstImage, width, height, 4*tx, 4*ty, dstChannels);
                    }
                }
            };
            threads.push_back(std::thread(decodeFunction, 0, height/16));
            threads.push_back(std::thread(decodeFunction, height/16, height/12));
            threads.push_back(std::thread(decodeFunction, height/12, height/8));
            threads.push_back(std::thread(decodeFunction, height/8, height/4));
            for (std::thread &th : threads)
            {
                th.join();
            }
#endif
        }
        break;
    }

	/* Ok, now write out the active pixels to the destination image.
	 * (But only if the active pixels differ from the total pixels)
	 */

	if( !(height == activeHeight && width == activeWidth) ) {
		int dstPixelBytes = dstChannels * dstChannelBytes;
		int dstRowBytes = dstPixelBytes * width;
		int activeRowBytes = activeWidth * dstPixelBytes;
		GLubyte *newimg = (GLubyte*)malloc(dstPixelBytes * activeWidth * activeHeight);
		unsigned int xx, yy;
		int zz;

		if (!newimg) {
			free(*dstImage);
			return ETC2_OUT_OF_MEMORY;
		}
		
		/* Convert from total area to active area: */

		for (yy = 0; yy < activeHeight; yy++) {
			for (xx = 0; xx < activeWidth; xx++) {
				for (zz = 0; zz < dstPixelBytes; zz++) {
					newimg[ yy*activeRowBytes + xx*dstPixelBytes + zz ] = (*dstImage)[ yy*dstRowBytes + xx*dstPixelBytes + zz];
				}
			}
		}

		free(*dstImage);
		*dstImage = newimg;
	}

	return ETC2_SUCCESS;
}

