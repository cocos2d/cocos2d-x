//
//  ZAttributedString.m
//  FontLabel
//
//  Created by Kevin Ballard on 9/22/09.
//  Copyright 2009 Zynga Game Networks. All rights reserved.
//

#import "ZAttributedString.h"
#import "ZAttributedStringPrivate.h"

@interface ZAttributedString ()
- (NSUInteger)indexOfEffectiveAttributeRunForIndex:(NSUInteger)index;
- (NSDictionary *)attributesAtIndex:(NSUInteger)index effectiveRange:(NSRangePointer)aRange uniquingOnName:(NSString *)attributeName;
- (NSDictionary *)attributesAtIndex:(NSUInteger)index longestEffectiveRange:(NSRangePointer)aRange
                            inRange:(NSRange)rangeLimit uniquingOnName:(NSString *)attributeName;
@end

@interface ZAttributedString ()
@property (nonatomic, readonly) NSArray *attributes;
@end

@implementation ZAttributedString
@synthesize string = _buffer;
@synthesize attributes = _attributes;

- (id)initWithAttributedString:(ZAttributedString *)attr {
    NSParameterAssert(attr != nil);
    if ((self = [super init])) {
        _buffer = [attr->_buffer mutableCopy];
        _attributes = [[NSMutableArray alloc] initWithArray:attr->_attributes copyItems:YES];
    }
    return self;
}

- (id)initWithString:(NSString *)str {
    return [self initWithString:str attributes:nil];
}

- (id)initWithString:(NSString *)str attributes:(NSDictionary *)attributes {
    if ((self = [super init])) {
        _buffer = [str mutableCopy];
        _attributes = [[NSMutableArray alloc] initWithObjects:[ZAttributeRun attributeRunWithIndex:0 attributes:attributes], nil];
    }
    return self;
}

- (id)init {
    return [self initWithString:@"" attributes:nil];
}

- (id)initWithCoder:(NSCoder *)decoder {
    if ((self = [super init])) {
        _buffer = [[decoder decodeObjectForKey:@"buffer"] mutableCopy];
        _attributes = [[decoder decodeObjectForKey:@"attributes"] mutableCopy];
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeObject:_buffer forKey:@"buffer"];
    [aCoder encodeObject:_attributes forKey:@"attributes"];
}

- (id)copyWithZone:(NSZone *)zone {
    return [self retain];
}

- (id)mutableCopyWithZone:(NSZone *)zone {
    return [(ZMutableAttributedString *)[ZMutableAttributedString allocWithZone:zone] initWithAttributedString:self];
}

- (NSUInteger)length {
    return [_buffer length];
}

- (NSString *)description {
    NSMutableArray *components = [NSMutableArray arrayWithCapacity:[_attributes count]*2];
    NSRange range = NSMakeRange(0, 0);
    for (NSUInteger i = 0; i <= [_attributes count]; i++) {
        range.location = NSMaxRange(range);
        ZAttributeRun *run;
        if (i < [_attributes count]) {
            run = [_attributes objectAtIndex:i];
            range.length = run.index - range.location;
        } else {
            run = nil;
            range.length = [_buffer length] - range.location;
        }
        if (range.length > 0) {
            [components addObject:[NSString stringWithFormat:@"\"%@\"", [_buffer substringWithRange:range]]];
        }
        if (run != nil) {
            NSMutableArray *attrDesc = [NSMutableArray arrayWithCapacity:[run.attributes count]];
            for (id key in run.attributes) {
                [attrDesc addObject:[NSString stringWithFormat:@"%@: %@", key, [run.attributes objectForKey:key]]];
            }
            [components addObject:[NSString stringWithFormat:@"{%@}", [attrDesc componentsJoinedByString:@", "]]];
        }
    }
    return [NSString stringWithFormat:@"%@", [components componentsJoinedByString:@" "]];
}

- (id)attribute:(NSString *)attributeName atIndex:(NSUInteger)index effectiveRange:(NSRangePointer)aRange {
    NSParameterAssert(attributeName != nil);
    return [[self attributesAtIndex:index effectiveRange:aRange uniquingOnName:attributeName] objectForKey:attributeName];
}

