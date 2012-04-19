/*
 * Copyright (C) 2011 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkAdvancedTypefaceMetrics_DEFINED
#define SkAdvancedTypefaceMetrics_DEFINED

#include "SkRect.h"
#include "SkRefCnt.h"
#include "SkString.h"
#include "SkTDArray.h"
#include "SkTemplates.h"
#include "SkTScopedPtr.h"

/** \class SkAdvancedTypefaceMetrics

    The SkAdvancedTypefaceMetrics class is used by the PDF backend to correctly
    embed typefaces.  This class is filled in with information about a given
    typeface by the SkFontHost class.
*/

class SkAdvancedTypefaceMetrics : public SkRefCnt {
public:
    SkString fFontName;

    enum FontType {
        kType1_Font,
        kType1CID_Font,
        kCFF_Font,
        kTrueType_Font,
        kOther_Font,
        kNotEmbeddable_Font,
    };
    // The type of the underlying font program.  This field determines which
    // of the following fields are valid.  If it is kOther_Font or
    // kNotEmbeddable_Font, the per glyph information will never be populated.
    FontType fType;

    // fMultiMaster may be true for Type1_Font or CFF_Font.
    bool fMultiMaster;
    uint16_t fLastGlyphID; // The last valid glyph ID in the font.
    uint16_t fEmSize;  // The size of the em box (defines font units).

    // These enum values match the values used in the PDF file format.
    enum StyleFlags {
        kFixedPitch_Style  = 0x00001,
        kSerif_Style       = 0x00002,
        kSymbolic_Style    = 0x00004,
        kScript_Style      = 0x00008,
        kNonsymbolic_Style = 0x00020,
        kItalic_Style      = 0x00040,
        kAllCaps_Style     = 0x10000,
        kSmallCaps_Style   = 0x20000,
        kForceBold_Style   = 0x40000,
    };
    uint16_t fStyle;        // Font style characteristics.
    int16_t fItalicAngle;   // Counterclockwise degrees from vertical of the
                            // dominant vertical stroke for an Italic face.
    // The following fields are all in font units.
    int16_t fAscent;       // Max height above baseline, not including accents.
    int16_t fDescent;      // Max depth below baseline (negative).
    int16_t fStemV;        // Thickness of dominant vertical stem.
    int16_t fCapHeight;    // Height (from baseline) of top of flat capitals.

    SkIRect fBBox;  // The bounding box of all glyphs (in font units).

    // The type of advance data wanted.
    enum PerGlyphInfo {
      kNo_PerGlyphInfo         = 0x0, // Don't populate any per glyph info.
      kHAdvance_PerGlyphInfo   = 0x1, // Populate horizontal advance data.
      kVAdvance_PerGlyphInfo   = 0x2, // Populate vertical advance data.
      kGlyphNames_PerGlyphInfo = 0x4, // Populate glyph names (Type 1 only).
      kToUnicode_PerGlyphInfo  = 0x8, // Populate ToUnicode table, ignored
                                      // for Type 1 fonts
    };

    template <typename Data>
    struct AdvanceMetric {
        enum MetricType {
            kDefault,  // Default advance: fAdvance.count = 1
            kRange,    // Advances for a range: fAdvance.count = fEndID-fStartID
            kRun,      // fStartID-fEndID have same advance: fAdvance.count = 1
        };
        MetricType fType;
        uint16_t fStartId;
        uint16_t fEndId;
        SkTDArray<Data> fAdvance;
        SkTScopedPtr<AdvanceMetric<Data> > fNext;
    };

    struct VerticalMetric {
        int16_t fVerticalAdvance;
        int16_t fOriginXDisp;  // Horiz. displacement of the secondary origin.
        int16_t fOriginYDisp;  // Vert. displacement of the secondary origin.
    };
    typedef AdvanceMetric<int16_t> WidthRange;
    typedef AdvanceMetric<VerticalMetric> VerticalAdvanceRange;

    // This is indexed by glyph id.
    SkTScopedPtr<WidthRange> fGlyphWidths;
    // Only used for Vertical CID fonts.
    SkTScopedPtr<VerticalAdvanceRange> fVerticalMetrics;

    // The names of each glyph, only populated for postscript fonts.
    SkTScopedPtr<SkAutoTArray<SkString> > fGlyphNames;

    // The mapping from glyph to Unicode, only populated if
    // kToUnicode_PerGlyphInfo is passed to GetAdvancedTypefaceMetrics.
    SkTDArray<SkUnichar> fGlyphToUnicode;
};

namespace skia_advanced_typeface_metrics_utils {

template <typename Data>
void resetRange(SkAdvancedTypefaceMetrics::AdvanceMetric<Data>* range,
                       int startId);

template <typename Data>
SkAdvancedTypefaceMetrics::AdvanceMetric<Data>* appendRange(
        SkTScopedPtr<SkAdvancedTypefaceMetrics::AdvanceMetric<Data> >* nextSlot,
        int startId);

template <typename Data>
void finishRange(
        SkAdvancedTypefaceMetrics::AdvanceMetric<Data>* range,
        int endId,
        typename SkAdvancedTypefaceMetrics::AdvanceMetric<Data>::MetricType
                type);

template <typename Data, typename FontHandle>
SkAdvancedTypefaceMetrics::AdvanceMetric<Data>* getAdvanceData(
        FontHandle fontHandle,
        int num_glyphs,
        bool (*getAdvance)(FontHandle fontHandle, int gId, Data* data));

} // namespace skia_advanced_typeface_metrics_utils

#endif
