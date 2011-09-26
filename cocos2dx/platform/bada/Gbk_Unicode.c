/*
 * Gbk_Unicode.h
 *
 *  Created on: 2011-9-12
 *      Author: dumganhar
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gbk_Unicode.h"
#include "gbk_table.h"
#include "unicode_table.h"

#define LOGI //printf

#undef SAFE_FREE
#define SAFE_FREE(p) do \
	{\
	if ((p) != NULL) \
		{ \
			free((p)); \
			(p) = NULL; \
		} \
	}while(0)

#define UNICODE1_BEGIN  (0x3000)
#define UNICODE1_END    (0x9FA5)
#define UNICODE1_TOTAL  (UNICODE1_END-UNICODE1_BEGIN+1)

#define UNICODE2_BEGIN  (0xFF00)
#define UNICODE2_END    (0xFFEF)
#define UNICODE2_TOTAL  (UNICODE2_END-UNICODE2_BEGIN+1)

#define UNICODE3_BEGIN  (0x2000)
#define UNICODE3_END    (0x206F)
#define UNICODE3_TOTAL  (UNICODE3_END-UNICODE3_BEGIN+1)

#define FONT_ROW_BEGIN 129
#define FONT_ROW_END   254
#define FONT_COL_BEGIN 64
#define FONT_COL_END   254
#define FONT_TOTAL     (((FONT_ROW_END)-(FONT_ROW_BEGIN)+1)*((FONT_COL_END)-(FONT_COL_BEGIN)+1))

static int myWcslen(const unsigned short* str)
{
	int i=0;
	while(*str++) i++;
	return i;
}

#define GET_GBK_WORD(table, s, e) \
	if (pUnicodeIn[i] >= s && pUnicodeIn[i] <= e) \
	{ \
		iIndex = pUnicodeIn[i]-s; \
		oneGbk = table[iIndex]; \
		pGbk = (unsigned char*)&oneGbk; \
		pGBKOut[j++] = *(pGbk+1); \
		pGBKOut[j++] = *pGbk; \
		continue; \
	} 


int MyUnicodeToGBK(char* pGBKOut, int iGbkBufSize, const unsigned short* pUnicodeIn)
{
	unsigned char* pOneUnicode = NULL;
	int len = 0;
	int iIndex = 0;
	int i = 0, j = 0;

	if (pUnicodeIn == NULL || pGBKOut == NULL || iGbkBufSize <= 2)
	{
		LOGI("pUnicodeIn == NULL || pGBKOut == NULL || iGbkBufSize <= 2");
		return 0;
	}

	memset(pGBKOut, 0, iGbkBufSize);

	len = myWcslen(pUnicodeIn);
	for (i = 0, j = 0; i < len; i++)
	{
		unsigned char* pGbk = NULL;
		unsigned short oneGbk = 0;
		pOneUnicode = (unsigned char*)&pUnicodeIn[i];
		if (j >= iGbkBufSize-1)
		{
			break;
		}

		if (pOneUnicode[1] == 0)
		{// 半角字母符号
			if (pOneUnicode[0] == 0xb7)
			{
				pGBKOut[j++] = 0xa1;
				pGBKOut[j++] = 0xa4;
			}
			else if (pOneUnicode[0] == 0xB0)
			{
				pGBKOut[j++] = 0xA1;
				pGBKOut[j++] = 0xE3;
			}
			else
			{
				pGBKOut[j++] = pOneUnicode[0];
			}		
		}
		else
		{
			GET_GBK_WORD(g_gbk_table1_array, UNICODE1_BEGIN, UNICODE1_END);// 汉字
			GET_GBK_WORD(g_gbk_table2_array, UNICODE2_BEGIN, UNICODE2_END);// 全角字母符号
			GET_GBK_WORD(g_gbk_table3_array, UNICODE3_BEGIN, UNICODE3_END);// 常用标点符号
		}
	}

	j = j > iGbkBufSize-1 ? iGbkBufSize-1 : j;

	pGBKOut[j] = '\0';
	return 1;
}

int MyGBKToUnicode(unsigned short* pUnicodeOut, int iUniBufSize, const char* pGBKIn)
{
	int i = 0;
	int j = 0;
	int len = 0;
	int iIndex = 0;
	unsigned char* pUnicode = NULL;
	unsigned short oneGbkHanzi = 0;
	unsigned char* pOneGbkHanzi = (unsigned char*)&oneGbkHanzi;
	const unsigned char* pGBKInU = (const unsigned char*)pGBKIn;

	if (pUnicodeOut == NULL || pGBKIn == NULL || iUniBufSize <= 3)
	{
		LOGI("pUnicodeOut == NULL || pGBKIn == NULL || iUniBufSize <= 3");
		return 0;
	}

	memset(pUnicodeOut, 0, iUniBufSize);

	len = strlen(pGBKIn);
	for (i = 0; i < len; i++)
	{
		if (j >= iUniBufSize/2-1)
		{
			break;
		}

		pUnicode = (unsigned char*)&pUnicodeOut[j];
		if (pGBKInU[i] >= 0x00 && pGBKInU[i] <= 0x80)
		{// 半角字母符号
			*(pUnicode++) = pGBKInU[i];
			*pUnicode = 0x00;
			++j;
		}
		else if ((pGBKInU[i] >= 0x81 && pGBKInU[i] <= 0xFE)
			&&(pGBKInU[i+1] >= 0x40 && pGBKInU[i+1] <= 0xFE)
			&& (pGBKInU[i+1] != 0x7F)
			)
		{// 中文
			pOneGbkHanzi[1] = pGBKInU[i];
			pOneGbkHanzi[0] = pGBKInU[i+1];
			iIndex = (pOneGbkHanzi[1]-0x81)*191+(pOneGbkHanzi[0]-0x40);
			pUnicodeOut[j] = g_uni_table_array[iIndex];
			++i;
			++j;
		}
	}
//	LOGI("unicode len = %d", j);

	j = j > iUniBufSize/2-1 ? iUniBufSize/2-1 : j;

	pUnicodeOut[j] = L'\0';
	return 1;
}

static int GetUtf8Len(unsigned short* pUniStr)
{
	int wideLen = 0;
	int len = 0;
	int i = 0;

	if (pUniStr == NULL || (wideLen = myWcslen(pUniStr)) <= 0)
		return 0;

	for (i = 0; i < wideLen; i++)
	{
		unsigned short c = pUniStr[i];
		if (c < 0x80)
		{
			len += 1;
		}
		else if (c < 0x800)
		{
			len += 2;
		}
		else if (c < 0x10000)
		{
			len += 3;
		}
		else if (c < 0x200000)
		{
			len += 4;
		}
		else if (c < 0x4000000)
		{
			len += 5;
		}
		else
		{
			len += 6;
		}
	}
	return len;
}

static int unichar_to_utf8 (unsigned short c, char* outbuf)
{
	/* If this gets modified, also update the copy in g_string_insert_unichar() */
	size_t len = 0;    
	int first;
	int i;

	if (c < 0x80)
	{
		first = 0;
		len = 1;
	}
	else if (c < 0x800)
	{
		first = 0xc0;
		len = 2;
	}
	else if (c < 0x10000)
	{
		first = 0xe0;
		len = 3;
	}
	else if (c < 0x200000)
	{
		first = 0xf0;
		len = 4;
	}
	else if (c < 0x4000000)
	{
		first = 0xf8;
		len = 5;
	}
	else
	{
		first = 0xfc;
		len = 6;
	}

	if (outbuf)
	{
		for (i = len - 1; i > 0; --i)
		{
			outbuf[i] = (c & 0x3f) | 0x80;
			c >>= 6;
		}
		outbuf[0] = c | first;
	}

	return len;
}

