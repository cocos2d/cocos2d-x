//
//  PluginTwitter.h
//  PluginTwitter
//
//  Created by zhangbin on 13-6-8.
//  Copyright (c) 2013年 zhangbin. All rights reserved.
//

#import "InterfaceSocial.h"

@interface SocialTwitter : NSObject <InterfaceSocial>
{
    
}

@property BOOL debug;
@property (copy, nonatomic) NSMutableDictionary* mShareInfo;

/**
 * @brief interfaces of protocol : InterfaceSocial
 */
- (void) configDeveloperInfo : (NSMutableDictionary*) cpInfo;
- (void) share: (NSMutableDictionary*) shareInfo;
- (void) setDebugMode: (BOOL) debug;
- (NSString*) getSDKVersion;
- (NSString*) getPluginVersion;

@end
