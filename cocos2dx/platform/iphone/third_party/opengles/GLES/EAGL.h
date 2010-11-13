/*
    Copyright:  (c) 2006-2008 Apple Inc. All rights reserved.
*/

#ifndef _EAGL_H_
#define _EAGL_H_

// HEADER REVISION 14

#include <Foundation/Foundation.h>

#ifdef __cplusplus
#define EAGL_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define EAGL_EXTERN extern __attribute__((visibility ("default")))
#endif

#define EAGL_EXTERN_CLASS __attribute__((visibility("default")))

/************************************************************************/
/* EAGL API Version                                                     */
/************************************************************************/
#define EAGL_MAJOR_VERSION   1
#define EAGL_MINOR_VERSION   0


/************************************************************************/
/* EAGL Enumerated values                                               */
/************************************************************************/

/* EAGL rendering API */
enum
{
	kEAGLRenderingAPIOpenGLES1 = 1,
	kEAGLRenderingAPIOpenGLES2 = 2
};
typedef NSUInteger EAGLRenderingAPI;

/************************************************************************/
/* EAGL Functions                                                       */
/************************************************************************/

EAGL_EXTERN void EAGLGetVersion(unsigned int* major, unsigned int* minor);

/************************************************************************/
/* EAGL Sharegroup                                                      */
/************************************************************************/

EAGL_EXTERN_CLASS
@interface EAGLSharegroup : NSObject
{
@package
	struct _EAGLSharegroupPrivate *_private;
}

@end

/************************************************************************/
/* EAGL Context                                                         */
/************************************************************************/

EAGL_EXTERN_CLASS
@interface EAGLContext : NSObject
{
@package
	struct _EAGLContextPrivate *_private;
}

- (id) initWithAPI:(EAGLRenderingAPI) api;
- (id) initWithAPI:(EAGLRenderingAPI) api sharegroup:(EAGLSharegroup*) sharegroup;

+ (BOOL)            setCurrentContext:(EAGLContext*) context;
+ (EAGLContext*)    currentContext;

@property (readonly) EAGLRenderingAPI   API;
@property (readonly) EAGLSharegroup*    sharegroup;

@end


#endif /* _EAGL_H_ */

