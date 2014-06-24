//
//  MessageBoxServiceMac.mm
//  quick-x-player
//

#include "MessageBoxServiceMac.h"

PLAYER_NS_BEGIN


int MessageBoxServiceMac::showMessageBox(const char *title, const char *message, MessageBoxButtonsType buttons)
{
    NSAlert *alert = [[NSAlert alloc] init];

    std::vector<std::string> titles = getTitles(buttons);
    for (string& title : titles)
    {
        [alert addButtonWithTitle:[NSString stringWithUTF8String:title.c_str()]];
    }
    
    [alert setMessageText:[NSString stringWithUTF8String:title]];
    [alert setInformativeText:[NSString stringWithUTF8String:message]];
    [alert setAlertStyle:NSWarningAlertStyle];
    
    int buttonId = (int)[alert runModal] - NSAlertFirstButtonReturn;
    return buttonId;
}

std::vector<std::string> MessageBoxServiceMac::getTitles(MessageBoxButtonsType buttons)
{
    std::vector<std::string> titles;
    
    switch (buttons) {
        case MessageBoxOK:
            titles.push_back("OK");
            break;
            
        case MessageBoxOKCancel:
            titles.push_back("OK");
            titles.push_back("Cancel");
            break;
            
        case MessageBoxYesNo:
            titles.push_back("Yes");
            titles.push_back("No");
            break;
            
        case MessageBoxYesNoCancel:
            titles.push_back("Yes");
            titles.push_back("No");
            titles.push_back("Cancel");
            break;
            
        default:
            break;
    }
    
    return titles;
}

PLAYER_NS_END