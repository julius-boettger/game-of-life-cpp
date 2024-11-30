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

    std::atomic<bool> update_thread_running { true };
    std::thread update_thread { ([&] {
        while (update_thread_running) {
            std::this_thread::sleep_for(FRAME_TIME);
            grid.update();
            screen.RequestAnimationFrame();
        }
    }) };

    auto event_handler = ui::CatchEvent(grid.getComponent(), [&](ui::Event event) {
        constexpr char escape_key { 27 };
        if (event == ui::Event::Character('q') ||
            event == ui::Event::Character(escape_key))
        {
            screen.ExitLoopClosure()();
            return true; // event handled
        }
        return false; // event not handled
    });

    // start main loop which blocks the main thread
    // terminates on screen.ExitLoopClosure()() or SIGINT
    screen.Loop(event_handler);
    // main loop has ended, clean up!

    update_thread_running = false;
    update_thread.join();

    return 0;
}