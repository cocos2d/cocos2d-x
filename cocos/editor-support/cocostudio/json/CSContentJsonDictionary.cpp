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
    
    JsonDictionary::JsonDictionary()
    {
        m_cValue.clear();
    }
    
    
    JsonDictionary::~JsonDictionary()
    {
        m_cValue.clear();
    }
    
    
    void JsonDictionary::initWithDescription(const char *pszDescription)
    {
        CSJson::Reader cReader;
        m_cValue.clear();
        if (pszDescription && *pszDescription)
        {
            std::string strValue = pszDescription;
            cReader.parse(strValue, m_cValue, false);
        }
    }
    
    
    void JsonDictionary::initWithValue(CSJson::Value& value)
    {
        m_cValue = value;
    }
    
    
    void JsonDictionary::insertItem(const char *pszKey, int nValue)
    {
        m_cValue[pszKey] = nValue;
    }
    
    
    void JsonDictionary::insertItem(const char *pszKey, double fValue)
    {
        m_cValue[pszKey] = fValue;
    }
    
    
    void JsonDictionary::insertItem(const char *pszKey, const char * pszValue)
    {
        m_cValue[pszKey] = pszValue;
    }
    
    void JsonDictionary::insertItem(const char *pszKey, bool bValue)
    {
        m_cValue[pszKey] = bValue;
    }
    
    void JsonDictionary::insertItem(const char *pszKey, JsonDictionary * subDictionary)
    {
        if (subDictionary)
            m_cValue[pszKey] = subDictionary->m_cValue;
    }
    
    
    bool JsonDictionary::deleteItem(const char *pszKey)
    {
        if(!m_cValue.isMember(pszKey))
            return false;
        
        m_cValue.removeMember(pszKey);
        
        return true;
    }
    
    
    void JsonDictionary::cleanUp()
    {
        m_cValue.clear();
    }
    
    
    bool JsonDictionary::isKeyValidate(const char *pszKey)
    {
        return m_cValue.isMember(pszKey);
    }
    
    
    int JsonDictionary::getItemIntValue(const char *pszKey, int nDefaultValue)
    {
        if (!isKeyValidate(pszKey, m_cValue) || !m_cValue[pszKey].isNumeric())
            return nDefaultValue;
        
        return m_cValue[pszKey].asInt();
    }
    
    
    double JsonDictionary::getItemFloatValue(const char *pszKey, double fDefaultValue)
    {
        if (!isKeyValidate(pszKey, m_cValue) || !m_cValue[pszKey].isNumeric())
            return fDefaultValue;
        
        return m_cValue[pszKey].asDouble();
    }
    
    
    const char * JsonDictionary::getItemStringValue(const char *pszKey)
    {
        if (!isKeyValidate(pszKey, m_cValue) || !m_cValue[pszKey].isString())
            return NULL;
        
        return m_cValue[pszKey].asCString();
    }
    
    bool JsonDictionary::getItemBoolvalue(const char *pszKey, bool bDefaultValue)
    {
        if (!isKeyValidate(pszKey, m_cValue) || !m_cValue[pszKey].isBool())
            return bDefaultValue;
        
        return m_cValue[pszKey].asBool();
    }
    
    
    JsonDictionary * JsonDictionary::getSubDictionary(const char *pszKey)
    {
        JsonDictionary * pNewDictionary;
        if (!isKeyValidate(pszKey, m_cValue) || (!m_cValue[pszKey].isArray() &&
                                                 !m_cValue[pszKey].isObject() &&
                                                 !m_cValue[pszKey].isConvertibleTo(CSJson::arrayValue) &&
                                                 !m_cValue[pszKey].isConvertibleTo(CSJson::objectValue)))
        {
            pNewDictionary = NULL;
        }
        else
        {
            pNewDictionary = new JsonDictionary();
            pNewDictionary->initWithValue(m_cValue[pszKey]);
        }
        return pNewDictionary;
    }
    
    
    std::string JsonDictionary::getDescription()
    {
        std::string strReturn = m_cValue.toStyledString();
        return strReturn;
    }
    
    
    bool JsonDictionary::insertItemToArray(const char *pszArrayKey, int nValue)
    {
        CSJson::Value array;
        if(m_cValue.isMember(pszArrayKey))
        {
            if (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
                return false;
            
            array = m_cValue[pszArrayKey];
        }
        
        array.append(nValue);
        m_cValue[pszArrayKey] = array;
        
        return true;
    }
    
    
    bool JsonDictionary::insertItemToArray(const char *pszArrayKey, double fValue)
    {
        CSJson::Value array;
        if(m_cValue.isMember(pszArrayKey))
        {
            if (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
                return false;
            
            array = m_cValue[pszArrayKey];
        }
        
        array.append(fValue);
        m_cValue[pszArrayKey] = array;
        
        return true;
    }
    
    
    bool JsonDictionary::insertItemToArray(const char *pszArrayKey, const char * pszValue)
    {
        CSJson::Value array;
        if(m_cValue.isMember(pszArrayKey))
        {
            if (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
                return false;
            
            array = m_cValue[pszArrayKey];
        }
        
        array.append(pszValue);
        m_cValue[pszArrayKey] = array;
        
        return true;
    }
    
    
    bool JsonDictionary::insertItemToArray(const char *pszArrayKey, JsonDictionary * subDictionary)
    {
        CSJson::Value array;
        if(m_cValue.isMember(pszArrayKey))
        {
            if (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
                return false;
            
            array = m_cValue[pszArrayKey];
        }
        
        array.append(subDictionary->m_cValue);
        m_cValue[pszArrayKey] = array;
        
        return true;
    }
    
    
    int JsonDictionary::getItemCount()
    {
        return m_cValue.size();
    }
    
    
    DicItemType JsonDictionary::getItemType(int nIndex)
    {
        return (DicItemType)m_cValue[nIndex].type();
    }
    
    
    DicItemType JsonDictionary::getItemType(const char *pszKey)
    {
        return (DicItemType)m_cValue[pszKey].type();
    }
    
    std::vector<std::string> JsonDictionary::getAllMemberNames()
    {
        return m_cValue.getMemberNames();
    }
    
    
    int JsonDictionary::getArrayItemCount(const char *pszArrayKey)
    {
        int nRet = 0;
        if (!isKeyValidate(pszArrayKey, m_cValue) ||
            (!m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isObject() &&
             !m_cValue[pszArrayKey].isConvertibleTo(CSJson::arrayValue) && !m_cValue[pszArrayKey].isConvertibleTo(CSJson::objectValue)))
        {
            nRet = 0;
        }
        else
        {
            CSJson::Value arrayValue = m_cValue[pszArrayKey];
            nRet = arrayValue.size();
        }
        
        return nRet;
    }
    
    
    int JsonDictionary::getIntValueFromArray(const char *pszArrayKey, int nIndex, int nDefaultValue)
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
    
    
    double JsonDictionary::getFloatValueFromArray(const char *pszArrayKey, int nIndex, double fDefaultValue)
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
    
    bool JsonDictionary::getBoolValueFromArray(const char *pszArrayKey, int nIndex, bool bDefaultValue)
    {
        bool bRet = bDefaultValue;
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
        {
            if ((*arrayValue)[nIndex].isNumeric())
                bRet = (*arrayValue)[nIndex].asBool();
        }
        
        return bRet;
    }
    
    
    const char * JsonDictionary::getStringValueFromArray(const char *pszArrayKey, int nIndex)
    {
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
        {
            if ((*arrayValue)[nIndex].isString())
                return (*arrayValue)[nIndex].asCString();
        }
        
        return NULL;
    }
    
    
    JsonDictionary * JsonDictionary::getSubItemFromArray(const char *pszArrayKey, int nIndex)
    {
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
        {
            if ((*arrayValue)[nIndex].isArray() || (*arrayValue)[nIndex].isObject())
            {
                JsonDictionary * pNewDictionary = new JsonDictionary();
                pNewDictionary->initWithValue((*arrayValue)[nIndex]);
                return pNewDictionary;
            }
        }
        
        return NULL;
    }
    
    
    DicItemType JsonDictionary::getItemTypeFromArray(const char *pszArrayKey, int nIndex)
    {
        CSJson::Value * arrayValue = validateArrayItem(pszArrayKey, nIndex);
        if (arrayValue)
            return (DicItemType)((*arrayValue)[nIndex].type());
        
        return (DicItemType)CSJson::nullValue;
    }
    
    
    inline bool JsonDictionary::isKeyValidate(const char *pszKey, CSJson::Value& root)
    {
        if (root.isNull() || !root.isMember(pszKey))
            return false;
        
        return true;
    }
    
    
    inline CSJson::Value * JsonDictionary::validateArrayItem(const char *pszArrayKey, int nIndex)
    {
        if (!isKeyValidate(pszArrayKey, m_cValue) && !m_cValue[pszArrayKey].isArray() && !m_cValue[pszArrayKey].isConvertibleTo(CSJson::arrayValue))
            return NULL;
        if (!m_cValue[pszArrayKey].isValidIndex(nIndex))
            return NULL;
        
        return &m_cValue[pszArrayKey];
    }
}
