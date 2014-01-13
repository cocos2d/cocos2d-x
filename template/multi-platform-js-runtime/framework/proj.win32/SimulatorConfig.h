#ifndef __SIMULATOR_CONFIG_H_
#define __SIMULATOR_CONFIG_H_

#include <string>
#include <vector>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;


// SimulatorConfig
typedef struct _SimulatorScreenSize {
    string title;
    int width;
    int height;

    _SimulatorScreenSize(const string title_, int width_, int height_)
    {
        title  = title_;
        width  = width_;
        height = height_;
    }
} SimulatorScreenSize;

typedef vector<SimulatorScreenSize> ScreenSizeArray;
typedef ScreenSizeArray::iterator ScreenSizeArrayIterator;

class SimulatorConfig
{
public:
    static SimulatorConfig *getInstance();
	void createSimulator(const char* viewName, float width, float height);
    // predefined screen size
    int getScreenSizeCount(void);
    const SimulatorScreenSize getScreenSize(int index);
    int checkScreenSize();
	void onViewChangeOrientation(int viewMenuID);
	void onViewChangeFrameSize(int viewMenuID);
	void onHelpAbout();

private:
    SimulatorConfig(void);
	void createViewMenu();
	
	void updateMenu();
	void updateView();

    static SimulatorConfig *s_sharedInstance;
    ScreenSizeArray m_screenSizeArray;
	HWND m_hWnd;
	bool isLandscape;
	CCSize m_screenSize;
	EGLView m_eglView;
};

#endif /* __PROJECT_CONFIG_H_ */
