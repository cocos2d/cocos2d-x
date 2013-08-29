/*
 *  Base64Transcoder.c
 *  Base64Test
 *
 *  Created by Jonathan Wight on Tue Mar 18 2003.
 *  Copyright (c) 2003 Toxic Software. All rights reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 */

#include "Base64TranscoderFHS.h"

#include <math.h>
#include <string.h>

const u_int8_t kBase64EncodeTable_[64] = {
	/*  0 */ 'A',	/*  1 */ 'B',	/*  2 */ 'C',	/*  3 */ 'D', 
	/*  4 */ 'E',	/*  5 */ 'F',	/*  6 */ 'G',	/*  7 */ 'H', 
	/*  8 */ 'I',	/*  9 */ 'J',	/* 10 */ 'K',	/* 11 */ 'L', 
	/* 12 */ 'M',	/* 13 */ 'N',	/* 14 */ 'O',	/* 15 */ 'P', 
	/* 16 */ 'Q',	/* 17 */ 'R',	/* 18 */ 'S',	/* 19 */ 'T', 
	/* 20 */ 'U',	/* 21 */ 'V',	/* 22 */ 'W',	/* 23 */ 'X', 
	/* 24 */ 'Y',	/* 25 */ 'Z',	/* 26 */ 'a',	/* 27 */ 'b', 
	/* 28 */ 'c',	/* 29 */ 'd',	/* 30 */ 'e',	/* 31 */ 'f', 
	/* 32 */ 'g',	/* 33 */ 'h',	/* 34 */ 'i',	/* 35 */ 'j', 
	/* 36 */ 'k',	/* 37 */ 'l',	/* 38 */ 'm',	/* 39 */ 'n', 
	/* 40 */ 'o',	/* 41 */ 'p',	/* 42 */ 'q',	/* 43 */ 'r', 
	/* 44 */ 's',	/* 45 */ 't',	/* 46 */ 'u',	/* 47 */ 'v', 
	/* 48 */ 'w',	/* 49 */ 'x',	/* 50 */ 'y',	/* 51 */ 'z', 
	/* 52 */ '0',	/* 53 */ '1',	/* 54 */ '2',	/* 55 */ '3', 
	/* 56 */ '4',	/* 57 */ '5',	/* 58 */ '6',	/* 59 */ '7', 
	/* 60 */ '8',	/* 61 */ '9',	/* 62 */ '+',	/* 63 */ '/'
};

/*
-1 = Base64 end of data marker.
-2 = White space (tabs, cr, lf, space)
-3 = Noise (all non whitespace, non-base64 characters) 
-4 = Dangerous noise
-5 = Illegal noise (null byte)
*/

