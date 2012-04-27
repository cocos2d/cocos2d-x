#ifndef __CCMEMLAYER_H__
#define __CCMEMLAYER_H__
#include "ControlDefine.h"
#include "cocos2d.h"
#include "NdListLoaderListener.h"

using namespace cocos2d;
namespace NdCxControl {
	class NdCxList;
class CC_DLL NdTextureWatcher :public CCObject, public CNdListLoaderListener
{
private:
	NdTextureWatcher();
public:
	virtual ~NdTextureWatcher();

	static NdTextureWatcher *sharedTextureWatcher();

	void setDisplayWatcher(bool bDisplayWatcher);	
	void fresh(void);
protected:
	void actionFresh(CCObject* object);
	void actionHide(CCObject* object);
	void hide(void);
	void dovisit(void);
	static void visit(void* pSender);
	void showTexture();
protected:
	virtual void OnLoadItem(int nCurPage);
	virtual void OnUnLoadItem(int nCurPage);
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
	NdCxList *m_pList;	
};
}// namespace
#endif