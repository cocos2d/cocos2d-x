
#import "NumberFormater.h"

@implementation NumberFormater

/*
 * @brief	Constructor.
 *
 */

+(NumberFormater *) formater {
    return [[[self alloc] init] autorelease];
}

- (id) init
{
	self = [super init];
	if (self != nil) {
	}
	return self;
}

/*
 * @brief	System's method for getting string.
 *
 */
- (NSString *) stringForObjectValue:(id)anObject
{
    return [NSString stringWithFormat:@"%@", anObject];
}

/*
 * @brief	System's method for getting value.
 *
 */
- (BOOL) getObjectValue:(id *)anObject forString:(NSString *)string errorDescription:(NSString **)error
{
    BOOL returnValue = NO;

	if(NULL != string)
    {
		*anObject = [NSNumber numberWithFloat:[string floatValue]];
		returnValue = YES;
	}
    else
    {
		*anObject = NULL;
		returnValue = NO;
		if (error) *error = NSLocalizedString(@"Couldn't convert  to int", @"Error converting");
	}
    return returnValue;
}

/*
 * @brief	System's method for getting attributed string.
 *
 */
- (NSAttributedString *) attributedStringForObjectValue:(id)anObject
                                  withDefaultAttributes:(NSDictionary *)attributes
{
	NSAttributedString	*result = [[[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"%d", [anObject intValue]]] autorelease];
	return result;
}

/*
 * @brief	System's method for checking si string valid.
 *
 */
- (BOOL) isPartialStringValid:(NSString **)partialStringPtr
        proposedSelectedRange:(NSRangePointer)proposedSelRangePtr
               originalString:(NSString *)origString
        originalSelectedRange:(NSRange)origSelRange
             errorDescription:(NSString **)error
{
	int i = 0;
    int dotCount = 0;
    
	// check the new string
	for(i = 0; i < [*partialStringPtr length]; i++)
    {
		char tmpChar = [*partialStringPtr characterAtIndex:i];
        if (tmpChar == '-' && i == 0)
        {
            continue;
        }
		else if(tmpChar < '0' || tmpChar > '9')
        {
            if (tmpChar == '.')
            {
                dotCount++;
                if (dotCount > 1)
                {
                    return NO;
                }
            }
            else
            {
                return NO;
            }

		}
	}
	return YES;
}


/*
 * @brief	Set the format.
 *
 * @param	form	the format to set
 */
- (void) setFormat:(NSString*)form
{
	format = form;
}

/*
 * @brief	Get the format.
 *
 * @return	the format
 */
- (NSString*) format
{
	return format;
}

@end