const int8_t kBase64DecodeTable_[128] = {
	/* 0x00 */ -5, 	/* 0x01 */ -3, 	/* 0x02 */ -3, 	/* 0x03 */ -3,
	/* 0x04 */ -3, 	/* 0x05 */ -3, 	/* 0x06 */ -3, 	/* 0x07 */ -3,
	/* 0x08 */ -3, 	/* 0x09 */ -2, 	/* 0x0a */ -2, 	/* 0x0b */ -2,
	/* 0x0c */ -2, 	/* 0x0d */ -2, 	/* 0x0e */ -3, 	/* 0x0f */ -3,
	/* 0x10 */ -3, 	/* 0x11 */ -3, 	/* 0x12 */ -3, 	/* 0x13 */ -3,
	/* 0x14 */ -3, 	/* 0x15 */ -3, 	/* 0x16 */ -3, 	/* 0x17 */ -3,
	/* 0x18 */ -3, 	/* 0x19 */ -3, 	/* 0x1a */ -3, 	/* 0x1b */ -3,
	/* 0x1c */ -3, 	/* 0x1d */ -3, 	/* 0x1e */ -3, 	/* 0x1f */ -3,
	/* ' ' */ -2,	/* '!' */ -3,	/* '"' */ -3,	/* '#' */ -3,
	/* '$' */ -3,	/* '%' */ -3,	/* '&' */ -3,	/* ''' */ -3,
	/* '(' */ -3,	/* ')' */ -3,	/* '*' */ -3,	/* '+' */ 62,
	/* ',' */ -3,	/* '-' */ -3,	/* '.' */ -3,	/* '/' */ 63,
	/* '0' */ 52,	/* '1' */ 53,	/* '2' */ 54,	/* '3' */ 55,
	/* '4' */ 56,	/* '5' */ 57,	/* '6' */ 58,	/* '7' */ 59,
	/* '8' */ 60,	/* '9' */ 61,	/* ':' */ -3,	/* ';' */ -3,
	/* '<' */ -3,	/* '=' */ -1,	/* '>' */ -3,	/* '?' */ -3,
	/* '@' */ -3,	/* 'A' */ 0,	/* 'B' */  1,	/* 'C' */  2,
	/* 'D' */  3,	/* 'E' */  4,	/* 'F' */  5,	/* 'G' */  6,
	/* 'H' */  7,	/* 'I' */  8,	/* 'J' */  9,	/* 'K' */ 10,
	/* 'L' */ 11,	/* 'M' */ 12,	/* 'N' */ 13,	/* 'O' */ 14,
	/* 'P' */ 15,	/* 'Q' */ 16,	/* 'R' */ 17,	/* 'S' */ 18,
	/* 'T' */ 19,	/* 'U' */ 20,	/* 'V' */ 21,	/* 'W' */ 22,
	/* 'X' */ 23,	/* 'Y' */ 24,	/* 'Z' */ 25,	/* '[' */ -3,
	/* '\' */ -3,	/* ']' */ -3,	/* '^' */ -3,	/* '_' */ -3,
	/* '`' */ -3,	/* 'a' */ 26,	/* 'b' */ 27,	/* 'c' */ 28,
	/* 'd' */ 29,	/* 'e' */ 30,	/* 'f' */ 31,	/* 'g' */ 32,
	/* 'h' */ 33,	/* 'i' */ 34,	/* 'j' */ 35,	/* 'k' */ 36,
	/* 'l' */ 37,	/* 'm' */ 38,	/* 'n' */ 39,	/* 'o' */ 40,
	/* 'p' */ 41,	/* 'q' */ 42,	/* 'r' */ 43,	/* 's' */ 44,
	/* 't' */ 45,	/* 'u' */ 46,	/* 'v' */ 47,	/* 'w' */ 48,
	/* 'x' */ 49,	/* 'y' */ 50,	/* 'z' */ 51,	/* '{' */ -3,
	/* '|' */ -3,	/* '}' */ -3,	/* '~' */ -3,	/* 0x7f */ -3
};

const u_int8_t kBits_00000011_ = 0x03;
const u_int8_t kBits_00001111_ = 0x0F;
const u_int8_t kBits_00110000_ = 0x30;
const u_int8_t kBits_00111100_ = 0x3C;
const u_int8_t kBits_00111111_ = 0x3F;
const u_int8_t kBits_11000000_ = 0xC0;
const u_int8_t kBits_11110000_ = 0xF0;
const u_int8_t kBits_11111100_ = 0xFC;

size_t EstimateBas64EncodedDataSizeFHS(size_t inDataSize) {
    size_t theEncodedDataSize = (int)ceil(inDataSize / 3.0) * 4;
    theEncodedDataSize = theEncodedDataSize / 72 * 74 + theEncodedDataSize % 72;
    return(theEncodedDataSize);
}

size_t EstimateBas64DecodedDataSizeFHS(size_t inDataSize)   {
    size_t theDecodedDataSize = (int)ceil(inDataSize / 4.0) * 3;
    //theDecodedDataSize = theDecodedDataSize / 72 * 74 + theDecodedDataSize % 72;
    return(theDecodedDataSize);
}

