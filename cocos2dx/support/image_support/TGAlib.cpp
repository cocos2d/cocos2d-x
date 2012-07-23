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

#include <string.h>
#include <stdlib.h>

#include "TGAlib.h"
#include "CCFileUtils.h"

namespace   cocos2d {

void tgaLoadRLEImageData(FILE *file, tImageTGA *info);
void tgaFlipImage( tImageTGA *info );

// load the image header field from stream
bool tgaLoadHeader(unsigned char* Buffer, unsigned long bufSize, tImageTGA *psInfo)
{
    bool bRet = false;

    do 
    {
        size_t step = sizeof(unsigned char) * 2;
        CC_BREAK_IF((step + sizeof(unsigned char)) > bufSize);
        memcpy(&psInfo->type, Buffer + step, sizeof(unsigned char));

        step += sizeof(unsigned char) * 2;
        step += sizeof(signed short) * 4;
        CC_BREAK_IF((step + sizeof(signed short) * 2 + sizeof(unsigned char)) > bufSize);
        memcpy(&psInfo->width, Buffer + step, sizeof(signed short));
        memcpy(&psInfo->height, Buffer + step + sizeof(signed short), sizeof(signed short));
        memcpy(&psInfo->pixelDepth, Buffer + step + sizeof(signed short) * 2, sizeof(unsigned char));

        step += sizeof(unsigned char);
        step += sizeof(signed short) * 2;
        CC_BREAK_IF((step + sizeof(unsigned char)) > bufSize);
        unsigned char cGarbage;
        memcpy(&cGarbage, Buffer + step, sizeof(unsigned char));

        psInfo->flipped = 0;
        if ( cGarbage & 0x20 ) 
        {
            psInfo->flipped = 1;
        }
        bRet = true;
    } while (0);

    return bRet;
}

bool tgaLoadImageData(unsigned char *Buffer, unsigned long bufSize, tImageTGA *psInfo)
{
    bool bRet = false;

    do 
    {
        int mode,total,i;
        unsigned char aux;
        size_t step = (sizeof(unsigned char) + sizeof(signed short)) * 6;

        // mode equal the number of components for each pixel
        mode = psInfo->pixelDepth / 8;
        // total is the number of unsigned chars we'll have to read
        total = psInfo->height * psInfo->width * mode;

        size_t dataSize = sizeof(unsigned char) * total;
        CC_BREAK_IF((step + dataSize) > bufSize);
        memcpy(psInfo->imageData, Buffer + step, dataSize);

        // mode=3 or 4 implies that the image is RGB(A). However TGA
        // stores it as BGR(A) so we'll have to swap R and B.
        if (mode >= 3)
        {
            for (i=0; i < total; i+= mode)
            {
                aux = psInfo->imageData[i];
                psInfo->imageData[i] = psInfo->imageData[i+2];
                psInfo->imageData[i+2] = aux;
            }
        }

        bRet = true;
    } while (0);

    return bRet;
}

static bool tgaLoadRLEImageData(unsigned char* Buffer, unsigned long bufSize, tImageTGA *psInfo)
{
    unsigned int mode,total,i, index = 0;
    unsigned char aux[4], runlength = 0;
    unsigned int skip = 0, flag = 0;
    size_t step = (sizeof(unsigned char) + sizeof(signed short)) * 6;

    // mode equal the number of components for each pixel
    mode = psInfo->pixelDepth / 8;
    // total is the number of unsigned chars we'll have to read
    total = psInfo->height * psInfo->width;

    for( i = 0; i < total; i++ )
    {
        // if we have a run length pending, run it
        if ( runlength != 0 )
        {
            // we do, update the run length count
            runlength--;
            skip = (flag != 0);
        }
        else
        {
            // otherwise, read in the run length token
            CC_BREAK_IF((step + sizeof(unsigned char)) > bufSize);
            memcpy(&runlength, Buffer + step, sizeof(unsigned char));
            step += sizeof(unsigned char);

            // see if it's a RLE encoded sequence
            flag = runlength & 0x80;
            if ( flag )
            {
                runlength -= 128;
            }
            skip = 0;
        }

        // do we need to skip reading this pixel?
        if ( !skip )
        {
            // no, read in the pixel data
            CC_BREAK_IF((step + sizeof(unsigned char) * mode) > bufSize);

            memcpy(aux, Buffer + step, sizeof(unsigned char) * mode);
            step += sizeof(unsigned char) * mode;

            // mode=3 or 4 implies that the image is RGB(A). However TGA
            // stores it as BGR(A) so we'll have to swap R and B.
            if ( mode >= 3 )
            {
                unsigned char tmp;

                tmp = aux[0];
                aux[0] = aux[2];
                aux[2] = tmp;
            }
        }

        // add the pixel to our image
        memcpy(&psInfo->imageData[index], aux, mode);
        index += mode;
    }
    
    return true;
}

void tgaFlipImage( tImageTGA *psInfo )
{
	// mode equal the number of components for each pixel
	int mode = psInfo->pixelDepth / 8;
	int rowbytes = psInfo->width*mode;
	unsigned char *row = (unsigned char *)malloc(rowbytes);
	int y;
	
	if (row == NULL) return;
	
	for( y = 0; y < (psInfo->height/2); y++ )
	{
		memcpy(row, &psInfo->imageData[y*rowbytes],rowbytes);
		memcpy(&psInfo->imageData[y*rowbytes], &psInfo->imageData[(psInfo->height-(y+1))*rowbytes], rowbytes);
		memcpy(&psInfo->imageData[(psInfo->height-(y+1))*rowbytes], row, rowbytes);
	}
	
	free(row);
	psInfo->flipped = 0;
}

// this is the function to call when we want to load an image
tImageTGA * tgaLoad(const char *pszFilename)
{
    int mode,total;
    tImageTGA *info = NULL;
    CCFileData data(pszFilename, "rb");
    unsigned long nSize = data.getSize();
    unsigned char* pBuffer = data.getBuffer();

    do
    {
        CC_BREAK_IF(! pBuffer);
        info = (tImageTGA *)malloc(sizeof(tImageTGA));

        // get the file header info
        if (! tgaLoadHeader(pBuffer, nSize, info))
        {
            info->status = TGA_ERROR_MEMORY;
            break;
        }

        // check if the image is color indexed
        if (info->type == 1)
        {
            info->status = TGA_ERROR_INDEXED_COLOR;
            break;
        }

        // check for other types (compressed images)
        if ((info->type != 2) && (info->type !=3) && (info->type !=10) )
        {
            info->status = TGA_ERROR_COMPRESSED_FILE;
            break;
        }

        // mode equals the number of image components
        mode = info->pixelDepth / 8;
        // total is the number of unsigned chars to read
        total = info->height * info->width * mode;
        // allocate memory for image pixels
        info->imageData = (unsigned char *)malloc(sizeof(unsigned char) * total);

        // check to make sure we have the memory required
        if (info->imageData == NULL)
        {
            info->status = TGA_ERROR_MEMORY;
            break;
        }

        bool bLoadImage = false;
        // finally load the image pixels
        if ( info->type == 10 )
        {
            bLoadImage = tgaLoadRLEImageData(pBuffer, nSize, info);
        }
        else
        {
            bLoadImage = tgaLoadImageData(pBuffer, nSize, info);
        }

        // check for errors when reading the pixels
        if (! bLoadImage)
        {
            info->status = TGA_ERROR_READING_FILE;
            break;
        }
        info->status = TGA_OK;

        if ( info->flipped )
        {
            tgaFlipImage( info );
            if ( info->flipped )
            {
                info->status = TGA_ERROR_MEMORY;
            }
        }
    } while(0);

    return info;
}

// converts RGB to greyscale
void tgaRGBtogreyscale(tImageTGA *psInfo) {
	
	int mode,i,j;
	
	unsigned char *newImageData;
	
	// if the image is already greyscale do nothing
	if (psInfo->pixelDepth == 8)
		return;
	
	// compute the number of actual components
	mode = psInfo->pixelDepth / 8;
	
	// allocate an array for the new image data
	newImageData = (unsigned char *)malloc(sizeof(unsigned char) * 
										   psInfo->height * psInfo->width);
	if (newImageData == NULL) {
		return;
	}
	
	// convert pixels: greyscale = o.30 * R + 0.59 * G + 0.11 * B
	for (i = 0,j = 0; j < psInfo->width * psInfo->height; i +=mode, j++)
		newImageData[j] =	
		(unsigned char)(0.30 * psInfo->imageData[i] + 
						0.59 * psInfo->imageData[i+1] +
						0.11 * psInfo->imageData[i+2]);
	
	
	//free old image data
	free(psInfo->imageData);
	
	// reassign pixelDepth and type according to the new image type
	psInfo->pixelDepth = 8;
	psInfo->type = 3;
	// reassing imageData to the new array.
	psInfo->imageData = newImageData;
}

// releases the memory used for the image
void tgaDestroy(tImageTGA *psInfo) {
	
	if (psInfo != NULL) {
		if (psInfo->imageData != NULL)
		{
			free(psInfo->imageData);
		}

		free(psInfo);
	}
}
}//namespace   cocos2d 
