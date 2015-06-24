/****************************************************************************
Copyright (c) 2015 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCSKELETONNODE_H__
#define  __CCSKELETONNODE_H__

#include "CCPlatformMacros.h"
#include "CCTimelineMacro.h"
#include "renderer/CCGroupCommand.h"
#include "cocostudio/CocosStudioExport.h"

#include "CCBoneNode.h"

namespace cocos2d {
    class GroupCommand;
}

NS_TIMELINE_BEGIN

class CC_STUDIO_DLL SkeletonNode : public BoneNode
{
public:
    static SkeletonNode* create();

    void setLength(float length) override;
    void setContentSize(const cocos2d::Size &size) override;

    void setAllRackShow(bool showRack);
    bool isAllRackShow() const { return _isAllRackShow; }

    cocos2d::Rect getBoundingBox() const override;
protected:
    SkeletonNode();
    virtual ~SkeletonNode();
    virtual bool init() override;

    virtual void updateVertices() override;
    virtual void updateColor() override;

    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags) override;

protected:
    bool _isAllRackShow;

private:
    cocos2d::GroupCommand  _groupCommand;

    Vec2          _squareVertices[8];
    Color4F       _squareColors[8];
    Vec3          _noMVPVertices[8];

    CC_DISALLOW_COPY_AND_ASSIGN(SkeletonNode);
};

NS_TIMELINE_END

#endif //__CCSKELETONNODE_H__
