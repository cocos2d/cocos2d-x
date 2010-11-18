/*
    Copyright:  (c) 2006-2008 Apple Inc. All rights reserved.
*/

#ifndef _EAGL_DRAWABLE_H_
#define _EAGL_DRAWABLE_H_

#include <OpenGLES/EAGL.h>

/************************************************************************/
/* Keys for EAGLDrawable drawableProperties dictionary                  */
/*                                                                      */
/* kEAGLDrawablePropertyRetainedBacking:                                */
/*  Type: NSNumber (boolean)                                            */
/*  Legal Values: True/False                                            */
/*  Default Value: False                                                */
/*  Description: True if EAGLDrawable contents are retained after a     */
/*               call to presentRenderbuffer.  False, if they are not   */
/*                                                                      */
/* kEAGLDrawablePropertyColorFormat:                                    */
/*  Type: NSString                                                      */
/*  Legal Values: kEAGLColorFormat*                                     */
/*  Default Value: kEAGLColorFormatRGBA8                                */
/*  Description: Format of pixels in renderbuffer                       */
/************************************************************************/
EAGL_EXTERN NSString * const kEAGLDrawablePropertyRetainedBacking;
EAGL_EXTERN NSString * const kEAGLDrawablePropertyColorFormat;

/************************************************************************/
/* Values for kEAGLDrawablePropertyColorFormat key                      */
/************************************************************************/
EAGL_EXTERN NSString * const kEAGLColorFormatRGB565;
EAGL_EXTERN NSString * const kEAGLColorFormatRGBA8;

/************************************************************************/
/* EAGLDrawable Interface                                               */
/************************************************************************/
@protocol EAGLDrawable

/* Contains keys from kEAGLDrawableProperty* above */
@property(copy) NSDictionary* drawableProperties;

@end

/* Extends EAGLContext interface */
@interface EAGLContext (EAGLContextDrawableAdditions)

/* Attaches an EAGLDrawable as storage for the OpenGL ES renderbuffer object bound to <target> */
- (BOOL)renderbufferStorage:(NSUInteger)target fromDrawable:(id<EAGLDrawable>)drawable;

/* Request the native window system display the OpenGL ES renderbuffer bound to <target> */
- (BOOL)presentRenderbuffer:(NSUInteger)target;

@end /* EAGLDrawable protocol */

#endif /* _EAGL_DRAWABLE_H_ */

