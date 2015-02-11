//
//  OpenUDID.h
//  openudid
//
//  initiated by Yann Lechelle (cofounder @Appsfire) on 8/28/11.
//  Copyright 2011 OpenUDID.org
//
//  Main branches
//      iOS code: https://github.com/ylechelle/OpenUDID
//

/*
    !!! IMPORTANT !!!

    IF YOU ARE GOING TO INTEGRATE OpenUDID INSIDE A (STATIC) LIBRARY,
    PLEASE MAKE SURE YOU REFACTOR THE OpenUDID CLASS WITH A PREFIX OF YOUR OWN,
    E.G. ACME_OpenUDID. THIS WILL AVOID CONFUSION BY DEVELOPERS WHO ARE ALSO
    USING OpenUDID IN THEIR OWN CODE. 

    !!! IMPORTANT !!!

*/

/*
 http://en.wikipedia.org/wiki/Zlib_License
 
 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source
 distribution.
*/

#import <Foundation/Foundation.h>

//
// Usage:
//    #include "OpenUDID.h"
//    NSString* openUDID = [OpenUDID value];
//

#define kOpenUDIDErrorNone          0
#define kOpenUDIDErrorOptedOut      1
#define kOpenUDIDErrorCompromised   2

@interface OpenUDIDMac : NSObject {
}
+ (NSString*) value;
+ (NSString*) valueWithError:(NSError**)error;
+ (void) setOptOut:(BOOL)optOutValue;

@end
