#ifndef __CCMEMLAYER_H__
#define __CCMEMLAYER_H__

#include "extensions/CCListView/CCListView.h"

namespace cocos2d { class CCDictionary; }
namespace cocos2d { class CCLabelTTF; }
namespace cocos2d { class CCMenu; }
namespace cocos2d { class CCLayerColor; }


NS_CC_EXT_BEGIN

class CC_DLL CCTextureWatcher :public CCObject, public CCListViewDelegate
{
private:
	CCTextureWatcher();
public:
	virtual ~CCTextureWatcher();

	static CCTextureWatcher* sharedTextureWatcher();
    static void purgeTextureWatcher();
	void setDisplayWatcher(bool bDisplayWatcher);	
	void fresh(void);
protected:
	void actionFresh(CCObject* object);
	void actionHide(CCObject* object);
	void hide(void);
	void dovisit(void);
	static void visit(void* pSender);
protected:
	virtual void CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data);
	virtual void CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data);
	virtual void CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data);
	virtual void CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data);
private:
	bool m_bDisplayWatcher;
	bool m_bFresh;
	bool m_bHide;
	CCDictionary *m_pTextures;
	char *m_pszString;
	int m_nCurrnetPage;
	int m_nTotalPage;
	CCLabelTTF *m_labelHide;
	CCLabelTTF *m_labelPage;
	CCMenu *m_menuHide;
	CCLayerColor *m_pLayer;
	CCListView *m_pList;	
};

NS_CC_EXT_END

#endif
