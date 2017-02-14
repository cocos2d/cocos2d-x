/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "editor-support/cocostudio/CCArmatureDefine.h"
#include "editor-support/cocostudio/CCDecorativeDisplay.h"
#include "editor-support/cocostudio/CCDatas.h"
#include "editor-support/cocostudio/CocosStudioExport.h"

namespace cocostudio {

class Bone;

/**! DisplayManager manages Bone's display
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
     * Use BoneData to init the display list.
     * If display is a sprite, and it have texture info in the TextureData, then use TextureData to init the display's anchor point
     * If the display is a Armature, then create a new Armature
     */
    virtual void initDisplayList(BoneData *boneData);

    /**
     * Add display and use  _DisplayData init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     *
     *    @param     displayData it include the display information, like DisplayType.
     *                    If you want to create a sprite display, then create a SpriteDisplayData param
     *
     *    @param     index the index of the display you want to replace or add to
     *                    -1 : append display from back
     */
    void addDisplay(DisplayData *displayData, int index);

    void addDisplay(cocos2d::Node *display, int index);

    void removeDisplay(int index);

    const cocos2d::Vector<DecorativeDisplay*>& getDecorativeDisplayList() const;

    /*
     * @deprecated, please use changeDisplayWithIndex and changeDisplayWithName
     */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const std::string& name, bool force);
    
    /**
     * Change display by index. You can just use this method to change display in the display list.
     * The display list is just used for this bone, and it is the displays you may use in every frame.
     *
     * Note : if index is the same with prev index, the method will not effect
     *
     * @param index The index of the display you want to change
     * @param force If true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
     */
    void changeDisplayWithIndex(int index, bool force);
    void changeDisplayWithName(const std::string& name, bool force);

    cocos2d::Node *getDisplayRenderNode() const;
    DisplayType getDisplayRenderNodeType() const;

    int getCurrentDisplayIndex() const;

    virtual void setCurrentDecorativeDisplay(DecorativeDisplay *decoDisplay);
    virtual DecorativeDisplay *getCurrentDecorativeDisplay() const;
    virtual DecorativeDisplay *getDecorativeDisplayByIndex( int index) const;

    /**
     * Sets whether the display is visible
     * The default value is true, a node is default to visible
     *
     * @param visible   true if the node is visible, false if the node is hidden.
     */
    virtual void setVisible(bool visible);
    /**
     * Determines if the display is visible
     *
     * @see setVisible(bool)
     * @return true if the node is visible, false if the node is hidden.
     */
    virtual bool isVisible() const;

    cocos2d::Size getContentSize() const;
    cocos2d::Rect getBoundingBox() const;

    cocos2d::Vec2 getAnchorPoint() const;
    cocos2d::Vec2 getAnchorPointInPoints() const;

    /**
     * Check if the position is inside the bone.
     */
    virtual bool containPoint(cocos2d::Vec2 &_point);

    /**
     * Check if the position is inside the bone.
     */
    virtual bool containPoint(float x, float y);

    virtual void setForceChangeDisplay(bool force) { _forceChangeDisplay = force; }
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
