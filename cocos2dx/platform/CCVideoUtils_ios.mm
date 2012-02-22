//
//  CCVideoUtils.m
//
//  Created by Dmitry Matyukhin on 10/12/2011.
//

#import "CCVideoUtils.h"
#import "CCVideoUtils_ios_support.h"

using namespace cocos2d;

void CCVideoUtils::playVideo(char const* filename, bool showControls, bool skipByTap, CCObject* pSelectorTarget,
                             SEL_CallFuncN selector, cocos2d::CCNode* withObject) {
    [[CCVideoUtils_iOS shared] playVideo:[NSString stringWithUTF8String:filename] showControls:showControls skipByTap:skipByTap target:pSelectorTarget selector:selector withObject:withObject];
}

void CCVideoUtils::purgeCCVideoUtils() {
    [CCVideoUtils_iOS purge];
}


void CCVideoUtils::openURL(const char *url) {
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]]];
}
