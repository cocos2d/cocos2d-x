#ifndef __ModalLayer_WP8_H__
#define __ModalLayer_WP8_H__

#include "cocos2d.h"

class ModalLayer : public cocos2d::CCLayer
{
public:
	~ModalLayer();
    virtual bool init();
    void setMessage(const char* pszMsg);
    void menuCloseCallback(CCObject* pSender);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    CREATE_FUNC(ModalLayer);

private:
	CCNode* m_frame;
};

#endif    // end of __ModalLayer_WP8_H__