int MyGBKToUTF8_M(char** ppszOutUtf8, char* pszGbk)
{
	int i = 0;
	int iRet = 0;
	int wideLenGuess = 0;
	int wideLen = 0;
	int utfLen = 0;
	unsigned short* pUnicode = NULL;
	if (ppszOutUtf8 == NULL || pszGbk == NULL || strlen(pszGbk) <= 0)
		return 0;
	wideLenGuess = (strlen(pszGbk)+1)*2;
	pUnicode = (unsigned short*)malloc(wideLenGuess);
	if (pUnicode == NULL)
	{
		LOGI("int MyGBKToUTF8_M malloc unicode buf fails!");
		return 0;
	}

	memset(pUnicode, 0, wideLenGuess);

	do {
		if (0 == MyGBKToUnicode(pUnicode, wideLenGuess, pszGbk))
		{
			LOGI("MyGBKToUnicode fails in MyGBKToUTF8_M");
			break;
		}
		wideLen = myWcslen(pUnicode);
		utfLen = GetUtf8Len(pUnicode);
		*ppszOutUtf8 = (char*)malloc(utfLen+1);
		if (*ppszOutUtf8 == NULL)
		{
			break;
		}

		memset(*ppszOutUtf8, 0, utfLen+1);
		for (i = 0; i < wideLen; i++)
		{
			char szTmpUtf8[7] = {0};
			unichar_to_utf8(pUnicode[i], szTmpUtf8);
			strcat(*ppszOutUtf8, szTmpUtf8);
		}

		iRet = 1;
	}while (0);

	SAFE_FREE(pUnicode);

	return iRet;
}

