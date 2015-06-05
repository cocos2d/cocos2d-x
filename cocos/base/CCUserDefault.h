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

#include "platform/CCPlatformMacros.h"
#include <string>
#include "base/CCData.h"

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN


/**@~english
 * UserDefault acts as a tiny database. You can save and get base type values by it.
 * For example, setBoolForKey("played", true) will add a bool value true into the database.
 * Its key is "played". You can get the value of the key by getBoolForKey("played").
 * 
 * It supports the following base types:
 * bool, int, float, double, string
 * @~chinese 
 * UserDefault 是一个小型的数据管理类。你可以通过这个类保存并获得基本类型值的数据。
 * 例如：`setBoolForKey("played", true)` 将在数据库中添加一个值为 true 的布尔型数据。
 * 它的 key 是 "player"。可以通过 `getBoolForKey("player")` 获取这个数据。
 * 
 * 它支持以下基本类型:
 * Bool, int, float, double, string
 */
class CC_DLL UserDefault
{
public:
    // get value methods

    /**@~english
     * Get bool value by key, if the key doesn't exist, will return false.
     * You can set the default value, or it is false.
     * @~chinese 
     * 获取指定 key 的布尔型值，如果 key 不存在，则返回 false。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @return @~english Bool value by `key`.
     * @~chinese 关键字的布尔型值。
     * @js NA
     */
    bool    getBoolForKey(const char* key);
    
    /**@~english
     * Get bool value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 
     * 获取指定 key 的布尔型值，如果 key 不存在，则返回指定的 defaultValue。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @param defaultValue @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果关键字不存在，则返回此值。
     * @return @~english Bool value by `key`.
     * @~chinese 关键字的布尔型值。
     * @js NA
     */
    virtual bool getBoolForKey(const char* key, bool defaultValue);
    
    /**@~english
     * Get integer value by key, if the key doesn't exist, will return 0.
     * You can set the default value, or it is 0.
     * @~chinese 
     * 获取指定 key 的整型值，如果 key 不存在，则返回 0。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @return @~english Integer value of the key.
     * @~chinese 关键字的整型值。
     * @js NA
     */
    int     getIntegerForKey(const char* key);
    
    /**@~english
     * Get integer value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 
     * 获取指定 key 的整型值，如果 key 不存在，则返回指定的 defaultValue。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @param defaultValue @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果关键字不存在，则返回此值。
     * @return @~english Integer value of the key.
     * @~chinese 关键字的整型值。
     * @js NA
     */
    virtual int getIntegerForKey(const char* key, int defaultValue);
    
    /**@~english
     * Get float value by key, if the key doesn't exist, will return 0.0.
     * @~chinese 
     * 获取指定 key 的浮点值，如果 key 不存在，则返回指定的 0.0。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @return @~english Float value of the key.
     * @~chinese 关键字的浮点值。
     * @js NA
     */
    float    getFloatForKey(const char* key);
    
    /**@~english
     * Get float value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 
     * 获取指定 key 的浮点值，如果 key 不存在，则返回指定的 defaultValue。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @param defaultValue @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果关键字不存在，则返回此值。
     * @return @~english Float value of the key.
     * @~chinese 关键字的浮点值。
     * @js NA
     */
    virtual float getFloatForKey(const char* key, float defaultValue);
    
    /**@~english
     * Get double value by key, if the key doesn't exist, will return 0.0.
     * @~chinese 
     * 获取指定 key 的双精度浮点值，如果 key 不存在，则返回 0.0。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @return @~english Double value of the key.
     * @~chinese 关键字的双精度浮点值。
     * @js NA
     */
    double  getDoubleForKey(const char* key);
    
    /**@~english
     * Get double value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 
     * 获取指定 key 的双精度浮点值，如果 key 不存在，则返回指定的 defaultValue。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @param defaultValue @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果关键字不存在，则返回此值。
     * @return @~english Double value of the key.
     * @~chinese 关键字的双精度浮点值。
     * @js NA
     */
    virtual double getDoubleForKey(const char* key, double defaultValue);
    
    /**@~english
     * Get string value by key, if the key doesn't exist, will return an empty string.
     * @~chinese 
     * 获取指定 key 的字符串值，如果 key 不存在，则返回空字符串。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @return @~english String value of the key.
     * @~chinese 关键字的字符串值。
     * @js NA
     */
    std::string getStringForKey(const char* key);
    
    /**@~english
     * Get string value by key, if the key doesn't exist, will return passed default value.
     * @~chinese 
     * 获取指定 key 的字符串值，如果 key 不存在，则返回指定的 defaultValue。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @param defaultValue @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果关键字不存在，则返回此值。
     * @return @~english String value of the key.
     * @~chinese 关键字的字符串值。
     * @js NA
     */
    virtual std::string getStringForKey(const char* key, const std::string & defaultValue);
    
    /**@~english
     * Get Data value by key, if the key doesn't exist, will return an empty Data.
     * @~chinese 
     * 获取指定 key 的数据，如果 key 不存在，则返回空的数据。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @return @~english Data value of the key.
     * @~chinese `Data` 数据对象。
     * @js NA
     */
    Data getDataForKey(const char* key);
    
