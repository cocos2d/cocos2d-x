#ifndef __BUG_CLIPPING_NODE_H__
#define __BUG_CLIPPING_NODE_H__

#include "BugsTest.h"

class BugClippingNodeLayer : public BugsTestBase
{
public:
    CREATE_FUNC(BugClippingNodeLayer);

    virtual bool init() override;

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

private:

    cocos2d::ClippingNode *_clipSprite;
    cocos2d::ClippingNode *_clipSprite3D;
};

#endif // __BUG_CLIPPING_NODE_H__