/*************************************************************************************************

 * 将UTF8编码转换成Unicode（UCS-2）编码

 * 参数：

 *    char* pInput  指向输入字符串（以'\0'结尾）的指针 

 *    char** ppOutput 指向输出字符串指针的指针

 * 返回值：

 *    返回转换后的Unicode字符串的字节数，如果出错则返回-1

 * 注意：

 *     1. UTF8没有字节序问题，但是Unicode字符有字节序，

 *        字节序分为大端（Big Endian）和小端（Little Endian）两种，

 *        在Intel处理器中采用小端法表示，因此本例中采用小端法表示。（低地址存低位）

 *     2. 在调用本函数后需要手动释放 *ppOutput 指向的内存，否则将会造成内存泄漏。

 **************************************************************************************************/

static int utf8_to_unicode(char* pInput, char** ppOutput)
{
    int outputSize = 0; //记录转换后的Unicode字符串的字节数
	char *tmp = NULL;
	if (pInput == NULL || strlen(pInput) <= 0)
		return -1;

    *ppOutput = (char *)malloc(strlen(pInput) * 2);  //为输出字符串分配足够大的内存空间
    memset(*ppOutput, 0, strlen(pInput) * 2);
    tmp = *ppOutput; //临时变量，用于遍历输出字符串

    while (*pInput)
    {
        if (*pInput > 0x00 && *pInput <= 0x7F) //处理单字节UTF8字符（英文字母、数字）
        {
            *tmp = *pInput;
            tmp++;
            *tmp = 0; //小端法表示，在高地址填补0
        }
        else if (((*pInput) & 0xE0) == 0xC0) //处理双字节UTF8字符
        {
            char high = *pInput;
			char low = 0;
            pInput++;
            low = *pInput;

            if ((low & 0xC0) != 0x80)  //检查是否为合法的UTF8字符表示
            {
                return -1; //如果不是则报错
            }
   
            *tmp = (high << 6) + (low & 0x3F);
            tmp++;
            *tmp = (high >> 2) & 0x07;
        }
        else if (((*pInput) & 0xF0) == 0xE0) //处理三字节UTF8字符
        {
            char high = *pInput;
			char middle = 0;
			char low = 0;

            pInput++;
            middle = *pInput;
            pInput++;
            low = *pInput;

            if (((middle & 0xC0) != 0x80) || ((low & 0xC0) != 0x80))
            {
                return -1;
            }

            *tmp = (middle << 6) + (low & 0x7F);
            tmp++;
            *tmp = (high << 4) + ((middle >> 2) & 0x0F); 
        }
        else //对于其他字节数的UTF8字符不进行处理
        {
            return -1;
        }

        pInput ++;
        tmp ++;
        outputSize += 2;
    }

    *tmp = 0;
    tmp++;
    *tmp = 0;

    return outputSize;
}

int MyUTF8ToGBK_M(char** ppszOutGbk, char* pszUtf8)
{
	int iRet = 0;
	int unicodeBytes = 0;
	unsigned short* pUnicodeStrChar = NULL;
	
	if (ppszOutGbk == NULL || pszUtf8 == NULL || strlen(pszUtf8) <= 0)
		return 0;
	
	do {
		unicodeBytes = utf8_to_unicode(pszUtf8, (char**)&pUnicodeStrChar);
		if (unicodeBytes <= 0)
		{
			break;
		}

		*ppszOutGbk = (char*)malloc(unicodeBytes+1);
		if (*ppszOutGbk == NULL)
		{
			break;
		}
		memset(*ppszOutGbk, 0, unicodeBytes+1);
		if (0 == MyUnicodeToGBK(*ppszOutGbk, unicodeBytes+1, pUnicodeStrChar))
		{
			LOGI("MyUnicodeToGBK fails in MyUTF8ToGBK_M");
			SAFE_FREE(*ppszOutGbk);
			break;
		}
		iRet = 1;
	} while(0);

	SAFE_FREE(pUnicodeStrChar);

	return iRet;
}
