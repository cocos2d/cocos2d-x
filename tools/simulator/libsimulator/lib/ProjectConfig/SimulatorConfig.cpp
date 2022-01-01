/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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


#include "SimulatorConfig.h"
#include <sstream>

SimulatorConfig *SimulatorConfig::_instance = NULL;

SimulatorConfig *SimulatorConfig::getInstance()
{
    if (!_instance)
    {
        _instance = new SimulatorConfig();
    }
    return _instance;
}

SimulatorConfig::SimulatorConfig()
{
    _screenSizeArray.push_back(SimulatorScreenSize("iPhone 3Gs (320x480)", 320, 480));
    _screenSizeArray.push_back(SimulatorScreenSize("iPhone 4 (640x960)", 640, 960));
    _screenSizeArray.push_back(SimulatorScreenSize("iPhone 5 (640x1136)", 640, 1136));
    _screenSizeArray.push_back(SimulatorScreenSize("iPhone 6 (750x1334)", 750, 1334));
    _screenSizeArray.push_back(SimulatorScreenSize("iPhone 6Plus (1242x2208)", 1242, 2208));
    _screenSizeArray.push_back(SimulatorScreenSize("iPad (768x1024)", 768, 1024));
    _screenSizeArray.push_back(SimulatorScreenSize("iPad Retina (1536x2048)", 1536, 2048));
    _screenSizeArray.push_back(SimulatorScreenSize("Android (480x800)", 480, 800));
    _screenSizeArray.push_back(SimulatorScreenSize("Android (480x854)", 480, 854));
    _screenSizeArray.push_back(SimulatorScreenSize("Android (540x960)", 540, 960));
    _screenSizeArray.push_back(SimulatorScreenSize("Android (600x1024)", 600, 1024));
    _screenSizeArray.push_back(SimulatorScreenSize("Android (720x1280)", 720, 1280));
    _screenSizeArray.push_back(SimulatorScreenSize("Android (800x1280)", 800, 1280));
    _screenSizeArray.push_back(SimulatorScreenSize("Android (1080x1920)", 1080, 1920));

    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (320x480)", 320, 480));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (640x960)", 640, 960));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (640x1136)", 640, 1136));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (750x1334)", 750, 1334));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (1242x2208)", 1242, 2208));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (768x1024)", 768, 1024));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (1536x2048)", 1536, 2048));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (480x800)", 480, 800));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (480x854)", 480, 854));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (540x960)", 540, 960));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (600x1024)", 600, 1024));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (720x1280)", 720, 1280));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (800x1280)", 800, 1280));
    _designResolutionSizeArray.push_back(SimulatorScreenSize("Design Resolution (1080x1920)", 1080, 1920));

    _designResolutionPolicyArray.push_back(SimulatorDesignResolutionPolicy("Resolution Policy (EXACT_FIT)", ResolutionPolicy::EXACT_FIT));
    _designResolutionPolicyArray.push_back(SimulatorDesignResolutionPolicy("Resolution Policy (NO_BORDER)", ResolutionPolicy::NO_BORDER));
    _designResolutionPolicyArray.push_back(SimulatorDesignResolutionPolicy("Resolution Policy (SHOW_ALL)", ResolutionPolicy::SHOW_ALL));
    _designResolutionPolicyArray.push_back(SimulatorDesignResolutionPolicy("Resolution Policy (FIXED_HEIGHT)", ResolutionPolicy::FIXED_HEIGHT));
    _designResolutionPolicyArray.push_back(SimulatorDesignResolutionPolicy("Resolution Policy (FIXED_WIDTH)", ResolutionPolicy::FIXED_WIDTH));

    _designContentScaleFactorArray.push_back(SimulatorDesignContentScaleFactor("Content Scale Factor (1.0)", 1.0f));
    _designContentScaleFactorArray.push_back(SimulatorDesignContentScaleFactor("Content Scale Factor (1.25)", 1.25f));
    _designContentScaleFactorArray.push_back(SimulatorDesignContentScaleFactor("Content Scale Factor (1.5)", 1.5f));
    _designContentScaleFactorArray.push_back(SimulatorDesignContentScaleFactor("Content Scale Factor (1.75)", 1.75f));
    _designContentScaleFactorArray.push_back(SimulatorDesignContentScaleFactor("Content Scale Factor (2.0)", 2.0f));
}

