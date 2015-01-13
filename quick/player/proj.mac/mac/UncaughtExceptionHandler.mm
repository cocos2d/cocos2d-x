//
//  UncaughtExceptionHandler.mm
//  player3
//
//  Created by ZhuJunfeng on 15-1-8.
//
//

#include <execinfo.h>
#include "base/CCDirector.h"


#import "UncaughtExceptionHandler.h"

NSString * const UncaughtExceptionHandlerSignalExceptionName = @"UncaughtExceptionHandlerSignalExceptionName";

NSString * const UncaughtExceptionHandlerSignalKey = @"UncaughtExceptionHandlerSignalKey";

NSString * const UncaughtExceptionHandlerAddressesKey = @"UncaughtExceptionHandlerAddressesKey";

volatile int32_t UncaughtExceptionCount = 0;

volatile int32_t ProcessedCount = 0;

const int32_t UncaughtExceptionMaximum = 10;

const NSInteger UncaughtExceptionHandlerSkipAddressCount = 4;

const NSInteger UncaughtExceptionHandlerReportAddressCount = 5;

@implementation UncaughtExceptionHandler

+ (NSArray *)backtrace

{
    
    void* callstack[128];
    
    int frames = backtrace(callstack, 128);
    
    char **strs = backtrace_symbols(callstack, frames);
    
    int i;
    
    NSMutableArray *backtrace = [NSMutableArray arrayWithCapacity:frames];
    
    for (
         
         i = UncaughtExceptionHandlerSkipAddressCount;
         
         i < UncaughtExceptionHandlerSkipAddressCount +
         
         UncaughtExceptionHandlerReportAddressCount;
         
         i++)
        
    {
        
        [backtrace addObject:[NSString stringWithUTF8String:strs[i]]];
        
    }
    
    free(strs);
    
    return backtrace;
    
}

//- (void)alertView:(NSAlert *)anAlertView clickedButtonAtIndex:(NSInteger)anIndex
//
//{
//    
//    if (anIndex == 0)
//        
//    {
//        
//        dismissed = YES;
//        
//    }
//    
//}

- (void)alertDidEnd:(NSAlert *)alert

         returnCode:(NSInteger)returnCode

        contextInfo:(void *)contextInfo

{
    dismissed = YES;
    
    if (returnCode == NSAlertFirstButtonReturn)
    {
    }
}

- (void)handleException:(NSException *)exception

{
    int32_t processCount = OSAtomicIncrement32(&ProcessedCount);
    if (processCount > 1)
    {
        return;
    }
    printf("-----------------my exception process\n");
    
//    NSAlert *alert = [[[NSAlert alloc] init] autorelease];
//    [alert addButtonWithTitle:@"OK"];
//    [alert setMessageText:message];
//    [alert setInformativeText:title];
//    [alert setAlertStyle:NSWarningAlertStyle];
//    [alert runModal];
    NSAlert *alert = [[NSAlert alloc] init];
    
    [alert addButtonWithTitle:NSLocalizedString(@"Quit", nil)];
    
    [alert addButtonWithTitle:NSLocalizedString(@"Continue", nil)];
    
    [alert setMessageText:[NSString stringWithFormat:NSLocalizedString(
                                                                       
                                                                       @"You can try to continue but the application may be unstable.\n"
                                                                       
                                                                       @"%@\n%@", nil),
                           
                           [exception reason],
                           
                           [[exception userInfo] objectForKey:UncaughtExceptionHandlerAddressesKey]]];

//    [alert setDelegate:self];
//
        [alert setAlertStyle:NSWarningAlertStyle];
//        [alert runModal];
//    [alert autorelease];
//
    auto direct = cocos2d::Director::getInstance();
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    id window = glview->getCocoaWindow();
    [alert beginSheetModalForWindow:window modalDelegate:[window delegate] didEndSelector:@selector(alertDidEnd:returnCode:contextInfo:) contextInfo:nil];
    
//    direct->mainLoop();

    CFRunLoopRef runLoop = CFRunLoopGetCurrent();
    
    CFArrayRef allModes = CFRunLoopCopyAllModes(runLoop);
    
    while (!dismissed)
        
    {
        
        for (NSString *mode in (NSArray *)allModes)
            
        {
            
            CFRunLoopRunInMode((CFStringRef)mode, 0.001, false);
            
        }
        
    }	
    
    CFRelease(allModes);
    
//    NSString *msg = [NSString stringWithFormat:NSLocalizedString(
//                                                                
//                                                                @"You can try to continue but the application may be unstable.\n"
//                                                                
//                                                                @"%@\n%@", nil),
//                    
//                    [exception reason],
//                    
//                    [[exception userInfo] objectForKey:UncaughtExceptionHandlerAddressesKey]];
//    
//    cocos2d::MessageBox("--------", "error");
    
    NSSetUncaughtExceptionHandler(NULL);
    
    signal(SIGABRT, SIG_DFL);
    
    signal(SIGILL, SIG_DFL);
    
    signal(SIGSEGV, SIG_DFL);
    
    signal(SIGFPE, SIG_DFL);
    
    signal(SIGBUS, SIG_DFL);
    
    signal(SIGPIPE, SIG_DFL);	
    
    if ([[exception name] isEqual:UncaughtExceptionHandlerSignalExceptionName])
    
    {
        
        kill(getpid(), [[[exception userInfo] objectForKey:UncaughtExceptionHandlerSignalKey] intValue]);
        
    }
    
    
    else
        
    {
        
        [exception raise];
        
    }
    
//    exit(999);
}

@end

NSString* getAppInfo()
{
    NSString *appInfo = [NSString stringWithFormat:@"App : %@ %@(%@)\n\n", [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleDisplayName"], [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"], [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]];
    NSLog(@"Crash!!!! %@", appInfo);
    return appInfo;
}

void MySignalHandler(int signal)
{
    int32_t exceptionCount = OSAtomicIncrement32(&UncaughtExceptionCount);
    if (exceptionCount > UncaughtExceptionMaximum)
    {
        return;
    }
    
    NSMutableDictionary *userInfo =
    
    [NSMutableDictionary
     
     dictionaryWithObject:[NSNumber numberWithInt:signal]
     
     forKey:UncaughtExceptionHandlerSignalKey];
    
    NSArray *callStack = [UncaughtExceptionHandler backtrace];
    
    [userInfo
     
     setObject:callStack
     
     forKey:UncaughtExceptionHandlerAddressesKey];
    
    [[[[UncaughtExceptionHandler alloc] init] autorelease]
     
     performSelectorOnMainThread:@selector(handleException:)
     
     withObject:
     
     [NSException
      
      exceptionWithName:UncaughtExceptionHandlerSignalExceptionName
      
      reason:
      
      [NSString stringWithFormat:
       
       NSLocalizedString(@"Signal %d was raised.\n"
                         
                         @"%@", nil),
       
       signal, getAppInfo()]
      
      userInfo:
      
      [NSDictionary
       
       dictionaryWithObject:[NSNumber numberWithInt:signal]
       
       forKey:UncaughtExceptionHandlerSignalKey]]
     
     waitUntilDone:YES];
    
}

void InstallUncaughtExceptionHandler()
{
    signal(SIGABRT, MySignalHandler);
    signal(SIGILL, MySignalHandler);
    signal(SIGSEGV, MySignalHandler);
    signal(SIGFPE, MySignalHandler);
    signal(SIGBUS, MySignalHandler);
    signal(SIGPIPE, MySignalHandler);
}