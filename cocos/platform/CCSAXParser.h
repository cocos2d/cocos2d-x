/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 Copyright (c) 2010 Максим Аксенов
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef __CCSAXPARSER_H__
#define __CCSAXPARSER_H__
/// @cond DO_NOT_SHOW

#include "platform/CCPlatformConfig.h"
#include "platform/CCCommon.h"
#include <string>

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

typedef unsigned char CC_XML_CHAR;

class CC_DLL SAXDelegator
{
public:
    virtual ~SAXDelegator() {}

    /**
     * @js NA
     * @lua NA
     */
    virtual void startElement(void *ctx, const char *name, const char **atts) = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void endElement(void *ctx, const char *name) = 0;
    /**
     * @js NA
     * @lua NA
     */
    virtual void textHandler(void *ctx, const char *s, size_t len) = 0;
};

class CC_DLL SAXParser
{
    SAXDelegator*    _delegator;
public:
    /**
     * @js NA
     * @lua NA
     */
    SAXParser();
    /**
     * @js NA
     * @lua NA
     */
    ~SAXParser();
    /**
     * @js NA
     * @lua NA
     */
    bool init(const char *encoding);
    /**
     * @js NA
     * @lua NA
     */
    bool parse(const char* xmlData, size_t dataLength);
    /**
     * @js NA
     * @lua NA
     */
    bool parse(const std::string& filename);

    /**
    * New API for performance.
    */
    bool parseIntrusive(char* xmlData, size_t dataLength);

    /**
     * @js NA
     * @lua NA
     */
    void setDelegator(SAXDelegator* delegator);
    /**
     * @js NA
     * @lua NA
     */
    static void startElement(void *ctx, const CC_XML_CHAR *name, const CC_XML_CHAR **atts);
    /**
     * @js NA
     * @lua NA
     */
    static void endElement(void *ctx, const CC_XML_CHAR *name);
    /**
     * @js NA
     * @lua NA
     */
    static void textHandler(void *ctx, const CC_XML_CHAR *name, size_t len);
};

// end of platform group
/// @}

NS_CC_END

/// @endcond
#endif //__CCSAXPARSER_H__
