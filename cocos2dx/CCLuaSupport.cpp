
#include "CCLuaSupport.h"
#include "CCArray.h"
#include "CCTimer.h"
#include "LuaEngine.h"

using namespace cocos2d;

CCSchedulerFuncEntry* CCSchedulerFuncEntry::entryWithRefID(int refID, ccTime fInterval, bool bPaused)
{
    CCSchedulerFuncEntry* entry = new CCSchedulerFuncEntry();
    entry->initWithRefID(refID, fInterval, bPaused);
    entry->autorelease();
    return entry;
}


bool CCSchedulerFuncEntry::initWithRefID(int refID, ccTime fInterval, bool bPaused)
{
    LuaEngine::sharedEngine()->retainRefID(refID);
    m_timer = new CCTimer();
    m_timer->initWithScriptFunc(refID, fInterval);
    m_timer->autorelease();
    m_timer->retain();
    m_refID = refID;
    m_paused = bPaused;
    return true;
}

CCSchedulerFuncEntry::CCSchedulerFuncEntry(void)
: m_timer(NULL)
, m_refID(0)
, m_paused(true)
, m_isMarkDeleted(false)
{
    static int handleCount = 0;
    ++handleCount;
    m_handle = handleCount;
}

CCSchedulerFuncEntry::~CCSchedulerFuncEntry(void)
{
    m_timer->release();
    LuaEngine::sharedEngine()->releaseRefID(m_refID);
    CCLOG("CCSchedulerFuncEntry::~CCSchedulerFuncEntry() - remove script entry, handle: %d, refid: %d",
          m_handle, m_refID);
}