- (id)attribute:(NSString *)attributeName atIndex:(NSUInteger)index longestEffectiveRange:(NSRangePointer)aRange inRange:(NSRange)rangeLimit {
    NSParameterAssert(attributeName != nil);
    return [[self attributesAtIndex:index longestEffectiveRange:aRange inRange:rangeLimit uniquingOnName:attributeName] objectForKey:attributeName];
}

- (ZAttributedString *)attributedSubstringFromRange:(NSRange)aRange {
    if (NSMaxRange(aRange) > [_buffer length]) {
        @throw [NSException exceptionWithName:NSRangeException reason:@"range was outisde of the attributed string" userInfo:nil];
    }
    ZMutableAttributedString *newStr = [self mutableCopy];
    if (aRange.location > 0) {
        [newStr deleteCharactersInRange:NSMakeRange(0, aRange.location)];
    }
    if (NSMaxRange(aRange) < [_buffer length]) {
        [newStr deleteCharactersInRange:NSMakeRange(aRange.length, [_buffer length] - NSMaxRange(aRange))];
    }
    return [newStr autorelease];
}

- (NSDictionary *)attributesAtIndex:(NSUInteger)index effectiveRange:(NSRangePointer)aRange {
    return [NSDictionary dictionaryWithDictionary:[self attributesAtIndex:index effectiveRange:aRange uniquingOnName:nil]];
}

- (NSDictionary *)attributesAtIndex:(NSUInteger)index longestEffectiveRange:(NSRangePointer)aRange inRange:(NSRange)rangeLimit {
    return [NSDictionary dictionaryWithDictionary:[self attributesAtIndex:index longestEffectiveRange:aRange inRange:rangeLimit uniquingOnName:nil]];
}

#if Z_BLOCKS
// Warning: this code has not been tested. The only guarantee is that it compiles.
- (void)enumerateAttribute:(NSString *)attrName inRange:(NSRange)enumerationRange options:(ZAttributedStringEnumerationOptions)opts
                usingBlock:(void (^)(id, NSRange, BOOL*))block {
    if (opts & ZAttributedStringEnumerationLongestEffectiveRangeNotRequired) {
        [self enumerateAttributesInRange:enumerationRange options:opts usingBlock:^(NSDictionary *attrs, NSRange range, BOOL *stop) {
            id value = [attrs objectForKey:attrName];
            if (value != nil) {
                block(value, range, stop);
            }
        }];
    } else {
        __block id oldValue = nil;
        __block NSRange effectiveRange = NSMakeRange(0, 0);
        [self enumerateAttributesInRange:enumerationRange options:opts usingBlock:^(NSDictionary *attrs, NSRange range, BOOL *stop) {
            id value = [attrs objectForKey:attrName];
            if (oldValue == nil) {
                oldValue = value;
                effectiveRange = range;
            } else if (value != nil && [oldValue isEqual:value]) {
                // combine the attributes
                effectiveRange = NSUnionRange(effectiveRange, range);
            } else {
                BOOL innerStop = NO;
                block(oldValue, effectiveRange, &innerStop);
                if (innerStop) {
                    *stop = YES;
                    oldValue = nil;
                } else {
                    oldValue = value;
                }
            }
        }];
        if (oldValue != nil) {
            BOOL innerStop = NO; // necessary for the block, but unused
            block(oldValue, effectiveRange, &innerStop);
        }
    }
}

