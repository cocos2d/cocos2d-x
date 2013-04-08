#ifndef __CCX_PROTOCOL_ANALYTICS_H__
#define __CCX_PROTOCOL_ANALYTICS_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::pair< std::string, std::string >   LogEventParamPair;
typedef std::map< std::string, std::string >    LogEventParamMap;

class ProtocolAnalytics : public PluginProtocol
{
public:

    /**
     @brief plugin initialization
     */
	virtual bool init();
    
	/**
     @brief Start a new session.
     @param appKey The identity of the application.
     */
	virtual void startSession(const char* appKey);
    
	/**
     @brief Stop a session.
     @warning This interface only worked on android
     */
	virtual void stopSession();
    
	/**
     @brief Set whether needs to output logs to console.
     @param debug if true debug mode enabled, or debug mode disabled.
     @note It must be invoked before calling startSession.
     */
	virtual void setDebugMode(bool debug);
    
    /**
     @brief Set the timeout for expiring a session.
     @param millis In milliseconds as the unit of time.
     @note It must be invoked before calling startSession.
     */
	virtual void setSessionContinueMillis(long millis);
    
    /**
     @brief log an error
     @param errorId The identity of error
     @param message Extern message for the error
     */
	virtual void logError(const char* errorId, const char* message);
    
	/**
     @brief log an event.
     @param eventId The identity of event
     @param paramMap Extern parameters of the event, use NULL if not needed.
     */
	virtual void logEvent(const char* eventId, LogEventParamMap* paramMap = NULL);
    
    /**
     @brief Track an event begin.
     @param eventId The identity of event
     */
    virtual void logTimedEventBegin(const char* eventId);
    
    /**
     @brief Track an event end.
     @param eventId The identity of event
     */
	virtual void logTimedEventEnd(const char* eventId);
    
	/**
     @brief Whether to catch uncaught exceptions to server.
     @warning This interface only worked on android.
     */
	virtual void setCaptureUncaughtException(bool enabled);

    virtual const char* getPluginVersion() { return "ProtocolAnalytics, v0.1.01 , subclass should override this interface!"; };
    virtual const char* getSDKVersion();
    virtual const char* getPluginName() = 0;

protected:
	ProtocolAnalytics();
public:
	virtual ~ProtocolAnalytics();
};

}} // namespace cocos2d { namespace plugin {


#endif /* __CCX_PROTOCOL_ANALYTICS_H__ */