    /**@~english
     * Get Data value by key, if the key doesn't exist, will return an empty Data.
     * @~chinese 
     * 获取指定 key 的数据，如果 key 不存在，则返回指定的默认值。
     * @param key @~english The key to get value.
     * @~chinese 需要获取的关键字。
     * @param defaultValue @~english The default value to return if the key doesn't exist.
     * @~chinese 返回的默认值。如果关键字不存在，则返回此值。
     * @return @~english Data value of the key.
     * @~chinese `Data` 数据对象。
     * @js NA
     */
    virtual Data getDataForKey(const char* key, const Data& defaultValue);

    // set value methods

    /**@~english
     * Set bool value by key.
     * @~chinese 
     * 为关键字设置布尔型值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的关键字。
     * @param value @~english A bool value to set to the key.
     * @~chinese 需要设置的值。
     * @js NA
     */
    virtual void setBoolForKey(const char* key, bool value);
    /**@~english
     * Set integer value by key.
     * @~chinese 
     * 为关键字设置整型值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的关键字。
     * @param value @~english A integer value to set to the key.
     * @~chinese 需要设置的值。
     * @js NA
     */
    virtual void setIntegerForKey(const char* key, int value);
    /**@~english
     * Set float value by key.
     * @~chinese 
     * 为关键字设置浮点值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的关键字。
     * @param value @~english A float value to set to the key.
     * @~chinese 需要设置的值。
     * @js NA
     */
    virtual void setFloatForKey(const char* key, float value);
    /**@~english
     * Set double value by key.
     * @~chinese 
     * 为关键字设置双精度浮点值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的关键字。
     * @param value @~english A double value to set to the key.
     * @~chinese 需要设置的值。
     * @js NA
     */
    virtual void setDoubleForKey(const char* key, double value);
    /**@~english
     * Set string value by key.
     * @~chinese 
     * 为关键字设置字符串值。
     * @param key @~english The key to set.
     * @~chinese 需要设置的关键字。
     * @param value @~english A string value to set to the key.
     * @~chinese 需要设置的值。
     * @js NA
     */
    virtual void setStringForKey(const char* key, const std::string & value);
    /**@~english
     * Set Data value by key.
     * @~chinese 
     * 为关键字设置 Data 数据。
     * @param key @~english The key to set.
     * @~chinese 需要设置的关键字。
     * @param value @~english A Data value to set to the key.
     * @~chinese 需要设置的值。
     * @js NA
     */
    virtual void setDataForKey(const char* key, const Data& value);
    /**@~english
     * You should invoke this function to save values set by setXXXForKey().
     * @~chinese 
     * 此方法将 setXXXForKey() 设置的数据保存到文件中。
     * @js NA
     */
    virtual void flush();

    /** @~english Returns the singleton.
     * @~chinese 返回 UserDefault 单例对象。
     * @js NA
     * @lua NA
     */
    static UserDefault* getInstance();
    /**
     * @js NA
     */
    static void destroyInstance();

    /**@~english
     * You can inherit from platform dependent implementation of UserDefault, such as UserDefaultAndroid,
     * and use this function to set delegate, then UserDefault will invoke delegate's implementation.
     * For example, your store native data base or other format store.
     *
     * If you don't want to system default implementation after setting delegate, you can just pass nullptr
     * to this function.
     *
     * @~chinese 
     * 你可以通过继承 UserDefault 来实现自定义的数据管理类，比如：UserDefaultAndroid,
     * 使用这个函数来设置代理对象，然后 UserDefault 将调用代理对象的实现。
     * 例如：使用本地化的数据库或者数据格式来存储与读取数据。
     * 
     * 如果在设置代理对象之后，想要不再使用代理对象。可以通过调用 `setDelegate(nullptr)` 来实现。
     * 
    * @warm @~english It will delete previous delegate
     * @~chinese 这个函数将删除之前的代理对象。
    */
    static void setDelegate(UserDefault *delegate);

    /** @deprecated Use getInstace() instead.
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static UserDefault* sharedUserDefault();
    /**@deprecated Use destroyInstance() instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedUserDefault();
    /** @~english All supported platforms other iOS & Android use xml file to save values. This function is return the file path of the xml path.
     * @~chinese 除了 iOS 和 Android 之外的所有支持的平台都使用 xml 文件保存数据。这个函数返回 xml 文件的路径。
     * @js NA
     */
    static const std::string& getXMLFilePath();
    /** @~english All supported platforms other iOS & Android and CC_PLATFORM_WINRT use xml file to save values. This function checks whether the xml file exists or not.
     * @~chinese 除了 iOS 和 Android 之外的所有支持的平台都使用 xml 文件保存数据。该函数检查 xml 文件是否存在。
     * @return @~english True if the xml file exists, flase if not.
     * @~chinese 如果 xml 文件存在则返回 true；否则返回 false。
     * @js NA
     */
    static bool isXMLFileExist();

protected:
    UserDefault();
    virtual ~UserDefault();
    
private:
    
    static bool createXMLFile();
    static void initXMLFilePath();
    
    static UserDefault* _userDefault;
    static std::string _filePath;
    static bool _isFilePathInitialized;
};


NS_CC_END
// end of base group
/// @}

#endif // __SUPPORT_CCUSERDEFAULT_H__
