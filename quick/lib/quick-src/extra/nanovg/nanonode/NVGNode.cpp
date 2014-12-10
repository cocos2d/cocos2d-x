//
//  NVGNode.cpp
//  player3
//
//  Created by htl on 14/12/5.
//
//

#include "NVGNode.h"
#include "../nanovg/nanovg_gl.h"

NS_CC_EXT_BEGIN

NVGcontext* gNVGCtx = nullptr;

NVGNode::NVGNode() {
}

NVGNode::~NVGNode() {
}

NVGcontext* NVGNode::getNVGCtx() {
    if (nullptr == gNVGCtx) {
        int flag = NVG_ANTIALIAS | NVG_STENCIL_STROKES;
#if DEBUG
        flag = flag | NVG_DEBUG;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        gNVGCtx = nvgCreateGLES2(flag);
#else
        gNVGCtx = nvgCreateGL2(flag);
#endif
    }

    return gNVGCtx;
}

void NVGNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    return;
}

NS_CC_EXT_END
