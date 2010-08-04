#ifndef _HelloWorld_H_
#define _HelloWorld_H_

#include "CCLayer.h"
#include "HelloSprite.h"

using namespace cocos2d;

class HelloWorld : public CCLayer
{
public:
    HelloWorld();
    virtual ~HelloWorld();

private:
    HelloSprite * m_pHSprite;
};

#endif
