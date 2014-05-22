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

#include "base/CCPlatformMacros.h"
#include <string>
#include "base/CCData.h"

NS_CC_BEGIN

/**
 * @addtogroup data_storage
 * @{
 */

/**
 * UserDefault是个微型数据库，你可以将基础数据类型存储在里面或从里面读取出来.
 * 例如:setBoolForKey("played", true)是将一个bool值存储进去,
 * 其key是"played",因此你可以通过getBoolForKey("played")从数据库中读取该bool值
 * 
 * 其支持的基础数据类型如下:
 * bool, int, float, double, string
 */
class CC_DLL UserDefault
{
public:
    // 读取数据值方法

    /**
    @brief 读取bool值,如果这个key不存在，将返回默认值
     你可以设置默认值，或不设置则为false
    * @js NA
    */
    bool    getBoolForKey(const char* pKey);
    /**
     * @js NA
     */
    bool    getBoolForKey(const char* pKey, bool defaultValue);
    /**
    @brief 读取integer值,如果这个key不存在，将返回默认值
     你可以设置默认值，或不设置则为0
    * @js NA
    */
    int     getIntegerForKey(const char* pKey);
    /**
     * @js NA
     */
    int     getIntegerForKey(const char* pKey, int defaultValue);
    /**
    @brief 读取float值,如果这个key不存在，将返回默认值
     你可以设置默认值，或不设置则为0.0f.
    * @js NA
    */
    float    getFloatForKey(const char* pKey);
    /**
     * @js NA
     */
    float    getFloatForKey(const char* pKey, float defaultValue);
    /**
    @brief 读取double值,如果这个key不存在，将返回默认值
     你可以设置默认值，或不设置则为0.0.
    * @js NA
    */
    double  getDoubleForKey(const char* pKey);
    /**
     * @js NA
     */
    double  getDoubleForKey(const char* pKey, double defaultValue);
    /**
    @brief 读取string值,如果这个key不存在，将返回默认值
    你可以设置默认值，或不设置则为"".
    * @js NA
    */
    std::string getStringForKey(const char* pKey);
    /**
     * @js NA
     */
    std::string getStringForKey(const char* pKey, const std::string & defaultValue);
    /**
     @brief 读取基于key的二进制数据(binary data),如果这个key不存在，将返回默认值
     你可以设置默认值，或不设置则为null.
     * @js NA
     * @lua NA
     */
    Data getDataForKey(const char* pKey);
    /**
     * @js NA
     * @lua NA
     */
    Data getDataForKey(const char* pKey, const Data& defaultValue);

    // 存储值方法

    /**
     @brief 存储bool值
     * @js NA
     */
    void    setBoolForKey(const char* pKey, bool value);
    /**
     @brief 存储integer值
     * @js NA
     */
    void    setIntegerForKey(const char* pKey, int value);
    /**
     @brief 存储float值
     * @js NA
     */
    void    setFloatForKey(const char* pKey, float value);
    /**
     @brief 存储double值
     * @js NA
     */
    void    setDoubleForKey(const char* pKey, double value);
    /**
     @brief 存储string值
     * @js NA
     */
    void    setStringForKey(const char* pKey, const std::string & value);
    /**
     @brief 存储二进制数据(binary data)
     * @js NA
     * @lua NA
     */
    void    setDataForKey(const char* pKey, const Data& value);
    /**
     @brief 将内容保存到xml文件
     * @js NA
     */
    void    flush();

    /** 返回singleton 
     * @js NA
     * @lua NA
     */
    static UserDefault* getInstance();
    /**
     * @js NA
     */
    static void destroyInstance();

    /**@deprecated. 使用getInstace()代替
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
