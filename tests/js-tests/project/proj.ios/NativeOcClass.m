/*
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#import "NativeOcClass.h"
#if  TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
#endif
@implementation NativeOcClass
+(float) callNative:(NSNumber *)a andInt:(NSString *)str{
    float b = [a floatValue]+111.3333;
    NSLog(@"callNative string is %@ and int value is %f",str,b);
    return b;
}
+(void)callNativeWithParam:(NSString *)str{
    NSLog(@"callNativeWithParam: str is %@ ",str);
}
+(NSString *)callNativeWithReturnString{
    return @"yes is a return string form objective-c";
}
+(BOOL)callNativeWithReturnBool{
    return true;
}
+(int)callNativeWithAdd:(NSNumber *)num1 and:(NSNumber *)num2{
    return [num1 intValue]+[num2 intValue];
}
#if TARGET_OS_IPHONE
+(BOOL)callNativeUIWithTitle:(NSString *) title andContent:(NSString *)content{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:content delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
    [alertView show];
    return true;
}
#elif TARGET_OS_MAC

+(BOOL)callNativeUIWithTitle:(NSString *) title andContent:(NSString *)content{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"OK"];
    [alert addButtonWithTitle:@"Cancel"];
    [alert setMessageText:title];
    [alert setInformativeText:content];
    [alert setAlertStyle:NSWarningAlertStyle];
    [alert runModal];
    return true;
}

#endif
@end
