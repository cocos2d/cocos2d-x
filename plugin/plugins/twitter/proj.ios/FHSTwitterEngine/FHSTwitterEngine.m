//
//  FHSTwitterEngine.m
//  FHSTwitterEngine
//
//  Created by Nathaniel Symer on 8/22/12.
//  Copyright (C) 2012 Nathaniel Symer.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#import "FHSTwitterEngine.h"

#import "OAuthConsumer.h"
#import <QuartzCore/QuartzCore.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <ifaddrs.h>
#import <objc/runtime.h>

NSString * const FHSProfileBackgroundColorKey = @"profile_background_color";
NSString * const FHSProfileLinkColorKey = @"profile_link_color";
NSString * const FHSProfileSidebarBorderColorKey = @"profile_sidebar_border_color";
NSString * const FHSProfileSidebarFillColorKey = @"profile_sidebar_fill_color";
NSString * const FHSProfileTextColorKey = @"profile_text_color";

NSString * const FHSProfileNameKey = @"name";
NSString * const FHSProfileURLKey = @"url";
NSString * const FHSProfileLocationKey = @"location";
NSString * const FHSProfileDescriptionKey = @"description";


static NSString * const errorFourhundred = @"Bad Request: The request you are trying to make has missing or bad parameters.";

static NSString * const authBlockKey = @"FHSTwitterEngineOAuthCompletion";

static FHSTwitterEngine *sharedInstance = nil;

id removeNull(id rootObject) {
    if ([rootObject isKindOfClass:[NSDictionary class]]) {
        NSMutableDictionary *sanitizedDictionary = [NSMutableDictionary dictionaryWithDictionary:rootObject];
        [rootObject enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
            id sanitized = removeNull(obj);
            if (!sanitized) {
                [sanitizedDictionary setObject:@"" forKey:key];
            } else {
                [sanitizedDictionary setObject:sanitized forKey:key];
            }
        }];
        return [NSMutableDictionary dictionaryWithDictionary:sanitizedDictionary];
    }
    
    if ([rootObject isKindOfClass:[NSArray class]]) {
        NSMutableArray *sanitizedArray = [NSMutableArray arrayWithArray:rootObject];
        [rootObject enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            id sanitized = removeNull(obj);
            if (!sanitized) {
                [sanitizedArray replaceObjectAtIndex:[sanitizedArray indexOfObject:obj] withObject:@""];
            } else {
                [sanitizedArray replaceObjectAtIndex:[sanitizedArray indexOfObject:obj] withObject:sanitized];
            }
        }];
        return [NSMutableArray arrayWithArray:sanitizedArray];
    }

    if ([rootObject isKindOfClass:[NSNull class]]) {
        return (id)nil;
    } else {
        return rootObject;
    }
}

NSError * getBadRequestError() {
    return [NSError errorWithDomain:errorFourhundred code:400 userInfo:nil];
}

NSError * getNilReturnLengthError() {
    return [NSError errorWithDomain:@"Twitter successfully processed the request, but did not return any content" code:204 userInfo:nil];
}

@interface FHSTwitterEngineController : UIViewController <UIWebViewDelegate> 

@property (nonatomic, retain) UINavigationBar *navBar;
@property (nonatomic, retain) UIView *blockerView;
@property (nonatomic, retain) UIToolbar *pinCopyBar;

//@property (nonatomic, retain) FHSTwitterEngine *engine;
@property (nonatomic, retain) UIWebView *theWebView;
@property (nonatomic, retain) OAToken *requestToken;

//- (id)initWithEngine:(FHSTwitterEngine *)theEngine;
- (NSString *)locatePin;
- (void)showPinCopyPrompt;

@end

@interface FHSTwitterEngine()

// Login stuff
- (NSString *)getRequestTokenString;

// General Get request sender
- (id)sendRequest:(NSURLRequest *)request;

// These are here to obfuscate them from prying eyes
@property (retain, nonatomic) OAConsumer *consumer;
@property (assign, nonatomic) BOOL shouldClearConsumer;
@property (retain, nonatomic) NSDateFormatter *dateFormatter;

@end

@implementation NSString (FHSTwitterEngine)

- (NSString *)fhs_trimForTwitter {
    NSString *string = [self stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    return (string.length > 140)?[string substringToIndex:140]:string;
}

- (NSString *)fhs_stringWithRange:(NSRange)range {
    return [[self substringFromIndex:range.location]substringToIndex:range.length];
}

- (BOOL)fhs_isNumeric {
	const char *raw = (const char *)[self UTF8String];
    
	for (int i = 0; i < strlen(raw); i++) {
		if (raw[i] < '0' || raw[i] > '9') {
            return NO;
        }
	}
	return YES;
}

@end

@implementation FHSTwitterEngine

static NSString * const url_search_tweets = @"https://api.twitter.com/1.1/search/tweets.json";

static NSString * const url_users_search = @"https://api.twitter.com/1.1/users/search.json";
static NSString * const url_users_show = @"https://api.twitter.com/1.1/users/show.json";
static NSString * const url_users_report_spam = @"https://api.twitter.com/1.1/users/report_spam.json";
static NSString * const url_users_lookup = @"https://api.twitter.com/1.1/users/lookup.json";

static NSString * const url_lists_create = @"https://api.twitter.com/1.1/lists/create.json";
static NSString * const url_lists_show = @"https://api.twitter.com/1.1/lists/show.json";
static NSString * const url_lists_update = @"https://api.twitter.com/1.1/lists/update.json";
static NSString * const url_lists_members = @"https://api.twitter.com/1.1/lists/members.json";
static NSString * const url_lists_members_destroy_all = @"https://api.twitter.com/1.1/lists/members/destroy_all.json";
static NSString * const url_lists_members_create_all = @"https://api.twitter.com/1.1/lists/members/create_all.json";
static NSString * const url_lists_statuses = @"https://api.twitter.com/1.1/lists/statuses.json";
static NSString * const url_lists_list = @"https://api.twitter.com/1.1/lists/list.json";

static NSString * const url_statuses_home_timeline = @"https://api.twitter.com/1.1/statuses/home_timeline.json";
static NSString * const url_statuses_update = @"https://api.twitter.com/1.1/statuses/update.json";
static NSString * const url_statuses_retweets_of_me = @"https://api.twitter.com/1.1/statuses/retweets_of_me.json";
static NSString * const url_statuses_user_timeline = @"https://api.twitter.com/1.1/statuses/user_timeline.json";
static NSString * const url_statuses_metions_timeline = @"https://api.twitter.com/1.1/statuses/mentions_timeline.json";
static NSString * const url_statuses_update_with_media = @"https://api.twitter.com/1.1/statuses/update_with_media.json";
static NSString * const url_statuses_destroy = @"https://api.twitter.com/1.1/statuses/destroy.json";
static NSString * const url_statuses_show = @"https://api.twitter.com/1.1/statuses/show.json";
static NSString * const url_statuses_oembed = @"https://api.twitter.com/1.1/statuses/oembed.json";

static NSString * const url_blocks_exists = @"https://api.twitter.com/1.1/blocks/exists.json";
static NSString * const url_blocks_blocking = @"https://api.twitter.com/1.1/blocks/blocking.json";
static NSString * const url_blocks_blocking_ids = @"https://api.twitter.com/1.1/blocks/blocking/ids.json";
static NSString * const url_blocks_destroy = @"https://api.twitter.com/1.1/blocks/destroy.json";
static NSString * const url_blocks_create = @"https://api.twitter.com/1.1/blocks/create.json";

static NSString * const url_help_languages = @"https://api.twitter.com/1.1/help/languages.json";
static NSString * const url_help_configuration = @"https://api.twitter.com/1.1/help/configuration.json";
static NSString * const url_help_privacy = @"https://api.twitter.com/1.1/help/privacy.json";
static NSString * const url_help_tos = @"https://api.twitter.com/1.1/help/tos.json";
static NSString * const url_help_test = @"https://api.twitter.com/1.1/help/test.json";

static NSString * const url_direct_messages_show = @"https://api.twitter.com/1.1/direct_messages/show.json";
static NSString * const url_direct_messages_new = @"https://api.twitter.com/1.1/direct_messages/new.json";
static NSString * const url_direct_messages_sent = @"https://api.twitter.com/1.1/direct_messages/sent.json";
static NSString * const url_direct_messages_destroy = @"https://api.twitter.com/1.1/direct_messages/destroy.json";
static NSString * const url_direct_messages = @"https://api.twitter.com/1.1/direct_messages.json";

static NSString * const url_friendships_no_retweets_ids = @"https://api.twitter.com/1.1/friendships/no_retweets/ids.json";
static NSString * const url_friendships_update = @"https://api.twitter.com/1.1/friendships/update.json";
static NSString * const url_friendships_outgoing = @"https://api.twitter.com/1.1/friendships/outgoing.json";
static NSString * const url_friendships_incoming = @"https://api.twitter.com/1.1/friendships/incoming.json";
static NSString * const url_friendships_lookup = @"https://api.twitter.com/1.1/friendships/lookup.json";
static NSString * const url_friendships_destroy = @"https://api.twitter.com/1.1/friendships/destroy.json";
static NSString * const url_friendships_create = @"https://api.twitter.com/1.1/friendships/create.json";

static NSString * const url_account_verify_credentials = @"https://api.twitter.com/1.1/account/verify_credentials.json";
static NSString * const url_account_update_profile_colors = @"https://api.twitter.com/1.1/account/update_profile_colors.json";
static NSString * const url_account_update_profile_background_image = @"https://api.twitter.com/1.1/account/update_profile_background_image.json";
static NSString * const url_account_update_profile_image = @"https://api.twitter.com/1.1/account/update_profile_image.json";
static NSString * const url_account_settings = @"https://api.twitter.com/1.1/account/settings.json";
static NSString * const url_account_update_profile = @"https://api.twitter.com/1.1/account/update_profile.json";

static NSString * const url_favorites_list = @"https://api.twitter.com/1.1/favorites/list.json";
static NSString * const url_favorites_create = @"https://api.twitter.com/1.1/favorites/create.json";
static NSString * const url_favorites_destroy = @"https://api.twitter.com/1.1/favorites/destroy.json";

static NSString * const url_application_rate_limit_status = @"https://api.twitter.com/1.1/application/rate_limit_status.json";

static NSString * const url_followers_ids = @"https://api.twitter.com/1.1/followers/ids.json";
static NSString * const url_followers_list = @"https://api.twitter.com/1.1/followers/list.json";

static NSString * const url_friends_ids = @"https://api.twitter.com/1.1/friends/ids.json";
static NSString * const url_friends_list = @"https://api.twitter.com/1.1/friends/list.json";

- (id)listFollowersForUser:(NSString *)user isID:(BOOL)isID withCursor:(NSString *)cursor {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_friends_list];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *skipstatusP = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    OARequestParameter *include_entitiesP = [OARequestParameter requestParameterWithName:@"include_entities" value:self.includeEntities?@"true":@"false"];
    OARequestParameter *screen_nameP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    OARequestParameter *cursorP = [OARequestParameter requestParameterWithName:@"cursor" value:cursor];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:include_entitiesP, skipstatusP, screen_nameP, cursorP, nil]];
}

