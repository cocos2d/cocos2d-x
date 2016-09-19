/****************************************************************************
 Copyright (c) 2010      Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Corpyight (c) 2011      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.

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

// Only compile this code on iOS. These files should NOT be included on your Mac project.
// But in case they are included, it won't be compiled.

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import "platform/ios/CCESRenderer-ios.h"

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#import "platform/CCPlatformMacros.h"

@interface CCES2Renderer : NSObject <CCESRenderer>
{
    // The pixel dimensions of the CAEAGLLayer
    GLint backingWidth_;
    GLint backingHeight_;

    unsigned int    samplesToUse_;
    BOOL            multiSampling_;

    unsigned int    depthFormat_;
    unsigned int    pixelFormat_;

    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
    GLuint defaultFramebuffer_;
    GLuint colorRenderbuffer_;
    GLuint depthBuffer_;


    //buffers for MSAA
    GLuint msaaFramebuffer_;
    GLuint msaaColorbuffer_;

    EAGLContext *context_;
}

/** Color Renderbuffer */
@property (nonatomic,readonly) GLuint colorRenderbuffer;

/** Default Renderbuffer */
@property (nonatomic,readonly) GLuint defaultFramebuffer;

/** MSAA Framebuffer */
@property (nonatomic,readonly) GLuint msaaFramebuffer;

/** MSAA Color Buffer */
@property (nonatomic,readonly) GLuint msaaColorbuffer;

/** EAGLContext */
@property (nonatomic,readonly) EAGLContext* context;

- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer;
@end


#endif // CC_PLATFORM_IOS
