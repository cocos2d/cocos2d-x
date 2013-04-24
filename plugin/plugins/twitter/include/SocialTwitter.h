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
    @brief initialize the developer info
    @param devInfo This parameter is the info of developer, must contains key:
    		TwitterKey			The consumerkey of twitter account
    		TwitterSecret		The consumersecret of twitter account
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void initDeveloperInfo(TSocialDevInfo devInfo);

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