- (id)listFriendsForUser:(NSString *)user isID:(BOOL)isID withCursor:(NSString *)cursor {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_friends_list];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *skipstatusP = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    OARequestParameter *include_entitiesP = [OARequestParameter requestParameterWithName:@"include_entities" value:self.includeEntities?@"true":@"false"];
    OARequestParameter *screen_nameP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    OARequestParameter *cursorP = [OARequestParameter requestParameterWithName:@"cursor" value:cursor];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:include_entitiesP, skipstatusP, screen_nameP, cursorP, nil]];
}

- (id)searchUsersWithQuery:(NSString *)q andCount:(int)count {
    
    if (count == 0) {
        return nil;
    }
    
    if (q.length == 0) {
        return getBadRequestError();
    }
    
    if (q.length > 1000) {
        q = [q substringToIndex:1000];
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_users_search];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *include_entitiesP = [OARequestParameter requestParameterWithName:@"include_entities" value:self.includeEntities?@"true":@"false"];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    OARequestParameter *qP = [OARequestParameter requestParameterWithName:@"q" value:q];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:include_entitiesP, countP, qP, nil]];
}

- (id)searchTweetsWithQuery:(NSString *)q count:(int)count resultType:(FHSTwitterEngineResultType)resultType unil:(NSDate *)untilDate sinceID:(NSString *)sinceID maxID:(NSString *)maxID {
    
    if (count == 0) {
        return nil;
    }
    
    if (q.length == 0) {
        return getBadRequestError();
    }
    
    if (q.length > 1000) {
        q = [q substringToIndex:1000];
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_search_tweets];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *include_entitiesP = [OARequestParameter requestParameterWithName:@"include_entities" value:self.includeEntities?@"true":@"false"];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    OARequestParameter *untilP = [OARequestParameter requestParameterWithName:@"until" value:nil];
    OARequestParameter *result_typeP = [OARequestParameter requestParameterWithName:@"result_type" value:nil];
    OARequestParameter *qP = [OARequestParameter requestParameterWithName:@"q" value:q];
    
    [self.dateFormatter setDateFormat:@"YYYY-MM-DD"];
    NSString *untilString = [self.dateFormatter stringFromDate:untilDate];
    [self.dateFormatter setDateFormat:@"EEE MMM dd HH:mm:ss ZZZZ yyyy"];
    
    untilP.value = untilString;

    if (resultType == FHSTwitterEngineResultTypeMixed) {
        result_typeP.value = @"mixed";
    } else if (resultType == FHSTwitterEngineResultTypeRecent) {
        result_typeP.value = @"recent";
    } else if (resultType == FHSTwitterEngineResultTypePopular) {
        result_typeP.value = @"popular";
    }
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:countP, include_entitiesP, qP, nil];
    
    if (maxID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"max_id" value:maxID]];
    }
    
    if (sinceID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"since_id" value:sinceID]];
    }
    
    return [self sendGETRequest:request withParameters:params];
}

- (NSError *)createListWithName:(NSString *)name isPrivate:(BOOL)isPrivate description:(NSString *)description {
    
    if (name.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_create];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *nameP = [OARequestParameter requestParameterWithName:@"name" value:name];
    OARequestParameter *isPrivateP = [OARequestParameter requestParameterWithName:@"mode" value:isPrivate?@"private":@"public"];
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:nameP, isPrivateP, nil];
    
    if (description.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"description" value:description]];
    }
    
    return [self sendPOSTRequest:request withParameters:params];
}

- (id)getListWithID:(NSString *)listID {
    
    if (listID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_show];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *listIDP = [OARequestParameter requestParameterWithName:@"list_id" value:listID];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:listIDP, nil]];
}

- (NSError *)changeDescriptionOfListWithID:(NSString *)listID toDescription:(NSString *)newName {
    
    if (listID.length == 0) {
        return getBadRequestError();
    }
    
    if (newName.length == 0 ) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_update];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *listIDP = [OARequestParameter requestParameterWithName:@"list_id" value:listID];
    OARequestParameter *nameP = [OARequestParameter requestParameterWithName:@"description" value:newName];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:listIDP, nameP, nil]];
}

- (NSError *)changeNameOfListWithID:(NSString *)listID toName:(NSString *)newName {
    
    if (listID.length == 0) {
        return getBadRequestError();
    }
    
    if (newName.length == 0 ) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_update];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *listIDP = [OARequestParameter requestParameterWithName:@"list_id" value:listID];
    OARequestParameter *nameP = [OARequestParameter requestParameterWithName:@"name" value:newName];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:listIDP, nameP, nil]];
}

- (NSError *)setModeOfListWithID:(NSString *)listID toPrivate:(BOOL)isPrivate {
    
    if (listID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_update];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *listIDP = [OARequestParameter requestParameterWithName:@"list_id" value:listID];
    OARequestParameter *isPrivateP = [OARequestParameter requestParameterWithName:@"mode" value:isPrivate?@"private":@"public"];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:listIDP, isPrivateP, nil]];
}

- (id)listUsersInListWithID:(NSString *)listID {
    
    if (listID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_members];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *listIDP = [OARequestParameter requestParameterWithName:@"list_id" value:listID];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:listIDP, nil]];
}

- (NSError *)removeUsersFromListWithID:(NSString *)listID users:(NSArray *)users {
    
    if (users.count == 0) {
        return getBadRequestError();
    }
    
    if (users.count > 100) {
        return getBadRequestError();
    }
    
    if (listID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_members_destroy_all];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *screen_name = [OARequestParameter requestParameterWithName:@"screen_name" value:[users componentsJoinedByString:@","]];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:screen_name, nil]];
}

- (NSError *)addUsersToListWithID:(NSString *)listID users:(NSArray *)users {
    
    if (users.count == 0) {
        return getBadRequestError();
    }
    
    if (users.count > 100) {
        return getBadRequestError();
    }
    
    if (listID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_members_create_all];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *screen_name = [OARequestParameter requestParameterWithName:@"screen_name" value:[users componentsJoinedByString:@","]];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:screen_name, nil]];
}

- (id)getTimelineForListWithID:(NSString *)listID count:(int)count {
    return [self getTimelineForListWithID:listID count:count sinceID:nil maxID:nil];
}

- (id)getTimelineForListWithID:(NSString *)listID count:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID {
    return [self getTimelineForListWithID:listID count:count sinceID:sinceID maxID:maxID excludeRetweets:YES excludeReplies:YES];
}

- (id)getTimelineForListWithID:(NSString *)listID count:(int)count excludeRetweets:(BOOL)excludeRetweets excludeReplies:(BOOL)excludeReplies {
    return [self getTimelineForListWithID:listID count:count sinceID:nil maxID:nil excludeRetweets:excludeRetweets excludeReplies:excludeReplies];
}

