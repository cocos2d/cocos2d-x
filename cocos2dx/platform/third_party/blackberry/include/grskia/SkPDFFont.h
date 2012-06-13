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

#ifndef SkPDFFont_DEFINED
#define SkPDFFont_DEFINED

#include "SkAdvancedTypefaceMetrics.h"
#include "SkPDFTypes.h"
#include "SkTDArray.h"
#include "SkThread.h"

class SkPaint;

/** \class SkPDFFont
    A PDF Object class representing a font.  The font may have resources
    attached to it in order to embed the font.  SkPDFFonts are canonicalized
    so that resource deduplication will only include one copy of a font.
    This class uses the same pattern as SkPDFGraphicState, a static weak
    reference to each instantiated class.
*/
class SkPDFFont : public SkPDFDict {
public:
    SK_API virtual ~SkPDFFont();

    SK_API virtual void getResources(SkTDArray<SkPDFObject*>* resourceList);

    /** Returns the typeface represented by this class. Returns NULL for the
     *  default typeface.
     */
    SK_API SkTypeface* typeface();

    /** Returns the font type represented in this font.  For Type0 fonts,
     *  returns the type of the decendant font.
     */
    SK_API SkAdvancedTypefaceMetrics::FontType getType();

    /** Return true if this font has an encoding for the passed glyph id.
     */
    SK_API bool hasGlyph(uint16_t glyphID);

    /** Returns true if this font encoding supports glyph IDs above 255.
     */
    SK_API bool multiByteGlyphs();

    /** Convert (in place) the input glyph IDs into the font encoding.  If the
     *  font has more glyphs than can be encoded (like a type 1 font with more
     *  than 255 glyphs) this method only converts up to the first out of range
     *  glyph ID.
     *  @param glyphIDs       The input text as glyph IDs.
     *  @param numGlyphs      The number of input glyphs.
     *  @return               Returns the number of glyphs consumed.
     */
    SK_API size_t glyphsToPDFFontEncoding(uint16_t* glyphIDs, size_t numGlyphs);

    /** Get the font resource for the passed typeface and glyphID. The
     *  reference count of the object is incremented and it is the caller's
     *  responsibility to unreference it when done.  This is needed to
     *  accommodate the weak reference pattern used when the returned object
     *  is new and has no other references.
     *  @param typeface  The typeface to find.
     *  @param glyphID   Specify which section of a large font is of interest.
     */
    SK_API static SkPDFFont* getFontResource(SkTypeface* typeface,
                                             uint16_t glyphID);

private:
    SkRefPtr<SkTypeface> fTypeface;
    SkAdvancedTypefaceMetrics::FontType fType;
#ifdef SK_DEBUG
    bool fDescendant;
#endif
    bool fMultiByteGlyphs;

    // The glyph IDs accessible with this font.  For Type1 (non CID) fonts,
    // this will be a subset if the font has more than 255 glyphs.
    uint16_t fFirstGlyphID;
    uint16_t fLastGlyphID;
    // The font info is only kept around after construction for large
    // Type1 (non CID) fonts that need multiple "fonts" to access all glyphs.
    SkRefPtr<SkAdvancedTypefaceMetrics> fFontInfo;
    SkTDArray<SkPDFObject*> fResources;
    SkRefPtr<SkPDFDict> fDescriptor;

    class FontRec {
    public:
        SkPDFFont* fFont;
        uint32_t fFontID;
        uint16_t fGlyphID;

        // A fGlyphID of 0 with no fFont always matches.
        bool operator==(const FontRec& b) const;
        FontRec(SkPDFFont* font, uint32_t fontID, uint16_t fGlyphID);
    };

    // This should be made a hash table if performance is a problem.
    static SkTDArray<FontRec>& canonicalFonts();
    static SkMutex& canonicalFontsMutex();

    /** Construct a new font dictionary and support objects.
     *  @param fontInfo       Information about the to create.
     *  @param typeface       The typeface for the font.
     *  @param glyphID        The glyph ID the caller is interested in. This
     *                        is important only for Type1 fonts, which have
     *                        more than 255 glyphs.
     *  @param descendantFont If this is the descendant (true) or root
     *                        (Type 0 font - false) font dictionary.  Only True
     *                        Type and CID encoded fonts will use a true value.
     *  @param fontDescriptor If the font descriptor has already have generated
     *                        for this font, pass it in here, otherwise pass
     *                        NULL.
     */
    SkPDFFont(class SkAdvancedTypefaceMetrics* fontInfo, SkTypeface* typeface,
              uint16_t glyphID, bool descendantFont, SkPDFDict* fontDescriptor);

    void populateType0Font();
    void populateCIDFont();
    bool populateType1Font(int16_t glyphID);

    /** Populate the PDF font dictionary as Type3 font which includes glyph
     *  descriptions with instructions for painting the glyphs. This function
     *  doesn't use any fields from SkAdvancedTypefaceMetrics (fFontInfo). Font
     *  information including glyph paths are queried from the platform
     *  dependent SkGlyphCache.
    */
    void populateType3Font(int16_t glyphID);
    bool addFontDescriptor(int16_t defaultWidth);
    void populateToUnicodeTable();
    void addWidthInfoFromRange(int16_t defaultWidth,
        const SkAdvancedTypefaceMetrics::WidthRange* widthRangeEntry);
    /** Set fFirstGlyphID and fLastGlyphID to span at most 255 glyphs,
     *  including the passed glyphID.
     */
    void adjustGlyphRangeForSingleByteEncoding(int16_t glyphID);

    static bool find(uint32_t fontID, uint16_t glyphID, int* index);
};

#endif
