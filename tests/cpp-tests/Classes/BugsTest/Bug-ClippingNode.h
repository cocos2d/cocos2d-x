#ifndef __BUG_CLIPPING_NODE_H__
#define __BUG_CLIPPING_NODE_H__

#include "BugsTest.h"

class BugClippingNodeLayer : public BugsTestBase
{
public:
    CREATE_FUNC(BugClippingNodeLayer);

    virtual bool init() override;

private:

    cocos2d::ClippingNode *_clipSprite;
    cocos2d::ClippingNode *_clipSprite3D;
};

#endif // __BUG_CLIPPING_NODE_H__
