/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

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
#ifndef __SUPPORT_CCUSERDEFAULTDATA_H__
#define __SUPPORT_CCUSERDEFAULTDATA_H__

#include "base/CCUserDefault.h"
#include "base/CCValue.h"

NS_CC_BEGIN

/**
 * @addtogroup data_storage
 * @{
 */

/**
 * Delegate Load/Save ValueMap:
 */
class CC_DLL DataStoreDelegate
{
public:
    virtual bool Load(ValueMap& valueMap) = 0;
    virtual bool Save(ValueMap& valueMap) = 0;
};

/**
 * UserDefaultData acts as a tiny database. You can save and get base type values by it.
 * For example, setBoolForKey("played", true) will add a bool value true into the database.
 * Its key is "played". You can get the value of the key by getBoolForKey("played").
 * Loading xml file in the first call
 * Saving xml file on demand or in the destruction
 * 
 * It supports the following base types:
 * bool, int, float, double, string, Data
 */
class CC_DLL UserDefaultData : public UserDefault
{
public:
    /**
    * Set delegate UserDefault to UserDefaultData
    * @js NA
    */
    static void makeCurrentUserDefault();

    static void setDataStoreDelegate(DataStoreDelegate* delegate);

    // get value methods
    
    /**
     * Get bool value by key, if the key doesn't exist, will return passed default value.
     * @param key The key to get value.
     * @param defaultValue The default value to return if the key doesn't exist.
     * @js NA
     */
    virtual bool getBoolForKey(const char* key, bool defaultValue) override;
    
    /**
     * Get bool value by key, if the key doesn't exist, will return passed default value.
     * @param key The key to get value.
     * @param defaultValue The default value to return if the key doesn't exist.
     * @return Integer value of the key.
     * @js NA
     */
    virtual int getIntegerForKey(const char* key, int defaultValue) override;
    
    /**
     * Get float value by key, if the key doesn't exist, will return passed default value.
     * @param key The key to get value.
     * @param defaultValue The default value to return if the key doesn't exist.
     * @return Float value of the key.
     * @js NA
     */
    virtual float getFloatForKey(const char* key, float defaultValue) override;
    
    /**
     * Get double value by key, if the key doesn't exist, will return passed default value.
     * @param key The key to get value.
     * @param defaultValue The default value to return if the key doesn't exist.
     * @return Double value of the key.
     * @js NA
     */
    virtual double getDoubleForKey(const char* key, double defaultValue) override;
    
    /**
     * Get string value by key, if the key doesn't exist, will return passed default value.
     * @param key The key to get value.
     * @param defaultValue The default value to return if the key doesn't exist.
     * @return String value of the key.
     * @js NA
     */
    virtual std::string getStringForKey(const char* key, const std::string & defaultValue) override;
    
    /**
     * Get Data value by key, if the key doesn't exist, will return an empty Data.
     * @param key The key to get value.
     * @param defaultValue The default value to return if the key doesn't exist.
     * @return Data value of the key.
     * @js NA
     */
    virtual Data getDataForKey(const char* key, const Data& defaultValue) override;

    // set value methods

    /**
     * Set bool value by key.
     * @param key The key to set.
     * @param value A bool value to set to the key.
     * @js NA
     */
    virtual void setBoolForKey(const char* key, bool value) override;
    /**
     * Set integer value by key.
     * @param key The key to set.
     * @param value A integer value to set to the key.
     * @js NA
     */
    virtual void setIntegerForKey(const char* key, int value) override;
    /**
     * Set float value by key.
     * @param key The key to set.
     * @param value A float value to set to the key.
     * @js NA
     */
    virtual void setFloatForKey(const char* key, float value) override;
    /**
     * Set double value by key.
     * @param key The key to set.
     * @param value A double value to set to the key.
     * @js NA
     */
    virtual void setDoubleForKey(const char* key, double value) override;
    /**
     * Set string value by key.
     * @param key The key to set.
     * @param value A string value to set to the key.
     * @js NA
     */
    virtual void setStringForKey(const char* key, const std::string & value) override;
    /**
     * Set Data value by key.
     * @param key The key to set.
     * @param value A Data value to set to the key.
     * @js NA
     */
    virtual void setDataForKey(const char* key, const Data& value) override;
    /**
     * You should invoke this function to save values set by setXXXForKey().
     * @js NA
     */
    virtual void flush() override;

private:
    UserDefaultData();
    ~UserDefaultData();

    /**
    * Check first loaded.
    */
    void checkLoaded();

    /**
    * Default xml data store, xml file UserDefault.xml from FileUtils::getInstance()->getWritablePath()
    */
    DataStoreDelegate* getDefaultXmlDataStore();

    /**
    * Variables.
    */
    ValueMap _valueMap;

    /**
    * Is loaded.
    */
    bool _loaded;

    /**
    * Delegate Load/Save data.
    */
    static DataStoreDelegate* _dataStore;

    static UserDefaultData* _userDefaultData;
};

// end of data_storage group
/// @}

NS_CC_END

#endif // __SUPPORT_CCUSERDEFAULTDATA_H__
