//
//  CCBDirectoryComparer.h
//  CocosBuilder
//
//  Created by Viktor Lidholt on 2/5/13.
//
//

#import <Foundation/Foundation.h>

@interface CCBDirectoryComparer : NSObject
{
}

@property (nonatomic,readonly) NSMutableDictionary* files;

- (void) loadDirectory: (NSString*) dir;

- (NSArray*) diffWithFiles:(NSDictionary*) diffFiles;

@end
