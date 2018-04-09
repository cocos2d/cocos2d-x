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

#import "ShareFacebook.h"
#import "ShareWrapper.h"
#import <FacebookSDK/FacebookSDK.h>
#import "ParseUtils.h"
#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation ShareFacebook

@synthesize mShareInfo;
@synthesize debug = __debug;

/**
 * A function for parsing URL parameters.
 */
- (NSDictionary*)parseURLParams:(NSString *)query {
    NSArray *pairs = [query componentsSeparatedByString:@"&"];
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    for (NSString *pair in pairs) {
        NSArray *kv = [pair componentsSeparatedByString:@"="];
        NSString *val =
        [kv[1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        NSString *key = [kv[0] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        params[key] = val;
    }
    return params;
}

/**
 * shareInfo parameters support both AnySDK style and facebook style
 *  1. AnySDK style
 *      - title
 *      - site
 *      - siteUrl
 *      - text
 *      - imageUrl
 *      - imagePath
 *
 *  2. Facebook style
 *      - caption
 *      - name
 *      - link
 *      - description
 *      - picture
 */
- (void)convertParamsToFBParams:(NSMutableDictionary*) shareInfo {
    // Link type share info
    NSString *link = [shareInfo objectForKey:@"siteUrl"];
    if (!link) {
        link = [shareInfo objectForKey:@"link"];
    }
    else {
        [shareInfo setObject:link forKey:@"link"];
    }
    // Photo type share info
    NSString *photo = [shareInfo objectForKey:@"imageUrl"];
    if (!photo) {
        photo = [shareInfo objectForKey:@"imagePath"];
    }
    if (!photo) {
        photo = [shareInfo objectForKey:@"photo"];
    }
    else {
        [shareInfo setObject:photo forKey:@"photo"];
        [shareInfo setObject:photo forKey:@"picture"];
    }
    
    // Title
    NSString *caption = [shareInfo objectForKey:@"title"];
    if (!caption) {
        link = [shareInfo objectForKey:@"caption"];
    }
    else {
        [shareInfo setObject:caption forKey:@"caption"];
    }
    
    // Site name
    NSString *name = [shareInfo objectForKey:@"site"];
    if (!name) {
        link = [shareInfo objectForKey:@"name"];
    }
    else {
        [shareInfo setObject:name forKey:@"name"];
    }
    
    // Description
    NSString *desc = [shareInfo objectForKey:@"text"];
    if (!desc) {
        link = [shareInfo objectForKey:@"description"];
    }
    else {
        [shareInfo setObject:desc forKey:@"description"];
    }
}

- (void) configDeveloperInfo : (NSMutableDictionary*) cpInfo
{
}

- (void) share: (NSMutableDictionary*) shareInfo
{
    [self convertParamsToFBParams:shareInfo];
    NSString *link = [shareInfo objectForKey:@"link"];
    NSString *photo = [shareInfo objectForKey:@"photo"];
    
    if (link) {
        // Link type share info
        NSString *link = [shareInfo objectForKey:@"link"];
        NSString *caption = [shareInfo objectForKey:@"caption"];
        NSString *name = [shareInfo objectForKey:@"name"];
        NSString *desc = [shareInfo objectForKey:@"description"];
        NSString *photo = [shareInfo objectForKey:@"picture"];
        
        FBLinkShareParams *params = [[FBLinkShareParams alloc] initWithLink:[NSURL URLWithString:link]
                                                                       name:name
                                                                    caption:caption
                                                                description:desc
                                                                    picture:[NSURL URLWithString:photo]];
        
        // If the Facebook app is installed and we can present the share dialog
        if ([FBDialogs canPresentShareDialogWithParams:params]) {
            [self shareLinkDialogFB:params];
        } else {
            // Fallback to web feed dialog
            [self feedDialogWeb:shareInfo];
        }
    }
    else if (photo) {
        NSURL *photoUrl = [NSURL URLWithString:[shareInfo objectForKey:@"photo"]];
        UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:photoUrl]];
        FBPhotoParams *params = [[FBPhotoParams alloc] init];
        params.photos = @[img];
        
        // If the Facebook app is installed and we can present the share dialog
        if ([FBDialogs canPresentShareDialogWithPhotos]) {
            [self sharePhotoDialogFB:params];
        } else {
            NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, facebook sdk cannot present the photo sharing dialog" andKey:@"error_message"];
            [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
        }
    }
    else {
        NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, share target absent or not supported, please add 'siteUrl' or 'imageUrl' in parameters" andKey:@"error_message"];
        [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
    }
}

- (void) setDebugMode: (BOOL) debug
{
    self.debug = debug;
}

- (NSString*) getSDKVersion
{
    return [FBSettings sdkVersion];
}

- (void) setSDKVersion: (NSString *)sdkVersion{
     [FBSettings setSDKVersion:sdkVersion];
}

- (NSString*) getPluginVersion
{
    return @"0.2.0";
}

- (void) dialog: (NSMutableDictionary*) shareInfo
{
    [self convertParamsToFBParams:shareInfo];
    NSString *dialog_type = [shareInfo objectForKey:@"dialog"];
    
    bool not_supported = false;
    
    if ([dialog_type hasSuffix:@"Link"]) {
        // Link type share info
        NSString *link = [shareInfo objectForKey:@"link"];
        NSString *caption = [shareInfo objectForKey:@"caption"];
        NSString *name = [shareInfo objectForKey:@"name"];
        NSString *desc = [shareInfo objectForKey:@"description"];
        NSString *photo = [shareInfo objectForKey:@"picture"];
        
        FBLinkShareParams *params = [[FBLinkShareParams alloc] initWithLink:[NSURL URLWithString:link]
                                                                       name:name
                                                                    caption:caption
                                                                description:desc
                                                                    picture:[NSURL URLWithString:photo]];
        
        // Additional properties
        NSString *place = [shareInfo objectForKey:@"place"];
        if (place) {
            params.place = place;
        }
        NSString *ref = [shareInfo objectForKey:@"reference"];
        if (place) {
            params.ref = ref;
        }
        NSString *to = [shareInfo objectForKey:@"to"];
        if(to){
            NSArray *friends = [to componentsSeparatedByString:@","];
            params.friends = friends;
        }
        if ([dialog_type isEqualToString:@"shareLink"]) {
            // If the Facebook app is installed and we can present the share dialog
            if ([FBDialogs canPresentShareDialogWithParams:params]) {
                [self shareLinkDialogFB:params];
            } else {
                NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, facebook sdk cannot present the link sharing dialog, Facebook app is needed on target device" andKey:@"error_message"];
                [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            }
        }
        else if ([dialog_type isEqualToString:@"messageLink"]) {
            if ([FBDialogs canPresentMessageDialogWithParams:params]) {
                [self messageLinkDialogFB:params];
            }
            else {
                NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, facebook sdk cannot present the link message dialog, Facebook Messenger is needed on target device" andKey:@"error_message"];
                [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            }
        }
        else {
            not_supported = true;
        }
    }
    else if ([dialog_type hasSuffix:@"OpenGraph"]) {
        NSString *type = [shareInfo objectForKey:@"action_type"];
        NSString *previewProperty = [shareInfo objectForKey:@"preview_property_name"];
        NSString *title = [shareInfo objectForKey:@"title"];
        NSString *image = [shareInfo objectForKey:@"image"];
        NSString *link = [shareInfo objectForKey:@"link"];
        NSString *desc = [shareInfo objectForKey:@"description"];
        
        id<FBGraphObject> object = [FBGraphObject openGraphObjectForPostWithType: type
                                                                           title: title
                                                                           image: image
                                                                             url: [NSURL URLWithString:link]
                                                                     description: desc];
        id<FBOpenGraphAction> action = (id<FBOpenGraphAction>)[FBGraphObject graphObject];
        [action setObject:object forKey:previewProperty];
        FBOpenGraphActionParams *params = [[FBOpenGraphActionParams alloc] initWithAction:action
                                                                               actionType:type
                                                                      previewPropertyName:previewProperty];
        
        if ([dialog_type isEqualToString:@"shareOpenGraph"]) {
            if ([FBDialogs canPresentShareDialogWithOpenGraphActionParams:params]) {
                [self shareOpenGraphDialogFB:params];
            } else {
                NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, facebook sdk cannot present the open graph sharing dialog, Facebook app is needed on target device" andKey:@"error_message"];
                [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            }
        }
        else if ([dialog_type isEqualToString:@"messageOpenGraph"]) {
            if ([FBDialogs canPresentMessageDialogWithOpenGraphActionParams:params]) {
                [self messageOpenGraphDialogFB:params];
            } else {
                NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, facebook sdk cannot present the open graph message dialog, Facebook Messenger is needed on target device" andKey:@"error_message"];
                [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            }
        }
        else {
            not_supported = true;
        }
    }
    else if ([dialog_type hasSuffix:@"Photo"]) {
        UIImage *img = [[UIImage alloc] initWithContentsOfFile:[shareInfo objectForKey:@"photo"]];
        if(img ==nil){
            NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, photo can't be found" andKey:@"error_message"];
            [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            return;
        }
        FBPhotoParams *params = [[FBPhotoParams alloc] init];
        params.photos = @[img];
        
        if ([dialog_type isEqualToString:@"sharePhoto"]) {
            if ([FBDialogs canPresentShareDialogWithPhotos]) {
                [self sharePhotoDialogFB:params];
            } else {
                NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, facebook sdk cannot present the photo sharing dialog, Facebook app is needed on target device" andKey:@"error_message"];
                [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            }
        }
        else if ([dialog_type isEqualToString:@"messagePhoto"]) {
            if ([FBDialogs canPresentMessageDialogWithPhotos]) {
                [self messagePhotoDialogFB:params];
            } else {
                NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, facebook sdk cannot present the photo message dialog, Facebook Messenger is needed on target device" andKey:@"error_message"];
                [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            }
        }
        else {
            not_supported = true;
        }
    }
    else if ([dialog_type isEqualToString:@"feedDialog"]) {
        [self feedDialogWeb:shareInfo];
    }
    else {
        not_supported = true;
    }
    
    if (not_supported) {
        NSString *error = [NSString stringWithFormat:@"Share failed, dialog not supported: %@", dialog_type];
        NSString *msg = [ParseUtils MakeJsonStringWithObject:error andKey:@"error_message"];
        [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
    }
}
-(BOOL) canPresentDialogWithParams:(NSMutableDictionary *)shareInfo{
    [self convertParamsToFBParams:shareInfo];
    NSString *dialog_type = [shareInfo objectForKey:@"dialog"];
    
    if ([dialog_type hasSuffix:@"Link"]) {
        NSString *link = [shareInfo objectForKey:@"link"];
        NSString *caption = [shareInfo objectForKey:@"caption"];
        NSString *name = [shareInfo objectForKey:@"name"];
        NSString *desc = [shareInfo objectForKey:@"description"];
        NSString *photo = [shareInfo objectForKey:@"picture"];
        
        FBLinkShareParams *params = [[FBLinkShareParams alloc] initWithLink:[NSURL URLWithString:link]
                                                                       name:name
                                                                    caption:caption
                                                                description:desc
                                                                    picture:[NSURL URLWithString:photo]];
        
        // Additional properties
        NSString *place = [shareInfo objectForKey:@"place"];
        if (place) {
            params.place = place;
        }
        NSString *ref = [shareInfo objectForKey:@"reference"];
        if (place) {
            params.ref = ref;
        }
        
        if ([dialog_type isEqualToString:@"shareLink"]) {
            // If the Facebook app is installed and we can present the share dialog
            return [FBDialogs canPresentShareDialogWithParams:params];
        }
        else if ([dialog_type isEqualToString:@"messageLink"]) {
            return [FBDialogs canPresentMessageDialogWithParams:params];
        }
    }
    else if ([dialog_type hasSuffix:@"OpenGraph"]) {
        NSString *type = [shareInfo objectForKey:@"action_type"];
        NSString *previewProperty = [shareInfo objectForKey:@"preview_property_name"];
        NSString *title = [shareInfo objectForKey:@"title"];
        NSString *image = [shareInfo objectForKey:@"image"];
        NSString *link = [shareInfo objectForKey:@"url"];
        NSString *desc = [shareInfo objectForKey:@"description"];
        
        id<FBGraphObject> object = [FBGraphObject openGraphObjectForPostWithType: type
                                                                           title: title
                                                                           image: image
                                                                             url: [NSURL URLWithString:link]
                                                                     description: desc];
        id<FBOpenGraphAction> action = (id<FBOpenGraphAction>)[FBGraphObject graphObject];
        [action setObject:object forKey:previewProperty];
        FBOpenGraphActionParams *params = [[FBOpenGraphActionParams alloc] initWithAction:action
                                                                               actionType:type
                                                                      previewPropertyName:previewProperty];
        
        if ([dialog_type isEqualToString:@"shareOpenGraph"]) {
             return [FBDialogs canPresentShareDialogWithOpenGraphActionParams:params];
        }
        else if ([dialog_type isEqualToString:@"messageOpenGraph"]) {
            return [FBDialogs canPresentMessageDialogWithOpenGraphActionParams:params];
        }
    }
    else if ([dialog_type hasSuffix:@"Photo"]) {
        UIImage *img = [[UIImage alloc] initWithContentsOfFile:[shareInfo objectForKey:@"photo"]];
        if(img ==nil){
            NSString *msg = [ParseUtils MakeJsonStringWithObject:@"Share failed, photo can't be found" andKey:@"error_message"];
            [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            return false;
        }
        FBPhotoParams *params = [[FBPhotoParams alloc] init];
        params.photos = @[img];
        
        if ([dialog_type isEqualToString:@"sharePhoto"]) {
            return [FBDialogs canPresentShareDialogWithPhotos];
        }
        else if ([dialog_type isEqualToString:@"messagePhoto"]) {
            return [FBDialogs canPresentMessageDialogWithPhotos];
        }
    }
    return false;
}

-(void) showDialog:(NSString *) type widthInfo:(NSMutableDictionary *)shareInfo{
    [FBWebDialogs presentDialogModallyWithSession:[FBSession activeSession] dialog:type parameters:shareInfo handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
        if (error) {
            // Error launching the dialog or publishing a story.
            NSString *errorMsg = [NSString stringWithFormat:@"Share failed: %@", error.description];
            NSString *msg = [ParseUtils MakeJsonStringWithObject:errorMsg andKey:@"error_message"];
            [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
        } else {
            if (result == FBWebDialogResultDialogNotCompleted) {
                // User clicked the "x" icon
                 NSString *msg = [ParseUtils MakeJsonStringWithObject:@"User canceled sharing" andKey:@"error_message"];
                [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
            } else {
                // Handle the publish feed callback
                NSDictionary *urlParams = [self parseURLParams:[resultURL query]];
                if([urlParams objectForKey:@"error_code"] != nil){
                    NSString *msg = [ParseUtils MakeJsonStringWithObject:[urlParams objectForKey:@"error_message"] andKey:@"error_message"];
                    [ShareWrapper onShareResult:self withRet:(int)[urlParams objectForKey:@"error_code"] withMsg:msg];
                    return;
                }

                if (![urlParams valueForKey:@"post_id"]) {
                    // User clicked the Cancel button
                     NSString *msg = [ParseUtils MakeJsonStringWithObject:@"User canceled sharing" andKey:@"error_message"];
                    [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
                } else {
                    // User clicked the Share button
                    NSString *msg = [ParseUtils MakeJsonStringWithObject:[urlParams valueForKey:@"post_id"] andKey:@"post_id"];
                    [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
                }
            }
        }
    }];
}
- (void) shareLinkDialogFB: (FBLinkShareParams*) params
{
    // Present the share dialog
    [FBDialogs presentShareDialogWithParams: params
                                clientState: nil
                                    handler: ^(FBAppCall *call, NSDictionary *results, NSError *error) {
                                        if(error) {
                                            NSString *msg = [ParseUtils MakeJsonStringWithObject:error.description andKey:@"error_message"];
                                            [ShareWrapper onShareResult:self withRet:(int)error.code withMsg:msg];
                                        } else {
                                            if([self checkDialogResult:results]){
                                                NSString *msg = nil;
                                                if([results objectForKey:@"postId"]!=nil){
                                                    NSMutableDictionary *mdic = [NSMutableDictionary dictionaryWithDictionary:results];
                                                    [mdic removeObjectForKey:@"postId"];
                                                    [mdic setObject:[results objectForKey:@"postId"] forKey:@"post_id"];
                                                    msg = [ParseUtils NSDictionaryToNSString:mdic];
                                                }else{
                                                    msg = [ParseUtils NSDictionaryToNSString: results];
                                                }
                                                [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
                                            }
                                        }
                                    }];
}

- (void) shareOpenGraphDialogFB: (FBOpenGraphActionParams*) params
{
    [FBDialogs
     presentShareDialogWithOpenGraphActionParams: params
     clientState: nil
     handler: ^(FBAppCall *call, NSDictionary *results, NSError *error) {
         if(error) {
             NSString *errorMsg = [NSString stringWithFormat:@"Share failed: %@", error.description];
             NSString *msg = [ParseUtils MakeJsonStringWithObject:errorMsg andKey:@"error_message"];
             [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
         } else {
             if([self checkDialogResult:results]){
                 NSString *msg = nil;
                 if([results objectForKey:@"postId"]!=nil){
                     NSMutableDictionary *mdic = [NSMutableDictionary dictionaryWithDictionary:results];
                     [mdic removeObjectForKey:@"postId"];
                     [mdic setObject:[results objectForKey:@"postId"] forKey:@"post_id"];
                     msg = [ParseUtils NSDictionaryToNSString:mdic];
                 }else{
                     msg = [ParseUtils NSDictionaryToNSString: results];
                 }
                 [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
             }
         }
     }];
}

- (void) sharePhotoDialogFB: (FBPhotoParams*) params
{
    // Present the share dialog
    [FBDialogs presentShareDialogWithPhotoParams:params
                                     clientState:nil
                                         handler:^(FBAppCall *call, NSDictionary *results, NSError *error) {
                                             if(error) {
                                                 NSString *msg = [ParseUtils MakeJsonStringWithObject:error.description andKey:@"error_message"];
                                                 [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
                                             } else {
                                                 if([self checkDialogResult:results]){
                                                     NSString *msg = nil;
                                                     if([results objectForKey:@"didComplete"]){
                                                         NSDictionary *dic = [NSDictionary  dictionaryWithObject:[results objectForKey:@"didComplete"] forKey:@"didComplete"];
                                                         msg = [ParseUtils NSDictionaryToNSString:dic];
                                                     }else{
                                                         msg = [ParseUtils NSDictionaryToNSString:results];
                                                     }
                                                     [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
                                                 }
                                             }
                                         }];
}

- (void) messageLinkDialogFB: (FBLinkShareParams*) params
{
    // Present the share dialog
    [FBDialogs presentMessageDialogWithParams: params
                                  clientState: nil
                                      handler: ^(FBAppCall *call, NSDictionary *results, NSError *error) {
                                          if(error) {
                                              NSString *errorMsg = [NSString stringWithFormat:@"Failed to send message: %@", error.description];
                                              NSString *msg = [ParseUtils MakeJsonStringWithObject:errorMsg andKey:@"error_message"];
                                              [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
                                          } else {
                                              if([self checkDialogResult:results]){
                                                  NSString *msg = nil;
                                                  if([results objectForKey:@"didComplete"]){
                                                      NSDictionary *dic = [NSDictionary  dictionaryWithObject:[results objectForKey:@"didComplete"] forKey:@"didComplete"];
                                                      msg = [ParseUtils NSDictionaryToNSString:dic];
                                                  }else{
                                                      msg = [ParseUtils NSDictionaryToNSString:results];
                                                  }
                                                  [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
                                              }
                                          }
                                      }];
}

- (void) messageOpenGraphDialogFB: (FBOpenGraphActionParams*) params
{
    [FBDialogs
     presentMessageDialogWithOpenGraphActionParams:params
     clientState:nil
     handler: ^(FBAppCall *call, NSDictionary *results, NSError *error) {
         if(error) {
             NSString *errorMsg = [NSString stringWithFormat:@"Failed to send message: %@", error.description];
             NSString *msg = [ParseUtils MakeJsonStringWithObject:errorMsg andKey:@"error_message"];
             [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
         } else {
             if([self checkDialogResult:results]){
                 NSString *msg = nil;
                 if([results objectForKey:@"didComplete"]){
                     NSDictionary *dic = [NSDictionary  dictionaryWithObject:[results objectForKey:@"didComplete"] forKey:@"didComplete"];
                     msg = [ParseUtils NSDictionaryToNSString:dic];
                 }else{
                     msg = [ParseUtils NSDictionaryToNSString:results];
                 }
                 [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
             }
         }
     }];
}

- (void) messagePhotoDialogFB: (FBPhotoParams*) params
{
    // Present the share dialog
    [FBDialogs presentMessageDialogWithPhotoParams:params
                                       clientState:nil
                                           handler:^(FBAppCall *call, NSDictionary *results, NSError *error) {
                                               if(error) {
                                                   NSString *errorMsg = [NSString stringWithFormat:@"Failed to send message: %@", error.description];
                                                   NSString *msg = [ParseUtils MakeJsonStringWithObject:errorMsg andKey:@"error_message"];
                                                   [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
                                               } else {
                                                   if([self checkDialogResult:results]){
                                                       NSString *msg = nil;
                                                       if([results objectForKey:@"didComplete"]){
                                                           NSDictionary *dic = [NSDictionary  dictionaryWithObject:[results objectForKey:@"didComplete"] forKey:@"didComplete"];
                                                           msg = [ParseUtils NSDictionaryToNSString:dic];
                                                       }else{
                                                           msg = [ParseUtils NSDictionaryToNSString:results];
                                                       }
                                                       [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
                                                   }
                                               }
                                           }];
}
-(BOOL) checkDialogResult:(NSDictionary *)results{
    if([results valueForKey:@"completionGesture"]!=nil &&![[results valueForKey:@"completionGesture"] isEqualToString:@"cancel"]){
        return true;
    }else{
        NSString  *msg = [ParseUtils MakeJsonStringWithObject:@"User canceled request" andKey:@"error_message"];
        [ShareWrapper onShareResult:self withRet:kShareCancel withMsg:msg];
        return false;
    }
}
- (void) feedDialogWeb: (NSDictionary*) params
{
    [FBWebDialogs
     presentFeedDialogModallyWithSession:[FBSession activeSession]
     parameters:params
     handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
         if (error) {
             // Error launching the dialog or publishing a story.
             NSString *errorMsg = [NSString stringWithFormat:@"Share failed: %@", error.description];
             NSString *msg = [ParseUtils MakeJsonStringWithObject:errorMsg andKey:@"error_message"];
             [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
         } else {
             if (result == FBWebDialogResultDialogNotCompleted) {
                 // User clicked the "x" icon
                 [ShareWrapper onShareResult:self withRet:kShareFail withMsg:@"User canceled sharing"];
             } else {
                 // Handle the publish feed callback
                 NSDictionary *urlParams = [self parseURLParams:[resultURL query]];
                 if([urlParams objectForKey:@"error_code"] != nil){
                     NSString *msg = [ParseUtils MakeJsonStringWithObject:[urlParams objectForKey:@"error_message"] andKey:@"error_message"];
                     [ShareWrapper onShareResult:self withRet:(int)[urlParams objectForKey:@"error_code"] withMsg:msg];
                     return;
                 }

                 if (![urlParams valueForKey:@"post_id"]) {
                     // User clicked the Cancel button
                     [ShareWrapper onShareResult:self withRet:kShareFail withMsg:@"User canceled sharing"];
                 } else {
                     // User clicked the Share button
                     NSString *msg = [ParseUtils MakeJsonStringWithObject:[urlParams valueForKey:@"post_id"] andKey:@"post_id"];
                     [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
                 }
             }
         }
     }];
}

- (void) appRequest: (NSMutableDictionary*) shareInfo
{
    NSString *message = [shareInfo objectForKey:@"message"];
    NSString *title = [shareInfo objectForKey:@"title"];
    NSMutableDictionary *param = [[NSMutableDictionary alloc] init];
    for(NSString *key in shareInfo){
        NSString *item = [shareInfo objectForKey:key];
        if(![@"message" isEqualToString:key]&& ![@"title" isEqualToString:key]){
            [param setObject:item forKey:key];
        }
    }
    
    // Display the requests dialog
    [FBWebDialogs
     presentRequestsDialogModallyWithSession:[FBSession activeSession]
     message: message
     title: title
     parameters: param
     handler: ^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
         if (error) {
             // Error launching the dialog or sending the request.
             NSString *errorMsg = [NSString stringWithFormat:@"Sending request failed: %@", error.description];
             NSString *msg = [ParseUtils MakeJsonStringWithObject:errorMsg andKey:@"error_message"];
             [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
         } else {
             if (result == FBWebDialogResultDialogNotCompleted) {
                 // User clicked the "x" icon
                 NSString *msg = [ParseUtils MakeJsonStringWithObject:@"User canceled request" andKey:@"error_message"];
                 [ShareWrapper onShareResult:self withRet:kShareFail withMsg:msg];
             } else {
                 // Handle the send request callback
                 NSDictionary *urlParams = [self parseURLParams:[resultURL query]];
                 NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
                 if([urlParams objectForKey:@"error_code"] != nil){
                     NSString *msg = [ParseUtils MakeJsonStringWithObject:[urlParams objectForKey:@"error_message"] andKey:@"error_message"];
                     [ShareWrapper onShareResult:self withRet:(int)[urlParams objectForKey:@"error_code"] withMsg:msg];
                     return;
                 }
                 if([urlParams count]>0){
                     int i = 0;
                     NSMutableArray *resultArray = [[NSMutableArray alloc] init];
                     while ([urlParams objectForKey:[NSString stringWithFormat:@"to[%d]",i]]!=nil) {
                         resultArray[i] = [urlParams objectForKey:[NSString stringWithFormat:@"to[%d]",i]];
                         ++i;
                     }
                     if([urlParams valueForKey:@"request"]){
                         [dic setObject:[urlParams objectForKey:@"request"] forKey:@"request"];
                     }
                     if([resultArray count]>0){
                         [dic setObject:resultArray forKey:@"to"];
                     }
                 }
                 if (![urlParams valueForKey:@"request"]) {
                     // User clicked the Cancel button
                     NSString *msg = [ParseUtils MakeJsonStringWithObject:@"User canceled request" andKey:@"error_message"];
                     [ShareWrapper onShareResult:self withRet:(int)error.code withMsg:msg];
                 } else {
                     // User clicked the Send button
                     NSString *msg = [ParseUtils NSDictionaryToNSString:dic];
                     [ShareWrapper onShareResult:self withRet:kShareSuccess withMsg:msg];
                 }
             }
         }
     }];
}

@end