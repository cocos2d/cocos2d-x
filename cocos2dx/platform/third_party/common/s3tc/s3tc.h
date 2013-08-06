//
//  s3tc.h
//  cocos2d_libs
//
//  Created by zhangrongjian on 13-7-25.
//
//

#ifndef __cocos2d_libs__s3tc__
#define __cocos2d_libs__s3tc__

#include "CCStdC.h"

void dxt1_decode_pixels (uint8_t **in_data, uint32_t *d, unsigned int qstride, unsigned int flag, uint64_t alpha);

//Decode DXT1 encoded data to RGB32.
void ff_decode_dxt1 (uint8_t *in_data,uint8_t *dst, const unsigned int w, const unsigned int h, const unsigned int stride);

//Decode DXT3 encoded data to RGB32.
void ff_decode_dxt3 (uint8_t *in_data,uint8_t *dst, const unsigned int w, const unsigned int h, const unsigned int stride);

void ff_decode_dxt5(uint8_t *in_data,uint8_t *dst, const unsigned int w, const unsigned int h, const unsigned int stride);



#endif /* defined(__cocos2d_libs__s3tc__) */
