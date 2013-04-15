#include "AnalyticsFlurry.h"

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AnalyticsFlurry)

AnalyticsFlurry::~AnalyticsFlurry()
{
}

bool AnalyticsFlurry::init()
{
    return true;
}

void AnalyticsFlurry::setReportLocation(bool enabled)
{

}

void AnalyticsFlurry::logPageView()
{

}

void AnalyticsFlurry::setVersionName(const char* versionName)
{

}

void AnalyticsFlurry::setAge(int age)
{

}

void AnalyticsFlurry::setGender(Gender gender)
{

}

void AnalyticsFlurry::setUserId(const char* userId)
{

}

void AnalyticsFlurry::setUseHttps(bool useHttps)
{

}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId)
{

}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId, LogEventParamMap* paramMap)
{

}

}} // namespace cocos2d { namespace plugin {
