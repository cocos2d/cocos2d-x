/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2012 NetGragon

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

#ifndef __CC_LIST_VIEW_H__
#define __CC_LIST_VIEW_H__


#include "platform/platform.h"
#include "CCListViewCell.h"
#include <string>
#include <vector>
#include <time.h>

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 */

class CC_DLL CCRange
{
public:
    CCRange() 
    {
        this->location = 0;
        this->length = 0;
    }

    CCRange(unsigned int loc, unsigned int len) 
    {
        this->location = loc;
        this->length = len;
    }

    static unsigned int CCMaxRange(CCRange range) 
    {
        return (range.location + range.length-1);
    }

    static bool CCLocationInRange(unsigned int loc, CCRange range)
    {
        return (loc - range.location <= range.length);
    }

    static bool CCEqualRanges(CCRange range1, CCRange range2)
    {
        return (range1.location == range2.location && range1.length == range2.length);
    }
    
    unsigned int length;
    unsigned int location;
};

#define CCRangeMake(__location__, __length__) CCRange((__location__), (__length__))

typedef enum  
{
    CCListViewSlideDirNone,
    CCListViewSlideDirUp,
    CCListViewSlideDirDown,
    CCListViewSlideDirLeft,
    CCListViewSlideDirRight,
} CCListViewSlideDir;

typedef enum  
{
    CCListViewStateWatting,
    CCListViewStateTrackingTouch,
    CCListViewStateEaseOut,
    CCListViewStateFix,
    CCListViewStateScroll,
} CCListViewState;

typedef enum 
{
    CCListViewModeHorizontal,
    CCListViewModeVertical,
} CCListViewMode;

typedef struct _CCListViewProtrolData
{
    unsigned int nNumberOfRows;
    unsigned int nRow;
    CCListViewCell *cell;
} CCListViewProtrolData;

class CC_DLL CCListViewDelegate
{
public :
    CCListViewDelegate(){};
    virtual ~CCListViewDelegate(){};

    virtual void CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data)=0;
    virtual void CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data)=0;
    virtual void CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data)=0;
    virtual void CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data)=0;
};


class CC_DLL CCListView : public CCLayerColor
{
public:
    virtual ~CCListView(void);
    CCListView(void);

    // @deprecated: This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCListView* viewWithMode(CCListViewMode mode);

    static CCListView* create(CCListViewMode mode);

    bool initWithMode(CCListViewMode mode);

    void setDelegateName(const char* pszName);
    void selectCellAtRow(unsigned int nRow);
    void unselectCellAtRow(unsigned int nRow);
    void scrollCellToFront(unsigned int nRow, bool bAnimated);
    void scrollCellToBack(unsigned int nRow, bool bAnimated);
    void reload(void);
    void insertCellsAtRow(unsigned int nRow, unsigned int nCount);
    void deleteCellsAtRow(unsigned int nRow, unsigned int nCount);
    CCListViewCell *cellAtRow(unsigned int nRow);

    CCListViewSlideDir getSlideDir(CCPoint ptTouchBegan, CCPoint ptTouchEnd);
    inline CCListViewSlideDir getSlideDir(void) { return m_nSlideDir; }

    inline CCListViewCellSeparatorStyle getSeparatorStyle(void) { return m_nSeparatorStyle; }
    inline void setSeparatorStyle(CCListViewCellSeparatorStyle style) { m_nSeparatorStyle = style; }
    inline CCListViewMode getMode(void) { return m_nMode; }

    inline void setListViewParent(CCListView *pParent) { m_pListViewParent = pParent; }
    inline CCListView *getListViewParent(void) { return m_pListViewParent; }

    inline void setEnabled(bool bEnabled) { m_bIsEnabled = bEnabled; }
    inline bool isEnabled(void) { return m_bIsEnabled; }

    // un
    void setDelegate(const CCListViewDelegate *pDelegate) { m_pDelegate = const_cast<CCListViewDelegate*>(pDelegate);}
    void finishFix(void);
    void finishScroll(void);
    void finishEaseOut(void);

public:
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

    virtual void onEnter(void);
    virtual void onExit(void);

    virtual void registerWithTouchDispatcher(void);
    virtual void visit(void);

protected:
    void displayVisibleRows(void);
    CCListViewCell* appendRowToBack(unsigned int nRow);
    CCListViewCell* appendRowToFront(unsigned int nRow);
    void fixFirstRow(void);
    void fixLastRow(void);
    void easeOutWithDistance(float dis);
    void clearUnvisibleRows(void);

    int rowForTouch(cocos2d::CCTouch *touch);
    bool isTouchInside(CCTouch *touch);
    bool isFullFill(void);

    void stopActionImmediately(void);

    unsigned int triggerNumberOfCells(void);
    CCListViewCell *triggerCellForRow(unsigned int nRow);
    void triggerDidClickCellAtRow(unsigned int nRow);
    void triggerDidScrollToRow(unsigned int nRow);
    bool isMenuTouch(CCTouch *touch, CCNode *parent);

private:
    CCListViewState       m_nState;
    CCListViewMode        m_nMode;
    CCListViewSlideDir    m_nSlideDir;
    CCListViewCellSeparatorStyle    m_nSeparatorStyle;
    unsigned int           m_nNumberOfRows;
    float                  m_fActionDuration;
    clock_t                m_timeTouchBegan;
    CCRange                m_drawedRows;            // all drawed cell
    CCRange                m_visibleRows;           // all visible cell
    CCPoint                m_ptTouchBegan;
    CCPoint                m_ptTouchEnd;
    CCPoint                m_ptPanelOffset;
    CCPoint                m_ptDestination; 
    std::string            m_strDeletegate;
    CCListViewDelegate*    m_pDelegate;
    CCLayer*               m_layerPanel;
    CCListView*            m_pListViewParent;
    int                    m_nSelectedRow;
    int                    m_nCurrentRow;
    bool                   m_bIsEnabled;
    bool                   m_bIsOnTouch;
};

// end of GUI group
/// @}

NS_CC_EXT_END


#endif // __CC_LIST_VIEW_H__