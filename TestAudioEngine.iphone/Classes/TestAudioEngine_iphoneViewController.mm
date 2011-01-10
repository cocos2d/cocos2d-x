//
//  TestAudioEngine_iphoneViewController.m
//  TestAudioEngine.iphone
//
//  Created by Walzer on 11-1-8.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "TestAudioEngine_iphoneViewController.h"
#include "SimpleAudioEngine.h"

@implementation TestAudioEngine_iphoneViewController



/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {    
    [super viewDidLoad];
    
    // preload background music and effect music
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Effect1.wav");
   
    // button1 play background music
    UIButton *button1 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button1 setTitle:@"play background music" forState:UIControlStateNormal];
    CGRect button1Rect = CGRectMake(10, 30, 200, 20);
    [button1 setFrame:button1Rect];
    [button1 addTarget:self action:@selector(button1Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button2 stop background music
    UIButton *button2 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button2 setTitle:@"stop background music" forState:UIControlStateNormal];
    CGRect button2Rect = CGRectMake(10, 50, 200, 20);
    [button2 setFrame:button2Rect];
    [button2 addTarget:self action:@selector(button2Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button3 pause background music
    UIButton *button3 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button3 setTitle:@"pause background music" forState:UIControlStateNormal];
    CGRect button3Rect = CGRectMake(10, 70, 200, 20);
    [button3 setFrame:button3Rect];
    [button3 addTarget:self action:@selector(button3Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button4 resume background music
    UIButton *button4 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button4 setTitle:@"resume background music" forState:UIControlStateNormal];
    CGRect button4Rect = CGRectMake(10, 90, 200, 20);
    [button4 setFrame:button4Rect];
    [button4 addTarget:self action:@selector(button4Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button5 rewind background music
    UIButton *button5 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button5 setTitle:@"rewind background music" forState:UIControlStateNormal];
    CGRect button5Rect = CGRectMake(10, 110, 200, 20);
    [button5 setFrame:button5Rect];
    [button5 addTarget:self action:@selector(button5Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button6 add background  music volume
    UIButton *button6 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button6 setTitle:@"add background music volume" forState:UIControlStateNormal];
    CGRect button6Rect = CGRectMake(10, 130, 230, 20);
    [button6 setFrame:button6Rect];
    [button6 addTarget:self action:@selector(button6Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button7 sub background music volume
    UIButton *button7 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button7 setTitle:@"sub background music volume" forState:UIControlStateNormal];
    CGRect button7Rect = CGRectMake(10, 150, 230, 20);
    [button7 setFrame:button7Rect];
    [button7 addTarget:self action:@selector(button7Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button8 check if background music is playing
    UIButton *button8 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button8 setTitle:@"is background music playing" forState:UIControlStateNormal];
    CGRect button8Rect = CGRectMake(10, 170, 230, 20);
    [button8 setFrame:button8Rect];
    [button8 addTarget:self action:@selector(button8Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button9 play effect
    UIButton *button9 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button9 setTitle:@"play effect" forState:UIControlStateNormal];
    CGRect button9Rect = CGRectMake(10, 190, 200, 20);
    [button9 setFrame:button9Rect];
    [button9 addTarget:self action:@selector(button9Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button10 add effect music volume
    UIButton *button10 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button10 setTitle:@"add effect music volume" forState:UIControlStateNormal];
    CGRect button10Rect = CGRectMake(10, 210, 200, 20);
    [button10 setFrame:button10Rect];
    [button10 addTarget:self action:@selector(button10Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button11 sub effect music volume
    UIButton *button11 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button11 setTitle:@"sub effect music volume" forState:UIControlStateNormal];
    CGRect button11Rect = CGRectMake(10, 230, 200, 20);
    [button11 setFrame:button11Rect];
    [button11 addTarget:self action:@selector(button11Click:) forControlEvents:UIControlEventTouchUpInside];
    
    // button12 reset
    UIButton *button12 = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button12 setTitle:@"reset" forState:UIControlStateNormal];
    CGRect button12Rect = CGRectMake(10, 250, 200, 20);
    [button12 setFrame:button12Rect];
    [button12 addTarget:self action:@selector(button12Click:) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview:button1];
    [self.view addSubview:button2];
    [self.view addSubview:button3];
    [self.view addSubview:button4];
    [self.view addSubview:button5];
    [self.view addSubview:button6];
    [self.view addSubview:button7];
    [self.view addSubview:button8];
    [self.view addSubview:button9];
    [self.view addSubview:button10];
    [self.view addSubview:button11];
    [self.view addSubview:button12];
}

// play background music
- (void)button1Click:(UIButton*)sender{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
}

// stop background music
- (void)button2Click:(UIButton*)sender{
     CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

// pause background music
- (void)button3Click:(UIButton*)sender{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// resume background music
- (void)button4Click:(UIButton*)sender{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

// rewind background music
- (void)button5Click:(UIButton*)sender{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
}

// add background music volume
- (void)button6Click:(UIButton*)sender{
    int volume = CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
    NSAssert(volume <= 100 && volume >= 0, @"invalid volume");
    
    volume += 1;
    if (volume > 100) {
        volume = 100;
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

// sub  background music volume
- (void)button7Click:(UIButton*)sender{
    int volume = CocosDenshion::SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
    NSAssert(volume <= 100 && volume >= 0, @"invalid volume");
    
    volume -= 1;
    if (volume < 0) {
        volume = 0;
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

// is background music playing
- (void)button8Click:(UIButton*)sender{
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        NSLog(@"background music is playing");
    }
    else {
        NSLog(@"background music is not playing");
    }

}

// play effect
- (void)button9Click:(UIButton*)sender{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Effect1.wav");
}

// add effect music volume
- (void)button10Click:(UIButton*)sender{
    int volume = CocosDenshion::SimpleAudioEngine::sharedEngine()->getEffectsVolume();
    NSAssert(volume <= 100 && volume >= 0, @"invalid volume");
    
    volume += 1;
    if (volume > 100) {
        volume = 100;
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

// sub effect music volume
- (void)button11Click:(UIButton*)sender{
    int volume = CocosDenshion::SimpleAudioEngine::sharedEngine()->getEffectsVolume();
    NSAssert(volume <= 100 && volume >= 0, @"invalid volume");
    
    volume -= 1;
    if (volume < 0) {
        volume = 0;
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

// reset
- (void)button12Click:(UIButton*)sender{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->release();
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

@end
