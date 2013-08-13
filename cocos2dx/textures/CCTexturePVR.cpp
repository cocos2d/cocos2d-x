/****************************************************************************
Copyright (c) 2011        Jirka Fajfr for cocos2d-x
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "CCConfiguration.h"
#include "support/ccUtils.h"
#include "CCStdC.h"
#include "platform/CCFileUtils.h"
#include "support/zip_support/ZipUtils.h"
#include "shaders/ccGLStateCache.h"
#include <ctype.h>
#include <cctype>

NS_CC_BEGIN

#define PVR_TEXTURE_FLAG_TYPE_MASK    0xff

//
// XXX DO NO ALTER THE ORDER IN THIS LIST XXX
//
static const ccPVRTexturePixelFormatInfo PVRTableFormats[] = {
	
	// 0: BGRA_8888
	{GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE, 32, false, true, kCCTexture2DPixelFormat_RGBA8888},
	// 1: RGBA_8888
	{GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 32, false, true, kCCTexture2DPixelFormat_RGBA8888},
	// 2: RGBA_4444
	{GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 16, false, true, kCCTexture2DPixelFormat_RGBA4444},
	// 3: RGBA_5551
	{GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 16, false, true, kCCTexture2DPixelFormat_RGB5A1},
	// 4: RGB_565
	{GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 16, false, false, kCCTexture2DPixelFormat_RGB565},
	// 5: RGB_888
	{GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 24, false, false, kCCTexture2DPixelFormat_RGB888},
	// 6: A_8
	{GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 8, false, false, kCCTexture2DPixelFormat_A8},
	// 7: L_8
	{GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 8, false, false, kCCTexture2DPixelFormat_I8},
	// 8: LA_88
	{GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 16, false, true, kCCTexture2DPixelFormat_AI88},

// Not all platforms include GLES/gl2ext.h so these PVRTC enums are not always
// available.
#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
	// 9: PVRTC 2BPP RGB
	{GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, false, kCCTexture2DPixelFormat_PVRTC2},
	// 10: PVRTC 2BPP RGBA
	{GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, true, kCCTexture2DPixelFormat_PVRTC2},
	// 11: PVRTC 4BPP RGB
	{GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false, kCCTexture2DPixelFormat_PVRTC4},
	// 12: PVRTC 4BPP RGBA
	{GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, true, kCCTexture2DPixelFormat_PVRTC4},
#endif
};

struct _pixel_formathash {
	uint64_t pixelFormat;
	const ccPVRTexturePixelFormatInfo * pixelFormatInfo;
};

// Values taken from PVRTexture.h from http://www.imgtec.com
enum {
    kPVR2TextureFlagMipmap         = (1<<8),        // has mip map levels
    kPVR2TextureFlagTwiddle        = (1<<9),        // is twiddled
    kPVR2TextureFlagBumpmap        = (1<<10),       // has normals encoded for a bump map
    kPVR2TextureFlagTiling         = (1<<11),       // is bordered for tiled pvr
    kPVR2TextureFlagCubemap        = (1<<12),       // is a cubemap/skybox
    kPVR2TextureFlagFalseMipCol    = (1<<13),       // are there false colored MIP levels
    kPVR2TextureFlagVolume         = (1<<14),       // is this a volume texture
    kPVR2TextureFlagAlpha          = (1<<15),       // v2.1 is there transparency info in the texture
    kPVR2TextureFlagVerticalFlip   = (1<<16),       // v2.1 is the texture vertically flipped
};

enum {
	kPVR3TextureFlagPremultipliedAlpha	= (1<<1)	// has premultiplied alpha
};
    
static char gPVRTexIdentifier[5] = "PVR!";

// v2
typedef enum
{
	kPVR2TexturePixelFormat_RGBA_4444= 0x10,
	kPVR2TexturePixelFormat_RGBA_5551,
	kPVR2TexturePixelFormat_RGBA_8888,
	kPVR2TexturePixelFormat_RGB_565,
	kPVR2TexturePixelFormat_RGB_555,				// unsupported
	kPVR2TexturePixelFormat_RGB_888,
	kPVR2TexturePixelFormat_I_8,
	kPVR2TexturePixelFormat_AI_88,
	kPVR2TexturePixelFormat_PVRTC_2BPP_RGBA,
	kPVR2TexturePixelFormat_PVRTC_4BPP_RGBA,
	kPVR2TexturePixelFormat_BGRA_8888,
	kPVR2TexturePixelFormat_A_8,
} ccPVR2TexturePixelFormat;

// v3
/* supported predefined formats */
#define kPVR3TexturePixelFormat_PVRTC_2BPP_RGB   0
#define kPVR3TexturePixelFormat_PVRTC_2BPP_RGBA  1
#define kPVR3TexturePixelFormat_PVRTC_4BPP_RGB   2
#define kPVR3TexturePixelFormat_PVRTC_4BPP_RGBA  3
	
