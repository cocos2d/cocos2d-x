//
//  FHSTwitterEngine.h
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

//
//
//  //// FHSTwitterEngine Version 1.6.1 ////
//    Modified OAuthConsumer Version 1.2.2
//
//


//
// FHSTwitterEngine
// The synchronous Twitter engine that doesn’t suck!!
//

// FHSTwitterEngine is Synchronous
// That means you will have to thread. Boo Hoo.

// Setup
// Just add the FHSTwitterEngine folder to you project.

// USAGE
// See README.markdown

//
// NOTE TO CONTRIBUTORS
// Use NSJSONSerialization with removeNull(). Life is easy that way.
//


#import <Foundation/Foundation.h>

// These are for the dispatch_async() calls that you use to get around the synchronous-ness
#define GCDBackgroundThread dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)
#define GCDMainThread dispatch_get_main_queue()

// oEmbed align modes
typedef enum {
    FHSTwitterEngineAlignModeLeft,
    FHSTwitterEngineAlignModeRight,
    FHSTwitterEngineAlignModeCenter,
    FHSTwitterEngineAlignModeNone
} FHSTwitterEngineAlignMode;

// Image sizes
typedef enum {
    FHSTwitterEngineImageSizeMini, // 24px by 24px
    FHSTwitterEngineImageSizeNormal, // 48x48
    FHSTwitterEngineImageSizeBigger, // 73x73
    FHSTwitterEngineImageSizeOriginal // original size of image
} FHSTwitterEngineImageSize;

typedef enum {
    FHSTwitterEngineResultTypeMixed,
    FHSTwitterEngineResultTypeRecent,
    FHSTwitterEngineResultTypePopular
} FHSTwitterEngineResultType;

// Remove NSNulls from NSDictionary and NSArray
// Credit for this function goes to Conrad Kramer
id removeNull(id rootObject);

extern NSString * const FHSProfileBackgroundColorKey;
extern NSString * const FHSProfileLinkColorKey;
extern NSString * const FHSProfileSidebarBorderColorKey;
extern NSString * const FHSProfileSidebarFillColorKey;
extern NSString * const FHSProfileTextColorKey;

extern NSString * const FHSProfileNameKey;
extern NSString * const FHSProfileURLKey;
extern NSString * const FHSProfileLocationKey;
extern NSString * const FHSProfileDescriptionKey;

@protocol FHSTwitterEngineAccessTokenDelegate <NSObject>

- (void)storeAccessToken:(NSString *)accessToken;
- (NSString *)loadAccessToken;

@end

@class OAToken;
@class OAConsumer;
@class OAMutableURLRequest;

@interface FHSTwitterEngine : NSObject <UIWebViewDelegate>

//
// REST API
//

// statuses/update
- (NSError *)postTweet:(NSString *)tweetString;
- (NSError *)postTweet:(NSString *)tweetString inReplyTo:(NSString *)inReplyToString;

// statuses/home_timeline
- (id)getHomeTimelineSinceID:(NSString *)sinceID count:(int)count;

// help/test
- (id)testService;

// blocks/create
- (NSError *)block:(NSString *)username;

// blocks/destroy
- (NSError *)unblock:(NSString *)username;

// users/lookup
- (id)lookupUsers:(NSArray *)users areIDs:(BOOL)areIDs;

// users/search
- (id)searchUsersWithQuery:(NSString *)q andCount:(int)count;

// account/update_profile_image
- (NSError *)setProfileImageWithImageAtPath:(NSString *)file;
- (NSError *)setProfileImageWithImageData:(NSData *)data;

// account/settings GET and POST
// See FHSTwitterEngine.m For details
- (id)getUserSettings;
- (NSError *)updateSettingsWithDictionary:(NSDictionary *)settings;

// account/update_profile
// See FHSTwitterEngine.m for details
- (NSError *)updateUserProfileWithDictionary:(NSDictionary *)settings;

// account/update_profile_background_image
- (NSError *)setProfileBackgroundImageWithImageData:(NSData *)data tiled:(BOOL)isTiled;
- (NSError *)setProfileBackgroundImageWithImageAtPath:(NSString *)file tiled:(BOOL)isTiled;
- (NSError *)setUseProfileBackgroundImage:(BOOL)shouldUseProfileBackgroundImage;

