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
