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


#include "CCData.h"
#include "CCFileUtils.h"

#include <stdio.h>

using namespace std;
namespace   cocos2d {

CCData::CCData(void)
: m_pData(NULL)
{
}

CCData::~CCData(void)
{
	CC_SAFE_DELETE_ARRAY(m_pData);
}

CCData* CCData::dataWithContentsOfFile(const string &strPath)
{
    CCFileData data(strPath.c_str(), "rb");
    unsigned long  nSize = data.getSize();
    unsigned char* pBuffer = data.getBuffer();

    if (! pBuffer)
    {
        return NULL;
    }

	CCData *pRet = new CCData();
    pRet->m_pData = new char[nSize];
    memcpy(pRet->m_pData, pBuffer, nSize);

	return pRet;
}

void* CCData::bytes(void)
{
	return m_pData;
}

//@todo implement
CCData* CCData::dataWithBytes(unsigned char *pBytes, int size)
{
    CC_UNUSED_PARAM(pBytes);
    CC_UNUSED_PARAM(size);
	return NULL;
}
}//namespace   cocos2d 