// account/update_profile_colors
// See FHSTwitterEngine.m for details
// If the dictionary is nil, FHSTwitterEngine resets the values
- (NSError *)updateProfileColorsWithDictionary:(NSDictionary *)dictionary;

// account/rate_limit_status
- (id)getRateLimitStatus;

// favorites/create, favorites/destroy
- (NSError *)markTweet:(NSString *)tweetID asFavorite:(BOOL)flag;

// favorites/list
- (id)getFavoritesForUser:(NSString *)user isID:(BOOL)isID andCount:(int)count;
- (id)getFavoritesForUser:(NSString *)user isID:(BOOL)isID andCount:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID;

// account/verify_credentials
- (id)verifyCredentials;

// friendships/create
- (NSError *)followUser:(NSString *)user isID:(BOOL)isID;

// friendships/destroy
- (NSError *)unfollowUser:(NSString *)user isID:(BOOL)isID;

// friendships/lookup
- (id)lookupFriendshipStatusForUsers:(NSArray *)users areIDs:(BOOL)areIDs;

// friendships/incoming
- (id)getPendingIncomingFollowers;

// friendships/outgoing
- (id)getPendingOutgoingFollowers;

// friendships/update
- (NSError *)enableRetweets:(BOOL)enableRTs andDeviceNotifs:(BOOL)devNotifs forUser:(NSString *)user isID:(BOOL)isID;

// friendships/no_retweet_ids
- (id)getNoRetweetIDs;

// help/tos
- (id)getTermsOfService;

// help/privacy
- (id)getPrivacyPolicy;

// direct_messages
- (id)getDirectMessages:(int)count;

// direct_messages/destroy
- (NSError *)deleteDirectMessage:(NSString *)messageID;

// direct_messages/sent
- (id)getSentDirectMessages:(int)count;

// direct_messages/new
- (NSError *)sendDirectMessage:(NSString *)body toUser:(NSString *)user isID:(BOOL)isID;

// direct_messages/show
- (id)showDirectMessage:(NSString *)messageID;

// users/report_spam
- (NSError *)reportUserAsSpam:(NSString *)user isID:(BOOL)isID;

// help/configuration
- (id)getConfiguration;

// help/languages
- (id)getLanguages;

// blocks/blocking/ids
- (id)listBlockedIDs;

// blocks/blocking
- (id)listBlockedUsers;

// blocks/exists
- (id)authenticatedUserIsBlocking:(NSString *)user isID:(BOOL)isID;

// users/profile_image
- (id)getProfileImageForUsername:(NSString *)username andSize:(FHSTwitterEngineImageSize)size;

// statuses/user_timeline
- (id)getTimelineForUser:(NSString *)user isID:(BOOL)isID count:(int)count;
- (id)getTimelineForUser:(NSString *)user isID:(BOOL)isID count:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID;

// statuses/retweet
- (NSError *)retweet:(NSString *)identifier;

// statuses/oembed
- (id)oembedTweet:(NSString *)identifier maxWidth:(float)maxWidth alignmentMode:(FHSTwitterEngineAlignMode)alignmentMode;

// statuses/show
- (id)getDetailsForTweet:(NSString *)identifier;

// statuses/destroy
- (NSError *)destroyTweet:(NSString *)identifier;

// statuses/update_with_media
- (NSError *)postTweet:(NSString *)tweetString withImageData:(NSData *)theData;
- (NSError *)postTweet:(NSString *)tweetString withImageData:(NSData *)theData inReplyTo:(NSString *)irt;

// statuses/mentions_timeline
- (id)getMentionsTimelineWithCount:(int)count;
- (id)getMentionsTimelineWithCount:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID;

// statuses/retweets_of_me
- (id)getRetweetedTimelineWithCount:(int)count;
- (id)getRetweetedTimelineWithCount:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID;

// statuses/retweets
- (id)getRetweetsForTweet:(NSString *)identifier count:(int)count;

// lists/list
- (id)getListsForUser:(NSString *)user isID:(BOOL)isID;

// lists/statuses
- (id)getTimelineForListWithID:(NSString *)listID count:(int)count;
- (id)getTimelineForListWithID:(NSString *)listID count:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID;
- (id)getTimelineForListWithID:(NSString *)listID count:(int)count excludeRetweets:(BOOL)excludeRetweets excludeReplies:(BOOL)excludeReplies;
- (id)getTimelineForListWithID:(NSString *)listID count:(int)count sinceID:(NSString *)sinceID maxID:(NSString *)maxID excludeRetweets:(BOOL)excludeRetweets excludeReplies:(BOOL)excludeReplies;

