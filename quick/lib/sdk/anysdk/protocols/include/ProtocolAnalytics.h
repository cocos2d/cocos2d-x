/** @file ProtocolAnalytics.h
 */
#ifndef __CCX_PROTOCOL_ANALYTICS_H__
#define __CCX_PROTOCOL_ANALYTICS_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace anysdk { namespace framework {
/// \typedef std::map<std::string, std::string> LogEventParamPair
/// typedef LogEventParamPair.
typedef std::pair< std::string, std::string >   LogEventParamPair;
/// \typedef std::map<std::string, std::string> LogEventParamMap
/// typedef LogEventParamMap.
typedef std::map< std::string, std::string >    LogEventParamMap;

/**   
 *@class  ProtocolAnalytics
 *@brief the interface of Analytics
 */
class ProtocolAnalytics : public PluginProtocol
{
public:

	/**
     @brief Start a new session.
     @param appKey The identity of the application.
     */
	virtual void startSession() = 0;
    
	/**
     @brief Stop a session.
     @warning This interface only worked on android
     */
	virtual void stopSession() = 0;

    /**
     @brief Set the timeout for expiring a session.
     @param millis In milliseconds as the unit of time.
     @note It must be invoked before calling startSession.
     */
	virtual void setSessionContinueMillis(long millis) = 0;

    /**
     @brief log an error
     @param errorId The identity of error
     @param message Extern message for the error
     */
	virtual void logError(const char* errorId, const char* message) = 0;
    
	/**
     @brief log an event.
     @param eventId The identity of event
     @param paramMap Extern parameters of the event, use NULL if not needed.
     */
	virtual void logEvent(const char* eventId, LogEventParamMap* paramMap = NULL) = 0;

    /**
     @brief Track an event begin.
     @param eventId The identity of event
     */
	virtual void logTimedEventBegin(const char* eventId) = 0;

    /**
     @brief Track an event end.
     @param eventId The identity of event
     */
	virtual void logTimedEventEnd(const char* eventId) = 0;

	/**
     @brief Whether to catch uncaught exceptions to server.
     @warning This interface only worked on android.
     */
	virtual void setCaptureUncaughtException(bool enabled) = 0;
};

}} // namespace anysdk { namespace framework {


#endif /* __CCX_PROTOCOL_ANALYTICS_H__ */
