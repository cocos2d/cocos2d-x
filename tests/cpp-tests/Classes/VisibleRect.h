#ifndef __VISIBLERECT_H__
#define __VISIBLERECT_H__

#include "cocos2d.h"

class VisibleRect
{
public:
    static cocos2d::Rect getVisibleRect();

    static cocos2d::Point left();
    static cocos2d::Point right();
    static cocos2d::Point top();
    static cocos2d::Point bottom();
    static cocos2d::Point center();
    static cocos2d::Point leftTop();
    static cocos2d::Point rightTop();
    static cocos2d::Point leftBottom();
    static cocos2d::Point rightBottom();
private:
    static void lazyInit();
    static cocos2d::Rect s_visibleRect;
};

#endif /* __VISIBLERECT_H__ */
