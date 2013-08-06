//
//  s3tc.cpp
//  cocos2d_libs
//
//  Created by zhangrongjian on 13-7-25.
//
//


 /*
  * S3 Texture Compression (S3TC) decoding functions
  * Copyright (c) 2007 by Ivo van Poorten
  *
  * see also: http://wiki.multimedia.cx/index.php?title=S3TC
  *
  * This file is part of FFmpeg.
  *
  * FFmpeg is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * FFmpeg is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with FFmpeg; if not, write to the Free Software
  * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
  */

// #include "libavcodec/bytestream.h"
// #include "avcodec.h"
#include "s3tc.h"
typedef enum
{
    dxt1 = 1,
    dxt3 = 3,
    dxt5 = 5,
}ccS3TCCompressionFlag;

void dxt1_decode_pixels(uint8_t **block_data,
                          uint32_t *d,
                          unsigned int qstride,
                          unsigned int flag,
                          uint64_t alpha,
                          ccS3TCCompressionFlag comFlag)
{
    unsigned int x = 0, y = 0, c0 = 0 , c1 = 0, a = (!flag * 255u) << 24;
    unsigned int rb0 = 0, rb1 = 0, rb2 = 0, rb3 = 0, g0 = 0, g1 = 0, g2 = 0, g3 = 0;

    uint32_t colors[4], pixels = 0;
    
    memcpy((void *)&c0, *block_data, 2);
    (*block_data) += 2;
    
    memcpy((void *)&c1, *block_data, 2);
    (*block_data) += 2;
    
    // the channel is r5g6b5
    
    rb0  = (c0<<19 | c0>>8) & 0xf800f8;
    rb1  = (c1<<19 | c1>>8) & 0xf800f8;
    
    g0   =        (c0 <<5) & 0x00fc00;
    g1   =        (c1 <<5) & 0x00fc00;
    g0  +=        (g0 >>6) & 0x000300;
    g1  +=        (g1 >>6) & 0x000300;
    
    colors[0] = rb0 + g0 + a;
    colors[1] = rb1 + g1 + a;
    
    if (c0 > c1 || flag)
    {
        rb2 = (((2*rb0+rb1) * 21) >> 6) & 0xff00ff;
        rb3 = (((2*rb1+rb0) * 21) >> 6) & 0xff00ff;
        g2  = (((2*g0 +g1 ) * 21) >> 6) & 0x00ff00;
        g3  = (((2*g1 +g0 ) * 21) >> 6) & 0x00ff00;
        colors[3] = rb3 + g3 + a;
     }
    else
    {
        rb2 = ((rb0+rb1) >> 1) & 0xff00ff;
        g2  = ((g0 +g1 ) >> 1) & 0x00ff00;
        colors[3] = 0;
    }
   
   colors[2] = rb2 + g2 + a;
   
   memcpy((void*)&pixels, *block_data, 4);  //read 4 bytes
    (*block_data) += 4;
  
   if(dxt5 == comFlag) //dxt5 use interpolate alpha
   {
       unsigned int alphaArray[8];
       
        // 8-Alpha block: derive the other six alphas.
        // Bit code 000 = alpha0, 001 = alpha1, other are interpolated.
       
       alphaArray[0] = (alpha )& 0xff ;
       alphaArray[1] = (alpha >> 8)& 0xff ;
       
       //
       if(alphaArray[0] >= alphaArray[1])  
       {
           alphaArray[2] = (alphaArray[0]*6 + alphaArray[1]*1)/7;
           alphaArray[3] = (alphaArray[0]*5 + alphaArray[1]*2)/7;
           alphaArray[4] = (alphaArray[0]*4 + alphaArray[1]*3)/7;
           alphaArray[5] = (alphaArray[0]*3 + alphaArray[1]*4)/7;
           alphaArray[6] = (alphaArray[0]*2 + alphaArray[1]*5)/7;
           alphaArray[7] = (alphaArray[0]*1 + alphaArray[1]*6)/7;
       }
       else if(alphaArray[0] < alphaArray[1])
       {
           alphaArray[2] = (alphaArray[0]*4 + alphaArray[1]*1)/5;
           alphaArray[3] = (alphaArray[0]*3 + alphaArray[1]*2)/5;
           alphaArray[4] = (alphaArray[0]*2 + alphaArray[1]*3)/5;
           alphaArray[5] = (alphaArray[0]*1 + alphaArray[1]*4)/5;
           alphaArray[6] = 0;
           alphaArray[7] = 255;
       }
       
       // read the flowing 48bit indices (16*3)
       alpha >>= 16;
       
       for (y=0; y<4; y++)
       {
           for (x=0; x<4; x++)
           {
               d[x] = (alphaArray[alpha & 5] <<24) + colors[pixels & 3];
               pixels >>= 2;
               alpha >>= 3;
           }
           d += qstride;
       }
   } //if (dxt5 == comFlag)
   else   //dxt1 dxt3 use explicit alpha
   {
       for (y=0; y<4; y++)
       {
           for (x=0; x<4; x++)
           {
               a        = (alpha & 0x0f) << 28;
               a       += a >> 4;
               d[x]     = a + colors[pixels & 3];
               pixels >>= 2;
               alpha  >>= 4;
           }
           d += qstride;
       }
   }
   
}

 void ff_decode_dxt1(uint8_t *in_data,
                     uint8_t *dst,
                     const unsigned int w,
                     const unsigned int h,
                     const unsigned int stride)
{
   unsigned int bx, by, qstride = stride/4;
   uint32_t *d = (uint32_t *) dst;
   
   for (by=0; by < h/4; by++, d += stride-w)         //stride = 4*width
       for (bx = 0; bx < w / 4; bx++, d += 4)        //skip 4 pixels
                dxt1_decode_pixels(&in_data, d, qstride, 0, 0LL, dxt1);
}

 void ff_decode_dxt3(uint8_t *in_data,
                     uint8_t *dst,
                     const unsigned int w,
                     const unsigned int h,
                     const unsigned int stride)
{
    unsigned int bx, by, qstride = stride/4;
    uint32_t *d = (uint32_t *) dst;
 
    for (by=0; by < h/4; by++, d += stride-w)
                for (bx = 0; bx < w / 4; bx++, d += 4)
                {
                    uint64_t tempAlpha=0;
                    
                    memcpy((void *)&tempAlpha, in_data, 8);
                    in_data += 8;
                    
                    dxt1_decode_pixels(&in_data, d, qstride, 1, tempAlpha, dxt3);
                }
}

void ff_decode_dxt5(uint8_t *in_data,
                    uint8_t *dst,
                    const unsigned int w,
                    const unsigned int h,
                    const unsigned int stride)
{
    unsigned int bx, by, qstride = stride/4;
    uint32_t *d = (uint32_t *) dst;
    
    for (by=0; by < h/4; by++,d += stride-w)
    {
        for(bx = 0; bx < w / 4; bx++, d += 4)
        {
            uint64_t tempAlpha = 0;
            
            memcpy((void *)&tempAlpha, in_data, 8);
            in_data += 8;
            
            dxt1_decode_pixels(&in_data, d, qstride, 1, tempAlpha, dxt5);
            
        }
    }
}
