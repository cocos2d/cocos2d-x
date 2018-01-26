
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