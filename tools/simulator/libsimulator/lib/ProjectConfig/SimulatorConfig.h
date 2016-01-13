
#ifndef __SIMULATOR_CONFIG_H_
#define __SIMULATOR_CONFIG_H_

#include <string>
#include <vector>

using namespace std;

#include "cocos2d.h"
#include "SimulatorExport.h"

#if defined(_WINDOWS)
#define DIRECTORY_SEPARATOR "\\"
#define DIRECTORY_SEPARATOR_CHAR '\\'
#else
#define DIRECTORY_SEPARATOR "/"
#define DIRECTORY_SEPARATOR_CHAR '/'
#endif

typedef struct _SimulatorScreenSize {
    string title;
    int width;
    int height;

    _SimulatorScreenSize(const string &title_, int width_, int height_)
    {
        title  = title_;
        width  = width_;
        height = height_;
    }
} SimulatorScreenSize;

typedef vector<SimulatorScreenSize> ScreenSizeArray;
typedef ScreenSizeArray::iterator ScreenSizeArrayIterator;

typedef struct _SimulatorDesignResolutionPolicy {
    string title;
    ResolutionPolicy policy;

    _SimulatorDesignResolutionPolicy (const string &title_, ResolutionPolicy policy_)
    {
        title = title_;
        policy = policy_;
    }
} SimulatorDesignResolutionPolicy;

typedef struct _SimulatorDesignContentScaleFactor {
    string title;
    float scaleFactor;

    _SimulatorDesignContentScaleFactor (const string &title_, float scaleFactor_)
    {
        title = title_;
        scaleFactor = scaleFactor_;
    }
} SimulatorDesignContentScaleFactor;

class CC_LIBSIM_DLL SimulatorConfig
{
public:
    static SimulatorConfig *getInstance();

    // predefined screen size
    int getScreenSizeCount() const;
    SimulatorScreenSize getScreenSize(int index) const;
    int checkScreenSize(const cocos2d::Size &size) const;
    void addScreenSize(const SimulatorScreenSize &screenSize);

    // predefined design resolution size
    int getDesignResolutionSizeCount() const;
    SimulatorScreenSize getDesignResolutionSize(int index) const;
    int checkDesignResolutionSize(const cocos2d::Size &size) const;
    void addDesignResolutionSize(const SimulatorScreenSize &screenSize);

    // predefined design resolution policy
    int getDesignResolutionPolicyCount() const;
    SimulatorDesignResolutionPolicy getDesignResolutionPolicy(int index) const;
    int checkDesignResolutionPolicy(ResolutionPolicy policy) const;

    // preefined design content scale factor
    int getDesignContentScaleFactorCount() const;
    SimulatorDesignContentScaleFactor getDesignContentScaleFactor(int index) const;
    int checkDesignContentScaleFactor(float scaleFactor) const;
    void addDesignContentScaleFactor(const SimulatorDesignContentScaleFactor &scaleFactor);

    // helper
    static void makeNormalizePath(string *path, const char *directorySeparator = NULL);

private:
    SimulatorConfig();

    static SimulatorConfig *_instance;

    ScreenSizeArray _screenSizeArray;
    ScreenSizeArray _designResolutionSizeArray;
    vector<SimulatorDesignResolutionPolicy> _designResolutionPolicyArray;
    vector<SimulatorDesignContentScaleFactor> _designContentScaleFactorArray;
};

#endif // __SIMULATOR_CONFIG_H_
