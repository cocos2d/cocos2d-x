/*
 * Gbk_Unicode.h
 *
 *  Created on: 2011-9-12
 *      Author: dumganhar
 */

#ifndef GBK_UNICODE_H_
#define GBK_UNICODE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * param: 
 *   pGbkOut[out]:用于存放输出Gbk的缓冲
 *   iGbkBufSize[in]:用于存放输出Gbk的缓冲的大小，单位为字节, 若pGbkOut为数组, 可使用sizeof()计算数组长度
 *   pUnicodeIn[in]:需要转换的unicode缓冲
 * return: 0:失败, 1: 成功
*/
int MyUnicodeToGBK(char* pGBKOut, int iGbkBufSize, const unsigned short* pUnicodeIn);

/*
 * param: 
 *   pUnicodeOut[out]:用于存放输出unicode的缓冲
 *   iUniBufSize[in]:用于存放输出unicode的缓冲的大小，单位为字节, 若pUnicodeOut为数组, 可使用sizeof()计算数组长度
 *   pGBKIn[in]:需要转换的gbk缓冲
 * return: 0:失败, 1: 成功
*/
int MyGBKToUnicode(unsigned short* pUnicodeOut, int iUniBufSize, const char* pGBKIn);
// ppszOutUtf8为空指针的地址传入，函数内部对其赋值，_M结束的函数需要用free释放
int MyGBKToUTF8_M(char** ppszOutUtf8, char* pszGbk);
// ppszOutGbk为空指针的地址传入，函数内部对其赋值，_M结束的函数需要用free释放
int MyUTF8ToGBK_M(char** ppszOutGbk, char* pszUtf8);

#ifdef __cplusplus
}
#endif


#endif /* GBK_UNICODE_H_ */
