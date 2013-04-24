#ifndef  __CXX_PROTOCOL_SOCIAL_H__
#define  __CXX_PROTOCOL_SOCIAL_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TDeveloperInfo;
typedef std::map<std::string, std::string> TShareInfo;

typedef enum 
{
    eShareSuccess = 0,
    eShareFail,
    eShareCancel,
    eShareTimeOut,
} EShareResult;

class ShareResultListener
{
public:
    virtual void shareResult(EShareResult ret, const char* msg, TShareInfo info) = 0;
};

class ProtocolSocial : public PluginProtocol
{
public:

    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
    @brief initialize the developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void initDeveloperInfo(TDeveloperInfo devInfo);

    /**
    @brief share information
    @param info The info of share, must contains key:
            text                The text of share
    @warning For different plugin, the parameter should have other keys to share.
             Look at the manual of plugins.
    */
    virtual void share(TShareInfo info);

    /**
	 @brief Set whether needs to output logs to console.
	 @param debug if true debug mode enabled, or debug mode disabled.
	 */
	virtual void setDebugMode(bool debug);

    /**
    @breif set the result listener
    @param pListener The callback object for share result
    @wraning Must invoke this interface before share
    */
    static void setResultListener(ShareResultListener* pListener);

    /**
    @brief share result callback
    */
    static void shareResult(EShareResult ret, const char* msg);

    virtual const char* getPluginVersion() { return "ProtocolSocial, v0.1.00 , subclass should override this interface!"; };
    virtual const char* getSDKVersion();
    virtual const char* getPluginName() = 0;

protected:
    ProtocolSocial();
public:
    virtual ~ProtocolSocial();

protected:
    static bool m_bSharing;
    static ShareResultListener* m_pListener;
    static TShareInfo m_curInfo;
};

}} // namespace cocos2d { namespace plugin {

#endif   /* ----- #ifndef __CXX_PROTOCOL_SOCIAL_H__ ----- */