- (void)enumerateAttributesInRange:(NSRange)enumerationRange options:(ZAttributedStringEnumerationOptions)opts
                        usingBlock:(void (^)(NSDictionary*, NSRange, BOOL*))block {
    // copy the attributes so we can mutate the string if necessary during enumeration
    // also clip the array during copy to only the subarray of attributes that cover the requested range
    NSArray *attrs;
    if (NSEqualRanges(enumerationRange, NSMakeRange(0, 0))) {
        attrs = [NSArray arrayWithArray:_attributes];
    } else {
        // in this binary search, last is the first run after the range
        NSUInteger first = 0, last = [_attributes count];
        while (last > first+1) {
            NSUInteger pivot = (last + first) / 2;
            ZAttributeRun *run = [_attributes objectAtIndex:pivot];
            if (run.index < enumerationRange.location) {
                first = pivot;
            } else if (run.index >= NSMaxRange(enumerationRange)) {
                last = pivot;
            }
        }
        attrs = [_attributes subarrayWithRange:NSMakeRange(first, last-first)];
    }
    if (opts & ZAttributedStringEnumerationReverse) {
        NSUInteger end = [_buffer length];
        for (ZAttributeRun *run in [attrs reverseObjectEnumerator]) {
            BOOL stop = NO;
            NSUInteger start = run.index;
            // clip to enumerationRange
            start = MAX(start, enumerationRange.location);
            end = MIN(end, NSMaxRange(enumerationRange));
            block(run.attributes, NSMakeRange(start, end - start), &stop);
            if (stop) break;
            end = run.index;
        }
    } else {
        NSUInteger start = 0;
        ZAttributeRun *run = [attrs objectAtIndex:0];
        NSInteger offset = 0;
        NSInteger oldLength = [_buffer length];
        for (NSUInteger i = 1;;i++) {
            NSUInteger end;
            if (i >= [attrs count]) {
                end = oldLength;
            } else {
                end = [[attrs objectAtIndex:i] index];
            }
            BOOL stop = NO;
            NSUInteger clippedStart = MAX(start, enumerationRange.location);
            NSUInteger clippedEnd = MIN(end, NSMaxRange(enumerationRange));
            block(run.attributes, NSMakeRange(clippedStart + offset, clippedEnd - start), &stop);
            if (stop || i >= [attrs count]) break;
            start = end;
            NSUInteger newLength = [_buffer length];
            offset += (newLength - oldLength);
            oldLength = newLength;
        }
    }
}
#endif

- (BOOL)isEqualToAttributedString:(ZAttributedString *)otherString {
    return ([_buffer isEqualToString:otherString->_buffer] && [_attributes isEqualToArray:otherString->_attributes]);
}

- (BOOL)isEqual:(id)object {
    return [object isKindOfClass:[ZAttributedString class]] && [self isEqualToAttributedString:(ZAttributedString *)object];
}

#pragma mark -

- (NSUInteger)indexOfEffectiveAttributeRunForIndex:(NSUInteger)index {
    NSUInteger first = 0, last = [_attributes count];
    while (last > first + 1) {
        NSUInteger pivot = (last + first) / 2;
        ZAttributeRun *run = [_attributes objectAtIndex:pivot];
        if (run.index > index) {
            last = pivot;
        } else if (run.index < index) {
            first = pivot;
        } else {
            first = pivot;
            break;
        }
    }
    return first;
}

