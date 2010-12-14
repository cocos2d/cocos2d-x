/*
 * Gbk_Unicode.h
 *
 *  Created on: 2010-7-7
 *      Author: Administrator
 */

#ifndef GBK_UNICODE_H_
#define GBK_UNICODE_H_

int InitGbkUnicodeTable(char* szTablePath);
void ReleaseGbkUnicodeTable(void);
void MyUnicodeToGBK(char* pGBKOut, wchar_t* pUnicodeIn);
void MyGBKToUnicode(wchar_t* pUnicodeOut, char* pGBKIn);

#endif /* GBK_UNICODE_H_ */
