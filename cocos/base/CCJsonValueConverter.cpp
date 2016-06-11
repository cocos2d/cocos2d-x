/****************************************************************************
 Copyright (c) 2010      cocos2d-x.org
 Copyright (C) 2013-2016 Chukong Technologies Inc.
 
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

#include "base/CCJsonValueConverter.h"
#include "json/document.h"
#include "json/writer.h"
#include "base/CCValue.h"

using namespace rapidjson;

NS_CC_BEGIN

//
// Json -> Value
//

namespace JsonValueConverter {
    cocos2d::Value fromJsonObject(const rapidjson::Value &json);
    cocos2d::Value fromJsonArray(const rapidjson::Value &json);
}

cocos2d::Value JsonValueConverter::fromJsonObject(const rapidjson::Value &json) {
    cocos2d::ValueMap ret;
    for (auto it = json.MemberBegin(); it != json.MemberEnd(); ++it) {
        ret[it->name.GetString()] = fromJson(it->value); 
    }
    return cocos2d::Value(ret); 
}

cocos2d::Value JsonValueConverter::fromJsonArray(const rapidjson::Value &json) {
    cocos2d::ValueVector ret;
    ret.reserve(json.Size());
    for (SizeType i = 0; i < json.Size(); ++i) {
        ret.push_back(fromJson(json[i]));
    }
    return cocos2d::Value(ret);
}

cocos2d::Value JsonValueConverter::fromJson(const rapidjson::Value &json) {
    if (json.IsObject()) {
        return fromJsonObject(json);
    }
    
    if (json.IsArray()) {
        return fromJsonArray(json);
    }
    
    if (json.IsString()) {
        return cocos2d::Value(json.GetString());
    }
    
    if (json.IsInt()) {
        return cocos2d::Value(json.GetInt());
    }
    
    if (json.IsBool()) {
        return cocos2d::Value(json.GetBool());
    }
    
    if (json.IsNull()) {
        return cocos2d::Value::Null;
    }
    
    if (json.IsDouble()) {
        return cocos2d::Value(json.GetDouble());
    }
    
    if (json.IsNumber()) {
        return cocos2d::Value(json.GetDouble());
    }

    cocos2d::log("Can't handle json value with type: %d", static_cast<int>(json.GetType()));
    return cocos2d::Value::Null;
}

cocos2d::Value JsonValueConverter::fromJsonString(const std::string &json) {
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    if (doc.HasParseError()) {
        return cocos2d::Value::Null;
    }
    return fromJson(doc);
}


//
// Value -> Json
//

namespace JsonValueConverter {
    void initJsonValueForCocosValue(rapidjson::Value *json, const cocos2d::Value &value, rapidjson::Document::AllocatorType &allocator);
    void fillJsonValueForValueMap(rapidjson::Value *json, const cocos2d::ValueMap &valueMap, rapidjson::Document::AllocatorType &allocator);
    void fillJsonValueForValueVector(rapidjson::Value *json, const cocos2d::ValueVector &valueVector, rapidjson::Document::AllocatorType &allocator);
    void fillJsonValueForIntKeyMap(rapidjson::Value *json, const cocos2d::ValueMapIntKey &intKeyMap, rapidjson::Document::AllocatorType &allocator);
}

std::string JsonValueConverter::toJsonString(const cocos2d::Value &value) {
    rapidjson::Document json = toJson(value);
    rapidjson::StringBuffer s;
    rapidjson::Writer<StringBuffer> writer(s);
    json.Accept(writer);
    return s.GetString();
}

rapidjson::Document JsonValueConverter::toJson(const cocos2d::Value &value) {
    rapidjson::Document doc;
    initJsonValueForCocosValue(&doc, value, doc.GetAllocator());
    return doc;
}

void JsonValueConverter::initJsonValueForCocosValue(rapidjson::Value *json, const cocos2d::Value &value, rapidjson::Document::AllocatorType &allocator) {
    switch (value.getType()) {
        case cocos2d::Value::Type::NONE:
            json->SetNull();
            break;
            
        case cocos2d::Value::Type::BYTE:
            json->SetInt(value.asByte());
            break;
        
        case cocos2d::Value::Type::UNSIGNED:
            json->SetUint(value.asUnsignedInt());
            break;
            
        case cocos2d::Value::Type::INTEGER:
            json->SetInt(value.asInt());
            break;
            
        case cocos2d::Value::Type::FLOAT:
            json->SetDouble(value.asFloat());
            break;
            
        case cocos2d::Value::Type::DOUBLE:
            json->SetDouble(value.asDouble());
            break;
            
        case cocos2d::Value::Type::BOOLEAN:
            json->SetBool(value.asBool());
            break;
            
        case cocos2d::Value::Type::STRING: {
            const std::string str = value.asString();
            json->SetString(str.c_str(), static_cast<unsigned int>(str.size()), allocator);
            break;
        }
        case cocos2d::Value::Type::VECTOR:
            fillJsonValueForValueVector(json, value.asValueVector(), allocator);
            break;
            
        case cocos2d::Value::Type::MAP:
            fillJsonValueForValueMap(json, value.asValueMap(), allocator);
            break;
            
        case cocos2d::Value::Type::INT_KEY_MAP:
            fillJsonValueForIntKeyMap(json, value.asIntKeyMap(), allocator);
            break;
    }
}

void JsonValueConverter::fillJsonValueForValueMap(rapidjson::Value *json, const cocos2d::ValueMap &valueMap, rapidjson::Document::AllocatorType &allocator) {
    json->SetObject();
    for (auto &&entry: valueMap) {
        rapidjson::Value name(entry.first.c_str(), static_cast<unsigned int>(entry.first.size()), allocator);
        rapidjson::Value value;
        initJsonValueForCocosValue(&value, entry.second, allocator);
        json->AddMember(name, value, allocator);
    }
}

void JsonValueConverter::fillJsonValueForValueVector(rapidjson::Value *json, const cocos2d::ValueVector &valueVector, rapidjson::Document::AllocatorType &allocator) {
    json->SetArray();
    for (auto &&entry: valueVector) {
        rapidjson::Value value;
        initJsonValueForCocosValue(&value, entry, allocator);
        json->PushBack(value, allocator);
    }
}

void JsonValueConverter::fillJsonValueForIntKeyMap(rapidjson::Value *json, const cocos2d::ValueMapIntKey &intKeyMap, rapidjson::Document::AllocatorType &allocator) {
    CCASSERT(false, "Convertion ValueMapIntKey -> JsonValue not supported");
}

NS_CC_END
