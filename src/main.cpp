#include "globals.hpp"
#include "grid.hpp"

#include <chrono>

#include <ftxui/component/screen_interactive.hpp>

int main() {
    constexpr std::chrono::milliseconds FRAME_TIME { 500 };
    const std::string emptyField { " " };

    auto screen { ui::ScreenInteractive::Fullscreen() };
    screen.SetCursor(ui::Screen::Cursor {
        .shape = ui::Screen::Cursor::Shape::Hidden
    });

    Grid grid { ui::Dimension::Full(), emptyField };

    std::thread update_thread([&] {
        while (true) {
            std::this_thread::sleep_for(FRAME_TIME);
            grid.update();
            screen.RequestAnimationFrame();
        }
    });

    screen.Loop(grid.getComponent());
    return 0;
}