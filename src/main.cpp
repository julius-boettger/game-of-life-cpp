#include "globals.hpp"

#include <format>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

int main() {
    auto screen { ui::ScreenInteractive::Fullscreen() };

    auto renderer { ui::Renderer([&] {
        auto dims { ui::Dimension::Full() };
        return ui::center(ui::text(std::format("{} x {}", dims.dimx, dims.dimy)));
    }) };

    screen.SetCursor(ui::Screen::Cursor {
        .shape = ui::Screen::Cursor::Shape::Hidden
    });

    screen.Loop(renderer);
 
    return 0;
}