/****************************************************************************
Copyright (c) 2011		Jirka Fajfr for cocos2d-x
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

#include "CCTexture2D.h"
#include "CCTexturePVR.h"
#include "ccMacros.h"
#include "CCData.h"
#include "CCConfiguration.h"
#include "support/ccUtils.h"
#include "CCStdC.h"
#include "CCFileUtils.h"
#include "support/zip_support/ZipUtils.h"

#include <cctype>

namespace   cocos2d {

#define PVR_TEXTURE_FLAG_TYPE_MASK	0xff
#define PVR_TEXTURE_FLAG_FLIPPED_MASK 0x10000

// Values taken from PVRTexture.h from http://www.imgtec.com
enum {
    kPVRTextureFlagMipmap		= (1<<8),		// has mip map levels
    kPVRTextureFlagTwiddle		= (1<<9),		// is twiddled
    kPVRTextureFlagBumpmap		= (1<<10),		// has normals encoded for a bump map
    kPVRTextureFlagTiling		= (1<<11),		// is bordered for tiled pvr
    kPVRTextureFlagCubemap		= (1<<12),		// is a cubemap/skybox
    kPVRTextureFlagFalseMipCol	= (1<<13),		// are there false coloured MIP levels
    kPVRTextureFlagVolume		= (1<<14),		// is this a volume texture
    kPVRTextureFlagAlpha		= (1<<15),		// v2.1 is there transparency info in the texture
    kPVRTextureFlagVerticalFlip	= (1<<16),		// v2.1 is the texture vertically flipped
};
    
/*
	PVR header contains special field called PVRTag. This tag
	is used only to determine that passed file is really pvrt.

	Its set of 4 numbers. Each number casted to the char 
	must correspond to the "PVR!" string
*/
static unsigned int gPVRTexIdentifier[] = { 'P', 'V', 'R', '!'};

/*
	List of formats in pvr container
*/
enum
{
	kPVRTextureFlagTypeRGBA_4444= 0x10,
	kPVRTextureFlagTypeRGBA_5551,
	kPVRTextureFlagTypeRGBA_8888,
	kPVRTextureFlagTypeRGB_565,
	kPVRTextureFlagTypeRGB_555,				// unsupported
	kPVRTextureFlagTypeRGB_888,				// unsupported
	kPVRTextureFlagTypeI_8,
	kPVRTextureFlagTypeAI_88,
	kPVRTextureFlagTypePVRTC_2,
	kPVRTextureFlagTypePVRTC_4,	
	kPVRTextureFlagTypeBGRA_8888,
	kPVRTextureFlagTypeA_8,
};

/*
	Helps us to convert pvr format to the gl compatible bitspaces

	WARNING!! OpenGL ES 1.1. does not support GL_BGRA format. Its PowerVR 
	extension and it will work only on PowerVR chipsets. It means that

	kPVRTextureFlagTypeBGRA_8888 can be used only on apple devices (or PowerVR compatible)
*/
static const unsigned int tableFormats[][7] = {
	
	// - PVR texture format
	// - OpenGL internal format
	// - OpenGL format
	// - OpenGL type
	// - bpp
	// - compressed
    // - Cocos2d texture format constant
	{ kPVRTextureFlagTypeRGBA_4444, GL_RGBA,	GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4,	16, false, kCCTexture2DPixelFormat_RGBA4444	},
	{ kPVRTextureFlagTypeRGBA_5551, GL_RGBA,	GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1,	16, false, kCCTexture2DPixelFormat_RGB5A1	},
	{ kPVRTextureFlagTypeRGBA_8888, GL_RGBA,	GL_RGBA, GL_UNSIGNED_BYTE,			32, false, kCCTexture2DPixelFormat_RGBA8888	},
	{ kPVRTextureFlagTypeRGB_565,	GL_RGB,		GL_RGB,	 GL_UNSIGNED_SHORT_5_6_5,	16, false, kCCTexture2DPixelFormat_RGB565	},
    { kPVRTextureFlagTypeA_8,		GL_ALPHA,	GL_ALPHA,	GL_UNSIGNED_BYTE,		8,	false, kCCTexture2DPixelFormat_A8	    },
	{ kPVRTextureFlagTypeI_8,		GL_LUMINANCE,	GL_LUMINANCE,	GL_UNSIGNED_BYTE,			8,	false, kCCTexture2DPixelFormat_I8	},
	{ kPVRTextureFlagTypeAI_88,		GL_LUMINANCE_ALPHA,	GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,	16,	false, kCCTexture2DPixelFormat_AI88 },
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{ kPVRTextureFlagTypePVRTC_2,	GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, -1, -1,	2,	true, kCCTexture2DPixelFormat_PVRTC2 },
	{ kPVRTextureFlagTypePVRTC_4,	GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, -1, -1,	4,	true, kCCTexture2DPixelFormat_PVRTC4 },
	{ kPVRTextureFlagTypeBGRA_8888, GL_RGBA,	GL_BGRA, GL_UNSIGNED_BYTE,			32,	false, kCCTexture2DPixelFormat_RGBA8888	},
#endif
};

