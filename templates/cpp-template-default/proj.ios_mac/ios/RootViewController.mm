/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"

@interface RootViewController()


@property(strong,nonatomic) CCEAGLView *eaglView;

//dismisses the game scene and moves to native iOS screen

//-(void)closeGameScene;
@end
@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
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
    
    cocos2d::Application *app = cocos2d::Application::getInstance();
    
    //initialize the GLView attributes
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();
    
    //initialize the CCEAGLView
    self.eaglView = [CCEAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
    [self.eaglView setMultipleTouchEnabled:NO];

    /*Use the RootViewController to manage the CCEAGLView*/
    
    //insert EAGLView as subview of RootViewController
    [self.view insertSubview:self.eaglView atIndex:0];
    
    //Create a custom event listener to listen to the custom event triggered by HelloWorldScene.cpp and add the event listener to the Director to close the game scene and move to native iOS screen(if present) without quitting the application 
    /*
    cocos2d::EventListenerCustom *_listener = cocos2d::EventListenerCustom::create("game_scene_close_event", [=](cocos2d::EventCustom *gameCustomEvent){
        
        printf("game_scene_close_event\n");
        
        [self closeGameScene];
        
        
    });
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 1);
     
     */
    
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(self.eaglView);
    
    //set the GLView as OpenGLView of the Director
    cocos2d::Director::getInstance()->setOpenGLView(glview);
    
    //run the cocos2d-x game scene
    app->run();
    
    
}


// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (__bridge CCEAGLView *)glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

//dismisses the game scene without quitting the application and navigates to native iOS screen 

/*
-(void)closeGameScene{
    
    cocos2d::Director::getInstance()->end();
    
    [self dismissViewControllerAnimated:YES completion:nil];
}
*/
- (void)viewDidDisappear:(BOOL)animated{
    
    //manually release the CCEAGLView when closing the RootViewController
    self.eaglView = nil;
}
- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

@end
