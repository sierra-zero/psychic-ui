#pragma once

#include "../Skin.hpp"
#include "../components/Range.hpp"
#include "../components/Label.hpp"

namespace psychicui {
    namespace internal {
        class SliderBase;
    }

    class SliderRangeSkin : public RangeSkin {
    public:
        SliderRangeSkin();
        void setValue(float value) override;

    protected:
        void added() override;
        void sendMouseValue(int x, int y);

        bool                       _dragging{false};
        std::shared_ptr<Label>     _value{nullptr};
        std::shared_ptr<Component> _track{nullptr};
        std::shared_ptr<Component> _range{nullptr};
    };
}
