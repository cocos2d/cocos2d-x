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
#ifndef __CCSTRING_H__
#define __CCSTRING_H__
#include <string>
#include <stdlib.h>
#include "CCObject.h"
namespace cocos2d {

	class CC_DLL CCString : public CCObject
	{
	public:
		std::string m_sString;
	public:
		CCString()
			:m_sString("")
		{}
		CCString(const char * str)
		{
			m_sString = str;
		}
		virtual ~CCString(){ m_sString.clear(); }
		
		int toInt()
		{
			return atoi(m_sString.c_str());
		}
		unsigned int toUInt()
		{
			return (unsigned int)atoi(m_sString.c_str());
		}
		float toFloat()
		{
			return (float)atof(m_sString.c_str());
		}
		std::string toStdString()
		{
			return m_sString;
		}

		bool isEmpty()
		{
			return m_sString.empty();
		}

        virtual bool isEqual(const CCObject* pObject)
        {
            bool bRet = false;
            const CCString* pStr = dynamic_cast<const CCString*>(pObject);
            if (pStr != NULL)
            {
                if (0 == m_sString.compare(pStr->m_sString))
                {
                    bRet = true;
                }
            }
            return bRet;
        }
	};
}// namespace cocos2d
#endif //__CCSTRING_H__