/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.
 
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
#pragma once

#include <string>
#include <stack>
#include "cocos2d.h"

#include "Macros.h"

NS_CCR_BEGIN

class RichtextStringVisitor : public cocos2d::SAXDelegator
{
public:
    RichtextStringVisitor();
    
    virtual void startElement(void *ctx, const char *name, const char **atts) override;
    virtual void endElement(void *ctx, const char *name) override;
    virtual void textHandler(void *ctx, const char *s, size_t len) override;
    
    const std::string& getOutput() const;
    const std::string& getRawString() const;
    int getMaxFontSize() const;
    
private:
    
    std::string convertColorString2Hex(const std::string& colorString) const;
    std::string convertAttributeName(const std::string& tagName, const std::string& attributeName) const;
    std::string convertAttributeValue(const std::string& tagName, const std::string& attributeName, const std::string& attributeValue) const;
    
    const static std::string COLOR_FLAG;
    const static std::string SIZE_FLAG;
    const static std::string IMG_FLAG;
    const static std::string BR_FLAG;
    const static std::map<std::string, std::string> COLOR_MAP;
    
    std::string _outputXML;
    std::string _rawString;
    int _maxFontSize;
    std::stack<bool> _addFontEndFlags;
};

NS_CCR_END
