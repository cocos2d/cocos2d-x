//
//  CCVideoUtils_ios_support.m
//
//  Created by Dmitry Matyukhin on 30/01/2012.
//
//  Used source from Gav T (http://www.cocos2d-x.org/boards/7/topics/550)

#import "CCVideoUtils_ios_support.h"

#import <MediaPlayer/MediaPlayer.h>

@implementation CCVideoUtils_iOS

static CCVideoUtils_iOS* shared_ = NULL;

+ (CCVideoUtils_iOS*) shared {
    if (!shared_) {
        shared_ = [[CCVideoUtils_iOS alloc] init];
    }
    return shared_;
}

+ (void)purge {
    [shared_ release], shared_ = nil;
}

MPMoviePlayerViewController *playerViewController=NULL;

int g_iPlayVideoState=0;

- (void)playVideo:(NSString*)filename showControls:(bool)showControls skipByTap:(bool)skipByTap  target:(cocos2d::CCObject*) target
         selector:(cocos2d::SEL_CallFuncN)selector withObject:(cocos2d::CCNode*)object
{
    CCLOGINFO(@"PlayVideo start");
    
    g_iPlayVideoState = 2;
    
    NSURL* url;
    
    if ([filename hasPrefix:@"http://"]) {
        url = [NSURL URLWithString:filename];
    } else {
        NSString* urlString = [[NSBundle mainBundle] pathForResource:filename ofType:nil];
        url = [NSURL fileURLWithPath:urlString];
    }
    
    CGRect rScreen;
    rScreen.origin.x = 0;
    rScreen.origin.y = 0;
    rScreen.size.width = 480;
    rScreen.size.height = 320;
    //rScreen = CGRect::CGRectMake(0,0, 480, 320);        
    
    MPMoviePlayerController *player2 = [[MPMoviePlayerController alloc] 
                                        initWithContentURL:url];
    
    [[NSNotificationCenter defaultCenter] 
     addObserver:self
     selector:@selector(movieFinishedCallback:)
     name:MPMoviePlayerPlaybackDidFinishNotification
     object:player2];
    if ([player2 respondsToSelector:@selector(setUseApplicationAudioSession:)]) {
        [player2 setUseApplicationAudioSession: NO];
    }
    movieplayer = player2;
    m_pTarget = target;
    m_Selector = selector;
    m_pObject = object;
    
    UIView* currentView = [UIApplication sharedApplication].keyWindow;
    
    //---play partial screen---
    //    player2.view.frame = currentView.frame;
    
    
    
    if ([player2 respondsToSelector:@selector(setFullscreen:animated:)]) {  
        player2.fullscreen = true;
        // Use the new 3.2 style API  
        player2.controlStyle = showControls ? MPMovieControlStyleFullscreen : MPMovieControlStyleNone;
        [player2.view setBounds:CGRectMake(0, 0, 480, 320)];
        [player2.view setCenter:CGPointMake(160, 240)];
        [player2.view setTransform:CGAffineTransformMakeRotation(M_PI / 2)];
        
        player2.movieSourceType = MPMovieSourceTypeFile;
        [player2 prepareToPlay];
    } else {
        // Use the old 2.0 style API 
        player2.movieControlMode = showControls ? MPMovieControlModeDefault : MPMovieControlModeHidden;
    }
    
    if ([player2 respondsToSelector:@selector(view)]) {
        if (!showControls && skipByTap) {
            UIButton* skipButton = [UIButton buttonWithType:UIButtonTypeCustom];
            [skipButton addTarget:self action:@selector(skip:) forControlEvents:UIControlEventTouchUpInside];
            skipButton.frame = CGRectMake(0, 0, player2.view.bounds.size.width, player2.view.bounds.size.height);
            //        [skipButton setBackgroundColor:[UIColor redColor]];
            
            [player2.view addSubview:skipButton];
        }
        
        
        [currentView addSubview:player2.view];
        player2.shouldAutoplay=TRUE;
    }
    
    //---play movie---
    [player2 play];
    
    [[UIApplication sharedApplication] setStatusBarHidden:YES animated:NO];
    
    
    g_iPlayVideoState = 1;
    
    CCLOGINFO(@"PlayVideo done");
}

- (void)skip:(UIButton*)button {
    [movieplayer stop];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
- (void) movieFinishedCallback:(NSNotification*) aNotification 
{
    CCLOGINFO(@"movieFinishedCallback");
    MPMoviePlayerController *player = [aNotification object];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackDidFinishNotification object:player];    
    
    if ([player respondsToSelector:@selector(view)]) {
        [player.view removeFromSuperview];
    }
    [player autorelease];    
    g_iPlayVideoState = 0;
    
    
    [[UIApplication sharedApplication] setStatusBarHidden:YES animated:NO];
    
    
    CCLOGINFO(@"movieFinishedCallback done");
    
    movieplayer = nil;
    
    
    if (m_pTarget && m_Selector) {
		(m_pTarget->*m_Selector)(m_pObject);
	}
    
}

@end