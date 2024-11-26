#include "globals.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

int main() {
    auto screen = ui::ScreenInteractive::Fullscreen();
    auto renderer = ui::Renderer([] {
        return ui::center(ui::text("Test"));
    });
    screen.Loop(renderer);
 
    return 0;
}