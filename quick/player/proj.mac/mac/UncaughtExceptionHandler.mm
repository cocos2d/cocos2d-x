//
//  UncaughtExceptionHandler.mm
//  player3
//
//  Created by ZhuJunfeng on 15-1-8.
//
//

#include <execinfo.h>

#import "UncaughtExceptionHandler.h"

NSString * const UncaughtExceptionHandlerSignalExceptionName = @"UncaughtExceptionHandlerSignalExceptionName";

NSString * const UncaughtExceptionHandlerSignalKey = @"UncaughtExceptionHandlerSignalKey";

NSString * const UncaughtExceptionHandlerAddressesKey = @"UncaughtExceptionHandlerAddressesKey";

volatile int32_t UncaughtExceptionCount = 0;

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

//- (void)alertView:(NSAlertView *)anAlertView clickedButtonAtIndex:(NSInteger)anIndex
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

- (void)handleException:(NSException *)exception

{
    printf("-----------------my exception process\n");
    
//    NSAlertView *alert =
//    
//    [[[NSAlertView alloc]
//      
//      initWithTitle:NSLocalizedString(@"Unhandled exception", nil)
//      
//      message:[NSString stringWithFormat:NSLocalizedString(
//                                                           
//                                                           @"You can try to continue but the application may be unstable.\n"
//                                                           
//                                                           @"%@\n%@", nil),
//               
//               [exception reason],
//               
//               [[exception userInfo] objectForKey:UncaughtExceptionHandlerAddressesKey]]
//      
//      delegate:self
//      
//      cancelButtonTitle:NSLocalizedString(@"Quit", nil)
//      
//      otherButtonTitles:NSLocalizedString(@"Continue", nil), nil]
//     
//     autorelease];
//    
//    [alert show];
    
//    CFRunLoopRef runLoop = CFRunLoopGetCurrent();
//    
//    CFArrayRef allModes = CFRunLoopCopyAllModes(runLoop);
//    
//    while (!dismissed)
//        
//    {
//        
//        for (NSString *mode in (NSArray *)allModes)
//            
//        {
//            
//            CFRunLoopRunInMode((CFStringRef)mode, 0.001, false);
//            
//        }
//        
//    }	
//    
//    CFRelease(allModes);
    
    NSSetUncaughtExceptionHandler(NULL);
    
    signal(SIGABRT, SIG_DFL);
    
    signal(SIGILL, SIG_DFL);
    
    signal(SIGSEGV, SIG_DFL);
    
    signal(SIGFPE, SIG_DFL);
    
    signal(SIGBUS, SIG_DFL);
    
    signal(SIGPIPE, SIG_DFL);	
    
//    if ([[exception name] isEqual:UncaughtExceptionHandlerSignalExceptionName])
    
//    {
//        
//        kill(getpid(), [[[exception userInfo] objectForKey:UncaughtExceptionHandlerSignalKey] intValue]);
//        
//    }
//    
    exit(999);
    
//    else
//        
//    {
//        
//        [exception raise];
//        
//    }
    
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