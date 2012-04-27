
#include "NdListView.h"
#include "NdListViewCell.h"


const int TOUCHBEGIN	= 1;
const int TOUCHEND		= 2;
const int TOUCHMOVING	= 3;
const int TOUCHCANCELLED= 4;

namespace NdCxControl 
{
/******************************************
**************Public Functions*************
*******************************************/
NdListViewCell::NdListViewCell(void) 
	:m_nSeparatorStyle(NdListViewCellSeparatorStyleNone)
	,m_bIsSelected(false)
{
	setIsTouchEnabled(true);
	m_selectionColor = ccc4(0, 0, 255, 255);
	m_separatorLineColor = ccc3(128, 128, 128);
}

NdListViewCell::~NdListViewCell(void) 
{

}

NdListViewCell *NdListViewCell::node(void)
{
	NdListViewCell *pRet = new NdListViewCell();
	pRet->initWithColorWidthHeight(ccc4(255, 255, 255, 255), 0, 0);
 	pRet->autorelease();
	return pRet;
}

void NdListViewCell::selected(void)
{
	m_bIsSelected = true;
	CCLayerColor::setColor(ccc3(m_selectionColor.r, m_selectionColor.g, m_selectionColor.b));
	CCLayerColor::setOpacity(m_selectionColor.a);
}

void NdListViewCell::unselected(void)
{
	m_bIsSelected = false;
	CCLayerColor::setColor(ccc3(m_normalColor.r, m_normalColor.g, m_normalColor.b));
	CCLayerColor::setOpacity(m_normalColor.a);
}

/******************************************
**************Virturl Functions************
*******************************************/
bool NdListViewCell::initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
	this->m_normalColor = color;
	return CCLayerColor::initWithColorWidthHeight(color, width, height);
}

void NdListViewCell::draw(void)
{
	CCLayerColor::draw();
	CCSize size = this->getContentSize();
	NdListView *owner = this->getOwner();
	if (NdListViewCellSeparatorStyleSingleLine == m_nSeparatorStyle)
	{
		glLineWidth(1.0f);
		glColor4ub(m_separatorLineColor.r, m_separatorLineColor.g, m_separatorLineColor.b, 255);

		if (NdListViewModeHorizontal == owner->getMode())
		{
			ccDrawLine(CCPointMake(size.width, 0), CCPointMake(size.width, size.height));
		}
		else if (NdListViewModeVertical == owner->getMode())
		{
			ccDrawLine(CCPointMake(0, 0), CCPointMake(size.width, 0));
		}
	}
}

void NdListViewCell::setColor(ccColor3B var)
{
	m_normalColor.r = var.r;
	m_normalColor.g = var.g;
	m_normalColor.b = var.b;
	CCLayerColor::setColor(var);
}

void NdListViewCell::setOpacity(GLubyte var)
{
	m_normalColor.a = var;
	CCLayerColor::setOpacity(var);
}

} // end of namespace NdCxControl