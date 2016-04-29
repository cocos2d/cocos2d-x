/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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


#import "ParseUtils.h"

@implementation ParseUtils
+ (id)NSStringToArrayOrNSDictionary:(NSString *)jsonData{
    NSError *error = nil;
    NSData *stringData = [jsonData dataUsingEncoding:NSUTF8StringEncoding];
    id jsonObject = [NSJSONSerialization JSONObjectWithData:stringData options:NSJSONReadingAllowFragments error:&error];
    
    if (jsonObject != nil && error == nil){
        return jsonObject;
    }else{
        return nil;
    }
    
}
+ (NSString *) NSDictionaryToNSString:(id)dic{
    NSString *result = nil;
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dic
                                                       options:0 // Pass 0 if you don't care about the readability of the generated string
                                                         error:&error];
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        result = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    return result;
}
+(NSString *)MakeJsonStringWithObject:(id) obj andKey:(NSString *)key {
    return [ParseUtils NSDictionaryToNSString:[NSDictionary dictionaryWithObject:obj forKey:key]];
}
@end
