
#include "network/CCNetwork.h"

NS_CC_EXTRA_BEGIN

HTTPRequest* Network::createHTTPRequest(HTTPRequestDelegate* delegate,
                                            const char* url,
                                            int method)
{
    HTTPRequest* request = HTTPRequest::createWithUrl(delegate, url, method);
    request->start();
    return request;
}

#if CC_LUA_ENGINE_ENABLED > 0
HTTPRequest* Network::createHTTPRequestLua(LUA_FUNCTION listener,
                                               const char* url,
                                               int method)
{
    HTTPRequest* request = HTTPRequest::createWithUrlLua(listener, url, method);
    request->start();
    return request;
}
#endif

NS_CC_EXTRA_END