//Tells How large is tableFormats
#define MAX_TABLE_ELEMENTS (sizeof(tableFormats) / sizeof(tableFormats[0]))

/*
	Helper enum to traverse tableFormats
*/
enum {
	kCCInternalPVRTextureFormat,
	kCCInternalOpenGLInternalFormat,
	kCCInternalOpenGLFormat,
	kCCInternalOpenGLType,
	kCCInternalBPP,
	kCCInternalCompressedImage,
    kCCInternalCCTexture2DPixelFormat,
};

/*
	Official PVRT header
*/
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

CCTexturePVR::CCTexturePVR() :
    m_uTableFormatIndex(0),
	m_uNumberOfMipmaps(0)
{
}

CCTexturePVR::~CCTexturePVR()
{
	CCLOGINFO( "cocos2d: deallocing CCTexturePVR" );

	if (m_uName != 0 && ! m_bRetainName )
		glDeleteTextures(1, &m_uName);
}

GLuint CCTexturePVR::getName()
{
	return m_uName;
}

unsigned int CCTexturePVR::getWidth()
{
	return m_uWidth;
}

unsigned int CCTexturePVR::getHeight()
{
	return m_uHeight;
}

CCTexture2DPixelFormat CCTexturePVR::getFormat()
{
	return m_eFormat;
}

bool CCTexturePVR::getHasAlpha()
{
	return m_bHasAlpha;
}

bool CCTexturePVR::getRetainName()
{
	return m_bRetainName;
}

void CCTexturePVR::setRetainName(bool var)
{
	m_bRetainName = var;
}

