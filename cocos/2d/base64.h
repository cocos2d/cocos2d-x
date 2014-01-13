/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __SUPPORT_BASE64_H__
#define __SUPPORT_BASE64_H__

#ifdef __cplusplus
extern "C" {
#endif    
    
namespace cocos2d {

/** @file
 base64 helper functions
 */

/** 
 * Decodes a 64base encoded memory. The decoded memory is
 * expected to be freed by the caller by calling `free()`
 *
 * @returns the length of the out buffer
 *
 @since v0.8.1
 */
int base64Decode(const unsigned char *in, unsigned int inLength, unsigned char **out);
    
/**
 * Encodes bytes into a 64base encoded memory with terminating '\0' character. 
 * The encoded memory is expected to be freed by the caller by calling `free()`
 *
 * @returns the length of the out buffer
 *
 @since v2.1.4
 */
int base64Encode(const unsigned char *in, unsigned int inLength, char **out);

}//namespace   cocos2d 

#ifdef __cplusplus
}
#endif    

#endif // __SUPPORT_BASE64_H__
