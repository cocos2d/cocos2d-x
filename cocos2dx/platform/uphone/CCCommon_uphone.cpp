/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCCommon_uphone.h"

#include "TG3.h"

#define MAX_LEN         256
#define LOG_FILE_PATH   "/NEWPLUS/TDA_DATA/UserData/Cocos2dLog.txt"

namespace   cocos2d {

void CCLog(const char * pszFormat, ...)
{
    SS_printf("Cocos2d: ");
    char szBuf[MAX_LEN];

    va_list ap;
    va_start(ap, pszFormat);
#ifdef _TRANZDA_VM_
    vsprintf_s(szBuf, MAX_LEN, pszFormat, ap);
#else
    vsnprintf(szBuf, MAX_LEN, pszFormat, ap);
#endif
    va_end(ap);
    
    SS_printf("%s", szBuf);
#ifdef _TRANZDA_VM_
    SS_printf("\n");
#else
    SS_printf("\r\n");
    FILE * pf = fopen(LOG_FILE_PATH, "a+");
    if (! pf)
    {
        return;
    }

    fwrite(szBuf, 1, strlen(szBuf), pf);
    fwrite("\r\n", 1, strlen("\r\n"), pf);
    fflush(pf);
    fclose(pf);
#endif
}

}//namespace   cocos2d 
