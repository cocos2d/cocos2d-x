/** @file PluginProtocol.h
 */
#ifndef __CCX_IPLUGIN_H__
#define __CCX_IPLUGIN_H__

#include "PluginParam.h"
#include <vector>

namespace anysdk { namespace framework {

/**
 * 	@class PluginProtocol
 *	@brief	The super class for all plugins.
 */
class PluginProtocol
{
public:

    /**
     *@brief set plugin name
     *@param the name of plugin
    */
	virtual void setPluginName(const char* name) = 0 ;
    /**
     *@brief get plugin name
     *@return the name of plugin
    */
	virtual const char* getPluginName() = 0 ;

    /**
     *@brief get the version of plugin
     *@return the version of plugin
    */
	virtual std::string getPluginVersion() = 0 ;
    /**
     *@brief get the version of sdk
     *@return the version of sdk
    */
	virtual std::string getSDKVersion() = 0 ;

    /**
     *@brief switch debug plug-in on/off
     *@param the value of on/off
    */
	virtual void setDebugMode(bool bDebug) = 0 ;

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return void
     */
	virtual void callFuncWithParam(const char* funcName, PluginParam* param, ...) = 0 ;
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return void
     */
	virtual void callFuncWithParam(const char* funcName, std::vector<PluginParam*> params) = 0 ;

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return string
     */
	virtual std::string callStringFuncWithParam(const char* funcName, PluginParam* param, ...) = 0 ;
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return string
     */
	virtual std::string callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params) = 0 ;

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return int
     */
	virtual int callIntFuncWithParam(const char* funcName, PluginParam* param, ...) = 0 ;
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return int
     */
	virtual int callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params) = 0 ;

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return bool
     */
	virtual bool callBoolFuncWithParam(const char* funcName, PluginParam* param, ...) = 0 ;
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return bool
     */
	virtual bool callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params) = 0 ;

    /**
     *@brief methods for reflections
     *@param function name
     *@param PluginParam* param
     *@return float
     */
	virtual float callFloatFuncWithParam(const char* funcName, PluginParam* param, ...) = 0 ;
    /**
     *@brief methods for reflections
     *@param function name
     *@param std::vector<PluginParam*> params
     *@return float
     */
	virtual float callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params) = 0 ;


};

}} //namespace anysdk { namespace framework {

#endif /* __CCX_IPLUGIN_H__ */