- (NSDictionary *)attributesAtIndex:(NSUInteger)index effectiveRange:(NSRangePointer)aRange uniquingOnName:(NSString *)attributeName {
    if (index >= [_buffer length]) {
        @throw [NSException exceptionWithName:NSRangeException reason:@"index beyond range of attributed string" userInfo:nil];
    }
    NSUInteger runIndex = [self indexOfEffectiveAttributeRunForIndex:index];
    ZAttributeRun *run = [_attributes objectAtIndex:runIndex];
    if (aRange != NULL) {
        aRange->location = run.index;
        runIndex++;
        if (runIndex < [_attributes count]) {
            aRange->length = [[_attributes objectAtIndex:runIndex] index] - aRange->location;
        } else {
            aRange->length = [_buffer length] - aRange->location;
        }
    }
    return run.attributes;
}
- (NSDictionary *)attributesAtIndex:(NSUInteger)index longestEffectiveRange:(NSRangePointer)aRange
                            inRange:(NSRange)rangeLimit uniquingOnName:(NSString *)attributeName {
    if (index >= [_buffer length]) {
        @throw [NSException exceptionWithName:NSRangeException reason:@"index beyond range of attributed string" userInfo:nil];
    } else if (NSMaxRange(rangeLimit) > [_buffer length]) {
        @throw [NSException exceptionWithName:NSRangeException reason:@"rangeLimit beyond range of attributed string" userInfo:nil];
    }
    NSUInteger runIndex = [self indexOfEffectiveAttributeRunForIndex:index];
    ZAttributeRun *run = [_attributes objectAtIndex:runIndex];
    if (aRange != NULL) {
        if (attributeName != nil) {
            id value = [run.attributes objectForKey:attributeName];
            NSUInteger endRunIndex = runIndex+1;
            runIndex--;
            // search backwards
            while (1) {
                if (run.index <= rangeLimit.location) {
                    break;
                }
                ZAttributeRun *prevRun = [_attributes objectAtIndex:runIndex];
                id prevValue = [prevRun.attributes objectForKey:attributeName];
                if (prevValue == value || (value != nil && [prevValue isEqual:value])) {
                    runIndex--;
                    run = prevRun;
                } else {
                    break;
                }
            }
            // search forwards
            ZAttributeRun *endRun = nil;
            while (endRunIndex < [_attributes count]) {
                ZAttributeRun *nextRun = [_attributes objectAtIndex:endRunIndex];
                if (nextRun.index >= NSMaxRange(rangeLimit)) {
                    endRun = nextRun;
                    break;
                }
                id nextValue = [nextRun.attributes objectForKey:attributeName];
                if (nextValue == value || (value != nil && [nextValue isEqual:value])) {
                    endRunIndex++;
                } else {
                    endRun = nextRun;
                    break;
                }
            }
            aRange->location = MAX(run.index, rangeLimit.location);
            aRange->length = MIN((endRun ? endRun.index : [_buffer length]), NSMaxRange(rangeLimit)) - aRange->location;
        } else {
            // with no attribute name, we don't need to do any real searching,
            // as we already guarantee each run has unique attributes.
            // just make sure to clip the range to the rangeLimit
            aRange->location = MAX(run.index, rangeLimit.location);
            ZAttributeRun *endRun = (runIndex+1 < [_attributes count] ? [_attributes objectAtIndex:runIndex+1] : nil);
            aRange->length = MIN((endRun ? endRun.index : [_buffer length]), NSMaxRange(rangeLimit)) - aRange->location;
        }
    }
    return run.attributes;
}

- (void)dealloc {
    [_buffer release];
    [_attributes release];
    [super dealloc];
}
@end

@interface ZMutableAttributedString ()
- (void)cleanupAttributesInRange:(NSRange)range;
- (NSRange)rangeOfAttributeRunsForRange:(NSRange)range;
- (void)offsetRunsInRange:(NSRange )range byOffset:(NSInteger)offset;
@end

@implementation ZMutableAttributedString
- (id)copyWithZone:(NSZone *)zone {
    return [(ZAttributedString *)[ZAttributedString allocWithZone:zone] initWithAttributedString:self];
}

- (void)addAttribute:(NSString *)name value:(id)value range:(NSRange)range {
    range = [self rangeOfAttributeRunsForRange:range];
    for (ZAttributeRun *run in [_attributes subarrayWithRange:range]) {
        [run.attributes setObject:value forKey:name];
    }
    [self cleanupAttributesInRange:range];
}

- (void)addAttributes:(NSDictionary *)attributes range:(NSRange)range {
    range = [self rangeOfAttributeRunsForRange:range];
    for (ZAttributeRun *run in [_attributes subarrayWithRange:range]) {
        [run.attributes addEntriesFromDictionary:attributes];
    }
    [self cleanupAttributesInRange:range];
}

- (void)appendAttributedString:(ZAttributedString *)str {
    [self insertAttributedString:str atIndex:[_buffer length]];
}

- (void)deleteCharactersInRange:(NSRange)range {
    NSRange runRange = [self rangeOfAttributeRunsForRange:range];
    [_buffer replaceCharactersInRange:range withString:@""];
    [_attributes removeObjectsInRange:runRange];
    for (NSUInteger i = runRange.location; i < [_attributes count]; i++) {
        ZAttributeRun *run = [_attributes objectAtIndex:i];
        ZAttributeRun *newRun = [[ZAttributeRun alloc] initWithIndex:(run.index - range.length) attributes:run.attributes];
        [_attributes replaceObjectAtIndex:i withObject:newRun];
        [newRun release];
    }
    [self cleanupAttributesInRange:NSMakeRange(runRange.location, 0)];
}

- (void)insertAttributedString:(ZAttributedString *)str atIndex:(NSUInteger)idx {
    [self replaceCharactersInRange:NSMakeRange(idx, 0) withAttributedString:str];
}

