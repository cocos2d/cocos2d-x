
/*!
*  @file		NewDeleteOp.cpp
*  @author 全智达
*  @brief 
* 
*  @section Copyright
* =======================================================================<br>
* <br>
* Copyright (c) 2005-2010 Tranzda Technologies Co.,Ltd. <br>
*      深圳市全智达科技有限公司 版权所有2005-2010<br>
* <br>
* PROPRIETARY RIGHTS of Tranzda Technologies Co.,Ltd. are involved in <br>
* the subject matter of this material. All manufacturing, reproduction, <br>
* use, and sales rights pertaining to this subject matter are governed <br>
* by the license agreement.  The recipient of this software implicitly <br>
* accepts the terms of the license. <br>
* 本软件文档资料是深圳市全智达科技有限公司的合法资产，任何人士阅读和使<br>
* 用本资料必须获得相应的书面授权,承担保密责任和接受相应的法律约束。<br>
* <br>
* 公司网址：<a href="http://www.tranzda.com"> http://www.tranzda.com </a> <br>
*  公司邮箱：<a  mailto="support@tranzda.com">support@tranzda.com</a> <br>
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