int SimulatorConfig::getScreenSizeCount() const
{
    return (int)_screenSizeArray.size();
}

SimulatorScreenSize SimulatorConfig::getScreenSize(int index) const
{
    return _screenSizeArray.at(index);
}

int SimulatorConfig::checkScreenSize(const cocos2d::Size &size) const
{
    int width = size.width;
    int height = size.height;

    if (width > height)
    {
        int w = width;
        width = height;
        height = w;
    }

    int count = (int)_screenSizeArray.size();
    for (int i = 0; i < count; ++i)
    {
        const SimulatorScreenSize &size = _screenSizeArray[i];
        if (size.width == width && size.height == height)
        {
            return i;
        }
    }

    return -1;
}

void SimulatorConfig::addScreenSize(const SimulatorScreenSize &screenSize)
{
    _screenSizeArray.push_back(screenSize);
}

int SimulatorConfig::getDesignResolutionSizeCount() const
{
    return (int)_designResolutionSizeArray.size();
}

SimulatorScreenSize SimulatorConfig::getDesignResolutionSize(int index) const
{
    return _designResolutionSizeArray.at(index);
}

int SimulatorConfig::checkDesignResolutionSize(const cocos2d::Size &size) const
{
    int width = size.width;
    int height = size.height;

    if (width > height)
    {
        int w = width;
        width = height;
        height = w;
    }

    int count = (int)_designResolutionSizeArray.size();
    for (int i = 0; i < count; ++i)
    {
        const SimulatorScreenSize &size = _designResolutionSizeArray[i];
        if (size.width == width && size.height == height)
        {
            return i;
        }
    }

    return -1;
}

void SimulatorConfig::addDesignResolutionSize(const SimulatorScreenSize &screenSize)
{
    _designResolutionSizeArray.push_back(screenSize);
}

int SimulatorConfig::getDesignResolutionPolicyCount() const
{
    return (int)_designResolutionPolicyArray.size();
}

SimulatorDesignResolutionPolicy SimulatorConfig::getDesignResolutionPolicy(int index) const
{
    return _designResolutionPolicyArray.at(index);
}

int SimulatorConfig::checkDesignResolutionPolicy(ResolutionPolicy policy) const
{
    int count = (int)_designResolutionPolicyArray.size();
    for (int i = 0; i < count; ++i)
    {
        const SimulatorDesignResolutionPolicy &policyInfo = _designResolutionPolicyArray[i];
        if (policyInfo.policy == policy)
        {
            return i;
        }
    }

    return -1;
}

int SimulatorConfig::getDesignContentScaleFactorCount() const
{
    return (int)_designContentScaleFactorArray.size();
}

SimulatorDesignContentScaleFactor SimulatorConfig::getDesignContentScaleFactor(int index) const
{
    return _designContentScaleFactorArray.at(index);
}

int SimulatorConfig::checkDesignContentScaleFactor(float scaleFactor) const
{
    int count = (int)_designResolutionPolicyArray.size();
    for (int i = 0; i < count; ++i)
    {
        const SimulatorDesignContentScaleFactor &scaleFactorInfo = _designContentScaleFactorArray[i];
        if (scaleFactorInfo.scaleFactor == scaleFactor)
        {
            return i;
        }
    }
    return -1;
}

void SimulatorConfig::addDesignContentScaleFactor(const SimulatorDesignContentScaleFactor &scaleFactor)
{
    _designContentScaleFactorArray.push_back(scaleFactor);
}


// helper

void SimulatorConfig::makeNormalizePath(string *path, const char *directorySeparator/* = NULL*/)
{
    if (!directorySeparator) directorySeparator = DIRECTORY_SEPARATOR;
    size_t pos = std::string::npos;
    while ((pos = path->find_first_of("/\\", pos + 1)) != std::string::npos)
    {
        path->replace(pos, 1, directorySeparator);
    }
}
