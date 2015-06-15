/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 Copyright (c) 2010 Максим Аксенов
 
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

/**@~english
 * SAXDelegator is the implementation class to parse the XML,
 * SAXParser when parsing the related results callback to SAXDelegator.
 * @~chinese 
 * SAXDelegator是解析XML的具体实现类，SAXParser通过设置委托的方式在进行解析的时候将相关结果回调给SAXDelegator
 */
class CC_DLL SAXDelegator
{
public:
    virtual ~SAXDelegator() {}

    /** @~english Start a node.
     * @~chinese 开始一个节点。
     * @js NA
     * @lua NA
     */
    virtual void startElement(void *ctx, const char *name, const char **atts) = 0;
    
    /** @~english End of a node.
     * @~chinese 结束一个节点。
     * @js NA
     * @lua NA
     */
    virtual void endElement(void *ctx, const char *name) = 0;
    
    /** @~english The text between the nodes.
     * @~chinese 节点之间的文本。
     * @js NA
     * @lua NA
     */
    virtual void textHandler(void *ctx, const char *s, int len) = 0;
};

/**@~english
 * SAXParser is a fast and efficient XML parser. It scan documents line by line, scan while parsing.
 * You should inherit SAXDelegator and implement the method, and then through the SAXParser: : setDelegator to delegate.
 *
 * @~chinese 
 * SAXParser是一个快速高效的XML解释器。它逐行扫描文档，一边扫描一边解析。
 * 你应当继承SAXDelegator并实现其中的方法，然后通过SAXParser::setDelegator来进行委托。
 *
 * @see SAXDelegator
 */
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
    ~SAXParser(void);
    
    /** @~english Initialization, in order to specify the file encoding
     * @~chinese 初始化，以便指定文件的编码
     * @param encoding @~english File encoding, such as: "utf-8"
     * @~chinese 文件编码，如："UTF-8"
     * @return @~english Returns true on success, otherwise it returns false.
     * @~chinese 成功则返回true，否则返回false。
     * @js NA
     * @lua NA
     */
    bool init(const char *encoding);
    
    /** @~english Parse the XML data.
     * @~chinese 解析XML数据。
     * @return @~english Parsing returns true on success, otherwise it returns false.
     * @~chinese 解析成功则返回true，否则返回false。
     * @js NA
     * @lua NA
     */
    bool parse(const char* xmlData, size_t dataLength);
    
    /** @~english Parse the XML whith file name.
     * @~chinese 解析XML文件。
     * @return @~english Parsing returns true on success, otherwise it returns false.
     * @~chinese 解析成功则返回true，否则返回false。
     * @js NA
     * @lua NA
     */
    bool parse(const std::string& filename);
    
    /** @~english Set the delegate.
     * @~chinese 设置委托。
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
    static void textHandler(void *ctx, const CC_XML_CHAR *name, int len);
};

// end of platform group
/// @}

NS_CC_END

/// @endcond
#endif //__CCSAXPARSER_H__
