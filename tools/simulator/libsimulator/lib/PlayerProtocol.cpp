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


#include "PlayerProtocol.h"
#include "base/ccMacros.h"

PLAYER_NS_BEGIN

USING_NS_CC;

PlayerProtocol *PlayerProtocol::_instance = nullptr;

PlayerProtocol::PlayerProtocol()
{
    CCASSERT(_instance == nullptr, "CAN NOT CREATE MORE PLAYER INSTANCE");
    _instance = this;
}

PlayerProtocol::~PlayerProtocol()
{
    _instance = nullptr;
}

PlayerProtocol *PlayerProtocol::getInstance()
{
    return _instance;
}

void PlayerProtocol::purgeInstance()
{
    if (_instance) delete _instance;
}

void PlayerProtocol::setPlayerSettings(const PlayerSettings &settings)
{
    _settings = settings;
}

PlayerSettings PlayerProtocol::getPlayerSettings() const
{
    return _settings;
}

PLAYER_NS_END
