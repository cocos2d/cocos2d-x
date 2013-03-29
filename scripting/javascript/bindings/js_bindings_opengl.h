#include "cocos2d.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

class GLNode : public cocos2d::CCNode {
 public:
  void draw();
};

void js_register_cocos2dx_GLNode(JSContext *cx, JSObject *global);