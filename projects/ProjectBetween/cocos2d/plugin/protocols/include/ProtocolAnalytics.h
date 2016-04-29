/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
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
	ProtocolAnalytics();
	virtual ~ProtocolAnalytics();

	/**
     @brief Start a new session.
     @param appKey The identity of the application.
     */
	void startSession(const char* appKey);
    
	/**
     @brief Stop a session.
     @warning This interface only worked on android
     */
	void stopSession();

    /**
     @brief Set the timeout for expiring a session.
     @param millis In milliseconds as the unit of time.
     @note It must be invoked before calling startSession.
     */
	void setSessionContinueMillis(long millis);
    
    /**
     @brief log an error
     @param errorId The identity of error
     @param message Extern message for the error
     */
	void logError(const char* errorId, const char* message);
    
	/**
     @brief log an event.
     @param eventId The identity of event
     @param paramMap Extern parameters of the event, use NULL if not needed.
     */
	void logEvent(const char* eventId, LogEventParamMap* paramMap = NULL);
    
    /**
     @brief Track an event begin.
     @param eventId The identity of event
     */
    void logTimedEventBegin(const char* eventId);
    
    /**
     @brief Track an event end.
     @param eventId The identity of event
     */
	void logTimedEventEnd(const char* eventId);
    
	/**
     @brief Whether to catch uncaught exceptions to server.
     @warning This interface only worked on android.
     */
	void setCaptureUncaughtException(bool enabled);
};

}} // namespace cocos2d { namespace plugin {


#endif /* __CCX_PROTOCOL_ANALYTICS_H__ */
