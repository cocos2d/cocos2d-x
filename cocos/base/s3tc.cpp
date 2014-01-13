/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies
 
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

#include "s3tc.h"

//Decode S3TC encode block to 4x4 RGB32 pixels
static void s3tc_decode_block(uint8_t **blockData,
                       uint32_t *decodeBlockData,
                       unsigned int stride,
                       bool oneBitAlphaFlag,
                       uint64_t alpha,
                       S3TCDecodeFlag decodeFlag)
{
    unsigned int colorValue0 = 0 , colorValue1 = 0, initAlpha = (!oneBitAlphaFlag * 255u) << 24;
    unsigned int rb0 = 0, rb1 = 0, rb2 = 0, rb3 = 0, g0 = 0, g1 = 0, g2 = 0, g3 = 0;
    
    uint32_t colors[4], pixelsIndex = 0;
    
    /* load the two color values*/
    memcpy((void *)&colorValue0, *blockData, 2);
    (*blockData) += 2;
    
    memcpy((void *)&colorValue1, *blockData, 2);
    (*blockData) += 2;
    
    /* the channel is r5g6b5 , 16 bits */
    rb0  = (colorValue0 << 19 | colorValue0 >> 8) & 0xf800f8;
    rb1  = (colorValue1 << 19 | colorValue1 >> 8) & 0xf800f8;
    g0   = (colorValue0 << 5) & 0x00fc00;
    g1   = (colorValue1 << 5) & 0x00fc00;
    g0  += (g0 >> 6) & 0x000300;
    g1  += (g1 >> 6) & 0x000300;
    
    colors[0] = rb0 + g0 + initAlpha;
    colors[1] = rb1 + g1 + initAlpha;
    
    /* interpolate the other two color values */
    if (colorValue0 > colorValue1 || oneBitAlphaFlag)
    {
        rb2 = (((2*rb0 + rb1) * 21) >> 6) & 0xff00ff;
        rb3 = (((2*rb1 + rb0) * 21) >> 6) & 0xff00ff;
        g2  = (((2*g0 + g1 ) * 21) >> 6) & 0x00ff00;
        g3  = (((2*g1 + g0 ) * 21) >> 6) & 0x00ff00;
        colors[3] = rb3 + g3 + initAlpha;
    }
    else
    {
        rb2 = ((rb0+rb1) >> 1) & 0xff00ff;
        g2  = ((g0 +g1 ) >> 1) & 0x00ff00;
        colors[3] = 0 ;
    }
    colors[2] = rb2 + g2 + initAlpha;
    
    /*read the pixelsIndex , 2bits per pixel, 4 bytes */
    memcpy((void*)&pixelsIndex, *blockData, 4);
    (*blockData) += 4;
    
    if (S3TCDecodeFlag::DXT5 == decodeFlag)
    {
        //dxt5 use interpolate alpha
        // 8-Alpha block: derive the other six alphas.
        // Bit code 000 = alpha0, 001 = alpha1, other are interpolated.
        
        unsigned int alphaArray[8];
        
        alphaArray[0] = (alpha ) & 0xff ;
        alphaArray[1] = (alpha >> 8) & 0xff ;
        
        if (alphaArray[0] >= alphaArray[1])
        {
            alphaArray[2] = (alphaArray[0]*6 + alphaArray[1]*1) / 7;
            alphaArray[3] = (alphaArray[0]*5 + alphaArray[1]*2) / 7;
            alphaArray[4] = (alphaArray[0]*4 + alphaArray[1]*3) / 7;
            alphaArray[5] = (alphaArray[0]*3 + alphaArray[1]*4) / 7;
            alphaArray[6] = (alphaArray[0]*2 + alphaArray[1]*5) / 7;
            alphaArray[7] = (alphaArray[0]*1 + alphaArray[1]*6) / 7;
        }
        else if (alphaArray[0] < alphaArray[1])
        {
            alphaArray[2] = (alphaArray[0]*4 + alphaArray[1]*1) / 5;
            alphaArray[3] = (alphaArray[0]*3 + alphaArray[1]*2) / 5;
            alphaArray[4] = (alphaArray[0]*2 + alphaArray[1]*3) / 5;
            alphaArray[5] = (alphaArray[0]*1 + alphaArray[1]*4) / 5;
            alphaArray[6] = 0;
            alphaArray[7] = 255;
        }
        
        // read the flowing 48bit indices (16*3)
        alpha >>= 16;
        
        for (int y = 0; y < 4; ++y)
        {
            for (int x = 0; x < 4; ++x)
            {
                decodeBlockData[x] = (alphaArray[alpha & 5] << 24) + colors[pixelsIndex & 3];
                pixelsIndex >>= 2;
                alpha >>= 3;
            }
            decodeBlockData += stride;
        }
    } //if (dxt5 == comFlag)
    else
    { //dxt1 dxt3 use explicit alpha
        for (int y = 0; y < 4; ++y)
        {
            for (int x = 0; x < 4; ++x)
            {
                initAlpha   = (static_cast<int>(alpha) & 0x0f) << 28;
                initAlpha   += initAlpha >> 4;
                decodeBlockData[x] = initAlpha + colors[pixelsIndex & 3];
                pixelsIndex >>= 2;
                alpha       >>= 4;
            }
            decodeBlockData += stride;
        }
    }
}

//Decode S3TC encode data to RGB32
void s3tc_decode(uint8_t *encodeData,             //in_data
                 uint8_t *decodeData,             //out_data
                 const int pixelsWidth,
                 const int pixelsHeight,
                 S3TCDecodeFlag decodeFlag)
{
    uint32_t *decodeBlockData = (uint32_t *)decodeData;
    for (int block_y = 0; block_y < pixelsHeight / 4; ++block_y, decodeBlockData += 3 * pixelsWidth)   //stride = 3*width
    {
        for(int block_x = 0; block_x < pixelsWidth / 4; ++block_x, decodeBlockData += 4)            //skip 4 pixels
        {
            uint64_t blockAlpha = 0;
            
            switch (decodeFlag)
            {
                case S3TCDecodeFlag::DXT1:
                {
                    s3tc_decode_block(&encodeData, decodeBlockData, pixelsWidth, 0, 0LL, S3TCDecodeFlag::DXT1);
                }
                    break;
                case S3TCDecodeFlag::DXT3:
                {
                    memcpy((void *)&blockAlpha, encodeData, 8);
                    encodeData += 8;
                    s3tc_decode_block(&encodeData, decodeBlockData, pixelsWidth, 1, blockAlpha, S3TCDecodeFlag::DXT3);
                }
                    break;
                case S3TCDecodeFlag::DXT5:
                {
                    memcpy((void *)&blockAlpha, encodeData, 8);
                    encodeData += 8;
                    s3tc_decode_block(&encodeData, decodeBlockData, pixelsWidth, 1, blockAlpha, S3TCDecodeFlag::DXT5);
                }
                    break;
                default:
                    break;
            }//switch
        }//for block_x
    }//for block_y
}


