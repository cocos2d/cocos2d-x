//
//  CCTextureS3TC.h
//  cocos2d_libs
//
//  Created by zhangrongjian on 13-7-25.
//
//

#ifndef __cocos2d_libs__CCTextureS3TC__
#define __cocos2d_libs__CCTextureS3TC__

#include <iostream>
#include "cocoa/CCObject.h"
#include "platform/CCPlatformMacros.h"
#include "CCGL.h"

/* GL_EXT_texture_compression_dxt1 */
#ifndef GL_EXT_texture_compression_dxt1
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                         0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                        0x83F1
#endif

/* GL_ANGLE_texture_compression_dxt3 */
#ifndef GL_ANGLE_texture_compression_dxt3
#define GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE                      0x83F2
#endif

/* GL_ANGLE_texture_compression_dxt5 */
#ifndef GL_ANGLE_texture_compression_dxt5
#define GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE                      0x83F3
#endif

NS_CC_BEGIN

//GL Image Information
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;
typedef void* LPVOID;
typedef char BYTE;

typedef struct
{
    GLsizei width;
    GLsizei height;
    GLint components;
    GLenum type;
    GLenum format;
    GLenum internalFormat;
    
    GLsizei cmapEntries;
    GLenum cmapFormat;
    GLubyte *cmap;
    GLubyte *pixels;
    
} gliGenericImage;



class CC_DLL TextureS3TC : public Object
{
public:
    TextureS3TC();
    virtual ~TextureS3TC();
    
    bool initWithFile(const char* file);
    
    unsigned int getName() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
   
private:
    const DWORD MakeFourCC(char ch0,char ch1,char ch2,char ch3);
    gliGenericImage* ReadDDSFile(const char *filename, int * bufsize, int * numMipmaps);
    bool loadTexture(const char*file);
    
private:
    GLuint _name;
    unsigned int _width;
    unsigned int _height;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCTextureS3TC__) */
