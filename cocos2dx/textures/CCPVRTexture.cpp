/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008      Apple Inc. All Rights Reserved.

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

#if 0 // PVR TEXTURE CANNOT CROSS PLATFORM

#include "CCPVRTexture.h"
#include "ccMacros.h"
#include "CCData.h"

namespace   cocos2d {

#define PVR_TEXTURE_FLAG_TYPE_MASK	0xff

static char* gPVRTexIdentifier[] = {"PVR!"};

enum
{
	kPVRTextureFlagTypePVRTC_2 = 24,
	kPVRTextureFlagTypePVRTC_4
};

typedef struct _PVRTexHeader
{
	unsigned int headerLength;
	unsigned int height;
	unsigned int width;
	unsigned int numMipmaps;
	unsigned int flags;
	unsigned int dataLength;
	unsigned int bpp;
	unsigned int bitmaskRed;
	unsigned int bitmaskGreen;
	unsigned int bitmaskBlue;
	unsigned int bitmaskAlpha;
	unsigned int pvrTag;
	unsigned int numSurfs;
} PVRTexHeader;

CCPVRTexture::CCPVRTexture()
{
}

CCPVRTexture::~CCPVRTexture()
{
	CCLOGINFO( "cocos2d: deallocing CCPVRTexture" );

	m_pImageData->removeAllObjects();
	CC_SAFE_DELETE(m_pImageData)

	if (m_uName != 0 && ! m_bRetainName )
		glDeleteTextures(1, &m_uName);
}

GLuint CCPVRTexture::getName()
{
	return m_uName;
}

unsigned int CCPVRTexture::getWidth()
{
	return m_uWidth;
}

unsigned int CCPVRTexture::getHeight()
{
	return m_uHeight;
}

GLenum CCPVRTexture::getInternalFormat()
{
	return m_uInternalFormat;
}

bool CCPVRTexture::getHasAlpha()
{
	return m_bHasAlpha;
}

bool CCPVRTexture::getRetainName()
{
	return m_bRetainName;
}

void CCPVRTexture::setRetainName(bool var)
{
	m_bRetainName = var;
}

/** @todo CCData uint8_t
- (BOOL)unpackPVRData:(CCData *)data
{
	BOOL success = FALSE;
	PVRTexHeader *header = NULL;
	uint32_t flags, pvrTag;
	uint32_t dataLength = 0, dataOffset = 0, dataSize = 0;
	uint32_t blockSize = 0, widthBlocks = 0, heightBlocks = 0;
	uint32_t width = 0, height = 0, bpp = 4;
	uint8_t *bytes = NULL;
	uint32_t formatFlags;

	header = (PVRTexHeader *)[data bytes];

	pvrTag = CFSwapInt32LittleToHost(header->pvrTag);

	if ((uint32_t)gPVRTexIdentifier[0] != ((pvrTag >>  0) & 0xff) ||
		(uint32_t)gPVRTexIdentifier[1] != ((pvrTag >>  8) & 0xff) ||
		(uint32_t)gPVRTexIdentifier[2] != ((pvrTag >> 16) & 0xff) ||
		(uint32_t)gPVRTexIdentifier[3] != ((pvrTag >> 24) & 0xff))
	{
		return FALSE;
	}

	flags = CFSwapInt32LittleToHost(header->flags);
	formatFlags = flags & PVR_TEXTURE_FLAG_TYPE_MASK;

	if (formatFlags == kPVRTextureFlagTypePVRTC_4 || formatFlags == kPVRTextureFlagTypePVRTC_2)
	{
		[_imageData removeAllObjects];

		if (formatFlags == kPVRTextureFlagTypePVRTC_4)
			_internalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
		else if (formatFlags == kPVRTextureFlagTypePVRTC_2)
			_internalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;

		_width = width = CFSwapInt32LittleToHost(header->width);
		_height = height = CFSwapInt32LittleToHost(header->height);

		if (CFSwapInt32LittleToHost(header->bitmaskAlpha))
			_hasAlpha = TRUE;
		else
			_hasAlpha = FALSE;

		dataLength = CFSwapInt32LittleToHost(header->dataLength);

		bytes = ((uint8_t *)[data bytes]) + sizeof(PVRTexHeader);

		// Calculate the data size for each texture level and respect the minimum number of blocks
		while (dataOffset < dataLength)
		{
			if (formatFlags == kPVRTextureFlagTypePVRTC_4)
			{
				blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
				widthBlocks = width / 4;
				heightBlocks = height / 4;
				bpp = 4;
			}
			else
			{
				blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
				widthBlocks = width / 8;
				heightBlocks = height / 4;
				bpp = 2;
			}

			// Clamp to minimum number of blocks
			if (widthBlocks < 2)
				widthBlocks = 2;
			if (heightBlocks < 2)
				heightBlocks = 2;

			dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);

			[_imageData addObject:[CCData dataWithBytes:bytes+dataOffset length:dataSize]];

			dataOffset += dataSize;

			width = MAX(width >> 1, 1);
			height = MAX(height >> 1, 1);
		}

		success = TRUE;
	}

	return success;
}*/


bool CCPVRTexture::createGLTexture()
{
	int width = m_uWidth;
	int height = m_uHeight;
/// @todo	CCData *data;
	GLenum err;

	if (m_pImageData->count() > 0)
	{
		if (m_uName != 0)
			glDeleteTextures(1, &m_uName);

		glGenTextures(1, &m_uName);
		glBindTexture(GL_TEXTURE_2D, m_uName);
	}

	for (unsigned int i=0; i < m_pImageData->count(); i++)
	{
/// @todo CCData		data = m_pImageData->getObjectAtIndex(i);
/// @todo CCData		glCompressedTexImage2D(GL_TEXTURE_2D, i, m_uInternalFormat, width, height, 0, [data length], [data bytes]);

		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			CCLOG("Error uploading compressed texture level: %u. glError: %u", i, err);
			return false;
		}

		width = MAX(width >> 1, 1);
		height = MAX(height >> 1, 1);
	}

	m_pImageData->removeAllObjects();

	return true;
}


CCPVRTexture * CCPVRTexture::initWithContentsOfFile(const char* path)
{
	/** @todo CCData*/
	CCData *data = CCData::dataWithContentsOfFile(path);

	m_pImageData = new CCMutableArray<CCData*>(10);

	m_uName = 0;
	m_uWidth = m_uHeight = 0;
	m_uInternalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
	m_bHasAlpha = false;

	m_bRetainName = false; // cocos2d integration
/// @todo
// 	if (!data || ![self unpackPVRData:data] || ![self createGLTexture])
// 	{
// 		[self release];
// 		self = nil;
// 	}

	return this;
}

/** @todo NSURL
- (id)initWithContentsOfURL:(NSURL *)url
{
	if (![url isFileURL])
	{
		CCLOG(@"cocos2d: CCPVRTexture: Only files are supported");
		[self release];
		return nil;
	}

	return [self initWithContentsOfFile:[url path]];
}*/


CCPVRTexture * CCPVRTexture::pvrTextureWithContentsOfFile(const char* path)
{
	CCPVRTexture * pTexture = new CCPVRTexture();
	pTexture->initWithContentsOfFile(path);
	pTexture->autorelease();
	return pTexture;
}

/** @todo NSURL
+ (id)pvrTextureWithContentsOfURL:(NSURL *)url
{
	if (![url isFileURL])
		return nil;

	return [CCPVRTexture pvrTextureWithContentsOfFile:[url path]];
}*/

}//namespace   cocos2d 

#endif
