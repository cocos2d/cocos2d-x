//
//  AppEvent.h
//  Simulator
//
//

#ifndef __Simulator__AppEvent__
#define __Simulator__AppEvent__

#include <string>
#include "cocos2d.h"

// encode / decode json
#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "SimulatorExport.h"

enum
{
    APP_EVENT_MENU = 1,
    APP_EVENT_DROP = 2
};

#define kAppEventDropName "APP.EVENT.DROP"
#define kAppEventName     "APP.EVENT"

class CC_LIBSIM_DLL AppEvent : public cocos2d::EventCustom
{
public:
    /** Constructor */
    AppEvent(const std::string& eventName, int type);
    
    /** Gets event name */
    inline const std::string& getEventName() const { return _eventName; };
    
    void setEventType(int type);
    int  getEventType();
    void setDataString(std::string data);
    std::string getDataString();
protected:
    std::string _eventName;
    std::string _dataString;
    int         _eventType;
};

#endif /* defined(__Simulator__AppEvent__) */
