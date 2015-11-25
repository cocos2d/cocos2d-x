//
//  Widget_mac.mm
//  libsimulator_studio
//
//  Created by Norman on 11/20/15.
//  Copyright (c) 2015 cocos. All rights reserved.
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
