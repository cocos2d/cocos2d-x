#ifndef _HelloWorld_H_
#define _HelloWorld_H_

#include "CCLayer.h"
#include "HelloSprite.h"

class HelloWorld : public CCLayer
{
public:
    HelloWorld();
    ~HelloWorld();

private:
    HelloSprite * m_pHSprite;
};

#endif
