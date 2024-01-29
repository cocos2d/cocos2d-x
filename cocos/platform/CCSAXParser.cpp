/****************************************************************************
 Copyright (c) 2010 Максим Аксенов
 Copyright (c) 2010 cocos2d-x.org  
 Copyright (c) 2013 Martell Malone
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

#include "platform/CCSAXParser.h"

#include <vector> // because its based on windows 8 build :P

#include "platform/CCFileUtils.h"
#include "rapidxml/rapidxml_sax3.hpp"

NS_CC_BEGIN

/// rapidxml SAX handler
class RapidXmlSaxHander : public rapidxml::xml_sax2_handler
{

public:
    RapidXmlSaxHander() :_ccsaxParserImp(0) {};

    void setSAXParserImp(SAXParser* parser)
    {
        _ccsaxParserImp = parser;
    }

    void xmlSAX2StartElement(const char *name, size_t /*len*/, const char **atts, size_t /*attslen*/) override
    {
        SAXParser::startElement(_ccsaxParserImp, (const CC_XML_CHAR *)name, (const CC_XML_CHAR **)atts);
    }

    void xmlSAX2EndElement(const char *name, size_t /*len*/) override
    {
        SAXParser::endElement(_ccsaxParserImp, (const CC_XML_CHAR *)name);
    }

    void xmlSAX2Text(const char *s, size_t len) override
    {
        SAXParser::textHandler(_ccsaxParserImp, (const CC_XML_CHAR *)s, len);
    }

private:
    SAXParser *_ccsaxParserImp;
};

SAXParser::SAXParser()
{
    _delegator = nullptr;
}

SAXParser::~SAXParser()
{
}

bool SAXParser::init(const char* /*encoding*/)
{
    // nothing to do
    return true;
}

bool SAXParser::parse(const char* xmlData, size_t dataLength)
{
    if(xmlData != nullptr && dataLength > 0) {
        std::string mutableData(xmlData, dataLength);
        return this->parseIntrusive(&mutableData.front(), dataLength);
    }
    return false;
}

bool SAXParser::parse(const std::string& filename)
{
    bool ret = false;
    Data data = FileUtils::getInstance()->getDataFromFile(filename);
    if (!data.isNull())
    {
        ret = parseIntrusive((char*)data.getBytes(), data.getSize());
    }

    return ret;
}

bool SAXParser::parseIntrusive(char* xmlData, size_t dataLength)
{
    RapidXmlSaxHander printer;
    printer.setSAXParserImp(this);

    rapidxml::xml_sax3_parser<> parser(&printer);
    try {
        parser.parse<>(xmlData, static_cast<int>(dataLength));
        return true;
    }
    catch (rapidxml::parse_error& e)
    {
        CCLOG("cocos2d: SAXParser: Error parsing xml: %s at %s", e.what(), e.where<char>());
        return false;
    }

    return false;
}

void SAXParser::startElement(void *ctx, const CC_XML_CHAR *name, const CC_XML_CHAR **atts)
{
    ((SAXParser*)(ctx))->_delegator->startElement(ctx, (char*)name, (const char**)atts);
}

void SAXParser::endElement(void *ctx, const CC_XML_CHAR *name)
{
    ((SAXParser*)(ctx))->_delegator->endElement(ctx, (char*)name);
}
void SAXParser::textHandler(void *ctx, const CC_XML_CHAR *name, size_t len)
{
    ((SAXParser*)(ctx))->_delegator->textHandler(ctx, (char*)name, len);
}
void SAXParser::setDelegator(SAXDelegator* delegator)
{
    _delegator = delegator;
}

NS_CC_END


