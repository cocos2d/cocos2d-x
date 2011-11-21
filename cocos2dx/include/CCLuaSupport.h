
#ifndef __CC_LUA_SUPPORT_
#define __CC_LUA_SUPPORT_

#include "CCObject.h"
#include "ccTypes.h"

namespace cocos2d
{
    class CCTimer;
    
    class CCSchedulerFuncEntry : public CCObject
    {
    public:
        static CCSchedulerFuncEntry* entryWithRefID(int refID, ccTime fInterval, bool bPaused);
        ~CCSchedulerFuncEntry(void);
        
        inline CCTimer* getTimer(void) {
            return m_timer;
        }
        
        inline bool isPaused(void) {
            return m_paused;
        }
        
        inline int getRefID(void) {
            return m_refID;
        }
        
        inline int getHandle(void) {
            return m_handle;
        }
        
        void markDeleted(void) {
            m_isMarkDeleted = true;
        }
        
        bool isMarkDeleted(void) {
            return m_isMarkDeleted;
        }
        
    private:
        CCSchedulerFuncEntry(void);
        bool initWithRefID(int refID, ccTime fInterval, bool bPaused);

        CCTimer*    m_timer;
        bool        m_paused;
        int         m_refID;
        int         m_handle;
        bool        m_isMarkDeleted;
    };
}

#endif // __CC_LUA_SUPPORT_
