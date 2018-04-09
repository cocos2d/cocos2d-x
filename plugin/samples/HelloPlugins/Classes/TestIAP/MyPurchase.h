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
#ifndef __MY_PURCHASE_H__
#define __MY_PURCHASE_H__

#include "ProtocolIAP.h"

class MyPurchaseResult : public cocos2d::plugin::PayResultListener
{
public:
	virtual void onPayResult(cocos2d::plugin::PayResultCode ret, const char* msg, cocos2d::plugin::TProductInfo info);
};

class MyPurchase
{
public:
	static MyPurchase* getInstance();
    static void purgePurchase();

    typedef enum {
    	eNoneMode = 0,
    	eGoogle,
    } MyPayMode;

	void unloadIAPPlugin();
    void loadIAPPlugin();
    void payByMode(cocos2d::plugin::TProductInfo info, MyPayMode mode);

private:
    MyPurchase();
    virtual ~MyPurchase();

    static MyPurchase* s_pPurchase;
    cocos2d::plugin::ProtocolIAP* s_pGoogle;
    MyPurchaseResult* s_pRetListener;
};

#endif // __MY_PURCHASE_H__
