/*
 * Copyright (C) 2006 The Android Open Source Project
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

#ifndef SkTextBox_DEFINED
#define SkTextBox_DEFINED

#include "SkCanvas.h"

/** \class SkTextBox

    SkTextBox is a helper class for drawing 1 or more lines of text
    within a rectangle. The textbox is positioned and clipped by its Frame.
    The Margin rectangle controls where the text is drawn relative to
    the Frame. Line-breaks occur inside the Margin rectangle.

    Spacing is a linear equation used to compute the distance between lines
    of text. Spacing consists of two scalars: mul and add, and the spacing
    between lines is computed as: spacing = paint.getTextSize() * mul + add
*/
class SkTextBox {
public:
    SkTextBox();

    enum Mode {
        kOneLine_Mode,
        kLineBreak_Mode,

        kModeCount
    };
    Mode    getMode() const { return (Mode)fMode; }
    void    setMode(Mode);

    enum SpacingAlign {
        kStart_SpacingAlign,
        kCenter_SpacingAlign,
        kEnd_SpacingAlign,

        kSpacingAlignCount
    };
    SpacingAlign    getSpacingAlign() const { return (SpacingAlign)fSpacingAlign; }
    void            setSpacingAlign(SpacingAlign);

    void    getBox(SkRect*) const;
    void    setBox(const SkRect&);
    void    setBox(SkScalar left, SkScalar top, SkScalar right, SkScalar bottom);

    void    getSpacing(SkScalar* mul, SkScalar* add) const;
    void    setSpacing(SkScalar mul, SkScalar add);

    void    draw(SkCanvas*, const char text[], size_t len, const SkPaint&);

    void    setText(const char text[], size_t len, const SkPaint&);
    void    draw(SkCanvas*);
    int     countLines() const;
    SkScalar getTextHeight() const;

private:
    SkRect      fBox;
    SkScalar    fSpacingMul, fSpacingAdd;
    uint8_t     fMode, fSpacingAlign;
    const char* fText;
    size_t      fLen;
    const SkPaint* fPaint;
};

class SkTextLineBreaker {
public:
    static int CountLines(const char text[], size_t len, const SkPaint&, SkScalar width);
};

#endif