bool Base64EncodeDataFHS(const void *inInputData, size_t inInputDataSize, char *outOutputData, size_t *ioOutputDataSize) {
    
    size_t theEncodedDataSize = EstimateBas64EncodedDataSizeFHS(inInputDataSize);
    if (*ioOutputDataSize < theEncodedDataSize) {
        return false;
    }
    
    *ioOutputDataSize = theEncodedDataSize;
    const u_int8_t *theInPtr = (const u_int8_t *)inInputData;
    u_int32_t theInIndex = 0, theOutIndex = 0;
    for (; theInIndex < (inInputDataSize / 3) * 3; theInIndex += 3) {
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex] & kBits_11111100_) >> 2];
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex] & kBits_00000011_) << 4 | (theInPtr[theInIndex + 1] & kBits_11110000_) >> 4];
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex + 1] & kBits_00001111_) << 2 | (theInPtr[theInIndex + 2] & kBits_11000000_) >> 6];
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex + 2] & kBits_00111111_) >> 0];
        
        if (theOutIndex % 74 == 72) {
            outOutputData[theOutIndex++] = '\r';
            outOutputData[theOutIndex++] = '\n';
		}
	}
    
    const size_t theRemainingBytes = inInputDataSize - theInIndex;
    
    if (theRemainingBytes == 1) {
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex] & kBits_11111100_) >> 2];
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex] & kBits_00000011_) << 4 | (0 & kBits_11110000_) >> 4];
        outOutputData[theOutIndex++] = '=';
        outOutputData[theOutIndex++] = '=';
        
        if (theOutIndex % 74 == 72) {
            outOutputData[theOutIndex++] = '\r';
            outOutputData[theOutIndex++] = '\n';
		}
	} else if (theRemainingBytes == 2) {
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex] & kBits_11111100_) >> 2];
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex] & kBits_00000011_) << 4 | (theInPtr[theInIndex + 1] & kBits_11110000_) >> 4];
        outOutputData[theOutIndex++] = kBase64EncodeTable_[(theInPtr[theInIndex + 1] & kBits_00001111_) << 2 | (0 & kBits_11000000_) >> 6];
        outOutputData[theOutIndex++] = '=';
        
        if (theOutIndex % 74 == 72) {
            outOutputData[theOutIndex++] = '\r';
            outOutputData[theOutIndex++] = '\n';
		}
	}
    
    return true;
}

bool Base64DecodeData_(const void *inInputData, size_t inInputDataSize, void *ioOutputData, size_t *ioOutputDataSize) {
    
    memset(ioOutputData, '.', *ioOutputDataSize);

    size_t theDecodedDataSize = EstimateBas64DecodedDataSizeFHS(inInputDataSize);
    if (*ioOutputDataSize < theDecodedDataSize) {
        return false;
    }

    *ioOutputDataSize = 0;
    const u_int8_t *theInPtr = (const u_int8_t *)inInputData;
    u_int8_t *theOutPtr = (u_int8_t *)ioOutputData;
    size_t theInIndex = 0, theOutIndex = 0;
    u_int8_t theOutputOctet;
    size_t theSequence = 0;
    for (; theInIndex < inInputDataSize; ) {
        int8_t theSextet = 0;
	
        int8_t theCurrentInputOctet = theInPtr[theInIndex];
        theSextet = kBase64DecodeTable_[theCurrentInputOctet];
        
        if (theSextet == -1) {
            break;
        }
        
        while (theSextet == -2) {
            theCurrentInputOctet = theInPtr[++theInIndex];
            theSextet = kBase64DecodeTable_[theCurrentInputOctet];
		}
        
        while (theSextet == -3) {
            theCurrentInputOctet = theInPtr[++theInIndex];
            theSextet = kBase64DecodeTable_[theCurrentInputOctet];
		}
        
        if (theSequence == 0) {
            theOutputOctet = (theSextet >= 0 ? theSextet : 0) << 2 & kBits_11111100_;
		} else if (theSequence == 1) {
            theOutputOctet |= (theSextet >- 0 ? theSextet : 0) >> 4 & kBits_00000011_;
            theOutPtr[theOutIndex++] = theOutputOctet;
		} else if (theSequence == 2) {
            theOutputOctet = (theSextet >= 0 ? theSextet : 0) << 4 & kBits_11110000_;
		} else if (theSequence == 3) {
            theOutputOctet |= (theSextet >= 0 ? theSextet : 0) >> 2 & kBits_00001111_;
            theOutPtr[theOutIndex++] = theOutputOctet;
		} else if (theSequence == 4) {
            theOutputOctet = (theSextet >= 0 ? theSextet : 0) << 6 & kBits_11000000_;
		} else if (theSequence == 5) {
            theOutputOctet |= (theSextet >= 0 ? theSextet : 0) >> 0 & kBits_00111111_;
            theOutPtr[theOutIndex++] = theOutputOctet;
		}
        
        theSequence = (theSequence+1)%6;
        
        if (theSequence != 2 && theSequence != 4) {
            theInIndex++;
        }
    }
    *ioOutputDataSize = theOutIndex;
    return true;
}
