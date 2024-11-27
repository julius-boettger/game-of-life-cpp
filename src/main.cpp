#include "globals.hpp"
#include "grid.hpp"

#include <ftxui/component/screen_interactive.hpp>

int main() {
    auto screen { ui::ScreenInteractive::Fullscreen() };
    screen.SetCursor(ui::Screen::Cursor {
        .shape = ui::Screen::Cursor::Shape::Hidden
    });

    Grid grid { ui::Dimension::Full(), " " };
    grid.set(0, 0, "█");
    grid.set(0, 1, "█");
    grid.set(1, 0, "█");
    grid.set(1, 1, "█");

    screen.Loop(grid.getComponent());
    return 0;
}