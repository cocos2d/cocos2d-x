/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCDISPLAYMANAGER_H__
#define __CCDISPLAYMANAGER_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDecorativeDisplay.h"
#include "cocostudio/CCDatas.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

class Bone;

/**
 *  @~english DisplayManager manages Bone's display
 * @~chinese 显示管理器，管理骨头的显示。
 *  @js NA
 *  @lua NA
 */
class CC_STUDIO_DLL DisplayManager : public cocos2d::Ref
{
public:
    static DisplayManager *create(Bone *bone);

public:
    DisplayManager();
    ~DisplayManager();

    bool init(Bone *bone);

    /**
     * @~english Use BoneData to init the display list.
     * If display is a sprite, and it have texture info in the TexutreData, then use TexutreData to init the display's anchor point.
     * If the display is a Armature, then create a new Armature.
     * @~chinese 使用骨头数据来初始化显示列表。如果显示为精灵并且其在材质数据中有材质信息，
     * 那么使用材质数据初始化显示的锚点。如果显示为骨骼，那么创建一套新骨骼。
     * @param boneData @~english Bone data.
     * @~chinese 骨骼数据。
     */
    virtual void initDisplayList(BoneData *boneData);

    /**
     * @~english Add display and use  _DisplayData init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     * @~chinese 添加显示并使用_DisplayData来初始化显示。如果索引处已经有显示，则将其覆盖。
     * 如果索引为当前显示索引，则同时将显示更改为_index处显示。
     *
<<<<<<< HEAD
     *	@param 	displayData @~english it include the display information, like DisplayType.
     *					If you want to create a sprite display, then create a `SpriteDisplayData` param
     * @~chinese 显示数据，包含显示信息，例如显示种类。
     * 要创建一个精灵显示，则创建一个`SpriteDisplayData`参数。
     *
     *	@param 	index @~english the index of the display you want to replace or add to
     *					-1 : append display from back
     * @~chinese 要添加或覆盖的显示的索引。为-1时将显示添加至最后
=======
     *    @param     displayData it include the display information, like DisplayType.
     *                    If you want to create a sprite display, then create a SpriteDisplayData param
     *
     *    @param     index the index of the display you want to replace or add to
     *                    -1 : append display from back
>>>>>>> v3.7-release
     */
    void addDisplay(DisplayData *displayData, int index);

    /**
    * @~english Add node and use node to init the display.
    * If index already have a display, then replace it.
    * If index is current display index, then also change display to _index
    * @~chinese 为骨头增加节点，并使用节点来初始化显示性。
    * 如果索引处已有显示，则将其覆盖。
    * 如果索引为当前显示索引，则同时将显示更改为_index处显示。
    * @param display @~english The node to add.
    * @~chinese 要添加的节点。
    * @param index @~english The index of the display you want to replace or add to
    *          -1 : append display from back
    * @~chinese 要添加或覆盖的显示的索引。为-1时将显示添加至最后。
    */
    void addDisplay(cocos2d::Node *display, int index);

    /**
    * @~english Remove a display.
    * @~chinese 为骨头移除显示。
    * @param index @~english The index of the display you want to remove.
    * @~chinese 要移除的显示的索引。
    */
    void removeDisplay(int index);

    /**
    * @~english Get list of decorative display.
    * @~chinese 获得装饰显示列表。
    * @return @~english The list of decorative display.
    * @~chinese 装饰显示列表。
    */
    const cocos2d::Vector<DecorativeDisplay*>& getDecorativeDisplayList() const;

