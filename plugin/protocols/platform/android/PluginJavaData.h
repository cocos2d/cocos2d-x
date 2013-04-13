#ifndef __PLUGIN_JAVA_DATA_H__
#define __PLUGIN_JAVA_DATA_H__

#include <string>
#include <jni.h>

namespace cocos2d { namespace plugin {

typedef struct _PluginJavaData_
{
	jobject jobj;
	std::string  jclassName;
} PluginJavaData;

}} //namespace cocos2d { namespace plugin {

#endif // __PLUGIN_JAVA_DATA_H__
