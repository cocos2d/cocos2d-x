/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org

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

#ifndef __CCDATA_H__
#define __CCDATA_H__

#include "platform/CCPlatformMacros.h"
#include "CCObject.h"

NS_CC_BEGIN

class CC_DLL Data : public Object
{
public:
    /**
     * @js NA
     * @lua NA
     */
    Data(unsigned char *pBytes, const unsigned long nSize);
    /**
     * @js NA
     * @lua NA
     */
    Data(Data *pData);
    /**
     * @js NA
     * @lua NA
     */
    ~Data();
    /**
     * @js NA
     * @lua NA
     */
    static Data* create(unsigned char *pBytes, const unsigned long nSize)
    {
        Data* pRet = new Data(pBytes, nSize);
        if (pRet)
        {
            pRet->autorelease();
        }
        return pRet;
    }    
    /**
     * @js NA
     * @lua NA
     */
    unsigned char* getBytes() const;
    /**
     * @js NA
     * @lua NA
     */
    unsigned long getSize() const;
    
    /** override functions
     * @js NA
     * @lua NA
     */
    virtual void acceptVisitor(DataVisitor &visitor) { visitor.visit(this); }

private:
    unsigned char* _bytes;
    unsigned long _size;
};

NS_CC_END

#endif // __CCDATA_H__
