#ifndef __CC_LIST_VIEW_H__
#define __CC_LIST_VIEW_H__

#include <time.h>
#include "platform.h"
#include <vector>
#include <string>
//#include "../lua/cocos2dx_support/CCLuaEngine.h"
#include "CCListViewCell.h"

NS_CC_EXT_BEGIN

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

    static bool CCEqualRanges(CCRange range1, CCRange range2)    {        return (range1.location == range2.location && range1.length == range2.length);    }
    
    unsigned int length;
    unsigned int location;
};

#define CCRangeMake(__min__, __max__) CCRange((__min__), (__max__))

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

	static CCListView* viewWithMode(CCListViewMode mode);
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

	inline void setIsEnabled(bool bEnabled) { m_bIsEnabled = bEnabled; }
	inline bool getIsEnabled(void) { return m_bIsEnabled; }

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
	CCListViewState		m_nState;
	CCListViewMode		m_nMode;
	CCListViewSlideDir	m_nSlideDir;
	CCListViewCellSeparatorStyle	m_nSeparatorStyle;
	unsigned int		m_nNumberOfRows;
	float				m_fActionDuration;
	clock_t				m_timeTouchBegan;
	CCRange				m_drawedRows;			//所有已绘制的cell
	CCRange				m_visibleRows;			//所有可见的cell
	CCPoint				m_ptTouchBegan;
	CCPoint				m_ptTouchEnd;
	CCPoint				m_ptPanelOffset;
	CCPoint				m_ptDestination; 
	std::string			m_strDeletegate;
	CCListViewDelegate*	m_pDelegate;
	CCLayer*			m_layerPanel;
	CCListView*			m_pListViewParent;
	int					m_nSelectedRow;
	int					m_nCurrentRow;
	bool				m_bIsEnabled;
	bool				m_bIsOnTouch;
};

NS_CC_EXT_END


#endif // __CC_LIST_VIEW_H__