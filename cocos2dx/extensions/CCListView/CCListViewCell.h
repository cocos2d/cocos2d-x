#ifndef __CC_LIST_VIEW_CELL_H_
#define __CC_LIST_VIEW_CELL_H_

#include "CCControlDefine.h"
#include "CCLayer.h"

NS_CC_EXT_BEGIN

class CCListView;
typedef enum
{
	CCListViewCellSeparatorStyleNone,
	CCListViewCellSeparatorStyleSingleLine,
}CCListViewCellSeparatorStyle;

class CC_DLL CCListViewCell : public CCLayerColor
{
	public:
		CCListViewCell(void);
		virtual ~CCListViewCell(void);

		static CCListViewCell *node(void);

		void selected(void);
		void unselected(void);

		inline CCListViewCellSeparatorStyle getSeparatorStyle(void) { return m_nSeparatorStyle; }
		inline void setSeparatorStyle(CCListViewCellSeparatorStyle style) { m_nSeparatorStyle = style; }

		inline ccColor4B getSelectionColor(void) { return m_selectionColor; }
		inline void setSelectionColor(ccColor4B color) { m_selectionColor = color; }

		inline ccColor3B getSeparatorLineColor(void) { return m_separatorLineColor; }
		inline void setSeparatorLineColor(ccColor3B color) { m_separatorLineColor = color; }

	public:
		virtual bool initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
		virtual void draw(void);
		virtual void setColor(ccColor3B color);
		virtual void setOpacity(GLubyte var);

	private:
		inline CCListView *getOwner(void) { return (CCListView*)(this->getParent()->getParent()); }

	private:
		CCListViewCellSeparatorStyle	m_nSeparatorStyle;
		bool			m_bIsSelected;
		ccColor4B		m_selectionColor;
		ccColor4B		m_normalColor;
		ccColor3B		m_separatorLineColor;
};

NS_CC_EXT_END

#endif // __CC_LIST_VIEW_CELL_H_