- (id)getTimelineForListWithID:(NSString *)listID count:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID excludeRetweets:(BOOL)excludeRetweets excludeReplies:(BOOL)excludeReplies {
    
    if (count == 0) {
        return nil;
    }
    
    if (listID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_statuses];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    OARequestParameter *excludeRepliesP = [OARequestParameter requestParameterWithName:@"exclude_replies" value:excludeReplies?@"true":@"false"];
    OARequestParameter *includeRTsP = [OARequestParameter requestParameterWithName:@"include_rts" value:excludeRetweets?@"false":@"true"];
    OARequestParameter *listIDP = [OARequestParameter requestParameterWithName:@"list_id" value:listID];
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:countP, excludeRepliesP, includeRTsP, listIDP, nil];
    
    if (sinceID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"since_id" value:sinceID]];
    }
    
    if (maxID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"max_id" value:maxID]];
    }
    
    return [self sendGETRequest:request withParameters:params];
}

- (id)getListsForUser:(NSString *)user isID:(BOOL)isID {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_lists_list];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:userP, nil]];
}

- (id)getRetweetsForTweet:(NSString *)identifier count:(int)count {
    
    if (count == 0) {
        return nil;
    }
    
    if (identifier.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:[NSString stringWithFormat:@"https://api.twitter.com/1.1/statuses/retweets/%@.json",identifier]];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *identifierP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:identifierP, nil]];
}

- (id)getRetweetedTimelineWithCount:(int)count {
    return [self getRetweetedTimelineWithCount:count sinceID:nil maxID:nil];
}

- (id)getRetweetedTimelineWithCount:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID {
    
    if (count == 0) {
        return nil;
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_statuses_retweets_of_me];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    OARequestParameter *excludeRepliesP = [OARequestParameter requestParameterWithName:@"exclude_replies" value:@"false"];
    OARequestParameter *includeRTsP = [OARequestParameter requestParameterWithName:@"include_rts" value:@"true"];
    
    NSMutableArray *params = [NSMutableArray array];
    [params addObject:countP];
    [params addObject:excludeRepliesP];
    [params addObject:includeRTsP];
    
    if (sinceID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"since_id" value:sinceID]];
    }
    
    if (maxID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"max_id" value:maxID]];
    }
    
    return [self sendGETRequest:request withParameters:params];
}

- (id)getMentionsTimelineWithCount:(int)count {
    return [self getMentionsTimelineWithCount:count sinceID:nil maxID:nil];
}

- (id)getMentionsTimelineWithCount:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID {
    
    if (count == 0) {
        return nil;
    }

    NSURL *baseURL = [NSURL URLWithString:url_statuses_metions_timeline];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    OARequestParameter *excludeRepliesP = [OARequestParameter requestParameterWithName:@"exclude_replies" value:@"false"];
    OARequestParameter *includeRTsP = [OARequestParameter requestParameterWithName:@"include_rts" value:@"true"];

    NSMutableArray *params = [NSMutableArray array];
    [params addObject:countP];
    [params addObject:excludeRepliesP];
    [params addObject:includeRTsP];
    
    if (sinceID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"since_id" value:sinceID]];
    }
    
    if (maxID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"max_id" value:maxID]];
    }
    
    return [self sendGETRequest:request withParameters:params];
}

- (NSError *)postTweet:(NSString *)tweetString withImageData:(NSData *)theData {
    return [self postTweet:tweetString withImageData:theData inReplyTo:nil];
}

- (NSError *)postTweet:(NSString *)tweetString withImageData:(NSData *)theData inReplyTo:(NSString *)irt {
    
    if (tweetString.length == 0) {
        return getBadRequestError();
    }
    
    if (theData.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_statuses_update_with_media];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *statusP = [OARequestParameter requestParameterWithName:@"status" value:tweetString];
    OARequestParameter *mediaP = [OARequestParameter requestParameterWithName:@"media_data[]" value:[theData base64EncodingWithLineLength:0]];
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:statusP, mediaP, nil];
    
    if (irt.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"in_reply_to_status_id" value:irt]];
    }
    
    return [self sendPOSTRequest:request withParameters:params];
}

- (NSError *)destroyTweet:(NSString *)identifier {
    
    if (identifier.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_statuses_destroy];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *identifierP = [OARequestParameter requestParameterWithName:@"id" value:identifier];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:identifierP, nil]];
}

- (id)getDetailsForTweet:(NSString *)identifier {
    
    if (identifier.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_statuses_show];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *identifierP = [OARequestParameter requestParameterWithName:@"id" value:identifier];
    OARequestParameter *includeMyRetweet = [OARequestParameter requestParameterWithName:@"include_my_retweet" value:@"true"];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:includeMyRetweet, identifierP, nil]];
}

- (id)oembedTweet:(NSString *)identifier maxWidth:(float)maxWidth alignmentMode:(FHSTwitterEngineAlignMode)alignmentMode {
    
    if (identifier.length == 0) {
        return getBadRequestError();
    }
    
    NSString *language = [[NSLocale preferredLanguages]objectAtIndex:0];
    NSString *alignment = [[NSArray arrayWithObjects:@"left", @"right", @"center", @"none", nil]objectAtIndex:alignmentMode];
    
    NSURL *baseURL = [NSURL URLWithString:url_statuses_oembed];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *identifierP = [OARequestParameter requestParameterWithName:@"id" value:identifier];
    OARequestParameter *maxWidthP = [OARequestParameter requestParameterWithName:@"maxwidth" value:[NSString stringWithFormat:@"%f",maxWidth]];
    OARequestParameter *languageP= [OARequestParameter requestParameterWithName:@"lang" value:language];
    OARequestParameter *alignmentP = [OARequestParameter requestParameterWithName:@"align" value:alignment];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:identifierP, maxWidthP, languageP,alignmentP, nil]];
}

- (NSError *)retweet:(NSString *)identifier {
    
    if (identifier.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:[NSString stringWithFormat:@"https://api.twitter.com/1.1/statuses/retweet/%@.json",identifier]];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    return [self sendPOSTRequest:request withParameters:nil];
}

- (id)getTimelineForUser:(NSString *)user isID:(BOOL)isID count:(int)count {
    return [self getTimelineForUser:user isID:isID count:count sinceID:nil maxID:nil];
}

- (id)getTimelineForUser:(NSString *)user isID:(BOOL)isID count:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID {
    
    if (count == 0) {
        return nil;
    }
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_statuses_user_timeline];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    OARequestParameter *excludeRepliesP = [OARequestParameter requestParameterWithName:@"exclude_replies" value:@"false"];
    OARequestParameter *includeRTsP = [OARequestParameter requestParameterWithName:@"include_rts" value:@"true"];

    NSMutableArray *params = [NSMutableArray array];
    [params addObject:countP];
    [params addObject:userP];
    [params addObject:excludeRepliesP];
    [params addObject:includeRTsP];
    
    if (sinceID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"since_id" value:sinceID]];
    }
    
    if (maxID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"max_id" value:maxID]];
    }
    
    return [self sendGETRequest:request withParameters:params];
}

- (id)getProfileImageForUsername:(NSString *)username andSize:(FHSTwitterEngineImageSize)size {
    
    if (username.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_users_show];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *usernameP = [OARequestParameter requestParameterWithName:@"screen_name" value:username];
    
    NSArray *params = [NSArray arrayWithObjects:usernameP, nil];
    
    id userShowReturn = [self sendGETRequest:request withParameters:params];
    
    if ([userShowReturn isKindOfClass:[NSError class]]) {
        return [NSError errorWithDomain:[(NSError *)userShowReturn domain] code:[(NSError *)userShowReturn code] userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
    } else if ([userShowReturn isKindOfClass:[NSDictionary class]]) {
        NSString *url = [userShowReturn objectForKey:@"profile_image_url"]; // normal
        
        if (size == 0) { // mini
            url = [url stringByReplacingOccurrencesOfString:@"_normal" withString:@"_mini"];
        } else if (size == 2) { // bigger
            url = [url stringByReplacingOccurrencesOfString:@"_normal" withString:@"_bigger"];
        } else if (size == 3) { // original
            url = [url stringByReplacingOccurrencesOfString:@"_normal" withString:@""];
        }
        
        id ret = [self sendRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:url]]];
        
        if ([ret isKindOfClass:[NSData class]]) {
            return [UIImage imageWithData:(NSData *)ret];
        }

        return ret;
    }
    
    return [NSError errorWithDomain:@"Bad Request: The request you attempted to make messed up royally." code:400 userInfo:nil];
}

- (id)authenticatedUserIsBlocking:(NSString *)user isID:(BOOL)isID {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_blocks_exists];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    OARequestParameter *skipstatusP = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    
    id obj = [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:skipstatusP, userP, nil]];
    
    if ([obj isKindOfClass:[NSError class]]) {
        return obj;
    } else if ([obj isKindOfClass:[NSDictionary class]]) {
        if ([[obj objectForKey:@"error"]isEqualToString:@"You are not blocking this user."]) {
            return @"NO";
        } else {
            return @"YES";
        }
    }
    
    return getBadRequestError();
}

- (id)listBlockedUsers {
    NSURL *baseURL = [NSURL URLWithString:url_blocks_blocking];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *skipstatusP = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:skipstatusP, nil]];
}

