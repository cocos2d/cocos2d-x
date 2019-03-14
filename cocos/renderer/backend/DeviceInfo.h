#pragma once

#include <string>

#include "Macros.h"
#include "base/CCRef.h"
#include "base/CCValue.h"

/**
 * @addtogroup backend
 * @{
 */
CC_BACKEND_BEGIN

/** @class DeviceInfo
 * @brief DeviceInfo used for querying most device implementation limits
 * @since v0.99.0
 * @js NA
 */
class DeviceInfo : public Ref
{
public:
    
    /** Returns a shared instance of DeviceInfo.
     * 
     * @return An autoreleased DeviceInfo object.
     */
    static DeviceInfo *getInstance();

    /** Purge the shared instance of DeviceInfo.
     */
    static void destroyInstance();

public:
    /** Destructor
     * @js NA
     * @lua NA
     */
	virtual ~DeviceInfo() = default;

    /** Initialize method.
     *
     * @return Is true if initialize success.
     */
    virtual bool init() = 0;

	/** Returns the value of a given key as a double.
     *
     * @param key A given key.
     * @param defaultValue if not find the value, return the defaultValue.
     * @return 
     */
	const Value& getValue(const std::string& key, const Value& defaultValue = Value::Null) const;

	/** Sets a new key/value pair  in the configuration dictionary.
     *
     * @param key A given key.
     * @param value A given value.
     */
	void setValue(const std::string& key, const Value& value);

    /** Returns the Configuration info.
     *
     * @return The Configuration info.
     */
    std::string getInfo() const;

private:
    static DeviceInfo    *s_sharedDeviceInfo;
	
protected:
    int           _maxAttributes = 0;
    
	ValueMap        _valueDict;
};

CC_BACKEND_END
