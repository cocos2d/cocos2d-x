
/*!
*  @file		NewDeleteOp.cpp
*  @author ȫ�Ǵ�
*  @brief 
* 
*  @section Copyright
* =======================================================================<br>
* <br>
* Copyright (c) 2005-2010 Tranzda Technologies Co.,Ltd. <br>
*      ������ȫ�Ǵ�Ƽ����޹�˾ ��Ȩ����2005-2010<br>
* <br>
* PROPRIETARY RIGHTS of Tranzda Technologies Co.,Ltd. are involved in <br>
* the subject matter of this material. All manufacturing, reproduction, <br>
* use, and sales rights pertaining to this subject matter are governed <br>
* by the license agreement.  The recipient of this software implicitly <br>
* accepts the terms of the license. <br>
* ������ĵ�������������ȫ�Ǵ�Ƽ����޹�˾�ĺϷ��ʲ����κ���ʿ�Ķ���ʹ<br>
* �ñ����ϱ�������Ӧ��������Ȩ,�е��������κͽ�����Ӧ�ķ���Լ����<br>
* <br>
* ��˾��ַ��<a href="http://www.tranzda.com"> http://www.tranzda.com </a> <br>
*  ��˾���䣺<a  mailto="support@tranzda.com">support@tranzda.com</a> <br>
* =======================================================================<br>
*/

#include "ssTypes.h"
#include "TG3_Type.h"
#include "TG3_Memory.h"

#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif

#ifndef _WIN32
    #define __cdecl
#endif

void * __cdecl operator new(unsigned int size)
{
    return TMalloc(size);
}

void * __cdecl operator new[](unsigned int size)
{
    return TMalloc(size);
}

void * __cdecl operator new(unsigned int size, const unsigned short * fileName, int lineNo)
{
    return TMallocEx(size, fileName, lineNo);
}

void * __cdecl operator new[](unsigned int size, const unsigned short * fileName, int lineNo)
{
    return TMallocEx(size, fileName, lineNo);
}

void __cdecl operator delete(void *p)
{
    TFree(p);
}

void __cdecl operator delete[](void *p)
{
    TFree(p);
}

void __cdecl operator delete(void *p, const unsigned short * fileName, int lineNo)
{
    TFreeEx(p, fileName, lineNo);
}

void __cdecl operator delete[](void *p, const unsigned short * fileName, int lineNo)
{
    TFreeEx(p, fileName, lineNo);
}


