#include "ProtocolAnalytics.h"

namespace cocos2d { namespace plugin {

ProtocolAnalytics::ProtocolAnalytics()
{
}

ProtocolAnalytics::~ProtocolAnalytics()
{
}

bool ProtocolAnalytics::init()
{
    return true;
}

/**
 @brief Start a new session.
 @param appKey The identity of the application.
 */
void ProtocolAnalytics::startSession(const char* appKey)
{

}

/**
 @brief Stop a session.
 @warning This interface only worked on android
 */
void ProtocolAnalytics::stopSession()
{

}

/**
 @brief Set whether needs to output logs to console.
 @param debug if true debug mode enabled, or debug mode disabled.
 @note It must be invoked before calling startSession.
 */
void ProtocolAnalytics::setDebugMode(bool debug)
{

}

/**
 @brief Set the timeout for expiring a session.
 @param millis In milliseconds as the unit of time.
 @note It must be invoked before calling startSession.
 */
void ProtocolAnalytics::setSessionContinueMillis(long millis)
{

}

/**
 @brief log an error
 @param errorId The identity of error
 @param message Extern message for the error
 */
void ProtocolAnalytics::logError(const char* errorId, const char* message)
{

}

/**
 @brief log an event.
 @param eventId The identity of event
 @param paramMap Extern parameters of the event, use NULL if not needed.
 */
void ProtocolAnalytics::logEvent(const char* eventId, LogEventParamMap* paramMap)
{

}

/**
 @brief Track an event begin.
 @param eventId The identity of event
 */
void ProtocolAnalytics::logTimedEventBegin(const char* eventId)
{

}

/**
 @brief Track an event end.
 @param eventId The identity of event
 */
void ProtocolAnalytics::logTimedEventEnd(const char* eventId)
{

}

/**
 @brief Whether to catch uncaught exceptions to server.
 @warning This interface only worked on android.
 */
void ProtocolAnalytics::setCaptureUncaughtException(bool enabled)
{

}

const char* ProtocolAnalytics::getSDKVersion()
{
    return "Subclass should override this interface";
}

}} //namespace cocos2d { namespace plugin {
