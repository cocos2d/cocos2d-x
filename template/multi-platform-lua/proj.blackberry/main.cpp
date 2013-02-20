
#include "../Classes/AppDelegate.h"
#include "cocos2d.h"


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

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(width, height);

    return CCApplication::sharedApplication()->run();
}
