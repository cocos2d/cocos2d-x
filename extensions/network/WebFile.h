#ifndef __CC_WEB_FILE_H__
#define __CC_WEB_FILE_H__

#include "ExtensionMacros.h"
#include "cocos2d.h"

#include <functional>

NS_CC_EXT_BEGIN

typedef std::function<void(bool)> fn_cb_t;

class WebFile : public Object {
public :
	static void get(const char * url, const char * destFile, fn_cb_t callback);

	static void clearStorage(fn_cb_t callback);
};

NS_CC_EXT_END

#endif
