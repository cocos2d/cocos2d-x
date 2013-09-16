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

#ifndef COCOSTUDIO_CSCONTENTJSONDICTIONARY_H
#define COCOSTUDIO_CSCONTENTJSONDICTIONARY_H


#include "lib_json/json_lib.h"
#include <vector>
#include <string>

namespace cs {

    typedef enum _DicItemType
    {
        EDIC_TYPENULL = 0,
        EDIC_TYPEINT,
        EDIC_TYPEUINT,
        EDIC_TYPEFLOAT,
        EDIC_TYPESTRING,
        EDIC_TYPEBOOLEN,
        EDIC_TYPEARRAY,
        EDIC_TYPEOBJECT
    }DicItemType;

    class CSJsonDictionary
    {
    public:
        CSJsonDictionary();
        ~CSJsonDictionary();

    public:
        void    initWithDescription(const char *pszDescription);
        void    insertItem(const char *pszKey, int nValue);
        void    insertItem(const char *pszKey, double fValue);
        void    insertItem(const char *pszKey, const char * pszValue);
        void    insertItem(const char *pszKey, CSJsonDictionary * subDictionary);
        void    insertItem(const char *pszKey, bool bValue);
        bool    deleteItem(const char *pszKey);
        void    cleanUp();
        bool    isKeyValidate(const char *pszKey);

        int             getItemIntValue(const char *pszKey, int nDefaultValue);
        double          getItemFloatValue(const char *pszKey, double fDefaultValue);
        const char *    getItemStringValue(const char *pszKey);
        bool            getItemBoolvalue(const char *pszKey, bool bDefaultValue);
        CSJsonDictionary *   getSubDictionary(const char *pszKey);

        std::string          getDescription();

        bool    insertItemToArray(const char *pszArrayKey, int nValue);
        bool    insertItemToArray(const char *pszArrayKey, double fValue);
        bool    insertItemToArray(const char *pszArrayKey, const char * pszValue);
        bool    insertItemToArray(const char *pszArrayKey, CSJsonDictionary * subDictionary);

        int getArrayItemCount(const char *pszArrayKey);
        int getIntValueFromArray(const char *pszArrayKey, int nIndex, int nDefaultValue);
        double getFloatValueFromArray(const char *pszArrayKey, int nIndex, double fDefaultValue);
        bool getBoolValueFromArray(const char *pszArrayKey, int nIndex, bool bDefaultValue);
        const char * getStringValueFromArray(const char *pszArrayKey, int nIndex);
        CSJsonDictionary *getSubItemFromArray(const char *pszArrayKey, int nIndex);
        DicItemType getItemTypeFromArray(const char *pszArrayKey, int nIndex);

        int         getItemCount();
        DicItemType getItemType(int nIndex);
        DicItemType getItemType(const char *pszKey);
        std::vector<std::string> getAllMemberNames();

    protected:
        CSJson::Value m_cValue;

    private:
        void initWithValue(CSJson::Value& value);
        inline bool isKeyValidate(const char *pszKey, CSJson::Value& root);
        inline CSJson::Value * validateArrayItem(const char *pszArrayKey, int nIndex);
    };

}

#endif
