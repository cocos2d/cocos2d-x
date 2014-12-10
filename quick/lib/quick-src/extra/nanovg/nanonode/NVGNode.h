//
//  NVGNode.h
//  player3
//
//  Created by htl on 14/12/5.
//
//

#ifndef __NVGNode__
#define __NVGNode__

#include "cocos2d.h"
#include "ExtensionMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#define NANOVG_GLES2_IMPLEMENTATION
#else
#define NANOVG_GL2_IMPLEMENTATION
#endif

#include "../nanovg/nanovg.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

class NVGNode : public Node {

public:
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;


CC_CONSTRUCTOR_ACCESS:
    NVGNode();
    ~NVGNode();

protected:
    
    NVGcontext* getNVGCtx();

};

NS_CC_EXT_END

#endif /* defined(__NVGNode__) */
