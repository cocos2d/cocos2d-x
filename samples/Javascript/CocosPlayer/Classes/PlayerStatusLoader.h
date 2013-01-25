#ifndef _PLAYERSTATUSLOADER_H_
#define _PLAYERSTATUSLOADER_H_

#include "PlayerStatus.h"

/* Forward declaration. */
class CCBReader;

class PlayerStatusLoader : public cocos2d::extension::CCLayerLoader {
public:
  CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PlayerStatusLoader, loader);

protected:
  CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PlayerStatus);
};

#endif