- (id)listBlockedIDs {
    NSURL *baseURL = [NSURL URLWithString:url_blocks_blocking_ids];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *stringifyIDsP = [OARequestParameter requestParameterWithName:@"stringify_ids" value:@"true"];
    
    id object = [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:stringifyIDsP, nil]];
    
    if ([object isKindOfClass:[NSDictionary class]]) {
        return [(NSDictionary *)object objectForKey:@"ids"];
    }
    return object;
}

- (id)getLanguages {
    NSURL *baseURL = [NSURL URLWithString:url_help_languages];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    return [self sendGETRequest:request withParameters:nil];
}

- (id)getConfiguration {
    NSURL *baseURL = [NSURL URLWithString:url_help_configuration];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    return [self sendGETRequest:request withParameters:nil];
}

- (NSError *)reportUserAsSpam:(NSString *)user isID:(BOOL)isID {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_users_report_spam];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:userP, nil]];
}

- (id)showDirectMessage:(NSString *)messageID {
    
    if (messageID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_direct_messages_show];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *id_ = [OARequestParameter requestParameterWithName:@"id" value:messageID];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:id_, nil]];
}

- (NSError *)sendDirectMessage:(NSString *)body toUser:(NSString *)user isID:(BOOL)isID {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    if (body.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_direct_messages_new];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *bodyP = [OARequestParameter requestParameterWithName:@"text" value:[body fhs_trimForTwitter]];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:userP, bodyP, nil]];
}

- (id)getSentDirectMessages:(int)count {
    
    if (count == 0) {
        return nil;
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_direct_messages_sent];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:countP, nil]];
}

- (NSError *)deleteDirectMessage:(NSString *)messageID {
    
    if (messageID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_direct_messages_destroy];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *identitifierP = [OARequestParameter requestParameterWithName:@"id" value:messageID];
    OARequestParameter *includeEntitiesP = [OARequestParameter requestParameterWithName:@"include_entities" value:self.includeEntities?@"true":@"false"];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:identitifierP, includeEntitiesP, nil]];
}

- (id)getDirectMessages:(int)count {
    
    if (count == 0) {
        return nil;
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_direct_messages];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    OARequestParameter *skipStatusP = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:countP, skipStatusP, nil]];
}

- (id)getPrivacyPolicy {
    NSURL *baseURL = [NSURL URLWithString:url_help_privacy];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    
    id object = [self sendGETRequest:request withParameters:nil];
    
    if ([object isKindOfClass:[NSDictionary class]]) {
        NSDictionary *dict = (NSDictionary *)object;
        if ([dict.allKeys containsObject:@"privacy"]) {
            return [dict objectForKey:@"privacy"];
        }
    }
    return object;
}

- (id)getTermsOfService {
    NSURL *baseURL = [NSURL URLWithString:url_help_tos];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    
    id object = [self sendGETRequest:request withParameters:nil];
    
    if ([object isKindOfClass:[NSDictionary class]]) {
        NSDictionary *dict = (NSDictionary *)object;
        if ([dict.allKeys containsObject:@"tos"]) {
            return [dict objectForKey:@"tos"];
        }
    }
    return object;
}

- (id)getNoRetweetIDs {
    NSURL *baseURL = [NSURL URLWithString:url_friendships_no_retweets_ids];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *stringifyIDsP = [OARequestParameter requestParameterWithName:@"stringify_ids" value:@"true"];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:stringifyIDsP, nil]];
}

- (NSError *)enableRetweets:(BOOL)enableRTs andDeviceNotifs:(BOOL)devNotifs forUser:(NSString *)user isID:(BOOL)isID {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_friendships_update];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    OARequestParameter *retweetsP = [OARequestParameter requestParameterWithName:@"retweets" value:enableRTs?@"true":@"false"];
    OARequestParameter *deviceP = [OARequestParameter requestParameterWithName:@"device" value:devNotifs?@"true":@"false"];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:userP, retweetsP, deviceP, nil]];
}

- (id)getPendingOutgoingFollowers {
    NSURL *baseURL = [NSURL URLWithString:url_friendships_outgoing];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *stringifyIDsP = [OARequestParameter requestParameterWithName:@"stringify_ids" value:@"true"];
    
    id object = [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:stringifyIDsP, nil]];
    
    if ([object isKindOfClass:[NSDictionary class]]) {
        NSDictionary *dict = (NSDictionary *)object;
        if ([dict.allKeys containsObject:@"ids"]) {
            return [dict objectForKey:@"ids"];
        }
    }
    return object;
}

- (id)getPendingIncomingFollowers {
    NSURL *baseURL = [NSURL URLWithString:url_friendships_incoming];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *stringifyIDsP = [OARequestParameter requestParameterWithName:@"stringify_ids" value:@"true"];
    
    id object = [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:stringifyIDsP, nil]];
    
    if ([object isKindOfClass:[NSDictionary class]]) {
        NSDictionary *dict = (NSDictionary *)object;
        if ([dict.allKeys containsObject:@"ids"]) {
            return [dict objectForKey:@"ids"];
        }
    }
    return object;
}

- (id)lookupFriendshipStatusForUsers:(NSArray *)users areIDs:(BOOL)areIDs {
    
    if (users.count == 0) {
        return nil;
    }
    
    NSMutableArray *returnedDictionaries = [NSMutableArray array];
    NSArray *reqStrings = [self generateRequestStringsFromArray:users];
    
    NSURL *baseURL = [NSURL URLWithString:url_friendships_lookup];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    
    for (NSString *reqString in reqStrings) {
        OARequestParameter *userP = [OARequestParameter requestParameterWithName:areIDs?@"user_id":@"screen_name" value:reqString];
        
        id retObj = [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:userP, nil]];
        
        if ([retObj isKindOfClass:[NSArray class]]) {
            [returnedDictionaries addObjectsFromArray:(NSArray *)retObj];
        } else if ([retObj isKindOfClass:[NSError class]]) {
            return retObj;
        }
    }
    return returnedDictionaries;
}

- (NSError *)unfollowUser:(NSString *)user isID:(BOOL)isID {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_friendships_destroy];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:userP, nil]];
}

- (NSError *)followUser:(NSString *)user isID:(BOOL)isID {
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_friendships_create];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:userP, nil]];
}

- (id)verifyCredentials {
    NSURL *baseURL = [NSURL URLWithString:url_account_verify_credentials];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    return [self sendGETRequest:request withParameters:nil];
}

- (id)getFavoritesForUser:(NSString *)user isID:(BOOL)isID andCount:(int)count {
    return [self getFavoritesForUser:user isID:isID andCount:count sinceID:nil maxID:nil];
}

- (id)getFavoritesForUser:(NSString *)user isID:(BOOL)isID andCount:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID {
    if (count == 0) {
        return nil;
    }
    
    if (user.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_favorites_list];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *countP = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d",count]];
    OARequestParameter *userP = [OARequestParameter requestParameterWithName:isID?@"user_id":@"screen_name" value:user];
    OARequestParameter *includeEntitiesP = [OARequestParameter requestParameterWithName:@"include_entities" value:self.includeEntities?@"true":@"false"];
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:countP, userP, includeEntitiesP, nil];
    
    if (sinceID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"since_id" value:sinceID]];
    }
    
    if (maxID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"max_id" value:maxID]];
    }
    
    return [self sendGETRequest:request withParameters:params];
}

- (NSError *)markTweet:(NSString *)tweetID asFavorite:(BOOL)flag {
    
    if (tweetID.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:flag?url_favorites_create:url_favorites_destroy];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *idP = [OARequestParameter requestParameterWithName:@"id" value:tweetID];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:idP, nil]];
}

- (id)getRateLimitStatus {
    NSURL *baseURL = [NSURL URLWithString:url_application_rate_limit_status];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    return [self sendGETRequest:request withParameters:nil];
}

- (NSError *)updateProfileColorsWithDictionary:(NSDictionary *)dictionary {
    
    // profile_background_color - hex color
    // profile_link_color - hex color
    // profile_sidebar_border_color - hex color
    // profile_sidebar_fill_color - hex color
    // profile_text_color - hex color
    
    NSString *profile_background_color = nil;
    NSString *profile_link_color = nil;
    NSString *profile_sidebar_border_color = nil;
    NSString *profile_sidebar_fill_color = nil;
    NSString *profile_text_color = nil;
    
    if (!dictionary) {
        profile_background_color = @"C0DEED";
        profile_link_color = @"0084B4";
        profile_sidebar_border_color = @"C0DEED";
        profile_sidebar_fill_color = @"DDEEF6";
        profile_text_color = @"333333";
    } else {
        profile_background_color = [dictionary objectForKey:FHSProfileBackgroundColorKey];
        profile_link_color = [dictionary objectForKey:FHSProfileLinkColorKey];
        profile_sidebar_border_color = [dictionary objectForKey:FHSProfileSidebarBorderColorKey];
        profile_sidebar_fill_color = [dictionary objectForKey:FHSProfileSidebarFillColorKey];
        profile_text_color = [dictionary objectForKey:FHSProfileTextColorKey];
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_account_update_profile_colors];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *skipStatus = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:skipStatus, nil];
    
    if (profile_background_color.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"profile_background_color" value:profile_background_color]];
    }
    
    if (profile_link_color.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"profile_link_color" value:profile_link_color]];
    }
    
    if (profile_sidebar_border_color.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"profile_sidebar_border_color" value:profile_sidebar_border_color]];
    }
    
    if (profile_sidebar_fill_color.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"profile_sidebar_fill_color" value:profile_sidebar_fill_color]];
    }
    
    if (profile_text_color.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"profile_text_color" value:profile_text_color]];
    }
    
    return [self sendPOSTRequest:request withParameters:params];
}

