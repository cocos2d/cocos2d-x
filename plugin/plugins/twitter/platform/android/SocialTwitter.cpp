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
@brief initialize the developer info
@param devInfo This parameter is the info of developer, must contains key:
    		consumerkey		The consumerkey of twitter account
			consumersecret		The consumersecret of twitter account
       More: https://dev.twitter.com
@warning Must invoke this interface before other interfaces.
		 And invoked only once.
*/
void SocialTwitter::initDeveloperInfo(TDeveloperInfo devInfo)
{
	ProtocolSocial::initDeveloperInfo(devInfo);
}

/**
@brief pay for product
@param info The info of product, must contains key:
		text         The text to share
		imagePath        The full path of image to share
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