/* supported channel type formats */
#define kPVR3TexturePixelFormat_BGRA_8888  0x0808080861726762ULL
#define kPVR3TexturePixelFormat_RGBA_8888  0x0808080861626772ULL
#define kPVR3TexturePixelFormat_RGBA_4444  0x0404040461626772ULL
#define kPVR3TexturePixelFormat_RGBA_5551  0x0105050561626772ULL
#define kPVR3TexturePixelFormat_RGB_565    0x0005060500626772ULL
#define kPVR3TexturePixelFormat_RGB_888    0x0008080800626772ULL
#define kPVR3TexturePixelFormat_A_8        0x0000000800000061ULL
#define kPVR3TexturePixelFormat_L_8        0x000000080000006cULL
#define kPVR3TexturePixelFormat_LA_88      0x000008080000616cULL


// v2
static struct _pixel_formathash v2_pixel_formathash[] = {
    
	{ kPVR2TexturePixelFormat_BGRA_8888,	&PVRTableFormats[0] },
	{ kPVR2TexturePixelFormat_RGBA_8888,	&PVRTableFormats[1] },
	{ kPVR2TexturePixelFormat_RGBA_4444,	&PVRTableFormats[2] },
	{ kPVR2TexturePixelFormat_RGBA_5551,	&PVRTableFormats[3] },
	{ kPVR2TexturePixelFormat_RGB_565,		&PVRTableFormats[4] },
	{ kPVR2TexturePixelFormat_RGB_888,		&PVRTableFormats[5] },
	{ kPVR2TexturePixelFormat_A_8,			&PVRTableFormats[6] },
	{ kPVR2TexturePixelFormat_I_8,			&PVRTableFormats[7] },
	{ kPVR2TexturePixelFormat_AI_88,		&PVRTableFormats[8] },
    
#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
	{ kPVR2TexturePixelFormat_PVRTC_2BPP_RGBA,	&PVRTableFormats[10] },
	{ kPVR2TexturePixelFormat_PVRTC_4BPP_RGBA,	&PVRTableFormats[12] },
#endif
};

#define PVR2_MAX_TABLE_ELEMENTS (sizeof(v2_pixel_formathash) / sizeof(v2_pixel_formathash[0]))

// v3
struct _pixel_formathash v3_pixel_formathash[] = {
	
