//
//  Widget_mac.cpp
//  Simulator
//
//

#include <string>
#include "Widget_mac.h"

using namespace std;

std::string getCurAppName(void)
{
    string appName = [[[NSProcessInfo processInfo] processName] UTF8String];
    size_t found = appName.find(" ");
    if (found!=std::string::npos)
        appName = appName.substr(0,found);
    
    return appName;
}
