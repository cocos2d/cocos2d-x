/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __MY_USER_MANAGER_H__
#define __MY_USER_MANAGER_H__

#include "ProtocolUser.h"
#include "Configs.h"

class MyUserActionResult : public cocos2d::plugin::UserActionListener
{
public:
    virtual void onActionResult(cocos2d::plugin::ProtocolUser* pPlugin, cocos2d::plugin::UserActionResultCode code, const char* msg);
};

class MyUserManager
{
public:
	static MyUserManager* getInstance();
    static void purgeManager();

    typedef enum {
    	kNoneMode = 0,
    	kQH360,
    	kND91,
#if TEST_UC
    	kUC,
#endif
    } MyUserMode;

	void unloadPlugin();
    void loadPlugin();
    void loginByMode(MyUserMode mode);
    void logoutByMode(MyUserMode mode);

private:
    MyUserManager();
    virtual ~MyUserManager();

    static MyUserManager* s_pManager;

    cocos2d::plugin::ProtocolUser* _qh360;
    cocos2d::plugin::ProtocolUser* _nd91;
    cocos2d::plugin::ProtocolUser* _uc;
    MyUserActionResult* _retListener;
};

#endif // __MY_USER_MANAGER_H__
