/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "JsonValueConverterTest.h"
#include "base/CCJsonValueConverter.h"
#include "deprecated/CCString.h"

USING_NS_CC;

ValueConverterTests::ValueConverterTests()
{
    ADD_TEST_CASE(JsonValueConverterTest);
}

JsonValueConverterTest::JsonValueConverterTest() {
    cocos2d::ValueMap map;
    map["int"] = Value(10);
    map["float"] = Value(12.34f);
    map["array"] = Value({Value(1), Value(2), Value(3), Value(4)});
    map["object"] = Value({
        {"string", Value("string value")},
        {"null", Value::Null}
    });
    
    const std::string str = JsonValueConverter::toJsonString(Value(map));
    
    
    
    const Value value = JsonValueConverter::fromJsonString(str);
    const ValueMap &readMap = value.asValueMap();
    std::string readValues;
    readValues += "int = " + StringUtils::toString(readMap.at("int").asInt());
    readValues += "\nfloat = " + StringUtils::toString(readMap.at("float").asFloat());
    readValues += "\narray = [";
    const ValueVector &array = readMap.at("array").asValueVector();
    for (const Value &value: array) {
        readValues += StringUtils::toString(value.asString()) + ",";
    }
    readValues += "]";
    
    const ValueMap &obj = readMap.at("object").asValueMap();
    readValues += "\nobject.string = " + obj.at("string").asString();
    readValues += std::string("\nobject.null = ") + (obj.at("null").isNull() ? "null" : "not null");
    
    const Size screenSize = Director::getInstance()->getWinSize();
    Label *label = Label::create();
    label->setTextColor(Color4B::WHITE);
    label->setHorizontalAlignment(TextHAlignment::LEFT);
    label->setLineBreakWithoutSpace(true);
    //label->setMaxLineWidth(screenSize.width - 20);
    label->setWidth(screenSize.width - 20.0f);
    label->setString(str + "\n\n" + readValues);
    label->setAnchorPoint(Point(0.5f, 1.0f));
    label->setPosition(screenSize.width * 0.5f, screenSize.height - 150.0f);
    addChild(label);
}

std::string JsonValueConverterTest::title() const {
    return "Test converting CCValue <-> JSON";
}

