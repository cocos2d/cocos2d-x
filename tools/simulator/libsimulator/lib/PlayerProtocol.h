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


#ifndef __PLAYER_PROTOCOL_H_
#define __PLAYER_PROTOCOL_H_

#include "PlayerMacros.h"
#include "PlayerSettings.h"

#include "PlayerFileDialogServiceProtocol.h"
#include "PlayerMessageBoxServiceProtocol.h"
#include "PlayerMenuServiceProtocol.h"
#include "PlayerEditBoxServiceProtocol.h"
#include "PlayerTaskServiceProtocol.h"

#include "ProjectConfig/ProjectConfig.h"
#include "SimulatorExport.h"

PLAYER_NS_BEGIN

class CC_LIBSIM_DLL PlayerProtocol
{
public:
    virtual ~PlayerProtocol();

    static PlayerProtocol *getInstance();
    static void purgeInstance();

    void setPlayerSettings(const PlayerSettings &settings);
    PlayerSettings getPlayerSettings() const;

    virtual PlayerFileDialogServiceProtocol *getFileDialogService() = 0; // implemented in platform related source files
    virtual PlayerMessageBoxServiceProtocol *getMessageBoxService() = 0;
    virtual PlayerMenuServiceProtocol *getMenuService() = 0;
    virtual PlayerEditBoxServiceProtocol *getEditBoxService() = 0;
    virtual PlayerTaskServiceProtocol *getTaskService() = 0;
    
protected:
    PlayerProtocol(); // avoid create instance from outside

    PlayerSettings _settings;

private:
    static PlayerProtocol *_instance;
};

PLAYER_NS_END

#endif // __PLAYER_PROTOCOL_H_
