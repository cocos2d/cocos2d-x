//
//  SSZipArchive.h
//  SSZipArchive
//
//  Created by Sam Soffes on 7/21/10.
//  Copyright (c) Sam Soffes 2010-2011. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "minizip/unzip.h"

@protocol SSZipArchiveDelegate;

@interface SSZipArchive : NSObject

// Unzip
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination;
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination overwrite:(BOOL)overwrite password:(NSString *)password error:(NSError **)error;

+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination delegate:(id<SSZipArchiveDelegate>)delegate;
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination overwrite:(BOOL)overwrite password:(NSString *)password error:(NSError **)error delegate:(id<SSZipArchiveDelegate>)delegate;

// Zip
+ (BOOL)createZipFileAtPath:(NSString *)path withFilesAtPaths:(NSArray *)filenames;

- (id)initWithPath:(NSString *)path;
- (BOOL)open;
- (BOOL)writeFile:(NSString *)path;
- (BOOL)writeData:(NSData *)data filename:(NSString *)filename;
- (BOOL)close;

@end


@protocol SSZipArchiveDelegate <NSObject>

@optional

- (void)zipArchiveWillUnzipArchiveAtPath:(NSString *)path zipInfo:(unz_global_info)zipInfo;
- (void)zipArchiveDidUnzipArchiveAtPath:(NSString *)path zipInfo:(unz_global_info)zipInfo unzippedPath:(NSString *)unzippedPath;

- (void)zipArchiveWillUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath fileInfo:(unz_file_info)fileInfo;
- (void)zipArchiveDidUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath fileInfo:(unz_file_info)fileInfo;

@end
