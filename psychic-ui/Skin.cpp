#include "Skin.hpp"

namespace psychic_ui {
    namespace internal {
        // TODO: This is getting out of hand, maybe just an exclusion list would be better
        const InheritableValues SkinBase::_inheritableValues{
            {
                color,
                backgroundColor,
                borderColor,
                borderHorizontalColor,
                borderLeftColor,
                borderRightColor,
                borderVerticalColor,
                borderTopColor,
                borderBottomColor,
                selectionColor,
                selectionBackgroundColor,
                contentBackgroundColor
            },
            {
                fontFamily, textAlign, textJustify,
                direction, justifyContent, flexDirection, alignContent, alignItems,
                flexWrap, overflow,
                orientation
            },
            {
                opacity,
                fontSize,  letterSpacing, lineHeight,
                padding,
                paddingHorizontal, paddingLeft, paddingRight,
                paddingVertical, paddingTop, paddingBottom,
                paddingPercent,
                paddingHorizontalPercent, paddingLeftPercent, paddingRightPercent,
                paddingVerticalPercent, paddingTopPercent, paddingBottomPercent,
                border, borderHorizontal, borderLeft, borderRight, borderVertical, borderTop, borderBottom,
                borderRadius, borderRadiusTop, borderRadiusBottom, borderRadiusLeft, borderRadiusRight,
                borderRadiusTopLeft, borderRadiusTopRight, borderRadiusBottomLeft, borderRadiusBottomRight
            },
            {
                cursor,
                gap
            },
            {
                antiAlias,
                textAntiAlias
            }
        };

        SkinBase::SkinBase() :
            Div() {
            setTag("Skin");
            _inlineStyle
                ->set(shrink, 1)
                ->set(grow, 1);
        }

        const InheritableValues SkinBase::inheritableValues() const {
            return _inheritableValues;
        }
    }
}
