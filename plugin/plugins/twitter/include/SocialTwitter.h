/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

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
#ifndef __CCX_SOCIAL_TWITTER_H__
#define __CCX_SOCIAL_TWITTER_H__

#include "ProtocolSocial.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

class SocialTwitter : public ProtocolSocial
{
	PLUGIN_REGISTER_DECL(SocialTwitter)
public:
    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
    @brief config the developer info
    @param devInfo This parameter is the info of developer, must contains key:
    		TwitterKey			The consumerkey of twitter account
    		TwitterSecret		The consumersecret of twitter account
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void configDeveloperInfo(TSocialDeveloperInfo devInfo);

    /**
    @brief pay for product
    @param info The info of product, can contains key:
            SharedText			The text need to share
            SharedImagePath		The full path of image file need to share (optinal)
    @warning For different plugin, the parameter should have other keys to pay.
             Look at the manual of plugins.
    */
    virtual void share(TShareInfo info);

    /**
	 @brief Set whether needs to output logs to console.
	 @param debug if true debug mode enabled, or debug mode disabled.
	 */
	virtual void setDebugMode(bool debug);

    virtual const char* getPluginVersion() { return "v0.1.01"; };
    virtual const char* getSDKVersion();

    virtual ~SocialTwitter();
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_SOCIAL_TWITTER_H__ */