- (NSError *)setUseProfileBackgroundImage:(BOOL)shouldUseBGImg {
    NSURL *baseURL = [NSURL URLWithString:url_account_update_profile_background_image];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *skipStatus = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    OARequestParameter *useImage = [OARequestParameter requestParameterWithName:@"profile_use_background_image" value:shouldUseBGImg?@"true":@"false"];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:skipStatus, useImage, nil]];
}

- (NSError *)setProfileBackgroundImageWithImageData:(NSData *)data tiled:(BOOL)isTiled {
    if (data.length == 0) {
        return getBadRequestError();
    }
    
    if (data.length >= 800000) {
        return [NSError errorWithDomain:@"The image you are trying to upload is too large." code:422 userInfo:nil];
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_account_update_profile_background_image];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *tiled = [OARequestParameter requestParameterWithName:@"tiled" value:isTiled?@"true":@"false"];
    OARequestParameter *skipStatus = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    OARequestParameter *useImage = [OARequestParameter requestParameterWithName:@"profile_use_background_image" value:@"true"];
    OARequestParameter *image = [OARequestParameter requestParameterWithName:@"image" value:[data base64EncodingWithLineLength:0]];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:tiled, skipStatus, useImage, image, nil]];
}

- (NSError *)setProfileBackgroundImageWithImageAtPath:(NSString *)file tiled:(BOOL)isTiled {
    return [self setProfileBackgroundImageWithImageData:[NSData dataWithContentsOfFile:file] tiled:isTiled];
}

- (NSError *)setProfileImageWithImageData:(NSData *)data {
    if (data.length == 0) {
        return getBadRequestError();
    }
    
    if (data.length >= 700000) {
        return [NSError errorWithDomain:@"The image you are trying to upload is too large." code:422 userInfo:nil];
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_account_update_profile_image];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *skipStatus = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    OARequestParameter *image = [OARequestParameter requestParameterWithName:@"image" value:[data base64EncodingWithLineLength:0]];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:image, skipStatus, nil]];
}

- (NSError *)setProfileImageWithImageAtPath:(NSString *)file {
    return [self setProfileImageWithImageData:[NSData dataWithContentsOfFile:file]];
}

- (id)getUserSettings {
    NSURL *baseURL = [NSURL URLWithString:url_account_settings];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    return [self sendGETRequest:request withParameters:nil];
}

- (NSError *)updateUserProfileWithDictionary:(NSDictionary *)settings {
    
    if (!settings) {
        return getBadRequestError();
    }
    
    // all of the values are just non-normalized strings. They appear:
    
    //   setting   - length in characters
    // name        -        20
    // url         -        100
    // location    -        30
    // description -        160
    
    NSString *name = [settings objectForKey:FHSProfileNameKey];
    NSString *url = [settings objectForKey:FHSProfileURLKey];
    NSString *location = [settings objectForKey:FHSProfileLocationKey];
    NSString *description = [settings objectForKey:FHSProfileDescriptionKey];
    
    NSURL *baseURL = [NSURL URLWithString:url_account_update_profile];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *skipStatus = [OARequestParameter requestParameterWithName:@"skip_status" value:@"true"];
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:skipStatus, nil];
    
    if (name.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"name" value:name]];
    }
    
    if (url.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"url" value:url]];
    }
    
    if (location.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"location" value:location]];
    }
    
    if (description.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"description" value:description]];
    }
    
    return [self sendPOSTRequest:request withParameters:params];
}

- (NSError *)updateSettingsWithDictionary:(NSDictionary *)settings {
    
    if (!settings) {
        return getBadRequestError();
    }
    
    // Dictionary with keys:
    // All strings... You could have guessed that.
    // sleep_time_enabled - true/false
    // start_sleep_time - UTC time
    // end_sleep_time - UTC time
    // time_zone - Europe/Copenhagen, Pacific/Tongatapu
    // lang - en, it, es
    
    NSString *sleep_time_enabled = [settings objectForKey:@"sleep_time_enabled"];
    NSString *start_sleep_time = [settings objectForKey:@"start_sleep_time"];
    NSString *end_sleep_time = [settings objectForKey:@"end_sleep_time"];
    NSString *time_zone = [settings objectForKey:@"time_zone"];
    NSString *lang = [settings objectForKey:@"lang"];
    
    NSURL *baseURL = [NSURL URLWithString:url_account_settings];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    
    NSMutableArray *params = [NSMutableArray array];
    
    if (sleep_time_enabled.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"sleep_time_enabled" value:sleep_time_enabled]];
    }
    
    if (start_sleep_time.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"start_sleep_time" value:start_sleep_time]];
    }
    
    if (end_sleep_time.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"end_sleep_time" value:end_sleep_time]];
    }
    
    if (time_zone.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"time_zone" value:time_zone]];
    }
    
    if (lang.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"lang" value:lang]];
    }
    
    return [self sendPOSTRequest:request withParameters:params];
}

- (id)lookupUsers:(NSArray *)users areIDs:(BOOL)areIDs {
    
    if (users.count == 0) {
        return nil;
    }
    
    if (users.count > 100) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_users_lookup];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *usernames = [OARequestParameter requestParameterWithName:areIDs?@"user_id":@"screen_name" value:[users componentsJoinedByString:@","]];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:usernames, nil]];
}

- (NSError *)unblock:(NSString *)username {

    if (username.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_blocks_destroy];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *usernameP = [OARequestParameter requestParameterWithName:@"screen_name" value:username];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:usernameP, nil]];
}

- (NSError *)block:(NSString *)username {
    
    if (username.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_blocks_create];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *usernameP = [OARequestParameter requestParameterWithName:@"screen_name" value:username];
    return [self sendPOSTRequest:request withParameters:[NSArray arrayWithObjects:usernameP, nil]];
}

- (id)testService {
    NSURL *baseURL = [NSURL URLWithString:url_help_test];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    
    id retValue = [self sendGETRequest:request withParameters:nil];
    
    if ([retValue isKindOfClass:[NSString class]]) {
        if ([(NSString *)retValue isEqualToString:@"ok"]) {
            return @"YES";
        } else {
            return @"NO";
        }
    } else if ([retValue isKindOfClass:[NSError class]]) {
        return retValue;
    }
    
    return getBadRequestError();
}

- (id)getHomeTimelineSinceID:(NSString *)sinceID count:(int)count {
    
    if (count == 0) {
        return nil;
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_statuses_home_timeline];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *countParam = [OARequestParameter requestParameterWithName:@"count" value:[NSString stringWithFormat:@"%d", count]];
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:countParam, nil];
    
    if (sinceID.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"since_id" value:sinceID]];
    }
    
    return [self sendGETRequest:request withParameters:params];
}

- (NSError *)postTweet:(NSString *)tweetString inReplyTo:(NSString *)inReplyToString {
    
    if (tweetString.length == 0) {
        return getBadRequestError();
    }
    
    NSURL *baseURL = [NSURL URLWithString:url_statuses_update];
    OARequestParameter *status = [OARequestParameter requestParameterWithName:@"status" value:[tweetString fhs_trimForTwitter]];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    
    NSMutableArray *params = [NSMutableArray arrayWithObjects:status, nil];
    
    if (inReplyToString.length > 0) {
        [params addObject:[OARequestParameter requestParameterWithName:@"in_reply_to_status_id" value:inReplyToString]];
    }
    
    return [self sendPOSTRequest:request withParameters:params];
}

- (NSError *)postTweet:(NSString *)tweetString {
    return [self postTweet:tweetString inReplyTo:nil];
}

- (id)getFollowersIDs {
    NSURL *baseURL = [NSURL URLWithString:url_followers_ids];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *param = [OARequestParameter requestParameterWithName:@"screen_name" value:self.loggedInUsername];
    OARequestParameter *stringify_ids = [OARequestParameter requestParameterWithName:@"stringify_ids" value:@"true"];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:param, stringify_ids, nil]];
}

- (id)getFriendsIDs {
    NSURL *baseURL = [NSURL URLWithString:url_friends_ids];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:self.accessToken];
    OARequestParameter *param = [OARequestParameter requestParameterWithName:@"screen_name" value:self.loggedInUsername];
    OARequestParameter *stringify_ids = [OARequestParameter requestParameterWithName:@"stringify_ids" value:@"true"];
    return [self sendGETRequest:request withParameters:[NSArray arrayWithObjects:param, stringify_ids, nil]];
}

