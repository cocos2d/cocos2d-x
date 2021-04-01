/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 * cocos2d-x: http://www.cocos2d-x.org
 *
 * Copyright (c) 2012 Pierre-David Bélanger
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#pragma once

#include "2d/CCNode.h"
#include "renderer/CCCallbackCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

/**
@brief Clipping Rectangle Node.
@details A node that clipped with specified rectangle.
 The region of ClippingRectangleNode doesn't support any transform except scale.
@js NA
*/
class CC_DLL ClippingRectangleNode : public Node
{    
public:
    /**
    @brief Create node with specified clipping region.
    @param clippingRegion Specify the clipping rectangle.
    @return If the creation success, return a pointer of ClippingRectangleNode; otherwise return nil.
    */
    static ClippingRectangleNode* create(const Rect& clippingRegion);
    /**
    @brief Create a clipping rectangle node.
    @return If the creation success, return a pointer of ClippingRectangleNode; otherwise return nil.
    */
    static ClippingRectangleNode* create();
    
    /**
    @brief Get the clipping rectangle.
    @return The clipping rectangle.
    */
    const Rect& getClippingRegion() const {
        return _clippingRegion;
    }
    /**
    @brief Set the clipping rectangle.
    @param clippingRegion Specify the clipping rectangle.
    */
    void setClippingRegion(const Rect& clippingRegion);
    
    /**
    @brief Get whether the clipping is enabled or not.
    @return Whether the clipping is enabled or not. Default is true.
    */
    bool isClippingEnabled() const {
        return _clippingEnabled;
    }

    /**
    @brief Enable/Disable the clipping.
    @param enabled Pass true to enable clipping. Pass false to disable clipping.
    */
    void setClippingEnabled(bool enabled) {
        _clippingEnabled = enabled;
    }

    //virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

protected:
    ClippingRectangleNode() = default;
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    
    Rect _clippingRegion;
    bool _clippingEnabled = true;

    bool _oldScissorTest = false;
    
    CallbackCommand _beforeVisitCmdScissor;
    CallbackCommand _afterVisitCmdScissor;
};

// end of _2d group
/// @}

NS_CC_END
