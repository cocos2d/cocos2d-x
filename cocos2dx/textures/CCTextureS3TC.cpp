//
//  CCTextureS3TC.cpp
//  cocos2d_libs
//
//  Created by zhangrongjian on 13-7-25.
//
//

#include "CCTextureS3TC.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCFileUtils.h"
#include "CCConfiguration.h"
#include "s3tc/s3tc.h"
#include "shaders/ccGLStateCache.h"
#include "support/ccUtils.h"



NS_CC_BEGIN

typedef struct _DDCOLORKEY
{
    DWORD dwColorSpaceLowValue;
    DWORD dwColorSpaceHighValue;
    
} DDCOLORKEY;

typedef struct _DDSCAPS2
{
    DWORD dwCaps;
    DWORD dwCaps2;
    DWORD dwCaps3;
    DWORD dwCaps4;
} DDSCAPS2;

typedef struct DDS_PIXELFORMAT
{
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwFourCC;
    DWORD dwRGBBitCount;
    DWORD dwRBitMask;
    DWORD dwGBitMask;
    DWORD dwBBitMask;
    DWORD dwABitMask;
}DDPIXELFORMAT;


typedef struct _DDSURFACEDESC2
{
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwHeight;
    DWORD dwWidth;
    
    union
    {
        DWORD lPitch;
        DWORD dwLinearSize;
    } DUMMYUNIONNAMEN1;
    
    union
    {
        DWORD dwBackBufferCount;
        DWORD dwDepth;
    } DUMMYUNIONNAMEN5;
    
    union
    {
        DWORD dwMipMapCount;
        DWORD dwRefreshRate;
        DWORD dwSrcVBHandle;
    } DUMMYUNIONNAMEN2;
    
    DWORD dwAlphaBitDepth;
    DWORD dwReserved;
    DWORD lpSurface;
    
    union
    {
        DDCOLORKEY ddckCKDestOverlay;
        DWORD dwEmptyFaceColor;
    } DUMMYUNIONNAMEN3;
    
    DDCOLORKEY ddckCKDestBlt;
    DDCOLORKEY ddckCKSrcOverlay;
    DDCOLORKEY ddckCKSrcBlt;
    
    union
    {
        DDPIXELFORMAT ddpfPixelFormat;
        DWORD dwFVF;
    } DUMMYUNIONNAMEN4;
    
    DDSCAPS2 ddsCaps;
    DWORD dwTextureStage;
    
} DDSURFACEDESC2, *LPDDSURFACEDESC2;

#pragma pack(push,1)

typedef struct ccS3TCTexHeader
{
    char fileCode[4];
    DDSURFACEDESC2 ddsd;
    
}ccS3TCTexHeader;

#pragma pack(pop)


TextureS3TC::TextureS3TC()
: _name(0)
, _width(0)
, _height(0)
{}

TextureS3TC::~TextureS3TC()
{
}

bool TextureS3TC::initWithFile(const char *file)
{
    return loadTexture(FileUtils::getInstance()->fullPathForFilename(file).c_str());
}
unsigned int TextureS3TC::getName() const
{
    return _name;
}
unsigned int TextureS3TC::getWidth() const
{
    return _width;
}
unsigned int TextureS3TC::getHeight() const
{
    return _height;
}

