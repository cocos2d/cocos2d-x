#include "main.h"

#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCEGLView.h"

USING_NS_CC;
int main(int argc, char **argv) {

    // create the application instance
	AppDelegate app;

	CCEGLView * pMainWnd = new CCEGLView();
	if(! pMainWnd || ! pMainWnd->Create("cocos2d: Hello World", 480, 320 ,480, 320)){
		return -1;
	}

	CCFileUtils::sharedFileUtils()->setResourcePath("../Resources/");
    return CCApplication::sharedApplication().run();
}
