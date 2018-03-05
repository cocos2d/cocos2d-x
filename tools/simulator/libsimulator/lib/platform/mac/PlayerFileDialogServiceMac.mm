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

#import <AppKit/AppKit.h>
#include "PlayerFileDialogServiceMac.h"

#include "glfw3.h"
#include "glfw3native.h"

#define VALIDATE_FRAMEBUFFER { \
NSOpenGLContext *__context = glfwGetNSGLContext(glfwGetCurrentContext()); \
[__context makeCurrentContext]; \
}

PLAYER_NS_BEGIN

std::string PlayerFileDialogServiceMac::openFile(const std::string &title,
                                                 const std::string &directory,
                                                 const std::string &extensions) const
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:[NSString stringWithUTF8String:title.c_str()]];
    [openDlg setCanChooseDirectories:NO];
    [openDlg setCanChooseFiles:YES];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];
    
    if (directory.length()) {
        [openDlg setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:directory.c_str()]]];
    }
    
    if (extensions.length())
    {
        NSMutableArray *fileTypes = [NSMutableArray array];
        
        NSString *buff = [NSString stringWithUTF8String:extensions.c_str()];
        NSArray *extensionArray = [buff componentsSeparatedByString:@";"];
        
        for (NSString *oneExtension in extensionArray) {
            NSArray *tmpData = [oneExtension componentsSeparatedByString:@"|"];
            if ([tmpData count] > 1)
            {
                NSString *suffixString = [tmpData objectAtIndex:1];
                suffixString = [suffixString stringByReplacingOccurrencesOfString:@"*." withString:@""];
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
    
    [openDlg close];
    VALIDATE_FRAMEBUFFER
    return filePath;
}

std::string PlayerFileDialogServiceMac::openDirectory( const std::string &title,
                                                      const std::string &directory) const
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:[NSString stringWithUTF8String:title.c_str()]];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:NO];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];
    
    if (directory.length()) {
        [openDlg setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:directory.c_str()]]];
    }
    
    std::string path;
    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSURL *url = [openDlg.URLs objectAtIndex:0];
        path = [[url path] UTF8String];
    }
    
    [openDlg close];
    VALIDATE_FRAMEBUFFER
    return path;
}

std::vector<std::string> PlayerFileDialogServiceMac::openMultiple(  const std::string &title,
                                                                  const std::string &directory,
                                                                  const std::string &extensions) const
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:[NSString stringWithUTF8String:title.c_str()]];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:YES];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:NO];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:YES];
    
    if (directory.length()) {
        [openDlg setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:directory.c_str()]]];
    }
    
    if (extensions.length())
    {
        NSMutableArray *fileTypes = [NSMutableArray array];
        
        NSString *buff = [NSString stringWithUTF8String:extensions.c_str()];
        NSArray *extensionArray = [buff componentsSeparatedByString:@";"];
        
        for (NSString *oneExtension in extensionArray) {
            NSArray *tmpData = [oneExtension componentsSeparatedByString:@"|"];
            if ([tmpData count] > 1)
            {
                NSString *suffixString = [tmpData objectAtIndex:1];
                suffixString = [suffixString stringByReplacingOccurrencesOfString:@"*." withString:@""];
                [fileTypes addObjectsFromArray:[suffixString componentsSeparatedByString:@","]];
            }
        }
        
        [openDlg setAllowedFileTypes:fileTypes];
    }
    
    std::vector<std::string> pathes;
    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        for (NSURL *url in openDlg.URLs) {
            pathes.push_back([[url path] UTF8String]);
        }
    }
    
    [openDlg close];
    VALIDATE_FRAMEBUFFER
    return  pathes;
}

std::string PlayerFileDialogServiceMac::saveFile(const std::string &title,
                                                 const std::string &path) const
{
    NSSavePanel* saveDlg = [NSSavePanel savePanel];
    [saveDlg setTitle:[NSString stringWithUTF8String:title.c_str()]];
    [saveDlg setCanHide:YES];
    [saveDlg setCanCreateDirectories:NO];
    [saveDlg setCanSelectHiddenExtension:NO];
    
    
    // set directory
    NSString *tempPath = [NSString stringWithUTF8String:path.c_str()];
    NSString *directory = [tempPath stringByDeletingLastPathComponent];
    if (directory)
    {
        [saveDlg setDirectoryURL:[NSURL fileURLWithPath:directory]];
    }
    
    // set filename
    [saveDlg setNameFieldStringValue:[tempPath lastPathComponent]];
    
    std::string filePath;
    if ([saveDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSURL *url = saveDlg.URL;
        filePath = [[url path] UTF8String];
    }

    [saveDlg close];
    VALIDATE_FRAMEBUFFER
    return filePath;
}

PLAYER_NS_END
