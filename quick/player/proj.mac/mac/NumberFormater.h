
#import <Foundation/Foundation.h>

@interface NumberFormater : NSFormatter {
	NSString* format;
}

- (void) setFormat:(NSString*)form;
- (NSString*) format;
+(NumberFormater *) formater;
@end