    /** @deprecated Use `changeDisplayWithIndex(int index, bool force)` instead */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    /** @deprecated Use `changeDisplayWithName(const std::string& name, bool force)` instead */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);
    
    /**
     * @~english Change display by index. You can just use this method to change display in the display list.
     * The display list is just used for this bone, and it is the displays you may use in every frame.
     *
     * Note : if index is the same with prev index, the method will not effect.
     *
     * @~chinese 通过索引改变显示。可以通过此方法改变显示列表中的显示。
     * 显示列表仅为当前骨头使用，是可在每帧中使用的显示。
     *
     * @param index @~english The index of the display you want to change
     * @~chinese 要改变的显示的索引。
     * @param force @~english If true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
     * @~chinese 如果为真，强制将显示改为指定的显示，或者当前的显示会被设置为在flash中每个关键帧中编辑的显示索引值。
     */
    void changeDisplayWithIndex(int index, bool force);

    /**
    * @~english Change display by name. You can just use this method to change display in the display list.
    * The display list is just used for this bone, and it is the displays you may use in every frame.
    *
    * Note : if index is the same with prev index, the method will not effect.
    *
    * @~chinese 通过名称改变显示。可以通过此方法改变显示列表中的显示。
    * 显示列表仅为当前骨头使用，是可在每帧中使用的显示。
    *
    * @param name @~english The name of the display you want to change
    * @~chinese 要改变的显示的名称。
    * @param force @~english If true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
    * @~chinese 如果为真，强制将显示改为指定的显示，或者当前的显示会被设置为在flash中每个关键帧中编辑的显示索引值。
    */
    void changeDisplayWithName(const std::string& name, bool force);

    /**
    * @~english Get display render node.
    * @~chinese 获得显示渲染节点。
    * @return @~english The display render node.
    * @~chinese 显示渲染节点。
    */
    cocos2d::Node *getDisplayRenderNode() const;
    /**
    * @~english Get type of display render node.
    * @~chinese 获得显示渲染节点类型。
    * @return @~english The type of display render node.
    * @~chinese 显示渲染节点类型。
    */
    DisplayType getDisplayRenderNodeType() const;

    /**
    * @~english Get current display index.
    * @~chinese 获得当前显示索引。
    * @return @~english Current display index.
    * @~chinese 显示当前显示索引。
    */
    int getCurrentDisplayIndex() const;

    /**
    * @~english Set current decorative display.
    * @~chinese 设置当前装饰显示。
    * @param decoDisplay @~english Current decorative display.
    * @~chinese 当前装饰显示。
    */
    virtual void setCurrentDecorativeDisplay(DecorativeDisplay *decoDisplay);
    /**
    * @~english Get current decorative display.
    * @~chinese 获取当前装饰显示。
    * @return @~english Current decorative display.
    * @~chinese 当前装饰显示。
    */
    virtual DecorativeDisplay *getCurrentDecorativeDisplay() const;
    /**
    * @~english Get current decorative display by index.
    * @~chinese 通过索引获取当前装饰显示。
    * @param index @~english Index of display.
    * @~chinese 显示的索引。
    * @return @~english Current decorative display.
    * @~chinese 当前装饰显示。
    */
    virtual DecorativeDisplay *getDecorativeDisplayByIndex(int index) const;

    /**
     * @~english Sets whether the display is visible.
     * The default value is true, a node is default to visible.
     * @~chinese 设置显示是否可见。默认和节点一样为可见。
     *
     * @param visible @~english True if the node is visible, false if the node is hidden.
     * @~chinese 节点可见时为真，否则为假。
     */
    virtual void setVisible(bool visible);
    /**
     * @~english Determines if the display is visible
     * @~chinese 检查显示是否可见。
     *
     * @see setVisible(bool)
     * @return @~english true if the node is visible, false if the node is hidden.
     * @~chinese 节点可见时为真，否则为假。
     */
    virtual bool isVisible() const;

    /**
    * @see Node:getContentSize().
    */
    cocos2d::Size getContentSize() const;
    /**
    * @see Node:getBoundingBox().
    */
    cocos2d::Rect getBoundingBox() const;

    /**
    * @see Node:getAnchorPoint().
    */
    cocos2d::Vec2 getAnchorPoint() const;
    /**
    * @see Node:getAnchorPointInPoints().
    */
    cocos2d::Vec2 getAnchorPointInPoints() const;

    /**
    * @~english Check if the position is inside the bone.
    * @~chinese 检查位置点坐标是否在骨头中。
    * @param _point @~english The point to be checked.
    * @~chinese 要检查的点。
    */
    virtual bool containPoint(cocos2d::Vec2 &_point);

    /**
     * @~english Check if the position is inside the bone.
     * @~chinese 检查位置点坐标是否在骨头中。
     * @param x @~english The x of point to be checked.
     * @~chinese 要检查的点x坐标。
     * @param y @~english The y of point to be checked.
     * @~chinese 要检查的点y坐标。
     */
    virtual bool containPoint(float x, float y);

    /**
    * @~english Set force change display.
    * @~chinese 设置是否强制改变显示。
    * @param force @~english Is force change display.
    * @~chinese 是否强制改变显示。
    */
    virtual void setForceChangeDisplay(bool force) { _forceChangeDisplay = force; }
    /**
    * @~english Get force change display.
    * @~chinese 是否强制改变显示。
    * @return @~english Is force change display.
    * @~chinese 是否强制改变显示。
    */
    virtual bool isForceChangeDisplay() const { return _forceChangeDisplay; }
protected:
    cocos2d::Vector<DecorativeDisplay*> _decoDisplayList;
    //! Display render node.
    cocos2d::Node *_displayRenderNode;
    //! Display render node type
    DisplayType _displayType;
    //! Include current display information, like contour sprite, etc.
    DecorativeDisplay *_currentDecoDisplay;
    //! Current display index
    int _displayIndex;

    bool _forceChangeDisplay;

    //! Whether of not the bone is visible. Default is true
    bool _visible;

    Bone *_bone;
};

}

#endif /*__CCDISPLAYMANAGER_H__*/
