/*
 * CCControlColourPickerTest.m
 *
 * Copyright (c) 2012 Yannick Loriot
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

#import "CCControlColourPickerTest.h"

@interface CCControlColourPickerTest ()
@property (nonatomic, retain) CCLabelTTF *colorLabel;

/** Callback for the change value. */
- (void)colourValueChanged:(CCControlColourPicker *)sender;

@end

@implementation CCControlColourPickerTest
@synthesize colorLabel;

- (void)dealloc
{
    [colorLabel release];
    
    [super dealloc];
}

- (id)init
{
	if ((self = [super init]))
    {
        CGSize screenSize = [[CCDirector sharedDirector] winSize];

        CCNode *layer                       = [CCNode node];
        layer.position                      = ccp (screenSize.width / 2, screenSize.height / 2);
        [self addChild:layer z:1];
        
        double layer_width = 0;
        
        // Create the colour picker
        CCControlColourPicker *colourPicker = [CCControlColourPicker colorPicker];
        colourPicker.color                  = ccc3(37, 46, 252);
        colourPicker.position               = ccp (colourPicker.contentSize.width / 2, 0);
        
        // Add it to the layer
        [layer addChild:colourPicker];
        
#if NS_BLOCKS_AVAILABLE
        // Add block for value changed event
        [colourPicker setBlock:^(id sender, CCControlEvent event)
         {
             [self colourValueChanged:sender];
         } 
              forControlEvents:CCControlEventValueChanged];
#else
        // Add the target-action pair
        [colourPicker addTarget:self action:@selector(colourValueChanged:) forControlEvents:CCControlEventValueChanged];
#endif
        
        layer_width += colourPicker.contentSize.width;
        
        // Add the black background for the text
        CCScale9Sprite *background = [CCScale9Sprite spriteWithFile:@"buttonBackground.png"];
        [background setContentSize:CGSizeMake(150, 50)];
        [background setPosition:ccp(layer_width + background.contentSize.width / 2.0f, 0)];
        [layer addChild:background];
        
        layer_width += background.contentSize.width;
        
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
        colorLabel = [CCLabelTTF labelWithString:@"#color" fontName:@"HelveticaNeue-Bold" fontSize:30];
#elif __MAC_OS_X_VERSION_MAX_ALLOWED
        colorLabel = [CCLabelTTF labelWithString:@"#color" fontName:@"Marker Felt" fontSize:30];
#endif
        colorLabel.position = background.position;
        [layer addChild:colorLabel];
        
        // Set the layer size
        layer.contentSize                   = CGSizeMake(layer_width, 0);
        layer.anchorPoint                   = ccp (0.5f, 0.5f);
        
        // Update the color text
        [self colourValueChanged:colourPicker];
	}
	return self;
}

#pragma mark -
#pragma mark CCControlColourPickerTest Public Methods

#pragma mark CCControlColourPickerTest Private Methods

- (void)colourValueChanged:(CCControlColourPicker *)sender
{
    colorLabel.string = [NSString stringWithFormat:@"#%02X%02X%02X",sender.color.r, sender.color.g, sender.color.b];
}

@end
