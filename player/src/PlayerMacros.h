
#ifndef __PLAYER_MACROS_H_
#define __PLAYER_MACROS_H_

#define PLAYER_NS_BEGIN namespace player {
#define PLAYER_NS_END }
#define USING_PLAYER_NS using namespace player;

#define PLAYER_SAFE_DELETE(p) if (p) { delete p; p = NULL; }
#define PLAYER_DECLARE_GLOBAL_INSTANCE(className, instanceName) className instanceName = className()

#endif // __PLAYER_MACROS_H_
