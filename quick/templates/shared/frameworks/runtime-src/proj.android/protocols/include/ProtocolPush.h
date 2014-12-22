/** @file PluginFactory.h
 */
#ifndef __CCX_PROTOCOL_PUSH_H__
#define __CCX_PROTOCOL_PUSH_H__

#include "PluginProtocol.h"
#include <map>
#include <list>
#include <string>
using namespace std;

namespace anysdk { namespace framework {
/** @brief Plugin_type enum, with inline docs */
typedef enum
{
	kPushReceiveMessage = 0,/**value is callback of Receiving Message . */


} PushActionResultCode;
class ProtocolPush;
/**   
 *@class  PushActionListener
 *@brief the interface of Push callback  
 */
class PushActionListener
{
public:
	/**   
	 *@brief the interface of Push callback 
	 *@param the adatper of plugin
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg) = 0;
};
/**   
 *  @class  ProtocolPush  
 */
class ProtocolPush : public PluginProtocol
{
public:


    /**
     *@brief start/register  Push services
     *@return void
     */
    virtual  void startPush() = 0 ;


    /**
     *@brief close Push services
     *@return void
     */
    virtual void closePush() = 0 ;


    /**
     *@brief set alias
     *@param tags
     *@return void
     */
    virtual void setAlias(string alias) = 0;

    /**
     *@brief del alias
     *@param tags
     *@return void
     */
    virtual void delAlias(string alias) = 0;

    /**
     *@brief set tag
     *@param tags
     *@return void
     */
    virtual void setTags(list<string> tags) = 0;

    /**
     *@brief delete tag
     *@param tags
     *@return void
     */
    virtual void delTags(list<string> tags) = 0;

    /**
     @brief set the result listener
     @param pListener The callback object for push result
     */
    virtual void setActionListener(PushActionListener* listener) = 0 ;

    /**
     @brief get pListener The callback object for Push result
     @return the listener
     */
    virtual  PushActionListener* getActionListener() = 0 ;



};

}} // namespace anysdk { namespace framework {

#endif /* __CCX_PROTOCOL_PUSH_H__ */