gliGenericImage* TextureS3TC::ReadDDSFile(const char *filename, int * bufsize, int * numMipmaps)
{
    gliGenericImage *genericImage;     
    
    unsigned char* s3tcFileData = nullptr;
    unsigned long s3tcFileSize = 0;
    ccS3TCTexHeader *header = NULL;
    
    s3tcFileData = FileUtils::getInstance()->getFileData(filename, "rb", &s3tcFileSize); 
    header = (ccS3TCTexHeader *)s3tcFileData;

    if (strncmp(header->fileCode, "DDS", 3)!= 0)    
    {
        CCLOG("cocos2d: the file is not a dds file!");
        return nullptr;
    }
    
    genericImage = (gliGenericImage*) malloc(sizeof(gliGenericImage));
    memset(genericImage,0,sizeof(gliGenericImage));  
    
    //*bufsize = header->ddsd.DUMMYUNIONNAMEN2.dwMipMapCount > 1 ? header->ddsd.DUMMYUNIONNAMEN1.dwLinearSize * 2
    //: header->ddsd.DUMMYUNIONNAMEN1.dwLinearSize;
    
    genericImage->pixels = (unsigned char*)malloc(s3tcFileSize-sizeof(ccS3TCTexHeader));  
    memcpy(genericImage->pixels, (unsigned char*)s3tcFileData+sizeof(ccS3TCTexHeader), s3tcFileSize-sizeof(ccS3TCTexHeader));

    genericImage->width = header->ddsd.dwWidth;
    _width = header->ddsd.dwWidth;
    genericImage->height = header->ddsd.dwHeight;
    _height = header->ddsd.dwHeight;
    
    const DWORD FOURCC_DXT1 = MakeFourCC('D', 'X', 'T', '1');
    const DWORD FOURCC_DXT3 = MakeFourCC('D', 'X', 'T', '3');
    const DWORD FOURCC_DXT5 = MakeFourCC('D', 'X', 'T', '5');
    
    genericImage->components = (header->ddsd.DUMMYUNIONNAMEN4.ddpfPixelFormat.dwFourCC == FOURCC_DXT1) ? 3 : 4;
    
    *numMipmaps = header->ddsd.DUMMYUNIONNAMEN2.dwMipMapCount;  
    
    if (FOURCC_DXT1==header->ddsd.DUMMYUNIONNAMEN4.ddpfPixelFormat.dwFourCC)  
    {
        genericImage->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    }
    else if(FOURCC_DXT3==header->ddsd.DUMMYUNIONNAMEN4.ddpfPixelFormat.dwFourCC)
    {
        genericImage->format = GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE;
    }
    else if(FOURCC_DXT5==header->ddsd.DUMMYUNIONNAMEN4.ddpfPixelFormat.dwFourCC)
    {
        genericImage->format = GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE;
    }
    else
    {
        free(genericImage->pixels);
        free(genericImage);
        return NULL;
    }
    CC_SAFE_DELETE_ARRAY(s3tcFileData);
    
    /* return data */
    return genericImage;
}

const DWORD TextureS3TC::MakeFourCC(char ch0, char ch1, char ch2, char ch3)
{
    const DWORD fourCC=((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ));
    return fourCC;
}

bool TextureS3TC::loadTexture(const char*file)
{
    int ddsbufsize = 0;
    int numMipmaps = 0;
    
    /* load the .dds file */
    gliGenericImage *ddsimage = ReadDDSFile(file,&ddsbufsize,&numMipmaps);
    
    int height = ddsimage->height;
    int width = ddsimage->width;
    int offset =0;
    int blockSize = (ddsimage->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    
    if (numMipmaps > 0)
    {
        if (_name != 0)
        {
            ccGLDeleteTexture(_name);
        }
        
        // From PVR sources: "PVR files are never row aligned."
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        
        glGenTextures(1, &_name);
        glBindTexture(GL_TEXTURE_2D, _name);
        
        // Default: Anti alias.
		if (numMipmaps == 1)
        {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
		else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);  //mipmap limited support
        }
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    
    /* load the mipmaps */
    for (unsigned int i = 0; i < numMipmaps && (width || height); ++i)  //   mipmap 无法全部读取问题
    {
        if (width == 0) width = 1;
        
        if (height == 0) height = 1;
        
        int size = ((width+3)/4)*((height+3)/4)*blockSize;

        if (Configuration::getInstance()->supportsS3TC())
        {
            CCLOG("this is s3tc H decode");
            
            glCompressedTexImage2D(GL_TEXTURE_2D, i, ddsimage->format, width, height, 0, size, ddsimage->pixels + offset);
        }
        else
        {
            //if it is not gles or device do not support S3TC, decode texture by software
            int bitPerPixel = 4;
            unsigned int stride = width * bitPerPixel;
            //
            std::vector<unsigned char> decodeImageData(stride * height);
            if(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT==ddsimage->format)
            {
                ff_decode_dxt1(ddsimage->pixels+offset, &decodeImageData[0], width, height, stride);
            }
            else if(GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE==ddsimage->format)
            {
                ff_decode_dxt3(ddsimage->pixels+offset, &decodeImageData[0], width, height, stride);
            }
            else if(GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE==ddsimage->format)
            {
                ff_decode_dxt5(ddsimage->pixels+offset, &decodeImageData[0], width, height, stride);
            }
            
            glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &decodeImageData[0]);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        if (i > 0 && (width != height || ccNextPOT(width) != width ))
        {
			CCLOG("cocos2d: TexturePVR. WARNING. Mipmap level %u is not squared. Texture won't render correctly. width=%u != height=%u", i, width, height);
        }
        
        GLenum err;
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			CCLOG("cocos2d: TexturePVR: Error uploading compressed texture level: %u . glError: 0x%04X", i, err);
			return false;
		}
        
		offset += size;
        width >>= 1;
        height >>= 1;
    }
    
    free(ddsimage->pixels);
    free(ddsimage);
    ddsimage=NULL;
    
    return true;
}
NS_CC_END
