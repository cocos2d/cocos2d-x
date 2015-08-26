/* cocos2d for iPhone: http://www.cocos2d-iphone.org
 * cocos2d-x: http://www.cocos2d-x.org
 *
 * Copyright (c) 2012 Pierre-David Bélanger
 * Copyright (c) 2012 cocos2d-x.org
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

#ifndef __MISCNODE_CCCLIPPING_RECTANGLE_NODE_H__
#define __MISCNODE_CCCLIPPING_RECTANGLE_NODE_H__

#include "2d/CCNode.h"
#include "renderer/CCCustomCommand.h"
#include "platform/CCGL.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

/**
@brief @~english Clipping Rectangle Node.
 * @~chinese 裁剪矩形节点。
@details @~english A node that clipped with specified rectangle.
 * @~chinese 一个使用指定矩形裁剪的节点。
@js NA
*/
class CC_DLL ClippingRectangleNode : public Node
{    
public:
    /**
    @brief @~english Create node with specified clipping region.
     * @~chinese 创建一个指定裁剪区域的节点。
    @param clippingRegion @~english Specify the clipping rectangle.
     * @~chinese 指定裁剪矩形。
    @return @~english If the creation success, return a pointer of ClippingRectangleNode; otherwise return nil.
     * @~chinese 如果创建成功,返回一个指向ClippingRectangleNode的指针;否则返回空。
    */
    static ClippingRectangleNode* create(const Rect& clippingRegion);
    /**
    @brief @~english Create a clipping rectangle node.
     * @~chinese 创建一个裁剪矩形节点。
    @return @~english If the creation success, return a pointer of ClippingRectangleNode; otherwise return nil.
     * @~chinese 如果创建成功,返回一个指向ClippingRectangleNode的指针;否则返回空。
    */
    static ClippingRectangleNode* create();
    
    /**
    @brief @~english Get the clipping rectangle.
     * @~chinese 获取裁剪矩形。
    @return @~english The clipping rectangle.
     * @~chinese 裁剪矩形。
    */
    const Rect& getClippingRegion() const {
        return _clippingRegion;
    }
    /**
    @brief @~english Set the clipping rectangle. The rectangle is base on screen coordinate, so ClippingRectangleNode's region doesn't support any transforms, such as setScale, setRotate and so on.
     * @~chinese 设置裁剪矩形。裁剪矩形是基于屏幕坐标系的，所以它不支持任何仿射变换，比如缩放或旋转。
    @param clippingRegion @~english Specify the clipping rectangle.
     * @~chinese 指定的裁剪矩形。
    */
    void setClippingRegion(const Rect& clippingRegion);
    
    /**
    @brief @~english Get whether the clipping is enabled or not.
     * @~chinese 获取是否启用了裁剪。
    @return @~english Whether the clipping is enabled or not. Default is true.
     * @~chinese 裁剪是否开启，默认是开启的。
    */
    const bool isClippingEnabled() const {
        return _clippingEnabled;
    }

    /**
    @brief @~english Enable/Disable the clipping.
     * @~chinese 启用/禁用裁剪。
    @param enabled @~english Pass true to enable clipping. Pass false to disable clipping.
     * @~chinese true为开启裁剪，false为关闭裁剪。
    */
    void setClippingEnabled(bool enabled) {
        _clippingEnabled = enabled;
    }

    //virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

protected:
    ClippingRectangleNode()
    : _clippingEnabled(true)
    {
    }
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    
    Rect _clippingRegion;
    bool _clippingEnabled;
    
    CustomCommand _beforeVisitCmdScissor;
    CustomCommand _afterVisitCmdScissor;
};

// end of _2d group
/// @}

NS_CC_END

#endif

