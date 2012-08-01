#include "cocos2d.h"
#include "AppDelegate.h"

USING_NS_CC;

int main(int argc, char **argv)
{
	// create the application instance
    AppDelegate app;

	int width, height;
	const char *width_str, *height_str;
	width_str = getenv("WIDTH");
	height_str = getenv("HEIGHT");
	if (width_str && height_str)
	{
		width = atoi(width_str);
		height = atoi(height_str);
	}
	else
	{
		width = 1024;
		height = 600;
	}

	CCFileUtils::sharedFileUtils()->setResourcePath("app/native/Resources");

    CCEGLView& eglView = CCEGLView::sharedOpenGLView();
    eglView.setViewName("Test Suite");
    eglView.setFrameSize(width, height);
    // set the design resolution screen size, if you want to use Design Resolution scaled to current screen, please uncomment next line.
    eglView.setDesignResolutionSize(width/2, height/2);

    return CCApplication::sharedApplication().run();
}
