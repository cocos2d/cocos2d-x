/*
 * Gbk_Unicode.cpp
 *
 *  Created on: 2010-7-7
 *      Author: Administrator
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "Gbk_Unicode.h"

#define UNICODE_BEGIN  (0x3001)
#define UNICODE_END    (0x9FA5)
#define UNICODE_TOTAL  (UNICODE_END-UNICODE_BEGIN+1)
#define UNICODE2_BEGIN  (0xFF00)
#define UNICODE2_END    (0xFFEF)
#define UNICODE2_TOTAL  (UNICODE2_END-UNICODE2_BEGIN+1)


#define FONT_ROW_BEGIN 129
#define FONT_ROW_END   254
#define FONT_COL_BEGIN 64
#define FONT_COL_END   254
#define FONT_TOTAL     (((FONT_ROW_END)-(FONT_ROW_BEGIN)+1)*((FONT_COL_END)-(FONT_COL_BEGIN)+1))

const unsigned short* gbk_table = NULL;
const unsigned short* gbk_table2 = NULL;
const unsigned short* uni_table = NULL;

int InitGbkUnicodeTable(char* szTablePath)
{
	int ret = 0;
	FILE* fp = NULL;
	fp = fopen(szTablePath, "rb");
	if (fp == NULL)
	{
		return 0;
	}
	gbk_table = (unsigned short*)malloc(UNICODE_TOTAL*2);
	memset((void*)gbk_table, 0, UNICODE_TOTAL*2);
	gbk_table2 = (unsigned short*)malloc(UNICODE2_TOTAL*2);
	memset((void*)gbk_table2, 0, UNICODE2_TOTAL*2);
	uni_table = (unsigned short*)malloc(FONT_TOTAL*2);
	memset((void*)uni_table, 0, FONT_TOTAL*2);

	ret = fread((void*)uni_table, FONT_TOTAL*2, 1, fp);
	ret = fread((void*)gbk_table, UNICODE_TOTAL*2, 1, fp);
	ret = fread((void*)gbk_table2, UNICODE2_TOTAL*2, 1, fp);




	fclose(fp);

	return 1;
}

void ReleaseGbkUnicodeTable(void)
{
	if (gbk_table != NULL)
	{
		free((void*)gbk_table);
		gbk_table = NULL;
	}

	if (gbk_table2 != NULL)
	{
		free((void*)gbk_table2);
		gbk_table2 = NULL;
	}

	if (uni_table != NULL)
	{
		free((void*)uni_table);
		uni_table = NULL;
	}
}

void MyUnicodeToGBK(char* pGBKOut, wchar_t* pUnicodeIn)
{
	char* pOneUnicode = NULL;
	int len = wcslen(pUnicodeIn);
	int iIndex = 0;
	int i = 0, j = 0;
	if (pUnicodeIn == NULL|| pGBKOut == NULL)
	{
		return;
	}

	for (i = 0, j = 0; i < len; i++)
	{
		unsigned char* pGbk = NULL;
		unsigned short oneGbk = 0;
		pOneUnicode = (char*)&pUnicodeIn[i];
		if (pOneUnicode[1] == 0)
		{// 半角字母符号
			pGBKOut[j++] = pOneUnicode[0];
		}
		else
		{
			if (pUnicodeIn[i] >= UNICODE_BEGIN && pUnicodeIn[i] <= UNICODE_END)
			{// 汉字
				iIndex = pUnicodeIn[i]-UNICODE_BEGIN;
				oneGbk = gbk_table[iIndex];
				pGbk = (unsigned char*)&oneGbk;
				pGBKOut[j++] = *(pGbk+1);
				pGBKOut[j++] = *pGbk;
			}
			else if (pUnicodeIn[i] >=UNICODE2_BEGIN && pUnicodeIn[i] <= UNICODE2_END)
			{// 全角字母符号
				iIndex = pUnicodeIn[i]-UNICODE2_BEGIN;
				oneGbk = gbk_table2[iIndex];
				pGbk = (unsigned char*)&oneGbk;
				pGBKOut[j++] = *(pGbk+1);
				pGBKOut[j++] = *pGbk;
			}

		}
	}
	pGBKOut[j] = '\0';
}

void MyGBKToUnicode(wchar_t* pUnicodeOut, char* pGBKIn)
{
	int i = 0;
	int j = 0;
	int len = 0;
	int iIndex = 0;
	unsigned char* pUnicode = NULL;
	unsigned short oneGbkHanzi = 0;
	unsigned char* pOneGbkHanzi = (unsigned char*)&oneGbkHanzi;
	unsigned char* pGBKInU = (unsigned char*)pGBKIn;

	if (pUnicodeOut == NULL || pGBKIn == NULL)
	{
		return;
	}
	len = strlen(pGBKIn);
	for (i = 0; i < len; i++)
	{
		pUnicode = (unsigned char*)&pUnicodeOut[j];
		if (pGBKInU[i] >= 0x00 && pGBKInU[i] <= 0x80)
		{// 半角字母符号
			*(pUnicode++) = pGBKInU[i];
			*pUnicode = 0x00;;
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
			pUnicodeOut[j] = uni_table[iIndex];
			++i;
			++j;
		}
	}
	pUnicodeOut[j] = L'\0';
}
