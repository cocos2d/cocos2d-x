/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __SUPPORT_CCUSERDEFAULT_H__
#define __SUPPORT_CCUSERDEFAULT_H__

#include "CCPlatformMacros.h"
#include <string>
#include "CCData.h"

NS_CC_BEGIN

/**
 * @addtogroup data_storage
 * @{
 */

/**
 * UserDefault acts as a tiny database. You can save and get base type values by it.
 * For example, setBoolForKey("played", true) will add a bool value true into the database.
 * Its key is "played". You can get the value of the key by getBoolForKey("played").
 * 
 * It supports the following base types:
 * bool, int, float, double, string
 */
class CC_DLL UserDefault
{
public:
    // get value methods

    /**
    @brief Get bool value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is false.
    * @js NA
    */
    bool    getBoolForKey(const char* pKey);
    /**
     * @js NA
     */
    bool    getBoolForKey(const char* pKey, bool defaultValue);
    /**
    @brief Get integer value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is 0.
    * @js NA
    */
    int     getIntegerForKey(const char* pKey);
    /**
     * @js NA
     */
    int     getIntegerForKey(const char* pKey, int defaultValue);
    /**
    @brief Get float value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is 0.0f.
    * @js NA
    */
    float    getFloatForKey(const char* pKey);
    /**
     * @js NA
     */
    float    getFloatForKey(const char* pKey, float defaultValue);
    /**
    @brief Get double value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is 0.0.
    * @js NA
    */
    double  getDoubleForKey(const char* pKey);
    /**
     * @js NA
     */
    double  getDoubleForKey(const char* pKey, double defaultValue);
    /**
    @brief Get string value by key, if the key doesn't exist, a default value will return.
    You can set the default value, or it is "".
    * @js NA
    */
    std::string getStringForKey(const char* pKey);
    /**
     * @js NA
     */
    std::string getStringForKey(const char* pKey, const std::string & defaultValue);
    /**
     @brief Get binary data value by key, if the key doesn't exist, a default value will return.
     You can set the default value, or it is null.
     * @js NA
     * @lua NA
     */
    Data getDataForKey(const char* pKey);
    /**
     * @js NA
     * @lua NA
     */
    Data getDataForKey(const char* pKey, const Data& defaultValue);

    // set value methods

    /**
     @brief Set bool value by key.
     * @js NA
     */
    void    setBoolForKey(const char* pKey, bool value);
    /**
     @brief Set integer value by key.
     * @js NA
     */
    void    setIntegerForKey(const char* pKey, int value);
    /**
     @brief Set float value by key.
     * @js NA
     */
    void    setFloatForKey(const char* pKey, float value);
    /**
     @brief Set double value by key.
     * @js NA
     */
    void    setDoubleForKey(const char* pKey, double value);
    /**
     @brief Set string value by key.
     * @js NA
     */
    void    setStringForKey(const char* pKey, const std::string & value);
    /**
     @brief Set binary data value by key.
     * @js NA
     * @lua NA
     */
    void    setDataForKey(const char* pKey, const Data& value);
    /**
     @brief Save content to xml file
     * @js NA
     */
    void    flush();

    /** returns the singleton 
     * @js NA
     * @lua NA
     */
    static UserDefault* getInstance();
    /**
     * @js NA
     */
    static void destroyInstance();

    /** deprecated. Use getInstace() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static UserDefault* sharedUserDefault();
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedUserDefault();
    /**
     * @js NA
     */
    const static std::string& getXMLFilePath();
    /**
     * @js NA
     */
    static bool isXMLFileExist();

private:
    UserDefault();
    ~UserDefault();
    
    static bool createXMLFile();
    static void initXMLFilePath();
    
    static UserDefault* _userDefault;
    static std::string _filePath;
    static bool _isFilePathInitialized;
};

// end of data_storage group
/// @}

NS_CC_END

#endif // __SUPPORT_CCUSERDEFAULT_H__
