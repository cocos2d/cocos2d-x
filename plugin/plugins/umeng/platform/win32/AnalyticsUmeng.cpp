#include "AnalyticsUmeng.h"

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AnalyticsUmeng)

AnalyticsUmeng::~AnalyticsUmeng()
{
}

bool AnalyticsUmeng::init()
{
    return true;
}

void AnalyticsUmeng::updateOnlineConfig()
{

}

const char* AnalyticsUmeng::getConfigParams(const char* key)
{
    return "";
}

void AnalyticsUmeng::setDefaultReportPolicy(ReportPolicy ePolicy)
{

}

void AnalyticsUmeng::logEventWithLabel(const char* eventId, const char* label)
{

}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, const char* label)
{

}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, LogEventParamMap* paramMap /* = NULL */)
{

}

void AnalyticsUmeng::logTimedEventWithLabelBegin(const char* eventId, const char* label)
{

}

void AnalyticsUmeng::logTimedEventWithLabelEnd(const char* eventId, const char* label)
{

}

void AnalyticsUmeng::logTimedKVEventBegin(const char* eventId, const char* label, LogEventParamMap* paramMap)
{

}

void AnalyticsUmeng::logTimedKVEventEnd(const char* eventId, const char* label)
{

}


}} // namespace cocos2d { namespace plugin {
