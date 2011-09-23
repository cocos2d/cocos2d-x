
#import "ES1Renderer.h"
//#import "OpenGL_Internal.h"

#include "support/gl_support/OpenGLES/OpenGLES11/OpenGLES11Context.h"
#include "support/gl_support/OpenGLES/OpenGLES20/OpenGLES20Context.h"

@implementation ES1Renderer

@synthesize context=context_;

- (id) initWithDepthFormat:(unsigned int)depthFormat withPixelFormat:(unsigned int)pixelFormat withSharegroup:(EAGLSharegroup*)sharegroup withMultiSampling:(BOOL) multiSampling withNumberOfSamples:(unsigned int) requestedSamples
{
    if ((self = [super init]))
    {
		if ( sharegroup == nil )
		{
#if CC_OPENGLES20_SUPPORT
			context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
#endif
			if (!context_)
				context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		}
		else
		{
#if CC_OPENGLES20_SUPPORT
			context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 sharegroup:sharegroup];
#endif
			if (!context_)
			context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1 sharegroup:sharegroup];
		}

        if (!context_ || ![EAGLContext setCurrentContext:context_])
        {
            [self release];
            return nil;
        }

		OpenGLES::OpenGLESContext* glContext;
		switch (context_.API) {
			default:
			case kEAGLRenderingAPIOpenGLES1:
				glContext = new OpenGLES::OpenGLES1::OpenGLES11Context;
				break;
			case kEAGLRenderingAPIOpenGLES2:
				glContext = new OpenGLES::OpenGLES2::OpenGLES20Context;
				break;
		}
		cocos2d::CCDirector *director = cocos2d::CCDirector::sharedDirector();
		director->setGLContext(glContext);		

        // Create default framebuffer object. The backing will be allocated for the current layer in -resizeFromLayer
        glContext->glGenFramebuffers(1, &defaultFramebuffer_);
		NSAssert( defaultFramebuffer_, @"Can't create default frame buffer");
        glContext->glGenRenderbuffers(1, &colorRenderbuffer_);
		NSAssert( colorRenderbuffer_, @"Can't create default render buffer");

        glContext->glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer_);
        glContext->glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
        glContext->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer_);

		depthFormat_ = depthFormat;
		
		if( depthFormat_ ) {
			glContext->glGenRenderbuffers(1, &depthBuffer_);
			glContext->glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
			glContext->glRenderbufferStorage(GL_RENDERBUFFER, depthFormat_, 100, 100);
			glContext->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_);

			// default buffer
			glContext->glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
		}
		
		pixelFormat_ = pixelFormat;
		multiSampling_ = multiSampling;	
		if (multiSampling_)
		{
			GLint maxSamplesAllowed;
			glContext->glGetIntegerv(GL_MAX_SAMPLES_APPLE, &maxSamplesAllowed);
			samplesToUse_ = MIN(maxSamplesAllowed,requestedSamples);
			
			/* Create the MSAA framebuffer (offscreen) */
			glContext->glGenFramebuffers(1, &msaaFramebuffer_);
			glContext->glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer_);
			
		}
    }

    return self;
}

- (BOOL)resizeFromLayer:(CAEAGLLayer *)layer
{		
	cocos2d::CCDirector *director = cocos2d::CCDirector::sharedDirector();
	OpenGLES::OpenGLESContext* glContext = director->getGLContext();		

    // Allocate color buffer backing based on the current layer size

    glContext->glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);

	if (![context_ renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer])
	{
		/*CCLOG(@"failed to call context");	*/
	}

    glContext->glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth_);
    glContext->glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight_);

	/*CCLOG(@"cocos2d: surface size: %dx%d", (int)backingWidth_, (int)backingHeight_);*/

	if (multiSampling_)
	{
	        if ( msaaColorbuffer_) 
	        {
                        glContext->glDeleteRenderbuffers(1, &msaaColorbuffer_);
                        msaaColorbuffer_ = 0;
                }
                
		/* Create the offscreen MSAA color buffer.
		 After rendering, the contents of this will be blitted into ColorRenderbuffer */
		
		//msaaFrameBuffer needs to be binded
		glContext->glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer_);
		glContext->glGenRenderbuffers(1, &msaaColorbuffer_);
		glContext->glBindRenderbuffer(GL_RENDERBUFFER, msaaColorbuffer_);
		glContext->glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, samplesToUse_,pixelFormat_ , backingWidth_, backingHeight_);
		glContext->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, msaaColorbuffer_);

		if (glContext->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			/*CCLOG(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));*/
			return NO;
		}
	}
	
	if (depthFormat_) 
	{
		if( ! depthBuffer_ )
			glContext->glGenRenderbuffers(1, &depthBuffer_);
		
		glContext->glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_);
		if( multiSampling_ )
			glContext->glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, samplesToUse_, depthFormat_,backingWidth_, backingHeight_);
		else
			glContext->glRenderbufferStorage(GL_RENDERBUFFER, depthFormat_, backingWidth_, backingHeight_);
		glContext->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_);
		
		// bind color buffer
		glContext->glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
	}
	
	glContext->glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer_);
	
	if (glContext->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		/*CCLOG(@"Failed to make complete framebuffer object %x", glContext->glCheckFramebufferStatus(GL_FRAMEBUFFER));*/
		return NO;
	}

    return YES;
}

-(CGSize) backingSize
{
	return CGSizeMake( backingWidth_, backingHeight_);
}

- (NSString*) description
{
	return [NSString stringWithFormat:@"<%@ = %08X | size = %ix%i>", [self class], self, backingWidth_, backingHeight_];
}


- (void)dealloc
{
	cocos2d::CCDirector *director = cocos2d::CCDirector::sharedDirector();
	OpenGLES::OpenGLESContext* glContext = director->getGLContext();		
	/*CCLOGINFO(@"cocos2d: deallocing %@", self);*/

    // Tear down GL
    if(defaultFramebuffer_)
    {
        glContext->glDeleteFramebuffers(1, &defaultFramebuffer_);
        defaultFramebuffer_ = 0;
    }

    if(colorRenderbuffer_)
    {
        glContext->glDeleteRenderbuffers(1, &colorRenderbuffer_);
        colorRenderbuffer_ = 0;
    }

	if( depthBuffer_ )
	{
		glContext->glDeleteRenderbuffers(1, &depthBuffer_);
		depthBuffer_ = 0;
	}

	if ( msaaColorbuffer_)
	{
		glContext->glDeleteRenderbuffers(1, &msaaColorbuffer_);
		msaaColorbuffer_ = 0;
	}
	
	if ( msaaFramebuffer_)
	{
		glContext->glDeleteRenderbuffers(1, &msaaFramebuffer_);
		msaaFramebuffer_ = 0;
	}
	
    // Tear down context
    if ([EAGLContext currentContext] == context_)
        [EAGLContext setCurrentContext:nil];

    [context_ release];
    context_ = nil;

    [super dealloc];
}

- (unsigned int) colorRenderBuffer
{
	return colorRenderbuffer_;
}

- (unsigned int) defaultFrameBuffer
{
	return defaultFramebuffer_;
}

- (unsigned int) msaaFrameBuffer
{
	return msaaFramebuffer_;	
}

- (unsigned int) msaaColorBuffer
{
	return msaaColorbuffer_;	
}

@end