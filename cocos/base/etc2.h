/**
    @file   etc2.h
    @note   etc2 cpu decode
*/

#ifndef __etc2_h__
#define __etc2_h__

#ifdef __cplusplus
extern "C" {
#endif

int etc2_decode_image(const unsigned char* pIn, const GLenum srcFormat, unsigned int width, unsigned int height, unsigned char** pOut);

#ifdef __cplusplus
}
#endif

#endif