	{kPVR3TexturePixelFormat_BGRA_8888,	&PVRTableFormats[0] },
	{kPVR3TexturePixelFormat_RGBA_8888,	&PVRTableFormats[1] },
	{kPVR3TexturePixelFormat_RGBA_4444, &PVRTableFormats[2] },
	{kPVR3TexturePixelFormat_RGBA_5551, &PVRTableFormats[3] },
	{kPVR3TexturePixelFormat_RGB_565,	&PVRTableFormats[4] },
	{kPVR3TexturePixelFormat_RGB_888,	&PVRTableFormats[5] },
	{kPVR3TexturePixelFormat_A_8,		&PVRTableFormats[6] },
	{kPVR3TexturePixelFormat_L_8,		&PVRTableFormats[7] },
	{kPVR3TexturePixelFormat_LA_88,		&PVRTableFormats[8] },
	
#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
	{kPVR3TexturePixelFormat_PVRTC_2BPP_RGB,	&PVRTableFormats[9] },
	{kPVR3TexturePixelFormat_PVRTC_2BPP_RGBA,	&PVRTableFormats[10] },
	{kPVR3TexturePixelFormat_PVRTC_4BPP_RGB,	&PVRTableFormats[11] },
	{kPVR3TexturePixelFormat_PVRTC_4BPP_RGBA,	&PVRTableFormats[12] },
#endif
};


//Tells How large is tableFormats
#define PVR3_MAX_TABLE_ELEMENTS (sizeof(v3_pixel_formathash) / sizeof(v3_pixel_formathash[0]))


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
} ccPVRv2TexHeader;

#ifdef _MSC_VER
#pragma pack(push,1)
#endif
typedef struct {
	uint32_t version;
	uint32_t flags;
	uint64_t pixelFormat;
	uint32_t colorSpace;
	uint32_t channelType;
	uint32_t height;
	uint32_t width;
	uint32_t depth;
	uint32_t numberOfSurfaces;
	uint32_t numberOfFaces;
	uint32_t numberOfMipmaps;
	uint32_t metadataLength;
#ifdef _MSC_VER
} ccPVRv3TexHeader;
#pragma pack(pop)
#else
} __attribute__((packed)) ccPVRv3TexHeader;
#endif


CCTexturePVR::CCTexturePVR() 
: m_uNumberOfMipmaps(0)
, m_uWidth(0)
, m_uHeight(0)
, m_uName(0)
, m_bHasAlpha(false)
, m_bHasPremultipliedAlpha(false)
, m_bForcePremultipliedAlpha(false)
, m_bRetainName(false)
, m_eFormat(kCCTexture2DPixelFormat_Default)
, m_pPixelFormatInfo(NULL)
{
}

CCTexturePVR::~CCTexturePVR()
{
    CCLOGINFO( "cocos2d: deallocing CCTexturePVR" );

    if (m_uName != 0 && ! m_bRetainName)
    {
        ccGLDeleteTexture(m_uName);
    }
}

