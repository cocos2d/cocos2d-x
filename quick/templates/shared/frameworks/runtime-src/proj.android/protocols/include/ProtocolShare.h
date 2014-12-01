/** @file ProtocolShare.h
 */
#ifndef  __CCX_PROTOCOL_SHARE_H__
#define  __CCX_PROTOCOL_SHARE_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace anysdk { namespace framework {
/// \typedef std::map<std::string, std::string> TShareDeveloperInfo
/// typedef TShareDeveloperInfo.
typedef std::map<std::string, std::string> TShareDeveloperInfo;
/// \typedef std::map<std::string, std::string> TShareInfo
/// typedef TShareInfo.
typedef std::map<std::string, std::string> TShareInfo;
/** @brief ShareResultCode enum, with inline docs */
typedef enum 
{
    kShareSuccess = 0,/**< enum value is callback of failing to sharing . */
    kShareFail,/**< enum value is callback of failing to share . */
    kShareCancel,/**< enum value is callback of canceling to share . */
    kShareNetworkError,/**< enum value is callback of network error . */
} ShareResultCode;
/**   
 *@class  ShareResultListener
 *@brief the interface of share callback  
 */
class ShareResultListener
{
public:
	/**   
	 *@brief the interface of share callback 
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onShareResult(ShareResultCode ret, const char* msg) = 0;
};
/**   
 *@class  ProtocolShare
 *@brief the interface of share  
 */
class ProtocolShare : public PluginProtocol
{
public:



    /**
    @brief share information
    @param info The info of share, contains key:
            SharedText                	The text need to share
            SharedImagePath				The full path of image file need to share (optinal)
    @warning For different plugin, the parameter should have other keys to share.
             Look at the manual of plugins.
    */
    virtual void share(TShareInfo info) = 0;

    /**
    @breif set the result listener
    @param pListener The callback object for share result
    @wraning Must invoke this interface before share
    */
    virtual void setResultListener(ShareResultListener* pListener) = 0;

};

}} // namespace anysdk { namespace framework {

#endif   /* ----- #ifndef __CCX_PROTOCOL_SHARE_H__ ----- */
