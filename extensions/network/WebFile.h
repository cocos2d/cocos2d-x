#ifndef __CC_WEB_FILE_H__
#define __CC_WEB_FILE_H__

#include "ExtensionMacros.h"
#include "cocos2d.h"

#include <functional>

NS_CC_EXT_BEGIN

class WebFile : public Object {
public :
	static void get( const char * url, const char * destFile, std::function<void(bool)> callback );

	static void clearStorage(std::function<void(bool)> callback);
};

NS_CC_EXT_END

#endif
