#ifndef __CCX_ANALYTICS_UMENG_H__
#define __CCX_ANALYTICS_UMENG_H__

#include "ProtocolAnalytics.h"

namespace cocos2d { namespace plugin {

// Please refer to http://dev.umeng.com/doc/document_ana_android.html for the detail informations about
// how to use the interfaces of Umeng.

class AnalyticsUmeng : public ProtocolAnalytics
{
	PLUGIN_REGISTER_DECL(AnalyticsUmeng)
public:
	enum UmengReportPolicy
	{
		REALTIME = 0,
		BATCH_AT_LAUNCH = 1,
		DAILY = 4,
		WIFIONLY = 5
	};

	virtual ~AnalyticsUmeng();
    
    /**
     @par override interface of base class
     */
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
     @warning Only worked on android
     */
	virtual void setSessionContinueMillis(long millis);
    
    /**
     @brief log an error
     @param errorId The identity of error
     @param message Extern message for the error
     @warning Only worked on android
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
    
    virtual const char* getPluginVersion() { return "v0.1.01"; };
    virtual const char* getSDKVersion();
    
    /**
     @par Unique interface of Umeng
     */

	/**
     @brief Update the online configuration
     */
	void updateOnlineConfig();

	/**
     @brief Get the online configuration parameters
     */
	const char* getConfigParams(const char* key);

	/**
     @brief Set the default policy
     */
	void setDefaultReportPolicy(UmengReportPolicy policy);

	/**
     @brief Log event with a label.
	 * @note The label param is for distinguish event that with the same id. It will not be kept in the server.
	 */
	void logEventWithLabel(const char* eventId, const char* label);

	/**
     @brief Log event with duration and a label
	 * @note The label param is for distinguish event that with the same id. It will not be kept in the server.
     */
	void logEventWithDuration(const char* eventId, long duration, const char* label);

	/**
     @brief Log event with duration and a map which contains event parameters.
	 * @note The label param is for distinguish event that with the same id. It will not be kept in the server.
     */
	void logEventWithDuration(const char* eventId, long duration, LogEventParamMap* paramMap = NULL);

	/**
     @brief Start log a timed event with a label.
     */
	void logTimedEventWithLabelBegin(const char* eventId, const char* label);

	/**
     @brief Finish log a timed event with a label
     */
	void logTimedEventWithLabelEnd(const char* eventId, const char* label);

	/**
     @brief Start log a timed event with a label and a map which contains event parameters.
     */
	void logTimedKVEventBegin(const char* eventId, const char* label, LogEventParamMap* paramMap);

	/**
     @brief Finish log a timed event with a label.
     */
	void logTimedKVEventEnd(const char* eventId, const char* label);

    /**
     @par interface for ios
     */
    /**
     @brief start session with policy and channel id
     @warning On android, policy & channelId are ignored.
     */
    void startSession(const char* appKey, UmengReportPolicy policy, const char* channelId);
    void checkUpdate();
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ANALYTICS_UMENG_H__ */
