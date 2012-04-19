
#ifndef SkSfntUtils_DEFINED
#define SkSfntUtils_DEFINED

#include "SkFontHost.h"

struct SkSfntTable_head {
    SkFixed     fVersion;
    SkFixed     fRevision;
    uint32_t    fCheckSumAdjustment;
    uint32_t    fMagicNumber;
    uint16_t    fFlags;
    uint16_t    fUnitsPerEm;
    Sk64        fDateCreated;
    Sk64        fDateModified;
    int16_t     fXMin;
    int16_t     fYMin;
    int16_t     fXMax;
    int16_t     fYMax;
    uint16_t    fMacStyle;
    uint16_t    fLowestPPEM;
    int16_t     fFontDirectionHint;
    int16_t     fIndexToLocFormat;
    int16_t     fGlyphDataFormat;
};

struct SkSfntTable_maxp {
    SkFixed     fVersion;
    uint16_t    fNumGlyphs;
    uint16_t    fMaxPoints;
    uint16_t    fMaxContours;
    uint16_t    fMaxComponentPoints;
    uint16_t    fMaxComponentContours;
    uint16_t    fMaxZones;
    uint16_t    fMaxTwilightPoints;
    uint16_t    fMaxStorage;
    uint16_t    fMaxFunctionDefs;
    uint16_t    fMaxInstructionDefs;
    uint16_t    fMaxStackElements;
    uint16_t    fMaxSizeOfInstructions;
    uint16_t    fMaxComponentElements;
    uint16_t    fMaxComponentDepth;
};

class SkSfntUtils {
public:
    static bool ReadTable_head(SkFontID, SkSfntTable_head*);
    static bool ReadTable_maxp(SkFontID, SkSfntTable_maxp*);
};

#endif

