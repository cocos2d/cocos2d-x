/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __cocos2d_libs__CCController__
#define __cocos2d_libs__CCController__

#include "CCPlatformMacros.h"

#include <string>
#include <vector>
#include <functional>


NS_CC_BEGIN

class Gamepad;
class ControllerImpl;

class Controller
{
public:
    static const std::vector<Controller*>& getControllers();

    static void startDiscoveryController();
    static void stopDiscoveryController();

    const std::string& getVendorName();
    bool isConnected() const;

    static const int PLAYER_INDEX_UNSET = -1;

    int getPlayerIndex() const;
    void setPlayerIndex(int playerIndex);

    Gamepad* getGamepad();

    // For internal use only
    inline ControllerImpl* getImpl() const { return _impl; };

    Controller();
    virtual ~Controller();

private:
    static std::vector<Controller*> _controllers;

    std::string _vendorName;
	int _playerIndex;
    Gamepad* _gamepad;

    friend class ControllerImpl;
    ControllerImpl* _impl;
};


NS_CC_END

#endif /* defined(__cocos2d_libs__CCController__) */
