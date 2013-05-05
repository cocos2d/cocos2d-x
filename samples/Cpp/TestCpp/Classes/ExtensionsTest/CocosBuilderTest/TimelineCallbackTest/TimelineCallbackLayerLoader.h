#ifndef _TIMELINECALLBACK_TESTLAYERLOADER_H_
#define _TIMELINECALLBACK_TESTLAYERLOADER_H_

#include "TimelineCallbackTestLayer.h"

class TimelineCallbackTestLayerLoader : public cocos2d::extension::CCLayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TimelineCallbackTestLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TimelineCallbackTestLayer);
};

#endif /* _TIMELINECALLBACK_TESTLAYERLOADER_H_ */
