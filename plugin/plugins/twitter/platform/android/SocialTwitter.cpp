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
