/*
 * Copyright (C) 2010 The Android Open Source Project
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
    virtual ~SkPDFFont();

    virtual void getResources(SkTDArray<SkPDFObject*>* resourceList);

    /* Returns the font ID represented by this class.
     */
    uint32_t fontID();

    /** Returns true if this font supports glyph IDs above 255.
     */
    bool multiByteGlyphs();

    /** Covert the specified text to glyph IDs, taking into consideration
     *  PDF encodings and return the number of glyphs IDs written.
     */
    int textToPDFGlyphs(const void* text, size_t byteLength,
                        const SkPaint& paint, uint16_t* glyphs,
                        size_t glyphsLength) const;

    /** Get the font resource for the passed font ID. The reference count of
     *  the object is incremented and it is the caller's responsibility to
     *  unreference it when done.  This is needed to accommodate the weak
     *  reference pattern used when the returned object is new and has no
     *  other references.
     *  @param paint  The SkPaint to emulate.
     */
    static SkPDFFont* getFontResouceByID(uint32_t fontID);

private:
    uint32_t fFontID;
    bool fMultiByteGlyphs;

    SkTDArray<SkPDFObject*> fResources;

    class FontRec {
    public:
        SkPDFFont* fFont;
        uint32_t fFontID;

        bool operator==(const FontRec& b) const;
        FontRec(SkPDFFont* font, uint32_t fontID);
    };

    // This should be made a hash table if performance is a problem.
    static SkTDArray<FontRec>& canonicalFonts();
    static SkMutex& canonicalFontsMutex();

    SkPDFFont(uint32_t fontID, bool multiByteGlyphs);

    void populateBuiltinFont(const char fontName[]);
    void populateFont(const char subType[], const char fontName[],
                      int firstChar, int lastChar, int widths[],
                      SkPDFObject* fontDescriptor);

    static int find(uint32_t fontID);
};

#endif
