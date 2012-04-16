/*
 * CCControlSliderTest.m
 *
 * Copyright (c) 2011 Yannick Loriot
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */


#import "CCControlSliderTest.h"

@interface CCControlSliderTest ()
@property (nonatomic, retain) CCLabelTTF *displayValueLabel;

- (void)valueChanged:(CCControlSlider *)sender;

@end

@implementation CCControlSliderTest
@synthesize displayValueLabel;

- (void)dealloc
{
    [displayValueLabel release], displayValueLabel = nil;
    
    [super dealloc];
}

- (id)init
{
	if ((self = [super init]))
    {
        CGSize screenSize = [[CCDirector sharedDirector] winSize];
        
		// Add a label in which the slider value will be displayed
		self.displayValueLabel = [CCLabelTTF labelWithString:@"Move the slider thumb!" fontName:@"Marker Felt" fontSize:32];
        displayValueLabel.anchorPoint = ccp(0.5f, -1.0f);
        displayValueLabel.position = ccp(screenSize.width / 2.0f, screenSize.height / 2.0f);
		[self addChild:displayValueLabel];
		
        // Add the slider
		CCControlSlider *slider = [CCControlSlider sliderWithBackgroundFile:@"sliderTrack.png" 
                                                               progressFile:@"sliderProgress.png" 
                                                                  thumbFile:@"sliderThumb.png"];
        slider.anchorPoint = ccp(0.5f, 1.0f);
        slider.minimumValue = 0.0f; // Sets the min value of range
        slider.maximumValue = 5.0f; // Sets the max value of range
        slider.position = ccp(screenSize.width / 2.0f, screenSize.height / 2.0f);
        
        // When the value of the slider will change, the given selector will be call
		[slider addTarget:self action:@selector(valueChanged:) forControlEvents:CCControlEventValueChanged];
        
		[self addChild:slider];	
	}
	return self;
}

#pragma mark -
#pragma CCSliderTestLayer Public Methods

#pragma CCSliderTestLayer Private Methods

- (void)valueChanged:(CCControlSlider *)sender
{
	// Change value of label.
	displayValueLabel.string = [NSString stringWithFormat:@"Slider value = %.02f", sender.value];	
}

@end


