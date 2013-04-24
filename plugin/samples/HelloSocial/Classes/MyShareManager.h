#ifndef __MY_SHARE_MANAGER_H__
#define __MY_SHARE_MANAGER_H__

#include "SocialTwitter.h"

class MyShareResult : public cocos2d::plugin::ShareResultListener
{
public:
	virtual void shareResult(cocos2d::plugin::EShareResult ret, const char* msg);
};

class MyShareManager
{
public:
	static MyShareManager* sharedManager();
    static void purgeManager();

    typedef enum {
    	eNoneMode = 0,
    	eTwitter,
    } MyShareMode;

	void unloadSocialPlugin();
    void loadSocialPlugin();
    void shareByMode(cocos2d::plugin::TShareInfo info, MyShareMode mode);

private:
    MyShareManager();
    virtual ~MyShareManager();

    static MyShareManager* s_pManager;

    cocos2d::plugin::SocialTwitter* s_pTwitter;
    MyShareResult* s_pRetListener;
};

#endif // __MY_SHARE_MANAGER_H__
