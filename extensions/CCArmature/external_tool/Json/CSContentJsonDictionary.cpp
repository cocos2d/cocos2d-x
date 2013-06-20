/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.cocostudio.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include "CSContentJsonDictionary.h"

namespace cs {
    
    CSJsonDictionary::CSJsonDictionary()
    {
        _value.clear();
    }
    
    
    CSJsonDictionary::~CSJsonDictionary()
    {
        _value.clear();
    }
    
    
    void CSJsonDictionary::initWithDescription(const char *pszDescription)
    {
        CSJson::Reader cReader;
        _value.clear();
        if (pszDescription && *pszDescription)
        {
            std::string strValue = pszDescription;
            cReader.parse(strValue, _value, false);
        }
    }
    
    
    void CSJsonDictionary::initWithValue(CSJson::Value& value)
    {
        _value = value;
    }
    
    
    void CSJsonDictionary::insertItem(const char *pszKey, int nValue)
    {
        _value[pszKey] = nValue;
    }
    
    
    void CSJsonDictionary::insertItem(const char *pszKey, double fValue)
    {
        _value[pszKey] = fValue;
    }
    
    
    void CSJsonDictionary::insertItem(const char *pszKey, const char * pszValue)
    {
        _value[pszKey] = pszValue;
    }
    
    void CSJsonDictionary::insertItem(const char *pszKey, bool bValue)
    {
        _value[pszKey] = bValue;
    }
    
    void CSJsonDictionary::insertItem(const char *pszKey, CSJsonDictionary * subDictionary)
    {
        if (subDictionary)
            _value[pszKey] = subDictionary->_value;
    }
    
    
    bool CSJsonDictionary::deleteItem(const char *pszKey)
    {
        if(!_value.isMember(pszKey))
            return false;
        
        _value.removeMember(pszKey);
        
        return true;
    }
    
    
    void CSJsonDictionary::cleanUp()
    {
        _value.clear();
    }
    
    
    bool CSJsonDictionary::isKeyValidate(const char *pszKey)
    {
        return _value.isMember(pszKey);
    }
    
    
    int CSJsonDictionary::getItemIntValue(const char *pszKey, int nDefaultValue)
    {
        if (!isKeyValidate(pszKey, _value) || !_value[pszKey].isNumeric())
            return nDefaultValue;
        
        return _value[pszKey].asInt();
    }
    
    
    double CSJsonDictionary::getItemFloatValue(const char *pszKey, double fDefaultValue)
    {
        if (!isKeyValidate(pszKey, _value) || !_value[pszKey].isNumeric())
            return fDefaultValue;
        
        return _value[pszKey].asDouble();
    }
    
    
    const char * CSJsonDictionary::getItemStringValue(const char *pszKey)
    {
        if (!isKeyValidate(pszKey, _value) || !_value[pszKey].isString())
            return NULL;
        
        return _value[pszKey].asCString();
    }
    
