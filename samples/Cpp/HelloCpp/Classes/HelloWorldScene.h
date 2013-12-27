#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
namespace PhoneDirect3DXamlAppComponent
{
	public delegate void ShowWebBroswerDelegate();
	public ref class BroswerEventHelper sealed
	{
	public:
		BroswerEventHelper(void);
		void SetShowWebBroswerDelegate(ShowWebBroswerDelegate^ delegate);
		bool ShowWebBroswer();
	private:
		property static ShowWebBroswerDelegate^ m_broswerDelegate;
	};

}
#endif

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void menuCallPageTest( CCObject* sender );
};

#endif // __HELLOWORLD_SCENE_H__
