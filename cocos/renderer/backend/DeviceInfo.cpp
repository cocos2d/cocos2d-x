#include "DeviceInfo.h"

CC_BACKEND_BEGIN

DeviceInfo* DeviceInfo::s_sharedDeviceInfo = nullptr;

std::string DeviceInfo::getInfo() const
{
    // Dump
    Value forDump = Value(_valueDict);
    return forDump.getDescription();
}

void DeviceInfo::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_sharedDeviceInfo);
}

const Value& DeviceInfo::getValue(const std::string& key, const Value& defaultValue) const
{
    auto iter = _valueDict.find(key);
    if (iter != _valueDict.cend())
        return iter->second;

    return defaultValue;
}

void DeviceInfo::setValue(const std::string& key, const Value& value)
{
	_valueDict[key] = value;
}

CC_BACKEND_END
