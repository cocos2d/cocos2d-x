#ifndef __CCX_ANALYTICS_FLURRY_H__
#define __CCX_ANALYTICS_FLURRY_H__

#include "ProtocolAnalytics.h"

namespace cocos2d { namespace plugin {

class AnalyticsFlurry : public ProtocolAnalytics
{
	PLUGIN_REGISTER_DECL(AnalyticsFlurry)
public:
	enum Gender{
	    FEMALE = 0,
	    MALE = 1
	};

	virtual ~AnalyticsFlurry();

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

    virtual const char* getPluginVersion() { return "v0.1.01"; };
    virtual const char* getSDKVersion();

    /**
    @par Unique interface of Flurry
    */
    /**
    @brief Sets the age of the user at the time of this session.
    */
	void setAge(int age);

	/**
    @brief Sets the gender of the user.
    */
	void setGender(Gender gender);

	/**
	@brief Sets the userId for this session.
	*/
	void setUserId(const char* userId);

    /**
    @brief Log a page view.
    */
	void logPageView();

	/**
     @brief Set the version name of the app.
     @note It must be invoked before calling startSession.
	*/
	void setVersionName(const char* versionName);

    /**
    @par interface for android
    */
    /**
    @brief Enable the use of HTTPS communications.
    @warning This interface only worked on android
    */
	void setUseHttps(bool useHttps);
	
	/** @brief Enable or disable detailed location reporting.
	 *  @note It must be invoked before calling startSession.
     *  @warning This interface only worked on android
	 */
	void setReportLocation(bool enabled);

    /**
    @par interface for ios
    */
    /**
    @brief Log a timed event with parameters. 
    @warning The paramMap is only worked on ios.
             On android, paramMap is ignored.
    */
	void logTimedEventBegin(const char* eventId, LogEventParamMap* paramMap);
    void logTimedEventEnd(const char* eventId, LogEventParamMap* paramMap);
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_ANALYTICS_FLURRY_H__ */
