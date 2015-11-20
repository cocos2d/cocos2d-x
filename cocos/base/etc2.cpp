/**
    @file   etc2.cpp
    @note   etc2 cpu decode
*/

#include "platform/CCGL.h"
#include "etc2.h"
#include "etc2types.h"

extern ETC2_error_code
_unpackETC(const GLubyte* __restrict srcETC, const GLenum srcFormat,
            etc2_uint32_t activeWidth, etc2_uint32_t activeHeight,
            GLubyte** __restrict dstImage,
            GLenum* __restrict format, GLenum* __restrict internalFormat, GLenum* __restrict type,
            GLint R16Formats, GLboolean supportsSRGB);

int etc2_decode_image(const unsigned char* pIn, const GLenum srcFormat, unsigned int width, unsigned int height, unsigned char** pOut)
{
    GLenum format;
    GLenum internalFormat;
    GLenum type;
    ETC2_error_code ret = _unpackETC(
            pIn, srcFormat,
            width, height,
            pOut,
            &format, &internalFormat, &type,
            ETC2_NO_R16_FORMATS, false);
    return (ret == ETC2_SUCCESS) ? 0 : -1;
}

