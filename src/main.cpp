#include "globals.hpp"
#include "grid.hpp"

#include <chrono>

#include <ftxui/component/screen_interactive.hpp>

bool running { true };
std::thread update_thread;
auto screen { ui::ScreenInteractive::Fullscreen() };

void exit() {
    running = false;
    if (update_thread.joinable()) {
        update_thread.join();
    }

    screen.ExitLoopClosure()();
}

int main() {
    constexpr std::chrono::milliseconds FRAME_TIME { 500 };
    const std::string emptyField { " " };

    screen.SetCursor(ui::Screen::Cursor {
        .shape = ui::Screen::Cursor::Shape::Hidden
    });

    Grid grid { ui::Dimension::Full(), emptyField };

    update_thread = std::thread([&] {
        while (running) {
            std::this_thread::sleep_for(FRAME_TIME);
            grid.update();
            screen.RequestAnimationFrame();
        }
    });

    auto event_handler = ui::CatchEvent(grid.getComponent(), [&](ui::Event event) {
        if (event == ui::Event::Character("q")) {
            exit();
            return true; // event handled
        }
        return false; // event not handled
    });

    screen.Loop(event_handler);
    return 0;
}