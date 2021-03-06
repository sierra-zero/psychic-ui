#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <psychic-ui/Window.hpp>
#include <psychic-ui/components/Label.hpp>
#include <psychic-ui/components/Button.hpp>
#include <psychic-ui/components/Tabs.hpp>
#include <psychic-ui/components/TabContainer.hpp>
#include <psychic-ui/themes/default.hpp>
#include <psychic-ui/components/TitleBar.hpp>
#include <psychic-ui/components/ToolBar.hpp>
#include <psychic-ui/components/MenuBar.hpp>
#include <psychic-ui/components/Spacer.hpp>
#include "Typography.hpp"
#include "TextInputs.hpp"
#include "Buttons.hpp"
#include "Divs.hpp"
#include "Scrollers.hpp"
#include "Ranges.hpp"
#include "Colors.hpp"
#include "../demo-stylesheet.hpp"

namespace psychic_ui {
    class DemoWindow : public Window {

    public:
        DemoWindow();

    protected:
        void render(SkCanvas *canvas) override;

    private:
        std::shared_ptr<Label> fpsLabel{};
    };

    DemoWindow::DemoWindow() :
        Window("Demo Application") {
        _decorated = false;

        loadStyleSheet<OneDarkStyleSheet>();
        loadStyleSheet<DemoStyleSheet>();

        app->add<TitleBar>();

        std::vector<std::shared_ptr<MenuItem>> mainMenuContents{
            Menu::item(
                "File", {
                    Menu::item("New", []() {}, "Ctrl+N"),
                    Menu::item("Open", []() {}, "Ctrl+O"),
                    Menu::item(
                        "Open Recent...", {
                            Menu::item("My Resume3.docx", []() {}),
                            Menu::item("My Resume3.1-Final.docx", []() {}),
                            Menu::item("My Resume-FINAL-REAL.docx", []() {}),
                        }
                    ),
                    Menu::item("Save", []() {}, "Ctrl+S"),
                    Menu::item("Save As...", []() {}, "Ctrl+Shift+S"),
                    Menu::item("Quit", []() {}, "Ctrl+Q"),
                }
            ),
            Menu::item(
                "Edit", {
                    Menu::item("Copy", []() {}),
                    Menu::item("Cut", []() {}),
                    Menu::item("Paste", []() {}),
                }
            ),
            Menu::item(
                "View", {
                    Menu::item(
                        "Theme", {
                            Menu::item(
                                "Psychic", [this]() {
                                    loadStyleSheet<PsychicStyleSheet>(true);
                                    loadStyleSheet<DemoStyleSheet>();
                                }
                            ),
                            Menu::item(
                                "Dark", [this]() {
                                    loadStyleSheet<OneDarkStyleSheet>(true);
                                    loadStyleSheet<DemoStyleSheet>();
                                }
                            ),
                            Menu::item(
                                "Light", [this]() {
                                    loadStyleSheet<OneLightStyleSheet>(true);
                                    loadStyleSheet<DemoStyleSheet>();
                                }
                            )
                        }
                    ),
                    Menu::item(
                        "Toolbar Items", {
                            Menu::item("Show Debug Layout", []() {}),
                            Menu::item("Show Help", []() {})
                        }
                    ),
                    Menu::item(
                        "Panels", {
                            Menu::item("Show Inspector", []() {}),
                            Menu::item("Show Status Bar", []() {})
                        }
                    ),
                }
            ),
            Menu::item("Window", []() {}),
            Menu::item("Help", []() {})
        };

        app->add<MenuBar>(mainMenuContents);

        auto toolBar = app->add<ToolBar>();
        toolBar->add<Button>("New");
        toolBar->add<Button>("Start");
        toolBar->add<Button>("Stop");

        toolBar->add<Spacer>();

        #ifdef DEBUG_LAYOUT
        toolBar->add<Button>("Debug Layout")
            ->setToggle(true)
            ->onChange([](bool selected) { Div::debugLayout = selected; });
        #endif
        toolBar->add<Button>("Help");

        std::vector<std::pair<std::string, std::shared_ptr<Hatcher<std::shared_ptr<Div>>>>> panels{};
        panels.emplace_back(std::make_pair("Divs", Hatcher<std::shared_ptr<Div>>::make([]() { return std::make_shared<Divs>(); })));
        panels.emplace_back(std::make_pair("Scroller", Hatcher<std::shared_ptr<Div>>::make([]() { return std::make_shared<Scrollers>(); })));
        panels.emplace_back(std::make_pair("Typography", Hatcher<std::shared_ptr<Div>>::make([]() { return std::make_shared<Typography>(); })));
        panels.emplace_back(std::make_pair("Text Input", Hatcher<std::shared_ptr<Div>>::make([]() { return std::make_shared<TextInputs>(); })));
        panels.emplace_back(std::make_pair("Buttons", Hatcher<std::shared_ptr<Div>>::make([]() { return std::make_shared<Buttons>(); })));
        panels.emplace_back(std::make_pair("Ranges", Hatcher<std::shared_ptr<Div>>::make([]() { return std::make_shared<Ranges>(); })));
        panels.emplace_back(std::make_pair("Colors", Hatcher<std::shared_ptr<Div>>::make([]() { return std::make_shared<Colors>(); })));

        app->add<TabContainer<std::pair<std::string, std::shared_ptr<Hatcher<std::shared_ptr<Div>>>>>>(
               panels,
               [](const auto &item) -> std::string {
                   return item.first;
               },
               [](const auto &item) {
                   auto panel = item.second->hatch();
                   panel->style()->set(heightPercent, 1.0f);
                   return panel;
               }
           )
           ->select(panels[3])
           ->style()
           ->set(heightPercent, 1.f);

        fpsLabel = app->add<Label>();
        fpsLabel->style()
                ->set(fontFamily, "stan0755")
                ->set(fontSize, 8)
                ->set(textAntiAlias, false)
                ->set(position, "absolute")
                ->set(right, 0);
    }

    void DemoWindow::render(SkCanvas *canvas) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(3) << fps;
        fpsLabel->setText("FPS: " + stream.str());
        Window::render(canvas);
    }
}