bool CCTexturePVR::unpackPVRv2Data(unsigned char* data, unsigned int len)
{
    bool success = false;
    ccPVRv2TexHeader *header = NULL;
    unsigned int flags, pvrTag;
    unsigned int dataLength = 0, dataOffset = 0, dataSize = 0;
    unsigned int blockSize = 0, widthBlocks = 0, heightBlocks = 0;
    unsigned int width = 0, height = 0, bpp = 4;
    unsigned char *bytes = NULL;
    unsigned int formatFlags;

    //Cast first sizeof(PVRTexHeader) bytes of data stream as PVRTexHeader
    header = (ccPVRv2TexHeader *)data;

    //Make sure that tag is in correct formatting
    pvrTag = CC_SWAP_INT32_LITTLE_TO_HOST(header->pvrTag);

    if (gPVRTexIdentifier[0] != (char)(((pvrTag >>  0) & 0xff)) ||
        gPVRTexIdentifier[1] != (char)(((pvrTag >>  8) & 0xff)) ||
        gPVRTexIdentifier[2] != (char)(((pvrTag >> 16) & 0xff)) ||
        gPVRTexIdentifier[3] != (char)(((pvrTag >> 24) & 0xff)))
    {
        return false;
    }
    
    CCConfiguration *configuration = CCConfiguration::sharedConfiguration();

    flags = CC_SWAP_INT32_LITTLE_TO_HOST(header->flags);
    formatFlags = flags & PVR_TEXTURE_FLAG_TYPE_MASK;
    bool flipped = (flags & kPVR2TextureFlagVerticalFlip) ? true : false;
    if (flipped)
    {
        CCLOG("cocos2d: WARNING: Image is flipped. Regenerate it using PVRTexTool");
    }

    if (! configuration->supportsNPOT() &&
        (header->width != ccNextPOT(header->width) || header->height != ccNextPOT(header->height)))
    {
        CCLOG("cocos2d: ERROR: Loading an NPOT texture (%dx%d) but is not supported on this device", header->width, header->height);
        return false;
    }
    
    unsigned int pvr2TableElements = PVR2_MAX_TABLE_ELEMENTS;
    if (! CCConfiguration::sharedConfiguration()->supportsPVRTC())
    {
        pvr2TableElements = 9;
    }

    for (unsigned int i = 0; i < pvr2TableElements; i++)
    {
        //Does image format in table fits to the one parsed from header?
        if (v2_pixel_formathash[i].pixelFormat == formatFlags)
        {
            m_pPixelFormatInfo = v2_pixel_formathash[i].pixelFormatInfo;
            
            //Reset num of mipmaps
            m_uNumberOfMipmaps = 0;

            //Get size of mipmap
            m_uWidth = width = CC_SWAP_INT32_LITTLE_TO_HOST(header->width);
            m_uHeight = height = CC_SWAP_INT32_LITTLE_TO_HOST(header->height);
            
            //Do we use alpha ?
            if (CC_SWAP_INT32_LITTLE_TO_HOST(header->bitmaskAlpha))
            {
                m_bHasAlpha = true;
            }
            else
            {
                m_bHasAlpha = false;
            }
            
            //Get ptr to where data starts..
            dataLength = CC_SWAP_INT32_LITTLE_TO_HOST(header->dataLength);

            //Move by size of header
            bytes = ((unsigned char *)data) + sizeof(ccPVRv2TexHeader);
            m_eFormat = m_pPixelFormatInfo->ccPixelFormat;
            bpp = m_pPixelFormatInfo->bpp;
            
            // Calculate the data size for each texture level and respect the minimum number of blocks
            while (dataOffset < dataLength)
            {
                switch (formatFlags) {
                    case kPVR2TexturePixelFormat_PVRTC_2BPP_RGBA:
                        blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
                        widthBlocks = width / 8;
                        heightBlocks = height / 4;
                        break;
                    case kPVR2TexturePixelFormat_PVRTC_4BPP_RGBA:
                        blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
                        widthBlocks = width / 4;
                        heightBlocks = height / 4;
                        break;
                    case kPVR2TexturePixelFormat_BGRA_8888:
                        if (CCConfiguration::sharedConfiguration()->supportsBGRA8888() == false) 
                        {
                            CCLOG("cocos2d: TexturePVR. BGRA8888 not supported on this device");
                            return false;
                        }
                    default:
                        blockSize = 1;
                        widthBlocks = width;
                        heightBlocks = height;
                        break;
                }
                
                // Clamp to minimum number of blocks
                if (widthBlocks < 2)
                {
                    widthBlocks = 2;
                }
                if (heightBlocks < 2)
                {
                    heightBlocks = 2;
                }

                dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);
                unsigned int packetLength = (dataLength - dataOffset);
                packetLength = packetLength > dataSize ? dataSize : packetLength;
                
                //Make record to the mipmaps array and increment counter
                m_asMipmaps[m_uNumberOfMipmaps].address = bytes + dataOffset;
                m_asMipmaps[m_uNumberOfMipmaps].len = packetLength;
                m_uNumberOfMipmaps++;
                
                //Check that we didn't overflow
                CCAssert(m_uNumberOfMipmaps < CC_PVRMIPMAP_MAX, 
                         "TexturePVR: Maximum number of mipmaps reached. Increase the CC_PVRMIPMAP_MAX value");
                
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

    if (! success)
    {
        CCLOG("cocos2d: WARNING: Unsupported PVR Pixel Format: 0x%2x. Re-encode it with a OpenGL pixel format variant", formatFlags);
    }
    
    return success;
}

bool CCTexturePVR::unpackPVRv3Data(unsigned char* dataPointer, unsigned int dataLength)
{
    if (dataLength < sizeof(ccPVRv3TexHeader))
    {
		return false;
	}
	
	ccPVRv3TexHeader *header = (ccPVRv3TexHeader *)dataPointer;
	
	// validate version
	if (CC_SWAP_INT32_BIG_TO_HOST(header->version) != 0x50565203)
    {
		CCLOG("cocos2d: WARNING: pvr file version mismatch");
		return false;
	}
	
	// parse pixel format
	uint64_t pixelFormat = header->pixelFormat;
    
	
	bool infoValid = false;
    
    unsigned int pvr3TableElements = PVR3_MAX_TABLE_ELEMENTS;
    if (! CCConfiguration::sharedConfiguration()->supportsPVRTC())
    {
        pvr3TableElements = 9;
    }
	
	for(unsigned int i = 0; i < pvr3TableElements; i++)
    {
		if( v3_pixel_formathash[i].pixelFormat == pixelFormat )
        {
			m_pPixelFormatInfo = v3_pixel_formathash[i].pixelFormatInfo;
			m_bHasAlpha = m_pPixelFormatInfo->alpha;
			infoValid = true;
			break;
		}
	}
	
	// unsupported / bad pixel format
	if (! infoValid)
    {
		CCLOG("cocos2d: WARNING: unsupported pvr pixelformat: %lx", (unsigned long)pixelFormat );
		return false;
	}
    
    // flags
	uint32_t flags = CC_SWAP_INT32_LITTLE_TO_HOST(header->flags);
	
	// PVRv3 specifies premultiply alpha in a flag -- should always respect this in PVRv3 files
	m_bForcePremultipliedAlpha = true;
	if (flags & kPVR3TextureFlagPremultipliedAlpha)
    {
		m_bHasPremultipliedAlpha = true;
	}
    
	// sizing
	uint32_t width = CC_SWAP_INT32_LITTLE_TO_HOST(header->width);
	uint32_t height = CC_SWAP_INT32_LITTLE_TO_HOST(header->height);
	m_uWidth = width;
	m_uHeight = height;
	uint32_t dataOffset = 0, dataSize = 0;
	uint32_t blockSize = 0, widthBlocks = 0, heightBlocks = 0;
	uint8_t *bytes = NULL;
	
	dataOffset = (sizeof(ccPVRv3TexHeader) + header->metadataLength);
	bytes = dataPointer;
	
	m_uNumberOfMipmaps = header->numberOfMipmaps;
	CCAssert(m_uNumberOfMipmaps < CC_PVRMIPMAP_MAX, "TexturePVR: Maximum number of mimpaps reached. Increate the CC_PVRMIPMAP_MAX value");
    
	for (unsigned int i = 0; i < m_uNumberOfMipmaps; i++)
    {	
		switch (pixelFormat)
        {
			case kPVR3TexturePixelFormat_PVRTC_2BPP_RGB :
			case kPVR3TexturePixelFormat_PVRTC_2BPP_RGBA :
				blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
				widthBlocks = width / 8;
				heightBlocks = height / 4;
				break;
			case kPVR3TexturePixelFormat_PVRTC_4BPP_RGB :
			case kPVR3TexturePixelFormat_PVRTC_4BPP_RGBA :
				blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
				widthBlocks = width / 4;
				heightBlocks = height / 4;
				break;
			case kPVR3TexturePixelFormat_BGRA_8888:
				if( ! CCConfiguration::sharedConfiguration()->supportsBGRA8888())
                {
					CCLOG("cocos2d: TexturePVR. BGRA8888 not supported on this device");
					return false;
				}
			default:
				blockSize = 1;
				widthBlocks = width;
				heightBlocks = height;
				break;
		}
        
		// Clamp to minimum number of blocks
		if (widthBlocks < 2)
        {
			widthBlocks = 2;
        }
		if (heightBlocks < 2)
        {
			heightBlocks = 2;
        }
		
		dataSize = widthBlocks * heightBlocks * ((blockSize  * m_pPixelFormatInfo->bpp) / 8);
		unsigned int packetLength = ((unsigned int)dataLength-dataOffset);
		packetLength = packetLength > dataSize ? dataSize : packetLength;
		
		m_asMipmaps[i].address = bytes+dataOffset;
		m_asMipmaps[i].len = packetLength;
		
		dataOffset += packetLength;
		CCAssert(dataOffset <= dataLength, "CCTexurePVR: Invalid lenght");
		
		
		width = MAX(width >> 1, 1);
		height = MAX(height >> 1, 1);
	}
	
	return true;
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
            ccGLDeleteTexture(m_uName);
        }
        
        // From PVR sources: "PVR files are never row aligned."
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        
        glGenTextures(1, &m_uName);
        ccGLBindTexture2D(m_uName);
        
        // Default: Anti alias.
		if (m_uNumberOfMipmaps == 1)
        {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
		else
        {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        }
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    
    CHECK_GL_ERROR_DEBUG(); // clean possible GL error
    
	GLenum internalFormat = m_pPixelFormatInfo->internalFormat;
	GLenum format = m_pPixelFormatInfo->format;
	GLenum type = m_pPixelFormatInfo->type;
    bool compressed = m_pPixelFormatInfo->compressed;

    // Generate textures with mipmaps
    for (unsigned int i = 0; i < m_uNumberOfMipmaps; ++i)
    {
        if (compressed && ! CCConfiguration::sharedConfiguration()->supportsPVRTC()) 
        {
			CCLOG("cocos2d: WARNING: PVRTC images are not supported");
			return false;
		}
        
		unsigned char *data = m_asMipmaps[i].address;
		GLsizei datalen = m_asMipmaps[i].len;
        
		if (compressed)
        {
			glCompressedTexImage2D(GL_TEXTURE_2D, i, internalFormat, width, height, 0, datalen, data);
        }
		else
        {
			glTexImage2D(GL_TEXTURE_2D, i, internalFormat, width, height, 0, format, type, data);
        }
        
		if (i > 0 && (width != height || ccNextPOT(width) != width ))
        {
			CCLOG("cocos2d: TexturePVR. WARNING. Mipmap level %u is not squared. Texture won't render correctly. width=%u != height=%u", i, width, height);
        }
        
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			CCLOG("cocos2d: TexturePVR: Error uploading compressed texture level: %u . glError: 0x%04X", i, err);
			return false;
		}
        
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
        pvrdata = CCFileUtils::sharedFileUtils()->getFileData(path, "rb", (unsigned long *)(&pvrlen));
    }
    
    if (pvrlen < 0)
    {
        this->release();
        return false;
    }
    
    m_uNumberOfMipmaps = 0;

    m_uName = 0;
    m_uWidth = m_uHeight = 0;
    m_pPixelFormatInfo = NULL;
    m_bHasAlpha = false;
    m_bForcePremultipliedAlpha = false;
    m_bHasPremultipliedAlpha = false;

    m_bRetainName = false; // cocos2d integration

    if (! ((unpackPVRv2Data(pvrdata, pvrlen)  || unpackPVRv3Data(pvrdata, pvrlen)) && createGLTexture()) )
    {
        CC_SAFE_DELETE_ARRAY(pvrdata);
        this->release();
        return false;
    }

    CC_SAFE_DELETE_ARRAY(pvrdata);
    
    return true;
}

CCTexturePVR * CCTexturePVR::create(const char* path)
{
    CCTexturePVR * pTexture = new CCTexturePVR();
    if (pTexture)
    {
        if (pTexture->initWithContentsOfFile(path))
        {
            pTexture->autorelease();
        }
        else
        {
            delete pTexture;
            pTexture = NULL;
        }
    }

    return pTexture;
}

NS_CC_END

