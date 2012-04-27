#ifndef __ND_LIST_VIEW_CELL_H_
#define __ND_LIST_VIEW_CELL_H_

#include "ControlDefine.h"
#include "cocos2d.h"
#include <map>
#include <list>
using namespace cocos2d;

namespace NdCxControl {

#define LUA_DLL CC_DLL

class NdListView;
typedef enum
{
	NdListViewCellSeparatorStyleNone,
	NdListViewCellSeparatorStyleSingleLine,
}NdListViewCellSeparatorStyle;

class LUA_DLL NdListViewCell : public CCLayerColor
{
	public:
		NdListViewCell(void);
		virtual ~NdListViewCell(void);

		static NdListViewCell *node(void);

		void selected(void);
		void unselected(void);

		inline NdListViewCellSeparatorStyle getSeparatorStyle(void) { return m_nSeparatorStyle; }
		inline void setSeparatorStyle(NdListViewCellSeparatorStyle style) { m_nSeparatorStyle = style; }

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
		inline NdListView *getOwner(void) { return (NdListView*)(this->getParent()->getParent()); }

	private:
		NdListViewCellSeparatorStyle	m_nSeparatorStyle;
		bool			m_bIsSelected;
		ccColor4B		m_selectionColor;
		ccColor4B		m_normalColor;
		ccColor3B		m_separatorLineColor;
};

} // end of NdCxControl

#endif // __ND_LIST_VIEW_CELL_H_