- (void)removeAttribute:(NSString *)name range:(NSRange)range {
    range = [self rangeOfAttributeRunsForRange:range];
    for (ZAttributeRun *run in [_attributes subarrayWithRange:range]) {
        [run.attributes removeObjectForKey:name];
    }
    [self cleanupAttributesInRange:range];
}

- (void)replaceCharactersInRange:(NSRange)range withAttributedString:(ZAttributedString *)str {
    NSRange replaceRange = [self rangeOfAttributeRunsForRange:range];
    NSInteger offset = [str->_buffer length] - range.length;
    [_buffer replaceCharactersInRange:range withString:str->_buffer];
    [_attributes replaceObjectsInRange:replaceRange withObjectsFromArray:str->_attributes];
    NSRange newRange = NSMakeRange(replaceRange.location, [str->_attributes count]);
    [self offsetRunsInRange:newRange byOffset:range.location];
    [self offsetRunsInRange:NSMakeRange(NSMaxRange(newRange), [_attributes count] - NSMaxRange(newRange)) byOffset:offset];
    [self cleanupAttributesInRange:NSMakeRange(newRange.location, 0)];
    [self cleanupAttributesInRange:NSMakeRange(NSMaxRange(newRange), 0)];
}

- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)str {
    [self replaceCharactersInRange:range withAttributedString:[[[ZAttributedString alloc] initWithString:str] autorelease]];
}

- (void)setAttributedString:(ZAttributedString *)str {
    [_buffer release], _buffer = [str->_buffer mutableCopy];
    [_attributes release], _attributes = [str->_attributes mutableCopy];
}

- (void)setAttributes:(NSDictionary *)attributes range:(NSRange)range {
    range = [self rangeOfAttributeRunsForRange:range];
    for (ZAttributeRun *run in [_attributes subarrayWithRange:range]) {
        [run.attributes setDictionary:attributes];
    }
    [self cleanupAttributesInRange:range];
}

#pragma mark -

// splits the existing runs to provide one or more new runs for the given range
- (NSRange)rangeOfAttributeRunsForRange:(NSRange)range {
    NSParameterAssert(NSMaxRange(range) <= [_buffer length]);
    
    // find (or create) the first run
    NSUInteger first = 0;
    ZAttributeRun *lastRun = nil;
    for (;;first++) {
        if (first >= [_attributes count]) {
            // we didn't find a run
            first = [_attributes count];
            ZAttributeRun *newRun = [[ZAttributeRun alloc] initWithIndex:range.location attributes:lastRun.attributes];
            [_attributes addObject:newRun];
            [newRun release];
            break;
        }
        ZAttributeRun *run = [_attributes objectAtIndex:first];
        if (run.index == range.location) {
            break;
        } else if (run.index > range.location) {
            ZAttributeRun *newRun = [[ZAttributeRun alloc] initWithIndex:range.location attributes:lastRun.attributes];
            [_attributes insertObject:newRun atIndex:first];
            [newRun release];
            break;
        }
        lastRun = run;
    }
    
    if (((ZAttributeRun *)[_attributes lastObject]).index < NSMaxRange(range)) {
        NSRange subrange = NSMakeRange(first, [_attributes count] - first);
        if (NSMaxRange(range) < [_buffer length]) {
            ZAttributeRun *newRun = [[ZAttributeRun alloc] initWithIndex:NSMaxRange(range)
                                                              attributes:(NSDictionary*)[(ZAttributeRun *)[_attributes lastObject] attributes]];
            [_attributes addObject:newRun];
            [newRun release];
        }
        return subrange;
    } else {
        // find the last run within and the first run after the range
        NSUInteger lastIn = first, firstAfter = [_attributes count]-1;
        while (firstAfter > lastIn + 1) {
            NSUInteger idx = (firstAfter + lastIn) / 2;
            ZAttributeRun *run = [_attributes objectAtIndex:idx];
            if (run.index < range.location) {
                lastIn = idx;
            } else if (run.index > range.location) {
                firstAfter = idx;
            } else {
                // this is definitively the first run after the range
                firstAfter = idx;
                break;
            }
        }
        if ([[_attributes objectAtIndex:firstAfter] index] > NSMaxRange(range)) {
            // the first after is too far after, insert another run!
            ZAttributeRun *newRun = [[ZAttributeRun alloc] initWithIndex:NSMaxRange(range)
                                                              attributes:[(ZAttributeRun *)[_attributes objectAtIndex:firstAfter-1] attributes]];
            [_attributes insertObject:newRun atIndex:firstAfter];
            [newRun release];
        }
        return NSMakeRange(lastIn, firstAfter - lastIn);
    }
}

