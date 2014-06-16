
#include "FileDialogServiceMac.h"

PLAYER_NS_BEGIN

string FileDialogServiceMac::openFile(  const char *title,
                                        const char *directory /* = NULL */,
                                        const char *extensions /* = NULL */)
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:[NSString stringWithUTF8String:title]];
    [openDlg setCanChooseDirectories:NO];
    [openDlg setCanChooseFiles:YES];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];
    
    if (directory) {
        [openDlg setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:directory]]];
    }
    
    if (extensions)
    {
        NSMutableArray *fileTypes = [NSMutableArray array];
        
        NSString *buff = [NSString stringWithUTF8String:extensions];
        NSArray *extensionArray = [buff componentsSeparatedByString:@"\n"];
        
        for (NSString *oneExtension in extensionArray) {
            NSArray *tmpData = [oneExtension componentsSeparatedByString:@"|"];
//            NSString *info = [tmpData objectAtIndex:0];
            if ([tmpData count] > 1)
            {
                NSString *suffixString = [tmpData objectAtIndex:1];
                [fileTypes addObjectsFromArray:[suffixString componentsSeparatedByString:@","]];
            }
        }

        [openDlg setAllowedFileTypes:fileTypes];
    }
    
    std::string filePath;
    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSURL *url = [openDlg.URLs objectAtIndex:0];
        filePath = [[url path] UTF8String];
    }
    return filePath;
}

string FileDialogServiceMac::openDirectory( const char *title,
                                            const char *directory /* = NULL */)
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:[NSString stringWithUTF8String:title]];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:NO];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];
    
    if (directory) {
        [openDlg setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:directory]]];
    }
    
    std::string path;
    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSURL *url = [openDlg.URLs objectAtIndex:0];
        path = [[url path] UTF8String];
    }
    return path;
}

vector<string> FileDialogServiceMac::openMultiple(  const char *title,
                                                    const char *directory /* = NULL */)
{

    
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:[NSString stringWithUTF8String:title]];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:YES];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:YES];
    
    if (directory) {
        [openDlg setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:directory]]];
    }
    
    std::vector<std::string> pathes;
    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        for (NSURL *url in openDlg.URLs) {
            pathes.push_back([[url path] UTF8String]);
        }
    }
    
    return  pathes;
}

string FileDialogServiceMac::saveFile(  const char *title,
                                        const char *filename,
                                        const char *directory)
{
    NSSavePanel* saveDlg = [NSSavePanel savePanel];
    [saveDlg setTitle:[NSString stringWithUTF8String:title]];
    [saveDlg setCanHide:YES];
    [saveDlg setCanCreateDirectories:NO];
    [saveDlg setCanSelectHiddenExtension:NO];
    
    if (filename)
    {
        [saveDlg setNameFieldStringValue:[NSString stringWithUTF8String:filename]];
    }
    
    if (directory) {
        [saveDlg setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:directory]]];
    }
    
    std::string filePath;
    if ([saveDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSURL *url = saveDlg.URL;
        filePath = [[url path] UTF8String];
    }
    return filePath;
}

PLAYER_NS_END
