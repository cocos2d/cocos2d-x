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


#include "PlayerMessageBoxServiceMac.h"

PLAYER_NS_BEGIN

int PlayerMessageBoxServiceMac::showMessageBox(const std::string &title,
                                         const std::string &message,
                                         int buttonsType)
{
    NSAlert *alert = [[NSAlert alloc] init];

    auto titles = getTitles(buttonsType);
    for (auto& title : titles)
    {
        [alert addButtonWithTitle:[NSString stringWithUTF8String:title.title.c_str()]];
    }
    
    [alert setMessageText:[NSString stringWithUTF8String:title.c_str()]];
    [alert setInformativeText:[NSString stringWithUTF8String:message.c_str()]];
    [alert setAlertStyle:NSWarningAlertStyle];
    
    int index = (int)[alert runModal] - NSAlertFirstButtonReturn;
    return titles.at(index).buttonId;
}

std::vector<PlayerMessageBoxServiceMac::MessageBoxInfo> PlayerMessageBoxServiceMac::getTitles(int buttons)
{
    std::vector<PlayerMessageBoxServiceMac::MessageBoxInfo> titles;
    
    switch (buttons) {
        case BUTTONS_OK:
            titles.push_back({"OK", BUTTON_OK});
            break;
            
        case BUTTONS_OK_CANCEL:
            titles.push_back({"OK", BUTTON_OK});
            titles.push_back({"Cancel", BUTTON_CANCEL});
            break;
            
        case BUTTONS_YES_NO:
            titles.push_back({"Yes", BUTTON_YES});
            titles.push_back({"No",  BUTTON_NO});
            break;
            
        case BUTTONS_YES_NO_CANCEL:
            titles.push_back({"Yes", BUTTON_YES});
            titles.push_back({"No",  BUTTON_NO});
            titles.push_back({"Cancel",  BUTTON_CANCEL});
            break;
            
        default:
            break;
    }
    
    return titles;
}

PLAYER_NS_END