- (void)cleanupAttributesInRange:(NSRange)range {
    // expand the range to include one surrounding attribute on each side
    if (range.location > 0) {
        range.location -= 1;
        range.length += 1;
    }
    if (NSMaxRange(range) < [_attributes count]) {
        range.length += 1;
    } else {
        // make sure the range is capped to the attributes count
        range.length = [_attributes count] - range.location;
    }
    if (range.length == 0) return;
    ZAttributeRun *lastRun = [_attributes objectAtIndex:range.location];
    for (NSUInteger i = range.location+1; i < NSMaxRange(range);) {
        ZAttributeRun *run = [_attributes objectAtIndex:i];
        if ([lastRun.attributes isEqualToDictionary:run.attributes]) {
            [_attributes removeObjectAtIndex:i];
            range.length -= 1;
        } else {
            lastRun = run;
            i++;
        }
    }
}

- (void)offsetRunsInRange:(NSRange)range byOffset:(NSInteger)offset {
    for (NSUInteger i = range.location; i < NSMaxRange(range); i++) {
        ZAttributeRun *run = [_attributes objectAtIndex:i];
        ZAttributeRun *newRun = [[ZAttributeRun alloc] initWithIndex:run.index + offset attributes:run.attributes];
        [_attributes replaceObjectAtIndex:i withObject:newRun];
        [newRun release];
    }
}
@end

@implementation ZAttributeRun
@synthesize index = _index;
@synthesize attributes = _attributes;

+ (id)attributeRunWithIndex:(NSUInteger)idx attributes:(NSDictionary *)attrs {
    return [[[self alloc] initWithIndex:idx attributes:attrs] autorelease];
}

- (id)initWithIndex:(NSUInteger)idx attributes:(NSDictionary *)attrs {
    NSParameterAssert(idx >= 0);
    if ((self = [super init])) {
        _index = idx;
        if (attrs == nil) {
            _attributes = [[NSMutableDictionary alloc] init];
        } else {
            _attributes = [attrs mutableCopy];
        }
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)decoder {
    if ((self = [super init])) {
        _index = [[decoder decodeObjectForKey:@"index"] unsignedIntegerValue];
        _attributes = [[decoder decodeObjectForKey:@"attributes"] mutableCopy];
    }
    return self;
}

- (id)init {
    return [self initWithIndex:0 attributes:[NSDictionary dictionary]];
}

- (id)copyWithZone:(NSZone *)zone {
    return [[ZAttributeRun allocWithZone:zone] initWithIndex:_index attributes:_attributes];
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeObject:[NSNumber numberWithUnsignedInteger:_index] forKey:@"index"];
    [aCoder encodeObject:_attributes forKey:@"attributes"];
}

- (NSString *)description {
    NSMutableArray *components = [NSMutableArray arrayWithCapacity:[_attributes count]];
    for (id key in _attributes) {
        [components addObject:[NSString stringWithFormat:@"%@=%@", key, [_attributes objectForKey:key]]];
    }
    return [NSString stringWithFormat:@"<%@: %p index=%lu attributes={%@}>",
            NSStringFromClass([self class]), self, (unsigned long)_index, [components componentsJoinedByString:@" "]];
}

- (BOOL)isEqual:(id)object {
    if (![object isKindOfClass:[ZAttributeRun class]]) return NO;
    ZAttributeRun *other = (ZAttributeRun *)object;
    return _index == other->_index && [_attributes isEqualToDictionary:other->_attributes];
}

- (void)dealloc {
    [_attributes release];
    [super dealloc];
}
@end

NSString * const ZFontAttributeName = @"ZFontAttributeName";
NSString * const ZForegroundColorAttributeName = @"ZForegroundColorAttributeName";
NSString * const ZBackgroundColorAttributeName = @"ZBackgroundColorAttributeName";
NSString * const ZUnderlineStyleAttributeName = @"ZUnderlineStyleAttributeName";