bool CCTexturePVR::unpackPVRData(unsigned char* data, unsigned int len)
{
	bool success = false;
    PVRTexHeader *header = NULL;
    unsigned int flags, pvrTag;
	unsigned int dataLength = 0, dataOffset = 0, dataSize = 0;
	unsigned int blockSize = 0, widthBlocks = 0, heightBlocks = 0;
	unsigned int width = 0, height = 0, bpp = 4;
	unsigned char *bytes = NULL;
    unsigned int formatFlags;

	//Cast first sizeof(PVRTexHeader) bytes of data stream as PVRTexHeader
    header = (PVRTexHeader *)data;

	//Make sure that tag is in correct formatting
	pvrTag = CC_SWAP_INT32_LITTLE_TO_HOST(header->pvrTag);

	/*
		Check that given data really represents pvrtexture

		[0] = 'P'
		[1] = 'V'
		[2] = 'R'
		[3] = '!'
	*/
	if (gPVRTexIdentifier[0] != ((pvrTag >>  0) & 0xff) ||
		gPVRTexIdentifier[1] != ((pvrTag >>  8) & 0xff) ||
		gPVRTexIdentifier[2] != ((pvrTag >> 16) & 0xff) ||
		gPVRTexIdentifier[3] != ((pvrTag >> 24) & 0xff))
	{
		return false;
	}
    
    CCConfiguration *configuration = CCConfiguration::sharedConfiguration();

	//Get file flags (in correct byte order)
	flags = CC_SWAP_INT32_LITTLE_TO_HOST(header->flags);

	//Trim to only bites which are needed. Resulting flag is image format
	formatFlags = flags & PVR_TEXTURE_FLAG_TYPE_MASK;

	/*
     When flags combined with flipped mask is not empty (zero). 
     It means that image is compressed as flipped. We don't
     support automatic flipping.
     */
    bool flipped = (bool)(flags & kPVRTextureFlagVerticalFlip);
    if ( flipped )
    {
        CCLOG("cocos2d: WARNING: Image is flipped. Regenerate it using PVRTexTool");
    }

    if ( ! configuration->isSupportsNPOT() &&
        (header->width != ccNextPOT(header->width) || header->height != ccNextPOT(header->height)))
    {
        CCLOG("cocos2d: ERROR: Loding an NPOT texture (%dx%d) but is not supported on this device", header->width, header->height);
        return false;
    }
	
	//Check that sides of texture are power of two
	if(header->width != ccNextPOT(header->width) || header->height != ccNextPOT(header->height)) 
	{
		CCLOG("cocos2d: WARNING: PVR NPOT textures are not supported. Regenerate it.");
		return false;
	}

	//Go thru format array
	for (m_uTableFormatIndex = 0; m_uTableFormatIndex < (unsigned int)MAX_TABLE_ELEMENTS; m_uTableFormatIndex++)
	{
		//Does image format in table fits to the one parsed from header?
		if (tableFormats[m_uTableFormatIndex][kCCInternalPVRTextureFormat] == formatFlags)
		{
			//Reset num of mipmaps
			m_uNumberOfMipmaps = 0;

			//Get size of maimap
			m_uWidth = width = CC_SWAP_INT32_LITTLE_TO_HOST(header->width);
			m_uHeight = height = CC_SWAP_INT32_LITTLE_TO_HOST(header->height);
			
			//Do we use alpha ?
			if (CC_SWAP_INT32_LITTLE_TO_HOST(header->bitmaskAlpha))
				m_bHasAlpha = true;
			else
				m_bHasAlpha = false;
			
			//Get ptr to where data starts..
			dataLength = CC_SWAP_INT32_LITTLE_TO_HOST(header->dataLength);

			//Move by size of header
			bytes = ((unsigned char *)data) + sizeof(PVRTexHeader);
            m_eFormat = (CCTexture2DPixelFormat)( tableFormats[m_uTableFormatIndex][kCCInternalCCTexture2DPixelFormat] );
            bpp = tableFormats[m_uTableFormatIndex][kCCInternalBPP];
			
			// Calculate the data size for each texture level and respect the minimum number of blocks
			while (dataOffset < dataLength)
			{
				switch (formatFlags) {
					case kPVRTextureFlagTypePVRTC_2:
						blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
						widthBlocks = width / 8;
						heightBlocks = height / 4;
						bpp = 2;
						break;
					case kPVRTextureFlagTypePVRTC_4:
						blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
						widthBlocks = width / 4;
						heightBlocks = height / 4;
						bpp = 4;
						break;
					case kPVRTextureFlagTypeBGRA_8888:
						if (CCConfiguration::sharedConfiguration()->isSupportsBGRA8888() == false) 
						{
							CCLOG("cocos2d: TexturePVR. BGRA8888 not supported on this device");
							return false;
						}
					default:
						blockSize = 1;
						widthBlocks = width;
						heightBlocks = height;
						bpp = tableFormats[m_uTableFormatIndex][kCCInternalBPP];
						break;
				}
				
				// Clamp to minimum number of blocks
				if (widthBlocks < 2)
					widthBlocks = 2;
				if (heightBlocks < 2)
					heightBlocks = 2;

				dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);
				unsigned int packetLength = (dataLength-dataOffset);
				packetLength = packetLength > dataSize ? dataSize : packetLength;
				
				//Make record to the mipmaps array and increment coutner
				m_asMipmaps[m_uNumberOfMipmaps].address = bytes+dataOffset;
				m_asMipmaps[m_uNumberOfMipmaps].len = packetLength;
				m_uNumberOfMipmaps++;
				
				//Check that we didn't overflow
				CCAssert(m_uNumberOfMipmaps < CC_PVRMIPMAP_MAX, 
                         "TexturePVR: Maximum number of mimpaps reached. Increate the CC_PVRMIPMAP_MAX value");
				
				dataOffset += packetLength;
				
				//Update width and height to the next lower power of two 
				width = MAX(width >> 1, 1);
				height = MAX(height >> 1, 1);
			}
			
			//Mark pass as success
			success = true;
			break;
		}
	}

	if (false == success)
    {
		CCLOG("cocos2d: WARNING: Unssupported PVR Pixel Format: 0x%2x", formatFlags);
    }
	
	return success;
}

