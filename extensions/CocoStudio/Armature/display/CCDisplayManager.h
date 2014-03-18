/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "../utils/CCArmatureDefine.h"
#include "../display/CCDecorativeDisplay.h"
#include "../datas/CCDatas.h"

NS_CC_EXT_BEGIN

class CCBone;

/**! CCDisplayManager manages CCBone's display
 *  @js NA
 *  @lua NA
 */
class  CC_EX_DLL CCDisplayManager : public CCObject
{
public:
    static CCDisplayManager *create(CCBone *bone);

public:
    CCDisplayManager();
    ~CCDisplayManager();

    bool init(CCBone *bone);

    /**
     * Use CCBoneData to init the display list.
     * If display is a sprite, and it have texture info in the TexutreData, then use TexutreData to init the display's anchor point
     * If the display is a CCArmature, then create a new CCArmature
     */
    virtual void initDisplayList(CCBoneData *boneData);

    /**
     * Add display and use  _DisplayData init the display.
     * If index already have a display, then replace it.
     * If index is current display index, then also change display to _index
     *
     *	@param 	displayData it include the display information, like DisplayType.
     *					If you want to create a sprite display, then create a CCSpriteDisplayData param
     *
     *	@param 	index the index of the display you want to replace or add to
     *					-1 : append display from back
     */
    void addDisplay(CCDisplayData *displayData, int index);

    void addDisplay(CCNode *display, int index);

    void removeDisplay(int index);

    CCArray *getDecorativeDisplayList();

    /**
     * @deprecated please use changeDisplayWithIndex and changeDisplayWithName
     */
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByIndex(int index, bool force);
    CC_DEPRECATED_ATTRIBUTE void changeDisplayByName(const char *name, bool force);

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
    void changeDisplayWithName(const char *name, bool force);

    CCNode *getDisplayRenderNode();
    DisplayType getDisplayRenderNodeType();

    int getCurrentDisplayIndex();

    virtual void setCurrentDecorativeDisplay(CCDecorativeDisplay *decoDisplay);
    virtual CCDecorativeDisplay *getCurrentDecorativeDisplay();
    virtual CCDecorativeDisplay *getDecorativeDisplayByIndex( int index);

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
    virtual bool isVisible();

    CCSize getContentSize();
    CCRect getBoundingBox();

    CCPoint getAnchorPoint();
    CCPoint getAnchorPointInPoints();

    /**
     * Check if the position is inside the bone.
     */
    virtual bool containPoint(CCPoint &_point);

    /**
     * Check if the position is inside the bone.
     */
    virtual bool containPoint(float x, float y);

protected:
    CCArray *m_pDecoDisplayList;
    //! Display render node.
    CCNode *m_pDisplayRenderNode;
    //! Display render node type
    DisplayType m_eDisplayType;
    //! Include current display information, like contour sprite, etc.
    CCDecorativeDisplay *m_pCurrentDecoDisplay;
    //! Current display index
    int m_iDisplayIndex;

    CC_SYNTHESIZE(bool, m_bForceChangeDisplay, ForceChangeDisplay)

    //! Whether of not the bone is visible. Default is true
    bool m_bVisible;

    CCBone *m_pBone;
};

NS_CC_EXT_END

#endif /*__CCDISPLAYMANAGER_H__*/