    bool CSJsonDictionary::getItemBoolvalue(const char *pszKey, bool bDefaultValue)
    {
        if (!isKeyValidate(pszKey, _value) || !_value[pszKey].isBool())
            return bDefaultValue;
        
        return _value[pszKey].asBool();
    }
    
    
    CSJsonDictionary * CSJsonDictionary::getSubDictionary(const char *pszKey)
    {
        CSJsonDictionary * pNewDictionary;
        if (!isKeyValidate(pszKey, _value) || (!_value[pszKey].isArray() &&
                                                 !_value[pszKey].isObject() &&
                                                 !_value[pszKey].isConvertibleTo(CSJson::arrayValue) &&
                                                 !_value[pszKey].isConvertibleTo(CSJson::objectValue)))
        {
            pNewDictionary = NULL;
        }
        else
        {
            pNewDictionary = new CSJsonDictionary();
            pNewDictionary->initWithValue(_value[pszKey]);
        }
        return pNewDictionary;
    }
    
    
    std::string CSJsonDictionary::getDescription()
    {
        std::string strReturn = _value.toStyledString();
        return strReturn;
    }
    
    
    bool CSJsonDictionary::insertItemToArray(const char *pszArrayKey, int nValue)
    {
        CSJson::Value array;
        if(_value.isMember(pszArrayKey))
        {
            if (!_value[pszArrayKey].isArray() && !_value[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
                return false;
            
            array = _value[pszArrayKey];
        }
        
        array.append(nValue);
        _value[pszArrayKey] = array;
        
        return true;
    }
    
    
    bool CSJsonDictionary::insertItemToArray(const char *pszArrayKey, double fValue)
    {
        CSJson::Value array;
        if(_value.isMember(pszArrayKey))
        {
            if (!_value[pszArrayKey].isArray() && !_value[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
                return false;
            
            array = _value[pszArrayKey];
        }
        
        array.append(fValue);
        _value[pszArrayKey] = array;
        
        return true;
    }
    
    
    bool CSJsonDictionary::insertItemToArray(const char *pszArrayKey, const char * pszValue)
    {
        CSJson::Value array;
        if(_value.isMember(pszArrayKey))
        {
            if (!_value[pszArrayKey].isArray() && !_value[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
                return false;
            
            array = _value[pszArrayKey];
        }
        
        array.append(pszValue);
        _value[pszArrayKey] = array;
        
        return true;
    }
    
    
    bool CSJsonDictionary::insertItemToArray(const char *pszArrayKey, CSJsonDictionary * subDictionary)
    {
        CSJson::Value array;
        if(_value.isMember(pszArrayKey))
        {
            if (!_value[pszArrayKey].isArray() && !_value[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
                return false;
            
            array = _value[pszArrayKey];
        }
        
        array.append(subDictionary->_value);
        _value[pszArrayKey] = array;
        
        return true;
    }
    
    
    int CSJsonDictionary::getItemCount()
    {
        return _value.size();
    }
    
    
    DicItemType CSJsonDictionary::getItemType(int nIndex)
    {
        return (DicItemType)_value[nIndex].type();
    }
    
    
    DicItemType CSJsonDictionary::getItemType(const char *pszKey)
    {
        return (DicItemType)_value[pszKey].type();
    }
    
    std::vector<std::string> CSJsonDictionary::getAllMemberNames()
    {
        return _value.getMemberNames();
    }
    
    
    int CSJsonDictionary::getArrayItemCount(const char *pszArrayKey)
    {
        int nRet = 0;
        if (!isKeyValidate(pszArrayKey, _value) ||
            (!_value[pszArrayKey].isArray() && !_value[pszArrayKey].isObject() &&
             !_value[pszArrayKey].isConvertibleTo(CSJson::arrayValue) && !_value[pszArrayKey].isConvertibleTo(CSJson::objectValue)))
        {
            nRet = 0;
        }
        else
        {
            CSJson::Value arrayValue = _value[pszArrayKey];
            nRet = arrayValue.size();
        }
        
        return nRet;
    }
    
    
    int CSJsonDictionary::getIntValueFromArray(const char *pszArrayKey, int nIndex, int nDefaultValue)
    {
        int nRet = nDefaultValue;
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
        {
            if ((*arrayValue)[nIndex].isNumeric())
                nRet = (*arrayValue)[nIndex].asInt();
        }
        
        return nRet;
    }
    
    
    double CSJsonDictionary::getFloatValueFromArray(const char *pszArrayKey, int nIndex, double fDefaultValue)
    {
        double fRet = fDefaultValue;
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
        {
            if ((*arrayValue)[nIndex].isNumeric())
                fRet = (*arrayValue)[nIndex].asDouble();
        }
        
        return fRet;
    }
    
    
    const char * CSJsonDictionary::getStringValueFromArray(const char *pszArrayKey, int nIndex)
    {
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
        {
            if ((*arrayValue)[nIndex].isString())
                return (*arrayValue)[nIndex].asCString();
        }
        
        return NULL;
    }
    
    
    CSJsonDictionary * CSJsonDictionary::getSubItemFromArray(const char *pszArrayKey, int nIndex)
    {
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
        {
            if ((*arrayValue)[nIndex].isArray() || (*arrayValue)[nIndex].isObject())
            {
                CSJsonDictionary * pNewDictionary = new CSJsonDictionary();
                pNewDictionary->initWithValue((*arrayValue)[nIndex]);
                return pNewDictionary;
            }
        }
        
        return NULL;
    }
    
    
    DicItemType CSJsonDictionary::getItemTypeFromArray(const char *pszArrayKey, int nIndex)
    {
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
            return (DicItemType)((*arrayValue)[nIndex].type());
        
        return (DicItemType)CSJson::nullValue;
    }
    
    
    inline bool CSJsonDictionary::isKeyValidate(const char *pszKey, CSJson::Value& root)
    {
        if (root.isNull() || !root.isMember(pszKey))
            return false;
        
        return true;
    }
    
    
    inline CSJson::Value * CSJsonDictionary::validateArrayItem(const char *pszArrayKey, int nIndex)
    {
        if (!isKeyValidate(pszArrayKey, _value) && !_value[pszArrayKey].isArray() && !_value[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
            return NULL;
        if (!_value[pszArrayKey].isValidIndex(nIndex))
            return NULL;
        
        return &_value[pszArrayKey];
    }
}
