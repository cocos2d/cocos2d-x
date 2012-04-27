#include "CCListView.h"
#include "CCListViewCell.h"
#include "cocos2d.h"

NS_CC_EXT_BEGIN

const int TOUCHBEGIN	= 1;
const int TOUCHEND		= 2;
const int TOUCHMOVING	= 3;
const int TOUCHCANCELLED= 4;


/******************************************
**************Public Functions*************
*******************************************/
CCListViewCell::CCListViewCell(void) 
	:m_nSeparatorStyle(CCListViewCellSeparatorStyleNone)
	,m_bIsSelected(false)
{
	setIsTouchEnabled(true);
	m_selectionColor = ccc4(0, 0, 255, 255);
	m_separatorLineColor = ccc3(128, 128, 128);
}

CCListViewCell::~CCListViewCell(void) 
{

}

CCListViewCell *CCListViewCell::node(void)
{
	CCListViewCell *pRet = new CCListViewCell();
	pRet->initWithColorWidthHeight(ccc4(255, 255, 255, 255), 0, 0);
 	pRet->autorelease();
	return pRet;
}

void CCListViewCell::selected(void)
{
	m_bIsSelected = true;
	CCLayerColor::setColor(ccc3(m_selectionColor.r, m_selectionColor.g, m_selectionColor.b));
	CCLayerColor::setOpacity(m_selectionColor.a);
}

void CCListViewCell::unselected(void)
{
	m_bIsSelected = false;
	CCLayerColor::setColor(ccc3(m_normalColor.r, m_normalColor.g, m_normalColor.b));
	CCLayerColor::setOpacity(m_normalColor.a);
}

/******************************************
**************Virturl Functions************
*******************************************/
bool CCListViewCell::initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
	this->m_normalColor = color;
	return CCLayerColor::initWithColor(color, width, height);
}

void CCListViewCell::draw(void)
{
	CCLayerColor::draw();
	CCSize size = this->getContentSize();
	CCListView *owner = this->getOwner();
	if (CCListViewCellSeparatorStyleSingleLine == m_nSeparatorStyle)
	{
		glLineWidth(1.0f);
		ccDrawColor4B(m_separatorLineColor.r, m_separatorLineColor.g, m_separatorLineColor.b, 255);

		if (CCListViewModeHorizontal == owner->getMode())
		{
			ccDrawLine(CCPointMake(size.width, 0), CCPointMake(size.width, size.height));
		}
		else if (CCListViewModeVertical == owner->getMode())
		{
			ccDrawLine(CCPointMake(0, 0), CCPointMake(size.width, 0));
		}
	}
}

void CCListViewCell::setColor(ccColor3B var)
{
	m_normalColor.r = var.r;
	m_normalColor.g = var.g;
	m_normalColor.b = var.b;
	CCLayerColor::setColor(var);
}

void CCListViewCell::setOpacity(GLubyte var)
{
	m_normalColor.a = var;
	CCLayerColor::setOpacity(var);
}

NS_CC_EXT_END