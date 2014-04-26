#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"

class VisibleRect
{
public:
    static cocos2d::Rect getVisibleRect();

    static cocos2d::Vector2 left();
    static cocos2d::Vector2 right();
    static cocos2d::Vector2 top();
    static cocos2d::Vector2 bottom();
    static cocos2d::Vector2 center();
    static cocos2d::Vector2 leftTop();
    static cocos2d::Vector2 rightTop();
    static cocos2d::Vector2 leftBottom();
    static cocos2d::Vector2 rightBottom();
private:
    static void lazyInit();
    static cocos2d::Rect s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */
