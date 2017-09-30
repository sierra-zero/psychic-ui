#pragma once

/*
 * Modified version of Skia's TextBox
 *
 * Original code Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in Skia's LICENSE file.
 */

#include <memory>
#include <vector>
#include <unicode/unistr.h>
#include <unicode/brkiter.h>
#include <SkCanvas.h>
#include <SkPaint.h>
#include <SkTextBlob.h>

namespace psychic_ui {

    enum class TextBoxMode {
        OneLine,
        LineBreak,
    };

    enum TextBoxAlign {
        Start,
        Center,
        End,
    };

    using TextBoxVisitor = std::function<void(const char text[], size_t len, float x, float y)>;

    /**
     * @class SkTextBox
     *
     * SkTextBox is a helper class for drawing 1 or more lines of text
     * within a rectangle. The textbox is positioned and clipped by its Frame.
     * The Margin rectangle controls where the text is drawn relative to
     * the Frame. Line-breaks occur inside the Margin rectangle.
     *
     * Spacing is a linear equation used to compute the distance between lines
     * of text. Spacing consists of two scalars: mul and add, and the spacing
     * between lines is computed as: spacing = paint.getTextSize() * mul + add
     */
    class TextBox {
    public:
        TextBox();

        TextBoxMode getMode() const { return _mode; }

        void setMode(TextBoxMode);

        TextBoxAlign getAlign() const { return _align; }

        void setAlign(TextBoxAlign);
        void setBox(const SkRect &);
        void setBox(float left, float top, float right, float bottom);
        void setSpacing(float mul, float add);
        void setPaint(const SkPaint &);
        void setText(const UnicodeString &text);
        void draw(SkCanvas *);
        void recalculate();
        int countLines() const;
        unsigned int lineCount() const;
        float getTextHeight() const;
        std::unique_ptr<SkTextBlob, std::function<void(SkTextBlob *)>> snapshotTextBlob();

        unsigned int indexFromPos(int x, int y) const;
        std::pair<int, int> posFromIndex(int index) const;
        unsigned int lineStart(unsigned int line) const;
        unsigned int lineEnd(unsigned int line) const;
        unsigned int lineFromIndex(unsigned int index) const;

    protected:
        unsigned int nextLineBreak(int start) const;
        std::unique_ptr<BreakIterator> lineIterator{nullptr};
        std::unique_ptr<BreakIterator> wordIterator{nullptr};

    private:
        SkRect                    _box{};
        float                     _spacingMult{1.0f};
        float                     _spacingAdd{0.0f};
        TextBoxAlign              _align{TextBoxAlign::Start};
        TextBoxMode               _mode{TextBoxMode::LineBreak};
        const UnicodeString       *_text{nullptr};
        const SkPaint             *_paint{nullptr};
        std::vector<unsigned int> visit(TextBoxVisitor visitor) const;

        // Calculated values
        std::vector<unsigned int> _lineStarts{};
    };
}