- (id)init {
    self = [super init];
    if (self) {
        // Twitter API datestamps are UTC
        // Don't question this code.
        self.dateFormatter = [[[NSDateFormatter alloc]init]autorelease];
        _dateFormatter.locale = [[[NSLocale alloc]initWithLocaleIdentifier:@"en_US"]autorelease];
        _dateFormatter.dateStyle = NSDateFormatterLongStyle;
        _dateFormatter.formatterBehavior = NSDateFormatterBehavior10_4;
        _dateFormatter.dateFormat = @"EEE MMM dd HH:mm:ss ZZZZ yyyy";
    }
    return self;
}

// The shared* class method
+ (FHSTwitterEngine *)sharedEngine {
    @synchronized (self) {
        if (sharedInstance == nil) {
            [[self alloc]init];
        }
    }
    return sharedInstance;
}

// Override stuff to make sure that the singleton is never dealloc'd. Fun.
+ (id)allocWithZone:(NSZone *)zone {
    @synchronized(self) {
        if (sharedInstance == nil) {
            sharedInstance = [super allocWithZone:zone];
            return sharedInstance;
        }
    }
    return nil;
}

- (id)retain {
    return self;
}

- (oneway void)release {
    // Do nothing
}

- (id)autorelease {
    return self;
}

- (NSUInteger)retainCount {
    return NSUIntegerMax;
}

- (NSArray *)generateRequestStringsFromArray:(NSArray *)array {
    
    NSString *initialString = [array componentsJoinedByString:@","];
    
    if (array.count <= 100) {
        return [NSArray arrayWithObjects:initialString, nil];
    }
    
    int offset = 0;
    int remainder = fmod(array.count, 100);
    int numberOfStrings = (array.count-remainder)/100;
    
    NSMutableArray *reqStrs = [NSMutableArray array];
    
    for (int i = 1; i <= numberOfStrings; ++i) {
        NSString *ninetyNinththItem = (NSString *)[array objectAtIndex:(i*100)-1];
        NSRange range = [initialString rangeOfString:ninetyNinththItem];
        int endOffset = range.location+range.length;
        NSRange rangeOfAString = NSMakeRange(offset, endOffset-offset);
        offset = endOffset;
        NSString *endResult = [initialString fhs_stringWithRange:rangeOfAString];
        
        if ([[endResult substringToIndex:1]isEqualToString:@","]) {
            endResult = [endResult substringFromIndex:1];
        }
        
        [reqStrs addObject:endResult];
    }
    
    NSString *remainderString = [initialString stringByReplacingOccurrencesOfString:[reqStrs componentsJoinedByString:@","] withString:@""];
    
    if ([[remainderString substringToIndex:1]isEqualToString:@","]) {
        remainderString = [remainderString substringFromIndex:1];
    }
    
    [reqStrs addObject:remainderString];
    
    return reqStrs;
}

//
// XAuth
//

- (NSError *)getXAuthAccessTokenForUsername:(NSString *)username password:(NSString *)password {
    
    if (password.length == 0) {
        return [NSError errorWithDomain:@"Bad Request: The request you are trying to make is missing parameters." code:400 userInfo:nil];
    }
    
    if (username.length == 0) {
        return [NSError errorWithDomain:@"Bad Request: The request you are trying to make is missing parameters." code:400 userInfo:nil];
    }
    
    NSURL *baseURL = [NSURL URLWithString:@"https://api.twitter.com/oauth/access_token"];
	OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:baseURL consumer:self.consumer token:nil];
    OARequestParameter *x_auth_mode = [OARequestParameter requestParameterWithName:@"x_auth_mode" value:@"client_auth"];
    OARequestParameter *x_auth_username = [OARequestParameter requestParameterWithName:@"x_auth_username" value:username];
    OARequestParameter *x_auth_password = [OARequestParameter requestParameterWithName:@"x_auth_password" value:password];
	[request setHTTPMethod:@"POST"];
    
	[request setParameters:[NSArray arrayWithObjects:x_auth_mode, x_auth_username, x_auth_password, nil]];
    [request prepare];
    
    if (self.shouldClearConsumer) {
        self.shouldClearConsumer = NO;
        self.consumer = nil;
    }
    
    id ret = [self sendRequest:request];
    
    if ([ret isKindOfClass:[NSError class]]) {
        return ret;
    }
    
    NSString *httpBody = [[[NSString alloc]initWithData:(NSData *)ret encoding:NSUTF8StringEncoding]autorelease];
    
    if (httpBody.length > 0) {
        [self storeAccessToken:httpBody];
    } else {
        [self storeAccessToken:nil];
        return [NSError errorWithDomain:@"Twitter messed up and did not return anything for some reason. Please try again later." code:500 userInfo:nil];
    }
    return nil;
}

//
// sendRequest:
//

- (id)sendRequest:(NSURLRequest *)request {
    
    NSHTTPURLResponse *response = nil;
    NSError *error = nil;
    
    NSData *data = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    
    if (error) {
        return error;
    }
    
    if (response == nil) {
        return error;
    }
    
    if (response.statusCode >= 304) {
        return error;
    }
    
    if (data.length == 0) {
        return error;
    }
    
    return data;
}


