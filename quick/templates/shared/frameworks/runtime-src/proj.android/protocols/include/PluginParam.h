/** @file PluginParam.h
 */
#ifndef __CCX_PLUGIN_PARAM_H__
#define __CCX_PLUGIN_PARAM_H__

#include <map>
#include <string>
/// \typedef std::map<std::string, std::string> StringMap
/// typedef YString.
typedef std::map<std::string, std::string>   StringMap;

namespace anysdk { namespace framework {

class PluginProtocol;
/**   
 *  @class  PluginParam  
 */
class PluginParam
{
public:
    /**
     @brief the default constructor of PluginParam
     */
    PluginParam();

    virtual ~PluginParam();
    /**
     @brief the constructor of PluginParam
     @param the value is Integer
     */
	PluginParam(int nValue);
    /**
     @brief the  constructor of PluginParam
     @param the value is float
     */
	PluginParam(float fValue);
    /**
     @brief the constructor of PluginParam
     @param the value is boolean
     */
	PluginParam(bool bValue);
    /**
     @brief the default constructor of PluginParam
     @param the value is char
     */
	PluginParam(const char* strValue);
    /**
     @brief the default constructor of PluginParam
     @param the value is StringMap
     */
	PluginParam(StringMap strMapValue);

	typedef enum{
		kParamTypeNull = 0,
		kParamTypeInt,
		kParamTypeFloat,
		kParamTypeBool,
		kParamTypeString,
        kParamTypeStringMap,
		kParamTypeMap,
	} ParamType;
    /**
     @brief get the ParamType of value
     */
	inline ParamType getCurrentType() {
		return _type;
	}
    /**
     @brief get the int value
     */
	inline int getIntValue() {
		return _intValue;
	}
    /**
     @brief get the float value
     */
	inline float getFloatValue() {
		return _floatValue;
	}
    /**
     @brief get the boolean value
     */
	inline bool getBoolValue() {
		return _boolValue;
	}
    /**
     @brief get the char value
     */
	inline const char* getStringValue() {
		return _strValue.c_str();
	}
    /**
     @brief get the map of  value
     */
	inline std::map<std::string, PluginParam*> getMapValue() {
		return _mapValue;
	}
    /**
     @brief get the StringMap value
     */
	inline StringMap getStrMapValue() {
        return _strMapValue;
    }

private:
	friend class PluginProtocol;
    /**
     @brief the  constructor of PluginParam
     @param the  map of value
     */
    PluginParam(std::map<std::string, PluginParam*> mapValue);

private:
	ParamType _type;

	int _intValue;
	float _floatValue;
	bool _boolValue;
	std::string _strValue;
	std::map<std::string, PluginParam*> _mapValue;
	StringMap _strMapValue;
};

}} //namespace anysdk { namespace framework {

#endif /* __CCX_PLUGIN_PARAM_H__ */
