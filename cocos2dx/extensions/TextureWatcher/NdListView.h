#ifndef __ND_LIST_VIEW_H__
#define __ND_LIST_VIEW_H__

#include <time.h>
#include "platform.h"
#include <vector>
#include "../cocos2dx_support/LuaEngine.h"
#include "NdListViewCell.h"

using namespace cocos2d;
namespace  NdCxControl 
{
	typedef enum  
	{
		NdListViewSlideDirNone,
		NdListViewSlideDirUp,
		NdListViewSlideDirDown,
		NdListViewSlideDirLeft,
		NdListViewSlideDirRight,
	} NdListViewSlideDir;

	typedef enum  
	{
		NdListViewStateWatting,
		NdListViewStateTrackingTouch,
		NdListViewStateEaseOut,
		NdListViewStateFix,
		NdListViewStateScroll,
	} NdListViewState;

	typedef enum 
	{
		NdListViewModeHorizontal,
		NdListViewModeVertical,
	} NdListViewMode;

	typedef struct _NdListViewProtrolData
	{
		unsigned int nNumberOfRows;
		unsigned int nRow;
		NdListViewCell *cell;
	} NdListViewProtrolData;

	class NdListViewDelegate
	{
	public :
		NdListViewDelegate(){};
		virtual ~NdListViewDelegate(){};
 
		virtual void NdListView_numberOfCells(NdListView *listView, NdListViewProtrolData *data)=0;
		virtual void NdListView_cellForRow(NdListView *listView, NdListViewProtrolData *data)=0;
		virtual void NdListView_didClickCellAtRow(NdListView *listView, NdListViewProtrolData *data)=0;
		virtual void NdListView_didScrollToRow(NdListView *listView, NdListViewProtrolData *data)=0;
	};


	class LUA_DLL NdListView : public CCLayerColor
	{
	public:
		virtual ~NdListView(void);
		NdListView(void);

		static NdListView* viewWithMode(NdListViewMode mode);
		bool initWithMode(NdListViewMode mode);

		void setDelegateName(const char* pszName);
		void selectCellAtRow(unsigned int nRow);
		void unselectCellAtRow(unsigned int nRow);
		void scrollCellToFront(unsigned int nRow, bool bAnimated);
		void scrollCellToBack(unsigned int nRow, bool bAnimated);
		void reload(void);
		void insertCellsAtRow(unsigned int nRow, unsigned int nCount);
		void deleteCellsAtRow(unsigned int nRow, unsigned int nCount);
		NdListViewCell *cellAtRow(unsigned int nRow);

		NdListViewSlideDir getSlideDir(CCPoint ptTouchBegan, CCPoint ptTouchEnd);
		inline NdListViewSlideDir getSlideDir(void) { return m_nSlideDir; }

		inline NdListViewCellSeparatorStyle getSeparatorStyle(void) { return m_nSeparatorStyle; }
		inline void setSeparatorStyle(NdListViewCellSeparatorStyle style) { m_nSeparatorStyle = style; }
		inline NdListViewMode getMode(void) { return m_nMode; }

		inline void setListViewParent(NdListView *pParent) { m_pListViewParent = pParent; }
		inline NdListView *getListViewParent(void) { return m_pListViewParent; }

		inline void setIsEnabled(bool bEnabled) { m_bIsEnabled = bEnabled; }
		inline bool getIsEnabled(void) { return m_bIsEnabled; }
	
		// un
		void setDelegate(const NdListViewDelegate *pDelegate);
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
		NdListViewCell* appendRowToBack(unsigned int nRow);
		NdListViewCell* appendRowToFront(unsigned int nRow);
		void fixFirstRow(void);
		void fixLastRow(void);
		void easeOutWithDistance(float dis);
		void clearUnvisibleRows(void);

		int rowForTouch(cocos2d::CCTouch *touch);
		bool isTouchInside(CCTouch *touch);
		bool isFullFill(void);

		void stopActionImmediately(void);

		unsigned int triggerNumberOfCells(void);
		NdListViewCell *triggerCellForRow(unsigned int nRow);
		void triggerDidClickCellAtRow(unsigned int nRow);
		void triggerDidScrollToRow(unsigned int nRow);
		bool isMenuTouch(CCTouch *touch, CCNode *parent);

	private:
		NdListViewState		m_nState;
		NdListViewMode		m_nMode;
		NdListViewSlideDir	m_nSlideDir;
		NdListViewCellSeparatorStyle	m_nSeparatorStyle;
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
		NdListViewDelegate*	m_pDelegate;
		CCLayer*			m_layerPanel;
		NdListView*			m_pListViewParent;
		int					m_nSelectedRow;
		int					m_nCurrentRow;
		bool				m_bIsEnabled;
		bool				m_bIsOnTouch;
	};
} // end of namespace NdCxControl


#endif // __ND_LIST_VIEW_H__