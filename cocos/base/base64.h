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
 base64 助手(helper)函数
 */

/** 
 * 解码base64编码的内存信息, 解码后的内存信息(指in)应该调用`free()`函数释放.
 * 注:原文为decoded memory, 但是释放的应该是已经处理过的内存区域, 实现中仅会在
 * 解码失败时释放out内存区域.
 *
 * @returns 输出缓冲区的长度
 *
 @since v0.8.1
 */
int base64Decode(const unsigned char *in, unsigned int inLength, unsigned char **out);
    
/**
 * 把给定字符编码为以'\0'结尾的base64编码的内存信息.
 * 编码后的内存信息(指in)应该调用`free()`函数释放.
 *
 * @returns 输出缓冲区的长度
 *
 @since v2.1.4
 */
int base64Encode(const unsigned char *in, unsigned int inLength, char **out);

}//namespace   cocos2d 

#ifdef __cplusplus
}
#endif    

#endif // __SUPPORT_BASE64_H__
