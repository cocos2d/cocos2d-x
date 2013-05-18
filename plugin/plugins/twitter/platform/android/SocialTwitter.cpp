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
#include "SocialTwitter.h"
#include "PluginUtils.h"

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(SocialTwitter)

SocialTwitter::~SocialTwitter()
{
}

/**
@brief plugin initialization
*/
bool SocialTwitter::init()
{
	return PluginUtils::initJavaPlugin(this, "org.cocos2dx.plugin.SocialTwitter");
}

/**
@brief config the developer info
@param devInfo This parameter is the info of developer, must contains key:
		TwitterKey			The consumerkey of twitter account
		TwitterSecret		The consumersecret of twitter account
		More: https://dev.twitter.com
@warning Must invoke this interface before other interfaces.
		 And invoked only once.
*/
void SocialTwitter::configDeveloperInfo(TSocialDeveloperInfo devInfo)
{
	ProtocolSocial::configDeveloperInfo(devInfo);
}

/**
@brief pay for product
@param info The info of product, must contains key:
		SharedText			The text need to share
		SharedImagePath		The full path of image file need to share (optinal)
*/
void SocialTwitter::share(TShareInfo info)
{
    ProtocolSocial::share(info);
}

const char* SocialTwitter::getSDKVersion()
{
	return ProtocolSocial::getSDKVersion();
}

void SocialTwitter::setDebugMode(bool debug)
{
	ProtocolSocial::setDebugMode(debug);
}

}} // namespace cocos2d { namespace plugin {