// lists/members/create_all
- (NSError *)addUsersToListWithID:(NSString *)listID users:(NSArray *)users;

// lists/members/destroy_all
- (NSError *)removeUsersFromListWithID:(NSString *)listID users:(NSArray *)users;

// lists/members
- (id)listUsersInListWithID:(NSString *)listID;

// lists/update
- (NSError *)setModeOfListWithID:(NSString *)listID toPrivate:(BOOL)isPrivate;
- (NSError *)changeNameOfListWithID:(NSString *)listID toName:(NSString *)newName;
- (NSError *)changeDescriptionOfListWithID:(NSString *)listID toDescription:(NSString *)newName;

// lists/show
- (id)getListWithID:(NSString *)listID;

// lists/create
- (NSError *)createListWithName:(NSString *)name isPrivate:(BOOL)isPrivate description:(NSString *)description;

// tweets/search
- (id)searchTweetsWithQuery:(NSString *)q count:(int)count resultType:(FHSTwitterEngineResultType)resultType unil:(NSDate *)untilDate sinceID:(NSString *)sinceID maxID:(NSString *)maxID;

// followers/ids
- (id)getFollowersIDs;

// followers/list
- (id)listFollowersForUser:(NSString *)user isID:(BOOL)isID withCursor:(NSString *)cursor;

// friends/ids
- (id)getFriendsIDs;

// friends/list
- (id)listFriendsForUser:(NSString *)user isID:(BOOL)isID withCursor:(NSString *)cursor;

//
// Login and Auth
//

// XAuth login
- (NSError *)getXAuthAccessTokenForUsername:(NSString *)username password:(NSString *)password;

// OAuth login
- (void)showOAuthLoginControllerFromViewController:(UIViewController *)sender;
- (void)showOAuthLoginControllerFromViewController:(UIViewController *)sender withCompletion:(void(^)(BOOL success))completionBlock;

// Access Token Mangement
- (void)clearAccessToken;
- (void)loadAccessToken;
- (BOOL)isAuthorized;

// Clear Keys
- (void)clearConsumer;

// sendRequest methods, use these for every request
- (NSError *)sendPOSTRequest:(OAMutableURLRequest *)request withParameters:(NSArray *)params;
- (id)sendGETRequest:(OAMutableURLRequest *)request withParameters:(NSArray *)params;

//
// Misc Methods
//

// Date parser
- (NSDate *)getDateFromTwitterCreatedAt:(NSString *)twitterDate;

// id list generator - returns an array of id/username list strings
- (NSArray *)generateRequestStringsFromArray:(NSArray *)array;

// Temporaryily set keys
// if you don't want your keys in memory, simply use
// this method. You will have to use it before
// making any API calls.
- (void)temporarilySetConsumerKey:(NSString *)consumerKey andSecret:(NSString *)consumerSecret;

// Use to set the consumer key when using the singleton
- (void)permanentlySetConsumerKey:(NSString *)consumerKey andSecret:(NSString *)consumerSecret;

// Singleton, NEVER use the -init method. Ever.
+ (FHSTwitterEngine *)sharedEngine;

// Determines your internet status
+ (BOOL)isConnectedToInternet;

// Determines if entities should be included
@property (nonatomic, assign) BOOL includeEntities;

// Logged in user's username
@property (nonatomic, retain) NSString *loggedInUsername;

// Logged in user's Twitter ID
@property (nonatomic, retain) NSString *loggedInID;

// Will be called to store the accesstoken
@property (nonatomic, assign) id<FHSTwitterEngineAccessTokenDelegate> delegate;

// Access Token
@property (nonatomic, retain) OAToken *accessToken;

@end

@interface NSData (Base64)
+ (NSData *)dataWithBase64EncodedString:(NSString *)string;
- (id)initWithBase64EncodedString:(NSString *)string;
- (NSString *)base64EncodingWithLineLength:(unsigned int)lineLength;
@end

@interface NSString (FHSTwitterEngine)
- (NSString *)fhs_trimForTwitter;
- (NSString *)fhs_stringWithRange:(NSRange)range;
- (BOOL)fhs_isNumeric;
@end