- (NSError *)sendPOSTRequest:(OAMutableURLRequest *)request withParameters:(NSArray *)params {
    
    if (![self isAuthorized]) {
        [self loadAccessToken];
        if (![self isAuthorized]) {
            return [NSError errorWithDomain:@"You are not authorized via OAuth" code:401 userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
        }
    }
    
    [request setHTTPMethod:@"POST"];
    [request setParameters:params];
    [request prepare];
    
    if (_shouldClearConsumer) {
        self.shouldClearConsumer = NO;
        self.consumer = nil;
    }
    
    id retobj = [self sendRequest:request];
    
    if (retobj == nil) {
        return getNilReturnLengthError();
    }
    
    if ([retobj isKindOfClass:[NSError class]]) {
        return retobj;
    }
    
    id parsedJSONResponse = removeNull([NSJSONSerialization JSONObjectWithData:(NSData *)retobj options:NSJSONReadingMutableContainers error:nil]);
    
    if ([parsedJSONResponse isKindOfClass:[NSDictionary class]]) {
        NSString *errorMessage = [parsedJSONResponse objectForKey:@"error"];
        NSArray *errorArray = [parsedJSONResponse objectForKey:@"errors"];
        if (errorMessage.length > 0) {
            return [NSError errorWithDomain:errorMessage code:[[parsedJSONResponse objectForKey:@"code"]intValue] userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
        } else if (errorArray.count > 0) {
            if (errorArray.count > 1) {
                return [NSError errorWithDomain:@"Multiple Errors" code:1337 userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
            } else {
                NSDictionary *theError = [errorArray objectAtIndex:0];
                return [NSError errorWithDomain:[theError objectForKey:@"message"] code:[[theError objectForKey:@"code"]integerValue] userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
            }
        }
    }
    
    return nil;
}

- (id)sendGETRequest:(OAMutableURLRequest *)request withParameters:(NSArray *)params {
    
    if (![self isAuthorized]) {
        [self loadAccessToken];
        if (![self isAuthorized]) {
            return [NSError errorWithDomain:@"You are not authorized via OAuth" code:401 userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
        }
    }
    
    [request setHTTPMethod:@"GET"];
    [request setParameters:params];
    [request prepare];
    
    if (_shouldClearConsumer) {
        self.shouldClearConsumer = NO;
        self.consumer = nil;
    }
    
    id retobj = [self sendRequest:request];
    
    if (retobj == nil) {
        return getNilReturnLengthError();
    }
    
    if ([retobj isKindOfClass:[NSError class]]) {
        return retobj;
    }
    
    id parsedJSONResponse = removeNull([NSJSONSerialization JSONObjectWithData:(NSData *)retobj options:NSJSONReadingMutableContainers error:nil]);
    
    if ([parsedJSONResponse isKindOfClass:[NSDictionary class]]) {
        NSString *errorMessage = [parsedJSONResponse objectForKey:@"error"];
        NSArray *errorArray = [parsedJSONResponse objectForKey:@"errors"];
        if (errorMessage.length > 0) {
            return [NSError errorWithDomain:errorMessage code:[[parsedJSONResponse objectForKey:@"code"]intValue] userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
        } else if (errorArray.count > 0) {
            if (errorArray.count > 1) {
                return [NSError errorWithDomain:@"Multiple Errors" code:1337 userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
            } else {
                NSDictionary *theError = [errorArray objectAtIndex:0];
                return [NSError errorWithDomain:[theError objectForKey:@"message"] code:[[theError objectForKey:@"code"]integerValue] userInfo:[NSDictionary dictionaryWithObject:request forKey:@"request"]];
            }
        }
    }
    
    return parsedJSONResponse;
}


//
// OAuth
//

- (NSString *)getRequestTokenString {
    NSURL *url = [NSURL URLWithString:@"https://api.twitter.com/oauth/request_token"];
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:url consumer:self.consumer token:nil];
    [request setHTTPMethod:@"POST"];
    [request prepare];
    
    id retobj = [self sendRequest:request];
    
    if ([retobj isKindOfClass:[NSData class]]) {
        return [[[NSString alloc]initWithData:(NSData *)retobj encoding:NSUTF8StringEncoding]autorelease];
    }
    
    return nil;
}

- (BOOL)finishAuthWithRequestToken:(OAToken *)reqToken {

    NSURL *url = [NSURL URLWithString:@"https://api.twitter.com/oauth/access_token"];
    
    OAMutableURLRequest *request = [OAMutableURLRequest requestWithURL:url consumer:self.consumer token:reqToken];
    [request setHTTPMethod:@"POST"];
    [request prepare];
    
    if (_shouldClearConsumer) {
        self.shouldClearConsumer = NO;
        self.consumer = nil;
    }
    
    id retobj = [self sendRequest:request];
    
    if ([retobj isKindOfClass:[NSError class]]) {
        return NO;
    }
    
    NSString *response = [[[NSString alloc]initWithData:(NSData *)retobj encoding:NSUTF8StringEncoding]autorelease];
    
    if (response.length == 0) {
        return NO;
    }
    
    [self storeAccessToken:response];
    
    return YES;
}

//
// Access Token Management
//

- (void)loadAccessToken {
    
    NSString *savedHttpBody = nil;
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(loadAccessToken)]) {
        savedHttpBody = [self.delegate loadAccessToken];
    } else {
        savedHttpBody = [[NSUserDefaults standardUserDefaults]objectForKey:@"SavedAccessHTTPBody"];
    }
    
    self.accessToken = [OAToken tokenWithHTTPResponseBody:savedHttpBody];
    self.loggedInUsername = [self extractValueForKey:@"screen_name" fromHTTPBody:savedHttpBody];
    self.loggedInID = [self extractValueForKey:@"user_id" fromHTTPBody:savedHttpBody];
}

- (void)storeAccessToken:(NSString *)accessTokenZ {
    self.accessToken = [OAToken tokenWithHTTPResponseBody:accessTokenZ];
    self.loggedInUsername = [self extractValueForKey:@"screen_name" fromHTTPBody:accessTokenZ];
    self.loggedInID = [self extractValueForKey:@"user_id" fromHTTPBody:accessTokenZ];
    
    if ([self.delegate respondsToSelector:@selector(storeAccessToken:)]) {
        [self.delegate storeAccessToken:accessTokenZ];
    } else {
        [[NSUserDefaults standardUserDefaults]setObject:accessTokenZ forKey:@"SavedAccessHTTPBody"];
    }
}

- (NSString *)extractValueForKey:(NSString *)target fromHTTPBody:(NSString *)body {
    if (body.length == 0) {
        return nil;
    }
    
    if (target.length == 0) {
        return nil;
    }
	
	NSArray *tuples = [body componentsSeparatedByString:@"&"];
	if (tuples.count < 1) {
        return nil;
    }
	
	for (NSString *tuple in tuples) {
		NSArray *keyValueArray = [tuple componentsSeparatedByString:@"="];
		
		if (keyValueArray.count >= 2) {
			NSString *key = [keyValueArray objectAtIndex:0];
			NSString *value = [keyValueArray objectAtIndex:1];
			
			if ([key isEqualToString:target]) {
                return value;
            }
		}
	}
	
	return nil;
}

- (BOOL)isAuthorized {
    if (!self.consumer) {
        return NO;
    }
    
	if (self.accessToken.key && self.accessToken.secret) {
        if (self.accessToken.key.length > 0 && self.accessToken.secret.length > 0) {
            return YES;
        }
    }
    
	return NO;
}

- (void)clearAccessToken {
    [self storeAccessToken:@""];
	self.accessToken = nil;
    self.loggedInUsername = nil;
}

- (NSDate *)getDateFromTwitterCreatedAt:(NSString *)twitterDate {
    return [self.dateFormatter dateFromString:twitterDate];
}

- (void)clearConsumer {
    self.consumer = nil;
}

- (void)permanentlySetConsumerKey:(NSString *)consumerKey andSecret:(NSString *)consumerSecret {
    self.shouldClearConsumer = NO;
    self.consumer = [OAConsumer consumerWithKey:consumerKey secret:consumerSecret];
}

- (void)temporarilySetConsumerKey:(NSString *)consumerKey andSecret:(NSString *)consumerSecret {
    self.shouldClearConsumer = YES;
    self.consumer = [OAConsumer consumerWithKey:consumerKey secret:consumerSecret];
}

- (void)showOAuthLoginControllerFromViewController:(UIViewController *)sender {
    [self showOAuthLoginControllerFromViewController:sender withCompletion:nil];
}

- (void)showOAuthLoginControllerFromViewController:(UIViewController *)sender withCompletion:(void(^)(BOOL success))block {
    FHSTwitterEngineController *vc = [[[FHSTwitterEngineController alloc]init]autorelease];
    vc.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
    objc_setAssociatedObject(authBlockKey, "FHSTwitterEngineOAuthCompletion", block, OBJC_ASSOCIATION_COPY_NONATOMIC);
    [sender presentModalViewController:vc animated:YES];
}

+ (BOOL)isConnectedToInternet {
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
    
    SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr *)&zeroAddress);
    if (reachability) {
        SCNetworkReachabilityFlags flags;
        BOOL worked = SCNetworkReachabilityGetFlags(reachability, &flags);
        CFRelease(reachability);
        
        if (worked) {
            
            if ((flags & kSCNetworkReachabilityFlagsReachable) == 0) {
                return NO;
            }
            
            if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) == 0) {
                return YES;
            }
            
            
            if ((((flags & kSCNetworkReachabilityFlagsConnectionOnDemand) != 0) || (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0)) {
                if ((flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0) {
                    return YES;
                }
            }
            
            if ((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN) {
                return YES;
            }
        }
        
    }
    return NO;
}

- (void)dealloc {
    [self setConsumer:nil];
    [self setDateFormatter:nil];
    [self setLoggedInUsername:nil];
    [self setLoggedInID:nil];
    [self setDelegate:nil];
    [self setAccessToken:nil];
    [super dealloc];
}

@end

@implementation FHSTwitterEngineController

static NSString * const newPinJS = @"var d = document.getElementById('oauth-pin'); if (d == null) d = document.getElementById('oauth_pin'); if (d) { var d2 = d.getElementsByTagName('code'); if (d2.length > 0) d2[0].innerHTML; }";
static NSString * const oldPinJS = @"var d = document.getElementById('oauth-pin'); if (d == null) d = document.getElementById('oauth_pin'); if (d) d = d.innerHTML; d;";

- (void)loadView {
    [super loadView];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(pasteboardChanged:) name:UIPasteboardChangedNotification object:nil];
    
    self.view = [[[UIView alloc]initWithFrame:CGRectMake(0, 0, 320, 460)]autorelease];
    self.view.backgroundColor = [UIColor grayColor];
    self.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    
    self.theWebView = [[[UIWebView alloc]initWithFrame:CGRectMake(0, 44, 320, 416)]autorelease];
    _theWebView.hidden = YES;
    _theWebView.delegate = self;
    _theWebView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _theWebView.dataDetectorTypes = UIDataDetectorTypeNone;
    _theWebView.backgroundColor = [UIColor darkGrayColor];
    
    self.navBar = [[[UINavigationBar alloc]initWithFrame:CGRectMake(0, 0, 320, 44)]autorelease];
    _navBar.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleBottomMargin;
	
	[self.view addSubview:_theWebView];
	[self.view addSubview:_navBar];
    
	self.blockerView = [[[UIView alloc]initWithFrame:CGRectMake(0, 0, 200, 60)]autorelease];
	_blockerView.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.8];
	_blockerView.center = CGPointMake(self.view.bounds.size.width/2, self.view.bounds.size.height/2);
	_blockerView.clipsToBounds = YES;
    _blockerView.layer.cornerRadius = 10;
    
    self.pinCopyBar = [[[UIToolbar alloc]initWithFrame:CGRectMake(0, 44, self.view.bounds.size.width, 44)]autorelease];
    _pinCopyBar.barStyle = UIBarStyleBlackTranslucent;
    _pinCopyBar.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleBottomMargin;
    _pinCopyBar.items = [NSArray arrayWithObjects:[[[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil]autorelease], [[[UIBarButtonItem alloc]initWithTitle:@"Select and Copy the PIN" style: UIBarButtonItemStylePlain target:nil action: nil]autorelease], [[[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil]autorelease], nil];
	
	UILabel	*label = [[UILabel alloc]initWithFrame:CGRectMake(0, 5, _blockerView.bounds.size.width, 15)];
	label.text = @"Please Wait...";
	label.backgroundColor = [UIColor clearColor];
	label.textColor = [UIColor whiteColor];
	label.textAlignment = UITextAlignmentCenter;
	label.font = [UIFont boldSystemFontOfSize:15];
	[_blockerView addSubview:label];
    [label release];
	
	UIActivityIndicatorView	*spinner = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
	spinner.center = CGPointMake(_blockerView.bounds.size.width/2, (_blockerView.bounds.size.height/2)+10);
	[_blockerView addSubview:spinner];
	[self.view addSubview:_blockerView];
	[spinner startAnimating];
    [spinner release];
	
	UINavigationItem *navItem = [[[UINavigationItem alloc]initWithTitle:@"Twitter Login"]autorelease];
	navItem.leftBarButtonItem = [[[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(close)]autorelease];
	[_navBar pushNavigationItem:navItem animated:NO];
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
    dispatch_async(GCDBackgroundThread, ^{
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
        
        NSString *reqString = [[FHSTwitterEngine sharedEngine]getRequestTokenString];
        
        if (reqString.length == 0) {
            [self dismissModalViewControllerAnimated:YES];
            [pool release];
            return;
        }
        
        self.requestToken = [OAToken tokenWithHTTPResponseBody:reqString];
        NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"https://api.twitter.com/oauth/authorize?oauth_token=%@",_requestToken.key]]];
        
        dispatch_sync(GCDMainThread, ^{
            NSAutoreleasePool *poolTwo = [[NSAutoreleasePool alloc]init];
            [_theWebView loadRequest:request];
            [poolTwo release];
        });
        
        [pool release];
    });
}

- (void)gotPin:(NSString *)pin {
    _requestToken.verifier = pin;
    BOOL ret = [[FHSTwitterEngine sharedEngine]finishAuthWithRequestToken:_requestToken];
    
    void(^block)(BOOL success) = objc_getAssociatedObject(authBlockKey, "FHSTwitterEngineOAuthCompletion");
    objc_removeAssociatedObjects(authBlockKey);
    
    if (block) {
        block(ret);
    }
    
    [self dismissModalViewControllerAnimated:YES];
}

- (void)pasteboardChanged:(NSNotification *)note {
	
	if (![note.userInfo objectForKey:UIPasteboardChangedTypesAddedKey]) {
        return;
    }
    
    NSString *string = [[UIPasteboard generalPasteboard]string];
	
	if (string.length != 7 || !string.fhs_isNumeric) {
        return;
    }
	
	[self gotPin:string];
}

- (NSString *)locatePin {
	NSString *pin = [[_theWebView stringByEvaluatingJavaScriptFromString:newPinJS]stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
	
	if (pin.length == 7) {
		return pin;
	} else {
		pin = [[_theWebView stringByEvaluatingJavaScriptFromString:oldPinJS]stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
		
		if (pin.length == 7) {
			return pin;
		}
	}
	
	return nil;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView {
    _theWebView.userInteractionEnabled = YES;
    NSString *authPin = [self locatePin];
    
    if (authPin.length > 0) {
        [self gotPin:authPin];
        return;
    }
    
    NSString *formCount = [webView stringByEvaluatingJavaScriptFromString:@"document.forms.length"];
    
    if ([formCount isEqualToString:@"0"]) {
        [self showPinCopyPrompt];
    }
	
	[UIView beginAnimations:nil context:nil];
	_blockerView.hidden = YES;
	[UIView commitAnimations];
	
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    
    _theWebView.hidden = NO;
}

- (void)showPinCopyPrompt {
	if (_pinCopyBar.superview) {
        return;
    }
    
	_pinCopyBar.center = CGPointMake(_pinCopyBar.bounds.size.width/2, _pinCopyBar.bounds.size.height/2);
	[self.view insertSubview:_pinCopyBar belowSubview:_navBar];
	
	[UIView beginAnimations:nil context:nil];
    _pinCopyBar.center = CGPointMake(_pinCopyBar.bounds.size.width/2, _navBar.bounds.size.height+_pinCopyBar.bounds.size.height/2);
	[UIView commitAnimations];
}

- (void)webViewDidStartLoad:(UIWebView *)webView {
    _theWebView.userInteractionEnabled = NO;
    [_theWebView setHidden:YES];
    [_blockerView setHidden:NO];
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
    
    if (strstr([request.URL.absoluteString UTF8String], "denied=")) {
        [self dismissModalViewControllerAnimated:YES];
        return NO;
    }
    
    NSData *data = request.HTTPBody;
	char *raw = data?(char *)[data bytes]:"";
	
	if (raw && (strstr(raw, "cancel=") || strstr(raw, "deny="))) {
		[self dismissModalViewControllerAnimated:YES];
		return NO;
	}
    
	return YES;
}

- (void)close {
    [self dismissModalViewControllerAnimated:YES];
}

- (void)dismissModalViewControllerAnimated:(BOOL)animated {
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    [[NSNotificationCenter defaultCenter]removeObserver:self];
    [_theWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@""]]];
    [super dismissModalViewControllerAnimated:animated];
}

- (void)dealloc {
    [self setNavBar:nil];
    [self setBlockerView:nil];
    [self setPinCopyBar:nil];
    [self setTheWebView:nil];
    [self setRequestToken:nil];
    [super dealloc];
}

@end


static char const encodingTable[64] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
    'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/' };

@implementation NSData (Base64)

+ (NSData *)dataWithBase64EncodedString:(NSString *)string {
	return [[[NSData alloc]initWithBase64EncodedString:string]autorelease];
}

- (id)initWithBase64EncodedString:(NSString *)string {
	NSMutableData *mutableData = nil;
    
	if (string) {
		unsigned long ixtext = 0;
		unsigned char ch = 0;
        unsigned char inbuf[4] = {0,0,0,0};
        unsigned char outbuf[3] = {0,0,0};
		short ixinbuf = 0;
		BOOL flignore = NO;
		BOOL flendtext = NO;
        
		NSData *base64Data = [string dataUsingEncoding:NSASCIIStringEncoding];
		const unsigned char *base64Bytes = [base64Data bytes];
		mutableData = [NSMutableData dataWithCapacity:base64Data.length];
		unsigned long lentext = [base64Data length];
        
        while (!(ixtext >= lentext)) {
            
			ch = base64Bytes[ixtext++];
			flignore = NO;
            
			if ((ch >= 'A') && (ch <= 'Z')) {
                ch = ch - 'A';
            } else if ((ch >= 'a') && (ch <= 'z')) {
                ch = ch - 'a' + 26;
            } else if ((ch >= '0') && (ch <= '9')) {
                ch = ch - '0' + 52;
            } else if (ch == '+') {
                ch = 62;
            } else if (ch == '=') {
                flendtext = YES;
            } else if (ch == '/') {
                ch = 63;
            } else {
                flignore = YES;
            }
            
			if (!flignore) {
				short ctcharsinbuf = 3;
				BOOL flbreak = NO;
                
				if (flendtext) {
					if (!ixinbuf) {
                        break;
                    }
                    
					if (ixinbuf == 1 || ixinbuf == 2) {
                        ctcharsinbuf = 1;
                    } else {
                        ctcharsinbuf = 2;
                    }
                    
					ixinbuf = 3;
					flbreak = YES;
				}
                
				inbuf[ixinbuf++] = ch;
                
				if (ixinbuf == 4) {
					ixinbuf = 0;
					outbuf[0] = (inbuf[0] << 2) | ((inbuf[1] & 0x30) >> 4);
					outbuf[1] = ((inbuf[1] & 0x0F) << 4) | ((inbuf[2] & 0x3C) >> 2);
					outbuf[2] = ((inbuf[2] & 0x03) << 6) | (inbuf[3] & 0x3F);
                    
					for (int i = 0; i < ctcharsinbuf; i++) {
						[mutableData appendBytes:&outbuf[i] length:1];
                    }
				}
                
				if (flbreak)  {
                    break;
                }
			}
		}
	}
    
	self = [self initWithData:mutableData];
	return self;
}

- (NSString *)base64EncodingWithLineLength:(unsigned int)lineLength {
    
	const unsigned char	*bytes = [self bytes];
	unsigned long ixtext = 0;
	unsigned long lentext = [self length];
	long ctremaining = 0;
    unsigned char inbuf[3] = {0,0,0};
    unsigned char outbuf[4] = {0,0,0,0};
    
	short charsonline = 0;
    short ctcopy = 0;
	unsigned long ix = 0;
    
    NSMutableString *result = [NSMutableString stringWithCapacity:lentext];
    
	while (YES) {
		ctremaining = lentext-ixtext;
        
		if (ctremaining <= 0) {
            break;
        }
        
		for (int i = 0; i < 3; i++) {
			ix = ixtext + i;
            inbuf[i] = (ix < lentext)?bytes[ix]:0;
		}
        
		outbuf[0] = (inbuf[0] & 0xFC) >> 2;
		outbuf[1] = ((inbuf[0] & 0x03) << 4) | ((inbuf[1] & 0xF0) >> 4);
		outbuf[2] = ((inbuf[1] & 0x0F) << 2) | ((inbuf[2] & 0xC0) >> 6);
		outbuf[3] = inbuf[2] & 0x3F;
        
		switch (ctremaining) {
            case 1:
                ctcopy = 2;
                break;
            case 2:
                ctcopy = 3;
                break;
            default:
                ctcopy = 4;
                break;
		}
        
		for (int i = 0; i < ctcopy; i++) {
			[result appendFormat:@"%c",encodingTable[outbuf[i]]];
        }
        
		for (int i = ctcopy; i < 4; i++) {
            [result appendString:@"="];
        }
        
		ixtext += 3;
		charsonline += 4;
        
		if (lineLength > 0) {
			if (charsonline >= lineLength) {
				charsonline = 0;
				[result appendString:@"\n"];
			}
		}
	}
	return result;
}

@end
