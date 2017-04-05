/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#ifndef __SUPPORT_DATA_SUPPORT_TGALIB_H__
#define __SUPPORT_DATA_SUPPORT_TGALIB_H__
/// @cond DO_NOT_SHOW

namespace cocos2d {

enum {
    TGA_OK,
    TGA_ERROR_FILE_OPEN,
    TGA_ERROR_READING_FILE,
    TGA_ERROR_INDEXED_COLOR,
    TGA_ERROR_MEMORY,
    TGA_ERROR_COMPRESSED_FILE,
};

/** TGA format */
typedef struct sImageTGA {
    int status;
    unsigned char type, pixelDepth;
    
    /** map width */
    signed short width;
    
    /** map height */
    signed short height;
    
    /** raw data */
    unsigned char *imageData;
    int flipped;
} tImageTGA;

/// load the image header fields. We only keep those that matter!
bool tgaLoadHeader(unsigned char *buffer, unsigned long bufSize, tImageTGA *info);

/// loads the image pixels. You shouldn't call this function directly
bool tgaLoadImageData(unsigned char *buffer, unsigned long bufSize, tImageTGA *info);

/// this is the function to call when we want to load an image buffer.
tImageTGA* tgaLoadBuffer(unsigned char* buffer, long size);

/// this is the function to call when we want to load an image
tImageTGA * tgaLoad(const char *filename);

// /converts RGB to grayscale
void tgaRGBtogreyscale(tImageTGA *info);

/// releases the memory used for the image
void tgaDestroy(tImageTGA *info);

}//namespace cocos2d 

/// @endcond
#endif // __SUPPORT_DATA_SUPPORT_TGALIB_H__