bool CCTexturePVR::createGLTexture()
{
	unsigned int width = m_uWidth;
	unsigned int height = m_uHeight;
	GLenum err;
	
	if (m_uNumberOfMipmaps > 0)
	{
		if (m_uName != 0)
        {
			glDeleteTextures(1, &m_uName);
        }
		
		glGenTextures(1, &m_uName);
		glBindTexture(GL_TEXTURE_2D, m_uName);
	}

	// Generate textures with mipmaps
	for (unsigned int i = 0; i < m_uNumberOfMipmaps; ++i)
	{
		GLenum internalFormat = tableFormats[m_uTableFormatIndex][kCCInternalOpenGLInternalFormat];
		GLenum format = tableFormats[m_uTableFormatIndex][kCCInternalOpenGLFormat];
		GLenum type = tableFormats[m_uTableFormatIndex][kCCInternalOpenGLType];
		bool compressed = tableFormats[m_uTableFormatIndex][kCCInternalCompressedImage] == 1;
		 
		if (compressed == true && CCConfiguration::sharedConfiguration()->isSupportsPVRTC() == false) 
		{
			CCLOG("cocos2d: WARNING: PVRTC images are not supported");
			return false;
		}			
		
		unsigned char *data = m_asMipmaps[i].address;
		unsigned int datalen = m_asMipmaps[i].len;
		
		if (compressed == true)
		{
			glCompressedTexImage2D(GL_TEXTURE_2D, i, internalFormat, width, height, 0, datalen, data);
		}
		else 
		{
			glTexImage2D(GL_TEXTURE_2D, i, internalFormat, width, height, 0, format, type, data);
		}

		if(i > 0 && (width != height || ccNextPOT(width) != width ) )
        {
			CCLOG("cocos2d: TexturePVR. WARNING. Mipmap level %lu is not squared. Texture won't render correctly. width=%lu != height=%lu", i, width, height);
        }
		
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			CCLOG("cocos2d: TexturePVR: Error uploading compressed texture level: %u . glError: 0x%04X", (unsigned int)i, err);
			return false;
		}
		
		//Update width and height to the next lower power of two
		width = MAX(width >> 1, 1);
		height = MAX(height >> 1, 1);
	}
		
	return true;
}


bool CCTexturePVR::initWithContentsOfFile(const char* path)
{
    unsigned char* pvrdata = NULL;
    int pvrlen = 0;
    
    std::string lowerCase(path);
    for (unsigned int i = 0; i < lowerCase.length(); ++i)
    {
        lowerCase[i] = tolower(lowerCase[i]);
    }
        
    if (lowerCase.find(".ccz") != std::string::npos)
    {
        pvrlen = ZipUtils::ccInflateCCZFile(path, &pvrdata);
    }
    else if (lowerCase.find(".gz") != std::string::npos)
    {
        pvrlen = ZipUtils::ccInflateGZipFile(path, &pvrdata);
    }
    else
    {
		pvrdata = CCFileUtils::getFileData(path, "rb", (unsigned long *)(&pvrlen));
    }
    
    if (pvrlen < 0)
    {
        this->release();
        return false;
    }
    
    m_uNumberOfMipmaps = 0;

	m_uName = 0;
	m_uWidth = m_uHeight = 0;
	m_bHasAlpha = false;

	m_bRetainName = false; // cocos2d integration

	if ( !unpackPVRData(pvrdata, pvrlen)  || !createGLTexture() )
	{
		delete [] pvrdata;
		this->release();
		return false;
	}

    delete [] pvrdata;
    
	return true;
}

CCTexturePVR * CCTexturePVR::pvrTextureWithContentsOfFile(const char* path)
{
	CCTexturePVR * pTexture = new CCTexturePVR();
	if(true == pTexture->initWithContentsOfFile(path))
    {
        pTexture->autorelease();
        return pTexture;
    }
    else
    {
        return NULL;
    }
}

}//namespace   cocos2d 
